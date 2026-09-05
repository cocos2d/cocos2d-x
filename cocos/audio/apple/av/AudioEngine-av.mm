/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#define LOG_TAG "AudioEngine-av.mm"

#include "audio/apple/av/AudioEngine-av.h"

#import <AVFoundation/AVFoundation.h>

#include "audio/include/AudioEngine.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/ccUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#endif

using namespace cocos2d;

static AudioEngineImpl* s_instance = nullptr;
static id s_configObserver = nil;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
@interface AudioEngineSessionHandler : NSObject
{
}

-(id) init;
-(void)handleInterruption:(NSNotification*)notification;

@end

@implementation AudioEngineSessionHandler

-(id) init
{
    if (self = [super init])
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterruption:) name:AVAudioSessionInterruptionNotification object:[AVAudioSession sharedInstance]];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterruption:) name:UIApplicationDidBecomeActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterruption:) name:UIApplicationWillResignActiveNotification object:nil];

        BOOL success = [[AVAudioSession sharedInstance]
                        setCategory: AVAudioSessionCategoryAmbient
                        error: nil];
        if (!success)
            ALOGE("Fail to set audio session.");
    }
    return self;
}

-(void)handleInterruption:(NSNotification*)notification
{
    static bool isAudioSessionInterrupted = false;
    static bool resumeOnBecomingActive = false;
    static bool pauseOnResignActive = false;

    if ([notification.name isEqualToString:AVAudioSessionInterruptionNotification])
    {
        NSInteger reason = [[[notification userInfo] objectForKey:AVAudioSessionInterruptionTypeKey] integerValue];
        if (reason == AVAudioSessionInterruptionTypeBegan)
        {
            isAudioSessionInterrupted = true;

            ALOGD("AVAudioSessionInterruptionTypeBegan, pause the engine");
            if (s_instance != nullptr)
                s_instance->onEngineInterrupted();

            if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive)
            {
                pauseOnResignActive = true;
            }
        }

        if (reason == AVAudioSessionInterruptionTypeEnded)
        {
            isAudioSessionInterrupted = false;

            if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive)
            {
                ALOGD("AVAudioSessionInterruptionTypeEnded, application == UIApplicationStateActive, resume the engine");
                NSError *error = nil;
                [[AVAudioSession sharedInstance] setActive:YES error:&error];
                if(error != nil){
                    ALOGE("AVAudioSessionInterruptionTypeEnded, AVAudioSession setActive fail, %d",(int)error.code);
                    // Leave the engine parked and retry on the next activation, otherwise the
                    // interrupted flag sticks and playback never comes back.
                    resumeOnBecomingActive = true;
                    return;
                }

                if (s_instance != nullptr)
                    s_instance->onEngineResumed();

                if (Director::getInstance()->isPaused())
                {
                    ALOGD("AVAudioSessionInterruptionTypeEnded, director was paused, try to resume it.");
                    Director::getInstance()->resume();
                }
            }
            else
            {
                ALOGD("AVAudioSessionInterruptionTypeEnded, application != UIApplicationStateActive, resumeOnBecomingActive = true");
                resumeOnBecomingActive = true;
            }
        }
    }
    else if ([notification.name isEqualToString:UIApplicationWillResignActiveNotification])
    {
        ALOGD("UIApplicationWillResignActiveNotification");
        if (pauseOnResignActive)
        {
            pauseOnResignActive = false;
            ALOGD("UIApplicationWillResignActiveNotification, pause the engine");
            if (s_instance != nullptr)
                s_instance->onEngineInterrupted();
        }
    }
    else if ([notification.name isEqualToString:UIApplicationDidBecomeActiveNotification])
    {
        ALOGD("UIApplicationDidBecomeActiveNotification");
        if (resumeOnBecomingActive)
        {
            resumeOnBecomingActive = false;
            ALOGD("UIApplicationDidBecomeActiveNotification, resume the engine");
            NSError *error = nil;
            BOOL success = [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryAmbient error: &error];
            if (!success) {
                ALOGE("Fail to set audio session.");
                return;
            }
            [[AVAudioSession sharedInstance] setActive:YES error:&error];
            if(error != nil){
                ALOGE("UIApplicationDidBecomeActiveNotification, AVAudioSession setActive fail, %d",(int)error.code);
                return;
            }

            if (s_instance != nullptr)
                s_instance->onEngineResumed();
        }
        else if (isAudioSessionInterrupted)
        {
            ALOGD("Audio session is still interrupted, pause director!");
            Director::getInstance()->pause();
        }
    }
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:AVAudioSessionInterruptionNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillResignActiveNotification object:nil];

    [super dealloc];
}
@end

