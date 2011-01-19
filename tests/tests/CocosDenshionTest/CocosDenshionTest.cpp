#include "CocosDenshionTest.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define LINE_SPACE          40

CocosDenshionTest::CocosDenshionTest()
: m_pItmeMenu(NULL),
m_tBeginPos(CGPointZero)
{
	std::string testItems[] = {
		"preload background music",
		"play background music",
		"stop background music",
		"pause background music",
		"resume background music",
		"rewind background music",
		"is background music playing",
		"preload effect",
		"play effect",
		"stop effect",
		"unload effect"
	};

	// add menu items for tests
	m_pItmeMenu = CCMenu::menuWithItems(NULL);
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	m_nTestCount = sizeof(testItems) / sizeof(testItems[0]);

	for (int i = 0; i < m_nTestCount; ++i)
	{
		CCLabelTTF* label = CCLabelTTF::labelWithString(testItems[i].c_str(), "Arial", 24);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(CocosDenshionTest::menuCallback));

		m_pItmeMenu->addChild(pMenuItem, i + 10000);
		pMenuItem->setPosition( CGPointMake( s.width / 2, (s.height - (i + 1) * LINE_SPACE) ));
	}

	m_pItmeMenu->setContentSize(CGSizeMake(s.width, (m_nTestCount + 1) * LINE_SPACE));
	m_pItmeMenu->setPosition(CGPointZero);
	addChild(m_pItmeMenu);

	setIsTouchEnabled(true);
}

CocosDenshionTest::~CocosDenshionTest()
{
}

void CocosDenshionTest::onExit()
{
	CCLayer::onExit();

	SimpleAudioEngine::sharedEngine()->end();
}

void CocosDenshionTest::menuCallback(NSObject * pSender)
{
	// get the userdata, it's the index of the menu item clicked
	CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;

	switch(nIdx)
	{
	// preload background music
	case 0:
		break;
	// play background music
	case 1:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mid");
		break;
	// stop background music
	case 2:
		break;
	// pause background music
	case 3:
		break;
	// resume background music
	case 4:
		break;
	// rewind background music
	case 5:
		break;
	// is background music playing
	case 6:
		break;
	// preload effect
	case 7:
		break;
	// play effect
	case 8:
		break;
	// stop effect
	case 9:
		break;
	// unload effect
	case 10:
		break;
	}
}

void CocosDenshionTest::ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent)
{
	NSSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->locationInView( touch->view() );	
	m_tBeginPos = CCDirector::sharedDirector()->convertToGL( m_tBeginPos );
}

void CocosDenshionTest::ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent)
{
	NSSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CGPoint touchLocation = touch->locationInView( touch->view() );	
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CGPoint curPos  = m_pItmeMenu->getPosition();
	CGPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
	CGSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (nextPos.y < 0.0f)
	{
		m_pItmeMenu->setPosition(CGPointZero);
		return;
	}

	if (nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - winSize.height))
	{
		m_pItmeMenu->setPosition(ccp(0, ((m_nTestCount + 1)* LINE_SPACE - winSize.height)));
		return;
	}

	m_pItmeMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
}

void CocosDenshionTestScene::runThisTest()
{
	CCLayer* pLayer = new CocosDenshionTest();
	addChild(pLayer);
	pLayer->autorelease();

	CCDirector::sharedDirector()->replaceScene(this);
}