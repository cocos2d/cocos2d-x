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

#include "audio/include/AudioEngine.h"
#include <condition_variable>
#include <queue>
#include "platform/CCFileUtils.h"
#include "base/ccUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "android/AudioEngine-inl.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#include "apple/AudioEngine-inl.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "win32/AudioEngine-win32.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#include "winrt/AudioEngine-winrt.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#include "linux/AudioEngine-linux.h"
#endif

#define TIME_DELAY_PRECISION 0.0001

#ifdef ERROR
#undef ERROR
#endif // ERROR

using namespace cocos2d;
using namespace cocos2d::experimental;

const int AudioEngine::INVALID_AUDIO_ID = -1;
const float AudioEngine::TIME_UNKNOWN = -1.0f;

//audio file path,audio IDs
std::unordered_map<std::string,std::list<int>> AudioEngine::_audioPathIDMap;
//profileName,ProfileHelper
std::unordered_map<std::string, AudioEngine::ProfileHelper> AudioEngine::_audioPathProfileHelperMap;
unsigned int AudioEngine::_maxInstances = MAX_AUDIOINSTANCES;
AudioEngine::ProfileHelper* AudioEngine::_defaultProfileHelper = nullptr;
std::unordered_map<int, AudioEngine::AudioInfo> AudioEngine::_audioIDInfoMap;
AudioEngineImpl* AudioEngine::_audioEngineImpl = nullptr;

AudioEngine::AudioEngineThreadPool* AudioEngine::s_threadPool = nullptr;

class AudioEngine::AudioEngineThreadPool
{
public:
    AudioEngineThreadPool(bool detach, int threads = 4)
        : _detach(detach)
        , _stop(false)
    {
        for (int index = 0; index < threads; ++index)
        {
            _workers.emplace_back(std::thread(std::bind(&AudioEngineThreadPool::threadFunc, this)));
            if (_detach)
            {
                _workers[index].detach();
            }
        }
    }

    void addTask(const std::function<void()> &task){
        std::unique_lock<std::mutex> lk(_queueMutex);
        _taskQueue.emplace(task);
        _taskCondition.notify_one();
    }

    ~AudioEngineThreadPool()
    {
        {
            std::unique_lock<std::mutex> lk(_queueMutex);
            _stop = true;
            _taskCondition.notify_all();
        }

        if (!_detach)
        {
            for (auto&& worker : _workers) {
                worker.join();
            }
        }
    }

private:
    void threadFunc()
    {
        while (true) {
            std::function<void()> task = nullptr;
            {
                std::unique_lock<std::mutex> lk(_queueMutex);
                if (_stop)
                {
                    break;
                }
                if (!_taskQueue.empty())
                {
                    task = std::move(_taskQueue.front());
                    _taskQueue.pop();
                }
                else
                {
                    _taskCondition.wait(lk);
                    continue;
                }
            }

            task();
        }
    }

    std::vector<std::thread>  _workers;
    std::queue< std::function<void()> > _taskQueue;

    std::mutex _queueMutex;
    std::condition_variable _taskCondition;
    bool _detach;
    bool _stop;
};

void AudioEngine::end()
{
    if (s_threadPool)
    {
        delete s_threadPool;
        s_threadPool = nullptr;
    }

    delete _audioEngineImpl;
    _audioEngineImpl = nullptr;

    delete _defaultProfileHelper;
    _defaultProfileHelper = nullptr;
}

