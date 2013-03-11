#include "SpriteTest.h"
#include "../testResource.h"


enum 
{
    kTagTileMap = 1,
    kTagSpriteBatchNode = 1,
    kTagNode = 2,
    kTagAnimation1 = 1,
    kTagSpriteLeft,
    kTagSpriteRight,
};

enum 
{
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1; 


CCLayer* nextSpriteTestAction();
CCLayer* backSpriteTestAction();
CCLayer* restartSpriteTestAction();

typedef CCLayer* (*NEWSPRITETESTFUNC)();
#define SPRITETEST_CREATE_FUNC(className) \
static CCLayer* create##className() \
{ return new className(); }

SPRITETEST_CREATE_FUNC(Sprite1);
SPRITETEST_CREATE_FUNC(SpriteBatchNode1);
SPRITETEST_CREATE_FUNC(SpriteFrameTest);
SPRITETEST_CREATE_FUNC(SpriteFrameAliasNameTest);
SPRITETEST_CREATE_FUNC(SpriteAnchorPoint);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeAnchorPoint);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorRotation);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotation);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorScale);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorScale);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorSkew);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorRotationalSkew);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkew);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkew);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorSkewScale);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorRotationalSkewScale);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkewScale);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkewScale);
SPRITETEST_CREATE_FUNC(SpriteOffsetAnchorFlip);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeOffsetAnchorFlip);
SPRITETEST_CREATE_FUNC(SpriteAnimationSplit);
SPRITETEST_CREATE_FUNC(SpriteColorOpacity);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeColorOpacity);
SPRITETEST_CREATE_FUNC(SpriteZOrder);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeZOrder);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorder);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorderIssue744);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorderIssue766);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorderIssue767);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorderSameIndex);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeReorderOneChild);
SPRITETEST_CREATE_FUNC(NodeSort);
SPRITETEST_CREATE_FUNC(SpriteZVertex);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeZVertex);
SPRITETEST_CREATE_FUNC(Sprite6);
SPRITETEST_CREATE_FUNC(SpriteFlip);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeFlip);
SPRITETEST_CREATE_FUNC(SpriteAliased);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeAliased);
SPRITETEST_CREATE_FUNC(SpriteNewTexture);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeNewTexture);
SPRITETEST_CREATE_FUNC(SpriteHybrid);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeChildren);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeChildrenZ);
SPRITETEST_CREATE_FUNC(SpriteChildrenVisibility);
SPRITETEST_CREATE_FUNC(SpriteChildrenVisibilityIssue665);
SPRITETEST_CREATE_FUNC(SpriteChildrenAnchorPoint);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeChildrenAnchorPoint);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeChildrenScale);
SPRITETEST_CREATE_FUNC(SpriteChildrenChildren);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeChildrenChildren);
SPRITETEST_CREATE_FUNC(SpriteSkewNegativeScaleChildren);
SPRITETEST_CREATE_FUNC(SpriteRotationalSkewNegativeScaleChildren);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeSkewNegativeScaleChildren);
SPRITETEST_CREATE_FUNC(SpriteBatchNodeRotationalSkewNegativeScaleChildren);
SPRITETEST_CREATE_FUNC(SpriteNilTexture);
SPRITETEST_CREATE_FUNC(SpriteSubclass);
SPRITETEST_CREATE_FUNC(SpriteDoubleResolution);
SPRITETEST_CREATE_FUNC(SpriteBatchBug1217);
SPRITETEST_CREATE_FUNC(AnimationCache);
SPRITETEST_CREATE_FUNC(AnimationCacheFile);


static NEWSPRITETESTFUNC createFunctions[] =
{
    createSprite1,
	createSpriteBatchNode1,
	createSpriteFrameTest,
	createSpriteFrameAliasNameTest,
	createSpriteAnchorPoint,
	createSpriteBatchNodeAnchorPoint,
	createSpriteOffsetAnchorRotation,
	createSpriteBatchNodeOffsetAnchorRotation,
	createSpriteOffsetAnchorScale,
	createSpriteBatchNodeOffsetAnchorScale,
	createSpriteOffsetAnchorSkew,
	createSpriteOffsetAnchorRotationalSkew,
	createSpriteBatchNodeOffsetAnchorSkew,
	createSpriteBatchNodeOffsetAnchorRotationalSkew,
	createSpriteOffsetAnchorSkewScale,
	createSpriteOffsetAnchorRotationalSkewScale,
	createSpriteBatchNodeOffsetAnchorSkewScale,
	createSpriteBatchNodeOffsetAnchorRotationalSkewScale,
	createSpriteOffsetAnchorFlip,
	createSpriteBatchNodeOffsetAnchorFlip,
	createSpriteAnimationSplit,
	createSpriteColorOpacity,
	createSpriteBatchNodeColorOpacity,
	createSpriteZOrder,
	createSpriteBatchNodeZOrder,
	createSpriteBatchNodeReorder,
	createSpriteBatchNodeReorderIssue744,
	createSpriteBatchNodeReorderIssue766,
	createSpriteBatchNodeReorderIssue767,
	createSpriteBatchNodeReorderSameIndex,
	createSpriteBatchNodeReorderOneChild,
	createNodeSort,
	createSpriteZVertex,
	createSpriteBatchNodeZVertex,
	createSprite6,
	createSpriteFlip,
	createSpriteBatchNodeFlip,
	createSpriteAliased,
	createSpriteBatchNodeAliased,
	createSpriteNewTexture,
	createSpriteBatchNodeNewTexture,
	createSpriteHybrid,
	createSpriteBatchNodeChildren,
	createSpriteBatchNodeChildrenZ,
	createSpriteChildrenVisibility,
	createSpriteChildrenVisibilityIssue665,
	createSpriteChildrenAnchorPoint,
	createSpriteBatchNodeChildrenAnchorPoint,
	createSpriteBatchNodeChildrenScale,
	createSpriteChildrenChildren,
	createSpriteBatchNodeChildrenChildren,
	createSpriteSkewNegativeScaleChildren,
	createSpriteRotationalSkewNegativeScaleChildren,
	createSpriteBatchNodeSkewNegativeScaleChildren,
	createSpriteBatchNodeRotationalSkewNegativeScaleChildren,
	createSpriteNilTexture,
	createSpriteSubclass,
	createSpriteDoubleResolution,
	createSpriteBatchBug1217,
	createAnimationCache,
	createAnimationCacheFile,
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

CCLayer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartSpriteTestAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
} 

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

SpriteTestDemo::SpriteTestDemo(void)
{
}

SpriteTestDemo::~SpriteTestDemo(void)
{
}

std::string SpriteTestDemo::title()
{
    return "No title";
}

std::string SpriteTestDemo::subtitle()
{
    return "";
}

void SpriteTestDemo::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 28);
    addChild(label, 1);
    label->setPosition( ccp(s.width/2, s.height-50) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(s.width/2, s.height-80) );
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(SpriteTestDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png","Images/r2.png", this, menu_selector(SpriteTestDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(SpriteTestDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    
}

void SpriteTestDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new SpriteTestScene();
    s->addChild(restartSpriteTestAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteTestDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new SpriteTestScene();
    s->addChild( nextSpriteTestAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void SpriteTestDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new SpriteTestScene();
    s->addChild( backSpriteTestAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Sprite1
//
//------------------------------------------------------------------

Sprite1::Sprite1()
{
    setTouchEnabled( true );
    
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    addNewSpriteWithCoords( ccp(s.width/2, s.height/2) );
    
}

void Sprite1::addNewSpriteWithCoords(CCPoint p)
{
    int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    
    
    CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(x,y,85,121) );
    addChild( sprite );
    
    sprite->setPosition( ccp( p.x, p.y) );
    
    CCActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = CCScaleBy::create(3, 2);
    else if(random < 0.40)
        action = CCRotateBy::create(3, 360);
    else if( random < 0.60)
        action = CCBlink::create(1, 3);
    else if( random < 0.8 )
        action = CCTintBy::create(2, 0, -255, -255);
    else 
        action = CCFadeOut::create(2);
    CCActionInterval* action_back = action->reverse();
    CCActionInterval* seq = CCSequence::create( action, action_back, NULL );
    
    sprite->runAction( CCRepeatForever::create(seq) );
}

void Sprite1::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();
    
        addNewSpriteWithCoords( location );
    }
}

std::string Sprite1::title()
{
    return "Sprite (tap screen)";
}

//------------------------------------------------------------------
//
// SpriteBatchNode1
//
//------------------------------------------------------------------

SpriteBatchNode1::SpriteBatchNode1()
{
    setTouchEnabled( true );

    CCSpriteBatchNode* BatchNode = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 50);
    addChild(BatchNode, 0, kTagSpriteBatchNode);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    addNewSpriteWithCoords( ccp(s.width/2, s.height/2) );
}

void SpriteBatchNode1::addNewSpriteWithCoords(CCPoint p)
{
    CCSpriteBatchNode* BatchNode = (CCSpriteBatchNode*) getChildByTag( kTagSpriteBatchNode );
    
    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    

    CCSprite* sprite = CCSprite::createWithTexture(BatchNode->getTexture(), CCRectMake(x,y,85,121));
    BatchNode->addChild(sprite);

    sprite->setPosition( ccp( p.x, p.y) );

    CCActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = CCScaleBy::create(3, 2);
    else if(random < 0.40)
        action = CCRotateBy::create(3, 360);
    else if( random < 0.60)
        action = CCBlink::create(1, 3);
    else if( random < 0.8 )
        action = CCTintBy::create(2, 0, -255, -255);
    else 
        action = CCFadeOut::create(2);

    CCActionInterval* action_back = action->reverse();
    CCActionInterval* seq = CCSequence::create(action, action_back, NULL);
    
    sprite->runAction( CCRepeatForever::create(seq));
}

void SpriteBatchNode1::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();
            
        addNewSpriteWithCoords( location );
    }

}

std::string SpriteBatchNode1::title()
{
    return "SpriteBatchNode (tap screen)";
}


//------------------------------------------------------------------
//
// SpriteColorOpacity
//
//------------------------------------------------------------------

SpriteColorOpacity::SpriteColorOpacity()
{
    CCSprite* sprite1 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
    CCSprite* sprite2 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    CCSprite* sprite3 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121));
    CCSprite* sprite4 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121));
    
    CCSprite* sprite5 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
    CCSprite* sprite6 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    CCSprite* sprite7 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121));
    CCSprite* sprite8 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121));
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    sprite1->setPosition( ccp( (s.width/5)*1, (s.height/3)*1) );
    sprite2->setPosition( ccp( (s.width/5)*2, (s.height/3)*1) );
    sprite3->setPosition( ccp( (s.width/5)*3, (s.height/3)*1) );
    sprite4->setPosition( ccp( (s.width/5)*4, (s.height/3)*1) );
    sprite5->setPosition( ccp( (s.width/5)*1, (s.height/3)*2) );
    sprite6->setPosition( ccp( (s.width/5)*2, (s.height/3)*2) );
    sprite7->setPosition( ccp( (s.width/5)*3, (s.height/3)*2) );
    sprite8->setPosition( ccp( (s.width/5)*4, (s.height/3)*2) );
    
    CCActionInterval* action = CCFadeIn::create(2);
    CCActionInterval* action_back = action->reverse();
    CCAction* fade = CCRepeatForever::create( CCSequence::create( action, action_back, NULL) );
    
    CCActionInterval* tintred = CCTintBy::create(2, 0, -255, -255);
    CCActionInterval* tintred_back = tintred->reverse();
    CCAction* red = CCRepeatForever::create( CCSequence::create( tintred, tintred_back, NULL) );
    
    CCActionInterval* tintgreen = CCTintBy::create(2, -255, 0, -255);
    CCActionInterval* tintgreen_back = tintgreen->reverse();
    CCAction* green = CCRepeatForever::create( CCSequence::create( tintgreen, tintgreen_back, NULL) );
    
    CCActionInterval* tintblue = CCTintBy::create(2, -255, -255, 0);
    CCActionInterval* tintblue_back = tintblue->reverse();
    CCAction* blue = CCRepeatForever::create( CCSequence::create( tintblue, tintblue_back, NULL) );
    
    sprite5->runAction(red);
    sprite6->runAction(green);
    sprite7->runAction(blue);
    sprite8->runAction(fade);
    
    // late add: test dirtyColor and dirtyPosition
    addChild(sprite1, 0, kTagSprite1);
    addChild(sprite2, 0, kTagSprite2);
    addChild(sprite3, 0, kTagSprite3);
    addChild(sprite4, 0, kTagSprite4);
    addChild(sprite5, 0, kTagSprite5);
    addChild(sprite6, 0, kTagSprite6);
    addChild(sprite7, 0, kTagSprite7);
    addChild(sprite8, 0, kTagSprite8);
    
    schedule( schedule_selector(SpriteColorOpacity::removeAndAddSprite), 2 );
}

// this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
void SpriteColorOpacity::removeAndAddSprite(float dt)
{
    CCSprite* sprite = (CCSprite*)(getChildByTag(kTagSprite5));    
    sprite->retain();
    
    removeChild(sprite, false);
    addChild(sprite, 0, kTagSprite5);
    
    sprite->release();
}

