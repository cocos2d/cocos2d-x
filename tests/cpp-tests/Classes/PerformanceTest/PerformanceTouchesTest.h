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

    virtual std::string title() const;

    virtual void showCurrentTest() override;
    virtual void onEnter() override;
    virtual void update(float dt) override;

protected:
    cocos2d::Label*  _plabel;
    int numberOfTouchesB;
    int numberOfTouchesM;
    int numberOfTouchesE;
    int numberOfTouchesC;
    float elapsedTime;
};

class TouchesPerformTest1 : public TouchesMainScene
{
public:
    TouchesPerformTest1(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter() override;
    virtual std::string title() const override;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) override;
};

class TouchesPerformTest2 : public TouchesMainScene
{
public:
    TouchesPerformTest2(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter() override;
    virtual std::string title() const override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
};

class TouchesPerformTest3 : public PerformBasicLayer
{
public:
    TouchesPerformTest3(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
    : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }
    
    virtual void onEnter() override;
    virtual std::string title() const;
    virtual void showCurrentTest() override;
};

void runTouchesTest();

#endif
