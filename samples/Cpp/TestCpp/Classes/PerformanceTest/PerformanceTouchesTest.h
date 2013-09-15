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

    virtual void showCurrentTest() override;
    virtual void onEnter() override;
    virtual std::string title();
    virtual void update(float dt) override;

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

    virtual void onEnter() override;
    virtual std::string title() override;

    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchMoved(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
    virtual void onTouchCancelled(Touch* touch, Event* event) override;
};

class TouchesPerformTest2 : public TouchesMainScene
{
public:
    TouchesPerformTest2(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter() override;
    virtual std::string title() override;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event) override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event) override;
};

class TouchesPerformTest3 : public PerformBasicLayer
{
public:
    TouchesPerformTest3(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
    : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }
    
    virtual void onEnter() override;
    virtual std::string title();
    virtual void showCurrentTest() override;
};

void runTouchesTest();

#endif
