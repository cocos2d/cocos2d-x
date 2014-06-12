#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include "ui/CocosGUI.h"

#include "../testBasic.h"
#include "extensions/cocos-ext.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

class ShaderTestDemo : public BaseTest
{
public:
    ShaderTestDemo(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    CREATE_FUNC(ShaderTestDemo);
};

class ShaderMonjori : public ShaderTestDemo
{
public:
    ShaderMonjori();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderMandelbrot : public ShaderTestDemo
{
public:
    ShaderMandelbrot();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderJulia : public ShaderTestDemo
{
public:
    ShaderJulia();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderHeart : public ShaderTestDemo
{
public:
    ShaderHeart();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderFlower : public ShaderTestDemo
{
public:
    ShaderFlower();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderPlasma : public ShaderTestDemo
{
public:
    ShaderPlasma();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class SpriteBlur;
class ShaderBlur : public ShaderTestDemo
{
public:
    ShaderBlur();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
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
    ShaderRetroEffect();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    bool init();
    void update(float dt);
protected:
    Label* _label;
    float           _accum;
};

class ShaderNode : public Node
{
public:
    static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);

    virtual void update(float dt);
    virtual void setPosition(const Vec2 &newPosition);
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

class ShaderTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ShaderLensFlare : public ShaderTestDemo
{
public:
    ShaderLensFlare();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderGlow : public ShaderTestDemo
{
public:
    ShaderGlow();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

class ShaderMultiTexture : public ShaderTestDemo
{
    static const int rightSpriteTag = 2014;
public:
    ShaderMultiTexture();
    ui::Slider* createSliderCtl();
    void changeTexture(Ref*);
    int _changedTextureId;
    Sprite *_sprite;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual bool init();
};

#endif
