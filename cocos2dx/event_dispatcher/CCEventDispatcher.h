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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include "platform/CCPlatformMacros.h"
#include "CCEventListener.h"

#include <functional>
#include <string>
#include <map>
#include <list>

NS_CC_BEGIN

class Event;
class TouchEvent;
class Node;

/**
This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
*/
class EventDispatcher
{
public:
    /** Gets the singleton of EventDispatcher */
    static EventDispatcher* getInstance();

    /** Registers a callback function for an specified event with the priority of scene graph.
     *  @return The unique ID for the listener.
     */
    int registerEventListenerWithSceneGraphPriority(std::shared_ptr<EventListener> listener, Node* node);

    /** Registers a callback function for an specified event with the fixed priority.
     *  @return The unique ID for the listener.
     */
    int registerEventListenerWithFixedPriority(std::shared_ptr<EventListener> listener, int fixedPriority);

    /** Unregisters a callback function by the unique ID. */
    void unregisterEventListener(int listenerId);

    /** Sets listener's priority with node's draw order. */
    void setPriorityWithSceneGraph(int listenerId, Node* node);

    /** Sets listener's priority with fixed value. */
    void setPriorityWithFixedValue(int listenerId, int fixedPriority);

    /** Whether to enable dispatching events */
    void setEnabled(bool isEnabled) { _isEnabled = isEnabled; };

    /** Checks whether dispatching events is enabled */
    bool isEnabled() const { return _isEnabled; };

    /** Dispatches the event
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     */
    void dispatchEvent(Event* event);
    
    /** Removes listeners by event type */
    void removeListenersForEventType(const std::string& eventType);
    
    /** Removes all listeners */
    void removeAllListeners();

public:
    /** Destructor of EventDispatcher */
    ~EventDispatcher();

private:
    struct EventListenerItem
    {
        int           id;
        Node*         node;            // Weak reference.
        int           fixedPriority;   // The higher the number, the higher the priority
        std::shared_ptr<EventListener> listener;
    };
    
    /** Constructor of EventDispatcher */
    EventDispatcher();
    
    void registerEventListenerWithItem(EventListenerItem* item);
    
    /** Touch event needs to be processed different with other events since it needs support ALL_AT_ONCE and ONE_BY_NONE mode. */
    void dispatchTouchEvent(TouchEvent* event);
    
    /** Gets event listener list by event type. */
    std::list<EventListenerItem*>* getListeners(const std::string& eventType);
    
    /** Sorts all listeners by priority */
    void sortAllEventListenerItems();
    
    /** Remove listeners that have been unregistered. */
    void removeUnregisteredListeners();

private:
    /**
     * Listeners map.
     */
    std::map<std::string, std::list<EventListenerItem*>*>* _listeners;

    int               _inDispatch;
    std::list<Node*>  _eventNodes;
    bool              _isEnabled;
};


NS_CC_END


#endif // __CC_EVENT_DISPATCHER_H__
