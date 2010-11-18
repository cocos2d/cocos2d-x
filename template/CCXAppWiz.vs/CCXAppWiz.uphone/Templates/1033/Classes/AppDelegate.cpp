#include "AppDelegate.h"

#include "HelloWorldScene.h"
#include "Resource.h"
extern const AppResourceEntry [!output PROJECT_NAME]ResourceEntry;

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
	if (!(m_pMainWnd = new CCXEGLView(this)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
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

    // set the resource path
    CCFileUtils::setResourcePath("/NEWPLUS/TDA_DATA/Data/cocos2d_tests/");

    // set the Images ResInfo (name and ResID)
    // CCFileUtils::setResourceInfo(ResInfo, sizeof(ResInfo) / sizeof(T_ResourceInfo));

    CCScene * pScene = HelloWorld::scene();

	pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
