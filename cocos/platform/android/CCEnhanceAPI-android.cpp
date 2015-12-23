/****************************************************************************
 * Samsung API for cocos
 * Developed by Game Engine part
 *
 * Copyright 2015 by Mobile Solution Lab, MSG, SRC-NJ.
 * Wang Ying
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics, Inc. ("Confidential Information"). You
 * Shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung
****************************************************************************/


#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "jni/JniHelper.h"
#include "CCEnhanceAPI-android.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "CCEnhanceAPI_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

// FIXME: using ndk-r10c will cause the next function could not be found. It may be a bug of ndk-r10c.
// Here is the workaround method to fix the problem.
#ifdef __aarch64__
extern "C" size_t __ctype_get_mb_cur_max(void) {
    return (size_t) sizeof(wchar_t);
}
#endif

NS_CC_BEGIN

EnhanceAPI::EnhanceAPI()
{
}

EnhanceAPI::~EnhanceAPI()
{
}

int EnhanceAPI::setResolutionPercent(int n)
{
    JniMethodInfo t;
    int ret = -1;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setResolutionPercent", "(I)I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, n);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

int EnhanceAPI::setFPS(int fps)
{
    JniMethodInfo t;
    int ret = -1;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFPS", "(I)I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, fps);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

int EnhanceAPI::fastLoading(int sec)
{
    JniMethodInfo t;
    int ret = -1;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "fastLoading", "(I)I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, sec);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

int EnhanceAPI::getTemperature()
{
    JniMethodInfo t;
    int ret = -1;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getTemperature", "()I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

int EnhanceAPI::setLowPowerMode(bool enable)
{
    JniMethodInfo t;
    int ret = -1;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setLowPowerMode", "(Z)I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, enable);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}
NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

