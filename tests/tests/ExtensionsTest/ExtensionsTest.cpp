#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    TEST_NOTIFICATIONCENTER = 0,
    TEST_CCCONTROLBUTTON,
    TEST_TEXTUREWATCHER,
    TEST_COCOSBUILDER,
    TEST_MAX_COUNT,
};

static const std::string testsName[TEST_MAX_COUNT] = 
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "TextureWatcherTest",
    "CocosBuilderTest",
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

    CCMenu* pMenu = CCMenu::menuWithItems(NULL);
    pMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < TEST_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::itemWithString(testsName[i].c_str(), this,
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
    case TEST_TEXTUREWATCHER:
        {
            static bool s_bOpened = false;
            s_bOpened = !s_bOpened;
            CCTextureWatcher::sharedTextureWatcher()->setDisplayWatcher(s_bOpened);
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
