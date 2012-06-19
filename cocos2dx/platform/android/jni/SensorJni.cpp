/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "SensorJni.h"
#include "cocoa/CCGeometry.h"
#include "platform/android/CCAccelerometer.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <android/log.h>
#include <jni.h>
#include "CCDirector.h"

#if 0
#define  LOG_TAG    "SensorJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

extern "C"
{

    //////////////////////////////////////////////////////////////////////////
    // handle accelerometer changes
    //////////////////////////////////////////////////////////////////////////

    void Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp)
    {
        // We need to invert to make it compatible with iOS.
        CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
        float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
//         cocos2d::CCAccelerometer::sharedAccelerometer()->update((x - rcRect.origin.x) / fScreenScaleFactor,
//             (y - rcRect.origin.y) / fScreenScaleFactor, 
//             z, 
//             timeStamp);
        CCDirector* pDirector = CCDirector::sharedDirector();
        pDirector->getAccelerometer()->update(x, y, z, timeStamp);
    }    

    void enableAccelerometerJNI()
    {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, 
                                     "org/cocos2dx/lib/Cocos2dxActivity",
                                     "enableAccelerometer",
                                     "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void disableAccelerometerJNI()
    {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, 
            "org/cocos2dx/lib/Cocos2dxActivity",
            "disableAccelerometer",
            "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}
