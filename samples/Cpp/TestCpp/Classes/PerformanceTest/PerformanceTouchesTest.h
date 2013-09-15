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
    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);
    virtual void ccTouchCancelled(Touch* touch, Event* event);
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
    virtual void registerWithTouchDispatcher();

    virtual void ccTouchesBegan(Set* touches, Event* event);
    virtual void ccTouchesMoved(Set* touches, Event* event);
    virtual void ccTouchesEnded(Set* touches, Event* event);
    virtual void ccTouchesCancelled(Set* touches, Event* event);
};

void runTouchesTest();

#endif
