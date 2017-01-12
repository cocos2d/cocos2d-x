#include <iostream>
#include <vector>

#include "../include/SimpleAudioEngine.h"
#include "../include/AudioEngine.h"
#include "cocos2d.h"

using namespace CocosDenshion;

extern "C" {
    // Methods implemented in SimpleAudioEngine.js
    void SimpleAudioEngine_init();
    
    void SimpleAudioEngine_rewindBackgroundMusic();
    void SimpleAudioEngine_preloadEffect(const char *);
    int SimpleAudioEngine_playEffect(const char *, int);
    void SimpleAudioEngine_stopEffect(int);
    void SimpleAudioEngine_setEffectsVolume(int);
    void SimpleAudioEngine_pauseEffect(int);
    void SimpleAudioEngine_resumeEffect(int);
    void SimpleAudioEngine_pauseAllEffects();
    void SimpleAudioEngine_resumeAllEffects();
    void SimpleAudioEngine_stopAllEffects();
    
    void SimpleAudioEngine_preloadBackgroundMusic(const char *);
    int SimpleAudioEngine_isBackgroundMusicPlaying();
    void SimpleAudioEngine_playBackgroundMusic(const char *, int);
    void SimpleAudioEngine_pauseBackgroundMusic();
    void SimpleAudioEngine_resumeBackgroundMusic();
    void SimpleAudioEngine_stopBackgroundMusic();
    void SimpleAudioEngine_setBackgroundMusicVolume(int);
    void SimpleAudioEngine_setUseFileExt(const char *);
    
    void SimpleAudioEngine_end();
};


float s_effectsVolume = 1.0;
float s_backgroundVolume = 1.0;
static SimpleAudioEngine * s_engine = nullptr;


SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if (!s_engine)
        s_engine = new SimpleAudioEngine();
    return s_engine;
}

void SimpleAudioEngine::end()
{
    SimpleAudioEngine_end();

    if(s_engine)
        delete s_engine;
    s_engine = nullptr;
}


SimpleAudioEngine::SimpleAudioEngine()
{
    SimpleAudioEngine_init();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* filePath)
{
    SimpleAudioEngine_preloadBackgroundMusic(filePath);
}

void SimpleAudioEngine::playBackgroundMusic(const char* filePath, bool loop)
{
    SimpleAudioEngine_playBackgroundMusic(filePath, loop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool releaseData)
{
    SimpleAudioEngine_stopBackgroundMusic();
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    SimpleAudioEngine_pauseBackgroundMusic();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    SimpleAudioEngine_resumeBackgroundMusic();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    SimpleAudioEngine_rewindBackgroundMusic();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return true;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return SimpleAudioEngine_isBackgroundMusicPlaying();
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
    return s_backgroundVolume;
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
    // Ensure volume is between 0.0 and 1.0.
    volume = volume > 1.0 ? 1.0 : volume;
    volume = volume < 0.0 ? 0.0 : volume;
    
    SimpleAudioEngine_setBackgroundMusicVolume((int) (volume * 100));
    s_backgroundVolume = volume;
}

/**
 * The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
 */
float SimpleAudioEngine::getEffectsVolume()
{
    return s_effectsVolume;
}

/**
* Set the volume of sound effects.
*
* @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
*/
void SimpleAudioEngine::setEffectsVolume(float volume)
{
    volume = volume > 1.0 ? 1.0 : volume;
    volume = volume < 0.0 ? 0.0 : volume;
    SimpleAudioEngine_setEffectsVolume((int) (volume * 100));
    s_effectsVolume = volume;
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
    return SimpleAudioEngine_playEffect(filePath, loop);
}

/**
* Pause playing sound effect.
*
* @param soundId The return value of function playEffect.
*/
void SimpleAudioEngine::pauseEffect(unsigned int soundId)
{
    SimpleAudioEngine_pauseEffect(soundId);
}

/**
* Pause all playing sound effect.
*/
void SimpleAudioEngine::pauseAllEffects()
{
    SimpleAudioEngine_pauseAllEffects();
}

/**
* Resume playing sound effect.
*
* @param soundId The return value of function playEffect.
*/
void SimpleAudioEngine::resumeEffect(unsigned int soundId)
{
    SimpleAudioEngine_resumeEffect(soundId);
}

/**
* Resume all playing sound effect.
*/
void SimpleAudioEngine::resumeAllEffects()
{
    SimpleAudioEngine_resumeAllEffects();
}

/**
* Stop playing sound effect.
*
* @param soundId The return value of function playEffect.
*/
void SimpleAudioEngine::stopEffect(unsigned int soundId)
{
    SimpleAudioEngine_stopEffect(soundId);
}
/**
* Stop all playing sound effects.
*/
void SimpleAudioEngine::stopAllEffects()
{
    SimpleAudioEngine_stopAllEffects();
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
    SimpleAudioEngine_preloadEffect(filePath);
}

/**
* Unload the preloaded effect from internal buffer.
*
* @param filePath The path of the effect file.
*/
void SimpleAudioEngine::unloadEffect(const char* filePath)
{
    // This doesn't make as much sense here. Just ignore.
}

void SimpleAudioEngine::setUseFileExt(const std::vector<std::string> &extFiles)
{
    std::string transferExts;
    for (int i = 0; i < extFiles.size(); ++i)
    {
        transferExts += extFiles[i];
        if (i + 1 < extFiles.size())
            transferExts += ",";
    }
    
    SimpleAudioEngine_setUseFileExt(transferExts.c_str());
}


    