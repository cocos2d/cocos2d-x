#ifndef _KEYBOARD_TEST_H_
#define _KEYBOARD_TEST_H_

#ifdef CC_KEYBOARD_SUPPORT

#include "cocos2d.h"
#include "../testBasic.h"

class KeyboardTest : public Layer
{
public:
    KeyboardTest();
    ~KeyboardTest();

    virtual void onKeyPressed(KeyboardEvent::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(KeyboardEvent::KeyCode keyCode, Event* event);

private:
    LabelTTF*            _label;
};

class KeyboardTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif

#endif
