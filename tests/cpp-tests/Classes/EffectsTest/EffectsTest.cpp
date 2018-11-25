/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "EffectsTest.h"
#include "../testResource.h"

USING_NS_CC;

EffectTests::EffectTests()
{
    ADD_TEST_CASE(Shaky3DDemo);
    ADD_TEST_CASE(Waves3DDemo);
    ADD_TEST_CASE(FlipX3DDemo);
    ADD_TEST_CASE(FlipY3DDemo);
    ADD_TEST_CASE(Lens3DDemo);
    ADD_TEST_CASE(Ripple3DDemo);
    ADD_TEST_CASE(LiquidDemo);
    ADD_TEST_CASE(WavesDemo);
    ADD_TEST_CASE(TwirlDemo);
    ADD_TEST_CASE(ShakyTiles3DDemo);
    ADD_TEST_CASE(ShatteredTiles3DDemo);
    ADD_TEST_CASE(ShuffleTilesDemo);
    ADD_TEST_CASE(FadeOutTRTilesDemo);
    ADD_TEST_CASE(FadeOutBLTilesDemo);
    ADD_TEST_CASE(FadeOutUpTilesDemo);
    ADD_TEST_CASE(FadeOutDownTilesDemo);
    ADD_TEST_CASE(TurnOffTilesDemo);
    ADD_TEST_CASE(WavesTiles3DDemo);
    ADD_TEST_CASE(JumpTiles3DDemo);
    ADD_TEST_CASE(SplitRowsDemo);
    ADD_TEST_CASE(SplitColsDemo);
    ADD_TEST_CASE(PageTurn3DDemo);
    ADD_TEST_CASE(PageTurn3DRectDemo);
}

Shaky3DDemo::Shaky3DDemo()
{
    _title = "Shaky3D";
    _subtitle = "";
}

cocos2d::ActionInterval* Shaky3DDemo::createEffect(float t)
{
    return Shaky3D::create(t, Size(15,10), 5, false);
}

Waves3DDemo::Waves3DDemo()
{
    _title = "Waves3D";
    _subtitle = "";
}

cocos2d::ActionInterval* Waves3DDemo::createEffect(float t)
{
    return Waves3D::create(t, Size(15,10), 5, 40);
}

cocos2d::ActionInterval* FlipX3DDemo::createEffect(float t)
{
    auto flipx  = FlipX3D::create(t);
    auto flipx_back = flipx->reverse();
    auto delay = DelayTime::create(2);
    return Sequence::create(flipx, delay, flipx_back, nullptr);
}

FlipX3DDemo::FlipX3DDemo()
{
    _title = "FlipX3D";
    _subtitle = "";
}

cocos2d::ActionInterval* FlipY3DDemo::createEffect(float t)
{
    auto flipy  = FlipY3D::create(t);
    auto flipy_back = flipy->reverse();
    auto delay = DelayTime::create(2);
    
    return Sequence::create(flipy, delay, flipy_back, nullptr);
}

FlipY3DDemo::FlipY3DDemo()
{
    _title = "FlipY3D";
    _subtitle = "";
}

cocos2d::ActionInterval* Lens3DDemo::createEffect(float t)
{
    auto size = Director::getInstance()->getWinSize();
    return Lens3D::create(t, Size(15,10), Vec2(size.width/2,size.height/2), 240);
}

Lens3DDemo::Lens3DDemo()
{
    _title = "Lens3D";
    _subtitle = "";
}

cocos2d::ActionInterval* Ripple3DDemo::createEffect(float t)
{
    auto size = Director::getInstance()->getWinSize();
    return Ripple3D::create(t, Size(32,24), Vec2(size.width/2,size.height/2), 240, 4, 160);
}

Ripple3DDemo::Ripple3DDemo()
{
    _title = "Ripple3D";
    _subtitle = "";
}

cocos2d::ActionInterval* LiquidDemo::createEffect(float t)
{
    return Liquid::create(t, Size(16,12), 4, 20);
}

LiquidDemo::LiquidDemo()
{
    _title = "Liquid";
    _subtitle = "";
}

cocos2d::ActionInterval* WavesDemo::createEffect(float t)
{
    return Waves::create(t, Size(16,12), 4, 20, true, true);
}

WavesDemo::WavesDemo()
{
    _title = "Waves";
    _subtitle = "";
}

cocos2d::ActionInterval* TwirlDemo::createEffect(float t)
{
    auto size = Director::getInstance()->getWinSize();
    return Twirl::create(t, Size(12,8), Vec2(size.width/2, size.height/2), 1, 2.5f);
}

TwirlDemo::TwirlDemo()
{
    _title = "Twirl";
    _subtitle = "";
}

cocos2d::ActionInterval* ShakyTiles3DDemo::createEffect(float t)
{
    return ShakyTiles3D::create(t, Size(16,12), 5, false) ;
}

ShakyTiles3DDemo::ShakyTiles3DDemo()
{
    _title = "ShakyTiles3D";
    _subtitle = "";
}

cocos2d::ActionInterval* ShatteredTiles3DDemo::createEffect(float t)
{
    return ShatteredTiles3D::create(t, Size(16,12), 5, false);
}

ShatteredTiles3DDemo::ShatteredTiles3DDemo()
{
    _title = "ShatteredTiles3D";
    _subtitle = "";
}

