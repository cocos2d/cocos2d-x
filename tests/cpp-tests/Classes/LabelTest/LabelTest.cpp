#include "LabelTest.h"
#include "../testResource.h"
#include "cocos2d.h"

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

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
// AtlasDemo
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

Layer* nextAtlasAction();
Layer* backAtlasAction();
Layer* restartAtlasAction();

static int sceneIdx = -1; 

static std::function<Layer*()> createFunctions[] =
{
    CL(LabelAtlasTest),
    CL(LabelAtlasColorTest),
    CL(Atlas3),
    CL(Atlas4),
    CL(Atlas5),
    CL(Atlas6),
    CL(AtlasBitmapColor),
    CL(AtlasFastBitmap),
    CL(BitmapFontMultiLine),
    CL(LabelsEmpty),
    CL(LabelBMFontHD),
    CL(LabelAtlasHD),
    CL(LabelGlyphDesigner),
    CL(LabelTTFTest),
    CL(LabelTTFMultiline),
    CL(LabelTTFChinese),
    CL(LabelBMFontChinese),
    CL(BitmapFontMultiLineAlignment),
    CL(LabelTTFOpacityTest),
    CL(BMFontOneAtlas),
    CL(BMFontUnicode),
    CL(BMFontInit),
    CL(TTFFontInit),
    CL(Issue1343),
    CL(LabelTTFAlignment),
    CL(LabelBMFontBounds),
    CL(TTFFontShadowAndStroke),
    // should be moved to another test
    CL(Atlas1),
    CL(LabelBMFontCrashTest),
	CL(LabelBMFontBinaryFormat),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextAtlasAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backAtlasAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartAtlasAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
} 


AtlasDemo::AtlasDemo(void)
{
}

AtlasDemo::~AtlasDemo(void)
{
}

std::string AtlasDemo::title() const
{
    return "No title";
}

std::string AtlasDemo::subtitle() const
{
    return "";
}

void AtlasDemo::onEnter()
{
    BaseTest::onEnter();
}

void AtlasDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) AtlasTestScene();
    s->addChild(restartAtlasAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) AtlasTestScene();
    s->addChild( nextAtlasAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) AtlasTestScene();
    s->addChild( backAtlasAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
Atlas1::Atlas1()
{
    setGLProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
    _textureAtlas = TextureAtlas::create(s_AtlasTest, 3); _textureAtlas->retain();
    
    auto s = Director::getInstance()->getWinSize();

    //
    // Notice: u,v tex coordinates are inverted
    //
    V3F_C4B_T2F_Quad quads[] = 
    {
        {
            {Vec3(0,0,0),Color4B(0,0,255,255),Tex2F(0.0f,1.0f),},                // bottom left
            {Vec3(s.width,0,0),Color4B(0,0,255,0),Tex2F(1.0f,1.0f),},            // bottom right
            {Vec3(0,s.height,0),Color4B(0,0,255,0),Tex2F(0.0f,0.0f),},            // top left
            {Vec3(s.width,s.height,0),Color4B(0,0,255,255),Tex2F(1.0f,0.0f),},    // top right
        },        
        {
            {Vec3(40,40,0),Color4B(255,255,255,255),Tex2F(0.0f,0.2f),},            // bottom left
            {Vec3(120,80,0),Color4B(255,0,0,255),Tex2F(0.5f,0.2f),},            // bottom right
            {Vec3(40,160,0),Color4B(255,255,255,255),Tex2F(0.0f,0.0f),},        // top left
            {Vec3(160,160,0),Color4B(0,255,0,255),Tex2F(0.5f,0.0f),},            // top right
        },

        {
            {Vec3(s.width/2,40,0),Color4B(255,0,0,255),Tex2F(0.0f,1.0f),},        // bottom left
            {Vec3(s.width,40,0),Color4B(0,255,0,255),Tex2F(1.0f,1.0f),},        // bottom right
            {Vec3(s.width/2-50,200,0),Color4B(0,0,255,255),Tex2F(0.0f,0.0f),},        // top left
            {Vec3(s.width,100,0),Color4B(255,255,0,255),Tex2F(1.0f,0.0f),},        // top right
        },
        
    };
    
    
    for( int i=0;i<3;i++) 
    {
        _textureAtlas->updateQuad(&quads[i], i);
    }
}

Atlas1::~Atlas1()
{
    _textureAtlas->release();
}

void Atlas1::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Atlas1::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Atlas1::onDraw(const Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);
    _textureAtlas->drawQuads();
}

std::string Atlas1::title() const
{
    return "CCTextureAtlas";
}

std::string Atlas1::subtitle() const
{
    return "Manual creation of TextureAtlas";
}