std::string SpriteColorOpacity::title()
{
    return "Sprite: Color & Opacity";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeColorOpacity
//
//------------------------------------------------------------------

SpriteBatchNodeColorOpacity::SpriteBatchNodeColorOpacity()
{
    // small capacity. Testing resizing.
    // Don't use capacity=1 in your real game. It is expensive to resize the capacity
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    addChild(batch, 0, kTagSpriteBatchNode);        
    
    CCSprite* sprite1 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
    CCSprite* sprite2 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    CCSprite* sprite3 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*2, 121*1, 85, 121));
    CCSprite* sprite4 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*3, 121*1, 85, 121));
    
    CCSprite* sprite5 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
    CCSprite* sprite6 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    CCSprite* sprite7 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*2, 121*1, 85, 121));
    CCSprite* sprite8 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*3, 121*1, 85, 121));
    
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    sprite1->setPosition( ccp( (s.width/5)*1, (s.height/3)*1) );
    sprite2->setPosition( ccp( (s.width/5)*2, (s.height/3)*1) );
    sprite3->setPosition( ccp( (s.width/5)*3, (s.height/3)*1) );
    sprite4->setPosition( ccp( (s.width/5)*4, (s.height/3)*1) );
    sprite5->setPosition( ccp( (s.width/5)*1, (s.height/3)*2) );
    sprite6->setPosition( ccp( (s.width/5)*2, (s.height/3)*2) );
    sprite7->setPosition( ccp( (s.width/5)*3, (s.height/3)*2) );
    sprite8->setPosition( ccp( (s.width/5)*4, (s.height/3)*2) );

    CCActionInterval* action = CCFadeIn::create(2);
    CCActionInterval* action_back = action->reverse();
    CCAction* fade = CCRepeatForever::create( CCSequence::create( action, action_back,NULL) );

    CCActionInterval* tintred = CCTintBy::create(2, 0, -255, -255);
    CCActionInterval* tintred_back = tintred->reverse();
    CCAction* red = CCRepeatForever::create( CCSequence::create( tintred, tintred_back,NULL) );

    CCActionInterval* tintgreen = CCTintBy::create(2, -255, 0, -255);
    CCActionInterval* tintgreen_back = tintgreen->reverse();
    CCAction* green = CCRepeatForever::create( CCSequence::create( tintgreen, tintgreen_back,NULL) );

    CCActionInterval* tintblue = CCTintBy::create(2, -255, -255, 0);
    CCActionInterval* tintblue_back = tintblue->reverse();
    CCAction* blue = CCRepeatForever::create( CCSequence::create( tintblue, tintblue_back,NULL) );
    
    
    sprite5->runAction(red);
    sprite6->runAction(green);
    sprite7->runAction(blue);
    sprite8->runAction(fade);
    
    // late add: test dirtyColor and dirtyPosition
    batch->addChild(sprite1, 0, kTagSprite1);
    batch->addChild(sprite2, 0, kTagSprite2);
    batch->addChild(sprite3, 0, kTagSprite3);
    batch->addChild(sprite4, 0, kTagSprite4);
    batch->addChild(sprite5, 0, kTagSprite5);
    batch->addChild(sprite6, 0, kTagSprite6);
    batch->addChild(sprite7, 0, kTagSprite7);
    batch->addChild(sprite8, 0, kTagSprite8);
    
    
    schedule( schedule_selector(SpriteBatchNodeColorOpacity::removeAndAddSprite), 2);
}

// this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
void SpriteBatchNodeColorOpacity::removeAndAddSprite(float dt)
{
    CCSpriteBatchNode* batch= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteBatchNode ));
    CCSprite* sprite = (CCSprite*)(batch->getChildByTag(kTagSprite5));
    
    sprite->retain();

    batch->removeChild(sprite, false);
    batch->addChild(sprite, 0, kTagSprite5);
    
    sprite->release();
}

std::string SpriteBatchNodeColorOpacity::title()
{
    return "SpriteBatchNode: Color & Opacity";
}

//------------------------------------------------------------------
//
// SpriteZOrder
//
//------------------------------------------------------------------

SpriteZOrder::SpriteZOrder()
{
    m_dir = 1;
            
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    float step = s.width/11;
    for(int i=0;i<5;i++) 
    {
        CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        addChild(sprite, i);
    }
    
    for(int i=5;i<10;i++) 
    {
        CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*0, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        addChild(sprite, 14-i);
    }
    
    CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*0, 85, 121));
    addChild(sprite, -1, kTagSprite1);
    sprite->setPosition( ccp(s.width/2, s.height/2 - 20) );
    sprite->setScaleX( 6 );
    sprite->setColor(ccRED);
    
    schedule( schedule_selector(SpriteZOrder::reorderSprite), 1);        
}

void SpriteZOrder::reorderSprite(float dt)
{
    CCSprite* sprite = (CCSprite*)(getChildByTag(kTagSprite1));
    
    int z = sprite->getZOrder();
    
    if( z < -1 )
        m_dir = 1;
    if( z > 10 )
        m_dir = -1;
    
    z += m_dir * 3;
    
    reorderChild(sprite, z);
    
}

std::string SpriteZOrder::title()
{
    return "Sprite: Z order";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeZOrder
//
//------------------------------------------------------------------

SpriteBatchNodeZOrder::SpriteBatchNodeZOrder()
{
    m_dir = 1;
    
    // small capacity. Testing resizing.
    // Don't use capacity=1 in your real game. It is expensive to resize the capacity
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    addChild(batch, 0, kTagSpriteBatchNode);        
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    float step = s.width/11;
    for(int i=0;i<5;i++) 
    {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        batch->addChild(sprite, i);
    }
    
    for(int i=5;i<10;i++) 
    {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*0, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        batch->addChild(sprite, 14-i);
    }
    
    CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*3, 121*0, 85, 121));
    batch->addChild(sprite, -1, kTagSprite1);
    sprite->setPosition( ccp(s.width/2, s.height/2 - 20) );
    sprite->setScaleX( 6 );
    sprite->setColor(ccRED);
    
    schedule( schedule_selector(SpriteBatchNodeZOrder::reorderSprite), 1);        
}

void SpriteBatchNodeZOrder::reorderSprite(float dt)
{
    CCSpriteBatchNode* batch= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteBatchNode ));
    CCSprite* sprite = (CCSprite*)(batch->getChildByTag(kTagSprite1));
    
    int z = sprite->getZOrder();
    
    if( z < -1 )
        m_dir = 1;
    if( z > 10 )
        m_dir = -1;
    
    z += m_dir * 3;

    batch->reorderChild(sprite, z);
}

std::string SpriteBatchNodeZOrder::title()
{
    return "SpriteBatchNode: Z order";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeReorder
//
//------------------------------------------------------------------

SpriteBatchNodeReorder::SpriteBatchNodeReorder()
{
    CCArray* a = CCArray::createWithCapacity(10);
    CCSpriteBatchNode* asmtest = CCSpriteBatchNode::create("animations/ghosts.png");
    
    for(int i=0; i<10; i++)
    {
        CCSprite* s1 = CCSprite::createWithTexture(asmtest->getTexture(), CCRectMake(0, 0, 50, 50));
        a->addObject(s1);
        asmtest->addChild(s1, 10);
    }
    
    for(int i=0; i<10; i++)
    {
        if(i!=5)
        {
            asmtest->reorderChild( (CCNode*)(a->objectAtIndex(i)), 9 );
        }
    }
    
    int CC_UNUSED prev = -1;
    CCArray* children = asmtest->getChildren();
    CCSprite* child;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(children, pObject)
    {
        child = (CCSprite*)pObject;
        if(! child )
            break;

        int currentIndex = child->getAtlasIndex();
        CCAssert( prev == currentIndex-1, "Child order failed");
        ////----CCLOG("children %x - atlasIndex:%d", child, currentIndex);
        prev = currentIndex;
    }
    
    prev = -1;
    CCArray* sChildren = asmtest->getDescendants();
    CCARRAY_FOREACH(sChildren, pObject)
    {
        child = (CCSprite*)pObject;
        if(! child )
            break;

        int currentIndex = child->getAtlasIndex();
        CCAssert( prev == currentIndex-1, "Child order failed");
        ////----CCLOG("descendant %x - atlasIndex:%d", child, currentIndex);
        prev = currentIndex;
    }
}

std::string SpriteBatchNodeReorder::title()
{
    return "SpriteBatchNode: reorder #1";
}

std::string SpriteBatchNodeReorder::subtitle()
{
    return "Should not crash";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue744
//
//------------------------------------------------------------------

SpriteBatchNodeReorderIssue744::SpriteBatchNodeReorderIssue744()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    

    // Testing issue #744
    // http://code.google.com/p/cocos2d-iphone/issues/detail?id=744
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);
    addChild(batch, 0, kTagSpriteBatchNode);        

    CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(),CCRectMake(0, 0, 85, 121));
    sprite->setPosition( ccp(s.width/2, s.height/2) );
    batch->addChild(sprite, 3);
    batch->reorderChild(sprite, 1);
}

std::string SpriteBatchNodeReorderIssue744::title()
{
    return "SpriteBatchNode: reorder issue #744";
}

std::string SpriteBatchNodeReorderIssue744::subtitle()
{
    return "Should not crash";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue766
//
//------------------------------------------------------------------

CCSprite* SpriteBatchNodeReorderIssue766::makeSpriteZ(int aZ)
{
    CCSprite *sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(128,0,64,64));
    batchNode->addChild(sprite, aZ+1, 0);

    //children
    CCSprite *spriteShadow = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(0,0,64,64));
    spriteShadow->setOpacity(128);
    sprite->addChild(spriteShadow, aZ, 3);

    CCSprite *spriteTop = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(64,0,64,64));
    sprite->addChild(spriteTop, aZ+2, 3);

    return sprite;
}

void SpriteBatchNodeReorderIssue766::reorderSprite(float dt)
{
    unschedule(schedule_selector(SpriteBatchNodeReorderIssue766::reorderSprite));

    batchNode->reorderChild(sprite1, 4);
}

// on "init" you need to initialize your instance
SpriteBatchNodeReorderIssue766::SpriteBatchNodeReorderIssue766()
{
    batchNode = CCSpriteBatchNode::create("Images/piece.png", 15);
    addChild(batchNode, 1, 0);

    sprite1 = makeSpriteZ(2);
    sprite1->setPosition(ccp(200,160));

    sprite2 = makeSpriteZ(3);
    sprite2->setPosition(ccp(264,160));

    sprite3 = makeSpriteZ(4);
    sprite3->setPosition(ccp(328,160));

    schedule(schedule_selector(SpriteBatchNodeReorderIssue766::reorderSprite), 2);
}

std::string SpriteBatchNodeReorderIssue766::title()
{
    return "SpriteBatchNode: reorder issue #766";
}

std::string SpriteBatchNodeReorderIssue766::subtitle()
{
    return "In 2 seconds 1 sprite will be reordered";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue767
//
//------------------------------------------------------------------
SpriteBatchNodeReorderIssue767::SpriteBatchNodeReorderIssue767()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();        

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist", "animations/ghosts.png");
    CCNode *aParent;
    CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;

    //
    // SpriteBatchNode: 3 levels of children
    //
    aParent = CCSpriteBatchNode::create("animations/ghosts.png");
    addChild(aParent, 0, kTagSprite1);

    // parent
    l1 = CCSprite::createWithSpriteFrameName("father.gif");
    l1->setPosition(ccp( s.width/2, s.height/2));
    aParent->addChild(l1, 0, kTagSprite2);
    CCSize l1Size = l1->getContentSize();

    // child left
    l2a = CCSprite::createWithSpriteFrameName("sister1.gif");
    l2a->setPosition(ccp( -25 + l1Size.width/2, 0 + l1Size.height/2));
    l1->addChild(l2a, -1, kTagSpriteLeft);
    CCSize l2aSize = l2a->getContentSize();        


    // child right
    l2b = CCSprite::createWithSpriteFrameName("sister2.gif");
    l2b->setPosition(ccp( +25 + l1Size.width/2, 0 + l1Size.height/2));
    l1->addChild(l2b, 1, kTagSpriteRight);
    CCSize l2bSize = l2a->getContentSize();


    // child left bottom
    l3a1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a1->setScale(0.65f);
    l3a1->setPosition(ccp(0+l2aSize.width/2,-50+l2aSize.height/2));
    l2a->addChild(l3a1, -1);

    // child left top
    l3a2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a2->setScale(0.65f);
    l3a2->setPosition(ccp(0+l2aSize.width/2,+50+l2aSize.height/2));
    l2a->addChild(l3a2, 1);

    // child right bottom
    l3b1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b1->setScale(0.65f);
    l3b1->setPosition(ccp(0+l2bSize.width/2,-50+l2bSize.height/2));
    l2b->addChild(l3b1, -1);

    // child right top
    l3b2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b2->setScale(0.65f);
    l3b2->setPosition(ccp(0+l2bSize.width/2,+50+l2bSize.height/2));
    l2b->addChild(l3b2, 1);

    schedule(schedule_selector(SpriteBatchNodeReorderIssue767::reorderSprites), 1);
}

std::string SpriteBatchNodeReorderIssue767::title()
{
    return "SpriteBatchNode: reorder issue #767";
}

std::string SpriteBatchNodeReorderIssue767::subtitle()
{
    return "Should not crash";
}

void SpriteBatchNodeReorderIssue767::reorderSprites(float dt)
{
    CCSpriteBatchNode* spritebatch = (CCSpriteBatchNode*)getChildByTag(kTagSprite1);
    CCSprite *father = (CCSprite*)spritebatch->getChildByTag(kTagSprite2);
    CCSprite *left = (CCSprite*)father->getChildByTag(kTagSpriteLeft);
    CCSprite *right = (CCSprite*)father->getChildByTag(kTagSpriteRight);

    int newZLeft = 1;

    if( left->getZOrder() == 1 )
        newZLeft = -1;

    father->reorderChild(left, newZLeft);
    father->reorderChild(right, -newZLeft);
}

//------------------------------------------------------------------
//
// SpriteZVertex
//
//------------------------------------------------------------------

