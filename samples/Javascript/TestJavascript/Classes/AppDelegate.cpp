#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_gui_auto.hpp"
#include "jsb_cocos2dx_spine_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "cocostudio/jsb_cocos2dx_studio_manual.h"
#include "gui/jsb_cocos2dx_gui_manual.h"
#include "cocos2d_specifics.hpp"
#include "cocosbuilder/cocosbuilder_specifics.hpp"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "localstorage/js_bindings_system_registration.h"
#include "jsb_opengl_registration.h"
#include "network/XMLHTTPRequest.h"
#include "network/jsb_websocket.h"
#include "cocosbuilder/js_bindings_ccbreader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    ScriptEngineManager::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());

    // JS-Test in Html5 uses 800x450 as design resolution
    EGLView::getInstance()->setDesignResolutionSize(800, 450, ResolutionPolicy::FIXED_HEIGHT);
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    searchPaths.push_back("script");
    
    const char* paths[] = {
        "res",
        "res/scenetest",
        "res/scenetest/ArmatureComponentTest",
        "res/scenetest/AttributeComponentTest",
        "res/scenetest/BackgroundComponentTest",
        "res/scenetest/EffectComponentTest",
        "res/scenetest/LoadSceneEdtiorFileTest",
        "res/scenetest/ParticleComponentTest",
        "res/scenetest/SpriteComponentTest",
        "res/scenetest/TmxMapComponentTest",
        "res/scenetest/UIComponentTest",
        "res/scenetest/TriggerTest",
    };

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    std::string testFolder = "tests/";
    searchPaths.push_back(testFolder);
    
    for (const auto& path : paths)
    {
        searchPaths.push_back(testFolder + path);
    }
#else
    for (const auto& path : paths)
    {
        searchPaths.push_back(path);
    }
#endif
    
    fileUtils->setSearchPaths(searchPaths);

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    sc->addRegisterCallback(register_jsb_websocket);

    sc->addRegisterCallback(register_all_cocos2dx_builder);
    sc->addRegisterCallback(register_CCBuilderReader);

    sc->addRegisterCallback(register_all_cocos2dx_gui);
    sc->addRegisterCallback(register_all_cocos2dx_gui_manual);
    sc->addRegisterCallback(register_all_cocos2dx_studio);
    sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    
    sc->addRegisterCallback(register_all_cocos2dx_spine);
    
    sc->start();
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();
#endif
    
    auto pEngine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
#ifdef JS_OBFUSCATED
    ScriptingCore::getInstance()->runScript("game.js");
#else
    ScriptingCore::getInstance()->runScript("tests-boot-jsb.js");
#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
