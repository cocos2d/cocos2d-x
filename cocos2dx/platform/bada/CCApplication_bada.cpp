#include "CCApplication_bada.h"

#include "CCDirector.h"
#include "Gbk_Unicode.h"


using namespace Osp::App;
using namespace Osp::System;


NS_CC_BEGIN;

static CCApplication * s_pApplication = NULL;
static long long s_nAnimationInterval = 0;

CCApplication::CCApplication()
{
	CCLog("CCApplication constructor...");
	s_pApplication = this;
}

CCApplication::~CCApplication()
{
	s_pApplication = NULL;
}

CCApplication::Orientation CCApplication::setOrientation(CCApplication::Orientation orientation)
{
    // swap width and height
    CCEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pView)
    {
        return (Orientation)pView->setDeviceOrientation(orientation);
    }
    return (Orientation)CCDirector::sharedDirector()->getDeviceOrientation();
}

CCRect CCApplication::statusBarFrame(CCRect * rect)
{
    if (rect)
    {
        // bada doesn't have status bar.
        *rect = CCRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
/// Implement static class member
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(s_pApplication);
    return *s_pApplication;
}

void CCApplication::setAnimationInterval(double interval)
{
    s_nAnimationInterval = (long long)(interval * 1000 * 1000);
}

bool CCApplication::OnAppInitializing(AppRegistry& appRegistry)
{
	InitGbkUnicodeTable("/Res/gbk_uni_tb.dat");
	if (applicationDidFinishLaunching())
		return true;
	return false;
}


bool CCApplication::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	ReleaseGbkUnicodeTable();
	return true;
}


void CCApplication::OnForeground(void)
{

}


void CCApplication::OnBackground(void)
{

}


void CCApplication::OnLowMemory(void)
{
}


void CCApplication::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}



NS_CC_END;