void SpriteZVertex::onEnter()
{
    SpriteTestDemo::onEnter();
    
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void SpriteZVertex::onExit()
{
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    SpriteTestDemo::onExit();
}

SpriteZVertex::SpriteZVertex()
{
    //
    // This test tests z-order
    // If you are going to use it is better to use a 3D projection
    //
    // WARNING:
    // The developer is resposible for ordering its sprites according to its Z if the sprite has
    // transparent parts.
    //

    //
    // Configure shader to mimic glAlphaTest
    //
    CCGLProgram *alphaTestShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    GLint alphaValueLocation = glGetUniformLocation(alphaTestShader->getProgram(), kCCUniformAlphaTestValue);

    // set alpha test value
    // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
    if (getShaderProgram())
    {
        getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, 0.0f);
    }
    
    
    m_dir = 1;
    m_time = 0;

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    float step = s.width/12;
    
    CCNode* node = CCNode::create();
    // camera uses the center of the image as the pivoting point
    node->setContentSize( CCSizeMake(s.width,s.height) );
    node->setAnchorPoint( ccp(0.5f, 0.5f));
    node->setPosition( ccp(s.width/2, s.height/2));

    addChild(node, 0);

    for(int i=0;i<5;i++) 
    {
        CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121));
        sprite->setPosition( ccp((i+1)*step, s.height/2) );
        sprite->setVertexZ( 10 + i*40 );
        sprite->setShaderProgram(alphaTestShader);
        node->addChild(sprite, 0);
        
    }
    
    for(int i=5;i<11;i++) 
    {
        CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*0, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        sprite->setVertexZ( 10 + (10-i)*40 );
        sprite->setShaderProgram(alphaTestShader);
        node->addChild(sprite, 0);
    }

    node->runAction( CCOrbitCamera::create(10, 1, 0, 0, 360, 0, 0) );
}

std::string SpriteZVertex::title()
{
    return "Sprite: openGL Z vertex";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeZVertex
//
//------------------------------------------------------------------

void SpriteBatchNodeZVertex::onEnter()
{
    SpriteTestDemo::onEnter();

    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void SpriteBatchNodeZVertex::onExit()
{
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    SpriteTestDemo::onExit();
}

SpriteBatchNodeZVertex::SpriteBatchNodeZVertex()
{
    //
    // This test tests z-order
    // If you are going to use it is better to use a 3D projection
    //
    // WARNING:
    // The developer is resposible for ordering its sprites according to its Z if the sprite has
    // transparent parts.
    //

    //
    // Configure shader to mimic glAlphaTest
    //
    CCGLProgram *alphaTestShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    GLint alphaValueLocation = glGetUniformLocation(alphaTestShader->getProgram(), kCCUniformAlphaTestValue);

    // set alpha test value
    // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
    if (getShaderProgram())
    {
        getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, 0.0f);
    }
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    float step = s.width/12;
    
    // small capacity. Testing resizing.
    // Don't use capacity=1 in your real game. It is expensive to resize the capacity
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    // camera uses the center of the image as the pivoting point
    batch->setContentSize( CCSizeMake(s.width,s.height));
    batch->setAnchorPoint( ccp(0.5f, 0.5f));
    batch->setPosition( ccp(s.width/2, s.height/2));
    
    batch->setShaderProgram(alphaTestShader);
    addChild(batch, 0, kTagSpriteBatchNode);        
    
    for(int i=0;i<5;i++) 
    {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*0, 121*1, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        sprite->setVertexZ(  10 + i*40 );
        batch->addChild(sprite, 0);
        
    }
    
    for(int i=5;i<11;i++) {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*0, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );
        sprite->setVertexZ(  10 + (10-i)*40 );
        batch->addChild(sprite, 0);
    }
    
    batch->runAction(CCOrbitCamera::create(10, 1, 0, 0, 360, 0, 0) );
}

std::string SpriteBatchNodeZVertex::title()
{
    return "SpriteBatchNode: openGL Z vertex";
}


//------------------------------------------------------------------
//
// SpriteAnchorPoint
//
//------------------------------------------------------------------

SpriteAnchorPoint::SpriteAnchorPoint()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    
    CCActionInterval* rotate = CCRotateBy::create(10, 360);
    CCAction* action = CCRepeatForever::create(rotate);
    
    for(int i=0;i<3;i++) 
    {
        CCSprite* sprite = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*i, 121*1, 85, 121) );
        sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 10);
        
        switch(i) 
        {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }
        
        point->setPosition( sprite->getPosition() );
        
        CCAction* copy = (CCAction*)(action->copy()->autorelease());
        sprite->runAction(copy);
        addChild(sprite, i);
    }        
}

std::string SpriteAnchorPoint::title()
{
    return "Sprite: anchor point";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeAnchorPoint
//
//------------------------------------------------------------------
SpriteBatchNodeAnchorPoint::SpriteBatchNodeAnchorPoint()
{
    // small capacity. Testing resizing.
    // Don't use capacity=1 in your real game. It is expensive to resize the capacity
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    addChild(batch, 0, kTagSpriteBatchNode);        
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    
    CCActionInterval* rotate = CCRotateBy::create(10, 360);
    CCAction* action = CCRepeatForever::create(rotate);
    for(int i=0;i<3;i++) 
    {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*i, 121*1, 85, 121));
        sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 1);

        switch(i) 
        {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }

        point->setPosition( sprite->getPosition() );
        
        CCAction* copy = (CCAction*)(action->copy()->autorelease());
        sprite->runAction(copy);
        batch->addChild(sprite, i);
    }
}

std::string SpriteBatchNodeAnchorPoint::title()
{
    return "SpriteBatchNode: anchor point";
}

//------------------------------------------------------------------
//
// Sprite6
//
//------------------------------------------------------------------

Sprite6::Sprite6()
{
    // small capacity. Testing resizing
    // Don't use capacity=1 in your real game. It is expensive to resize the capacity
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    addChild(batch, 0, kTagSpriteBatchNode);
    batch->ignoreAnchorPointForPosition( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    batch->setAnchorPoint( ccp(0.5f, 0.5f) );
    batch->setContentSize( CCSizeMake(s.width, s.height) );
    
    
    // SpriteBatchNode actions
    CCActionInterval* rotate = CCRotateBy::create(5, 360);
    CCAction* action = CCRepeatForever::create(rotate);

    // SpriteBatchNode actions
    CCActionInterval* rotate_back = rotate->reverse();
    CCActionInterval* rotate_seq = CCSequence::create(rotate, rotate_back, NULL);
    CCAction* rotate_forever = CCRepeatForever::create(rotate_seq);
    
    CCActionInterval* scale = CCScaleBy::create(5, 1.5f);
    CCActionInterval* scale_back = scale->reverse();
    CCActionInterval* scale_seq = CCSequence::create( scale, scale_back, NULL);
    CCAction* scale_forever = CCRepeatForever::create(scale_seq);

    float step = s.width/4;

    for(int i=0;i<3;i++) 
    {
        CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*i, 121*1, 85, 121));
        sprite->setPosition( ccp( (i+1)*step, s.height/2) );

        sprite->runAction( (CCAction*)(action->copy()->autorelease()) );
        batch->addChild(sprite, i);
    }
    
    batch->runAction( scale_forever);
    batch->runAction( rotate_forever);
}

std::string Sprite6::title()
{
    return "SpriteBatchNode transformation";
}

//------------------------------------------------------------------
//
// SpriteFlip
//
//------------------------------------------------------------------
SpriteFlip::SpriteFlip()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* sprite1 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
    addChild(sprite1, 0, kTagSprite1);
    
    CCSprite* sprite2 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
    addChild(sprite2, 0, kTagSprite2);
    
    schedule( schedule_selector(SpriteFlip::flipSprites), 1);
}

void SpriteFlip::flipSprites(float dt)
{
    CCSprite* sprite1 = (CCSprite*)(getChildByTag(kTagSprite1));
    CCSprite* sprite2 = (CCSprite*)(getChildByTag(kTagSprite2));
    
    bool x = sprite1->isFlipX();
    bool y = sprite2->isFlipY();
    
    CCLOG("Pre: %f", sprite1->getContentSize().height);
    sprite1->setFlipX(!x);
    sprite2->setFlipY(!y);
    CCLOG("Post: %f", sprite1->getContentSize().height);
}

std::string SpriteFlip::title()
{
    return "Sprite Flip X & Y";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeFlip
//
//------------------------------------------------------------------
SpriteBatchNodeFlip::SpriteBatchNodeFlip()
{
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 10);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* sprite1 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
    batch->addChild(sprite1, 0, kTagSprite1);
    
    CCSprite* sprite2 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
    batch->addChild(sprite2, 0, kTagSprite2);
    
    schedule( schedule_selector(SpriteBatchNodeFlip::flipSprites), 1);
}

void SpriteBatchNodeFlip::flipSprites(float dt)
{
    CCSpriteBatchNode* batch= (CCSpriteBatchNode*)(getChildByTag( kTagSpriteBatchNode ));
    CCSprite* sprite1 = (CCSprite*)(batch->getChildByTag(kTagSprite1));
    CCSprite* sprite2 = (CCSprite*)(batch->getChildByTag(kTagSprite2));
    
    bool x = sprite1->isFlipX();
    bool y = sprite2->isFlipY();
    
    CCLOG("Pre: %f", sprite1->getContentSize().height);
    sprite1->setFlipX(!x);
    sprite2->setFlipY(!y);
    CCLOG("Post: %f", sprite1->getContentSize().height);
}

std::string SpriteBatchNodeFlip::title()
{
    return "SpriteBatchNode Flip X & Y";
}

//------------------------------------------------------------------
//
// SpriteAliased
//
//------------------------------------------------------------------

SpriteAliased::SpriteAliased()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* sprite1 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
    addChild(sprite1, 0, kTagSprite1);
    
    CCSprite* sprite2 = CCSprite::create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121));
    sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
    addChild(sprite2, 0, kTagSprite2);
    
    CCActionInterval* scale = CCScaleBy::create(2, 5);
    CCActionInterval* scale_back = scale->reverse();
    CCActionInterval* seq = CCSequence::create( scale, scale_back, NULL);
    CCAction* repeat = CCRepeatForever::create(seq);
    
    CCAction* repeat2 = (CCAction*)(repeat->copy()->autorelease());
    
    sprite1->runAction(repeat);
    sprite2->runAction(repeat2);
    
}

void SpriteAliased::onEnter()
{
    SpriteTestDemo::onEnter();
    
    //
    // IMPORTANT:
    // This change will affect every sprite that uses the same texture
    // So sprite1 and sprite2 will be affected by this change
    //
    CCSprite* sprite = (CCSprite*)getChildByTag(kTagSprite1);
    sprite->getTexture()->setAliasTexParameters();
}

void SpriteAliased::onExit()
{
    // restore the tex parameter to AntiAliased.
    CCSprite* sprite = (CCSprite*)getChildByTag(kTagSprite1);
    sprite->getTexture()->setAntiAliasTexParameters();
    SpriteTestDemo::onExit();
}

std::string SpriteAliased::title()
{
    return "Sprite Aliased";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeAliased
//
//------------------------------------------------------------------

SpriteBatchNodeAliased::SpriteBatchNodeAliased()
{
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 10);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite* sprite1 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    sprite1->setPosition( ccp( s.width/2 - 100, s.height/2 ) );
    batch->addChild(sprite1, 0, kTagSprite1);
    
    CCSprite* sprite2 = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(85*1, 121*1, 85, 121));
    sprite2->setPosition( ccp( s.width/2 + 100, s.height/2 ) );
    batch->addChild(sprite2, 0, kTagSprite2);
    
    CCActionInterval* scale = CCScaleBy::create(2, 5);
    CCActionInterval* scale_back = scale->reverse();
    CCActionInterval* seq = CCSequence::create( scale, scale_back, NULL);
    CCAction* repeat = CCRepeatForever::create(seq);
    
    CCAction* repeat2 = (CCAction*)(repeat->copy()->autorelease());
    
    sprite1->runAction(repeat);
    sprite2->runAction(repeat2);
        
}
void SpriteBatchNodeAliased::onEnter()
{
    SpriteTestDemo::onEnter();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*) getChildByTag( kTagSpriteBatchNode );
    batch->getTexture()->setAliasTexParameters();
}

void SpriteBatchNodeAliased::onExit()
{
    // restore the tex parameter to AntiAliased.
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*) getChildByTag( kTagSpriteBatchNode );
    batch->getTexture()->setAntiAliasTexParameters();
    SpriteTestDemo::onExit();
}

std::string SpriteBatchNodeAliased::title()
{
    return "SpriteBatchNode Aliased";
}

//------------------------------------------------------------------
//
// SpriteNewTexture
//
//------------------------------------------------------------------

SpriteNewTexture::SpriteNewTexture()
{
    setTouchEnabled( true );
    
    CCNode* node = CCNode::create();
    addChild(node, 0, kTagSpriteBatchNode);

    m_texture1 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas.png");
    m_texture1->retain();
    m_texture2 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas-mono.png");
    m_texture2->retain();
    
    m_usingTexture1 = true;

    for(int i=0;i<30;i++)
        addNewSprite();
}

SpriteNewTexture::~SpriteNewTexture()
{
    m_texture1->release();
    m_texture2->release();
}

void SpriteNewTexture::addNewSprite()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);

    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    
    
    CCNode* node = getChildByTag( kTagSpriteBatchNode );
    CCSprite* sprite = CCSprite::createWithTexture(m_texture1, CCRectMake(x,y,85,121));
    node->addChild(sprite);
    
    sprite->setPosition( ccp( p.x, p.y) );
    
    CCActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = CCScaleBy::create(3, 2);
    else if(random < 0.40)
        action = CCRotateBy::create(3, 360);
    else if( random < 0.60)
        action = CCBlink::create(1, 3);
    else if( random < 0.8 )
        action = CCTintBy::create(2, 0, -255, -255);
    else 
        action = CCFadeOut::create(2);

    CCActionInterval* action_back = action->reverse();
    CCActionInterval* seq = CCSequence::create(action, action_back, NULL);
    
    sprite->runAction( CCRepeatForever::create(seq) );
}

