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
#ifndef __CCCONTROLPOTENTIOMETER_H__
#define __CCCONTROLPOTENTIOMETER_H__

#include "CCControl.h"
#include "2d/CCProgressTimer.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlPotentiometer Potentiometer control for Cocos2D. */
class CC_EX_DLL ControlPotentiometer : public Control
{
public:
    /**
     * Creates potentiometer with a track filename and a progress filename.
     */
    static ControlPotentiometer* create(const char* backgroundFile, const char* progressFile, const char* thumbFile);
    /**
     * @js ctor
     * @lua new
     */
    ControlPotentiometer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlPotentiometer();

    /** 
     * Initializes a potentiometer with a track sprite and a progress bar.
     *
     * @param trackSprite   Sprite, that is used as a background.
     * @param progressTimer ProgressTimer, that is used as a progress bar.
     */
    bool initWithTrackSprite_ProgressTimer_ThumbSprite(Sprite* trackSprite, ProgressTimer* progressTimer, Sprite* thumbSprite);

    void setValue(float value);
    float getValue();
     
    void setMinimumValue(float minimumValue);
    float getMinimumValue();

    void setMaximumValue(float maximumValue);
    float getMaximumValue();

    // Overrides
    virtual bool isTouchInside(Touch * touch) override;
    void setEnabled(bool enabled) override;
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;

    /** Factorize the event dispatch into these methods. */
    void potentiometerBegan(Vec2 location);
    void potentiometerMoved(Vec2 location);
    void potentiometerEnded(Vec2 location);

    /** Returns the distance between the point1 and point2. */
    float distanceBetweenPointAndPoint(Vec2 point1, Vec2 point2);
    /** Returns the angle in degree between line1 and line2. */
    float angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(
        Vec2 beginLineA, 
        Vec2 endLineA,
        Vec2 beginLineB,
        Vec2 endLineB);

protected:
    /** Contains the receiver’s current value. */
    float           _value;
    /** Contains the minimum value of the receiver.
     * The default value of this property is 0.0. */
    float           _minimumValue;
    /** Contains the maximum value of the receiver.
     * The default value of this property is 1.0. */
    float           _maximumValue;

    CC_SYNTHESIZE_RETAIN(Sprite*, _thumbSprite, ThumbSprite)
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _progressTimer, ProgressTimer)
    CC_SYNTHESIZE(Vec2, _previousLocation, PreviousLocation)
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLPOTENTIOMETER_H__ */
