#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "lua_assetsmanager_test_sample.h"

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
    auto pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    auto screenSize = EGLView::getInstance()->getFrameSize();
    
    auto designSize = Size(480, 320);
    
    auto pFileUtils = FileUtils::getInstance();
    
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(960, 640);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("hd");
        pFileUtils->setSearchPaths(searchPaths);
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    
    EGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    
    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    LuaStack* stack = pEngine->getLuaStack();
    register_assetsmanager_test_sample(stack->getLuaState());
#endif
    
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), "Images");
    searchPaths.insert(searchPaths.begin(), "cocosbuilderRes");
    if (screenSize.height > 320)
    {
        searchPaths.insert(searchPaths.begin(), "hd/scenetest/LoadSceneEdtiorFileTest");
    }
    else
    {
        searchPaths.insert(searchPaths.begin(), "scenetest/LoadSceneEdtiorFileTest");
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
    searchPaths.push_back("TestCppResources");
    searchPaths.push_back("script");
#endif
    FileUtils::getInstance()->setSearchPaths(searchPaths);

    pEngine->executeScriptFile("luaScript/controller.lua");
    
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
