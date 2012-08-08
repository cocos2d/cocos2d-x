#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
    
    if (isIpad())
    {
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView().setDesignResolutionSize(960, 640, kResolutionScaleFullScreen);
    }
    else 
    {
        // iphone or other platforms
        
        if (pDirector->enableRetinaDisplay(true))
        {
            // iphone
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        }
        else 
        {
            if (isIos())
            {
                CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
            }
            else 
            {
                CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
                // android or other platform, use hd resource
                CCEGLView::sharedOpenGLView().setDesignResolutionSize(960, 640, kResolutionScaleFullScreen);
            }
        }
    }

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