void SpriteNewTexture::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

    CCNode *node = getChildByTag( kTagSpriteBatchNode );

    CCArray* children = node->getChildren();
    CCSprite* sprite;
    CCObject* pObject;

    if( m_usingTexture1 )                          //--> win32 : Let's it make just simple sentence
    {
        CCARRAY_FOREACH(children, pObject)
        {
            sprite = (CCSprite*)pObject;
            if(! sprite)
                break;

            sprite->setTexture(m_texture2);
        }

        m_usingTexture1 = false;
    } 
    else 
    {
        CCARRAY_FOREACH(children, pObject)
        {
            sprite = (CCSprite*)pObject;
            if(! sprite)
                break;

            sprite->setTexture(m_texture1);
        }

        m_usingTexture1 = true;
    }
}

std::string SpriteNewTexture::title()
{
    return "Sprite New texture (tap)";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeNewTexture
//
//------------------------------------------------------------------

SpriteBatchNodeNewTexture::SpriteBatchNodeNewTexture()
{
    setTouchEnabled( true );
    
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 50);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    m_texture1 = batch->getTexture(); m_texture1->retain();
    m_texture2 = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas-mono.png");
    m_texture2->retain();
    
    for(int i=0;i<30;i++)
        addNewSprite();
}

SpriteBatchNodeNewTexture::~SpriteBatchNodeNewTexture()
{
    m_texture1->release();
    m_texture2->release();
}

void SpriteBatchNodeNewTexture::addNewSprite()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
    
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*) getChildByTag( kTagSpriteBatchNode );
    
    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    
    
    CCSprite* sprite = CCSprite::createWithTexture(batch->getTexture(), CCRectMake(x,y,85,121));
    batch->addChild(sprite);
    
    sprite->setPosition( ccp( p.x, p.y) );
    
    CCActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = CCScaleBy::create(3, 2);
    else if(random < 0.40)
        action = CCRotateBy::create(3, 360);
    else if( random < 0.60)
        action = CCBlink::create(1, 3);
    else if( random < 0.8 )
        action = CCTintBy::create(2, 0, -255, -255);
    else 
        action = CCFadeOut::create(2);
    CCActionInterval* action_back = action->reverse();
    CCActionInterval* seq = CCSequence::create(action, action_back, NULL);
    
    sprite->runAction( CCRepeatForever::create(seq) );
}

void SpriteBatchNodeNewTexture::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*) getChildByTag( kTagSpriteBatchNode );
    
    if( batch->getTexture() == m_texture1 )
        batch->setTexture(m_texture2);
    else
        batch->setTexture(m_texture1);    
}

std::string SpriteBatchNodeNewTexture::title()
{
    return "SpriteBatchNode new texture (tap)";
}


//------------------------------------------------------------------
//
// SpriteFrameTest
//
//------------------------------------------------------------------

void SpriteFrameTest::onEnter()
{
    SpriteTestDemo::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // IMPORTANT:
    // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
    //     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    cache->addSpriteFramesWithFile("animations/grossini_blue.plist", "animations/grossini_blue.png");

    //
    // Animation using Sprite BatchNode
    //
    m_pSprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    m_pSprite1->setPosition( ccp( s.width/2-80, s.height/2) );

    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    spritebatch->addChild(m_pSprite1);
    addChild(spritebatch);

    CCArray* animFrames = CCArray::createWithCapacity(15);

    char str[100] = {0};
    for(int i = 1; i < 15; i++) 
    {
        sprintf(str, "grossini_dance_%02d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }

    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
    m_pSprite1->runAction( CCRepeatForever::create( CCAnimate::create(animation) ) );

    // to test issue #732, uncomment the following line
    m_pSprite1->setFlipX(false);
    m_pSprite1->setFlipY(false);

    //
    // Animation using standard Sprite
    //
    m_pSprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    m_pSprite2->setPosition( ccp( s.width/2 + 80, s.height/2) );
    addChild(m_pSprite2);


    CCArray* moreFrames = CCArray::createWithCapacity(20);
    for(int i = 1; i < 15; i++) 
    {
        sprintf(str, "grossini_dance_gray_%02d.png",i);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        moreFrames->addObject(frame);
    }


    for( int i = 1; i < 5; i++) {
        sprintf(str, "grossini_blue_%02d.png",i);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        moreFrames->addObject(frame);
    }

    // append frames from another batch
    moreFrames->addObjectsFromArray(animFrames);
    CCAnimation *animMixed = CCAnimation::createWithSpriteFrames(moreFrames, 0.3f);


    m_pSprite2->runAction(CCRepeatForever::create( CCAnimate::create(animMixed) ) );


    // to test issue #732, uncomment the following line
    m_pSprite2->setFlipX(false);
    m_pSprite2->setFlipY(false);

    schedule(schedule_selector(SpriteFrameTest::startIn05Secs), 0.5f);
    m_nCounter = 0;
}

void SpriteFrameTest::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_blue.plist");
}

std::string SpriteFrameTest::title()
{
    return "Sprite vs. SpriteBatchNode animation";
}

std::string SpriteFrameTest::subtitle()
{
    return "Testing issue #792";
}

void SpriteFrameTest::startIn05Secs(float dt)
{
    unschedule(schedule_selector(SpriteFrameTest::startIn05Secs));
    schedule(schedule_selector(SpriteFrameTest::flipSprites), 1.0f);
}

void SpriteFrameTest::flipSprites(float dt)
{
    m_nCounter++;

    bool fx = false;
    bool fy = false;
    int  i  = m_nCounter % 4;

    switch ( i ) {
        case 0:
            fx = false;
            fy = false;
            break;
        case 1:
            fx = true;
            fy = false;
            break;
        case 2:
            fx = false;
            fy = true;
            break;
        case 3:
            fx = true;
            fy = true;
            break;
    }

    m_pSprite1->setFlipX(fx);
    m_pSprite1->setFlipY(fy);
    m_pSprite2->setFlipX(fx);
    m_pSprite2->setFlipY(fy);
    //NSLog(@"flipX:%d, flipY:%d", fx, fy);
}

//------------------------------------------------------------------
//
// SpriteFrameAliasNameTest
//
//------------------------------------------------------------------
void SpriteFrameAliasNameTest::onEnter()
{
    SpriteTestDemo::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // IMPORTANT:
    // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
    //     [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
    //
    // CCSpriteFrameCache is a cache of CCSpriteFrames
    // CCSpriteFrames each contain a texture id and a rect (frame).

    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini-aliases.plist", "animations/grossini-aliases.png");

    //
    // Animation using Sprite batch
    //
    // A CCSpriteBatchNode can reference one and only one texture (one .png file)
    // Sprites that are contained in that texture can be instantiatied as CCSprites and then added to the CCSpriteBatchNode
    // All CCSprites added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call
    // If the CCSprites are not added to a CCSpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient
    //
    // When you animate a sprite, CCAnimation changes the frame of the sprite using setDisplayFrame: (this is why the animation must be in the same texture)
    // When setDisplayFrame: is used in the CCAnimation it changes the frame to one specified by the CCSpriteFrames that were added to the animation,
    // but texture id is still the same and so the sprite is still a child of the CCSpriteBatchNode, 
    // and therefore all the animation sprites are also drawn as part of the CCSpriteBatchNode
    //

    CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite->setPosition(ccp(s.width * 0.5f, s.height * 0.5f));

    CCSpriteBatchNode *spriteBatch = CCSpriteBatchNode::create("animations/grossini-aliases.png");
    spriteBatch->addChild(sprite);
    addChild(spriteBatch);

    CCArray* animFrames = CCArray::createWithCapacity(15);
    char str[100] = {0};
    for(int i = 1; i < 15; i++)
    {
        // Obtain frames by alias name
        sprintf(str, "dance_%02d", i);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
    // 14 frames * 1sec = 14 seconds
    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
}

void SpriteFrameAliasNameTest::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("animations/grossini-aliases.plist");
}

std::string SpriteFrameAliasNameTest::title()
{
    return "SpriteFrame Alias Name";
}

std::string SpriteFrameAliasNameTest::subtitle()
{
    return "SpriteFrames are obtained using the alias name";
}

//------------------------------------------------------------------
//
// SpriteOffsetAnchorRotation
//
//------------------------------------------------------------------
SpriteOffsetAnchorRotation::SpriteOffsetAnchorRotation()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();        
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    for(int i=0;i<3;i++) 
    {
        //
        // Animation using Sprite batch
        //
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp( s.width/4*(i+1), s.height/2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 1);

        switch(i) 
        {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }
        
        point->setPosition( sprite->getPosition() );
        
        CCArray* animFrames = CCArray::createWithCapacity(14);
        char str[100] = {0};
        for(int i = 0; i < 14; i++) 
        {
            sprintf(str, "grossini_dance_%02d.png",(i+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(str);
            animFrames->addObject(frame);
        }

        CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create( CCAnimate::create(animation) ) );            
        sprite->runAction(CCRepeatForever::create(CCRotateBy::create(10, 360) ) );

        addChild(sprite, 0);

    }        
}


void SpriteOffsetAnchorRotation::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteOffsetAnchorRotation::title()
{
    return "Sprite offset + anchor + rot";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorRotation
//
//------------------------------------------------------------------

SpriteBatchNodeOffsetAnchorRotation::SpriteBatchNodeOffsetAnchorRotation()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize(); 
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);
    
    for(int i=0;i<3;i++) 
    {
        //
        // Animation using Sprite BatchNode
        //
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition( ccp( s.width/4*(i+1), s.height/2));
        
        CCSprite* point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 200);
        
        switch(i) 
        {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }
        
        point->setPosition( sprite->getPosition() );
        
        CCArray* animFrames = CCArray::createWithCapacity(14);
        char str[100] = {0};
        for(int k = 0; k < 14; k++) 
        {
            sprintf(str, "grossini_dance_%02d.png",(k+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(str);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create( CCAnimate::create(animation) ));
        sprite->runAction(CCRepeatForever::create(CCRotateBy::create(10, 360) ));
        
        spritebatch->addChild(sprite, i);
    }        
}


void SpriteBatchNodeOffsetAnchorRotation::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteBatchNodeOffsetAnchorRotation::title()
{
    return "SpriteBatchNode offset + anchor + rot";
}


//------------------------------------------------------------------
//
// SpriteOffsetAnchorScale
//
//------------------------------------------------------------------


SpriteOffsetAnchorScale::SpriteOffsetAnchorScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();   
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    for(int i=0;i<3;i++) 
    {
        //
        // Animation using Sprite BatchNode
        //
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 1);
        
        switch(i) 
        {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }
        
        point->setPosition( sprite->getPosition() );
        
        CCArray* animFrames = CCArray::createWithCapacity(14);
        char str[100] = {0};
        for(int i = 0; i < 14; i++) 
        {
            sprintf(str, "grossini_dance_%02d.png",(i+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(str);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create( CCAnimate::create(animation) ));            
        
        CCActionInterval* scale = CCScaleBy::create(2, 2);
        CCActionInterval* scale_back = scale->reverse();
        CCActionInterval* seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale));
        
        addChild(sprite, 0);
    }        
}

void SpriteOffsetAnchorScale::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteOffsetAnchorScale::title()
{
    return "Sprite offset + anchor + scale";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorScale
//
//------------------------------------------------------------------
SpriteBatchNodeOffsetAnchorScale::SpriteBatchNodeOffsetAnchorScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize(); 
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritesheet);
    
    for(int i=0;i<3;i++) 
    {
        //
        // Animation using Sprite BatchNode
        //
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition( ccp( s.width/4*(i+1), s.height/2) );
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale( 0.25f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 200);
        
        switch(i) {
            case 0:
                sprite->setAnchorPoint( CCPointZero );
                break;
            case 1:
                sprite->setAnchorPoint( ccp(0.5f, 0.5f) );
                break;
            case 2:
                sprite->setAnchorPoint( ccp(1,1) );
                break;
        }
        
        point->setPosition( sprite->getPosition() );
        
        CCArray* animFrames = CCArray::createWithCapacity(14);
        char str[100] = {0};
        for(int k = 0; k < 14; k++) 
        {
            sprintf(str, "grossini_dance_%02d.png",(k+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(str);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create( CCAnimate::create(animation) ) );

        CCActionInterval* scale = CCScaleBy::create(2, 2);
        CCActionInterval* scale_back = scale->reverse();
        CCActionInterval* seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale) );
        
        spritesheet->addChild(sprite, i);
    }        
}

void SpriteBatchNodeOffsetAnchorScale::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteBatchNodeOffsetAnchorScale::title()
{
    return "SpriteBatchNode offset + anchor + scale";
}

//------------------------------------------------------------------
//
// SpriteAnimationSplit
//
//------------------------------------------------------------------

SpriteAnimationSplit::SpriteAnimationSplit()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("animations/dragon_animation.png");
    
    // manually add frames to the frame cache
    CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*0, 132*0, 132, 132));
    CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*1, 132*0, 132, 132));
    CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*2, 132*0, 132, 132));
    CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*3, 132*0, 132, 132));
    CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*0, 132*1, 132, 132));
    CCSpriteFrame *frame5 = CCSpriteFrame::createWithTexture(texture, CCRectMake(132*1, 132*1, 132, 132));
    
    
    //
    // Animation using Sprite BatchNode
    //
    CCSprite* sprite = CCSprite::createWithSpriteFrame(frame0);
    sprite->setPosition( ccp( s.width/2-80, s.height/2) );
    addChild(sprite);
            
    CCArray* animFrames = CCArray::createWithCapacity(6);
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    animFrames->addObject(frame3);
    animFrames->addObject(frame4);
    animFrames->addObject(frame5);
            
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCActionInterval* seq = CCSequence::create( animate,
                       CCFlipX::create(true),
                       animate->copy()->autorelease(),
                       CCFlipX::create(false),
                       NULL);
    
    sprite->runAction(CCRepeatForever::create( seq ) );
}

