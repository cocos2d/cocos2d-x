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
#include <iostream>

#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

struct SimpleAudioEngineDelegate {
    SimpleAudioEngine * engine = nullptr;
    int musicid;
    float effectsvolume;
    std::string musicpath;
};

SimpleAudioEngineDelegate * g_SimpleAudioEngine = nullptr;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if (!g_SimpleAudioEngine) {
        g_SimpleAudioEngine = new SimpleAudioEngineDelegate();
        g_SimpleAudioEngine->engine = new SimpleAudioEngine();
    }
    return g_SimpleAudioEngine->engine;
}

void SimpleAudioEngine::end()
{
    if (g_SimpleAudioEngine) {
        delete g_SimpleAudioEngine->engine;
        delete g_SimpleAudioEngine;
    }
    g_SimpleAudioEngine = nullptr;
}

SimpleAudioEngine::SimpleAudioEngine()
{
    g_SimpleAudioEngine->musicid = -1;
    g_SimpleAudioEngine->effectsvolume = 1.0f;
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* filePath)
{
    g_SimpleAudioEngine->musicpath = filePath;
    AudioEngine::preload(filePath);
}

void SimpleAudioEngine::playBackgroundMusic(const char* filePath, bool loop)
{
    g_SimpleAudioEngine->musicpath = filePath;
    g_SimpleAudioEngine->musicid = AudioEngine::play2d(filePath, loop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool releaseData)
{
    AudioEngine::stop(g_SimpleAudioEngine->musicid);
    if (releaseData) {
        AudioEngine::uncache(g_SimpleAudioEngine->musicpath.c_str());
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    AudioEngine::pause(g_SimpleAudioEngine->musicid);
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    AudioEngine::resume(g_SimpleAudioEngine->musicid);
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    AudioEngine::setCurrentTime(g_SimpleAudioEngine->musicid, 0);
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return g_SimpleAudioEngine->musicid != -1;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return AudioEngine::getState(g_SimpleAudioEngine->musicid) == AudioEngine::AudioState::PLAYING;
}

//
// properties
//

/**
 * The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.
 * @js getMusicVolume
 * @lua getMusicVolume
 */
float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return AudioEngine::getVolume(g_SimpleAudioEngine->musicid);
}

/**
 * Set the volume of background music.
 *
 * @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
 * @js setMusicVolume
 * @lua setMusicVolume
 */
void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    AudioEngine::setVolume(g_SimpleAudioEngine->musicid, volume);
}

/**
 * The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
 */
float SimpleAudioEngine::getEffectsVolume()
{
    return g_SimpleAudioEngine->effectsvolume;
}

/**
 * Set the volume of sound effects.
 *
 * @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
 */
void SimpleAudioEngine::setEffectsVolume(float volume)
{
    g_SimpleAudioEngine->effectsvolume = volume;
}

/**
 * Play sound effect with a file path, pitch, pan and gain.
 *
 * @param filePath The path of the effect file.
 * @param loop Determines whether to loop the effect playing or not. The default value is false.
 * @param pitch Frequency, normal value is 1.0. Will also change effect play time.
 * @param pan   Stereo effect, in the range of [-1..1] where -1 enables only left channel.
 * @param gain  Volume, in the range of [0..1]. The normal value is 1.
 * @return The sound id.
 *
 * @note Full support is under development, now there are limitations:
 *     - no pitch effect on Samsung Galaxy S2 with OpenSL backend enabled;
 *     - no pitch/pan/gain on win32.
 */
unsigned int SimpleAudioEngine::playEffect(const char* filePath, bool loop, float pitch, float pan, float gain)
{
    return AudioEngine::play2d(filePath, loop, g_SimpleAudioEngine->effectsvolume);
}

/**
 * Pause playing sound effect.
 *
 * @param soundId The return value of function playEffect.
 */
void SimpleAudioEngine::pauseEffect(unsigned int soundId)
{
    AudioEngine::pause(soundId);
}

/**
 * Pause all playing sound effect.
 */
void SimpleAudioEngine::pauseAllEffects()
{
    AudioEngine::pauseAll();
}

/**
 * Resume playing sound effect.
 *
 * @param soundId The return value of function playEffect.
 */
void SimpleAudioEngine::resumeEffect(unsigned int soundId)
{
    AudioEngine::resume(soundId);
}

/**
 * Resume all playing sound effect.
 */
void SimpleAudioEngine::resumeAllEffects()
{
    AudioEngine::resumeAll();
}

/**
 * Stop playing sound effect.
 *
 * @param soundId The return value of function playEffect.
 */
void SimpleAudioEngine::stopEffect(unsigned int soundId)
{
    AudioEngine::stop(soundId);
}

/**
 * Stop all playing sound effects.
 */
void SimpleAudioEngine::stopAllEffects()
{
    AudioEngine::stopAll();
}

/**
 * Preload a compressed audio file.
 *
 * The compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine.
 *
 * @param filePath The path of the effect file.
 * @js NA
 */
void SimpleAudioEngine::preloadEffect(const char* filePath)
{
    AudioEngine::preload(filePath);
}

/**
 * Unload the preloaded effect from internal buffer.
 *
 * @param filePath The path of the effect file.
 */
void SimpleAudioEngine::unloadEffect(const char* filePath)
{
    AudioEngine::uncache(filePath);
}
