#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::getInstance()->end();
    //CCScriptEngineManager::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = EGLView::createWithSize("Hello Lua", Size(900,640));

    director->setOpenGLView(glview);
    
    glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

    std::string path = FileUtils::getInstance()->fullPathForFilename("hello.lua");
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
