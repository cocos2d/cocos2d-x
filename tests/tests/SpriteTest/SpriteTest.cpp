#include "SpriteTest.h"
#include "../testResource.h"

enum 
{
	kTagTileMap = 1,
	kTagSpriteSheet = 1,
	kTagNode = 2,
	kTagAnimation1 = 1,
};

enum 
{
	kTagSprite1,
	kTagSprite2,
	kTagSprite3,
	kTagSprite4,
	kTagSprite5,
	kTagSprite6,
	kTagSprite7,
	kTagSprite8,
};

enum
{
	IDC_NEXT = 100,
	IDC_BACK,
	IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER	36

CCLayer* createSpriteTestLayer(int nIndex)
{

	switch(nIndex)
	{
		case 0: return new Sprite1();
		case 1: return new SpriteSheet1();
		case 2: return new SpriteFrameTest();
		case 3: return new SpriteAnchorPoint();
		case 4: return new SpriteSheetAnchorPoint();
		case 5: return new SpriteOffsetAnchorRotation();
		case 6: return new SpriteSheetOffsetAnchorRotation();
		case 7: return new SpriteOffsetAnchorScale();
		case 8: return new SpriteSheetOffsetAnchorScale();
		case 9: return new SpriteAnimationSplit();
		case 10: return new SpriteColorOpacity();
		case 11: return new SpriteSheetColorOpacity();
		case 12: return new SpriteZOrder();
		case 13: return new SpriteSheetZOrder();
		case 14: return new SpriteSheetReorder();
		case 15: return new SpriteSheetReorderIssue744();
		case 16: return new SpriteZVertex();
		case 17: return new SpriteSheetZVertex();
		case 18: return new Sprite6();
		case 19: return new SpriteFlip();
		case 20: return new SpriteSheetFlip();
		case 21: return new SpriteAliased();
		case 22: return new SpriteSheetAliased();
		case 23: return new SpriteNewTexture();
		case 24: return new SpriteSheetNewTexture();
		case 25: return new SpriteHybrid();
		case 26: return new SpriteSheetChildren();
		case 27: return new SpriteSheetChildren2();
		case 28: return new SpriteSheetChildrenZ();
		case 29: return new SpriteChildrenVisibility();
		case 30: return new SpriteChildrenAnchorPoint();
		case 31: return new SpriteSheetChildrenAnchorPoint();
		case 32: return new SpriteSheetChildrenScale();
		case 33: return new SpriteChildrenChildren();
		case 34: return new SpriteSheetChildrenChildren();
		case 35: return new SpriteNilTexture();
	}

	return NULL;
}

CCLayer* nextSpriteTestAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createSpriteTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backSpriteTestAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createSpriteTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartSpriteTestAction()
{
	CCLayer* pLayer = createSpriteTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

SpriteTestDemo::SpriteTestDemo(void)
{
}

SpriteTestDemo::~SpriteTestDemo(void)
{
}

std::string SpriteTestDemo::title()
{
	return "No title";
}

std::string SpriteTestDemo::subtitle()
{
	return "";
}

void SpriteTestDemo::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 1);
	label->setPosition( ccp(s.width/2, s.height-50) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition( ccp(s.width/2, s.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(SpriteTestDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(SpriteTestDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(SpriteTestDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( ccp( s.width/2 - 100,30) );
	item2->setPosition( ccp( s.width/2, 30) );
	item3->setPosition( ccp( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void SpriteTestDemo::restartCallback(CCObject* pSender)
{
	CCScene* s = new SpriteTestScene();
	s->addChild(restartSpriteTestAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteTestDemo::nextCallback(CCObject* pSender)
{
	CCScene* s = new SpriteTestScene();
	s->addChild( nextSpriteTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteTestDemo::backCallback(CCObject* pSender)
{
	CCScene* s = new SpriteTestScene();
	s->addChild( backSpriteTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Sprite1
//
//------------------------------------------------------------------

Sprite1::Sprite1()
{
	setIsTouchEnabled( true );
	
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	addNewSpriteWithCoords( ccp(s.width/2, s.height/2) );
	
}

void Sprite1::addNewSpriteWithCoords(CCPoint p)
{
	int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
	int x = (idx%5) * 85;
	int y = (idx/5) * 121;
	
	
	CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(x,y,85,121) );
	addChild( sprite );
	
	sprite->setPosition( ccp( p.x, p.y) );
	
	CCActionInterval* action;
	float random = CCRANDOM_0_1();
	
	if( random < 0.20 )
		action = CCScaleBy::actionWithDuration(3, 2);
	else if(random < 0.40)
		action = CCRotateBy::actionWithDuration(3, 360);
	else if( random < 0.60)
		action = CCBlink::actionWithDuration(1, 3);
	else if( random < 0.8 )
		action = CCTintBy::actionWithDuration(2, 0, -255, -255);
	else 
		action = CCFadeOut::actionWithDuration(2);
	CCActionInterval* action_back = action->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( action, action_back, NULL ));
	
	sprite->runAction( CCRepeatForever::actionWithAction(seq) );
}

void Sprite1::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCSetIterator it;
	CCTouch* touch;

	for( it = touches->begin(); it != touches->end(); it++) 
	{
		touch = (CCTouch*)(*it);

		if(!touch)
			break;

		CCPoint location = touch->locationInView(touch->view());
		
		location = CCDirector::sharedDirector()->convertToGL(location);
	
		addNewSpriteWithCoords( location );
	}
}

std::string Sprite1::title()
{
	return "Sprite (tap screen)";
}

//------------------------------------------------------------------
//
// SpriteSheet1
//
//------------------------------------------------------------------

SpriteSheet1::SpriteSheet1()
{
	setIsTouchEnabled( true );

	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	addNewSpriteWithCoords( ccp(s.width/2, s.height/2) );
}

void SpriteSheet1::addNewSpriteWithCoords(CCPoint p)
{
	CCSpriteBatchNode* sheet = (CCSpriteBatchNode*) getChildByTag( kTagSpriteSheet );
	
	int idx = CCRANDOM_0_1() * 1400 / 100;
	int x = (idx%5) * 85;
	int y = (idx/5) * 121;
	

	CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(x,y,85,121));
	sheet->addChild(sprite);

	sprite->setPosition( ccp( p.x, p.y) );

	CCActionInterval* action;
	float random = CCRANDOM_0_1();
	
	if( random < 0.20 )
		action = CCScaleBy::actionWithDuration(3, 2);
	else if(random < 0.40)
		action = CCRotateBy::actionWithDuration(3, 360);
	else if( random < 0.60)
		action = CCBlink::actionWithDuration(1, 3);
	else if( random < 0.8 )
		action = CCTintBy::actionWithDuration(2, 0, -255, -255);
	else 
		action = CCFadeOut::actionWithDuration(2);

	CCActionInterval* action_back = action->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(action, action_back, NULL));
	
	sprite->runAction( CCRepeatForever::actionWithAction(seq));
}

void SpriteSheet1::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCSetIterator it;
	CCTouch* touch;

	for( it = touches->begin(); it != touches->end(); it++) 
	{
		touch = (CCTouch*)(*it);

		if(!touch)
			break;

		CCPoint location = touch->locationInView(touch->view());
		
		location = CCDirector::sharedDirector()->convertToGL(location);
	
		addNewSpriteWithCoords( location );
	}

}

std::string SpriteSheet1::title()
{
	return "SpriteSheet (tap screen)";
}


//------------------------------------------------------------------
//
// SpriteColorOpacity
//
//------------------------------------------------------------------

SpriteColorOpacity::SpriteColorOpacity()
{
	CCSprite* sprite1 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
	CCSprite* sprite2 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	CCSprite* sprite3 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121));
	CCSprite* sprite4 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121));
	
	CCSprite* sprite5 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
	CCSprite* sprite6 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	CCSprite* sprite7 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121));
	CCSprite* sprite8 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121));
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	sprite1->setPosition( ccp( (s.width/5)*1, (s.height/3)*1) );
	sprite2->setPosition( ccp( (s.width/5)*2, (s.height/3)*1) );
	sprite3->setPosition( ccp( (s.width/5)*3, (s.height/3)*1) );
	sprite4->setPosition( ccp( (s.width/5)*4, (s.height/3)*1) );
	sprite5->setPosition( ccp( (s.width/5)*1, (s.height/3)*2) );
	sprite6->setPosition( ccp( (s.width/5)*2, (s.height/3)*2) );
	sprite7->setPosition( ccp( (s.width/5)*3, (s.height/3)*2) );
	sprite8->setPosition( ccp( (s.width/5)*4, (s.height/3)*2) );
	
	CCActionInterval* action = CCFadeIn::actionWithDuration(2);
	CCActionInterval* action_back = action->reverse();
	CCAction* fade = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( action, action_back, NULL)));
	
	CCActionInterval* tintred = CCTintBy::actionWithDuration(2, 0, -255, -255);
	CCActionInterval* tintred_back = tintred->reverse();
	CCAction* red = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintred, tintred_back, NULL)) );
	
	CCActionInterval* tintgreen = CCTintBy::actionWithDuration(2, -255, 0, -255);
	CCActionInterval* tintgreen_back = tintgreen->reverse();
	CCAction* green = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintgreen, tintgreen_back, NULL)));
	
	CCActionInterval* tintblue = CCTintBy::actionWithDuration(2, -255, -255, 0);
	CCActionInterval* tintblue_back = tintblue->reverse();
	CCAction* blue = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintblue, tintblue_back, NULL)) );
	
	sprite5->runAction(red);
	sprite6->runAction(green);
	sprite7->runAction(blue);
	sprite8->runAction(fade);
	
	// late add: test dirtyColor and dirtyPosition
	addChild(sprite1, 0, kTagSprite1);
	addChild(sprite2, 0, kTagSprite2);
	addChild(sprite3, 0, kTagSprite3);
	addChild(sprite4, 0, kTagSprite4);
	addChild(sprite5, 0, kTagSprite5);
	addChild(sprite6, 0, kTagSprite6);
	addChild(sprite7, 0, kTagSprite7);
	addChild(sprite8, 0, kTagSprite8);
	
	schedule( schedule_selector(SpriteColorOpacity::removeAndAddSprite), 2 );
}

