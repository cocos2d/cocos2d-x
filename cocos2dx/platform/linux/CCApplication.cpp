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
		Director::sharedDirector()->mainLoop();
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
    FileUtils* pFileUtils = FileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), _resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& Application::getResourceRootPath(void)
{
    return _resourceRootPath;
}

TargetPlatform Application::getTargetPlatform()
{
    return kTargetLinux;
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::sharedApplication()
{
	CC_ASSERT(sm_pSharedApplication);
	return sm_pSharedApplication;
}

ccLanguageType Application::getCurrentLanguage()
{
	char *pLanguageName = getenv("LANG");
	ccLanguageType ret = kLanguageEnglish;
	if (!pLanguageName)
	{
		return kLanguageEnglish;
	}
	strtok(pLanguageName, "_");
	if (!pLanguageName)
	{
		return kLanguageEnglish;
	}
	
	if (0 == strcmp("zh", pLanguageName))
	{
		ret = kLanguageChinese;
	}
	else if (0 == strcmp("en", pLanguageName))
	{
		ret = kLanguageEnglish;
	}
	else if (0 == strcmp("fr", pLanguageName))
	{
		ret = kLanguageFrench;
	}
	else if (0 == strcmp("it", pLanguageName))
	{
		ret = kLanguageItalian;
	}
	else if (0 == strcmp("de", pLanguageName))
	{
		ret = kLanguageGerman;
	}
	else if (0 == strcmp("es", pLanguageName))
	{
		ret = kLanguageSpanish;
	}
	else if (0 == strcmp("ru", pLanguageName))
	{
		ret = kLanguageRussian;
	}
	else if (0 == strcmp("ko", pLanguageName))
	{
		ret = kLanguageKorean;
	}
	else if (0 == strcmp("ja", pLanguageName))
	{
		ret = kLanguageJapanese;
	}
	else if (0 == strcmp("hu", pLanguageName))
	{
		ret = kLanguageHungarian;
	}
    else if (0 == strcmp("pt", pLanguageName))
	{
		ret = kLanguagePortuguese;
	}
    else if (0 == strcmp("ar", pLanguageName))
	{
		ret = kLanguageArabic;
	}
	else if (0 == strcmp("nb", pLanguageName))
	{
		ret = kLanguageNorwegian;
	}
	else if (0 == strcmp("pl", pLanguageName))
	{
		ret = kLanguagePolish;
	}
	
	return ret;
}

NS_CC_END
