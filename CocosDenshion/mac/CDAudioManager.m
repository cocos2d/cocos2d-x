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


#import "CDAudioManager.h"

NSString * const kCDN_AudioManagerInitialised = @"kCDN_AudioManagerInitialised";

//NSOperation object used to asynchronously initialise 
@implementation CDAsynchInitialiser

-(void) main {
    [super main];
    [CDAudioManager sharedManager];
}    

@end

@implementation CDLongAudioSource

@synthesize audioSourcePlayer, audioSourceFilePath, delegate, backgroundMusic, paused;

-(id) init {
    if ((self = [super init])) {
        state = kLAS_Init;
        volume = 1.0f;
        mute = NO;
        enabled_ = YES;
        paused = NO;
    }
    return self;
}

-(void) dealloc {
    CDLOGINFO(@"Denshion::CDLongAudioSource - deallocating %@", self);
    [audioSourcePlayer release];
    [audioSourceFilePath release];
    [super dealloc];
}    

-(void) load:(NSString*) filePath {
    //We have alread loaded a file previously,  check if we are being asked to load the same file
    if (state == kLAS_Init || ![filePath isEqualToString:audioSourceFilePath]) {
        CDLOGINFO(@"Denshion::CDLongAudioSource - Loading new audio source %@",filePath);
        //New file
        if (state != kLAS_Init) {
            [audioSourceFilePath release];//Release old file path
            [audioSourcePlayer release];//Release old AVAudioPlayer, they can't be reused
        }
        audioSourceFilePath = [filePath copy];
        NSError *error = nil;
        NSString *path = [CDUtilities fullPathFromRelativePath:audioSourceFilePath];
        audioSourcePlayer = [(AVAudioPlayer*)[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL fileURLWithPath:path] error:&error];
        if (error == nil) {
            [audioSourcePlayer prepareToPlay];
            audioSourcePlayer.delegate = self;
            if (delegate && [delegate respondsToSelector:@selector(cdAudioSourceFileDidChange:)]) {
                //Tell our delegate the file has changed
                [delegate cdAudioSourceFileDidChange:self];
            }    
        } else {
            CDLOG(@"Denshion::CDLongAudioSource - Error initialising audio player: %@",error);
        }    
    } else {
        //Same file - just return it to a consistent state
        [self pause];
        [self rewind];
    }
    audioSourcePlayer.volume = volume;
    audioSourcePlayer.numberOfLoops = numberOfLoops;
    state = kLAS_Loaded;
}    

-(void) play {
    if (enabled_) {
        self->systemPaused = NO;
        self->paused = NO;
        [audioSourcePlayer play];
    } else {
        CDLOGINFO(@"Denshion::CDLongAudioSource long audio source didn't play because it is disabled");
    }    
}    

-(void) stop {
    self->paused = NO;
    [audioSourcePlayer stop];
}    

-(void) pause {
    self->paused = YES;
    [audioSourcePlayer pause];
}    

-(void) rewind {
    self->paused = NO;
    [audioSourcePlayer setCurrentTime:0];
}

-(void) resume {
    self->paused = NO;
    [audioSourcePlayer play];
}    

-(BOOL) isPlaying {
    if (state != kLAS_Init) {
        return [audioSourcePlayer isPlaying];
    } else {
        return NO;
    }
}

-(void) setVolume:(float) newVolume
{
    volume = newVolume;
    if (state != kLAS_Init && !mute) {
        audioSourcePlayer.volume = newVolume;
    }    
}

-(float) volume 
{
    return volume;
}

#pragma mark Audio Interrupt Protocol
-(BOOL) mute
{
    return mute;
}    

-(void) setMute:(BOOL) muteValue 
{
    if (mute != muteValue) {
        if (mute) {
            //Turn sound back on
            audioSourcePlayer.volume = volume;
        } else {
            audioSourcePlayer.volume = 0.0f;
        }
        mute = muteValue;
    }    
}    

-(BOOL) enabled 
{
    return enabled_;
}    

-(void) setEnabled:(BOOL)enabledValue 
{
    if (enabledValue != enabled_) {
        enabled_ = enabledValue;
        if (!enabled_) {
            //"Stop" the sounds
            [self pause];
            [self rewind];
        }    
    }    
}    

