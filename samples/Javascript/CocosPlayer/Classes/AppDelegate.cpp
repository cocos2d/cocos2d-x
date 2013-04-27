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
#include "platform/CCDevice.h"



static bool firstTime = true;

static bool isPortraitApp = true;
char *_cocosplayer_log_buf = NULL;


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
    
    if(CCDirector::sharedDirector()->getRunningScene() != NULL && CCDirector::sharedDirector()->getRunningScene() != mainScene) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, mainScene, transitionColor));
    } else if(CCDirector::sharedDirector()->getRunningScene() != NULL) {
        
    }else {
        CCDirector::sharedDirector()->runWithScene(CCTransitionFade::create(0.5f, mainScene, transitionColor));
    }
    return true;
}

void handle_ccb_run() {
    CCFileUtils::sharedFileUtils()->purgeCachedEntries();
    SimpleAudioEngine::sharedEngine()->end();
    CCFileUtils::sharedFileUtils()->loadFilenameLookupDictionaryFromFile("fileLookup.plist");
    ScriptingCore::getInstance()->runScript("main.js");
}

bool handle_eval_script(const char *script, jsval *out) {
    ScriptingCore::getInstance()->evalString(script, out);
    return true;
}


void handle_connected() {
    CCBHelper::setStatusMessage("Connected!");
}

void resetCocosApp();

void initViews(CCSize designSize) {
    (CCScriptEngineManager::sharedManager())->removeScriptEngine();
    resetCocosApp();
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
}

static void setViewValues(CCEGLView *pView, CCSize frameSize, CCSize designSize) {
    CCFileUtils::sharedFileUtils()->purgeCachedEntries();
    ((AppDelegate *)CCApplication::sharedApplication())->initGameView();
}

void handle_set_orient(bool isPortrait) {
    cocos2d::CCEGLView* pView = CCEGLView::sharedOpenGLView();
    if (pView != NULL)
    {
        CCSize frameSize = pView->getFrameSize();
        CCSize designSize = pView->getDesignResolutionSize();
        if (((frameSize.width > frameSize.height && isPortrait))
            || (frameSize.width < frameSize.height && !isPortrait)) {
            isPortraitApp = isPortrait;
            pView->setFrameSize(frameSize.height, frameSize.width);
            setViewValues(pView, frameSize, designSize);
        }
    }
}

void openEditBox();
void updatePairingLabel(const char * label) {
    if(!label) {
        PlayerStatus::pairingLabel = "";
    } else {
        PlayerStatus::pairingLabel = label;
    }
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
    SimpleAudioEngine::sharedEngine()->end();
    runMainScene();
}

void sendLogMsg(const char *msg);


void cocosPlayerNetworkLog(const char * pszFormat, ...)
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

void cocosplayer_js_log(const char *format, ...) {
    if (_cocosplayer_log_buf == NULL) {
        _cocosplayer_log_buf = (char *)calloc(sizeof(char), kMaxLogLen+1);
    }
    va_list vl;
    va_start(vl, format);
    int len = vsnprintf(_cocosplayer_log_buf, kMaxLogLen, format, vl);
    va_end(vl);
    if (len) {
        cocosPlayerNetworkLog("CocosPlayer: %s\n", _cocosplayer_log_buf);
    }
}

JSBool JS_cocosPlayerLog(JSContext* cx, uint32_t argc, jsval *vp)
{
    if (argc > 0) {
        JSString *string = NULL;
        JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
        if (string) {
            JSStringWrapper wrapper(string);
            cocosplayer_js_log((char *)wrapper);
        }
    }
    return JS_TRUE;
}