void SpriteAnimationSplit::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteAnimationSplit::title()
{
    return "Sprite: Animation + flip";
}

//------------------------------------------------------------------
//
// SpriteHybrid
//
//------------------------------------------------------------------
SpriteHybrid::SpriteHybrid()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // parents
    CCNode *parent1 = CCNode::create();
    CCSpriteBatchNode *parent2 = CCSpriteBatchNode::create("animations/grossini.png", 50);
    
    addChild(parent1, 0, kTagNode);
    addChild(parent2, 0, kTagSpriteBatchNode);
    
    
    // IMPORTANT:
    // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
    //     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
    
    
    // create 250 sprites
    // only show 80% of them
    for(int i = 0; i < 250; i++) 
    {
        int spriteIdx = CCRANDOM_0_1() * 14;
        char str[25] = {0};
        sprintf(str, "grossini_dance_%02d.png", (spriteIdx+1));
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        CCSprite* sprite = CCSprite::createWithSpriteFrame(frame);
        parent1->addChild(sprite, i, i);
        
        float x=-1000;
        float y=-1000;
        if( CCRANDOM_0_1() < 0.2f ) 
        {
            x = CCRANDOM_0_1() * s.width;
            y = CCRANDOM_0_1() * s.height;
        }
        sprite->setPosition( ccp(x,y) );
            
        CCActionInterval* action = CCRotateBy::create(4, 360);
        sprite->runAction( CCRepeatForever::create(action) );
    }
    
    m_usingSpriteBatchNode = false;
    
    schedule( schedule_selector(SpriteHybrid::reparentSprite), 2);
}

void SpriteHybrid::reparentSprite(float dt)
{
    CCNode *p1 = getChildByTag(kTagNode);
    CCNode *p2 = getChildByTag( kTagSpriteBatchNode );
    
    CCArray* retArray = CCArray::createWithCapacity(250);

    if( m_usingSpriteBatchNode )
        CC_SWAP(p1,p2, CCNode*);

    ////----CCLOG("New parent is: %x", p2);
    
    CCNode* node;
    CCObject* pObject;
    CCArray* children = p1->getChildren();
    CCARRAY_FOREACH(children, pObject)
    {
        node = (CCNode*)pObject;
        if(! node )
            break;

        retArray->addObject(node);
    }

    int i=0;
    p1->removeAllChildrenWithCleanup(false);

    CCARRAY_FOREACH(retArray, pObject)
    {
        node = (CCNode*)pObject;
        if(! node)
            break;

        p2->addChild(node, i, i);
        i++;
    }

    m_usingSpriteBatchNode = ! m_usingSpriteBatchNode;
}

void SpriteHybrid::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("animations/grossini.plist");
}

std::string SpriteHybrid::title()
{
    return "HybrCCSprite* sprite Test";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeChildren
//
//------------------------------------------------------------------

SpriteBatchNodeChildren::SpriteBatchNodeChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    // parents
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("animations/grossini.png", 50);
    
    addChild(batch, 0, kTagSpriteBatchNode);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp( s.width/3, s.height/2));
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(50,50));
    
    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-50,-50));
    
    batch->addChild(sprite1);
    sprite1->addChild(sprite2);
    sprite1->addChild(sprite3);
    
    // BEGIN NEW CODE
    CCArray *animFrames = CCArray::create();
    char str[100] = {0};
    for(int i = 1; i < 15; i++) 
    {
        sprintf(str, "grossini_dance_%02d.png",i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
    sprite1->runAction(CCRepeatForever::create( CCAnimate::create(animation) ) );
    // END NEW CODE
    
    CCActionInterval* action = CCMoveBy::create(2, ccp(200,0));
    CCActionInterval* action_back = action->reverse();
    CCActionInterval* action_rot = CCRotateBy::create(2, 360);
    CCActionInterval* action_s = CCScaleBy::create(2, 2);
    CCActionInterval* action_s_back = action_s->reverse();
    
    CCActionInterval* seq2 = action_rot->reverse();
    sprite2->runAction( CCRepeatForever::create(seq2) );
    
    sprite1->runAction( CCRepeatForever::create(action_rot));
    sprite1->runAction( CCRepeatForever::create(CCSequence::create(action, action_back,NULL)) );
    sprite1->runAction( CCRepeatForever::create(CCSequence::create(action_s, action_s_back,NULL)) );

}

void SpriteBatchNodeChildren::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteBatchNodeChildren::title()
{
    return "SpriteBatchNode Grand Children";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenZ
//
//------------------------------------------------------------------
SpriteBatchNodeChildrenZ::SpriteBatchNodeChildrenZ()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    // parents
    CCSpriteBatchNode* batch;
    CCSprite* sprite1, *sprite2, *sprite3;

    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
    
    // test 1
    batch = CCSpriteBatchNode::create("animations/grossini.png", 50);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp( s.width/3, s.height/2));
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    batch->addChild(sprite1);
    sprite1->addChild(sprite2, 2);
    sprite1->addChild(sprite3, -2);
    
    // test 2
    batch = CCSpriteBatchNode::create("animations/grossini.png", 50);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp( 2*s.width/3, s.height/2));
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    batch->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, 2);
    
    // test 3
    batch = CCSpriteBatchNode::create("animations/grossini.png", 50);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp( s.width/2 - 90, s.height/4));
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp( s.width/2 - 60,s.height/4));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp( s.width/2 - 30, s.height/4));
    
    batch->addChild(sprite1, 10);
    batch->addChild(sprite2, -10);
    batch->addChild(sprite3, -5);

    // test 4
    batch = CCSpriteBatchNode::create("animations/grossini.png", 50);
    addChild(batch, 0, kTagSpriteBatchNode);
    
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp( s.width/2 +30, s.height/4));
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp( s.width/2 +60,s.height/4));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp( s.width/2 +90, s.height/4));
    
    batch->addChild(sprite1, -10);
    batch->addChild(sprite2, -5);
    batch->addChild(sprite3, -2);
}

void SpriteBatchNodeChildrenZ::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteBatchNodeChildrenZ::title()
{
    return "SpriteBatchNode Children Z";
}

//------------------------------------------------------------------
//
// SpriteChildrenVisibility
//
//------------------------------------------------------------------

SpriteChildrenVisibility::SpriteChildrenVisibility()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");

    CCNode *aParent;
    CCSprite* sprite1, *sprite2, *sprite3;
    //
    // SpriteBatchNode
    //
    // parents
    aParent = CCSpriteBatchNode::create("animations/grossini.png", 50);
    aParent->setPosition( ccp(s.width/3, s.height/2) );
    addChild(aParent, 0);
    
    
    
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp(0,0));
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, 2);
    
    sprite1->runAction(CCBlink::create(5, 10));
    
    //
    // Sprite
    //
    aParent = CCNode::create();
    aParent->setPosition( ccp(2*s.width/3, s.height/2) );
    addChild(aParent, 0);

    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp(0,0));
            
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, 2);
    
    sprite1->runAction(CCBlink::create(5, 10));
}

void SpriteChildrenVisibility::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteChildrenVisibility::title()
{
    return "Sprite & SpriteBatchNode Visibility";
}

//------------------------------------------------------------------
//
// SpriteChildrenVisibilityIssue665
//
//------------------------------------------------------------------
SpriteChildrenVisibilityIssue665::SpriteChildrenVisibilityIssue665()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");

    CCNode *aParent;
    CCSprite *sprite1, *sprite2, *sprite3;
    //
    // SpriteBatchNode
    //
    // parents
    aParent = CCSpriteBatchNode::create("animations/grossini.png", 50);
    aParent->setPosition(ccp(s.width/3, s.height/2));
    addChild(aParent, 0);

    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp(0,0));

    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));

    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));

    // test issue #665
    sprite1->setVisible(false);

    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, 2);

    //
    // Sprite
    //
    aParent = CCNode::create();
    aParent->setPosition(ccp(2*s.width/3, s.height/2));
    addChild(aParent, 0);

    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite1->setPosition(ccp(0,0));

    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));

    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));

    // test issue #665
    sprite1->setVisible(false);

    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, 2);
}

SpriteChildrenVisibilityIssue665::~SpriteChildrenVisibilityIssue665()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteChildrenVisibilityIssue665::title()
{
    return "Sprite & SpriteBatchNode Visibility";
}

std::string SpriteChildrenVisibilityIssue665::subtitle()
{
    return "No sprites should be visible";
}

//------------------------------------------------------------------
//
// SpriteChildrenAnchorPoint
//
//------------------------------------------------------------------
SpriteChildrenAnchorPoint::SpriteChildrenAnchorPoint()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
    
    CCNode *aParent;
    CCSprite* sprite1, *sprite2, *sprite3, *sprite4, *point;
    //
    // SpriteBatchNode
    //
    // parents
    
    aParent = CCNode::create();
    addChild(aParent, 0);
    
    // anchor (0,0)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/4,s.height/2));
    sprite1->setAnchorPoint( ccp(0,0) );

    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );

    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);
    
    
    // anchor (0.5, 0.5)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/2,s.height/2));
    sprite1->setAnchorPoint( ccp(0.5f, 0.5f) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));

    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));

    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );        

    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);        
    
    
    // anchor (1,1)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/2+s.width/4,s.height/2));
    sprite1->setAnchorPoint( ccp(1,1) );

    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );        
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);        
}

void SpriteChildrenAnchorPoint::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteChildrenAnchorPoint::title()
{
    return "Sprite: children + anchor";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenAnchorPoint
//
//------------------------------------------------------------------
SpriteBatchNodeChildrenAnchorPoint::SpriteBatchNodeChildrenAnchorPoint()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini.plist");
    
    CCNode *aParent;
    CCSprite* sprite1, *sprite2, *sprite3, *sprite4, *point;
    //
    // SpriteBatchNode
    //
    // parents
    
    aParent = CCSpriteBatchNode::create("animations/grossini.png", 50);
    addChild(aParent, 0);
    
    // anchor (0,0)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/4,s.height/2));
    sprite1->setAnchorPoint( ccp(0,0) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);
    
    
    // anchor (0.5, 0.5)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/2,s.height/2));
    sprite1->setAnchorPoint( ccp(0.5f, 0.5f) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );        
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);        
    
    
    // anchor (1,1)
    sprite1 = CCSprite::createWithSpriteFrameName("grossini_dance_08.png");
    sprite1->setPosition(ccp(s.width/2+s.width/4,s.height/2));
    sprite1->setAnchorPoint( ccp(1,1) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossini_dance_02.png");
    sprite2->setPosition(ccp(20,30));
    
    sprite3 = CCSprite::createWithSpriteFrameName("grossini_dance_03.png");
    sprite3->setPosition(ccp(-20,30));
    
    sprite4 = CCSprite::createWithSpriteFrameName("grossini_dance_04.png");
    sprite4->setPosition(ccp(0,0));
    sprite4->setScale( 0.5f );        
    
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2, -2);
    sprite1->addChild(sprite3, -2);
    sprite1->addChild(sprite4, 3);
    
    point = CCSprite::create("Images/r1.png");
    point->setScale( 0.25f );
    point->setPosition( sprite1->getPosition() );
    addChild(point, 10);        
}

void SpriteBatchNodeChildrenAnchorPoint::onExit()
{
    SpriteTestDemo::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

std::string SpriteBatchNodeChildrenAnchorPoint::title()
{
    return "SpriteBatchNode: children + anchor";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenScale
//
//------------------------------------------------------------------
SpriteBatchNodeChildrenScale::SpriteBatchNodeChildrenScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();        
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/grossini_family.plist");

    CCNode *aParent;
    CCSprite* sprite1, *sprite2;
    CCActionInterval* rot = CCRotateBy::create(10, 360);
    CCAction* seq = CCRepeatForever::create(rot);
    
    //
    // Children + Scale using Sprite
    // Test 1
    //
    aParent = CCNode::create();
    sprite1 = CCSprite::createWithSpriteFrameName("grossinis_sister1.png");
    sprite1->setPosition( ccp( s.width/4, s.height/4) );
    sprite1->setScaleX( -0.5f );
    sprite1->setScaleY( 2.0f );
    sprite1->runAction(seq);
    
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossinis_sister2.png");
    sprite2->setPosition( ccp( 50,0) );
    
    addChild(aParent);
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2);

    
    //
    // Children + Scale using SpriteBatchNode
    // Test 2
    //
    
    aParent = CCSpriteBatchNode::create("animations/grossini_family.png");
    sprite1 = CCSprite::createWithSpriteFrameName("grossinis_sister1.png");
    sprite1->setPosition( ccp( 3*s.width/4, s.height/4) );
    sprite1->setScaleX( -0.5f );
    sprite1->setScaleY( 2.0f );
    sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossinis_sister2.png");
    sprite2->setPosition( ccp( 50,0) );
    
    addChild(aParent);
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2);

    
    //
    // Children + Scale using Sprite
    // Test 3
    //
    
    aParent = CCNode::create();
    sprite1 = CCSprite::createWithSpriteFrameName("grossinis_sister1.png");
    sprite1->setPosition( ccp( s.width/4, 2*s.height/3) );
    sprite1->setScaleX( 1.5f );
    sprite1->setScaleY( -0.5f );
    sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossinis_sister2.png");
    sprite2->setPosition( ccp( 50,0) );
    
    addChild(aParent);
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2);
    
    //
    // Children + Scale using Sprite
    // Test 4
    //
    
    aParent = CCSpriteBatchNode::create("animations/grossini_family.png");
    sprite1 = CCSprite::createWithSpriteFrameName("grossinis_sister1.png");
    sprite1->setPosition( ccp( 3*s.width/4, 2*s.height/3) );
    sprite1->setScaleX( 1.5f );
    sprite1->setScaleY( -0.5f);
    sprite1->runAction( (CCAction*)(seq->copy()->autorelease()) );
    
    sprite2 = CCSprite::createWithSpriteFrameName("grossinis_sister2.png");
    sprite2->setPosition( ccp( 50,0) );
    
    addChild(aParent);
    aParent->addChild(sprite1);
    sprite1->addChild(sprite2);
    
}

