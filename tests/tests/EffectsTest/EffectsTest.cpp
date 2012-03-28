#include "EffectsTest.h"
#include "../testResource.h"

enum {
    kTagTextLayer = 1,

    kTagBackground = 1,
    kTagLabel = 2,
};

static int actionIdx=0; 
static std::string effectsList[] =
{
	"Shaky3D",
	"Waves3D",
	"FlipX3D",
	"FlipY3D",
	"Lens3D",
	"Ripple3D",
	"Liquid",
	"Waves",
	"Twirl",
	"ShakyTiles3D",
	"ShatteredTiles3D",
	"ShuffleTiles",
	"FadeOutTRTiles",
	"FadeOutBLTiles",
	"FadeOutUpTiles",
	"FadeOutDownTiles",
	"TurnOffTiles",
	"WavesTiles3D",
	"JumpTiles3D",
	"SplitRows",
	"SplitCols",
	"PageTurn3D",
}; 


class Shaky3DDemo : public CCShaky3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCShaky3D::actionWithRange(5, true, ccg(15,10), t);
	}
};

class Waves3DDemo : public CCWaves3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCWaves3D::actionWithWaves(5, 40, ccg(15,10), t);
	}
};

class FlipX3DDemo : public CCFlipX3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFlipX3D* flipx  = CCFlipX3D::actionWithDuration(t);
		CCActionInterval* flipx_back = flipx->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(2);
		
		return (CCActionInterval*)(CCSequence::actions(flipx, delay, flipx_back, NULL));
	}
};

class FlipY3DDemo : public CCFlipY3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFlipY3D* flipy  = CCFlipY3D::actionWithDuration(t);
		CCActionInterval* flipy_back = flipy->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(2);
		
		return (CCActionInterval*)(CCSequence::actions(flipy, delay, flipy_back, NULL));
	}
};

class Lens3DDemo : public CCLens3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		return CCLens3D::actionWithPosition(CCPointMake(size.width/2,size.height/2), 240, ccg(15,10), t); 
	}
};


class Ripple3DDemo : public CCRipple3D 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		return CCRipple3D::actionWithPosition(CCPointMake(size.width/2,size.height/2), 240, 4, 160, ccg(32,24), t);
	}
};


class LiquidDemo : public CCLiquid
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCLiquid::actionWithWaves(4, 20, ccg(16,12), t); 
	}
};


class WavesDemo : public CCWaves 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCWaves::actionWithWaves(4, 20, true, true, ccg(16,12), t);  
	}
};


class TwirlDemo : public CCTwirl 
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		return CCTwirl::actionWithPosition(CCPointMake(size.width/2, size.height/2), 1, 2.5f, ccg(12,8), t); 
	}
};


class ShakyTiles3DDemo : public CCShakyTiles3D
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCShakyTiles3D::actionWithRange(5, true, ccg(16,12), t) ;
	}
};


class ShatteredTiles3DDemo : public CCShatteredTiles3D
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCShatteredTiles3D::actionWithRange(5, true, ccg(16,12), t); 
	}
};


class ShuffleTilesDemo : public CCShuffleTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCShuffleTiles* shuffle = CCShuffleTiles::actionWithSeed(25, ccg(16,12), t);
		CCActionInterval* shuffle_back = shuffle->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(2);

		return (CCActionInterval*)(CCSequence::actions(shuffle, delay, shuffle_back, NULL));
	}
};


class FadeOutTRTilesDemo : public CCFadeOutTRTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFadeOutTRTiles* fadeout = CCFadeOutTRTiles::actionWithSize(ccg(16,12), t);
		CCActionInterval* back = fadeout->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(0.5f);

		return (CCActionInterval*)(CCSequence::actions(fadeout, delay, back, NULL));
	}
};


class FadeOutBLTilesDemo : public CCFadeOutBLTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFadeOutBLTiles* fadeout = CCFadeOutBLTiles::actionWithSize(ccg(16,12), t);
		CCActionInterval* back = fadeout->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(0.5f);

		return (CCActionInterval*)(CCSequence::actions(fadeout, delay, back, NULL));
	}
};


