/*
 Copyright (c) 2010 Steve Oldmeadow
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 $Id$
 */

#import "CocosDenshion.h"

ALvoid  alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq);
ALvoid  alcMacOSXMixerOutputRateProc(const ALdouble value);


typedef ALvoid    AL_APIENTRY    (*alBufferDataStaticProcPtr) (const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq);
ALvoid  alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq)
{
    static    alBufferDataStaticProcPtr    proc = NULL;
    
    if (proc == NULL) {
        proc = (alBufferDataStaticProcPtr) alcGetProcAddress(NULL, (const ALCchar*) "alBufferDataStatic");
    }
    
    if (proc)
        proc(bid, format, data, size, freq);
    
    return;
}

typedef ALvoid    AL_APIENTRY    (*alcMacOSXMixerOutputRateProcPtr) (const ALdouble value);
ALvoid  alcMacOSXMixerOutputRateProc(const ALdouble value)
{
    static    alcMacOSXMixerOutputRateProcPtr    proc = NULL;
    
    if (proc == NULL) {
        proc = (alcMacOSXMixerOutputRateProcPtr) alcGetProcAddress(NULL, (const ALCchar*) "alcMacOSXMixerOutputRate");
    }
    
    if (proc)
        proc(value);
    
    return;
}

NSString * const kCDN_BadAlContext = @"kCDN_BadAlContext";
NSString * const kCDN_AsynchLoadComplete = @"kCDN_AsynchLoadComplete";
float const kCD_PitchDefault = 1.0f;
float const kCD_PitchLowerOneOctave = 0.5f;
float const kCD_PitchHigherOneOctave = 2.0f;
float const kCD_PanDefault = 0.0f;
float const kCD_PanFullLeft = -1.0f;
float const kCD_PanFullRight = 1.0f;
float const kCD_GainDefault = 1.0f;

@interface CDSoundEngine (PrivateMethods)
-(BOOL) _initOpenAL;
-(void) _testGetGain;
-(void) _dumpSourceGroupsInfo;
-(void) _getSourceIndexForSourceGroup;
-(void) _freeSourceGroups;
-(BOOL) _setUpSourceGroups:(int[]) definitions total:(NSUInteger) total; 
@end

#pragma mark - CDUtilities

@implementation CDUtilities

+(NSString*) fullPathFromRelativePath:(NSString*) relPath
{
    // do not convert an absolute path (starting with '/')
    if(([relPath length] > 0) && ([relPath characterAtIndex:0] == '/'))
    {
        return relPath;
    }
    
    NSMutableArray *imagePathComponents = [NSMutableArray arrayWithArray:[relPath pathComponents]];
    NSString *file = [imagePathComponents lastObject];
    
    [imagePathComponents removeLastObject];
    NSString *imageDirectory = [NSString pathWithComponents:imagePathComponents];
    
    NSString *fullpath = [[NSBundle mainBundle] pathForResource:file ofType:nil inDirectory:imageDirectory];
    if (fullpath == nil)
        fullpath = relPath;
    
    return fullpath;    
}

@end

#pragma mark -
#pragma mark CDSoundEngine

@implementation CDSoundEngine

static Float32 _mixerSampleRate;
static BOOL _mixerRateSet = NO;

@synthesize lastErrorCode = lastErrorCode_;
@synthesize functioning = functioning_;
@synthesize asynchLoadProgress = asynchLoadProgress_;
@synthesize getGainWorks = getGainWorks_;
@synthesize sourceTotal = sourceTotal_;

+ (void) setMixerSampleRate:(Float32) sampleRate {
    _mixerRateSet = YES;
    _mixerSampleRate = sampleRate;
}    

- (void) _testGetGain {
    float testValue = 0.7f;
    ALuint testSourceId = _sources[0].sourceId;
    alSourcef(testSourceId, AL_GAIN, 0.0f);//Start from know value
    alSourcef(testSourceId, AL_GAIN, testValue);
    ALfloat gainVal;
    alGetSourcef(testSourceId, AL_GAIN, &gainVal);
    getGainWorks_ = (gainVal == testValue);
}

//Generate sources one at a time until we fail
-(void) _generateSources {
    
    _sources = (sourceInfo*)malloc( sizeof(_sources[0]) * CD_SOURCE_LIMIT);
    BOOL hasFailed = NO;
    sourceTotal_ = 0;
    alGetError();//Clear error
    while (!hasFailed && sourceTotal_ < CD_SOURCE_LIMIT) {
        alGenSources(1, &(_sources[sourceTotal_].sourceId));
        if (alGetError() == AL_NO_ERROR) {
            //Now try attaching source to null buffer
            alSourcei(_sources[sourceTotal_].sourceId, AL_BUFFER, 0);
            if (alGetError() == AL_NO_ERROR) {
                _sources[sourceTotal_].usable = true;    
                sourceTotal_++;
            } else {
                hasFailed = YES;
            }    
        } else {
            _sources[sourceTotal_].usable = false;
            hasFailed = YES;
        }    
    }
    //Mark the rest of the sources as not usable
    for (int i=sourceTotal_; i < CD_SOURCE_LIMIT; i++) {
        _sources[i].usable = false;
    }    
}    

-(void) _generateBuffers:(int) startIndex endIndex:(int) endIndex {
    if (_buffers) {
        alGetError();
        for (int i=startIndex; i <= endIndex; i++) {
            alGenBuffers(1, &_buffers[i].bufferId);
            _buffers[i].bufferData = NULL;
            if (alGetError() == AL_NO_ERROR) {
                _buffers[i].bufferState = CD_BS_EMPTY;
            } else {
                _buffers[i].bufferState = CD_BS_FAILED;
                CDLOG(@"Denshion::CDSoundEngine - buffer creation failed %i",i);
            }    
        }
    }    
}

/**
 * Internal method called during init
 */
- (BOOL) _initOpenAL
{
    //ALenum            error;
    context = NULL;
    ALCdevice        *newDevice = NULL;

    //Set the mixer rate for the audio mixer
    if (!_mixerRateSet) {
        _mixerSampleRate = CD_SAMPLE_RATE_DEFAULT;
    }
    alcMacOSXMixerOutputRateProc(_mixerSampleRate);
    CDLOGINFO(@"Denshion::CDSoundEngine - mixer output rate set to %0.2f",_mixerSampleRate);
    
    // Create a new OpenAL Device
    // Pass NULL to specify the system's default output device
    newDevice = alcOpenDevice(NULL);
    if (newDevice != NULL)
    {
        // Create a new OpenAL Context
        // The new context will render to the OpenAL Device just created 
        context = alcCreateContext(newDevice, 0);
        if (context != NULL)
        {
            // Make the new context the Current OpenAL Context
            alcMakeContextCurrent(context);
            
            // Create some OpenAL Buffer Objects
            [self _generateBuffers:0 endIndex:bufferTotal-1];
            
            // Create some OpenAL Source Objects
            [self _generateSources];
            
        }
    } else {
        return FALSE;//No device
    }    
    alGetError();//Clear error
    return TRUE;
}

