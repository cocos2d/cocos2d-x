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

#ifndef __CCEVENTLISTENER_H__
#define __CCEVENTLISTENER_H__

#include <functional>
#include <string>
#include <memory>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class Node;

/** @class EventListener
 *  @brief @~english The base class of event listener.
 *  If you need custom listener which with different callback, you need to inherit this class.
 *  For instance, you could refer to EventListenerAcceleration, EventListenerKeyboard, EventListenerTouchOneByOne, EventListenerCustom.
 * @~chinese 事件监听器的基类。
 * 如果你需要自定义有不同回调的监听器时,你需要继承这个类。
 * 例如,你可以参考EventListenerAcceleration,EventListenerKeyboard,EventListenerTouchOneByOne EventListenerCustom。
 */
class CC_DLL EventListener : public Ref
{
public:
    /** @~english Type Event type. @~chinese 事件类型。*/
    enum class Type
    {
        UNKNOWN,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        KEYBOARD,
        MOUSE,
        ACCELERATION,
        FOCUS,
		GAME_CONTROLLER,
        CUSTOM
    };

    typedef std::string ListenerID;

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Constructor
     * @~chinese 
     * 构造函数
     * @js ctor
     */
    EventListener();

    /** @~english
     * Initializes event with type and callback function
     * @~chinese 
     * 初始化事件和回调函数
     * @js NA
     */
    bool init(Type t, const ListenerID& listenerID, const std::function<void(Event*)>& callback);
public:
    /** @~english Destructor.
     * @~chinese 析构函数。
     * @js NA 
     */
    virtual ~EventListener();

    /** @~english Checks whether the listener is available.
     * 
     * @~chinese 检查是否监听器是可用的。
     * 
     * @return @~english True if the listener is available.
     * @~chinese 如果监听器是可用的,返回true。
     */
    virtual bool checkAvailable() = 0;

    /** @~english Clones the listener, its subclasses have to override this method.
     * @~chinese 克隆监听器,它的子类必须重写此方法。
     */
    virtual EventListener* clone() = 0;

    /** @~english Enables or disables the listener.
     * @~chinese 启用或禁用监听器。
     * @note @~english Only listeners with `enabled` state will be able to receive events.
     *        When an listener was initialized, it's enabled by default.
     *        An event listener can receive events when it is enabled and is not paused.
     *        paused state is always false if it is a fixed priority listener.
     *
     * @~chinese 只有监听器处于“启用”状态时才能够接收事件。
     * 当一个监听器初始化,它默认是启用的。
     * 当一个监听器处于启用状态且没被暂停，它可以收到事件。
     * 如果它是一个固定优先级的监听器,处于暂停状态的时候，这个值始终为false。
     * 
     * @param enabled @~english True if enables the listener.
     * @~chinese 如果开启监听器值为true。
     */
    inline void setEnabled(bool enabled) { _isEnabled = enabled; };

    /** @~english Checks whether the listener is enabled.
     *
     * @~chinese 检查监听器是否可用。
     * 
     * @return @~english True if the listenrt is enabled.
     * @~chinese 如果监听器可用，值为true。
     */
    inline bool isEnabled() const { return _isEnabled; };

protected:

    /** @~english Sets paused state for the listener
     *  The paused state is only used for scene graph priority listeners.
     *  `EventDispatcher::resumeAllEventListenersForTarget(node)` will set the paused state to `true`,
     *  while `EventDispatcher::pauseAllEventListenersForTarget(node)` will set it to `false`.
     * @~chinese 设置监听器的暂停状态
     * 暂停状态仅被用于场景图像优先级监听器
     * `EventDispatcher::resumeAllEventListenersForTarget(node)` 将会设置暂停状态为 `true`,
     *  然而 `EventDispatcher::pauseAllEventListenersForTarget(node)` 将会设置暂停状态为 `false`.
     *  @note @~english 1) Fixed priority listeners will never get paused. If a fixed priority doesn't want to receive events,
     *           call `setEnabled(false)` instead.
     *        2) In `Node`'s onEnter and onExit, the `paused state` of the listeners which associated with that node will be automatically updated.
     * @~chinese 1) 固定优先级的监听器不会有暂停.  如果个一个固定优先级的监听器不想接收事件,调用
     *           `setEnabled(false)` 代替.
     *           2) 在节点(`Node`)的 onEnter 和 onExit 方法中, 监听器的暂停状态  关联的节点将会自动更新.
     */
    inline void setPaused(bool paused) { _paused = paused; };

