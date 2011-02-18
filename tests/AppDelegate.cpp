#include "AppDelegate.h"

#include "cocos2d.h"
#include "tests/controller.h"

USING_NS_CC;

// static void TimerCallback1(Int32 nTimerId, UInt32 uUserData);
AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)
    CCX_SAFE_DELETE(m_pMainWnd);
#endif
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// init the window
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)
    TApplication* pApp = TApplication::GetCurrentApplication();
	if (!(m_pMainWnd = new CCXEGLView(pApp)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,pApp->GetScreenWidth(),pApp->GetScreenHeight())))
#elif (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)
	if (!(m_pMainWnd = new CCXEGLView()) ||
		! m_pMainWnd->Create(L"cocos2d-win32", 320, 480) )
#elif (CCX_TARGET_PLATFORM == CCX_PLATFORM_IPHONE)
    if (!(m_pMainWnd = new CCXEGLView()))
#elif (CCX_TARGET_PLATFORM == CCX_PLATFORM_ANDROID)
    if (!(m_pMainWnd = CCDirector::sharedDirector()->getOpenGLView()))
#else
    #error
#endif
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

#if  (CCX_TARGET_PLATFORM == CCX_PLATFORM_ANDROID)
	CCFileUtils::setRelativePath("assets");
#endif

#if  (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)

#ifndef _TRANZDA_VM_
    CCFileUtils::setResource("TestCocos2dx.zip");
#endif

#endif

    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
}
