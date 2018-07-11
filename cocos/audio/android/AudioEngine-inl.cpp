/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#define LOG_TAG "AudioEngineImpl"

#include "audio/android/AudioEngine-inl.h"

#include <unistd.h>
// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <unordered_map>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>
#include "audio/include/AudioEngine.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"
#include "base/ccUTF8.h"
#include "platform/android/CCFileUtils-android.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

#include "audio/android/IAudioPlayer.h"
#include "audio/android/ICallerThreadUtils.h"
#include "audio/android/AudioPlayerProvider.h"
#include "audio/android/cutils/log.h"
#include "audio/android/UrlAudioPlayer.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

// Audio focus values synchronized with which in cocos/platform/android/java/src/org/cocos2dx/lib/Cocos2dxActivity.java
static const int AUDIOFOCUS_GAIN = 0;
static const int AUDIOFOCUS_LOST = 1;
static const int AUDIOFOCUS_LOST_TRANSIENT = 2;
static const int AUDIOFOCUS_LOST_TRANSIENT_CAN_DUCK = 3;

static int __currentAudioFocus = AUDIOFOCUS_GAIN;
static AudioEngineImpl* __impl = nullptr;

class CallerThreadUtils : public ICallerThreadUtils
{
public:
    virtual void performFunctionInCallerThread(const std::function<void()>& func)
    {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread(func);
    };

    virtual std::thread::id getCallerThreadId()
    {
        return _tid;
    };

    void setCallerThreadId(std::thread::id tid)
    {
        _tid = tid;
    };

private:
    std::thread::id _tid;
};

static CallerThreadUtils __callerThreadUtils;

static int fdGetter(const std::string& url, off_t* start, off_t* length)
{
    int fd = -1;
    if (cocos2d::FileUtilsAndroid::getObbFile() != nullptr)
    {
        fd = getObbAssetFileDescriptorJNI(url.c_str(), start, length);
    } 
    
    if (fd <= 0)
    {
        auto asset = AAssetManager_open(cocos2d::FileUtilsAndroid::getAssetManager(), url.c_str(), AASSET_MODE_UNKNOWN);
        // open asset as file descriptor
        fd = AAsset_openFileDescriptor(asset, start, length);
        AAsset_close(asset);
    }

    if (fd <= 0)
    {
        ALOGE("Failed to open file descriptor for '%s'", url.c_str());
    }

    return fd;
};

//====================================================
AudioEngineImpl::AudioEngineImpl()
    : _engineObject(nullptr)
    , _engineEngine(nullptr)
    , _outputMixObject(nullptr)
    , _audioPlayerProvider(nullptr)
    , _onPauseListener(nullptr)
    , _onResumeListener(nullptr)
    , _audioIDIndex(0)
    , _lazyInitLoop(true)
{
    __callerThreadUtils.setCallerThreadId(std::this_thread::get_id());
    __impl = this;
}

AudioEngineImpl::~AudioEngineImpl()
{
    if (_audioPlayerProvider != nullptr)
    {
        delete _audioPlayerProvider;
        _audioPlayerProvider = nullptr;
    }

    if (_outputMixObject)
    {
        (*_outputMixObject)->Destroy(_outputMixObject);
    }
    if (_engineObject)
    {
        (*_engineObject)->Destroy(_engineObject);
    }

    if (_onPauseListener != nullptr)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_onPauseListener);
    }

    if (_onResumeListener != nullptr)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_onResumeListener);
    }

    __impl = nullptr;
}

