/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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
 *  @brief The base class of event listener.
 *  If you need custom listener which with different callback, you need to inherit this class.
 *  For instance, you could refer to EventListenerAcceleration, EventListenerKeyboard, EventListenerTouchOneByOne, EventListenerCustom.
 */
class CC_DLL EventListener : public Ref
{
public:
    /** Type Event type.*/
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
    /**
     * Constructor
     * @js ctor
     */
    EventListener();

    /** 
     * Initializes event with type and callback function
     * @js NA
     */
    bool init(Type t, const ListenerID& listenerID, const std::function<void(Event*)>& callback);
public:
    /** Destructor.
     * @js NA 
     */
    virtual ~EventListener();

    /** Checks whether the listener is available.
     * 
     * @return True if the listener is available.
     */
    virtual bool checkAvailable() = 0;

    /** Clones the listener, its subclasses have to override this method.
     */
    virtual EventListener* clone() = 0;

    /** Enables or disables the listener.
     * @note Only listeners with `enabled` state will be able to receive events.
     *        When an listener was initialized, it's enabled by default.
     *        An event listener can receive events when it is enabled and is not paused.
     *        paused state is always false when it is a fixed priority listener.
     *
     * @param enabled True if enables the listener.
     */
    void setEnabled(bool enabled) { _isEnabled = enabled; }

    /** Checks whether the listener is enabled.
     *
     * @return True if the listener is enabled.
     */
    bool isEnabled() const { return _isEnabled; }

protected:

    /** Sets paused state for the listener
     *  The paused state is only used for scene graph priority listeners.
     *  `EventDispatcher::resumeAllEventListenersForTarget(node)` will set the paused state to `true`,
     *  while `EventDispatcher::pauseAllEventListenersForTarget(node)` will set it to `false`.
     *  @note 1) Fixed priority listeners will never get paused. If a fixed priority doesn't want to receive events,
     *           call `setEnabled(false)` instead.
     *        2) In `Node`'s onEnter and onExit, the `paused state` of the listeners which associated with that node will be automatically updated.
     */
    void setPaused(bool paused) { _paused = paused; }

    /** Checks whether the listener is paused */
    bool isPaused() const { return _paused; }

    /** Marks the listener was registered by EventDispatcher */
    void setRegistered(bool registered) { _isRegistered = registered; }

    /** Checks whether the listener was registered by EventDispatcher */
    bool isRegistered() const { return _isRegistered; }

    /** Gets the type of this listener
     *  @note It's different from `EventType`, e.g. TouchEvent has two kinds of event listeners - EventListenerOneByOne, EventListenerAllAtOnce
     */
    Type getType() const { return _type; }

    /** Gets the listener ID of this listener
     *  When event is being dispatched, listener ID is used as key for searching listeners according to event type.
     */
    const ListenerID& getListenerID() const { return _listenerID; }

    /** Sets the fixed priority for this listener
     *  @note This method is only used for `fixed priority listeners`, it needs to access a non-zero value.
     *  0 is reserved for scene graph priority listeners
     */
    void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; }

    /** Gets the fixed priority of this listener
     *  @return 0 if it's a scene graph priority listener, non-zero for fixed priority listener
     */
    int getFixedPriority() const { return _fixedPriority; }

    /** Sets the node associated with this listener */
    void setAssociatedNode(Node* node) { _node = node; }

    /** Gets the node associated with this listener
     *  @return nullptr if it's a fixed priority listener, otherwise return non-nullptr
     */
    Node* getAssociatedNode() const { return _node; }

    ///////////////
    // Properties
    //////////////
    std::function<void(Event*)> _onEvent;   /// Event callback function

    Type _type;                             /// Event listener type
    ListenerID _listenerID;                 /// Event listener ID
    bool _isRegistered;                     /// Whether the listener has been added to dispatcher.

    int   _fixedPriority;   // The higher the number, the higher the priority, 0 is for scene graph base priority.
    Node* _node;            // scene graph based priority
    bool _paused;           // Whether the listener is paused
    bool _isEnabled;        // Whether the listener is enabled
    friend class EventDispatcher;
};

NS_CC_END

// end of base group
/// @}

#endif // __CCEVENTLISTENER_H__
