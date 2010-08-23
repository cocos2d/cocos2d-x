#include "ClickAndMoveTest.h"
#include "CCDirector.h"
#include "CCSprite.h"
#include "../testResource.h"
#include "CCIntervalAction.h"
#include "CCInstantAction.h"
#include "touch_dispatcher/CCTouch.h"
#include "NSSet.h"

enum
{
	kTagSprite = 1,
};

void ClickAndMoveTestScene::runThisTest()
{
    CCLayer* pLayer = new MainLayer();
    pLayer->autorelease();

    addChild(pLayer);
    CCDirector::getSharedDirector()->replaceScene(this);
}

MainLayer::MainLayer()
{
	setIsTouchEnabled(true);
	
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	
	CCLayer* layer = CCColorLayer::layerWithColor(ccc4(255,255,0,255));
	addChild(layer, -1);
		
	addChild(sprite, 0, kTagSprite);
	sprite->setPosition( CGPointMake(20,150) );
	
	sprite->runAction( CCJumpTo::actionWithDuration(4, CGPointMake(300,48), 100, 4) );
	
	layer->runAction( CCRepeatForever::actionWithAction( 
														dynamic_cast<CCIntervalAction*>( CCSequence::actions(	
																			CCFadeIn::actionWithDuration(1),
																			CCFadeOut::actionWithDuration(1),
																			NULL) )
														) ); 
}

void MainLayer::ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent)
{
    NSSetIterator it = pTouches->begin();
	CCTouch* touch = dynamic_cast<CCTouch*>(*it);
	
	CGPoint location = touch->locationInView( touch->view() );
	CGPoint convertedLocation = CCDirector::getSharedDirector()->convertToGL(location);

	CCNode* s = getChildByTag(kTagSprite);
	s->stopAllActions();
	s->runAction( CCMoveTo::actionWithDuration(1, CGPointMake(convertedLocation.x, convertedLocation.y) ) );
	float o = convertedLocation.x - s->getPosition().x;
	float a = convertedLocation.y - s->getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
	
	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + abs(at);
		else
			at = 180 - abs(at);	
	}
	
	s->runAction( CCRotateTo::actionWithDuration(1, at) );
}
