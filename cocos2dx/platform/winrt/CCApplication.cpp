/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#include "platform/winrt/CCEGLView.h"
#else
#include "platform/wp8/CCEGLView.h"
#endif
#include "CCDirector.h"
#include <algorithm>
#include "platform/CCFileUtils.h"
/**
@brief    This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/

NS_CC_BEGIN

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;





////////////////////////////////////////////////////////////////////////////////
// implement CCApplication
////////////////////////////////////////////////////////////////////////////////

// sharedApplication pointer
CCApplication * s_pSharedApplication = 0;

CCApplication::CCApplication()
{
    m_nAnimationInterval.QuadPart = 0;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return 0;
    }

	CCEGLView::sharedOpenGLView()->Run();
	return 0;
 #if 0
   // Main message loop:
    MSG msg;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLast);

    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return 0;
    }

    CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();
    while (1)
    {
        if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Get current time tick.
            QueryPerformanceCounter(&nNow);

            // If it's the time to draw next frame, draw it, else sleep a while.
            if (nNow.QuadPart - nLast.QuadPart > m_nAnimationInterval.QuadPart)
            {
                nLast.QuadPart = nNow.QuadPart;
                CCDirector::sharedDirector()->mainLoop();
            }
            else
            {
                Sleep(0);
            }
            continue;
        }

        if (WM_QUIT == msg.message)
        {
            // Quit message loop.
            break;
        }

        // Deal with windows message.

    }

    return (int) msg.wParam;
#endif
}

void CCApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;

    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {0};

    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
    {
        wchar_t* primary = NULL;
        wchar_t* sub = NULL;

        primary = wcstok(localeName, L"-");
        sub = wcstok(NULL, L"-");
        
        if (wcscmp(primary, L"zh") == 0)
        {
            ret = kLanguageChinese;
        }
        else if (wcscmp(primary, L"ja") == 0)
        {
            ret = kLanguageJapanese;
        }
        else if (wcscmp(primary, L"fr") == 0)
        {
            ret = kLanguageFrench;
        }
        else if (wcscmp(primary, L"it") == 0)
        {
            ret = kLanguageItalian;
        }
        else if (wcscmp(primary, L"de") == 0)
        {
            ret = kLanguageGerman;
        }
        else if (wcscmp(primary, L"es") == 0)
        {
            ret = kLanguageSpanish;
        }
        else if (wcscmp(primary, L"nl") == 0)
        {
            ret = kLanguageDutch;
        }
        else if (wcscmp(primary, L"ru") == 0)
        {
            ret = kLanguageRussian;
        }
        else if (wcscmp(primary, L"hu") == 0)
        {
            ret = kLanguageHungarian;
        }
        else if (wcscmp(primary, L"pt") == 0)
        {
            ret = kLanguagePortuguese;
        }
        else if (wcscmp(primary, L"ko") == 0)
        {
            ret = kLanguageKorean;
        }
        else if (wcscmp(primary, L"ar") == 0)
        {
            ret = kLanguageArabic;
        } 
    }

    return ret;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetWinRT;
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
    std::replace(m_resourceRootPath.begin(), m_resourceRootPath.end(), '\\', '/');
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/')
    {
        m_resourceRootPath += '/';
    }
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& CCApplication::getResourceRootPath(void)
{
    return m_resourceRootPath;
}

void CCApplication::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    std::replace(m_startupScriptFilename.begin(), m_startupScriptFilename.end(), '\\', '/');
}

NS_CC_END


