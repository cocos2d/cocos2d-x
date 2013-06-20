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
    
    Size size = Director::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;

    //CCMutableArray *array = [UIFont familyNames];
    //for( String *s in array )
    //    NSLog( s );
    LabelTTF* label = LabelTTF::create("cocos2d", "Tahoma", 64);

    label->setPosition( ccp(x/2,y/2) );
    
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
    
    Size size = Director::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;
    
    Sprite* sprite = Sprite::create(s_pPathGrossini);
    Sprite* spriteSister1 = Sprite::create(s_pPathSister1);
    Sprite* spriteSister2 = Sprite::create(s_pPathSister2);
    
    sprite->setScale(1.5f);
    spriteSister1->setScale(1.5f);
    spriteSister2->setScale(1.5f);
    
    sprite->setPosition(ccp(x/2,y/2));
    spriteSister1->setPosition(ccp(40,y/2));
    spriteSister2->setPosition(ccp(x-40,y/2));

    Action *rot = RotateBy::create(16, -3600);
    
    addChild(sprite);
    addChild(spriteSister1);
    addChild(spriteSister2);
    
    sprite->runAction(rot);

    ActionInterval *jump1 = JumpBy::create(4, ccp(-400,0), 100, 4);
    ActionInterval *jump2 = jump1->reverse();
    
    ActionInterval *rot1 = RotateBy::create(4, 360*2);
    ActionInterval *rot2 = rot1->reverse();
    
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
    
    Size size = Director::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;
    
    Node* blue =  LayerColor::create(ccc4(0,0,255,255));
    Node* red =   LayerColor::create(ccc4(255,0,0,255));
    Node* green = LayerColor::create(ccc4(0,255,0,255));
    Node* white = LayerColor::create(ccc4(255,255,255,255));

    blue->setScale(0.5f);
    blue->setPosition(ccp(-x/4,-y/4));
    blue->addChild( SpriteLayer::create() );
    
    red->setScale(0.5f);
    red->setPosition(ccp(x/4,-y/4));

    green->setScale(0.5f);
    green->setPosition(ccp(-x/4,y/4));
    green->addChild(TestLayer::create());

    white->setScale(0.5f);
    white->setPosition(ccp(x/4,y/4));
    white->ignoreAnchorPointForPosition(false);
    white->setPosition(ccp(x/4*3,y/4*3));

    addChild(blue, -1);
    addChild(white);
    addChild(green);
    addChild(red);

    Action* rot = RotateBy::create(8, 720);
    
    blue->runAction(rot);
    red->runAction(rot->clone());
    green->runAction(rot->clone());
    white->runAction(rot->clone());
}

void RotateWorldTestScene::runThisTest()
{
    Layer* pLayer = RotateWorldMainLayer::create();

    addChild(pLayer);
    runAction( RotateBy::create(4, -360) );

    Director::sharedDirector()->replaceScene(this);

}