class FadeOutUpTilesDemo : public CCFadeOutUpTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFadeOutUpTiles* fadeout = CCFadeOutUpTiles::actionWithSize(ccg(16,12), t);
		CCActionInterval* back = fadeout->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(0.5f);

		return (CCActionInterval*)(CCSequence::actions(fadeout, delay, back, NULL));
	}
};

class FadeOutDownTilesDemo : public CCFadeOutDownTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCFadeOutDownTiles* fadeout = CCFadeOutDownTiles::actionWithSize(ccg(16,12), t);
		CCActionInterval* back = fadeout->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(0.5f);

		return (CCActionInterval*)(CCSequence::actions(fadeout, delay, back, NULL));
	}
};

class TurnOffTilesDemo : public CCTurnOffTiles
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCTurnOffTiles* fadeout = CCTurnOffTiles::actionWithSeed(25, ccg(48,32) , t);
		CCActionInterval* back = fadeout->reverse();
		CCDelayTime* delay = CCDelayTime::actionWithDuration(0.5f);

		return (CCActionInterval*)(CCSequence::actions(fadeout, delay, back, NULL));
	}
};

class WavesTiles3DDemo : public CCWavesTiles3D
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCWavesTiles3D::actionWithWaves(4, 120, ccg(15,10), t); 
	}
};

class JumpTiles3DDemo : public CCJumpTiles3D
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		return CCJumpTiles3D::actionWithJumps(2, 30, ccg(15,10), t); 
	}
};

class SplitRowsDemo : public CCSplitRows
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCSplitRows::actionWithRows(9, t); 
	}
};

class SplitColsDemo : public CCSplitCols
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
		return CCSplitCols::actionWithCols(9, t); 
	}
};

class PageTurn3DDemo : public CCPageTurn3D
{
public:
	static CCActionInterval* actionWithDuration(ccTime t)
	{
        CCDirector::sharedDirector()->setDepthTest(true);
		return CCPageTurn3D::actionWithSize(ccg(15,10), t); 
	}
};

//------------------------------------------------------------------
//
// TextLayer
//
//------------------------------------------------------------------
#define MAX_LAYER	22

CCActionInterval* createEffect(int nIndex, ccTime t)
{

    CCDirector::sharedDirector()->setDepthTest(false);

	switch(nIndex)
	{
		case 0: return Shaky3DDemo::actionWithDuration(t);
		case 1: return Waves3DDemo::actionWithDuration(t);
		case 2: return FlipX3DDemo::actionWithDuration(t);
		case 3: return FlipY3DDemo::actionWithDuration(t);
		case 4: return Lens3DDemo::actionWithDuration(t);
		case 5: return Ripple3DDemo::actionWithDuration(t);
		case 6: return LiquidDemo::actionWithDuration(t);
		case 7: return WavesDemo::actionWithDuration(t);
		case 8: return TwirlDemo::actionWithDuration(t);
		case 9: return ShakyTiles3DDemo::actionWithDuration(t);
		case 10: return ShatteredTiles3DDemo::actionWithDuration(t);
		case 11: return ShuffleTilesDemo::actionWithDuration(t);
		case 12: return FadeOutTRTilesDemo::actionWithDuration(t);
		case 13: return FadeOutBLTilesDemo::actionWithDuration(t);
		case 14: return FadeOutUpTilesDemo::actionWithDuration(t);
		case 15: return FadeOutDownTilesDemo::actionWithDuration(t);
		case 16: return TurnOffTilesDemo::actionWithDuration(t);
		case 17: return WavesTiles3DDemo::actionWithDuration(t);
		case 18: return JumpTiles3DDemo::actionWithDuration(t);
		case 19: return SplitRowsDemo::actionWithDuration(t);
		case 20: return SplitColsDemo::actionWithDuration(t);
		case 21: return PageTurn3DDemo::actionWithDuration(t);
	}

	return NULL;
}

CCActionInterval* getAction()
{
	CCActionInterval* pEffect = createEffect(actionIdx, 3);

	return pEffect;
} 