// this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
void SpriteColorOpacity::removeAndAddSprite(ccTime dt)
{
	CCSprite* sprite = (CCSprite*)(getChildByTag(kTagSprite5));	
	sprite->retain();
	
	removeChild(sprite, false);
	addChild(sprite, 0, kTagSprite5);
	
	sprite->release();
}

std::string SpriteColorOpacity::title()
{
	return "Sprite: Color & Opacity";
}

//------------------------------------------------------------------
//
// SpriteSheetColorOpacity
//
//------------------------------------------------------------------

SpriteSheetColorOpacity::SpriteSheetColorOpacity()
{
	// small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 1);
	addChild(sheet, 0, kTagSpriteSheet);		
	
	CCSprite* sprite1 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
	CCSprite* sprite2 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	CCSprite* sprite3 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*2, 121*1, 85, 121));
	CCSprite* sprite4 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*3, 121*1, 85, 121));
	
	CCSprite* sprite5 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
	CCSprite* sprite6 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	CCSprite* sprite7 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*2, 121*1, 85, 121));
	CCSprite* sprite8 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*3, 121*1, 85, 121));
	
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	sprite1->setPosition( ccp( (s.width/5)*1, (s.height/3)*1) );
	sprite2->setPosition( ccp( (s.width/5)*2, (s.height/3)*1) );
	sprite3->setPosition( ccp( (s.width/5)*3, (s.height/3)*1) );
	sprite4->setPosition( ccp( (s.width/5)*4, (s.height/3)*1) );
	sprite5->setPosition( ccp( (s.width/5)*1, (s.height/3)*2) );
	sprite6->setPosition( ccp( (s.width/5)*2, (s.height/3)*2) );
	sprite7->setPosition( ccp( (s.width/5)*3, (s.height/3)*2) );
	sprite8->setPosition( ccp( (s.width/5)*4, (s.height/3)*2) );

	CCActionInterval* action = CCFadeIn::actionWithDuration(2);
	CCActionInterval* action_back = action->reverse();
	CCAction* fade = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( action, action_back,NULL)));

	CCActionInterval* tintred = CCTintBy::actionWithDuration(2, 0, -255, -255);
	CCActionInterval* tintred_back = tintred->reverse();
	CCAction* red = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintred, tintred_back,NULL)));

	CCActionInterval* tintgreen = CCTintBy::actionWithDuration(2, -255, 0, -255);
	CCActionInterval* tintgreen_back = tintgreen->reverse();
	CCAction* green = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintgreen, tintgreen_back,NULL)));

	CCActionInterval* tintblue = CCTintBy::actionWithDuration(2, -255, -255, 0);
	CCActionInterval* tintblue_back = tintblue->reverse();
	CCAction* blue = CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions( tintblue, tintblue_back,NULL)));
	
	
	sprite5->runAction(red);
	sprite6->runAction(green);
	sprite7->runAction(blue);
	sprite8->runAction(fade);
	
	// late add: test dirtyColor and dirtyPosition
	sheet->addChild(sprite1, 0, kTagSprite1);
	sheet->addChild(sprite2, 0, kTagSprite2);
	sheet->addChild(sprite3, 0, kTagSprite3);
	sheet->addChild(sprite4, 0, kTagSprite4);
	sheet->addChild(sprite5, 0, kTagSprite5);
	sheet->addChild(sprite6, 0, kTagSprite6);
	sheet->addChild(sprite7, 0, kTagSprite7);
	sheet->addChild(sprite8, 0, kTagSprite8);
	
	
	schedule( schedule_selector(SpriteSheetColorOpacity::removeAndAddSprite), 2);
}

// this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
void SpriteSheetColorOpacity::removeAndAddSprite(ccTime dt)
{
	CCSpriteBatchNode* sheet= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteSheet ));
	CCSprite* sprite = (CCSprite*)(sheet->getChildByTag(kTagSprite5));
	
	sprite->retain();

	sheet->removeChild(sprite, false);
	sheet->addChild(sprite, 0, kTagSprite5);
	
	sprite->release();
}

std::string SpriteSheetColorOpacity::title()
{
	return "SpriteSheet: Color & Opacity";
}

//------------------------------------------------------------------
//
// SpriteZOrder
//
//------------------------------------------------------------------

SpriteZOrder::SpriteZOrder()
{
	m_dir = 1;
			
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	float step = s.width/11;
	for(int i=0;i<5;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		addChild(sprite, i);
	}
	
	for(int i=5;i<10;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*0, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		addChild(sprite, 14-i);
	}
	
	CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*0, 85, 121));
	addChild(sprite, -1, kTagSprite1);
	sprite->setPosition( ccp(s.width/2, s.height/2 - 20) );
	sprite->setScaleX( 6 );
	sprite->setColor(ccRED);
	
	schedule( schedule_selector(SpriteZOrder::reorderSprite), 1);		
}

void SpriteZOrder::reorderSprite(ccTime dt)
{
	CCSprite* sprite = (CCSprite*)(getChildByTag(kTagSprite1));
	
	int z = sprite->getZOrder();
	
	if( z < -1 )
		m_dir = 1;
	if( z > 10 )
		m_dir = -1;
	
	z += m_dir * 3;
	
	reorderChild(sprite, z);
	
}

std::string SpriteZOrder::title()
{
	return "Sprite: Z order";
}

//------------------------------------------------------------------
//
// SpriteSheetZOrder
//
//------------------------------------------------------------------

SpriteSheetZOrder::SpriteSheetZOrder()
{
	m_dir = 1;
	
	// small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 1);
	addChild(sheet, 0, kTagSpriteSheet);		
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	float step = s.width/11;
	for(int i=0;i<5;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		sheet->addChild(sprite, i);
	}
	
	for(int i=5;i<10;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*0, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		sheet->addChild(sprite, 14-i);
	}
	
	CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*3, 121*0, 85, 121));
	sheet->addChild(sprite, -1, kTagSprite1);
	sprite->setPosition( ccp(s.width/2, s.height/2 - 20) );
	sprite->setScaleX( 6 );
	sprite->setColor(ccRED);
	
	schedule( schedule_selector(SpriteSheetZOrder::reorderSprite), 1);		
}

void SpriteSheetZOrder::reorderSprite(ccTime dt)
{
	CCSpriteBatchNode* sheet= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteSheet ));
	CCSprite* sprite = (CCSprite*)(sheet->getChildByTag(kTagSprite1));
	
	int z = sprite->getZOrder();
	
	if( z < -1 )
		m_dir = 1;
	if( z > 10 )
		m_dir = -1;
	
	z += m_dir * 3;

	sheet->reorderChild(sprite, z);
}

std::string SpriteSheetZOrder::title()
{
	return "SpriteSheet: Z order";
}

//------------------------------------------------------------------
//
// SpriteSheetReorder
//
//------------------------------------------------------------------

