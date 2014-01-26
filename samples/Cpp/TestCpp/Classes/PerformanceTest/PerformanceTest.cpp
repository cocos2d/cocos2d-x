#include "PerformanceTest.h"
#include "../testResource.h"
#include "PerformanceNodeChildrenTest.h"
#include "PerformanceParticleTest.h"
#include "PerformanceSpriteTest.h"
#include "PerformanceTextureTest.h"
#include "PerformanceTouchesTest.h"
#include "PerformanceAllocTest.h"
#include "PerformanceLabelTest.h"
#include "PerformanceRendererTest.h"
#include "PerformanceContainerTest.h"
#include "PerformanceEventDispatcherTest.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

struct {
	const char *name;
	std::function<void(Object*)> callback;
} g_testsName[] =
{
    { "Alloc Test", [](Object*sender){runAllocPerformanceTest(); } },
    { "NodeChildren Test", [](Object*sender){runNodeChildrenTest();} },
	{ "Particle Test",[](Object*sender){runParticleTest();} },
	{ "Sprite Perf Test",[](Object*sender){runSpriteTest();} },
	{ "Texture Perf Test",[](Object*sender){runTextureTest();} },
	{ "Touches Perf Test",[](Object*sender){runTouchesTest();} },
    { "Label Perf Test",[](Object*sender){runLabelTest();} },
    { "Renderer Perf Test",[](Object*sender){runRendererTest();} },
    { "Container Perf Test", [](Object* sender ) { runContainerPerformanceTest(); } },
    { "EventDispatcher Perf Test", [](Object* sender ) { runEventDispatcherPerformanceTest(); } },
};

static const int g_testMax = sizeof(g_testsName)/sizeof(g_testsName[0]);

////////////////////////////////////////////////////////
//
// PerformanceMainLayer
//
////////////////////////////////////////////////////////
void PerformanceMainLayer::onEnter()
{
    Layer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    _itemMenu = Menu::create();
    _itemMenu->setPosition( Point::ZERO );
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_testMax; ++i)
    {
        auto pItem = MenuItemFont::create(g_testsName[i].name, g_testsName[i].callback);
        pItem->setPosition(Point(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }

    addChild(_itemMenu);
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(PerformanceMainLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PerformanceMainLayer::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(PerformanceMainLayer::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool PerformanceMainLayer::onTouchBegan(Touch* touches, Event  *event)
{
    _beginPos = touches->getLocation();
    return true;
}
void PerformanceMainLayer::onTouchMoved(Touch* touches, Event  *event)
{
    auto touchLocation = touches->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Point(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Point::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_testMax + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Point(0, ((g_testMax + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
}

void PerformanceMainLayer::onMouseScroll(Event *event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    float nMoveY = mouseEvent->getScrollY() * 6;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Point(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Point::ZERO);
        return;
    }
    
    if (nextPos.y > ((g_testMax + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Point(0, ((g_testMax + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
}

////////////////////////////////////////////////////////
//
// PerformBasicLayer
//
////////////////////////////////////////////////////////
PerformBasicLayer::PerformBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: _controlMenuVisible(bControlMenuVisible)
, _maxCases(nMaxCases)
, _curCase(nCurCase)
{

}

void PerformBasicLayer::onEnter()
{
    Layer::onEnter();

    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    auto pMainItem = MenuItemFont::create("Back", CC_CALLBACK_1(PerformBasicLayer::toMainLayer, this));
    pMainItem->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menu = Menu::create(pMainItem, NULL);
    menu->setPosition( Point::ZERO );

    if (_controlMenuVisible)
    {
        auto item1 = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(PerformBasicLayer::backCallback, this));
        auto item2 = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(PerformBasicLayer::restartCallback, this));
        auto item3 = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(PerformBasicLayer::nextCallback, this));
        item1->setPosition(Point(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(Point(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

        menu->addChild(item1, kItemTagBasic);
        menu->addChild(item2, kItemTagBasic);
        menu->addChild(item3, kItemTagBasic);
    }
    addChild(menu);
}

void PerformBasicLayer::toMainLayer(Object* sender)
{
    auto scene = new PerformanceTestScene();
    scene->runThisTest();

    scene->release();
}

void PerformBasicLayer::restartCallback(Object* sender)
{
    showCurrentTest();
}

void PerformBasicLayer::nextCallback(Object* sender)
{
    _curCase++;
    _curCase = _curCase % _maxCases;

    showCurrentTest();
}

void PerformBasicLayer::backCallback(Object* sender)
{
    _curCase--;
    if( _curCase < 0 )
        _curCase += _maxCases;

    showCurrentTest();
}

////////////////////////////////////////////////////////
//
// PerformanceTestScene
//
////////////////////////////////////////////////////////

void PerformanceTestScene::runThisTest()
{
    auto layer = new PerformanceMainLayer();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
