#ifndef _KEYPAD_TEST_H_
#define _KEYPAD_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class KeypadTest : public Layer
{
public:
    KeypadTest();
    ~KeypadTest();

    virtual void keyBackClicked();
    virtual void keyMenuClicked();

private:
    LabelTTF*            _label;
};

class KeypadTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
