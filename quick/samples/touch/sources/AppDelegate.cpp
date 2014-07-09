
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "support/CCNotificationCenter.h"
#include "CCLuaEngine.h"
#include <string>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // register lua engine
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    CCLuaStack *pStack = pEngine->getLuaStack();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // load framework
    pStack->loadChunksFromZIP("res/framework_precompiled.zip");

    // set script path
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("scripts/main.lua");
#else
    // load framework
    if (m_projectConfig.isLoadPrecompiledFramework())
    {
        const string precompiledFrameworkPath = SimulatorConfig::sharedDefaults()->getPrecompiledFrameworkPath();
        pStack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
    }

    // set script path
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_projectConfig.getScriptFileRealPath().c_str());
#endif

    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/\\");
    if (p != path.npos)
    {
        const string dir = path.substr(0, p);
        pStack->addSearchPath(dir.c_str());

        p = dir.find_last_of("/\\");
        if (p != dir.npos)
        {
            pStack->addSearchPath(dir.substr(0, p).c_str());
        }
    }

    string env = "__LUA_STARTUP_FILE__=\"";
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
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_BACKGROUND_EVENT");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ENTER_FOREGROUND_EVENT");
}

void AppDelegate::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
}
