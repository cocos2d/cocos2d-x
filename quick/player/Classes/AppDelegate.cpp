#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Runtime.h"
#include "ConfigParser.h"
#include "lua_module_register.h"

#include "native/CCNative.h"
#include "network/CCHTTPRequest.h"
#include "luabinding/cocos2dx_extra_luabinding.h"
#include "luabinding/lua_cocos2dx_extension_filter_auto.hpp"
#include "luabinding/lua_cocos2dx_extension_nanovg_auto.hpp"
#include "luabinding/lua_cocos2dx_extension_nanovg_manual.hpp"
#include "luabinding/HelperFunc_luabinding.h"
#include "lua_extensions/lua_extensions_more.h"
#include "PlayerProtocol.h"

using namespace CocosDenshion;

USING_NS_CC;
USING_NS_CC_EXTRA;
using namespace std;

static void quick_module_register(lua_State *L)
{
    luaopen_lua_extensions_more(L);

    lua_getglobal(L, "_G");
    if (lua_istable(L, -1))//stack:...,_G,
    {
        register_all_quick_manual(L);
        luaopen_cocos2dx_extra_luabinding(L);
        register_all_cocos2dx_extension_filter(L);
        register_all_cocos2dx_extension_nanovg(L);
        register_all_cocos2dx_extension_nanovg_manual(L);
        luaopen_HelperFunc_luabinding(L);
    }
    lua_pop(L, 1);
}

//
AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    if (_project.getDebuggerType() == kCCLuaDebuggerCodeIDE)
    {
        initRuntime();
        {
            ConfigParser::getInstance()->readConfig();
        }
    }
    
    // initialize director
    auto director = Director::getInstance();
    director->setProjection(Director::Projection::_2D);
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	director->startAnimation();

    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    // If you want to use Quick-Cocos2d-X, please uncomment below code
    quick_module_register(L);

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
    
    
    StartupCall *call = StartupCall::create(this);
    if (_project.getDebuggerType() == kCCLuaDebuggerLDT)
    {
        auto scene = Scene::create();
        auto label = Label::createWithSystemFont("WAITING FOR CONNECT TO DEBUGGER...", "Arial", 32);
        const Size winSize = director->getWinSize();
        label->setPosition(winSize.width / 2, winSize.height / 2);
        scene->addChild(label);
        director->runWithScene(scene);
        scene->runAction(CallFunc::create(bind(&StartupCall::startup, *call)));
    }
    else
    {
        call->startup();
    }
    
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


void AppDelegate::setProjectConfig(const ProjectConfig& project)
{
    _project = project;
}

// ----------------------------------------

StartupCall *StartupCall::create(AppDelegate *app)
{
    StartupCall *call = new StartupCall();
    call->_app = app;
    call->autorelease();
    return call;
}

void StartupCall::startup()
{
    auto engine = LuaEngine::getInstance();
    auto stack = engine->getLuaStack();
    
    const ProjectConfig &project = _app->_project;
    
    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(project.getScriptFileRealPath().c_str());
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
        stack->addSearchPath(workdir.c_str());
        FileUtils::getInstance()->addSearchPath(workdir);
    }
    
    // connect debugger
    if (project.getDebuggerType() != kCCLuaDebuggerNone)
    {
        //        stack->connectDebugger(project.getDebuggerType(), NULL, 0, NULL, workdir.c_str());
    }
    
    // load framework
    if (project.isLoadPrecompiledFramework())
    {
        const string precompiledFrameworkPath = SimulatorConfig::getInstance()->getPrecompiledFrameworkPath();
        stack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
    }
    
    // Code IDE
    if (project.getDebuggerType() == kCCLuaDebuggerCodeIDE)
    {
        startRuntime();
        return ;
    }
    
    // load script
    string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    engine->executeString(env.c_str());
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    engine->executeScriptFile(path.c_str());
    
    // track start event
    trackLaunchEvent();
}

void StartupCall::trackEvent(const char *eventName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    const char *platform = "win";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    const char *platform = "mac";
#else
    const char *platform = "UNKNOWN";
#endif
    
    HTTPRequest *request = HTTPRequest::createWithUrl(NULL,
                                                      "http://www.google-analytics.com/collect",
                                                      kCCHTTPRequestMethodPOST);
    request->addPOSTValue("v", "1");
    request->addPOSTValue("tid", "UA-55061270-1");
    request->addPOSTValue("cid", Native::getOpenUDID().c_str());
    request->addPOSTValue("t", "event");
    
    request->addPOSTValue("an", "player");
    request->addPOSTValue("av", cocos2dVersion());
    
    request->addPOSTValue("ec", platform);
    request->addPOSTValue("ea", eventName);
    
    request->start();
}

void StartupCall::trackLaunchEvent()
{
    trackEvent("launch");
    
    const char *trackUrl = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    trackUrl = "http://c.kp747.com/k.js?id=c19010907080b2d7";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    trackUrl = "http://c.kp747.com/k.js?id=c1e060d0a0e0e207";
#endif
    
    if (trackUrl)
    {
        HTTPRequest *request = HTTPRequest::createWithUrl(NULL, trackUrl, kCCHTTPRequestMethodGET);
        request->start();
    }
}
