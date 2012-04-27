#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"

enum
{
    MAX_COUNT = 3,
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static const std::string testsName[MAX_COUNT] = 
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "TextureWatcherTest"
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
    for (int i = 0; i < MAX_COUNT; ++i)
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
    case 0:
        runNotificationCenterTest();
        break;
    case 1:
        {
            CCControlSceneManager* pManager = CCControlSceneManager::sharedControlSceneManager();
            CCScene* pScene = pManager->currentControlScene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        break;
    case 2:
        {
            static bool s_bOpened = false;
            s_bOpened = !s_bOpened;
            CCTextureWatcher::sharedTextureWatcher()->setDisplayWatcher(s_bOpened);
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
