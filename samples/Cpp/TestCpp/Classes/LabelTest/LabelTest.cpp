#include "LabelTest.h"
#include "../testResource.h"

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

CCLayer* nextAtlasAction();
CCLayer* backAtlasAction();
CCLayer* restartAtlasAction();

static int sceneIdx = -1; 

#define MAX_LAYER    27

CCLayer* createAtlasLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new LabelAtlasTest();
        case 1: return new LabelAtlasColorTest();
        case 2: return new Atlas3();
        case 3: return new Atlas4();
        case 4: return new Atlas5();
        case 5: return new Atlas6();
        case 6: return new AtlasBitmapColor();
        case 7: return new AtlasFastBitmap();
        case 8: return new BitmapFontMultiLine();
        case 9: return new LabelsEmpty();
        case 10: return new LabelBMFontHD();
        case 11: return new LabelAtlasHD();
        case 12: return new LabelGlyphDesigner();

        // Not a label test. Should be moved to Atlas test
        case 13: return new Atlas1();
        case 14: return new LabelTTFTest();
        case 15: return new LabelTTFMultiline();
        case 16: return new LabelTTFChinese();
        case 17: return new LabelBMFontChinese();
        case 18: return new BitmapFontMultiLineAlignment();
        case 19: return new LabelTTFA8Test();
        case 20: return new BMFontOneAtlas();
        case 21: return new BMFontUnicode();
        case 22: return new BMFontInit();
        case 23: return new TTFFontInit();
        case 24: return new Issue1343();
        case 25: return new LabelTTFAlignment();
        case 26: return new LabelBMFontBounds();
    }

    return NULL;
}

