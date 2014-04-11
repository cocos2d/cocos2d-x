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

#include "CCControlHuePicker.h"

NS_CC_EXT_BEGIN

ControlHuePicker::ControlHuePicker()
: _hue(0.0f)
, _huePercentage(0.0f)
, _background(nullptr)
, _slider(nullptr)
{

}

ControlHuePicker::~ControlHuePicker()
{
    removeAllChildrenWithCleanup(true);
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_slider);
}

ControlHuePicker* ControlHuePicker::create(Node* target, Point pos)
{
    ControlHuePicker *pRet = new ControlHuePicker();
    pRet->initWithTargetAndPos(target, pos);
    pRet->autorelease();
    return pRet;
}


bool ControlHuePicker::initWithTargetAndPos(Node* target, Point pos)
{
    if (Control::init())
    {
        // Add background and slider sprites
        this->setBackground(ControlUtils::addSpriteToTargetWithPosAndAnchor("huePickerBackground.png", target, pos, Point(0.0f, 0.0f)));
        this->setSlider(ControlUtils::addSpriteToTargetWithPosAndAnchor("colourPicker.png", target, pos, Point(0.5f, 0.5f)));
        
        _slider->setPosition(Point(pos.x, pos.y + _background->getBoundingBox().size.height * 0.5f));
        _startPos=pos;

        // Sets the default value
        _hue=0.0f;
        _huePercentage=0.0f;
        return true;
    }
    else
    {
        return false;
    }
}

void ControlHuePicker::setHue(float hueValue)
{
    _hue=hueValue;
    // Set the position of the slider to the correct hue
    // We need to divide it by 360 as its taken as an angle in degrees
    float huePercentage	= hueValue / 360.0f;
    setHuePercentage(huePercentage);
}

void ControlHuePicker::setHuePercentage(float hueValueInPercent)
{
    _huePercentage=hueValueInPercent;
    _hue=_huePercentage*360.0f;

    // Clamp the position of the icon within the circle
    Rect backgroundBox=_background->getBoundingBox();

    // Get the center point of the background image
    float centerX           = _startPos.x + backgroundBox.size.width * 0.5f;
    float centerY           = _startPos.y + backgroundBox.size.height * 0.5f;
    
    // Work out the limit to the distance of the picker when moving around the hue bar
    float limit             = backgroundBox.size.width * 0.5f - 15.0f;
    
    // Update angle
    float angleDeg          = _huePercentage * 360.0f - 180.0f;
    float angle             = CC_DEGREES_TO_RADIANS(angleDeg);
    
    // Set new position of the slider
    float x                 = centerX + limit * cosf(angle);
    float y                 = centerY + limit * sinf(angle);
    _slider->setPosition(Point(x, y));

}

void ControlHuePicker::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    if (_slider != NULL)
    {
        _slider->setOpacity(enabled ? 255 : 128);
    }
}

void ControlHuePicker::updateSliderPosition(Point location)
{

    // Clamp the position of the icon within the circle
    Rect backgroundBox=_background->getBoundingBox();
    
    // Get the center point of the background image
    float centerX           = _startPos.x + backgroundBox.size.width * 0.5f;
    float centerY           = _startPos.y + backgroundBox.size.height * 0.5f;

    // Work out the distance difference between the location and center
    float dx                = location.x - centerX;
    float dy                = location.y - centerY;
    
    // Update angle by using the direction of the location
    float angle             = atan2f(dy, dx);
    float angleDeg          = CC_RADIANS_TO_DEGREES(angle) + 180.0f;
    
    // use the position / slider width to determin the percentage the dragger is at
    setHue(angleDeg);
    
    // send Control callback
    sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
}

bool ControlHuePicker::checkSliderPosition(Point location)
{
    // compute the distance between the current location and the center
    double distance = sqrt(pow (location.x + 10, 2) + pow(location.y, 2));

    // check that the touch location is within the circle
    if (80 > distance && distance > 59)
    {
        updateSliderPosition(location);
        return true;
    }
    return false;
}

bool ControlHuePicker::onTouchBegan(Touch* touch, Event* event)
{
    if (!isEnabled() || !isVisible())
    {
        return false;
    }
    
    // Get the touch location
    Point touchLocation=getTouchLocation(touch);

    // Check the touch position on the slider
    return checkSliderPosition(touchLocation);
}


void ControlHuePicker::onTouchMoved(Touch* touch, Event* event)
{
    // Get the touch location
    Point touchLocation=getTouchLocation(touch);

    //small modification: this allows changing of the colour, even if the touch leaves the bounding area
//     updateSliderPosition(touchLocation);
//     sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
    // Check the touch position on the slider
    checkSliderPosition(touchLocation);
}

NS_CC_EXT_END