static id s_AudioEngineSessionHandler = nullptr;
#endif

AudioEngineImpl::AudioEngineImpl()
: _engine(nil)
, _lazyInitLoop(true)
, _rebuildPlayback(false)
, _sessionInterrupted(false)
, _currentAudioID(0)
, _scheduler(nullptr)
{
    for (int i = 0; i < MAX_AUDIOINSTANCES; ++i)
    {
        _nodes[i] = nil;
        _nodeFormats[i] = nil;
    }
    s_instance = this;
}

AudioEngineImpl::~AudioEngineImpl()
{
    if (_scheduler != nullptr)
    {
        _scheduler->unschedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this);
    }

    for (auto&& e : _audioPlayers)
    {
        delete e.second;
    }
    _audioPlayers.clear();
    _audioCaches.clear();

    if (s_configObserver != nil)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:s_configObserver];
        [s_configObserver release];
        s_configObserver = nil;
    }

    if (_engine != nil)
    {
        [_engine stop];
        for (int i = 0; i < MAX_AUDIOINSTANCES; ++i)
        {
            if (_nodes[i] != nil)
            {
                [_engine detachNode:_nodes[i]];
                [_nodes[i] release];
                _nodes[i] = nil;
            }
            [_nodeFormats[i] release];
            _nodeFormats[i] = nil;
        }
        [_engine release];
        _engine = nil;
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    [s_AudioEngineSessionHandler release];
    s_AudioEngineSessionHandler = nullptr;
#endif
    s_instance = nullptr;
}

bool AudioEngineImpl::init()
{
    bool ret = false;
    do
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        s_AudioEngineSessionHandler = [[AudioEngineSessionHandler alloc] init];
#endif

        _engine = [[AVAudioEngine alloc] init];
        BREAK_IF_ERR_LOG(_engine == nil, "Failed to create AVAudioEngine");

        // Reading mainMixerNode is what connects the mixer to the output node.
        BREAK_IF_ERR_LOG(_engine.mainMixerNode == nil, "AVAudioEngine has no main mixer");

        for (int i = 0; i < MAX_AUDIOINSTANCES; ++i)
        {
            _nodes[i] = [[AVAudioPlayerNode alloc] init];
            [_engine attachNode:_nodes[i]];
            _unusedNodesPool.push_back(i);
        }

        s_configObserver = [[[NSNotificationCenter defaultCenter]
                             addObserverForName:AVAudioEngineConfigurationChangeNotification
                                         object:_engine
                                          queue:nil
                                     usingBlock:^(NSNotification* note) {
                                         (void)note;
                                         if (s_instance != nullptr)
                                             s_instance->onConfigurationChanged();
                                     }] retain];

        _scheduler = Director::getInstance()->getScheduler();
        ret = true;
        ALOGI("AVAudioEngine was initialized successfully!");

    } while (false);

    return ret;
}

bool AudioEngineImpl::startEngine()
{
    std::lock_guard<std::mutex> lk(_engineMutex);

    if (_engine == nil || _sessionInterrupted)
        return false;

    if (_engine.isRunning)
        return true;

    NSError* error = nil;
    if (![_engine startAndReturnError:&error])
    {
        ALOGE("Failed to start AVAudioEngine, %s", [[error localizedDescription] UTF8String]);
        return false;
    }

    return true;
}

void AudioEngineImpl::connectNode(int index, AVAudioFormat* format)
{
    std::lock_guard<std::mutex> lk(_engineMutex);

    if (_nodeFormats[index] != nil && [_nodeFormats[index] isEqual:format])
        return;

    [_nodeFormats[index] release];
    _nodeFormats[index] = [format retain];

    [_engine connect:_nodes[index] to:_engine.mainMixerNode format:format];
}

