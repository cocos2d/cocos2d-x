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
    CL(LayerExtendedBlendOpacityTest)
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

string LayerTest::subtitle()
{
    return "";
}

std::string LayerTest::title()
{
    return "No title";
}

void LayerTest::onEnter()
{
    BaseTest::onEnter();
}

void LayerTest::restartCallback(Object* sender)
{
    auto s = new LayerTestScene();
    s->addChild(restartAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void LayerTest::nextCallback(Object* sender)
{
    auto s = new LayerTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LayerTest::backCallback(Object* sender)
{
    auto s = new LayerTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

//#pragma mark - Cascading support extensions

static void setEnableRecursiveCascading(Node* node, bool enable)
{
    auto rgba = dynamic_cast<RGBAProtocol*>(node);
    if (rgba)
    {
        rgba->setCascadeColorEnabled(enable);
        rgba->setCascadeOpacityEnabled(enable);
    }
    
    auto& children = node->getChildren();
    std::for_each(children.begin(), children.end(), [enable](Node* child){
        setEnableRecursiveCascading(child, enable);
    });
}

// LayerTestCascadingOpacityA
void LayerTestCascadingOpacityA::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerRGBA::create();
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, s.height/2));
    sister2->setPosition( Point( s.width*2/3, s.height/2));
    label->setPosition( Point( s.width/2, s.height/2));
    
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

std::string LayerTestCascadingOpacityA::title()
{
    return "LayerRGBA: cascading opacity";
}


//  LayerTestCascadingOpacityB
void LayerTestCascadingOpacityB::onEnter()
{
    LayerTest::onEnter();
        
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(192, 0, 0, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    
    layer1->setPosition( Point(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, 0));
    sister2->setPosition( Point( s.width*2/3, 0));
    label->setPosition( Point( s.width/2, 0));
    
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

std::string LayerTestCascadingOpacityB::title()
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
    
    layer1->setPosition( Point(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, 0));
    sister2->setPosition( Point( s.width*2/3, 0));
    label->setPosition( Point( s.width/2, 0));
    
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

std::string LayerTestCascadingOpacityC::title()
{
    return "CCLayerColor: non-cascading opacity";
}


//#pragma mark Example LayerTestCascadingColor

// LayerTestCascadingColorA
void LayerTestCascadingColorA::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerRGBA::create();
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, s.height/2));
    sister2->setPosition( Point( s.width*2/3, s.height/2));
    label->setPosition( Point( s.width/2, s.height/2));
    
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

std::string LayerTestCascadingColorA::title()
{
    return "LayerRGBA: cascading color";
}


// LayerTestCascadingColorB
void LayerTestCascadingColorB::onEnter()
{
    LayerTest::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto layer1 = LayerColor::create(Color4B(255, 255, 255, 255), s.width, s.height/2);
    
    layer1->setPosition( Point(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, 0));
    sister2->setPosition( Point( s.width*2/3, 0));
    label->setPosition( Point( s.width/2, 0));
    
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

std::string LayerTestCascadingColorB::title()
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
    layer1->setPosition( Point(0, s.height/2));
    
    auto sister1 = Sprite::create("Images/grossinis_sister1.png");
    auto sister2 = Sprite::create("Images/grossinis_sister2.png");
    auto label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( Point( s.width*1/3, 0));
    sister2->setPosition( Point( s.width*2/3, 0));
    label->setPosition( Point( s.width/2, 0));
    
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

std::string LayerTestCascadingColorC::title()
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
    layer->setPosition( Point(s.width/2, s.height/2) );
    addChild(layer, 1, kTagLayer);
}

void LayerTest1::updateSize(Point &touchLocation)
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

std::string LayerTest1::title()
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
    layer1->setPosition(Point(s.width/3, s.height/2));
    layer1->ignoreAnchorPointForPosition(false);
    addChild(layer1, 1);
    
    auto layer2 = LayerColor::create( Color4B(0, 0, 255, 255), 100, 300);
    layer2->setPosition(Point((s.width/3)*2, s.height/2));
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

std::string LayerTest2::title()
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
    
    sister1->setPosition( Point( s.width*1/3, s.height/2) );
    sister2->setPosition( Point( s.width*2/3, s.height/2) );

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


std::string LayerTestBlend::title()
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
    auto layer1 = LayerGradient::create(Color4B(255,0,0,255), Color4B(0,255,0,255), Point(0.9f, 0.9f));
    addChild(layer1, 0, kTagLayer);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(LayerGradientTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto label1 = LabelTTF::create("Compressed Interpolation: Enabled", "Marker Felt", 26);
    auto label2 = LabelTTF::create("Compressed Interpolation: Disabled", "Marker Felt", 26);
    auto item1 = MenuItemLabel::create(label1);
    auto item2 = MenuItemLabel::create(label2);
    auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(LayerGradientTest::toggleItem, this), item1, item2, NULL);

    auto menu = Menu::create(item, NULL);
    addChild(menu);
    auto s = Director::getInstance()->getWinSize();
    menu->setPosition(Point(s.width / 2, 100));
}

void LayerGradientTest::toggleItem(Object *sender)
{
    auto gradient = static_cast<LayerGradient*>( getChildByTag(kTagLayer) );
    gradient->setCompressedInterpolation(! gradient->isCompressedInterpolation());
}

void LayerGradientTest::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    auto s = Director::getInstance()->getWinSize();

    auto touch = touches[0];
    auto start = touch->getLocation();    

    auto diff =  Point(s.width/2,s.height/2) - start;
    diff = diff.normalize();

    auto gradient = static_cast<LayerGradient*>( getChildByTag(1) );
    gradient->setVector(diff);
}

std::string LayerGradientTest::title()
{
    return "LayerGradientTest";
}

string LayerGradientTest::subtitle()
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
    auto layer = new LayerGradient;
    layer->initWithColor(Color4B(255,0,0,255), Color4B(255,255,0,255));
    layer->autorelease();
    addChild(layer);
}

std::string LayerGradientTest2::title()
{
    return "LayerGradientTest 2";
}

string LayerGradientTest2::subtitle()
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

std::string LayerGradientTest3::title()
{
    return "LayerGradientTest 3";
}

string LayerGradientTest3::subtitle()
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

    l->setAnchorPoint(Point(0.5f, 0.5f));
    l->setPosition(Point( s.width/2, s.height/2));

    auto move = MoveBy::create(2, Point(100,2));
    auto back = (MoveBy *)move->reverse();
    auto seq = Sequence::create(move, back, NULL);
    l->runAction(RepeatForever::create(seq));
    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Point(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toggle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointPos::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Point(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointPos::onToggle(Object* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointPos::title()
{
    return "IgnoreAnchorPoint - Position";
}

std::string LayerIgnoreAnchorPointPos::subtitle()
{
    return "Ignoring Anchor Point for position";
}

// LayerIgnoreAnchorPointRot

void LayerIgnoreAnchorPointRot::onEnter()
{
    LayerTest::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto l = LayerColor::create(Color4B(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(Point(0.5f, 0.5f));
    l->setPosition(Point( s.width/2, s.height/2));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto rot = RotateBy::create(2, 360);
    l->runAction(RepeatForever::create(rot));


    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Point(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointRot::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Point(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointRot::onToggle(Object* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointRot::title()
{
    return "IgnoreAnchorPoint - Rotation";
}

std::string LayerIgnoreAnchorPointRot::subtitle()
{
    return "Ignoring Anchor Point for rotations";
}

// LayerIgnoreAnchorPointScale
void LayerIgnoreAnchorPointScale::onEnter()
{
    LayerTest::onEnter();
    
    auto s = Director::getInstance()->getWinSize();

    auto l = LayerColor::create(Color4B(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(Point(0.5f, 1.0f));
    l->setPosition(Point( s.width/2, s.height/2));


    auto scale = ScaleBy::create(2, 2);
    auto back = (ScaleBy*)scale->reverse();
    auto seq = Sequence::create(scale, back, NULL);

    l->runAction(RepeatForever::create(seq));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    auto child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    auto lsize = l->getContentSize();
    child->setPosition(Point(lsize.width/2, lsize.height/2));

    auto item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointScale::onToggle, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(Point(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointScale::onToggle(Object* pObject)
{
    auto layer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = layer->isIgnoreAnchorPointForPosition();
    layer->ignoreAnchorPointForPosition(! ignore);
}

std::string LayerIgnoreAnchorPointScale::title()
{
    return "IgnoreAnchorPoint - Scale";
}

std::string LayerIgnoreAnchorPointScale::subtitle()
{
    return "Ignoring Anchor Point for scale";
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
    layer1->setPosition(Point(50,50));
    addChild(layer1);
    
    auto layer2 = LayerGradient::create(Color4B(0, 0, 0, 127), Color4B(255, 255, 255, 127));
    layer2->setContentSize(Size(80, 80));
    layer2->setPosition(Point(100,90));
    addChild(layer2);
    
    auto layer3 = LayerGradient::create();
    layer3->setContentSize(Size(80, 80));
    layer3->setPosition(Point(150,140));
    layer3->setStartColor(Color3B(255, 0, 0));
    layer3->setEndColor(Color3B(255, 0, 255));
    layer3->setStartOpacity(255);
    layer3->setEndOpacity(255);
    layer3->setBlendFunc( BlendFunc::ALPHA_NON_PREMULTIPLIED );
    addChild(layer3);
}

string LayerExtendedBlendOpacityTest::title()
{
    return "Extended Blend & Opacity";
}

string LayerExtendedBlendOpacityTest::subtitle()
{
    return "You should see 3 layers";
}