//------------------------------------------------------------------
//
// LabelAtlasTest
//
//------------------------------------------------------------------

LabelAtlasTest::LabelAtlasTest()
{
    _time = 0;

    auto label1 = LabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Vec2(10,100) );
    label1->setOpacity( 200 );

    auto label2 = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Vec2(10,200) );
    label2->setOpacity( 32 );

    schedule(CC_CALLBACK_1(LabelAtlasTest::step, this), "step_key");
}

void LabelAtlasTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //string.format("%2.2f Test", _time);

    auto label1 = (LabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (LabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    //string.format("%d", (int)_time);
    label2->setString(string);
}

std::string LabelAtlasTest::title() const
{
    return "LabelAtlas";
}

std::string LabelAtlasTest::subtitle() const
{
    return "Updating label should be fast";
}

//------------------------------------------------------------------
//
// LabelAtlasColorTest
//
//------------------------------------------------------------------
LabelAtlasColorTest::LabelAtlasColorTest()
{
    auto label1 = LabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Vec2(10,100) );
    label1->setOpacity( 200 );
    
    auto label2 = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Vec2(10,200) );
    label2->setColor( Color3B::RED );

    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto cb = CallFunc::create(CC_CALLBACK_0(LabelAtlasColorTest::actionFinishCallback, this));
    auto seq = Sequence::create(fade, fade_in, cb, nullptr);
    auto repeat = RepeatForever::create( seq );
    label2->runAction( repeat );    

    _time = 0;
    
    schedule(CC_CALLBACK_1(LabelAtlasColorTest::step, this), "step_key");
}

void LabelAtlasColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelAtlasColorTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //std::string string = std::string::createWithFormat("%2.2f Test", _time);
    auto label1 = (LabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);
    
    auto label2 = (LabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString( string );    
}

std::string LabelAtlasColorTest::title() const
{
    return "CCLabelAtlas";
}

std::string LabelAtlasColorTest::subtitle() const
{
    return "Opacity + Color should work at the same time";
}


//------------------------------------------------------------------
//
// LabelTTFAlignment
//
//------------------------------------------------------------------
LabelTTFAlignment::LabelTTFAlignment()
{
    auto s = Director::getInstance()->getWinSize();

    auto ttf0 = LabelTTF::create("Alignment 0\nnew line", "Helvetica", 12,
                                          Size(256, 32), TextHAlignment::LEFT);
    
    ttf0->setPosition(Vec2(s.width/2,(s.height/6)*2));
    ttf0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(ttf0);
    
    auto ttf1 = LabelTTF::create("Alignment 1\nnew line", "Helvetica", 12,
                                      Size(245, 32), TextHAlignment::CENTER);
    ttf1->setPosition(Vec2(s.width/2,(s.height/6)*3));
    ttf1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(ttf1);

    auto ttf2 = LabelTTF::create("Alignment 2\nnew line", "Helvetica", 12,
                                          Size(245, 32), TextHAlignment::RIGHT);
    ttf2->setPosition(Vec2(s.width/2,(s.height/6)*4));
    ttf2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(ttf2);
}

std::string LabelTTFAlignment::title() const
{
    return "CCLabelTTF alignment";
}

std::string LabelTTFAlignment::subtitle() const
{
    return "Tests alignment values";
}
//------------------------------------------------------------------
//
// Atlas3
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas3::Atlas3()
{
    _time = 0;

    auto col = LayerColor::create( Color4B(128,128,128,255) );
    addChild(col, -10);
    
    auto label1 = LabelBMFont::create("Test",  "fonts/bitmapFontTest2.fnt");
    
    // testing anchors
    label1->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
    addChild(label1, 0, kTagBitmapAtlas1);
    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto seq = Sequence::create(fade, fade_in, nullptr);
    auto repeat = RepeatForever::create(seq);
    label1->runAction(repeat);
    

    // VERY IMPORTANT
    // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
    // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
    // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
    auto label2 = LabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label2->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
    label2->setColor( Color3B::RED );
    addChild(label2, 0, kTagBitmapAtlas2);
    auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
        TintTo::create(1, 0, 255, 0),
        TintTo::create(1, 0, 0, 255),
        nullptr);
    label2->runAction( RepeatForever::create(tint) );
    
    auto label3 = LabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label3->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT );
    addChild(label3, 0, kTagBitmapAtlas3);
       
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );

    schedule(CC_CALLBACK_1(Atlas3::step, this), "step_key");
}

void Atlas3::step(float dt)
{
    _time += dt;
    //std::string string;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    //string.format("%2.2f Test j", _time);
    
    auto label1 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    auto label2 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    auto label3 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);
}

std::string Atlas3::title() const
{
    return "CCLabelBMFont";
}

std::string Atlas3::subtitle() const
{
    return "Testing alignment. Testing opacity + tint";
}

//------------------------------------------------------------------
//
// Atlas4
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas4::Atlas4()
{
    _time = 0;

    auto s = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    drawNode->drawLine( Vec2(0, s.height/2), Vec2(s.width, s.height/2), Color4F(1.0, 1.0, 1.0, 1.0) );
    drawNode->drawLine( Vec2(s.width/2, 0), Vec2(s.width/2, s.height), Color4F(1.0, 1.0, 1.0, 1.0) );
    addChild(drawNode, -1);

    // Upper Label
    auto label = LabelBMFont::create("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
    addChild(label);
    
    label->setPosition( Vec2(s.width/2, s.height/2) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
    
    
    auto BChar = (Sprite*) label->getChildByTag(0);
    auto FChar = (Sprite*) label->getChildByTag(7);
    auto AChar = (Sprite*) label->getChildByTag(12);
    
    
    auto rotate = RotateBy::create(2, 360);
    auto rot_4ever = RepeatForever::create(rotate);
    
    auto scale = ScaleBy::create(2, 1.5f);
    auto scale_back = scale->reverse();
    auto scale_seq = Sequence::create(scale, scale_back,nullptr);
    auto scale_4ever = RepeatForever::create(scale_seq);
    
    auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    
    auto fade_out = FadeOut::create(1);
    auto fade_in = FadeIn::create(1);
    auto seq = Sequence::create(fade_out, fade_in, nullptr);
    auto fade_4ever = RepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    auto label2 = LabelBMFont::create("00.0", "fonts/bitmapFontTest.fnt");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( Vec2(s.width/2.0f, 80) );
    
    auto lastChar = (Sprite*) label2->getChildByTag(3);
    lastChar->runAction( rot_4ever->clone() );
    
    schedule(CC_CALLBACK_1(Atlas4::step, this), 0.1f, "step_key");
}

void Atlas4::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
//     std::string string;
//     string.format("%04.1f", _time);
    
    auto label1 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string Atlas4::title() const
{
    return "CCLabelBMFont";
}

std::string Atlas4::subtitle() const
{
    return "Using fonts as Sprite objects. Some characters should rotate.";
}

//------------------------------------------------------------------
//
// Atlas5
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas5::Atlas5()
{
    auto label = LabelBMFont::create("abcdefg", "fonts/bitmapFontTest4.fnt");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Vec2(s.width/2, s.height/2) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
}

std::string Atlas5::title() const
{
    return "CCLabelBMFont";
}

std::string Atlas5::subtitle() const
{
    return "Testing padding";
}
//------------------------------------------------------------------
//
// Atlas6
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas6::Atlas6()
{
    auto s = Director::getInstance()->getWinSize();

    LabelBMFont* label = nullptr;
    label = LabelBMFont::create("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2+50) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE ) ;
    
    label = LabelBMFont::create("fafefifofu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );

    label = LabelBMFont::create("aeiou", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2-50) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE ); 
}

std::string Atlas6::title() const
{
    return "CCLabelBMFont";
}

std::string Atlas6::subtitle() const
{
    return "Rendering should be OK. Testing offset";
}

//------------------------------------------------------------------
//
// AtlasBitmapColor
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
AtlasBitmapColor::AtlasBitmapColor()
{
    auto s = Director::getInstance()->getWinSize();
    
    LabelBMFont* label = nullptr;
    label = LabelBMFont::create("Blue", "fonts/bitmapFontTest5.fnt");
    label->setColor( Color3B::BLUE );
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/4) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );

    label = LabelBMFont::create("Red", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Vec2(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
    label->setColor( Color3B::RED );

    label = LabelBMFont::create("G", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Vec2(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
    label->setColor( Color3B::GREEN );
    label->setString("Green");
}

std::string AtlasBitmapColor::title() const
{
    return "CCLabelBMFont";
}

std::string AtlasBitmapColor::subtitle() const
{
    return "Testing color";
}

//------------------------------------------------------------------
//
// AtlasFastBitmap
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

AtlasFastBitmap::AtlasFastBitmap()
{
        // Upper Label
        for( int i=0 ; i < 100;i ++ ) 
        {
            char str[6] = {0};
            sprintf(str, "-%d-", i);
            auto label = LabelBMFont::create(str, "fonts/bitmapFontTest.fnt");
            addChild(label);
            
            auto s = Director::getInstance()->getWinSize();

            auto p = Vec2( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
            label->setPosition( p );
            label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        }
}

std::string AtlasFastBitmap::title() const
{
    return "CCLabelBMFont";
}

std::string AtlasFastBitmap::subtitle() const
{
    return "Creating several LabelBMFont with the same .fnt file should be fast";
}

//------------------------------------------------------------------
//
// BitmapFontMultiLine
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
BitmapFontMultiLine::BitmapFontMultiLine()
{
    Size s;

    // Left
    auto label1 = LabelBMFont::create(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    auto label2 = LabelBMFont::create("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    auto label3 = LabelBMFont::create("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string BitmapFontMultiLine::title() const
{
    return "CCLabelBMFont";
}

std::string BitmapFontMultiLine::subtitle() const
{
    return "Multiline + anchor point";
}

//------------------------------------------------------------------
//
// LabelsEmpty
//
//------------------------------------------------------------------
LabelsEmpty::LabelsEmpty()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelBMFont::create("", "fonts/bitmapFontTest3.fnt");
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, s.height-100));

    // LabelTTF
    auto label2 = LabelTTF::create("", "Arial", 24);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, s.height/2));

    // LabelAtlas
    auto label3 = LabelAtlas::create("", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(Vec2(s.width/2, 0+100));

    schedule(CC_CALLBACK_1(LabelsEmpty::updateStrings, this), 1.0f, "update_strings_key");

    setEmpty = false;
}

void LabelsEmpty::updateStrings(float dt)
{
    auto label1 = static_cast<LabelBMFont*>( getChildByTag(kTagBitmapAtlas1) );
    auto label2 = static_cast<LabelTTF*>( getChildByTag(kTagBitmapAtlas2) );
    auto label3 = static_cast<LabelAtlas*>( getChildByTag(kTagBitmapAtlas3) );

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
        label3->setString("hi");

        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
        label3->setString("");

        setEmpty = false;
    }
}

std::string LabelsEmpty::title() const
{
    return "Testing empty labels";
}

std::string LabelsEmpty::subtitle() const
{
    return "3 empty labels: LabelAtlas, LabelTTF and LabelBMFont";
}

//------------------------------------------------------------------
//
// LabelBMFontHD
//
//------------------------------------------------------------------
LabelBMFontHD::LabelBMFontHD()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelBMFont::create("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));
}

std::string LabelBMFontHD::title() const
{
    return "Testing Retina Display BMFont";
}

std::string LabelBMFontHD::subtitle() const
{
    return "loading arista16 or arista16-hd";
}

//------------------------------------------------------------------
//
// LabelAtlasHD
//
//------------------------------------------------------------------
LabelAtlasHD::LabelAtlasHD()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelAtlas::create("TESTING RETINA DISPLAY", "fonts/larabie-16.plist");
    label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));
}

std::string LabelAtlasHD::title() const
{
    return "LabelAtlas with Retina Display";
}

std::string LabelAtlasHD::subtitle() const
{
    return "loading larabie-16 / larabie-16-hd";
}

//------------------------------------------------------------------
//
// LabelGlyphDesigner
//
//------------------------------------------------------------------
LabelGlyphDesigner::LabelGlyphDesigner()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);

    // LabelBMFont
    auto label1 = LabelBMFont::create("Testing Glyph Designer", "fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));
}

