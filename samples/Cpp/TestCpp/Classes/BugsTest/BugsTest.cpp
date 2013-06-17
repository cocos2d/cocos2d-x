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

#define TEST_BUG(__bug__)									\
{															\
	CCScene* pScene = CCScene::create();					\
	Bug##__bug__##Layer* pLayer = new Bug##__bug__##Layer();	\
	pLayer->init();                                         \
	pScene->addChild(pLayer);                               \
	CCDirector::sharedDirector()->replaceScene(pScene);     \
	pLayer->autorelease();                                  \
}

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 5432,
};

static CCPoint s_tCurPos = CCPointZero;

struct {
	const char *test_name;
	std::function<void(CCObject*)> callback;
} g_bugs[] = {
	{ "Bug-350", [](CCObject* sender){ TEST_BUG(350)} },
	{ "Bug-422", [](CCObject* sender){ TEST_BUG(422)} },
	{ "Bug-458", [](CCObject* sender){ TEST_BUG(458)} },
	{ "Bug-624", [](CCObject* sender){ TEST_BUG(624)} },
	{ "Bug-886", [](CCObject* sender){ TEST_BUG(886)} },
	{ "Bug-899", [](CCObject* sender){ TEST_BUG(899)} },
	{ "Bug-914", [](CCObject* sender){ TEST_BUG(914)} },
	{ "Bug-1159", [](CCObject* sender){ TEST_BUG(1159)} },
	{ "Bug-1174", [](CCObject* sender){ TEST_BUG(1174)} },
};

static const int g_maxitems = sizeof(g_bugs) / sizeof(g_bugs[0]);


////////////////////////////////////////////////////////
//
// BugsTestMainLayer
//
////////////////////////////////////////////////////////
void BugsTestMainLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pItmeMenu = CCMenu::create();
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxitems; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(g_bugs[i].test_name, g_bugs[i].callback);
        pItem->setPosition(ccp(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        m_pItmeMenu->addChild(pItem, kItemTagBasic + i);
    }

    m_pItmeMenu->setPosition(s_tCurPos);
    addChild(m_pItmeMenu);
    setTouchEnabled(true);
}

void BugsTestMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation();    
}

void BugsTestMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - m_tBeginPos.y;

    CCPoint curPos  = m_pItmeMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (nextPos.y < 0.0f)
    {
        m_pItmeMenu->setPosition(CCPointZero);
        return;
    }

    if (nextPos.y > ((g_maxitems + 1)* LINE_SPACE - winSize.height))
    {
        m_pItmeMenu->setPosition(ccp(0, ((g_maxitems + 1)* LINE_SPACE - winSize.height)));
        return;
    }

    m_pItmeMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// BugsTestBaseLayer
//
////////////////////////////////////////////////////////
void BugsTestBaseLayer::onEnter()
{
    CCLayer::onEnter();

    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    CCMenuItemFont* pMainItem = CCMenuItemFont::create("Back", CC_CALLBACK_1(BugsTestBaseLayer::backCallback, this));
    pMainItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    CCMenu* pMenu = CCMenu::create(pMainItem, NULL);
    pMenu->setPosition( CCPointZero );
    addChild(pMenu);
}

void BugsTestBaseLayer::backCallback(CCObject* pSender)
{
//    CCDirector::sharedDirector()->enableRetinaDisplay(false);
    BugsTestScene* pScene = new BugsTestScene();
    pScene->runThisTest();
    pScene->autorelease();
}

////////////////////////////////////////////////////////
//
// BugsTestScene
//
////////////////////////////////////////////////////////
void BugsTestScene::runThisTest()
{
    CCLayer* pLayer = new BugsTestMainLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