bool AudioEngine::lazyInit()
{
    if (_audioEngineImpl == nullptr)
    {
        _audioEngineImpl = new (std::nothrow) AudioEngineImpl();
        if(!_audioEngineImpl ||  !_audioEngineImpl->init() ){
            delete _audioEngineImpl;
            _audioEngineImpl = nullptr;
           return false;
        }
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    if (_audioEngineImpl && s_threadPool == nullptr)
    {
        s_threadPool = new (std::nothrow) AudioEngineThreadPool(true);
    }
#elif CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    if (_audioEngineImpl && s_threadPool == nullptr)
    {
        s_threadPool = new (std::nothrow) AudioEngineThreadPool(false);
    }
#endif

    return true;
}

int AudioEngine::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile *profile)
{
    int ret = AudioEngine::INVALID_AUDIO_ID;

    do {
        if ( !lazyInit() ){
            break;
        }

        if ( !FileUtils::getInstance()->isFileExist(filePath)){
            break;
        }

        auto profileHelper = _defaultProfileHelper;
        if (profile && profile != &profileHelper->profile){
            CC_ASSERT(!profile->name.empty());
            profileHelper = &_audioPathProfileHelperMap[profile->name];
            profileHelper->profile = *profile;
        }
        
        if (_audioIDInfoMap.size() >= _maxInstances) {
            log("Fail to play %s cause by limited max instance of AudioEngine",filePath.c_str());
            break;
        }
        if (profileHelper)
        {
             if(profileHelper->profile.maxInstances != 0 && profileHelper->audioIDs.size() >= profileHelper->profile.maxInstances){
                 log("Fail to play %s cause by limited max instance of AudioProfile",filePath.c_str());
                 break;
             }
             if (profileHelper->profile.minDelay > TIME_DELAY_PRECISION) {
                 auto currTime = utils::gettime();
                 if (profileHelper->lastPlayTime > TIME_DELAY_PRECISION && currTime - profileHelper->lastPlayTime <= profileHelper->profile.minDelay) {
                     log("Fail to play %s cause by limited minimum delay",filePath.c_str());
                     break;
                 }
             }
        }
        
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        else if (volume > 1.0f){
            volume = 1.0f;
        }
        
        ret = _audioEngineImpl->play2d(filePath, loop, volume);
        if (ret != INVALID_AUDIO_ID)
        {
            _audioPathIDMap[filePath].push_back(ret);
            auto it = _audioPathIDMap.find(filePath);
            
            auto& audioRef = _audioIDInfoMap[ret];
            audioRef.volume = volume;
            audioRef.loop = loop;
            audioRef.filePath = &it->first;

            if (profileHelper) {
                profileHelper->lastPlayTime = utils::gettime();
                profileHelper->audioIDs.push_back(ret);
            }
            audioRef.profileHelper = profileHelper;
        }
    } while (0);

    return ret;
}

void AudioEngine::setLoop(int audioID, bool loop)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.loop != loop){
        _audioEngineImpl->setLoop(audioID, loop);
        it->second.loop = loop;
    }
}

void AudioEngine::setVolume(int audioID, float volume)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()){
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        else if (volume > 1.0f){
            volume = 1.0f;
        }

        if (it->second.volume != volume){
            _audioEngineImpl->setVolume(audioID, volume);
            it->second.volume = volume;
        }
    }
}

void AudioEngine::pause(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PLAYING){
        _audioEngineImpl->pause(audioID);
        it->second.state = AudioState::PAUSED;
    }
}

void AudioEngine::pauseAll()
{
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
    {
        if (it->second.state == AudioState::PLAYING)
        {
            _audioEngineImpl->pause(it->first);
            it->second.state = AudioState::PAUSED;
        }
    }
}

void AudioEngine::resume(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PAUSED){
        _audioEngineImpl->resume(audioID);
        it->second.state = AudioState::PLAYING;
    }
}

void AudioEngine::resumeAll()
{
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
    {
        if (it->second.state == AudioState::PAUSED)
        {
            _audioEngineImpl->resume(it->first);
            it->second.state = AudioState::PLAYING;
        }
    }
}

void AudioEngine::stop(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()){
        _audioEngineImpl->stop(audioID);

        remove(audioID);
    }
}

void AudioEngine::remove(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()){
        if (it->second.profileHelper) {
            it->second.profileHelper->audioIDs.remove(audioID);
        }
        _audioPathIDMap[*it->second.filePath].remove(audioID);
        _audioIDInfoMap.erase(audioID);
    }
}

void AudioEngine::stopAll()
{
    if(!_audioEngineImpl){
        return;
    }
    _audioEngineImpl->stopAll();
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it)
    {
        if (it->second.profileHelper){
            it->second.profileHelper->audioIDs.remove(it->first);
        }
    }
    _audioPathIDMap.clear();
    _audioIDInfoMap.clear();
}

