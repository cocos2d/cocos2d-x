/**
 *
 * Cocos2D-X Qt 5 Platform
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/


#include "platform/CCCommon.h"
#include "SimpleAudioEngine.h"

#include <QGuiApplication>

namespace CocosDenshion {

/* Singleton object */
static SimpleAudioEngine *
simple_audio_engine = NULL;


/**
@brief Get the shared Engine object,it will new one when first time be called
*/
SimpleAudioEngine *
SimpleAudioEngine::sharedEngine()
{
    if (simple_audio_engine == NULL) {
        simple_audio_engine = new SimpleAudioEngine;
    }

    return simple_audio_engine;
}

/**
@brief Release the shared Engine object
@warning It must be called before the application exit, or a memroy leak will be casued.
*/
void
SimpleAudioEngine::end()
{
    if (simple_audio_engine != NULL) {
        delete simple_audio_engine;
        simple_audio_engine = NULL;
    }
}


SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

/**
 @brief Preload background music
 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
 */
void
SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
}
    
/**
@brief Play background music
@param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
@param bLoop Whether the background music loop or not
*/
void
SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
}

/**
@brief Stop playing background music
@param bReleaseData If release the background music data or not.As default value is false
*/
void
SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
}

/**
@brief Pause playing background music
*/
void
SimpleAudioEngine::pauseBackgroundMusic()
{
}

/**
@brief Resume playing background music
*/
void
SimpleAudioEngine::resumeBackgroundMusic()
{
}

/**
@brief Rewind playing background music
*/
void
SimpleAudioEngine::rewindBackgroundMusic()
{
}

bool
SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

/**
@brief Whether the background music is playing
@return If is playing return true,or return false
*/
bool
SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return false;
}

// properties
/**
@brief The volume of the background music max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getBackgroundMusicVolume()
{
    return 1.0;
}

/**
@brief set the volume of background music
@param volume must be in 0.0~1.0
*/
void
SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
}

/**
@brief The volume of the effects max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getEffectsVolume()
{
    return 1.0;
}

/**
@brief set the volume of sound effecs
@param volume must be in 0.0~1.0
*/
void
SimpleAudioEngine::setEffectsVolume(float volume)
{
}

// for sound effects
/**
@brief Play sound effect
@param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
@bLoop Whether to loop the effect playing, default value is false
*/
unsigned int
SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    return 0;
}

/**
@brief Pause playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
}

/**
@brief Pause all playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::pauseAllEffects()
{
}

/**
@brief Resume playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
}

/**
@brief Resume all playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeAllEffects()
{
}

/**
@brief Stop playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
}

/**
@brief Stop all playing sound effects
*/
void
SimpleAudioEngine::stopAllEffects()
{
}

/**
@brief          preload a compressed audio file
@details        the compressed audio will be decode to wave, then write into an 
internal buffer in SimpleAudioEngine
*/
void
SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
}

/**
@brief          unload the preloaded effect from internal buffer
@param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
*/
void
SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
}

} /* end namespace CocosDenshion */
