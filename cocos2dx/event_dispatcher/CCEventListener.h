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
#include "cocoa/CCObject.h"

#include <functional>
#include <string>
#include <memory>

NS_CC_BEGIN

class Event;

/**
 *  The base class of event listener.
 *  If you need custom listener which with different callback, you need to inherit this class.
 *  For instance, you could refer to AccelerationEventListener, KeyboardEventListener or TouchEventListener.
 *  Usage:
 *        auto dispatcher = EventDispatcher::getInstance();
 *     Adds a listener:
 *
 *        auto callback = [](Event* event){ do_some_thing(); };
 *        auto listener = EventListener::create("your_event_type", callback);
 *        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
 *
 *     Dispatchs a custom event:
 *        
 *        Event event("your_event_type");
 *        dispatcher->dispatchEvent(&event);
 *
 *     Removes a listener
 *       
 *        dispatcher->removeListener(listener);
 */
class EventListener : public Object
{
public:
    /** Creates an event listener with type and callback.
     *  @param eventType The type of the event.
     *  @param callback The callback function when the specified event was emitted.
     */
    static EventListener* create(const std::string& eventType, std::function<void(Event*)> callback);
    
protected:
    /** Constructor */
    EventListener();
    
    /** Initializes event with type and callback function */
    bool init(const std::string& t, std::function<void(Event*)>callback);
public:
    /** Destructor */
    virtual ~EventListener();
    
    /** Checks whether the listener is available. */
    virtual bool checkAvaiable();
    
    /** Clones the listener, its subclasses have to override this method. */
    virtual EventListener* clone();
protected:
    std::function<void(Event*)> onEvent;   /// Event callback function
    std::string type;                      /// Event type
    bool _isRegistered;                    /// Whether the listener has been added to dispatcher.
    
    friend class EventDispatcher;
};

NS_CC_END

#endif