void AudioEngine::uncache(const std::string &filePath)
{
    if(_audioPathIDMap.find(filePath) != _audioPathIDMap.end()){
        auto itEnd = _audioPathIDMap[filePath].end();
        for (auto it = _audioPathIDMap[filePath].begin() ; it != itEnd; ++it) {
            auto audioID = *it;
            _audioEngineImpl->stop(audioID);
            
            auto itInfo = _audioIDInfoMap.find(audioID);
            if (itInfo != _audioIDInfoMap.end()){
                if (itInfo->second.profileHelper) {
                    itInfo->second.profileHelper->audioIDs.remove(audioID);
                }
                _audioIDInfoMap.erase(audioID);
            }
        }
        _audioPathIDMap.erase(filePath);
    }

    if (_audioEngineImpl){
        _audioEngineImpl->uncache(filePath);
    }
}

void AudioEngine::uncacheAll()
{
    if(!_audioEngineImpl){
        return;
    }
    stopAll();
    _audioEngineImpl->uncacheAll();
}

float AudioEngine::getDuration(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALZING)
    {
        if (it->second.duration == TIME_UNKNOWN)
        {
            it->second.duration = _audioEngineImpl->getDuration(audioID);
        }
        return it->second.duration;
    }
    
    return TIME_UNKNOWN;
}

bool AudioEngine::setCurrentTime(int audioID, float time)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALZING){
        return _audioEngineImpl->setCurrentTime(audioID, time);
    }

    return false;
}

float AudioEngine::getCurrentTime(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALZING){
        return _audioEngineImpl->getCurrentTime(audioID);
    }
    return 0.0f;
}

void AudioEngine::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()){
        _audioEngineImpl->setFinishCallback(audioID, callback);
    }
}

bool AudioEngine::setMaxAudioInstance(int maxInstances)
{
    if (maxInstances > 0 && maxInstances <= MAX_AUDIOINSTANCES) {
        _maxInstances = maxInstances;
        return true;
    }

    return false;
}

bool AudioEngine::isLoop(int audioID)
{
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end())
    {
        return tmpIterator->second.loop;
    }
    
    log("AudioEngine::isLoop-->The audio instance %d is non-existent", audioID);
    return false;
}

float AudioEngine::getVolume(int audioID)
{
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end())
    {
        return tmpIterator->second.volume;
    }

    log("AudioEngine::getVolume-->The audio instance %d is non-existent", audioID);
    return 0.0f;
}

AudioEngine::AudioState AudioEngine::getState(int audioID)
{
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end())
    {
        return tmpIterator->second.state;
    }
    
    return AudioState::ERROR;
}

AudioProfile* AudioEngine::getProfile(int audioID)
{
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end())
    {
        return &it->second.profileHelper->profile;
    }
    
    return nullptr;
}

AudioProfile* AudioEngine::getDefaultProfile()
{
    if (_defaultProfileHelper == nullptr)
    {
        _defaultProfileHelper = new (std::nothrow) ProfileHelper();
    }
    
    return &_defaultProfileHelper->profile;
}

AudioProfile* AudioEngine::getProfile(const std::string &name)
{
    auto it = _audioPathProfileHelperMap.find(name);
    if (it != _audioPathProfileHelperMap.end()) {
        return &it->second.profile;
    } else {
        return nullptr;
    }
}

void AudioEngine::preload(const std::string& filePath, std::function<void(bool isSuccess)> callback)
{
    lazyInit();

    if (_audioEngineImpl)
    {
        if (!FileUtils::getInstance()->isFileExist(filePath)){
            if (callback)
            {
                callback(false);
            }
            return;
        }

        _audioEngineImpl->preload(filePath, callback);
    }
}

void AudioEngine::addTask(const std::function<void()>& task)
{
    lazyInit();

    if (_audioEngineImpl && s_threadPool)
    {
        s_threadPool->addTask(task);
    }
}
