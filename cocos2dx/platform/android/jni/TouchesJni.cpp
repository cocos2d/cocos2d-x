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
#include "CCSet.h"
#include "CCDirector.h"
#include "CCKeypadDispatcher.h"
#include "CCTouch.h"
#include "CCEGLView.h"
#include "CCTouchDispatcher.h"

#include <android/log.h>
#include <jni.h>

#if 0
#define  LOG_TAG    "NativeTouchesJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

extern "C"
{

#define MAX_TOUCHES         5
static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };

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
}
