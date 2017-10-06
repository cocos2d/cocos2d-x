/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#define  LOG_TAG    "cocosdenshion::android::AndroidJavaEngine"

#include "audio/android/jni/cddandroidAndroidJavaEngine.h"
#include <stdlib.h>

#include <sys/system_properties.h>
#include "audio/android/ccdandroidUtils.h"
#include "audio/android/utils/Utils.h"
#include "audio/include/AudioEngine.h"
#include "platform/android/jni/JniHelper.h"

// logging
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

// Java class
static const char* helperClassName = "org/cocos2dx/lib/Cocos2dxHelper";

using namespace cocos2d;
using namespace cocos2d::experimental;
using namespace CocosDenshion::android;

AndroidJavaEngine::AndroidJavaEngine()
    : _implementBaseOnAudioEngine(false)
    , _effectVolume(1.f)
{
    int sdkVer = getSDKVersion();
    if (sdkVer > 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d", "android SDK version:%d", sdkVer);
        if (sdkVer == 21)
        {
            _implementBaseOnAudioEngine = true;
        }
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d", "%s", "Fail to get android SDK version.");
    }
}

AndroidJavaEngine::~AndroidJavaEngine()
{
    if (_implementBaseOnAudioEngine)
    {
        stopAllEffects();
    }

    JniHelper::callStaticMethod<void>(helperClassName, "end");
}

void AndroidJavaEngine::preloadBackgroundMusic(const char* filePath) {
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);
    JniHelper::callStaticMethod<void>(helperClassName, "preloadBackgroundMusic", fullPath);
}

void AndroidJavaEngine::playBackgroundMusic(const char* filePath, bool loop) {
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);
    JniHelper::callStaticMethod<void>(helperClassName, "playBackgroundMusic", fullPath, loop);
}

void AndroidJavaEngine::stopBackgroundMusic(bool releaseData) {
    JniHelper::callStaticMethod<void>(helperClassName, "stopBackgroundMusic");
}

void AndroidJavaEngine::pauseBackgroundMusic() {
    JniHelper::callStaticMethod<void>(helperClassName, "pauseBackgroundMusic");

}

void AndroidJavaEngine::resumeBackgroundMusic() {
    JniHelper::callStaticMethod<void>(helperClassName, "resumeBackgroundMusic");
}

void AndroidJavaEngine::rewindBackgroundMusic() {
    JniHelper::callStaticMethod<void>(helperClassName, "rewindBackgroundMusic");
}

bool AndroidJavaEngine::willPlayBackgroundMusic() {
    return JniHelper::callStaticMethod<bool>(helperClassName, "willPlayBackgroundMusic");
}

bool AndroidJavaEngine::isBackgroundMusicPlaying() {
    return JniHelper::callStaticMethod<bool>(helperClassName, "isBackgroundMusicPlaying");
}

float AndroidJavaEngine::getBackgroundMusicVolume() {
    return JniHelper::callStaticMethod<float>(helperClassName, "getBackgroundMusicVolume");
}

void AndroidJavaEngine::setBackgroundMusicVolume(float volume) {
    JniHelper::callStaticMethod<void>(helperClassName, "setBackgroundMusicVolume", volume);
}

float AndroidJavaEngine::getEffectsVolume()
{
    if (_implementBaseOnAudioEngine)
    {
        return _effectVolume;
    }
    else
    {
        return JniHelper::callStaticMethod<float>(helperClassName, "getEffectsVolume");
    }
}

void AndroidJavaEngine::setEffectsVolume(float volume)
{
    if (_implementBaseOnAudioEngine)
    {
        if (volume > 1.f)
        {
            volume = 1.f;
        }
        else if (volume < 0.f)
        {
            volume = 0.f;
        }

        if (_effectVolume != volume)
        {
            _effectVolume = volume;
            for (auto it : _soundIDs)
            {
                AudioEngine::setVolume(it, volume);
            }
        }
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "setEffectsVolume", volume);
    }
}

unsigned int AndroidJavaEngine::playEffect(const char* filePath, bool loop,
    float pitch, float pan, float gain)
{
    if (_implementBaseOnAudioEngine)
    {
        auto soundID = AudioEngine::play2d(filePath, loop, _effectVolume);
        if (soundID != AudioEngine::INVALID_AUDIO_ID)
        {
            _soundIDs.push_back(soundID);

            AudioEngine::setFinishCallback(soundID, [this](int id, const std::string& filePath){
                _soundIDs.remove(id);
            });
        }

        return soundID;
    }
    else
    {
        std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);
        int ret = JniHelper::callStaticMethod<int>(helperClassName, "playEffect", fullPath, loop, pitch, pan, gain);
        return (unsigned int)ret;
    }
}

void AndroidJavaEngine::pauseEffect(unsigned int soundID)
{
    if (_implementBaseOnAudioEngine)
    {
        AudioEngine::pause(soundID);
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "pauseEffect", (int)soundID);
    }
}

void AndroidJavaEngine::resumeEffect(unsigned int soundID)
{
    if (_implementBaseOnAudioEngine)
    {
        AudioEngine::resume(soundID);
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "resumeEffect", (int)soundID);
    }
}

void AndroidJavaEngine::stopEffect(unsigned int soundID)
{
    if (_implementBaseOnAudioEngine)
    {
        AudioEngine::stop(soundID);
        _soundIDs.remove(soundID);
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "stopEffect", (int)soundID);
    }
}

void AndroidJavaEngine::pauseAllEffects()
{
    if (_implementBaseOnAudioEngine)
    {
        for (auto it : _soundIDs)
        {
            AudioEngine::pause(it);
        }
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "pauseAllEffects");
    }
}

void AndroidJavaEngine::resumeAllEffects()
{
    if (_implementBaseOnAudioEngine)
    {
        for (auto it : _soundIDs)
        {
            AudioEngine::resume(it);
        }
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "resumeAllEffects");
    }
}

void AndroidJavaEngine::stopAllEffects()
{
    if (_implementBaseOnAudioEngine)
    {
        for (auto it : _soundIDs)
        {
            AudioEngine::stop(it);
        }
        _soundIDs.clear();
    }
    else
    {
        JniHelper::callStaticMethod<void>(helperClassName, "stopAllEffects");
    }
}

void AndroidJavaEngine::preloadEffect(const char* filePath)
{
    if (!_implementBaseOnAudioEngine)
    {
        std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);
        JniHelper::callStaticMethod<void>(helperClassName, "preloadEffect", fullPath);
    }
    else
    {
        AudioEngine::preload(filePath);
    }
}

void AndroidJavaEngine::unloadEffect(const char* filePath)
{
    if (!_implementBaseOnAudioEngine)
    {
        std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);
        JniHelper::callStaticMethod<void>(helperClassName, "unloadEffect", fullPath);
    }
    else
    {
        AudioEngine::uncache(filePath);
    }
}
