#ifndef _NODE_TEST_H_
#define _NODE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class TestCocosNodeDemo : public BaseTest
{
public:
    TestCocosNodeDemo(void);
    ~TestCocosNodeDemo(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class Test2 : public TestCocosNodeDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class Test4 : public TestCocosNodeDemo
{
public:
    Test4();
    void delay2(float dt);
    void delay4(float dt);

    virtual std::string title() const override;
};

class Test5 : public TestCocosNodeDemo
{
public:
    Test5();
    void addAndRemove(float dt);

    virtual std::string title() const override;
};

class Test6 : public TestCocosNodeDemo
{
public:
    Test6();
    void addAndRemove(float dt);

    virtual std::string title() const override;
};

class StressTest1 : public TestCocosNodeDemo
{
    void shouldNotCrash(float dt);
    void removeMe(Node* node);
public:
    StressTest1();

    virtual std::string title() const override;
};

class StressTest2 : public TestCocosNodeDemo
{
    void shouldNotLeak(float dt);
public:
    StressTest2();

    virtual std::string title() const override;
};

class SchedulerTest1 : public TestCocosNodeDemo
{
public:
    SchedulerTest1();
    void doSomething(float dt);

    virtual std::string title() const override;
};

class NodeToWorld : public TestCocosNodeDemo
{
public:
    NodeToWorld();
    virtual std::string title() const override;
};

class CameraOrbitTest : public TestCocosNodeDemo
{
public:
    CameraOrbitTest();

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title() const override;
};

class CameraZoomTest : public TestCocosNodeDemo
{
    float    _z;
public:
    CameraZoomTest();
    void update(float dt);

    virtual void onEnter();
    virtual void onExit();

    virtual std::string title() const override;
};

class CameraCenterTest : public TestCocosNodeDemo
{
public:
    CameraCenterTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ConvertToNode : public TestCocosNodeDemo
{
public:
    ConvertToNode();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class NodeOpaqueTest : public TestCocosNodeDemo
{
public:
    NodeOpaqueTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class NodeNonOpaqueTest : public TestCocosNodeDemo
{
public:
    NodeNonOpaqueTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CocosNodeTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

//CCLayer* nextAction();

#endif