-(NSInteger) numberOfLoops {
    return numberOfLoops;
}    

-(void) setNumberOfLoops:(NSInteger) loopCount
{
    audioSourcePlayer.numberOfLoops = loopCount;
    numberOfLoops = loopCount;
}    

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    CDLOGINFO(@"Denshion::CDLongAudioSource - audio player finished");
#if TARGET_IPHONE_SIMULATOR    
    CDLOGINFO(@"Denshion::CDLongAudioSource - workaround for OpenAL clobbered audio issue");
    //This is a workaround for an issue in all simulators (tested to 3.1.2).  Problem is 
    //that OpenAL audio playback is clobbered when an AVAudioPlayer stops.  Workaround
    //is to keep the player playing on an endless loop with 0 volume and then when
    //it is played again reset the volume and set loop count appropriately.
    //NB: this workaround is not foolproof but it is good enough for most situations.
    player.numberOfLoops = -1;
    player.volume = 0;
    [player play];
#endif    
    if (delegate && [delegate respondsToSelector:@selector(cdAudioSourceDidFinishPlaying:)]) {
        [delegate cdAudioSourceDidFinishPlaying:self];
    }    
}    

-(void)audioPlayerBeginInterruption:(AVAudioPlayer *)player {
    CDLOGINFO(@"Denshion::CDLongAudioSource - audio player interrupted");
}

-(void)audioPlayerEndInterruption:(AVAudioPlayer *)player {
    CDLOGINFO(@"Denshion::CDLongAudioSource - audio player resumed");
    if (self.backgroundMusic) {
        //Check if background music can play as rules may have changed during 
        //the interruption. This is to address a specific issue in 4.x when
        //fast task switching
        if([CDAudioManager sharedManager].willPlayBackgroundMusic) {
            [player play];
        }    
    } else {
        [player play];
    }    
}    

@end


@interface CDAudioManager (PrivateMethods)
-(BOOL) audioSessionSetActive:(BOOL) active;
-(BOOL) audioSessionSetCategory:(NSString*) category;
-(void) badAlContextHandler;
@end


@implementation CDAudioManager
#define BACKGROUND_MUSIC_CHANNEL kASC_Left

@synthesize soundEngine, willPlayBackgroundMusic;
static CDAudioManager *sharedManager;
static tAudioManagerState _sharedManagerState = kAMStateUninitialised;
static tAudioManagerMode configuredMode;
static BOOL configured = FALSE;

-(BOOL) audioSessionSetActive:(BOOL) active {
    NSError *activationError = nil;
    if ([[AVAudioSession sharedInstance] setActive:active error:&activationError]) {
        _audioSessionActive = active;
        CDLOGINFO(@"Denshion::CDAudioManager - Audio session set active %i succeeded", active); 
        return YES;
    } else {
        //Failed
        CDLOG(@"Denshion::CDAudioManager - Audio session set active %i failed with error %@", active, activationError); 
        return NO;
    }    
}    

-(BOOL) audioSessionSetCategory:(NSString*) category {
    NSError *categoryError = nil;
    if ([[AVAudioSession sharedInstance] setCategory:category error:&categoryError]) {
        CDLOGINFO(@"Denshion::CDAudioManager - Audio session set category %@ succeeded", category); 
        return YES;
    } else {
        //Failed
        CDLOG(@"Denshion::CDAudioManager - Audio session set category %@ failed with error %@", category, categoryError); 
        return NO;
    }    
}    

// Init
+ (CDAudioManager *) sharedManager
{
    @synchronized(self)     {
        if (!sharedManager) {
            if (!configured) {
                //Set defaults here
                configuredMode = kAMM_FxPlusMusicIfNoOtherAudio;
            }
            sharedManager = [[CDAudioManager alloc] init:configuredMode];
            _sharedManagerState = kAMStateInitialised;//This is only really relevant when using asynchronous initialisation
            [[NSNotificationCenter defaultCenter] postNotificationName:kCDN_AudioManagerInitialised object:nil];
        }    
    }
    return sharedManager;
}

+ (tAudioManagerState) sharedManagerState {
    return _sharedManagerState;
}    

/**
 * Call this to set up audio manager asynchronously.  Initialisation is finished when sharedManagerState == kAMStateInitialised
 */
