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

#ifndef _MOTION_STREAK_TEST_H_
#define _MOTION_STREAK_TEST_H_

#include "../BaseTest.h"


DEFINE_TEST_SUITE(MotionStreakTests);

class MotionStreakTest : public TestCase
{
public:
    MotionStreakTest(void);
    ~MotionStreakTest(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void modeCallback(cocos2d::Ref* sender);
protected:
    cocos2d::MotionStreak* _streak;
};

class MotionStreakTest1 : public MotionStreakTest
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;

public:
    CREATE_FUNC(MotionStreakTest1);
    virtual void onEnter() override;
    void onUpdate(float delta);
    virtual std::string title() const override;
};

class MotionStreakTest2 : public MotionStreakTest
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;

public:
    CREATE_FUNC(MotionStreakTest2);
    virtual void onEnter() override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual std::string title() const override;
};

class Issue1358 : public MotionStreakTest
{
public:
    CREATE_FUNC(Issue1358);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void update(float dt) override;
private:
    cocos2d::Vec2 _center;
    float _radius;
    float _angle;
};

class Issue12226 : public MotionStreakTest
{
public:
    CREATE_FUNC(Issue12226);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};


#endif
