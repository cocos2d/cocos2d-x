#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include "../testBasic.h"
#include "cocos-ext.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

class ShaderTestDemo : public BaseTest
{
public:
    ShaderTestDemo(void);

    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    CREATE_FUNC(ShaderTestDemo);
};

class ShaderMonjori : public ShaderTestDemo
{
public:
    ShaderMonjori();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class ShaderMandelbrot : public ShaderTestDemo
{
public:
    ShaderMandelbrot();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class ShaderJulia : public ShaderTestDemo
{
public:
    ShaderJulia();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class ShaderHeart : public ShaderTestDemo
{
public:
    ShaderHeart();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class ShaderFlower : public ShaderTestDemo
{
public:
    ShaderFlower();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class ShaderPlasma : public ShaderTestDemo
{
public:
    ShaderPlasma();

    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
};

class SpriteBlur;
class ShaderBlur : public ShaderTestDemo
{
public:
    ShaderBlur();
    virtual std::string title();
    virtual std::string subtitle();
    virtual bool init();
    ControlSlider* createSliderCtl();
    void sliderAction(Object* sender, Control::EventType controlEvent);
protected:
    SpriteBlur* _blurSprite;
    ControlSlider* _sliderCtl;
};

class ShaderRetroEffect : public ShaderTestDemo
{
public:
    ShaderRetroEffect();
    virtual std::string title();
    virtual std::string subtitle();
    bool init();
    void update(float dt);
protected:
    LabelBMFont* _label;
    float           _accum;
};

class ShaderNode : public Node
{
public:
    ShaderNode();
    ~ShaderNode();

    bool initWithVertex(const char *vert, const char *frag);
    void loadShaderVertex(const char *vert, const char *frag);
    void listenBackToForeground(Object *obj);

    virtual void update(float dt);
    virtual void setPosition(const Point &newPosition);
    virtual void draw();

    static ShaderNode* shaderNodeWithVertex(const char *vert, const char *frag);

private:

    Vertex2F _center;
    Vertex2F _resolution;
    float      _time;
    GLuint     _uniformCenter, _uniformResolution, _uniformTime;
    std::string _vertFileName;
    std::string _fragFileName;
};

class ShaderFail : public ShaderTestDemo
{
public:
    ShaderFail();
    std::string title();
    std::string subtitle();
};

class ShaderTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
