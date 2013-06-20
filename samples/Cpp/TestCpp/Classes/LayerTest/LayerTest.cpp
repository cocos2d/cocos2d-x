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
    CL(LayerGradient),
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
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
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

void LayerTest::restartCallback(Object* pSender)
{
    Scene* s = new LayerTestScene();
    s->addChild(restartAction());

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::nextCallback(Object* pSender)
{
    Scene* s = new LayerTestScene();
    s->addChild( nextAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::backCallback(Object* pSender)
{
    Scene* s = new LayerTestScene();
    s->addChild( backAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
} 

//#pragma mark - Cascading support extensions

static void setEnableRecursiveCascading(Node* node, bool enable)
{
    RGBAProtocol* rgba = dynamic_cast<RGBAProtocol*>(node);
    if (rgba)
    {
        rgba->setCascadeColorEnabled(enable);
        rgba->setCascadeOpacityEnabled(enable);
    }
    
    Object* obj;
    Array* children = node->getChildren();
    CCARRAY_FOREACH(children, obj)
    {
        Node* child = (Node*)obj;
        setEnableRecursiveCascading(child, enable);
    }
}

// LayerTestCascadingOpacityA
void LayerTestCascadingOpacityA::onEnter()
{
    LayerTest::onEnter();
    
    Size s = Director::sharedDirector()->getWinSize();
    LayerRGBA* layer1 = LayerRGBA::create();
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, s.height/2));
    sister2->setPosition( ccp( s.width*2/3, s.height/2));
    label->setPosition( ccp( s.width/2, s.height/2));
    
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
        
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create(ccc4(192, 0, 0, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    
    layer1->setPosition( ccp(0, s.height/2));
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, 0));
    sister2->setPosition( ccp( s.width*2/3, 0));
    label->setPosition( ccp( s.width/2, 0));
    
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
    
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create(ccc4(192, 0, 0, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    layer1->setCascadeOpacityEnabled(false);
    
    layer1->setPosition( ccp(0, s.height/2));
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, 0));
    sister2->setPosition( ccp( s.width*2/3, 0));
    label->setPosition( ccp( s.width/2, 0));
    
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
    
    Size s = Director::sharedDirector()->getWinSize();
    LayerRGBA* layer1 = LayerRGBA::create();
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, s.height/2));
    sister2->setPosition( ccp( s.width*2/3, s.height/2));
    label->setPosition( ccp( s.width/2, s.height/2));
    
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
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create(ccc4(255, 255, 255, 255), s.width, s.height/2);
    
    layer1->setPosition( ccp(0, s.height/2));
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, 0));
    sister2->setPosition( ccp( s.width*2/3, 0));
    label->setPosition( ccp( s.width/2, 0));
    
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
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create(ccc4(255, 255, 255, 255), s.width, s.height/2);
    layer1->setCascadeColorEnabled(false);
    layer1->setPosition( ccp(0, s.height/2));
    
    Sprite *sister1 = Sprite::create("Images/grossinis_sister1.png");
    Sprite *sister2 = Sprite::create("Images/grossinis_sister2.png");
    LabelBMFont *label = LabelBMFont::create("Test", "fonts/bitmapFontTest.fnt");
    
    layer1->addChild(sister1);
    layer1->addChild(sister2);
    layer1->addChild(label);
    this->addChild( layer1, 0, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, 0));
    sister2->setPosition( ccp( s.width*2/3, 0));
    label->setPosition( ccp( s.width/2, 0));
    
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

    setTouchEnabled(true);
    
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer = LayerColor::create( ccc4(0xFF, 0x00, 0x00, 0x80), 200, 200); 
    
    layer->ignoreAnchorPointForPosition(false);
    layer->setPosition( ccp(s.width/2, s.height/2) );
    addChild(layer, 1, kTagLayer);
}

void LayerTest1::updateSize(Point &touchLocation)
{    
    Size s = Director::sharedDirector()->getWinSize();
    
    Size newSize = CCSizeMake( fabs(touchLocation.x - s.width/2)*2, fabs(touchLocation.y - s.height/2)*2);
    
    LayerColor* l = (LayerColor*) getChildByTag(kTagLayer);

    l->setContentSize( newSize );
}

void LayerTest1::ccTouchesBegan(Set *pTouches, Event *pEvent)
{
    ccTouchesMoved(pTouches, pEvent);
}

