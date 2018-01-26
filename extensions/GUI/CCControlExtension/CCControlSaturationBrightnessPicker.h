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


#ifndef __CCCONTROL_SATURATION_PICKER_H__
#define __CCCONTROL_SATURATION_PICKER_H__

#include "CCControl.h"
#include "CCInvocation.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CC_EX_DLL ControlSaturationBrightnessPicker : public Control
{
    /** Contains the receiver's current saturation value. */
    CC_SYNTHESIZE_READONLY(float, _saturation, Saturation);
    /** Contains the receiver's current brightness value. */
    CC_SYNTHESIZE_READONLY(float, _brightness, Brightness);

    //not sure if these need to be there actually. I suppose someone might want to access the sprite?
    CC_SYNTHESIZE_READONLY(Sprite*, _background, Background);
    CC_SYNTHESIZE_READONLY(Sprite*, _overlay, Overlay);
    CC_SYNTHESIZE_READONLY(Sprite*, _shadow, Shadow);
    CC_SYNTHESIZE_READONLY(Sprite*, _slider, Slider);
    CC_SYNTHESIZE_READONLY(Vec2, _startPos, StartPos);

protected:
    int         boxPos;
    int         boxSize;
    
public:
    /**
     * @js ctor
     */
    ControlSaturationBrightnessPicker();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlSaturationBrightnessPicker();
    virtual bool initWithTargetAndPos(Node* target, Vec2 pos);

    static ControlSaturationBrightnessPicker* create(Node* target, Vec2 pos);

    virtual void setEnabled(bool enabled) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void updateWithHSV(HSV hsv);
    /**
     * @js NA
     * @lua NA
     */
    virtual void updateDraggerWithHSV(HSV hsv);

protected:    
    void updateSliderPosition(Vec2 location);
    bool checkSliderPosition(Vec2 location);

    virtual bool onTouchBegan(Touch* touch, Event* pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
