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

#include "CCControlSaturationBrightnessPicker.h"
#include "support/CCPointExtension.h"

NS_CC_EXT_BEGIN

CCControlSaturationBrightnessPicker::CCControlSaturationBrightnessPicker()
: _saturation(0.0f)
, _brightness(0.0f)
, _background(NULL)
, _overlay(NULL)
, _shadow(NULL)
, _slider(NULL)
, boxPos(0)
, boxSize(0)
{

}

CCControlSaturationBrightnessPicker::~CCControlSaturationBrightnessPicker()
{
    removeAllChildrenWithCleanup(true);

    _background = NULL;
    _overlay    = NULL;
    _shadow     = NULL;
    _slider     = NULL;
}
    
bool CCControlSaturationBrightnessPicker::initWithTargetAndPos(CCNode* target, CCPoint pos)
{
    if (CCControl::init())
    {
        setTouchEnabled(true);
        // Add background and slider sprites
        _background=CCControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerBackground.png", target, pos, ccp(0.0f, 0.0f));
        _overlay=CCControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerOverlay.png", target, pos, ccp(0.0f, 0.0f));
        _shadow=CCControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerShadow.png", target, pos, ccp(0.0f, 0.0f));
        _slider=CCControlUtils::addSpriteToTargetWithPosAndAnchor("colourPicker.png", target, pos, ccp(0.5f, 0.5f));
                
        _startPos=pos; // starting position of the colour picker        
        boxPos          = 35;    // starting position of the virtual box area for picking a colour
        boxSize         = _background->getContentSize().width / 2;;    // the size (width and height) of the virtual box for picking a colour from
        return true;
    }
    else
    {
        return false;
    }
}

CCControlSaturationBrightnessPicker* CCControlSaturationBrightnessPicker::create(CCNode* target, CCPoint pos)
{
    CCControlSaturationBrightnessPicker *pRet = new CCControlSaturationBrightnessPicker();
    pRet->initWithTargetAndPos(target, pos);
    pRet->autorelease();
    return pRet;
}

void CCControlSaturationBrightnessPicker::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    if (_slider != NULL)
    {
        _slider->setOpacity(enabled ? 255 : 128);
    }
}

void CCControlSaturationBrightnessPicker::updateWithHSV(HSV hsv)
{
    HSV hsvTemp;
    hsvTemp.s = 1;
    hsvTemp.h = hsv.h;
    hsvTemp.v = 1;
    
    RGBA rgb = CCControlUtils::RGBfromHSV(hsvTemp);
    _background->setColor(ccc3((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
}

void CCControlSaturationBrightnessPicker::updateDraggerWithHSV(HSV hsv)
{
    // Set the position of the slider to the correct saturation and brightness
    CCPoint pos = CCPointMake(_startPos.x + boxPos + (boxSize*(1 - hsv.s)),
                              _startPos.y + boxPos + (boxSize*hsv.v));
    
    // update
    updateSliderPosition(pos);
}

void CCControlSaturationBrightnessPicker::updateSliderPosition(CCPoint sliderPosition)
{
    // Clamp the position of the icon within the circle
    
    // Get the center point of the bkgd image
    float centerX           = _startPos.x + _background->boundingBox().size.width*0.5f;
    float centerY           = _startPos.y + _background->boundingBox().size.height*0.5f;
    
    // Work out the distance difference between the location and center
    float dx                = sliderPosition.x - centerX;
    float dy                = sliderPosition.y - centerY;
    float dist              = sqrtf(dx * dx + dy * dy);
    
    // Update angle by using the direction of the location
    float angle             = atan2f(dy, dx);
    
    // Set the limit to the slider movement within the colour picker
    float limit             = _background->boundingBox().size.width*0.5f;
    
    // Check distance doesn't exceed the bounds of the circle
    if (dist > limit)
    {
        sliderPosition.x    = centerX + limit * cosf(angle);
        sliderPosition.y    = centerY + limit * sinf(angle);
    }
    
    // Set the position of the dragger
    _slider->setPosition(sliderPosition);
    
    
    // Clamp the position within the virtual box for colour selection
    if (sliderPosition.x < _startPos.x + boxPos)                        sliderPosition.x = _startPos.x + boxPos;
    else if (sliderPosition.x > _startPos.x + boxPos + boxSize - 1)    sliderPosition.x = _startPos.x + boxPos + boxSize - 1;
    if (sliderPosition.y < _startPos.y + boxPos)                        sliderPosition.y = _startPos.y + boxPos;
    else if (sliderPosition.y > _startPos.y + boxPos + boxSize)        sliderPosition.y = _startPos.y + boxPos + boxSize;
    
    // Use the position / slider width to determin the percentage the dragger is at
    _saturation = 1.0f - fabs((_startPos.x + (float)boxPos - sliderPosition.x)/(float)boxSize);
    _brightness = fabs((_startPos.y + (float)boxPos - sliderPosition.y)/(float)boxSize);
}

bool CCControlSaturationBrightnessPicker::checkSliderPosition(CCPoint location)
{
    // Clamp the position of the icon within the circle
    
    // get the center point of the bkgd image
    float centerX           = _startPos.x + _background->boundingBox().size.width*0.5f;
    float centerY           = _startPos.y + _background->boundingBox().size.height*0.5f;
    
    // work out the distance difference between the location and center
    float dx                = location.x - centerX;
    float dy                = location.y - centerY;
    float dist              = sqrtf(dx*dx+dy*dy);
    
    // check that the touch location is within the bounding rectangle before sending updates
    if (dist <= _background->boundingBox().size.width*0.5f)
    {
        updateSliderPosition(location);
        sendActionsForControlEvents(CCControlEventValueChanged);
        return true;
    }
    return false;
}


bool CCControlSaturationBrightnessPicker::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!isEnabled() || !isVisible())
    {
        return false;
    }
    
    // Get the touch location
    CCPoint touchLocation=getTouchLocation(touch);

    // Check the touch position on the slider
    return checkSliderPosition(touchLocation);
}


void CCControlSaturationBrightnessPicker::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // Get the touch location
    CCPoint touchLocation=getTouchLocation(touch);

    //small modification: this allows changing of the colour, even if the touch leaves the bounding area
//     updateSliderPosition(touchLocation);
//     sendActionsForControlEvents(CCControlEventValueChanged);
    // Check the touch position on the slider
    checkSliderPosition(touchLocation);
}

NS_CC_EXT_END
