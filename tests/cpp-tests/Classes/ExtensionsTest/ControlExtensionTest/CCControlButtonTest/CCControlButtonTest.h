/*
 * ControlButtonTest.h
 *
 * Copyright (c) 2011 Yannick Loriot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __CCCONTROLBUTTONTEST_H__
#define __CCCONTROLBUTTONTEST_H__

#include "../CCControlScene.h"

class ControlButtonTest_HelloVariableSize : public ControlScene
{
public:
    CREATE_FUNC(ControlButtonTest_HelloVariableSize);

    virtual bool init() override;
    /** Creates and return a button with a default background and title color. */
    cocos2d::extension::ControlButton* standardButtonWithTitle(const char * title);
};

class ControlButtonTest_Event : public ControlScene
{
public:
    CREATE_FUNC(ControlButtonTest_Event);

    ControlButtonTest_Event();
    ~ControlButtonTest_Event();

    virtual bool init() override;

    void touchDownAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchDragInsideAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchDragOutsideAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchDragEnterAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchDragExitAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchUpInsideAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchUpOutsideAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchCancelAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void touchBitmaskAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
protected:
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _displayValueLabel, DisplayValueLabel)
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _displayBitmaskLabel, DisplayBitmaskLabel)
    
};

class ControlButtonTest_Styling : public ControlScene
{
public:
    virtual bool init() override;
    cocos2d::extension::ControlButton* standardButtonWithTitle(const char *title);
    CREATE_FUNC(ControlButtonTest_Styling);
};


#endif /* __CCCONTROLBUTTONTEST_H__ */
