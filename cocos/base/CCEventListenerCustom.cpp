/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "base/CCEventListenerCustom.h"
#include "base/CCEventCustom.h"

NS_CC_BEGIN

EventListenerCustom::EventListenerCustom()
: _onCustomEvent(nullptr)
{
}

EventListenerCustom* EventListenerCustom::create(const std::string& eventName, const std::function<void(EventCustom*)>& callback)
{
    EventListenerCustom* ret = new EventListenerCustom();
    if (ret && ret->init(eventName, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerCustom::init(const ListenerID& listenerId, const std::function<void(EventCustom*)>& callback)
{
    bool ret = false;
    
    _onCustomEvent = callback;
    
    auto listener = [this](Event* event){
        if (_onCustomEvent != nullptr)
        {
            _onCustomEvent(static_cast<EventCustom*>(event));
        }
    };
    
    if (EventListener::init(EventListener::Type::CUSTOM, listenerId, listener))
    {
        ret = true;
    }
    return ret;
}

EventListenerCustom* EventListenerCustom::clone()
{
    EventListenerCustom* ret = new EventListenerCustom();
    if (ret && ret->init(_listenerID, _onCustomEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerCustom::checkAvailable()
{
    bool ret = false;
    if (EventListener::checkAvailable() && _onCustomEvent != nullptr)
    {
        ret = true;
    }
    return ret;
}

NS_CC_END
