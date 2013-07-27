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
#include "NetworkTest/SocketIOTest.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
#include "EditBoxTest/EditBoxTest.h"
#endif

#include "Scale9SpriteTest/Scale9SpriteTest.h"

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
    { "Scale9SpriteTest", [](Object* sender) {
            S9SpriteTestScene* scene = new S9SpriteTestScene();
            if (scene)
            {
                scene->runThisTest();
                scene->release();
            }
        }
	},
	{ "CCControlButtonTest", [](Object *sender){
		ControlSceneManager* pManager = ControlSceneManager::sharedControlSceneManager();
		Scene* scene = pManager->currentControlScene();
		Director::getInstance()->replaceScene(scene);
	}},
	{ "CocosBuilderTest", [](Object *sender) {
		TestScene* scene = new CocosBuilderTestScene();
		if (scene)
		{
			scene->runThisTest();
			scene->release();
		}
	}},
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
	{ "HttpClientTest", [](Object *sender){ runHttpClientTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{ "WebSocketTest", [](Object *sender){ runWebSocketTest();}
	},
	{ "SocketIOTest", [](Object *sender){ runSocketIOTest();}
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
    { "ArmatureTest", [](Object *sender) { ArmatureTestScene *scene = new ArmatureTestScene();
                                             scene->runThisTest();
                                             scene->release();
                                        }
    },
};

static const int g_maxTests = sizeof(g_extensionsTests) / sizeof(g_extensionsTests[0]);

static Point s_tCurPos = Point::ZERO;

////////////////////////////////////////////////////////
//
// ExtensionsMainLayer
//
////////////////////////////////////////////////////////
void ExtensionsMainLayer::onEnter()
{
    Layer::onEnter();
    
    Size s = Director::getInstance()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( Point::ZERO );
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

void ExtensionsMainLayer::ccTouchesBegan(Set  *touches, Event  *event)
{
    Touch* touch = static_cast<Touch*>(touches->anyObject());

    _beginPos = touch->getLocation();    
}

void ExtensionsMainLayer::ccTouchesMoved(Set  *touches, Event  *event)
{
    Touch* touch = static_cast<Touch*>(touches->anyObject());

    Point touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;

    Point curPos  = _itemMenu->getPosition();
    Point nextPos = Point(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Point::ZERO);
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
    Layer* layer = new ExtensionsMainLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}


