#include "AppDelegate.h"

#include "cocos2d.h"
USING_NS_CC;

#include "HelloWorldScene.h"

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

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = HelloWorld::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
