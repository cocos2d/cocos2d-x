/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#include "AudioEngine-winrt.h"
#include <condition_variable>


using namespace cocos2d;
using namespace cocos2d::experimental;


namespace cocos2d {
    namespace experimental {
        class AudioEngineThreadPool
        {
        public:
            AudioEngineThreadPool()
                : _running(true)
                , _numThread(6)
            {
                _threads.reserve(_numThread);
                _tasks.reserve(_numThread);

                for (int index = 0; index < _numThread; ++index) {
                    _tasks.push_back(nullptr);
                    _threads.push_back(std::thread(std::bind(&AudioEngineThreadPool::threadFunc, this, index)));
                }
            }

            void addTask(const std::function<void()> &task){
                _taskMutex.lock();
                int targetIndex = -1;
                for (int index = 0; index < _numThread; ++index) {
                    if (_tasks[index] == nullptr) {
                        targetIndex = index;
                        _tasks[index] = task;
                        break;
                    }
                }
                if (targetIndex == -1) {
                    _tasks.push_back(task);
                    _threads.push_back(std::thread(std::bind(&AudioEngineThreadPool::threadFunc, this, _numThread)));

                    _numThread++;
                }
                _taskMutex.unlock();
                _sleepCondition.notify_all();
            }

            void destroy()
            {
                _running = false;
                _sleepCondition.notify_all();

                for (int index = 0; index < _numThread; ++index) {
                    _threads[index].join();
                }
            }
        private:
            bool _running;
            std::vector<std::thread>  _threads;
            std::vector< std::function<void()> > _tasks;

            void threadFunc(int index)
            {
                while (_running) {
                    std::function<void()> task = nullptr;
                    _taskMutex.lock();
                    task = _tasks[index];
                    _taskMutex.unlock();

                    if (nullptr == task)
                    {
                        std::unique_lock<std::mutex> lk(_sleepMutex);
                        _sleepCondition.wait(lk);
                        continue;
                    }

                    task();

                    _taskMutex.lock();
                    _tasks[index] = nullptr;
                    _taskMutex.unlock();
                }
            }

            int _numThread;

            std::mutex _taskMutex;
            std::mutex _sleepMutex;
            std::condition_variable _sleepCondition;
        };
    }
}

AudioEngineImpl::AudioEngineImpl()
    : _lazyInitLoop(true)
    , _currentAudioID(0)
    , _threadPool(nullptr)
{

}

AudioEngineImpl::~AudioEngineImpl()
{
    _audioCaches.clear();

    if (_threadPool) {
        _threadPool->destroy();
        delete _threadPool;
    }
}

bool AudioEngineImpl::init()
{
    bool ret = false;

    if (nullptr == _threadPool) {
        _threadPool = new (std::nothrow) AudioEngineThreadPool();
    }

    ret = true;
    return ret;
}

int AudioEngineImpl::play2d(const std::string &filePath, bool loop, float volume)
{
    AudioCache* audioCache = nullptr;
    auto it = _audioCaches.find(filePath);
    if (it == _audioCaches.end()) {
        audioCache = &_audioCaches[filePath];

        auto ext = filePath.substr(filePath.rfind('.'));
        transform(ext.begin(), ext.end(), ext.begin(), tolower);

        bool eraseCache = true;

        if (ext.compare(".wav") == 0){
            audioCache->_fileFormat = FileFormat::WAV;
            eraseCache = false;
        }
        else if (ext.compare(".ogg") == 0){
            audioCache->_fileFormat = FileFormat::OGG;
            eraseCache = false;
        }
        else if (ext.compare(".mp3") == 0){
            audioCache->_fileFormat = FileFormat::MP3;
            eraseCache = false;
        }
        else{
            log("unsupported media type:%s\n", ext.c_str());
        }

        if (eraseCache){
            _audioCaches.erase(filePath);
            return AudioEngine::INVALID_AUDIO_ID;
        }

        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        audioCache->_fileFullPath = fullPath;
        _threadPool->addTask(std::bind(&AudioCache::readDataTask, audioCache));
    }
    else {
        audioCache = &it->second;
    }

    auto player = &_audioPlayers[_currentAudioID];
    player->_loop = loop;
    player->_volume = volume;
    audioCache->addCallback(std::bind(&AudioEngineImpl::_play2d, this, audioCache, _currentAudioID));

    if (_lazyInitLoop) {
        _lazyInitLoop = false;

        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(schedule_selector(AudioEngineImpl::update), this, 0.05f, false);
    }

    return _currentAudioID++;
}

