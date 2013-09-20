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

#ifndef __cocos2d_libs__CCCustomEventListener__
#define __cocos2d_libs__CCCustomEventListener__

#include "CCEventListener.h"

NS_CC_BEGIN

class EventCustom;

/**
 *  Usage:
 *        auto dispatcher = EventDispatcher::getInstance();
 *     Adds a listener:
 *
 *        auto callback = [](CustomEvent* event){ do_some_thing(); };
 *        auto listener = CustomEventListener::create(callback);
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
class EventListenerCustom : public EventListener
{
public:
    /** Creates an event listener with type and callback.
     *  @param eventType The type of the event.
     *  @param callback The callback function when the specified event was emitted.
     */
    static EventListenerCustom* create(const std::string& eventName, std::function<void(EventCustom*)> callback);
    
    /// Overrides
    virtual bool checkAvaiable() override;
    virtual EventListenerCustom* clone() override;
    
protected:
    /** Constructor */
    EventListenerCustom();
    
    /** Initializes event with type and callback function */
    bool init(const std::string& eventName, std::function<void(EventCustom*)> callback);
    
    std::function<void(EventCustom*)> _onCustomEvent;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCCustomEventListener__) */
