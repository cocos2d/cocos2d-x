#include "CCApplication.h"
#include "platform/CCFileUtils.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <bps/locale.h>

#define  LOGD(...)  fprintf(stderr, __VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;
long Application::_animationInterval = 1000;

// convert the timespec into milliseconds
static long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
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
}

int Application::run()
{
	struct timespec time_struct;
	long current_time, update_time;

	// Initialize instance and cocos2d.
	if (!applicationDidFinishLaunching())
	{
		return 0;
	}

	clock_gettime(CLOCK_REALTIME, &time_struct);
	update_time = time2millis(&time_struct);


	while (1) // or device wants to quit
	{
		EGLView::sharedOpenGLView()->handleEvents();

		clock_gettime(CLOCK_REALTIME, &time_struct);
		current_time = time2millis(&time_struct);

		if ((current_time - update_time) > _animationInterval)
		{
			update_time = current_time;
			Director::sharedDirector()->mainLoop();
		}
		else
		{
//			sleep(0);
		}
	}
	
	return -1;
}

void Application::setAnimationInterval(double interval)
{
	// interval in milliseconds
	_animationInterval = (long)(interval * 1000);
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
    return kTargetBlackBerry;
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
	ccLanguageType ret_language = kLanguageEnglish;
	char *language, *country;

	locale_get(&language, &country);

	if (strcmp(language, "en") == 0)
	{
		ret_language = kLanguageEnglish;
	}
	else if (strcmp(language, "fr") == 0)
	{
		ret_language = kLanguageFrench;
	}
	else if (strcmp(language, "de") == 0)
	{
		ret_language = kLanguageGerman;
	}
	else if (strcmp(language, "it") == 0)
	{
		ret_language = kLanguageItalian;
	}
	else if (strcmp(language, "es") == 0)
	{
		ret_language = kLanguageSpanish;
	}
	else if (strcmp(language, "ch") == 0)
	{
		ret_language = kLanguageChinese;
	}
	else if (strcmp(language, "ru") == 0)
	{
		ret_language = kLanguageRussian;
	}
	else if (strcmp(language, "ko") == 0)
	{
		ret_language = kLanguageKorean;
	}
	else if (strcmp(language, "ja") == 0)
	{
		ret_language = kLanguageJapanese;
	}
	else if (strcmp(language, "hu") == 0)
	{
		ret_language = kLanguageHungarian;
	}
    else if (strcmp(language, "pt") == 0)
    {
        ret_language = kLanguagePortuguese;
    }
    else if (strcmp(language, "ar") == 0)
    {
        ret_language = kLanguageArabic;
    }
    else if (strcmp(language, "nb") == 0)
    {
        ret_language = kLanguageNorwegian;
    }
    else if (strcmp(language, "pl") == 0)
    {
        ret_language = kLanguagePolish;
    }
	free(language);
	free(country);

    return ret_language;
}

NS_CC_END;
