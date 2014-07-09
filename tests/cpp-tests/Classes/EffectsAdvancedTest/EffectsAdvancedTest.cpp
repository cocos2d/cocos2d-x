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

    //auto target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     Lens3D is Grid3D and it's size is (15,10)
    //     Waves3D is Grid3D and it's size is (15,10)
    
    auto size = Director::getInstance()->getWinSize();
    auto lens = Lens3D::create(0.0f, Size(15,10), Vec2(size.width/2,size.height/2), 240);
    auto waves = Waves3D::create(10, Size(15,10), 18, 15);

    auto reuse = ReuseGrid::create(1);
    auto delay = DelayTime::create(8);

//    auto orbit = OrbitCamera::create(5, 1, 2, 0, 180, 0, -90);
//    auto orbit_back = orbit->reverse();

    //_bgNode->runAction( RepeatForever::create( Sequence::create( orbit, orbit_back, nullptr)  ) );
    _bgNode->runAction( Sequence::create(lens, delay, reuse, waves, nullptr) );
}

std::string Effect1::title() const
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

    //auto target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     ShakyTiles is TiledGrid3D and it's size is (15,10)
    //     Shuffletiles is TiledGrid3D and it's size is (15,10)
    //       TurnOfftiles is TiledGrid3D and it's size is (15,10)
    auto shaky = ShakyTiles3D::create(5, Size(15,10), 4, false);
    auto shuffle = ShuffleTiles::create(0, Size(15,10), 3);
    auto turnoff = TurnOffTiles::create(0, Size(15,10), 3);
    auto turnon = turnoff->reverse();
    
    // reuse 2 times:
    //   1 for shuffle
    //   2 for turn off
    //   turnon tiles will use a new grid
    auto reuse = ReuseGrid::create(2);

    auto delay = DelayTime::create(1);
    
//    id orbit = [OrbitCamera::create:5 radius:1 deltaRadius:2 angleZ:0 deltaAngleZ:180 angleX:0 deltaAngleX:-90];
//    id orbit_back = [orbit reverse];
//
//    [target runAction: [RepeatForever::create: [Sequence actions: orbit, orbit_back, nil]]];    
    _bgNode->runAction(Sequence::create( shaky, delay, reuse, shuffle, delay->clone(), turnoff, turnon, nullptr) );
}

std::string Effect2::title() const
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
    //auto bg = getChildByTag(kTagBackground);
    //auto target1 = bg->getChildByTag(kTagSprite1);
    //auto target2 = bg->getChildByTag(kTagSprite2);    
    auto waves = Waves::create(5, Size(15,10), 5, 20, true, false);
    auto shaky = Shaky3D::create(5, Size(15,10), 4, false);
    
    _target1->runAction( RepeatForever::create( waves ) );
    _target2->runAction( RepeatForever::create( shaky ) );
    
    // moving background. Testing issue #244
    auto move = MoveBy::create(3, Vec2(200,0) );
    _bgNode->runAction(RepeatForever::create( Sequence::create(move, move->reverse(), nullptr) ));    
}

std::string Effect3::title() const
{
    return "Effects on 2 sprites";
}


//------------------------------------------------------------------
//
// Effect4
//
//------------------------------------------------------------------

class Lens3DTarget : public Node
{
public:
    virtual void setPosition(const Vec2& var)
    {
        _lens3D->setPosition(var);
    }
    
    virtual const Vec2& getPosition() const
    {
        return _lens3D->getPosition();
    }
    
    static Lens3DTarget* create(Lens3D* pAction)
    {
        Lens3DTarget* pRet = new Lens3DTarget();
        pRet->_lens3D = pAction;
        pRet->autorelease();
        return pRet;
    }
private:

    Lens3DTarget()
        : _lens3D(nullptr)
    {}

    Lens3D* _lens3D;
};

void Effect4::onEnter()
{
    EffectAdvanceTextLayer::onEnter();
    //Node* gridNode = NodeGrid::create();
    
    auto lens = Lens3D::create(10, Size(32,24), Vec2(100,180), 150);
    auto move = JumpBy::create(5, Vec2(380,0), 100, 4);
    auto move_back = move->reverse();
    auto seq = Sequence::create( move, move_back, nullptr);

    /* In cocos2d-iphone, the type of action's target is 'id', so it supports using the instance of 'Lens3D' as its target.
        While in cocos2d-x, the target of action only supports Node or its subclass,
        so we make an encapsulation for Lens3D to achieve that.
    */

    auto director = Director::getInstance();
    auto pTarget = Lens3DTarget::create(lens);
    // Please make sure the target been added to its parent.
    this->addChild(pTarget);
    //gridNode->addChild(pTarget);

    director->getActionManager()->addAction(seq, pTarget, false);
    
    _bgNode->runAction( lens );
}

