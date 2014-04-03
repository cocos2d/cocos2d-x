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

#ifndef cocos2d_libs_EventListener_h
#define cocos2d_libs_EventListener_h

#include "CCPlatformMacros.h"
#include "CCRef.h"

#include <functional>
#include <string>
#include <memory>
#include <set>

NS_CC_BEGIN

class Event;
class Node;

/**
 *  The base class of event listener.
 *  If you need custom listener which with different callback, you need to inherit this class.
 *  For instance, you could refer to EventListenerAcceleration, EventListenerKeyboard, EventListenerTouchOneByOne, EventListenerCustom.
 */
class EventListener : public Ref
{
public:
    enum class Type
    {
        UNKNOWN,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        KEYBOARD,
        MOUSE,
        ACCELERATION,
        CUSTOM
    };
    
    typedef std::string ListenerID;
    
protected:
    /** Constructor */
    EventListener();
    
    /** Initializes event with type and callback function */
    bool init(Type t, const ListenerID& listenerID, const std::function<void(Event*)>& callback);
public:
    /** Destructor */
    virtual ~EventListener();
    
    /** Checks whether the listener is available. */
    virtual bool checkAvailable() = 0;
    
    /** Clones the listener, its subclasses have to override this method. */
    virtual EventListener* clone() = 0;

    /** Enables or disables the listener
     *  @note Only listeners with `enabled` state will be able to receive events.
     *        When an listener was initialized, it's enabled by default.
     *        For a `scene graph priority` listener, to receive an event, excepting it was `enabled`,
     *        it also shouldn't be in `pause` state.
     */
    inline void setEnabled(bool enabled) { _isEnabled = enabled; };

    /** Checks whether the listener is enabled */
    inline bool isEnabled() const { return _isEnabled; };

protected:

    /** Sets pause state for the listener
     *  The paused state is only used for scene graph priority listeners.
     *  `EventDispatcher::resumeAllEventListenersForTarget(node)` will set the paused state to `true`,
     *  while `EventDispatcher::pauseAllEventListenersForTarget(node)` will set it to `false`.
     *  @note Fixed priority listeners will never get paused. If a fixed priority doesn't want to receive events,
     *        call `setEnabled(false)` instead.
     */
    inline void setPaused(bool paused) { _paused = paused; };

    /** Checks whether the listener is paused */
    inline bool isPaused() const { return _paused; };

    /** Marks the listener was registered by EventDispatcher */
    inline void setRegistered(bool registered) { _isRegistered = registered; };

    /** Checks whether the listener was registered by EventDispatcher */
    inline bool isRegistered() const { return _isRegistered; };

    /** Gets the type of this listener
     *  @note It's different from `EventType`, e.g. TouchEvent has two kinds of event listeners - EventListenerOneByOne, EventListenerAllAtOnce
     */
    inline Type getType() const { return _type; };

    /** Gets the listener ID of this listener
     *  When event is being dispatched, listener ID is used as key for searching listeners according to event type.
     */
    inline const ListenerID& getListenerID() const { return _listenerID; };

    /** Sets the fixed priority for this listener
     *  @note This method is only used for `fixed priority listeners`, it needs to access a non-zero value.
     *  0 is reserved for scene graph priority listeners
     */
    inline void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; };

    /** Gets the fixed priority of this listener
     *  @return 0 if it's a scene graph priority listener, non-zero for fixed priority listener
     */
    inline int getFixedPriority() const { return _fixedPriority; };

    /** Sets scene graph priority for this listener */
    inline void setSceneGraphPriority(Node* node) { _node = node; };

    /** Gets scene graph priority of this listener
     *  @return nullptr if it's a fixed priority listener, non-nullptr for scene graph priority listener
     */
    inline Node* getSceneGraphPriority() const { return _node; };

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

#endif
