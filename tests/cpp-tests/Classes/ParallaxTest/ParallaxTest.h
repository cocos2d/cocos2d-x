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

#ifndef _PARALLAX_TEST_H_
#define _PARALLAX_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ParallaxTests);

class ParallaxDemo : public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;
};

class Parallax1 : public ParallaxDemo
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;
    cocos2d::MotionStreak*        _streak;

public:
    CREATE_FUNC(Parallax1);
    Parallax1();
    virtual std::string title() const override;
};

class Parallax2 : public ParallaxDemo
{
protected:
    cocos2d::Node*        _root;
    cocos2d::Node*        _target;
    cocos2d::MotionStreak*        _streak;

public:
    CREATE_FUNC(Parallax2);
    Parallax2();
    
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    virtual std::string title() const override;
};

class Issue2572 : public ParallaxDemo
{
protected:
    cocos2d::ParallaxNode* _paraNode;
    float _moveTimer;
    float _addTimer;
    cocos2d::Vector<cocos2d::Sprite*> _childList;
    ssize_t _preListSize;
    int _printCount;
    
    float _addChildStep;
    float _wholeMoveTime;
    cocos2d::Vec2 _wholeMoveSize;

    virtual void update(float dt) override;
    
public:
    CREATE_FUNC(Issue2572);
    Issue2572();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