std::string SpriteBatchNodeChildrenScale::title()
{
    return "Sprite/BatchNode + child + scale + rot";
}

//------------------------------------------------------------------
//
// SpriteChildrenChildren
//
//------------------------------------------------------------------
SpriteChildrenChildren::SpriteChildrenChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();        
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");
    
    CCNode *aParent;
    CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;
    CCActionInterval* rot = CCRotateBy::create(10, 360);
    CCAction* seq = CCRepeatForever::create(rot);
    
    CCActionInterval* rot_back = rot->reverse();
    CCAction* rot_back_fe = CCRepeatForever::create(rot_back);
    
    //
    // SpriteBatchNode: 3 levels of children
    //
    
    aParent = CCNode::create();
    addChild(aParent);
    
    // parent
    l1 = CCSprite::createWithSpriteFrameName("father.gif");
    l1->setPosition( ccp( s.width/2, s.height/2) );
    l1->runAction( (CCAction*)(seq->copy()->autorelease()) );
    aParent->addChild(l1);
    CCSize l1Size = l1->getContentSize();
    
    // child left
    l2a = CCSprite::createWithSpriteFrameName("sister1.gif");
    l2a->setPosition( ccp( -50 + l1Size.width/2, 0 + l1Size.height/2) );
    l2a->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
    l1->addChild(l2a);
    CCSize l2aSize = l2a->getContentSize();        
    
    
    // child right
    l2b = CCSprite::createWithSpriteFrameName("sister2.gif");
    l2b->setPosition( ccp( +50 + l1Size.width/2, 0 + l1Size.height/2) );
    l2b->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
    l1->addChild(l2b);
    CCSize l2bSize = l2a->getContentSize();        
    
    
    // child left bottom
    l3a1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a1->setScale( 0.45f );
    l3a1->setPosition( ccp(0+l2aSize.width/2,-100+l2aSize.height/2) );
    l2a->addChild(l3a1);
    
    // child left top
    l3a2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a2->setScale( 0.45f );
    l3a1->setPosition( ccp(0+l2aSize.width/2,+100+l2aSize.height/2) );
    l2a->addChild(l3a2);
    
    // child right bottom
    l3b1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b1->setScale( 0.45f);
    l3b1->setFlipY( true );
    l3b1->setPosition( ccp(0+l2bSize.width/2,-100+l2bSize.height/2) );
    l2b->addChild(l3b1);
    
    // child right top
    l3b2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b2->setScale( 0.45f );
    l3b2->setFlipY( true );
    l3b1->setPosition( ccp(0+l2bSize.width/2,+100+l2bSize.height/2) );
    l2b->addChild(l3b2);
}

std::string SpriteChildrenChildren::title()
{
    return "Sprite multiple levels of children";
}


//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenChildren
//
//------------------------------------------------------------------

SpriteBatchNodeChildrenChildren::SpriteBatchNodeChildrenChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();        
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");
    
    CCSpriteBatchNode *aParent;
    CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;
    CCActionInterval* rot = CCRotateBy::create(10, 360);
    CCAction* seq = CCRepeatForever::create(rot);
    
    CCActionInterval* rot_back = rot->reverse();
    CCAction* rot_back_fe = CCRepeatForever::create(rot_back);
    
    //
    // SpriteBatchNode: 3 levels of children
    //
    
    aParent = CCSpriteBatchNode::create("animations/ghosts.png");
    aParent->getTexture()->generateMipmap();
    addChild(aParent);
    
    // parent
    l1 = CCSprite::createWithSpriteFrameName("father.gif");
    l1->setPosition( ccp( s.width/2, s.height/2) );
    l1->runAction( (CCAction*)(seq->copy()->autorelease()) );
    aParent->addChild(l1);
    CCSize l1Size = l1->getContentSize();

    // child left
    l2a = CCSprite::createWithSpriteFrameName("sister1.gif");
    l2a->setPosition( ccp( -50 + l1Size.width/2, 0 + l1Size.height/2) );
    l2a->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
    l1->addChild(l2a);
    CCSize l2aSize = l2a->getContentSize();        


    // child right
    l2b = CCSprite::createWithSpriteFrameName("sister2.gif");
    l2b->setPosition( ccp( +50 + l1Size.width/2, 0 + l1Size.height/2) );
    l2b->runAction( (CCAction*)(rot_back_fe->copy()->autorelease()) );
    l1->addChild(l2b);
    CCSize l2bSize = l2a->getContentSize();        

    
    // child left bottom
    l3a1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a1->setScale( 0.45f );
    l3a1->setPosition( ccp(0+l2aSize.width/2,-100+l2aSize.height/2) );
    l2a->addChild(l3a1);
    
    // child left top
    l3a2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a2->setScale( 0.45f );
    l3a1->setPosition( ccp(0+l2aSize.width/2,+100+l2aSize.height/2) );
    l2a->addChild(l3a2);
    
    // child right bottom
    l3b1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b1->setScale( 0.45f );
    l3b1->setFlipY( true );
    l3b1->setPosition( ccp(0+l2bSize.width/2,-100+l2bSize.height/2) );
    l2b->addChild(l3b1);

    // child right top
    l3b2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b2->setScale( 0.45f );
    l3b2->setFlipY( true );
    l3b1->setPosition( ccp(0+l2bSize.width/2,+100+l2bSize.height/2) );
    l2b->addChild(l3b2);
    
}

std::string SpriteBatchNodeChildrenChildren::title()
{
    return "SpriteBatchNode multiple levels of children";
}

//------------------------------------------------------------------
//
// SpriteBatchNodeSkewNegativeScaleChildren
//
//------------------------------------------------------------------

SpriteBatchNodeSkewNegativeScaleChildren::SpriteBatchNodeSkewNegativeScaleChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);

    for(int i=0;i<2;i++) {
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp( s.width/4*(i+1), s.height/2));

        // Skew
        CCSkewBy* skewX = CCSkewBy::create(2, 45, 0);
        CCSkewBy* skewX_back = (CCSkewBy*)skewX->reverse();
        CCSkewBy* skewY = CCSkewBy::create(2, 0, 45);
        CCSkewBy* skewY_back = (CCSkewBy*)skewY->reverse();

        if(i == 1)
        {
            sprite->setScale(-1.0f);
        }

        CCSequence* seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        CCSprite *child1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        child1->setPosition(ccp(sprite->getContentSize().width / 2.0f, sprite->getContentSize().height / 2.0f));

        child1->setScale(0.8f);

        sprite->addChild(child1);

        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeSkewNegativeScaleChildren::~SpriteBatchNodeSkewNegativeScaleChildren()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteBatchNodeSkewNegativeScaleChildren::title()
{
    return "SpriteBatchNode + children + skew";
}

std::string SpriteBatchNodeSkewNegativeScaleChildren::subtitle()
{
    return "SpriteBatchNode skew + negative scale with children";
}

// SpriteSkewNegativeScaleChildren

SpriteSkewNegativeScaleChildren::SpriteSkewNegativeScaleChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    CCNode *parent = CCNode::create();
    addChild(parent);

    for(int i=0;i<2;i++) {
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp( s.width/4*(i+1), s.height/2));

        // Skew
        CCSkewBy* skewX = CCSkewBy::create(2, 45, 0);
        CCSkewBy* skewX_back = (CCSkewBy*)skewX->reverse();
        CCSkewBy* skewY = CCSkewBy::create(2, 0, 45);
        CCSkewBy* skewY_back = (CCSkewBy*)skewY->reverse();

        if(i == 1)
        {
            sprite->setScale(-1.0f);
        }

        CCSequence* seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        CCSprite *child1 = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        child1->setPosition(ccp(sprite->getContentSize().width / 2.0f, sprite->getContentSize().height / 2.0f));

        sprite->addChild(child1);

        child1->setScale(0.8f);

        parent->addChild(sprite, i);
    }
}

SpriteSkewNegativeScaleChildren::~SpriteSkewNegativeScaleChildren()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

std::string SpriteSkewNegativeScaleChildren::title()
{
    return "Sprite + children + skew";
}

std::string SpriteSkewNegativeScaleChildren::subtitle()
{
    return "Sprite skew + negative scale with children";
}

//------------------------------------------------------------------
//
// SpriteNilTexture
//
//------------------------------------------------------------------

SpriteNilTexture::SpriteNilTexture()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite* sprite = NULL;
    
    // TEST: If no texture is given, then Opacity + Color should work.

    sprite = new CCSprite();
    sprite->init();
    sprite->setTextureRect( CCRectMake(0, 0, 300,300) );
    sprite->setColor(ccRED);
    sprite->setOpacity(128);
    sprite->setPosition(ccp(3*s.width/4, s.height/2));
    addChild(sprite, 100);
    sprite->release();

    sprite = new CCSprite();
    sprite->init();
    sprite->setTextureRect(CCRectMake(0, 0, 300,300));
    sprite->setColor(ccBLUE);
    sprite->setOpacity(128);
    sprite->setPosition(ccp(1*s.width/4, s.height/2));
    addChild(sprite, 100);
    sprite->release();
}

std::string SpriteNilTexture::title()
{
    return "Sprite without texture";
}

std::string SpriteNilTexture::subtitle()
{
    return "opacity and color should work";
}

class MySprite1 : public CCSprite
{
public:
    MySprite1() : ivar(10) {}
    static MySprite1* createWithSpriteFrameName(const char *pszSpriteFrameName)
    {
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
        MySprite1 *pobSprite = new MySprite1();
        pobSprite->initWithSpriteFrame(pFrame);
        pobSprite->autorelease();

        return pobSprite;
    }

private:
    int ivar;
};

class MySprite2 : public CCSprite
{
public:
    MySprite2() : ivar(10) {}
    static MySprite2* create(const char *pszName)
    {
        MySprite2 *pobSprite = new MySprite2();
        pobSprite->initWithFile(pszName);
        pobSprite->autorelease();

        return pobSprite;
    }

private:
    int ivar;
};

//------------------------------------------------------------------
//
// SpriteSubclass
//
//------------------------------------------------------------------
SpriteSubclass::SpriteSubclass()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");
    CCSpriteBatchNode *aParent = CCSpriteBatchNode::create("animations/ghosts.png");

    // MySprite1
    MySprite1 *sprite = MySprite1::createWithSpriteFrameName("father.gif");
    sprite->setPosition(ccp( s.width/4*1, s.height/2));
    aParent->addChild(sprite);
    addChild(aParent);

    // MySprite2
    MySprite2 *sprite2 = MySprite2::create("Images/grossini.png");
    addChild(sprite2);
    sprite2->setPosition(ccp(s.width/4*3, s.height/2));
}

std::string SpriteSubclass::title()
{
    return "Sprite subclass";
}

std::string SpriteSubclass::subtitle()
{
    return "Testing initWithTexture:rect method";
}


class DoubleSprite : public CCSprite
{
public:
    DoubleSprite() {m_bHD = false;}
    virtual bool initWithTexture(CCTexture2D* texture, CCRect rect);
    // Called everytime the vertex needs to be updated.
    virtual void setContentSize(const CCSize& size);
    // rect used only for the vertex. Called everytime the vertex needs to be updated.
    virtual void setVertexRect(CCRect rect);

    static DoubleSprite* create(const char* pszFileName);
    bool m_bHD;
};

DoubleSprite* DoubleSprite::create(const char* pszFileName)
{
    DoubleSprite* pSp = new DoubleSprite();
    pSp->initWithFile(pszFileName);
    pSp->autorelease();
    return pSp;
}

bool DoubleSprite::initWithTexture(CCTexture2D* texture, CCRect rect)
{
    if( CCSprite::initWithTexture(texture, rect)) 
    {
        return true;
    }

    return false;
}

// Called everytime the vertex needs to be updated.
void DoubleSprite::setContentSize(const CCSize& size)
{
    CCSize s = size;
    // If Retina Display and Texture is in HD then scale the vertex rect
    if( CC_CONTENT_SCALE_FACTOR() == 2 && ! m_bHD ) {
        s.width *= 2;
        s.height *= 2;
    }

    CCSprite::setContentSize(s);
}

// rect used only for the vertex. Called everytime the vertex needs to be updated.
void DoubleSprite::setVertexRect(CCRect rect)
{
    // If Retina Display and Texture is in HD then scale the vertex rect
    if( CC_CONTENT_SCALE_FACTOR() == 2 && ! m_bHD ) {
        rect.size.width *= 2;
        rect.size.height *= 2;
    }

    CCSprite::setVertexRect(rect);
}


// SpriteDoubleResolution

SpriteDoubleResolution::SpriteDoubleResolution()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    //
    // LEFT: SD sprite
    //
    // there is no HD resolution file of grossini_dance_08.
    DoubleSprite *spriteSD = DoubleSprite::create("Images/grossini_dance_08.png");
    addChild(spriteSD);
    spriteSD->setPosition(ccp(s.width/4*1,s.height/2));

    CCSprite *child1_left = DoubleSprite::create("Images/grossini_dance_08.png");
    spriteSD->addChild(child1_left);
    child1_left->setPosition(ccp(-30,0));

    CCSprite *child1_right = CCSprite::create("Images/grossini.png");
    spriteSD->addChild(child1_right);
    child1_left->setPosition(ccp( spriteSD->getContentSize().height, 0));



    //
    // RIGHT: HD sprite
    //
    // there is an HD version of grossini.png
    CCSprite *spriteHD = CCSprite::create("Images/grossini.png");
    addChild(spriteHD);
    spriteHD->setPosition(ccp(s.width/4*3,s.height/2));

    CCSprite *child2_left = DoubleSprite::create("Images/grossini_dance_08.png");
    spriteHD->addChild(child2_left);
    child2_left->setPosition(ccp(-30,0));

    CCSprite *child2_right = CCSprite::create("Images/grossini.png");
    spriteHD->addChild(child2_right);
    child2_left->setPosition(ccp( spriteHD->getContentSize().height, 0));



    // Actions
    CCScaleBy* scale = CCScaleBy::create(2, 0.5);
    CCScaleBy* scale_back = (CCScaleBy*)scale->reverse();
    CCSequence* seq = CCSequence::create(scale, scale_back, NULL);

    CCSequence* seq_copy = (CCSequence*)seq->copy()->autorelease();

    spriteSD->runAction(seq);
    spriteHD->runAction(seq_copy);

}

