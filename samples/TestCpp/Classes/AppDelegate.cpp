#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
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

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    if (winSize.width > 1024)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024*2, 768*2, kResolutionShowAll);
    }
    else if (winSize.width > 960)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ipad");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionShowAll);
    }
    else if (winSize.width > 480)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480*2, 320*2, kResolutionShowAll);
    }
    else
    {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320, kResolutionShowAll);
    }
    

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    CCScene * pScene = CCScene::create();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
