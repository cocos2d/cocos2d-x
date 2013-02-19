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
    static CCActionInterval* create(float t)
    {
        return CCShaky3D::create(t, CCSizeMake(15,10), 5, false);
    }
};

class Waves3DDemo : public CCWaves3D 
{
public:
    static CCActionInterval* create(float t)
    {
        return CCWaves3D::create(t, CCSizeMake(15,10), 5, 40);
    }
};

class FlipX3DDemo : public CCFlipX3D 
{
public:
    static CCActionInterval* create(float t)
    {
        CCFlipX3D* flipx  = CCFlipX3D::create(t);
        CCActionInterval* flipx_back = flipx->reverse();
        CCDelayTime* delay = CCDelayTime::create(2);
        
        return CCSequence::create(flipx, delay, flipx_back, NULL);
    }
};

class FlipY3DDemo : public CCFlipY3D 
{
public:
    static CCActionInterval* create(float t)
    {
        CCFlipY3D* flipy  = CCFlipY3D::create(t);
        CCActionInterval* flipy_back = flipy->reverse();
        CCDelayTime* delay = CCDelayTime::create(2);
        
        return CCSequence::create(flipy, delay, flipy_back, NULL);
    }
};

class Lens3DDemo : public CCLens3D 
{
public:
    static CCActionInterval* create(float t)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        return CCLens3D::create(t, CCSizeMake(15,10), ccp(size.width/2,size.height/2), 240); 
    }
};


class Ripple3DDemo : public CCRipple3D 
{
public:
    static CCActionInterval* create(float t)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        return CCRipple3D::create(t, CCSizeMake(32,24), ccp(size.width/2,size.height/2), 240, 4, 160);
    }
};


class LiquidDemo : public CCLiquid
{
public:
    static CCActionInterval* create(float t)
    {
        return CCLiquid::create(t, CCSizeMake(16,12), 4, 20); 
    }
};


class WavesDemo : public CCWaves 
{
public:
    static CCActionInterval* create(float t)
    {
        return CCWaves::create(t, CCSizeMake(16,12), 4, 20, true, true);  
    }
};


class TwirlDemo : public CCTwirl 
{
public:
    static CCActionInterval* create(float t)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        return CCTwirl::create(t, CCSizeMake(12,8), ccp(size.width/2, size.height/2), 1, 2.5f); 
    }
};


class ShakyTiles3DDemo : public CCShakyTiles3D
{
public:
    static CCActionInterval* create(float t)
    {
        return CCShakyTiles3D::create(t, CCSizeMake(16,12), 5, false) ;
    }
};


class ShatteredTiles3DDemo : public CCShatteredTiles3D
{
public:
    static CCActionInterval* create(float t)
    {
        return CCShatteredTiles3D::create(t, CCSizeMake(16,12), 5, false); 
    }
};


class ShuffleTilesDemo : public CCShuffleTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCShuffleTiles* shuffle = CCShuffleTiles::create(t, CCSizeMake(16,12), 25);
        CCActionInterval* shuffle_back = shuffle->reverse();
        CCDelayTime* delay = CCDelayTime::create(2);

        return CCSequence::create(shuffle, delay, shuffle_back, NULL);
    }
};


class FadeOutTRTilesDemo : public CCFadeOutTRTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCFadeOutTRTiles* fadeout = CCFadeOutTRTiles::create(t, CCSizeMake(16,12));
        CCActionInterval* back = fadeout->reverse();
        CCDelayTime* delay = CCDelayTime::create(0.5f);

        return CCSequence::create(fadeout, delay, back, NULL);
    }
};


class FadeOutBLTilesDemo : public CCFadeOutBLTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCFadeOutBLTiles* fadeout = CCFadeOutBLTiles::create(t, CCSizeMake(16,12));
        CCActionInterval* back = fadeout->reverse();
        CCDelayTime* delay = CCDelayTime::create(0.5f);

        return CCSequence::create(fadeout, delay, back, NULL);
    }
};


class FadeOutUpTilesDemo : public CCFadeOutUpTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCFadeOutUpTiles* fadeout = CCFadeOutUpTiles::create(t, CCSizeMake(16,12));
        CCActionInterval* back = fadeout->reverse();
        CCDelayTime* delay = CCDelayTime::create(0.5f);

        return CCSequence::create(fadeout, delay, back, NULL);
    }
};

class FadeOutDownTilesDemo : public CCFadeOutDownTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCFadeOutDownTiles* fadeout = CCFadeOutDownTiles::create(t, CCSizeMake(16,12));
        CCActionInterval* back = fadeout->reverse();
        CCDelayTime* delay = CCDelayTime::create(0.5f);

        return CCSequence::create(fadeout, delay, back, NULL);
    }
};

class TurnOffTilesDemo : public CCTurnOffTiles
{
public:
    static CCActionInterval* create(float t)
    {
        CCTurnOffTiles* fadeout = CCTurnOffTiles::create(t, CCSizeMake(48,32), 25);
        CCActionInterval* back = fadeout->reverse();
        CCDelayTime* delay = CCDelayTime::create(0.5f);

        return CCSequence::create(fadeout, delay, back, NULL);
    }
};

class WavesTiles3DDemo : public CCWavesTiles3D
{
public:
    static CCActionInterval* create(float t)
    {
        return CCWavesTiles3D::create(t, CCSizeMake(15,10), 4, 120); 
    }
};

