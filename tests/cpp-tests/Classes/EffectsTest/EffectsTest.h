#ifndef _EFFECTS_TEST_H_
#define _EFFECTS_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(EffectTests);

class EffectBaseTest : public TestCase
{
public:
    EffectBaseTest();
    virtual ~EffectBaseTest();
protected:
    virtual bool init() override;
    virtual cocos2d::ActionInterval* createEffect(float t) {return nullptr;}
    void checkAnim(float dt);
    virtual bool isRectEffect(){return false;}
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
    std::string _title;
    std::string _subtitle;
    cocos2d::NodeGrid* _gridNodeTarget;
};

class Shaky3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(Shaky3DDemo);
    Shaky3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class Waves3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(Waves3DDemo);
    Waves3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FlipX3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FlipX3DDemo);
    FlipX3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FlipY3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FlipY3DDemo);
    FlipY3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class Lens3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(Lens3DDemo);
    Lens3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class Ripple3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(Ripple3DDemo);
    Ripple3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class LiquidDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(LiquidDemo);
    LiquidDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class WavesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(WavesDemo);
    WavesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class TwirlDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(TwirlDemo);
    TwirlDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class ShakyTiles3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(ShakyTiles3DDemo);
    ShakyTiles3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class ShatteredTiles3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(ShatteredTiles3DDemo);
    ShatteredTiles3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class ShuffleTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(ShuffleTilesDemo);
    ShuffleTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FadeOutTRTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FadeOutTRTilesDemo);
    FadeOutTRTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FadeOutBLTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FadeOutBLTilesDemo);
    FadeOutBLTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FadeOutUpTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FadeOutUpTilesDemo);
    FadeOutUpTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class FadeOutDownTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(FadeOutDownTilesDemo);
    FadeOutDownTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class TurnOffTilesDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(TurnOffTilesDemo);
    TurnOffTilesDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class WavesTiles3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(WavesTiles3DDemo);
    WavesTiles3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class JumpTiles3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(JumpTiles3DDemo);
    JumpTiles3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class SplitRowsDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(SplitRowsDemo);
    SplitRowsDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class SplitColsDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(SplitColsDemo);
    SplitColsDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class PageTurn3DDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(PageTurn3DDemo);
    PageTurn3DDemo();
protected:
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

class PageTurn3DRectDemo : public EffectBaseTest
{
public:
    CREATE_FUNC(PageTurn3DRectDemo);
    PageTurn3DRectDemo();
protected:
    virtual bool isRectEffect() override {return true;}
    virtual cocos2d::ActionInterval* createEffect(float t) override;
};

#endif
