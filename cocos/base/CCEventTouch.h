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

#ifndef __cocos2d_libs__TouchEvent__
#define __cocos2d_libs__TouchEvent__

#include "base/CCEvent.h"
#include "base/CCTouch.h"
#include <vector>

NS_CC_BEGIN

#define TOUCH_PERF_DEBUG 1

class EventTouch : public Event
{
public:
    static const int MAX_TOUCHES = 5;
    
    enum class EventCode
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };

    EventTouch();

    inline EventCode getEventCode() const { return _eventCode; };
    inline const std::vector<Touch*>& getTouches() const { return _touches; };

#if TOUCH_PERF_DEBUG
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };
    void setTouches(const std::vector<Touch*>& touches) { _touches = touches; };
#endif
    
private:
    EventCode _eventCode;
    std::vector<Touch*> _touches;

    friend class GLViewProtocol;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__TouchEvent__) */
