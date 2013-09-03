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

#ifndef cocos2d_libs_EventListener_h
#define cocos2d_libs_EventListener_h

#include "platform/CCPlatformMacros.h"

#include <functional>
#include <string>
#include <memory>

NS_CC_BEGIN

class Event;

class EventListener
{
public:
    static std::shared_ptr<EventListener> create(const std::string& eventType, std::function<void(Event*)> callback);
    
protected:
    EventListener(const std::string& t, std::function<void(Event*)>callback);
    
public:
    virtual ~EventListener();
    virtual bool checkAvaiable();
    
protected:
    std::function<void(Event*)> onEvent;
    std::string type;
    
    friend class EventDispatcher;
};

NS_CC_END

#endif
