#include "LayerTest.h"
#include "../testResource.h"

enum 
{
    kTagLayer = 1,
};

static std::function<Layer*()> createFunctions[] = {
    CL(LayerTestCascadingOpacityA),
    CL(LayerTestCascadingOpacityB),
    CL(LayerTestCascadingOpacityC),
    CL(LayerTestCascadingColorA),
    CL(LayerTestCascadingColorB),
    CL(LayerTestCascadingColorC),
    CL(LayerTest1),
    CL(LayerTest2),
    CL(LayerTestBlend),
    CL(LayerGradientTest),
    CL(LayerGradientTest2),
    CL(LayerGradientTest3),
    CL(LayerIgnoreAnchorPointPos),
    CL(LayerIgnoreAnchorPointRot),
    CL(LayerIgnoreAnchorPointScale),
    CL(LayerExtendedBlendOpacityTest),
    CL(LayerBug3162A),
    CL(LayerBug3162B),
    CL(LayerColorOccludeBug),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();    
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

//------------------------------------------------------------------
//
// LayerTest
//
//------------------------------------------------------------------

LayerTest::LayerTest(void)
{
}

LayerTest::~LayerTest(void)
{
}

std::string LayerTest::subtitle() const
{
    return "";
}

std::string LayerTest::title() const
{
    return "Layer Test";
}

void LayerTest::onEnter()
{
    BaseTest::onEnter();
}

void LayerTest::restartCallback(Ref* sender)
{
    auto s = new LayerTestScene();
    s->addChild(restartAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void LayerTest::nextCallback(Ref* sender)
{
    auto s = new LayerTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LayerTest::backCallback(Ref* sender)
{
    auto s = new LayerTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

// Cascading support extensions

static void setEnableRecursiveCascading(Node* node, bool enable)
{
    node->setCascadeColorEnabled(enable);
    node->setCascadeOpacityEnabled(enable);
    
    auto& children = node->getChildren();
    for(const auto &child : children) {
        setEnableRecursiveCascading(child, enable);
    }
}

// LayerTestCascadingOpacityA
void LayerTestCascadingOpacityA::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = Layer::create();
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, s.height/2));
    sister2->setPosition( Vec2( s.width*2/3, s.height/2));
    label->setPosition( Vec2( s.width/2, s.height/2));
    
    layer1->runAction(
        RepeatForever::create(
            Sequence::create(
                FadeTo::create(4, 0),
                FadeTo::create(4, 255),
                DelayTime::create(1),
                NULL)));

    sister1->runAction(
        RepeatForever::create(
            Sequence::create(
                FadeTo::create(2, 0),
                FadeTo::create(2, 255),
                FadeTo::create(2, 0),
                FadeTo::create(2, 255),
                DelayTime::create(1),
                NULL)));
    
    // Enable cascading in scene
    setEnableRecursiveCascading(this, true);
}

std::string LayerTestCascadingOpacityA::subtitle() const
{
    return "Layer: cascading opacity";
}


//  LayerTestCascadingOpacityB
void LayerTestCascadingOpacityB::onEnter()
{
    LayerTest::onEnter();
        
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(192, 0, 0, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    
    layer1->setPosition( Vec2(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, 0));
    sister2->setPosition( Vec2( s.width*2/3, 0));
    label->setPosition( Vec2( s.width/2, 0));
    
    layer1->runAction(
     RepeatForever::create(
      Sequence::create(
       FadeTo::create(4, 0),
       FadeTo::create(4, 255),
       DelayTime::create(1),
       NULL)));
    
    sister1->runAction(
     RepeatForever::create(
      Sequence::create(
       FadeTo::create(2, 0),
       FadeTo::create(2, 255),
       FadeTo::create(2, 0),
       FadeTo::create(2, 255),
       DelayTime::create(1),
       NULL)));
    
    // Enable cascading in scene
    setEnableRecursiveCascading(this, true);
}

std::string LayerTestCascadingOpacityB::subtitle() const
{
    return "CCLayerColor: cascading opacity";
}


// LayerTestCascadingOpacityC
void LayerTestCascadingOpacityC::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(192, 0, 0, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    layer1->setCascadeOpacityEnabled(false);
    
    layer1->setPosition( Vec2(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, 0));
    sister2->setPosition( Vec2( s.width*2/3, 0));
    label->setPosition( Vec2( s.width/2, 0));
    
    layer1->runAction(
     RepeatForever::create(
      Sequence::create(
       FadeTo::create(4, 0),
       FadeTo::create(4, 255),
       DelayTime::create(1),
       NULL)));
    
    sister1->runAction(
     RepeatForever::create(
      Sequence::create(
       FadeTo::create(2, 0),
       FadeTo::create(2, 255),
       FadeTo::create(2, 0),
       FadeTo::create(2, 255),
       DelayTime::create(1),
       NULL)));
}

std::string LayerTestCascadingOpacityC::subtitle() const
{
    return "CCLayerColor: non-cascading opacity";
}


//// Example LayerTestCascadingColor

// LayerTestCascadingColorA
void LayerTestCascadingColorA::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = Layer::create();
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, s.height/2));
    sister2->setPosition( Vec2( s.width*2/3, s.height/2));
    label->setPosition( Vec2( s.width/2, s.height/2));
    
    layer1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(6, 255, 0, 255),
       TintTo::create(6, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
    
    sister1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(2, 255, 255, 0),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 0, 255, 255),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 255, 0, 255),
       TintTo::create(2, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
    
    // Enable cascading in scene
    setEnableRecursiveCascading(this, true);
     
}

