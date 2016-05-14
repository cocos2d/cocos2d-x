/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
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
 ****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "audio/apple/AudioEngine-inl.h"

#import <OpenAL/alc.h>
#import <AVFoundation/AVFoundation.h>

#include "audio/include/AudioEngine.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/ccUtils.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

static ALCdevice *s_ALDevice = nullptr;
static ALCcontext *s_ALContext = nullptr;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
@interface AudioEngineSessionHandler : NSObject
{
}

-(id) init;
-(void)handleInterruption:(NSNotification*)notification;

@end

@implementation AudioEngineSessionHandler

// only enable it on iOS. Disable it on tvOS
#if !defined(CC_TARGET_OS_TVOS)
void AudioEngineInterruptionListenerCallback(void* user_data, UInt32 interruption_state)
{
    if (kAudioSessionBeginInterruption == interruption_state)
    {
      alcMakeContextCurrent(nullptr);
    }
    else if (kAudioSessionEndInterruption == interruption_state)
    {
      OSStatus result = AudioSessionSetActive(true);
      if (result) NSLog(@"Error setting audio session active! %d\n", result);

      alcMakeContextCurrent(s_ALContext);
    }
}
#endif

-(id) init
{
    if (self = [super init])
    {
      if ([[[UIDevice currentDevice] systemVersion] intValue] > 5) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterruption:) name:AVAudioSessionInterruptionNotification object:[AVAudioSession sharedInstance]];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterruption:) name:UIApplicationDidBecomeActiveNotification object:nil];
      }
    // only enable it on iOS. Disable it on tvOS
    // AudioSessionInitialize removed from tvOS
#if !defined(CC_TARGET_OS_TVOS)
      else {
        AudioSessionInitialize(NULL, NULL, AudioEngineInterruptionListenerCallback, self);
      }
#endif
    }
    return self;
}

-(void)handleInterruption:(NSNotification*)notification
{
    static bool resumeOnBecomingActive = false;
    
    if ([notification.name isEqualToString:AVAudioSessionInterruptionNotification]) {
        NSInteger reason = [[[notification userInfo] objectForKey:AVAudioSessionInterruptionTypeKey] integerValue];
        if (reason == AVAudioSessionInterruptionTypeBegan) {
            alcMakeContextCurrent(NULL);
        }
        
        if (reason == AVAudioSessionInterruptionTypeEnded) {
            if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive) {
                NSError *error = nil;
                [[AVAudioSession sharedInstance] setActive:YES error:&error];
                alcMakeContextCurrent(s_ALContext);
            } else {
                resumeOnBecomingActive = true;
            }
        }
    }
    
    if ([notification.name isEqualToString:UIApplicationDidBecomeActiveNotification] && resumeOnBecomingActive) {
        resumeOnBecomingActive = false;
        NSError *error = nil;
        BOOL success = [[AVAudioSession sharedInstance]
                        setCategory: AVAudioSessionCategoryAmbient
                        error: &error];
        if (!success) {
            printf("Fail to set audio session.\n");
            return;
        }
        [[AVAudioSession sharedInstance] setActive:YES error:&error];
        alcMakeContextCurrent(s_ALContext);
    }
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:AVAudioSessionInterruptionNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
    
    [super dealloc];
}
@end

static id s_AudioEngineSessionHandler = nullptr;
#endif

AudioEngineImpl::AudioEngineImpl()
: _lazyInitLoop(true)
, _currentAudioID(0)
{
    
}

AudioEngineImpl::~AudioEngineImpl()
{
    if (s_ALContext) {
        alDeleteSources(MAX_AUDIOINSTANCES, _alSources);
        
        _audioCaches.clear();
        
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(s_ALContext);
    }
    if (s_ALDevice) {
        alcCloseDevice(s_ALDevice);
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    [s_AudioEngineSessionHandler release];
#endif
}

bool AudioEngineImpl::init()
{
    bool ret = false;
    do{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        s_AudioEngineSessionHandler = [[AudioEngineSessionHandler alloc] init];
#endif
        
        s_ALDevice = alcOpenDevice(nullptr);
        
        if (s_ALDevice) {
            s_ALContext = alcCreateContext(s_ALDevice, nullptr);
            alcMakeContextCurrent(s_ALContext);
            
            alGenSources(MAX_AUDIOINSTANCES, _alSources);
            auto alError = alGetError();
            if(alError != AL_NO_ERROR)
            {
                printf("%s:generating sources fail! error = %x\n", __PRETTY_FUNCTION__, alError);
                break;
            }
            
            for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
                _alSourceUsed[_alSources[i]] = false;
            }
            _scheduler = Director::getInstance()->getScheduler();
            ret = true;
        }
    }while (false);
    
    return ret;
}

