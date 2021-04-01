/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
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

#ifndef __TestCpp__UITextTest__
#define __TestCpp__UITextTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UITextTests);

class UITextTest : public UIScene
{
public:
    CREATE_FUNC(UITextTest);

    virtual bool init() override;
};

class UITextTest_LineWrap : public UIScene
{
public:
    CREATE_FUNC(UITextTest_LineWrap);

    virtual bool init() override;
};


class UILabelTest_Effect : public UIScene
{
public:
    CREATE_FUNC(UILabelTest_Effect);

    virtual bool init() override;
};
 

class UITextTest_TTF : public UIScene
{
public:
    CREATE_FUNC(UITextTest_TTF);

    virtual bool init() override;
};

class UITextTest_IgnoreContentSize : public UIScene
{
public:
    CREATE_FUNC(UITextTest_IgnoreContentSize);

    virtual bool init() override;
};

class UITextTest_Clone : public UIScene
{
public:
    CREATE_FUNC(UITextTest_Clone);

    virtual bool init() override;
};

class Issue16073Test : public UIScene
{
public:
    CREATE_FUNC(Issue16073Test);

    virtual bool init() override;
};

#endif /* defined(__TestCpp__UITextTest__) */
