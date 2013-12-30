#include "LabelTestNew.h"
#include "../testResource.h"
#include "renderer/CCRenderer.h"

enum {
    kTagTileMap = 1,
    kTagSpriteManager = 1,
    kTagAnimation1 = 1,
    kTagBitmapAtlas1 = 1,
    kTagBitmapAtlas2 = 2,
    kTagBitmapAtlas3 = 3,
};

enum {
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

//------------------------------------------------------------------
//
// AtlasDemoNew
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

Layer* nextAtlasActionNew();
Layer* backAtlasActionNew();
Layer* restartAtlasActionNew();

static int sceneIdx = -1; 

static std::function<Layer*()> createFunctions[] =
{
    CL(LabelFNTColorAndOpacity),
    CL(LabelFNTSpriteActions),
    CL(LabelFNTPadding),
    CL(LabelFNTOffset),
    CL(LabelFNTColor),
    CL(LabelFNTHundredLabels),
    CL(LabelFNTMultiLine),
    CL(LabelFNTandTTFEmpty),
    CL(LabelFNTRetina),
    CL(LabelFNTGlyphDesigner),
    CL(LabelTTFUnicodeChinese),
    CL(LabelFNTUnicodeChinese),
    CL(LabelFNTMultiLineAlignment),
    CL(LabelFNTUNICODELanguages),
    CL(LabelTTFAlignmentNew),
    CL(LabelFNTBounds),
    CL(LabelTTFLongLineWrapping),
    CL(LabelTTFColor),
    CL(LabelTTFFontsTestNew),
    CL(LabelTTFDynamicAlignment),
    CL(LabelTTFUnicodeNew),
    CL(LabelBMFontTestNew),
    CL(LabelTTFDistanceField),
    CL(LabelTTFDistanceFieldEffect)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextAtlasActionNew()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backAtlasActionNew()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartAtlasActionNew()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void AtlasTestSceneNew::runThisTest()
{
    sceneIdx = -1;
    auto layer = nextAtlasActionNew();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

AtlasDemoNew::AtlasDemoNew(void)
{
}

AtlasDemoNew::~AtlasDemoNew(void)
{
}

std::string AtlasDemoNew::title() const
{
    return "No title";
}

std::string AtlasDemoNew::subtitle() const
{
    return "";
}

void AtlasDemoNew::onEnter()
{
    BaseTest::onEnter();
}

void AtlasDemoNew::restartCallback(Object* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild(restartAtlasActionNew()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemoNew::nextCallback(Object* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild( nextAtlasActionNew() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemoNew::backCallback(Object* sender)
{
    auto s = new AtlasTestSceneNew();
    s->addChild( backAtlasActionNew() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

LabelTTFAlignmentNew::LabelTTFAlignmentNew()
{
    auto s = Director::getInstance()->getWinSize();

    auto ttf0 = Label::createWithTTF("Alignment 0\nnew line", "fonts/tahoma.ttf", 32);
    ttf0->setAlignment(TextHAlignment::LEFT);
    ttf0->setPosition(Point(s.width/2,(s.height/6)*2 - 30));
    ttf0->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf0);

    auto ttf1 = Label::createWithTTF("Alignment 1\nnew line", "fonts/tahoma.ttf", 32);
    ttf1->setAlignment(TextHAlignment::CENTER);
    ttf1->setPosition(Point(s.width/2,(s.height/6)*3 - 30));
    ttf1->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf1);

    auto ttf2 = Label::createWithTTF("Alignment 2\nnew line", "fonts/tahoma.ttf", 32);
    ttf1->setAlignment(TextHAlignment::RIGHT);
    ttf2->setPosition(Point(s.width/2,(s.height/6)*4 - 30));
    ttf2->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf2);
}

std::string LabelTTFAlignmentNew::title() const
{
    return "New Label + TTF";
}

std::string LabelTTFAlignmentNew::subtitle() const
{
    return "Tests alignment values";
}

LabelFNTColorAndOpacity::LabelFNTColorAndOpacity()
{
    _time = 0;

    auto col = LayerColor::create( Color4B(128,128,128,255) );
    addChild(col, -10);
    
    auto label1 = Label::createWithBMFont("Test", "fonts/bitmapFontTest2.fnt");
    
    label1->setAnchorPoint( Point(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto seq = Sequence::create(fade, fade_in, NULL);
    auto repeat = RepeatForever::create(seq);
    label1->runAction(repeat);
    
    auto label2 = Label::createWithBMFont("Test", "fonts/bitmapFontTest2.fnt");
    label2->setAnchorPoint( Point(0.5f, 0.5f) );
    label2->setColor( Color3B::RED );
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->runAction( repeat->clone() );
    
    auto label3 = Label::createWithBMFont("Test", "fonts/bitmapFontTest2.fnt");
    label3->setAnchorPoint( Point(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
    
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );
    
    schedule( schedule_selector(LabelFNTColorAndOpacity::step) );//:@selector(step:)];
}

void LabelFNTColorAndOpacity::step(float dt)
{
    _time += dt;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    auto label2 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    auto label3 = (Label*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);
}

std::string LabelFNTColorAndOpacity::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTColorAndOpacity::subtitle() const
{
    return "Testing opacity + tint";
}

LabelFNTSpriteActions::LabelFNTSpriteActions()
{
    _time = 0;

    // Upper Label
    auto label = Label::createWithBMFont("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    
    
    auto BChar = (Sprite*) label->getLetter(0);
    auto FChar = (Sprite*) label->getLetter(7);
    auto AChar = (Sprite*) label->getLetter(12);
    
    
    auto rotate = RotateBy::create(2, 360);
    auto rot_4ever = RepeatForever::create(rotate);
    
    auto scale = ScaleBy::create(2, 1.5f);
    auto scale_back = scale->reverse();
    auto scale_seq = Sequence::create(scale, scale_back,NULL);
    auto scale_4ever = RepeatForever::create(scale_seq);
    
    auto jump = JumpBy::create(0.5f, Point::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    
    auto fade_out = FadeOut::create(1);
    auto fade_in = FadeIn::create(1);
    auto seq = Sequence::create(fade_out, fade_in, NULL);
    auto fade_4ever = RepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    auto label2 = Label::createWithBMFont("00.0", "fonts/bitmapFontTest.fnt");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( Point(s.width/2.0f, 80) );
    
    auto lastChar = (Sprite*) label2->getLetter(3);
    lastChar->runAction( rot_4ever->clone() );
    
    schedule( schedule_selector(LabelFNTSpriteActions::step), 0.1f);
}

void LabelFNTSpriteActions::draw()
{
    _renderCmd.init(0, _vertexZ);
    _renderCmd.func = CC_CALLBACK_0(LabelFNTSpriteActions::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_renderCmd);
    
}

void LabelFNTSpriteActions::onDraw()
{
    kmMat4 oldMat;
    kmGLGetMatrix(KM_GL_MODELVIEW, &oldMat);
    kmGLLoadMatrix(&_modelViewTransform);
    
    auto s = Director::getInstance()->getWinSize();
    DrawPrimitives::drawLine( Point(0, s.height/2), Point(s.width, s.height/2) );
    DrawPrimitives::drawLine( Point(s.width/2, 0), Point(s.width/2, s.height) );
    
    kmGLLoadMatrix(&oldMat);
}

void LabelFNTSpriteActions::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string LabelFNTSpriteActions::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTSpriteActions::subtitle() const
{
    return "Using fonts as Sprite objects. Some characters should rotate.";
}

LabelFNTPadding::LabelFNTPadding()
{
    auto label = Label::createWithBMFont("abcdefg", "fonts/bitmapFontTest4.fnt");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
}

std::string LabelFNTPadding::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTPadding::subtitle() const
{
    return "Testing padding";
}

LabelFNTOffset::LabelFNTOffset()
{
    auto s = Director::getInstance()->getWinSize();

    Label* label = NULL;
    label = Label::createWithBMFont("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2+50) );
    label->setAnchorPoint( Point(0.5f, 0.5f) ) ;
    
    label = Label::createWithBMFont("fafefifofu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );

    label = Label::createWithBMFont("aeiou", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2-50) );
    label->setAnchorPoint( Point(0.5f, 0.5f) ); 
}

std::string LabelFNTOffset::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTOffset::subtitle() const
{
    return "Rendering should be OK. Testing offset";
}

LabelFNTColor::LabelFNTColor()
{
    auto s = Director::getInstance()->getWinSize();
    
    Label* label = NULL;
    label = Label::createWithBMFont("Blue", "fonts/bitmapFontTest5.fnt");
    label->setColor( Color3B::BLUE );
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );

    label = Label::createWithBMFont("Red", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    label->setColor( Color3B::RED );

    label = Label::createWithBMFont("G", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    label->setColor( Color3B::GREEN );
    label->setString("Green");
}

std::string LabelFNTColor::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTColor::subtitle() const
{
    return "Testing color";
}

LabelFNTHundredLabels::LabelFNTHundredLabels()
{
    // Upper Label
    for ( int i=0 ; i < 100;i ++ ) 
    {
        char str[6] = {0};
        sprintf(str, "-%d-", i);
        auto label = Label::createWithBMFont(str, "fonts/bitmapFontTest.fnt");
        addChild(label);
        
        auto s = Director::getInstance()->getWinSize();

        auto p = Point( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
        label->setPosition( p );
        label->setAnchorPoint(Point(0.5f, 0.5f));
    }
}

std::string LabelFNTHundredLabels::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTHundredLabels::subtitle() const
{
    return "Creating several Labels using the same FNT file; should be fast";
}

LabelFNTMultiLine::LabelFNTMultiLine()
{
    Size s;

    // Left
    auto label1 = Label::createWithBMFont(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(Point(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    auto label2 = Label::createWithBMFont("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(Point(0.5f, 0.5f));
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    auto label3 = Label::createWithBMFont("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(Point(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string LabelFNTMultiLine::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTMultiLine::subtitle() const
{
    return "Multiline + anchor point";
}

LabelFNTandTTFEmpty::LabelFNTandTTFEmpty()
{
    auto s = Director::getInstance()->getWinSize();
    float delta = s.height/4;

    // LabelBMFont
    auto label1 = Label::createWithBMFont("", "fonts/bitmapFontTest3.fnt", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    label1->setPosition(Point(s.width/2, delta));

    // LabelTTF
    auto label2 = Label::createWithTTF("", "fonts/arial.ttf", 48, s.width, TextHAlignment::CENTER,GlyphCollection::NEHE);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setAnchorPoint(Point(0.5f, 0.5f));
    label2->setPosition(Point(s.width/2, delta * 2));

    

    schedule(schedule_selector(LabelFNTandTTFEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelFNTandTTFEmpty::updateStrings(float dt)
{
    auto label1 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas1) );
    auto label2 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas2) );

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
    
        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
    
        setEmpty = false;
    }
}

std::string LabelFNTandTTFEmpty::title() const
{
    return "New Label : .FNT file & .TTF file";
}

std::string LabelFNTandTTFEmpty::subtitle() const
{
    return "2 empty labels: new Label + .FNT and new Label + .TTF";
}

LabelFNTRetina::LabelFNTRetina()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTRetina::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTRetina::subtitle() const
{
    return "loading arista16 or arista16-hd";
}

LabelFNTGlyphDesigner::LabelFNTGlyphDesigner()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);

    // LabelBMFont
    auto label1 = Label::createWithBMFont("Testing Glyph Designer", "fonts/futura-48.fnt");
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTGlyphDesigner::title() const
{
    return "New Label + .FNT file";
}

std::string LabelFNTGlyphDesigner::subtitle() const
{
    return "Testing Glyph Designer: you should see a font with shawdows and outline";
}

LabelTTFUnicodeChinese::LabelTTFUnicodeChinese()
{
    auto size = Director::getInstance()->getWinSize();
    // Adding "啊" letter at the end of string to make VS2012 happy, otherwise VS will generate errors  
    // like "Error 3 error C2146: syntax error : missing ')' before identifier 'label'"; 
    auto label = Label::createWithTTF("美好的一天啊", "fonts/wt021.ttf", 55, size.width, TextHAlignment::CENTER, GlyphCollection::CUSTOM, "美好的一天啊");
    label->setAnchorPoint(Point(0.5f, 0.5f));
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelTTFUnicodeChinese::title() const
{
    return "New Label + .TTF file Chinese";
}

std::string LabelTTFUnicodeChinese::subtitle() const
{
    return "Testing new Label + TTF with Chinese character";
}

LabelFNTUnicodeChinese::LabelFNTUnicodeChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = Label::createWithBMFont("中国", "fonts/bitmapFontChinese.fnt");
    label->setAnchorPoint(Point(0.5f, 0.5f));
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelFNTUnicodeChinese::title() const
{
    return "New Label + .FNT file Chinese";
}

std::string LabelFNTUnicodeChinese::subtitle() const
{
    return "Testing new Label + FNT with Chinese character";
}


/// BitmapFontMultiLineAlignmentNew

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample    "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample         "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding  = 50;
static float menuItemPaddingCenter = 50;

LabelFNTMultiLineAlignment::LabelFNTMultiLineAlignment()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // ask director the the window size
    auto size = Director::getInstance()->getWinSize();

    // create and initialize a Label
    this->_labelShouldRetain = Label::createWithBMFont(LongSentencesExample, "fonts/markerFelt.fnt", TextHAlignment::CENTER, size.width/1.5);
    //this->_labelShouldRetain = Label::createWithBMFont(LongSentencesExample, "fonts/bitmapFontTest.fnt", TextHAlignment::CENTER, size.width/1.5);
    this->_labelShouldRetain->setAnchorPoint(Point(0.5f, 0.5f));
    this->_labelShouldRetain->retain();

    this->_arrowsBarShouldRetain = Sprite::create("Images/arrowsBar.png");
    this->_arrowsBarShouldRetain->retain();
    this->_arrowsShouldRetain = Sprite::create("Images/arrows.png");
    this->_arrowsShouldRetain->retain();

    MenuItemFont::setFontSize(20);
    auto longSentences = MenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto lineBreaks    = MenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto mixed         = MenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto stringMenu    = Menu::create(longSentences, lineBreaks, mixed, NULL);
    stringMenu->alignItemsVertically();

    longSentences->setColor(Color3B::RED);
    _lastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    MenuItemFont::setFontSize(30);

    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto center = MenuItemFont::create("Center", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto alignmentMenu = Menu::create(left, center, right, NULL);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(Color3B::RED);
    _lastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->_labelShouldRetain->setPosition(Point(size.width/2, size.height/2));

    this->_arrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->_arrowsBarShouldRetain->setScaleX(arrowsWidth / this->_arrowsBarShouldRetain->getContentSize().width);
    this->_arrowsBarShouldRetain->setPosition(Point(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_labelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(Point(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(Point(size.width/2, menuItemPaddingCenter+15));

    this->addChild(this->_labelShouldRetain);
    this->addChild(this->_arrowsBarShouldRetain);
    this->addChild(this->_arrowsShouldRetain);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);
}

LabelFNTMultiLineAlignment::~LabelFNTMultiLineAlignment()
{
    this->_labelShouldRetain->release();
    this->_arrowsBarShouldRetain->release();
    this->_arrowsShouldRetain->release();
}

std::string LabelFNTMultiLineAlignment::title() const
{
    return "";
}

std::string LabelFNTMultiLineAlignment::subtitle() const
{
    return "";
}

void LabelFNTMultiLineAlignment::stringChanged(cocos2d::Object *sender)
{
    auto item = (MenuItemFont*)sender;
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        this->_labelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        this->_labelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        this->_labelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::alignmentChanged(cocos2d::Object *sender)
{
    auto item = static_cast<MenuItemFont*>(sender);
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::LEFT);
        break;
    case CenterAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::CENTER);
        break;
    case RightAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::RIGHT);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches[0];
    auto location = touch->getLocationInView();

    if (this->_arrowsShouldRetain->getBoundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBarShouldRetain->setVisible(true);
    }
}

void LabelFNTMultiLineAlignment::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBarShouldRetain->setVisible(false);
}

void LabelFNTMultiLineAlignment::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (! _drag)
    {
        return;
    }

    auto touch = touches[0];
    auto location = touch->getLocationInView();

    auto winSize = Director::getInstance()->getWinSize();

    this->_arrowsShouldRetain->setPosition(Point(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->_arrowsShouldRetain->getPosition().x - this->_labelShouldRetain->getPosition().x) * 2;

    this->_labelShouldRetain->setWidth(labelWidth);
}

void LabelFNTMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrowsShouldRetain->setPosition(Point(this->_labelShouldRetain->getPosition().x + this->_labelShouldRetain->getContentSize().width/2,
        this->_labelShouldRetain->getPosition().y));
}

/// BMFontUnicodeNew
LabelFNTUNICODELanguages::LabelFNTUNICODELanguages()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    std::string russian  = strings["russian"].asString();
    std::string spanish  = strings["spanish"].asString();
    std::string japanese = strings["japanese"].asString();

    auto s = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont(spanish, "fonts/arial-unicode-26.fnt", TextHAlignment::CENTER, 200);
    addChild(label1);
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    label1->setPosition(Point(s.width/2, s.height/5*3));
    
    auto label2 = Label::createWithBMFont(chinese, "fonts/arial-unicode-26.fnt");
    addChild(label2);
    label2->setAnchorPoint(Point(0.5f, 0.5f));
    label2->setPosition(Point(s.width/2, s.height/5*2.5));

    auto label3 = Label::createWithBMFont(russian, "fonts/arial-26-en-ru.fnt");
    addChild(label3);
    label3->setAnchorPoint(Point(0.5f, 0.5f));
    label3->setPosition(Point(s.width/2, s.height/5*2));

    auto label4 = Label::createWithBMFont(japanese, "fonts/arial-unicode-26.fnt");
    addChild(label4);
    label4->setAnchorPoint(Point(0.5f, 0.5f));
    label4->setPosition(Point(s.width/2, s.height/5*1.5));
}

std::string LabelFNTUNICODELanguages::title() const
{
    return "New Label + .FNT + UNICODE";
}

std::string LabelFNTUNICODELanguages::subtitle() const
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

LabelFNTBounds::LabelFNTBounds()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);
    
    // LabelBMFont
    label1 = Label::createWithBMFont("Testing Glyph Designer", "fonts/boundsTestFont.fnt", TextHAlignment::CENTER, s.width);
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelFNTBounds::title() const
{
    return "New Label + .FNT + Bounds";
}

std::string LabelFNTBounds::subtitle() const
{
    return "You should see string enclosed by a box";
}

void LabelFNTBounds::draw()
{
    _renderCmd.init(0, _vertexZ);
    _renderCmd.func = CC_CALLBACK_0(LabelFNTBounds::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_renderCmd);
}

void LabelFNTBounds::onDraw()
{
    kmMat4 oldMat;
    kmGLGetMatrix(KM_GL_MODELVIEW, &oldMat);
    kmGLLoadMatrix(&_modelViewTransform);
    
    auto labelSize = label1->getContentSize();
    auto origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Point vertices[4]=
    {
        Point(origin.width, origin.height),
        Point(labelSize.width + origin.width, origin.height),
        Point(labelSize.width + origin.width, labelSize.height + origin.height),
        Point(origin.width, labelSize.height + origin.height)
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
    
    kmGLLoadMatrix(&oldMat);
}

LabelTTFLongLineWrapping::LabelTTFLongLineWrapping()
{
    auto size = Director::getInstance()->getWinSize();

    // Long sentence
    auto label1 = Label::createWithTTF(LongSentencesExample, "fonts/arial.ttf", 28, size.width, TextHAlignment::CENTER, GlyphCollection::NEHE);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setAnchorPoint(Point(0.5, 1.0));
    addChild(label1);
}

std::string LabelTTFLongLineWrapping::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFLongLineWrapping::subtitle() const
{
    return "Uses the new Label with TTF. Testing auto-wrapping";
}

LabelTTFColor::LabelTTFColor()
{
    auto size = Director::getInstance()->getWinSize();

    // Green
    auto label1 = Label::createWithTTF("Green", "fonts/arial.ttf", 35, size.width, TextHAlignment::CENTER, GlyphCollection::NEHE);
    label1->setPosition( Point(size.width/2, size.height/5 * 1.5) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point(0.5, 0.5));
    addChild(label1);

    // Red
    auto label2 = Label::createWithTTF("Red", "fonts/arial.ttf", 35, size.width, TextHAlignment::CENTER, GlyphCollection::NEHE);
    label2->setPosition( Point(size.width/2, size.height/5 * 2.0) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point(0.5, 0.5));
    addChild(label2);

    // Blue
    auto label3 = Label::createWithTTF("Blue", "fonts/arial.ttf", 35, size.width, TextHAlignment::CENTER, GlyphCollection::NEHE);
    label3->setPosition( Point(size.width/2, size.height/5 * 2.5) );
    label3->setColor( Color3B::BLUE );
    label3->setAnchorPoint(Point(0.5, 0.5));
    addChild(label3);
}

std::string LabelTTFColor::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFColor::subtitle() const
{
    return "Uses the new Label with TTF. Testing Color";
}

LabelTTFDynamicAlignment::LabelTTFDynamicAlignment()
{
    auto size = Director::getInstance()->getWinSize();
    
    _label = Label::createWithTTF(LongSentencesExample, "fonts/arial.ttf", 45, size.width, TextHAlignment::CENTER, GlyphCollection::NEHE);
    _label->setPosition( Point(size.width/2, size.height/2) );
    _label->setAnchorPoint(Point(0.5, 0.5));
    
    
    
    auto menu = Menu::create(
                              MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentLeft, this)),
                              MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentCenter, this)),
                              MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentRight, this)),
                              NULL);
    
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(50, size.height / 4 ));
    
    addChild(_label);
    this->addChild(menu);
}

void  LabelTTFDynamicAlignment::updateAlignment()
{
    if (_label)
    {
        _label->setAlignment(_horizAlign);
    }
}

void LabelTTFDynamicAlignment::setAlignmentLeft(Object* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentCenter(Object* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentRight(Object* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    this->updateAlignment();
}

std::string LabelTTFDynamicAlignment::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDynamicAlignment::subtitle() const
{
    return "Uses the new Label with TTF. Testing alignment";
}

//
// NewLabelTTF unicode test
//
LabelTTFUnicodeNew::LabelTTFUnicodeNew()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    
//    std::string russian  = strings["russian"].asString();
//    std::string spanish  = strings["spanish"].asString();
//    std::string japanese = strings["japanese"].asString();
    
    auto size = Director::getInstance()->getWinSize();
    
    float vStep = size.height/9;
    float vSize = size.height;
     
    
    // Spanish
    auto label1 = Label::createWithTTF("Buen día, ¿cómo te llamas?", "fonts/arial.ttf", 45, size.width, TextHAlignment::CENTER, GlyphCollection::ASCII);
    label1->setPosition( Point(size.width/2, vSize - (vStep * 4.5)) );
    label1->setAnchorPoint(Point(0.5, 0.5));
    addChild(label1);
    
    // German
    auto label2 = Label::createWithTTF("In welcher Straße haben Sie gelebt?", "fonts/arial.ttf", 45, size.width, TextHAlignment::CENTER, GlyphCollection::ASCII);
    label2->setPosition( Point(size.width/2, vSize - (vStep * 5.5)) );
    label2->setAnchorPoint(Point(0.5, 0.5));
    addChild(label2);
    
    // chinese
    auto label3 = Label::createWithTTF(chinese, "fonts/wt021.ttf", 45, size.width, TextHAlignment::CENTER, GlyphCollection::CUSTOM, chinese.c_str());
    label3->setPosition( Point(size.width/2, vSize - (vStep * 6.5)) );
    label3->setAnchorPoint(Point(0.5, 0.5));
    addChild(label3);
}

std::string LabelTTFUnicodeNew::title() const
{
    return "New Label + TTF unicode";
}

std::string LabelTTFUnicodeNew::subtitle() const
{
    return "Uses the new Label with TTF. Testing unicode";
}

LabelTTFFontsTestNew::LabelTTFFontsTestNew()
{
    const char *ttfpaths[] = {
        "fonts/A Damn Mess.ttf",
        "fonts/Abberancy.ttf",
        "fonts/Abduction.ttf",
        "fonts/American Typewriter.ttf",
        "fonts/Paint Boy.ttf",
        "fonts/Schwarzwald Regular.ttf",
        "fonts/Scissor Cuts.ttf",
    };
#define arraysize(ar)  (sizeof(ar) / sizeof(ar[0]))

    auto size = Director::getInstance()->getWinSize();

    for(size_t i=0;i < arraysize(ttfpaths); ++i) {
        auto label = Label::createWithTTF( ttfpaths[i], ttfpaths[i], 40, 0, TextHAlignment::CENTER, GlyphCollection::NEHE);
        if( label ) {
            
            label->setPosition( Point(size.width/2, ((size.height * 0.6)/arraysize(ttfpaths) * i) + (size.height/5)));
            addChild(label);
            
            label->setAnchorPoint(Point(0.5, 0.5));
        } else {
            log("ERROR: Cannot load: %s", ttfpaths[i]);
        }
    }
}

std::string LabelTTFFontsTestNew::title() const
{
    return "New Label + TTF";
}

std::string LabelTTFFontsTestNew::subtitle() const
{
    return "";
}

LabelBMFontTestNew::LabelBMFontTestNew()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont("Hello World, this is testing the new Label using fnt file", "fonts/bitmapFontTest2.fnt", TextHAlignment::CENTER, size.width);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setAnchorPoint(Point(0.5, 0.5));
    addChild(label1);
}

std::string LabelBMFontTestNew::title() const
{
    return "New Label + FNT";
}

std::string LabelBMFontTestNew::subtitle() const
{
    return "Uses the new Label with .FNT file";
}

LabelTTFDistanceField::LabelTTFDistanceField()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithTTF("Distance Field", "fonts/arial.ttf", 80, size.width, TextHAlignment::CENTER, GlyphCollection::DYNAMIC,nullptr,true);
    label1->setPosition( Point(size.width/2, size.height/2) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point(0.5, 0.5));
    addChild(label1);

    auto action = Sequence::create(
        DelayTime::create(1.0f),
        ScaleTo::create(6.0f,5.0f,5.0f),
        ScaleTo::create(6.0f,1.0f,1.0f),
        nullptr);
    label1->runAction(RepeatForever::create(action));

    auto label2 = Label::createWithTTF("Distance Field", "fonts/arial.ttf", 80, size.width, TextHAlignment::CENTER, GlyphCollection::DYNAMIC,nullptr,true);
    label2->setPosition( Point(size.width/2, size.height/5) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point(0.5, 0.5));
    addChild(label2);

}

std::string LabelTTFDistanceField::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDistanceField::subtitle() const
{
    return "Testing rendering base on DistanceField";
}

LabelTTFDistanceFieldEffect::LabelTTFDistanceFieldEffect()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    auto label1 = Label::createWithTTF("Glow", "fonts/arial.ttf", 80, size.width, TextHAlignment::CENTER, GlyphCollection::DYNAMIC,nullptr,true);
    label1->setPosition( Point(size.width/2, size.height*0.5) );
    label1->setColor( Color3B::GREEN );
    label1->setAnchorPoint(Point(0.5, 0.5));
    label1->setLabelEffect(LabelEffect::GLOW,Color3B::YELLOW);
    addChild(label1);

    auto label2 = Label::createWithTTF("Outline", "fonts/arial.ttf", 80, size.width, TextHAlignment::CENTER, GlyphCollection::DYNAMIC,nullptr,true);
    label2->setPosition( Point(size.width/2, size.height*0.375) );
    label2->setColor( Color3B::RED );
    label2->setAnchorPoint(Point(0.5, 0.5));
    label2->setLabelEffect(LabelEffect::OUTLINE,Color3B::BLUE);
    addChild(label2);

    auto label3 = Label::createWithTTF("Shadow", "fonts/arial.ttf", 80, size.width, TextHAlignment::CENTER, GlyphCollection::DYNAMIC,nullptr,true);
    label3->setPosition( Point(size.width/2, size.height*0.25f) );
    label3->setColor( Color3B::RED );
    label3->setAnchorPoint(Point(0.5, 0.5));
    label3->setLabelEffect(LabelEffect::SHADOW,Color3B::BLACK);
    addChild(label3);

}

std::string LabelTTFDistanceFieldEffect::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDistanceFieldEffect::subtitle() const
{
    return "Testing effect base on DistanceField";
}
