#ifndef _TRANSITIONS_TEST_H_
#define _TRANSITIONS_TEST_H_

#include "../testBasic.h"

USING_NS_CC;

class TransitionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class TestLayer1 : public Layer
{
public:
    TestLayer1(void);
    ~TestLayer1(void);

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    void step(float dt);

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onExit();
};

class TestLayer2 : public Layer
{
public:
    TestLayer2(void);
    ~TestLayer2(void);

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    void step(float dt);

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onExit();
};

#endif
