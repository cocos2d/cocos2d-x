#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
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
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("Lua Tests", Rect(0,0,900,640));
        director->setOpenGLView(glview);
    }

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

//    auto screenSize = glview->getFrameSize();
//
//    auto designSize = Size(480, 320);
//
//    if (screenSize.height > 320)
//    {
//        auto resourceSize = Size(960, 640);
//        director->setContentScaleFactor(resourceSize.height/designSize.height);
//    }
//
//    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);

    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    LuaStack* stack = pEngine->getLuaStack();
    register_assetsmanager_test_sample(stack->getLuaState());
#endif

//    pEngine->executeScriptFile("src/controller.lua");
    
    LuaStack *pStack = pEngine->getLuaStack();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    const char * mainLuaFile = "scripts/main.lua";
#else
    const char * mainLuaFile = "/Users/zhujunfeng/quick-x-3/tests/lua-tests/scripts/main.lua";
#endif
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // load framework
    pStack->loadChunksFromZIP("res/framework_precompiled.zip");
    
    // set script path
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("scripts/main.lua");
#else
    // load framework
//    if (m_projectConfig.isLoadPrecompiledFramework())
//    {
//        const string precompiledFrameworkPath = SimulatorConfig::sharedDefaults()->getPrecompiledFrameworkPath();
//        pStack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
//    }
    
    // set script path
//    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_projectConfig.getScriptFileRealPath().c_str());
    std::string path = CCFileUtils::getInstance()->fullPathForFilename(mainLuaFile);
#endif
    
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/\\");
    if (p != path.npos)
    {
        const std::string dir = path.substr(0, p);
        pStack->addSearchPath(dir.c_str());
        
        p = dir.find_last_of("/\\");
        if (p != dir.npos)
        {
            pStack->addSearchPath(dir.substr(0, p).c_str());
        }
    }
    
    std::string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    pEngine->executeString(env.c_str());
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());

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
