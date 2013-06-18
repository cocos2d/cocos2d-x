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
CCApplication * CCApplication::sm_pSharedApplication = 0;
long CCApplication::m_nAnimationInterval = 1000;

CCApplication::CCApplication()
{
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return false;
    }

    return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
    m_nAnimationInterval = interval * 1000.0f;
}

long CCApplication::getAnimationInterval()
{
    return m_nAnimationInterval;
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CCAssert(sm_pSharedApplication, "");
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    result r = E_SUCCESS;
    int index = 0;
    String localelanguageCode, languageCode;
    ccLanguageType ret = kLanguageEnglish;

    r = SettingInfo::GetValue(L"http://tizen.org/setting/locale.language", localelanguageCode);
    TryLog(!IsFailed(r), "[%s] Cannot get the current language setting", GetErrorMessage(r));
    localelanguageCode.IndexOf("_", 0, index);
    localelanguageCode.SubString(0, index, languageCode);

    if (0 == languageCode.CompareTo(L"zho"))
    {
        ret = kLanguageChinese;
    }
    else if (0 == languageCode.CompareTo(L"eng"))
    {
        ret = kLanguageEnglish;
    }
    else if (0 == languageCode.CompareTo(L"fre"))
    {
        ret = kLanguageFrench;
    }
    else if (0 == languageCode.CompareTo(L"ita"))
    {
        ret = kLanguageItalian;
    }
    else if (0 == languageCode.CompareTo(L"deu"))
    {
        ret = kLanguageGerman;
    }
    else if (0 == languageCode.CompareTo(L"spa"))
    {
        ret = kLanguageSpanish;
    }
    else if (0 == languageCode.CompareTo(L"rus"))
    {
        ret = kLanguageRussian;
    }
    else if (0 == languageCode.CompareTo(L"kor"))
    {
        ret = kLanguageKorean;
    }
    else if (0 == languageCode.CompareTo(L"jpn"))
    {
        ret = kLanguageJapanese;
    }
    else if (0 == languageCode.CompareTo(L"hun"))
    {
        ret = kLanguageHungarian;
    }
    else if (0 == languageCode.CompareTo(L"por"))
    {
        ret = kLanguagePortuguese;
    }
    else if (0 == languageCode.CompareTo(L"ara"))
    {
        ret = kLanguageArabic;
    }

    return ret;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetTizen;
}

NS_CC_END

