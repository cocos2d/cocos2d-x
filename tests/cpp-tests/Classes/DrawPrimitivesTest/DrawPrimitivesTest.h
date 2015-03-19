#ifndef _DRAW_PRIMITIVES_TEST_H_
#define _DRAW_PRIMITIVES_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

#include <string>

class BaseLayer : public BaseTest
{
public:
    BaseLayer();
    
    void restartCallback(Ref* sender) override;
    void nextCallback(Ref* sender) override;
    void backCallback(Ref* sender) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};

class DrawPrimitivesTest : public BaseLayer
{
public:
    DrawPrimitivesTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
    void onDraw(const Mat4 &transform, uint32_t flags);
    CustomCommand _customCommand;
};

class DrawNodeTest : public BaseLayer
{
public:
    DrawNodeTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DrawPrimitivesTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
