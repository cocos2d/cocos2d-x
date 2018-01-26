#include <iostream>

#include "audio/include/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace cocos2d::experimental;

struct SimpleAudioEngineLinux {
    SimpleAudioEngine * engine = nullptr;
    int musicid;
    float effectsvolume;
    std::string musicpath;
};

SimpleAudioEngineLinux * g_SimpleAudioEngineLinux = nullptr;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if (!g_SimpleAudioEngineLinux) {
        g_SimpleAudioEngineLinux = new SimpleAudioEngineLinux();
        g_SimpleAudioEngineLinux->engine = new SimpleAudioEngine();
    }
    return g_SimpleAudioEngineLinux->engine;
}

void SimpleAudioEngine::end()
{
    if (g_SimpleAudioEngineLinux) {
        delete g_SimpleAudioEngineLinux->engine;
        delete g_SimpleAudioEngineLinux;
    }
    g_SimpleAudioEngineLinux = nullptr;
}

SimpleAudioEngine::SimpleAudioEngine()
{
    g_SimpleAudioEngineLinux->musicid = -1;
    g_SimpleAudioEngineLinux->effectsvolume = 1.0f;
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* filePath)
{
    g_SimpleAudioEngineLinux->musicpath = filePath;
    AudioEngine::preload(filePath);
}

void SimpleAudioEngine::playBackgroundMusic(const char* filePath, bool loop)
{
    g_SimpleAudioEngineLinux->musicpath = filePath;
    g_SimpleAudioEngineLinux->musicid = AudioEngine::play2d(filePath, loop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool releaseData)
{
    AudioEngine::stop(g_SimpleAudioEngineLinux->musicid);
    if (releaseData) {
        AudioEngine::uncache(g_SimpleAudioEngineLinux->musicpath.c_str());
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    AudioEngine::pause(g_SimpleAudioEngineLinux->musicid);
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    AudioEngine::resume(g_SimpleAudioEngineLinux->musicid);
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    AudioEngine::setCurrentTime(g_SimpleAudioEngineLinux->musicid, 0);
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return g_SimpleAudioEngineLinux->musicid != -1;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return AudioEngine::getState(g_SimpleAudioEngineLinux->musicid) == AudioEngine::AudioState::PLAYING;
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
    return AudioEngine::getVolume(g_SimpleAudioEngineLinux->musicid);
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
    AudioEngine::setVolume(g_SimpleAudioEngineLinux->musicid, volume);
}

/**
 * The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
 */
float SimpleAudioEngine::getEffectsVolume()
{
    return g_SimpleAudioEngineLinux->effectsvolume;
}

/**
 * Set the volume of sound effects.
 *
 * @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
 */
void SimpleAudioEngine::setEffectsVolume(float volume)
{
    g_SimpleAudioEngineLinux->effectsvolume = volume;
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
    return AudioEngine::play2d(filePath, loop, gain);
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
