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

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class CCControlPotentiometer Potentiometer control for Cocos2D. */
class CCControlPotentiometer : public CCControl
{
public:
    CCControlPotentiometer();
    virtual ~CCControlPotentiometer();
    /** 
     * Creates potentiometer with a track filename and a progress filename.
     */
    static CCControlPotentiometer* create(const char* backgroundFile, const char* progressFile, const char* thumbFile);

    /** 
     * Initializes a potentiometer with a track sprite and a progress bar.
     *
     * @param trackSprite CCSprite, that is used as a background.
     * @param progressSprite CCProgressTimer, that is used as a progress bar.
     */
    bool initWithTrackSprite_ProgressTimer_ThumbSprite(CCSprite* trackSprite, CCProgressTimer* progressTimer, CCSprite* thumbSprite);
    void setValue(float value);
    float getValue();
     
    void setMinimumValue(float minimumValue);
    float getMinimumValue();

    void setMaximumValue(float maximumValue);
    float getMaximumValue();

    void setEnabled(bool enabled);

    virtual bool isTouchInside(CCTouch * touch);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pThumbSprite, ThumbSprite)
    CC_SYNTHESIZE_RETAIN(CCProgressTimer*, m_pProgressTimer, ProgressTimer)
    CC_SYNTHESIZE(CCPoint, m_tPreviousLocation, PreviousLocation)
    /** Contains the receiver’s current value. */
    float           m_fValue; 
    /** Contains the minimum value of the receiver. 
    * The default value of this property is 0.0. */
    float           m_fMinimumValue;
    /** Contains the maximum value of the receiver. 
    * The default value of this property is 1.0. */
    float           m_fMaximumValue;
    /** Factorize the event dispath into these methods. */
    void potentiometerBegan(CCPoint location);
    void potentiometerMoved(CCPoint location);
    void potentiometerEnded(CCPoint location);

    /** Returns the distance between the point1 and point2. */
    float distanceBetweenPointAndPoint(CCPoint point1, CCPoint point2);
    /** Returns the angle in degree between line1 and line2. */
    float angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(
        CCPoint beginLineA, 
        CCPoint endLineA,
        CCPoint beginLineB,
        CCPoint endLineB);

};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLPOTENTIOMETER_H__ */
