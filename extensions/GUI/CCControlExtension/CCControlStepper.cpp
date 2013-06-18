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
 * IMPLIED, INCLUDING BUT falseT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND falseNINFRINGEMENT. IN false EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "CCControlStepper.h"

NS_CC_EXT_BEGIN

#define CCControlStepperLabelColorEnabled   ccc3(55, 55, 55)
#define CCControlStepperLabelColorDisabled  ccc3(147, 147, 147)

#define CCControlStepperLabelFont           "CourierNewPSMT"


#define kAutorepeatDeltaTime                0.15f
#define kAutorepeatIncreaseTimeIncrement    12

CCControlStepper::CCControlStepper()
: _minusSprite(NULL)
, _plusSprite(NULL)
, _minusLabel(NULL)
, _plusLabel(NULL)
, _value(0.0)
, _continuous(false)
, _autorepeat(false)
, _wraps(false)
, _minimumValue(0.0)
, _maximumValue(0.0)
, _stepValue(0.0)
, _touchInsideFlag(false)
, _touchedPart(kCCControlStepperPartNone)
, _autorepeatCount(0)
{

}

CCControlStepper::~CCControlStepper()
{
    unscheduleAllSelectors();
    
    CC_SAFE_RELEASE(_minusSprite);
    CC_SAFE_RELEASE(_plusSprite);
    CC_SAFE_RELEASE(_minusLabel);
    CC_SAFE_RELEASE(_plusLabel);
}

bool CCControlStepper::initWithMinusSpriteAndPlusSprite(CCSprite *minusSprite, CCSprite *plusSprite)
{
    if (CCControl::init())
    {
        CCAssert(minusSprite,   "Minus sprite must be not nil");
        CCAssert(plusSprite,    "Plus sprite must be not nil");
        
        setTouchEnabled(true);

        // Set the default values
        _autorepeat                         = true;
        _continuous                         = true;
        _minimumValue                       = 0;
        _maximumValue                       = 100;
        _value                              = 0;
        _stepValue                          = 1;
        _wraps                              = false;
        this->ignoreAnchorPointForPosition( false );
    
        // Add the minus components
        this->setMinusSprite(minusSprite);
		_minusSprite->setPosition( ccp(minusSprite->getContentSize().width / 2, minusSprite->getContentSize().height / 2) );
		this->addChild(_minusSprite);
        
        this->setMinusLabel( CCLabelTTF::create("-", CCControlStepperLabelFont, 40));
        _minusLabel->setColor(CCControlStepperLabelColorDisabled);
        _minusLabel->setPosition(CCPointMake(_minusSprite->getContentSize().width / 2, _minusSprite->getContentSize().height / 2) );
        _minusSprite->addChild(_minusLabel);
        
        // Add the plus components 
        this->setPlusSprite( plusSprite );
		_plusSprite->setPosition( ccp(minusSprite->getContentSize().width + plusSprite->getContentSize().width / 2, 
                                                  minusSprite->getContentSize().height / 2) );
		this->addChild(_plusSprite);
        
        this->setPlusLabel( CCLabelTTF::create("+", CCControlStepperLabelFont, 40 ));
        _plusLabel->setColor( CCControlStepperLabelColorEnabled );
        _plusLabel->setPosition( CCPointMake(_plusSprite->getContentSize().width / 2, _plusSprite->getContentSize().height / 2) );
        _plusSprite->addChild(_plusLabel);
        
        // Defines the content size
        CCRect maxRect = CCControlUtils::CCRectUnion(_minusSprite->boundingBox(), _plusSprite->boundingBox());
        this->setContentSize( CCSizeMake(_minusSprite->getContentSize().width + _plusSprite->getContentSize().height, maxRect.size.height) );
        return true;
    }
    return false;
}

