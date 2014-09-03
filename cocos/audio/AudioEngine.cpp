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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "audio/include/AudioEngine.h"
#include "platform/CCFileUtils.h"
#include "base/ccUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "android/AudioEngine-inl.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "ios/AudioEngine-inl.h"
#endif

static cocos2d::AudioEngine *s_sharedAudioEngine = nullptr;

#define TIME_DELAY_PRECISION 0.0001

using namespace cocos2d;

const int AudioEngine::INVAILD_AUDIO_ID = -1;
const float AudioEngine::TIME_UNKNOWN = -1.0f;

AudioEngine* AudioEngine::getInstance()
{
    if (!s_sharedAudioEngine)
    {
        s_sharedAudioEngine = new (std::nothrow) AudioEngine();
        CCASSERT(s_sharedAudioEngine, "FATAL: Not enough memory");

        if(!s_sharedAudioEngine->init()){
            delete s_sharedAudioEngine;
            s_sharedAudioEngine = nullptr;
        }
    }

    return s_sharedAudioEngine;
}

void AudioEngine::destroyInstance()
{
    delete s_sharedAudioEngine;
    s_sharedAudioEngine = nullptr;
}

AudioEngine::AudioEngine()
    : _maxInstances(kMaxSources)
{
    _audioEngineImpl = new (std::nothrow) AudioEngineImpl(this);

    _audioProfiles["audioengine_defaultProfile"] = new AudioProfile;
    _defaultProfile = _audioProfiles["audioengine_defaultProfile"];
}

AudioEngine::~AudioEngine()
{
    for (auto it = _audioProfiles.begin(); it != _audioProfiles.end(); ++it) {
        delete it->second;
    }
    _audioProfiles.clear();

    delete _audioEngineImpl;
}

bool AudioEngine::init()
{
    return _audioEngineImpl->init();
}

int AudioEngine::play2d(const std::string& filePath, bool loop, float volume, AudioProfile *profile)
{
    int ret = AudioEngine::INVAILD_AUDIO_ID;
    if ( !FileUtils::getInstance()->isFileExist(filePath)){
        return ret;
    }

    do {
        auto targetProfile = profile;
        if (!targetProfile) {
            targetProfile = _defaultProfile;
        }

        if (_audioInfos.size() >= _maxInstances || (targetProfile->maxInstances != 0 && targetProfile->audioIDs.size() >= targetProfile->maxInstances)) {
            log("Fail to play %s cause by limited max instance",filePath.c_str());
            break;
        }

        if (targetProfile->minDelay > TIME_DELAY_PRECISION) {
            auto currTime = utils::gettime();
            if (targetProfile->lastPlayTime > TIME_DELAY_PRECISION && currTime - targetProfile->lastPlayTime <= targetProfile->minDelay) {
                log("Fail to play %s cause by limited minimum delay",filePath.c_str());
                break;
            }
        }
        
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        else if (volume > 1.0f){
            volume = 1.0f;
        }
        
        ret = _audioEngineImpl->play2d(filePath, loop, volume, targetProfile);
        if (ret != INVAILD_AUDIO_ID)
        {
            _audioIDs[filePath].push_back(ret);
            auto it = _audioIDs.find(filePath);
            
            auto& audioRef = _audioInfos[ret];
            audioRef.volume = volume;
            audioRef.loop = loop;
            audioRef.is3dAudio = false;
            audioRef.filePath = &it->first;
            audioRef.profile = targetProfile;
            //audioRef.state = AudioEngine::AudioState::PLAYING;
        }
    } while (0);

    return ret;
}

void AudioEngine::setLoop(int audioID, bool loop)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.loop != loop){
        _audioEngineImpl->setLoop(audioID, loop);
        it->second.loop = loop;
    }
}

void AudioEngine::setVolume(int audioID, float volume)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end()){
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        else if (volume > 1.0f){
            volume = 1.0f;
        }
        _audioEngineImpl->setVolume(audioID, volume);
        it->second.volume = volume;
    }
}

void AudioEngine::pause(int audioID)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.state == AudioState::PLAYING){
        _audioEngineImpl->pause(audioID);
        it->second.state = AudioState::PAUSED;
    }
}

void AudioEngine::pauseAll()
{
    auto itEnd = _audioInfos.end();
    for (auto it = _audioInfos.begin(); it != itEnd; ++it)
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
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.state == AudioState::PAUSED){
        _audioEngineImpl->resume(audioID);
        it->second.state = AudioState::PLAYING;
    }
}

void AudioEngine::resumeAll()
{
    auto itEnd = _audioInfos.end();
    for (auto it = _audioInfos.begin(); it != itEnd; ++it)
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
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end()){
        _audioEngineImpl->stop(audioID);

        if (it->second.profile) {
            it->second.profile->audioIDs.remove(audioID);
        }
        _audioIDs[*it->second.filePath].remove(audioID);
        _audioInfos.erase(audioID);
    }
}

void AudioEngine::remove(int audioID)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end()){
        if (it->second.profile) {
            it->second.profile->audioIDs.remove(audioID);
        }
        _audioIDs[*it->second.filePath].remove(audioID);
        _audioInfos.erase(audioID);
    }
}

