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
    virtual std::string title() const { return "Shader Sprite!";}
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

class BloomSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(BloomSpriteTest);

    BloomSpriteTest();
    virtual std::string subtitle() const {return "BloomSpriteTest";}
};

class LensFlareSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(LensFlareSpriteTest);

    LensFlareSpriteTest();
    virtual std::string subtitle() const {return "LensFlareSpriteTest";}
};

class CelShadingSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(CelShadingSpriteTest);

    CelShadingSpriteTest();
    virtual std::string subtitle() const {return "CelShadingSpriteTest";}
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
    Effect() : _glprogramstate(nullptr)
    {}
    virtual ~Effect() {}
    GLProgramState *_glprogramstate;
};

class EffectSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EffectSpriteTest);
    EffectSpriteTest();
    virtual std::string subtitle() const {return "Cycle different effects on the sprite";}

protected:
    ssize_t _vectorIndex;
    cocos2d::Vector<Effect*> _effects;
    EffectSprite *_sprite;
};


#endif