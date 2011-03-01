#include "AppDelegate.h"

#include "cocos2d.h"
[! if CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

[! endif]
#include "HelloWorldScene.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
[! if CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
    SimpleAudioEngine::end();
[! endif]
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCXEGLView * pMainWnd = new CCXEGLView();
        CCX_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("[!output PROJECT_NAME]"), 320, 480));

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCXEGLView::sharedOpenGLView());

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
[! if CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
[! endif]
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
[! if CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
[! endif]
}
