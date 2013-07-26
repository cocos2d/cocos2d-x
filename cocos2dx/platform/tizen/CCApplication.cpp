/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "CCApplication.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include <FSystem.h>

NS_CC_BEGIN
using namespace Tizen::Base;
using namespace Tizen::System;

// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;
long Application::_animationInterval = 1000;

Application::Application()
{
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = NULL;
}

int Application::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return false;
    }

    return -1;
}

void Application::setAnimationInterval(double interval)
{
    _animationInterval = interval * 1000.0f;
}

long Application::getAnimationInterval()
{
    return _animationInterval;
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

LanguageType Application::getCurrentLanguage()
{
    result r = E_SUCCESS;
    int index = 0;
    Tizen::Base::String localelanguageCode, languageCode;
    LanguageType ret = LanguageType::ENGLISH;

    r = SettingInfo::GetValue(L"http://tizen.org/setting/locale.language", localelanguageCode);
    TryLog(!IsFailed(r), "[%s] Cannot get the current language setting", GetErrorMessage(r));
    localelanguageCode.IndexOf("_", 0, index);
    localelanguageCode.SubString(0, index, languageCode);

    if (0 == languageCode.CompareTo(L"zho"))
    {
        ret = LanguageType::CHINESE;
    }
    else if (0 == languageCode.CompareTo(L"eng"))
    {
        ret = LanguageType::ENGLISH;
    }
    else if (0 == languageCode.CompareTo(L"fre"))
    {
        ret = LanguageType::FRENCH;
    }
    else if (0 == languageCode.CompareTo(L"ita"))
    {
        ret = LanguageType::ITALIAN;
    }
    else if (0 == languageCode.CompareTo(L"deu"))
    {
        ret = LanguageType::GERMAN;
    }
    else if (0 == languageCode.CompareTo(L"spa"))
    {
        ret = LanguageType::SPANISH;
    }
    else if (0 == languageCode.CompareTo(L"rus"))
    {
        ret = LanguageType::RUSSIAN;
    }
    else if (0 == languageCode.CompareTo(L"kor"))
    {
        ret = LanguageType::KOREAN;
    }
    else if (0 == languageCode.CompareTo(L"jpn"))
    {
        ret = LanguageType::JAPANESE;
    }
    else if (0 == languageCode.CompareTo(L"hun"))
    {
        ret = LanguageType::HUNGARIAN;
    }
    else if (0 == languageCode.CompareTo(L"por"))
    {
        ret = LanguageType::PORTUGUESE;
    }
    else if (0 == languageCode.CompareTo(L"ara"))
    {
        ret = LanguageType::ARABIC;
    }
    else if (0 == languageCode.CompareTo(L"nor"))
    {
        ret = LanguageType::NORWEGIAN;
    }
    else if (0 == languageCode.CompareTo(L"pol"))
    {
        ret = LanguageType::POLISH;
    }
    return ret;
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_TIZEN;
}

NS_CC_END

