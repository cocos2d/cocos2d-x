/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#include "cddandroidAndroidJavaEngine.h"
#include <stdlib.h>
#include <android/log.h>
#include <jni.h>
#include <sys/system_properties.h>
#include "platform/android/jni/JniHelper.h"
#include "ccdandroidUtils.h"
#include "audio/include/AudioEngine.h"

// logging
#define  LOG_TAG    "cocosdenshion::android::AndroidJavaEngine"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

// Java class
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

using namespace cocos2d::experimental;
using namespace CocosDenshion::android;

static inline bool getJNIStaticMethodInfo(cocos2d::JniMethodInfo &methodinfo,
    const char *methodName,
    const char *paramCode) {
    return cocos2d::JniHelper::getStaticMethodInfo(methodinfo,
        CLASS_NAME,
        methodName,
        paramCode);
}

AndroidJavaEngine::AndroidJavaEngine()
    : _implementBaseOnAudioEngine(false)
    , _effectVolume(1.f)
{
    char sdk_ver_str[PROP_VALUE_MAX] = "0";
    auto len = __system_property_get("ro.build.version.sdk", sdk_ver_str);
    if (len > 0)
    {
        auto sdk_ver = atoi(sdk_ver_str);
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d", "android build version:%d", sdk_ver);
        if (sdk_ver == 21)
        {
            _implementBaseOnAudioEngine = true;
        }
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d", "%s", "Fail to get android build version.");
    }
}

AndroidJavaEngine::~AndroidJavaEngine()
{
    if (_implementBaseOnAudioEngine)
    {
        stopAllEffects();
    }
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "end", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::preloadBackgroundMusic(const char* filePath) {
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);

    // void playBackgroundMusic(String,boolean)
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "preloadBackgroundMusic", "(Ljava/lang/String;)V")) {
        return;
    }

    jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::playBackgroundMusic(const char* filePath, bool loop) {
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);

    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "playBackgroundMusic", "(Ljava/lang/String;Z)V")) {
        return;
    }

    jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, loop);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::stopBackgroundMusic(bool releaseData) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "stopBackgroundMusic", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::pauseBackgroundMusic() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "pauseBackgroundMusic", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::resumeBackgroundMusic() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "resumeBackgroundMusic", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::rewindBackgroundMusic() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "rewindBackgroundMusic", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

bool AndroidJavaEngine::willPlayBackgroundMusic() {
    return true;
}

bool AndroidJavaEngine::isBackgroundMusicPlaying() {
    cocos2d::JniMethodInfo methodInfo;
    jboolean ret = false;

    if (!getJNIStaticMethodInfo(methodInfo, "isBackgroundMusicPlaying", "()Z")) {
        return ret;
    }

    ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);

    return ret;
}

float AndroidJavaEngine::getBackgroundMusicVolume() {
    cocos2d::JniMethodInfo methodInfo;
    jfloat ret = -1.0;

    if (!getJNIStaticMethodInfo(methodInfo, "getBackgroundMusicVolume", "()F")) {
        return ret;
    }

    ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);

    return ret;
}

void AndroidJavaEngine::setBackgroundMusicVolume(float volume) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "setBackgroundMusicVolume", "(F)V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, volume);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}


static float _jni_getEffectsVolume() {
    cocos2d::JniMethodInfo methodInfo;
    jfloat ret = -1.0;

    if (!getJNIStaticMethodInfo(methodInfo, "getEffectsVolume", "()F")) {
        return ret;
    }

    ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);

    return ret;
}

static void _jni_setEffectsVolume(float volume) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "setEffectsVolume", "(F)V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, volume);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static unsigned int _jni_playEffect(const char* filePath, bool loop, float pitch, float pan, float gain)
{
    cocos2d::JniMethodInfo methodInfo;
    int ret = 0;
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);

    if (!getJNIStaticMethodInfo(methodInfo, "playEffect", "(Ljava/lang/String;ZFFF)I")) {
        return ret;
    }

    jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
    ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID,
        methodInfo.methodID,
        stringArg,
        loop,
        pitch, pan, gain);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);

    return (unsigned int)ret;
}

static void _jni_pauseEffect(unsigned int soundId) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "pauseEffect", "(I)V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)soundId);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_pauseAllEffects() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "pauseAllEffects", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_resumeEffect(unsigned int soundId) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "resumeEffect", "(I)V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)soundId);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_resumeAllEffects() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "resumeAllEffects", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_stopEffect(unsigned int soundId) {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "stopEffect", "(I)V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)soundId);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_stopAllEffects() {
    cocos2d::JniMethodInfo methodInfo;

    if (!getJNIStaticMethodInfo(methodInfo, "stopAllEffects", "()V")) {
        return;
    }

    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void loadEffect(const char* filePath, char* loadEffectName) {
    cocos2d::JniMethodInfo methodInfo;
    std::string fullPath = CocosDenshion::android::getFullPathWithoutAssetsPrefix(filePath);

    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, loadEffectName, "(Ljava/lang/String;)V")) {
        return;
    }

    jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

static void _jni_preloadEffect(const char* filePath) {
    loadEffect(filePath, "preloadEffect");
}

static void _jni_unloadEffect(const char* filePath) {
    loadEffect(filePath, "unloadEffect");
}


float AndroidJavaEngine::getEffectsVolume()
{
    if (_implementBaseOnAudioEngine)
    {
        return _effectVolume;
    }
    else
    {
        return _jni_getEffectsVolume();
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
        _jni_setEffectsVolume(volume);
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
        return _jni_playEffect(filePath, loop, pitch, pan, gain);
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
        _jni_pauseEffect(soundID);
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
        _jni_resumeEffect(soundID);
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
        _jni_stopEffect(soundID);
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
        _jni_pauseAllEffects();
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
        _jni_resumeAllEffects();
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
        _jni_stopAllEffects();
    }
}

void AndroidJavaEngine::preloadEffect(const char* filePath)
{
    if (!_implementBaseOnAudioEngine)
    {
        _jni_preloadEffect(filePath);
    }
}

void AndroidJavaEngine::unloadEffect(const char* filePath)
{
    if (!_implementBaseOnAudioEngine)
    {
        _jni_unloadEffect(filePath);
    }
}
