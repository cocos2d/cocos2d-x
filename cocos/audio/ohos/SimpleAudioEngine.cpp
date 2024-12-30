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

#include <string>
#include "../include/SimpleAudioEngine.h"
#include "platform/ohos/CCFileUtils-ohos.h"
#include "audio/include/AudioEngine.h"
#include "cutils/log.h"

using namespace cocos2d::experimental;

namespace CocosDenshion {

    static  int _lastBackGroundAudioID = -1;
    static  char* _lastBackGroundFilename;
    static  int _lastEffectAudioID;
    static  char* _lastEffectFilename;
    static bool useJsFunc = false;
    static float effectsvolume = 1.0;

    static std::string getFullPathWithoutAssetsPrefix(const char* pszFilename) {
        std::string fullPath = cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename(pszFilename);
        size_t pos = fullPath.find("hap:/");
        if (pos == 0)
        {
            fullPath = fullPath.substr(strlen("hap:/"));
        }
        return fullPath;
    }


    static SimpleAudioEngine *s_pEngine = 0;

    SimpleAudioEngine* SimpleAudioEngine::getInstance() {
    if (! s_pEngine) {
        s_pEngine = new SimpleAudioEngine();
    }
    
        return s_pEngine;
    }

    void SimpleAudioEngine::end() {
        cocos2d::experimental::AudioEngine::end();
    }

    SimpleAudioEngine::SimpleAudioEngine() {
    }

    SimpleAudioEngine::~SimpleAudioEngine() {
    }

    // Empty implementations. On Android, only subclasses are meant to be used
    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath) {
        ALOGD("preloadBackgroundMusic start!");
        std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    
    }

    void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
        ALOGD("playBackgroundMusic: %s", pszFilePath);
        std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
        _lastBackGroundAudioID = cocos2d::experimental::AudioEngine::play2d(uri, bLoop, 0.5);
        ALOGD("playBackgroundMusic  %s  end, and id:%d", uri.c_str(), _lastBackGroundAudioID);
    }

    void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData) {
        ALOGD("stopBackgroundMusic");
        cocos2d::experimental::AudioEngine::stop(_lastBackGroundAudioID);
        ALOGD("stopBackgroundMusic end, and id:%d", _lastBackGroundAudioID);
    }

    void SimpleAudioEngine::pauseBackgroundMusic() {
        ALOGD("pauseBackgroundMusic");
        cocos2d::experimental::AudioEngine::pause(_lastBackGroundAudioID);
    }

    void SimpleAudioEngine::resumeBackgroundMusic() {
        ALOGD("resumeBackgroundMusic start!");
        cocos2d::experimental::AudioEngine::resume(_lastBackGroundAudioID);
    }

    void SimpleAudioEngine::rewindBackgroundMusic() {
        ALOGD("rewindBackgroundMusic");
        cocos2d::experimental::AudioEngine::setCurrentTime(_lastBackGroundAudioID, 0);
    }

    bool SimpleAudioEngine::willPlayBackgroundMusic() {
        return _lastBackGroundAudioID != -1;
    }

    bool SimpleAudioEngine::isBackgroundMusicPlaying() {
        return cocos2d::experimental::AudioEngine::getState(_lastBackGroundAudioID) == cocos2d::experimental::AudioEngine::AudioState::PLAYING;
    }

    float SimpleAudioEngine::getBackgroundMusicVolume() {
        return AudioEngine::getVolume(_lastBackGroundAudioID);
    }

    void SimpleAudioEngine::setBackgroundMusicVolume(float volume) {
        AudioEngine::setVolume(_lastBackGroundAudioID, volume);
    }

    float SimpleAudioEngine::getEffectsVolume() {
        return effectsvolume;
    }

    void SimpleAudioEngine::setEffectsVolume(float volume) {
        effectsvolume = volume;
    }

    unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain) {
        std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
        ALOGD("playEffect start! and uri:%s", uri.data());
        return  AudioEngine::play2d(uri, bLoop);
    }

    void SimpleAudioEngine::pauseEffect(unsigned int nSoundId) {
        AudioEngine::stop(nSoundId);
    }

    void SimpleAudioEngine::pauseAllEffects() {
        AudioEngine::pauseAll();
    }

    void SimpleAudioEngine::resumeEffect(unsigned int nSoundId) {
        cocos2d::experimental::AudioEngine::resume(nSoundId);
    }

    void SimpleAudioEngine::resumeAllEffects() {
        cocos2d::experimental::AudioEngine::resumeAll();
    }

    void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
        AudioEngine::stop(nSoundId);
    }

    void SimpleAudioEngine::stopAllEffects() {
        cocos2d::experimental::AudioEngine::stopAll();
    }

    void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
        std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
        AudioEngine::preload(uri);
    }

    void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
        std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
        AudioEngine::uncache(uri);
    }
}
