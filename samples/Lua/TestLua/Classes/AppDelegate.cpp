#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "Lua_extensions_CCB.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Lua_web_socket.h"
#endif

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
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    CCLuaStack *pStack = pEngine->getLuaStack();
    pStack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
    lua_State *tolua_s = pStack->getLuaState();
    tolua_extensions_ccb_open(tolua_s);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    
    pStack = pEngine->getLuaStack();
    tolua_s = pStack->getLuaState();
    tolua_web_socket_open(tolua_s);
#endif
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize designSize = CCSizeMake(480, 320);
    std::vector<std::string> searchPaths;
    searchPaths.push_back("cocosbuilderRes");
    if (screenSize.height > 320)
    {
        CCSize resourceSize = CCSizeMake(960, 640);
        searchPaths.insert(searchPaths.begin(), "ccs-res");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/ArmatureComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/AttributeComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/BackgroundComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/EffectComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/ParticleComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/SpriteComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/TmxMapComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/UIComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd/scenetest/TriggerTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/hd");
        searchPaths.insert(searchPaths.begin(),  "hd");
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.insert(searchPaths.begin(), "ccs-res");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/ArmatureComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/AttributeComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/BackgroundComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/EffectComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/ParticleComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/SpriteComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/TmxMapComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/UIComponentTest");
        searchPaths.insert(searchPaths.begin(), "ccs-res/scenetest/TriggerTest");
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
    searchPaths.push_back("TestCppResources");
    searchPaths.push_back("script");
#endif
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    pEngine->executeScriptFile("luaScript/controller.lua");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}