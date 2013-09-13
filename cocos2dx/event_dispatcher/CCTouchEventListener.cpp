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

#include "CCTouchEventListener.h"
#include "CCEventDispatcher.h"
#include "CCTouchEvent.h"

#include <algorithm>

NS_CC_BEGIN

TouchEventListener::TouchEventListener(Touch::DispatchMode mode)
: EventListener(TouchEvent::EVENT_TYPE, nullptr)
, onTouchBegan(nullptr)
, onTouchMoved(nullptr)
, onTouchEnded(nullptr)
, onTouchCancelled(nullptr)
, onTouchesBegan(nullptr)
, onTouchesMoved(nullptr)
, onTouchesEnded(nullptr)
, onTouchesCancelled(nullptr)
, _needSwallow(false)
, _dispatchMode(mode)
{
}

void TouchEventListener::setSwallowTouches(bool needSwallow)
{
    CCASSERT(_dispatchMode == Touch::DispatchMode::ONE_BY_ONE, "Swallow touches only available in OneByOne mode.");
    _needSwallow = needSwallow;
}

std::shared_ptr<TouchEventListener> TouchEventListener::create(Touch::DispatchMode mode)
{
    std::shared_ptr<TouchEventListener> ret(new TouchEventListener(mode));
    return ret;
}

bool TouchEventListener::checkAvaiable()
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

std::shared_ptr<EventListener> TouchEventListener::clone()
{
    std::shared_ptr<TouchEventListener> ret(new TouchEventListener(_dispatchMode));
    
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
    
    return ret;
}

NS_CC_END