SpriteSheetReorder::SpriteSheetReorder()
{
	CCMutableArray<CCObject*>* a = new CCMutableArray<CCObject*>(10);
	CCSpriteBatchNode* asmtest = CCSpriteBatchNode::spriteSheetWithFile("animations/ghosts.png");
	
	for(int i=0; i<10; i++)
	{
		CCSprite* s1 = CCSprite::spriteWithSpriteSheet((CCSpriteSheetInternalOnly* )asmtest, CCRectMake(0, 0, 50, 50));
		a->addObject(s1);
		asmtest->addChild(s1, 10);
	}
	
	for(int i=0; i<10; i++)
	{
		if(i!=5)
			asmtest->reorderChild( (CCNode*)(a->getObjectAtIndex(i)), 9 );
	}
	
    CCMutableArray<CCNode*>::CCMutableArrayIterator it;

	int prev = -1;
	CCMutableArray<CCNode*>* children = asmtest->getChildren();
	CCSprite* child;
	for(it = children->begin(); it != children->end(); it++)
	{
		child = (CCSprite*)(*it);
		if(! child )
			break;

		int currentIndex = child->getAtlasIndex();
		CCAssert( prev == currentIndex-1, "Child order failed");
		////----UXLOG("children %x - atlasIndex:%d", child, currentIndex);
		prev = currentIndex;
	}
	
	prev = -1;
    CCMutableArray<CCSprite*>::CCMutableArrayIterator itChild;
	CCMutableArray<CCSprite*>* sChildren = asmtest->getDescendants();
	for(itChild = sChildren->begin(); itChild != sChildren->end(); itChild++)
	{
		child = (CCSprite*)(*itChild);
		if(! child )
			break;

		int currentIndex = child->getAtlasIndex();
		CCAssert( prev == currentIndex-1, "Child order failed");
		////----UXLOG("descendant %x - atlasIndex:%d", child, currentIndex);
		prev = currentIndex;
	}

	a->release();	   //memory leak : 2010-0415
}

std::string SpriteSheetReorder::title()
{
	return "SpriteSheet: reorder #1";
}

std::string SpriteSheetReorder::subtitle()
{
	return "Should not crash";
}

//------------------------------------------------------------------
//
// SpriteSheetReorderIssue744
//
//------------------------------------------------------------------

SpriteSheetReorderIssue744::SpriteSheetReorderIssue744()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	

	// Testing issue #744
	// http://code.google.com/p/cocos2d-iphone/issues/detail?id=744
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 15);
	addChild(sheet, 0, kTagSpriteSheet);		

	CCSprite* sprite = CCSprite::spriteWithSpriteSheet((CCSpriteSheetInternalOnly* )sheet,CCRectMake(0, 0, 85, 121));
	sprite->setPosition( ccp(s.width/2, s.height/2) );
	sheet->addChild(sprite, 3);
	sheet->reorderChild(sprite, 1);
}

std::string SpriteSheetReorderIssue744::title()
{
	return "SpriteSheet: reorder issue #744";
}

std::string SpriteSheetReorderIssue744::subtitle()
{
	return "Should not crash";
}

//------------------------------------------------------------------
//
// SpriteZVertex
//
//------------------------------------------------------------------

void SpriteZVertex::onEnter()
{
	SpriteTestDemo::onEnter();
	
	// TIP: don't forget to enable Alpha test
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void SpriteZVertex::onExit()
{
	glDisable(GL_ALPHA_TEST);
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	SpriteTestDemo::onExit();
}

SpriteZVertex::SpriteZVertex()
{
	//
	// This test tests z-order
	// If you are going to use it is better to use a 3D projection
	//
	// WARNING:
	// The developer is resposible for ordering it's sprites according to it's Z if the sprite has
	// transparent parts.
	//
	
	m_dir = 1;
	m_time = 0;

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float step = s.width/12;
	
	CCNode* node = CCNode::node();
	// camera uses the center of the image as the pivoting point
	node->setContentSize( CCSizeMake(s.width,s.height) );
	node->setAnchorPoint( ccp(0.5f, 0.5f));
	node->setPosition( ccp(s.width/2, s.height/2));

	addChild(node, 0);

	for(int i=0;i<5;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
		sprite->setPosition( ccp((i+1)*step, s.height/2) );
		sprite->setVertexZ( 10 + i*40 );
		node->addChild(sprite, 0);
		
	}
	
	for(int i=5;i<11;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*0, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		sprite->setVertexZ( 10 + (10-i)*40 );
		node->addChild(sprite, 0);
	}

	node->runAction( CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0) );
}

std::string SpriteZVertex::title()
{
	return "Sprite: openGL Z vertex";
}

//------------------------------------------------------------------
//
// SpriteSheetZVertex
//
//------------------------------------------------------------------

void SpriteSheetZVertex::onEnter()
{
	SpriteTestDemo::onEnter();

	// TIP: don't forget to enable Alpha test
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void SpriteSheetZVertex::onExit()
{
	glDisable(GL_ALPHA_TEST);
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	SpriteTestDemo::onExit();
}

SpriteSheetZVertex::SpriteSheetZVertex()
{
	//
	// This test tests z-order
	// If you are going to use it is better to use a 3D projection
	//
	// WARNING:
	// The developer is resposible for ordering it's sprites according to it's Z if the sprite has
	// transparent parts.
	//
	
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	float step = s.width/12;
	
	// small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 1);
	// camera uses the center of the image as the pivoting point
	sheet->setContentSize( CCSizeMake(s.width,s.height));
	sheet->setAnchorPoint( ccp(0.5f, 0.5f));
	sheet->setPosition( ccp(s.width/2, s.height/2));
	

	addChild(sheet, 0, kTagSpriteSheet);		
	
	for(int i=0;i<5;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		sprite->setVertexZ(  10 + i*40 );
		sheet->addChild(sprite, 0);
		
	}
	
	for(int i=5;i<11;i++) {
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*0, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );
		sprite->setVertexZ(  10 + (10-i)*40 );
		sheet->addChild(sprite, 0);
	}
	
	sheet->runAction(CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0) );
}

std::string SpriteSheetZVertex::title()
{
	return "SpriteSheet: openGL Z vertex";
}


//------------------------------------------------------------------
//
// SpriteAnchorPoint
//
//------------------------------------------------------------------

SpriteAnchorPoint::SpriteAnchorPoint()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	
	CCActionInterval* rotate = CCRotateBy::actionWithDuration(10, 360);
	CCAction* action = CCRepeatForever::actionWithAction(rotate);
	
	for(int i=0;i<3;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*i, 121*1, 85, 121) );
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
		
		CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
		point->setScale( 0.25f );
		point->setPosition( sprite->getPosition() );
		addChild(point, 10);
		
		switch(i) 
		{
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}
		
		point->setPosition( sprite->getPosition() );
		
		CCAction* copy = (CCAction*)(action->copy()->autorelease());
		sprite->runAction(copy);
		addChild(sprite, i);
	}		
}

std::string SpriteAnchorPoint::title()
{
	return "Sprite: anchor point";
}

//------------------------------------------------------------------
//
// SpriteSheetAnchorPoint
//
//------------------------------------------------------------------
SpriteSheetAnchorPoint::SpriteSheetAnchorPoint()
{
	// small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 1);
	addChild(sheet, 0, kTagSpriteSheet);		
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	
	CCActionInterval* rotate = CCRotateBy::actionWithDuration(10, 360);
	CCAction* action = CCRepeatForever::actionWithAction(rotate);
	for(int i=0;i<3;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*i, 121*1, 85, 121));
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
		
		CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
		point->setScale( 0.25f );
		point->setPosition( sprite->getPosition() );
		addChild(point, 1);

		switch(i) 
		{
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}

		point->setPosition( sprite->getPosition() );
		
		CCAction* copy = (CCAction*)(action->copy()->autorelease());
		sprite->runAction(copy);
		sheet->addChild(sprite, i);
	}
}

std::string SpriteSheetAnchorPoint::title()
{
	return "SpriteSheet: anchor point";
}

//------------------------------------------------------------------
//
// Sprite6
//
//------------------------------------------------------------------

Sprite6::Sprite6()
{
	// small capacity. Testing resizing
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 1);
	addChild(sheet, 0, kTagSpriteSheet);
	sheet->setIsRelativeAnchorPoint( false );

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	sheet->setAnchorPoint( ccp(0.5f, 0.5f) );
	sheet->setContentSize( CCSizeMake(s.width, s.height) );
	
	
	// SpriteSheet actions
	CCActionInterval* rotate = CCRotateBy::actionWithDuration(5, 360);
	CCAction* action = CCRepeatForever::actionWithAction(rotate);

	// SpriteSheet actions
	CCActionInterval* rotate_back = rotate->reverse();
	CCActionInterval* rotate_seq = (CCActionInterval*)(CCSequence::actions(rotate, rotate_back, NULL));
	CCAction* rotate_forever = CCRepeatForever::actionWithAction(rotate_seq);
	
	CCActionInterval* scale = CCScaleBy::actionWithDuration(5, 1.5f);
	CCActionInterval* scale_back = scale->reverse();
	CCActionInterval* scale_seq = (CCActionInterval*)(CCSequence::actions( scale, scale_back, NULL));
	CCAction* scale_forever = CCRepeatForever::actionWithAction(scale_seq);

	float step = s.width/4;

	for(int i=0;i<3;i++) 
	{
		CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*i, 121*1, 85, 121));
		sprite->setPosition( ccp( (i+1)*step, s.height/2) );

		sprite->runAction( (CCAction*)(action->copy()->autorelease()) );
		sheet->addChild(sprite, i);
	}
	
	sheet->runAction( scale_forever);
	sheet->runAction( rotate_forever);
}

