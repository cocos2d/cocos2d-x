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

#ifndef __CCCONTROLSWITCH_H__
#define __CCCONTROLSWITCH_H__

#include "CCControl.h"


namespace cocos2d { class CCSprite; }
namespace cocos2d { class CCLabelTTF; }

NS_CC_EXT_BEGIN

class CCControlSwitchSprite;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class CCControlSwitch Switch control for Cocos2D. */
class CC_EX_DLL CCControlSwitch : public CCControl
{
public:
    CCControlSwitch();
    virtual ~CCControlSwitch();
    /** Initializes a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
    bool initWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite);

    /** Creates a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
    static CCControlSwitch* create(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite);


    /** Initializes a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
    bool initWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite, CCLabelTTF* onLabel, CCLabelTTF* offLabel);

    /** Creates a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
    static CCControlSwitch* create(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite, CCLabelTTF* onLabel, CCLabelTTF* offLabel);


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
    bool isOn(void) { return m_bOn; }
    bool hasMoved() { return m_bMoved; }
    virtual void setEnabled(bool enabled);

    CCPoint locationFromTouch(CCTouch* touch);
    //events
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

protected:
    /** Sprite which represents the view. */
    CCControlSwitchSprite* m_pSwitchSprite;
    float m_fInitialTouchXPosition;
    
    bool m_bMoved;
    /** A Boolean value that determines the off/on state of the switch. */
    bool m_bOn;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLSWITCH_H__ */

