/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
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
    g_pAnalytics->setSessionContinueMillis(10000);

    const char* sdkVer = g_pAnalytics->getSDKVersion();
    CCLog("SDK version : %s", sdkVer);

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
    //pDirector->setDisplayStats(true);

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
