#ifndef _KEYBOARD_TEST_H_
#define _KEYBOARD_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class KeyboardTest : public Layer
{
public:
    KeyboardTest();
    ~KeyboardTest();

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
    LabelTTF*            _label;
};

class KeyboardTestScene : public TestScene
{
public:
    virtual void runThisTest();
};


#endif
