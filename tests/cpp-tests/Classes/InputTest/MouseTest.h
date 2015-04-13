#ifndef __MOUSE_TEST_H_
#define __MOUSE_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(MouseTests);

class BaseMouseTest : public TestCase
{
public:
    
};

class MouseEventTest : public BaseMouseTest
{
public:
    CREATE_FUNC(MouseEventTest);
    MouseEventTest();
    ~MouseEventTest();

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onMouseScroll(cocos2d::Event* event);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    cocos2d::Label*   _labelAction;
    cocos2d::Label*   _labelPosition;
    cocos2d::EventListenerMouse* _mouseListener;
};

class HideMouseTest : public BaseMouseTest
{
public:
    CREATE_FUNC(HideMouseTest);
    HideMouseTest();
    ~HideMouseTest();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    cocos2d::EventListenerMouse* _lis;
};

#endif
