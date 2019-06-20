/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
 * http://yannickloriot.com
 * 
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#ifndef __CCCONTROLSWITCH_H__
#define __CCCONTROLSWITCH_H__

#include "CCControl.h"
#include "extensions/ExtensionExport.h"

namespace cocos2d { class Sprite; }
namespace cocos2d { class Label; }

NS_CC_EXT_BEGIN

class ControlSwitchSprite;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlSwitch Switch control for Cocos2D. */
class CC_EX_DLL ControlSwitch : public Control
{
public:
    /** Creates a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
    static ControlSwitch* create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel);
    /** Creates a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
    static ControlSwitch* create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite);
    /**
     * @js ctor
     * @lua new
     */
    ControlSwitch();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlSwitch();

    /** Initializes a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
    bool initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite);
    /** Initializes a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
    bool initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel);

    /**
     * Set the state of the switch to On or Off, optionally animating the transition.
     *
     * @param isOn YES if the switch should be turned to the On position; NO if it 
     * should be turned to the Off position. If the switch is already in the 
     * designated position, nothing happens.
     * @param animated YES to animate the "flipping" of the switch; otherwise NO.
     */
    void setOn(bool isOn, bool animated);
    void setOn(bool isOn);
    bool isOn() const { return _on; }
    bool hasMoved() const { return _moved; }
    virtual void setEnabled(bool enabled) override;

    Vec2 locationFromTouch(Touch* touch);

    // Overrides
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:
    /** Sprite which represents the view. */
    ControlSwitchSprite* _switchSprite;
    float _initialTouchXPosition;
    
    bool _moved;
    /** A Boolean value that determines the off/on state of the switch. */
    bool _on;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLSWITCH_H__ */

