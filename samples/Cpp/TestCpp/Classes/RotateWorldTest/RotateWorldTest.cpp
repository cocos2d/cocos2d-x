#include "RotateWorldTest.h"
#include "../testResource.h"

//------------------------------------------------------------------
//
// TestLayer
//
//------------------------------------------------------------------
void TestLayer::onEnter()
{
    Layer::onEnter();

    float x,y;
    
    auto size = Director::getInstance()->getWinSize();
    x = size.width;
    y = size.height;

    //auto array = [UIFont familyNames];
    //for( String *s in array )
    //    NSLog( s );
    auto label = LabelTTF::create("cocos2d", "Tahoma", 64);

    label->setPosition( Point(x/2,y/2) );
    
    addChild(label);
}

//------------------------------------------------------------------
//
// SpriteLayer
//
//------------------------------------------------------------------
void SpriteLayer::onEnter()
{
    Layer::onEnter();

    float x,y;
    
    auto size = Director::getInstance()->getWinSize();
    x = size.width;
    y = size.height;
    
    auto sprite = Sprite::create(s_pathGrossini);
    auto spriteSister1 = Sprite::create(s_pathSister1);
    auto spriteSister2 = Sprite::create(s_pathSister2);
    
    sprite->setScale(1.5f);
    spriteSister1->setScale(1.5f);
    spriteSister2->setScale(1.5f);
    
    sprite->setPosition(Point(x/2,y/2));
    spriteSister1->setPosition(Point(40,y/2));
    spriteSister2->setPosition(Point(x-40,y/2));

    auto rot = RotateBy::create(16, -3600);
    
    addChild(sprite);
    addChild(spriteSister1);
    addChild(spriteSister2);
    
    sprite->runAction(rot);

    auto jump1 = JumpBy::create(4, Point(-400,0), 100, 4);
    auto jump2 = jump1->reverse();
    
    auto rot1 = RotateBy::create(4, 360*2);
    auto rot2 = rot1->reverse();
    
    spriteSister1->runAction(Repeat::create( Sequence::create(jump2, jump1, NULL), 5 ));
    spriteSister2->runAction(Repeat::create( Sequence::create(jump1->clone(), jump2->clone(), NULL), 5 ));
    
    spriteSister1->runAction(Repeat::create( Sequence::create(rot1, rot2, NULL), 5 ));
    spriteSister2->runAction(Repeat::create( Sequence::create(rot2->clone(), rot1->clone(), NULL), 5 ));
}

//------------------------------------------------------------------
//
// RotateWorldMainLayer
//
//------------------------------------------------------------------

void RotateWorldMainLayer::onEnter()
{
    Layer::onEnter();

    float x,y;
    
    auto size = Director::getInstance()->getWinSize();
    x = size.width;
    y = size.height;
    
    auto blue =  LayerColor::create(Color4B(0,0,255,255));
    auto red =   LayerColor::create(Color4B(255,0,0,255));
    auto green = LayerColor::create(Color4B(0,255,0,255));
    auto white = LayerColor::create(Color4B(255,255,255,255));

    blue->setScale(0.5f);
    blue->setPosition(Point(-x/4,-y/4));
    blue->addChild( SpriteLayer::create() );
    
    red->setScale(0.5f);
    red->setPosition(Point(x/4,-y/4));

    green->setScale(0.5f);
    green->setPosition(Point(-x/4,y/4));
    green->addChild(TestLayer::create());

    white->setScale(0.5f);
    white->setPosition(Point(x/4,y/4));
    white->ignoreAnchorPointForPosition(false);
    white->setPosition(Point(x/4*3,y/4*3));

    addChild(blue, -1);
    addChild(white);
    addChild(green);
    addChild(red);

    auto rot = RotateBy::create(8, 720);
    
    blue->runAction(rot);
    red->runAction(rot->clone());
    green->runAction(rot->clone());
    white->runAction(rot->clone());
}

void RotateWorldTestScene::runThisTest()
{
    auto layer = RotateWorldMainLayer::create();

    addChild(layer);
    runAction( RotateBy::create(4, -360) );

    Director::getInstance()->replaceScene(this);

}
