#ifndef __CLIPPINGNODETEST_H__
#define __CLIPPINGNODETEST_H__

#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"
#include <list>

DEFINE_TEST_SUITE(ClippingNodeTests);

class BaseClippingNodeTest : public TestCase
{
public:
    CREATE_FUNC(BaseClippingNodeTest);

    ~BaseClippingNodeTest();
    virtual bool init() override;

	virtual std::string title() const override;
    virtual void setup();
};

class BasicTest : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(BasicTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;

	virtual cocos2d::Action* actionRotate();
	virtual cocos2d::Action* actionScale();

	virtual cocos2d::DrawNode* shape();
	virtual cocos2d::Sprite* grossini();

	virtual cocos2d::Node* stencil();
	virtual cocos2d::ClippingNode* clipper();
	virtual cocos2d::Node* content();
};

class ShapeTest : public BasicTest
{
public:
    CREATE_FUNC(ShapeTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual cocos2d::Node* stencil() override;
    virtual cocos2d::Node* content() override;
};

class ShapeInvertedTest : public ShapeTest
{
public:
    CREATE_FUNC(ShapeInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual cocos2d::ClippingNode* clipper() override;
};

class SpriteTest : public BasicTest
{
public:
    CREATE_FUNC(SpriteTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual cocos2d::Node* stencil() override;
    virtual cocos2d::ClippingNode* clipper() override;
    virtual cocos2d::Node* content() override;
};

class SpriteNoAlphaTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteNoAlphaTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual cocos2d::ClippingNode* clipper() override;
};

class SpriteInvertedTest : public SpriteTest
{
public:
    CREATE_FUNC(SpriteInvertedTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual cocos2d::ClippingNode* clipper() override;
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
    void pokeHoleAtPoint(cocos2d::Vec2 point);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	cocos2d::ClippingNode* _outerClipper;
    cocos2d::Node* _holes;
    cocos2d::Node* _holesStencil;
};

class ScrollViewDemo : public BaseClippingNodeTest
{
public:
    CREATE_FUNC(ScrollViewDemo);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void setup() override;
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	bool _scrolling;
    cocos2d::Vec2 _lastPoint;
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
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	virtual void setupStencilForClippingOnPlane(GLint plane);
	virtual void setupStencilForDrawingOnPlane(GLint plane);

protected:
    std::list<cocos2d::CustomCommand> _renderCmds;
    void onEnableStencil();
    void onDisableStencil();
    void onBeforeDrawClip(int planeIndex, const cocos2d::Vec2& pt);
    void onBeforeDrawSprite(int planeIndex, const cocos2d::Vec2& pt);
protected:
    cocos2d::Vector<cocos2d::Sprite*> _sprites;
    cocos2d::Vector<cocos2d::Sprite*> _spritesStencil;
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

#endif //__CLIPPINGNODETEST_H__
