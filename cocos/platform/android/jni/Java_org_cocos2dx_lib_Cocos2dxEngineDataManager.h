/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.

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

#pragma once
#include "base/ccTypes.h"

#include <string>
#include <functional>
#include <vector>

#include <jni.h>

namespace cocos2d {

class ParticleSystem;
class EventCustom;

class EngineDataManager
{
public:
    static void init();
    static void destroy();
    
    static std::string getVendorInfo();

    enum class GameStatus
    {
        LAUNCH_BEGIN = 0,
        LAUNCH_END,
        SCENE_CHANGE_BEGIN,
        SCENE_CHANGE_END,
        IN_SCENE
    };

    static void notifyGameStatus(GameStatus type, int cpuLevel, int gpuLevel);
    static void setAnimationInterval(float interval, SetIntervalReason reason);
    // Used in FileUtilsAndroid::getContents
    static void onBeforeReadFile();

private:
    static void notifyContinuousFrameLost(int frameLostCycle, int continueFrameLostThreshold, int times);
    static void notifyLowFps(int lowFpsCycle, float lowFpsThreshold, int frames);
    static void notifyFpsChanged(float oldFps, float newFps);
    static void notifyGameStatusIfCpuOrGpuLevelChanged();

    static void calculateFrameLost();

    static void onBeforeSetNextScene(EventCustom* event);
    static void onAfterDrawScene(EventCustom* event);
    static void onEnterForeground(EventCustom* event);
    static void onEnterBackground(EventCustom* event);

    static int getTotalParticleCount();

// For JNI function use, should be public
public:
    static void nativeOnQueryFps(JNIEnv* env, jobject thiz, jintArray arrExpectedFps, jintArray arrRealFps);
    static void nativeOnChangeContinuousFrameLostConfig(JNIEnv* env, jobject thiz, jint continueFrameLostCycle, jint continueFrameLostThreshold);
    static void nativeOnChangeLowFpsConfig(JNIEnv* env, jobject thiz, jint lowFpsCycle, jfloat lowFpsThreshold);
    static void nativeOnChangeExpectedFps(JNIEnv* env, jobject thiz, jint fps);
    static void nativeOnChangeSpecialEffectLevel(JNIEnv* env, jobject thiz, jint level);
    static void nativeOnChangeMuteEnabled(JNIEnv* env, jobject thiz, jboolean enabled);
};

} // namespace cocos2d {