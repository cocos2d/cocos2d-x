#include "AppDelegate.h"

#include <vector>
#include <string>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "cocos2d_specifics.hpp"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    ScriptEngineManager::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());
    pDirector->setProjection(Director::Projection::_2D);


    FileUtils::getInstance()->addSearchPath("script");
    
    auto screenSize = EGLView::getInstance()->getFrameSize();

    auto designSize = Size(320, 480);
    auto resourceSize = Size(320, 480);
    
    std::vector<std::string> resDirOrders;
    
    Platform platform = Application::getInstance()->getTargetPlatform();
    if (platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD || platform == Application::Platform::OS_MAC)
    {
        std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published files iOS");
        FileUtils::getInstance()->setSearchPaths(searchPaths);
        if (screenSize.height > 1024)
        {
            resourceSize = Size(1536, 2048);
            resDirOrders.push_back("resources-ipadhd");
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
        }
        else if (screenSize.height > 960)
        {
            resourceSize = Size(768, 1024);
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
        }
        else if (screenSize.height > 480)
        {
            resourceSize = Size(640, 960);
            resDirOrders.push_back("resources-iphonehd");
            resDirOrders.push_back("resources-iphone");
        }
        else
        {
            resourceSize = Size(320, 480);
            resDirOrders.push_back("resources-iphone");
        }
        
    }
    else if (platform == Application::Platform::OS_ANDROID || platform == Application::Platform::OS_WINDOWS)
    {
        if (screenSize.height > 960)
        {
            resourceSize = Size(1280, 1920);
            resDirOrders.push_back("resources-xlarge");
            resDirOrders.push_back("resources-large");
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else if (screenSize.height > 720)
        {
            resourceSize = Size(640, 960);
            resDirOrders.push_back("resources-large");
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else if (screenSize.height > 480)
        {
            resourceSize = Size(480, 720);
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else
        {
            resourceSize = Size(320, 480);
            resDirOrders.push_back("resources-small");
        }
    }
    
    FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);
    
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);

    EGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_all_cocos2dx_builder);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->addRegisterCallback(jsb_register_chipmunk);
    
    sc->start();

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();
#endif
    
    js_log("RUNNING Main");
    auto pEngine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    ScriptingCore::getInstance()->runScript("main.js");
       
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