    /** @~english Checks whether the listener is paused  @~chinese 检查监听器是否被暂停*/
    inline bool isPaused() const { return _paused; };

    /** @~english Marks the listener was registered by EventDispatcher  @~chinese 标记监听器已经被加入到事件派发器(EventDispatcher)*/
    inline void setRegistered(bool registered) { _isRegistered = registered; };

    /** @~english Checks whether the listener was registered by EventDispatcher  @~chinese 检查监听器是否被注册到事件派发器(EventDispatcher)*/
    inline bool isRegistered() const { return _isRegistered; };

    /** @~english Gets the type of this listener
     * @~chinese 获取监听器(listener)的类型
     *  @note @~english It's different from `EventType`, e.g. TouchEvent has two kinds of event listeners - EventListenerOneByOne, EventListenerAllAtOnce
     * @~chinese 它不同于`EventType`, 例如. TouchEvent有两种事件监听器 - EventListenerOneByOne, EventListenerAllAtOnce
     */
    inline Type getType() const { return _type; };

    /** @~english Gets the listener ID of this listener
     *  When event is being dispatched, listener ID is used as key for searching listeners according to event type.
     * @~chinese 获取监听器的ID 
     * 当事件派发,监听器ID是用于查找符合事件类型的监听器的关键字.
     */
    inline const ListenerID& getListenerID() const { return _listenerID; };

    /** @~english Sets the fixed priority for this listener
     * @~chinese 为监听器设置固定优先级
     *  @note @~english This method is only used for `fixed priority listeners`, it needs to access a non-zero value.
     *  0 is reserved for scene graph priority listeners
     * @~chinese 此方法仅用于 `fixed priority listeners`, 它需要传人一个非零(non-zero)值.
     * 0 被保留用于场景图像监听器的优先级
     */
    inline void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; };

    /** @~english Gets the fixed priority of this listener
     * @~chinese 获取监听器的优先级
     *  @return @~english 0 if it's a scene graph priority listener, non-zero for fixed priority listener
     * @~chinese 如果是场景图像监听器则返回0,其他固定优先级的监听器返回非零(non-zero)值
     */
    inline int getFixedPriority() const { return _fixedPriority; };

    /** @~english Sets the node associated with this listener  @~chinese 设置和监听器关联的节点*/
    inline void setAssociatedNode(Node* node) { _node = node; };

    /** @~english Gets the node associated with this listener
     * @~chinese 获取和监听器关联的节点
     *  @return @~english nullptr if it's a fixed priority listener, otherwise return non-nullptr
     * @~chinese 如果是固定优先级的监听器则返回空指针(nullptr),否则返回非空指针(non-nullptr)
     */
    inline Node* getAssociatedNode() const { return _node; };

    ///////////////
    // Properties
    //////////////
    std::function<void(Event*)> _onEvent;   /// @~english Event callback function @~chinese 事件回调函数

    Type _type;                             /// @~english Event listener type @~chinese 事件监听器的类型
    ListenerID _listenerID;                 /// @~english Event listener ID @~chinese 事件监听器的ID
    bool _isRegistered;                     /// @~english Whether the listener has been added to dispatcher. @~chinese 监听器是否被加入到派发器 

    int   _fixedPriority;   // @~english The higher the number, the higher the priority, 0 is for scene graph base priority. @~chinese 数值越高，优先级越高. 0 是场景图像的基础优先级.
    Node* _node;            // @~english scene graph based priority @~chinese 事件监听器关联的节点
    bool _paused;           // @~english Whether the listener is paused @~chinese 监听器是否暂停
    bool _isEnabled;        // @~english Whether the listener is enabled @~chinese 监听器是否启用
    friend class EventDispatcher;
};

NS_CC_END

// end of base group
/// @}

#endif // __CCEVENTLISTENER_H__
