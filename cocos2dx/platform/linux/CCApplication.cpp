/*
 * CCAplication_linux.cpp
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
CCApplication * CCApplication::sm_pSharedApplication = 0;

static long getCurrentMillSecond() {
	long lLastTime;
	struct timeval stCurrentTime;

	gettimeofday(&stCurrentTime,NULL);
	lLastTime = stCurrentTime.tv_sec*1000+stCurrentTime.tv_usec*0.001; //millseconds
	return lLastTime;
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
	m_nAnimationInterval = 1.0f/60.0f*1000.0f;
}

int CCApplication::run()
{
	// Initialize instance and cocos2d.
	if (! applicationDidFinishLaunching())
	{
		return 0;
	}


	for (;;) {
		long iLastTime = getCurrentMillSecond();
		CCDirector::sharedDirector()->mainLoop();
		long iCurTime = getCurrentMillSecond();
		if (iCurTime-iLastTime<m_nAnimationInterval){
			usleep((m_nAnimationInterval - iCurTime+iLastTime)*1000);
		}

	}
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	//TODO do something else
	m_nAnimationInterval = interval*1000.0f;
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
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

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetLinux;
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
	
	return ret;
}

NS_CC_END
