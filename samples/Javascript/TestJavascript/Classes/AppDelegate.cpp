#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "generated/jsb_cocos2dx_auto.hpp"
#include "generated/jsb_cocos2dx_extension_auto.hpp"
#include "generated/jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_extension_manual.h"
#include "jsb_cocos2dx_studio_manual.h"
#include "cocos2d_specifics.hpp"
#include "js_bindings_chipmunk_registration.h"
#include "js_bindings_system_registration.h"
#include "jsb_opengl_registration.h"
#include "XMLHTTPRequest.h"
#include "jsb_websocket.h"
#include "js_bindings_ccbreader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    CCScriptEngineManager::purgeSharedManager();
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

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_all_cocos2dx_studio);
    sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    sc->addRegisterCallback(register_jsb_websocket);
    sc->addRegisterCallback(register_CCBuilderReader);

    sc->start();
    
    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    
    CCFileUtils::sharedFileUtils()->addSearchPath("res");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/ArmatureComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/AttributeComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/BackgroundComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/EffectComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/LoadSceneEdtiorFileTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/ParticleComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/SpriteComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/TmxMapComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/UIComponentTest");
    CCFileUtils::sharedFileUtils()->addSearchPath("res/scenetest/TriggerTest");
    
#ifdef JS_OBFUSCATED
    ScriptingCore::getInstance()->runScript("game.js");
#else
#if JSB_ENABLE_DEBUGGER
    ScriptingCore::getInstance()->enableDebugger();
#endif // JSB_ENABLE_DEBUGGER
    ScriptingCore::getInstance()->runScript("tests-boot-jsb.js");
#endif
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
