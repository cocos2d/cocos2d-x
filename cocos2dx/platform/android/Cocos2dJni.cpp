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
#include "platform/android/CCXUIAccelerometer_android.h"
#include <android/log.h>

extern "C"
{
	static cocos2d::CCTouch s_touch;
	static cocos2d::NSSet s_set;

	// handle accelerometer changes

	void Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp)
	{
		// We need to invert to make it compatible with iOS.
		cocos2d::UIAccelerometer::sharedAccelerometer()->update(-1*x, -1*y, -1*z, timeStamp);
	}

	// handle touch event
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		s_set.addObject(&s_touch);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesBegan(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesEnded(&s_set, NULL);
		s_set.removeObject(&s_touch);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesMoved(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
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

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		gJavaVM = vm;
		return JNI_VERSION_1_4;
	}
	
	// native renderer

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env)
	{
		cocos2d::CCDirector::sharedDirector()->mainLoop();
	}
}
