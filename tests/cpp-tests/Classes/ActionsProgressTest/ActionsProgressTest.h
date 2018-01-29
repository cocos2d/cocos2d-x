/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef _ACTIONS__PROGRESS_TEST_H_
#define _ACTIONS__PROGRESS_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ActionsProgressTests);

class SpriteDemo : public TestCase
{
public:
    SpriteDemo(void);
    ~SpriteDemo(void);

    virtual std::string title() const override;
    virtual void onEnter() override;
};

class SpriteProgressToRadial : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressToRadial);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressToHorizontal : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressToHorizontal);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressToVertical : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressToVertical);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressToRadialMidpointChanged : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressToRadialMidpointChanged);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressBarVarious : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressBarVarious);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressBarTintAndFade : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressBarTintAndFade);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteProgressWithSpriteFrame : public SpriteDemo
{
public:
    CREATE_FUNC(SpriteProgressWithSpriteFrame);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif // _ACTIONS__PROGRESS_TEST_H_
