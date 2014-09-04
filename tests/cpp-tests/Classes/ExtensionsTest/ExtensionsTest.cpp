#include "ExtensionsTest.h"
#include "../testResource.h"
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include "NetworkTest/HttpClientTest.h"
#endif
#include "TableViewTest/TableViewTestScene.h"

#include "CocoStudioArmatureTest/ArmatureScene.h"
#include "CocoStudioActionTimelineTest/ActionTimelineTestScene.h"
#include "CocoStudioComponentsTest/ComponentsTestScene.h"
#include "CocoStudioSceneTest/SceneEditorTest.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) 
#include "NetworkTest/WebSocketTest.h"
#include "NetworkTest/SocketIOTest.h"
#endif


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct {
	const char *name;
	std::function<void(Ref* sender)> callback;
} g_extensionsTests[] = {
	{ "NotificationCenterTest", [](Ref* sender) { runNotificationCenterTest(); }
	},
	{ "CCControlButtonTest", [](Ref *sender){
		ControlSceneManager* pManager = ControlSceneManager::sharedControlSceneManager();
		auto scene = pManager->currentControlScene();
		Director::getInstance()->replaceScene(scene);
	}},
	{ "CocosBuilderTest", [](Ref *sender) {
		auto scene = new (std::nothrow) CocosBuilderTestScene();
		if (scene)
		{
			scene->runThisTest();
			scene->release();
		}
	}},
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
	{ "HttpClientTest", [](Ref *sender){ runHttpClientTest();}
	},
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	{ "WebSocketTest", [](Ref *sender){ runWebSocketTest();}
	},
	{ "SocketIOTest", [](Ref *sender){ runSocketIOTest();}
	},
#endif

	{ "TableViewTest", [](Ref *sender){ runTableViewTest();}
	},
	{ "CocoStudioArmatureTest", [](Ref *sender) { ArmatureTestScene *scene = new (std::nothrow) ArmatureTestScene();
	                                       scene->runThisTest();
	                                       scene->release();
	}
	},
    { "CocoStudioActionTimelineTest", [](Ref *sender) { ActionTimelineTestScene *scene = new (std::nothrow) ActionTimelineTestScene();
    scene->runThisTest();
    scene->release();
    }
    },
    { "CocoStudioComponentsTest", [](Ref *sender) { runComponentsTestLayerTest(); }
    },
	{ "CocoStudioSceneTest", [](Ref *sender) { SceneEditorTestScene *scene = new (std::nothrow) SceneEditorTestScene();
	                                       scene->runThisTest();
	                                       scene->release();
 }
	},
};

static const int g_maxTests = sizeof(g_extensionsTests) / sizeof(g_extensionsTests[0]);

static Vec2 s_tCurPos = Vec2::ZERO;

////////////////////////////////////////////////////////
//
// ExtensionsMainLayer
//
////////////////////////////////////////////////////////
void ExtensionsMainLayer::onEnter()
{
    Layer::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( Vec2::ZERO );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        auto pItem = MenuItemFont::create(g_extensionsTests[i].name, g_extensionsTests[i].callback);
        pItem->setPosition(Vec2(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(ExtensionsMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(ExtensionsMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(ExtensionsMainLayer::onMouseScroll, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    addChild(_itemMenu);
}


void ExtensionsMainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);

    _beginPos = touch->getLocation();    
}

void ExtensionsMainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);

    auto touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;

    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }

    if (nextPos.y > ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(0, ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height));
        return;
    }

    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

void ExtensionsMainLayer::onMouseScroll(Event* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    float nMoveY = mouseEvent->getScrollY() * 6;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(0, ((g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// ExtensionsTestScene
//
////////////////////////////////////////////////////////

void ExtensionsTestScene::runThisTest()
{
    auto layer = new (std::nothrow) ExtensionsMainLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}


