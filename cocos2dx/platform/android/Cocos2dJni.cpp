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
#include "CCSet.h"
#include "CCDirector.h"
#include "CCKeypadDispatcher.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCFileUtils.h"
#include "CCGeometry.h"
#include "platform/android/CCAccelerometer_android.h"
#include <android/log.h>

#if 0
#define  LOG_TAG    "Cocos2dJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

extern "C"
{

	#define MAX_TOUCHES         5
	static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };

	// handle accelerometer changes

	void Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp)
	{
		// We need to invert to make it compatible with iOS.
		CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
		cocos2d::CCAccelerometer::sharedAccelerometer()->update((x - rcRect.origin.x) / fScreenScaleFactor,
		                                                        (y - rcRect.origin.y) / fScreenScaleFactor, 
		                                                         z, 
		                                                         timeStamp);
	}

	// handle touch event	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
		CCSet set;

		CCTouch *pTouch = s_pTouches[id];
		if (! pTouch)
		{
			LOGD("Beginning touches with id: %d, x=%f, y=%f", id, x, y);

			pTouch = new CCTouch();			
			pTouch->SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor, (y - rcRect.origin.y) / fScreenScaleFactor);
			s_pTouches[id] = pTouch;
			set.addObject(pTouch);

			cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesBegan(&set, NULL);
		}	
		else
		{
			LOGD("Beginnig touches with id: %d error", id);
		}
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
		CCSet set;

		/* Add to the set to send to the director */
		CCTouch* pTouch = s_pTouches[id];		
		if (pTouch)
		{
			LOGD("Ending touches with id: %d, x=%f, y=%f", id, x, y);

			pTouch->SetTouchInfo(0, (x - rcRect.origin.x) / fScreenScaleFactor , (y - rcRect.origin.y) / fScreenScaleFactor);
		    set.addObject(pTouch);

			// release the object
			pTouch->release();
			s_pTouches[id] = NULL;

			cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesEnded(&set, NULL);
		} else {
			LOGD("Ending touches with id: %d error", id);
		}		
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv*  env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys)
	{
		int size = env->GetArrayLength(ids);
		jint id[size];
		jfloat x[size];
		jfloat y[size];
		CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
		CCSet set;

		env->GetIntArrayRegion(ids, 0, size, id);
		env->GetFloatArrayRegion(xs, 0, size, x);
		env->GetFloatArrayRegion(ys, 0, size, y);

		for( int i = 0 ; i < size ; i++ ) {
			LOGD("Moving touches with id: %d, x=%f, y=%f", id[i], x[i], y[i]);
			cocos2d::CCTouch* pTouch = s_pTouches[id[i]];
			if (pTouch)
			{
				pTouch->SetTouchInfo(0, (x[i] - rcRect.origin.x) / fScreenScaleFactor , 
			                        (y[i] - rcRect.origin.y) / fScreenScaleFactor);
				set.addObject(pTouch);
			}
			else
			{
				// It is error, should return.
				LOGD("Moving touches with id: %d error", id[i]);
				return;
			}
		}
		
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesMoved(&set, NULL);
	}

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv*  env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys)
	{
		int size = env->GetArrayLength(ids);
		jint id[size];
		jfloat x[size];
		jfloat y[size];
		CCRect rcRect = CCEGLView::sharedOpenGLView().getViewPort();
		float fScreenScaleFactor = CCEGLView::sharedOpenGLView().getScreenScaleFactor();
		CCSet set;

		env->GetIntArrayRegion(ids, 0, size, id);
		env->GetFloatArrayRegion(xs, 0, size, x);
		env->GetFloatArrayRegion(ys, 0, size, y);

		for( int i = 0 ; i < size ; i++ ) {
			cocos2d::CCTouch* pTouch = s_pTouches[id[i]];
			if (pTouch)
			{
				pTouch->SetTouchInfo(0, (x[i] - rcRect.origin.x) / fScreenScaleFactor , 
			                        (y[i] - rcRect.origin.y) / fScreenScaleFactor);
				set.addObject(pTouch);
				s_pTouches[id[i]] = NULL;
				pTouch->release();
			}
		}

		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesCancelled(&set, NULL);
	}

#define KEYCODE_BACK 0x04
#define KEYCODE_MENU 0x52
	
	// handle keydown event

	jboolean Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown(JNIEnv*  env, jobject thiz, jint keyCode)
	{
		switch (keyCode)
		{
		case KEYCODE_BACK:
			if (CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeBackClicked))
				return JNI_TRUE;
			break;
		case KEYCODE_MENU:
			if (CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked))
				return JNI_TRUE;
			break;
		default:
			return JNI_FALSE;
		}
		return JNI_FALSE;
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
		jmethodID methodID = getMethodID("enableAccelerometer", "()V");

		if (methodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, methodID);
		}
	}

	void disableAccelerometerJNI()
	{
		jmethodID methodID = getMethodID("disableAccelerometer", "()V");

		if (methodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, methodID);
		}
	}

	void showMessageBoxJNI(const char * pszMsg, const char * pszTitle)
	{
		if (! pszMsg)
		{
			return;
		}

		jmethodID methodID = getMethodID("showMessageBox", "(Ljava/lang/String;Ljava/lang/String;)V");

		if (methodID)
		{
			jstring StringArg1;

			if (! pszTitle)
			{
				StringArg1 = env->NewStringUTF("");
			}
			else
			{
				StringArg1 = env->NewStringUTF(pszTitle);
			}

			jstring StringArg2 = env->NewStringUTF(pszMsg);
			env->CallStaticVoidMethod(classOfCocos2dxActivity, methodID, StringArg1, StringArg2);
		}
	}

	// native renderer

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env)
	{
		cocos2d::CCDirector::sharedDirector()->mainLoop();
	}
}
