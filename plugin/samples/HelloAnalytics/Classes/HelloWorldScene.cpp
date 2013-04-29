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
#include "HelloWorldScene.h"
#include "PluginManager.h"
#include "AnalyticsFlurry.h"
#include "AnalyticsUmeng.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

extern ProtocolAnalytics* g_pAnalytics;
extern std::string s_strAppKey;

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

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(size.width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    float yPos = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        CCLabelTTF* label = CCLabelTTF::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::eventMenuCallback));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        yPos = size.height - 35*i - 100;
        pMenuItem->setPosition( ccp(size.width / 2, yPos));
    }

    std::string strName = g_pAnalytics->getPluginName();
    std::string strVer = g_pAnalytics->getPluginVersion();
    char ret[256] = { 0 };
    sprintf(ret, "Plugin : %s, Ver : %s", strName.c_str(), strVer.c_str());
    CCLabelTTF* pLabel = CCLabelTTF::create(ret, "Arial", 18, CCSizeMake(size.width, 0), kCCTextAlignmentCenter);
    pLabel->setPosition(ccp(size.width / 2, yPos - 80));
    addChild(pLabel);

    CCLabelTTF* label = CCLabelTTF::create("reload all plugins", "Arial", 24);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::reloadPluginMenuCallback));
    pMenuItem->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pMenuItem, 0);
    pMenuItem->setPosition( ccp(size.width / 2, 0));

    return true;
}

void HelloWorld::reloadPluginMenuCallback(CCObject* pSender)
{
    PluginManager::getInstance()->unloadPlugin("AnalyticsFlurry");
    PluginManager::getInstance()->unloadPlugin("AnalyticsUmeng");

    AppDelegate::loadAnalyticsPlugin();
}

void HelloWorld::eventMenuCallback(CCObject* pSender)
{
    CCMenuItemLabel* pMenuItem = (CCMenuItemLabel*)pSender;
    AnalyticsUmeng* pUmeng = dynamic_cast<AnalyticsUmeng*>(g_pAnalytics);
    AnalyticsFlurry* pFlurry = dynamic_cast<AnalyticsFlurry*>(g_pAnalytics);

    switch (pMenuItem->getTag())
    {
    case TAG_LOG_EVENT_ID:
        {
            g_pAnalytics->logEvent("click");
            g_pAnalytics->logEvent("music");
        }
        break;
    case TAG_LOG_EVENT_ID_KV:
        {
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            g_pAnalytics->logEvent("music", &paramMap);
        }
        break;
    case TAG_LOG_ONLINE_CONFIG:
        {
            if (pUmeng != NULL)
            {
                CCLog("Online config = %s", pUmeng->getConfigParams("abc"));           
            }
            else
            {
                CCLog("Now is not using umeng!");
            }
        }
        break;
    case TAG_LOG_EVENT_ID_DURATION:
        {
            if (pUmeng != NULL)
            {
                pUmeng->logEventWithDuration("book", 12000);
                pUmeng->logEventWithDuration("book", 23000, "chapter1");
                LogEventParamMap paramMap;
                paramMap.insert(LogEventParamPair("type", "popular"));
                paramMap.insert(LogEventParamPair("artist", "JJLin"));
                pUmeng->logEventWithDuration("music", 2330000, &paramMap);
            }
            else
            {
                CCLog("Now is not using umeng!");
            }
        }
        break;
    case TAG_LOG_EVENT_BEGIN:
        {
            g_pAnalytics->logTimedEventBegin("music");

            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));

            if (pUmeng != NULL)
            {
                pUmeng->logTimedEventWithLabelBegin("music", "one");
                pUmeng->logTimedKVEventBegin("music", "flag0", &paramMap);
            }
            else if (pFlurry != NULL)
            {
                pFlurry->logTimedEventBegin("music-kv", &paramMap);
            }
        }
        break;
    case TAG_LOG_EVENT_END:
        {
            g_pAnalytics->logTimedEventEnd("music");
            if (pUmeng != NULL)
            {          
                pUmeng->logTimedEventWithLabelEnd("music", "one");
                pUmeng->logTimedKVEventEnd("music", "flag0");
            }
            else if (pFlurry != NULL)
            {
                pFlurry->logTimedEventEnd("music-kv");
            }
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

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    if (g_pAnalytics)
        g_pAnalytics->stopSession();

    PluginManager::end();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
