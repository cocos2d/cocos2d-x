#ifndef __PERFORMANCE_TOUCHES_TEST_H__
#define __PERFORMANCE_TOUCHES_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceTouchesTests);

class TouchesMainScene : public TestCase
{
public:
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
    CREATE_FUNC(TouchesPerformTest1);

    virtual void onEnter() override;
    virtual std::string title() const override;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
};

class TouchesPerformTest2 : public TouchesMainScene
{
public:
    CREATE_FUNC(TouchesPerformTest2);

    virtual void onEnter() override;
    virtual std::string title() const override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class TouchesPerformTest3 : public TestCase
{
public:
    CREATE_FUNC(TouchesPerformTest3);

    virtual void onEnter() override;
    virtual std::string title() const;
};


#endif
