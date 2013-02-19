#include "EffectsAdvancedTest.h"

enum 
{
    kTagTextLayer = 1,

    kTagSprite1 = 1,
    kTagSprite2 = 2,

    kTagBackground = 1,
    kTagLabel = 2,
};

//------------------------------------------------------------------
//
// Effect1
//
//------------------------------------------------------------------
void Effect1::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    CCNode* target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     Lens3D is Grid3D and it's size is (15,10)
    //     Waves3D is Grid3D and it's size is (15,10)
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCActionInterval* lens = CCLens3D::create(0.0f, CCSizeMake(15,10), ccp(size.width/2,size.height/2), 240);
    CCActionInterval* waves = CCWaves3D::create(10, CCSizeMake(15,10), 18, 15);

    CCFiniteTimeAction* reuse = CCReuseGrid::create(1);
    CCActionInterval* delay = CCDelayTime::create(8);

    CCActionInterval* orbit = CCOrbitCamera::create(5, 1, 2, 0, 180, 0, -90);
    CCActionInterval* orbit_back = orbit->reverse();

    target->runAction( CCRepeatForever::create( CCSequence::create( orbit, orbit_back, NULL)  ) );
    target->runAction( CCSequence::create(lens, delay, reuse, waves, NULL) );
}

std::string Effect1::title()
{
    return "Lens + Waves3d and OrbitCamera";
}

//------------------------------------------------------------------
//
// Effect2
//
//------------------------------------------------------------------
void Effect2::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    CCNode* target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     ShakyTiles is TiledGrid3D and it's size is (15,10)
    //     Shuffletiles is TiledGrid3D and it's size is (15,10)
    //       TurnOfftiles is TiledGrid3D and it's size is (15,10)
    CCActionInterval* shaky = CCShakyTiles3D::create(5, CCSizeMake(15,10), 4, false);
    CCActionInterval* shuffle = CCShuffleTiles::create(0, CCSizeMake(15,10), 3);
    CCActionInterval* turnoff = CCTurnOffTiles::create(0, CCSizeMake(15,10), 3);
    CCActionInterval* turnon = turnoff->reverse();
    
    // reuse 2 times:
    //   1 for shuffle
    //   2 for turn off
    //   turnon tiles will use a new grid
    CCFiniteTimeAction* reuse = CCReuseGrid::create(2);

    CCActionInterval* delay = CCDelayTime::create(1);
    
//    id orbit = [OrbitCamera::create:5 radius:1 deltaRadius:2 angleZ:0 deltaAngleZ:180 angleX:0 deltaAngleX:-90];
//    id orbit_back = [orbit reverse];
//
//    [target runAction: [RepeatForever::create: [Sequence actions: orbit, orbit_back, nil]]];
    target->runAction(CCSequence::create( shaky, delay, reuse, shuffle, delay->copy()->autorelease(), turnoff, turnon, NULL) );
}

std::string Effect2::title()
{
    return "ShakyTiles + ShuffleTiles + TurnOffTiles";
}


//------------------------------------------------------------------
//
// Effect3
//
//------------------------------------------------------------------
void Effect3::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    CCNode* bg = getChildByTag(kTagBackground);
    CCNode* target1 = bg->getChildByTag(kTagSprite1);
    CCNode* target2 = bg->getChildByTag(kTagSprite2);    
    
    CCActionInterval* waves = CCWaves::create(5, CCSizeMake(15,10), 5, 20, true, false);
    CCActionInterval* shaky = CCShaky3D::create(5, CCSizeMake(15,10), 4, false);
    
    target1->runAction( CCRepeatForever::create( waves ) );
    target2->runAction( CCRepeatForever::create( shaky ) );
    
    // moving background. Testing issue #244
    CCActionInterval* move = CCMoveBy::create(3, ccp(200,0) );
    bg->runAction(CCRepeatForever::create( CCSequence::create(move, move->reverse(), NULL) ));    
}

std::string Effect3::title()
{
    return "Effects on 2 sprites";
}


//------------------------------------------------------------------
//
// Effect4
//
//------------------------------------------------------------------

class Lens3DTarget : public CCNode
{
public:
    virtual void setPosition(const CCPoint& var)
    {
        m_pLens3D->setPosition(var);
    }
    
    virtual const CCPoint& getPosition()
    {
        return m_pLens3D->getPosition();
    }
    
    static Lens3DTarget* create(CCLens3D* pAction)
    {
        Lens3DTarget* pRet = new Lens3DTarget();
        pRet->m_pLens3D = pAction;
        pRet->autorelease();
        return pRet;
    }
private:

    Lens3DTarget()
        : m_pLens3D(NULL)
    {}

    CCLens3D* m_pLens3D;
};

void Effect4::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    CCLens3D* lens = CCLens3D::create(10, CCSizeMake(32,24), ccp(100,180), 150);
    CCActionInterval* move = CCJumpBy::create(5, ccp(380,0), 100, 4);
    CCActionInterval* move_back = move->reverse();
    CCActionInterval* seq = CCSequence::create( move, move_back, NULL);

    /* In cocos2d-iphone, the type of action's target is 'id', so it supports using the instance of 'CCLens3D' as its target.
        While in cocos2d-x, the target of action only supports CCNode or its subclass,
        so we make an encapsulation for CCLens3D to achieve that.
    */

    CCDirector* director = CCDirector::sharedDirector();
    CCNode* pTarget = Lens3DTarget::create(lens);
    // Please make sure the target been added to its parent.
    this->addChild(pTarget);

    director->getActionManager()->addAction(seq, pTarget, false);
    this->runAction( lens );
}

