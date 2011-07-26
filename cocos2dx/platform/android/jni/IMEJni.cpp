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
#include "IMEJni.h"
#include "CCIMEDispatcher.h"
#include "JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

#if 0
#define  LOG_TAG    "IMEJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

extern "C"
{
    //////////////////////////////////////////////////////////////////////////
    // handle IME message
    //////////////////////////////////////////////////////////////////////////

    void setKeyboardStateJNI(int bOpen)
    {
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t, 
			"org/cocos2dx/lib/Cocos2dxGLSurfaceView",
			(bOpen) ? "openIMEKeyboard" : "closeIMEKeyboard",
			"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
    }

    void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText(JNIEnv* env, jobject thiz, jstring text)
    {
        jboolean isCopy = 0;
        const char* pszText = env->GetStringUTFChars(text, &isCopy);
        if (isCopy) 
        {
            cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
            env->ReleaseStringUTFChars(text, pszText);
        }
    }

    void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeDeleteBackward(JNIEnv* env, jobject thiz)
    {
        cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }

    jstring Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeGetContentText()
    {
        JNIEnv * env = 0;

        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK || ! env)
        {
            return 0;
        }
        const char * pszText = cocos2d::CCIMEDispatcher::sharedDispatcher()->getContentText();
        return env->NewStringUTF(pszText);
    }
}
