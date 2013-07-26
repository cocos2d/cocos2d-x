/*
 * Aplication_linux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */
#include "CCApplication.h"
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include "CCDirector.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN


// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;

static long getCurrentMillSecond() {
	long lLastTime;
	struct timeval stCurrentTime;

	gettimeofday(&stCurrentTime,NULL);
	lLastTime = stCurrentTime.tv_sec*1000+stCurrentTime.tv_usec*0.001; //millseconds
	return lLastTime;
}

Application::Application()
{
	CC_ASSERT(! sm_pSharedApplication);
	sm_pSharedApplication = this;
}

Application::~Application()
{
	CC_ASSERT(this == sm_pSharedApplication);
	sm_pSharedApplication = NULL;
	_animationInterval = 1.0f/60.0f*1000.0f;
}

int Application::run()
{
	// Initialize instance and cocos2d.
	if (! applicationDidFinishLaunching())
	{
		return 0;
	}


	for (;;) {
		long iLastTime = getCurrentMillSecond();
		Director::getInstance()->mainLoop();
		long iCurTime = getCurrentMillSecond();
		if (iCurTime-iLastTime<_animationInterval){
			usleep((_animationInterval - iCurTime+iLastTime)*1000);
		}

	}
	return -1;
}

void Application::setAnimationInterval(double interval)
{
	//TODO do something else
	_animationInterval = interval*1000.0f;
}

void Application::setResourceRootPath(const std::string& rootResDir)
{
    _resourceRootPath = rootResDir;
    if (_resourceRootPath[_resourceRootPath.length() - 1] != '/')
    {
        _resourceRootPath += '/';
    }
    FileUtils* pFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), _resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& Application::getResourceRootPath(void)
{
    return _resourceRootPath;
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_LINUX;
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
	CC_ASSERT(sm_pSharedApplication);
	return sm_pSharedApplication;
}

// @deprecated Use getInstance() instead
Application* Application::sharedApplication()
{
    return Application::getInstance();
}

LanguageType Application::getCurrentLanguage()
{
	char *pLanguageName = getenv("LANG");
	LanguageType ret = LanguageType::ENGLISH;
	if (!pLanguageName)
	{
		return LanguageType::ENGLISH;
	}
	strtok(pLanguageName, "_");
	if (!pLanguageName)
	{
		return LanguageType::ENGLISH;
	}
	
	if (0 == strcmp("zh", pLanguageName))
	{
		ret = LanguageType::CHINESE;
	}
	else if (0 == strcmp("en", pLanguageName))
	{
		ret = LanguageType::ENGLISH;
	}
	else if (0 == strcmp("fr", pLanguageName))
	{
		ret = LanguageType::FRENCH;
	}
	else if (0 == strcmp("it", pLanguageName))
	{
		ret = LanguageType::ITALIAN;
	}
	else if (0 == strcmp("de", pLanguageName))
	{
		ret = LanguageType::GERMAN;
	}
	else if (0 == strcmp("es", pLanguageName))
	{
		ret = LanguageType::SPANISH;
	}
	else if (0 == strcmp("ru", pLanguageName))
	{
		ret = LanguageType::RUSSIAN;
	}
	else if (0 == strcmp("ko", pLanguageName))
	{
		ret = LanguageType::KOREAN;
	}
	else if (0 == strcmp("ja", pLanguageName))
	{
		ret = LanguageType::JAPANESE;
	}
	else if (0 == strcmp("hu", pLanguageName))
	{
		ret = LanguageType::HUNGARIAN;
	}
    else if (0 == strcmp("pt", pLanguageName))
	{
		ret = LanguageType::PORTUGUESE;
	}
    else if (0 == strcmp("ar", pLanguageName))
	{
		ret = LanguageType::ARABIC;
	}
	else if (0 == strcmp("nb", pLanguageName))
	{
		ret = LanguageType::NORWEGIAN;
	}
	else if (0 == strcmp("pl", pLanguageName))
	{
		ret = LanguageType::POLISH;
	}
	
	return ret;
}

NS_CC_END
