/*
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2012 Yannick Loriot
 * http://yannickloriot.com
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

#ifndef __CCCONTROLSTEPPERTEST_H__
#define __CCCONTROLSTEPPERTEST_H__

#include "../CCControlScene.h"

class ControlStepperTest : public ControlScene
{
public:
    ControlStepperTest();
    virtual ~ControlStepperTest();
    bool init();
    /** Creates and returns a new ControlStepper. */
    ControlStepper* makeControlStepper();

    /** Callback for the change value. */
    void valueChanged(Object *sender, Control::EventType controlEvent);
protected:
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _displayValueLabel, DisplayValueLabel)
    CONTROL_SCENE_CREATE_FUNC(ControlStepperTest)
};

#endif /* __CCCONTROLSTEPPERTEST_H__ */

