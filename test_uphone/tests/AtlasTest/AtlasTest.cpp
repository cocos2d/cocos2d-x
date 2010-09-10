#include "AtlasTest.h"
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

static int sceneIdx = -1; 

#define MAX_LAYER	9

CCLayer* createAtlasLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new Atlas1();
		case 1: return new LabelAtlasTest();
		case 2: return new LabelAtlasColorTest();
		case 3: return new Atlas3();
		case 4: return new Atlas4();
		case 5: return new Atlas5();
		case 6: return new Atlas6();
		case 7: return new AtlasBitmapColor();
		case 8: return new AtlasFastBitmap();
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

	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 1);
	label->setPosition( ccp(s.width/2, s.height-50) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabel* l = CCLabel::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition( ccp(s.width/2, s.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(AtlasDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(AtlasDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(AtlasDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CGPointZero );
	item1->setPosition( ccp( s.width/2 - 100,30) );
	item2->setPosition( ccp( s.width/2, 30) );
	item3->setPosition( ccp( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void AtlasDemo::restartCallback(NSObject* pSender)
{
	CCScene* s = new AtlasTestScene();
	s->addChild(restartAtlasAction()); 

	CCDirector::getSharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::nextCallback(NSObject* pSender)
{
	CCScene* s = new AtlasTestScene();
	s->addChild( nextAtlasAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::backCallback(NSObject* pSender)
{
	CCScene* s = new AtlasTestScene();
	s->addChild( backAtlasAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
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
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	//
	// Notice: u,v tex coordinates are inverted
	//
	ccV3F_C4B_T2F_Quad quads[] = 
	{
		{
			{{0,0,0},{0,0,255,255},{0.0f,1.0f},},				// bottom left
			{{s.width,0,0},{0,0,255,0},{1.0f,1.0f},},			// bottom right
			{{0,s.height,0},{0,0,255,0},{0.0f,0.0f},},			// top left
			{{s.width,s.height,0},{0,0,255,255},{1.0f,0.0f},},	// top right
		},		
		{
			{{40,40,0},{255,255,255,255},{0.0f,0.2f},},			// bottom left
			{{120,80,0},{255,0,0,255},{0.5f,0.2f},},			// bottom right
			{{40,160,0},{255,255,255,255},{0.0f,0.0f},},		// top left
			{{160,160,0},{0,255,0,255},{0.5f,0.0f},},			// top right
		},

		{
			{{s.width/2,40,0},{255,0,0,255},{0.0f,1.0f},},		// bottom left
			{{s.width,40,0},{0,255,0,255},{1.0f,1.0f},},		// bottom right
			{{s.width/2-50,200,0},{0,0,255,255},{0.0f,0.0f},},		// top left
			{{s.width,100,0},{255,255,0,255},{1.0f,0.0f},},		// top right
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

	CCLabelAtlas* label1 = CCLabelAtlas::labelAtlasWithString("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label1, 0, kTagSprite1);
	label1->setPosition( ccp(10,100) );
	label1->setOpacity( 200 );

	CCLabelAtlas *label2 = CCLabelAtlas::labelAtlasWithString("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
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
	CCLabelAtlas* label1 = CCLabelAtlas::labelAtlasWithString("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label1, 0, kTagSprite1);
	label1->setPosition( ccp(10,100) );
	label1->setOpacity( 200 );
	
	CCLabelAtlas* label2 = CCLabelAtlas::labelAtlasWithString("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	addChild(label2, 0, kTagSprite2);
	label2->setPosition( ccp(10,200) );
	label2->setColor( ccRED );

	CCIntervalAction* fade = CCFadeOut::actionWithDuration(1.0f);
	CCIntervalAction* fade_in = fade->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(fade, fade_in, NULL);
	CCAction* repeat = CCRepeatForever::actionWithAction( (CCIntervalAction*)seq );
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
//------------------------------------------------------------------
Atlas3::Atlas3()
{
	m_time = 0;

	CCColorLayer* col = CCColorLayer::layerWithColor( ccc4(128,128,128,255) );
	addChild(col, -10);
	
	CCBitmapFontAtlas* label1 = CCBitmapFontAtlas::bitmapFontAtlasWithString("Test",  "fonts/bitmapFontTest2.fnt");
	
	// testing anchors
	label1->setAnchorPoint( ccp(0,0) );
	addChild(label1, 0, kTagBitmapAtlas1);
	CCIntervalAction* fade = CCFadeOut::actionWithDuration(1.0f);
	CCIntervalAction* fade_in = fade->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(fade, fade_in, NULL);
	CCAction* repeat = CCRepeatForever::actionWithAction((CCIntervalAction*)seq);
	label1->runAction(repeat);
	

	// VERY IMPORTANT
	// color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
	// If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
	// Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
	CCBitmapFontAtlas *label2 = CCBitmapFontAtlas::bitmapFontAtlasWithString("Test", "fonts/bitmapFontTest2.fnt");
	// testing anchors
	label2->setAnchorPoint( ccp(0.5f, 0.5f) );
	label2->setColor( ccRED );
	addChild(label2, 0, kTagBitmapAtlas2);
	label2->runAction( (CCAction*)(repeat->copy()->autorelease()) );
	
	CCBitmapFontAtlas* label3 = CCBitmapFontAtlas::bitmapFontAtlasWithString("Test", "fonts/bitmapFontTest2.fnt");
	// testing anchors
	label3->setAnchorPoint( ccp(1,1) );
	addChild(label3, 0, kTagBitmapAtlas3);
	
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();	
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
	
	CCBitmapFontAtlas *label1 = (CCBitmapFontAtlas*) getChildByTag(kTagBitmapAtlas1);
	label1->setString(string);
	
	CCBitmapFontAtlas *label2 = (CCBitmapFontAtlas*) getChildByTag(kTagBitmapAtlas2);
	label2->setString(string);
	
	CCBitmapFontAtlas *label3 = (CCBitmapFontAtlas*) getChildByTag(kTagBitmapAtlas3);
	label3->setString(string);

}

std::string Atlas3::title()
{
	return "CCBitmapFontAtlas";
}

std::string Atlas3::subtitle()
{
	return "Testing alignment. Testing opacity + tint";
}

//------------------------------------------------------------------
//
// Atlas4
//
//------------------------------------------------------------------
Atlas4::Atlas4()
{
	m_time = 0;

	// Upper Label
	CCBitmapFontAtlas *label = CCBitmapFontAtlas::bitmapFontAtlasWithString("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
	addChild(label);
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	
	label->setPosition( ccp(s.width/2, s.height/2) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
	
	
	CCSprite* BChar = (CCSprite*) label->getChildByTag(0);
	CCSprite* FChar = (CCSprite*) label->getChildByTag(7);
	CCSprite* AChar = (CCSprite*) label->getChildByTag(12);
	
	
	CCIntervalAction* rotate = CCRotateBy::actionWithDuration(2, 360);
	CCAction* rot_4ever = CCRepeatForever::actionWithAction(rotate);
	
	CCIntervalAction* scale = CCScaleBy::actionWithDuration(2, 1.5f);
	CCIntervalAction* scale_back = scale->reverse();
	CCFiniteTimeAction* scale_seq = CCSequence::actions(scale, scale_back,NULL);
	CCAction* scale_4ever = CCRepeatForever::actionWithAction((CCIntervalAction*)scale_seq);
	
	CCIntervalAction* jump = CCJumpBy::actionWithDuration(0.5f, CGPointZero, 60, 1);
	CCAction* jump_4ever = CCRepeatForever::actionWithAction(jump);
	
	CCIntervalAction* fade_out = CCFadeOut::actionWithDuration(1);
	CCIntervalAction* fade_in = CCFadeIn::actionWithDuration(1);
	CCFiniteTimeAction* seq = CCSequence::actions(fade_out, fade_in, NULL);
	CCAction* fade_4ever = CCRepeatForever::actionWithAction((CCIntervalAction*)seq);
	
	BChar->runAction(rot_4ever);
	BChar->runAction(scale_4ever);
	FChar->runAction(jump_4ever);
	AChar->runAction(fade_4ever);
	
	
	// Bottom Label
	CCBitmapFontAtlas *label2 = CCBitmapFontAtlas::bitmapFontAtlasWithString("00.0", "fonts/bitmapFontTest.fnt");
	addChild(label2, 0, kTagBitmapAtlas2);
	label2->setPosition( ccp(s.width/2.0f, 80) );
	
	CCSprite* lastChar = (CCSprite*) label2->getChildByTag(3);
	lastChar->runAction( (CCAction*)(rot_4ever->copy()->autorelease()) );
	
	schedule( schedule_selector(Atlas4::step), 0.1f);
}

void Atlas4::draw()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
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
	
	CCBitmapFontAtlas* label1 = (CCBitmapFontAtlas*) getChildByTag(kTagBitmapAtlas2);
	label1->setString(string);
}

std::string Atlas4::title()
{
	return "CCBitmapFontAtlas";
}

std::string Atlas4::subtitle()
{
	return "Using fonts as CCSprite objects. Some characters should rotate.";
}

//------------------------------------------------------------------
//
// Atlas5
//
//------------------------------------------------------------------

Atlas5::Atlas5()
{
	CCBitmapFontAtlas *label = CCBitmapFontAtlas::bitmapFontAtlasWithString("abcdefg", "fonts/bitmapFontTest4.fnt");
	addChild(label);
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	
	label->setPosition( ccp(s.width/2, s.height/2) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
}

std::string Atlas5::title()
{
	return "CCBitmapFontAtlas";
}

std::string Atlas5::subtitle()
{
	return "Testing padding";
}
//------------------------------------------------------------------
//
// Atlas6
//
//------------------------------------------------------------------

Atlas6::Atlas6()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	CCBitmapFontAtlas* label = NULL;
	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/2+50) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) ) ;
	
	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("fafefifofu", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/2) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );

	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("aeiou", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/2-50) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) ); 
}

std::string Atlas6::title()
{
	return "CCBitmapFontAtlas";
}

std::string Atlas6::subtitle()
{
	return "Rendering should be OK. Testing offset";
}

//------------------------------------------------------------------
//
// AtlasBitmapColor
//
//------------------------------------------------------------------

/*
 * Use any of these editors to generate bitmap font atlas:
 *   http://www.n4te.com/hiero/hiero.jnlp
 *   http://slick.cokeandcode.com/demos/hiero.jnlp
 *   http://www.angelcode.com/products/bmfont/
 */

AtlasBitmapColor::AtlasBitmapColor()
{
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	
	CCBitmapFontAtlas* label = NULL;
	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("Blue", "fonts/bitmapFontTest5.fnt");
	label->setColor( ccBLUE );
	addChild(label);
	label->setPosition( ccp(s.width/2, s.height/4) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );

	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("Red", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, 2*s.height/4) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
	label->setColor( ccRED );

	label = CCBitmapFontAtlas::bitmapFontAtlasWithString("G", "fonts/bitmapFontTest5.fnt");
	addChild(label);
	label->setPosition( ccp(s.width/2, 3*s.height/4) );
	label->setAnchorPoint( ccp(0.5f, 0.5f) );
	label->setColor( ccGREEN );
	label->setString("Green");
}

std::string AtlasBitmapColor::title()
{
	return "CCBitmapFontAtlas";
}

std::string AtlasBitmapColor::subtitle()
{
	return "Testing color";
}

//------------------------------------------------------------------
//
// AtlasFastBitmap
//
//------------------------------------------------------------------

AtlasFastBitmap::AtlasFastBitmap()
{
		// Upper Label
		for( int i=0 ; i < 100;i ++ ) 
		{
            char str[6] = {0};
            sprintf(str, "-%d-", i);
			CCBitmapFontAtlas* label = CCBitmapFontAtlas::bitmapFontAtlasWithString(str, "fonts/bitmapFontTest.fnt");
			addChild(label);
			
			CGSize s = CCDirector::getSharedDirector()->getWinSize();

			CGPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
			label->setPosition( p );
			label->setAnchorPoint(ccp(0.5f, 0.5f));
		}
}

std::string AtlasFastBitmap::title()
{
	return "CCBitmapFontAtlas";
}

std::string AtlasFastBitmap::subtitle()
{
	return "Creating several CCBitmapFontAtlas with the same .fnt file should be fast";
}

void AtlasTestScene::runThisTest()
{
    CCLayer* pLayer = nextAtlasAction();
    addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene(this);
}
