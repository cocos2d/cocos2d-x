/*
 * CCControlSlider
 *
 * Copyright 2011 Yannick Loriot. All rights reserved.
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


#ifndef __CCCONTROL_SLIDER_H__
#define __CCCONTROL_SLIDER_H__

#include "CCControl.h"
#include "CCInvocation.h"
#include "sprite_nodes/CCSprite.h"
#include "menu_nodes/CCMenuItem.h"

#define SLIDER_MARGIN_H 24
#define SLIDER_MARGIN_V 8

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class CC_DLL CCControlSlider: public CCControl
{
    //maunally put in the setters
    CC_SYNTHESIZE_READONLY(float, m_value, Value);
    virtual void setValue(float val);
    CC_SYNTHESIZE_READONLY(float, m_minimumValue, MinimumValue);
    virtual void setMinimumValue(float val);
    CC_SYNTHESIZE_READONLY(float, m_maximumValue, MaximumValue);
    virtual void setMaximumValue(float val);

    //interval to snap to
    CC_SYNTHESIZE(float, m_snappingInterval, SnappingInterval);

    // maybe this should be read-only
    CC_SYNTHESIZE_READONLY(CCMenuItem*, m_thumbItem, ThumbItem);
    CC_SYNTHESIZE_READONLY(CCSprite*, m_progressSprite, ProgressSprite);
    CC_SYNTHESIZE_READONLY(CCSprite*, m_backgroundSprite, BackgroundSprite);

public:

    virtual ~CCControlSlider();

    /** 
    * Initializes a slider with a background sprite, a progress bar and a thumb
    * item.
    *
    * @param backgroundSprite  CCSprite, that is used as a background.
    * @param progressSprite    CCSprite, that is used as a progress bar.
    * @param thumbItem         CCMenuItem, that is used as a thumb.
    */
    virtual bool initWithSprites(CCSprite * backgroundSprite, CCSprite* progessSprite, CCMenuItem* thumbItem);


    /** 
    * Creates slider with a background filename, a progress filename and a 
    * thumb image filename.
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCControlSlider* sliderWithFiles(const char* bgFile, const char* progressFile, const char* thumbFile);

    /** 
    * Creates a slider with a given background sprite and a progress bar and a
    * thumb item.
    *@deprecated: This interface will be deprecated sooner or later.
    * @see initWithBackgroundSprite:progressSprite:thumbMenuItem:
    */
    CC_DEPRECATED_ATTRIBUTE static CCControlSlider* sliderWithSprites(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCMenuItem* thumbItem);


    /** 
    * Creates slider with a background filename, a progress filename and a 
    * thumb image filename.
    */
    static CCControlSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile);

    /** 
    * Creates a slider with a given background sprite and a progress bar and a
    * thumb item.
    *
    * @see initWithBackgroundSprite:progressSprite:thumbMenuItem:
    */
    static CCControlSlider* create(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCMenuItem* thumbItem);


protected:
    void sliderBegan(CCPoint location);
    void sliderMoved(CCPoint location);
    void sliderEnded(CCPoint location);

    virtual CCPoint getTouchLocationInControl(CCTouch* touch);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);



/** Returns the value for the given location. */
    float valueForLocation(CCPoint location);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif