#include "AppDelegate.h"

[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

[! endif]
#include "HelloWorldScene.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
    SimpleAudioEngine::end();
[! endif]
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // init the window
    if (!(m_pMainWnd = new CCEGLView()) ||
        ! m_pMainWnd->Create(L"cocos2d-win32", 320, 480) )
    {
        CC_SAFE_DELETE(m_pMainWnd);
        return false;
    }

    // init director
    CCDirector * pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(m_pMainWnd);
    pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
    // pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
    pDirector->setDisplayFPS(true);


    CCScene * pScene = HelloWorld::scene();

    pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
[! endif]
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
[! endif]
}
