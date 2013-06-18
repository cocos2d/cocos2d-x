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

#include "CCControlPotentiometer.h"
#include "cocos2d.h"

NS_CC_EXT_BEGIN

CCControlPotentiometer::CCControlPotentiometer()
: _thumbSprite(NULL)
, _progressTimer(NULL)
, _value(0.0f)
, _minimumValue(0.0f)
, _maximumValue(0.0f)
{

}

CCControlPotentiometer::~CCControlPotentiometer()
{
    CC_SAFE_RELEASE(_thumbSprite);
    CC_SAFE_RELEASE(_progressTimer);
}

CCControlPotentiometer* CCControlPotentiometer::create(const char* backgroundFile, const char* progressFile, const char* thumbFile)
{
    CCControlPotentiometer* pRet = new CCControlPotentiometer();
    if (pRet != NULL)
    {
        // Prepare track for potentiometer
        CCSprite *backgroundSprite      = CCSprite::create(backgroundFile);

        // Prepare thumb for potentiometer
        CCSprite *thumbSprite           = CCSprite::create(thumbFile);

        // Prepare progress for potentiometer
        CCProgressTimer *progressTimer  = CCProgressTimer::create(CCSprite::create(progressFile));
        //progressTimer.type              = kCCProgressTimerTypeRadialCW;
        if (pRet->initWithTrackSprite_ProgressTimer_ThumbSprite(backgroundSprite, progressTimer, thumbSprite))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }
    }
    return pRet;
}

bool CCControlPotentiometer::initWithTrackSprite_ProgressTimer_ThumbSprite(CCSprite* trackSprite, CCProgressTimer* progressTimer, CCSprite* thumbSprite)
{
    if (CCControl::init())
    {
        setTouchEnabled(true);

        setProgressTimer(progressTimer);
        setThumbSprite(thumbSprite);
        thumbSprite->setPosition(progressTimer->getPosition());
        
        addChild(thumbSprite, 2);
        addChild(progressTimer, 1);
        addChild(trackSprite);
        
        setContentSize(trackSprite->getContentSize());
        
        // Init default values
        _minimumValue           = 0.0f;
        _maximumValue           = 1.0f;
        setValue(_minimumValue);
        return true;
    }
    return false;
}

void CCControlPotentiometer::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    if (_thumbSprite != NULL)
    {
        _thumbSprite->setOpacity((enabled) ? 255 : 128);
    }
}

void CCControlPotentiometer::setValue(float value)
{
    // set new value with sentinel
    if (value < _minimumValue)
    {
        value                   = _minimumValue;
    }
	
    if (value > _maximumValue) 
    {
        value                   = _maximumValue;
    }
    
    _value                      = value;
    
    // Update thumb and progress position for new value
    float percent               = (value - _minimumValue) / (_maximumValue - _minimumValue);
    _progressTimer->setPercentage(percent * 100.0f);
    _thumbSprite->setRotation(percent * 360.0f);
    
    sendActionsForControlEvents(CCControlEventValueChanged);    
}

float CCControlPotentiometer::getValue()
{
    return _value;
}

void CCControlPotentiometer::setMinimumValue(float minimumValue)
{
    _minimumValue       = minimumValue;
    
    if (_minimumValue >= _maximumValue)
    {
        _maximumValue   = _minimumValue + 1.0f;
    }
    
    setValue(_maximumValue);
}

float CCControlPotentiometer::getMinimumValue()
{
    return _minimumValue;
}

void CCControlPotentiometer::setMaximumValue(float maximumValue)
{
    _maximumValue       = maximumValue;
    
    if (_maximumValue <= _minimumValue)
    {
        _minimumValue   = _maximumValue - 1.0f;
    }
    
    setValue(_minimumValue);
}

float CCControlPotentiometer::getMaximumValue()
{
    return _maximumValue;
}

bool CCControlPotentiometer::isTouchInside(CCTouch * touch)
{
    CCPoint touchLocation   = this->getTouchLocation(touch);
    
    float distance          = this->distanceBetweenPointAndPoint(_progressTimer->getPosition(), touchLocation);

    return distance < MIN(getContentSize().width / 2, getContentSize().height / 2);
}

bool CCControlPotentiometer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isTouchInside(pTouch) || !this->isEnabled() || !isVisible())
    {
        return false;
    }
    
    _previousLocation    = this->getTouchLocation(pTouch);
    
    this->potentiometerBegan(_previousLocation);
    
    return true;
}

void CCControlPotentiometer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location    = this->getTouchLocation(pTouch);

    this->potentiometerMoved(location);
}

void CCControlPotentiometer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    this->potentiometerEnded(CCPointZero);
}

float CCControlPotentiometer::distanceBetweenPointAndPoint(CCPoint point1, CCPoint point2)
{
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    return sqrt(dx*dx + dy*dy);
}

float CCControlPotentiometer::angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(
    CCPoint beginLineA, 
    CCPoint endLineA,
    CCPoint beginLineB,
    CCPoint endLineB)
{
    float a = endLineA.x - beginLineA.x;
    float b = endLineA.y - beginLineA.y;
    float c = endLineB.x - beginLineB.x;
    float d = endLineB.y - beginLineB.y;
    
    float atanA = atan2(a, b);
    float atanB = atan2(c, d);
    
    // convert radiants to degrees
    return (atanA - atanB) * 180 / M_PI;
}

void CCControlPotentiometer::potentiometerBegan(CCPoint location)
{
    setSelected(true);
    getThumbSprite()->setColor(ccGRAY);
}

void CCControlPotentiometer::potentiometerMoved(CCPoint location)
{
    float angle       = this->angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(
        _progressTimer->getPosition(),
        location,
        _progressTimer->getPosition(),
        _previousLocation);
    
    // fix value, if the 12 o'clock position is between location and previousLocation
    if (angle > 180)
    {
        angle -= 360;
    }
    else if (angle < -180)
    {
        angle += 360;
    }

    setValue(_value + angle / 360.0f * (_maximumValue - _minimumValue));
    
    _previousLocation    = location;
}

void CCControlPotentiometer::potentiometerEnded(CCPoint location)
{
    getThumbSprite()->setColor(ccWHITE);
    setSelected(false);
}

NS_CC_EXT_END
