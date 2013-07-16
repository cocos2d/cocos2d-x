#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "Lua_extensions_CCB.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Lua_web_socket.h"
#endif
#include "LuaOpengl.h"
#include "LuaScrollView.h"
#include "LuaScriptHandlerMgr.h"

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
    // initialize director
    Director *pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    Size screenSize = EGLView::getInstance()->getFrameSize();
    
    Size designSize = Size(480, 320);
    
    FileUtils* pFileUtils = FileUtils::getInstance();
    
    if (screenSize.height > 320)
    {
        Size resourceSize = Size(960, 640);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("hd");
        pFileUtils->setSearchPaths(searchPaths);
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    
    EGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedHeight);
    
    // register lua engine
    LuaEngine* pEngine = LuaEngine::defaultEngine();
    ScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    
    LuaStack *pStack = pEngine->getLuaStack();
    lua_State *tolua_s = pStack->getLuaState();
    tolua_extensions_ccb_open(tolua_s);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    tolua_web_socket_open(tolua_s);
#endif
    tolua_opengl_open(tolua_s);
    tolua_scroll_view_open(tolua_s);
    tolua_script_handler_mgr_open(tolua_s);
    
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.push_back("cocosbuilderRes");

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
    searchPaths.push_back("TestCppResources");
    searchPaths.push_back("script");
#endif
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    pEngine->extendLuaObject();
    pEngine->executeScriptFile("luaScript/controller.lua");
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
