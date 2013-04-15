#include "AppDelegate.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "PluginManager.h"
#include "AnalyticsFlurry.h"
#include "AnalyticsUmeng.h"

using namespace cocos2d::plugin;
USING_NS_CC;

// The app key of flurry
#define FLURRY_KEY_IOS          "KMGG7CD9WPK2TW4X9VR8"
#define FLURRY_KEY_ANDROID      "SPKFH8KMPGHMMBWRBT5W"
#define UMENG_KEY_IOS           "50d2b18c5270152187000097"
#define UMENG_KEY_ANDROID       ""          // umeng key for android is setted in AndroidManifest.xml

ProtocolAnalytics* g_pAnalytics = NULL;
std::string s_strAppKey = "";

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

void AppDelegate::loadAnalyticsPlugin()
{
    PluginProtocol* pPlugin = NULL;
    ccLanguageType langType = CCApplication::sharedApplication()->getCurrentLanguage();

    std::string umengKey  = "";
    std::string flurryKey = "";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    umengKey  = UMENG_KEY_IOS;
    flurryKey = FLURRY_KEY_IOS;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    umengKey  = UMENG_KEY_ANDROID;
    flurryKey = FLURRY_KEY_ANDROID;
#endif

    if (kLanguageChinese == langType)
    {
        pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsUmeng");
        s_strAppKey = umengKey;
    }
    else
    {
        pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsFlurry");
        s_strAppKey = flurryKey;
    }

    g_pAnalytics = dynamic_cast<ProtocolAnalytics*>(pPlugin);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    loadAnalyticsPlugin();
    g_pAnalytics->setDebugMode(true);
    g_pAnalytics->startSession(s_strAppKey.c_str());
    g_pAnalytics->setCaptureUncaughtException(true);

    AnalyticsUmeng* pUmeng = dynamic_cast<AnalyticsUmeng*>(g_pAnalytics);
    AnalyticsFlurry* pFlurry = dynamic_cast<AnalyticsFlurry*>(g_pAnalytics);
    if (pUmeng != NULL)
    {
        pUmeng->updateOnlineConfig();
        pUmeng->setDefaultReportPolicy(AnalyticsUmeng::REALTIME);
    }

    if (pFlurry != NULL)
    {
        pFlurry->setReportLocation(true);
        pFlurry->logPageView();
        // const char* sdkVersion = pFlurry->getSDKVersion();
        pFlurry->setVersionName("1.1");
        pFlurry->setAge(20);
        pFlurry->setGender(AnalyticsFlurry::MALE);
        pFlurry->setUserId("123456");
        pFlurry->setUseHttps(false);
    }

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    g_pAnalytics->stopSession();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    if (g_pAnalytics)
    {
        g_pAnalytics->startSession(s_strAppKey.c_str());
    }

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
