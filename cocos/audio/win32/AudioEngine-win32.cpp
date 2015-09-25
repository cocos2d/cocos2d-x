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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "AudioEngine-win32.h"

#ifdef OPENAL_PLAIN_INCLUDES
#include "alc.h"
#include "alext.h"
#else
#include "AL/alc.h"
#include "AL/alext.h"
#endif
#include "audio/include/AudioEngine.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"
#include "mpg123.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

static ALCdevice *s_ALDevice = nullptr;
static ALCcontext *s_ALContext = nullptr;
static bool MPG123_LAZYINIT = true;

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
        s_ALContext = nullptr;
    }
    if (s_ALDevice) {
        alcCloseDevice(s_ALDevice);
        s_ALDevice = nullptr;
    }

    mpg123_exit();
    MPG123_LAZYINIT = true;
}

bool AudioEngineImpl::init()
{
    bool ret = false;
    do{
        s_ALDevice = alcOpenDevice(NULL);
        
        if (s_ALDevice) {
            auto alError = alGetError();
            s_ALContext = alcCreateContext(s_ALDevice, NULL);
            alcMakeContextCurrent(s_ALContext);
            
            alGenSources(MAX_AUDIOINSTANCES, _alSources);
            alError = alGetError();
            if(alError != AL_NO_ERROR){
                log("%s:generating sources fail! error = %x\n", __FUNCTION__, alError);
                break;
            }
            
            for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
                _alSourceUsed[_alSources[i]] = false;
            }
            
            ret = true;
        }
    }while (false);
    
    return ret;
}

AudioCache* AudioEngineImpl::preload(const std::string& filePath, std::function<void(bool)> callback)
{
    AudioCache* audioCache = nullptr;

    do 
    {
        auto it = _audioCaches.find(filePath);
        if (it != _audioCaches.end())
        {
            audioCache = &it->second;
            if (callback && audioCache->_alBufferReady)
            {
                callback(true);
            }
            break;
        }

        AudioCache::FileFormat fileFormat = AudioCache::FileFormat::UNKNOWN;

        std::string fileExtension = FileUtils::getInstance()->getFileExtension(filePath);
        if (fileExtension == ".ogg")
        {
            fileFormat = AudioCache::FileFormat::OGG;
        }
        else if (fileExtension == ".mp3")
        {
            fileFormat = AudioCache::FileFormat::MP3;

            if (MPG123_LAZYINIT)
            {
                auto error = mpg123_init();
                if (error == MPG123_OK)
                {
                    MPG123_LAZYINIT = false;
                }
                else
                {
                    log("Basic setup goes wrong: %s", mpg123_plain_strerror(error));
                    break;
                }
            }
        }
        else
        {
            log("Unsupported media type file: %s\n", filePath.c_str());
            break;
        }

        audioCache = &_audioCaches[filePath];
        audioCache->_fileFormat = fileFormat;

        audioCache->_fileFullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        AudioEngine::addTask(std::bind(&AudioCache::readDataTask, audioCache));
    } while (false);

    if (callback)
    {
        if (audioCache)
        {
            audioCache->addLoadCallback(callback);
        } 
        else
        {
            callback(false);
        }
    }

    return audioCache;
}

int AudioEngineImpl::play2d(const std::string &filePath ,bool loop ,float volume)
{
    bool availableSourceExist = false;
    ALuint alSource;
    for (int i = 0; i < MAX_AUDIOINSTANCES; ++i) {
        alSource = _alSources[i];
        if ( !_alSourceUsed[alSource]) {
            availableSourceExist = true;
            break;
        }
    }
    if(!availableSourceExist){
        return AudioEngine::INVALID_AUDIO_ID;
    }
    
    AudioCache* audioCache = preload(filePath, nullptr);
    if (audioCache == nullptr)
    {
        return AudioEngine::INVALID_AUDIO_ID;
    }
    
    auto player = &_audioPlayers[_currentAudioID];
    player->_alSource = alSource;
    player->_loop = loop;
    player->_volume = volume;
    audioCache->addPlayCallback(std::bind(&AudioEngineImpl::_play2d, this, audioCache, _currentAudioID));
    
    _alSourceUsed[alSource] = true;
    
    if (_lazyInitLoop) {
        _lazyInitLoop = false;
        
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(schedule_selector(AudioEngineImpl::update), this, 0.05f, false);
    }
    
    return _currentAudioID++;
}

