#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class ShaderTestDemo : public CCLayer
{
public:
	ShaderTestDemo(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual bool init();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);

	LAYER_NODE_FUNC(ShaderTestDemo);
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
    CCControlSlider* createSliderCtl();
    void sliderAction(CCObject* sender);
protected:
    SpriteBlur* m_pBlurSprite;
    CCControlSlider* m_pSliderCtl;
};

class ShaderRetroEffect : public ShaderTestDemo
{
public:
    ShaderRetroEffect();
    virtual std::string title();
    virtual std::string subtitle();
    bool init();
    void update(ccTime dt);
protected:
    CCLabelBMFont* m_pLabel;
    ccTime		   m_fAccum;
};

class ShaderNode : public CCNode
{
public:
    ShaderNode();

	bool initWithVertex(const char *vert, const char *frag);
	void loadShaderVertex(const char *vert, const char *frag);

	virtual void update(ccTime dt);
	virtual void setPosition(const CCPoint &newPosition);
	virtual void draw();

	static ShaderNode* shaderNodeWithVertex(const char *vert, const char *frag);

private:

	ccVertex2F m_center;
	ccVertex2F m_resolution;
	float      m_time;
	GLuint     m_uniformCenter, m_uniformResolution, m_uniformTime;
};

class ShaderTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
