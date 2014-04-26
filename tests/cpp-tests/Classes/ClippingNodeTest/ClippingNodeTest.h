#ifndef __CLIPPINGNODETEST_H__
#define __CLIPPINGNODETEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"
#include "2d/renderer/CCCustomCommand.h"
#include <list>

class BaseClippingNodeTest : public BaseTest
{
public:
    CREATE_FUNC(BaseClippingNodeTest);

    ~BaseClippingNodeTest();
    virtual bool init();

	virtual std::string title() const override;
	virtual std::string subtitle() const override;
    virtual void setup();

	void backCallback(Ref* sender);
	void nextCallback(Ref* sender);
	void restartCallback(Ref* sender);
};

class BasicTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(BasicTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
    CREATE_FUNC(ShapeTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual Node* stencil();
    virtual Node* content();
};

class ShapeInvertedTest : public ShapeTest
{
public:
    CREATE_FUNC(ShapeInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper();
};

class SpriteTest : public BasicTest
{
public:
    CREATE_FUNC(SpriteTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual Node* stencil();
    virtual ClippingNode* clipper();
    virtual Node* content();
};

class SpriteNoAlphaTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteNoAlphaTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper();
};

class SpriteInvertedTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper();
};

class NestedTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(NestedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup();
};

class HoleDemo : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(HoleDemo);

    ~HoleDemo();
    virtual void setup();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void pokeHoleAtPoint(Vector2 point);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
private:
	ClippingNode* _outerClipper;
    Node* _holes;
    Node* _holesStencil;
};

class ScrollViewDemo : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(ScrollViewDemo);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup();
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
private:
	bool _scrolling;
    Vector2 _lastPoint;
};

//#if COCOS2D_DEBUG > 1

class RawStencilBufferTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(RawStencilBufferTest);

    ~RawStencilBufferTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup();
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

	virtual void setupStencilForClippingOnPlane(GLint plane);
	virtual void setupStencilForDrawingOnPlane(GLint plane);

protected:
    std::list<CustomCommand> _renderCmds;
    void onEnableStencil();
    void onDisableStencil();
    void onBeforeDrawClip(int planeIndex, const Vector2& pt);
    void onBeforeDrawSprite(int planeIndex, const Vector2& pt);
protected:
    Vector<Sprite*> _sprites;
    Vector<Sprite*> _spritesStencil;
};

class RawStencilBufferTest2 : public RawStencilBufferTest
{
public:
    CREATE_FUNC(RawStencilBufferTest2);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest3 : public RawStencilBufferTest
{
public:
    CREATE_FUNC(RawStencilBufferTest3);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTestAlphaTest : public RawStencilBufferTest
{
public:
    virtual void setup() override;
};

class RawStencilBufferTest4 : public RawStencilBufferTestAlphaTest
{
public:
    CREATE_FUNC(RawStencilBufferTest4);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest5 : public RawStencilBufferTestAlphaTest
{
public:
    CREATE_FUNC(RawStencilBufferTest5);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

class RawStencilBufferTest6 : public RawStencilBufferTestAlphaTest
{
public:
    CREATE_FUNC(RawStencilBufferTest6);
    virtual void setup() override;
    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane);
    virtual void setupStencilForDrawingOnPlane(GLint plane);
};

//#endif //COCOS2D_DEBUG > 1

class ClippingNodeTestScene : public TestScene
{
public:
    CREATE_FUNC(ClippingNodeTestScene);

    virtual void runThisTest();
};

#endif //__CLIPPINGNODETEST_H__