void AudioEngineImpl::restartPlayback()
{
    if (_sessionInterrupted)
        return;

    {
        std::lock_guard<std::mutex> lk(_engineMutex);

        for (int i = 0; i < MAX_AUDIOINSTANCES; ++i)
        {
            if (_nodeFormats[i] != nil)
            {
                [_engine connect:_nodes[i] to:_engine.mainMixerNode format:_nodeFormats[i]];
            }
        }

        NSError* error = nil;
        if (![_engine startAndReturnError:&error])
        {
            ALOGE("Failed to restart AVAudioEngine, %s", [[error localizedDescription] UTF8String]);
            return;
        }
    }

    for (auto&& e : _audioPlayers)
    {
        AudioPlayer* player = e.second;
        if (player->_ready && !player->_isDestroyed)
        {
            player->rescheduleFrom(player->getTime());
        }
    }
}

void AudioEngineImpl::onEngineInterrupted()
{
    _sessionInterrupted = true;

    std::lock_guard<std::mutex> lk(_engineMutex);

    if (_engine != nil && _engine.isRunning)
    {
        [_engine pause];
    }
}

void AudioEngineImpl::onEngineResumed()
{
    _sessionInterrupted = false;
    _rebuildPlayback = true;
}

void AudioEngineImpl::onConfigurationChanged()
{
    if (!_sessionInterrupted)
    {
        _rebuildPlayback = true;
    }
}

AudioCache* AudioEngineImpl::preload(const std::string& filePath, std::function<void(bool)> callback)
{
    AudioCache* audioCache = nullptr;

    auto it = _audioCaches.find(filePath);
    if (it == _audioCaches.end()) {
        audioCache = &_audioCaches[filePath];
        audioCache->_fileFullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        unsigned int cacheId = audioCache->_id;
        auto isCacheDestroyed = audioCache->_isDestroyed;
        AudioEngine::addTask([audioCache, cacheId, isCacheDestroyed](){
            if (*isCacheDestroyed)
            {
                ALOGV("AudioCache (id=%u) was destroyed, no need to launch readDataTask.", cacheId);
                audioCache->setSkipReadDataTask(true);
                return;
            }
            audioCache->readDataTask(cacheId);
        });
    }
    else {
        audioCache = &it->second;
    }

    if (audioCache && callback)
    {
        audioCache->addLoadCallback(callback);
    }
    return audioCache;
}

int AudioEngineImpl::play2d(const std::string &filePath ,bool loop ,float volume)
{
    if (_engine == nil) {
        return AudioEngine::INVALID_AUDIO_ID;
    }

    int nodeIndex = findValidNode();
    if (nodeIndex < 0)
    {
        return AudioEngine::INVALID_AUDIO_ID;
    }

    auto player = new (std::nothrow) AudioPlayer;
    if (player == nullptr) {
        _unusedNodesPool.push_back(nodeIndex);
        return AudioEngine::INVALID_AUDIO_ID;
    }

    player->_nodeIndex = nodeIndex;
    player->_node = _nodes[nodeIndex];
    player->_loop = loop;
    player->_volume = volume;

    auto audioCache = preload(filePath, nullptr);
    if (audioCache == nullptr) {
        delete player;
        _unusedNodesPool.push_back(nodeIndex);
        return AudioEngine::INVALID_AUDIO_ID;
    }

    player->setCache(audioCache);
    _threadMutex.lock();
    _audioPlayers[_currentAudioID] = player;
    _threadMutex.unlock();

    audioCache->addPlayCallback(std::bind(&AudioEngineImpl::_play2d,this,audioCache,_currentAudioID));

    if (_lazyInitLoop) {
        _lazyInitLoop = false;
        _scheduler->schedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this, 0.05f, false);
    }

    return _currentAudioID++;
}

