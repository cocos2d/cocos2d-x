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

    Node* target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     Lens3D is Grid3D and it's size is (15,10)
    //     Waves3D is Grid3D and it's size is (15,10)
    
    Size size = Director::getInstance()->getWinSize();
    ActionInterval* lens = Lens3D::create(0.0f, Size(15,10), Point(size.width/2,size.height/2), 240);
    ActionInterval* waves = Waves3D::create(10, Size(15,10), 18, 15);

    FiniteTimeAction* reuse = ReuseGrid::create(1);
    ActionInterval* delay = DelayTime::create(8);

    ActionInterval* orbit = OrbitCamera::create(5, 1, 2, 0, 180, 0, -90);
    ActionInterval* orbit_back = orbit->reverse();

    target->runAction( RepeatForever::create( Sequence::create( orbit, orbit_back, NULL)  ) );
    target->runAction( Sequence::create(lens, delay, reuse, waves, NULL) );
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

    Node* target = getChildByTag(kTagBackground);
    
    // To reuse a grid the grid size and the grid type must be the same.
    // in this case:
    //     ShakyTiles is TiledGrid3D and it's size is (15,10)
    //     Shuffletiles is TiledGrid3D and it's size is (15,10)
    //       TurnOfftiles is TiledGrid3D and it's size is (15,10)
    ActionInterval* shaky = ShakyTiles3D::create(5, Size(15,10), 4, false);
    ActionInterval* shuffle = ShuffleTiles::create(0, Size(15,10), 3);
    ActionInterval* turnoff = TurnOffTiles::create(0, Size(15,10), 3);
    ActionInterval* turnon = turnoff->reverse();
    
    // reuse 2 times:
    //   1 for shuffle
    //   2 for turn off
    //   turnon tiles will use a new grid
    FiniteTimeAction* reuse = ReuseGrid::create(2);

    ActionInterval* delay = DelayTime::create(1);
    
//    id orbit = [OrbitCamera::create:5 radius:1 deltaRadius:2 angleZ:0 deltaAngleZ:180 angleX:0 deltaAngleX:-90];
//    id orbit_back = [orbit reverse];
//
//    [target runAction: [RepeatForever::create: [Sequence actions: orbit, orbit_back, nil]]];
    target->runAction(Sequence::create( shaky, delay, reuse, shuffle, delay->clone(), turnoff, turnon, NULL) );
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

    Node* bg = getChildByTag(kTagBackground);
    Node* target1 = bg->getChildByTag(kTagSprite1);
    Node* target2 = bg->getChildByTag(kTagSprite2);    
    
    ActionInterval* waves = Waves::create(5, Size(15,10), 5, 20, true, false);
    ActionInterval* shaky = Shaky3D::create(5, Size(15,10), 4, false);
    
    target1->runAction( RepeatForever::create( waves ) );
    target2->runAction( RepeatForever::create( shaky ) );
    
    // moving background. Testing issue #244
    ActionInterval* move = MoveBy::create(3, Point(200,0) );
    bg->runAction(RepeatForever::create( Sequence::create(move, move->reverse(), NULL) ));    
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

class Lens3DTarget : public Node
{
public:
    virtual void setPosition(const Point& var)
    {
        _lens3D->setPosition(var);
    }
    
    virtual const Point& getPosition() const
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
        : _lens3D(NULL)
    {}

    Lens3D* _lens3D;
};