std::string SpriteDoubleResolution::title()
{
    return "Sprite Double resolution";
}

std::string SpriteDoubleResolution::subtitle()
{
    return "Retina Display. SD (left) should be equal to HD (right)";
}

//------------------------------------------------------------------
//
// AnimationCache
//
//------------------------------------------------------------------
AnimationCache::AnimationCache()
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("animations/grossini.plist");
    frameCache->addSpriteFramesWithFile("animations/grossini_gray.plist");
    frameCache->addSpriteFramesWithFile("animations/grossini_blue.plist");

    //
    // create animation "dance"
    //
    CCArray* animFrames = CCArray::createWithCapacity(15);
    char str[100] = {0};
    for(int i = 1; i < 15; i++)
    {
        sprintf(str, "grossini_dance_%02d.png",i);
        CCSpriteFrame *frame = frameCache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);

    // Add an animation to the Cache
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "dance");

    //
    // create animation "dance gray"
    //
    animFrames->removeAllObjects();

    for(int i = 1; i < 15; i++)
    {
        sprintf(str, "grossini_dance_gray_%02d.png",i);
        CCSpriteFrame *frame = frameCache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }

    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);

    // Add an animation to the Cache
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "dance_gray");

    //
    // create animation "dance blue"
    //
    animFrames->removeAllObjects();

    for(int i = 1; i < 4; i++)
    {
        sprintf(str, "grossini_blue_%02d.png",i);
        CCSpriteFrame *frame = frameCache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }

    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);

    // Add an animation to the Cache
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "dance_blue");


    CCAnimationCache *animCache = CCAnimationCache::sharedAnimationCache();

    CCAnimation *normal = animCache->animationByName("dance");
    normal->setRestoreOriginalFrame(true);
    CCAnimation *dance_grey = animCache->animationByName("dance_gray");
    dance_grey->setRestoreOriginalFrame(true);
    CCAnimation *dance_blue = animCache->animationByName("dance_blue");
    dance_blue->setRestoreOriginalFrame(true);

    CCAnimate *animN = CCAnimate::create(normal);
    CCAnimate *animG = CCAnimate::create(dance_grey);
    CCAnimate *animB = CCAnimate::create(dance_blue);

    CCSequence *seq = CCSequence::create(animN, animG, animB, NULL);

    // create an sprite without texture
    CCSprite *grossini = CCSprite::create();
    CCSpriteFrame *frame = frameCache->spriteFrameByName("grossini_dance_01.png");
    grossini->setDisplayFrame(frame);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    grossini->setPosition(ccp(winSize.width/2, winSize.height/2));
    addChild(grossini);

    // run the animation
    grossini->runAction(seq);
}

std::string AnimationCache::title()
{
    return "AnimationCache";
}

std::string AnimationCache::subtitle()
{
    return "Sprite should be animated";
}

// AnimationCacheFile


AnimationCacheFile::AnimationCacheFile()
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("animations/grossini.plist");
    frameCache->addSpriteFramesWithFile("animations/grossini_gray.plist");
    frameCache->addSpriteFramesWithFile("animations/grossini_blue.plist");


    // Purge previously loaded animation
    CCAnimationCache::purgeSharedAnimationCache();

    CCAnimationCache *animCache = CCAnimationCache::sharedAnimationCache();

    // Add an animation to the Cache
    animCache->addAnimationsWithFile("animations/animations.plist");


    CCAnimation *normal = animCache->animationByName("dance_1");
    normal->setRestoreOriginalFrame(true);
    CCAnimation *dance_grey = animCache->animationByName("dance_2");
    dance_grey->setRestoreOriginalFrame(true);
    CCAnimation *dance_blue = animCache->animationByName("dance_3");
    dance_blue->setRestoreOriginalFrame(true);

    CCAnimate *animN = CCAnimate::create(normal);
    CCAnimate *animG = CCAnimate::create(dance_grey);
    CCAnimate *animB = CCAnimate::create(dance_blue);

    CCSequence *seq = CCSequence::create(animN, animG, animB, NULL);

    // create an sprite without texture
    CCSprite *grossini = CCSprite::create();

    CCSpriteFrame *frame = frameCache->spriteFrameByName("grossini_dance_01.png");
    grossini->setDisplayFrame(frame);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    grossini->setPosition(ccp(winSize.width/2, winSize.height/2));

    addChild(grossini);


    // run the animation
    grossini->runAction(seq);
}

std::string AnimationCacheFile::title()
{
    return "AnimationCache - Load file";
}

std::string AnimationCacheFile::subtitle()
{
    return "Sprite should be animated";
}

// SpriteBatchBug1217

SpriteBatchBug1217::SpriteBatchBug1217()
{
    CCSpriteBatchNode *bn = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);

    CCSprite * s1 = CCSprite::createWithTexture(bn->getTexture(), CCRectMake(0, 0, 57, 57));
    CCSprite * s2 = CCSprite::createWithTexture(bn->getTexture(), CCRectMake(0, 0, 57, 57));
    CCSprite * s3 = CCSprite::createWithTexture(bn->getTexture(), CCRectMake(0, 0, 57, 57));

    s1->setColor(ccc3(255, 0, 0));
    s2->setColor(ccc3(0, 255, 0));
    s3->setColor(ccc3(0, 0, 255));

    s1->setPosition(ccp(20,200));
    s2->setPosition(ccp(100,0));
    s3->setPosition(ccp(100,0));

    bn->setPosition(ccp(0,0));

    //!!!!!
    s1->addChild(s2);
    s2->addChild(s3);
    bn->addChild(s1);

    addChild(bn);
}

std::string SpriteBatchBug1217::title()
{
    return "SpriteBatch - Bug 1217";
}

std::string SpriteBatchBug1217::subtitle()
{
    return "Adding big family to spritebatch. You shall see 3 heads";
}


void SpriteTestScene::runThisTest()
{
    CCLayer* pLayer = nextSpriteTestAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

//
// SpriteOffsetAnchorSkew
// 
SpriteOffsetAnchorSkew::SpriteOffsetAnchorSkew()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 1);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());

        CCArray *animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", j + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        CCSkewBy *skewX = CCSkewBy::create(2, 45, 0);
        CCActionInterval *skewX_back = skewX->reverse();
        CCSkewBy *skewY = CCSkewBy::create(2, 0, 45);
        CCActionInterval *skewY_back = skewY->reverse();

        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        addChild(sprite, 0);
    }
}

SpriteOffsetAnchorSkew::~SpriteOffsetAnchorSkew()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteOffsetAnchorSkew::title()
{
    return "Sprite offset + anchor + scale";
}

//
// SpriteBatchNodeOffsetAnchorSkew
// 
SpriteBatchNodeOffsetAnchorSkew::SpriteBatchNodeOffsetAnchorSkew()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());
        
        CCArray* animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", j + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        CCSkewBy *skewX = CCSkewBy::create(2, 45, 0);
        CCActionInterval *skewX_back = skewX->reverse();
        CCSkewBy *skewY = CCSkewBy::create(2, 0, 45);
        CCActionInterval *skewY_back = skewY->reverse();

        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeOffsetAnchorSkew::~SpriteBatchNodeOffsetAnchorSkew()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteBatchNodeOffsetAnchorSkew::title()
{
    return "SpriteBatchNode offset + anchor + skew";
}

//
// SpriteOffsetAnchorSkewScale
//
SpriteOffsetAnchorSkewScale::SpriteOffsetAnchorSkewScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 1);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());

        CCArray *animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", j + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        // Skew
        CCSkewBy *skewX = CCSkewBy::create(2, 45, 0);
        CCActionInterval *skewX_back = skewX->reverse();
        CCSkewBy *skewY = CCSkewBy::create(2, 0, 45);
        CCActionInterval *skewY_back = skewY->reverse();

        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        // Scale
        CCScaleBy *scale = CCScaleBy::create(2, 2);
        CCActionInterval *scale_back = scale->reverse();
        CCSequence *seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale));

        addChild(sprite, 0);
    }
}

SpriteOffsetAnchorSkewScale::~SpriteOffsetAnchorSkewScale()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteOffsetAnchorSkewScale::title()
{
    return "Sprite anchor + skew + scale";
}

SpriteBatchNodeOffsetAnchorSkewScale::SpriteBatchNodeOffsetAnchorSkewScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());        

        CCArray *animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", j + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        // skew
        CCSkewBy *skewX = CCSkewBy::create(2, 45, 0);
        CCActionInterval *skewX_back = skewX->reverse();
        CCSkewBy *skewY = CCSkewBy::create(2, 0, 45);
        CCActionInterval *skewY_back = skewY->reverse();

        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));

        // scale 
        CCScaleBy *scale = CCScaleBy::create(2, 2);
        CCActionInterval *scale_back = scale->reverse();
        CCSequence *seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale));

        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeOffsetAnchorSkewScale::~SpriteBatchNodeOffsetAnchorSkewScale()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteBatchNodeOffsetAnchorSkewScale::title()
{
    return "SpriteBatchNode anchor + skew + scale";
}

//
// SpriteOffsetAnchorFlip
// 
SpriteOffsetAnchorFlip::SpriteOffsetAnchorFlip()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 1);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());

        CCArray* animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", i + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        CCFlipY *flip = CCFlipY::create(true);
        CCFlipY *flip_back = CCFlipY::create(false);
        CCDelayTime *delay = CCDelayTime::create(1);
        CCSequence *seq = CCSequence::create(delay, flip, delay->copy()->autorelease(), flip_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq));

        addChild(sprite, 0);
    }
}

SpriteOffsetAnchorFlip::~SpriteOffsetAnchorFlip()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteOffsetAnchorFlip::title()
{
    return "Sprite offset + anchor + flip";
}

string SpriteOffsetAnchorFlip::subtitle()
{
    return "issue #1078";
}

//
// SpriteBatchNodeOffsetAnchorFlip
// 

SpriteBatchNodeOffsetAnchorFlip::SpriteBatchNodeOffsetAnchorFlip()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);

    for (int i = 0; i < 3; i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width / 4 * (i + 1), s.height / 2));

        CCSprite *point = CCSprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);

        switch (i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1, 1));
            break;
        }

        point->setPosition(sprite->getPosition());        

        CCArray *animFrames = CCArray::create();
        char tmp[50];
        for (int j = 0; j < 14; j++)
        {            
            sprintf(tmp, "grossini_dance_%02d.png", i + 1);
            CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
            animFrames->addObject(frame);
        }

        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

        CCFlipY *flip = CCFlipY::create(true);
        CCFlipY *flip_back = CCFlipY::create(false);
        CCDelayTime *delay = CCDelayTime::create(1);
        CCSequence *seq = CCSequence::create(delay, flip, delay->copyWithZone(NULL)->autorelease(), flip_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq));

        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeOffsetAnchorFlip::~SpriteBatchNodeOffsetAnchorFlip()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteBatchNodeOffsetAnchorFlip::title()
{
    return "SpriteBatchNode offset + anchor + flip";
}

string SpriteBatchNodeOffsetAnchorFlip::subtitle()
{
    return "issue #1078";
}


/// NodeSort

NodeSort::NodeSort()
{
    m_pNode = CCNode::create();
    addChild(m_pNode, 0, 0);

    m_pSprite1 = CCSprite::create("Images/piece.png", CCRectMake(128, 0, 64, 64));
    m_pSprite1->setPosition(ccp(100, 160));
    m_pNode->addChild(m_pSprite1, -6, 1);

    m_pSprite2 = CCSprite::create("Images/piece.png", CCRectMake(128, 0, 64, 64));
    m_pSprite2->setPosition(ccp(164, 160));
    m_pNode->addChild(m_pSprite2, -6, 2);

    m_pSprite4 = CCSprite::create("Images/piece.png", CCRectMake(128, 0, 64, 64));
    m_pSprite4->setPosition(ccp(292, 160));
    m_pNode->addChild(m_pSprite4, -3, 4);

    m_pSprite3 = CCSprite::create("Images/piece.png", CCRectMake(128, 0, 64, 64));
    m_pSprite3->setPosition(ccp(228, 160));
    m_pNode->addChild(m_pSprite3, -4, 3);

    m_pSprite5 = CCSprite::create("Images/piece.png", CCRectMake(128, 0, 64, 64));
    m_pSprite5->setPosition(ccp(356, 160));
    m_pNode->addChild(m_pSprite5, -3, 5);

    schedule(schedule_selector(NodeSort::reorderSprite));
}

std::string NodeSort::title()
{
    return "node sort same index";
}

std::string NodeSort::subtitle()
{
    return "tag order in console should be 2,1,3,4,5";
}