void AudioEngineImpl::_play2d(AudioCache *cache, int audioID)
{
    //Note: It maybe in sub thread or main thread :(
    if (!*cache->_isDestroyed && cache->_state == AudioCache::State::READY)
    {
        _threadMutex.lock();
        auto playerIt = _audioPlayers.find(audioID);
        if (playerIt != _audioPlayers.end())
        {
            connectNode(playerIt->second->_nodeIndex, cache->_format);

            if (startEngine() && playerIt->second->play2d()) {
                _scheduler->performFunctionInCocosThread([audioID](){

                    if (AudioEngine::_audioIDInfoMap.find(audioID) != AudioEngine::_audioIDInfoMap.end()) {
                        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
                    }
                });
            }
        }
        _threadMutex.unlock();
    }
    else
    {
        ALOGD("AudioEngineImpl::_play2d, cache was destroyed or not ready!");
        auto iter = _audioPlayers.find(audioID);
        if (iter != _audioPlayers.end())
        {
            iter->second->_removeByAudioEngine = true;
        }
    }
}

int AudioEngineImpl::findValidNode()
{
    int nodeIndex = -1;
    if (!_unusedNodesPool.empty())
    {
        nodeIndex = _unusedNodesPool.front();
        _unusedNodesPool.pop_front();
    }

    return nodeIndex;
}

void AudioEngineImpl::setVolume(int audioID,float volume)
{
    auto player = _audioPlayers[audioID];
    player->_volume = volume;

    if (player->_ready) {
        player->_node.volume = volume;
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    _audioPlayers[audioID]->setLoop(loop);
}

bool AudioEngineImpl::pause(int audioID)
{
    auto player = _audioPlayers[audioID];

    player->getTime();
    player->_paused = true;
    [player->_node pause];

    return true;
}

bool AudioEngineImpl::resume(int audioID)
{
    auto player = _audioPlayers[audioID];

    player->_paused = false;
    if (!startEngine())
        return false;

    [player->_node play];

    return true;
}

void AudioEngineImpl::stop(int audioID)
{
    auto player = _audioPlayers[audioID];
    player->destroy();

    // Call 'update' method to cleanup immediately since the schedule may be cancelled without any notification.
    update(0.0f);
}

void AudioEngineImpl::stopAll()
{
    for(auto&& player : _audioPlayers)
    {
        player.second->destroy();
    }

    // Call 'update' method to cleanup immediately since the schedule may be cancelled without any notification.
    update(0.0f);
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
    auto player = _audioPlayers[audioID];
    if (!player->_ready)
        return 0.0f;

    return player->getTime();
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    return _audioPlayers[audioID]->setTime(time);
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    _audioPlayers[audioID]->_finishCallbak = callback;
}

void AudioEngineImpl::update(float dt)
{
    if (_rebuildPlayback && !_sessionInterrupted)
    {
        _rebuildPlayback = false;
        restartPlayback();
    }

    int audioID;
    AudioPlayer* player;

    for (auto it = _audioPlayers.begin(); it != _audioPlayers.end(); ) {
        audioID = it->first;
        player = it->second;
        const int nodeIndex = player->_nodeIndex;

        if (player->_removeByAudioEngine)
        {
            AudioEngine::remove(audioID);
            _threadMutex.lock();
            it = _audioPlayers.erase(it);
            _threadMutex.unlock();
            delete player;
            _unusedNodesPool.push_back(nodeIndex);
        }
        else if (player->_ready && player->isFinished()) {

            std::string filePath;
            if (player->_finishCallbak) {
                auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                filePath = audioInfo.filePath;
            }

            AudioEngine::remove(audioID);
            _threadMutex.lock();
            it = _audioPlayers.erase(it);
            _threadMutex.unlock();

            if (player->_finishCallbak) {
                player->_finishCallbak(audioID, filePath); //FIXME: callback will delay 50ms
            }

            delete player;
            _unusedNodesPool.push_back(nodeIndex);
        }
        else{
            player->topUpSchedule();
            ++it;
        }
    }

    if(_audioPlayers.empty()){
        _lazyInitLoop = true;

        {
            std::lock_guard<std::mutex> lk(_engineMutex);
            if (_engine != nil && _engine.isRunning)
            {
                [_engine pause];
            }
        }

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
