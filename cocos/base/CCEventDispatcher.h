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
* @brief @~english This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
 * @~chinese 这个类管理事件监听器的订阅和事件的分发
 * 
 * 
 * 事件监听器列表以这样的方式来进行管理：当事件正在分发的过程中，事件监听器可以被添加或者移除，包括事件监听器内部的监听器
@js NA
*/
class CC_DLL EventDispatcher : public Ref
{
public:
    // Adds event listener.
    
    /** @~english Adds a event listener for a specified event with the priority of scene graph.
     * @~chinese 给一个指定的事件添加一个事件监听器，该监听器带有基于场景图的优先级 。
     *  @param listener @~english The listener of a specified event.
     * @~chinese 指定事件的监听器。
     *  @param node @~english The priority of the listener is based on the draw order of this node.
     * @~chinese 监听器的优先级基于此节点的绘制顺序.
     *  @note  @~english The priority of scene graph will be fixed value 0. So the order of listener item
     *          in the vector will be ' <0, scene graph (0 priority), >0'.
     * @~chinese 场景图的优先级会被设置为固定值0，因此在容器(vector)中的侦听器的次序将会是：' <0, scene graph (0 priority), >0' .
     * 
     */
    void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);

    /** @~english Adds a event listener for a specified event with the fixed priority.
     * @~chinese 为指定的事件添加一个固定优先级事件监听器。
     *  @param listener @~english The listener of a specified event.
     * @~chinese 指定事件的监听器。
     *  @param fixedPriority @~english The fixed priority of the listener.
     * @~chinese 监听器的固定优先级。
     *  @note @~english A lower priority will be called before the ones that have a higher value.
     *        0 priority is forbidden for fixed priority since it's used for scene graph based priority.
     * @~chinese 值越小的将会比值大的先调用。
     * 0用来作为场景图的基础优先级，所以优先级不能设置为0
     */
    void addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority);

    /** @~english Adds a Custom event listener.
     It will use a fixed priority of 1.
     * @~chinese 添加一个自定义事件监听器。
     * 该监听器会使用值为1的一个固定优先级.
     * @param eventName @~english A given name of the event.
     * @~chinese 任意的事件名称。
     * @param callback @~english A given callback method that associated the event name.
     * @~chinese 跟事件名称关联的回调函数。
     * @return @~english the generated event. In order to remove the event later from the dispather 
     * @~chinese 返回产生的事件，以便后面从派发器中移除这个事件
     */
    EventListenerCustom* addCustomEventListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback);

    /////////////////////////////////////////////
    
    // Removes event listener
    
    /** @~english Remove a listener.
     *
     * @~chinese 删除一个监听器。
     * 
     *  @param listener @~english The specified event listener which needs to be removed.
     * @~chinese 需要被移除的事件监听器。
     */
    void removeEventListener(EventListener* listener);

    /** @~english Removes all listeners with the same event listener type.
     *
     * @~chinese 移除所有使用相同事件监听器类型的监听器
     * 
     * @param listenerType @~english A given event listener type which needs to be removed.
     * @~chinese 给定需要删除的事件监听器类型。
     */
    void removeEventListenersForType(EventListener::Type listenerType);

    /** @~english Removes all listeners which are associated with the specified target.
     *
     * @~chinese 移除所有与指定节点相关联的监听器
     * 
     * @param target @~english A given target node.
     * @~chinese 一个给定的目标节点。
     * @param recursive @~english True if remove recursively, the default value is false.
     * @~chinese 是否递归删除子节点的监听器。默认值是false。
     */
    void removeEventListenersForTarget(Node* target, bool recursive = false);
    
    /** @~english Removes all custom listeners with the same event name.
     *
     * @~chinese 删除所有的名称相同的自定义事件监听器。
     * 
     * @param customEventName @~english A given event listener name which needs to be removed.
     * @~chinese 给定一个需要删除的事件监听器名称,。
     */
    void removeCustomEventListeners(const std::string& customEventName);

    /** @~english Removes all listeners.
     * @~chinese 删除所有的听众。
     */
    void removeAllEventListeners();

    /////////////////////////////////////////////
    
    // Pauses / Resumes event listener
    
    /** @~english Pauses all listeners which are associated the specified target.
     *
     * @~chinese 暂停所有与指定节点相关联的监听器
     * 
     * @param target @~english A given target node.
     * @~chinese 一个给定的目标节点。
     * @param recursive @~english True if pause recursively, the default value is false.
     * @~chinese 是否递归暂停子节点的监听器,默认值是false。
     */
    void pauseEventListenersForTarget(Node* target, bool recursive = false);
    
    /** @~english Resumes all listeners which are associated the specified target.
     *
     * @~chinese 回复所有与指定节点相关联的监听器
     * 
     * @param target @~english A given target node.
     * @~chinese 一个给定的目标节点。
     * @param recursive @~english True if resume recursively, the default value is false.
     * @~chinese 是否递归恢复子节点的监听器,默认值是false。
     */
    void resumeEventListenersForTarget(Node* target, bool recursive = false);
    
    /////////////////////////////////////////////
    
    /** @~english Sets listener's priority with fixed value.
     * 
     * @~chinese 设置监听器的优先级为固定值。
     * 
     * @param listener @~english A given listener.
     * @~chinese 一个给定的监听器。
     * @param fixedPriority @~english The fixed priority value.
     * @~chinese 固定优先级。
     */
    void setPriority(EventListener* listener, int fixedPriority);

    /** @~english Whether to enable dispatching events.
     *
     * @~chinese 是否启用派发器。
     * 
     * @param isEnabled  @~english True if enable dispatching events.
     * @~chinese 如果为true，则开启派发器。
     */
    void setEnabled(bool isEnabled);

    /** @~english Checks whether dispatching events is enabled.
     *
     * @~chinese 检查是否启用了派发器。
     * 
     * @return @~english True if dispatching events is enabled.
     * @~chinese 如果为true，则开启派发器。
     */
    bool isEnabled() const;

    /////////////////////////////////////////////
    
    /** @~english Dispatches the event.
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     *
     * @~chinese 事件分发。
     * 还移除在事件分发列表中所有标记为删除的事件监听器
     * 
     * 
     * @param event @~english The event needs to be dispatched.
     * @~chinese 需要分发的事件。
     */
    void dispatchEvent(Event* event);

    /** @~english Dispatches a Custom Event with a event name an optional user data.
     *
     * @~chinese 分发一个指定事件名称和可选用户数据的自定义事件。
     * 
     * @param eventName @~english The name of the event which needs to be dispatched.
     * @~chinese 需要派发的事件名称,。
     * @param optionalUserData @~english The optional user data, it's a void*, the default value is nullptr.
     * @~chinese 可选的用户数据,类型是void * ,可以自行转换。默认值是nullptr
     */
    void dispatchCustomEvent(const std::string &eventName, void *optionalUserData = nullptr);

    /////////////////////////////////////////////
    
    /** @~english Constructor of EventDispatcher.
     * @~chinese EventDispatcher的构造函数。
     */
    EventDispatcher();
    /** @~english Destructor of EventDispatcher.
     * @~chinese EventDispatcher的析构函数。
     */
    ~EventDispatcher();

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    
    /**@~english
     * To help track down event listener issues in debug builds.
     * Verifies that the node has no event listeners associated with it when destroyed.
     * @~chinese 
     * 这个函数帮助在调试版本中跟踪调试事件监听器的相关问题。
     * 验证给定节点在销毁时没有事件监听器与其相关联.
     */
    void debugCheckNodeHasNoEventListenersOnDestruction(Node* node);
    