void NodeSort::reorderSprite(float dt)
{
    unschedule(schedule_selector(NodeSort::reorderSprite));

    CCLog("Before reorder--");
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pNode->getChildren(), pObj)
    {
        CCSprite *child = (CCSprite*)pObj;
        CCLog("tag %i z %i",(int)child->getTag(),(int)child->getZOrder());
    }
    //z-4
    m_pNode->reorderChild((CCNode *)m_pNode->getChildren()->objectAtIndex(0), -6);

    m_pNode->sortAllChildren();
    CCLog("After reorder--");
    CCARRAY_FOREACH(m_pNode->getChildren(), pObj)
    {
        CCSprite *child = (CCSprite*)pObj;
        CCLog("tag %i z %i",(int)child->getTag(),(int)child->getZOrder());
    }
}

/// SpriteBatchNodeReorderSameIndex
SpriteBatchNodeReorderSameIndex::SpriteBatchNodeReorderSameIndex()
{
    m_pBatchNode = CCSpriteBatchNode::create("Images/piece.png", 15);
    addChild(m_pBatchNode, 1, 0);

    m_pSprite1 = CCSprite::createWithTexture(m_pBatchNode->getTexture(), CCRectMake(128,0,64,64));
    m_pSprite1->setPosition(ccp(100,160));
    m_pBatchNode->addChild(m_pSprite1, 3, 1);

    m_pSprite2= CCSprite::createWithTexture(m_pBatchNode->getTexture(), CCRectMake(128,0,64,64));
    m_pSprite2->setPosition(ccp(164,160));
    m_pBatchNode->addChild(m_pSprite2, 4, 2);

    m_pSprite3 = CCSprite::createWithTexture(m_pBatchNode->getTexture(), CCRectMake(128,0,64,64));
    m_pSprite3->setPosition(ccp(228,160));
    m_pBatchNode->addChild(m_pSprite3, 4, 3);

    m_pSprite4 = CCSprite::createWithTexture(m_pBatchNode->getTexture(), CCRectMake(128,0,64,64));
    m_pSprite4->setPosition(ccp(292,160));
    m_pBatchNode->addChild(m_pSprite4, 5, 4);

    m_pSprite5 = CCSprite::createWithTexture(m_pBatchNode->getTexture(), CCRectMake(128,0,64,64));
    m_pSprite5->setPosition(ccp(356,160));
    m_pBatchNode->addChild(m_pSprite5, 6, 5);


    scheduleOnce(schedule_selector(SpriteBatchNodeReorderSameIndex::reorderSprite), 2);
}

std::string SpriteBatchNodeReorderSameIndex::title()
{
    return "SpriteBatchNodeReorder same index";
}

std::string SpriteBatchNodeReorderSameIndex::subtitle()
{
    return "tag order in console should be 2,3,4,5,1";
}

void SpriteBatchNodeReorderSameIndex::reorderSprite(float dt)
{
    m_pBatchNode->reorderChild(m_pSprite4, 4);
    m_pBatchNode->reorderChild(m_pSprite5, 4);
    m_pBatchNode->reorderChild(m_pSprite1, 4);

    m_pBatchNode->sortAllChildren();
    CCObject *child;
    CCARRAY_FOREACH(m_pBatchNode->getDescendants(), child)
    {
        CCLog("tag %i", (int)((CCSprite *)child)->getTag());
    }    
}

/// SpriteBatchNodeReorderOneChild
SpriteBatchNodeReorderOneChild::SpriteBatchNodeReorderOneChild()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animations/ghosts.plist");

    CCSpriteBatchNode *aParent;
    CCSprite *l1, *l2a, *l2b, *l3a1, *l3a2, *l3b1, *l3b2;

    //
    // SpriteBatchNode: 3 levels of children
    //

    aParent = CCSpriteBatchNode::create("animations/ghosts.png");

    m_pBatchNode = aParent;
    //[[aParent texture] generateMipmap];
    addChild(aParent);

    // parent
    l1 = CCSprite::createWithSpriteFrameName("father.gif");
    l1->setPosition(ccp( s.width/2, s.height/2));

    aParent->addChild(l1);
    CCSize l1Size = l1->getContentSize();

    // child left
    l2a = CCSprite::createWithSpriteFrameName("sister1.gif");
    l2a->setPosition(ccp( -10 + l1Size.width/2, 0 + l1Size.height/2));

    l1->addChild(l2a, 1);
    CCSize l2aSize = l2a->getContentSize();


    // child right
    l2b = CCSprite::createWithSpriteFrameName("sister2.gif");
    l2b->setPosition(ccp( +50 + l1Size.width/2, 0 + l1Size.height/2));

    l1->addChild(l2b, 2);
    CCSize l2bSize = l2a->getContentSize();


    // child left bottom
    l3a1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a1->setScale(0.45f);
    l3a1->setPosition(ccp(0+l2aSize.width/2,-50+l2aSize.height/2));
    l2a->addChild(l3a1, 1);

    // child left top
    l3a2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3a2->setScale(0.45f);
    l3a2->setPosition(ccp(0+l2aSize.width/2,+50+l2aSize.height/2));
    l2a->addChild(l3a2, 2);

    m_pReorderSprite = l2a;

    // child right bottom
    l3b1 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b1->setScale(0.45f);
    l3b1->setFlipY(true);
    l3b1->setPosition(ccp(0+l2bSize.width/2,-50+l2bSize.height/2));
    l2b->addChild(l3b1);

    // child right top
    l3b2 = CCSprite::createWithSpriteFrameName("child1.gif");
    l3b2->setScale(0.45f);
    l3b2->setFlipY(true);
    l3b2->setPosition(ccp(0+l2bSize.width/2,+50+l2bSize.height/2));
    l2b->addChild(l3b2);

    scheduleOnce(schedule_selector(SpriteBatchNodeReorderOneChild::reorderSprite), 2.0f);
}

void SpriteBatchNodeReorderOneChild::reorderSprite(float dt)
{
    m_pReorderSprite->getParent()->reorderChild(m_pReorderSprite, -1);

    m_pBatchNode->sortAllChildren();
    //CCSprite* child;
    //CCARRAY_FOREACH(batchNode.descendants,child) NSLog(@"tag %i",child.tag);
}

std::string SpriteBatchNodeReorderOneChild::title()
{
    return "SpriteBatchNode reorder 1 child";
}

// SpriteOffsetAnchorRotationalSkew
SpriteOffsetAnchorRotationalSkew::SpriteOffsetAnchorRotationalSkew()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    for(int i=0;i<3;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
                            
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 1);
        
        switch(i)
        {
            case 0:
                sprite->setAnchorPoint(CCPointZero);
                break;
            case 1:
                sprite->setAnchorPoint(ccp(0.5f, 0.5f));
                break;
            case 2:
                sprite->setAnchorPoint(ccp(1,1));
                break;
        }
        
        point->setPosition(sprite->getPosition());
        
        CCArray *animFrames = CCArray::create();
        for(int i = 0; i < 14; i++)
        {
            char pngName[30];
            snprintf(pngName, 30, "grossini_dance_%02d.png", (i+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(pngName);
            animFrames->addObject(frame);
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        addChild(sprite, 0);
    }
}

SpriteOffsetAnchorRotationalSkew::~SpriteOffsetAnchorRotationalSkew()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteOffsetAnchorRotationalSkew::title()
{
    return "Sprite offset + anchor + rotational skew";
}

// SpriteBatchNodeOffsetAnchorRotationalSkew
SpriteBatchNodeOffsetAnchorRotationalSkew::SpriteBatchNodeOffsetAnchorRotationalSkew()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);
    
    for(int i=0;i<3;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);
        
        switch(i)
        {
            case 0:
                sprite->setAnchorPoint(CCPointZero);
                break;
            case 1:
                sprite->setAnchorPoint(ccp(0.5f, 0.5f));
                break;
            case 2:
                sprite->setAnchorPoint(ccp(1,1));
                break;
        }
        
        point->setPosition(sprite->getPosition());
        
        CCArray *animFrames = CCArray::create();
        for(int j = 0; j < 14; j++)
        {
            char pngName[30];
            snprintf(pngName, 30, "grossini_dance_%02d.png", (j+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(pngName);
            animFrames->addObject(frame);
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeOffsetAnchorRotationalSkew::~SpriteBatchNodeOffsetAnchorRotationalSkew()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteBatchNodeOffsetAnchorRotationalSkew::title()
{
    return "SpriteBatchNode offset + anchor + rot skew";
}

// SpriteOffsetAnchorRotationalSkewScale
SpriteOffsetAnchorRotationalSkewScale::SpriteOffsetAnchorRotationalSkewScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    for(int i=0;i<3;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 1);
        
        switch(i)
        {
            case 0:
                sprite->setAnchorPoint(CCPointZero);
                break;
            case 1:
                sprite->setAnchorPoint(ccp(0.5f, 0.5f));
                break;
            case 2:
                sprite->setAnchorPoint(ccp(1,1));
                break;
        }
        
        point->setPosition(sprite->getPosition());
        
        CCArray *animFrames = CCArray::create();
        for(int j = 0; j < 14; j++)
        {
            char pngName[30];
            snprintf(pngName, 30, "grossini_dance_%02d.png", (j+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(pngName);
            animFrames->addObject(frame);
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        
        // Skew
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        // Scale
        CCScaleBy *scale = CCScaleBy::create(2, 2);
        CCScaleBy *scale_back = (CCScaleBy *)scale->reverse();
        CCSequence *seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale));
        
        addChild(sprite, i);
    }
}

SpriteOffsetAnchorRotationalSkewScale::~SpriteOffsetAnchorRotationalSkewScale()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteOffsetAnchorRotationalSkewScale::title()
{
    return "Sprite anchor + rot skew + scale";
}

// SpriteBatchNodeOffsetAnchorRotationalSkewScale
SpriteBatchNodeOffsetAnchorRotationalSkewScale::SpriteBatchNodeOffsetAnchorRotationalSkewScale()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);
    
    for(int i=0;i<3;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);
        
        switch(i)
        {
            case 0:
                sprite->setAnchorPoint(CCPointZero);
                break;
            case 1:
                sprite->setAnchorPoint(ccp(0.5f, 0.5f));
                break;
            case 2:
                sprite->setAnchorPoint(ccp(1,1));
                break;
        }
        
        point->setPosition(sprite->getPosition());
        
        CCArray *animFrames = CCArray::create();
        for(int j = 0; j < 14; j++)
        {
            char pngName[30];
            snprintf(pngName, 30, "grossini_dance_%02d.png", (j+1));
            CCSpriteFrame *frame = cache->spriteFrameByName(pngName);
            animFrames->addObject(frame);
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
        sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        
        // Skew
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        // Scale
        CCScaleBy *scale = CCScaleBy::create(2, 2);
        CCScaleBy *scale_back = (CCScaleBy *)scale->reverse();
        CCSequence *seq_scale = CCSequence::create(scale, scale_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_scale));
        
        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeOffsetAnchorRotationalSkewScale::~SpriteBatchNodeOffsetAnchorRotationalSkewScale()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteBatchNodeOffsetAnchorRotationalSkewScale::title()
{
    return "SpriteBatchNode anchor + rot skew + scale";
}

// SpriteRotationalSkewNegativeScaleChildren
SpriteRotationalSkewNegativeScaleChildren::SpriteRotationalSkewNegativeScaleChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCNode *parent = CCNode::create();
    addChild(parent);
    
    for(int i=0;i<2;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);
        
        // Skew
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        if (1 == 1)
        {
            sprite->setScale(-1.0f);
        }
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        CCSprite *child1 = CCSprite::create("Images/grossini_dance_01.png");
        child1->setPosition(ccp(sprite->getContentSize().width/2.0f, sprite->getContentSize().height/2.0f));
        
        sprite->addChild(child1);
        
        child1->setScale(0.8f);
        
        parent->addChild(sprite, i);
    }
}

SpriteRotationalSkewNegativeScaleChildren::~SpriteRotationalSkewNegativeScaleChildren()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("animations/grossini.plist");
    cache->removeSpriteFramesFromFile("animations/grossini_gray.plist");
}

string SpriteRotationalSkewNegativeScaleChildren::title()
{
    return "Sprite rot skew + negative scale with children";
}

// SpriteBatchNodeRotationalSkewNegativeScaleChildren
SpriteBatchNodeRotationalSkewNegativeScaleChildren::SpriteBatchNodeRotationalSkewNegativeScaleChildren()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animations/grossini.plist");
    cache->addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png");
    
    CCSpriteBatchNode *spritebatch = CCSpriteBatchNode::create("animations/grossini.png");
    addChild(spritebatch);
    
    for(int i=0;i<2;i++)
    {
        //
        // Animation using Sprite batch
        //
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
        sprite->setPosition(ccp(s.width/4*(i+1), s.height/2));
        
        CCSprite *point = CCSprite::create("Images/r1.png");
        
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 200);
        
        // Skew
        CCRotateBy *skewX = CCRotateBy::create(2, 45, 0);
        CCRotateBy *skewX_back = (CCRotateBy*)skewX->reverse();
        CCRotateBy *skewY = CCRotateBy::create(2, 0, 45);
        CCRotateBy *skewY_back = (CCRotateBy*)skewY->reverse();
        
        if (1 == 1)
        {
            sprite->setScale(-1.0f);
        }
        
        CCSequence *seq_skew = CCSequence::create(skewX, skewX_back, skewY, skewY_back, NULL);
        sprite->runAction(CCRepeatForever::create(seq_skew));
        
        CCSprite *child1 = CCSprite::create("Images/grossini_dance_01.png");
        child1->setPosition(ccp(sprite->getContentSize().width/2.0f, sprite->getContentSize().height/2.0f));
        
        sprite->addChild(child1);
        
        child1->setScale(0.8f);
        
        spritebatch->addChild(sprite, i);
    }
}

SpriteBatchNodeRotationalSkewNegativeScaleChildren::~SpriteBatchNodeRotationalSkewNegativeScaleChildren()
{
    
}

string SpriteBatchNodeRotationalSkewNegativeScaleChildren::title()
{
    return "SpriteBatchNode + children + rot skew";
}