std::string Sprite6::title()
{
	return "SpriteSheet transformation";
}

//------------------------------------------------------------------
//
// SpriteFlip
//
//------------------------------------------------------------------
SpriteFlip::SpriteFlip()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* sprite1 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
	addChild(sprite1, 0, kTagSprite1);
	
	CCSprite* sprite2 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
	addChild(sprite2, 0, kTagSprite2);
	
	schedule( schedule_selector(SpriteFlip::flipSprites), 1);
}

void SpriteFlip::flipSprites(ccTime dt)
{
	CCSprite* sprite1 = (CCSprite*)(getChildByTag(kTagSprite1));
	CCSprite* sprite2 = (CCSprite*)(getChildByTag(kTagSprite2));
	
	bool x = sprite1->isFlipX();
	bool y = sprite2->isFlipY();
	
	sprite1->setFlipX(!x);
	sprite2->setFlipY(!y);
}

std::string SpriteFlip::title()
{
	return "Sprite Flip X & Y";
}

//------------------------------------------------------------------
//
// SpriteSheetFlip
//
//------------------------------------------------------------------
SpriteSheetFlip::SpriteSheetFlip()
{
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 10);
	addChild(sheet, 0, kTagSpriteSheet);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* sprite1 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
	sheet->addChild(sprite1, 0, kTagSprite1);
	
	CCSprite* sprite2 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
	sheet->addChild(sprite2, 0, kTagSprite2);
	
	schedule( schedule_selector(SpriteSheetFlip::flipSprites), 1);
}

void SpriteSheetFlip::flipSprites(ccTime dt)
{
	CCSpriteBatchNode* sheet= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteSheet ));
	CCSprite* sprite1 = (CCSprite*)(sheet->getChildByTag(kTagSprite1));
	CCSprite* sprite2 = (CCSprite*)(sheet->getChildByTag(kTagSprite2));
	
	bool x = sprite1->isFlipX();
	bool y = sprite2->isFlipY();
	
	sprite1->setFlipX(!x);
	sprite2->setFlipY(!y);
}

std::string SpriteSheetFlip::title()
{
	return "SpriteSheet Flip X & Y";
}

//------------------------------------------------------------------
//
// SpriteAliased
//
//------------------------------------------------------------------

SpriteAliased::SpriteAliased()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* sprite1 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
	addChild(sprite1, 0, kTagSprite1);
	
	CCSprite* sprite2 = CCSprite::spriteWithFile("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
	sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
	addChild(sprite2, 0, kTagSprite2);
	
	CCActionInterval* scale = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* scale_back = scale->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( scale, scale_back, NULL));
	CCAction* repeat = CCRepeatForever::actionWithAction(seq);
	
	CCAction* repeat2 = (CCAction*)(repeat->copy()->autorelease());
	
	sprite1->runAction(repeat);
	sprite2->runAction(repeat2);
	
}

void SpriteAliased::onEnter()
{
	SpriteTestDemo::onEnter();
	
	//
	// IMPORTANT:
	// This change will affect every sprite that uses the same texture
	// So sprite1 and sprite2 will be affected by this change
	//
	CCSprite* sprite = (CCSprite*)getChildByTag(kTagSprite1);
	sprite->getTexture()->setAliasTexParameters();
}

void SpriteAliased::onExit()
{
	// restore the tex parameter to AntiAliased.
	CCSprite* sprite = (CCSprite*)getChildByTag(kTagSprite1);
	sprite->getTexture()->setAntiAliasTexParameters();
	SpriteTestDemo::onExit();
}

std::string SpriteAliased::title()
{
	return "Sprite Aliased";
}

//------------------------------------------------------------------
//
// SpriteSheetAliased
//
//------------------------------------------------------------------

SpriteSheetAliased::SpriteSheetAliased()
{
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 10);
	addChild(sheet, 0, kTagSpriteSheet);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite* sprite1 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
	sheet->addChild(sprite1, 0, kTagSprite1);
	
	CCSprite* sprite2 = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
	sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
	sheet->addChild(sprite2, 0, kTagSprite2);
	
	CCActionInterval* scale = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* scale_back = scale->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( scale, scale_back, NULL));
	CCAction* repeat = CCRepeatForever::actionWithAction(seq);
	
	CCAction* repeat2 = (CCAction*)(repeat->copy()->autorelease());
	
	sprite1->runAction(repeat);
	sprite2->runAction(repeat2);
		
}
void SpriteSheetAliased::onEnter()
{
	SpriteTestDemo::onEnter();
	CCSpriteBatchNode* sheet = (CCSpriteBatchNode*) getChildByTag( kTagSpriteSheet );
	sheet->getTexture()->setAliasTexParameters();
}

void SpriteSheetAliased::onExit()
{
	// restore the tex parameter to AntiAliased.
	CCSpriteBatchNode* sheet = (CCSpriteBatchNode*) getChildByTag( kTagSpriteSheet );
	sheet->getTexture()->setAntiAliasTexParameters();
	SpriteTestDemo::onExit();
}

std::string SpriteSheetAliased::title()
{
	return "SpriteSheet Aliased";
}

//------------------------------------------------------------------
//
// SpriteNewTexture
//
//------------------------------------------------------------------

SpriteNewTexture::SpriteNewTexture()
{
	setIsTouchEnabled( true );
	
	CCNode* node = CCNode::node();
	addChild(node, 0, kTagSpriteSheet);

    m_texture1 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas.png");
    m_texture1->retain();
	m_texture2 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas-mono.png");
    m_texture2->retain();
	
	m_usingTexture1 = true;

	for(int i=0;i<30;i++)
		addNewSprite();
}

SpriteNewTexture::~SpriteNewTexture()
{
	m_texture1->release();
	m_texture2->release();
}

void SpriteNewTexture::addNewSprite()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);

	int idx = CCRANDOM_0_1() * 1400 / 100;
	int x = (idx%5) * 85;
	int y = (idx/5) * 121;
	
	
	CCNode* node = getChildByTag( kTagSpriteSheet );
	CCSprite* sprite = CCSprite::spriteWithTexture(m_texture1, CCRectMake(x,y,85,121));
	node->addChild(sprite);
	
	sprite->setPosition( ccp( p.x, p.y) );
	
	CCActionInterval* action;
	float random = CCRANDOM_0_1();
	
	if( random < 0.20 )
		action = CCScaleBy::actionWithDuration(3, 2);
	else if(random < 0.40)
		action = CCRotateBy::actionWithDuration(3, 360);
	else if( random < 0.60)
		action = CCBlink::actionWithDuration(1, 3);
	else if( random < 0.8 )
		action = CCTintBy::actionWithDuration(2, 0, -255, -255);
	else 
		action = CCFadeOut::actionWithDuration(2);

	CCActionInterval* action_back = action->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(action, action_back, NULL));
	
	sprite->runAction( CCRepeatForever::actionWithAction(seq) );
}

void SpriteNewTexture::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

	CCNode *node = getChildByTag( kTagSpriteSheet );
	
	CCMutableArray<CCNode*>::CCMutableArrayIterator it;
	CCMutableArray<CCNode*>* children = node->getChildren();
	CCSprite* sprite;

	if( m_usingTexture1 )						  //--> win32 : Let's it make just simple sentence
	{
		for(it = children->begin(); it != children->end(); it++)
		{
			sprite = (CCSprite*)(*it);
			if(! sprite)
				break;

			sprite->setTexture(m_texture2);
		}

		m_usingTexture1 = false;
	} 
	else 
	{
		for(it = children->begin(); it != children->end(); it++)
		{
			sprite = (CCSprite*)(*it);
			if(! sprite)
				break;

			sprite->setTexture(m_texture1);
		}

		m_usingTexture1 = true;
	}
}

std::string SpriteNewTexture::title()
{
	return "Sprite New texture (tap)";
}

//------------------------------------------------------------------
//
// SpriteSheetNewTexture
//
//------------------------------------------------------------------

