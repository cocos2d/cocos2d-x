#include "AppDelegate.h"

#include "cocos2d.h"
#include "tests/controller.h"

USING_NS_CC;

// static void TimerCallback1(Int32 nTimerId, UInt32 uUserData);
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // init the window
    if (! ccxApplication::sharedApplication().initInstance())
    {
        return false;
    }

// TODO: Remove this code to ccxApplication::initInstance()

// #if (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)
//     if (!(m_pMainWnd = new CCXEGLView(this)) || 
//         ! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
// #elif (CCX_TARGET_PLATFORM == CCX_PLATFORM_IPHONE)
//     if (!(m_pMainWnd = new CCXEGLView()))
// #elif (CCX_TARGET_PLATFORM == CCX_PLATFORM_ANDROID)
//     if (!(m_pMainWnd = CCDirector::sharedDirector()->getOpenGLView()))
// #endif
//     {
//         CCX_SAFE_DELETE(m_pMainWnd);
//         return false;
//     }

// #if (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)
//     // set the resource path
//     CCFileUtils::setResourcePath("/NEWPLUS/TDA_DATA/Data/APPS/cocos2d_helloworld/");
// #endif

	// init director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCXEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);


	// sets landscape mode
	pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

    pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

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
