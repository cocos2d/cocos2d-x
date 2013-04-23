#include "AppDelegate.h"
#include "PlayerStatus.h"
#include "MainSceneHelper.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "generated/jsb_cocos2dx_auto.hpp"
#include "generated/jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_extension_manual.h"
#include "cocos2d_specifics.hpp"
#include "js_bindings_chipmunk_registration.h"
#include "js_bindings_ccbreader.h"
#include "js_bindings_system_registration.h"
#include "jsb_opengl_registration.h"


char *_js_log_buf_ccbuilder = NULL;

USING_NS_CC;
using namespace CocosDenshion;
CCScene *mainScene;

AppDelegate::AppDelegate(): isRetina(false), isIPhone(false)
{
}

AppDelegate::~AppDelegate()
{
    CCScriptEngineManager::sharedManager()->purgeSharedManager();
}


bool runMainScene() {
    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    mainScene = PlayerStatus::loadMainScene("StatusLayer.ccbi");
    if(CCDirector::sharedDirector()->getRunningScene() != NULL) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, mainScene, transitionColor));
    } else {
        CCDirector::sharedDirector()->runWithScene(CCTransitionFade::create(0.5f, mainScene, transitionColor));
    }
    return true;
}

void handle_ccb_run() {
    CCFileUtils::sharedFileUtils()->purgeCachedEntries();
    CCFileUtils::sharedFileUtils()->loadFilenameLookupDictionaryFromFile("fileLookup.plist");
    ScriptingCore::getInstance()->runScript("main.js");
}

void handle_connected() {
  CCBHelper::setStatusMessage("Connected!");
}

void handle_set_orient(bool isPortrait) {
  CCLOG("ORIENTATION HALF IMPLEMENTED");
}

void handle_set_message(const char* msg) {
    CCBHelper::setInstructionsMessage(msg);
}

void handle_set_status(const char* msg) {
    CCBHelper::setStatusMessage(msg);
}

void handle_disconnected() {
  CCBHelper::setStatusMessage("Disconnected");
}

void handle_ccb_stop() {
    runMainScene();
}

void sendLogMsg(const char *msg);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

void cocos2d::CCLog(const char * pszFormat, ...)
{
    printf("Cocos2d: ");
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
    sendLogMsg(szBuf);
}
#endif

extern "C" {


const char * getCCBDirectoryPath();
    
bool AppDelegate::applicationDidFinishLaunching()
{

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);

    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize = CCSizeMake(320, 480);
    CCSize resourceSize = CCSizeMake(320, 480);
    
    std::vector<std::string> resDirOrders;
    std::string res;
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    

    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published files iOS");        
        searchPaths.insert(searchPaths.begin(), getCCBDirectoryPath());

        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        if (screenSize.height > 1024)
        {
            res = "iPad";
            designSize = CCSizeMake(768, 1024);
            resourceSize = CCSizeMake(1536, 2048);
            resDirOrders.push_back("resources-ipadhd");
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
            isIPhone = false;
            isRetina = true;
        }
        else if (screenSize.height > 960)
        {
            res = "iPad";
            designSize = CCSizeMake(768, 1024);
            resourceSize = CCSizeMake(768, 1024);
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
            isIPhone = false;
            isRetina = false;
        }
        else if (screenSize.height > 480)
        {
            res = "iPhone";
            resourceSize = CCSizeMake(640, 960);
            resDirOrders.push_back("resources-iphonehd");
            resDirOrders.push_back("resources-iphone");
            isIPhone = true;
            isRetina = true;
        }
        else
        {
            res = "iPhone";
            resourceSize = CCSizeMake(320, 480);
            resDirOrders.push_back("resources-iphone");
            isIPhone = true;
            isRetina = false;
        }
        
    }
    else if (platform == kTargetAndroid || platform == kTargetWindows)
    {
        
        if (screenSize.height > 960)
        {
            res = "xlarge";
            resourceSize = CCSizeMake(1280, 1920);
            resDirOrders.push_back("resources-xlarge");
            resDirOrders.push_back("resources-large");
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else if (screenSize.height > 720)
        {
            res = "large";
            resourceSize = CCSizeMake(640, 960);
            resDirOrders.push_back("resources-large");
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else if (screenSize.height > 480)
        {
            res = "medium";
            resourceSize = CCSizeMake(480, 720);
            resDirOrders.push_back("resources-medium");
            resDirOrders.push_back("resources-small");
        }
        else
        {
            res = "small";
            resourceSize = CCSizeMake(320, 480);
            resDirOrders.push_back("resources-small");
        }
    }
    
    CCFileUtils *pFileUtils = CCFileUtils::sharedFileUtils();
    pFileUtils->setSearchResolutionsOrder(resDirOrders);
    
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
 
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), pFileUtils->getWritablePath());
    pFileUtils->setSearchPaths(searchPaths);

    PlayerStatus::setDeviceResolution(res);
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(JSB_register_opengl);
    sc->start();

    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    runMainScene();
}



void handle_signal(int signal) {
    static int internal_state = 0;
    ScriptingCore* sc = ScriptingCore::getInstance();
    // should start everything back
    CCDirector* director = CCDirector::sharedDirector();
    if (director->getRunningScene()) {
        director->popToRootScene();
    } else {
        CCPoolManager::sharedPoolManager()->finalize();
        if (internal_state == 0) {
            //sc->dumpRoot(NULL, 0, NULL);
            sc->start();
            internal_state = 1;
        } else {
            sc->runScript("hello.js");
            internal_state = 0;
        }
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

}