- (void) dealloc {
    
    ALCcontext    *currentContext = NULL;
    ALCdevice    *device = NULL;
    
    [self stopAllSounds];

    CDLOGINFO(@"Denshion::CDSoundEngine - Deallocing sound engine.");
    [self _freeSourceGroups];
    
    // Delete the Sources
    CDLOGINFO(@"Denshion::CDSoundEngine - deleting sources.");
    for (int i=0; i < sourceTotal_; i++) {
        alSourcei(_sources[i].sourceId, AL_BUFFER, 0);//Detach from current buffer
        alDeleteSources(1, &(_sources[i].sourceId));
        if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
            CDLOG(@"Denshion::CDSoundEngine - Error deleting source! %x\n", lastErrorCode_);
        } 
    }    

    // Delete the Buffers
    CDLOGINFO(@"Denshion::CDSoundEngine - deleting buffers.");
    for (int i=0; i < bufferTotal; i++) {
        alDeleteBuffers(1, &_buffers[i].bufferId);
#ifdef CD_USE_STATIC_BUFFERS
        if (_buffers[i].bufferData) {
            free(_buffers[i].bufferData);
        }    
#endif        
    }    
    CDLOGINFO(@"Denshion::CDSoundEngine - free buffers.");
    free(_buffers);
    currentContext = alcGetCurrentContext();
    //Get device for active context
    device = alcGetContextsDevice(currentContext);
    //Release context
    CDLOGINFO(@"Denshion::CDSoundEngine - destroy context.");
    alcMakeContextCurrent(NULL);
    alcDestroyContext(currentContext);
    //Close device
    CDLOGINFO(@"Denshion::CDSoundEngine - close device.");
    alcCloseDevice(device);
    CDLOGINFO(@"Denshion::CDSoundEngine - free sources.");
    free(_sources);
    
    //Release mutexes
    [_mutexBufferLoad release];
    
    [super dealloc];
}    

-(NSUInteger) sourceGroupTotal {
    return _sourceGroupTotal;
}    

-(void) _freeSourceGroups 
{
    CDLOGINFO(@"Denshion::CDSoundEngine freeing source groups");
    if(_sourceGroups) {
        for (int i=0; i < _sourceGroupTotal; i++) {
            if (_sourceGroups[i].sourceStatuses) {
                free(_sourceGroups[i].sourceStatuses);
                CDLOGINFO(@"Denshion::CDSoundEngine freed source statuses %i",i);
            }    
        }
        free(_sourceGroups);
    }    
}    

-(BOOL) _redefineSourceGroups:(int[]) definitions total:(NSUInteger) total
{
    if (_sourceGroups) {
        //Stop all sounds
        [self stopAllSounds];
        //Need to free source groups
        [self _freeSourceGroups];
    }
    return [self _setUpSourceGroups:definitions total:total];
}    

-(BOOL) _setUpSourceGroups:(int[]) definitions total:(NSUInteger) total 
{
    _sourceGroups = (sourceGroup *)malloc( sizeof(_sourceGroups[0]) * total);
    if(!_sourceGroups) {
        CDLOG(@"Denshion::CDSoundEngine - source groups memory allocation failed");
        return NO;
    }
    
    _sourceGroupTotal = total;
    int sourceCount = 0;
    for (int i=0; i < _sourceGroupTotal; i++) {
        
        _sourceGroups[i].startIndex = 0;
        _sourceGroups[i].currentIndex = _sourceGroups[i].startIndex;
        _sourceGroups[i].enabled = false;
        _sourceGroups[i].nonInterruptible = false;
        _sourceGroups[i].totalSources = definitions[i];
        _sourceGroups[i].sourceStatuses = malloc(sizeof(_sourceGroups[i].sourceStatuses[0]) * _sourceGroups[i].totalSources);
        if (_sourceGroups[i].sourceStatuses) {
            for (int j=0; j < _sourceGroups[i].totalSources; j++) {
                //First bit is used to indicate whether source is locked, index is shifted back 1 bit
                _sourceGroups[i].sourceStatuses[j] = (sourceCount + j) << 1;    
            }    
        }    
        sourceCount += definitions[i];
    }
    return YES;
}

-(void) defineSourceGroups:(int[]) sourceGroupDefinitions total:(NSUInteger) total {
    [self _redefineSourceGroups:sourceGroupDefinitions total:total];
}

-(void) defineSourceGroups:(NSArray*) sourceGroupDefinitions {
    CDLOGINFO(@"Denshion::CDSoundEngine - source groups defined by NSArray.");
    NSUInteger totalDefs = [sourceGroupDefinitions count];
    int* defs = (int *)malloc( sizeof(int) * totalDefs);
    int currentIndex = 0;
    for (id currentDef in sourceGroupDefinitions) {
        if ([currentDef isKindOfClass:[NSNumber class]]) {
            defs[currentIndex] = (int)[(NSNumber*)currentDef integerValue];
            CDLOGINFO(@"Denshion::CDSoundEngine - found definition %i.",defs[currentIndex]);
        } else {
            CDLOG(@"Denshion::CDSoundEngine - warning, did not understand source definition.");
            defs[currentIndex] = 0;
        }    
        currentIndex++;
    }
    [self _redefineSourceGroups:defs total:totalDefs];
    free(defs);
}    

- (id)init
{    
    if ((self = [super init])) {
        
        //Create mutexes
        _mutexBufferLoad = [[NSObject alloc] init];
        
        asynchLoadProgress_ = 0.0f;
        
        bufferTotal = CD_BUFFERS_START;
        _buffers = (bufferInfo *)malloc( sizeof(_buffers[0]) * bufferTotal);
    
        // Initialize our OpenAL environment
        if ([self _initOpenAL]) {
            //Set up the default source group - a single group that contains all the sources
            int sourceDefs[1];
            sourceDefs[0] = self.sourceTotal;
            [self _setUpSourceGroups:sourceDefs total:1];

            functioning_ = YES;
            //Synchronize premute gain
            _preMuteGain = self.masterGain;
            mute_ = NO;
            enabled_ = YES;
            //Test whether get gain works for sources
            [self _testGetGain];
        } else {
            //Something went wrong with OpenAL
            functioning_ = NO;
        }
    }
    
    return self;
}

/**
 * Delete the buffer identified by soundId
 * @return true if buffer deleted successfully, otherwise false
 */
