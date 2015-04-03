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

    void onMouseDown(Event* event);
    void onMouseUp(Event* event);
    void onMouseMove(Event* event);
    void onMouseScroll(Event* event);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    Label*   _labelAction;
    Label*   _labelPosition;
    EventListenerMouse* _mouseListener;
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
    EventListenerMouse* _lis;
};

#endif