std::string Effect4::title() const
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

    //CCDirector::getInstance()->setProjection(DirectorProjection2D);
    
    auto effect = Liquid::create(2, Size(32,24), 1, 20);    

    auto stopEffect = Sequence::create(
                                         effect,
                                         DelayTime::create(2),
                                         StopGrid::create(),
                    //                     [DelayTime::create:2],
                    //                     [[effect copy] autorelease],
                                         nullptr);
    
    //auto bg = getChildByTag(kTagBackground);
    _bgNode->runAction(stopEffect);
}

std::string Effect5::title() const
{
    return "Test Stop-Copy-Restar";
}

void Effect5::onExit()
{
    EffectAdvanceTextLayer::onExit();

    Director::getInstance()->setProjection(Director::Projection::_3D);
}

//------------------------------------------------------------------
//
// Effect5
//
//------------------------------------------------------------------
void Issue631::onEnter()
{
    EffectAdvanceTextLayer::onEnter();
        
    auto effect = Sequence::create( DelayTime::create(2.0f), Shaky3D::create(5.0f, Size(5, 5), 16, false), nullptr);

    // cleanup
    //auto bg = getChildByTag(kTagBackground);
    removeChild(_bgNode, true);

    // background
    auto layer = LayerColor::create( Color4B(255,0,0,255) );
    addChild(layer, -10);
    auto sprite = Sprite::create("Images/grossini.png");
    sprite->setPosition( Vec2(50,80) );
    layer->addChild(sprite, 10);
    
    // foreground
    auto layer2BaseGrid = NodeGrid::create();
    auto layer2 = LayerColor::create(Color4B( 0, 255,0,255 ) );
    auto fog = Sprite::create("Images/Fog.png");

    BlendFunc bf = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
    fog->setBlendFunc(bf);
    layer2->addChild(fog, 1);
    addChild(layer2BaseGrid, 1);
    layer2BaseGrid->addChild(layer2);
    
    layer2BaseGrid->runAction( RepeatForever::create(effect) );
}

std::string Issue631::title() const
{
    return "Testing Opacity";
}

std::string Issue631::subtitle() const
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

Layer* nextEffectAdvanceAction();
Layer* backEffectAdvanceAction();
Layer* restartEffectAdvanceAction();

Layer* createEffectAdvanceLayer(int nIndex)
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

    return nullptr;
}

Layer* nextEffectAdvanceAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backEffectAdvanceAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartEffectAdvanceAction()
{
    auto layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 


void EffectAdvanceTextLayer::onEnter(void)
{
    BaseTest::onEnter();
    
    _bgNode = NodeGrid::create();
    _bgNode->setAnchorPoint(Vec2(0.5,0.5));
    addChild(_bgNode);
    //_bgNode->setPosition( VisibleRect::center() );
    auto bg = Sprite::create("Images/background3.png");
    bg->setPosition( VisibleRect::center() );
    //addChild(bg, 0, kTagBackground);
    //bg->setPosition( VisibleRect::center() );
    _bgNode->addChild(bg);

    _target1 = NodeGrid::create();
    _target1->setAnchorPoint(Vec2(0.5,0.5));
    auto grossini = Sprite::create("Images/grossinis_sister2.png");
    _target1->addChild(grossini);
    _bgNode->addChild(_target1);
    _target1->setPosition( Vec2(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3.0f, VisibleRect::bottom().y+ 200) );
    auto sc = ScaleBy::create(2, 5);
    auto sc_back = sc->reverse();
    _target1->runAction( RepeatForever::create(Sequence::create(sc, sc_back, nullptr) ) );


    _target2 = NodeGrid::create();
    _target2->setAnchorPoint(Vec2(0.5,0.5));
    auto tamara = Sprite::create("Images/grossinis_sister1.png");
    _target2->addChild(tamara);
    _bgNode->addChild(_target2);
    _target2->setPosition( Vec2(VisibleRect::left().x+2*VisibleRect::getVisibleRect().size.width/3.0f,VisibleRect::bottom().y+200) );
    auto sc2 = ScaleBy::create(2, 5);
    auto sc2_back = sc2->reverse();
    _target2->runAction( RepeatForever::create(Sequence::create(sc2, sc2_back, nullptr) ) );    

}

EffectAdvanceTextLayer::~EffectAdvanceTextLayer(void)
{
}

std::string EffectAdvanceTextLayer::title() const
{
    return "No title";
}

std::string EffectAdvanceTextLayer::subtitle() const
{
    return "";
}

void EffectAdvanceTextLayer::restartCallback(Ref* sender)
{
    auto s = new EffectAdvanceScene();
    s->addChild(restartEffectAdvanceAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void EffectAdvanceTextLayer::nextCallback(Ref* sender)
{
    auto s = new EffectAdvanceScene();
    s->addChild( nextEffectAdvanceAction() );
    Director::getInstance()->replaceScene(s);

    s->release();
}

void EffectAdvanceTextLayer::backCallback(Ref* sender)
{
    auto s = new EffectAdvanceScene();
    s->addChild( backEffectAdvanceAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void EffectAdvanceScene::runThisTest()
{
    auto layer = nextEffectAdvanceAction();

    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
