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

#define ControlStepperLabelColorEnabled   Color3B(55, 55, 55)
#define ControlStepperLabelColorDisabled  Color3B(147, 147, 147)

#define ControlStepperLabelFont           "CourierNewPSMT"


#define kAutorepeatDeltaTime                0.15f
#define kAutorepeatIncreaseTimeIncrement    12

ControlStepper::ControlStepper()
: _value(0.0)
, _continuous(false)
, _autorepeat(false)
, _wraps(false)
, _minimumValue(0.0)
, _maximumValue(0.0)
, _stepValue(0.0)
, _touchInsideFlag(false)
, _touchedPart(Part::NONE)
, _autorepeatCount(0)
, _minusSprite(NULL)
, _plusSprite(NULL)
, _minusLabel(NULL)
, _plusLabel(NULL)
{

}

ControlStepper::~ControlStepper()
{
    unscheduleAllSelectors();
    
    CC_SAFE_RELEASE(_minusSprite);
    CC_SAFE_RELEASE(_plusSprite);
    CC_SAFE_RELEASE(_minusLabel);
    CC_SAFE_RELEASE(_plusLabel);
}

bool ControlStepper::initWithMinusSpriteAndPlusSprite(Sprite *minusSprite, Sprite *plusSprite)
{
    if (Control::init())
    {
        CCASSERT(minusSprite,   "Minus sprite must be not nil");
        CCASSERT(plusSprite,    "Plus sprite must be not nil");
        
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
		_minusSprite->setPosition( Point(minusSprite->getContentSize().width / 2, minusSprite->getContentSize().height / 2) );
		this->addChild(_minusSprite);
        
        this->setMinusLabel( LabelTTF::create("-", ControlStepperLabelFont, 40));
        _minusLabel->setColor(ControlStepperLabelColorDisabled);
        _minusLabel->setPosition(Point(_minusSprite->getContentSize().width / 2, _minusSprite->getContentSize().height / 2) );
        _minusSprite->addChild(_minusLabel);
        
        // Add the plus components 
        this->setPlusSprite( plusSprite );
		_plusSprite->setPosition( Point(minusSprite->getContentSize().width + plusSprite->getContentSize().width / 2, 
                                                  minusSprite->getContentSize().height / 2) );
		this->addChild(_plusSprite);
        
        this->setPlusLabel( LabelTTF::create("+", ControlStepperLabelFont, 40 ));
        _plusLabel->setColor( ControlStepperLabelColorEnabled );
        _plusLabel->setPosition( Point(_plusSprite->getContentSize().width / 2, _plusSprite->getContentSize().height / 2) );
        _plusSprite->addChild(_plusLabel);
        
        // Defines the content size
        Rect maxRect = ControlUtils::RectUnion(_minusSprite->getBoundingBox(), _plusSprite->getBoundingBox());
        this->setContentSize( Size(_minusSprite->getContentSize().width + _plusSprite->getContentSize().height, maxRect.size.height) );
        return true;
    }
    return false;
}

ControlStepper* ControlStepper::create(Sprite *minusSprite, Sprite *plusSprite)
{
    ControlStepper* pRet = new ControlStepper();
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

void ControlStepper::setWraps(bool wraps)
{
    _wraps = wraps;
    
    if (_wraps)
    {
        _minusLabel->setColor( ControlStepperLabelColorEnabled );
        _plusLabel->setColor(ControlStepperLabelColorEnabled );
    }
    
    this->setValue( _value );
}

void ControlStepper::setMinimumValue(double minimumValue)
{
    if (minimumValue >= _maximumValue)
    {
        CCASSERT(0, "Must be numerically less than maximumValue.");
    }
    
    _minimumValue   = minimumValue;
    this->setValue( _value );
}

void ControlStepper::setMaximumValue(double maximumValue)
{
    if (maximumValue <= _minimumValue)
    {
        CCASSERT(0, "Must be numerically greater than minimumValue.");
    }
    
    _maximumValue   = maximumValue;
    this->setValue(_value);
}

void ControlStepper::setValue(double value)
{
    this->setValueWithSendingEvent(value, true);
}

double ControlStepper::getValue() const
{
    return _value;
}

void ControlStepper::setStepValue(double stepValue)
{
    if (stepValue <= 0)
    {
        CCASSERT(0,"Must be numerically greater than 0.");
    }

    _stepValue  = stepValue;
}

bool ControlStepper::isContinuous() const
{
    return _continuous;
}
//#pragma mark -
//#pragma mark ControlStepper Public Methods

void ControlStepper::setValueWithSendingEvent(double value, bool send)
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
        _minusLabel->setColor((value == _minimumValue) ? ControlStepperLabelColorDisabled : ControlStepperLabelColorEnabled);
        _plusLabel->setColor((value == _maximumValue) ? ControlStepperLabelColorDisabled : ControlStepperLabelColorEnabled);
    }
    
    if (send)
    {
        this->sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
    }
}

