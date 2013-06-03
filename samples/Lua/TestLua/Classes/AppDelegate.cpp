#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "Lua_extensions_CCB.h"

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
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        
        searchPaths.insert(searchPaths.begin(), "Published-iOS");
        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        if (screenSize.height > 768)
        {// Ipadhd
            searchPaths.insert(searchPaths.begin(),"Published-iOS/resources-ipadhd");
        }
        else if (screenSize.height > 640)
        {// Ipad
            searchPaths.insert(searchPaths.begin(),"Published-iOS/resources-ipad");
        }
        else if (screenSize.height > 320)
        {// Iphone-hd 3.5 and 4.0 inch
            searchPaths.insert(searchPaths.begin(),"Published-iOS/resources-iphonehd");
        }
        else
        {// Iphone
            searchPaths.insert(searchPaths.begin(),"Published-iOS/resources-iphone");
        }
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }
    
    if (platform == kTargetAndroid )
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        
        searchPaths.insert(searchPaths.begin(), "Published-Android");
        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        searchPaths.push_back("Published-Android/resources-xlarge");
        searchPaths.push_back("Published-Android/resources-large");
        searchPaths.push_back("Published-Android/resources-medium");
        searchPaths.push_back("Published-Android/resources-small");
        searchPaths.push_back("Published-Android/resources-xsmall");
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }


    // register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    
    CCLuaStack *pStack = pEngine->getLuaStack();
    lua_State *tolua_s = pStack->getLuaState();
    tolua_extensions_ccb_open(tolua_s);

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
    std::vector<std::string> searchPaths;
    searchPaths.push_back("TestCppResources");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
#endif

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
