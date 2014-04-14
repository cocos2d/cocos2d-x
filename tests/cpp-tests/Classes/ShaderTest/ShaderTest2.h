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

class NormalSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(NormalSpriteTest);
    NormalSpriteTest();
    
    virtual std::string subtitle() const {return "NormalSpriteTest";}
};

class GreyScaleSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(GreyScaleSpriteTest);
    GreyScaleSpriteTest();
    
    virtual std::string subtitle() const {return "GreyScaleSpriteTest";}
};

class BlurSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(BlurSpriteTest);
    BlurSpriteTest();
    
    virtual std::string subtitle() const {return "BlurSpriteTest";}
};

class NoiseSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(NoiseSpriteTest);
    NoiseSpriteTest();
    virtual std::string subtitle() const {return "NoiseSpriteTest";}
};

class EdgeDetectionSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EdgeDetectionSpriteTest);

    EdgeDetectionSpriteTest();
    virtual std::string subtitle() const {return "EdgeDetectionSpriteTest";}
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

class OutlineShadingSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(OutlineShadingSpriteTest);
    OutlineShadingSpriteTest();
    virtual std::string subtitle() const {return "OutlineShadingSpriteTest";}
};

#endif