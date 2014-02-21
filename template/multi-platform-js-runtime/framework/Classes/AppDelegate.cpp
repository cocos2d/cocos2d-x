#include "AppDelegate.h"

#include "cocosbuilder/js_bindings_ccbreader.h"
#include "SimpleAudioEngine.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"
#include "Runtime.h"

USING_NS_CC;
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
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("Test Lua", Rect(0,0,900,640));
		director->setOpenGLView(glview);
	}

    // turn on display FPS
    director->setDisplayStats(true);
	auto designSize = Size(480, 320);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_all_cocos2dx_builder);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->addRegisterCallback(jsb_register_chipmunk);
    
	startRuntime();
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