void EffectTestScene::runThisTest()
{
    addChild(TextLayer::node());
    CCDirector::sharedDirector()->replaceScene(this);
}

#define SID_RESTART		1

TextLayer::TextLayer(void)
{
	initWithColor( ccc4f(32,32,32,255) );
		
	float x,y;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCNode* node = CCNode::node();
	CCActionInterval* effect = getAction();
	node->runAction(effect)
		;
	addChild(node, 0, kTagBackground);
	
	CCSprite *bg = CCSprite::spriteWithFile(s_back3);
	node->addChild(bg, 0);
	bg->setAnchorPoint( CCPointZero );

	CCSprite* grossini = CCSprite::spriteWithFile(s_pPathSister2);
	node->addChild(grossini, 1);
	grossini->setPosition( CCPointMake(x/3,y/2) );
	CCActionInterval* sc = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* sc_back = sc->reverse();
	grossini->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(sc, sc_back, NULL)) ) );

	CCSprite* tamara = CCSprite::spriteWithFile(s_pPathSister1);
	node->addChild(tamara, 1);
	tamara->setPosition( CCPointMake(2*x/3,y/2) );
	CCActionInterval* sc2 = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* sc2_back = sc2->reverse();
	tamara->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)(CCSequence::actions(sc2, sc2_back, NULL))) );
	
	CCLabelTTF* label = CCLabelTTF::labelWithString((effectsList[actionIdx]).c_str(), "Marker Felt", 32);
	
	label->setPosition( CCPointMake(x/2,y-80) );
	addChild(label);
	label->setTag( kTagLabel );

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TextLayer::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(TextLayer::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TextLayer::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( CCPointMake( size.width/2 - 100,30) );
	item2->setPosition( CCPointMake( size.width/2, 30) );
	item3->setPosition( CCPointMake( size.width/2 + 100,30) );
	
	addChild(menu, 1);	

	schedule( schedule_selector(TextLayer::checkAnim) );
}

void TextLayer::checkAnim(ccTime dt)
{
	CCNode* s2 = getChildByTag(kTagBackground);
	if ( s2->numberOfRunningActions() == 0 && s2->getGrid() != NULL)
		s2->setGrid(NULL);;
}


TextLayer::~TextLayer(void)
{
}

TextLayer* TextLayer::node()
{
	TextLayer* pLayer = new TextLayer();
	pLayer->autorelease();
	
	return pLayer;
}

void TextLayer::onEnter()
{
	CCLayer::onEnter();
}

void TextLayer::newOrientation()
{
	ccDeviceOrientation orientation = CCDirector::sharedDirector()->getDeviceOrientation();
	switch (orientation) 
	{
		case CCDeviceOrientationLandscapeLeft:
			orientation = CCDeviceOrientationPortrait;
			break;
		case CCDeviceOrientationPortrait:
			orientation = CCDeviceOrientationLandscapeRight;
			break;						
		case CCDeviceOrientationLandscapeRight:
			orientation = CCDeviceOrientationPortraitUpsideDown;
			break;
		case CCDeviceOrientationPortraitUpsideDown:
			orientation = CCDeviceOrientationLandscapeLeft;
			break;
	}

	CCDirector::sharedDirector()->setDeviceOrientation(orientation);
}

void TextLayer::newScene()
{
	CCScene* s = new EffectTestScene();
	CCNode* child = TextLayer::node();
	s->addChild(child);
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TextLayer::restartCallback(CCObject* pSender)
{
	/*newOrientation();*/
	newScene();
}

void TextLayer::nextCallback(CCObject* pSender)
{
    // update the action index
    actionIdx++;
    actionIdx = actionIdx % MAX_LAYER;

	/*newOrientation();*/
	newScene();
}

void TextLayer::backCallback(CCObject* pSender)
{
    // update the action index
    actionIdx--;
    int total = MAX_LAYER;
    if( actionIdx < 0 )
        actionIdx += total;	

	/*newOrientation();*/
	newScene();
} 