SpriteSheetNewTexture::SpriteSheetNewTexture()
{
	setIsTouchEnabled( true );
	
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("Images/grossini_dance_atlas.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	m_texture1 = sheet->getTexture(); m_texture1->retain();
	m_texture2 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas-mono.png");
	m_texture2->retain();
	
	for(int i=0;i<30;i++)
		addNewSprite();
}

SpriteSheetNewTexture::~SpriteSheetNewTexture()
{
	m_texture1->release();
	m_texture2->release();
}

void SpriteSheetNewTexture::addNewSprite()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
	
	CCSpriteBatchNode* sheet = (CCSpriteBatchNode*) getChildByTag( kTagSpriteSheet );
	
	int idx = CCRANDOM_0_1() * 1400 / 100;
	int x = (idx%5) * 85;
	int y = (idx/5) * 121;
	
	
	CCSprite* sprite = CCSprite::spriteWithTexture(sheet->getTexture(), CCRectMake(x,y,85,121));
	sheet->addChild(sprite);
	
	sprite->setPosition( ccp( p.x, p.y) );
	
	CCActionInterval* action;
	float random = CCRANDOM_0_1();
	
	if( random < 0.20 )
		action = CCScaleBy::actionWithDuration(3, 2);
	else if(random < 0.40)
		action = CCRotateBy::actionWithDuration(3, 360);
	else if( random < 0.60)
		action = CCBlink::actionWithDuration(1, 3);
	else if( random < 0.8 )
		action = CCTintBy::actionWithDuration(2, 0, -255, -255);
	else 
		action = CCFadeOut::actionWithDuration(2);
	CCActionInterval* action_back = action->reverse();
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(action, action_back, NULL));
	
	sprite->runAction( CCRepeatForever::actionWithAction(seq) );
}

void SpriteSheetNewTexture::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCSpriteBatchNode* sheet = (CCSpriteBatchNode*) getChildByTag( kTagSpriteSheet );
	
	if( sheet->getTexture() == m_texture1 )
		sheet->setTexture(m_texture2);
	else
		sheet->setTexture(m_texture1);	
}

std::string SpriteSheetNewTexture::title()
{
	return "SpriteSheet new texture (tap)";
}


//------------------------------------------------------------------
//
// SpriteFrameTest
//
//------------------------------------------------------------------

SpriteFrameTest::SpriteFrameTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// IMPORTANT:
	// The sprite frames will be cached AND RETAINED, and they won't be released unless you call
	//     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_gray.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_blue.plist");

	//
	// Animation using Sprite Sheet
	//
	m_pSprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	m_pSprite1->setPosition( ccp( s.width/2-80, s.height/2) );
	
	CCSpriteBatchNode* spritesheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png");
	spritesheet->addChild(m_pSprite1);
	addChild(spritesheet);

	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(15);

    char str[100] = {0};
	for(int i = 1; i < 15; i++) 
	{
        sprintf(str, "grossini_dance_%02d.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( str );
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
	m_pSprite1->runAction( CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ) );

	// to test issue #732, uncomment the following line
	m_pSprite1->setFlipX(false);
    m_pSprite1->setFlipY(false);

	//
	// Animation using standard Sprite
	//
	m_pSprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	m_pSprite2->setPosition( ccp( s.width/2 + 80, s.height/2) );
	addChild(m_pSprite2);
	

	CCMutableArray<CCSpriteFrame*>* moreFrames = new CCMutableArray<CCSpriteFrame*>(20);
	for(int i = 1; i < 15; i++) 
	{
        sprintf(str, "grossini_dance_gray_%02d.png",i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		moreFrames->addObject(frame);
	}


	for( int i = 1; i < 5; i++) {
        sprintf(str, "grossini_blue_%02d.png",i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		moreFrames->addObject(frame);
	}
	
	// append frames from another sheet
	moreFrames->addObjectsFromArray(animFrames);
	CCAnimation *animMixed = CCAnimation::animationWithName("dance", 0.2f, moreFrames);

	
	m_pSprite2->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animMixed, false) ) );

	animFrames->release();
	moreFrames->release(); 

	// to test issue #732, uncomment the following line
    m_pSprite2->setFlipX(false);
    m_pSprite2->setFlipY(false);

    schedule(schedule_selector(SpriteFrameTest::startIn05Secs), 0.5f);
    m_nCounter = 0;
}

void SpriteFrameTest::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

SpriteFrameTest::~SpriteFrameTest()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteFrameTest::title()
{
	return "Sprite vs. SpriteSheet animation";
}

std::string SpriteFrameTest::subtitle()
{
    return "Testing issue #792";
}

void SpriteFrameTest::startIn05Secs(ccTime dt)
{
    unschedule(schedule_selector(SpriteFrameTest::startIn05Secs));
    schedule(schedule_selector(SpriteFrameTest::flipSprites), 1.0f);
}

void SpriteFrameTest::flipSprites(ccTime dt)
{
    m_nCounter++;

    bool fx = false;
    bool fy = false;
    int  i  = m_nCounter % 4;

    switch ( i ) {
        case 0:
            fx = false;
            fy = false;
            break;
        case 1:
            fx = true;
            fy = false;
            break;
        case 2:
            fx = false;
            fy = true;
            break;
        case 3:
            fx = true;
            fy = true;
            break;
    }

    m_pSprite1->setFlipX(fx);
    m_pSprite1->setFlipY(fy);
    m_pSprite2->setFlipX(fx);
    m_pSprite2->setFlipY(fy);
    //NSLog(@"flipX:%d, flipY:%d", fx, fy);
}

//------------------------------------------------------------------
//
// SpriteOffsetAnchorRotation
//
//------------------------------------------------------------------
SpriteOffsetAnchorRotation::SpriteOffsetAnchorRotation()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_gray.plist");

	for(int i=0;i<3;i++) 
	{
        //
	    // Animation using Sprite Sheet
	    //
	    CCSprite* sprite = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );

        CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 1);

		switch(i) 
		{
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}
		
		point->setPosition( sprite->getPosition() );
		
		CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(14);
        char str[100] = {0};
		for(int i = 0; i < 14; i++) 
		{
            sprintf(str, "grossini_dance_%02d.png",(i+1));
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
			animFrames->addObject(frame);
		}

		CCAnimation* animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
		sprite->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ) );			
		sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(10, 360) ) );

		addChild(sprite, 0);

		animFrames->release();	// win32 : memory leak	2010-0415
	}		
}


void SpriteOffsetAnchorRotation::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteOffsetAnchorRotation::title()
{
	return "Sprite offset + anchor + rot";
}

//------------------------------------------------------------------
//
// SpriteSheetOffsetAnchorRotation
//
//------------------------------------------------------------------

SpriteSheetOffsetAnchorRotation::SpriteSheetOffsetAnchorRotation()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	for(int i=0;i<3;i++) 
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_gray.plist");
		
		//
		// Animation using Sprite Sheet
		//
		CCSprite* sprite = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2));
		
		CCSprite* point = CCSprite::spriteWithFile("Images/r1.png");
		point->setScale( 0.25f );
		point->setPosition( sprite->getPosition() );
		addChild(point, 200);
		
		switch(i) 
		{
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}
		
		point->setPosition( sprite->getPosition() );
		
		CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png");
		addChild(spritesheet);
		
		CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(14);
        char str[100] = {0};
        for(int k = 0; k < 14; k++) 
		{
            sprintf(str, "grossini_dance_%02d.png",(k+1));
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
			animFrames->addObject(frame);
		}

		CCAnimation *animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
		sprite->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ));
		sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(10, 360) ));
		
		spritesheet->addChild(sprite, i);

		animFrames->release();	// win32 : memory leak	2010-0415
	}		
}


void SpriteSheetOffsetAnchorRotation::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetOffsetAnchorRotation::title()
{
	return "SpriteSheet offset + anchor + rot";
}


//------------------------------------------------------------------
//
// SpriteOffsetAnchorScale
//
//------------------------------------------------------------------


SpriteOffsetAnchorScale::SpriteOffsetAnchorScale()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	for(int i=0;i<3;i++) 
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_gray.plist");
		
		//
		// Animation using Sprite Sheet
		//
		CCSprite* sprite = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
		
		CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
		point->setScale( 0.25f );
		point->setPosition( sprite->getPosition() );
		addChild(point, 1);
		
		switch(i) 
		{
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}
		
		point->setPosition( sprite->getPosition() );
		
		CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(14);
        char str[100] = {0};
		for(int i = 0; i < 14; i++) 
		{
            sprintf(str, "grossini_dance_%02d.png",(i+1));
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
			animFrames->addObject(frame);
		}

		CCAnimation *animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
		sprite->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ));			
		
		CCActionInterval* scale = CCScaleBy::actionWithDuration(2, 2);
		CCActionInterval* scale_back = scale->reverse();
		CCActionInterval* seq_scale = (CCActionInterval*)(CCSequence::actions(scale, scale_back, NULL));
		sprite->runAction(CCRepeatForever::actionWithAction(seq_scale));
		
		addChild(sprite, 0);

		animFrames->release();	// win32 : memory leak	2010-0415
	}		
}

