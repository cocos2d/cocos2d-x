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
    //    NSLog( s );
    CCLabelTTF* label = CCLabelTTF::create("cocos2d", "Tahoma", 64);

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
    CCLayer::onEnter();

    float x,y;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    x = size.width;
    y = size.height;
    
    CCSprite* sprite = CCSprite::create(s_pPathGrossini);
    CCSprite* spriteSister1 = CCSprite::create(s_pPathSister1);
    CCSprite* spriteSister2 = CCSprite::create(s_pPathSister2);
    
    sprite->setScale(1.5f);
    spriteSister1->setScale(1.5f);
    spriteSister2->setScale(1.5f);
    
    sprite->setPosition(ccp(x/2,y/2));
    spriteSister1->setPosition(ccp(40,y/2));
    spriteSister2->setPosition(ccp(x-40,y/2));

    CCAction *rot = CCRotateBy::create(16, -3600);
    
    addChild(sprite);
    addChild(spriteSister1);
    addChild(spriteSister2);
    
    sprite->runAction(rot);

    CCActionInterval *jump1 = CCJumpBy::create(4, ccp(-400,0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();
    
    CCActionInterval *rot1 = CCRotateBy::create(4, 360*2);
    CCActionInterval *rot2 = rot1->reverse();
    
    spriteSister1->runAction(CCRepeat::create( CCSequence::create(jump2, jump1, NULL), 5 ));
    spriteSister2->runAction(CCRepeat::create( CCSequence::create((CCFiniteTimeAction *)(jump1->copy()->autorelease()), (CCFiniteTimeAction *)(jump2->copy()->autorelease()), NULL), 5 ));
    
    spriteSister1->runAction(CCRepeat::create( CCSequence::create(rot1, rot2, NULL), 5 ));
    spriteSister2->runAction(CCRepeat::create( CCSequence::create((CCFiniteTimeAction *)(rot2->copy()->autorelease()), (CCFiniteTimeAction *)(rot1->copy()->autorelease()), NULL), 5 ));
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
    
    CCNode* blue =  CCLayerColor::create(ccc4(0,0,255,255));
    CCNode* red =   CCLayerColor::create(ccc4(255,0,0,255));
    CCNode* green = CCLayerColor::create(ccc4(0,255,0,255));
    CCNode* white = CCLayerColor::create(ccc4(255,255,255,255));

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

    CCAction* rot = CCRotateBy::create(8, 720);
    
    blue->runAction(rot);
    red->runAction((CCAction *)(rot->copy()->autorelease()));
    green->runAction((CCAction *)(rot->copy()->autorelease()) );
    white->runAction((CCAction *)(rot->copy()->autorelease()) );
}

void RotateWorldTestScene::runThisTest()
{
    CCLayer* pLayer = RotateWorldMainLayer::create();

    addChild(pLayer);
    runAction( CCRotateBy::create(4, -360) );

    CCDirector::sharedDirector()->replaceScene(this);

}
