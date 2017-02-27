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
    void SimpleAudioEngine_unloadEffect(const char *);
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
    void SimpleAudioEngine_stopBackgroundMusic(bool);
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
    SimpleAudioEngine_stopBackgroundMusic(releaseData);
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

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return s_backgroundVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    // Ensure volume is between 0.0 and 1.0.
    volume = volume > 1.0 ? 1.0 : volume;
    volume = volume < 0.0 ? 0.0 : volume;
    
    SimpleAudioEngine_setBackgroundMusicVolume((int) (volume * 100));
    s_backgroundVolume = volume;
}

float SimpleAudioEngine::getEffectsVolume()
{
    return s_effectsVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    volume = volume > 1.0 ? 1.0 : volume;
    volume = volume < 0.0 ? 0.0 : volume;
    SimpleAudioEngine_setEffectsVolume((int) (volume * 100));
    s_effectsVolume = volume;
}

unsigned int SimpleAudioEngine::playEffect(const char* filePath, bool loop, float pitch, float pan, float gain)
{
    if(!filePath || strlen(filePath) == 0)
        return 0;
    else
        return SimpleAudioEngine_playEffect(filePath, loop);
}

void SimpleAudioEngine::pauseEffect(unsigned int soundId)
{
    SimpleAudioEngine_pauseEffect(soundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    SimpleAudioEngine_pauseAllEffects();
}

void SimpleAudioEngine::resumeEffect(unsigned int soundId)
{
    SimpleAudioEngine_resumeEffect(soundId);
}

void SimpleAudioEngine::resumeAllEffects()
{
    SimpleAudioEngine_resumeAllEffects();
}

void SimpleAudioEngine::stopEffect(unsigned int soundId)
{
    SimpleAudioEngine_stopEffect(soundId);
}

void SimpleAudioEngine::stopAllEffects()
{
    SimpleAudioEngine_stopAllEffects();
}

void SimpleAudioEngine::preloadEffect(const char* filePath)
{
    SimpleAudioEngine_preloadEffect(filePath);
}

void SimpleAudioEngine::unloadEffect(const char* filePath)
{
    SimpleAudioEngine_unloadEffect(filePath);
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


    