void SpriteOffsetAnchorScale::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteOffsetAnchorScale::title()
{
	return "Sprite offset + anchor + scale";
}

//------------------------------------------------------------------
//
// SpriteSheetOffsetAnchorScale
//
//------------------------------------------------------------------
SpriteSheetOffsetAnchorScale::SpriteSheetOffsetAnchorScale()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	for(int i=0;i<3;i++) 
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_gray.plist");
		
		//
		// Animation using Sprite Sheet
		//
		CCSprite* sprite = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
		sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
		
		CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
		point->setScale( 0.25f );
		point->setPosition( sprite->getPosition() );
		addChild(point, 200);
		
		switch(i) {
			case 0:
				sprite->setAnchorPoint( CCPointZero );
				break;
			case 1:
				sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
				break;
			case 2:
				sprite->setAnchorPoint( ccp(1,1) );
				break;
		}
		
		point->setPosition( sprite->getPosition() );
		
		CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png");
		addChild(spritesheet);
		
		CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(14);
        char str[100] = {0};
		for(int k = 0; k < 14; k++) 
		{
            sprintf(str, "grossini_dance_%02d.png",(k+1));
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
			animFrames->addObject(frame);
		}

		CCAnimation *animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
		sprite->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ) );

		CCActionInterval* scale = CCScaleBy::actionWithDuration(2, 2);
		CCActionInterval* scale_back = scale->reverse();
		CCActionInterval* seq_scale = (CCActionInterval*)(CCSequence::actions(scale, scale_back, NULL) );
		sprite->runAction(CCRepeatForever::actionWithAction(seq_scale) );
		
		spritesheet->addChild(sprite, i);

		animFrames->release();	// win32 : memory leak	2010-0415
	}		
}

void SpriteSheetOffsetAnchorScale::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetOffsetAnchorScale::title()
{
	return "SpriteSheet offset + anchor + scale";
}

//------------------------------------------------------------------
//
// SpriteAnimationSplit
//
//------------------------------------------------------------------

SpriteAnimationSplit::SpriteAnimationSplit()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("animations/dragon_animation.png");
	
	// manually add frames to the frame cache
	CCSpriteFrame *frame0 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*0, 132*0, 132, 132));
	CCSpriteFrame *frame1 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*1, 132*0, 132, 132));
	CCSpriteFrame *frame2 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*2, 132*0, 132, 132));
	CCSpriteFrame *frame3 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*3, 132*0, 132, 132));
	CCSpriteFrame *frame4 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*0, 132*1, 132, 132));
	CCSpriteFrame *frame5 = CCSpriteFrame::frameWithTexture(texture, CCRectMake(132*1, 132*1, 132, 132));
	
	
	//
	// Animation using Sprite Sheet
	//
	CCSprite* sprite = CCSprite::spriteWithSpriteFrame(frame0);
	sprite->setPosition( ccp( s.width/2-80, s.height/2) );
	addChild(sprite);
			
	CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(6);
	animFrames->addObject(frame0);
	animFrames->addObject(frame1);
	animFrames->addObject(frame2);
	animFrames->addObject(frame3);
	animFrames->addObject(frame4);
	animFrames->addObject(frame5);
			
	CCAnimation *animation = CCAnimation::animationWithName("fly", 0.2f, animFrames);
	CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( animate,
					   CCFlipX::actionWithFlipX(true),
					   animate->copy()->autorelease(),
					   CCFlipX::actionWithFlipX(false),
					   NULL) );
	
	sprite->runAction(CCRepeatForever::actionWithAction( seq ) );
	animFrames->release();	// win32 : memory leak	2010-0415
}

void SpriteAnimationSplit::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteAnimationSplit::title()
{
	return "Sprite: Animation + flip";
}

//------------------------------------------------------------------
//
// SpriteHybrid
//
//------------------------------------------------------------------
SpriteHybrid::SpriteHybrid()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// parents
	CCNode *parent1 = CCNode::node();
	CCSpriteBatchNode *parent2 = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	
	addChild(parent1, 0, kTagNode);
	addChild(parent2, 0, kTagSpriteSheet);
	
	
	// IMPORTANT:
	// The sprite frames will be cached AND RETAINED, and they won't be released unless you call
	//     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	
	// create 250 sprites
	// only show 80% of them
	for(int i = 0; i < 250; i++) 
	{
		int spriteIdx = CCRANDOM_0_1() * 14;
        char str[25] = {0};
        sprintf(str, "grossini_dance_%02d.png", (spriteIdx+1));
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		CCSprite* sprite = CCSprite::spriteWithSpriteFrame(frame);
		parent1->addChild(sprite, i, i);
		
		float x=-1000;
		float y=-1000;
		if( CCRANDOM_0_1() < 0.2f ) 
		{
			x = CCRANDOM_0_1() * s.width;
			y = CCRANDOM_0_1() * s.height;
		}
		sprite->setPosition( ccp(x,y) );
			
		CCActionInterval* action = CCRotateBy::actionWithDuration(4, 360);
		sprite->runAction( CCRepeatForever::actionWithAction(action) );
	}
	
	m_usingSpriteSheet = false;
	
	schedule( schedule_selector(SpriteHybrid::reparentSprite), 2);
}

void SpriteHybrid::reparentSprite(ccTime dt)
{
	CCNode *p1 = getChildByTag(kTagNode);
	CCNode *p2 = getChildByTag( kTagSpriteSheet );
	
	CCMutableArray<CCNode*>* retArray = new CCMutableArray<CCNode*>(250);

	if( m_usingSpriteSheet )
		CC_SWAP(p1,p2, CCNode*);

	////----UXLOG("New parent is: %x", p2);
	
	CCNode* node;
	CCMutableArray<CCNode*>::CCMutableArrayIterator it;
	CCMutableArray<CCNode*>* children = p1->getChildren();
	for(it = children->begin(); it != children->end(); it++)
	{
		node = (CCNode*)(*it);
		if(! node )
			break;

		retArray->addObject(node);
	}

	int i=0;
	p1->removeAllChildrenWithCleanup(false);

	for(it = retArray->begin(); it != retArray->end(); it++)
	{
		node = (CCNode*)(*it);
		if(! node)
			break;

		p2->addChild(node, i, i);
		i++;
	}

	m_usingSpriteSheet = ! m_usingSpriteSheet;

	retArray->release();
}

void SpriteHybrid::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteHybrid::title()
{
	return "HybrCCSprite* sprite Test";
}

//------------------------------------------------------------------
//
// SpriteSheetChildren
//
//------------------------------------------------------------------

SpriteSheetChildren::SpriteSheetChildren()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	// parents
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	
	addChild(sheet, 0, kTagSpriteSheet);
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	CCSprite* sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp( s.width/3, s.height/2));
	
	CCSprite* sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(50,50));
	
	CCSprite* sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-50,-50));
	
	sheet->addChild(sprite1);
	sprite1->addChild(sprite2);
	sprite1->addChild(sprite3);
	
	// BEGIN NEW CODE
	CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>();
    char str[100] = {0};
	for(int i = 1; i < 15; i++) 
	{
        sprintf(str, "grossini_dance_%02d.png",i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	
	CCAnimation* animation = CCAnimation::animationWithName("dance", 0.2f, animFrames);
	sprite1->runAction(CCRepeatForever::actionWithAction( CCAnimate::actionWithAnimation(animation, false) ) );
	// END NEW CODE
	
	CCActionInterval* action = CCMoveBy::actionWithDuration(2, ccp(200,0));
	CCActionInterval* action_back = action->reverse();
	CCActionInterval* action_rot = CCRotateBy::actionWithDuration(2, 360);
	CCActionInterval* action_s = CCScaleBy::actionWithDuration(2, 2);
	CCActionInterval* action_s_back = action_s->reverse();
	
	CCActionInterval* seq2 = action_rot->reverse();
	sprite2->runAction( CCRepeatForever::actionWithAction(seq2) );
	
	sprite1->runAction( (CCAction*)(CCRepeatForever::actionWithAction(action_rot)) );
	sprite1->runAction( (CCAction*)(CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(action, action_back,NULL)) )));
	sprite1->runAction( (CCAction*)(CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(action_s, action_s_back,NULL)))) );

	animFrames->release();
		
}

void SpriteSheetChildren::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetChildren::title()
{
	return "SpriteSheet Grand Children";
}


//------------------------------------------------------------------
//
// SpriteSheetChildren2
//
//------------------------------------------------------------------

