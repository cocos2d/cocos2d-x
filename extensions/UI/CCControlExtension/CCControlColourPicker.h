/*
 * CCControlColourPicker.h
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

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CC_DLL CCControlColourPicker: public CCControl
{
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(ccColor3B, m_colorValue, ColorValue);
    virtual void setColorValue(const ccColor3B& colorValue);

protected:
    HSV m_hsv;
    CCControlSaturationBrightnessPicker* m_colourPicker;
    CCControlHuePicker* m_huePicker;

    CC_SYNTHESIZE_READONLY(CCSprite*, m_background, Background);   
    
public:
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCControlColourPicker* colourPicker();

    static CCControlColourPicker* create();

    virtual bool init();
    //virtual ~CCControlColourPicker();
    void hueSliderValueChanged(CCObject * sender, CCControlEvent controlEvent);
    void colourSliderValueChanged(CCObject * sender, CCControlEvent controlEvent);

protected:    
    void updateControlPicker();
    void updateHueAndControlPicker();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif