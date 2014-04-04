#ifndef _KEYPAD_TEST_H_
#define _KEYPAD_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class KeypadTest : public Layer
{
public:
    KeypadTest();
    ~KeypadTest();

    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

private:
    Label*            _label;
};

class KeypadTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