static void register_CocosPlayer(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

    JS_DefineFunction(cx, obj, "_cocosplayerLog", JS_cocosPlayerLog, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}

extern "C" {
    
    
    const char * getCCBDirectoryPath();
    
    
    static void setResolutionSizes(bool isTablet, bool isRetina, bool isPortrait) {
        CCSize designSize, resourceSize;
        if(isTablet && isPortrait) {
            designSize = CCSizeMake(768, 1024);
            if(isRetina) resourceSize = CCSizeMake(1536, 2048);
            else resourceSize = CCSizeMake(768, 1024);
        } else if(isTablet) {
            designSize = CCSizeMake(1024, 768);
            if(isRetina) resourceSize = CCSizeMake(2048, 1536);
            else resourceSize = CCSizeMake(1024, 768);
        } else if(isPortrait) {
            designSize = CCSizeMake(320, 480);
            if(isRetina) resourceSize = CCSizeMake(640, 960);
            else resourceSize = CCSizeMake(320, 480);
        } else {
            designSize = CCSizeMake(480, 320);
            if(isRetina) resourceSize = CCSizeMake(960, 640);
            else resourceSize = CCSizeMake(480, 320);            
        }
        
        CCDirector::sharedDirector()->setContentScaleFactor(resourceSize.width/designSize.width);
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
    }
    
    void AppDelegate::initGameView() {
    
    // initialize director
        CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);
    
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        if(!isPortraitApp) {
            screenSize = CCSizeMake(screenSize.height, screenSize.width);
        }
        
    std::vector<std::string> resDirOrders;
    std::string res;
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    
    
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published files iOS");
        searchPaths.insert(searchPaths.begin(), getCCBDirectoryPath());
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        if (screenSize.height > 1136)
        {
            res = "iPad";
            setResolutionSizes(true, true, isPortraitApp);
            resDirOrders.push_back("resources-ipadhd");
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
            isIPhone = false;
            isRetina = true;
            cocos2d::extension::CCBReader::setResolutionScale(2);
        } else if(screenSize.height > 1024) {
            res = "iPhone";
            setResolutionSizes(false, true, isPortraitApp);
            resDirOrders.push_back("resources-iphonehd");
            resDirOrders.push_back("resources-iphone");
            isIPhone = true;
            isRetina = true;
        }
        else if (screenSize.height > 960)
        {
            res = "iPad";
            setResolutionSizes(true, false, isPortraitApp);
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
            isIPhone = false;
            isRetina = false;
            cocos2d::extension::CCBReader::setResolutionScale(2);
            
        }
        else if (screenSize.height > 480)
        {
            res = "iPhone";
            setResolutionSizes(false, true, isPortraitApp);
            resDirOrders.push_back("resources-iphonehd");
            resDirOrders.push_back("resources-iphone");
            isIPhone = true;
            isRetina = true;
        }
        else
        {
            res = "iPhone";
            setResolutionSizes(false, false, isPortraitApp);
            resDirOrders.push_back("resources-iphone");
            isIPhone = true;
            isRetina = false;
        }
        
    }
    else if (platform == kTargetAndroid || platform == kTargetWindows)
    {
        int dpi = -1;
        dpi = CCDevice::getDPI();
        
        if(dpi > 300) { // retina
            if (screenSize.height > 1920) {
                res = "xlarge";
                setResolutionSizes(true, true, isPortraitApp);
                resDirOrders.push_back("resources-xlarge");
                resDirOrders.push_back("resources-large");
                resDirOrders.push_back("resources-medium");
                resDirOrders.push_back("resources-small");
            } else {
                res = "large";
                setResolutionSizes(false, true, isPortraitApp);
                resDirOrders.push_back("resources-large");
                resDirOrders.push_back("resources-medium");
                resDirOrders.push_back("resources-small");
            }
        } else { // non retina
            if (screenSize.height > 960)
            {
                res = "large";
                setResolutionSizes(true, false, isPortraitApp);
                resDirOrders.push_back("resources-large");
                resDirOrders.push_back("resources-medium");
                resDirOrders.push_back("resources-small");
                cocos2d::extension::CCBReader::setResolutionScale(2);
            }
            else if (screenSize.height > 768)
            {
                res = "medium";
                setResolutionSizes(true, false, isPortraitApp);
                resDirOrders.push_back("resources-medium");
                resDirOrders.push_back("resources-small");
            }
            else if (screenSize.height > 480)
            {
                res = "small";
                setResolutionSizes(false, false, isPortraitApp);
                resDirOrders.push_back("resources-small");
            }
            else
            {
                setResolutionSizes(false, false, isPortraitApp);
                res = "xsmall";
                resDirOrders.push_back("resources-xsmall");
            }
            
        }
    }
    
    CCFileUtils *pFileUtils = CCFileUtils::sharedFileUtils();
    pFileUtils->setSearchResolutionsOrder(resDirOrders);
    
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), pFileUtils->getWritablePath());
    pFileUtils->setSearchPaths(searchPaths);
    
    PlayerStatus::setDeviceResolution(res);
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
}
    
    bool AppDelegate::applicationDidFinishLaunching()
    {
        
        initGameView();
        ScriptingCore* sc = ScriptingCore::getInstance();
        sc->addRegisterCallback(register_all_cocos2dx);
        sc->addRegisterCallback(register_all_cocos2dx_extension);
        sc->addRegisterCallback(register_cocos2dx_js_extensions);
        sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
        sc->addRegisterCallback(register_CCBuilderReader);
        sc->addRegisterCallback(jsb_register_system);
        sc->addRegisterCallback(jsb_register_chipmunk);
        sc->addRegisterCallback(JSB_register_opengl);
        sc->addRegisterCallback(register_CocosPlayer);
        sc->start();
        
        CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
        CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
        if(firstTime) {
            runMainScene();
            firstTime = false;
        } else {
            handle_ccb_run();
        }
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