class JumpTiles3DDemo : public CCJumpTiles3D
{
public:
    static CCActionInterval* create(float t)
    {
        return CCJumpTiles3D::create(t, CCSizeMake(15,10), 2, 30); 
    }
};

class SplitRowsDemo : public CCSplitRows
{
public:
    static CCActionInterval* create(float t)
    {
        return CCSplitRows::create(t, 9); 
    }
};

class SplitColsDemo : public CCSplitCols
{
public:
    static CCActionInterval* create(float t)
    {
        return CCSplitCols::create(t, 9); 
    }
};

class PageTurn3DDemo : public CCPageTurn3D
{
public:
    static CCActionInterval* create(float t)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCPageTurn3D::create(t, CCSizeMake(15,10)); 
    }
};

//------------------------------------------------------------------
//
// TextLayer
//
//------------------------------------------------------------------
#define MAX_LAYER    22

CCActionInterval* createEffect(int nIndex, float t)
{

    CCDirector::sharedDirector()->setDepthTest(false);

    switch(nIndex)
    {
        case 0: return Shaky3DDemo::create(t);
        case 1: return Waves3DDemo::create(t);
        case 2: return FlipX3DDemo::create(t);
        case 3: return FlipY3DDemo::create(t);
        case 4: return Lens3DDemo::create(t);
        case 5: return Ripple3DDemo::create(t);
        case 6: return LiquidDemo::create(t);
        case 7: return WavesDemo::create(t);
        case 8: return TwirlDemo::create(t);
        case 9: return ShakyTiles3DDemo::create(t);
        case 10: return ShatteredTiles3DDemo::create(t);
        case 11: return ShuffleTilesDemo::create(t);
        case 12: return FadeOutTRTilesDemo::create(t);
        case 13: return FadeOutBLTilesDemo::create(t);
        case 14: return FadeOutUpTilesDemo::create(t);
        case 15: return FadeOutDownTilesDemo::create(t);
        case 16: return TurnOffTilesDemo::create(t);
        case 17: return WavesTiles3DDemo::create(t);
        case 18: return JumpTiles3DDemo::create(t);
        case 19: return SplitRowsDemo::create(t);
        case 20: return SplitColsDemo::create(t);
        case 21: return PageTurn3DDemo::create(t);
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
    addChild(TextLayer::create());
    CCDirector::sharedDirector()->replaceScene(this);
}

#define SID_RESTART        1

TextLayer::TextLayer(void)
{
    initWithColor( ccc4(32,128,32,255) );
    
    CCNode* node = CCNode::create();
    CCActionInterval* effect = getAction();
    node->runAction(effect);
    addChild(node, 0, kTagBackground);
    
    CCSprite *bg = CCSprite::create(s_back3);
    node->addChild(bg, 0);
//  bg->setAnchorPoint( CCPointZero );
    bg->setPosition(VisibleRect::center());

    CCSprite* grossini = CCSprite::create(s_pPathSister2);
    node->addChild(grossini, 1);
    grossini->setPosition( ccp(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3,VisibleRect::center().y) );
    CCActionInterval* sc = CCScaleBy::create(2, 5);
    CCActionInterval* sc_back = sc->reverse();
    grossini->runAction( CCRepeatForever::create(CCSequence::create(sc, sc_back, NULL) ) );

    CCSprite* tamara = CCSprite::create(s_pPathSister1);
    node->addChild(tamara, 1);
    tamara->setPosition( ccp(VisibleRect::left().x+2*VisibleRect::getVisibleRect().size.width/3,VisibleRect::center().y) );
    CCActionInterval* sc2 = CCScaleBy::create(2, 5);
    CCActionInterval* sc2_back = sc2->reverse();
    tamara->runAction( CCRepeatForever::create(CCSequence::create(sc2, sc2_back, NULL)) );
    
    CCLabelTTF* label = CCLabelTTF::create((effectsList[actionIdx]).c_str(), "Marker Felt", 32);
    
    label->setPosition( ccp(VisibleRect::center().x,VisibleRect::top().y-80) );
    addChild(label);
    label->setTag( kTagLabel );

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TextLayer::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TextLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TextLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    

    schedule( schedule_selector(TextLayer::checkAnim) );
}

void TextLayer::checkAnim(float dt)
{
    CCNode* s2 = getChildByTag(kTagBackground);
    if ( s2->numberOfRunningActions() == 0 && s2->getGrid() != NULL)
        s2->setGrid(NULL);;
}


TextLayer::~TextLayer(void)
{
}

// TextLayer* TextLayer::node()
// {
//     return TextLayer::create();
// }

TextLayer* TextLayer::create()
{
    TextLayer* pLayer = new TextLayer();
    pLayer->autorelease();
    
    return pLayer;
}

void TextLayer::onEnter()
{
    CCLayer::onEnter();
}

void TextLayer::newScene()
{
    CCScene* s = new EffectTestScene();
    CCNode* child = TextLayer::create();
    s->addChild(child);
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TextLayer::restartCallback(CCObject* pSender)
{
    newScene();
}

void TextLayer::nextCallback(CCObject* pSender)
{
    // update the action index
    actionIdx++;
    actionIdx = actionIdx % MAX_LAYER;

    newScene();
}

void TextLayer::backCallback(CCObject* pSender)
{
    // update the action index
    actionIdx--;
    int total = MAX_LAYER;
    if( actionIdx < 0 )
        actionIdx += total;    

    newScene();
} 