void LayerTest1::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch *touch = (Touch*)pTouches->anyObject();
    Point touchLocation = touch->getLocation();

    updateSize(touchLocation);
}

void LayerTest1::ccTouchesEnded(Set *pTouches, Event *pEvent)
{
    ccTouchesMoved(pTouches, pEvent);
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

    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create( ccc4(255, 255, 0, 80), 100, 300);
    layer1->setPosition(ccp(s.width/3, s.height/2));
    layer1->ignoreAnchorPointForPosition(false);
    addChild(layer1, 1);
    
    LayerColor* layer2 = LayerColor::create( ccc4(0, 0, 255, 255), 100, 300);
    layer2->setPosition(ccp((s.width/3)*2, s.height/2));
    layer2->ignoreAnchorPointForPosition(false);
    addChild(layer2, 1);
    
    ActionInterval* actionTint = TintBy::create(2, -255, -127, 0);
    ActionInterval* actionTintBack = actionTint->reverse();
    ActionInterval* seq1 = Sequence::create( actionTint, actionTintBack, NULL);
    layer1->runAction(seq1);

    ActionInterval* actionFade = FadeOut::create(2.0f);
    ActionInterval* actionFadeBack = actionFade->reverse();
    ActionInterval* seq2 = Sequence::create(actionFade, actionFadeBack, NULL);        
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
    Size s = Director::sharedDirector()->getWinSize();
    LayerColor* layer1 = LayerColor::create( ccc4(255, 255, 255, 80) );
    
    Sprite* sister1 = Sprite::create(s_pPathSister1);
    Sprite* sister2 = Sprite::create(s_pPathSister2);
    
    addChild(sister1);
    addChild(sister2);
    addChild(layer1, 100, kTagLayer);
    
    sister1->setPosition( ccp( s.width*1/3, s.height/2) );
    sister2->setPosition( ccp( s.width*2/3, s.height/2) );

    schedule( schedule_selector(LayerTestBlend::newBlend), 1.0f);
}

void LayerTestBlend::newBlend(float dt)
{
     LayerColor *layer = (LayerColor*)getChildByTag(kTagLayer);

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

    ccBlendFunc bf = {src, dst};
    layer->setBlendFunc( bf );
}


std::string LayerTestBlend::title()
{
    return "ColorLayer: blend";
}

//------------------------------------------------------------------
//
// LayerGradient
//
//------------------------------------------------------------------
LayerGradientTest::LayerGradientTest()
{
    LayerGradient* layer1 = LayerGradient::create(ccc4(255,0,0,255), ccc4(0,255,0,255), ccp(0.9f, 0.9f));
    addChild(layer1, 0, kTagLayer);

    setTouchEnabled(true);

    LabelTTF *label1 = LabelTTF::create("Compressed Interpolation: Enabled", "Marker Felt", 26);
    LabelTTF *label2 = LabelTTF::create("Compressed Interpolation: Disabled", "Marker Felt", 26);
    MenuItemLabel *item1 = MenuItemLabel::create(label1);
    MenuItemLabel *item2 = MenuItemLabel::create(label2);
    MenuItemToggle *item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(LayerGradientTest::toggleItem, this), item1, item2, NULL);

    Menu *menu = Menu::create(item, NULL);
    addChild(menu);
    Size s = Director::sharedDirector()->getWinSize();
    menu->setPosition(ccp(s.width / 2, 100));
}

void LayerGradientTest::toggleItem(Object *sender)
{
    LayerGradient *gradient = (LayerGradient*)getChildByTag(kTagLayer);
    gradient->setCompressedInterpolation(! gradient->isCompressedInterpolation());
}

