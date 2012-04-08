#include "RotateWorldTest.h"
#include "../testResource.h"

//------------------------------------------------------------------
//
// TestLayer
//
//------------------------------------------------------------------
void TestLayer::onEnter()
{
	CCLayer::onEnter();

	float x,y;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;

	//CCMutableArray *array = [UIFont familyNames];
	//for( CCString *s in array )
	//	NSLog( s );
	CCLabelTTF* label = CCLabelTTF::labelWithString("cocos2d", "Tahoma", 64);

	label->setPosition( CCPointMake(x/2,y/2) );
	
	addChild(label);
}

//------------------------------------------------------------------
//
// SpriteLayer
//
//------------------------------------------------------------------
void SpriteLayer::onEnter()
{
	CCLayer::onEnter();

	float x,y;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	CCSprite* spriteSister1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* spriteSister2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	sprite->setScale(1.5f);
	spriteSister1->setScale(1.5f);
	spriteSister2->setScale(1.5f);
	
	sprite->setPosition(CCPointMake(x/2,y/2));
	spriteSister1->setPosition(CCPointMake(40,y/2));
	spriteSister2->setPosition(CCPointMake(x-40,y/2));

	CCAction *rot = CCRotateBy::actionWithDuration(16, -3600);
	
	addChild(sprite);
	addChild(spriteSister1);
	addChild(spriteSister2);
	
	sprite->runAction(rot);

	CCActionInterval *jump1 = CCJumpBy::actionWithDuration(4, CCPointMake(-400,0), 100, 4);
	CCActionInterval *jump2 = jump1->reverse();
	
	CCActionInterval *rot1 = CCRotateBy::actionWithDuration(4, 360*2);
	CCActionInterval *rot2 = rot1->reverse();
	
	spriteSister1->runAction(CCRepeat::actionWithAction( CCSequence::actions(jump2, jump1, NULL), 5 ));
	spriteSister2->runAction(CCRepeat::actionWithAction( CCSequence::actions((CCFiniteTimeAction *)(jump1->copy()->autorelease()), (CCFiniteTimeAction *)(jump2->copy()->autorelease()), NULL), 5 ));
	
	spriteSister1->runAction(CCRepeat::actionWithAction( CCSequence::actions(rot1, rot2, NULL), 5 ));
	spriteSister2->runAction(CCRepeat::actionWithAction( CCSequence::actions((CCFiniteTimeAction *)(rot2->copy()->autorelease()), (CCFiniteTimeAction *)(rot1->copy()->autorelease()), NULL), 5 ));
}

//------------------------------------------------------------------
//
// RotateWorldMainLayer
//
//------------------------------------------------------------------

void RotateWorldMainLayer::onEnter()
{
	CCLayer::onEnter();

	float x,y;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCNode* blue =  CCLayerColor::layerWithColor(ccc4(0,0,255,255));
	CCNode* red =   CCLayerColor::layerWithColor(ccc4(255,0,0,255));
	CCNode* green = CCLayerColor::layerWithColor(ccc4(0,255,0,255));
	CCNode* white = CCLayerColor::layerWithColor(ccc4(255,255,255,255));

	blue->setScale(0.5f);
	blue->setPosition(CCPointMake(-x/4,-y/4));
	blue->addChild( SpriteLayer::node() );
	
	red->setScale(0.5f);
	red->setPosition(CCPointMake(x/4,-y/4));

	green->setScale(0.5f);
	green->setPosition(CCPointMake(-x/4,y/4));
	green->addChild(TestLayer::node());

	white->setScale(0.5f);
	white->setPosition(CCPointMake(x/4,y/4));

	addChild(blue, -1);
	addChild(white);
	addChild(green);
	addChild(red);

	CCAction* rot = CCRotateBy::actionWithDuration(8, 720);
	
	blue->runAction(rot);
	red->runAction((CCAction *)(rot->copy()->autorelease()));
	green->runAction((CCAction *)(rot->copy()->autorelease()) );
	white->runAction((CCAction *)(rot->copy()->autorelease()) );
}

void RotateWorldTestScene::runThisTest()
{
    CCLayer* pLayer = RotateWorldMainLayer::node();

    addChild(pLayer);
    runAction( CCRotateBy::actionWithDuration(4, -360) );

    CCDirector::sharedDirector()->replaceScene(this);

}