void AudioEngineImpl::_play2d(AudioCache *cache, int audioID)
{
    if(cache->_alBufferReady){
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

void AudioEngineImpl::setVolume(int audioID,float volume)
{
    auto& player = _audioPlayers[audioID];
    player._volume = volume;
    
    if (player._ready) {
        alSourcef(_audioPlayers[audioID]._alSource, AL_GAIN, volume);
        
        auto error = alGetError();
        if (error != AL_NO_ERROR) {
            log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
        }
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    auto& player = _audioPlayers[audioID];
    
    if (player._ready) {
        if (player._streamingSource) {
            player.setLoop(loop);
        } else {
            if (loop) {
                alSourcei(player._alSource, AL_LOOPING, AL_TRUE);
            } else {
                alSourcei(player._alSource, AL_LOOPING, AL_FALSE);
            }
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
            }
        }
    }
    else {
        player._loop = loop;
    }
}

bool AudioEngineImpl::pause(int audioID)
{
    bool ret = true;
    alSourcePause(_audioPlayers[audioID]._alSource);
    
    auto error = alGetError();
    if (error != AL_NO_ERROR) {
        ret = false;
        log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
    }
    
    return ret;
}

bool AudioEngineImpl::resume(int audioID)
{
    bool ret = true;
    alSourcePlay(_audioPlayers[audioID]._alSource);
    
    auto error = alGetError();
    if (error != AL_NO_ERROR) {
        ret = false;
        log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
    }
    
    return ret;
}

bool AudioEngineImpl::stop(int audioID)
{
    bool ret = true;
    auto& player = _audioPlayers[audioID];
    if (player._ready) {
        alSourceStop(player._alSource);
        
        auto error = alGetError();
        if (error != AL_NO_ERROR) {
            ret = false;
            log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
        }
    }
    
    alSourcei(player._alSource, AL_BUFFER, NULL);
    
    _alSourceUsed[player._alSource] = false;
    if (player._streamingSource)
    {
        player.notifyExitThread();
    } 
    else
    {
        _audioPlayers.erase(audioID);
    }
    
    return ret;
}

void AudioEngineImpl::stopAll()
{
    for(int index = 0; index < MAX_AUDIOINSTANCES; ++index)
    {
        alSourceStop(_alSources[index]);
        alSourcei(_alSources[index], AL_BUFFER, NULL);
        _alSourceUsed[_alSources[index]] = false;
    }
    
    for (auto it = _audioPlayers.begin(); it != _audioPlayers.end();) 
    {
        auto& player = it->second;
        if (player._streamingSource)
        {
            player.notifyExitThread();
            ++it;
        }
        else
        {
            it = _audioPlayers.erase(it);
        }
    }
}

float AudioEngineImpl::getDuration(int audioID)
{
    auto& player = _audioPlayers[audioID];
    if(player._ready){
        return player._audioCache->_duration;
    } else {
        return AudioEngine::TIME_UNKNOWN;
    }
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    float ret = 0.0f;
    auto& player = _audioPlayers[audioID];
    if(player._ready){
        if (player._streamingSource) {
            ret = player.getTime();
        } else {
            alGetSourcef(player._alSource, AL_SEC_OFFSET, &ret);
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                log("%s, audio id:%d,error code:%x", __FUNCTION__,audioID,error);
            }
        }
    }
    
    return ret;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    bool ret = false;
    auto& player = _audioPlayers[audioID];
    
    do {
        if (!player._ready) {
            break;
        }
        
        if (player._streamingSource) {
            ret = player.setTime(time);
            break;
        }
        else {
            alSourcef(player._alSource, AL_SEC_OFFSET, time);
            
            auto error = alGetError();
            if (error != AL_NO_ERROR) {
                log("%s: audio id = %d, error = %x\n", __FUNCTION__,audioID,error);
            }
            ret = true;
        }
    } while (0);
    
    return ret;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    _audioPlayers[audioID]._finishCallbak = callback;
}

void AudioEngineImpl::update(float dt)
{
    ALint sourceState;
    int audioID;
    
    if (_threadMutex.try_lock()) {
        size_t removeAudioCount = _toRemoveAudioIDs.size();
        for (size_t index = 0; index < removeAudioCount; ++index) {
            audioID = _toRemoveAudioIDs[index];
            auto playerIt = _audioPlayers.find(audioID);
            if (playerIt != _audioPlayers.end()) {
                _alSourceUsed[playerIt->second._alSource] = false;
                if(playerIt->second._finishCallbak) {
                    auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                    playerIt->second._finishCallbak(audioID, *audioInfo.filePath);
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
    
    for (auto it = _audioPlayers.begin(); it != _audioPlayers.end(); ) {
        audioID = it->first;
        auto& player = it->second;
        alGetSourcei(player._alSource, AL_SOURCE_STATE, &sourceState);
        
        if (player._readForRemove)
        {
            it = _audioPlayers.erase(it);
        }
        else if (player._ready && sourceState == AL_STOPPED) {
            _alSourceUsed[player._alSource] = false;
            if (player._finishCallbak) {
                auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                player._finishCallbak(audioID, *audioInfo.filePath);
            }
            
            AudioEngine::remove(audioID);
            
            if (player._streamingSource)
            {
                player.notifyExitThread();
                ++it;
            } 
            else
            {
                it = _audioPlayers.erase(it);
            }
        }
        else{
            ++it;
        }
    }
    
    if(_audioPlayers.empty()){
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
