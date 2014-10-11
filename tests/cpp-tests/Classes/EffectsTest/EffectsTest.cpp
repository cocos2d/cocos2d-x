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


class Shaky3DDemo : public Shaky3D 
{
public:
    static ActionInterval* create(float t)
    {
        return Shaky3D::create(t, Size(15,10), 5, false);
    }
};

class Waves3DDemo : public Waves3D 
{
public:
    static ActionInterval* create(float t)
    {
        return Waves3D::create(t, Size(15,10), 5, 40);
    }
};

class FlipX3DDemo : public FlipX3D 
{
public:
    static ActionInterval* create(float t)
    {
        auto flipx  = FlipX3D::create(t);
        auto flipx_back = flipx->reverse();
        auto delay = DelayTime::create(2);
        
        return Sequence::create(flipx, delay, flipx_back, nullptr);
    }
};

class FlipY3DDemo : public FlipY3D 
{
public:
    static ActionInterval* create(float t)
    {
        auto flipy  = FlipY3D::create(t);
        auto flipy_back = flipy->reverse();
        auto delay = DelayTime::create(2);
        
        return Sequence::create(flipy, delay, flipy_back, nullptr);
    }
};

class Lens3DDemo : public Lens3D 
{
public:
    static ActionInterval* create(float t)
    {
        auto size = Director::getInstance()->getWinSize();
        return Lens3D::create(t, Size(15,10), Vec2(size.width/2,size.height/2), 240); 
    }
};


class Ripple3DDemo : public Ripple3D 
{
public:
    static ActionInterval* create(float t)
    {
        auto size = Director::getInstance()->getWinSize();
        return Ripple3D::create(t, Size(32,24), Vec2(size.width/2,size.height/2), 240, 4, 160);
    }
};


class LiquidDemo : public Liquid
{
public:
    static ActionInterval* create(float t)
    {
        return Liquid::create(t, Size(16,12), 4, 20); 
    }
};


class WavesDemo : public Waves 
{
public:
    static ActionInterval* create(float t)
    {
        return Waves::create(t, Size(16,12), 4, 20, true, true);  
    }
};


class TwirlDemo : public Twirl 
{
public:
    static ActionInterval* create(float t)
    {
        auto size = Director::getInstance()->getWinSize();
        return Twirl::create(t, Size(12,8), Vec2(size.width/2, size.height/2), 1, 2.5f); 
    }
};


class ShakyTiles3DDemo : public ShakyTiles3D
{
public:
    static ActionInterval* create(float t)
    {
        return ShakyTiles3D::create(t, Size(16,12), 5, false) ;
    }
};


class ShatteredTiles3DDemo : public ShatteredTiles3D
{
public:
    static ActionInterval* create(float t)
    {
        return ShatteredTiles3D::create(t, Size(16,12), 5, false); 
    }
};


class ShuffleTilesDemo : public ShuffleTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto shuffle = ShuffleTiles::create(t, Size(16,12), 25);
        auto shuffle_back = shuffle->reverse();
        auto delay = DelayTime::create(2);

        return Sequence::create(shuffle, delay, shuffle_back, nullptr);
    }
};


class FadeOutTRTilesDemo : public FadeOutTRTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto fadeout = FadeOutTRTiles::create(t, Size(16,12));
        auto back = fadeout->reverse();
        auto delay = DelayTime::create(0.5f);

        return Sequence::create(fadeout, delay, back, nullptr);
    }
};


class FadeOutBLTilesDemo : public FadeOutBLTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto fadeout = FadeOutBLTiles::create(t, Size(16,12));
        auto back = fadeout->reverse();
        auto delay = DelayTime::create(0.5f);

        return Sequence::create(fadeout, delay, back, nullptr);
    }
};


class FadeOutUpTilesDemo : public FadeOutUpTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto fadeout = FadeOutUpTiles::create(t, Size(16,12));
        auto back = fadeout->reverse();
        auto delay = DelayTime::create(0.5f);

        return Sequence::create(fadeout, delay, back, nullptr);
    }
};

class FadeOutDownTilesDemo : public FadeOutDownTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto fadeout = FadeOutDownTiles::create(t, Size(16,12));
        auto back = fadeout->reverse();
        auto delay = DelayTime::create(0.5f);

        return Sequence::create(fadeout, delay, back, nullptr);
    }
};

class TurnOffTilesDemo : public TurnOffTiles
{
public:
    static ActionInterval* create(float t)
    {
        auto fadeout = TurnOffTiles::create(t, Size(48,32), 25);
        auto back = fadeout->reverse();
        auto delay = DelayTime::create(0.5f);

        return Sequence::create(fadeout, delay, back, nullptr);
    }
};