std::string Effect4::title()
{
    return "Jumpy Lens3D";
}

//------------------------------------------------------------------
//
// Effect5
//
//------------------------------------------------------------------
void Effect5::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    //CCDirector::sharedDirector()->setProjection(CCDirectorProjection2D);
    
    CCActionInterval* effect = CCLiquid::create(2, CCSizeMake(32,24), 1, 20);    

    CCActionInterval* stopEffect = CCSequence::create(
                                         effect,
                                         CCDelayTime::create(2),
                                         CCStopGrid::create(),
                    //                     [DelayTime::create:2],
                    //                     [[effect copy] autorelease],
                                         NULL);
    
    CCNode* bg = getChildByTag(kTagBackground);
    bg->runAction(stopEffect);
}

std::string Effect5::title()
{
    return "Test Stop-Copy-Restar";
}

void Effect5::onExit()
{
    EffectAdvanceTextLayer::onExit();

    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

//------------------------------------------------------------------
//
// Effect5
//
//------------------------------------------------------------------
void Issue631::onEnter()
{
    EffectAdvanceTextLayer::onEnter();
        
    CCActionInterval* effect = CCSequence::create( CCDelayTime::create(2.0f), CCShaky3D::create(5.0f, CCSizeMake(5, 5), 16, false), NULL);

    // cleanup
    CCNode* bg = getChildByTag(kTagBackground);
    removeChild(bg, true);

    // background
    CCLayerColor* layer = CCLayerColor::create( ccc4(255,0,0,255) );
    addChild(layer, -10);
    CCSprite* sprite = CCSprite::create("Images/grossini.png");
    sprite->setPosition( ccp(50,80) );
    layer->addChild(sprite, 10);
    
    // foreground
    CCLayerColor* layer2 = CCLayerColor::create(ccc4( 0, 255,0,255 ) );
    CCSprite* fog = CCSprite::create("Images/Fog.png");

    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
    fog->setBlendFunc(bf);
    layer2->addChild(fog, 1);
    addChild(layer2, 1);
    
    layer2->runAction( CCRepeatForever::create(effect) );
}

std::string Issue631::title()
{
    return "Testing Opacity";
}

std::string Issue631::subtitle()
{
    return "Effect image should be 100% opaque. Testing issue #631";
}

//------------------------------------------------------------------
//
// EffectAdvanceTextLayer
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER    6

CCLayer* nextEffectAdvanceAction();
CCLayer* backEffectAdvanceAction();
CCLayer* restartEffectAdvanceAction();

CCLayer* createEffectAdvanceLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new Effect3();
        case 1: return new Effect2();
        case 2: return new Effect1();
        case 3: return new Effect4();
        case 4: return new Effect5();
        case 5: return new Issue631();
    }  

    return NULL;
}

CCLayer* nextEffectAdvanceAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backEffectAdvanceAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartEffectAdvanceAction()
{
    CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


void EffectAdvanceTextLayer::onEnter(void)
{
    CCLayer::onEnter();
    
    CCSprite *bg = CCSprite::create("Images/background3.png");
    addChild(bg, 0, kTagBackground);
    bg->setPosition( VisibleRect::center() );
    
    CCSprite* grossini = CCSprite::create("Images/grossinis_sister2.png");
    bg->addChild(grossini, 1, kTagSprite1);
    grossini->setPosition( ccp(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3.0f, VisibleRect::bottom().y+ 200) );
    CCActionInterval* sc = CCScaleBy::create(2, 5);
    CCActionInterval* sc_back = sc->reverse();
    grossini->runAction( CCRepeatForever::create(CCSequence::create(sc, sc_back, NULL) ) );

    CCSprite* tamara = CCSprite::create("Images/grossinis_sister1.png");
    bg->addChild(tamara, 1, kTagSprite2);
    tamara->setPosition( ccp(VisibleRect::left().x+2*VisibleRect::getVisibleRect().size.width/3.0f,VisibleRect::bottom().y+200) );
    CCActionInterval* sc2 = CCScaleBy::create(2, 5);
    CCActionInterval* sc2_back = sc2->reverse();
    tamara->runAction( CCRepeatForever::create(CCSequence::create(sc2, sc2_back, NULL) ) );
    
    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Marker Felt", 28);
    
    label->setPosition( ccp(VisibleRect::center().x,VisibleRect::top().y-80) );
    addChild(label);
    label->setTag( kTagLabel );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 101);
        l->setPosition( ccp(VisibleRect::center().x,VisibleRect::top().y-80) );
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(EffectAdvanceTextLayer::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png","Images/r2.png", this, menu_selector(EffectAdvanceTextLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(EffectAdvanceTextLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    
}

EffectAdvanceTextLayer::~EffectAdvanceTextLayer(void)
{
}

std::string EffectAdvanceTextLayer::title()
{
    return "No title";
}

std::string EffectAdvanceTextLayer::subtitle()
{
    return "";
}

void EffectAdvanceTextLayer::restartCallback(CCObject* pSender)
{
    CCScene* s = new EffectAdvanceScene();
    s->addChild(restartEffectAdvanceAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void EffectAdvanceTextLayer::nextCallback(CCObject* pSender)
{
    CCScene* s = new EffectAdvanceScene();
    s->addChild( nextEffectAdvanceAction() );
    CCDirector::sharedDirector()->replaceScene(s);

    s->release();
}

void EffectAdvanceTextLayer::backCallback(CCObject* pSender)
{
    CCScene* s = new EffectAdvanceScene();
    s->addChild( backEffectAdvanceAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void EffectAdvanceScene::runThisTest()
{
    CCLayer* pLayer = nextEffectAdvanceAction();

    addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(this);
}