void Effect4::onEnter()
{
    EffectAdvanceTextLayer::onEnter();

    Lens3D* lens = Lens3D::create(10, Size(32,24), Point(100,180), 150);
    ActionInterval* move = JumpBy::create(5, Point(380,0), 100, 4);
    ActionInterval* move_back = move->reverse();
    ActionInterval* seq = Sequence::create( move, move_back, NULL);

    /* In cocos2d-iphone, the type of action's target is 'id', so it supports using the instance of 'Lens3D' as its target.
        While in cocos2d-x, the target of action only supports Node or its subclass,
        so we make an encapsulation for Lens3D to achieve that.
    */

    Director* director = Director::getInstance();
    Node* pTarget = Lens3DTarget::create(lens);
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

    //CCDirector::getInstance()->setProjection(DirectorProjection2D);
    
    ActionInterval* effect = Liquid::create(2, Size(32,24), 1, 20);    

    ActionInterval* stopEffect = Sequence::create(
                                         effect,
                                         DelayTime::create(2),
                                         StopGrid::create(),
                    //                     [DelayTime::create:2],
                    //                     [[effect copy] autorelease],
                                         NULL);
    
    Node* bg = getChildByTag(kTagBackground);
    bg->runAction(stopEffect);
}

std::string Effect5::title()
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
        
    ActionInterval* effect = Sequence::create( DelayTime::create(2.0f), Shaky3D::create(5.0f, Size(5, 5), 16, false), NULL);

    // cleanup
    Node* bg = getChildByTag(kTagBackground);
    removeChild(bg, true);

    // background
    LayerColor* layer = LayerColor::create( Color4B(255,0,0,255) );
    addChild(layer, -10);
    Sprite* sprite = Sprite::create("Images/grossini.png");
    sprite->setPosition( Point(50,80) );
    layer->addChild(sprite, 10);
    
    // foreground
    LayerColor* layer2 = LayerColor::create(Color4B( 0, 255,0,255 ) );
    Sprite* fog = Sprite::create("Images/Fog.png");

    BlendFunc bf = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
    fog->setBlendFunc(bf);
    layer2->addChild(fog, 1);
    addChild(layer2, 1);
    
    layer2->runAction( RepeatForever::create(effect) );
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

    return NULL;
}

Layer* nextEffectAdvanceAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backEffectAdvanceAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartEffectAdvanceAction()
{
    Layer* layer = createEffectAdvanceLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 


void EffectAdvanceTextLayer::onEnter(void)
{
    BaseTest::onEnter();
    
    Sprite *bg = Sprite::create("Images/background3.png");
    addChild(bg, 0, kTagBackground);
    bg->setPosition( VisibleRect::center() );
    
    Sprite* grossini = Sprite::create("Images/grossinis_sister2.png");
    bg->addChild(grossini, 1, kTagSprite1);
    grossini->setPosition( Point(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3.0f, VisibleRect::bottom().y+ 200) );
    ActionInterval* sc = ScaleBy::create(2, 5);
    ActionInterval* sc_back = sc->reverse();
    grossini->runAction( RepeatForever::create(Sequence::create(sc, sc_back, NULL) ) );

    Sprite* tamara = Sprite::create("Images/grossinis_sister1.png");
    bg->addChild(tamara, 1, kTagSprite2);
    tamara->setPosition( Point(VisibleRect::left().x+2*VisibleRect::getVisibleRect().size.width/3.0f,VisibleRect::bottom().y+200) );
    ActionInterval* sc2 = ScaleBy::create(2, 5);
    ActionInterval* sc2_back = sc2->reverse();
    tamara->runAction( RepeatForever::create(Sequence::create(sc2, sc2_back, NULL) ) );    
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

void EffectAdvanceTextLayer::restartCallback(Object* sender)
{
    Scene* s = new EffectAdvanceScene();
    s->addChild(restartEffectAdvanceAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void EffectAdvanceTextLayer::nextCallback(Object* sender)
{
    Scene* s = new EffectAdvanceScene();
    s->addChild( nextEffectAdvanceAction() );
    Director::getInstance()->replaceScene(s);

    s->release();
}

void EffectAdvanceTextLayer::backCallback(Object* sender)
{
    Scene* s = new EffectAdvanceScene();
    s->addChild( backEffectAdvanceAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void EffectAdvanceScene::runThisTest()
{
    Layer* layer = nextEffectAdvanceAction();

    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