class WavesTiles3DDemo : public WavesTiles3D
{
public:
    static ActionInterval* create(float t)
    {
        return WavesTiles3D::create(t, Size(15,10), 4, 120); 
    }
};

class JumpTiles3DDemo : public JumpTiles3D
{
public:
    static ActionInterval* create(float t)
    {
        return JumpTiles3D::create(t, Size(15,10), 2, 30); 
    }
};

class SplitRowsDemo : public SplitRows
{
public:
    static ActionInterval* create(float t)
    {
        return SplitRows::create(t, 9); 
    }
};

class SplitColsDemo : public SplitCols
{
public:
    static ActionInterval* create(float t)
    {
        return SplitCols::create(t, 9); 
    }
};

class PageTurn3DDemo : public PageTurn3D
{
public:
    static ActionInterval* create(float t)
    {
        return PageTurn3D::create(t, Size(15,10)); 
    }
};

//------------------------------------------------------------------
//
// TextLayer
//
//------------------------------------------------------------------
#define MAX_LAYER    22

ActionInterval* createEffect(int nIndex, float t)
{

    Director::getInstance()->setDepthTest(false);

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

    return nullptr;
}

ActionInterval* getAction()
{
    auto pEffect = createEffect(actionIdx, 3);

    return pEffect;
} 

void EffectTestScene::runThisTest()
{
    addChild(TextLayer::create());
    Director::getInstance()->replaceScene(this);
}

#define SID_RESTART        1

TextLayer::TextLayer(void)
: BaseTest()
{
	LayerColor *background = LayerColor::create( Color4B(32,128,32,255) );
	this->addChild(background,-20);
    
    _gridNodeTarget = NodeGrid::create();
    auto effect = getAction();
    _gridNodeTarget->runAction(effect);
    addChild(_gridNodeTarget, 0, kTagBackground);
    
    auto bg = Sprite::create(s_back3);
    _gridNodeTarget->addChild(bg, 0);
//  bg->setAnchorPoint( Vec2::ZERO );
    bg->setPosition(VisibleRect::center());

    auto grossini = Sprite::create(s_pathSister2);
    _gridNodeTarget->addChild(grossini, 1);
    grossini->setPosition(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3,VisibleRect::center().y);
    auto sc = ScaleBy::create(2, 5);
    auto sc_back = sc->reverse();
    grossini->runAction( RepeatForever::create(Sequence::create(sc, sc_back, nullptr) ) );

    auto tamara = Sprite::create(s_pathSister1);
    _gridNodeTarget->addChild(tamara, 1);
    tamara->setPosition(VisibleRect::left().x+2*VisibleRect::getVisibleRect().size.width/3,VisibleRect::center().y);
    auto sc2 = ScaleBy::create(2, 5);
    auto sc2_back = sc2->reverse();
    tamara->runAction( RepeatForever::create(Sequence::create(sc2, sc2_back, nullptr)) );
    
    auto label = Label::createWithTTF((effectsList[actionIdx]).c_str(), "fonts/Marker Felt.ttf", 32);
    
    label->setPosition(VisibleRect::center().x,VisibleRect::top().y-80);
    addChild(label);
    label->setTag( kTagLabel );
    
    schedule( CC_SCHEDULE_SELECTOR(TextLayer::checkAnim) );
}

void TextLayer::checkAnim(float dt)
{
    //auto s2 = getChildByTag(kTagBackground);
    if ( _gridNodeTarget->getNumberOfRunningActions() == 0 && _gridNodeTarget->getGrid() != nullptr)
        _gridNodeTarget->setGrid(nullptr);;
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
    auto layer = new (std::nothrow) TextLayer();
    layer->autorelease();
    
    return layer;
}

void TextLayer::onEnter()
{
    BaseTest::onEnter();
}

void TextLayer::newScene()
{
    auto s = new (std::nothrow) EffectTestScene();
    auto child = TextLayer::create();
    s->addChild(child);
    Director::getInstance()->replaceScene(s);
    s->release();
}

void TextLayer::restartCallback(Ref* sender)
{
    newScene();
}

void TextLayer::nextCallback(Ref* sender)
{
    // update the action index
    actionIdx++;
    actionIdx = actionIdx % MAX_LAYER;

    newScene();
}

void TextLayer::backCallback(Ref* sender)
{
    // update the action index
    actionIdx--;
    int total = MAX_LAYER;
    if( actionIdx < 0 )
        actionIdx += total;    

    newScene();
} 
