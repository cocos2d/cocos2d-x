#ifndef __PERFORMANCE_TOUCHES_TEST_H__
#define __PERFORMANCE_TOUCHES_TEST_H__

#include "PerformanceTest.h"

class TouchesMainScene : public PerformBasicLayer
{
public:
    TouchesMainScene(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void showCurrentTest();
    virtual void onEnter();
    virtual std::string title();
    virtual void update(float dt);

protected:
    LabelBMFont * _plabel;
    int                numberOfTouchesB;
    int                numberOfTouchesM;
    int                numberOfTouchesE;
    int                numberOfTouchesC;
    float            elapsedTime;
};

class TouchesPerformTest1 : public TouchesMainScene
{
public:
    TouchesPerformTest1(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter();
    virtual std::string title();
//    virtual void registerWithTouchDispatcher();

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
};

class TouchesPerformTest2 : public TouchesMainScene
{
public:
    TouchesPerformTest2(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter();
    virtual std::string title();
//    virtual void registerWithTouchDispatcher();

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event);
};

void runTouchesTest();

#endif
