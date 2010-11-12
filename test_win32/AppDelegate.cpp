#include "AppDelegate.h"
#include "tests/controller.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{
}

AppDelegate::~AppDelegate()
{
    CCX_SAFE_DELETE(m_pMainWnd);
}


bool AppDelegate::applicationDidFinishLaunching()
{
	// create window
	if (!(m_pMainWnd = new CCXEGLView() || 
        ! m_pMainWnd->Create(L"Cocos2dx-win32", 320, 480) )
	{
        CCX_SAFE_DELETE(m_pMainWnd);
		return false;
	}

	// init director
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(m_pMainWnd);
	pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
	// pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
	pDirector->setDisplayFPS(true);

	CCScene * pScene = CCScene::node();
	CCLayer * pLayer = new TestController();
	pLayer->autorelease();

	pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();
}