CCLayer* nextAtlasAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backAtlasAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartAtlasAction()
{
    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


AtlasDemo::AtlasDemo(void)
{
}

AtlasDemo::~AtlasDemo(void)
{
}

std::string AtlasDemo::title()
{
    return "No title";
}

std::string AtlasDemo::subtitle()
{
    return "";
}

void AtlasDemo::onEnter()
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

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(AtlasDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(AtlasDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(AtlasDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));;
    
    addChild(menu, 1);    
}

void AtlasDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild(restartAtlasAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild( nextAtlasAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild( backAtlasAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
Atlas1::Atlas1()
{
    m_textureAtlas = CCTextureAtlas::create(s_AtlasTest, 3); m_textureAtlas->retain();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    //
    // Notice: u,v tex coordinates are inverted
    //
    ccV3F_C4B_T2F_Quad quads[] = 
    {
        {
            {{0,0,0},ccc4(0,0,255,255),{0.0f,1.0f},},                // bottom left
            {{s.width,0,0},ccc4(0,0,255,0),{1.0f,1.0f},},            // bottom right
            {{0,s.height,0},ccc4(0,0,255,0),{0.0f,0.0f},},            // top left
            {{s.width,s.height,0},{0,0,255,255},{1.0f,0.0f},},    // top right
        },        
        {
            {{40,40,0},ccc4(255,255,255,255),{0.0f,0.2f},},            // bottom left
            {{120,80,0},ccc4(255,0,0,255),{0.5f,0.2f},},            // bottom right
            {{40,160,0},ccc4(255,255,255,255),{0.0f,0.0f},},        // top left
            {{160,160,0},ccc4(0,255,0,255),{0.5f,0.0f},},            // top right
        },

        {
            {{s.width/2,40,0},ccc4(255,0,0,255),{0.0f,1.0f},},        // bottom left
            {{s.width,40,0},ccc4(0,255,0,255),{1.0f,1.0f},},        // bottom right
            {{s.width/2-50,200,0},ccc4(0,0,255,255),{0.0f,0.0f},},        // top left
            {{s.width,100,0},ccc4(255,255,0,255),{1.0f,0.0f},},        // top right
        },
        
    };
    
    
    for( int i=0;i<3;i++) 
    {
        m_textureAtlas->updateQuad(&quads[i], i);
    }
}

Atlas1::~Atlas1()
{
    m_textureAtlas->release();
}

void Atlas1::draw()
{
    // GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
    // GL_TEXTURE_2D

    m_textureAtlas->drawQuads();

//    [textureAtlas drawNumberOfQuads:3];
    
}

std::string Atlas1::title()
{
    return "CCTextureAtlas";
}

std::string Atlas1::subtitle()
{
    return "Manual creation of CCTextureAtlas";
}

//------------------------------------------------------------------
//
// LabelAtlasTest
//
//------------------------------------------------------------------

LabelAtlasTest::LabelAtlasTest()
{
    m_time = 0;

    CCLabelAtlas* label1 = CCLabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( ccp(10,100) );
    label1->setOpacity( 200 );

    CCLabelAtlas *label2 = CCLabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( ccp(10,200) );
    label2->setOpacity( 32 );

    schedule(schedule_selector(LabelAtlasTest::step)); 
    
}

void LabelAtlasTest::step(float dt)
{
    m_time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", m_time);
    //string.format("%2.2f Test", m_time);

    CCLabelAtlas* label1 = (CCLabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);

    CCLabelAtlas*label2 = (CCLabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)m_time);
    //string.format("%d", (int)m_time);
    label2->setString(string);
}

std::string LabelAtlasTest::title()
{
    return "LabelAtlas";
}

std::string LabelAtlasTest::subtitle()
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
    CCLabelAtlas* label1 = CCLabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( ccp(10,100) );
    label1->setOpacity( 200 );
    
    CCLabelAtlas* label2 = CCLabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( ccp(10,200) );
    label2->setColor( ccRED );

    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade_in = fade->reverse();
    CCCallFunc* cb = CCCallFunc::create(this, callfunc_selector(LabelAtlasColorTest::actionFinishCallback));
    CCSequence* seq = CCSequence::create(fade, fade_in, cb, NULL);
    CCAction* repeat = CCRepeatForever::create( seq );
    label2->runAction( repeat );    

    m_time = 0;
    
    schedule( schedule_selector(LabelAtlasColorTest::step) ); //:@selector(step:)];
}

void LabelAtlasColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelAtlasColorTest::step(float dt)
{
    m_time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", m_time);
    //std::string string = std::string::createWithFormat("%2.2f Test", m_time);
    CCLabelAtlas* label1 = (CCLabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);
    
    CCLabelAtlas* label2 = (CCLabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)m_time);
    label2->setString( string );    
}

std::string LabelAtlasColorTest::title()
{
    return "CCLabelAtlas";
}

std::string LabelAtlasColorTest::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* ttf0 = CCLabelTTF::create("Alignment 0\nnew line", "Helvetica", 12,
                                          CCSizeMake(256, 32), kCCTextAlignmentLeft);
    ttf0->setPosition(ccp(s.width/2,(s.height/6)*2));
    ttf0->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf0);

    CCLabelTTF* ttf1 = CCLabelTTF::create("Alignment 1\nnew line", "Helvetica", 12,
                                          CCSizeMake(245, 32), kCCTextAlignmentCenter);
    ttf1->setPosition(ccp(s.width/2,(s.height/6)*3));
    ttf1->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf1);

    CCLabelTTF* ttf2 = CCLabelTTF::create("Alignment 2\nnew line", "Helvetica", 12,
                                          CCSizeMake(245, 32), kCCTextAlignmentRight);
    ttf2->setPosition(ccp(s.width/2,(s.height/6)*4));
    ttf2->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf2);
}

std::string LabelTTFAlignment::title()
{
    return "CCLabelTTF alignment";
}

