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

#ifndef __UNIT_TEST__
#define __UNIT_TEST__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(UnitTests);

class UnitTestDemo : public TestCase
{
public:
    virtual std::string title() const override;
};

//-------------------------------------

class TemplateVectorTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateVectorTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Vector<Node*>& vec) const;
};

class TemplateMapTest : public UnitTestDemo
{
public:
    CREATE_FUNC(TemplateMapTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Map<std::string, cocos2d::Node*>& map) const;
};

class ValueTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ValueTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void constFunc(const cocos2d::Value& value) const;
};

class UTFConversionTest : public UnitTestDemo
{
public:
    CREATE_FUNC(UTFConversionTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class UIHelperSubStringTest : public UnitTestDemo
{
public:
    CREATE_FUNC(UIHelperSubStringTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ParseIntegerListTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ParseIntegerListTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ParseUriTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ParseUriTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class MathUtilTest : public UnitTestDemo
{
public:
    CREATE_FUNC(MathUtilTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ResizableBufferAdapterTest : public UnitTestDemo
{
public:
    CREATE_FUNC(ResizableBufferAdapterTest);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


#endif /* __UNIT_TEST__ */