std::string LayerTestCascadingColorA::subtitle() const
{
    return "Layer: cascading color";
}


// LayerTestCascadingColorB
void LayerTestCascadingColorB::onEnter()
{
    LayerTest::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(255, 255, 255, 255), s.width, s.height/2);
    
    layer1->setPosition( Vec2(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, 0));
    sister2->setPosition( Vec2( s.width*2/3, 0));
    label->setPosition( Vec2( s.width/2, 0));
    
    layer1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(6, 255, 0, 255),
       TintTo::create(6, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
    
    sister1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(2, 255, 255, 0),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 0, 255, 255),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 255, 0, 255),
       TintTo::create(2, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
    
    // Enable cascading in scene
    setEnableRecursiveCascading(this, true);
}

std::string LayerTestCascadingColorB::subtitle() const
{
    return "CCLayerColor: cascading color";
}


// LayerTestCascadingColorC
void LayerTestCascadingColorC::onEnter()
{
    LayerTest::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(255, 255, 255, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    layer1->setPosition( Vec2(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, 0));
    sister2->setPosition( Vec2( s.width*2/3, 0));
    label->setPosition( Vec2( s.width/2, 0));
    
    layer1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(6, 255, 0, 255),
       TintTo::create(6, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
    
    sister1->runAction(
     RepeatForever::create(
      Sequence::create(
       TintTo::create(2, 255, 255, 0),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 0, 255, 255),
       TintTo::create(2, 255, 255, 255),
       TintTo::create(2, 255, 0, 255),
       TintTo::create(2, 255, 255, 255),
       DelayTime::create(1),
       NULL)));
}

std::string LayerTestCascadingColorC::subtitle() const
{
    return "CCLayerColor: non-cascading color";
}

//------------------------------------------------------------------
//
// LayerTest1
//
//------------------------------------------------------------------
void LayerTest1::onEnter()
{
    LayerTest::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(LayerTest1::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(LayerTest1::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(LayerTest1::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    auto layer = LayerColor::create( Color4B(0xFF, 0x00, 0x00, 0x80), 200, 200); 
    
    layer->ignoreAnchorPointForPosition(false);
    layer->setPosition( Vec2(s.width/2, s.height/2) );
    addChild(layer, 1, kTagLayer);
}

void LayerTest1::updateSize(Vec2 &touchLocation)
{    
    auto s = Director::getInstance()->getWinSize();
    
    auto newSize = Size( fabs(touchLocation.x - s.width/2)*2, fabs(touchLocation.y - s.height/2)*2);
    
    auto l = (LayerColor*) getChildByTag(kTagLayer);

    l->setContentSize( newSize );
}

void LayerTest1::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    onTouchesMoved(touches, event);
}

void LayerTest1::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touchLocation = touches[0]->getLocation();

    updateSize(touchLocation);
}

void LayerTest1::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    onTouchesMoved(touches, event);
}

std::string LayerTest1::subtitle() const
{
    return "ColorLayer resize (tap & move)";
}

//------------------------------------------------------------------
//
// LayerTest2
//
//------------------------------------------------------------------
void LayerTest2::onEnter()
{
    LayerTest::onEnter();

    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create( Color4B(255, 255, 0, 80), 100, 300);
    layer1->setPosition(Vec2(s.width/3, s.height/2));
    layer1->ignoreAnchorPointForPosition(false);
    addChild(layer1, 1);
    
    auto layer2 = LayerColor::create( Color4B(0, 0, 255, 255), 100, 300);
    layer2->setPosition(Vec2((s.width/3)*2, s.height/2));
    layer2->ignoreAnchorPointForPosition(false);
    addChild(layer2, 1);
    
    auto actionTint = TintBy::create(2, -255, -127, 0);
    auto actionTintBack = actionTint->reverse();
    auto seq1 = Sequence::create( actionTint, actionTintBack, NULL);
    layer1->runAction(seq1);

    auto actionFade = FadeOut::create(2.0f);
    auto actionFadeBack = actionFade->reverse();
    auto seq2 = Sequence::create(actionFade, actionFadeBack, NULL);        
    layer2->runAction(seq2);
}

std::string LayerTest2::subtitle() const
{
    return "ColorLayer: fade and tint";
}

//------------------------------------------------------------------
//
// LayerTestBlend
//
//------------------------------------------------------------------

LayerTestBlend::LayerTestBlend()
{
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create( Color4B(255, 255, 255, 80) );
    
    auto sister1 = Sprite::create(s_pathSister1);
    auto sister2 = Sprite::create(s_pathSister2);
    
    addChild(sister1);
    addChild(sister2);
    addChild(layer1, 100, kTagLayer);
    
    sister1->setPosition( Vec2( s.width*1/3, s.height/2) );
    sister2->setPosition( Vec2( s.width*2/3, s.height/2) );

    schedule( schedule_selector(LayerTestBlend::newBlend), 1.0f);
}

void LayerTestBlend::newBlend(float dt)
{
     auto layer = (LayerColor*)getChildByTag(kTagLayer);

    GLenum src;
    GLenum dst;

    if( layer->getBlendFunc().dst == GL_ZERO )
    {
        src = GL_SRC_ALPHA;
        dst = GL_ONE_MINUS_SRC_ALPHA;
    }
    else
    {
        src = GL_ONE_MINUS_DST_COLOR;
        dst = GL_ZERO;
    }

    BlendFunc bf = {src, dst};
    layer->setBlendFunc( bf );
}


std::string LayerTestBlend::subtitle() const
{
    return "ColorLayer: blend";
}

//------------------------------------------------------------------
//
// LayerGradientTest
//
//------------------------------------------------------------------
LayerGradientTest::LayerGradientTest()
{
    auto layer1 = LayerGradient::create(Color4B(255,0,0,255), Color4B(0,255,0,255), Vec2(0.9f, 0.9f));
    addChild(layer1, 0, kTagLayer);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(LayerGradientTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto label1 = Label::createWithTTF("Compressed Interpolation: Enabled", "fonts/Marker Felt.ttf", 26);
    auto label2 = Label::createWithTTF("Compressed Interpolation: Disabled", "fonts/Marker Felt.ttf", 26);
    auto item1 = MenuItemLabel::create(label1);
    auto item2 = MenuItemLabel::create(label2);
    auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(LayerGradientTest::toggleItem, this), item1, item2, NULL);

    auto menu = Menu::create(item, NULL);
    addChild(menu);
    auto s = Director::getInstance()->getWinSize();
    menu->setPosition(Vec2(s.width / 2, 100));
}

void LayerGradientTest::toggleItem(Ref *sender)
{
    auto gradient = static_cast<LayerGradient*>( getChildByTag(kTagLayer) );
    gradient->setCompressedInterpolation(! gradient->isCompressedInterpolation());
}

void LayerGradientTest::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    auto s = Director::getInstance()->getWinSize();

    auto touch = touches[0];
    auto start = touch->getLocation();    

    auto diff =  Vec2(s.width/2,s.height/2) - start;
    diff = diff.getNormalized();

    auto gradient = static_cast<LayerGradient*>( getChildByTag(1) );
    gradient->setVector(diff);
}

