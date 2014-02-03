/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "SimpleAudioEngine.h"

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "OpenALDecoder.h"

#ifdef ENABLE_MPG123
#include <mpg123.h>
#endif

USING_NS_CC;

using namespace std;

namespace CocosDenshion {

struct soundData {
    ALuint buffer;
    ALuint source;
    bool   isLooped;
    float pitch;
    float pan;
    float gain;
};

typedef map<string, soundData *> EffectsMap;
EffectsMap s_effects;

typedef enum {
    PLAYING,
    STOPPED,
    PAUSED,
} playStatus;

static float s_volume                  = 1.0f;
static float s_effectVolume            = 1.0f;

struct backgroundMusicData {
    ALuint buffer;
    ALuint source;
};

typedef map<string, backgroundMusicData *> BackgroundMusicsMap;
BackgroundMusicsMap s_backgroundMusics;

static ALuint s_backgroundSource = AL_NONE;

static SimpleAudioEngine  *s_engine = nullptr;

static int checkALError(const char *funcName)
{
    int err = alGetError();

    if (err != AL_NO_ERROR)
    {
        switch (err)
        {
            case AL_INVALID_NAME:
                fprintf(stderr, "AL_INVALID_NAME in %s\n", funcName);
                break;

            case AL_INVALID_ENUM:
                fprintf(stderr, "AL_INVALID_ENUM in %s\n", funcName);
                break;

            case AL_INVALID_VALUE:
                fprintf(stderr, "AL_INVALID_VALUE in %s\n", funcName);
                break;

            case AL_INVALID_OPERATION:
                fprintf(stderr, "AL_INVALID_OPERATION in %s\n", funcName);
                break;

            case AL_OUT_OF_MEMORY:
                fprintf(stderr, "AL_OUT_OF_MEMORY in %s\n", funcName);
                break;
        }
    }

    return err;
}

static void stopBackground(bool bReleaseData)
{
    // The background music might have been already stopped
    // Stop request can come from
    //   - stopBackgroundMusic(..)
    //   - end(..)
    if (s_backgroundSource != AL_NONE)
        alSourceStop(s_backgroundSource);

    if (bReleaseData)
    {
        for (auto it = s_backgroundMusics.begin(); it != s_backgroundMusics.end(); ++it)
        {
            if (it->second->source == s_backgroundSource)
            {
                alDeleteSources(1, &it->second->source);
                checkALError("stopBackground:alDeleteSources");
                alDeleteBuffers(1, &it->second->buffer);
                checkALError("stopBackground:alDeleteBuffers");
                delete it->second;
                s_backgroundMusics.erase(it);
                break;
            }
        }
    }

    s_backgroundSource = AL_NONE;
}

static void setBackgroundVolume(float volume)
{
    alSourcef(s_backgroundSource, AL_GAIN, volume);
}

SimpleAudioEngine::SimpleAudioEngine()
{
    alutInit(0, 0);
#ifdef ENABLE_MPG123
    mpg123_init();
#endif
    checkALError("SimpleAudioEngine:alutInit");
    OpenALDecoder::installDecoders();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
#ifdef ENABLE_MPG123
    mpg123_exit();
#endif
    alutExit();
}

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if (!s_engine)
        s_engine = new SimpleAudioEngine();

    return s_engine;
}

void SimpleAudioEngine::end()
{
    checkALError("end:init");

    // clear all the sound effects
    EffectsMap::const_iterator end = s_effects.end();
    for (auto it = s_effects.begin(); it != end; ++it)
    {
        alSourceStop(it->second->source);
        checkALError("end:alSourceStop");

        alDeleteSources(1, &it->second->source);
        checkALError("end:alDeleteSources");

        alDeleteBuffers(1, &it->second->buffer);
        checkALError("end:alDeleteBuffers");

        delete it->second;
    }
    s_effects.clear();

    // and the background music too
    stopBackground(true);

    for (auto it = s_backgroundMusics.begin(); it != s_backgroundMusics.end(); ++it)
    {
        alSourceStop(it->second->source);
        checkALError("end:alSourceStop");

        alDeleteSources(1, &it->second->source);
        checkALError("end:alDeleteSources");

        alDeleteBuffers(1, &it->second->buffer);
        checkALError("end:alDeleteBuffers");

        delete it->second;
    }
    s_backgroundMusics.clear();

    CC_SAFE_DELETE(s_engine);
}

