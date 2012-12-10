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
    setTouchEnabled(true);
    
    CCSprite* sprite = CCSprite::create(s_pPathGrossini);
    
    CCLayer* layer = CCLayerColor::create(ccc4(255,255,0,255));
    addChild(layer, -1);
        
    addChild(sprite, 0, kTagSprite);
    sprite->setPosition( ccp(20,150) );
    
    sprite->runAction( CCJumpTo::create(4, ccp(300,48), 100, 4) );
    
    layer->runAction( CCRepeatForever::create(
                                CCSequence::create(
                                        CCFadeIn::create(1),
                                        CCFadeOut::create(1),
                                        NULL)
                      )); 
}

void MainLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint location = touch->getLocation();

    CCNode* s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( CCMoveTo::create(1, ccp(location.x, location.y) ) );
    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
    
    if( a < 0 ) 
    {
        if(  o < 0 )
            at = 180 + fabs(at);
        else
            at = 180 - fabs(at);    
    }
    
    s->runAction( CCRotateTo::create(1, at) );
}
