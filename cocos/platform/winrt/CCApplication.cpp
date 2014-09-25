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
#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#include "platform/winrt/CCGLViewImpl.h"
#else
#include "platform/wp8/CCGLViewImpl-wp8.h"
#endif
#include "base/CCDirector.h"
#include <algorithm>
#include "platform/CCFileUtils.h"
#include "CCWinRTUtils.h"

/**
@brief    This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/

NS_CC_BEGIN

// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;





////////////////////////////////////////////////////////////////////////////////
// implement Application
////////////////////////////////////////////////////////////////////////////////

// sharedApplication pointer
Application * s_pSharedApplication = 0;

Application::Application() :
m_openURLDelegate(nullptr)
{
    m_nAnimationInterval.QuadPart = 0;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int Application::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return 0;
    }

	GLViewImpl::sharedOpenGLView()->Run();
	return 0;
}

void Application::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

const char * Application::getCurrentLanguageCode()
{
	static std::string code = "";

    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {0};
    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
    {
        wchar_t* primary = wcstok(localeName, L"-");
        code = CCUnicodeToUtf8(primary);
    }
    else
    {
        code = "en";
    }

    return code.c_str();
}


LanguageType Application::getCurrentLanguage()
{
    LanguageType ret = LanguageType::ENGLISH;

    const char* code = getCurrentLanguageCode();

    if (strcmp(code, "zh") == 0)
    {
        ret = LanguageType::CHINESE;
    }
    else if (strcmp(code, "ja") == 0)
    {
        ret = LanguageType::JAPANESE;
    }
    else if (strcmp(code, "fr") == 0)
    {
        ret = LanguageType::FRENCH;
    }
    else if (strcmp(code, "it") == 0)
    {
        ret = LanguageType::ITALIAN;
    }
    else if (strcmp(code, "de") == 0)
    {
        ret = LanguageType::GERMAN;
    }
    else if (strcmp(code, "es") == 0)
    {
        ret = LanguageType::SPANISH;
    }
    else if (strcmp(code, "nl") == 0)
    {
        ret = LanguageType::DUTCH;
    }
    else if (strcmp(code, "ru") == 0)
    {
        ret = LanguageType::RUSSIAN;
    }
    else if (strcmp(code, "hu") == 0)
    {
        ret = LanguageType::HUNGARIAN;
    }
    else if (strcmp(code, "pt") == 0)
    {
        ret = LanguageType::PORTUGUESE;
    }
    else if (strcmp(code, "ko") == 0)
    {
        ret = LanguageType::KOREAN;
    }
    else if (strcmp(code, "ar") == 0)
    {
        ret = LanguageType::ARABIC;
    } 

    return ret;
}

Application::Platform  Application::getTargetPlatform()
{
    return Platform::OS_WP8;
}

bool Application::openURL(const std::string &url)
{
    if (m_openURLDelegate)
    {
        m_openURLDelegate(PlatformStringFromString(url));
        return true;
    }
    else
    {
        return false;
    }
}

void Application::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
    std::replace(m_resourceRootPath.begin(), m_resourceRootPath.end(), '\\', '/');
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/')
    {
        m_resourceRootPath += '/';
    }
    FileUtils* pFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& Application::getResourceRootPath(void)
{
    return m_resourceRootPath;
}

void Application::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    std::replace(m_startupScriptFilename.begin(), m_startupScriptFilename.end(), '\\', '/');
}

NS_CC_END