SpriteSheetChildren2::SpriteSheetChildren2()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	// parents
	CCSpriteBatchNode* sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	sheet->getTexture()->generateMipmap();
	
	addChild(sheet, 0, kTagSpriteSheet);
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	
	CCSprite* sprite11 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite11->setPosition(ccp( s.width/3, s.height/2));

	CCSprite* sprite12 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite12->setPosition(ccp(20,30));
	sprite12->setScale( 0.2f );

	CCSprite* sprite13 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite13->setPosition(ccp(-20,30));
	sprite13->setScale( 0.2f );
	
	sheet->addChild(sprite11);
	sprite11->addChild(sprite12, -2);
	sprite11->addChild(sprite13, 2);

	// don't rotate with it's parent
	sprite12->setHornorParentTransform((ccHonorParentTransform) (sprite12->getHornorParentTransform() & ~CC_HONOR_PARENT_TRANSFORM_ROTATE));

	// don't scale and rotate with it's parent
	sprite13->setHornorParentTransform((ccHonorParentTransform) (sprite13->getHornorParentTransform() & ~(CC_HONOR_PARENT_TRANSFORM_SCALE | CC_HONOR_PARENT_TRANSFORM_ROTATE) ));
	
	CCActionInterval* action = CCMoveBy::actionWithDuration(2, ccp(200,0));
	CCActionInterval* action_back = action->reverse();
	CCActionInterval* action_rot = CCRotateBy::actionWithDuration(2, 360);
	CCActionInterval* action_s = CCScaleBy::actionWithDuration(2, 2);
	CCActionInterval* action_s_back = action_s->reverse();

	sprite11->runAction( CCRepeatForever::actionWithAction(action_rot));
	sprite11->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(action, action_back,NULL))));
	sprite11->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(action_s, action_s_back,NULL))));
	
	//
	// another set of parent / children
	//
	
	CCSprite* sprite21 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite21->setPosition(ccp( 2*s.width/3, s.height/2-50));
	
	CCSprite* sprite22 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite22->setPosition(ccp(20,30));
	sprite22->setScale( 0.8f );
	
	CCSprite* sprite23 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite23->setPosition(ccp(-20,30));
	sprite23->setScale( 0.8f );
	
	sheet->addChild(sprite21);
	sprite21->addChild(sprite22, -2);
	sprite21->addChild(sprite23, 2);
	
	// don't rotate with it's parent
	sprite22->setHornorParentTransform((ccHonorParentTransform) (sprite22->getHornorParentTransform() & ~CC_HONOR_PARENT_TRANSFORM_TRANSLATE));
	
	// don't scale and rotate with it's parent
	sprite23->setHornorParentTransform((ccHonorParentTransform) (sprite23->getHornorParentTransform() & ~CC_HONOR_PARENT_TRANSFORM_SCALE));
	
	sprite21->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(1, 360) ));
	sprite21->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions( CCScaleTo::actionWithDuration(0.5f, 5.0f), CCScaleTo::actionWithDuration(0.5f, 1), NULL ) )) );
}

void SpriteSheetChildren2::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetChildren2::title()
{
	return "SpriteSheet HonorTransform";
}

//------------------------------------------------------------------
//
// SpriteSheetChildrenZ
//
//------------------------------------------------------------------
SpriteSheetChildrenZ::SpriteSheetChildrenZ()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	// parents
	CCSpriteBatchNode* sheet;
	CCSprite* sprite1, *sprite2, *sprite3;

	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	// test 1
	sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp( s.width/3, s.height/2));
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sheet->addChild(sprite1);
	sprite1->addChild(sprite2, 2);
	sprite1->addChild(sprite3, -2);
	
	// test 2
	sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp( 2*s.width/3, s.height/2));
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sheet->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, 2);
	
	// test 3
	sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp( s.width/2 - 90, s.height/4));
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp( s.width/2 - 60,s.height/4));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp( s.width/2 - 30, s.height/4));
	
	sheet->addChild(sprite1, 10);
	sheet->addChild(sprite2, -10);
	sheet->addChild(sprite3, -5);

	// test 4
	sheet = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	addChild(sheet, 0, kTagSpriteSheet);
	
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp( s.width/2 +30, s.height/4));
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp( s.width/2 +60,s.height/4));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp( s.width/2 +90, s.height/4));
	
	sheet->addChild(sprite1, -10);
	sheet->addChild(sprite2, -5);
	sheet->addChild(sprite3, -2);
}

void SpriteSheetChildrenZ::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetChildrenZ::title()
{
	return "SpriteSheet Children Z";
}

//------------------------------------------------------------------
//
// SpriteChildrenVisibility
//
//------------------------------------------------------------------

SpriteChildrenVisibility::SpriteChildrenVisibility()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");

	CCNode *aParent;
	CCSprite* sprite1, *sprite2, *sprite3;
	//
	// SpriteSheet
	//
	// parents
	aParent = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	aParent->setPosition( ccp(s.width/3, s.height/2) );
	addChild(aParent, 0);
	
	
	
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp(0,0));
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, 2);
	
	sprite1->runAction(CCBlink::actionWithDuration(5, 10));
	
	//
	// Sprite
	//
	aParent = CCNode::node();
	aParent->setPosition( ccp(2*s.width/3, s.height/2) );
	addChild(aParent, 0);

	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_01.png");
	sprite1->setPosition(ccp(0,0));
			
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, 2);
	
	sprite1->runAction(CCBlink::actionWithDuration(5, 10));
}

void SpriteChildrenVisibility::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteChildrenVisibility::title()
{
	return "Sprite & SpriteSheet Visibility";
}

//------------------------------------------------------------------
//
// SpriteChildrenAnchorPoint
//
//------------------------------------------------------------------
SpriteChildrenAnchorPoint::SpriteChildrenAnchorPoint()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	CCNode *aParent;
	CCSprite* sprite1, *sprite2, *sprite3, *sprite4, *point;
	//
	// SpriteSheet
	//
	// parents
	
	aParent = CCNode::node();
	addChild(aParent, 0);
	
	// anchor (0,0)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/4,s.height/2));
	sprite1->setAnchorPoint( ccp(0,0) );

	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );

	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);
	
	
	// anchor (0.5, 0.5)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/2,s.height/2));
	sprite1->setAnchorPoint( ccp(0.5f, 0.5f) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));

	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));

	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );		

	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);		
	
	
	// anchor (1,1)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/2+s.width/4,s.height/2));
	sprite1->setAnchorPoint( ccp(1,1) );

	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );		
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);		
}

void SpriteChildrenAnchorPoint::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteChildrenAnchorPoint::title()
{
	return "Sprite: children + anchor";
}

//------------------------------------------------------------------
//
// SpriteSheetChildrenAnchorPoint
//
//------------------------------------------------------------------
SpriteSheetChildrenAnchorPoint::SpriteSheetChildrenAnchorPoint()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
	
	CCNode *aParent;
	CCSprite* sprite1, *sprite2, *sprite3, *sprite4, *point;
	//
	// SpriteSheet
	//
	// parents
	
	aParent = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini.png", 50);
	addChild(aParent, 0);
	
	// anchor (0,0)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/4,s.height/2));
	sprite1->setAnchorPoint( ccp(0,0) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);
	
	
	// anchor (0.5, 0.5)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/2,s.height/2));
	sprite1->setAnchorPoint( ccp(0.5f, 0.5f) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );		
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);		
	
	
	// anchor (1,1)
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossini_dance_08.png");
	sprite1->setPosition(ccp(s.width/2+s.width/4,s.height/2));
	sprite1->setAnchorPoint( ccp(1,1) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossini_dance_02.png");
	sprite2->setPosition(ccp(20,30));
	
	sprite3 = CCSprite::spriteWithSpriteFrameName("grossini_dance_03.png");
	sprite3->setPosition(ccp(-20,30));
	
	sprite4 = CCSprite::spriteWithSpriteFrameName("grossini_dance_04.png");
	sprite4->setPosition(ccp(0,0));
	sprite4->setScale( 0.5f );		
	
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2, -2);
	sprite1->addChild(sprite3, -2);
	sprite1->addChild(sprite4, 3);
	
	point = CCSprite::spriteWithFile("Images/r1.png");
	point->setScale( 0.25f );
	point->setPosition( sprite1->getPosition() );
	addChild(point, 10);		
}

