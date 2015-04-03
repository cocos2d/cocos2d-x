#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include "ui/CocosGUI.h"

#include "../testBasic.h"
#include "extensions/cocos-ext.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

DEFINE_TEST_SUITE(ShaderTests);

class ShaderTestDemo : public TestCase
{
public:
};

class ShaderMonjori : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderMonjori);
    ShaderMonjori();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderMandelbrot : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderMandelbrot);
    ShaderMandelbrot();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderJulia : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderJulia);
    ShaderJulia();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderHeart : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderHeart);
    ShaderHeart();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderFlower : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderFlower);
    ShaderFlower();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderPlasma : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderPlasma);
    ShaderPlasma();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class SpriteBlur;
class ShaderBlur : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderBlur);
    ShaderBlur();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
    void createSliderCtls();
    void onRadiusChanged(Ref* sender, Control::EventType controlEvent);
    void onSampleNumChanged(Ref* sender, Control::EventType controlEvent);
    
protected:
    SpriteBlur* _blurSprite;
    ControlSlider* _sliderRadiusCtl;
    ControlSlider* _sliderNumCtrl;
};

class ShaderRetroEffect : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderRetroEffect);
    ShaderRetroEffect();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    bool init() override;
    void update(float dt) override;
protected:
    Label* _label;
    float           _accum;
};

class ShaderNode : public Node
{
public:
    CREATE_FUNC(ShaderNode);
    static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);

    virtual void update(float dt) override;
    virtual void setPosition(const Vec2 &newPosition) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
    ShaderNode();
    ~ShaderNode();

    bool initWithVertex(const std::string &vert, const std::string &frag);
    void loadShaderVertex(const std::string &vert, const std::string &frag);

    void onDraw(const Mat4 &transform, uint32_t flags);

    Vec2 _center;
    Vec2 _resolution;
    float      _time;
    std::string _vertFileName;
    std::string _fragFileName;
    CustomCommand _customCommand;
};

class ShaderLensFlare : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderLensFlare);
    ShaderLensFlare();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderGlow : public ShaderTestDemo
{
public:
    CREATE_FUNC(ShaderGlow);
    ShaderGlow();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

class ShaderMultiTexture : public ShaderTestDemo
{
    static const int rightSpriteTag = 2014;
public:
    CREATE_FUNC(ShaderMultiTexture);
    ShaderMultiTexture();
    ui::Slider* createSliderCtl();
    void changeTexture(Ref*);
    int _changedTextureId;
    Sprite *_sprite;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

#endif
