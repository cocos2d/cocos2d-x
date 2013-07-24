#ifndef __CLIPPINGNODETEST_H__
#define __CLIPPINGNODETEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

class BaseClippingNodeTest : public BaseTest
{
public:
    ~BaseClippingNodeTest();
    virtual bool init();

	virtual std::string title();
	virtual std::string subtitle();
    virtual void setup();

	void backCallback(Object* sender);
	void nextCallback(Object* sender);
	void restartCallback(Object* sender);
};

class BasicTest : public BaseClippingNodeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();

	virtual Action* actionRotate();
	virtual Action* actionScale();

	virtual DrawNode* shape();
	virtual Sprite* grossini();

	virtual Node* stencil();
	virtual ClippingNode* clipper();
	virtual Node* content();
};

class ShapeTest : public BasicTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();

    virtual Node* stencil();
    virtual Node* content();
};

class ShapeInvertedTest : public ShapeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual ClippingNode* clipper();
};

class SpriteTest : public BasicTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();

    virtual Node* stencil();
    virtual ClippingNode* clipper();
    virtual Node* content();
};

class SpriteNoAlphaTest : public SpriteTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual ClippingNode* clipper();
};

class SpriteInvertedTest : public SpriteTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual ClippingNode* clipper();
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
    void pokeHoleAtPoint(Point point);
    virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
private:
	ClippingNode* _outerClipper;
    Node* _holes;
    Node* _holesStencil;
};

class ScrollViewDemo : public BaseClippingNodeTest
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void setup();
	virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
    virtual void ccTouchesMoved(Set *pTouches, Event *pEvent);
    virtual void ccTouchesEnded(Set *pTouches, Event *pEvent);
private:
	bool _scrolling;
    Point _lastPoint;
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
    Sprite* _sprite;
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
