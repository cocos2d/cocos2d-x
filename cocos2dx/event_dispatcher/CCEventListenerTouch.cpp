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

#include "CCEventListenerTouch.h"
#include "CCEventDispatcher.h"
#include "CCEventTouch.h"

#include <algorithm>

NS_CC_BEGIN

EventListenerTouch::EventListenerTouch()
: onTouchBegan(nullptr)
, onTouchMoved(nullptr)
, onTouchEnded(nullptr)
, onTouchCancelled(nullptr)
, onTouchesBegan(nullptr)
, onTouchesMoved(nullptr)
, onTouchesEnded(nullptr)
, onTouchesCancelled(nullptr)
, _needSwallow(false)
, _dispatchMode(Touch::DispatchMode::ALL_AT_ONCE)
{
}

EventListenerTouch::~EventListenerTouch()
{
    CCLOGINFO("In the destructor of TouchEventListener, %p", this);
}

bool EventListenerTouch::init(Touch::DispatchMode mode)
{
    if (EventListener::init(EventTouch::EVENT_TYPE, nullptr))
    {
        _dispatchMode = mode;
        return true;
    }
    
    return false;
}

void EventListenerTouch::setSwallowTouches(bool needSwallow)
{
    CCASSERT(_dispatchMode == Touch::DispatchMode::ONE_BY_ONE, "Swallow touches only available in OneByOne mode.");
    _needSwallow = needSwallow;
}

EventListenerTouch* EventListenerTouch::create(Touch::DispatchMode mode)
{
    auto ret = new EventListenerTouch();
    if (ret && ret->init(mode))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerTouch::checkAvaiable()
{
    if (_dispatchMode == Touch::DispatchMode::ALL_AT_ONCE)
    {
        if (onTouchesBegan == nullptr && onTouchesMoved == nullptr
            && onTouchesEnded == nullptr && onTouchesCancelled == nullptr)
        {
            CCASSERT(false, "Invalid TouchEventListener.");
            return false;
        }
    }
    else if (_dispatchMode == Touch::DispatchMode::ONE_BY_ONE)
    {
        if (onTouchBegan == nullptr && onTouchMoved == nullptr
            && onTouchEnded == nullptr && onTouchCancelled == nullptr)
        {
            CCASSERT(false, "Invalid TouchEventListener.");
            return false;
        }
    }
    else
    {
        CCASSERT(false, "");
    }
    
    return true;
}

EventListenerTouch* EventListenerTouch::clone()
{
    auto ret = new EventListenerTouch();
    if (ret && ret->init(_dispatchMode))
    {
        ret->autorelease();
        
        ret->onTouchBegan = onTouchBegan;
        ret->onTouchMoved = onTouchMoved;
        ret->onTouchEnded = onTouchEnded;
        ret->onTouchCancelled = onTouchCancelled;
        ret->onTouchesBegan = onTouchesBegan;
        ret->onTouchesMoved = onTouchesMoved;
        ret->onTouchesEnded = onTouchesEnded;
        ret->onTouchesCancelled = onTouchesCancelled;
        
        ret->_claimedTouches = _claimedTouches;
        ret->_dispatchMode = _dispatchMode;
        ret->_needSwallow = _needSwallow;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

NS_CC_END