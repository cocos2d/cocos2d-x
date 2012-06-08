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
    CCLabelBMFont * m_plabel;
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

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
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

    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
};

void runTouchesTest();

#endif