//
// background audio
//
void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);

    BackgroundMusicsMap::const_iterator it = s_backgroundMusics.find(fullPath);
    if (it == s_backgroundMusics.end())
    {
        ALuint buffer = AL_NONE;
        bool success = false;
        OpenALFile file;
        file.debugName = pszFilePath;
        file.file = fopen(fullPath.c_str(), "rb");
        if (!file.file) {
            fprintf(stderr, "Cannot read file: '%s'\n", fullPath.data());
            return;
        }

        const std::vector<OpenALDecoder *> &decoders = OpenALDecoder::getDecoders();
        for (size_t i = 0, n = decoders.size(); !success && i < n; ++i)
            success = decoders[i]->decode(file, buffer);
        file.clear();

        ALuint source = AL_NONE;
        alGenSources(1, &source);
        checkALError("preloadBackgroundMusic:alGenSources");

        alSourcei(source, AL_BUFFER, buffer);
        checkALError("preloadBackgroundMusic:alSourcei");

        backgroundMusicData* data = new backgroundMusicData();
        data->buffer = buffer;
        data->source = source;
        s_backgroundMusics.insert(BackgroundMusicsMap::value_type(fullPath, data));
    }
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    // If there is already a background music source we stop it first
    if (s_backgroundSource != AL_NONE)
        stopBackgroundMusic(false);

    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);

    BackgroundMusicsMap::const_iterator it = s_backgroundMusics.find(fullPath);
    if (it == s_backgroundMusics.end())
    {
        preloadBackgroundMusic(fullPath.c_str());
        it = s_backgroundMusics.find(fullPath);
    }

    if (it != s_backgroundMusics.end())
    {
        s_backgroundSource = it->second->source;
        alSourcei(s_backgroundSource, AL_LOOPING, bLoop ? AL_TRUE : AL_FALSE);
        setBackgroundVolume(s_volume);
        alSourcePlay(s_backgroundSource);
        checkALError("playBackgroundMusic:alSourcePlay");
    }
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    // If there is no source, then there is nothing that can be stopped
    if (s_backgroundSource == AL_NONE)
        return;

    ALint state;
    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING)
        stopBackground(bReleaseData);
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    // If there is no source, then there is nothing that can be paused
    if (s_backgroundSource == AL_NONE)
        return;

    ALint state;
    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING)
        alSourcePause(s_backgroundSource);

    checkALError("pauseBackgroundMusic:alSourcePause");
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    // If there is no source, then there is nothing that can be resumed
    if (s_backgroundSource == AL_NONE)
        return;

    ALint state;
    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &state);
    if (state == AL_PAUSED)
        alSourcePlay(s_backgroundSource);

    checkALError("resumeBackgroundMusic:alSourcePlay");
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    // If there is no source, then there is nothing that can be rewinded
    if (s_backgroundSource == AL_NONE)
        return;

    // Rewind and prevent the last state the source had
    ALint state;
    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &state);
    alSourceRewind(s_backgroundSource);

    if (state == AL_PLAYING)
    {
        alSourcePlay(s_backgroundSource);
    }
    else if (state == AL_PAUSED)
    {
        alSourcePlay(s_backgroundSource);
        alSourcePause(s_backgroundSource);
    }
    checkALError("rewindBackgroundMusic:alSourceRewind");
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    // We are able to play background music
    // if we have a valid background source
    if (s_backgroundSource == AL_NONE)
        return false;

    return (alIsSource(s_backgroundSource) == AL_TRUE ? true : false);
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    // If there is no source, then there is nothing that is playing
    if (s_backgroundSource == AL_NONE)
        return false;

    ALint play_status;
    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &play_status);
    checkALError("isBackgroundMusicPlaying:alGetSourcei");

    return (play_status == AL_PLAYING);
}

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return s_volume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    if (s_volume != volume && volume >= -0.0001 && volume <= 1.0001)
    {
        s_volume = volume;

        // No source, no background music, no volume adjustment
        if (s_backgroundSource != AL_NONE)
        {
            setBackgroundVolume(volume);
        }
    }
}

