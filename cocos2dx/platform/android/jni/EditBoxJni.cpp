/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

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
#include "EditBoxJni.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

#if 0
#define  LOG_TAG    "EditBoxJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

using namespace cocos2d;

static EditBoxCallback s_pfEditBoxCB = NULL;
static void* s_ctx = NULL;

extern "C"
{
//////////////////////////////////////////////////////////////////////////
// handle EditBox message
//////////////////////////////////////////////////////////////////////////



void showEditBoxDialogJni(const char* pszTitle,
                            const char* pszContent,
                            int nInputMode,
                            int nInputFlag,
                            int nReturnType,
                            int nMaxLength,
                            EditBoxCallback pfEditBoxCB,
                            void* ctx)
{
    LOGD("showEditBoxDialogJni...");

    if (pszContent == NULL) {
        return;
    }

    s_pfEditBoxCB = pfEditBoxCB;
    s_ctx = ctx;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/lib/Cocos2dxActivity"
        , "showEditBoxDialog"
        , "(Ljava/lang/String;Ljava/lang/String;IIII)V"))
    {
        jstring stringArg1;

        if (!pszTitle)
        {
            stringArg1 = t.env->NewStringUTF("");
        }
        else
        {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszContent);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, nInputMode, nInputFlag, nReturnType, nMaxLength);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void JNICALL Java_org_cocos2dx_lib_Cocos2dxActivity_nativeSetEditboxText(JNIEnv * env, jobject obj, jbyteArray text)
{
    jsize  size = env->GetArrayLength(text);

    if (size > 0)
    {
        jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
        char* pBuf = (char*)malloc(size+1);
        if (pBuf != NULL)
        {
            memcpy(pBuf, data, size);
            pBuf[size] = '\0';
            // pass data to editbox's delegate
            if (s_pfEditBoxCB) s_pfEditBoxCB(pBuf, s_ctx);
            free(pBuf);
        }
        env->ReleaseByteArrayElements(text, data, 0);
    }
    else
    {
        if (s_pfEditBoxCB) s_pfEditBoxCB("", s_ctx);
    }
}

int getFontSizeAccordingHeightJni(int height)
{
    int ret = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/lib/Cocos2dxBitmap"
        , "getFontSizeAccordingHeight"
        , "(I)I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, height);
        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

std::string getStringWithEllipsisJni(const char* pszText, float width, float fontSize)
{
    std::string ret;
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/lib/Cocos2dxBitmap"
        , "getStringWithEllipsis"
        , "(Ljava/lang/String;FF)Ljava/lang/String;"))
    {
        jstring stringArg1;

        if (!pszText)
        {
            stringArg1 = t.env->NewStringUTF("");
        }
        else
        {
            stringArg1 = t.env->NewStringUTF(pszText);
        }

        jstring retFromJava = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, width, fontSize);
        const char* str = t.env->GetStringUTFChars(retFromJava, 0);
        ret = str;

        t.env->ReleaseStringUTFChars(retFromJava, str);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
    LOGD("getStringWithEllipsisJni 07");
    return ret;
}

} // end of extern "C"