void AudioEngineImpl::_play2d(AudioCache *cache, int audioID)
{
    if (cache->_isReady){
        auto playerIt = _audioPlayers.find(audioID);
        if (playerIt != _audioPlayers.end()) {
            if (playerIt->second.play2d(cache)) {
                AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
            }
            else{
                _threadMutex.lock();
                _toRemoveAudioIDs.push_back(audioID);
                _threadMutex.unlock();
            }
        }
    }
    else {
        _threadMutex.lock();
        _toRemoveCaches.push_back(cache);
        _toRemoveAudioIDs.push_back(audioID);
        _threadMutex.unlock();
    }
}

void AudioEngineImpl::setVolume(int audioID, float volume)
{
    auto& player = _audioPlayers[audioID];

    if (player._ready){
        player.setVolume(volume);
    }

    if (player.isInError()) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        player._loop = loop;
    }

    if (player.isInError()) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }
}

bool AudioEngineImpl::pause(int audioID)
{
    bool ret = false;
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        player.pause();
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PAUSED;
    }

    ret = !player.isInError();

    if (!ret) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }

    return ret;
}

bool AudioEngineImpl::resume(int audioID)
{
    bool ret = false;
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        player.resume();
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
    }

    ret = !player.isInError();

    if (!ret) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }

    return ret;
}

bool AudioEngineImpl::stop(int audioID)
{
    bool ret = false;
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        player.stop();
        ret = !player.isInError();
    }

    if (!ret) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }

    _audioPlayers.erase(audioID);
    return ret;
}

void AudioEngineImpl::stopAll()
{
    for (auto &player : _audioPlayers) {
        player.second.stop();
    }

    _audioPlayers.clear();
}

float AudioEngineImpl::getDuration(int audioID)
{
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        return player.getDuration();
    }
    else {
        return AudioEngine::TIME_UNKNOWN;
    }
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    float ret = 0.0f;
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        ret = player.getCurrentTime();
    }

    return ret;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    bool ret = false;
    auto& player = _audioPlayers[audioID];

    if (player._ready) {
        ret = player.setTime(time);
    }

    if (!ret) {
        log("%s: audio id = %d, error.\n", __FUNCTION__, audioID);
    }

    return ret;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void(int, const std::string &)> &callback)
{
    _audioPlayers[audioID]._finishCallback = callback;
}

void AudioEngineImpl::update(float dt)
{
    int audioID;

    if (_threadMutex.try_lock()) {
        size_t removeAudioCount = _toRemoveAudioIDs.size();
        for (size_t index = 0; index < removeAudioCount; ++index) {
            audioID = _toRemoveAudioIDs[index];
            auto playerIt = _audioPlayers.find(audioID);
            if (playerIt != _audioPlayers.end()) {
                if (playerIt->second._finishCallback) {
                    auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                    playerIt->second._finishCallback(audioID, *audioInfo.filePath);
                }
                _audioPlayers.erase(audioID);
                AudioEngine::remove(audioID);
            }
        }

        size_t removeCacheCount = _toRemoveCaches.size();
        for (size_t index = 0; index < removeCacheCount; ++index) {
            auto itEnd = _audioCaches.end();
            for (auto it = _audioCaches.begin(); it != itEnd; ++it) {
                if (&it->second == _toRemoveCaches[index]) {
                    _audioCaches.erase(it);
                    break;
                }
            }
        }
        _threadMutex.unlock();
    }

    for (auto it = _audioPlayers.begin(); it != _audioPlayers.end();) {
        audioID = it->first;
        auto& player = it->second;

        if (player._ready && player._state == AudioPlayerState::STOPPED) {
            if (player._finishCallback) {
                auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                player._finishCallback(audioID, *audioInfo.filePath);
            }

            AudioEngine::remove(audioID);
            it = _audioPlayers.erase(it);
        }
        else{
            player.update();
            ++it;
        }
    }

    if (_audioPlayers.empty()){
        _lazyInitLoop = true;

        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(AudioEngineImpl::update), this);
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