std::string LabelGlyphDesigner::title() const
{
    return "Testing Glyph Designer";
}

std::string LabelGlyphDesigner::subtitle() const
{
    return "You should see a font with shawdows and outline";
}

void AtlasTestScene::runThisTest()
{
    sceneIdx = -1;
    auto layer = nextAtlasAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------
LabelTTFTest::LabelTTFTest()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    auto colorLayer = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    colorLayer->setPosition(Vec2((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

    this->addChild(colorLayer);

    MenuItemFont::setFontSize(30);
    auto menu = Menu::create(
		MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFTest::setAlignmentLeft, this)),
		MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFTest::setAlignmentCenter, this)),
		MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFTest::setAlignmentRight, this)),
        nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(50, s.height / 2 - 20));
    this->addChild(menu);

    menu = Menu::create(
		MenuItemFont::create("Top", CC_CALLBACK_1(LabelTTFTest::setAlignmentTop, this)),
		MenuItemFont::create("Middle", CC_CALLBACK_1(LabelTTFTest::setAlignmentMiddle, this)),
		MenuItemFont::create("Bottom", CC_CALLBACK_1(LabelTTFTest::setAlignmentBottom, this)),
		nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    _label = nullptr;
    _horizAlign = TextHAlignment::LEFT;
    _vertAlign = TextVAlignment::TOP;

    this->updateAlignment();
}

LabelTTFTest::~LabelTTFTest()
{
    CC_SAFE_RELEASE(_label);
}