void ControlStepper::startAutorepeat()
{
    _autorepeatCount    = -1;
    
    this->schedule(schedule_selector(ControlStepper::update), kAutorepeatDeltaTime, kRepeatForever, kAutorepeatDeltaTime * 3);
}

/** Stop the autorepeat. */
void ControlStepper::stopAutorepeat()
{
    this->unschedule(schedule_selector(ControlStepper::update));
}

void ControlStepper::update(float dt)
{
    _autorepeatCount++;
    
    if ((_autorepeatCount < kAutorepeatIncreaseTimeIncrement) && (_autorepeatCount % 3) != 0)
        return;
    
    if (_touchedPart == Part::MINUS)
    {
        this->setValueWithSendingEvent(_value - _stepValue, _continuous);
    } else if (_touchedPart == Part::PLUS)
    {
        this->setValueWithSendingEvent(_value + _stepValue, _continuous);
    }
}

//#pragma mark ControlStepper Private Methods

void ControlStepper::updateLayoutUsingTouchLocation(Point location)
{
    if (location.x < _minusSprite->getContentSize().width
        && _value > _minimumValue)
    {
        _touchedPart        = Part::MINUS;
        
        _minusSprite->setColor(Color3B::GRAY);
        _plusSprite->setColor(Color3B::WHITE);
    } else if (location.x >= _minusSprite->getContentSize().width
               && _value < _maximumValue)
    {
        _touchedPart        = Part::PLUS;
        
        _minusSprite->setColor(Color3B::WHITE);
        _plusSprite->setColor(Color3B::GRAY);
    } else
    {
        _touchedPart        = Part::NONE;
        
        _minusSprite->setColor(Color3B::WHITE);
        _plusSprite->setColor(Color3B::WHITE);
    }
}


bool ControlStepper::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    for (Node *c = this->_parent; c != nullptr; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    Point location    = this->getTouchLocation(pTouch);
    this->updateLayoutUsingTouchLocation(location);
    
    _touchInsideFlag = true;
    
    if (_autorepeat)
    {
        this->startAutorepeat();
    }
    
    return true;
}

void ControlStepper::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (this->isTouchInside(pTouch))
    {
        Point location    = this->getTouchLocation(pTouch);
        this->updateLayoutUsingTouchLocation(location);
        
        if (!_touchInsideFlag)
        {
            _touchInsideFlag    = true;
            
            if (_autorepeat)
            {
                this->startAutorepeat();
            }
        }
    }
    else
    {
        _touchInsideFlag    = false;
        
        _touchedPart        = Part::NONE;
        
        _minusSprite->setColor(Color3B::WHITE);
        _plusSprite->setColor(Color3B::WHITE);
        
        if (_autorepeat)
        {
            this->stopAutorepeat();
        }
    }
}

void ControlStepper::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    _minusSprite->setColor(Color3B::WHITE);
    _plusSprite->setColor(Color3B::WHITE);
    
    if (_autorepeat)
    {
        this->stopAutorepeat();
    }
    
    if (this->isTouchInside(pTouch))
    {
        Point location    = this->getTouchLocation(pTouch);
        
        this->setValue(_value + ((location.x < _minusSprite->getContentSize().width) ? (0.0-_stepValue) : _stepValue));
    }
}

NS_CC_EXT_END
