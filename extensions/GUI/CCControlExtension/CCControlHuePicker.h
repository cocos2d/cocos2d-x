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
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CC_EX_DLL ControlHuePicker : public Control
{
public:
    static ControlHuePicker* create(Node* target, Vec2 pos);
    /**
     * @js ctor
     */
    ControlHuePicker();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlHuePicker();
    virtual bool initWithTargetAndPos(Node* target, Vec2 pos);

    virtual void setEnabled(bool enabled);

    // overrides
    virtual bool onTouchBegan(Touch* touch, Event* pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;

protected:
    void updateSliderPosition(Vec2 location);
    bool checkSliderPosition(Vec2 location);

    //maunally put in the setters
    CC_SYNTHESIZE_READONLY(float, _hue, Hue);
    virtual void setHue(float val);
    CC_SYNTHESIZE_READONLY(float, _huePercentage, HuePercentage);
    virtual void setHuePercentage(float val);

    //not sure if these need to be there actually. I suppose someone might want to access the sprite?
    CC_SYNTHESIZE_RETAIN(Sprite*, _background, Background);
    CC_SYNTHESIZE_RETAIN(Sprite*, _slider, Slider);
    CC_SYNTHESIZE_READONLY(Vec2, _startPos, StartPos);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
