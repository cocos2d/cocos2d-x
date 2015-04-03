#ifndef _DRAW_PRIMITIVES_TEST_H_
#define _DRAW_PRIMITIVES_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

#include <string>

DEFINE_TEST_SUITE(DrawPrimitivesTests);

class DrawPrimitivesBaseTest : public TestCase
{
public:
    virtual std::string title() const override;
};

class DrawPrimitivesTest : public DrawPrimitivesBaseTest
{
public:
    CREATE_FUNC(DrawPrimitivesTest);
    DrawPrimitivesTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
    void onDraw(const Mat4 &transform, uint32_t flags);
    CustomCommand _customCommand;
};

class DrawNodeTest : public DrawPrimitivesBaseTest
{
public:
    CREATE_FUNC(DrawNodeTest);

    DrawNodeTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
