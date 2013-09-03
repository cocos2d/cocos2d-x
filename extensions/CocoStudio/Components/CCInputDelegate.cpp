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
, _touchListenerId(0)
, _accelerometerEnabled(false)
, _accelerometerListenerId(0)
, _keypadEnabled(false)
, _keyboardListenerId(0)
, _touchPriority(0)
, _touchMode(Touch::DispatchMode::ALL_AT_ONCE)
{

}

InputDelegate::~InputDelegate(void)
{
    auto dispatcher = EventDispatcher::getInstance();
    dispatcher->unregisterEventListener(_touchListenerId);
    dispatcher->unregisterEventListener(_keyboardListenerId);
    dispatcher->unregisterEventListener(_accelerometerListenerId);
}

bool InputDelegate::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    return true;
}

void InputDelegate::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void InputDelegate::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void InputDelegate::onTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::onTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::onTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void InputDelegate::onTouchesCancelled(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
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
            EventDispatcher::getInstance()->unregisterEventListener(_touchListenerId);
            
            if( _touchMode == Touch::DispatchMode::ALL_AT_ONCE ) {
                // Register Touch Event
                auto listener = TouchEventListener::create(Touch::DispatchMode::ALL_AT_ONCE);
                
                listener->onTouchesBegan = CC_CALLBACK_2(InputDelegate::onTouchesBegan, this);
                listener->onTouchesMoved = CC_CALLBACK_2(InputDelegate::onTouchesMoved, this);
                listener->onTouchesEnded = CC_CALLBACK_2(InputDelegate::onTouchesEnded, this);
                listener->onTouchesCancelled = CC_CALLBACK_2(InputDelegate::onTouchesCancelled, this);
                
                _touchListenerId = EventDispatcher::getInstance()->registerEventListenerWithFixedPriority(listener, 0);
            } else {
                // Register Touch Event
                auto listener = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
                listener->setSwallowTouches(true);
                
                listener->onTouchBegan = CC_CALLBACK_2(InputDelegate::onTouchBegan, this);
                listener->onTouchMoved = CC_CALLBACK_2(InputDelegate::onTouchMoved, this);
                listener->onTouchEnded = CC_CALLBACK_2(InputDelegate::onTouchEnded, this);
                listener->onTouchCancelled = CC_CALLBACK_2(InputDelegate::onTouchCancelled, this);
                
                _touchListenerId = EventDispatcher::getInstance()->registerEventListenerWithFixedPriority(listener, _touchPriority);
            }
        }
        else
        {
            EventDispatcher::getInstance()->unregisterEventListener(_touchListenerId);
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

        auto dispatcher = EventDispatcher::getInstance();
        dispatcher->unregisterEventListener(_accelerometerListenerId);
        if (enabled)
        {
            auto listener = AccelerationEventListener::create(CC_CALLBACK_2(InputDelegate::onAcceleration, this));
            _accelerometerListenerId = dispatcher->registerEventListenerWithFixedPriority(listener, 0);
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

        if (enabled)
        {
            auto listener = KeyboardEventListener::create();
            listener->onKeyPressed = CC_CALLBACK_2(InputDelegate::onKeyPressed, this);
            listener->onKeyReleased = CC_CALLBACK_2(InputDelegate::onKeyReleased, this);
            
            _keyboardListenerId = EventDispatcher::getInstance()->registerEventListenerWithFixedPriority(listener, 0);
        }
    }
}


NS_CC_EXT_END
