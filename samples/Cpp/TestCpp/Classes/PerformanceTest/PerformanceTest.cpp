#include "PerformanceTest.h"
#include "../testResource.h"
#include "PerformanceNodeChildrenTest.h"
#include "PerformanceParticleTest.h"
#include "PerformanceSpriteTest.h"
#include "PerformanceTextureTest.h"
#include "PerformanceTouchesTest.h"
#include "PerformanceAllocTest.h"

enum
{
    MAX_COUNT = 6,
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

const std::string testsName[MAX_COUNT] = 
{
    "Perf NodeChildren Test",
    "Perf Particle Test",
    "Perf Sprite Test",
    "Perf Texture Test",
    "Perf Touches Test",
    "Perf Alloc Test",
};

////////////////////////////////////////////////////////
//
// PerformanceMainLayer
//
////////////////////////////////////////////////////////
void PerformanceMainLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition( CCPointZero );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                    menu_selector(PerformanceMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        pMenu->addChild(pItem, kItemTagBasic + i);
    }

    addChild(pMenu);
}

void PerformanceMainLayer::menuCallback(CCObject* pSender)
{
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;

    switch (nIndex)
    {
    case 0:
        runNodeChildrenTest();
        break;
    case 1:
        runParticleTest();
        break;
    case 2:
        runSpriteTest();
        break;
    case 3:
        runTextureTest();
        break;
    case 4:
        runTouchesTest();
        break;
    case 5:
        runAllocPerformanceTest();
        break;
    default:
        break;
    }
}

////////////////////////////////////////////////////////
//
// PerformBasicLayer
//
////////////////////////////////////////////////////////
PerformBasicLayer::PerformBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: m_bControlMenuVisible(bControlMenuVisible)
, m_nMaxCases(nMaxCases)
, m_nCurCase(nCurCase)
{

}

void PerformBasicLayer::onEnter()
{
    CCLayer::onEnter();

    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    CCMenuItemFont* pMainItem = CCMenuItemFont::create("Back", this,
                                                    menu_selector(PerformBasicLayer::toMainLayer));
    pMainItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    CCMenu* pMenu = CCMenu::create(pMainItem, NULL);
    pMenu->setPosition( CCPointZero );

    if (m_bControlMenuVisible)
    {
        CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(PerformBasicLayer::backCallback) );
        CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(PerformBasicLayer::restartCallback) );
        CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(PerformBasicLayer::nextCallback) );
        item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

        pMenu->addChild(item1, kItemTagBasic);
        pMenu->addChild(item2, kItemTagBasic);
        pMenu->addChild(item3, kItemTagBasic);
    }
    addChild(pMenu);
}

void PerformBasicLayer::toMainLayer(CCObject* pSender)
{
    PerformanceTestScene* pScene = new PerformanceTestScene();
    pScene->runThisTest();

    pScene->release();
}

void PerformBasicLayer::restartCallback(CCObject* pSender)
{
    showCurrentTest();
}

void PerformBasicLayer::nextCallback(CCObject* pSender)
{
    m_nCurCase++;
    m_nCurCase = m_nCurCase % m_nMaxCases;

    showCurrentTest();
}

void PerformBasicLayer::backCallback(CCObject* pSender)
{
    m_nCurCase--;
    if( m_nCurCase < 0 )
        m_nCurCase += m_nMaxCases;

    showCurrentTest();
}

////////////////////////////////////////////////////////
//
// PerformanceTestScene
//
////////////////////////////////////////////////////////

void PerformanceTestScene::runThisTest()
{
    CCLayer* pLayer = new PerformanceMainLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