std::string LabelTTFAlignment::subtitle()
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
    m_time = 0;

    CCLayerColor* col = CCLayerColor::create( ccc4(128,128,128,255) );
    addChild(col, -10);
    
    CCLabelBMFont* label1 = CCLabelBMFont::create("Test",  "fonts/bitmapFontTest2.fnt");
    
    // testing anchors
    label1->setAnchorPoint( ccp(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade_in = fade->reverse();
    CCSequence* seq = CCSequence::create(fade, fade_in, NULL);
    CCAction* repeat = CCRepeatForever::create(seq);
    label1->runAction(repeat);
    

    // VERY IMPORTANT
    // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
    // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
    // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
    CCLabelBMFont *label2 = CCLabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label2->setAnchorPoint( ccp(0.5f, 0.5f) );
    label2->setColor( ccRED );
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->runAction( (CCAction*)(repeat->copy()->autorelease()) );
    
    CCLabelBMFont* label3 = CCLabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label3->setAnchorPoint( ccp(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
       
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );

    schedule( schedule_selector(Atlas3::step) );//:@selector(step:)];
}

void Atlas3::step(float dt)
{
    m_time += dt;
    //std::string string;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", m_time);
    //string.format("%2.2f Test j", m_time);
    
    CCLabelBMFont *label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    CCLabelBMFont *label2 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    CCLabelBMFont *label3 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);

}

std::string Atlas3::title()
{
    return "CCLabelBMFont";
}

std::string Atlas3::subtitle()
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
    m_time = 0;

    // Upper Label
    CCLabelBMFont *label = CCLabelBMFont::create("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
    addChild(label);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    
    
    CCSprite* BChar = (CCSprite*) label->getChildByTag(0);
    CCSprite* FChar = (CCSprite*) label->getChildByTag(7);
    CCSprite* AChar = (CCSprite*) label->getChildByTag(12);
    
    
    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCAction* rot_4ever = CCRepeatForever::create(rotate);
    
    CCActionInterval* scale = CCScaleBy::create(2, 1.5f);
    CCActionInterval* scale_back = scale->reverse();
    CCSequence* scale_seq = CCSequence::create(scale, scale_back,NULL);
    CCAction* scale_4ever = CCRepeatForever::create(scale_seq);
    
    CCActionInterval* jump = CCJumpBy::create(0.5f, CCPointZero, 60, 1);
    CCAction* jump_4ever = CCRepeatForever::create(jump);
    
    CCActionInterval* fade_out = CCFadeOut::create(1);
    CCActionInterval* fade_in = CCFadeIn::create(1);
    CCSequence* seq = CCSequence::create(fade_out, fade_in, NULL);
    CCAction* fade_4ever = CCRepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    CCLabelBMFont *label2 = CCLabelBMFont::create("00.0", "fonts/bitmapFontTest.fnt");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( ccp(s.width/2.0f, 80) );
    
    CCSprite* lastChar = (CCSprite*) label2->getChildByTag(3);
    lastChar->runAction( (CCAction*)(rot_4ever->copy()->autorelease()) );
    
    schedule( schedule_selector(Atlas4::step), 0.1f);
}

void Atlas4::draw()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    ccDrawLine( ccp(0, s.height/2), ccp(s.width, s.height/2) );
    ccDrawLine( ccp(s.width/2, 0), ccp(s.width/2, s.height) );
}

void Atlas4::step(float dt)
{
    m_time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", m_time);
//     std::string string;
//     string.format("%04.1f", m_time);
    
    CCLabelBMFont* label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string Atlas4::title()
{
    return "CCLabelBMFont";
}

std::string Atlas4::subtitle()
{
    return "Using fonts as CCSprite objects. Some characters should rotate.";
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
    CCLabelBMFont *label = CCLabelBMFont::create("abcdefg", "fonts/bitmapFontTest4.fnt");
    addChild(label);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
}

std::string Atlas5::title()
{
    return "CCLabelBMFont";
}

std::string Atlas5::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* label = NULL;
    label = CCLabelBMFont::create("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2+50) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) ) ;
    
    label = CCLabelBMFont::create("fafefifofu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );

    label = CCLabelBMFont::create("aeiou", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2-50) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) ); 
}

std::string Atlas6::title()
{
    return "CCLabelBMFont";
}

std::string Atlas6::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelBMFont* label = NULL;
    label = CCLabelBMFont::create("Blue", "fonts/bitmapFontTest5.fnt");
    label->setColor( ccBLUE );
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );

    label = CCLabelBMFont::create("Red", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setColor( ccRED );

    label = CCLabelBMFont::create("G", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setColor( ccGREEN );
    label->setString("Green");
}

std::string AtlasBitmapColor::title()
{
    return "CCLabelBMFont";
}

std::string AtlasBitmapColor::subtitle()
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
            CCLabelBMFont* label = CCLabelBMFont::create(str, "fonts/bitmapFontTest.fnt");
            addChild(label);
            
            CCSize s = CCDirector::sharedDirector()->getWinSize();

            CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
            label->setPosition( p );
            label->setAnchorPoint(ccp(0.5f, 0.5f));
        }
}

std::string AtlasFastBitmap::title()
{
    return "CCLabelBMFont";
}

