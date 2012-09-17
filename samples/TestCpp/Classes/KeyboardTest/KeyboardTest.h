//
//  KeyboardTest.h
//  TestCpp
//
//  Created by William DeVore on 9/17/12 A.
//
//

#ifndef _KEYBOARD_TEST_H_
#define _KEYBOARD_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"


class KeyboardTest : public CCLayer, public CCKeyboardDelegate
{
public:
    KeyboardTest();
    ~KeyboardTest();
    
#pragma mark CCKeyboardDelegate methods
    void keyUp(CCKeyboard* pKeyboard);
    
    void keyDown(CCKeyboard* pKeyboard);
    
    void flagsChanged(CCKeyboard* pKeyboard);
    
#pragma mark CCLayer (parent) methods
    void onExit();
    void onEnterTransitionDidFinish();

private:
    CCLabelTTF*            m_pLabel;
    bool                m_bShow;
};

class KeyboardTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
