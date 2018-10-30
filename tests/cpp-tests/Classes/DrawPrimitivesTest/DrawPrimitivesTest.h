/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

protected:
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    cocos2d::CustomCommand _customCommand;
};

class DrawNodeTest : public DrawPrimitivesBaseTest
{
public:
    CREATE_FUNC(DrawNodeTest);

    DrawNodeTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PrimitivesCommandTest : public DrawPrimitivesBaseTest
{
public:
    CREATE_FUNC(PrimitivesCommandTest);

    PrimitivesCommandTest();
    virtual ~PrimitivesCommandTest();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    cocos2d::Texture2D* _texture;
    cocos2d::GLProgramState* _programState;
    cocos2d::Primitive* _primitive;

    cocos2d::PrimitiveCommand _primitiveCommand;
};

class Issue11942Test : public DrawPrimitivesBaseTest
{
public:
    CREATE_FUNC(Issue11942Test);

    Issue11942Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

};

#endif
