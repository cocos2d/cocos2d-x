#include "AppDelegate.h"
#include "cocos2d.h"

#include "HelloWorldScene.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
	// init the window
#if defined(CCX_PLATFORM_UPHONE)
	if (!(m_pMainWnd = new CCXEGLView(this)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
#elif defined(CCX_PLATFORM_WIN32)
	if (!(m_pMainWnd = new CCXEGLView()) ||
		! m_pMainWnd->Create(L"cocos2d-win32", 320, 480) )
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

#if defined(CCX_PLATFORM_UPHONE)
    // set the resource path
    CCFileUtils::setResourcePath("/NEWPLUS/TDA_DATA/Data/cocos2d_tests/");
#endif


    CCScene * pScene = HelloWorld::scene();
	CCLayer * pLayer = CCLayer::node();
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
