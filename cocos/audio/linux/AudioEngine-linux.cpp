/****************************************************************************
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

/**
 * @author cesarpachon
 */
#include <cstring>
#include <cstdint>
#include "audio/linux/AudioEngine-linux.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"

using namespace cocos2d;

AudioEngineImpl * g_AudioEngineImpl = nullptr;

void ERRCHECKWITHEXIT(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    }
}

bool ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return true;
    }
    return false;
}

FMOD_RESULT F_CALLBACK channelCallback(FMOD_CHANNELCONTROL *channelcontrol,
                                       FMOD_CHANNELCONTROL_TYPE controltype,
                                       FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
                                       void *commandData1, void *commandData2)
{
    if (controltype == FMOD_CHANNELCONTROL_CHANNEL && callbacktype == FMOD_CHANNELCONTROL_CALLBACK_END) {
        g_AudioEngineImpl->onSoundFinished((FMOD::Channel *)channelcontrol);
    }
    return FMOD_OK;
}

AudioEngineImpl::AudioEngineImpl()
{
}

AudioEngineImpl::~AudioEngineImpl()
{
    FMOD_RESULT result;
    result = pSystem->release();
    ERRCHECKWITHEXIT(result);
}

bool AudioEngineImpl::init()
{
    FMOD_RESULT result;
    /*
    Create a System object and initialize.
    */
    result = FMOD::System_Create(&pSystem);
    ERRCHECKWITHEXIT(result);

    result = pSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
    ERRCHECKWITHEXIT(result);

    result = pSystem->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECKWITHEXIT(result);

    mapChannelInfo.clear();
    mapSound.clear();

    auto scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(CC_SCHEDULE_SELECTOR(AudioEngineImpl::update), this, 0.05f, false);

    g_AudioEngineImpl = this;

    return true;
}

int AudioEngineImpl::play2d(const std::string &fileFullPath, bool loop, float volume)
{
    int id = preload(fileFullPath, nullptr);
    if (id >= 0) {
        mapChannelInfo[id].loop=loop;
        // channel is null here. Don't dereference it. It's only set in resume(id).
        //mapChannelInfo[id].channel->setPaused(true);
        mapChannelInfo[id].volume = volume;
        AudioEngine::_audioIDInfoMap[id].state = AudioEngine::AudioState::PAUSED;
        resume(id);
    }
    return id;
}

