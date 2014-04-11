#ifndef __MOUSE_TEST_H_
#define __MOUSE_TEST_H_

#include "cocos2d.h"
#include "../testScene.h"

class MouseTest : public Layer
{
public:
    MouseTest();
    ~MouseTest();

    void onMouseDown(Event* event);
    void onMouseUp(Event* event);
    void onMouseMove(Event* event);
    void onMouseScroll(Event* event);

private:
    Label*   _labelAction;
    Label*   _labelPosition;
    EventListenerMouse* _mouseListener;
};

class MouseTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
