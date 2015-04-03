#ifndef __CLIPPINGNODETEST_H__
#define __CLIPPINGNODETEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"
#include <list>

class BaseClippingNodeTest : public BaseTest
{
public:
    CREATE_FUNC(BaseClippingNodeTest);

    ~BaseClippingNodeTest();
    virtual bool init() override;

	virtual std::string title() const override;
	virtual std::string subtitle() const override;
    virtual void setup();

	void backCallback(Ref* sender) override;
	void nextCallback(Ref* sender) override;
	void restartCallback(Ref* sender) override;
};

class BasicTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(BasicTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;

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

    virtual Node* stencil() override;
    virtual Node* content() override;
};

class ShapeInvertedTest : public ShapeTest
{
public:
    CREATE_FUNC(ShapeInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper() override;
};

class SpriteTest : public BasicTest
{
public:
    CREATE_FUNC(SpriteTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual Node* stencil() override;
    virtual ClippingNode* clipper() override;
    virtual Node* content() override;
};

class SpriteNoAlphaTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteNoAlphaTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper() override;
};

class SpriteInvertedTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual ClippingNode* clipper() override;
};

class NestedTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(NestedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;
};

class HoleDemo : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(HoleDemo);

    ~HoleDemo();
    virtual void setup() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void pokeHoleAtPoint(Vec2 point);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) override;
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
    virtual void setup() override;
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event) override;
private:
	bool _scrolling;
    Vec2 _lastPoint;
};

//#if COCOS2D_DEBUG > 1

class RawStencilBufferTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(RawStencilBufferTest);

    ~RawStencilBufferTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	virtual void setupStencilForClippingOnPlane(GLint plane);
	virtual void setupStencilForDrawingOnPlane(GLint plane);

protected:
    std::list<CustomCommand> _renderCmds;
    void onEnableStencil();
    void onDisableStencil();
    void onBeforeDrawClip(int planeIndex, const Vec2& pt);
    void onBeforeDrawSprite(int planeIndex, const Vec2& pt);
protected:
    Vector<Sprite*> _sprites;
    Vector<Sprite*> _spritesStencil;
};

class RawStencilBufferTest2 : public RawStencilBufferTest
{
public:
    CREATE_FUNC(RawStencilBufferTest2);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane) override;
    virtual void setupStencilForDrawingOnPlane(GLint plane) override;
};

class RawStencilBufferTest3 : public RawStencilBufferTest
{
public:
    CREATE_FUNC(RawStencilBufferTest3);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane) override;
    virtual void setupStencilForDrawingOnPlane(GLint plane) override;
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
    virtual void setupStencilForClippingOnPlane(GLint plane) override;
    virtual void setupStencilForDrawingOnPlane(GLint plane) override;
};

class RawStencilBufferTest5 : public RawStencilBufferTestAlphaTest
{
public:
    CREATE_FUNC(RawStencilBufferTest5);

    virtual std::string subtitle() const override;
    virtual void setupStencilForClippingOnPlane(GLint plane) override;
    virtual void setupStencilForDrawingOnPlane(GLint plane) override;
};

class RawStencilBufferTest6 : public RawStencilBufferTestAlphaTest
{
public:
    CREATE_FUNC(RawStencilBufferTest6);

    virtual void setupStencilForClippingOnPlane(GLint plane) override;
    virtual void setupStencilForDrawingOnPlane(GLint plane) override;

    // override
    virtual void setup() override;
    virtual std::string subtitle() const override;
};

//#endif //COCOS2D_DEBUG > 1

class ClippingToRenderTextureTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(ClippingToRenderTextureTest);

    void expectedBehaviour();
    void reproduceBug();

    // override
    virtual void setup() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ClippingRectangleNodeTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(ClippingRectangleNodeTest);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;
};


class ClippingNodeTestScene : public TestScene
{
public:
    CREATE_FUNC(ClippingNodeTestScene);

    virtual void runThisTest();
};

#endif //__CLIPPINGNODETEST_H__