AudioCache* AudioEngineImpl::preload(const std::string& filePath, std::function<void(bool)> callback)
{
    AudioCache* audioCache = nullptr;
    
    auto it = _audioCaches.find(filePath);
    if (it == _audioCaches.end()) {
        audioCache = &_audioCaches[filePath];
        audioCache->_fileFullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        
        AudioEngine::addTask(std::bind(&AudioCache::readDataTask, audioCache));
    }
    else {
        audioCache = &it->second;
    }
    
    if(audioCache && callback)
    {
        audioCache->addLoadCallback(callback);
    }
    return audioCache;
}

int AudioEngineImpl::play2d(const std::string &filePath ,bool loop ,float volume)
{
    if (s_ALDevice == nullptr) {
        return AudioEngine::INVALID_AUDIO_ID;
    }
    
    bool sourceFlag = false;
    ALuint alSource = 0;
    for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
        alSource = _alSources[i];
        
        if ( !_alSourceUsed[alSource]) {
            sourceFlag = true;
            break;
        }
    }
    if(!sourceFlag){
        return AudioEngine::INVALID_AUDIO_ID;
    }
    
    auto player = new (std::nothrow) AudioPlayer;
    if (player == nullptr) {
        return AudioEngine::INVALID_AUDIO_ID;
    }
    player->_alSource = alSource;
    player->_loop = loop;
    player->_volume = volume;
    
    auto audioCache = preload(filePath, nullptr);
    if (audioCache == nullptr) {
        delete player;
        return AudioEngine::INVALID_AUDIO_ID;
    }
    
    _threadMutex.lock();
    _audioPlayers[_currentAudioID] = player;
    _threadMutex.unlock();
    
    audioCache->addPlayCallback(std::bind(&AudioEngineImpl::_play2d,this,audioCache,_currentAudioID));
    
    _alSourceUsed[alSource] = true;
    
    if (_lazyInitLoop) {
        _lazyInitLoop = false;
        _scheduler->schedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this, 0.05f, false);
    }
    
    return _currentAudioID++;
}

void AudioEngineImpl::_play2d(AudioCache *cache, int audioID)
{
    if(cache->_alBufferReady){
        _threadMutex.lock();
        auto playerIt = _audioPlayers.find(audioID);
        if (playerIt != _audioPlayers.end() && playerIt->second->play2d(cache)) {
            _scheduler->performFunctionInCocosThread([audioID](){
                if (AudioEngine::_audioIDInfoMap.find(audioID) != AudioEngine::_audioIDInfoMap.end()) {
                    AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
                }
            });
        }
        _threadMutex.unlock();
    }
}

void AudioEngineImpl::setVolume(int audioID,float volume)
{
    auto player = _audioPlayers[audioID];
    player->_volume = volume;
    
    if (player->_ready) {
        alSourcef(_audioPlayers[audioID]->_alSource, AL_GAIN, volume);
        
        auto error = alGetError();
        if (error != AL_NO_ERROR) {
            printf("%s: audio id = %d, error = %x\n", __PRETTY_FUNCTION__,audioID,error);
        }
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    auto player = _audioPlayers[audioID];
    
    if (player->_ready) {
        if (player->_streamingSource) {
            player->setLoop(loop);
        } else {
            if (loop) {
                alSourcei(player->_alSource, AL_LOOPING, AL_TRUE);
            } else {
                alSourcei(player->_alSource, AL_LOOPING, AL_FALSE);
            }
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                printf("%s: audio id = %d, error = %x\n", __PRETTY_FUNCTION__,audioID,error);
            }
        }
    }
    else {
        player->_loop = loop;
    }
}

