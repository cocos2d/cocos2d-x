/*
 * CCAplication_linux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */
#include "CCApplication.h"
#include <unistd.h>
#include <sys/time.h>

#include "CCDirector.h"

NS_CC_BEGIN;

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
	if (! initInstance() || ! applicationDidFinishLaunching())
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

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
	// swap width and height
	CCEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
	if (pView)
	{
		return (Orientation)pView->setDeviceOrientation(orientation);
	}
	return (Orientation)CCDirector::sharedDirector()->getDeviceOrientation();
}

void CCApplication::statusBarFrame(CCRect * rect) {

	if (rect)
	{
		// linux doesn't have status bar.
		*rect = CCRectMake(0, 0, 0, 0);
	}

}

void CCApplication::setAnimationInterval(double interval)
{
	//TODO do something else
	m_nAnimationInterval = interval*1000.0f;
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
	//TODO
	return kLanguageEnglish;
}

NS_CC_END;