+ (void) initAsynchronously: (tAudioManagerMode) mode {
    @synchronized(self) {
        if (_sharedManagerState == kAMStateUninitialised) {
            _sharedManagerState = kAMStateInitialising;
            [CDAudioManager configure:mode];
            CDAsynchInitialiser *initOp = [[[CDAsynchInitialiser alloc] init] autorelease];
            NSOperationQueue *opQ = [[[NSOperationQueue alloc] init] autorelease];
            [opQ addOperation:initOp];
        }    
    }
}    

+ (id) alloc
{
    @synchronized(self)     {
        NSAssert(sharedManager == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super alloc];
    }
    return nil;
}

/*
 * Call this method before accessing the shared manager in order to configure the shared audio manager
 */
+ (void) configure: (tAudioManagerMode) mode {
    configuredMode = mode;
    configured = TRUE;
}    

-(BOOL) isOtherAudioPlaying {
    UInt32 isPlaying = 0;
    UInt32 varSize = sizeof(isPlaying);
    AudioSessionGetProperty (kAudioSessionProperty_OtherAudioIsPlaying, &varSize, &isPlaying);
    return (isPlaying != 0);
}

-(void) setMode:(tAudioManagerMode) mode {

    _mode = mode;
    switch (_mode) {
            
        case kAMM_FxOnly:
            //Share audio with other app
            CDLOGINFO(@"Denshion::CDAudioManager - Audio will be shared");
            //_audioSessionCategory = kAudioSessionCategory_AmbientSound;
            _audioSessionCategory = AVAudioSessionCategoryAmbient;
            willPlayBackgroundMusic = NO;
            break;
            
        case kAMM_FxPlusMusic:
            //Use audio exclusively - if other audio is playing it will be stopped
            CDLOGINFO(@"Denshion::CDAudioManager -  Audio will be exclusive");
            //_audioSessionCategory = kAudioSessionCategory_SoloAmbientSound;
            _audioSessionCategory = AVAudioSessionCategorySoloAmbient;
            willPlayBackgroundMusic = YES;
            break;
            
        case kAMM_MediaPlayback:
            //Use audio exclusively, ignore mute switch and sleep
            CDLOGINFO(@"Denshion::CDAudioManager -  Media playback mode, audio will be exclusive");
            //_audioSessionCategory = kAudioSessionCategory_MediaPlayback;
            _audioSessionCategory = AVAudioSessionCategoryPlayback;
            willPlayBackgroundMusic = YES;
            break;
            
        case kAMM_PlayAndRecord:
            //Use audio exclusively, ignore mute switch and sleep, has inputs and outputs
            CDLOGINFO(@"Denshion::CDAudioManager -  Play and record mode, audio will be exclusive");
            //_audioSessionCategory = kAudioSessionCategory_PlayAndRecord;
            _audioSessionCategory = AVAudioSessionCategoryPlayAndRecord;
            willPlayBackgroundMusic = YES;
            break;
            
        default:
            //kAudioManagerFxPlusMusicIfNoOtherAudio
            if ([self isOtherAudioPlaying]) {
                CDLOGINFO(@"Denshion::CDAudioManager - Other audio is playing audio will be shared");
                //_audioSessionCategory = kAudioSessionCategory_AmbientSound;
                _audioSessionCategory = AVAudioSessionCategoryAmbient;
                willPlayBackgroundMusic = NO;
            } else {
                CDLOGINFO(@"Denshion::CDAudioManager - Other audio is not playing audio will be exclusive");
                //_audioSessionCategory = kAudioSessionCategory_SoloAmbientSound;
                _audioSessionCategory = AVAudioSessionCategorySoloAmbient;
                willPlayBackgroundMusic = YES;
            }    
            
            break;
    }
     
    [self audioSessionSetCategory:_audioSessionCategory];
    
}    

/**
 * This method is used to work around various bugs introduced in 4.x OS versions. In some circumstances the 
 * audio session is interrupted but never resumed, this results in the loss of OpenAL audio when following 
 * standard practices. If we detect this situation then we will attempt to resume the audio session ourselves.
 * Known triggers: lock the device then unlock it (iOS 4.2 gm), playback a song using MPMediaPlayer (iOS 4.0)
 */
