#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	//pDirector->setProjection(kCCDirectorProjection2D);
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
	if (screenSize.height > 768)
	{
		CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
        pDirector->setContentScaleFactor(1536.0f/kDesignResolutionSize_height);
	}
    else if (screenSize.height > 320)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ipad");
        pDirector->setContentScaleFactor(768.0f/kDesignResolutionSize_height);
    }
	else
    {
		CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
        pDirector->setContentScaleFactor(320.0f/kDesignResolutionSize_height);
    }
	
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(kDesignResolutionSize_width, kDesignResolutionSize_height, kResolutionNoBorder);
    
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
