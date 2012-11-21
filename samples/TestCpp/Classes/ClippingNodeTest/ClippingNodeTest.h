#ifndef __CLIPPINGNODETEST_H__
#define __CLIPPINGNODETEST_H__

#include "../testBasic.h"

class BaseClippingNodeTest : public CCLayer
{
public:
    ~BaseClippingNodeTest();
    virtual bool init();

	virtual std::string title();
	virtual std::string subtitle();
    virtual void setup();

	void backCallback(CCObject* sender);
	void nextCallback(CCObject* sender);
	void restartCallback(CCObject* sender);
};

class BasicTest : public BaseClippingNodeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();

	virtual CCAction* actionRotate();
	virtual CCAction* actionScale();

	virtual CCDrawNode* shape();
	virtual CCSprite* grossini();

	virtual CCNode* stencil();
	virtual CCClippingNode* clipper();
	virtual CCNode* content();
};

class ShapeTest : public BasicTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();

    virtual CCNode* stencil();
    virtual CCNode* content();
};

class ShapeInvertedTest : public ShapeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual CCClippingNode* clipper();
};

class SpriteTest : public BasicTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();

    virtual CCNode* stencil();
    virtual CCClippingNode* clipper();
    virtual CCNode* content();
};

class SpriteNoAlphaTest : public SpriteTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual CCClippingNode* clipper();
};

class SpriteInvertedTest : public SpriteTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual CCClippingNode* clipper();
};

class NestedTest : public BaseClippingNodeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();
};

class HoleDemo : public BaseClippingNodeTest
{
public:
    ~HoleDemo();
    virtual void setup();
    virtual std::string title();
    virtual std::string subtitle();
    void pokeHoleAtPoint(CCPoint point);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
private:
	CCClippingNode* m_pOuterClipper;
    CCNode* m_pHoles;
    CCNode* m_pHolesStencil;
};

class ScrollViewDemo : public BaseClippingNodeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
private:
	bool m_bScrolling;
    CCPoint m_lastPoint;
};

//#if COCOS2D_DEBUG > 1

class RawStencilBufferTest : public BaseClippingNodeTest
{
public:
    ~RawStencilBufferTest();

    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();
    virtual void draw();

	virtual void setupStencilForClippingOnPlane(GLint plane);
	virtual void setupStencilForDrawingOnPlane(GLint plane);

protected:
    CCSprite* m_pSprite;
};

class RawStencilBufferTest2 : public RawStencilBufferTest
{
public:
    virtual std::string subtitle();
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest3 : public RawStencilBufferTest
{
public:
    virtual std::string subtitle();
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest4 : public RawStencilBufferTest
{
public:
    virtual std::string subtitle();
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest5 : public RawStencilBufferTest
{
public:
    virtual std::string subtitle();
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest6 : public RawStencilBufferTest
{
public:
    virtual std::string subtitle();
    virtual void setup();
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

//#endif //COCOS2D_DEBUG > 1

class ClippingNodeTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif //__CLIPPINGNODETEST_H__