- (BOOL) unloadBuffer:(int) soundId 
{
    //Ensure soundId is within array bounds otherwise memory corruption will occur
    if (soundId < 0 || soundId >= bufferTotal) {
        CDLOG(@"Denshion::CDSoundEngine - soundId is outside array bounds, maybe you need to increase CD_MAX_BUFFERS");
        return FALSE;
    }    
    
    //Before a buffer can be deleted any sources that are attached to it must be stopped
    for (int i=0; i < sourceTotal_; i++) {
        //Note: tried getting the AL_BUFFER attribute of the source instead but doesn't
        //appear to work on a device - just returned zero.
        if (_buffers[soundId].bufferId == _sources[i].attachedBufferId) {
            
            CDLOG(@"Denshion::CDSoundEngine - Found attached source %i %i %i",i,_buffers[soundId].bufferId,_sources[i].sourceId);
#ifdef CD_USE_STATIC_BUFFERS
            //When using static buffers a crash may occur if a source is playing with a buffer that is about
            //to be deleted even though we stop the source and successfully delete the buffer. Crash is confirmed
            //on 2.2.1 and 3.1.2, however, it will only occur if a source is used rapidly after having its prior
            //data deleted. To avoid any possibility of the crash we wait for the source to finish playing.
            ALint state;
            
            alGetSourcei(_sources[i].sourceId, AL_SOURCE_STATE, &state);
            
            if (state == AL_PLAYING) {
                CDLOG(@"Denshion::CDSoundEngine - waiting for source to complete playing before removing buffer data"); 
                alSourcei(_sources[i].sourceId, AL_LOOPING, FALSE);//Turn off looping otherwise loops will never end
                while (state == AL_PLAYING) {
                    alGetSourcei(_sources[i].sourceId, AL_SOURCE_STATE, &state);
                    usleep(10000);
                }
            }
#endif            
            //Stop source and detach
            alSourceStop(_sources[i].sourceId);    
            if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
                CDLOG(@"Denshion::CDSoundEngine - error stopping source: %x\n", lastErrorCode_);
            }    
            
            alSourcei(_sources[i].sourceId, AL_BUFFER, 0);//Attach to "NULL" buffer to detach
            if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
                CDLOG(@"Denshion::CDSoundEngine - error detaching buffer: %x\n", lastErrorCode_);
            } else {
                //Record that source is now attached to nothing
                _sources[i].attachedBufferId = 0;
            }    
        }    
    }    
    
    alDeleteBuffers(1, &_buffers[soundId].bufferId);
    if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
        CDLOG(@"Denshion::CDSoundEngine - error deleting buffer: %x\n", lastErrorCode_);
        _buffers[soundId].bufferState = CD_BS_FAILED;
        return FALSE;
    } else {
#ifdef CD_USE_STATIC_BUFFERS
        //Free previous data, if alDeleteBuffer has returned without error then no 
        if (_buffers[soundId].bufferData) {
            CDLOGINFO(@"Denshion::CDSoundEngine - freeing static data for soundId %i @ %i",soundId,_buffers[soundId].bufferData);
            free(_buffers[soundId].bufferData);//Free the old data
            _buffers[soundId].bufferData = NULL;
        }
#endif        
    }    
    
    alGenBuffers(1, &_buffers[soundId].bufferId);
    if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
        CDLOG(@"Denshion::CDSoundEngine - error regenerating buffer: %x\n", lastErrorCode_);
        _buffers[soundId].bufferState = CD_BS_FAILED;
        return FALSE;
    } else {
        //We now have an empty buffer
        _buffers[soundId].bufferState = CD_BS_EMPTY;
        CDLOGINFO(@"Denshion::CDSoundEngine - buffer %i successfully unloaded\n",soundId);
        return TRUE;
    }    
}    

/**
 * Load buffers asynchronously 
 * Check asynchLoadProgress for progress. asynchLoadProgress represents fraction of completion. When it equals 1.0 loading
 * is complete. NB: asynchLoadProgress is simply based on the number of load requests, it does not take into account
 * file sizes.
 * @param An array of CDBufferLoadRequest objects
 */
- (void) loadBuffersAsynchronously:(NSArray *) loadRequests {
    @synchronized(self) {
        asynchLoadProgress_ = 0.0f;
        CDAsynchBufferLoader *loaderOp = [[[CDAsynchBufferLoader alloc] init:loadRequests soundEngine:self] autorelease];
        NSOperationQueue *opQ = [[[NSOperationQueue alloc] init] autorelease];
        [opQ addOperation:loaderOp];
    }
}    

-(BOOL) _resizeBuffers:(int) increment {
    
    void * tmpBufferInfos = realloc( _buffers, sizeof(_buffers[0]) * (bufferTotal + increment) );
    
    if(!tmpBufferInfos) {
        free(tmpBufferInfos);
        return NO;
    } else {
        _buffers = tmpBufferInfos;
        int oldBufferTotal = bufferTotal;
        bufferTotal = bufferTotal + increment;
        [self _generateBuffers:oldBufferTotal endIndex:bufferTotal-1];
        return YES;
    }    
}    

-(BOOL) loadBufferFromData:(int) soundId soundData:(ALvoid*) soundData format:(ALenum) format size:(ALsizei) size freq:(ALsizei) freq {

    @synchronized(_mutexBufferLoad) {
        
        if (!functioning_) {
            //OpenAL initialisation has previously failed
            CDLOG(@"Denshion::CDSoundEngine - Loading buffer failed because sound engine state != functioning");
            return FALSE;
        }
        
        //Ensure soundId is within array bounds otherwise memory corruption will occur
        if (soundId < 0) {
            CDLOG(@"Denshion::CDSoundEngine - soundId is negative");
            return FALSE;
        }
        
        if (soundId >= bufferTotal) {
            //Need to resize the buffers
            int requiredIncrement = CD_BUFFERS_INCREMENT;
            while (bufferTotal + requiredIncrement < soundId) {
                requiredIncrement += CD_BUFFERS_INCREMENT;
            }
            CDLOGINFO(@"Denshion::CDSoundEngine - attempting to resize buffers by %i for sound %i",requiredIncrement,soundId);
            if (![self _resizeBuffers:requiredIncrement]) {
                CDLOG(@"Denshion::CDSoundEngine - buffer resize failed");
                return FALSE;
            }    
        }    
        
        if (soundData)
        {
            if (_buffers[soundId].bufferState != CD_BS_EMPTY) {
                CDLOGINFO(@"Denshion::CDSoundEngine - non empty buffer, regenerating");
                if (![self unloadBuffer:soundId]) {
                    //Deletion of buffer failed, delete buffer routine has set buffer state and lastErrorCode
                    return NO;
                }    
            }    
            
#ifdef CD_DEBUG
            //Check that sample rate matches mixer rate and warn if they do not
            if (freq != (int)_mixerSampleRate) {
                CDLOGINFO(@"Denshion::CDSoundEngine - WARNING sample rate does not match mixer sample rate performance may not be optimal.");
            }    
#endif        
            
#ifdef CD_USE_STATIC_BUFFERS
            alBufferDataStaticProc(_buffers[soundId].bufferId, format, soundData, size, freq);
            _buffers[soundId].bufferData = data;//Save the pointer to the new data
#else        
            alBufferData(_buffers[soundId].bufferId, format, soundData, size, freq);
#endif
            if((lastErrorCode_ = alGetError()) != AL_NO_ERROR) {
                CDLOG(@"Denshion::CDSoundEngine -  error attaching audio to buffer: %x", lastErrorCode_);
                _buffers[soundId].bufferState = CD_BS_FAILED;
                return FALSE;
            } 
        } else {
            CDLOG(@"Denshion::CDSoundEngine Buffer data is null!");
            _buffers[soundId].bufferState = CD_BS_FAILED;
            return FALSE;
        }    
        
        _buffers[soundId].format = format;
        _buffers[soundId].sizeInBytes = size;
        _buffers[soundId].frequencyInHertz = freq;
        _buffers[soundId].bufferState = CD_BS_LOADED;
        CDLOGINFO(@"Denshion::CDSoundEngine Buffer %i loaded format:%i freq:%i size:%i",soundId,format,freq,size);
        return TRUE;
    }//end mutex
}    

