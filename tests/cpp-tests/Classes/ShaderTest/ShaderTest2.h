#ifndef _SHADER_TEST2_H_
#define _SHADER_TEST2_H_
#include "../testBasic.h"
#include "extensions/cocos-ext.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

class ShaderTestDemo2 : public BaseTest
{
public:
    ShaderTestDemo2(void);
    virtual std::string title() const { return "Effects on Sprites";}
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class ShaderTestScene2 : public TestScene
{
public:
    CREATE_FUNC(ShaderTestScene2);
    virtual void runThisTest();
};


//
// Effect
//
class EffectSprite;

class Effect : public Ref
{
public:
    GLProgramState* getGLProgramState() const { return _glprogramstate; }
    virtual void setTarget(EffectSprite *sprite){}

protected:
    bool initGLProgramState(const std::string &fragmentFilename);
    Effect();
    virtual ~Effect();
    GLProgramState *_glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::string _fragSource;
    EventListenerCustom* _backgroundListener;
#endif
};

class EffectSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EffectSpriteTest);
    EffectSpriteTest();
    virtual std::string subtitle() const {return "Different effects on Sprite";}

protected:
    ssize_t _vectorIndex;
    cocos2d::Vector<Effect*> _effects;
    EffectSprite *_sprite;
};

class EffectSpriteLamp : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EffectSpriteLamp);
    EffectSpriteLamp();
    virtual std::string subtitle() const {return "Sprite Lamp effects";}
    //callback
public:
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
protected:
    EffectSprite *_sprite;
    Effect* _effect;
    Sprite* _lightSprite;
};

#endif
