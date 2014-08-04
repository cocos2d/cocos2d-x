#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "lua_assetsmanager_test_sample.h"
#include "lua_module_register.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    
    LuaStack* stack = pEngine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
    
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        lua_module_register(L);
        register_assetsmanager_test_sample(L);
    }
    lua_pop(L, 1);
    
    pEngine->executeScriptFile("DeprecatedCocos2dClass");
    pEngine->executeScriptFile("DeprecatedCocos2dEnum");
    pEngine->executeScriptFile("DeprecatedCocos2dFunc");
    
    pEngine->executeScriptFile("DeprecatedCocosBuilderClass");
    
    pEngine->executeScriptFile("DeprecatedCocosDenshionClass");
    pEngine->executeScriptFile("DeprecatedCocosDenshionFunc");
    
    pEngine->executeScriptFile("DeprecatedCocoStudioClass");
    pEngine->executeScriptFile("DeprecatedCocoStudioFunc");
    
    pEngine->executeScriptFile("DeprecatedExtensionClass");
    pEngine->executeScriptFile("DeprecatedExtensionEnum");
    pEngine->executeScriptFile("DeprecatedExtensionFunc");
    
    pEngine->executeScriptFile("DeprecatedNetworkClass");
    pEngine->executeScriptFile("DeprecatedNetworkEnum");
    pEngine->executeScriptFile("DeprecatedNetworkFunc");
    
    pEngine->executeScriptFile("DeprecatedNetworkClass");
    pEngine->executeScriptFile("DeprecatedNetworkEnum");
    pEngine->executeScriptFile("DeprecatedNetworkFunc");
    
    pEngine->executeScriptFile("DeprecatedOpenglEnum");
    
    pEngine->executeScriptFile("DeprecatedUIEnum");
    pEngine->executeScriptFile("DeprecatedUIFunc");

    pEngine->executeScriptFile("src/controller.lua");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
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
