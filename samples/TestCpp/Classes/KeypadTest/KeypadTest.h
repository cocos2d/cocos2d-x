#ifndef _KEYPAD_TEST_H_
#define _KEYPAD_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class KeypadTest : public CCLayer
{
public:
    KeypadTest();
    ~KeypadTest();

    virtual void keyBackClicked();
    virtual void keyMenuClicked();

private:
    CCLabelTTF*            m_pLabel;
};

class KeypadTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
