/*
 * CCControlButtonTest.h
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

USING_NS_CC_EXT;

class CCControlButtonTest_HelloVariableSize : public CCControlScene
{
public:
    bool init();
    /** Creates and return a button with a default background and title color. */
    CCControlButton *standardButtonWithTitle(const char * title);

    CONTROL_SCENE_CREATE_FUNC(CCControlButtonTest_HelloVariableSize)
};

class CCControlButtonTest_Event : public CCControlScene
{
public:
    CCControlButtonTest_Event();
    ~CCControlButtonTest_Event();
    bool init();
    void touchDownAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragInsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragOutsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragEnterAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragExitAction(CCObject *sender, CCControlEvent controlEvent);
    void touchUpInsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchUpOutsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchCancelAction(CCObject *sender, CCControlEvent controlEvent);
protected:
    CC_SYNTHESIZE_RETAIN(CCLabelTTF *, m_pDisplayValueLabel, DisplayValueLabel)
    CONTROL_SCENE_CREATE_FUNC(CCControlButtonTest_Event)
};


class CCControlButtonTest_Styling : public CCControlScene
{
public:
    bool init();
    CCControlButton *standardButtonWithTitle(const char *title);
    CONTROL_SCENE_CREATE_FUNC(CCControlButtonTest_Styling)
};


#endif /* __CCCONTROLBUTTONTEST_H__ */
