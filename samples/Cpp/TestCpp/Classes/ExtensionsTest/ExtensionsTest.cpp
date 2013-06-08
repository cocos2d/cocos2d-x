#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
#include "NetworkTest/HttpClientTest.h"
#endif
#include "TableViewTest/TableViewTestScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "NetworkTest/WebSocketTest.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
#include "EditBoxTest/EditBoxTest.h"
#endif

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct {
	const char *name;
	std::function<void(CCObject* sender)> callback;
} g_extensionsTests[] = {
	{ "NotificationCenterTest", [](CCObject* sender) { runNotificationCenterTest(); }
	},
	{ "CCControlButtonTest", [](CCObject *sender){
		CCControlSceneManager* pManager = CCControlSceneManager::sharedControlSceneManager();
		CCScene* pScene = pManager->currentControlScene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}},
	{ "CocosBuilderTest", [](CCObject *sender) {
		TestScene* pScene = new CocosBuilderTestScene();
		if (pScene)
		{
			pScene->runThisTest();
			pScene->release();
		}
	}},
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
	{ "HttpClientTest", [](CCObject *sender){ runHttpClientTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{ "WebSocketTest", [](CCObject *sender){ runWebSocketTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
	{ "EditBoxTest", [](CCObject *sender){ runEditBoxTest();}
	},
#endif
	{ "TableViewTest", [](CCObject *sender){ runTableViewTest();}
	},
};

static const int g_maxTests = sizeof(g_extensionsTests) / sizeof(g_extensionsTests[0]);

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
    for (int i = 0; i < g_maxTests; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(g_extensionsTests[i].name, g_extensionsTests[i].callback);
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        pMenu->addChild(pItem, kItemTagBasic + i);
    }

    addChild(pMenu);
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
