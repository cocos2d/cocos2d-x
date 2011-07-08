#include "MotionStreakTest.h"
#include "../testResource.h"

CCLayer* nextMotionAction();
CCLayer* backMotionAction();
CCLayer* restartMotionAction();

//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
	MotionStreakTest::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();
  
	// the root object just rotates around
	m_root = CCSprite::spriteWithFile(s_pPathR1);
	addChild(m_root, 1);
	m_root->setPosition( CCPointMake(s.width/2, s.height/2) );
  
	// the target object is offset from root, and the streak is moved to follow it
	m_target = CCSprite::spriteWithFile(s_pPathR1);
	m_root->addChild(m_target);
	m_target->setPosition( CCPointMake(100,0) );

	// create the streak object and add it to the scene
	m_streak = CCMotionStreak::streakWithFade(2, 3, s_streak, 32, 32, ccc4(0,255,0,255) );
	addChild( m_streak );
	// schedule an update on each frame so we can syncronize the streak with the target
	schedule(schedule_selector(MotionStreakTest1::onUpdate));
  
	CCActionInterval* a1 = CCRotateBy::actionWithDuration(2, 360);

	CCAction* action1 = CCRepeatForever::actionWithAction(a1);
	CCActionInterval* motion = CCMoveBy::actionWithDuration(2, CCPointMake(100,0) );
	m_root->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(motion, motion->reverse(), NULL)) ) );
	m_root->runAction( action1 );
}

void MotionStreakTest1::onUpdate(ccTime delta)
{
	m_streak->setPosition( m_target->convertToWorldSpace(CCPointZero) );
}

std::string MotionStreakTest1::title()
{
	return "MotionStreak test 1";
}

//------------------------------------------------------------------
//
// MotionStreakTest2
//
//------------------------------------------------------------------

void MotionStreakTest2::onEnter()
{
	MotionStreakTest::onEnter();

	setIsTouchEnabled(true);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
		
	// create the streak object and add it to the scene
	m_streak = CCMotionStreak::streakWithFade(3, 3, s_streak, 64, 32, ccc4(255,255,255,255) );
	addChild( m_streak );
	
	m_streak->setPosition( CCPointMake(s.width/2, s.height/2) ); 
}

void MotionStreakTest2::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->locationInView( touch->view() );	
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	
	m_streak->setPosition( touchLocation );
}

std::string MotionStreakTest2::title()
{
	return "MotionStreak test";
}

//------------------------------------------------------------------
//
// MotionStreakTest
//
//------------------------------------------------------------------

// enum
// {
// 	IDC_NEXT = 100,
// 	IDC_BACK,
// 	IDC_RESTART
// };

static int sceneIdx = -1; 

#define MAX_LAYER	2

CCLayer* createMotionLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new MotionStreakTest1();
		case 1: return new MotionStreakTest2();
	}

	return NULL;
}

CCLayer* nextMotionAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createMotionLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backMotionAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createMotionLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartMotionAction()
{
	CCLayer* pLayer = createMotionLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


MotionStreakTest::MotionStreakTest(void)
{
}

MotionStreakTest::~MotionStreakTest(void)
{
}

std::string MotionStreakTest::title()
{
	return "No title";
}

void MotionStreakTest::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( CCPointMake(s.width/2, s.height-50) );

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(MotionStreakTest::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(MotionStreakTest::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(MotionStreakTest::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( CCPointMake( s.width/2 - 100,30) );
	item2->setPosition( CCPointMake( s.width/2, 30) );
	item3->setPosition( CCPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void MotionStreakTest::restartCallback(CCObject* pSender)
{
	CCScene* s = new MotionStreakTestScene();//CCScene::node();
	s->addChild(restartMotionAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::nextCallback(CCObject* pSender)
{
	CCScene* s = new MotionStreakTestScene();//CCScene::node();
	s->addChild( nextMotionAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::backCallback(CCObject* pSender)
{
	CCScene* s = new MotionStreakTestScene;//CCScene::node();
	s->addChild( backMotionAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void MotionStreakTestScene::runThisTest()
{
    CCLayer* pLayer = nextMotionAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
