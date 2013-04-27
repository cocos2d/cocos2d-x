#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
[! if CC_USE_LUA]
#include "CCLuaEngine.h"
[! else]
#include "HelloWorldScene.h"
[! endif]
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
[! endif]

USING_NS_CC;

AppDelegate::AppDelegate()
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
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

[! if CC_USE_LUA]
    // register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("hello.lua");
    pEngine->executeScriptFile(path.c_str());

[! else]
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
[! endif]
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
[! endif]
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
[! endif]
}
