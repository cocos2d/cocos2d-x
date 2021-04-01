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

#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

#include "../BaseTest.h"


DEFINE_TEST_SUITE(TouchesTests);

class PongScene : public TestCase
{
public:
    CREATE_FUNC(PongScene);
    
    virtual bool init() override;
};

class Ball;
class Paddle;
class PongLayer : public cocos2d::Layer
{
private:
    Ball*       _ball;
    cocos2d::Vector<Paddle*>    _paddles;
    cocos2d::Vec2     _ballStartingVelocity; 
public:
    CREATE_FUNC(PongLayer);
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

class ForceTouchTest : public TestCase
{
public:
    CREATE_FUNC(ForceTouchTest);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
protected:
    ForceTouchTest();
    virtual ~ForceTouchTest();

    cocos2d::Label * _infoLabel;
};

#endif