bool AudioEngineImpl::pause(int audioID)
{
    bool ret = true;
    alSourcePause(_audioPlayers[audioID]->_alSource);
    
    auto error = alGetError();
    if (error != AL_NO_ERROR) {
        ret = false;
        printf("%s: audio id = %d, error = %x\n", __PRETTY_FUNCTION__,audioID,error);
    }
    
    return ret;
}

bool AudioEngineImpl::resume(int audioID)
{
    bool ret = true;
    alSourcePlay(_audioPlayers[audioID]->_alSource);
    
    auto error = alGetError();
    if (error != AL_NO_ERROR) {
        ret = false;
        printf("%s: audio id = %d, error = %x\n", __PRETTY_FUNCTION__,audioID,error);
    }
    
    return ret;
}

void AudioEngineImpl::stop(int audioID)
{
    auto player = _audioPlayers[audioID];
    player->destroy();
    _alSourceUsed[player->_alSource] = false;
}

void AudioEngineImpl::stopAll()
{
    for(auto&& player : _audioPlayers)
    {
        player.second->destroy();
    }
    for(int index = 0; index < MAX_AUDIOINSTANCES; ++index)
    {
        _alSourceUsed[_alSources[index]] = false;
    }
}

float AudioEngineImpl::getDuration(int audioID)
{
    auto player = _audioPlayers[audioID];
    if(player->_ready){
        return player->_audioCache->_duration;
    } else {
        return AudioEngine::TIME_UNKNOWN;
    }
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    float ret = 0.0f;
    auto player = _audioPlayers[audioID];
    if(player->_ready){
        if (player->_streamingSource) {
            ret = player->getTime();
        } else {
            alGetSourcef(player->_alSource, AL_SEC_OFFSET, &ret);
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                printf("%s, audio id:%d,error code:%x", __PRETTY_FUNCTION__,audioID,error);
            }
        }
    }
    
    return ret;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    bool ret = false;
    auto player = _audioPlayers[audioID];
    
    do {
        if (!player->_ready) {
            break;
        }
        
        if (player->_streamingSource) {
            ret = player->setTime(time);
            break;
        }
        else {
            if (player->_audioCache->_bytesOfRead != player->_audioCache->_dataSize &&
                (time * player->_audioCache->_sampleRate * player->_audioCache->_bytesPerFrame) > player->_audioCache->_bytesOfRead) {
                printf("%s: audio id = %d\n", __PRETTY_FUNCTION__,audioID);
                break;
            }
            
            alSourcef(player->_alSource, AL_SEC_OFFSET, time);
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                printf("%s: audio id = %d, error = %x\n", __PRETTY_FUNCTION__,audioID,error);
            }
            ret = true;
        }
    } while (0);
    
    return ret;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    _audioPlayers[audioID]->_finishCallbak = callback;
}

void AudioEngineImpl::update(float dt)
{
    ALint sourceState;
    int audioID;
    AudioPlayer* player;
    
    for (auto it = _audioPlayers.begin(); it != _audioPlayers.end(); ) {
        audioID = it->first;
        player = it->second;
        alGetSourcei(player->_alSource, AL_SOURCE_STATE, &sourceState);
        
        if(player->_removeByAudioEngine)
        {
            AudioEngine::remove(audioID);
            _threadMutex.lock();
            it = _audioPlayers.erase(it);
            _threadMutex.unlock();
            delete player;
        }
        else if (player->_ready && sourceState == AL_STOPPED) {
            _alSourceUsed[player->_alSource] = false;
            if (player->_finishCallbak) {
                auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                player->_finishCallbak(audioID, *audioInfo.filePath);
            }
            
            AudioEngine::remove(audioID);
            delete player;
            _threadMutex.lock();
            it = _audioPlayers.erase(it);
            _threadMutex.unlock();
        }
        else{
            ++it;
        }
    }
    
    if(_audioPlayers.empty()){
        _lazyInitLoop = true;
        _scheduler->unschedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this);
    }
}

void AudioEngineImpl::uncache(const std::string &filePath)
{
    _audioCaches.erase(filePath);
}

void AudioEngineImpl::uncacheAll()
{
    _audioCaches.clear();
}

#endif
