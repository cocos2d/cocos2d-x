#include "RotateWorldTest.h"
#include "../testResource.h"
#include "CCLabel.h"
#include "CCDirector.h"
#include "CCMenu.h"
#include "CCIntervalAction.h"

//------------------------------------------------------------------
//
// TestLayer
//
//------------------------------------------------------------------
void TestLayer::onEnter()
{
	__super::onEnter();

	float x,y;
	
	CGSize size = CCDirector::getSharedDirector()->getWinSize();
	x = size.width;
	y = size.height;

	//NSArray *array = [UIFont familyNames];
	//for( NSString *s in array )
	//	NSLog( s );
	CCLabel* label = CCLabel::labelWithString("cocos2d", "Tahoma", 64);

	label->setPosition( CGPointMake(x/2,y/2) );
	
	addChild(label);
}

//------------------------------------------------------------------
//
// SpriteLayer
//
//------------------------------------------------------------------
void SpriteLayer::onEnter()
{
	__super::onEnter();

	float x,y;
	
	CGSize size = CCDirector::getSharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	CCSprite* spriteSister1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* spriteSister2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	sprite->setScale(1.5f);
	spriteSister1->setScale(1.5f);
	spriteSister2->setScale(1.5f);
	
	sprite->setPosition(CGPointMake(x/2,y/2));
	spriteSister1->setPosition(CGPointMake(40,y/2));
	spriteSister2->setPosition(CGPointMake(x-40,y/2));

	CCAction *rot = CCRotateBy::actionWithDuration(16, -3600);
	
	addChild(sprite);
	addChild(spriteSister1);
	addChild(spriteSister2);
	
	sprite->runAction(rot);

	CCIntervalAction *jump1 = CCJumpBy::actionWithDuration(4, CGPointMake(-400,0), 100, 4);
	CCIntervalAction *jump2 = jump1->reverse();
	
	CCIntervalAction *rot1 = CCRotateBy::actionWithDuration(4, 360*2);
	CCIntervalAction *rot2 = rot1->reverse();
	
	spriteSister1->runAction(CCRepeat::actionWithAction( CCSequence::actions(jump2, jump1, NULL), 5 ));
	spriteSister2->runAction(CCRepeat::actionWithAction( CCSequence::actions(dynamic_cast<CCFiniteTimeAction *>(jump1->copy()->autorelease()), dynamic_cast<CCFiniteTimeAction *>(jump2->copy()->autorelease()), NULL), 5 ));
	
	spriteSister1->runAction(CCRepeat::actionWithAction( CCSequence::actions(rot1, rot2, NULL), 5 ));
	spriteSister2->runAction(CCRepeat::actionWithAction( CCSequence::actions(dynamic_cast<CCFiniteTimeAction *>(rot2->copy()->autorelease()), dynamic_cast<CCFiniteTimeAction *>(rot1->copy()->autorelease()), NULL), 5 ));
}

//------------------------------------------------------------------
//
// RotateWorldMainLayer
//
//------------------------------------------------------------------

void RotateWorldMainLayer::onEnter()
{
	__super::onEnter();

	float x,y;
	
	CGSize size = CCDirector::getSharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCNode* blue =  CCColorLayer::layerWithColor(ccc4(0,0,255,255));
	CCNode* red =   CCColorLayer::layerWithColor(ccc4(255,0,0,255));
	CCNode* green = CCColorLayer::layerWithColor(ccc4(0,255,0,255));
	CCNode* white = CCColorLayer::layerWithColor(ccc4(255,255,255,255));

	blue->setScale(0.5f);
	blue->setPosition(CGPointMake(-x/4,-y/4));
	blue->addChild( SpriteLayer::node() );
	
	red->setScale(0.5f);
	red->setPosition(CGPointMake(x/4,-y/4));

	green->setScale(0.5f);
	green->setPosition(CGPointMake(-x/4,y/4));
	green->addChild(TestLayer::node());

	white->setScale(0.5f);
	white->setPosition(CGPointMake(x/4,y/4));

	addChild(blue, -1);
	addChild(white);
	addChild(green);
	addChild(red);

	CCAction* rot = CCRotateBy::actionWithDuration(8, 720);
	
	blue->runAction(rot);
	red->runAction( dynamic_cast<CCAction *>(rot->copy()->autorelease()) );
	green->runAction( dynamic_cast<CCAction *>(rot->copy()->autorelease()) );
	white->runAction( dynamic_cast<CCAction *>(rot->copy()->autorelease()) );
}

void RotateWorldTestScene::runThisTest()
{
    CCLayer* pLayer = RotateWorldMainLayer::node();

    addChild(pLayer);
    runAction( CCRotateBy::actionWithDuration(4, -360) );

    CCDirector::getSharedDirector()->replaceScene(this);

}