void  LabelTTFTest::updateAlignment()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    if (_label)
    {
        _label->removeFromParentAndCleanup(true);
    }

    CC_SAFE_RELEASE(_label);

    _label = LabelTTF::create(this->getCurrentAlignment(), "Marker Felt", 32,
                                  blockSize, _horizAlign, _vertAlign);
    _label->retain();

    _label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _label->setPosition(Vec2((s.width - blockSize.width) / 2, (s.height - blockSize.height)/2 ));

    this->addChild(_label);
}

void LabelTTFTest::setAlignmentLeft(Ref* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentCenter(Ref* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentRight(Ref* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentTop(Ref* sender)
{
    _vertAlign = TextVAlignment::TOP;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentMiddle(Ref* sender)
{
    _vertAlign = TextVAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentBottom(Ref* sender)
{
    _vertAlign = TextVAlignment::BOTTOM;
    this->updateAlignment();
}

const char* LabelTTFTest::getCurrentAlignment()
{
    const char* vertical = nullptr;
    const char* horizontal = nullptr;
    switch (_vertAlign) {
        case TextVAlignment::TOP:
            vertical = "Top";
            break;
        case TextVAlignment::CENTER:
            vertical = "Middle";
            break;
        case TextVAlignment::BOTTOM:
            vertical = "Bottom";
            break;
    }
    switch (_horizAlign) {
        case TextHAlignment::LEFT:
            horizontal = "Left";
            break;
        case TextHAlignment::CENTER:
            horizontal = "Center";
            break;
        case TextHAlignment::RIGHT:
            horizontal = "Right";
            break;
    }

    return String::createWithFormat("Alignment %s %s", vertical, horizontal)->getCString();
}

std::string LabelTTFTest::title() const
{
    return "Testing LabelTTF";
}

std::string LabelTTFTest::subtitle() const
{
    return "Select the buttons on the sides to change alignment";
}

LabelTTFMultiline::LabelTTFMultiline()
{
    auto s = Director::getInstance()->getWinSize();

    auto center = LabelTTF::create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
                                            "Paint Boy",
                                            32,
                                            Size(s.width/2,200),
                                            TextHAlignment::CENTER,
                                            TextVAlignment::TOP);

    center->setPosition(Vec2(s.width / 2, 150));

    addChild(center);
}

std::string LabelTTFMultiline::title() const
{
    return "Testing LabelTTF Word Wrap";
}

std::string LabelTTFMultiline::subtitle() const
{
    return "Word wrap using LabelTTF and a custom TTF font";
}

LabelTTFChinese::LabelTTFChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("中国", "Marker Felt", 30);
    label->setPosition(Vec2(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelTTFChinese::title() const
{
    return "Testing LabelTTF with Chinese character";
}

LabelBMFontChinese::LabelBMFontChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = LabelBMFont::create("中国", "fonts/bitmapFontChinese.fnt");
    label->setPosition(Vec2(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelBMFontChinese::title() const
{
    return "Testing LabelBMFont with Chinese character";
}

/// BitmapFontMultiLineAlignment

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding = 50;
static float menuItemPaddingCenter = 50;
BitmapFontMultiLineAlignment::BitmapFontMultiLineAlignment()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // ask director the the window size
    auto size = Director::getInstance()->getWinSize();

    // create and initialize a Label
    _labelShouldRetain = LabelBMFont::create(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, TextHAlignment::CENTER);
    _labelShouldRetain->retain();

    _arrowsBarShouldRetain = Sprite::create("Images/arrowsBar.png");
    _arrowsBarShouldRetain->retain();
    _arrowsShouldRetain = Sprite::create("Images/arrows.png");
    _arrowsShouldRetain->retain();

    MenuItemFont::setFontSize(20);
    auto longSentences = MenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto lineBreaks = MenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto mixed = MenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto stringMenu = Menu::create(longSentences, lineBreaks, mixed, nullptr);
    stringMenu->alignItemsVertically();

    longSentences->setColor(Color3B::RED);
    _lastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    MenuItemFont::setFontSize(30);

    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto center = MenuItemFont::create("Center", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto alignmentMenu = Menu::create(left, center, right, nullptr);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(Color3B::RED);
    _lastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    _labelShouldRetain->setPosition(Vec2(size.width/2, size.height/2));

    _arrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    _arrowsBarShouldRetain->setScaleX(arrowsWidth / this->_arrowsBarShouldRetain->getContentSize().width);
    _arrowsBarShouldRetain->setPosition(Vec2(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_labelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(Vec2(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(Vec2(size.width/2, menuItemPaddingCenter+15));

    addChild(_labelShouldRetain);
    addChild(_arrowsBarShouldRetain);
    addChild(_arrowsShouldRetain);
    addChild(stringMenu);
    addChild(alignmentMenu);
}

BitmapFontMultiLineAlignment::~BitmapFontMultiLineAlignment()
{
    this->_labelShouldRetain->release();
    this->_arrowsBarShouldRetain->release();
    this->_arrowsShouldRetain->release();
}

std::string BitmapFontMultiLineAlignment::title() const
{
    return "";
}

std::string BitmapFontMultiLineAlignment::subtitle() const
{
    return "";
}

void BitmapFontMultiLineAlignment::stringChanged(cocos2d::Ref *sender)
{
    auto item = (MenuItemFont*)sender;
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        _labelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        _labelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        _labelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::alignmentChanged(cocos2d::Ref *sender)
{
    auto item = static_cast<MenuItemFont*>(sender);
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        _labelShouldRetain->setAlignment(TextHAlignment::LEFT);
        break;
    case CenterAlign:
        _labelShouldRetain->setAlignment(TextHAlignment::CENTER);
        break;
    case RightAlign:
        _labelShouldRetain->setAlignment(TextHAlignment::RIGHT);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches[0];
    auto location = touch->getLocationInView();

    if (this->_arrowsShouldRetain->getBoundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBarShouldRetain->setVisible(true);
    }
}

void BitmapFontMultiLineAlignment::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBarShouldRetain->setVisible(false);
}

void BitmapFontMultiLineAlignment::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (! _drag)
    {
        return;
    }

    auto touch = touches[0];
    auto location = touch->getLocationInView();

    auto winSize = Director::getInstance()->getWinSize();

    this->_arrowsShouldRetain->setPosition(Vec2(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->_arrowsShouldRetain->getPosition().x - this->_labelShouldRetain->getPosition().x) * 2;

    _labelShouldRetain->setWidth(labelWidth);
}

void BitmapFontMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrowsShouldRetain->setPosition(Vec2(this->_labelShouldRetain->getPosition().x + this->_labelShouldRetain->getContentSize().width/2,
        this->_labelShouldRetain->getPosition().y));
}

/// LabelTTFOpacityTest
LabelTTFOpacityTest::LabelTTFOpacityTest()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128, 128, 128, 255));
    addChild(layer, -10);

    auto label1 = LabelTTF::create("Testing opacity", "Marker Felt", 48);
    addChild(label1);
    label1->setFontFillColor(Color3B::RED);
    label1->setPosition(Vec2(s.width/2, s.height/2));

    auto fadeOut = FadeOut::create(2);
    auto fadeIn = FadeIn::create(2);
    auto seq = Sequence::create(fadeOut, fadeIn, nullptr);
    auto forever = RepeatForever::create(seq);
    label1->runAction(forever);
}

std::string LabelTTFOpacityTest::title() const
{
    return "Testing opacity";
}

std::string LabelTTFOpacityTest::subtitle() const
{
    return "RED label, fading In and Out in the center of the screen";
}

/// BMFontOneAtlas
BMFontOneAtlas::BMFontOneAtlas()
{
    auto s = Director::getInstance()->getWinSize();

    auto label1 = LabelBMFont::create("This is Helvetica", "fonts/helvetica-32.fnt");
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/3*2));

    auto label2 = LabelBMFont::create("And this is Geneva", "fonts/geneva-32.fnt", 0, TextHAlignment::LEFT, Vec2(0, 128));
    addChild(label2);
    label2->setPosition(Vec2(s.width/2, s.height/3*1));
}

std::string BMFontOneAtlas::title() const
{
    return "CCLabelBMFont with one texture";
}

std::string BMFontOneAtlas::subtitle() const
{
    return "Using 2 .fnt definitions that share the same texture atlas.";
}

/// BMFontUnicode
BMFontUnicode::BMFontUnicode()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    std::string russian  = strings["russian"].asString();
    std::string spanish  = strings["spanish"].asString();
    std::string japanese = strings["japanese"].asString();

    auto s = Director::getInstance()->getWinSize();

    auto label1 = LabelBMFont::create(spanish, "fonts/arial-unicode-26.fnt", 200, TextHAlignment::LEFT);
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/5*4));

    auto label2 = LabelBMFont::create(chinese, "fonts/arial-unicode-26.fnt");
    addChild(label2);
    label2->setPosition(Vec2(s.width/2, s.height/5*3));

    auto label3 = LabelBMFont::create(russian, "fonts/arial-26-en-ru.fnt");
    addChild(label3);
    label3->setPosition(Vec2(s.width/2, s.height/5*2));

    auto label4 = LabelBMFont::create(japanese, "fonts/arial-unicode-26.fnt");
    addChild(label4);
    label4->setPosition(Vec2(s.width/2, s.height/5*1));
}

std::string BMFontUnicode::title() const
{
    return "CCLabelBMFont with Unicode support";
}

std::string BMFontUnicode::subtitle() const
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

// BMFontInit

BMFontInit::BMFontInit()
{
    auto s = Director::getInstance()->getWinSize();

    auto bmFont = LabelBMFont::create();

    bmFont->setFntFile("fonts/helvetica-32.fnt");
    bmFont->setString("It is working!");
    this->addChild(bmFont);
    bmFont->setPosition(Vec2(s.width/2,s.height/4*2));
}

std::string BMFontInit::title() const
{
    return "LabelBMFont create()";
}

std::string BMFontInit::subtitle() const
{
    return "Testing LabelBMFont::create() wihtout params";
}

// TTFFontInit

TTFFontInit::TTFFontInit()
{
    auto s = Director::getInstance()->getWinSize();

    auto font = LabelTTF::create();

    font->setFontName("Marker Felt");
    font->setFontSize(48);
    font->setString("It is working!");
    this->addChild(font);
    font->setPosition(Vec2(s.width/2,s.height/4*2));
}

std::string TTFFontInit::title() const
{
    return "LabelTTF create()";
}

std::string TTFFontInit::subtitle() const
{
    return "Testing LabelTTF::create() wihtout params";
}

TTFFontShadowAndStroke::TTFFontShadowAndStroke()
{
    auto layer = LayerColor::create(Color4B(0,190,0,255));
    addChild(layer, -10);
    
    auto s = Director::getInstance()->getWinSize();
    
    Color3B tintColorRed(  255, 0, 0   );
    Color3B tintColorYellow( 255, 255, 0 );
    Color3B tintColorBlue( 0, 0, 255   );
    Color3B strokeColor( 0, 0, 255  );
    Color3B strokeShadowColor( 255, 0, 0   );
    
    Size shadowOffset(12.0, 12.0);
    
    FontDefinition shadowTextDef;
    shadowTextDef._fontSize = 20;
    shadowTextDef._fontName = std::string("Marker Felt");
    
    shadowTextDef._shadow._shadowEnabled = true;
    shadowTextDef._shadow._shadowOffset  = shadowOffset;
    shadowTextDef._shadow._shadowOpacity = 1.0;
    shadowTextDef._shadow._shadowBlur    = 1.0;
    shadowTextDef._fontFillColor   = tintColorRed;
    
    // shadow only label
    auto fontShadow = LabelTTF::createWithFontDefinition("Shadow Only Red Text", shadowTextDef);
    
    // add label to the scene
    this->addChild(fontShadow);
    fontShadow->setPosition(Vec2(s.width/2,s.height/4*2.5));
    

    // create the stroke only label
    FontDefinition strokeTextDef;
    strokeTextDef._fontSize = 20;
    strokeTextDef._fontName = std::string("Marker Felt");
    
    strokeTextDef._stroke._strokeEnabled = true;
    strokeTextDef._stroke._strokeColor   = strokeColor;
    strokeTextDef._stroke._strokeSize    = 1.5;
    
    strokeTextDef._fontFillColor   = tintColorYellow;
    
    // stroke only label
    auto fontStroke = LabelTTF::createWithFontDefinition("Stroke Only Yellow Text", strokeTextDef);
    
    // add label to the scene
    this->addChild(fontStroke);
    fontStroke->setPosition(Vec2(s.width/2,s.height/4*1.8));
    
    
    
    // create the label stroke and shadow
    FontDefinition strokeShaodwTextDef;
    strokeShaodwTextDef._fontSize = 20;
    strokeShaodwTextDef._fontName = std::string("Marker Felt");
    
    strokeShaodwTextDef._stroke._strokeEnabled = true;
    strokeShaodwTextDef._stroke._strokeColor   = strokeShadowColor;
    strokeShaodwTextDef._stroke._strokeSize    = 1.5;
    
    strokeShaodwTextDef._shadow._shadowEnabled = true;
    strokeShaodwTextDef._shadow._shadowOffset  = shadowOffset;
    strokeShaodwTextDef._shadow._shadowOpacity = 1.0;
    strokeShaodwTextDef._shadow._shadowBlur    = 1.0;
    
    
    strokeShaodwTextDef._fontFillColor   = tintColorBlue;
    
    // shadow + stroke label
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    auto fontStrokeAndShadow = LabelTTF::createWithFontDefinition("Stroke && Shadow Blue Text", strokeShaodwTextDef);
#else
    auto fontStrokeAndShadow = LabelTTF::createWithFontDefinition("Stroke &Shadow Blue Text", strokeShaodwTextDef);
#endif 
    
    // add label to the scene
    this->addChild(fontStrokeAndShadow);
    fontStrokeAndShadow->setPosition(Vec2(s.width/2,s.height/4*1.1));
    
    auto buttonBG = MenuItemImage::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
    buttonBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    buttonBG->setPosition(VisibleRect::left());
    
    // create the label stroke and shadow
    strokeShaodwTextDef._fontSize = 18;
    strokeShaodwTextDef._fontName = "Marker Felt";
    
    strokeShaodwTextDef._stroke._strokeEnabled = true;
    strokeShaodwTextDef._stroke._strokeColor   = Color3B::BLACK;
    strokeShaodwTextDef._stroke._strokeSize    = 3.0f;
    
    strokeShaodwTextDef._shadow._shadowEnabled = false;
    strokeShaodwTextDef._shadow._shadowOffset  = Size(1, 1);
    strokeShaodwTextDef._shadow._shadowOpacity = 1.0;
    strokeShaodwTextDef._shadow._shadowBlur    = 0.5f;
    
    strokeShaodwTextDef._fontFillColor   = Color3B::WHITE;
    
    // shadow + stroke label
    fontStrokeAndShadow = LabelTTF::createWithFontDefinition("Test", strokeShaodwTextDef);
    
    // add label to the scene
    buttonBG->addChild(fontStrokeAndShadow);
    fontStrokeAndShadow->setPosition(Vec2(buttonBG->getContentSize().width/2, buttonBG->getContentSize().height/2));
    
    auto menu = Menu::create(buttonBG, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
}

std::string TTFFontShadowAndStroke::title() const
{
    return "CCLabelTTF  shadows + stroke";
}

std::string TTFFontShadowAndStroke::subtitle() const
{
    return "Test for support of TTF label with stroke and shadow";
}


// Issue1343

Issue1343::Issue1343()
{
    auto s = Director::getInstance()->getWinSize();

    auto bmFont = LabelBMFont::create();

    bmFont->setFntFile("fonts/font-issue1343.fnt");
    bmFont->setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'");

    this->addChild(bmFont);

    bmFont->setScale(0.3f);
    bmFont->setPosition(Vec2(s.width/2,s.height/4*2));
}

std::string Issue1343::title() const
{
    return "Issue 1343";
}

std::string Issue1343::subtitle() const
{
    return "You should see: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'";
}

LabelBMFontBounds::LabelBMFontBounds()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);
    
    // LabelBMFont
    auto label1 = LabelBMFont::create("Testing Glyph Designer", "fonts/boundsTestFont.fnt");
    
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));
    
    auto drawNode = DrawNode::create();
    
    auto labelSize = label1->getContentSize();
    auto origin = Director::getInstance()->getWinSize();
    
    origin.width = origin.width / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Vec2 vertices[4]=
    {
        Vec2(origin.width, origin.height),
        Vec2(labelSize.width + origin.width, origin.height),
        Vec2(labelSize.width + origin.width, labelSize.height + origin.height),
        Vec2(origin.width, labelSize.height + origin.height)
    };
    drawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
    addChild(drawNode);
}