void SpriteSheetChildrenAnchorPoint::onExit()
{
	SpriteTestDemo::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteSheetChildrenAnchorPoint::title()
{
	return "SpriteSheet: children + anchor";
}

//------------------------------------------------------------------
//
// SpriteSheetChildrenScale
//
//------------------------------------------------------------------
SpriteSheetChildrenScale::SpriteSheetChildrenScale()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_family.plist");

	CCNode *aParent;
	CCSprite* sprite1, *sprite2;
	CCActionInterval* rot = CCRotateBy::actionWithDuration(10, 360);
	CCAction* seq = CCRepeatForever::actionWithAction(rot);
	
	//
	// Children + Scale using Sprite
	// Test 1
	//
	aParent = CCNode::node();
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossinis_sister1.png");
	sprite1->setPosition( ccp( s.width/4, s.height/4) );
	sprite1->setScaleX( -0.5f );
	sprite1->setScaleY( 2.0f );
	sprite1->runAction(seq);
	
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossinis_sister2.png");
	sprite2->setPosition( ccp( 50,0) );
	
	addChild(aParent);
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2);

	
	//
	// Children + Scale using SpriteSheet
	// Test 2
	//
	
	aParent = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini_family.png");
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossinis_sister1.png");
	sprite1->setPosition( ccp( 3*s.width/4, s.height/4) );
	sprite1->setScaleX( -0.5f );
	sprite1->setScaleY( 2.0f );
	sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossinis_sister2.png");
	sprite2->setPosition( ccp( 50,0) );
	
	addChild(aParent);
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2);

	
	//
	// Children + Scale using Sprite
	// Test 3
	//
	
	aParent = CCNode::node();
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossinis_sister1.png");
	sprite1->setPosition( ccp( s.width/4, 2*s.height/3) );
	sprite1->setScaleX( 1.5f );
	sprite1->setScaleY( -0.5f );
	sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossinis_sister2.png");
	sprite2->setPosition( ccp( 50,0) );
	
	addChild(aParent);
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2);
	
	//
	// Children + Scale using Sprite
	// Test 4
	//
	
	aParent = CCSpriteBatchNode::spriteSheetWithFile("animations/grossini_family.png");
	sprite1 = CCSprite::spriteWithSpriteFrameName("grossinis_sister1.png");
	sprite1->setPosition( ccp( 3*s.width/4, 2*s.height/3) );
	sprite1->setScaleX( 1.5f );
	sprite1->setScaleY( -0.5f);
	sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
	
	sprite2 = CCSprite::spriteWithSpriteFrameName("grossinis_sister2.png");
	sprite2->setPosition( ccp( 50,0) );
	
	addChild(aParent);
	aParent->addChild(sprite1);
	sprite1->addChild(sprite2);
	
}

std::string SpriteSheetChildrenScale::title()
{
	return "Sprite/Sheet + child + scale + rot";
}

//------------------------------------------------------------------
//
// SpriteChildrenChildren
//
//------------------------------------------------------------------
SpriteChildrenChildren::SpriteChildrenChildren()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");
	
	CCNode *aParent;
	CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;
	CCActionInterval* rot = CCRotateBy::actionWithDuration(10, 360);
	CCAction* seq = CCRepeatForever::actionWithAction(rot);
	
	CCActionInterval* rot_back = rot->reverse();
	CCAction* rot_back_fe = CCRepeatForever::actionWithAction(rot_back);
	
	//
	// SpriteSheet: 3 levels of children
	//
	
	aParent = CCNode::node();
	addChild(aParent);
	
	// parent
	l1 = CCSprite::spriteWithSpriteFrameName("father.gif");
	l1->setPosition( ccp( s.width/2, s.height/2) );
	l1->runAction( (CCAction*)(seq->copy()->autorelease()) );
	aParent->addChild(l1);
	CCSize l1Size = l1->getContentSize();
	
	// child left
	l2a = CCSprite::spriteWithSpriteFrameName("sister1.gif");
	l2a->setPosition( ccp( -50 + l1Size.width/2, 0 + l1Size.height/2) );
	l2a->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
	l1->addChild(l2a);
	CCSize l2aSize = l2a->getContentSize();		
	
	
	// child right
	l2b = CCSprite::spriteWithSpriteFrameName("sister2.gif");
	l2b->setPosition( ccp( +50 + l1Size.width/2, 0 + l1Size.height/2) );
	l2b->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
	l1->addChild(l2b);
	CCSize l2bSize = l2a->getContentSize();		
	
	
	// child left bottom
	l3a1 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3a1->setScale( 0.45f );
	l3a1->setPosition( ccp(0+l2aSize.width/2,-100+l2aSize.height/2) );
	l2a->addChild(l3a1);
	
	// child left top
	l3a2 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3a2->setScale( 0.45f );
	l3a1->setPosition( ccp(0+l2aSize.width/2,+100+l2aSize.height/2) );
	l2a->addChild(l3a2);
	
	// child right bottom
	l3b1 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3b1->setScale( 0.45f);
	l3b1->setFlipY( true );
	l3b1->setPosition( ccp(0+l2bSize.width/2,-100+l2bSize.height/2) );
	l2b->addChild(l3b1);
	
	// child right top
	l3b2 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3b2->setScale( 0.45f );
	l3b2->setFlipY( true );
	l3b1->setPosition( ccp(0+l2bSize.width/2,+100+l2bSize.height/2) );
	l2b->addChild(l3b2);
}

std::string SpriteChildrenChildren::title()
{
	return "Sprite multiple levels of children";
}


//------------------------------------------------------------------
//
// SpriteSheetChildrenChildren
//
//------------------------------------------------------------------

SpriteSheetChildrenChildren::SpriteSheetChildrenChildren()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();		
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");
	
	CCSpriteBatchNode *aParent;
	CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;
	CCActionInterval* rot = CCRotateBy::actionWithDuration(10, 360);
	CCAction* seq = CCRepeatForever::actionWithAction(rot);
	
	CCActionInterval* rot_back = rot->reverse();
	CCAction* rot_back_fe = CCRepeatForever::actionWithAction(rot_back);
	
	//
	// SpriteSheet: 3 levels of children
	//
	
	aParent = CCSpriteBatchNode::spriteSheetWithFile("animations/ghosts.png");
	aParent->getTexture()->generateMipmap();
	addChild(aParent);
	
	// parent
	l1 = CCSprite::spriteWithSpriteFrameName("father.gif");
	l1->setPosition( ccp( s.width/2, s.height/2) );
	l1->runAction( (CCAction*)(seq->copy()->autorelease()) );
	aParent->addChild(l1);
	CCSize l1Size = l1->getContentSize();

	// child left
	l2a = CCSprite::spriteWithSpriteFrameName("sister1.gif");
	l2a->setPosition( ccp( -50 + l1Size.width/2, 0 + l1Size.height/2) );
	l2a->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
	l1->addChild(l2a);
	CCSize l2aSize = l2a->getContentSize();		


	// child right
	l2b = CCSprite::spriteWithSpriteFrameName("sister2.gif");
	l2b->setPosition( ccp( +50 + l1Size.width/2, 0 + l1Size.height/2) );
	l2b->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
	l1->addChild(l2b);
	CCSize l2bSize = l2a->getContentSize();		

	
	// child left bottom
	l3a1 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3a1->setScale( 0.45f );
	l3a1->setPosition( ccp(0+l2aSize.width/2,-100+l2aSize.height/2) );
	l2a->addChild(l3a1);
	
	// child left top
	l3a2 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3a2->setScale( 0.45f );
	l3a1->setPosition( ccp(0+l2aSize.width/2,+100+l2aSize.height/2) );
	l2a->addChild(l3a2);
	
	// child right bottom
	l3b1 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3b1->setScale( 0.45f );
	l3b1->setFlipY( true );
	l3b1->setPosition( ccp(0+l2bSize.width/2,-100+l2bSize.height/2) );
	l2b->addChild(l3b1);

	// child right top
	l3b2 = CCSprite::spriteWithSpriteFrameName("child1.gif");
	l3b2->setScale( 0.45f );
	l3b2->setFlipY( true );
	l3b1->setPosition( ccp(0+l2bSize.width/2,+100+l2bSize.height/2) );
	l2b->addChild(l3b2);
	
}

std::string SpriteSheetChildrenChildren::title()
{
	return "SpriteSheet multiple levels of children";
}

//------------------------------------------------------------------
//
// SpriteNilTexture
//
//------------------------------------------------------------------

SpriteNilTexture::SpriteNilTexture()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite* sprite = NULL;
	
	// TEST: If no texture is given, then Opacity + Color should work.

	sprite = new CCSprite();
	sprite->setTextureRect( CCRectMake(0, 0, 300,300) );
	sprite->setColor(ccRED);
	sprite->setOpacity(128);
	sprite->setPosition(ccp(3*s.width/4, s.height/2));
	addChild(sprite, 100);
    sprite->release();

	sprite = new CCSprite();
	sprite->setTextureRect(CCRectMake(0, 0, 300,300));
	sprite->setColor(ccBLUE);
	sprite->setOpacity(128);
	sprite->setPosition(ccp(1*s.width/4, s.height/2));
	addChild(sprite, 100);
    sprite->release();
}

std::string SpriteNilTexture::title()
{
	return "Sprite without texture";
}

std::string SpriteNilTexture::subtitle()
{
	return "opacity and color should work";
}

void SpriteTestScene::runThisTest()
{
    CCLayer* pLayer = nextSpriteTestAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
