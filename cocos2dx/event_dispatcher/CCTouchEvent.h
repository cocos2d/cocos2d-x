//
//  TouchEvent.h
//  cocos2d_libs
//
//  Created by James Chen on 8/31/13.
//
//

#ifndef __cocos2d_libs__TouchEvent__
#define __cocos2d_libs__TouchEvent__

#include "CCEvent.h"
#include "touch_dispatcher/CCTouch.h"
#include <vector>

NS_CC_BEGIN

class TouchEvent : public Event
{
public:
    static const char* EVENT_TYPE;
    
    enum class EventCode
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };
    
    TouchEvent()
    : Event(EVENT_TYPE)
    {
    }

    EventCode getEventCode() { return _eventCode; };
    const std::vector<Touch*> getTouches() { return _touches; };
    
private:
    EventCode _eventCode;
    std::vector<Touch*> _touches;
    
    friend class EGLViewProtocol;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__TouchEvent__) */
