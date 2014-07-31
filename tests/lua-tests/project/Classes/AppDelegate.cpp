#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "lua_assetsmanager_test_sample.h"
#include "lua_cocos2dx_extension_auto.hpp"
#include "extension/lua_cocos2dx_extension_manual.h"
#include "lua_cocos2dx_cocosbuilder_auto.hpp"
#include "cocosbuilder/lua_cocos2dx_cocosbuilder_manual.h"
#include "lua_cocos2dx_cocosdenshion_auto.hpp"
#include "lua_cocos2dx_studio_auto.hpp"
#include "cocosstudio/lua_cocos2dx_coco_studio_manual.hpp"
#include "lua_cocos2dx_ui_auto.hpp"
#include "ui/lua_cocos2dx_ui_manual.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "lua_cocos2dx_experimental_video_auto.hpp"
#include "ui/lua_cocos2dx_experimental_video_manual.hpp"
#endif
#include "lua_cocos2dx_spine_auto.hpp"
#include "spine/lua_cocos2dx_spine_manual.hpp"
#include "network/lua_extensions.h"
#include "network/Lua_web_socket.h"
#include "network/lua_xml_http_request.h"

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

    registerLuaBindings();
    pEngine->executeScriptFile("DeprecatedEnum.lua");
    pEngine->executeScriptFile("DeprecatedClass.lua");
    pEngine->executeScriptFile("Deprecated.lua");

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

void AppDelegate::registerLuaBindings()
{
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        register_all_cocos2dx_extension(L);
        register_all_cocos2dx_extension_manual(L);
        register_all_cocos2dx_cocosdenshion(L);
        register_all_cocos2dx_cocosbuilder(L);
        register_all_cocos2dx_cocosbuilder_manual(L);
        register_all_cocos2dx_studio(L);
        register_all_cocos2dx_coco_studio_manual(L);
        register_cocos2dx_protectedNode(L);
        register_all_cocos2dx_ui(L);
        register_all_cocos2dx_ui_manual(L);
        register_all_cocos2dx_spine(L);
        register_all_cocos2dx_spine_manual(L);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        luaopen_lua_extensions(L);
#endif
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        tolua_web_socket_open(L);
        register_web_socket_manual(L);
#endif
        register_xml_http_request(L);
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        register_assetsmanager_test_sample(L);
#endif
    
    }
    lua_pop(L, 1);//statck:...

}
