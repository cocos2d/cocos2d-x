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

#ifndef __CCCONTROL_COLOUR_PICKER_H__
#define __CCCONTROL_COLOUR_PICKER_H__


#include "CCControl.h"
#include "CCControlUtils.h"
#include "CCControlHuePicker.h"
#include "CCControlSaturationBrightnessPicker.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CC_EX_DLL ControlColourPicker: public Control
{
public:
    static ControlColourPicker* create();
    /**
     * @js ctor
     * @lua new
     */
    ControlColourPicker();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlColourPicker();

    virtual bool init() override;

    virtual void setColor(const Color3B& colorValue) override;
    virtual void setEnabled(bool bEnabled) override;

    //virtual ~ControlColourPicker();
    void hueSliderValueChanged(Ref * sender, Control::EventType controlEvent);
    void colourSliderValueChanged(Ref * sender, Control::EventType controlEvent);

protected:
    void updateControlPicker();
    void updateHueAndControlPicker();
    virtual bool onTouchBegan(Touch* touch, Event* pEvent) override;

    HSV _hsv;
    CC_SYNTHESIZE_RETAIN(ControlSaturationBrightnessPicker*, _colourPicker, colourPicker)
    CC_SYNTHESIZE_RETAIN(ControlHuePicker*, _huePicker, HuePicker)
    CC_SYNTHESIZE_RETAIN(Sprite*, _background, Background)
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
