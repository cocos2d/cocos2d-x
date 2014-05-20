/****************************************************************************
Copyright (c) 2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "JniHelper.h"
#include <string.h>
#include "base/CCDirector.h"
#include "../CCApplication.h"
#include "platform/CCFileUtils.h"
#include <jni.h>

using namespace cocos2d;


int getFontSizeAccordingHeightJni(int height) {
    int ret = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxBitmap", "getFontSizeAccordingHeight", "(I)I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, height);
        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

std::string getStringWithEllipsisJni(const char* pszText, float width, float fontSize) {
    std::string ret;
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxBitmap", "getStringWithEllipsis", "(Ljava/lang/String;FF)Ljava/lang/String;")) {
        jstring stringArg1;

        if (!pszText) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszText);
        }

        jstring retFromJava = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, width, fontSize);
        const char* str = t.env->GetStringUTFChars(retFromJava, 0);
        ret = str;

        t.env->ReleaseStringUTFChars(retFromJava, str);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