- (void) badAlContextHandler {
    if (_interrupted && alcGetCurrentContext() == NULL) {
        CDLOG(@"Denshion::CDAudioManager - bad OpenAL context detected, attempting to resume audio session");
        [self audioSessionResumed];
    }    
}    

- (id) init: (tAudioManagerMode) mode {
    if ((self = [super init])) {
        
        //Initialise the audio session 
        AVAudioSession* session = [AVAudioSession sharedInstance];
        session.delegate = self;
    
        _mode = mode;
        backgroundMusicCompletionSelector = nil;
        _isObservingAppEvents = FALSE;
        _mute = NO;
        _resigned = NO;
        _interrupted = NO;
        enabled_ = YES;
        _audioSessionActive = NO;
        [self setMode:mode];
        soundEngine = [[CDSoundEngine alloc] init];
        
        //Set up audioSource channels
        audioSourceChannels = [[NSMutableArray alloc] init];
        CDLongAudioSource *leftChannel = [[CDLongAudioSource alloc] init];
        leftChannel.backgroundMusic = YES;
        CDLongAudioSource *rightChannel = [[CDLongAudioSource alloc] init];
        rightChannel.backgroundMusic = NO;
        [audioSourceChannels insertObject:leftChannel atIndex:kASC_Left];    
        [audioSourceChannels insertObject:rightChannel atIndex:kASC_Right];
        [leftChannel release];
        [rightChannel release];
        //Used to support legacy APIs
        backgroundMusic = [self audioSourceForChannel:BACKGROUND_MUSIC_CHANNEL];
        backgroundMusic.delegate = self;
        
        //Add handler for bad al context messages, these are posted by the sound engine.
        [[NSNotificationCenter defaultCenter] addObserver:self    selector:@selector(badAlContextHandler) name:kCDN_BadAlContext object:nil];

    }    
    return self;        
}    

-(void) dealloc {
    CDLOGINFO(@"Denshion::CDAudioManager - deallocating");
    [self stopBackgroundMusic];
    [soundEngine release];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self audioSessionSetActive:NO];
    [audioSourceChannels release];
    [super dealloc];
}    

/** Retrieves the audio source for the specified channel */
-(CDLongAudioSource*) audioSourceForChannel:(tAudioSourceChannel) channel 
{
    return (CDLongAudioSource*)[audioSourceChannels objectAtIndex:channel];
}    

/** Loads the data from the specified file path to the channel's audio source */
-(CDLongAudioSource*) audioSourceLoad:(NSString*) filePath channel:(tAudioSourceChannel) channel
{
    CDLongAudioSource *audioSource = [self audioSourceForChannel:channel];
    if (audioSource) {
        [audioSource load:filePath];
    }
    return audioSource;
}    

-(BOOL) isBackgroundMusicPlaying {
    return [self.backgroundMusic isPlaying];
}    

//NB: originally I tried using a route change listener and intended to store the current route,
//however, on a 3gs running 3.1.2 no route change is generated when the user switches the 
//ringer mute switch to off (i.e. enables sound) therefore polling is the only reliable way to
//determine ringer switch state
-(BOOL) isDeviceMuted {

#if TARGET_IPHONE_SIMULATOR
    //Calling audio route stuff on the simulator causes problems
    return NO;
#else    
    CFStringRef newAudioRoute;
    UInt32 propertySize = sizeof (CFStringRef);
    
    AudioSessionGetProperty (
                             kAudioSessionProperty_AudioRoute,
                             &propertySize,
                             &newAudioRoute
                             );
    
    if (newAudioRoute == NULL) {
        //Don't expect this to happen but playing safe otherwise a null in the CFStringCompare will cause a crash
        return YES;
    } else {    
        CFComparisonResult newDeviceIsMuted =    CFStringCompare (
                                                                 newAudioRoute,
                                                                 (CFStringRef) @"",
                                                                 0
                                                                 );
        
        return (newDeviceIsMuted == kCFCompareEqualTo);
    }    
#endif
}    

#pragma mark Audio Interrupt Protocol

-(BOOL) mute {
    return _mute;
}    