std::string LayerGradientTest::title() const
{
    return "LayerGradientTest";
}

std::string LayerGradientTest::subtitle() const
{
    return "Touch the screen and move your finger";
}

//------------------------------------------------------------------
//
// LayerGradientTest2
//
//------------------------------------------------------------------
LayerGradientTest2::LayerGradientTest2()
{
    auto layer = LayerGradient::create(Color4B(255,0,0,255), Color4B(255,255,0,255));
    addChild(layer);
}

std::string LayerGradientTest2::title() const
{
    return "LayerGradientTest 2";
}

std::string LayerGradientTest2::subtitle() const
{
    return "You should see a gradient";
}


//------------------------------------------------------------------
//
// LayerGradientTest3
//
//------------------------------------------------------------------
LayerGradientTest3::LayerGradientTest3()
{
    auto layer1 = LayerGradient::create(Color4B(255,0,0,255), Color4B(255,255,0,255));
    addChild(layer1);
}

std::string LayerGradientTest3::title() const
{
    return "LayerGradientTest 3";
}

std::string LayerGradientTest3::subtitle() const
{
    return "You should see a gradient";
}

// LayerIgnoreAnchorPointPos

#define kLayerIgnoreAnchorPoint  1000

void LayerIgnoreAnchorPointPos::onEnter()
{
    LayerTest::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto l = LayerColor::create(Color4B(255, 0, 0, 255), 150, 150);

    l->setAnchorPoint(Vec2(0.5f, 0.5f));
    l->setPosition(Vec2( s.width/2, s.height/2));

    auto move = MoveBy::create(2, Vec2(100,2));
    auto back = (MoveBy *)move->reverse();
    auto seq = Sequence::create(move, back, NULL);
    l->runAction(RepeatForever::create(seq));
    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Vec2(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toggle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointPos::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Vec2(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointPos::onToggle(Ref* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointPos::title() const
{
    return "IgnoreAnchorPoint - Position";
}

std::string LayerIgnoreAnchorPointPos::subtitle() const
{
    return "Ignoring Anchor Vec2 for position";
}

// LayerIgnoreAnchorPointRot

void LayerIgnoreAnchorPointRot::onEnter()
{
    LayerTest::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto l = LayerColor::create(Color4B(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(Vec2(0.5f, 0.5f));
    l->setPosition(Vec2( s.width/2, s.height/2));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto rot = RotateBy::create(2, 360);
    l->runAction(RepeatForever::create(rot));


    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Vec2(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointRot::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Vec2(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointRot::onToggle(Ref* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointRot::title() const
{
    return "IgnoreAnchorPoint - Rotation";
}

std::string LayerIgnoreAnchorPointRot::subtitle() const
{
    return "Ignoring Anchor Vec2 for rotations";
}

// LayerIgnoreAnchorPointScale
void LayerIgnoreAnchorPointScale::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();

    auto l = LayerColor::create(Color4B(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(Vec2(0.5f, 1.0f));
    l->setPosition(Vec2( s.width/2, s.height/2));


    auto scale = ScaleBy::create(2, 2);
    auto back = (ScaleBy*)scale->reverse();
    auto seq = Sequence::create(scale, back, NULL);

    l->runAction(RepeatForever::create(seq));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Vec2(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointScale::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Vec2(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointScale::onToggle(Ref* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointScale::title() const
{
    return "IgnoreAnchorPoint - Scale";
}

std::string LayerIgnoreAnchorPointScale::subtitle() const
{
    return "Ignoring Anchor Vec2 for scale";
}

void LayerTestScene::runThisTest()
{
    sceneIdx = -1;
    auto layer = nextAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

LayerExtendedBlendOpacityTest::LayerExtendedBlendOpacityTest()
{
    auto layer1 = LayerGradient::create(Color4B(255, 0, 0, 255), Color4B(255, 0, 255, 255));
    layer1->setContentSize(Size(80, 80));
    layer1->setPosition(Vec2(50,50));
    addChild(layer1);
    
    auto layer2 = LayerGradient::create(Color4B(0, 0, 0, 127), Color4B(255, 255, 255, 127));
    layer2->setContentSize(Size(80, 80));
    layer2->setPosition(Vec2(100,90));
    addChild(layer2);
    
    auto layer3 = LayerGradient::create();
    layer3->setContentSize(Size(80, 80));
    layer3->setPosition(Vec2(150,140));
    layer3->setStartColor(Color3B(255, 0, 0));
    layer3->setEndColor(Color3B(255, 0, 255));
    layer3->setStartOpacity(255);
    layer3->setEndOpacity(255);
    layer3->setBlendFunc( BlendFunc::ALPHA_NON_PREMULTIPLIED );
    addChild(layer3);
}

std::string LayerExtendedBlendOpacityTest::title() const
{
    return "Extended Blend & Opacity";
}

std::string LayerExtendedBlendOpacityTest::subtitle() const
{
    return "You should see 3 layers";
}

// LayerBug3162A
void LayerBug3162A::onEnter()
{
    LayerTest::onEnter();
    
    Size size = VisibleRect::getVisibleRect().size;
    size.width = size.width / 2;
    size.height = size.height / 3;
    Color4B color[3] = {Color4B(255, 0, 0, 255), Color4B(0, 255, 0, 255), Color4B(0, 0, 255, 255)};
    
    for (int i = 0; i < 3; ++i)
    {
        _layer[i] = LayerColor::create(color[i]);
        _layer[i]->setContentSize(size);
        _layer[i]->setPosition(Vec2(size.width/2, size.height/2) - Vec2(20, 20));
        _layer[i]->setOpacity(150);
        _layer[i]->setCascadeOpacityEnabled(true);
        if (i > 0)
        {
            _layer[i-1]->addChild(_layer[i]);
        }
    }
    
    this->addChild(_layer[0]);
    
    schedule(schedule_selector(LayerBug3162A::step), 0.5, kRepeatForever, 0);
}

void LayerBug3162A::step(float dt)
{
    _layer[0]->setCascadeOpacityEnabled(!_layer[0]->isCascadeOpacityEnabled());
}

std::string LayerBug3162A::title() const
{
    return "Bug 3162 red layer cascade opacity eable/disable";
}

std::string LayerBug3162A::subtitle() const
{
    return "g and b layer opacity is effected/diseffected with r layer";
}

// LayerBug3162B
void LayerBug3162B::onEnter()
{
    LayerTest::onEnter();
    
    Size size = VisibleRect::getVisibleRect().size;
    size.width = size.width / 2;
    size.height = size.height / 3;
    Color4B color[3] = {Color4B(200, 0, 0, 255), Color4B(150, 0, 0, 255), Color4B(100, 0, 0, 255)};
    
    for (int i = 0; i < 3; ++i)
    {
        _layer[i] = LayerColor::create(color[i]);
        _layer[i]->setContentSize(size);
        _layer[i]->setPosition(Vec2(size.width/2, size.height/2) - Vec2(20, 20));
        //_layer[i]->setOpacity(150);
        if (i > 0)
        {
            _layer[i-1]->addChild(_layer[i]);
        }
    }
    
    this->addChild(_layer[0]);
    
    _layer[0]->setCascadeColorEnabled(true);
    _layer[1]->setCascadeColorEnabled(true);
    _layer[2]->setCascadeColorEnabled(true);
    
    schedule(schedule_selector(LayerBug3162B::step), 0.5, kRepeatForever, 0);
}

void LayerBug3162B::step(float dt)
{
    _layer[0]->setCascadeColorEnabled(!_layer[0]->isCascadeColorEnabled());
}

std::string LayerBug3162B::title() const
{
    return "Bug 3162 bottom layer cascade color eable/disable";
}

std::string LayerBug3162B::subtitle() const
{
    return "u and m layer color is effected/diseffected with b layer";
}

std::string LayerColorOccludeBug::title() const
{
    return "Layer Color Occlude Bug Test";
}

std::string LayerColorOccludeBug::subtitle() const
{
    return  "Layer Color Should not occlude titles and any sprites";
}

void LayerColorOccludeBug::onEnter()
{
    LayerTest::onEnter();
    Director::getInstance()->setDepthTest(true);
    _layer = LayerColor::create(Color4B(0, 80, 95, 255));
    addChild(_layer);
}

void LayerColorOccludeBug::onExit()
{
    LayerTest::onExit();
    Director::getInstance()->setDepthTest(false);
}