CCControlStepper* CCControlStepper::create(CCSprite *minusSprite, CCSprite *plusSprite)
{
    CCControlStepper* pRet = new CCControlStepper();
    if (pRet != NULL && pRet->initWithMinusSpriteAndPlusSprite(minusSprite, plusSprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

//#pragma mark Properties

void CCControlStepper::setWraps(bool wraps)
{
    _wraps = wraps;
    
    if (_wraps)
    {
        _minusLabel->setColor( CCControlStepperLabelColorEnabled );
        _plusLabel->setColor(CCControlStepperLabelColorEnabled );
    }
    
    this->setValue( _value );
}

void CCControlStepper::setMinimumValue(double minimumValue)
{
    if (minimumValue >= _maximumValue)
    {
        CCAssert(0, "Must be numerically less than maximumValue.");
    }
    
    _minimumValue   = minimumValue;
    this->setValue( _value );
}

void CCControlStepper::setMaximumValue(double maximumValue)
{
    if (maximumValue <= _minimumValue)
    {
        CCAssert(0, "Must be numerically greater than minimumValue.");
    }
    
    _maximumValue   = maximumValue;
    this->setValue(_value);
}

void CCControlStepper::setValue(double value)
{
    this->setValueWithSendingEvent(value, true);
}

double CCControlStepper::getValue()
{
    return _value;
}

void CCControlStepper::setStepValue(double stepValue)
{
    if (stepValue <= 0)
    {
        CCAssert(0,"Must be numerically greater than 0.");
    }

    _stepValue  = stepValue;
}

bool CCControlStepper::isContinuous()
{
    return _continuous;
}
//#pragma mark -
//#pragma mark CCControlStepper Public Methods

void CCControlStepper::setValueWithSendingEvent(double value, bool send)
{
    if (value < _minimumValue)
    {
        value = _wraps ? _maximumValue : _minimumValue;
    } else if (value > _maximumValue)
    {
        value = _wraps ? _minimumValue : _maximumValue;
    }
    
    _value = value;
    
    if (!_wraps)
    {
        _minusLabel->setColor((value == _minimumValue) ? CCControlStepperLabelColorDisabled : CCControlStepperLabelColorEnabled);
        _plusLabel->setColor((value == _maximumValue) ? CCControlStepperLabelColorDisabled : CCControlStepperLabelColorEnabled);
    }
    
    if (send)
    {
        this->sendActionsForControlEvents(CCControlEventValueChanged);
    }
}

void CCControlStepper::startAutorepeat()
{
    _autorepeatCount    = -1;
    
    this->schedule(schedule_selector(CCControlStepper::update), kAutorepeatDeltaTime, kCCRepeatForever, kAutorepeatDeltaTime * 3);
}

/** Stop the autorepeat. */
void CCControlStepper::stopAutorepeat()
{
    this->unschedule(schedule_selector(CCControlStepper::update));
}

void CCControlStepper::update(float dt)
{
    _autorepeatCount++;
    
    if ((_autorepeatCount < kAutorepeatIncreaseTimeIncrement) && (_autorepeatCount % 3) != 0)
        return;
    
    if (_touchedPart == kCCControlStepperPartMinus)
    {
        this->setValueWithSendingEvent(_value - _stepValue, _continuous);
    } else if (_touchedPart == kCCControlStepperPartPlus)
    {
        this->setValueWithSendingEvent(_value + _stepValue, _continuous);
    }
}

//#pragma mark CCControlStepper Private Methods

void CCControlStepper::updateLayoutUsingTouchLocation(CCPoint location)
{
    if (location.x < _minusSprite->getContentSize().width
        && _value > _minimumValue)
    {
        _touchedPart        = kCCControlStepperPartMinus;
        
        _minusSprite->setColor(ccGRAY);
        _plusSprite->setColor(ccWHITE);
    } else if (location.x >= _minusSprite->getContentSize().width
               && _value < _maximumValue)
    {
        _touchedPart        = kCCControlStepperPartPlus;
        
        _minusSprite->setColor(ccWHITE);
        _plusSprite->setColor(ccGRAY);
    } else
    {
        _touchedPart        = kCCControlStepperPartNone;
        
        _minusSprite->setColor(ccWHITE);
        _plusSprite->setColor(ccWHITE);
    }
}


bool CCControlStepper::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    CCPoint location    = this->getTouchLocation(pTouch);
    this->updateLayoutUsingTouchLocation(location);
    
    _touchInsideFlag = true;
    
    if (_autorepeat)
    {
        this->startAutorepeat();
    }
    
    return true;
}

void CCControlStepper::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (this->isTouchInside(pTouch))
    {
        CCPoint location    = this->getTouchLocation(pTouch);
        this->updateLayoutUsingTouchLocation(location);
        
        if (!_touchInsideFlag)
        {
            _touchInsideFlag    = true;
            
            if (_autorepeat)
            {
                this->startAutorepeat();
            }
        }
    } else
    {
        _touchInsideFlag    = false;
        
        _touchedPart        = kCCControlStepperPartNone;
        
        _minusSprite->setColor(ccWHITE);
        _plusSprite->setColor(ccWHITE);
        
        if (_autorepeat)
        {
            this->stopAutorepeat();
        }
    }
}

void CCControlStepper::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    _minusSprite->setColor(ccWHITE);
    _plusSprite->setColor(ccWHITE);
    
    if (_autorepeat)
    {
        this->stopAutorepeat();
    }
    
    if (this->isTouchInside(pTouch))
    {
        CCPoint location    = this->getTouchLocation(pTouch);
        
        this->setValue(_value + ((location.x < _minusSprite->getContentSize().width) ? (0.0-_stepValue) : _stepValue));
    }
}

NS_CC_EXT_END