cocos2d::ActionInterval* ShuffleTilesDemo::createEffect(float t)
{
    auto shuffle = ShuffleTiles::create(t, Size(16,12), 25);
    auto shuffle_back = shuffle->reverse();
    auto delay = DelayTime::create(2);
    
    return Sequence::create(shuffle, delay, shuffle_back, nullptr);
}

ShuffleTilesDemo::ShuffleTilesDemo()
{
    _title = "ShuffleTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* FadeOutTRTilesDemo::createEffect(float t)
{
    auto fadeout = FadeOutTRTiles::create(t, Size(16,12));
    auto back = fadeout->reverse();
    auto delay = DelayTime::create(0.5f);
    
    return Sequence::create(fadeout, delay, back, nullptr);
}

FadeOutTRTilesDemo::FadeOutTRTilesDemo()
{
    _title = "FadeOutTRTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* FadeOutBLTilesDemo::createEffect(float t)
{
    auto fadeout = FadeOutBLTiles::create(t, Size(16,12));
    auto back = fadeout->reverse();
    auto delay = DelayTime::create(0.5f);
    
    return Sequence::create(fadeout, delay, back, nullptr);
}

FadeOutBLTilesDemo::FadeOutBLTilesDemo()
{
    _title = "FadeOutBLTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* FadeOutUpTilesDemo::createEffect(float t)
{
    auto fadeout = FadeOutUpTiles::create(t, Size(16,12));
    auto back = fadeout->reverse();
    auto delay = DelayTime::create(0.5f);
    
    return Sequence::create(fadeout, delay, back, nullptr);
}

FadeOutUpTilesDemo::FadeOutUpTilesDemo()
{
    _title = "FadeOutUpTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* FadeOutDownTilesDemo::createEffect(float t)
{
    auto fadeout = FadeOutDownTiles::create(t, Size(16,12));
    auto back = fadeout->reverse();
    auto delay = DelayTime::create(0.5f);
    
    return Sequence::create(fadeout, delay, back, nullptr);
}

FadeOutDownTilesDemo::FadeOutDownTilesDemo()
{
    _title = "FadeOutDownTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* TurnOffTilesDemo::createEffect(float t)
{
    auto fadeout = TurnOffTiles::create(t, Size(48,32), 25);
    auto back = fadeout->reverse();
    auto delay = DelayTime::create(0.5f);
    
    return Sequence::create(fadeout, delay, back, nullptr);
}

TurnOffTilesDemo::TurnOffTilesDemo()
{
    _title = "TurnOffTiles";
    _subtitle = "";
}

cocos2d::ActionInterval* WavesTiles3DDemo::createEffect(float t)
{
    return WavesTiles3D::create(t, Size(15,10), 4, 120);
}

WavesTiles3DDemo::WavesTiles3DDemo()
{
    _title = "WavesTiles3D";
    _subtitle = "";
}

cocos2d::ActionInterval* JumpTiles3DDemo::createEffect(float t)
{
    return JumpTiles3D::create(t, Size(15,10), 2, 30);
}

JumpTiles3DDemo::JumpTiles3DDemo()
{
    _title = "JumpTiles3D";
    _subtitle = "";
}

cocos2d::ActionInterval* SplitRowsDemo::createEffect(float t)
{
    return SplitRows::create(t, 9);
}

SplitRowsDemo::SplitRowsDemo()
{
    _title = "SplitRows";
    _subtitle = "";
}

cocos2d::ActionInterval* SplitColsDemo::createEffect(float t)
{
    return SplitCols::create(t, 9);
}

SplitColsDemo::SplitColsDemo()
{
    _title = "SplitCols";
    _subtitle = "";
}

cocos2d::ActionInterval* PageTurn3DDemo::createEffect(float t)
{
    return PageTurn3D::create(t, Size(15,10));
}

PageTurn3DDemo::PageTurn3DDemo()
{
    _title = "PageTurn3D";
    _subtitle = "";
}

cocos2d::ActionInterval* PageTurn3DRectDemo::createEffect(float t)
{
    return PageTurn3D::create(t, Size(15,10));
}

PageTurn3DRectDemo::PageTurn3DRectDemo()
{
    _title = "PageTurn3D-Rect";
    _subtitle = "";
}

#define SID_RESTART        1

EffectBaseTest::EffectBaseTest()
: _gridNodeTarget(nullptr)
{
    
}

bool EffectBaseTest::init()
{
    if(TestCase::init())
    {
        LayerColor *background = LayerColor::create( Color4B(32,128,32,255) );
        this->addChild(background,-20);
        if(isRectEffect())
        {
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Rect gridRect = Rect(visibleSize.width * 0.2,
                                 visibleSize.height * 0.2,
                                 visibleSize.width * 0.6,
                                 visibleSize.height * 0.6);
            _gridNodeTarget = NodeGrid::create(gridRect);
        }
        else
        {
            _gridNodeTarget = NodeGrid::create();
        }
        addChild(_gridNodeTarget, 0);
        _gridNodeTarget->runAction(createEffect(3));
        
        auto bg = Sprite::create(s_back3);
        _gridNodeTarget->addChild(bg, 0);
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
        
        schedule( CC_SCHEDULE_SELECTOR(EffectBaseTest::checkAnim) );
        
        return true;
    }
    return false;
}

void EffectBaseTest::checkAnim(float dt)
{
    if ( _gridNodeTarget->getNumberOfRunningActions() == 0 && _gridNodeTarget->getGrid() != nullptr)
        _gridNodeTarget->setGrid(nullptr);
}

EffectBaseTest::~EffectBaseTest(void)
{
}
