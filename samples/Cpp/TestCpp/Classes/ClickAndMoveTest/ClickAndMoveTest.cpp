#include "ClickAndMoveTest.h"
#include "../testResource.h"

enum
{
    kTagSprite = 1,
};

void ClickAndMoveTestScene::runThisTest()
{
    Layer* pLayer = new MainLayer();
    pLayer->autorelease();

    addChild(pLayer);
    Director::sharedDirector()->replaceScene(this);
}

MainLayer::MainLayer()
{
    setTouchEnabled(true);
    
    Sprite* sprite = Sprite::create(s_pPathGrossini);
    
    Layer* layer = LayerColor::create(ccc4(255,255,0,255));
    addChild(layer, -1);
        
    addChild(sprite, 0, kTagSprite);
    sprite->setPosition( ccp(20,150) );
    
    sprite->runAction( JumpTo::create(4, ccp(300,48), 100, 4) );
    
    layer->runAction( RepeatForever::create(
                                Sequence::create(
                                        FadeIn::create(1),
                                        FadeOut::create(1),
                                        NULL)
                      )); 
}

void MainLayer::ccTouchesEnded(Set *pTouches, Event *pEvent)
{
    SetIterator it = pTouches->begin();
    Touch* touch = (Touch*)(*it);
    
    Point location = touch->getLocation();

    Node* s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(1, ccp(location.x, location.y) ) );
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
    
    s->runAction( RotateTo::create(1, at) );
}