/**
 * Load sound data for later play back.
 * @return TRUE if buffer loaded okay for play back otherwise false
 */
- (BOOL) loadBuffer:(int) soundId filePath:(NSString*) filePath
{

    ALvoid* data;
    ALenum  format;
    ALsizei size;
    ALsizei freq;
    
    CDLOGINFO(@"Denshion::CDSoundEngine - Loading openAL buffer %i %@", soundId, filePath);
    
    CFURLRef fileURL = nil;
    NSString *path = [CDUtilities fullPathFromRelativePath:filePath];
    if (path) {
        fileURL = (CFURLRef)[[NSURL fileURLWithPath:path] retain];
    }

    if (fileURL)
    {
        data = CDGetOpenALAudioData(fileURL, &size, &format, &freq);
        CFRelease(fileURL);
        BOOL result = [self loadBufferFromData:soundId soundData:data format:format size:size freq:freq];
#ifndef CD_USE_STATIC_BUFFERS
        free(data);//Data can be freed here because alBufferData performs a memcpy        
#endif
        return result;
    } else {
        CDLOG(@"Denshion::CDSoundEngine Could not find file!\n");
        //Don't change buffer state here as it will be the same as before method was called    
        return FALSE;
    }    
}

-(BOOL) validateBufferId:(int) soundId {
    if (soundId < 0 || soundId >= bufferTotal) {
        CDLOGINFO(@"Denshion::CDSoundEngine - validateBufferId buffer outside range %i",soundId);
        return NO;
    } else if (_buffers[soundId].bufferState != CD_BS_LOADED) {
        CDLOGINFO(@"Denshion::CDSoundEngine - validateBufferId invalide buffer state %i",soundId);
        return NO;
    } else {
        return YES;
    }    
}    

-(float) bufferDurationInSeconds:(int) soundId {
    if ([self validateBufferId:soundId]) {
        float factor = 0.0f;
        switch (_buffers[soundId].format) {
            case AL_FORMAT_MONO8:
                factor = 1.0f;
                break;
            case AL_FORMAT_MONO16:
                factor = 0.5f;
                break;
            case AL_FORMAT_STEREO8:
                factor = 0.5f;
                break;
            case AL_FORMAT_STEREO16:
                factor = 0.25f;
                break;
        }    
        return (float)_buffers[soundId].sizeInBytes/(float)_buffers[soundId].frequencyInHertz * factor;
    } else {
        return -1.0f;
    }    
}    

-(ALsizei) bufferSizeInBytes:(int) soundId {
    if ([self validateBufferId:soundId]) {
        return _buffers[soundId].sizeInBytes;
    } else {
        return -1.0f;
    }    
}    

-(ALsizei) bufferFrequencyInHertz:(int) soundId {
    if ([self validateBufferId:soundId]) {
        return _buffers[soundId].frequencyInHertz;
    } else {
        return -1.0f;
    }    
}    

- (ALfloat) masterGain {
    if (mute_) {
        //When mute the real gain will always be 0 therefore return the preMuteGain value
        return _preMuteGain;
    } else {    
        ALfloat gain;
        alGetListenerf(AL_GAIN, &gain);
        return gain;
    }    
}    

/**
 * Overall gain setting multiplier. e.g 0.5 is half the gain.
 */
- (void) setMasterGain:(ALfloat) newGainValue {
    if (mute_) {
        _preMuteGain = newGainValue;
    } else {    
        alListenerf(AL_GAIN, newGainValue);
    }    
}

#pragma mark CDSoundEngine AudioInterrupt protocol
- (BOOL) mute {
    return mute_;
}    

/**
 * Setting mute silences all sounds but playing sounds continue to advance playback
 */
- (void) setMute:(BOOL) newMuteValue {
    
    if (newMuteValue == mute_) {
        return;
    }
    
    mute_ = newMuteValue;
    if (mute_) {
        //Remember what the gain was
        _preMuteGain = self.masterGain;
        //Set gain to 0 - do not use the property as this will adjust preMuteGain when muted
        alListenerf(AL_GAIN, 0.0f);
    } else {
        //Restore gain to what it was before being muted
        self.masterGain = _preMuteGain;
    }    
}

- (BOOL) enabled {
    return enabled_;
}

- (void) setEnabled:(BOOL)enabledValue
{
    if (enabled_ == enabledValue) {
        return;
    }    
    enabled_ = enabledValue;
    if (enabled_ == NO) {
        [self stopAllSounds];
    }    
}    

-(void) _lockSource:(int) sourceIndex lock:(BOOL) lock {
    BOOL found = NO;
    for (int i=0; i < _sourceGroupTotal && !found; i++) {
        if (_sourceGroups[i].sourceStatuses) {
            for (int j=0; j < _sourceGroups[i].totalSources && !found; j++) {
                //First bit is used to indicate whether source is locked, index is shifted back 1 bit
                if((_sourceGroups[i].sourceStatuses[j] >> 1)==sourceIndex) {
                    if (lock) {
                        //Set first bit to lock this source
                        _sourceGroups[i].sourceStatuses[j] |= 1;
                    } else {
                        //Unset first bit to unlock this source
                        _sourceGroups[i].sourceStatuses[j] &= ~1; 
                    }    
                    found = YES;
                }    
            }    
        }    
    }
}    

