/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class EaseSpriteDemo : public BaseTest
{
protected:
    Sprite*    _grossini;
    Sprite*    _tamara;
    Sprite*    _kathia;

    std::string    _title;

public:
    EaseSpriteDemo(void);
    ~EaseSpriteDemo(void);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    
    void centerSprites(unsigned int numberOfSprites);
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    void positionForTwo();
};

class SpriteEase : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;

    void testStopAction(float dt);
};

class SpriteEaseInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseExponential : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseExponentialInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseSine : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseSineInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseElastic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseElasticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseBounce : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseBounceInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseBack : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseBackInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseBezier : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuadratic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuadraticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuartic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuarticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuintic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseQuinticInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};


class SpriteEaseCircle : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseCircleInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseCubic : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteEaseCubicInOut : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string title() const override;
};
class SpeedTest : public EaseSpriteDemo
{
public:
    void onEnter();
    virtual std::string subtitle() const override;

    void altertime(float dt);
};

class ActionsEaseTestScene : public TestScene
{
public:
    virtual void runThisTest();
};


#endif
