#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "generated/cocos2dx.hpp"
#include "cocos2d_specifics.hpp"
#include "js_bindings_chipmunk_registration.h"
#include "js_bindings_ccbreader.h"
#include "js_bindings_system_registration.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    CCScriptEngineManager::sharedManager()->purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);


    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

    CCSize designSize = CCSizeMake(320, 480);
    CCSize resourceSize = CCSizeMake(320, 480);
    
//    if (screenSize.height > 1024)
//    {
//        resourceSize = CCSizeMake(1536, 2048);
//        CCFileUtils::sharedFileUtils()->setResourceDirectory("resources-ipadhd");
//    }
//     else if (screenSize.height > 960)
//    {
//        resourceSize = CCSizeMake(768, 1536);
//        CCFileUtils::sharedFileUtils()->setResourceDirectory("resources-ipad");
//    }
//    else
        if (screenSize.height > 480)
    {
        resourceSize = CCSizeMake(640, 960);
        CCFileUtils::sharedFileUtils()->setResourceDirectory("resources-iphonehd");
        
    }
    else
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("resources-iphone");
    }
    
    pDirector->setContentScaleFactor(resourceSize.height/designSize.height);

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(jsb_register_system);
    
    sc->start();

    js_log("RUNNING Main");
    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    ScriptingCore::getInstance()->runScript("main.js");
       
    return true;
}

void handle_signal(int signal) {
    static int internal_state = 0;
    ScriptingCore* sc = ScriptingCore::getInstance();
    // should start everything back
    CCDirector* director = CCDirector::sharedDirector();
    if (director->getRunningScene()) {
        director->popToRootScene();
    } else {
        CCPoolManager::sharedPoolManager()->finalize();
        if (internal_state == 0) {
            //sc->dumpRoot(NULL, 0, NULL);
            sc->start();
            internal_state = 1;
        } else {
            sc->runScript("hello.js");
            internal_state = 0;
        }
    }
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
