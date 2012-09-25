/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Stewart Hamilton-Arrandale.
 * http://creativewax.co.uk
 *
 * Modified by Yannick Loriot.
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
 * Converted to c++ / cocos2d-x by Angus C
 */


#ifndef __CCCONTROL_HUE_PICKER_H__
#define __CCCONTROL_HUE_PICKER_H__

#include "CCControl.h"
#include "CCInvocation.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CCControlHuePicker : public CCControl
{
    //maunally put in the setters
    CC_SYNTHESIZE_READONLY(float, m_hue, Hue);
    virtual void setHue(float val);
    CC_SYNTHESIZE_READONLY(float, m_huePercentage, HuePercentage);
    virtual void setHuePercentage(float val);


    //not sure if these need to be there actually. I suppose someone might want to access the sprite?
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_background, Background);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_slider, Slider);
    CC_SYNTHESIZE_READONLY(CCPoint, m_startPos, StartPos);

public:
    CCControlHuePicker();
    virtual ~CCControlHuePicker();
    virtual bool initWithTargetAndPos(CCNode* target, CCPoint pos);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCControlHuePicker* pickerWithTargetAndPos(CCNode* target, CCPoint pos);
    static CCControlHuePicker* create(CCNode* target, CCPoint pos);
    virtual void setEnabled(bool enabled);
protected:    
    void updateSliderPosition(CCPoint location);
    bool checkSliderPosition(CCPoint location);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif