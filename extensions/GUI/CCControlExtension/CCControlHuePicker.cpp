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
#include "support/CCPointExtension.h"

NS_CC_EXT_BEGIN

CCControlHuePicker::CCControlHuePicker()
: m_hue(0.0f)
, m_huePercentage(0.0f)
, m_background(NULL)
, m_slider(NULL)
{

}

CCControlHuePicker::~CCControlHuePicker()
{
    removeAllChildrenWithCleanup(true);
    CC_SAFE_RELEASE(m_background);
    CC_SAFE_RELEASE(m_slider);
}

CCControlHuePicker* CCControlHuePicker::pickerWithTargetAndPos(CCNode* target, CCPoint pos)
{
    return CCControlHuePicker::create(target, pos);
}

CCControlHuePicker* CCControlHuePicker::create(CCNode* target, CCPoint pos)
{
    CCControlHuePicker *pRet = new CCControlHuePicker();
    pRet->initWithTargetAndPos(target, pos);
    pRet->autorelease();
    return pRet;
}


bool CCControlHuePicker::initWithTargetAndPos(CCNode* target, CCPoint pos)
{
    if (CCControl::init())
    {
        setTouchEnabled(true);
        // Add background and slider sprites
        this->setBackground(CCControlUtils::addSpriteToTargetWithPosAndAnchor("huePickerBackground.png", target, pos, ccp(0.0f, 0.0f)));
        this->setSlider(CCControlUtils::addSpriteToTargetWithPosAndAnchor("colourPicker.png", target, pos, ccp(0.5f, 0.5f)));
        
        m_slider->setPosition(ccp(pos.x, pos.y + m_background->boundingBox().size.height * 0.5f));
        m_startPos=pos;

        // Sets the default value
        m_hue=0.0f;
        m_huePercentage=0.0f;
        return true;
    }
    else
    {
        return false;
    }
}

void CCControlHuePicker::setHue(float hueValue)
{
    m_hue=hueValue;
    // Set the position of the slider to the correct hue
    // We need to divide it by 360 as its taken as an angle in degrees
    float huePercentage	= hueValue / 360.0f;
    setHuePercentage(huePercentage);
}

void CCControlHuePicker::setHuePercentage(float hueValueInPercent)
{
    m_huePercentage=hueValueInPercent;
    m_hue=m_huePercentage*360.0f;

    // Clamp the position of the icon within the circle
    CCRect backgroundBox=m_background->boundingBox();

    // Get the center point of the background image
    float centerX           = m_startPos.x + backgroundBox.size.width * 0.5f;
    float centerY           = m_startPos.y + backgroundBox.size.height * 0.5f;
    
    // Work out the limit to the distance of the picker when moving around the hue bar
    float limit             = backgroundBox.size.width * 0.5f - 15.0f;
    
    // Update angle
    float angleDeg          = m_huePercentage * 360.0f - 180.0f;
    float angle             = CC_DEGREES_TO_RADIANS(angleDeg);
    
    // Set new position of the slider
    float x                 = centerX + limit * cosf(angle);
    float y                 = centerY + limit * sinf(angle);
    m_slider->setPosition(ccp(x, y));

}

void CCControlHuePicker::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    if (m_slider != NULL)
    {
        m_slider->setOpacity(enabled ? 255 : 128);
    }
}

void CCControlHuePicker::updateSliderPosition(CCPoint location)
{

    // Clamp the position of the icon within the circle
    CCRect backgroundBox=m_background->boundingBox();
    
    // Get the center point of the background image
    float centerX           = m_startPos.x + backgroundBox.size.width * 0.5f;
    float centerY           = m_startPos.y + backgroundBox.size.height * 0.5f;

    // Work out the distance difference between the location and center
    float dx                = location.x - centerX;
    float dy                = location.y - centerY;
    
    // Update angle by using the direction of the location
    float angle             = atan2f(dy, dx);
    float angleDeg          = CC_RADIANS_TO_DEGREES(angle) + 180.0f;
    
    // use the position / slider width to determin the percentage the dragger is at
    setHue(angleDeg);
    
    // send CCControl callback
    sendActionsForControlEvents(CCControlEventValueChanged);
}

bool CCControlHuePicker::checkSliderPosition(CCPoint location)
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

bool CCControlHuePicker::ccTouchBegan(CCTouch* touch, CCEvent* event)
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


void CCControlHuePicker::ccTouchMoved(CCTouch* touch, CCEvent* event)
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
