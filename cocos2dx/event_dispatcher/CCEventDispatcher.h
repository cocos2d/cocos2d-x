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
#include <vector>

NS_CC_BEGIN

class Event;
class EventTouch;
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

    /** Destroys the singleton of EventDispatcher */
    static void destroyInstance();
    
    /** Adds a event listener for a specified event with the priority of scene graph.
     *  @param listener The listener of a specified event.
     *  @param node The priority of the listener is based on the draw order of this node.
     *  @note  The priority of scene graph will be fixed value 0. So the order of listener item
     *          in the vector will be ' <0, scene graph (0 priority), >0'.
     */
    void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);

    /** Adds a event listener for a specified event with the fixed priority.
     *  @param listener The listener of a specified event.
     *  @param fixedPriority The fixed priority of the listener.
     *  @note A lower priority will be called before the ones that have a higher value.
     *        0 priority is forbidden for fixed priority since it's used for scene graph based priority.
     */
    void addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority);

    /** Remove a listener 
     *  @param listener The specified event listener which needs to be removed.
     */
    void removeEventListener(EventListener* listener);

    /** Removes all listeners with the same event type */
    void removeListenersForEventType(const std::string& eventType);
    
    /** Removes all listeners */
    void removeAllListeners();

    /** Sets listener's priority with fixed value. */
    void setPriority(EventListener* listener, int fixedPriority);

    /** Whether to enable dispatching events */
    void setEnabled(bool isEnabled);

    /** Checks whether dispatching events is enabled */
    bool isEnabled() const;

    /** Dispatches the event
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     */
    void dispatchEvent(Event* event, bool forceSortListeners = false);

    void setDirtyForEventType(const std::string& eventType, bool isDirty);
    
    bool isDirtyForEventType(const std::string& eventType);
    
public:
    /** Destructor of EventDispatcher */
    ~EventDispatcher();

private:
    struct EventListenerItem
    {
        int            fixedPriority;   // The higher the number, the higher the priority
        Node*          node;            // Weak reference.
        EventListener* listener;
        ~EventListenerItem();
    };
    
    /** Constructor of EventDispatcher */
    EventDispatcher();
    
    /** Adds event listener with item */
    void addEventListenerWithItem(EventListenerItem* item);
    
    /** Touch event needs to be processed different with other events since it needs support ALL_AT_ONCE and ONE_BY_NONE mode. */
    void dispatchTouchEvent(EventTouch* event);
    
    /** Gets event the listener list for the event type. */
    std::vector<EventListenerItem*>* getListenerItemsForType(const std::string& eventType);
    
    /** Sorts the listeners of specified type by priority */
    void sortAllEventListenerItemsForType(const std::string& eventType);
    
    /** Updates all listener items
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     */
    void updateListenerItems();

private:
    /**
     * Listeners map.
     */
    std::map<std::string, std::vector<EventListenerItem*>*> _listeners;
    
    /// Priority dirty flag
    std::map<std::string, bool> _priorityDirtyFlagMap;
    
    std::vector<EventListenerItem*> _toAddedListeners;
    
    int   _inDispatch;        ///< Whether it's in dispatching event
    bool  _isEnabled;         ///< Whether to enable dispatching event
};


NS_CC_END


#endif // __CC_EVENT_DISPATCHER_H__
