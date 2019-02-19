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

#ifndef __ZWOPTEX_TEST_H__
#define __ZWOPTEX_TEST_H__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ZwoptexTests);

class ZwoptexTest : public TestCase
{
public:
};

class ZwoptexGenericTest : public ZwoptexTest
{
public:
    CREATE_FUNC(ZwoptexGenericTest);

    virtual ~ZwoptexGenericTest();

    virtual void onEnter() override;
    void flipSprites(float dt);
    void startIn05Secs(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    cocos2d::Sprite*  sprite1;
    cocos2d::Sprite*  sprite2;
    int counter;
};

#endif // __ZWOPTEX_TEST_H__