//
// Effect audio (using OpenAL)
//
float SimpleAudioEngine::getEffectsVolume()
{
    return s_effectVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    if (volume != s_effectVolume)
    {
        EffectsMap::const_iterator end = s_effects.end();
        for (EffectsMap::const_iterator it = s_effects.begin(); it != end; it++)
        {
            alSourcef(it->second->source, AL_GAIN, volume * it->second->gain);
        }

        s_effectVolume = volume;
    }
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
                                           float pitch, float pan, float gain)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);

    EffectsMap::iterator iter = s_effects.find(fullPath);

    if (iter == s_effects.end())
    {
        preloadEffect(fullPath.c_str());

        // let's try again
        iter = s_effects.find(fullPath);
        if (iter == s_effects.end())
        {
            fprintf(stderr, "could not find play sound %s\n", fullPath.c_str());
            return -1;
        }
    }

    checkALError("playEffect:init");

    soundData &d = *iter->second;
    d.isLooped = bLoop;
    d.pitch = pitch;
    d.pan = pan;
    d.gain = gain;
    alSourcei(d.source, AL_LOOPING, d.isLooped ? AL_TRUE : AL_FALSE);
    alSourcef(d.source, AL_GAIN, s_effectVolume * d.gain);
    alSourcef(d.source, AL_PITCH, d.pitch);
    float sourcePosAL[] = {d.pan, 0.0f, 0.0f};//Set position - just using left and right panning
    alSourcefv(d.source, AL_POSITION, sourcePosAL);
    alSourcePlay(d.source);
    checkALError("playEffect:alSourcePlay");

    return d.source;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    alSourceStop(nSoundId);
    checkALError("stopEffect:alSourceStop");
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);

    EffectsMap::iterator iter = s_effects.find(fullPath);

    // check if we have this already
    if (iter == s_effects.end())
    {
        ALuint      buffer = AL_NONE;
        ALuint      source = AL_NONE;
        soundData  *data = new soundData;

        checkALError("preloadEffect:init");
        OpenALFile file;
        file.debugName = pszFilePath;
        file.file = fopen(fullPath.c_str(), "rb");
        if (!file.file) {
            fprintf(stderr, "Cannot read file: '%s'\n", fullPath.data());
            return;
        }

        bool success = false;
        const std::vector<OpenALDecoder *> &decoders = OpenALDecoder::getDecoders();
        for (size_t i = 0, n = decoders.size(); !success && i < n; ++i)
            success = decoders[i]->decode(file, buffer);
        file.clear();

        alGenSources(1, &source);

        if (checkALError("preloadEffect:alGenSources") != AL_NO_ERROR)
        {
            alDeleteBuffers(1, &buffer);
            return;
        }

        alSourcei(source, AL_BUFFER, buffer);
        checkALError("preloadEffect:alSourcei");

        data->isLooped = false;
        data->buffer = buffer;
        data->source = source;
        data->pitch = 1.0;
        data->pan = 0.0;
        data->gain = 1.0;

        s_effects.insert(EffectsMap::value_type(fullPath, data));
    }
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);

    EffectsMap::iterator iter = s_effects.find(fullPath);

    if (iter != s_effects.end())
    {
        checkALError("unloadEffect:init");

        alSourceStop(iter->second->source);
        checkALError("unloadEffect:alSourceStop");

        alDeleteSources(1, &iter->second->source);
        checkALError("unloadEffect:DeletSources");

        alDeleteBuffers(1, &iter->second->buffer);
        checkALError("unloadEffect:alDeleteBuffers");
        delete iter->second;

        s_effects.erase(iter);
    }
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    ALint state;
    alGetSourcei(nSoundId, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING)
        alSourcePause(nSoundId);
    checkALError("pauseEffect:alSourcePause");
}

void SimpleAudioEngine::pauseAllEffects()
{
    EffectsMap::iterator iter = s_effects.begin();
    ALint state;
    while (iter != s_effects.end())
    {
        alGetSourcei(iter->second->source, AL_SOURCE_STATE, &state);
        if (state == AL_PLAYING)
            alSourcePause(iter->second->source);
        checkALError("pauseAllEffects:alSourcePause");
        ++iter;
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    ALint state;
    alGetSourcei(nSoundId, AL_SOURCE_STATE, &state);
    if (state == AL_PAUSED)
        alSourcePlay(nSoundId);
    checkALError("resumeEffect:alSourcePlay");
}

void SimpleAudioEngine::resumeAllEffects()
{
    EffectsMap::iterator iter = s_effects.begin();
    ALint state;
    while (iter != s_effects.end())
    {
        alGetSourcei(iter->second->source, AL_SOURCE_STATE, &state);
        if (state == AL_PAUSED)
            alSourcePlay(iter->second->source);
        checkALError("resumeAllEffects:alSourcePlay");
        ++iter;
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    EffectsMap::iterator iter = s_effects.begin();

    if (iter != s_effects.end())
    {
        checkALError("stopAllEffects:init");
        alSourceStop(iter->second->source);
        checkALError("stopAllEffects:alSourceStop");
    }
}

} // namespace CocosDenshion {
