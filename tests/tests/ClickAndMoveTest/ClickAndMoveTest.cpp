#include "ClickAndMoveTest.h"
#include "../testResource.h"

enum
{
	kTagSprite = 1,
};

void ClickAndMoveTestScene::runThisTest()
{
    CCLayer* pLayer = new MainLayer();
    pLayer->autorelease();

    addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(this);
}

MainLayer::MainLayer()
{
	setIsTouchEnabled(true);
	
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	
	CCLayer* layer = CCLayerColor::layerWithColor(ccc4f(255,255,0,255));
	addChild(layer, -1);
		
	addChild(sprite, 0, kTagSprite);
	sprite->setPosition( CCPointMake(20,150) );
	
	sprite->runAction( CCJumpTo::actionWithDuration(4, CCPointMake(300,48), 100, 4) );
	
	layer->runAction( CCRepeatForever::actionWithAction( 
														(CCActionInterval*)( CCSequence::actions(	
																			CCFadeIn::actionWithDuration(1),
																			CCFadeOut::actionWithDuration(1),
																			NULL) )
														) ); 
}

void MainLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	
	CCPoint location = touch->locationInView();
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	CCNode* s = getChildByTag(kTagSprite);
	s->stopAllActions();
	s->runAction( CCMoveTo::actionWithDuration(1, CCPointMake(convertedLocation.x, convertedLocation.y) ) );
	float o = convertedLocation.x - s->getPosition().x;
	float a = convertedLocation.y - s->getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
	
	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);	
	}
	
	s->runAction( CCRotateTo::actionWithDuration(1, at) );
}
