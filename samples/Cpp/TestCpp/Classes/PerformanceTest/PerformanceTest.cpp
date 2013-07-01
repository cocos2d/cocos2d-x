#include "PerformanceTest.h"
#include "../testResource.h"
#include "PerformanceNodeChildrenTest.h"
#include "PerformanceParticleTest.h"
#include "PerformanceSpriteTest.h"
#include "PerformanceTextureTest.h"
#include "PerformanceTouchesTest.h"

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
    { "PerformanceNodeChildrenTest", [](Object*sender){runNodeChildrenTest();} },
	{ "PerformanceParticleTest",[](Object*sender){runParticleTest();} },
	{ "PerformanceSpriteTest",[](Object*sender){runSpriteTest();} },
	{ "PerformanceTextureTest",[](Object*sender){runTextureTest();} },
	{ "PerformanceTouchesTest",[](Object*sender){runTouchesTest();} },
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

    Size s = Director::sharedDirector()->getWinSize();

    Menu* pMenu = Menu::create();
    pMenu->setPosition( PointZero );
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_testMax; ++i)
    {
        MenuItemFont* pItem = MenuItemFont::create(g_testsName[i].name, g_testsName[i].callback);
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        pMenu->addChild(pItem, kItemTagBasic + i);
    }

    addChild(pMenu);
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
    MenuItemFont* pMainItem = MenuItemFont::create("Back", CC_CALLBACK_1(PerformBasicLayer::toMainLayer, this));
    pMainItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    Menu* pMenu = Menu::create(pMainItem, NULL);
    pMenu->setPosition( PointZero );

    if (_controlMenuVisible)
    {
        MenuItemImage *item1 = MenuItemImage::create(s_pPathB1, s_pPathB2, CC_CALLBACK_1(PerformBasicLayer::backCallback, this));
        MenuItemImage *item2 = MenuItemImage::create(s_pPathR1, s_pPathR2, CC_CALLBACK_1(PerformBasicLayer::restartCallback, this));
        MenuItemImage *item3 = MenuItemImage::create(s_pPathF1, s_pPathF2, CC_CALLBACK_1(PerformBasicLayer::nextCallback, this));
        item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

        pMenu->addChild(item1, kItemTagBasic);
        pMenu->addChild(item2, kItemTagBasic);
        pMenu->addChild(item3, kItemTagBasic);
    }
    addChild(pMenu);
}

void PerformBasicLayer::toMainLayer(Object* pSender)
{
    PerformanceTestScene* pScene = new PerformanceTestScene();
    pScene->runThisTest();

    pScene->release();
}

void PerformBasicLayer::restartCallback(Object* pSender)
{
    showCurrentTest();
}

void PerformBasicLayer::nextCallback(Object* pSender)
{
    _curCase++;
    _curCase = _curCase % _maxCases;

    showCurrentTest();
}

void PerformBasicLayer::backCallback(Object* pSender)
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
    Layer* pLayer = new PerformanceMainLayer();
    addChild(pLayer);
    pLayer->release();

    Director::sharedDirector()->replaceScene(this);
}
