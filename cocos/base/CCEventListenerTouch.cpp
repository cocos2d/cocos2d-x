/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventTouch.h"
#include "base/CCTouch.h"

#include <algorithm>

NS_CC_BEGIN

const std::string EventListenerTouchOneByOne::LISTENER_ID = "__cc_touch_one_by_one";

EventListenerTouchOneByOne::EventListenerTouchOneByOne()
: onTouchBegan(nullptr)
, onTouchMoved(nullptr)
, onTouchEnded(nullptr)
, onTouchCancelled(nullptr)
, _needSwallow(false)
{
}

EventListenerTouchOneByOne::~EventListenerTouchOneByOne()
{
    CCLOGINFO("In the destructor of EventListenerTouchOneByOne, %p", this);
}

bool EventListenerTouchOneByOne::init()
{
    if (EventListener::init(Type::TOUCH_ONE_BY_ONE, LISTENER_ID, nullptr))
    {
        return true;
    }
    
    return false;
}

void EventListenerTouchOneByOne::setSwallowTouches(bool needSwallow)
{
    _needSwallow = needSwallow;
}

bool EventListenerTouchOneByOne::isSwallowTouches()
{
    return _needSwallow;
}

EventListenerTouchOneByOne* EventListenerTouchOneByOne::create()
{
    auto ret = new (std::nothrow) EventListenerTouchOneByOne();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerTouchOneByOne::checkAvailable()
{
    // EventDispatcher will use the return value of 'onTouchBegan' to determine whether to pass following 'move', 'end'
    // message to 'EventListenerTouchOneByOne' or not. So 'onTouchBegan' needs to be set.
    if (onTouchBegan == nullptr)
    {
        CCASSERT(false, "Invalid EventListenerTouchOneByOne!");
        return false;
    }
    
    return true;
}

EventListenerTouchOneByOne* EventListenerTouchOneByOne::clone()
{
    auto ret = new (std::nothrow) EventListenerTouchOneByOne();
    if (ret && ret->init())
    {
        ret->autorelease();
        
        ret->onTouchBegan = onTouchBegan;
        ret->onTouchMoved = onTouchMoved;
        ret->onTouchEnded = onTouchEnded;
        ret->onTouchCancelled = onTouchCancelled;
        
        ret->_claimedTouches = _claimedTouches;
        ret->_needSwallow = _needSwallow;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

/////////

const std::string EventListenerTouchAllAtOnce::LISTENER_ID = "__cc_touch_all_at_once";

EventListenerTouchAllAtOnce::EventListenerTouchAllAtOnce()
: onTouchesBegan(nullptr)
, onTouchesMoved(nullptr)
, onTouchesEnded(nullptr)
, onTouchesCancelled(nullptr)
{
}

EventListenerTouchAllAtOnce::~EventListenerTouchAllAtOnce()
{
    CCLOGINFO("In the destructor of EventListenerTouchAllAtOnce, %p", this);
}

bool EventListenerTouchAllAtOnce::init()
{
    if (EventListener::init(Type::TOUCH_ALL_AT_ONCE, LISTENER_ID, nullptr))
    {
        return true;
    }
    
    return false;
}

EventListenerTouchAllAtOnce* EventListenerTouchAllAtOnce::create()
{
    auto ret = new (std::nothrow) EventListenerTouchAllAtOnce();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerTouchAllAtOnce::checkAvailable()
{
    if (onTouchesBegan == nullptr && onTouchesMoved == nullptr
        && onTouchesEnded == nullptr && onTouchesCancelled == nullptr)
    {
        CCASSERT(false, "Invalid EventListenerTouchAllAtOnce!");
        return false;
    }
    
    return true;
}

EventListenerTouchAllAtOnce* EventListenerTouchAllAtOnce::clone()
{
    auto ret = new (std::nothrow) EventListenerTouchAllAtOnce();
    if (ret && ret->init())
    {
        ret->autorelease();
        
        ret->onTouchesBegan = onTouchesBegan;
        ret->onTouchesMoved = onTouchesMoved;
        ret->onTouchesEnded = onTouchesEnded;
        ret->onTouchesCancelled = onTouchesCancelled;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

NS_CC_END
