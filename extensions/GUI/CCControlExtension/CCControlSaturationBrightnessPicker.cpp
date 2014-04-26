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

NS_CC_EXT_BEGIN

ControlSaturationBrightnessPicker::ControlSaturationBrightnessPicker()
: _saturation(0.0f)
, _brightness(0.0f)
, _background(nullptr)
, _overlay(nullptr)
, _shadow(nullptr)
, _slider(nullptr)
, boxPos(0)
, boxSize(0)
{

}

ControlSaturationBrightnessPicker::~ControlSaturationBrightnessPicker()
{
    removeAllChildrenWithCleanup(true);

    _background = NULL;
    _overlay    = NULL;
    _shadow     = NULL;
    _slider     = NULL;
}
    
bool ControlSaturationBrightnessPicker::initWithTargetAndPos(Node* target, Vector2 pos)
{
    if (Control::init())
    {
        // Add background and slider sprites
        _background=ControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerBackground.png", target, pos, Vector2(0.0f, 0.0f));
        _overlay=ControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerOverlay.png", target, pos, Vector2(0.0f, 0.0f));
        _shadow=ControlUtils::addSpriteToTargetWithPosAndAnchor("colourPickerShadow.png", target, pos, Vector2(0.0f, 0.0f));
        _slider=ControlUtils::addSpriteToTargetWithPosAndAnchor("colourPicker.png", target, pos, Vector2(0.5f, 0.5f));
                
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

ControlSaturationBrightnessPicker* ControlSaturationBrightnessPicker::create(Node* target, Vector2 pos)
{
    ControlSaturationBrightnessPicker *pRet = new ControlSaturationBrightnessPicker();
    pRet->initWithTargetAndPos(target, pos);
    pRet->autorelease();
    return pRet;
}

void ControlSaturationBrightnessPicker::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    if (_slider != NULL)
    {
        _slider->setOpacity(enabled ? 255 : 128);
    }
}

void ControlSaturationBrightnessPicker::updateWithHSV(HSV hsv)
{
    HSV hsvTemp;
    hsvTemp.s = 1;
    hsvTemp.h = hsv.h;
    hsvTemp.v = 1;
    
    RGBA rgb = ControlUtils::RGBfromHSV(hsvTemp);
    _background->setColor(Color3B((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
}

void ControlSaturationBrightnessPicker::updateDraggerWithHSV(HSV hsv)
{
    // Set the position of the slider to the correct saturation and brightness
    Vector2 pos = Vector2(_startPos.x + boxPos + (boxSize*(1 - hsv.s)),
                              _startPos.y + boxPos + (boxSize*hsv.v));
    
    // update
    updateSliderPosition(pos);
}

void ControlSaturationBrightnessPicker::updateSliderPosition(Vector2 sliderPosition)
{
    // Clamp the position of the icon within the circle
    
    // Get the center point of the bkgd image
    float centerX           = _startPos.x + _background->getBoundingBox().size.width*0.5f;
    float centerY           = _startPos.y + _background->getBoundingBox().size.height*0.5f;
    
    // Work out the distance difference between the location and center
    float dx                = sliderPosition.x - centerX;
    float dy                = sliderPosition.y - centerY;
    float dist              = sqrtf(dx * dx + dy * dy);
    
    // Update angle by using the direction of the location
    float angle             = atan2f(dy, dx);
    
    // Set the limit to the slider movement within the colour picker
    float limit             = _background->getBoundingBox().size.width*0.5f;
    
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

bool ControlSaturationBrightnessPicker::checkSliderPosition(Vector2 location)
{
    // Clamp the position of the icon within the circle
    
    // get the center point of the bkgd image
    float centerX           = _startPos.x + _background->getBoundingBox().size.width*0.5f;
    float centerY           = _startPos.y + _background->getBoundingBox().size.height*0.5f;
    
    // work out the distance difference between the location and center
    float dx                = location.x - centerX;
    float dy                = location.y - centerY;
    float dist              = sqrtf(dx*dx+dy*dy);
    
    // check that the touch location is within the bounding rectangle before sending updates
    if (dist <= _background->getBoundingBox().size.width*0.5f)
    {
        updateSliderPosition(location);
        sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
        return true;
    }
    return false;
}


bool ControlSaturationBrightnessPicker::onTouchBegan(Touch* touch, Event* event)
{
    if (!isEnabled() || !isVisible())
    {
        return false;
    }
    
    // Get the touch location
    Vector2 touchLocation=getTouchLocation(touch);

    // Check the touch position on the slider
    return checkSliderPosition(touchLocation);
}


void ControlSaturationBrightnessPicker::onTouchMoved(Touch* touch, Event* event)
{
    // Get the touch location
    Vector2 touchLocation=getTouchLocation(touch);

    //small modification: this allows changing of the colour, even if the touch leaves the bounding area
//     updateSliderPosition(touchLocation);
//     sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
    // Check the touch position on the slider
    checkSliderPosition(touchLocation);
}

NS_CC_EXT_END
