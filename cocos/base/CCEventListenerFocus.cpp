/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "base/CCEventListenerFocus.h"
#include "base/CCEventFocus.h"
#include "base/ccMacros.h"

NS_CC_BEGIN


const std::string EventListenerFocus::LISTENER_ID = "__cc_focus_event";


EventListenerFocus::EventListenerFocus()
:onFocusChanged(nullptr)
{
    
}

EventListenerFocus::~EventListenerFocus()
{
    CCLOGINFO("In the destructor of EventListenerFocus, %p", this);
}

EventListenerFocus* EventListenerFocus::create()
{
    EventListenerFocus* ret = new (std::nothrow) EventListenerFocus;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

EventListenerFocus* EventListenerFocus::clone()
{
    EventListenerFocus* ret = new (std::nothrow) EventListenerFocus;
    if (ret && ret->init()) {
        ret->autorelease();
        
        ret->onFocusChanged = onFocusChanged;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerFocus::init()
{
    auto listener = [this](Event* event){
        auto focusEvent = static_cast<EventFocus*>(event);
        onFocusChanged(focusEvent->_widgetLoseFocus, focusEvent->_widgetGetFocus);
    };
    if (EventListener::init(Type::FOCUS, LISTENER_ID, listener)) {
        return true;
    }
    return false;
}

bool EventListenerFocus::checkAvailable()
{
    if (onFocusChanged == nullptr)
    {
        CCASSERT(false, "Invalid EventListenerFocus!");
        return false;
    }
    
    return true;
}



NS_CC_END
