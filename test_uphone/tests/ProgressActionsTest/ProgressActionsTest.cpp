#include "ProgressActionsTest.h"
#include "CCDirector.h"
#include "CCLabel.h"
#include "CCMenu.h"
#include "CCProgressTimer.h"
#include "CCProgressTimerActions.h"
#include "../testResource.h"

static int sceneIdx = -1; 

#define MAX_LAYER	3

CCLayer* createLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new SpriteProgressToRadial();
		case 1: return new SpriteProgressToHorizontal();
		case 2: return new SpriteProgressToVertical();
	}

	return NULL;
}

CCLayer* nextAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartAction()
{
	CCLayer* pLayer = createLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


void ProgressActionsTestScene::runThisTest()
{
    addChild(nextAction());
    CCDirector::getSharedDirector()->replaceScene(this);
}


//------------------------------------------------------------------
//
// SpriteDemo
//
//------------------------------------------------------------------
SpriteDemo::SpriteDemo(void)
{
}

SpriteDemo::~SpriteDemo(void)
{
}

std::string SpriteDemo::title()
{
	return "ProgressActionsTest";
}

std::string SpriteDemo::subtitle()
{
	return "";
}

void SpriteDemo::onEnter()
{
	__super::onEnter();

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

	CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 18);
	addChild(label, 1);
	label->setPosition( CGPointMake(s.width/2, s.height-50) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabel* l = CCLabel::labelWithString(strSubtitle.c_str(), "Thonburi", 22);
		addChild(l, 1);
		l->setPosition( CGPointMake(s.width/2, s.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(SpriteDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(SpriteDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(SpriteDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CGPointZero );
	item1->setPosition( CGPointMake( s.width/2 - 100,30) );
	item2->setPosition( CGPointMake( s.width/2, 30) );
	item3->setPosition( CGPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void SpriteDemo::restartCallback(NSObject* pSender)
{
	CCScene* s = new ProgressActionsTestScene();
	s->addChild(restartAction()); 

	CCDirector::getSharedDirector()->replaceScene(s);
}

void SpriteDemo::nextCallback(NSObject* pSender)
{
	CCScene* s = new ProgressActionsTestScene();
	s->addChild( nextAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
}

void SpriteDemo::backCallback(NSObject* pSender)
{
	CCScene* s = new ProgressActionsTestScene();
	s->addChild( backAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
} 

//------------------------------------------------------------------
//
// SpriteProgressToRadial
//
//------------------------------------------------------------------
void SpriteProgressToRadial::onEnter()
{
	__super::onEnter();
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	CCProgressTo *to1 = CCProgressTo::actionWithDuration(2, 100);
	CCProgressTo *to2 = CCProgressTo::actionWithDuration(2, 100);

	CCProgressTimer *left = CCProgressTimer::progressWithFile(s_pPathSister1);
	left->setType( kCCProgressTimerTypeRadialCW );
	addChild(left);
	left->setPosition(CGPointMake(100, s.height/2));
	left->runAction( CCRepeatForever::actionWithAction(to1));
	
	CCProgressTimer *right = CCProgressTimer::progressWithFile(s_pPathBlock);
	right->setType( kCCProgressTimerTypeRadialCCW );
	addChild(right);
	right->setPosition(CGPointMake(s.width-100, s.height/2));
	right->runAction( CCRepeatForever::actionWithAction(to2));
}

std::string SpriteProgressToRadial::subtitle()
{
	return "ProgressTo Radial";
}

//------------------------------------------------------------------
//
// SpriteProgressToHorizontal
//
//------------------------------------------------------------------

void SpriteProgressToHorizontal::onEnter()
{
	__super::onEnter();
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	
	CCProgressTo *to1 = CCProgressTo::actionWithDuration(2, 100);
	CCProgressTo *to2 = CCProgressTo::actionWithDuration(2, 100);
	
	CCProgressTimer *left = CCProgressTimer::progressWithFile(s_pPathSister1);
	left->setType( kCCProgressTimerTypeHorizontalBarLR );
	addChild(left);
	left->setPosition(CGPointMake(100, s.height/2));
	left->runAction( CCRepeatForever::actionWithAction(to1));
	
	CCProgressTimer *right = CCProgressTimer::progressWithFile(s_pPathSister2);
	right->setType( kCCProgressTimerTypeHorizontalBarRL );
	addChild(right);
	right->setPosition(CGPointMake(s.width-100, s.height/2));
	right->runAction( CCRepeatForever::actionWithAction(to2));
}

std::string SpriteProgressToHorizontal::subtitle()
{
	return "ProgressTo Horizontal";
}

//------------------------------------------------------------------
//
// SpriteProgressToVertical
//
//------------------------------------------------------------------
void SpriteProgressToVertical::onEnter()
{
	__super::onEnter();
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	
	CCProgressTo *to1 = CCProgressTo::actionWithDuration(2, 100);
	CCProgressTo *to2 = CCProgressTo::actionWithDuration(2, 100);
	
	CCProgressTimer *left = CCProgressTimer::progressWithFile(s_pPathSister1);
	left->setType( kCCProgressTimerTypeVerticalBarBT );
	addChild(left);
	left->setPosition(CGPointMake(100, s.height/2));
	left->runAction( CCRepeatForever::actionWithAction(to1));
	
	CCProgressTimer *right = CCProgressTimer::progressWithFile(s_pPathSister2);
	right->setType( kCCProgressTimerTypeVerticalBarTB );
	addChild(right);
	right->setPosition(CGPointMake(s.width-100, s.height/2));
	right->runAction( CCRepeatForever::actionWithAction(to2));
}

std::string SpriteProgressToVertical::subtitle()
{
	return "ProgressTo Vertical";
}
