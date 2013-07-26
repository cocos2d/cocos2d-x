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

#include <QMap>
#include <QMediaPlayer>

USING_NS_CC;

namespace CocosDenshion {

static QString
fullPath(const char *filename)
{
    return QString::fromStdString(FileUtils::getInstance()->fullPathForFilename(filename));
}

class CocosQt5AudioBackend {
    public:
        static void cleanup();
        static void gcEffects();

        static QMediaPlayer *player() {
            if (background_music == NULL) {
                background_music = new QMediaPlayer;
            }

            return background_music;
        }

        static void setEffectsVolume(float volume)
        {
            effects_volume = volume;

            foreach (QMediaPlayer *effect, effects.values()) {
                effect->setVolume(volume * 100.0);
            }
        }

        static QMap<int,QMediaPlayer*> effects;
        static QMediaPlayer *background_music;
        static int next_effect_id;
        static float effects_volume;
};

QMap<int,QMediaPlayer*>
CocosQt5AudioBackend::effects;

QMediaPlayer *
CocosQt5AudioBackend::background_music = NULL;

int
CocosQt5AudioBackend::next_effect_id = 0;

float
CocosQt5AudioBackend::effects_volume = 1.0;

void
CocosQt5AudioBackend::cleanup()
{
    foreach (QMediaPlayer *effect, effects.values()) {
        delete effect;
    }

    if (background_music != NULL) {
        delete background_music;
        background_music = NULL;
    }
}

void
CocosQt5AudioBackend::gcEffects()
{
    foreach (int id, effects.keys()) {
        QMediaPlayer *effect = effects[id];
        if (effect->state() == QMediaPlayer::StoppedState) {
            delete effect;
            effects.remove(id);
        }
    }
}


/* Singleton object */
static SimpleAudioEngine *
simple_audio_engine = NULL;


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
    QString filename = fullPath(pszFilePath);
}
    
/**
@brief Play background music
@param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
@param bLoop Whether the background music loop or not
*/
void
SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    QString filename = fullPath(pszFilePath);

    CocosQt5AudioBackend::player()->setMedia(QUrl::fromLocalFile(filename));
    if (bLoop) {
        // TODO: Set QMediaPlayer to loop infinitely
    }
    CocosQt5AudioBackend::player()->play();
}

/**
@brief Stop playing background music
@param bReleaseData If release the background music data or not.As default value is false
*/
void
SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    CocosQt5AudioBackend::player()->stop();

    if (bReleaseData) {
        CocosQt5AudioBackend::player()->setMedia(QMediaContent());
    }
}

/**
@brief Pause playing background music
*/
void
SimpleAudioEngine::pauseBackgroundMusic()
{
    CocosQt5AudioBackend::player()->pause();
}

/**
@brief Resume playing background music
*/
void
SimpleAudioEngine::resumeBackgroundMusic()
{
    CocosQt5AudioBackend::player()->play();
}

/**
@brief Rewind playing background music
*/
void
SimpleAudioEngine::rewindBackgroundMusic()
{
    CocosQt5AudioBackend::player()->stop();
    CocosQt5AudioBackend::player()->setPosition(0);
    CocosQt5AudioBackend::player()->play();
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
    return (CocosQt5AudioBackend::player()->state() == QMediaPlayer::PlayingState);
}

/**
@brief The volume of the background music max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getBackgroundMusicVolume()
{
    return (float)(CocosQt5AudioBackend::player()->volume()) / 100.;
}

/**
@brief set the volume of background music
@param volume must be in 0.0~1.0
*/
void
SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    CocosQt5AudioBackend::player()->setVolume(100. * volume);
}

/**
@brief The volume of the effects max value is 1.0,the min value is 0.0
*/
float
SimpleAudioEngine::getEffectsVolume()
{
    return CocosQt5AudioBackend::effects_volume;
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
SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
        float pitch, float pan, float gain)
{
    // TODO: Handle pitch, pan and gain

    CocosQt5AudioBackend::gcEffects();

    QString filename = fullPath(pszFilePath);
    int id = CocosQt5AudioBackend::next_effect_id++;

    QMediaPlayer *effect = new QMediaPlayer;
    effect->setMedia(QUrl::fromLocalFile(filename));
    effect->setVolume(CocosQt5AudioBackend::effects_volume * 100.0);
    if (bLoop) {
        // TODO: Set QMediaPlayer to loop infinitely
    }
    effect->play();

    CocosQt5AudioBackend::effects[id] = effect;
    return id;
}

/**
@brief Pause playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    if (CocosQt5AudioBackend::effects.contains(nSoundId)) {
        QMediaPlayer *effect = CocosQt5AudioBackend::effects[nSoundId];
        effect->pause();
    }
}

/**
@brief Pause all playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::pauseAllEffects()
{
    foreach (QMediaPlayer *effect, CocosQt5AudioBackend::effects.values()) {
        effect->pause();
    }
}

/**
@brief Resume playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    if (CocosQt5AudioBackend::effects.contains(nSoundId)) {
        QMediaPlayer *effect = CocosQt5AudioBackend::effects[nSoundId];
        effect->play();
    }
}

/**
@brief Resume all playing sound effect
@param nSoundId The return value of function playEffect
*/
void
SimpleAudioEngine::resumeAllEffects()
{
    foreach (QMediaPlayer *effect, CocosQt5AudioBackend::effects.values()) {
        if (effect->state() == QMediaPlayer::PausedState) {
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
    if (CocosQt5AudioBackend::effects.contains(nSoundId)) {
        QMediaPlayer *effect = CocosQt5AudioBackend::effects[nSoundId];
        CocosQt5AudioBackend::effects.remove(nSoundId);
        delete effect;
    }
}

/**
@brief Stop all playing sound effects
*/
void
SimpleAudioEngine::stopAllEffects()
{
    foreach (QMediaPlayer *effect, CocosQt5AudioBackend::effects.values()) {
        delete effect;
    }
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
    QString filename = fullPath(pszFilePath);
}

/**
@brief          unload the preloaded effect from internal buffer
@param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
*/
void
SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    QString filename = fullPath(pszFilePath);
}

} /* end namespace CocosDenshion */
