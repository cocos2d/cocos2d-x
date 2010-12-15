#include "CCXApplication_bada.h"

#include "CCDirector.h"
#include "Gbk_Unicode.h"


using namespace Osp::App;
using namespace Osp::System;


namespace   cocos2d {

static CCXApplication * s_pApplication = NULL;

CCXApplication::CCXApplication()
{
	AppLog("CCXApplication constructor...");
	s_pApplication = this;
}

CCXApplication::~CCXApplication()
{
	s_pApplication = NULL;
}

ccDeviceOrientation CCXApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
{
	// swap width and height
	CCXEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
	if (pView)
	{
		return (ccDeviceOrientation)pView->setDeviceOrientation(eOritation);
	}
	return CCDirector::sharedDirector()->getDeviceOrientation();
}

CGRect CCXApplication::statusBarFrame()
{
	CGRect rc;
	return rc;
}

//////////////////////////////////////////////////////////////////////////
/// Implement static class member
//////////////////////////////////////////////////////////////////////////
CCXApplication * CCXApplication::sharedApplication()
{
	return s_pApplication;
}


bool CCXApplication::OnAppInitializing(AppRegistry& appRegistry)
{
	InitGbkUnicodeTable("/Res/gbk_uni_tb.dat");
	if (applicationDidFinishLaunching())
		return true;
	return false;
}


bool CCXApplication::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	ReleaseGbkUnicodeTable();
	return true;
}


void CCXApplication::OnForeground(void)
{

}


void CCXApplication::OnBackground(void)
{

}


void CCXApplication::OnLowMemory(void)
{
}


void CCXApplication::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}



}
