/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
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

#ifndef __CCCONTROLSTEPPER_H__
#define __CCCONTROLSTEPPER_H__

#include "CCControl.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

typedef enum
{
    kControlStepperPartMinus,
    kControlStepperPartPlus,
    kControlStepperPartNone,
} ControlStepperPart;

class ControlStepper : public Control
{
public:
    ControlStepper();
    virtual ~ControlStepper();

    bool initWithMinusSpriteAndPlusSprite(Sprite *minusSprite, Sprite *plusSprite);
    static ControlStepper* create(Sprite *minusSprite, Sprite *plusSprite);
    virtual void setWraps(bool wraps);
    virtual void setMinimumValue(double minimumValue);
    virtual void setMaximumValue(double maximumValue);
    virtual void setValue(double value);
    virtual double getValue();
    virtual void setStepValue(double stepValue);
    virtual void setValueWithSendingEvent(double value, bool send);
    virtual bool isContinuous();
    void update(float dt);

    //events
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);

protected:
    // Weak links to children
	CC_SYNTHESIZE_RETAIN(Sprite*, _minusSprite, MinusSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, _plusSprite, PlusSprite)
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _minusLabel, MinusLabel)
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _plusLabel, PlusLabel)
    
    /** Update the layout of the stepper with the given touch location. */
    void updateLayoutUsingTouchLocation(Point location);

    /** Set the numeric value of the stepper. If send is true, the ControlEventValueChanged is sent. */
    void setValue(double value, bool send);

    /** Start the autorepeat increment/decrement. */
    void startAutorepeat();

    /** Stop the autorepeat. */
    void stopAutorepeat();

    /** The numeric value of the stepper. */
    double                  _value;
    /** The continuous vs. noncontinuous state of the stepper. */
    bool                    _continuous;
    /** The automatic vs. nonautomatic repeat state of the stepper. */
    bool                    _autorepeat;
    /** The wrap vs. no-wrap state of the stepper. */
    bool                    _wraps;
    /** The lowest possible numeric value for the stepper. */
    double                  _minimumValue;
    /** The highest possible numeric value for the stepper. */
    double                  _maximumValue;
    /** The step, or increment, value for the stepper. */
    double                  _stepValue;
    bool                    _touchInsideFlag;
    ControlStepperPart    _touchedPart;
    int                     _autorepeatCount;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLSTEPPER_H__ */