void AudioEngineImpl::setVolume(int audioID, float volume)
{
    try {
        mapChannelInfo[audioID].channel->setVolume(volume);
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setVolume: invalid audioID: %d\n", audioID);
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    try {
        mapChannelInfo[audioID].channel->setLoopCount(loop ? -1 : 0);
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setLoop: invalid audioID: %d\n", audioID);
    }
}

bool AudioEngineImpl::pause(int audioID)
{
    try {
        mapChannelInfo[audioID].channel->setPaused(true);
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PAUSED;
        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::pause: invalid audioID: %d\n", audioID);
        return false;
    }
}

bool AudioEngineImpl::resume(int audioID)
{
    try {
        if (!mapChannelInfo[audioID].channel) {
            FMOD::Channel *channel = nullptr;
            FMOD::ChannelGroup *channelgroup = nullptr;
            //starts the sound in pause mode, use the channel to unpause
            FMOD_RESULT result = pSystem->playSound(mapChannelInfo[audioID].sound, channelgroup, true, &channel);
            if (ERRCHECK(result)) {
                return false;
            }
            channel->setMode(mapChannelInfo[audioID].loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
            channel->setLoopCount(mapChannelInfo[audioID].loop ? -1 : 0);
            channel->setVolume(mapChannelInfo[audioID].volume);
            channel->setUserData(reinterpret_cast<void *>(static_cast<std::intptr_t>(mapChannelInfo[audioID].id)));
            mapChannelInfo[audioID].channel = channel;
        }

        mapChannelInfo[audioID].channel->setPaused(false);
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;

        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::resume: invalid audioID: %d\n", audioID);
        return false;
    }
}

bool AudioEngineImpl::stop(int audioID)
{
    try {
        mapChannelInfo[audioID].channel->stop();
        mapChannelInfo[audioID].channel = nullptr;
        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::stop: invalid audioID: %d\n", audioID);
        return false;
    }
}

void AudioEngineImpl::stopAll()
{
    for (auto& it : mapChannelInfo) {
        ChannelInfo & audioRef = it.second;
        audioRef.channel->stop();
        audioRef.channel = nullptr;
    }
}

float AudioEngineImpl::getDuration(int audioID)
{
    try {
        FMOD::Sound * sound = mapChannelInfo[audioID].sound;
        unsigned int length;
        FMOD_RESULT result = sound->getLength(&length, FMOD_TIMEUNIT_MS);
        ERRCHECK(result);
        float duration = (float)length / 1000.0f;
        return duration;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::getDuration: invalid audioID: %d\n", audioID);
        return AudioEngine::TIME_UNKNOWN;
    }
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    try {
        unsigned int position;
        FMOD_RESULT result = mapChannelInfo[audioID].channel->getPosition(&position, FMOD_TIMEUNIT_MS);
        ERRCHECK(result);
        float currenttime = position /1000.0f;
        return currenttime;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::getCurrentTime: invalid audioID: %d\n", audioID);
        return AudioEngine::TIME_UNKNOWN;
    }
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    bool ret = false;
    try {
        unsigned int position = (unsigned int)(time * 1000.0f);
        FMOD_RESULT result = mapChannelInfo[audioID].channel->setPosition(position, FMOD_TIMEUNIT_MS);
        ret = !ERRCHECK(result);
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setCurrentTime: invalid audioID: %d\n", audioID);
    }
    return ret;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    try {
        FMOD::Channel * channel = mapChannelInfo[audioID].channel;
        mapChannelInfo[audioID].callback = callback;
        FMOD_RESULT result = channel->setCallback(channelCallback);
        ERRCHECK(result);
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setFinishCallback: invalid audioID: %d\n", audioID);
    }
}

void AudioEngineImpl::onSoundFinished(FMOD::Channel * channel)
{
    int id = 0;
    try {
        void * data;
        channel->getUserData(&data);
        id = static_cast<int>(reinterpret_cast<std::intptr_t>(data));
        if (mapChannelInfo[id].callback) {
            mapChannelInfo[id].callback(id, mapChannelInfo[id].path);
        }
        mapChannelInfo[id].channel = nullptr;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::onSoundFinished: invalid audioID: %d\n", id);
    }
}

void AudioEngineImpl::uncache(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::map<std::string, FMOD::Sound *>::const_iterator it = mapSound.find(fullPath);
    if (it!=mapSound.end()) {
        FMOD::Sound * sound = it->second;
        if (sound) {
            sound->release();
        }
        mapSound.erase(it);
    }
    mapId.erase(path);
}

void AudioEngineImpl::uncacheAll()
{
    for (const auto& it : mapSound) {
        auto sound = it.second;
        if (sound) {
            sound->release();
        }
    }
    mapSound.clear();
    mapId.clear();
}

int AudioEngineImpl::preload(const std::string& filePath, std::function<void(bool isSuccess)> callback)
{
    FMOD::Sound * sound = findSound(filePath);
    if (!sound) {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        FMOD_RESULT result = pSystem->createSound(fullPath.c_str(), FMOD_LOOP_OFF, 0, &sound);
        if (ERRCHECK(result)) {
            printf("sound effect in %s could not be preload\n", filePath.c_str());
            if (callback) {
                callback(false);
            }
            return -1;
        }
        mapSound[fullPath] = sound;
    }

    int id = static_cast<int>(mapChannelInfo.size()) + 1;
    // std::map::insert returns std::pair<iter, bool>
    auto channelInfoIter = mapId.insert({filePath, id});
    id = channelInfoIter.first->second;

    auto& chanelInfo = mapChannelInfo[id];
    chanelInfo.sound = sound;
    chanelInfo.id = id;
    chanelInfo.channel = nullptr;
    chanelInfo.callback = nullptr;
    chanelInfo.path = filePath;
    //we are going to use UserData to store pointer to Channel when playing
    chanelInfo.sound->setUserData(reinterpret_cast<void *>(static_cast<std::intptr_t>(id)));

    if (callback) {
        callback(true);
    }
    return id;
}

void AudioEngineImpl::update(float dt)
{
    pSystem->update();
}

FMOD::Sound * AudioEngineImpl::findSound(const std::string &path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::map<std::string, FMOD::Sound *>::const_iterator it = mapSound.find(fullPath);
    return (it != mapSound.end()) ? (it->second) : nullptr;
}

FMOD::Channel * AudioEngineImpl::getChannel(FMOD::Sound *sound)
{
    void * data;
    sound->getUserData(&data);
    int id = static_cast<int>(reinterpret_cast<std::intptr_t>(data));
    return mapChannelInfo[id].channel;
}
