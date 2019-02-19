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

#ifndef _EFFECT_ADVANCED_TEST_H_
#define _EFFECT_ADVANCED_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(EffectAdvanceTests);

class EffectAdvanceBaseTest: public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;

    std::string    _title;

    cocos2d::Node* _bgNode;
    cocos2d::Node* _target1;
    cocos2d::Node* _target2;

public:
    virtual void onEnter() override;
    ~EffectAdvanceBaseTest(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Effect1 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect1);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect2 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect2);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect3 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect3);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect4 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect4);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class Effect5 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Effect5);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
};

class Issue631 : public EffectAdvanceBaseTest
{
public:
    CREATE_FUNC(Issue631);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
