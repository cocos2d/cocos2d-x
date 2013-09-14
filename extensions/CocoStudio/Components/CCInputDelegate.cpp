/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCInputDelegate.h"

NS_CC_EXT_BEGIN

InputDelegate::InputDelegate(void)
: _touchEnabled(false)
, _accelerometerEnabled(false)
, _keypadEnabled(false)
, _touchPriority(0)
, _touchMode(Touch::DispatchMode::ALL_AT_ONCE)
{

}

InputDelegate::~InputDelegate(void)
{
}

bool InputDelegate::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    return true;
}

void InputDelegate::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void InputDelegate::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void InputDelegate::ccTouchesBegan(Set *pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::ccTouchesEnded(Set *pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::ccTouchesCancelled(Set *pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::didAccelerate(Acceleration* pAccelerationValue)
{
   CC_UNUSED_PARAM(pAccelerationValue);
}

bool InputDelegate::isTouchEnabled() const
{
    return _touchEnabled;
}

void InputDelegate::setTouchEnabled(bool enabled)
{
    if (_touchEnabled != enabled)
    {
        _touchEnabled = enabled;
        if (enabled)
        {
            if( _touchMode == Touch::DispatchMode::ALL_AT_ONCE )
            {
                Director::getInstance()->getTouchDispatcher()->addStandardDelegate(this, 0);
            }
            else
            {
                Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, _touchPriority, true);
            }
        }
        else
        {
            Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}

void InputDelegate::setTouchMode(Touch::DispatchMode mode)
{
    if(_touchMode != mode)
    {
        _touchMode = mode;
        
		if( _touchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

void InputDelegate::setTouchPriority(int priority)
{
    if (_touchPriority != priority)
    {
        _touchPriority = priority;
        
		if( _touchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

int InputDelegate::getTouchPriority() const
{
    return _touchPriority;
}

Touch::DispatchMode InputDelegate::getTouchMode() const
{
    return _touchMode;
}

bool InputDelegate::isAccelerometerEnabled() const
{
    return _accelerometerEnabled;
}

void InputDelegate::setAccelerometerEnabled(bool enabled)
{
    if (enabled != _accelerometerEnabled)
    {
        _accelerometerEnabled = enabled;

        Director* pDirector = Director::getInstance();
        if (enabled)
        {
            pDirector->getAccelerometer()->setDelegate(CC_CALLBACK_1(InputDelegate::didAccelerate, this));
        }
        else
        {
            pDirector->getAccelerometer()->setDelegate(nullptr);
        }
    }
}

bool InputDelegate::isKeypadEnabled() const
{
    return _keypadEnabled;
}

void InputDelegate::setKeypadEnabled(bool enabled)
{
    if (enabled != _keypadEnabled)
    {
        _keypadEnabled = enabled;

        Director* pDirector = Director::getInstance();
        if (enabled)
        {
            pDirector->getKeypadDispatcher()->addDelegate(this);
        }
        else
        {
            pDirector->getKeypadDispatcher()->removeDelegate(this);
        }
    }
}


NS_CC_EXT_END
