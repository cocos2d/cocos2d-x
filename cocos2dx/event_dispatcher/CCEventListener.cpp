//
//  CCEventListener.cpp
//  cocos2d_libs
//
//  Created by James Chen on 9/11/13.
//
//

#include "CCEventListener.h"
#include "platform/CCCommon.h"

NS_CC_BEGIN

std::shared_ptr<EventListener> EventListener::create(const std::string& eventType, std::function<void(Event*)> callback)
{
    std::shared_ptr<EventListener> ret(new EventListener(eventType, callback));
    return ret;
}

EventListener::EventListener(const std::string& t, std::function<void(Event*)>callback)
: onEvent(callback)
, type(t)
{}
    
EventListener::~EventListener() 
{
	CCLOG("In the destructor of EventListener.");
}

bool EventListener::checkAvaiable()
{ 
	return (onEvent != nullptr);
}

NS_CC_END