void LayerGradientTest::ccTouchesMoved(Set * touches, Event *event)
{
    Size s = Director::sharedDirector()->getWinSize();

    SetIterator it = touches->begin();
    Touch* touch = (Touch*)(*it);
    Point start = touch->getLocation();    

    Point diff = ccpSub( ccp(s.width/2,s.height/2), start);    
    diff = ccpNormalize(diff);

    LayerGradient *gradient = (LayerGradient*) getChildByTag(1);
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

// LayerIgnoreAnchorPointPos

#define kLayerIgnoreAnchorPoint  1000

void LayerIgnoreAnchorPointPos::onEnter()
{
    LayerTest::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    LayerColor *l = LayerColor::create(ccc4(255, 0, 0, 255), 150, 150);

    l->setAnchorPoint(ccp(0.5f, 0.5f));
    l->setPosition(ccp( s.width/2, s.height/2));

    MoveBy *move = MoveBy::create(2, ccp(100,2));
    MoveBy * back = (MoveBy *)move->reverse();
    Sequence *seq = Sequence::create(move, back, NULL);
    l->runAction(RepeatForever::create(seq));
    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    Sprite *child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    Size lsize = l->getContentSize();
    child->setPosition(ccp(lsize.width/2, lsize.height/2));

    MenuItemFont *item = MenuItemFont::create("Toggle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointPos::onToggle, this));

    Menu *menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(ccp(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointPos::onToggle(Object* pObject)
{
    Node* pLayer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = pLayer->isIgnoreAnchorPointForPosition();
    pLayer->ignoreAnchorPointForPosition(! ignore);
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
    Size s = Director::sharedDirector()->getWinSize();

    LayerColor *l = LayerColor::create(ccc4(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(ccp(0.5f, 0.5f));
    l->setPosition(ccp( s.width/2, s.height/2));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    RotateBy *rot = RotateBy::create(2, 360);
    l->runAction(RepeatForever::create(rot));


    Sprite *child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    Size lsize = l->getContentSize();
    child->setPosition(ccp(lsize.width/2, lsize.height/2));

    MenuItemFont *item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointRot::onToggle, this));

    Menu *menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(ccp(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointRot::onToggle(Object* pObject)
{
    Node* pLayer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = pLayer->isIgnoreAnchorPointForPosition();
    pLayer->ignoreAnchorPointForPosition(! ignore);
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
    
    Size s = Director::sharedDirector()->getWinSize();

    LayerColor *l = LayerColor::create(ccc4(255, 0, 0, 255), 200, 200);

    l->setAnchorPoint(ccp(0.5f, 1.0f));
    l->setPosition(ccp( s.width/2, s.height/2));


    ScaleBy *scale = ScaleBy::create(2, 2);
    ScaleBy* back = (ScaleBy*)scale->reverse();
    Sequence *seq = Sequence::create(scale, back, NULL);

    l->runAction(RepeatForever::create(seq));

    this->addChild(l, 0, kLayerIgnoreAnchorPoint);

    Sprite *child = Sprite::create("Images/grossini.png");
    l->addChild(child);
    Size lsize = l->getContentSize();
    child->setPosition(ccp(lsize.width/2, lsize.height/2));

    MenuItemFont *item = MenuItemFont::create("Toogle ignore anchor point", CC_CALLBACK_1(LayerIgnoreAnchorPointScale::onToggle, this));

    Menu *menu = Menu::create(item, NULL);
    this->addChild(menu);

    menu->setPosition(ccp(s.width/2, s.height/2));
}

void LayerIgnoreAnchorPointScale::onToggle(Object* pObject)
{
    Node* pLayer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    bool ignore = pLayer->isIgnoreAnchorPointForPosition();
    pLayer->ignoreAnchorPointForPosition(! ignore);
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
    Layer* pLayer = nextAction();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}

LayerExtendedBlendOpacityTest::LayerExtendedBlendOpacityTest()
{
    LayerGradient* layer1 = LayerGradient::create(ccc4(255, 0, 0, 255), ccc4(255, 0, 255, 255));
    layer1->setContentSize(CCSizeMake(80, 80));
    layer1->setPosition(ccp(50,50));
    addChild(layer1);
    
    LayerGradient* layer2 = LayerGradient::create(ccc4(0, 0, 0, 127), ccc4(255, 255, 255, 127));
    layer2->setContentSize(CCSizeMake(80, 80));
    layer2->setPosition(ccp(100,90));
    addChild(layer2);
    
    LayerGradient* layer3 = LayerGradient::create();
    layer3->setContentSize(CCSizeMake(80, 80));
    layer3->setPosition(ccp(150,140));
    layer3->setStartColor(ccc3(255, 0, 0));
    layer3->setEndColor(ccc3(255, 0, 255));
    layer3->setStartOpacity(255);
    layer3->setEndOpacity(255);
    ccBlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE_MINUS_SRC_ALPHA;
    layer3->setBlendFunc(blend);
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

