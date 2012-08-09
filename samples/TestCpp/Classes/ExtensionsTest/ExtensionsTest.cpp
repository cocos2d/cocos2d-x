#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#include "NetworkTest/HttpClientTest.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_NOTIFICATIONCENTER = 0,
    TEST_CCCONTROLBUTTON,
    TEST_COCOSBUILDER,
    TEST_HTTPCLIENT,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] = 
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "CocosBuilderTest",
    "HttpClientTest",
};

////////////////////////////////////////////////////////
//
// ExtensionsMainLayer
//
////////////////////////////////////////////////////////
void ExtensionsMainLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                    menu_selector(ExtensionsMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        pMenu->addChild(pItem, kItemTagBasic + i);
    }

    addChild(pMenu);
}

void ExtensionsMainLayer::menuCallback(CCObject* pSender)
{
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;

    switch (nIndex)
    {
    case TEST_NOTIFICATIONCENTER:
        {
            runNotificationCenterTest();
        }
        break;
    case TEST_CCCONTROLBUTTON:
        {
            CCControlSceneManager* pManager = CCControlSceneManager::sharedControlSceneManager();
            CCScene* pScene = pManager->currentControlScene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        break;
    case TEST_COCOSBUILDER:
        {
            TestScene* pScene = new CocosBuilderTestScene();
            if (pScene)
            {
                pScene->runThisTest();
                pScene->release();
            }
        }
        break;
    case TEST_HTTPCLIENT:
        {
            runHttpClientTest();
        }
    default:
        break;
    }
}

////////////////////////////////////////////////////////
//
// ExtensionsTestScene
//
////////////////////////////////////////////////////////

void ExtensionsTestScene::runThisTest()
{
    CCLayer* pLayer = new ExtensionsMainLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