void AudioEngine::stopAll()
{
    _audioEngineImpl->stopAll();
    auto itEnd = _audioInfos.end();
    for (auto it = _audioInfos.begin(); it != itEnd; ++it)
    {
        if (it->second.profile){
            it->second.profile->audioIDs.remove(it->first);
        }
    }
    _audioIDs.clear();
    _audioInfos.clear();
}

void AudioEngine::uncache(const std::string &filePath)
{
    if(_audioIDs.find(filePath) != _audioIDs.end()){
        auto itEnd = _audioIDs[filePath].end();
        int audioID;
        for (auto it = _audioIDs[filePath].begin() ; it != itEnd; ++it) {
            audioID = *it;
            _audioEngineImpl->stop(audioID);
            
            auto& info = _audioInfos[audioID];
            if (info.profile) {
                info.profile->audioIDs.remove(audioID);
            }
            _audioInfos.erase(audioID);
        }
        _audioEngineImpl->uncache(filePath);
        _audioIDs.erase(filePath);
    }
}

void AudioEngine::uncacheAll()
{
    stopAll();
    _audioEngineImpl->uncacheAll();
}

float AudioEngine::getDuration(int audioID)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.state != AudioState::INITIAL)
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
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.state != AudioState::INITIAL){
        return _audioEngineImpl->setCurrentTime(audioID, time);
    }

    return false;
}

float AudioEngine::getCurrentTime(int audioID)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end() && it->second.state != AudioState::INITIAL){
        return _audioEngineImpl->getCurrentTime(audioID);
    }
    return 0.0f;
}

void AudioEngine::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end()){
        _audioEngineImpl->setFinishCallback(audioID, callback);
    }
}

bool AudioEngine::setMaxAudioInstance(unsigned int maxInstances)
{
    if (maxInstances <= kMaxSources) {
        _maxInstances = maxInstances;
        return true;
    }

    return false;
}

void AudioEngine::setDefaultProfile(AudioProfile *profile)
{
    if (_defaultProfile != profile && _defaultProfile) {
        auto itEnd = _defaultProfile->audioIDs.end();
        for (auto it = _defaultProfile->audioIDs.begin() ; it != itEnd; ++it) {
            _audioInfos[*it].profile = profile;
            profile->audioIDs.push_back(*it);
        }
        _defaultProfile->audioIDs.clear();
    }

    _defaultProfile = profile;
}

void AudioEngine::setProfile(int audioID, AudioProfile *profile)
{
    auto it = _audioInfos.find(audioID);
    if (it != _audioInfos.end())
    {
        if (it->second.profile) {
            it->second.profile->audioIDs.remove(audioID);
        }

        it->second.profile = profile;
        if (profile) {
            profile->audioIDs.push_back(audioID);
        }
    }
}

AudioProfile* AudioEngine::createProfile(const std::string &name, int maxInstances, double minDelay, float minRange, float maxRange)
{
    if (_audioProfiles.find(name) == _audioProfiles.end()) {
        _audioProfiles[name] = new AudioProfile;
    }
    auto profile = _audioProfiles[name];
    
    profile->maxInstances = maxInstances;
    profile->minDelay = minDelay;
    profile->minRange = minRange;
    profile->maxRange = maxRange;
    
    return profile;
}

AudioProfile* AudioEngine::getProfile(const std::string &name)
{
    auto it = _audioProfiles.find(name);
    if (it != _audioProfiles.end()) {
        return it->second;
    } else {
        log("AudioEngine::getProfile-->profile:%s not found", name.c_str());
        return nullptr;
    }
}

bool AudioEngine::isLoop(int audioID) const
{
    auto tmpIterator = _audioInfos.find(audioID);
    if (tmpIterator != _audioInfos.end())
    {
        return tmpIterator->second.loop;
    }
    
    log("AudioEngine::isLoop-->The audio instance %d is non-existent", audioID);
    return false;
}

float AudioEngine::getVolume(int audioID) const
{
    auto tmpIterator = _audioInfos.find(audioID);
    if (tmpIterator != _audioInfos.end())
    {
        return tmpIterator->second.volume;
    }

    log("AudioEngine::getVolume-->The audio instance %d is non-existent", audioID);
    return 0.0f;
}

AudioEngine::AudioState AudioEngine::getState(int audioID) const
{
    auto tmpIterator = _audioInfos.find(audioID);
    if (tmpIterator != _audioInfos.end())
    {
        return tmpIterator->second.state;
    }

    log("AudioEngine::getState-->The audio instance %d is non-existent", audioID);
    return AudioState::INITIAL;
}

AudioProfile* AudioEngine::getProfile(int audioID)
{
    auto tmpIterator = _audioInfos.find(audioID);
    if (tmpIterator != _audioInfos.end())
    {
        return tmpIterator->second.profile;
    }
    
    log("AudioEngine::getProfile-->The audio instance %d is non-existent", audioID);
    return nullptr;
}

AudioProfile* AudioEngine::getDefaultProfile() const
{
    return _defaultProfile;
}

unsigned int AudioEngine::getMaxAudioInstance()
{
    return _maxInstances;
}

#endif
