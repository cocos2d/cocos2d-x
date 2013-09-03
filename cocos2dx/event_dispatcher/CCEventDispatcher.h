//
//  CCEventDispatcher.h
//  cocos2d_libs
//
//  Created by James Chen on 8/30/13.
//
//

#ifndef __cocos2d_libs__CCEventDispatcher__
#define __cocos2d_libs__CCEventDispatcher__

#include "platform/CCPlatformMacros.h"
#include "CCEventDispatcherUnit.h"


NS_CC_BEGIN

class EventDispatcher
{
public:
    static EventDispatcher* getInstance();
    
    EventDispatcher();
    ~EventDispatcher();

    CallbackId registerEventCallback(const std::string& type, std::function<bool(Event*)> callback);    
	void unregisterEventCallback(CallbackId callbackId);
    void dispatchEvent(Event* event);
private:

    EventDispatcherUnit* _eventDispatcherUnit;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCEventDispatcher__) */
