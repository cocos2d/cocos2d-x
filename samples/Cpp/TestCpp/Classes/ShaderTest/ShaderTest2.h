#ifndef _SHADER_TEST2_H_
#define _SHADER_TEST2_H_
#include "../testBasic.h"
#include "cocos-ext.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

class ShaderTestDemo2 : public BaseTest
{
public:
    ShaderTestDemo2(void);
    virtual std::string title() { return "Shader Sprite!";}
    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
    
    CREATE_FUNC(ShaderTestDemo2);
};

class ShaderTestScene2 : public TestScene
{
public:
    virtual void runThisTest();
};

class NormalSpriteTest : public ShaderTestDemo2
{
public:
    NormalSpriteTest();
    
    virtual std::string subtitle() {return "NormalSpriteTest";}
};

class GreyScaleSpriteTest : public ShaderTestDemo2
{
public:
    GreyScaleSpriteTest();
    
    virtual std::string subtitle() {return "GreyScaleSpriteTest";}
};

class BlurSpriteTest : public ShaderTestDemo2
{
public:
    BlurSpriteTest();
    
    virtual std::string subtitle() {return "BlurSpriteTest";}
};

class NoiseSpriteTest : public ShaderTestDemo2
{
public:
    NoiseSpriteTest();
    virtual std::string subtitle() {return "NoiseSpriteTest";}
};

class EdgeDetectionSpriteTest : public ShaderTestDemo2
{
public:
    EdgeDetectionSpriteTest();
    virtual std::string subtitle() {return "EdgeDetectionSpriteTest";}
};

class BloomSpriteTest : public ShaderTestDemo2
{
public:
    BloomSpriteTest();
    virtual std::string subtitle() {return "BloomSpriteTest";}
};

class LensFlareSpriteTest : public ShaderTestDemo2
{
public:
    LensFlareSpriteTest();
    virtual std::string subtitle() {return "LensFlareSpriteTest";}
};

class CelShadingSpriteTest : public ShaderTestDemo2
{
public:
    CelShadingSpriteTest();
    virtual std::string subtitle() {return "CelShadingSpriteTest";}
};

#endif