-(int) _getSourceIndexForSourceGroup:(int)sourceGroupId 
{
    //Ensure source group id is valid to prevent memory corruption
    if (sourceGroupId < 0 || sourceGroupId >= _sourceGroupTotal) {
        CDLOG(@"Denshion::CDSoundEngine invalid source group id %i",sourceGroupId);
        return CD_NO_SOURCE;
    }    

    int sourceIndex = -1;//Using -1 to indicate no source found
    BOOL complete = NO;
    ALint sourceState = 0;
    sourceGroup *thisSourceGroup = &_sourceGroups[sourceGroupId];
    thisSourceGroup->currentIndex = thisSourceGroup->startIndex;
    while (!complete) {
        //Iterate over sources looking for one that is not locked, first bit indicates if source is locked
        if ((thisSourceGroup->sourceStatuses[thisSourceGroup->currentIndex] & 1) == 0) {
            //This source is not locked
            sourceIndex = thisSourceGroup->sourceStatuses[thisSourceGroup->currentIndex] >> 1;//shift back to get the index
            if (thisSourceGroup->nonInterruptible) {
                //Check if this source is playing, if so it can't be interrupted
                alGetSourcei(_sources[sourceIndex].sourceId, AL_SOURCE_STATE, &sourceState);
                if (sourceState != AL_PLAYING) {
                    //complete = YES;
                    //Set start index so next search starts at the next position
                    thisSourceGroup->startIndex = thisSourceGroup->currentIndex + 1;
                    break;
                } else {
                    sourceIndex = -1;//The source index was no good because the source was playing
                }    
            } else {    
                //complete = YES;
                //Set start index so next search starts at the next position
                thisSourceGroup->startIndex = thisSourceGroup->currentIndex + 1;
                break;
            }    
        }
        thisSourceGroup->currentIndex++;
        if (thisSourceGroup->currentIndex >= thisSourceGroup->totalSources) {
            //Reset to the beginning
            thisSourceGroup->currentIndex = 0;    
        }    
        if (thisSourceGroup->currentIndex == thisSourceGroup->startIndex) {
            //We have looped around and got back to the start
            complete = YES;
        }    
    }

    //Reset start index to beginning if beyond bounds
    if (thisSourceGroup->startIndex >= thisSourceGroup->totalSources) {
        thisSourceGroup->startIndex = 0;    
    }    
    
    if (sourceIndex >= 0) {
        return sourceIndex;
    } else {    
        return CD_NO_SOURCE;
    }    
    
}    

/**
 * Play a sound.
 * @param soundId the id of the sound to play (buffer id).
 * @param SourceGroupId the source group that will be used to play the sound.
 * @param pitch pitch multiplier. e.g 1.0 is unaltered, 0.5 is 1 octave lower. 
 * @param pan stereo position. -1 is fully left, 0 is centre and 1 is fully right.
 * @param gain gain multiplier. e.g. 1.0 is unaltered, 0.5 is half the gain
 * @param loop should the sound be looped or one shot.
 * @return the id of the source being used to play the sound or CD_MUTE if the sound engine is muted or non functioning 
 * or CD_NO_SOURCE if a problem occurs setting up the source
 * 
 */
- (ALuint)playSound:(int) soundId sourceGroupId:(int)sourceGroupId pitch:(float) pitch pan:(float) pan gain:(float) gain loop:(BOOL) loop {

#ifdef CD_DEBUG
    //Sanity check parameters - only in DEBUG
    NSAssert(soundId >= 0, @"soundId can not be negative");
    NSAssert(soundId < bufferTotal, @"soundId exceeds limit");
    NSAssert(sourceGroupId >= 0, @"sourceGroupId can not be negative");
    NSAssert(sourceGroupId < _sourceGroupTotal, @"sourceGroupId exceeds limit");
    NSAssert(pitch > 0, @"pitch must be greater than zero");
    NSAssert(pan >= -1 && pan <= 1, @"pan must be between -1 and 1");
    NSAssert(gain >= 0, @"gain can not be negative");
#endif
    //If mute or initialisation has failed or buffer is not loaded then do nothing
    if (!enabled_ || !functioning_ || _buffers[soundId].bufferState != CD_BS_LOADED || _sourceGroups[sourceGroupId].enabled) {
#ifdef CD_DEBUG
        if (!functioning_) {
            CDLOGINFO(@"Denshion::CDSoundEngine - sound playback aborted because sound engine is not functioning");
        } else if (_buffers[soundId].bufferState != CD_BS_LOADED) {
            CDLOGINFO(@"Denshion::CDSoundEngine - sound playback aborted because buffer %i is not loaded", soundId);
        }    
#endif        
        return CD_MUTE;
    }    

    int sourceIndex = [self _getSourceIndexForSourceGroup:sourceGroupId];//This method ensures sourceIndex is valid
    
    if (sourceIndex != CD_NO_SOURCE) {
        ALint state;
        ALuint source = _sources[sourceIndex].sourceId;
        ALuint buffer = _buffers[soundId].bufferId;
        alGetError();//Clear the error code    
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state == AL_PLAYING) {
            alSourceStop(source);
        }    
        alSourcei(source, AL_BUFFER, buffer);//Attach to sound
        alSourcef(source, AL_PITCH, pitch);//Set pitch
        alSourcei(source, AL_LOOPING, loop);//Set looping
        alSourcef(source, AL_GAIN, gain);//Set gain/volume
        float sourcePosAL[] = {pan, 0.0f, 0.0f};//Set position - just using left and right panning
        alSourcefv(source, AL_POSITION, sourcePosAL);
        alGetError();//Clear the error code
        alSourcePlay(source);
        if((lastErrorCode_ = alGetError()) == AL_NO_ERROR) {
            //Everything was okay
            _sources[sourceIndex].attachedBufferId = buffer;
            return source;
        } else {
            if (alcGetCurrentContext() == NULL) {
                CDLOGINFO(@"Denshion::CDSoundEngine - posting bad OpenAL context message");
                [[NSNotificationCenter defaultCenter] postNotificationName:kCDN_BadAlContext object:nil];
            }                
            return CD_NO_SOURCE;
        }    
    } else {    
        return CD_NO_SOURCE;
    }    
}

-(BOOL) _soundSourceAttachToBuffer:(CDSoundSource*) soundSource soundId:(int) soundId  {
    //Attach the source to the buffer
    ALint state;
    ALuint source = soundSource->_sourceId;
    ALuint buffer = _buffers[soundId].bufferId;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING) {
        alSourceStop(source);
    }
    alGetError();//Clear the error code    
    alSourcei(source, AL_BUFFER, buffer);//Attach to sound data
    if((lastErrorCode_ = alGetError()) == AL_NO_ERROR) {
        _sources[soundSource->_sourceIndex].attachedBufferId = buffer;
        //_sourceBufferAttachments[soundSource->_sourceIndex] = buffer;//Keep track of which
        soundSource->_soundId = soundId;
        return YES;
    } else {
        return NO;
    }    
}    

/**
 * Get a sound source for the specified sound in the specified source group
 */
-(CDSoundSource *) soundSourceForSound:(int) soundId sourceGroupId:(int) sourceGroupId 
{
    if (!functioning_) {
        return nil;
    }    
    //Check if a source is available
    int sourceIndex = [self _getSourceIndexForSourceGroup:sourceGroupId];
    if (sourceIndex != CD_NO_SOURCE) { 
        CDSoundSource *result = [[CDSoundSource alloc] init:_sources[sourceIndex].sourceId sourceIndex:sourceIndex soundEngine:self];
        [self _lockSource:sourceIndex lock:YES];
        //Try to attach to the buffer
        if ([self _soundSourceAttachToBuffer:result soundId:soundId]) {
            //Set to a known state
            result.pitch = 1.0f;
            result.pan = 0.0f;
            result.gain = 1.0f;
            result.looping = NO;
            return [result autorelease];
        } else {
            //Release the sound source we just created, this will also unlock the source
            [result release];
            return nil;
        }    
    } else {
        //No available source within that source group
        return nil;
    }
}    

-(void) _soundSourcePreRelease:(CDSoundSource *) soundSource {
    CDLOGINFO(@"Denshion::CDSoundEngine _soundSourcePreRelease %i",soundSource->_sourceIndex);
    //Unlock the sound source's source
    [self _lockSource:soundSource->_sourceIndex lock:NO];
}    

/**
 * Stop all sounds playing within a source group
 */
- (void) stopSourceGroup:(int) sourceGroupId {
    
    if (!functioning_ || sourceGroupId >= _sourceGroupTotal || sourceGroupId < 0) {
        return;
    }    
    int sourceCount = _sourceGroups[sourceGroupId].totalSources;
    for (int i=0; i < sourceCount; i++) {
        int sourceIndex = _sourceGroups[sourceGroupId].sourceStatuses[i] >> 1;
        alSourceStop(_sources[sourceIndex].sourceId);
    }
    alGetError();//Clear error in case we stopped any sounds that couldn't be stopped
}    

/**
 * Stop a sound playing.
 * @param sourceId an OpenAL source identifier i.e. the return value of playSound
 */
- (void)stopSound:(ALuint) sourceId {
    if (!functioning_) {
        return;
    }    
    alSourceStop(sourceId);
    alGetError();//Clear error in case we stopped any sounds that couldn't be stopped
}

- (void) stopAllSounds {
    for (int i=0; i < sourceTotal_; i++) {
        alSourceStop(_sources[i].sourceId);
    }    
    alGetError();//Clear error in case we stopped any sounds that couldn't be stopped
}    

- (void) pauseSound:(ALuint) sourceId {
  if (!functioning_) {
      return;
  }
  alSourcePause(sourceId);
  alGetError();//Clear error in case we pause any sounds that couldn't be paused
}

- (void) pauseAllSounds {
  for (int i = 0; i < sourceTotal_; i++) {
      [self pauseSound:_sources[i].sourceId];
  }
  alGetError();//Clear error in case we stopped any sounds that couldn't be paused
}

- (void) resumeSound:(ALuint) soundId {
  if (!functioning_) {
    return;
  }
  
    // only resume a sound id that is paused
    ALint state;
    alGetSourcei(soundId, AL_SOURCE_STATE, &state);
    if (state != AL_PAUSED)
    {
        return;
    }
        
  alSourcePlay(soundId);
  alGetError();//Clear error in case we stopped any sounds that couldn't be resumed
}

- (void) resumeAllSounds {
  for (int i = 0; i < sourceTotal_; i++) {
      [self resumeSound:_sources[i].sourceId];
  }
  alGetError();//Clear error in case we stopped any sounds that couldn't be resumed
}

/**
 * Set a source group as non interruptible.  Default is that source groups are interruptible.
 * Non interruptible means that if a request to play a sound is made for a source group and there are
 * no free sources available then the play request will be ignored and CD_NO_SOURCE will be returned.
 */
- (void) setSourceGroupNonInterruptible:(int) sourceGroupId isNonInterruptible:(BOOL) isNonInterruptible {
    //Ensure source group id is valid to prevent memory corruption
    if (sourceGroupId < 0 || sourceGroupId >= _sourceGroupTotal) {
        CDLOG(@"Denshion::CDSoundEngine setSourceGroupNonInterruptible invalid source group id %i",sourceGroupId);
        return;
    }    
    
    if (isNonInterruptible) {
        _sourceGroups[sourceGroupId].nonInterruptible = true;
    } else {
        _sourceGroups[sourceGroupId].nonInterruptible = false;
    }    
}

/**
 * Set the mute property for a source group. If mute is turned on any sounds in that source group
 * will be stopped and further sounds in that source group will play. However, turning mute off
 * will not restart any sounds that were playing when mute was turned on. Also the mute setting 
 * for the sound engine must be taken into account. If the sound engine is mute no sounds will play
 * no matter what the source group mute setting is.
 */
- (void) setSourceGroupEnabled:(int) sourceGroupId enabled:(BOOL) enabled {
    //Ensure source group id is valid to prevent memory corruption
    if (sourceGroupId < 0 || sourceGroupId >= _sourceGroupTotal) {
        CDLOG(@"Denshion::CDSoundEngine setSourceGroupEnabled invalid source group id %i",sourceGroupId);
        return;
    }    
    
    if (enabled) {
        _sourceGroups[sourceGroupId].enabled = true;
        [self stopSourceGroup:sourceGroupId];
    } else {
        _sourceGroups[sourceGroupId].enabled = false;    
    }    
}

/**
 * Return the mute property for the source group identified by sourceGroupId
 */
- (BOOL) sourceGroupEnabled:(int) sourceGroupId {
    return _sourceGroups[sourceGroupId].enabled;
}

-(ALCcontext *) openALContext {
    return context;
}    

- (void) _dumpSourceGroupsInfo {
#ifdef CD_DEBUG    
    CDLOGINFO(@"-------------- source Group Info --------------");
    for (int i=0; i < _sourceGroupTotal; i++) {
        CDLOGINFO(@"Group: %i start:%i total:%i",i,_sourceGroups[i].startIndex, _sourceGroups[i].totalSources);
        CDLOGINFO(@"----- mute:%i nonInterruptible:%i",_sourceGroups[i].enabled, _sourceGroups[i].nonInterruptible);
        CDLOGINFO(@"----- Source statuses ----");
        for (int j=0; j < _sourceGroups[i].totalSources; j++) {
            CDLOGINFO(@"Source status:%i index=%i locked=%i",j,_sourceGroups[i].sourceStatuses[j] >> 1, _sourceGroups[i].sourceStatuses[j] & 1);
        }    
    }    
#endif    
}    

@end

///////////////////////////////////////////////////////////////////////////////////////
@implementation CDSoundSource

@synthesize lastError;

//Macro for handling the al error code
#define CDSOUNDSOURCE_UPDATE_LAST_ERROR (lastError = alGetError())
#define CDSOUNDSOURCE_ERROR_HANDLER ( CDSOUNDSOURCE_UPDATE_LAST_ERROR == AL_NO_ERROR)

-(id)init:(ALuint) theSourceId sourceIndex:(int) index soundEngine:(CDSoundEngine*) engine {
    if ((self = [super init])) {
        _sourceId = theSourceId;
        _engine = engine;
        _sourceIndex = index;
        enabled_ = YES;
        mute_ = NO;
        _preMuteGain = self.gain;
    } 
    return self;
}

-(void) dealloc
{
    CDLOGINFO(@"Denshion::CDSoundSource deallocated %i",self->_sourceIndex);

    //Notify sound engine we are about to release
    [_engine _soundSourcePreRelease:self];
    [super dealloc];
}    

- (void) setPitch:(float) newPitchValue {
    alSourcef(_sourceId, AL_PITCH, newPitchValue);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
}    

- (void) setGain:(float) newGainValue {
    if (!mute_) {
        alSourcef(_sourceId, AL_GAIN, newGainValue);    
    } else {
        _preMuteGain = newGainValue;
    }    
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
}

- (void) setPan:(float) newPanValue {
    float sourcePosAL[] = {newPanValue, 0.0f, 0.0f};//Set position - just using left and right panning
    alSourcefv(_sourceId, AL_POSITION, sourcePosAL);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;

}

- (void) setLooping:(BOOL) newLoopingValue {
    alSourcei(_sourceId, AL_LOOPING, newLoopingValue);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;

}

- (BOOL) isPlaying {
    ALint state;
    alGetSourcei(_sourceId, AL_SOURCE_STATE, &state);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
    return (state == AL_PLAYING);
}    

- (float) pitch {
    ALfloat pitchVal;
    alGetSourcef(_sourceId, AL_PITCH, &pitchVal);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
    return pitchVal;
}

- (float) pan {
    ALfloat sourcePosAL[] = {0.0f,0.0f,0.0f};
    alGetSourcefv(_sourceId, AL_POSITION, sourcePosAL);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
    return sourcePosAL[0];
}

- (float) gain {
    if (!mute_) {
        ALfloat val;
        alGetSourcef(_sourceId, AL_GAIN, &val);
        CDSOUNDSOURCE_UPDATE_LAST_ERROR;
        return val;
    } else {
        return _preMuteGain;
    }    
}    

- (BOOL) looping {
    ALfloat val;
    alGetSourcef(_sourceId, AL_LOOPING, &val);
    CDSOUNDSOURCE_UPDATE_LAST_ERROR;
    return val;
}

-(BOOL) stop {
    alSourceStop(_sourceId);
    return CDSOUNDSOURCE_ERROR_HANDLER;
}    

-(BOOL) play {
    if (enabled_) {
        alSourcePlay(_sourceId);
        CDSOUNDSOURCE_UPDATE_LAST_ERROR;
        if (lastError != AL_NO_ERROR) {
            if (alcGetCurrentContext() == NULL) {
                CDLOGINFO(@"Denshion::CDSoundSource - posting bad OpenAL context message");
                [[NSNotificationCenter defaultCenter] postNotificationName:kCDN_BadAlContext object:nil];
            }    
            return NO;
        } else {
            return YES;
        }    
    } else {
        return NO;
    }
}    

-(BOOL) pause {
    alSourcePause(_sourceId);
    return CDSOUNDSOURCE_ERROR_HANDLER;
}

-(BOOL) rewind {
    alSourceRewind(_sourceId);
    return CDSOUNDSOURCE_ERROR_HANDLER;
}

-(void) setSoundId:(int) soundId {
    [_engine _soundSourceAttachToBuffer:self soundId:soundId];
}

-(int) soundId {
    return _soundId;
}    

-(float) durationInSeconds {
    return [_engine bufferDurationInSeconds:_soundId];
}    

#pragma mark CDSoundSource AudioInterrupt protocol
- (BOOL) mute {
    return mute_;
}    

/**
 * Setting mute silences all sounds but playing sounds continue to advance playback
 */
- (void) setMute:(BOOL) newMuteValue {
    
    if (newMuteValue == mute_) {
        return;
    }
    
    if (newMuteValue) {
        //Remember what the gain was
        _preMuteGain = self.gain;
        self.gain = 0.0f;
        mute_ = newMuteValue;//Make sure this is done after setting the gain property as the setter behaves differently depending on mute value
    } else {
        //Restore gain to what it was before being muted
        mute_ = newMuteValue;
        self.gain = _preMuteGain;
    }    
}

- (BOOL) enabled {
    return enabled_;
}

- (void) setEnabled:(BOOL)enabledValue
{
    if (enabled_ == enabledValue) {
        return;
    }    
    enabled_ = enabledValue;
    if (enabled_ == NO) {
        [self stop];
    }    
}    

@end

////////////////////////////////////////////////////////////////////////////
#pragma mark - CDAudioInterruptTargetGroup

@implementation CDAudioInterruptTargetGroup

-(id) init {
    if ((self = [super init])) {
        children_ = [[NSMutableArray alloc] initWithCapacity:32];
        enabled_ = YES;
        mute_ = NO;
    }
    return self;
}    

-(void) addAudioInterruptTarget:(NSObject<CDAudioInterruptProtocol>*) interruptibleTarget {
    //Synchronize child with group settings;
    [interruptibleTarget setMute:mute_];
    [interruptibleTarget setEnabled:enabled_];
    [children_ addObject:interruptibleTarget];
}    

-(void) removeAudioInterruptTarget:(NSObject<CDAudioInterruptProtocol>*) interruptibleTarget {
    [children_ removeObjectIdenticalTo:interruptibleTarget];
}    

- (BOOL) mute {
    return mute_;
}    

/**
 * Setting mute silences all sounds but playing sounds continue to advance playback
 */
- (void) setMute:(BOOL) newMuteValue {
    
    if (newMuteValue == mute_) {
        return;
    }
    
    for (NSObject<CDAudioInterruptProtocol>* target in children_) {
        [target setMute:newMuteValue];
    }    
}

- (BOOL) enabled {
    return enabled_;
}

- (void) setEnabled:(BOOL)enabledValue
{
    if (enabledValue == enabled_) {
        return;
    }
    
    for (NSObject<CDAudioInterruptProtocol>* target in children_) {
        [target setEnabled:enabledValue];
    }    
}    

@end



////////////////////////////////////////////////////////////////////////////

#pragma mark - CDAsynchBufferLoader

@implementation CDAsynchBufferLoader