-(void) setMute:(BOOL) muteValue {
    if (muteValue != _mute) {
        _mute = muteValue;
        [soundEngine setMute:muteValue];
        for( CDLongAudioSource *audioSource in audioSourceChannels) {
            audioSource.mute = muteValue;
        }    
    }    
}

-(BOOL) enabled {
    return enabled_;
}    

-(void) setEnabled:(BOOL) enabledValue {
    if (enabledValue != enabled_) {
        enabled_ = enabledValue;
        [soundEngine setEnabled:enabled_];
        for( CDLongAudioSource *audioSource in audioSourceChannels) {
            audioSource.enabled = enabled_;
        }    
    }    
}

-(CDLongAudioSource*) backgroundMusic
{
    return backgroundMusic;
}    

//Load background music ready for playing
-(void) preloadBackgroundMusic:(NSString*) filePath
{
    [self.backgroundMusic load:filePath];    
}    

-(void) playBackgroundMusic:(NSString*) filePath loop:(BOOL) loop
{
    [self.backgroundMusic load:filePath];

	if (loop) {
		[self.backgroundMusic setNumberOfLoops:-1];
	} else {
		[self.backgroundMusic setNumberOfLoops:0];
	}

	if (!willPlayBackgroundMusic || _mute) {
		CDLOGINFO(@"Denshion::CDAudioManager - play bgm aborted because audio is not exclusive or sound is muted");
		return;
	}

	[self.backgroundMusic play];
}

-(void) stopBackgroundMusic
{
    [self.backgroundMusic stop];
}

-(void) pauseBackgroundMusic
{
    [self.backgroundMusic pause];
}    

-(void) resumeBackgroundMusic
{
    if (!willPlayBackgroundMusic || _mute) {
        CDLOGINFO(@"Denshion::CDAudioManager - resume bgm aborted because audio is not exclusive or sound is muted");
        return;
    }
    
    if (![self.backgroundMusic paused]) {
        return;
    }
    
    [self.backgroundMusic resume];
}    

-(void) rewindBackgroundMusic
{
    [self.backgroundMusic rewind];
}    

-(void) setBackgroundMusicCompletionListener:(id) listener selector:(SEL) selector {
    backgroundMusicCompletionListener = listener;
    backgroundMusicCompletionSelector = selector;
}    

/*
 * Call this method to have the audio manager automatically handle application resign and
 * become active.  Pass a tAudioManagerResignBehavior to indicate the desired behavior
 * for resigning and becoming active again.
 *
 * If autohandle is YES then the applicationWillResignActive and applicationDidBecomActive 
 * methods are automatically called, otherwise you must call them yourself at the appropriate time.
 *
 * Based on idea of Dominique Bongard
 */
-(void) setResignBehavior:(tAudioManagerResignBehavior) resignBehavior autoHandle:(BOOL) autoHandle { 

    if (!_isObservingAppEvents && autoHandle) {
        [[NSNotificationCenter defaultCenter] addObserver:self    selector:@selector(applicationWillResignActive:) name:@"UIApplicationWillResignActiveNotification" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self    selector:@selector(applicationDidBecomeActive:) name:@"UIApplicationDidBecomeActiveNotification" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self    selector:@selector(applicationWillTerminate:) name:@"UIApplicationWillTerminateNotification" object:nil];
        _isObservingAppEvents = TRUE;
    }
    _resignBehavior = resignBehavior;
}    

- (void) applicationWillResignActive {
    self->_resigned = YES;
    
    //Set the audio sesssion to one that allows sharing so that other audio won't be clobbered on resume
    [self audioSessionSetCategory:AVAudioSessionCategoryAmbient];
    
    switch (_resignBehavior) {
            
        case kAMRBStopPlay:
            
            for( CDLongAudioSource *audioSource in audioSourceChannels) {
                if (audioSource.isPlaying) {
                    audioSource->systemPaused = YES;
                    audioSource->systemPauseLocation = audioSource.audioSourcePlayer.currentTime;
                    [audioSource stop];
                } else {
                    //Music is either paused or stopped, if it is paused it will be restarted
                    //by OS so we will stop it.
                    audioSource->systemPaused = NO;
                    [audioSource stop];
                }
            }
            break;
            
        case kAMRBStop:
            //Stop music regardless of whether it is playing or not because if it was paused
            //then the OS would resume it
            for( CDLongAudioSource *audioSource in audioSourceChannels) {
                [audioSource stop];
            }    
            
        default:
            break;
            
    }            
    CDLOGINFO(@"Denshion::CDAudioManager - handled resign active");
}

