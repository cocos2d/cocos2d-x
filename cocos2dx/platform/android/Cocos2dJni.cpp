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

#include <android/log.h>
#define  LOG_TAG    "Cocos2dJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
{

	#define MAX_TOUCHES         4
	static cocos2d::CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };
	static cocos2d::NSSet s_set;
	
	// handle touch event
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		cocos2d::CCTouch* pTouch = s_pTouches[id];
		if (!pTouch)
		{
			pTouch = new cocos2d::CCTouch;
		}

		pTouch->SetTouchInfo(0, x, y);
		s_set.addObject(pTouch);
		s_pTouches[id] = pTouch;
		cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesBegan(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		cocos2d::CCTouch* pTouch = s_pTouches[id];
		if (pTouch)
		{
			pTouch->SetTouchInfo(0, x, y);
			s_set.addObject(pTouch);
			cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesEnded(&s_set, NULL);
			s_set.removeObject(pTouch);
			pTouch->release();

			s_pTouches[id] = NULL;
		}
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		cocos2d::CCTouch* pTouch = s_pTouches[id];
		if (pTouch)
		{
			pTouch->SetTouchInfo(0, x, y);
			s_set.addObject(pTouch);
			cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesMoved(&s_set, NULL);
		}
	}

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv*  env, jobject thiz, jint id, jfloat x, jfloat y)
	{
		cocos2d::CCTouch* pTouch = s_pTouches[id];
		if (pTouch)
		{
			pTouch->SetTouchInfo(0, x, y);
			s_set.addObject(pTouch);
			cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDelegate()->touchesCancelled(&s_set, NULL);
			s_set.removeObject(pTouch);
		}
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