std::string LabelBMFontBounds::title() const
{
    return "Testing LabelBMFont Bounds";
}

std::string LabelBMFontBounds::subtitle() const
{
    return "You should see string enclosed by a box";
}

// LabelBMFontCrashTest
void LabelBMFontCrashTest::onEnter()
{
    AtlasDemo::onEnter();
    
    auto winSize = Director::getInstance()->getWinSize();
    //Create a label and add it
    auto label1 = new (std::nothrow) LabelBMFont();
    label1->initWithString("test", "fonts/bitmapFontTest2.fnt");
    this->addChild(label1);
    // Visit will call draw where the function "ccGLBindVAO(m_uVAOname);" will be invoked.
    label1->visit();
    
    // Remove this label
    label1->removeFromParentAndCleanup(true);
    label1->release();
    
    // Create a new label and add it (then crashes)
    auto label2 = LabelBMFont::create("test 2", "fonts/bitmapFontTest.fnt");
    label2->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(label2);
}

std::string LabelBMFontCrashTest::title() const
{
    return "LabelBMFont Crash Test";
}

std::string LabelBMFontCrashTest::subtitle() const
{
    return "Should not crash.";
}

// LabelBMFontBinaryFormat
LabelBMFontBinaryFormat::LabelBMFontBinaryFormat()
{
    auto s = Director::getInstance()->getWinSize();

    auto bmFont = LabelBMFont::create();

    bmFont->setFntFile("fonts/Roboto.bmf.fnt");
    bmFont->setString("It is working!");
    this->addChild(bmFont);
    bmFont->setPosition(Vec2(s.width/2,s.height/4*2));
}

std::string LabelBMFontBinaryFormat::title() const
{
    return "LabelBMFont Binary FNT File";
}

std::string LabelBMFontBinaryFormat::subtitle() const
{
    return "This label uses font file in AngelCode binary format";
}

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
