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

#ifndef _ACTIONS__EASE_TEST_H_
#define _ACTIONS__EASE_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ActionsEaseTests);

class EaseSpriteDemo : public TestCase
{
protected:
    cocos2d::Sprite*    _grossini;
    cocos2d::Sprite*    _tamara;
    cocos2d::Sprite*    _kathia;

    std::string    _title;

public:
    EaseSpriteDemo();
    ~EaseSpriteDemo();

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    
    void centerSprites(unsigned int numberOfSprites);

    void positionForTwo();
};

class SpriteEase : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEase);

    void onEnter() override;
    virtual std::string subtitle() const override;

    void testStopAction(float dt);
};

class SpriteEaseInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseExponential : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseExponential);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseExponentialInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseExponentialInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseSine : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseSine);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseSineInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseSineInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseElastic : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseElastic);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseElasticInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseElasticInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseBounce : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseBounce);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseBounceInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseBounceInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseBack : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseBack);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseBackInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseBackInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseBezier : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseBezier);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuadratic : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuadratic);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuadraticInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuadraticInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuartic : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuartic);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuarticInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuarticInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuintic : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuintic);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseQuinticInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseQuinticInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};


class SpriteEaseCircle : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseCircle);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseCircleInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseCircleInOut);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseCubic : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseCubic);

    void onEnter() override;
    virtual std::string subtitle() const override;
};

class SpriteEaseCubicInOut : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpriteEaseCubicInOut);

    void onEnter() override;
    virtual std::string title() const override;
};
class SpeedTest : public EaseSpriteDemo
{
public:
    CREATE_FUNC(SpeedTest);

    void onEnter() override;
    virtual std::string subtitle() const override;

    void altertime(float dt);
};


#endif