bool AudioEngineImpl::init()
{
    bool ret = false;
    do{

        // create engine
        auto result = slCreateEngine(&_engineObject, 0, nullptr, 0, nullptr, nullptr);
        if(SL_RESULT_SUCCESS != result){ ERRORLOG("create opensl engine fail"); break; }

        // realize the engine
        result = (*_engineObject)->Realize(_engineObject, SL_BOOLEAN_FALSE);
        if(SL_RESULT_SUCCESS != result){ ERRORLOG("realize the engine fail"); break; }

        // get the engine interface, which is needed in order to create other objects
        result = (*_engineObject)->GetInterface(_engineObject, SL_IID_ENGINE, &_engineEngine);
        if(SL_RESULT_SUCCESS != result){ ERRORLOG("get the engine interface fail"); break; }

        // create output mix
        const SLInterfaceID outputMixIIDs[] = {};
        const SLboolean outputMixReqs[] = {};
        result = (*_engineEngine)->CreateOutputMix(_engineEngine, &_outputMixObject, 0, outputMixIIDs, outputMixReqs);           
        if(SL_RESULT_SUCCESS != result){ ERRORLOG("create output mix fail"); break; }

        // realize the output mix
        result = (*_outputMixObject)->Realize(_outputMixObject, SL_BOOLEAN_FALSE);
        if(SL_RESULT_SUCCESS != result){ ERRORLOG("realize the output mix fail"); break; }

        _audioPlayerProvider = new AudioPlayerProvider(_engineEngine, _outputMixObject, getDeviceSampleRate(), getDeviceAudioBufferSizeInFrames(), fdGetter, &__callerThreadUtils);

        _onPauseListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_COME_TO_BACKGROUND, CC_CALLBACK_1(AudioEngineImpl::onEnterBackground, this));

        _onResumeListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(AudioEngineImpl::onEnterForeground, this));

        ret = true;
    }while (false);

    return ret;
}

void AudioEngineImpl::onEnterBackground(EventCustom* event)
{
    // _audioPlayerProvider->pause() pauses AudioMixer and PcmAudioService,
    // but UrlAudioPlayers could not be paused.
    if (_audioPlayerProvider != nullptr)
    {
        _audioPlayerProvider->pause();
    }

    // pause UrlAudioPlayers which are playing.
    for (auto&& e : _audioPlayers)
    {
        auto player = e.second;
        if (dynamic_cast<UrlAudioPlayer*>(player) != nullptr
            && player->getState() == IAudioPlayer::State::PLAYING)
        {
            _urlAudioPlayersNeedResume.emplace(e.first, player);
            player->pause();
        }
    }
}

void AudioEngineImpl::onEnterForeground(EventCustom* event)
{
    // _audioPlayerProvider->resume() resumes AudioMixer and PcmAudioService,
    // but UrlAudioPlayers could not be resumed.
    if (_audioPlayerProvider != nullptr)
    {
        _audioPlayerProvider->resume();
    }

    // resume UrlAudioPlayers
    for (auto&& iter : _urlAudioPlayersNeedResume)
    {
        iter.second->resume();
    }
    _urlAudioPlayersNeedResume.clear();
}

void AudioEngineImpl::setAudioFocusForAllPlayers(bool isFocus)
{
    for (const auto& e : _audioPlayers)
    {
        e.second->setAudioFocus(isFocus);
    }
}