-(id) init:(NSArray *)loadRequests soundEngine:(CDSoundEngine *) theSoundEngine {
    if ((self = [super init])) {
        _loadRequests = loadRequests;
        [_loadRequests retain];
        _soundEngine = theSoundEngine;
        [_soundEngine retain];
    } 
    return self;
}    

-(void) main {
    CDLOGINFO(@"Denshion::CDAsynchBufferLoader - loading buffers");
    [super main];
    _soundEngine.asynchLoadProgress = 0.0f;

    if ([_loadRequests count] > 0) {
        float increment = 1.0f / [_loadRequests count];
        //Iterate over load request and load
        for (CDBufferLoadRequest *loadRequest in _loadRequests) {
            [_soundEngine loadBuffer:loadRequest.soundId filePath:loadRequest.filePath];
            _soundEngine.asynchLoadProgress += increment;
        }    
    }    
    
    //Completed
    _soundEngine.asynchLoadProgress = 1.0f;
    [[NSNotificationCenter defaultCenter] postNotificationName:kCDN_AsynchLoadComplete object:nil];
    
}    

-(void) dealloc {
    [_loadRequests release];
    [_soundEngine release];
    [super dealloc];
}    

@end


///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDBufferLoadRequest

@implementation CDBufferLoadRequest

@synthesize filePath, soundId;

-(id) init:(int) theSoundId filePath:(const NSString *) theFilePath {
	if ((self = [super init])) {
		soundId = theSoundId;
		filePath = [theFilePath copy];
	}
	return self;
}

-(void) dealloc {
    [filePath release];
    [super dealloc];
}

@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDFloatInterpolator

@implementation CDFloatInterpolator
@synthesize start,end,interpolationType;

-(float) interpolate:(float) t {
    
    if (t < 1.0f) {
        switch (interpolationType) {
            case kIT_Linear:
                //Linear interpolation
                return ((end - start) * t) + start;
                
            case kIT_SCurve:
                //Cubic s curve t^2 * (3 - 2t)
                return ((float)(t * t * (3.0 - (2.0 * t))) * (end - start)) + start;
                
            case kIT_Exponential:    
                //Formulas taken from EaseAction
                if (end > start) {
                    //Fade in
                    float logDelta = (t==0) ? 0 : powf(2, 10 * (t/1 - 1)) - 1 * 0.001f;
                    return ((end - start) * logDelta) + start;
                } else {
                    //Fade Out
                    float logDelta = (-powf(2, -10 * t/1) + 1);
                    return ((end - start) * logDelta) + start;
                }
            default:
                return 0.0f;
        }
    } else {
        return end;
    } 
}

-(id) init:(tCDInterpolationType) type startVal:(float) startVal endVal:(float) endVal {
    if ((self = [super init])) {
        start = startVal;
        end = endVal;
        interpolationType = type;
    } 
    return self;
}

@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDPropertyModifier

@implementation CDPropertyModifier

@synthesize stopTargetWhenComplete;

-(id) init:(id) theTarget interpolationType:(tCDInterpolationType) type startVal:(float) startVal endVal:(float) endVal {
    if ((self = [super init])) {
        if (target) {
            //Release the previous target if there is one
            [target release];
        }    
        target = theTarget;
#if CD_DEBUG
        //Check target is of the required type
        if (![theTarget isMemberOfClass:[self _allowableType]] ) {
            CDLOG(@"Denshion::CDPropertyModifier target is not of type %@",[self _allowableType]);
            NSAssert([theTarget isKindOfClass:[CDSoundEngine class]], @"CDPropertyModifier target not of required type");
        }
#endif        
        [target retain];
        startValue = startVal;
        endValue = endVal;
        if (interpolator) {
            //Release previous interpolator if there is one
            [interpolator release];
        }    
        interpolator = [[CDFloatInterpolator alloc] init:type startVal:startVal endVal:endVal];
        stopTargetWhenComplete = NO;
    }
    return self;
}    

-(void) dealloc {
    CDLOGINFO(@"Denshion::CDPropertyModifier deallocated %@",self);
    [target release];
    [interpolator release];
    [super dealloc];
}    

-(void) modify:(float) t {
    if (t < 1.0) {
        [self _setTargetProperty:[interpolator interpolate:t]];
    } else {
        //At the end
        [self _setTargetProperty:endValue];
        if (stopTargetWhenComplete) {
            [self _stopTarget];
        }    
    }    
}    

-(float) startValue {
    return startValue;
}

-(void) setStartValue:(float) startVal
{
    startValue = startVal;
    interpolator.start = startVal;
}    

-(float) endValue {
    return startValue;
}

-(void) setEndValue:(float) endVal
{
    endValue = endVal;
    interpolator.end = endVal;
}    

-(tCDInterpolationType) interpolationType {
    return interpolator.interpolationType;
}

-(void) setInterpolationType:(tCDInterpolationType) interpolationType {
    interpolator.interpolationType = interpolationType;
}    

-(void) _setTargetProperty:(float) newVal {

}    

-(float) _getTargetProperty {
    return 0.0f;
}    

-(void) _stopTarget {

}    

-(Class) _allowableType {
    return [NSObject class];
}    
@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDSoundSourceFader

@implementation CDSoundSourceFader

-(void) _setTargetProperty:(float) newVal {
    ((CDSoundSource*)target).gain = newVal;
}    

-(float) _getTargetProperty {
    return ((CDSoundSource*)target).gain;
}

-(void) _stopTarget {
    [((CDSoundSource*)target) stop];
}

-(Class) _allowableType {
    return [CDSoundSource class];
}    

@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDSoundSourcePanner

@implementation CDSoundSourcePanner

-(void) _setTargetProperty:(float) newVal {
    ((CDSoundSource*)target).pan = newVal;
}    

-(float) _getTargetProperty {
    return ((CDSoundSource*)target).pan;
}

-(void) _stopTarget {
    [((CDSoundSource*)target) stop];
}

-(Class) _allowableType {
    return [CDSoundSource class];
}    

@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDSoundSourcePitchBender

@implementation CDSoundSourcePitchBender

-(void) _setTargetProperty:(float) newVal {
    ((CDSoundSource*)target).pitch = newVal;
}    

-(float) _getTargetProperty {
    return ((CDSoundSource*)target).pitch;
}

-(void) _stopTarget {
    [((CDSoundSource*)target) stop];
}

-(Class) _allowableType {
    return [CDSoundSource class];
}    

@end

///////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CDSoundEngineFader

@implementation CDSoundEngineFader

-(void) _setTargetProperty:(float) newVal {
    ((CDSoundEngine*)target).masterGain = newVal;
}    

-(float) _getTargetProperty {
    return ((CDSoundEngine*)target).masterGain;
}

-(void) _stopTarget {
    [((CDSoundEngine*)target) stopAllSounds];
}

-(Class) _allowableType {
    return [CDSoundEngine class];
}    

@end


