#ifndef _KEYBOARD_TEST_H_
#define _KEYBOARD_TEST_H_

#ifdef KEYBOARD_SUPPORT

#include "cocos2d.h"
#include "../testBasic.h"

class KeyboardTest : public CCLayer
{
public:
    KeyboardTest();
    ~KeyboardTest();

    virtual void keyPressed(int keyCode);
    virtual void keyReleased(int keyCode);

private:
    CCLabelTTF*            _label;
};

class KeyboardTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif

#endif