std::string AtlasFastBitmap::subtitle()
{
    return "Creating several CCLabelBMFont with the same .fnt file should be fast";
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
    CCSize s;

    // Left
    CCLabelBMFont *label1 = CCLabelBMFont::create(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(ccp(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    CCLabelBMFont *label2 = CCLabelBMFont::create("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    CCLabelBMFont *label3 = CCLabelBMFont::create("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(ccp(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string BitmapFontMultiLine::title()
{
    return "CCLabelBMFont";
}

std::string BitmapFontMultiLine::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("", "fonts/bitmapFontTest3.fnt");
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(ccp(s.width/2, s.height-100));

    // CCLabelTTF
    CCLabelTTF* label2 = CCLabelTTF::create("", "Arial", 24);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(ccp(s.width/2, s.height/2));

    // CCLabelAtlas
    CCLabelAtlas *label3 = CCLabelAtlas::create("", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(ccp(s.width/2, 0+100));

    schedule(schedule_selector(LabelsEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelsEmpty::updateStrings(float dt)
{
    CCLabelBMFont* label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    CCLabelTTF* label2 = (CCLabelTTF*) getChildByTag(kTagBitmapAtlas2);
    CCLabelAtlas* label3 = (CCLabelAtlas*) getChildByTag(kTagBitmapAtlas3);

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

std::string LabelsEmpty::title()
{
    return "Testing empty labels";
}

std::string LabelsEmpty::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelBMFontHD::title()
{
    return "Testing Retina Display BMFont";
}

std::string LabelBMFontHD::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelAtlas *label1 = CCLabelAtlas::create("TESTING RETINA DISPLAY", "fonts/larabie-16.plist");
    label1->setAnchorPoint(ccp(0.5f, 0.5f));

    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelAtlasHD::title()
{
    return "LabelAtlas with Retina Display";
}

std::string LabelAtlasHD::subtitle()
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *layer = CCLayerColor::create(ccc4(128,128,128,255));
    addChild(layer, -10);

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("Testing Glyph Designer", "fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelGlyphDesigner::title()
{
    return "Testing Glyph Designer";
}

std::string LabelGlyphDesigner::subtitle()
{
    return "You should see a font with shawdows and outline";
}

void AtlasTestScene::runThisTest()
{
    sceneIdx = -1;
    CCLayer* pLayer = nextAtlasAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------
LabelTTFTest::LabelTTFTest()
{
    CCSize blockSize = CCSizeMake(200, 160);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(ccp(0,0));
    colorLayer->setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

    this->addChild(colorLayer);

    CCMenuItemFont::setFontSize(30);
    CCMenu *menu = CCMenu::create(
        CCMenuItemFont::create("Left", this, menu_selector(LabelTTFTest::setAlignmentLeft)),
        CCMenuItemFont::create("Center", this, menu_selector(LabelTTFTest::setAlignmentCenter)),
        CCMenuItemFont::create("Right", this, menu_selector(LabelTTFTest::setAlignmentRight)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(ccp(50, s.height / 2 - 20));
    this->addChild(menu);

    menu = CCMenu::create(
        CCMenuItemFont::create("Top", this, menu_selector(LabelTTFTest::setAlignmentTop)),
        CCMenuItemFont::create("Middle", this, menu_selector(LabelTTFTest::setAlignmentMiddle)),
        CCMenuItemFont::create("Bottom", this, menu_selector(LabelTTFTest::setAlignmentBottom)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(ccp(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    m_plabel = NULL;
    m_eHorizAlign = kCCTextAlignmentLeft;
    m_eVertAlign = kCCVerticalTextAlignmentTop;

    this->updateAlignment();
}

LabelTTFTest::~LabelTTFTest()
{
    CC_SAFE_RELEASE(m_plabel);
}

void  LabelTTFTest::updateAlignment()
{
    CCSize blockSize = CCSizeMake(200, 160);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    if (m_plabel)
    {
        m_plabel->removeFromParentAndCleanup(true);
    }

    CC_SAFE_RELEASE(m_plabel);

    m_plabel = CCLabelTTF::create(this->getCurrentAlignment(), "Marker Felt", 32,
                                  blockSize, m_eHorizAlign, m_eVertAlign);
    m_plabel->retain();

    m_plabel->setAnchorPoint(ccp(0,0));
    m_plabel->setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height)/2 ));

    this->addChild(m_plabel);
}

void LabelTTFTest::setAlignmentLeft(CCObject* pSender)
{
    m_eHorizAlign = kCCTextAlignmentLeft;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentCenter(CCObject* pSender)
{
    m_eHorizAlign = kCCTextAlignmentCenter;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentRight(CCObject* pSender)
{
    m_eHorizAlign = kCCTextAlignmentRight;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentTop(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentTop;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentMiddle(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentCenter;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentBottom(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentBottom;
    this->updateAlignment();
}

const char* LabelTTFTest::getCurrentAlignment()
{
    const char* vertical = NULL;
    const char* horizontal = NULL;
    switch (m_eVertAlign) {
        case kCCVerticalTextAlignmentTop:
            vertical = "Top";
            break;
        case kCCVerticalTextAlignmentCenter:
            vertical = "Middle";
            break;
        case kCCVerticalTextAlignmentBottom:
            vertical = "Bottom";
            break;
    }
    switch (m_eHorizAlign) {
        case kCCTextAlignmentLeft:
            horizontal = "Left";
            break;
        case kCCTextAlignmentCenter:
            horizontal = "Center";
            break;
        case kCCTextAlignmentRight:
            horizontal = "Right";
            break;
    }

    return CCString::createWithFormat("Alignment %s %s", vertical, horizontal)->getCString();
}

string LabelTTFTest::title()
{
    return "Testing CCLabelTTF";
}

string LabelTTFTest::subtitle()
{
    return "Select the buttons on the sides to change alignment";
}

LabelTTFMultiline::LabelTTFMultiline()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *center = CCLabelTTF::create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
                                            "Paint Boy",
                                            32,
                                            CCSizeMake(s.width/2,200),
                                            kCCTextAlignmentCenter,
                                            kCCVerticalTextAlignmentTop);

    center->setPosition(ccp(s.width / 2, 150));

    addChild(center);
}

string LabelTTFMultiline::title()
{
    return "Testing CCLabelTTF Word Wrap";
}

string LabelTTFMultiline::subtitle()
{
    return "Word wrap using CCLabelTTF and a custom TTF font";
}

LabelTTFChinese::LabelTTFChinese()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *pLable = CCLabelTTF::create("中国", "Marker Felt", 30);
    pLable->setPosition(ccp(size.width / 2, size.height /2));
    this->addChild(pLable);
}

string LabelTTFChinese::title()
{
    return "Testing CCLabelTTF with Chinese character";
}

LabelBMFontChinese::LabelBMFontChinese()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelBMFont* pLable = CCLabelBMFont::create("中国", "fonts/bitmapFontChinese.fnt");
    pLable->setPosition(ccp(size.width / 2, size.height /2));
    this->addChild(pLable);
}

string LabelBMFontChinese::title()
{
    return "Testing CCLabelBMFont with Chinese character";
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
    this->setTouchEnabled(true);

    // ask director the the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // create and initialize a Label
    this->m_pLabelShouldRetain = CCLabelBMFont::create(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, kCCTextAlignmentCenter);
    this->m_pLabelShouldRetain->retain();

    this->m_pArrowsBarShouldRetain = CCSprite::create("Images/arrowsBar.png");
    this->m_pArrowsBarShouldRetain->retain();
    this->m_pArrowsShouldRetain = CCSprite::create("Images/arrows.png");
    this->m_pArrowsShouldRetain->retain();

    CCMenuItemFont::setFontSize(20);
    CCMenuItemFont *longSentences = CCMenuItemFont::create("Long Flowing Sentences", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
    CCMenuItemFont *lineBreaks = CCMenuItemFont::create("Short Sentences With Intentional Line Breaks", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
    CCMenuItemFont *mixed = CCMenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
    CCMenu *stringMenu = CCMenu::create(longSentences, lineBreaks, mixed, NULL);
    stringMenu->alignItemsVertically();

    longSentences->setColor(ccRED);
    m_pLastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    CCMenuItemFont::setFontSize(30);

    CCMenuItemFont *left = CCMenuItemFont::create("Left", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
    CCMenuItemFont *center = CCMenuItemFont::create("Center", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
    CCMenuItemFont *right = CCMenuItemFont::create("Right", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
    CCMenu *alignmentMenu = CCMenu::create(left, center, right, NULL);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(ccRED);
    m_pLastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->m_pLabelShouldRetain->setPosition(ccp(size.width/2, size.height/2));

    this->m_pArrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->m_pArrowsBarShouldRetain->setScaleX(arrowsWidth / this->m_pArrowsBarShouldRetain->getContentSize().width);
    this->m_pArrowsBarShouldRetain->setPosition(ccp(((ArrowsMax + ArrowsMin) / 2) * size.width, this->m_pLabelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(ccp(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(ccp(size.width/2, menuItemPaddingCenter+15));

    this->addChild(this->m_pLabelShouldRetain);
    this->addChild(this->m_pArrowsBarShouldRetain);
    this->addChild(this->m_pArrowsShouldRetain);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);
}

BitmapFontMultiLineAlignment::~BitmapFontMultiLineAlignment()
{
    this->m_pLabelShouldRetain->release();
    this->m_pArrowsBarShouldRetain->release();
    this->m_pArrowsShouldRetain->release();
}

std::string BitmapFontMultiLineAlignment::title()
{
    return "";
}

std::string BitmapFontMultiLineAlignment::subtitle()
{
    return "";
}

void BitmapFontMultiLineAlignment::stringChanged(cocos2d::CCObject *sender)
{
    CCMenuItemFont *item = (CCMenuItemFont*)sender;
    item->setColor(ccRED);
    this->m_pLastAlignmentItem->setColor(ccWHITE);
    this->m_pLastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        this->m_pLabelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        this->m_pLabelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        this->m_pLabelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::alignmentChanged(cocos2d::CCObject *sender)
{
    CCMenuItemFont *item = (CCMenuItemFont*)sender;
    item->setColor(ccRED);
    this->m_pLastAlignmentItem->setColor(ccWHITE);
    this->m_pLastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        this->m_pLabelShouldRetain->setAlignment(kCCTextAlignmentLeft);
        break;
    case CenterAlign:
        this->m_pLabelShouldRetain->setAlignment(kCCTextAlignmentCenter);
        break;
    case RightAlign:
        this->m_pLabelShouldRetain->setAlignment(kCCTextAlignmentRight);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();

    if (this->m_pArrowsShouldRetain->boundingBox().containsPoint(location))
    {
        m_drag = true;
        this->m_pArrowsBarShouldRetain->setVisible(true);
    }
}

void BitmapFontMultiLineAlignment::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    m_drag = false;
    this->snapArrowsToEdge();

    this->m_pArrowsBarShouldRetain->setVisible(false);
}

void BitmapFontMultiLineAlignment::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (! m_drag)
    {
        return;
    }

    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    this->m_pArrowsShouldRetain->setPosition(ccp(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->m_pArrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->m_pArrowsShouldRetain->getPosition().x - this->m_pLabelShouldRetain->getPosition().x) * 2;

    this->m_pLabelShouldRetain->setWidth(labelWidth);
}

void BitmapFontMultiLineAlignment::snapArrowsToEdge()
{
    this->m_pArrowsShouldRetain->setPosition(ccp(this->m_pLabelShouldRetain->getPosition().x + this->m_pLabelShouldRetain->getContentSize().width/2,
        this->m_pLabelShouldRetain->getPosition().y));
}

/// LabelTTFA8Test
LabelTTFA8Test::LabelTTFA8Test()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *layer = CCLayerColor::create(ccc4(128, 128, 128, 255));
    addChild(layer, -10);

    // CCLabelBMFont
    CCLabelTTF *label1 = CCLabelTTF::create("Testing A8 Format", "Marker Felt", 48);
    addChild(label1);
    label1->setColor(ccRED);
    label1->setPosition(ccp(s.width/2, s.height/2));

    CCFadeOut *fadeOut = CCFadeOut::create(2);
    CCFadeIn *fadeIn = CCFadeIn::create(2);
    CCSequence *seq = CCSequence::create(fadeOut, fadeIn, NULL);
    CCRepeatForever *forever = CCRepeatForever::create(seq);
    label1->runAction(forever);
}

std::string LabelTTFA8Test::title()
{
    return "Testing A8 Format";
}

std::string LabelTTFA8Test::subtitle()
{
    return "RED label, fading In and Out in the center of the screen";
}

/// BMFontOneAtlas
BMFontOneAtlas::BMFontOneAtlas()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont *label1 = CCLabelBMFont::create("This is Helvetica", "fonts/helvetica-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, CCPointZero);
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/3*2));

    CCLabelBMFont *label2 = CCLabelBMFont::create("And this is Geneva", "fonts/geneva-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, ccp(0, 128));
    addChild(label2);
    label2->setPosition(ccp(s.width/2, s.height/3*1));
}

std::string BMFontOneAtlas::title()
{
    return "CCLabelBMFont with one texture";
}

std::string BMFontOneAtlas::subtitle()
{
    return "Using 2 .fnt definitions that share the same texture atlas.";
}

/// BMFontUnicode
BMFontUnicode::BMFontUnicode()
{
    CCDictionary *strings = CCDictionary::createWithContentsOfFile("fonts/strings.xml");

    const char *chinese  = ((CCString*)strings->objectForKey("chinese1"))->m_sString.c_str();
    const char *japanese = ((CCString*)strings->objectForKey("japanese"))->m_sString.c_str();
    const char *russian  = ((CCString*)strings->objectForKey("russian"))->m_sString.c_str();
    const char *spanish  = ((CCString*)strings->objectForKey("spanish"))->m_sString.c_str();


    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont *label1 = CCLabelBMFont::create(spanish, "fonts/arial-unicode-26.fnt", 200, kCCTextAlignmentLeft);
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/5*4));

    CCLabelBMFont *label2 = CCLabelBMFont::create(chinese, "fonts/arial-unicode-26.fnt");
    addChild(label2);
    label2->setPosition(ccp(s.width/2, s.height/5*3));

    CCLabelBMFont *label3 = CCLabelBMFont::create(russian, "fonts/arial-26-en-ru.fnt");
    addChild(label3);
    label3->setPosition(ccp(s.width/2, s.height/5*2));

    CCLabelBMFont *label4 = CCLabelBMFont::create(japanese, "fonts/arial-unicode-26.fnt");
    addChild(label4);
    label4->setPosition(ccp(s.width/2, s.height/5*1));
}

std::string BMFontUnicode::title()
{
    return "CCLabelBMFont with Unicode support";
}

std::string BMFontUnicode::subtitle()
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

// BMFontInit

BMFontInit::BMFontInit()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* bmFont = new CCLabelBMFont();
    bmFont->init();
    bmFont->autorelease();
    //CCLabelBMFont* bmFont = [CCLabelBMFont create:@"Foo" fntFile:@"arial-unicode-26.fnt"];
    bmFont->setFntFile("fonts/helvetica-32.fnt");
    bmFont->setString("It is working!");
    this->addChild(bmFont);
    bmFont->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string BMFontInit::title()
{
    return "CCLabelBMFont init";
}

std::string BMFontInit::subtitle()
{
    return "Test for support of init method without parameters.";
}

// TTFFontInit

TTFFontInit::TTFFontInit()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* font = new CCLabelTTF();
    font->init();
    font->autorelease();
    font->setFontName("Marker Felt");
    font->setFontSize(48);
    font->setString("It is working!");
    this->addChild(font);
    font->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string TTFFontInit::title()
{
    return "CCLabelTTF init";
}

std::string TTFFontInit::subtitle()
{
    return "Test for support of init method without parameters.";
}


// Issue1343

Issue1343::Issue1343()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* bmFont = new CCLabelBMFont();
    bmFont->init();
    bmFont->setFntFile("fonts/font-issue1343.fnt");
    bmFont->setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'");
    this->addChild(bmFont);
    bmFont->release();
    bmFont->setScale(0.3f);

    bmFont->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string Issue1343::title()
{
    return "Issue 1343";
}

std::string Issue1343::subtitle()
{
    return "You should see: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'";
}

LabelBMFontBounds::LabelBMFontBounds()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor *layer = CCLayerColor::create(ccc4(128,128,128,255));
    addChild(layer, -10);
    
    // CCLabelBMFont
    label1 = CCLabelBMFont::create("Testing Glyph Designer", "fonts/boundsTestFont.fnt");
    
    
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

string LabelBMFontBounds::title()
{
    return "Testing LabelBMFont Bounds";
}

string LabelBMFontBounds::subtitle()
{
    return "You should see string enclosed by a box";
}

void LabelBMFontBounds::draw()
{
    CCSize labelSize = label1->getContentSize();
    CCSize origin = CCDirector::sharedDirector()->getWinSize();
    
    origin.width = origin.width / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    CCPoint vertices[4]=
    {
        ccp(origin.width, origin.height),
        ccp(labelSize.width + origin.width, origin.height),
        ccp(labelSize.width + origin.width, labelSize.height + origin.height),
        ccp(origin.width, labelSize.height + origin.height)
    };
    ccDrawPoly(vertices, 4, true);
}

