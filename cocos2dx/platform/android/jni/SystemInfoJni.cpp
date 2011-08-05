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
#include "SystemInfoJni.h"
#include "JniHelper.h"

#include <android/log.h>
#include <jni.h>


#if 0
#define  LOG_TAG    "SystemInfoJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

extern "C"
{
	char* getPackageNameJNI()
	{
		JniMethodInfo t;
		char* ret = 0;

		if (JniHelper::getStaticMethodInfo(t, 
						"org/cocos2dx/lib/Cocos2dxActivity",
						"getCocos2dxPackageName",
						"()Ljava/lang/String;"))
		{
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			ret = (char*)JniHelper::jstring2string(str).c_str();

			LOGD("package name %s", ret);
		}

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////
    // handle get current language
    //////////////////////////////////////////////////////////////////////////
    char* getCurrentLanguageJNI()
    {
        JniMethodInfo t;
        char* ret = 0;

        if (JniHelper::getStaticMethodInfo(t
            , "org/cocos2dx/lib/Cocos2dxActivity"
            , "getCurrentLanguage"
            , "()Ljava/lang/String;"))
        {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			ret = (char*)JniHelper::jstring2string(str).c_str();

			LOGD("language name %s", ret);
        }

        return ret;
    }
}
