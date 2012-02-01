#include "CCApplication.h"

#include "CCDirector.h"
#include "CCEGLView.h"
#include "CCAccelerometer.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <bps/locale.h>

#define  LOGD(...)  fprintf(stderr, __VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;
long CCApplication::m_animationInterval = 1000;

// convert the timespec into milliseconds
static long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
}

CCApplication::CCApplication()
{
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
	struct timespec time_struct;
	long current_time, update_time;

	// Initialize instance and cocos2d.
	if (!initInstance() || !applicationDidFinishLaunching())
	{
		return 0;
	}

	clock_gettime(CLOCK_REALTIME, &time_struct);
	update_time = time2millis(&time_struct);


	while (1) // or device wants to quit
	{
		CCEGLView::sharedOpenGLView().HandleEvents();

		clock_gettime(CLOCK_REALTIME, &time_struct);
		current_time = time2millis(&time_struct);

		if ((current_time - update_time) > m_animationInterval)
		{
			update_time = current_time;

			CCAccelerometer::sharedAccelerometer()->update(current_time);
			CCDirector::sharedDirector()->mainLoop();
		}
		else
		{
//			sleep(0);
		}
	}
	
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	// interval in milliseconds
	m_animationInterval = (long)(interval * 1000);
}

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
    return orientation;
}

void CCApplication::statusBarFrame(CCRect * rect)
{
    if (rect)
    {
        // qnx doesn't have a status bar
        *rect = CCRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
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

	free(language);
	free(country);

    return ret_language;
}

NS_CC_END;
