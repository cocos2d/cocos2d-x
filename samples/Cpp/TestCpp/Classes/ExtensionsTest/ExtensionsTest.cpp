#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
#include "NetworkTest/HttpClientTest.h"
#endif
#include "TableViewTest/TableViewTestScene.h"
#include "ComponentsTest/ComponentsTestScene.h"
#include "ArmatureTest/ArmatureScene.h"

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
	std::function<void(Object* sender)> callback;
} g_extensionsTests[] = {
	{ "NotificationCenterTest", [](Object* sender) { runNotificationCenterTest(); }
	},
	{ "CCControlButtonTest", [](Object *sender){
		ControlSceneManager* pManager = ControlSceneManager::sharedControlSceneManager();
		Scene* pScene = pManager->currentControlScene();
		Director::sharedDirector()->replaceScene(pScene);
	}},
	{ "CocosBuilderTest", [](Object *sender) {
		TestScene* pScene = new CocosBuilderTestScene();
		if (pScene)
		{
			pScene->runThisTest();
			pScene->release();
		}
	}},
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
	{ "HttpClientTest", [](Object *sender){ runHttpClientTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{ "WebSocketTest", [](Object *sender){ runWebSocketTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
	{ "EditBoxTest", [](Object *sender){ runEditBoxTest();}
	},
#endif
	{ "TableViewTest", [](Object *sender){ runTableViewTest();}
	},
    { "CommponentTest", [](Object *sender) { runComponentsTestLayerTest(); }
    },
    { "ArmatureTest", [](Object *sender) { ArmatureTestScene *pScene = new ArmatureTestScene();
                                             pScene->runThisTest();
                                             pScene->release();
                                        }
    },
};

static const int g_maxTests = sizeof(g_extensionsTests) / sizeof(g_extensionsTests[0]);

static Point s_tCurPos = PointZero;

////////////////////////////////////////////////////////
//
// ExtensionsMainLayer
//
////////////////////////////////////////////////////////
void ExtensionsMainLayer::onEnter()
{
    Layer::onEnter();
    
    Size s = Director::sharedDirector()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( PointZero );
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        MenuItemFont* pItem = MenuItemFont::create(g_extensionsTests[i].name, g_extensionsTests[i].callback);
        pItem->setPosition(Point(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }

	setTouchEnabled(true);
    
    addChild(_itemMenu);
}

void ExtensionsMainLayer::ccTouchesBegan(Set *pTouches, Event *pEvent)
{
    Touch* touch = static_cast<Touch*>(pTouches->anyObject());

    _beginPos = touch->getLocation();    
}

void ExtensionsMainLayer::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch* touch = static_cast<Touch*>(pTouches->anyObject());

    Point touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;

    Point curPos  = _itemMenu->getPosition();
    Point nextPos = Point(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(PointZero);
        return;
    }

    if (nextPos.y > ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Point(0, ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// ExtensionsTestScene
//
////////////////////////////////////////////////////////

void ExtensionsTestScene::runThisTest()
{
    Layer* pLayer = new ExtensionsMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    Director::sharedDirector()->replaceScene(this);
}


