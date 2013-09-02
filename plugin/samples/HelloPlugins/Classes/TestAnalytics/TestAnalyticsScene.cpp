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
#include "TestAnalyticsScene.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_LOG_EVENT_ID = 0,
    TAG_LOG_EVENT_ID_KV,
    TAG_LOG_ONLINE_CONFIG,
    TAG_LOG_EVENT_ID_DURATION,
    TAG_LOG_EVENT_BEGIN,
    TAG_LOG_EVENT_END,
    TAG_MAKE_ME_CRASH
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"OnlineConfig",        TAG_LOG_ONLINE_CONFIG},
    {"LogEvent-eventId"   , TAG_LOG_EVENT_ID},
    {"LogEvent-eventId-kv", TAG_LOG_EVENT_ID_KV},
    {"LogEvent-eventId-Duration", TAG_LOG_EVENT_ID_DURATION},
    {"LogEvent-Begin", TAG_LOG_EVENT_BEGIN},
    {"LogEvent-End", TAG_LOG_EVENT_END},
    {"MakeMeCrash", TAG_MAKE_ME_CRASH}
};

Scene* TestAnalytics::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestAnalytics *layer = TestAnalytics::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestAnalytics::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _pluginAnalytics = NULL;
    loadPlugins();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestAnalytics::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );
    this->addChild(pMenu, 1);

    float yPos = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        LabelTTF* label = LabelTTF::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestAnalytics::eventMenuCallback, this));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        yPos = visibleSize.height - 35*i - 100;
        pMenuItem->setPosition( Point(visibleSize.width / 2, yPos));
    }

    std::string strName = _pluginAnalytics->getPluginName();
    std::string strVer = _pluginAnalytics->getSDKVersion();
    char ret[256] = { 0 };
    sprintf(ret, "Plugin : %s, Ver : %s", strName.c_str(), strVer.c_str());
    LabelTTF* pLabel = LabelTTF::create(ret, "Arial", 18, Size(visibleSize.width, 0), TextHAlignment::CENTER);
    pLabel->setPosition(Point(visibleSize.width / 2, yPos - 80));
    addChild(pLabel);

    return true;
}

void TestAnalytics::onExit()
{
    unloadPlugins();
}

void TestAnalytics::eventMenuCallback(Object* pSender)
{
    MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;

    switch (pMenuItem->getTag())
    {
    case TAG_LOG_EVENT_ID:
        {
            _pluginAnalytics->logEvent("click");
            _pluginAnalytics->logEvent("music");
        }
        break;
    case TAG_LOG_EVENT_ID_KV:
        {
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            _pluginAnalytics->logEvent("music", &paramMap);
        }
        break;
    case TAG_LOG_ONLINE_CONFIG:
        {
            PluginParam param("abc");
            log("Online config = %s", _pluginAnalytics->callStringFuncWithParam("getConfigParams", &param, NULL).c_str());
        }
        break;
    case TAG_LOG_EVENT_ID_DURATION:
        {
            PluginParam event1("book");
            PluginParam dura1(12000);
            _pluginAnalytics->callFuncWithParam("logEventWithDuration", &event1, &dura1, NULL);

            PluginParam event2("book");
            PluginParam dura2(12000);
            PluginParam label("chapter1");
            _pluginAnalytics->callFuncWithParam("logEventWithDurationLabel", &event2, &dura2, &label, NULL);

            PluginParam event3("music");
            PluginParam dura3(2330000);
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            PluginParam mapValue(paramMap);
            _pluginAnalytics->callFuncWithParam("logEventWithDurationParams", &event3, &dura3, &mapValue, NULL);
        }
        break;
    case TAG_LOG_EVENT_BEGIN:
        {
            _pluginAnalytics->logTimedEventBegin("music");

            PluginParam event1("music");
            PluginParam label1("one");
            _pluginAnalytics->callFuncWithParam("logTimedEventWithLabelBegin", &event1, &label1, NULL);

            PluginParam event2("music");
            PluginParam label2("flag0");
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            PluginParam mapValue(paramMap);
            _pluginAnalytics->callFuncWithParam("logTimedKVEventBegin", &event2, &label2, &mapValue, NULL);

            PluginParam event3("music-kv");
            _pluginAnalytics->callFuncWithParam("logTimedEventBeginWithParams", &event3, &mapValue, NULL);
        }
        break;
    case TAG_LOG_EVENT_END:
        {
            _pluginAnalytics->logTimedEventEnd("music");

            PluginParam event1("music");
            PluginParam label1("one");
            _pluginAnalytics->callFuncWithParam("logTimedEventWithLabelEnd", &event1, &label1, NULL);

            PluginParam event2("music");
            PluginParam label2("flag0");
            _pluginAnalytics->callFuncWithParam("logTimedKVEventEnd", &event2, &label2, NULL);

            PluginParam event3("music-kv");
            _pluginAnalytics->callFuncWithParam("logTimedEventEnd", &event3, NULL);
        }
        break;
    case TAG_MAKE_ME_CRASH:
        {
            char* pNull = NULL;
            *pNull = 0;
        }
        break;
    default:
        break;
    }
}

