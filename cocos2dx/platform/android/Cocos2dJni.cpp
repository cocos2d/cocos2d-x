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
#include "Cocos2dJni.h"
#include "NSSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCXFileUtils.h"
#include "CGGeometry.h"
#include "platform/android/CCXUIAccelerometer_android.h"
#include <android/log.h>

#define  LOG_TAG    "Cocos2dJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{
	static cocos2d::CCTouch s_touch;
	static cocos2d::NSSet s_set;

	// handle accelerometer changes

	void Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp)
	{
		// We need to invert to make it compatible with iOS.
		CGRect rcRect = CCXEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCXEGLView::sharedOpenGLView().getScreenScaleFactor();
		cocos2d::UIAccelerometer::sharedAccelerometer()->update((x - rcRect.origin.x) / fScreenScaleFactor,
		                                                        (y - rcRect.origin.y) / fScreenScaleFactor, 
		                                                         z, 
		                                                         timeStamp);
	}

	// handle touch event
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
	        CGRect rcRect = CCXEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCXEGLView::sharedOpenGLView().getScreenScaleFactor();
		s_touch.SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor, (y - rcRect.origin.y) / fScreenScaleFactor);
		s_set.addObject(&s_touch);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesBegan(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
	        CGRect rcRect = CCXEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCXEGLView::sharedOpenGLView().getScreenScaleFactor();
		s_touch.SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor, (y - rcRect.origin.y) / fScreenScaleFactor);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesEnded(&s_set, NULL);
		s_set.removeObject(&s_touch);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		CGRect rcRect = CCXEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCXEGLView::sharedOpenGLView().getScreenScaleFactor();
		s_touch.SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor, (y - rcRect.origin.y) / fScreenScaleFactor);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesMoved(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		CGRect rcRect = CCXEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCXEGLView::sharedOpenGLView().getScreenScaleFactor();
		s_touch.SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor, (y - rcRect.origin.y) / fScreenScaleFactor);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesCancelled(&s_set, NULL);
		s_set.removeObject(&s_touch);
	}

    void Java_org_cocos2dx_lib_Cocos2dxActivity_nativeSetPaths(JNIEnv*  env, jobject thiz, jstring apkPath)
    {
        const char* str;
        jboolean isCopy;
        str = env->GetStringUTFChars(apkPath, &isCopy);
        if (isCopy) {
            cocos2d::CCFileUtils::setResourcePath(str);
            env->ReleaseStringUTFChars(apkPath, str);
        }
    }
	
	// record the java vm
	
	JavaVM *gJavaVM = NULL;
	jclass classOfCocos2dxActivity = 0;
	JNIEnv *env = 0;

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		gJavaVM = vm;
		return JNI_VERSION_1_4;
	}

	static jmethodID getMethodID(const char *methodName, const char *paramCode)
	{
		jmethodID ret = 0;

		// get jni environment and java class for Cocos2dxActivity
		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		{
			LOGD("Failed to get the environment using GetEnv()");
			return 0;
		}

		if (gJavaVM->AttachCurrentThread(&env, 0) < 0)
		{
			LOGD("Failed to get the environment using AttachCurrentThread()");
			return 0;
		}

		classOfCocos2dxActivity = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
		if (! classOfCocos2dxActivity)
		{
			LOGD("Failed to find class of org/cocos2dx/lib/Cocos2dxActivity");
			return 0;
		}

		if (env != 0 && classOfCocos2dxActivity != 0)
		{
			ret = env->GetStaticMethodID(classOfCocos2dxActivity, methodName, paramCode);
		}

		if (! ret)
		{
			LOGD("get method id of %s error", methodName);
		}

		return ret;
	}

	void enableAccelerometerJNI()
	{
		// void stopBackgroundMusic()
		jmethodID methodID = getMethodID("enableAccelerometer", "()V");

		if (methodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, methodID);
		}
	}

	void disableAccelerometerJNI()
	{
		// void stopBackgroundMusic()
		jmethodID methodID = getMethodID("disableAccelerometer", "()V");

		if (methodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, methodID);
		}
	}

	// native renderer

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env)
	{
		cocos2d::CCDirector::sharedDirector()->mainLoop();
	}
}
