#include "AppDelegate.h"

#include "cocos2d.h"
#include "tests/controller.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The tests is designed as HVGA.
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("cocos2d: tests"), 480, 320));

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        // Android doesn't need to do anything.

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The tests is designed as HVGA.
        CCEGLView* pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320 ,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_  
        // on wophone emulator, we copy resources files to Work7/NEWPLUS/TDA_DATA/Data folder instead of zip file
        cocos2d::CCFileUtils::setResource("TestCocos2dx.zip");
        CocosDenshion::SimpleAudioEngine::setResource("TestCocos2dx.zip");
#endif

#endif
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
		CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationLandscapeLeft);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

		// Initialize OpenGLView instance, that release by CCDirector when application terminate.
		// The HelloWorld is designed as HVGA.
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd
				|| ! pMainWnd->Create("cocos2d: tests", 480, 320, 480, 320));

		//set the base resource folder pay attention to add "/"
		CCFileUtils::setResourcePath("../Resources/");

#endif  // CC_PLATFORM_LINUX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)

		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(this, 480, 320));
		pMainWnd->setDeviceOrientation(Osp::Ui::ORIENTATION_LANDSCAPE);
		CCFileUtils::setResourcePath("/Res/");

#endif  // CC_PLATFORM_BADA

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(1024, 600));
		CCFileUtils::setResourcePath("app/native/Resources");
#endif // CC_PLATFORM_QNX

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // sets opengl landscape mode
    // tests set device orientation in RootViewController.mm
    // pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
    pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

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
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