void TestAnalytics::loadPlugins()
{
    LanguageType langType = Application::getInstance()->getCurrentLanguage();
    
    std::string umengKey  = "";
    std::string flurryKey = "";
    std::string pluginName = "";
    std::string strAppKey = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    umengKey  = UMENG_KEY_IOS;
    flurryKey = FLURRY_KEY_IOS;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    umengKey  = UMENG_KEY_ANDROID;
    flurryKey = FLURRY_KEY_ANDROID;
#endif
    
    if (LanguageType::CHINESE == langType)
    {
        pluginName = "AnalyticsUmeng";
        strAppKey = umengKey;
    }
    else
    {
        pluginName = "AnalyticsFlurry";
        strAppKey = flurryKey;
    }
    
    _pluginAnalytics = dynamic_cast<ProtocolAnalytics*> (PluginManager::getInstance()->loadPlugin(pluginName.c_str()));

    _pluginAnalytics->setDebugMode(true);
    _pluginAnalytics->startSession(strAppKey.c_str());
    _pluginAnalytics->setCaptureUncaughtException(true);
    _pluginAnalytics->setSessionContinueMillis(10000);
    
    const char* sdkVer = _pluginAnalytics->getSDKVersion().c_str();
    log("SDK version : %s", sdkVer);
    
    _pluginAnalytics->callFuncWithParam("updateOnlineConfig", NULL);
    
    PluginParam pParam1(true);
    _pluginAnalytics->callFuncWithParam("setReportLocation", &pParam1, NULL);
    
	_pluginAnalytics->callFuncWithParam("logPageView", NULL);
    
	PluginParam pParam2("1.1");
	_pluginAnalytics->callFuncWithParam("setVersionName", &pParam2, NULL);
    
	PluginParam pParam3(20);
	_pluginAnalytics->callFuncWithParam("setAge", &pParam3, NULL);
    
	PluginParam pParam4(1);
	_pluginAnalytics->callFuncWithParam("setGender", &pParam4, NULL);
    
	PluginParam pParam5("123456");
	_pluginAnalytics->callFuncWithParam("setUserId", &pParam5, NULL);
    
	PluginParam pParam6(false);
	_pluginAnalytics->callFuncWithParam("setUseHttps", &pParam6, NULL);

}

void TestAnalytics::unloadPlugins()
{
    if (NULL != _pluginAnalytics) {
        _pluginAnalytics->stopSession();

        std::string pluginName = _pluginAnalytics->getPluginName();
        PluginManager::getInstance()->unloadPlugin(pluginName.c_str());
        _pluginAnalytics = NULL;
    }
}

void TestAnalytics::menuBackCallback(Object* pSender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
