/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/CCApplication.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include <android/log.h>
#include <jni.h>
#include <cstring>

#define  LOG_TAG    "CCApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

// FIXME: using ndk-r10c will cause the next function could not be found. It may be a bug of ndk-r10c.
// Here is the workaround method to fix the problem.
#ifdef __aarch64__
extern "C" size_t __ctype_get_mb_cur_max(void) {
    return (size_t) sizeof(wchar_t);
}
#endif

static const std::string helperClassName = "org/cocos2dx/lib/Cocos2dxHelper";

NS_CC_BEGIN

// sharedApplication pointer
Application * Application::sm_pSharedApplication = nullptr;

Application::Application()
{
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = nullptr;
}

int Application::run()
{
    // Initialize instance and cocos2d.
    if (! applicationDidFinishLaunching())
    {
        return 0;
    }

    return -1;
}

void Application::setAnimationInterval(float interval)
{
    setAnimationInterval(interval, SetIntervalReason::BY_ENGINE);
}

void Application::setAnimationInterval(float interval, SetIntervalReason reason)
{
    EngineDataManager::setAnimationInterval(interval, reason);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
    CCAssert(sm_pSharedApplication, "");
    return sm_pSharedApplication;
}

// @deprecated Use getInstance() instead
Application* Application::sharedApplication()
{
    return Application::getInstance();
}

const char * Application::getCurrentLanguageCode()
{
    static char code[3]={0};
    std::string language = JniHelper::callStaticStringMethod(helperClassName, "getCurrentLanguage");
    strncpy(code, language.c_str(), 2);
    code[2]='\0';
    return code;
}

LanguageType Application::getCurrentLanguage()
{
    const char* code = getCurrentLanguageCode();

    return utils::getLanguageTypeByISO2(code);
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_ANDROID;
}

std::string Application::getVersion()
{
    return JniHelper::callStaticStringMethod(helperClassName, "getVersion");
}

bool Application::openURL(const std::string &url)
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "openURL", url);
}

void Application::applicationScreenSizeChanged(int newWidth, int newHeight) {

}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
