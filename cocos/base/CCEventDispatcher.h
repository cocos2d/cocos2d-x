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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

#include "platform/CCPlatformMacros.h"
#include "base/CCEventListener.h"
#include "base/CCEvent.h"
#include "platform/CCStdC.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class EventTouch;
class Node;
class EventCustom;
class EventListenerCustom;

/** @class EventDispatcher
* @brief This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
@js NA
*/
class CC_DLL EventDispatcher : public Ref
{
public:
    // Adds event listener.
    
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

    /** Adds a Custom event listener.
     It will use a fixed priority of 1.
     * @param eventName A given name of the event.
     * @param callback A given callback method that associated the event name.
     * @return the generated event. Needed in order to remove the event from the dispather
     */
    EventListenerCustom* addCustomEventListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback);

    /////////////////////////////////////////////
    
    // Removes event listener
    
    /** Remove a listener.
     *
     *  @param listener The specified event listener which needs to be removed.
     */
    void removeEventListener(EventListener* listener);

    /** Removes all listeners with the same event listener type.
     *
     * @param listenerType A given event listener type which needs to be removed.
     */
    void removeEventListenersForType(EventListener::Type listenerType);

    /** Removes all listeners which are associated with the specified target.
     *
     * @param target A given target node.
     * @param recursive True if remove recursively, the default value is false.
     */
    void removeEventListenersForTarget(Node* target, bool recursive = false);
    
    /** Removes all custom listeners with the same event name.
     *
     * @param customEventName A given event listener name which needs to be removed.
     */
    void removeCustomEventListeners(const std::string& customEventName);

    /** Removes all listeners.
     */
    void removeAllEventListeners();

    /////////////////////////////////////////////
    
    // Pauses / Resumes event listener
    
    /** Pauses all listeners which are associated the specified target.
     *
     * @param target A given target node.
     * @param recursive True if pause recursively, the default value is false.
     */
    void pauseEventListenersForTarget(Node* target, bool recursive = false);
    
    /** Resumes all listeners which are associated the specified target.
     *
     * @param target A given target node.
     * @param recursive True if resume recursively, the default value is false.
     */
    void resumeEventListenersForTarget(Node* target, bool recursive = false);
    
    /////////////////////////////////////////////
    
    /** Sets listener's priority with fixed value.
     * 
     * @param listener A given listener.
     * @param fixedPriority The fixed priority value.
     */
    void setPriority(EventListener* listener, int fixedPriority);

    /** Whether to enable dispatching events.
     *
     * @param isEnabled  True if enable dispatching events.
     */
    void setEnabled(bool isEnabled);

    /** Checks whether dispatching events is enabled.
     *
     * @return True if dispatching events is enabled.
     */
    bool isEnabled() const;

    /////////////////////////////////////////////
    
    /** Dispatches the event.
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     *
     * @param event The event needs to be dispatched.
     */
    void dispatchEvent(Event* event);

    /** Dispatches a Custom Event with a event name an optional user data.
     *
     * @param eventName The name of the event which needs to be dispatched.
     * @param optionalUserData The optional user data, it's a void*, the default value is nullptr.
     */
    void dispatchCustomEvent(const std::string &eventName, void *optionalUserData = nullptr);

    /////////////////////////////////////////////
    
    /** Constructor of EventDispatcher.
     */
    EventDispatcher();
    /** Destructor of EventDispatcher.
     */
    ~EventDispatcher();

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    
    /**
     * To help track down event listener issues in debug builds.
     * Verifies that the node has no event listeners associated with it when destroyed.
     */
    void debugCheckNodeHasNoEventListenersOnDestruction(Node* node);
    
#endif

protected:
    friend class Node;
    
    /** Sets the dirty flag for a node. */
    void setDirtyForNode(Node* node);
    
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
        inline ssize_t getGt0Index() const { return _gt0Index; };
        inline void setGt0Index(ssize_t index) { _gt0Index = index; };
    private:
        std::vector<EventListener*>* _fixedListeners;
        std::vector<EventListener*>* _sceneGraphListeners;
        ssize_t _gt0Index;
    };
    
    /** Adds an event listener with item
     *  @note if it is dispatching event, the added operation will be delayed to the end of current dispatch
     *  @see forceAddEventListener
     */
    void addEventListener(EventListener* listener);
    
    /** Force adding an event listener
     *  @note force add an event listener which will ignore whether it's in dispatching.
     *  @see addEventListener
     */
    void forceAddEventListener(EventListener* listener);
    
    /** Gets event the listener list for the event listener type. */
    EventListenerVector* getListeners(const EventListener::ListenerID& listenerID);
    
    /** Update dirty flag */
    void updateDirtyFlagForSceneGraph();
    
    /** Removes all listeners with the same event listener ID */
    void removeEventListenersForListenerID(const EventListener::ListenerID& listenerID);
    
    /** Sort event listener */
    void sortEventListeners(const EventListener::ListenerID& listenerID);
    
    /** Sorts the listeners of specified type by scene graph priority */
    void sortEventListenersOfSceneGraphPriority(const EventListener::ListenerID& listenerID, Node* rootNode);
    
    /** Sorts the listeners of specified type by fixed priority */
    void sortEventListenersOfFixedPriority(const EventListener::ListenerID& listenerID);
    
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
    void dispatchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /// Priority dirty flag
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRIORITY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRIORITY | SCENE_GRAPH_PRIORITY
    };
    
    /** Sets the dirty flag for a specified listener ID */
    void setDirty(const EventListener::ListenerID& listenerID, DirtyFlag flag);
    
    /** Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority */
    void visitTarget(Node* node, bool isRootNode);
    
    /** Listeners map */
    std::unordered_map<EventListener::ListenerID, EventListenerVector*> _listenerMap;
    
    /** The map of dirty flag */
    std::unordered_map<EventListener::ListenerID, DirtyFlag> _priorityDirtyFlagMap;
    
    /** The map of node and event listeners */
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** The map of node and its event priority */
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** key: Global Z Order, value: Sorted Nodes */
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;
    
    /** The listeners to be added after dispatching event */
    std::vector<EventListener*> _toAddedListeners;
    
    /** The nodes were associated with scene graph based priority listeners */
    std::set<Node*> _dirtyNodes;
    
    /** Whether the dispatcher is dispatching event */
    int _inDispatch;
    
    /** Whether to enable dispatching event */
    bool _isEnabled;
    
    int _nodePriorityIndex;
    
    std::set<std::string> _internalCustomListenerIDs;
};


NS_CC_END

// end of base group
/// @}

#endif // __CC_EVENT_DISPATCHER_H__
