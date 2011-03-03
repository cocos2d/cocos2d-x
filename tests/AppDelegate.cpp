#include "AppDelegate.h"
#include "cocos2d.h"
#include "tests/controller.h"

using namespace cocos2d;

// static void TimerCallback1(Int32 nTimerId, UInt32 uUserData);
AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{
#if defined(CCX_PLATFORM_WIN32)
    CCX_SAFE_DELETE(m_pMainWnd);
#endif
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// init the window
#if defined(CCX_PLATFORM_UPHONE)
	if (!(m_pMainWnd = new CCEGLView(this)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
#elif defined(CCX_PLATFORM_WIN32)
	if (!(m_pMainWnd = new CCEGLView()) ||
		! m_pMainWnd->Create(L"cocos2d-win32", 320, 480) )
#elif defined(CCX_PLATFORM_IPHONE)
    if (!(m_pMainWnd = new CCEGLView()))
#elif defined(CCX_PLATFORM_ANDROID)
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

#if defined(CCX_PLATFORM_ANDROID)
	CCFileUtils::setRelativePath("assets");
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
