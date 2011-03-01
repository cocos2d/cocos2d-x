#include "AppDelegate.h"

#include "cocos2d.h"
#include "tests/controller.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The tests is designed as HVGA.
        CCXEGLView * pMainWnd = new CCXEGLView();
        CCX_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("cocos2d: tests"), 320, 480));

#endif  // CCX_PLATFORM_WIN32

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCXEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

	// sets landscape mode
	pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
    pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

#if  (CCX_TARGET_PLATFORM == CCX_PLATFORM_ANDROID)
	CCFileUtils::setRelativePath("assets");
#endif

    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
}
