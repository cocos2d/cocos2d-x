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


#include "SimpleAudioEngine.h"

#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "CocosQt5Player.h"

#include <QMap>

USING_NS_CC;

namespace CocosDenshion {

class CocosQt5AudioBackend
{
public:
    static void cleanup();
    static void gcEffects();

    static CocosQt5Player *musicPlayer()
    {
        if (backgroundMusic.isNull())
            backgroundMusic.reset(new CocosQt5Player);
        return backgroundMusic.data();
    }

    static void setEffectsVolume(float volume)
    {
        effectsVolume = volume;
        foreach (const CocosQt5PlayerPtr &effect, effects.values())
            effect->setGlobalVolume(volume);
    }

    static QMap<int, CocosQt5PlayerPtr> effects;
    static CocosQt5PlayerPtr backgroundMusic;
    static int nextEffectId;
    static float effectsVolume;
};

QMap<int, CocosQt5PlayerPtr> CocosQt5AudioBackend::effects;

CocosQt5PlayerPtr CocosQt5AudioBackend::backgroundMusic;

int CocosQt5AudioBackend::nextEffectId = 0;

float CocosQt5AudioBackend::effectsVolume = 1.0;

void CocosQt5AudioBackend::cleanup()
{
    effects.clear();
    backgroundMusic.reset(NULL);
}

void CocosQt5AudioBackend::gcEffects()
{
    foreach (int id, effects.keys())
    {
        CocosQt5PlayerPtr effect = effects[id];
        if (effect->isStopped())
        {
            effects.remove(id);
        }
    }
}


/* Singleton object */
static SimpleAudioEngine *simple_audio_engine = NULL;


/**
@brief Get the shared Engine object,it will new one when first time be called
*/
SimpleAudioEngine *
SimpleAudioEngine::getInstance()
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
    // Free sound effects and stop background music
    CocosQt5AudioBackend::cleanup();
}

/**
 @brief Preload background music
 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
 */
void
SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    CC_UNUSED_PARAM(pszFilePath);
}
    
/**
@brief Play background music
@param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
@param bLoop Whether the background music loop or not
*/
void
SimpleAudioEngine::playBackgroundMusic(const char* filePath, bool loop)
{
    CocosQt5AudioBackend::musicPlayer()->setMedia(filePath, loop);
    CocosQt5AudioBackend::musicPlayer()->play();
}

/**
@brief Stop playing background music
@param bReleaseData If release the background music data or not.As default value is false
*/
void
SimpleAudioEngine::stopBackgroundMusic(bool releaseData)
{
    CocosQt5AudioBackend::musicPlayer()->stop(releaseData);
}

/**
@brief Pause playing background music
*/
void
SimpleAudioEngine::pauseBackgroundMusic()
{
    CocosQt5AudioBackend::musicPlayer()->pause();
}

/**
@brief Resume playing background music
*/
void
SimpleAudioEngine::resumeBackgroundMusic()
{
    CocosQt5AudioBackend::musicPlayer()->play();
}

/**
@brief Rewind playing background music
*/
void
SimpleAudioEngine::rewindBackgroundMusic()
{
    CocosQt5AudioBackend::musicPlayer()->rewind();
}

bool
SimpleAudioEngine::willPlayBackgroundMusic()
{
    return true;
}

/**
@brief Whether the background music is playing
@return If is playing return true,or return false
*/
bool
SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return CocosQt5AudioBackend::musicPlayer()->isPlaying();
}

/**
@brief The volume of the background music max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getBackgroundMusicVolume()
{
    return CocosQt5AudioBackend::musicPlayer()->getVolume();
}

/**
@brief set the volume of background music
@param volume must be in 0.0~1.0
*/
void
SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    CocosQt5AudioBackend::musicPlayer()->setGlobalVolume(100. * volume);
}

/**
@brief The volume of the effects max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getEffectsVolume()
{
    return CocosQt5AudioBackend::effectsVolume;
}

/**
@brief set the volume of sound effecs
@param volume must be in 0.0~1.0
*/
void
SimpleAudioEngine::setEffectsVolume(float volume)
{
    CocosQt5AudioBackend::setEffectsVolume(volume);
}

// for sound effects
/**
@brief Play sound effect
@param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
@bLoop Whether to loop the effect playing, default value is false
*/
unsigned int
SimpleAudioEngine::playEffect(const char* filePath, bool loop,
        float pitch, float pan, float gain)
{
    CocosQt5AudioBackend::gcEffects();

    int id = CocosQt5AudioBackend::nextEffectId++;

    CocosQt5PlayerPtr effect(new CocosQt5Player);
    effect->setMedia(filePath, loop);
    effect->setGlobalVolume(CocosQt5AudioBackend::effectsVolume);
    effect->setGain(gain);
    effect->setPitch(pitch);
    effect->setPan(pan);
    effect->play();

    CocosQt5AudioBackend::effects[id] = effect;
    return id;
}

/**
@brief Pause playing sound effect
@param nSoundId The return value of function playEffect
*/
void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    CocosQt5PlayerPtr effect = CocosQt5AudioBackend::effects.value(nSoundId);
    if (!effect.isNull())
        effect->pause();
}

/**
@brief Pause all playing sound effect
@param nSoundId The return value of function playEffect
*/
void SimpleAudioEngine::pauseAllEffects()
{
    foreach (const CocosQt5PlayerPtr &effect, CocosQt5AudioBackend::effects.values())
        effect->pause();
}

/**
@brief Resume playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    CocosQt5PlayerPtr effect = CocosQt5AudioBackend::effects.value(nSoundId);
    if (!effect.isNull())
        effect->play();
}

/**
@brief Resume all playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeAllEffects()
{
    foreach (const CocosQt5PlayerPtr &effect, CocosQt5AudioBackend::effects.values())
    {
        if (effect->isPaused())
        {
            effect->play();
        }
    }
}

/**
@brief Stop playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    CocosQt5PlayerPtr effect = CocosQt5AudioBackend::effects.value(nSoundId);
    if (!effect.isNull())
    {
        CocosQt5AudioBackend::effects.remove(nSoundId);
    }
}

/**
@brief Stop all playing sound effects
*/
void
SimpleAudioEngine::stopAllEffects()
{
    CocosQt5AudioBackend::effects.clear();
}

/**
@brief          preload a compressed audio file
@details        the compressed audio will be decode to wave, then write into an 
internal buffer in SimpleAudioEngine
*/
void
SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    CC_UNUSED_PARAM(pszFilePath);
}

/**
@brief          unload the preloaded effect from internal buffer
@param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
*/
void
SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    CC_UNUSED_PARAM(pszFilePath);
}

} /* end namespace CocosDenshion */