//Called when application resigns active only if setResignBehavior has been called
- (void) applicationWillResignActive:(NSNotification *) notification
{
    [self applicationWillResignActive];
}    

- (void) applicationDidBecomeActive {
    
    if (self->_resigned) {
        _resigned = NO;
        //Reset the mode incase something changed with audio while we were inactive
        [self setMode:_mode];
        switch (_resignBehavior) {
                
            case kAMRBStopPlay:
                
                //Music had been stopped but stop maintains current time
                //so playing again will continue from where music was before resign active.
                //We check if music can be played because while we were inactive the user might have
                //done something that should force music to not play such as starting a track in the iPod
                if (self.willPlayBackgroundMusic) {
                    for( CDLongAudioSource *audioSource in audioSourceChannels) {
                        if (audioSource->systemPaused) {
                            [audioSource resume];
                            audioSource->systemPaused = NO;
                        }
                    }
                }
                break;
                
            default:
                break;
                
        }
        CDLOGINFO(@"Denshion::CDAudioManager - audio manager handled become active");
    }
}

//Called when application becomes active only if setResignBehavior has been called
- (void) applicationDidBecomeActive:(NSNotification *) notification
{
    [self applicationDidBecomeActive];
}

//Called when application terminates only if setResignBehavior has been called 
- (void) applicationWillTerminate:(NSNotification *) notification
{
    CDLOGINFO(@"Denshion::CDAudioManager - audio manager handling terminate");
    [self stopBackgroundMusic];
}

/** The audio source completed playing */
- (void) cdAudioSourceDidFinishPlaying:(CDLongAudioSource *) audioSource {
    CDLOGINFO(@"Denshion::CDAudioManager - audio manager got told background music finished");
    if (backgroundMusicCompletionSelector != nil) {
        [backgroundMusicCompletionListener performSelector:backgroundMusicCompletionSelector];
    }    
}    

-(void) beginInterruption {
    CDLOGINFO(@"Denshion::CDAudioManager - begin interruption");
    [self audioSessionInterrupted];
}

-(void) endInterruption {
    CDLOGINFO(@"Denshion::CDAudioManager - end interruption");
    [self audioSessionResumed];
}

#if __CC_PLATFORM_IOS >= 40000
-(void) endInterruptionWithFlags:(NSUInteger)flags {
    CDLOGINFO(@"Denshion::CDAudioManager - interruption ended with flags %i",flags);
    if (flags == AVAudioSessionInterruptionFlags_ShouldResume) {
        [self audioSessionResumed];
    }    
}
#endif

-(void)audioSessionInterrupted 
{ 
    if (!_interrupted) {
        CDLOGINFO(@"Denshion::CDAudioManager - Audio session interrupted"); 
        _interrupted = YES;

        // Deactivate the current audio session 
        [self audioSessionSetActive:NO];
        
        if (alcGetCurrentContext() != NULL) {
            CDLOGINFO(@"Denshion::CDAudioManager - Setting OpenAL context to NULL"); 

            ALenum  error = AL_NO_ERROR;

            // set the current context to NULL will 'shutdown' openAL 
            alcMakeContextCurrent(NULL); 
        
            if((error = alGetError()) != AL_NO_ERROR) {
                CDLOG(@"Denshion::CDAudioManager - Error making context current %x\n", error);
            } 
            #pragma unused(error)
        }
    }    
} 

