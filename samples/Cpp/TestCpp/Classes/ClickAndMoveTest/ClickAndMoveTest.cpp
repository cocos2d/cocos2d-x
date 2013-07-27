#include "ClickAndMoveTest.h"
#include "../testResource.h"

enum
{
    kTagSprite = 1,
};

void ClickAndMoveTestScene::runThisTest()
{
    Layer* layer = new MainLayer();
    layer->autorelease();

    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

MainLayer::MainLayer()
{
    setTouchEnabled(true);
    
    Sprite* sprite = Sprite::create(s_pathGrossini);
    
    Layer* layer = LayerColor::create(Color4B(255,255,0,255));
    addChild(layer, -1);
        
    addChild(sprite, 0, kTagSprite);
    sprite->setPosition( Point(20,150) );
    
    sprite->runAction( JumpTo::create(4, Point(300,48), 100, 4) );
    
    layer->runAction( RepeatForever::create(
                                Sequence::create(
                                        FadeIn::create(1),
                                        FadeOut::create(1),
                                        NULL)
                      )); 
}

void MainLayer::ccTouchesEnded(Set  *touches, Event  *event)
{
    Touch* touch = static_cast<Touch*>( touches->anyObject() );
    
    Point location = touch->getLocation();

    Node* s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(1, Point(location.x, location.y) ) );
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
