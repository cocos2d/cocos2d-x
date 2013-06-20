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

USING_NS_CC_EXT;

class ControlButtonTest_HelloVariableSize : public ControlScene
{
public:
    bool init();
    /** Creates and return a button with a default background and title color. */
    ControlButton *standardButtonWithTitle(const char * title);

    CONTROL_SCENE_CREATE_FUNC(ControlButtonTest_HelloVariableSize)
};

class ControlButtonTest_Event : public ControlScene
{
public:
    ControlButtonTest_Event();
    ~ControlButtonTest_Event();
    bool init();
    void touchDownAction(Object *sender, ControlEvent controlEvent);
    void touchDragInsideAction(Object *sender, ControlEvent controlEvent);
    void touchDragOutsideAction(Object *sender, ControlEvent controlEvent);
    void touchDragEnterAction(Object *sender, ControlEvent controlEvent);
    void touchDragExitAction(Object *sender, ControlEvent controlEvent);
    void touchUpInsideAction(Object *sender, ControlEvent controlEvent);
    void touchUpOutsideAction(Object *sender, ControlEvent controlEvent);
    void touchCancelAction(Object *sender, ControlEvent controlEvent);
protected:
    CC_SYNTHESIZE_RETAIN(LabelTTF *, _displayValueLabel, DisplayValueLabel)
    CONTROL_SCENE_CREATE_FUNC(ControlButtonTest_Event)
};


class ControlButtonTest_Styling : public ControlScene
{
public:
    bool init();
    ControlButton *standardButtonWithTitle(const char *title);
    CONTROL_SCENE_CREATE_FUNC(ControlButtonTest_Styling)
};


#endif /* __CCCONTROLBUTTONTEST_H__ */
