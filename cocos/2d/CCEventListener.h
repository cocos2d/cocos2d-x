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
#include "CCObject.h"

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
class EventListener : public Object
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
    bool init(Type t, ListenerID listenerID, std::function<void(Event*)>callback);
public:
    /** Destructor */
    virtual ~EventListener();
    
    /** Checks whether the listener is available. */
    virtual bool checkAvailable() = 0;
    
    /** Clones the listener, its subclasses have to override this method. */
    virtual EventListener* clone() = 0;
    
protected:
    inline void setPaused(bool paused) { _paused = paused; };
    inline bool isPaused() const { return _paused; };
    
    inline void setRegistered(bool registered) { _isRegistered = registered; };
    inline bool isRegistered() const { return _isRegistered; };
    
    inline Type getType() const { return _type; };
    inline const ListenerID& getListenerID() const { return _listenerID; };
    
    inline void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; };
    inline int getFixedPriority() const { return _fixedPriority; };
    
    inline void setSceneGraphPriority(Node* node) { _node = node; };
    inline Node* getSceneGraphPriority() const { return _node; };
    
    std::function<void(Event*)> _onEvent;   /// Event callback function
    
    Type _type;                             /// Event listener type
    ListenerID _listenerID;                         /// Event listener ID
    bool _isRegistered;                     /// Whether the listener has been added to dispatcher.
    
    // The priority of event listener
    int   _fixedPriority;   // The higher the number, the higher the priority, 0 is for scene graph base priority.
    Node* _node;            // scene graph based priority
    bool _paused;           // Whether the listener is paused
    
    friend class EventDispatcher;
};

NS_CC_END

#endif
