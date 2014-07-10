#include "ClickAndMoveTest.h"
#include "../testResource.h"

enum
{
    kTagSprite = 1,
};

void ClickAndMoveTestScene::runThisTest()
{
    auto layer = new MainLayer();
    layer->autorelease();

    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

MainLayer::MainLayer()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto sprite = Sprite::create(s_pathGrossini);
    
    auto layer = LayerColor::create(Color4B(255,255,0,255));
    addChild(layer, -1);
        
    addChild(sprite, 0, kTagSprite);
    sprite->setPosition( Vec2(20,150) );
    
    sprite->runAction( JumpTo::create(4, Vec2(300,48), 100, 4) );
    
    layer->runAction( RepeatForever::create(
                                Sequence::create(
                                        FadeIn::create(1),
                                        FadeOut::create(1),
                                        nullptr)
                      )); 
}

bool MainLayer::onTouchBegan(Touch* touch, Event  *event)
{
    return true;
}

void MainLayer::onTouchEnded(Touch* touch, Event  *event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(1, Vec2(location.x, location.y) ) );
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
