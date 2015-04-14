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

#ifndef _NODE_TEST_H_
#define _NODE_TEST_H_

////----#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(CocosNodeTests);

class TestCocosNodeDemo : public TestCase
{
public:
    virtual std::string title() const override;

protected:
    TestCocosNodeDemo();
    virtual ~TestCocosNodeDemo();

    cocos2d::Director::Projection _preProjection;
};

class NodeTest2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeTest2);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class NodeTest4 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeTest4);
    void delay2(float dt);
    void delay4(float dt);

    virtual std::string subtitle() const override;

protected:
    NodeTest4();
};

class NodeTest5 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeTest5);

    void addAndRemove(float dt);
    virtual std::string subtitle() const override;

protected:
    NodeTest5();
};

class NodeTest6 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeTest6);
    void addAndRemove(float dt);
    virtual std::string subtitle() const override;

protected:
    NodeTest6();
};

class StressTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(StressTest1);
    void shouldNotCrash(float dt);
    void removeMe(Node* node);
    virtual std::string subtitle() const override;

protected:
    StressTest1();
};

class StressTest2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(StressTest2);
    void shouldNotLeak(float dt);
    virtual std::string subtitle() const override;

protected:
    StressTest2();
};

class SchedulerTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(SchedulerTest1);
    void doSomething(float dt);
    virtual std::string subtitle() const override;

protected:
    SchedulerTest1();
};

class SchedulerCallbackTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(SchedulerCallbackTest);
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

protected:
    float _total;
    SchedulerCallbackTest();
};


class NodeToWorld : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeToWorld);
    virtual std::string subtitle() const override;

protected:
    NodeToWorld();
};

class NodeToWorld3D : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeToWorld3D);
    virtual std::string subtitle() const override;

protected:
    NodeToWorld3D();
};

class CameraOrbitTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraOrbitTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string subtitle() const override;

protected:
    CameraOrbitTest();
};

class CameraZoomTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraZoomTest);
    void update(float dt) override;

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string subtitle() const override;

protected:
    CameraZoomTest();
    float    _z;
};

class CameraCenterTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraCenterTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    CameraCenterTest();
};

class CameraTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraTest1);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    CameraTest1();

    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
};

class CameraTest2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraTest2);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    CameraTest2();

    cocos2d::Sprite* _sprite1;
    cocos2d::Sprite* _sprite2;
};

class ConvertToNode : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(ConvertToNode);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    ConvertToNode();
};

class NodeOpaqueTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeOpaqueTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    NodeOpaqueTest();
};

class NodeNonOpaqueTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeNonOpaqueTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    NodeNonOpaqueTest();
};

class NodeGlobalZValueTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeGlobalZValueTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual void update(float dt) override;

protected:
    NodeGlobalZValueTest();
    cocos2d::Sprite* _sprite;
};

class NodeNormalizedPositionTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeNormalizedPositionTest1);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    NodeNormalizedPositionTest1();
};

class NodeNormalizedPositionTest2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeNormalizedPositionTest2);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    NodeNormalizedPositionTest2();

    void update(float dt) override;
    cocos2d::Size _copyContentSize;
    float _accum;
};

class NodeNormalizedPositionBugTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeNormalizedPositionBugTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    NodeNormalizedPositionBugTest();
    
    void update(float dt) override;
    float _accum;
    cocos2d::Sprite* sprite;
};

class NodeNameTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeNameTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void onEnter() override;

    void test(float dt);
};

#endif
