#ifndef _NODE_TEST_H_
#define _NODE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class TestCocosNodeDemo : public BaseTest
{
public:

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

protected:
    TestCocosNodeDemo();
    virtual ~TestCocosNodeDemo();
};

class Test2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(Test2);
    virtual void onEnter();
    virtual std::string title() const override;
};

class Test4 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(Test4);
    void delay2(float dt);
    void delay4(float dt);

    virtual std::string title() const override;

protected:
    Test4();
};

class Test5 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(Test5);

    void addAndRemove(float dt);
    virtual std::string title() const override;

protected:
    Test5();
};

class Test6 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(Test6);
    void addAndRemove(float dt);
    virtual std::string title() const override;

protected:
    Test6();
};

class StressTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(StressTest1);
    void shouldNotCrash(float dt);
    void removeMe(Node* node);
    virtual std::string title() const override;

protected:
    StressTest1();
};

class StressTest2 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(StressTest2);
    void shouldNotLeak(float dt);
    virtual std::string title() const override;

protected:
    StressTest2();
};

class SchedulerTest1 : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(SchedulerTest1);
    void doSomething(float dt);
    virtual std::string title() const override;

protected:
    SchedulerTest1();
};

class NodeToWorld : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(NodeToWorld);
    virtual std::string title() const override;

protected:
    NodeToWorld();
};

class CameraOrbitTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraOrbitTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;

protected:
    CameraOrbitTest();
};

class CameraZoomTest : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(CameraZoomTest);
    void update(float dt);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;

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

protected:
    CameraCenterTest();
};

class ConvertToNode : public TestCocosNodeDemo
{
public:
    CREATE_FUNC(ConvertToNode);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
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

class CocosNodeTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