-(void)audioSessionResumed 
{ 
    if (_interrupted) {
        CDLOGINFO(@"Denshion::CDAudioManager - Audio session resumed"); 
        _interrupted = NO;
        
        BOOL activationResult = NO;
        // Reactivate the current audio session
        activationResult = [self audioSessionSetActive:YES]; 
        
        //This code is to handle a problem with iOS 4.0 and 4.01 where reactivating the session can fail if
        //task switching is performed too rapidly. A test case that reliably reproduces the issue is to call the
        //iPhone and then hang up after two rings (timing may vary ;))
        //Basically we keep waiting and trying to let the OS catch up with itself but the number of tries is
        //limited.
        if (!activationResult) {
            CDLOG(@"Denshion::CDAudioManager - Failure reactivating audio session, will try wait-try cycle"); 
            int activateCount = 0;
            while (!activationResult && activateCount < 10) {
                [NSThread sleepForTimeInterval:0.5];
                activationResult = [self audioSessionSetActive:YES]; 
                activateCount++;
                CDLOGINFO(@"Denshion::CDAudioManager - Reactivation attempt %i status = %i",activateCount,activationResult); 
            }    
        }
        
        if (alcGetCurrentContext() == NULL) {
            CDLOGINFO(@"Denshion::CDAudioManager - Restoring OpenAL context"); 
            ALenum  error = AL_NO_ERROR;
            // Restore open al context 
            alcMakeContextCurrent([soundEngine openALContext]); 
            if((error = alGetError()) != AL_NO_ERROR) {
                CDLOG(@"Denshion::CDAudioManager - Error making context current%x\n", error);
            } 
            #pragma unused(error)
        }    
    }    
}

+(void) end {
    [sharedManager release];
    sharedManager = nil;
}    

@end

///////////////////////////////////////////////////////////////////////////////////////
@implementation CDLongAudioSourceFader

-(void) _setTargetProperty:(float) newVal {
    ((CDLongAudioSource*)target).volume = newVal;
}    

-(float) _getTargetProperty {
    return ((CDLongAudioSource*)target).volume;
}

-(void) _stopTarget {
    //Pause instead of stop as stop releases resources and causes problems in the simulator
    [((CDLongAudioSource*)target) pause];
}

-(Class) _allowableType {
    return [CDLongAudioSource class];
}    

@end
///////////////////////////////////////////////////////////////////////////////////////
@implementation CDBufferManager

-(id) initWithEngine:(CDSoundEngine *) theSoundEngine {
    if ((self = [super init])) {
        soundEngine = theSoundEngine;
        loadedBuffers = [[NSMutableDictionary alloc] initWithCapacity:CD_BUFFERS_START];
        freedBuffers = [[NSMutableArray alloc] init];
        nextBufferId = 0;
    }    
    return self;
}    

-(void) dealloc {
    [loadedBuffers release];
    [freedBuffers release];
    [super dealloc];
}    

-(int) bufferForFile:(NSString*) filePath create:(BOOL) create {
    
    NSNumber* soundId = (NSNumber*)[loadedBuffers objectForKey:filePath];
    if(soundId == nil)
    {
        if (create) {
            NSNumber* bufferId = nil;
            //First try to get a buffer from the free buffers
            if ([freedBuffers count] > 0) {
                bufferId = [[[freedBuffers lastObject] retain] autorelease];
                [freedBuffers removeLastObject]; 
                CDLOGINFO(@"Denshion::CDBufferManager reusing buffer id %i",[bufferId intValue]);
            } else {
                bufferId = [[NSNumber alloc] initWithInt:nextBufferId];
                [bufferId autorelease];
                CDLOGINFO(@"Denshion::CDBufferManager generating new buffer id %i",[bufferId intValue]);
                nextBufferId++;
            }
            
            if ([soundEngine loadBuffer:[bufferId intValue] filePath:filePath]) {
                //File successfully loaded
                CDLOGINFO(@"Denshion::CDBufferManager buffer loaded %@ %@",bufferId,filePath);
                [loadedBuffers setObject:bufferId forKey:filePath];
                return [bufferId intValue];
            } else {
                //File didn't load, put buffer id on free list
                [freedBuffers addObject:bufferId];
                return kCDNoBuffer;
            }    
        } else {
            //No matching buffer was found
            return kCDNoBuffer;
        }    
    } else {
        return [soundId intValue];
    }    
}    

-(void) releaseBufferForFile:(NSString *) filePath {
    int bufferId = [self bufferForFile:filePath create:NO];
    if (bufferId != kCDNoBuffer) {
        [soundEngine unloadBuffer:bufferId];
        [loadedBuffers removeObjectForKey:filePath];
        NSNumber *freedBufferId = [[NSNumber alloc] initWithInt:bufferId];
        [freedBufferId autorelease];
        [freedBuffers addObject:freedBufferId];
    }    
}    
@end