int AudioEngineImpl::play2d(const std::string &filePath ,bool loop ,float volume)
{
    ALOGV("play2d, _audioPlayers.size=%d", (int)_audioPlayers.size());
    auto audioId = AudioEngine::INVALID_AUDIO_ID;

    do 
    {
        if (_engineEngine == nullptr || _audioPlayerProvider == nullptr)
            break;

        auto fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);

        audioId = _audioIDIndex++;

        auto player = _audioPlayerProvider->getAudioPlayer(fullPath);
        if (player != nullptr)
        {
            player->setId(audioId);
            _audioPlayers.insert(std::make_pair(audioId, player));

            player->setPlayEventCallback([this, player, filePath](IAudioPlayer::State state){

                if (state != IAudioPlayer::State::OVER && state != IAudioPlayer::State::STOPPED)
                {
                    ALOGV("Ignore state: %d", static_cast<int>(state));
                    return;
                }

                int id = player->getId();

                ALOGV("Removing player id=%d, state:%d", id, (int)state);

                AudioEngine::remove(id);
                if (_audioPlayers.find(id) != _audioPlayers.end())
                {
                    _audioPlayers.erase(id);
                }
                if (_urlAudioPlayersNeedResume.find(id) != _urlAudioPlayersNeedResume.end())
                {
                    _urlAudioPlayersNeedResume.erase(id);
                }

                auto iter = _callbackMap.find(id);
                if (iter != _callbackMap.end())
                {
                    if (state == IAudioPlayer::State::OVER)
                    {
                        iter->second(id, filePath);
                    }
                    _callbackMap.erase(iter);
                }
            });

            player->setLoop(loop);
            player->setVolume(volume);
            player->setAudioFocus(__currentAudioFocus == AUDIOFOCUS_GAIN);
            player->play();
        } 
        else
        {
            ALOGE("Oops, player is null ...");
            return AudioEngine::INVALID_AUDIO_ID;
        }

        AudioEngine::_audioIDInfoMap[audioId].state = AudioEngine::AudioState::PLAYING;
        
    } while (0);

    return audioId;
}

void AudioEngineImpl::setVolume(int audioID,float volume)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        player->setVolume(volume);
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        player->setLoop(loop);
    }
}

void AudioEngineImpl::pause(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        player->pause();
    }
}

void AudioEngineImpl::resume(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        player->resume();
    }
}

void AudioEngineImpl::stop(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        player->stop();
    }
}

void AudioEngineImpl::stopAll()
{
    if (_audioPlayers.empty())
    {
        return;
    }

    // Create a temporary vector for storing all players since
    // p->stop() will trigger _audioPlayers.erase, 
    // and it will cause a crash as it's already in for loop
    std::vector<IAudioPlayer*> players;
    players.reserve(_audioPlayers.size());

    for (const auto& e : _audioPlayers)
    {
        players.push_back(e.second);
    }

    for (auto p : players)
    {
        p->stop();
    }
}

float AudioEngineImpl::getDuration(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        return player->getDuration();
    }
    return 0.0f;
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        return player->getPosition();
    }
    return 0.0f;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end())
    {
        auto player = iter->second;
        return player->setPosition(time);
    }
    return false;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    _callbackMap[audioID] = callback;
}

void AudioEngineImpl::preload(const std::string& filePath, const std::function<void(bool)>& callback)
{
    if (_audioPlayerProvider != nullptr)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        _audioPlayerProvider->preloadEffect(fullPath, [callback](bool succeed, PcmData data){
            if (callback != nullptr)
            {
                callback(succeed);
            }
        });
    }
    else
    {
        if (callback != nullptr)
        {
            callback(false);
        }
    }
}

void AudioEngineImpl::uncache(const std::string& filePath)
{
    if (_audioPlayerProvider != nullptr)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        _audioPlayerProvider->clearPcmCache(fullPath);
    }
}

void AudioEngineImpl::uncacheAll()
{
    if (_audioPlayerProvider != nullptr)
    {
        _audioPlayerProvider->clearAllPcmCaches();
    }
}

// It's invoked from javaactivity-android.cpp
void cocos_audioengine_focus_change(int focusChange)
{
    if (focusChange < AUDIOFOCUS_GAIN || focusChange > AUDIOFOCUS_LOST_TRANSIENT_CAN_DUCK)
    {
        CCLOGERROR("cocos_audioengine_focus_change: unknown value: %d", focusChange);
        return;
    }
    CCLOG("cocos_audioengine_focus_change: %d", focusChange);
    __currentAudioFocus = focusChange;

    if (__impl == nullptr)
    {
        CCLOGWARN("cocos_audioengine_focus_change: AudioEngineImpl isn't ready!");
        return;
    }

    if (__currentAudioFocus == AUDIOFOCUS_GAIN)
    {
        __impl->setAudioFocusForAllPlayers(true);
    }
    else
    {
        __impl->setAudioFocusForAllPlayers(false);
    }
}

#endif
