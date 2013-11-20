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

#include "CCPlatformMacros.h"
#include "CCEventListener.h"
#include "CCEvent.h"

#include <functional>
#include <string>
#include <unordered_map>
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
class EventDispatcher : public Object
{
public:
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

    /** Removes all listeners with the same event listener type */
    void removeEventListeners(EventListener::Type listenerType);
    
    /** Removes all custom listeners with the same event name */
    void removeCustomEventListeners(const std::string& customEventName);
    
    /** Removes all listeners */
    void removeAllEventListeners();

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
    void dispatchEvent(Event* event);
    
    /** Constructor of EventDispatcher */
    EventDispatcher();
    /** Destructor of EventDispatcher */
    ~EventDispatcher();

private:
    friend class Node;
    
    /** Sets the dirty flag for a node. */
    void setDirtyForNode(Node* node);
    
    /** Notifys event dispatcher that the node has been paused. */
    void pauseTarget(Node* node);
    
    /** Notifys event dispatcher that the node has been resumed. */
    void resumeTarget(Node* node);
    
    /** Notifys event dispatcher that the node has been deleted. */
    void cleanTarget(Node* node);
    
    /**
     *  The vector to store event listeners with scene graph based priority and fixed priority.
     */
    class EventListenerVector
    {
    public:
        EventListenerVector();
        ~EventListenerVector();
        size_t size() const;
        bool empty() const;
        
        void push_back(EventListener* item);
        void clearSceneGraphListeners();
        void clearFixedListeners();
        void clear();
        
        inline std::vector<EventListener*>* getFixedPriorityListeners() const { return _fixedListeners; };
        inline std::vector<EventListener*>* getSceneGraphPriorityListeners() const { return _sceneGraphListeners; };
        inline long getGt0Index() const { return _gt0Index; };
        inline void setGt0Index(long index) { _gt0Index = index; };
    private:
        std::vector<EventListener*>* _fixedListeners;
        std::vector<EventListener*>* _sceneGraphListeners;
        long _gt0Index;
    };
    
    /** Adds event listener with item */
    void addEventListener(EventListener* listener);
    
    /** Gets event the listener list for the event listener type. */
    EventListenerVector* getListeners(EventListener::ListenerID listenerID);
    
    /** Update dirty flag */
    void updateDirtyFlagForSceneGraph();
    
    /** Removes all listeners with the same event listener ID */
    void removeEventListenersForListenerID(EventListener::ListenerID listenerID);
    
    /** Sort event listener */
    void sortEventListeners(EventListener::ListenerID listenerID);
    
    /** Sorts the listeners of specified type by scene graph priority */
    void sortEventListenersOfSceneGraphPriority(EventListener::ListenerID listenerID);
    
    /** Sorts the listeners of specified type by fixed priority */
    void sortEventListenersOfFixedPriority(EventListener::ListenerID listenerID);
    
    /** Updates all listeners
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     */
    void updateListeners(Event* event);

    /** Touch event needs to be processed different with other events since it needs support ALL_AT_ONCE and ONE_BY_NONE mode. */
    void dispatchTouchEvent(EventTouch* event);
    
    /** Associates node with event listener */
    void associateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** Dissociates node with event listener */
    void dissociateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** Dispatches event to listeners with a specified listener type */
    void dispatchEventToListeners(EventListenerVector* listeners, std::function<bool(EventListener*)> onEvent);
    
    /// Priority dirty flag
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRITORY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRITORY | SCENE_GRAPH_PRIORITY
    };
    
    /** Sets the dirty flag for a specified listener ID */
    void setDirty(EventListener::ListenerID listenerID, DirtyFlag flag);
    
    /** Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority */
    void visitTarget(Node* node);
    
private:
    /** Listeners map */
    std::unordered_map<EventListener::ListenerID, EventListenerVector*> _listeners;
    
    /** The map of dirty flag */
    std::unordered_map<EventListener::ListenerID, DirtyFlag> _priorityDirtyFlagMap;
    
    /** The map of node and event listeners */
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** The map of node and its event priority */
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** The listeners to be added after dispatching event */
    std::vector<EventListener*> _toAddedListeners;
    
    /** The nodes were associated with scene graph based priority listeners */
    std::set<Node*> _dirtyNodes;
    
    /** Whether the dispatcher is dispatching event */
    int _inDispatch;
    
    /** Whether to enable dispatching event */
    bool _isEnabled;
    
    int _nodePriorityIndex;
};


NS_CC_END


#endif // __CC_EVENT_DISPATCHER_H__
