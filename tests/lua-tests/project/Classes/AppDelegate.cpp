#include "cocos2d.h"
#include "AppDelegate.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "lua_assetsmanager_test_sample.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "lua_test_bindings.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

    
    LuaStack* stack = pEngine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
    
    lua_State* L = stack->getLuaState();
    
    lua_module_register(L);

    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        register_assetsmanager_test_sample(L);
#endif
        register_test_binding(L);
    }
    lua_pop(L, 1);

#if CC_64BITS
    FileUtils::getInstance()->addSearchPath("src/64bit");
#endif
    FileUtils::getInstance()->addSearchPath("src");
    FileUtils::getInstance()->addSearchPath("res");
    pEngine->executeScriptFile("controller.lua");

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
