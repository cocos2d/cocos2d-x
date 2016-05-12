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
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#include "audio/include/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace cocos2d::experimental;

static float s_bgMusicVolume = 1.0f;
static float s_effectVolume = 1.0f;

namespace CocosDenshion {

SimpleAudioEngine::SimpleAudioEngine() {

}

SimpleAudioEngine::~SimpleAudioEngine() {
}

SimpleAudioEngine* SimpleAudioEngine::getInstance() {
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end() {
    AudioEngine::end();
}

static int s_bgAudioID = AudioEngine::INVALID_AUDIO_ID;
static std::string bgMusicFilePath;
//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,bool bLoop) {
    if (s_bgAudioID != AudioEngine::INVALID_AUDIO_ID)
    {
        AudioEngine::stop(s_bgAudioID);
        s_bgAudioID = AudioEngine::INVALID_AUDIO_ID;
    }

    if (pszFilePath)
    {
        bgMusicFilePath = pszFilePath;
        s_bgAudioID = AudioEngine::play2d(pszFilePath,bLoop,s_bgMusicVolume);
    }
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData) {
    AudioEngine::stop(s_bgAudioID);
}

void SimpleAudioEngine::pauseBackgroundMusic() {
    AudioEngine::pause(s_bgAudioID);
}

void SimpleAudioEngine::resumeBackgroundMusic() {
    AudioEngine::resume(s_bgAudioID);
}

void SimpleAudioEngine::rewindBackgroundMusic() {
    AudioEngine::stop(s_bgAudioID);
    if (!bgMusicFilePath.empty())
    {
        s_bgAudioID = AudioEngine::play2d(bgMusicFilePath);
    }
}

bool SimpleAudioEngine::willPlayBackgroundMusic() {
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying() {
    auto state = AudioEngine::getState(s_bgAudioID);
    if (state == AudioEngine::AudioState::PLAYING)
    {
        return true;
    }
    return false;
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath) {
    bgMusicFilePath = pszFilePath;
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
                                           float pitch, float pan, float gain) {
    return AudioEngine::play2d(pszFilePath,bLoop,s_effectVolume);
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
    AudioEngine::stop(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
    // FIXME: need implementation
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
    AudioEngine::uncache(pszFilePath);
}

void SimpleAudioEngine::pauseEffect(unsigned int uSoundId) {
    AudioEngine::pause(uSoundId);
}

void SimpleAudioEngine::pauseAllEffects() {
    bool resumeBGMusic = false;
    auto state = AudioEngine::getState(s_bgAudioID);
    if (state == AudioEngine::AudioState::PLAYING)
    {
        resumeBGMusic = true;
    }
    AudioEngine::pauseAll();
    if (resumeBGMusic)
    {
        AudioEngine::resume(s_bgAudioID);
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int uSoundId) {
    AudioEngine::resume(uSoundId);
}

void SimpleAudioEngine::resumeAllEffects() {
    bool pauseBGMusic = false;
    auto state = AudioEngine::getState(s_bgAudioID);
    if (state == AudioEngine::AudioState::PAUSED)
    {
        pauseBGMusic = true;
    }
    AudioEngine::resumeAll();
    if (pauseBGMusic)
    {
        AudioEngine::pause(s_bgAudioID);
    }
}

void SimpleAudioEngine::stopAllEffects() {
    //FIXME
    AudioEngine::stopAll();
}



//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume() {
    return s_bgMusicVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume) {
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if(volume < 0.0f)
    {
        volume = 0.0f;
    }
    s_bgMusicVolume = volume;
    AudioEngine::setVolume(s_bgAudioID, s_bgMusicVolume);
}

float SimpleAudioEngine::getEffectsVolume() {
    return s_effectVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume) {
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if(volume < 0.0f)
    {
        volume = 0.0f;
    }
    s_effectVolume = volume;
    //FIXME
}


} // end of namespace CocosDenshion

#endif
