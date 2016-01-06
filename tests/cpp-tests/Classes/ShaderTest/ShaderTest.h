#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include "ui/CocosGUI.h"

#include "extensions/cocos-ext.h"
#include "../BaseTest.h"


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
    void onRadiusChanged(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onSampleNumChanged(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    
protected:
    SpriteBlur* _blurSprite;
    cocos2d::extension::ControlSlider* _sliderRadiusCtl;
    cocos2d::extension::ControlSlider* _sliderNumCtrl;
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
    cocos2d::Label* _label;
    float           _accum;
};

class ShaderNode : public cocos2d::Node
{
public:
    CREATE_FUNC(ShaderNode);
    static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);

    virtual void update(float dt) override;
    virtual void setPosition(const cocos2d::Vec2 &newPosition) override;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

protected:
    ShaderNode();
    ~ShaderNode();

    bool initWithVertex(const std::string &vert, const std::string &frag);
    void loadShaderVertex(const std::string &vert, const std::string &frag);

    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

    cocos2d::Vec2 _center;
    cocos2d::Vec2 _resolution;
    float      _time;
    std::string _vertFileName;
    std::string _fragFileName;
    cocos2d::CustomCommand _customCommand;
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
    cocos2d::ui::Slider* createSliderCtl();
    void changeTexture(cocos2d::Ref*);
    int _changedTextureId;
    cocos2d::Sprite* _sprite;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init() override;
};

#endif