#endif

protected:
    friend class Node;
    
    /** @~english Sets the dirty flag for a node.  @~chinese 设置节点的脏标记。*/
    void setDirtyForNode(Node* node);
    
    /**@~english
     *  The vector to store event listeners with scene graph based priority and fixed priority.
     * @~chinese 
     * 该容器用来存储带有基于场景图优先级和固定优先级的事件监听器
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
    
    /** @~english Adds an event listener with item
     * @~chinese 为某一项添加一个事件监听器
     *  @note @~english if it is dispatching event, the added operation will be delayed to the end of current dispatch
     * @~chinese 如果是正在分发中的事件，添加操作会被延迟到当前分发操作的结束
     *  @see forceAddEventListener
     */
    void addEventListener(EventListener* listener);
    
    /** @~english Force adding an event listener
     * @~chinese 强制添加一个事件监听器
     *  @note @~english force add an event listener which will ignore whether it's in dispatching.
     * @~chinese 强制添加一个事件监听器，该事件无论是否在调度过程中都会忽略
     *  @see addEventListener
     */
    void forceAddEventListener(EventListener* listener);
    
    /** @~english Gets event the listener list for the event listener type.  @~chinese 获取指定监听器类型的事件监听器列表。*/
    EventListenerVector* getListeners(const EventListener::ListenerID& listenerID);
    
    /** @~english Update dirty flag  @~chinese 更新'脏标记'*/
    void updateDirtyFlagForSceneGraph();
    
    /** @~english Removes all listeners with the same event listener ID  @~chinese 移除所有使用相同事件监听器ID的监听器*/
    void removeEventListenersForListenerID(const EventListener::ListenerID& listenerID);
    
    /** @~english Sort event listener  @~chinese 事件监听器排序*/
    void sortEventListeners(const EventListener::ListenerID& listenerID);
    
    /** @~english Sorts the listeners of specified type by scene graph priority  @~chinese 通过场景图的优先级排序指定类型的监听器*/
    void sortEventListenersOfSceneGraphPriority(const EventListener::ListenerID& listenerID, Node* rootNode);
    
    /** @~english Sorts the listeners of specified type by fixed priority  @~chinese 通过固定优先级排序指定类型的监听器*/
    void sortEventListenersOfFixedPriority(const EventListener::ListenerID& listenerID);
    
    /** @~english Updates all listeners
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     * @~chinese 更新所有监听器
     * 1)在事件分发过程中移除所有已经标记为'移除'的监听器项.
     * 2)在事件分发过程中添加所有已经标记为'添加'的监听器项.
     */
    void updateListeners(Event* event);

    /** @~english Touch event needs to be processed different with other events since it needs support ALL_AT_ONCE and ONE_BY_NONE mode.  @~chinese 触摸事件的处理与其它事件不同，因为触摸事件需要支持ALL_AT_ONCE和ONE_BY_NONE模式*/
    void dispatchTouchEvent(EventTouch* event);
    
    /** @~english Associates node with event listener  @~chinese 关联节点和事件监听器*/
    void associateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** @~english Dissociates node with event listener  @~chinese 分离节点和事件监听器*/
    void dissociateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** @~english Dispatches event to listeners with a specified listener type  @~chinese 分发事件给带有指定监听器类型的监听器*/
    void dispatchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /** @~english Priority dirty flag @~chinese 带优先级的'脏标记'(dirty flag)*/
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRIORITY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRIORITY | SCENE_GRAPH_PRIORITY
    };
    
    /** @~english Sets the dirty flag for a specified listener ID  @~chinese 为一个指定的监听器ID设置一个'脏标志'(dirty flag) */
    void setDirty(const EventListener::ListenerID& listenerID, DirtyFlag flag);
    
    /** @~english Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority  @~chinese 遍历场景图获取每一个节点的绘制顺序，该函数在以场景图优先级排序的事件监听器之前被调用*/
    void visitTarget(Node* node, bool isRootNode);
    
    /** @~english Listeners map  @~chinese 监听器映射图*/
    std::unordered_map<EventListener::ListenerID, EventListenerVector*> _listenerMap;
    
    /** @~english The map of dirty flag  @~chinese 脏标志'(dirty flag)映射图*/
    std::unordered_map<EventListener::ListenerID, DirtyFlag> _priorityDirtyFlagMap;
    
    /** @~english The map of node and event listeners  @~chinese 节点和事件监听器的映射图*/
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** @~english The map of node and its event priority  @~chinese 节点映射和它的事件优先级*/
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** @~english key: Global Z Order, value: Sorted Nodes  @~chinese key: 全局Z轴次序, value: 排好序的节点*/
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;
    
    /** @~english The listeners to be added after dispatching event  @~chinese 在事件分发后需要被添加的监听器*/
    std::vector<EventListener*> _toAddedListeners;
    
    /** @~english The nodes were associated with scene graph based priority listeners  @~chinese 这些节点与基于场景图优先级的监听器相关联*/
    std::set<Node*> _dirtyNodes;
    
    /** @~english Whether the dispatcher is dispatching event  @~chinese 调度程序是否正在进行事件分发*/
    int _inDispatch;
    
    /** @~english Whether to enable dispatching event  @~chinese 是否要使分发事件可用*/
    bool _isEnabled;
    
    int _nodePriorityIndex;
    
    std::set<std::string> _internalCustomListenerIDs;
};


NS_CC_END

// end of base group
/// @}

#endif // __CC_EVENT_DISPATCHER_H__
