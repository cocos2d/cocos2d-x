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

#define MAX_LAYER	22

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

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 1);
	label->setPosition( ccp(s.width/2, s.height-50) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition( ccp(s.width/2, s.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemWithNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(AtlasDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemWithNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(AtlasDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemWithNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(AtlasDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( ccp( s.width/2 - 100,30) );
	item2->setPosition( ccp( s.width/2, 30) );
	item3->setPosition( ccp( s.width/2 + 100,30) );
	
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
	m_textureAtlas = CCTextureAtlas::textureAtlasWithFile(s_AtlasTest, 3); m_textureAtlas->retain();
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	//
	// Notice: u,v tex coordinates are inverted
	//
	ccV3F_C4B_T2F_Quad quads[] = 
	{
		{
			{{0,0,0},ccc4(0,0,255,255),{0.0f,1.0f},},				// bottom left
			{{s.width,0,0},ccc4(0,0,255,0),{1.0f,1.0f},},			// bottom right
			{{0,s.height,0},ccc4(0,0,255,0),{0.0f,0.0f},},			// top left
			{{s.width,s.height,0},{0,0,255,255},{1.0f,0.0f},},	// top right
		},		
		{
			{{40,40,0},ccc4(255,255,255,255),{0.0f,0.2f},},			// bottom left
			{{120,80,0},ccc4(255,0,0,255),{0.5f,0.2f},},			// bottom right
			{{40,160,0},ccc4(255,255,255,255),{0.0f,0.0f},},		// top left
			{{160,160,0},ccc4(0,255,0,255),{0.5f,0.0f},},			// top right
		},

		{
			{{s.width/2,40,0},ccc4(255,0,0,255),{0.0f,1.0f},},		// bottom left
			{{s.width,40,0},ccc4(0,255,0,255),{1.0f,1.0f},},		// bottom right
			{{s.width/2-50,200,0},ccc4(0,0,255,255),{0.0f,0.0f},},		// top left
			{{s.width,100,0},ccc4(255,255,0,255),{1.0f,0.0f},},		// top right
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

//	[textureAtlas drawNumberOfQuads:3];
	
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

	CCLabelAtlas* label1 = CCLabelAtlas::labelWithString("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label1, 0, kTagSprite1);
	label1->setPosition( ccp(10,100) );
	label1->setOpacity( 200 );

	CCLabelAtlas *label2 = CCLabelAtlas::labelWithString("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label2, 0, kTagSprite2);
	label2->setPosition( ccp(10,200) );
	label2->setOpacity( 32 );

	schedule(schedule_selector(LabelAtlasTest::step)); 
	
}

void LabelAtlasTest::step(ccTime dt)
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
	CCLabelAtlas* label1 = CCLabelAtlas::labelWithString("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label1, 0, kTagSprite1);
	label1->setPosition( ccp(10,100) );
	label1->setOpacity( 200 );
	
	CCLabelAtlas* label2 = CCLabelAtlas::labelWithString("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label2, 0, kTagSprite2);
	label2->setPosition( ccp(10,200) );
	label2->setColor( ccRED );

	CCActionInterval* fade = CCFadeOut::actionWithDuration(1.0f);
	CCActionInterval* fade_in = fade->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(fade, fade_in, NULL);
	CCAction* repeat = CCRepeatForever::actionWithAction( (CCActionInterval*)seq );
	label2->runAction( repeat );	

	m_time = 0;
	
	schedule( schedule_selector(LabelAtlasColorTest::step) ); //:@selector(step:)];
}

void LabelAtlasColorTest::step(ccTime dt)
{
	m_time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", m_time);
	//std::string string = std::string::stringWithFormat("%2.2f Test", m_time);
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

	CCLayerColor* col = CCLayerColor::layerWithColor( ccc4(128,128,128,255) );
	addChild(col, -10);
	
	CCLabelBMFont* label1 = CCLabelBMFont::labelWithString("Test",  "fonts/bitmapFontTest2.fnt");
	
	// testing anchors
	label1->setAnchorPoint( ccp(0,0) );
	addChild(label1, 0, kTagBitmapAtlas1);
	CCActionInterval* fade = CCFadeOut::actionWithDuration(1.0f);
	CCActionInterval* fade_in = fade->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(fade, fade_in, NULL);
	CCAction* repeat = CCRepeatForever::actionWithAction((CCActionInterval*)seq);
	label1->runAction(repeat);
	

	// VERY IMPORTANT
	// color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
	// If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
	// Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
	CCLabelBMFont *label2 = CCLabelBMFont::labelWithString("Test", "fonts/bitmapFontTest2.fnt");
	// testing anchors
	label2->setAnchorPoint( ccp(0.5f, 0.5f) );
	label2->setColor( ccRED );
	addChild(label2, 0, kTagBitmapAtlas2);
	label2->runAction( (CCAction*)(repeat->copy()->autorelease()) );
	
	CCLabelBMFont* label3 = CCLabelBMFont::labelWithString("Test", "fonts/bitmapFontTest2.fnt");
	// testing anchors
	label3->setAnchorPoint( ccp(1,1) );
	addChild(label3, 0, kTagBitmapAtlas3);
	
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();	
	label1->setPosition( ccp( 0,0) );
	label2->setPosition( ccp( s.width/2, s.height/2) );
	label3->setPosition( ccp( s.width, s.height) );

	schedule( schedule_selector(Atlas3::step) );//:@selector(step:)];
}

void Atlas3::step(ccTime dt)
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
	CCLabelBMFont *label = CCLabelBMFont::labelWithString("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
	addChild(label);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	label->setPosition( ccp(s.width/2, s.height/2) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
	
	
	CCSprite* BChar = (CCSprite*) label->getChildByTag(0);
	CCSprite* FChar = (CCSprite*) label->getChildByTag(7);
	CCSprite* AChar = (CCSprite*) label->getChildByTag(12);
	
	
	CCActionInterval* rotate = CCRotateBy::actionWithDuration(2, 360);
	CCAction* rot_4ever = CCRepeatForever::actionWithAction(rotate);
	
	CCActionInterval* scale = CCScaleBy::actionWithDuration(2, 1.5f);
	CCActionInterval* scale_back = scale->reverse();
	CCFiniteTimeAction* scale_seq = CCSequence::actions(scale, scale_back,NULL);
	CCAction* scale_4ever = CCRepeatForever::actionWithAction((CCActionInterval*)scale_seq);
	
	CCActionInterval* jump = CCJumpBy::actionWithDuration(0.5f, CCPointZero, 60, 1);
	CCAction* jump_4ever = CCRepeatForever::actionWithAction(jump);
	
	CCActionInterval* fade_out = CCFadeOut::actionWithDuration(1);
	CCActionInterval* fade_in = CCFadeIn::actionWithDuration(1);
	CCFiniteTimeAction* seq = CCSequence::actions(fade_out, fade_in, NULL);
	CCAction* fade_4ever = CCRepeatForever::actionWithAction((CCActionInterval*)seq);
	
	BChar->runAction(rot_4ever);
	BChar->runAction(scale_4ever);
	FChar->runAction(jump_4ever);
	AChar->runAction(fade_4ever);
	
	
	// Bottom Label
	CCLabelBMFont *label2 = CCLabelBMFont::labelWithString("00.0", "fonts/bitmapFontTest.fnt");
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

void Atlas4::step(ccTime dt)
{
	m_time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", m_time);
// 	std::string string;
// 	string.format("%04.1f", m_time);
	
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
	CCLabelBMFont *label = CCLabelBMFont::labelWithString("abcdefg", "fonts/bitmapFontTest4.fnt");
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
	label = CCLabelBMFont::labelWithString("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/2+50) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) ) ;
	
	label = CCLabelBMFont::labelWithString("fafefifofu", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/2) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );

	label = CCLabelBMFont::labelWithString("aeiou", "fonts/bitmapFontTest5.fnt");
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
	label = CCLabelBMFont::labelWithString("Blue", "fonts/bitmapFontTest5.fnt");
	label->setColor( ccBLUE );
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/4) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );

	label = CCLabelBMFont::labelWithString("Red", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, 2*s.height/4) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
	label->setColor( ccRED );

	label = CCLabelBMFont::labelWithString("G", "fonts/bitmapFontTest5.fnt");
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
			CCLabelBMFont* label = CCLabelBMFont::labelWithString(str, "fonts/bitmapFontTest.fnt");
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
    CCLabelBMFont *label1 = CCLabelBMFont::labelWithString(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(ccp(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    CCLabelBMFont *label2 = CCLabelBMFont::labelWithString("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    CCLabelBMFont *label3 = CCLabelBMFont::labelWithString("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(ccp(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    s = CCDirector::sharedDirector()->getWinSize();
    label1->setPosition(ccp( 0,0));
    label2->setPosition(ccp( s.width/2, s.height/2));
    label3->setPosition(ccp( s.width, s.height));
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
    CCLabelBMFont *label1 = CCLabelBMFont::labelWithString("", "fonts/bitmapFontTest3.fnt");
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(ccp(s.width/2, s.height-100));

    // CCLabelTTF
    CCLabelTTF* label2 = CCLabelTTF::labelWithString("", "Arial", 24);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(ccp(s.width/2, s.height/2));

    // CCLabelAtlas
    CCLabelAtlas *label3 = CCLabelAtlas::labelWithString("", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(ccp(s.width/2, 0+100));

    schedule(schedule_selector(LabelsEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelsEmpty::updateStrings(ccTime dt)
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
    CCLabelBMFont *label1 = CCLabelBMFont::labelWithString("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
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
    CCLabelAtlas *label1 = CCLabelAtlas::labelWithString("TESTING RETINA DISPLAY", "fonts/larabie-16.png", 10, 20, 'A');
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

    CCLayerColor *layer = CCLayerColor::layerWithColor(ccc4(128,128,128,255));
    addChild(layer, -10);

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::labelWithString("Testing Glyph Designer", "fonts/futura-48.fnt");
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
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// CCLabelBMFont
	CCLabelTTF *left = CCLabelTTF::labelWithString("align left", CCSizeMake(s.width, 50), CCTextAlignmentLeft, "Marker Felt", 32);
	CCLabelTTF *center = CCLabelTTF::labelWithString("align center", CCSizeMake(s.width, 50), CCTextAlignmentCenter, "Marker Felt", 32);
	CCLabelTTF *right = CCLabelTTF::labelWithString("align right", CCSizeMake(s.width, 50), CCTextAlignmentRight, "Marker Felt", 32);

	left->setPosition(ccp(s.width / 2, 200));
	center->setPosition(ccp(s.width / 2, 150));
	right->setPosition(ccp(s.width / 2, 100));

	addChild(left);
	addChild(center);
	addChild(right);
}

string LabelTTFTest::title()
{
	return "Testing CCLabelTTF";
}

string LabelTTFTest::subtitle()
{
	return "You should see 3 labels aligned left, center and right";
}

LabelTTFMultiline::LabelTTFMultiline()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// CCLabelBMFont
	CCLabelTTF *center = CCLabelTTF::labelWithString("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
		CCSizeMake(s.width / 2, 200), CCTextAlignmentCenter, "MarkerFelt.ttc", 32);
	center->setPosition(ccp(s.width / 2, 150));

	addChild(center);
}

string LabelTTFMultiline::title()
{
	return "Testing CCLabelTTF Word Wrap";
}

string LabelTTFMultiline::subtitle()
{
	return "Word wrap using CCLabelTTF";
}

LabelTTFChinese::LabelTTFChinese()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *pLable = CCLabelTTF::labelWithString("中国", "Marker Felt", 30);
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
    CCLabelBMFont* pLable = CCLabelBMFont::labelWithString("中国", "fonts/bitmapFontChinese.fnt");
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
	this->setIsTouchEnabled(true);

	// ask director the the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// create and initialize a Label
	this->m_pLabelShouldRetain = CCLabelBMFont::labelWithString(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, CCTextAlignmentCenter);
	this->m_pLabelShouldRetain->retain();

	this->m_pArrowsBarShouldRetain = CCSprite::spriteWithFile("Images/arrowsBar.png");
	this->m_pArrowsBarShouldRetain->retain();
	this->m_pArrowsShouldRetain = CCSprite::spriteWithFile("Images/arrows.png");
	this->m_pArrowsShouldRetain->retain();

	CCMenuItemFont::setFontSize(20);
	CCMenuItemFont *longSentences = CCMenuItemFont::itemWithString("Long Flowing Sentences", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
	CCMenuItemFont *lineBreaks = CCMenuItemFont::itemWithString("Short Sentences With Intentional Line Breaks", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
	CCMenuItemFont *mixed = CCMenuItemFont::itemWithString("Long Sentences Mixed With Intentional Line Breaks", this, menu_selector(BitmapFontMultiLineAlignment::stringChanged));
	CCMenu *stringMenu = CCMenu::menuWithItems(longSentences, lineBreaks, mixed, NULL);
	stringMenu->alignItemsVertically();

	longSentences->setColor(ccRED);
	m_pLastSentenceItem = longSentences;
	longSentences->setTag(LineBreaks);
	lineBreaks->setTag(LineBreaks);
	mixed->setTag(Mixed);

	CCMenuItemFont::setFontSize(30);

	CCMenuItemFont *left = CCMenuItemFont::itemWithString("Left", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
	CCMenuItemFont *center = CCMenuItemFont::itemWithString("Center", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
	CCMenuItemFont *right = CCMenuItemFont::itemWithString("Right", this, menu_selector(BitmapFontMultiLineAlignment::alignmentChanged));
	CCMenu *alignmentMenu = CCMenu::menuWithItems(left, center, right, NULL);
	alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

	center->setColor(ccRED);
	m_pLastAlignmentItem = center;
	left->setTag(LeftAlign);
	center->setTag(CenterAlign);
	right->setTag(RightAlign);

	// position the label on the center of the screen
	this->m_pLabelShouldRetain->setPosition(ccp(size.width/2, size.height/2));

	this->m_pArrowsBarShouldRetain->setIsVisible(false);

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
		this->m_pLabelShouldRetain->setAlignment(CCTextAlignmentLeft);
		break;
	case CenterAlign:
		this->m_pLabelShouldRetain->setAlignment(CCTextAlignmentCenter);
		break;
	case RightAlign:
		this->m_pLabelShouldRetain->setAlignment(CCTextAlignmentRight);
		break;

	default:
		break;
	}

	this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint location = touch->locationInView();

	if (CCRect::CCRectContainsPoint(this->m_pArrowsShouldRetain->boundingBox(), location))
	{
		m_drag = true;
		this->m_pArrowsBarShouldRetain->setIsVisible(true);
	}
}

void BitmapFontMultiLineAlignment::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	m_drag = false;
	this->snapArrowsToEdge();

	this->m_pArrowsBarShouldRetain->setIsVisible(false);
}

void BitmapFontMultiLineAlignment::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (! m_drag)
	{
		return;
	}

	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint location = touch->locationInView();

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

	CCLayerColor *layer = CCLayerColor::layerWithColor(ccc4(128, 128, 128, 255));
	addChild(layer, -10);

	// CCLabelBMFont
	CCLabelTTF *label1 = CCLabelTTF::labelWithString("Testing A8 Format", "Marker Felt", 48);
	addChild(label1);
	label1->setColor(ccRED);
	label1->setPosition(ccp(s.width/2, s.height/2));

	CCFadeOut *fadeOut = CCFadeOut::actionWithDuration(2);
	CCFadeIn *fadeIn = CCFadeIn::actionWithDuration(2);
	CCFiniteTimeAction *seq = CCSequence::actions(fadeOut, fadeIn, NULL);
	CCRepeatForever *forever = CCRepeatForever::actionWithAction((CCActionInterval *)seq);
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

	CCLabelBMFont *label1 = CCLabelBMFont::labelWithString("This is Helvetica", "fonts/helvetica-32.fnt", kCCLabelAutomaticWidth, CCTextAlignmentLeft, CCPointZero);
    addChild(label1);
	label1->setPosition(ccp(s.width/2, s.height/3*2));

	CCLabelBMFont *label2 = CCLabelBMFont::labelWithString("And this is Geneva", "fonts/geneva-32.fnt", kCCLabelAutomaticWidth, CCTextAlignmentLeft, ccp(0, 128));
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
	CCDictionary *strings = CCDictionary::dictionaryWithContentsOfFile("fonts/strings.xml");
	const char *chinese = ((CCString*)strings->objectForKey("chinese1"))->m_sString.c_str();
	const char *japanese = ((CCString*)strings->objectForKey("japanese"))->m_sString.c_str();
	const char *spanish = ((CCString*)strings->objectForKey("spanish"))->m_sString.c_str();


	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelBMFont *label1 = CCLabelBMFont::labelWithString(spanish, "fonts/arial-unicode-26.fnt", 200, CCTextAlignmentLeft);
    addChild(label1);
	label1->setPosition(ccp(s.width/2, s.height/4*3));

	CCLabelBMFont *label2 = CCLabelBMFont::labelWithString(chinese, "fonts/arial-unicode-26.fnt");
	addChild(label2);
	label2->setPosition(ccp(s.width/2, s.height/4*2));

	CCLabelBMFont *label3 = CCLabelBMFont::labelWithString(japanese, "fonts/arial-unicode-26.fnt");
	addChild(label3);
	label3->setPosition(ccp(s.width/2, s.height/4*1));
}

std::string BMFontUnicode::title()
{
	return "CCLabelBMFont with Unicode support";
}

std::string BMFontUnicode::subtitle()
{
	return "You should see 3 differnt labels: In Spanish, Chinese and Korean";
}
