#include "BugsTest.h"
#include "Bug-350.h"
#include "Bug-422.h"
#include "Bug-458/Bug-458.h"
#include "Bug-624.h"
#include "Bug-886.h"
#include "Bug-899.h"
#include "Bug-914.h"
#include "Bug-1159.h"
#include "Bug-1174.h"
#include "Bug-Child.h"

#define TEST_BUG(__bug__)									\
{															\
	Scene* scene = Scene::create();					\
	Bug##__bug__##Layer* layer = new Bug##__bug__##Layer();	\
	layer->init();                                         \
	scene->addChild(layer);                               \
	Director::getInstance()->replaceScene(scene);     \
	layer->autorelease();                                  \
}

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 5432,
};

static Vec2 s_tCurPos = Vec2::ZERO;

struct {
	const char *test_name;
	std::function<void(Ref*)> callback;
} g_bugs[] = {
    { "Bug-Child", [](Ref* sender){Director::getInstance()->replaceScene(BugChild::scene());} },
	{ "Bug-350", [](Ref* sender){ TEST_BUG(350)} },
	{ "Bug-422", [](Ref* sender){ TEST_BUG(422)} },
	{ "Bug-458", [](Ref* sender){ TEST_BUG(458)} },
	{ "Bug-624", [](Ref* sender){ TEST_BUG(624)} },
	{ "Bug-886", [](Ref* sender){ TEST_BUG(886)} },
	{ "Bug-899", [](Ref* sender){ TEST_BUG(899)} },
	{ "Bug-914", [](Ref* sender){ TEST_BUG(914)} },
	{ "Bug-1159", [](Ref* sender){ TEST_BUG(1159)} },
	{ "Bug-1174", [](Ref* sender){ TEST_BUG(1174)} },
};

static const int g_maxitems = sizeof(g_bugs) / sizeof(g_bugs[0]);


////////////////////////////////////////////////////////
//
// BugsTestMainLayer
//
////////////////////////////////////////////////////////
void BugsTestMainLayer::onEnter()
{
    Layer::onEnter();

    auto s = Director::getInstance()->getWinSize();
    _itmeMenu = Menu::create();
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxitems; ++i)
    {
        auto pItem = MenuItemFont::create(g_bugs[i].test_name, g_bugs[i].callback);
        pItem->setPosition(Vec2(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itmeMenu->addChild(pItem, kItemTagBasic + i);
    }

    _itmeMenu->setPosition(s_tCurPos);
    addChild(_itmeMenu);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BugsTestMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BugsTestMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BugsTestMainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    _beginPos = touches[0]->getLocation();
}

void BugsTestMainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touchLocation = touches[0]->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;

    auto curPos  = _itmeMenu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);
    auto winSize = Director::getInstance()->getWinSize();
    if (nextPos.y < 0.0f)
    {
        _itmeMenu->setPosition(Vec2::ZERO);
        return;
    }

    if (nextPos.y > ((g_maxitems + 1)* LINE_SPACE - winSize.height))
    {
        _itmeMenu->setPosition(Vec2(0, ((g_maxitems + 1)* LINE_SPACE - winSize.height)));
        return;
    }

    _itmeMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// BugsTestBaseLayer
//
////////////////////////////////////////////////////////
void BugsTestBaseLayer::onEnter()
{
    Layer::onEnter();

    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    auto pMainItem = MenuItemFont::create("Back", CC_CALLBACK_1(BugsTestBaseLayer::backCallback, this));
    pMainItem->setPosition(Vec2(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menu = Menu::create(pMainItem, NULL);
    menu->setPosition( Vec2::ZERO );
    addChild(menu);
}

void BugsTestBaseLayer::backCallback(Ref* sender)
{
//    Director::getInstance()->enableRetinaDisplay(false);
    auto scene = new BugsTestScene();
    scene->runThisTest();
    scene->autorelease();
}

////////////////////////////////////////////////////////
//
// BugsTestScene
//
////////////////////////////////////////////////////////
void BugsTestScene::runThisTest()
{
    auto layer = new BugsTestMainLayer();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
