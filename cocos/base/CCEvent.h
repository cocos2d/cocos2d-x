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


#ifndef __CCEVENT_H__
#define __CCEVENT_H__

#include <string>
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class Node;

/**
 *   Base class of all kinds of events.
 */
class CC_DLL Event : public Ref
{
public:
    enum class Type
    {
        TOUCH,
        KEYBOARD,
        ACCELERATION,
        MOUSE,
        FOCUS,
        GAME_CONTROLLER,
        CUSTOM
    };
    
CC_CONSTRUCTOR_ACCESS:
    /** Constructor */
    Event(Type type);
public:
    /** Destructor */
    virtual ~Event();

    /** Gets the event type */
	inline Type getType() const { return _type; };
    
    /** Stops propagation for current event */
    inline void stopPropagation() { _isStopped = true; };
    
    /** Checks whether the event has been stopped */
    inline bool isStopped() const { return _isStopped; };
    
    /** @brief Gets current target of the event
     *  @return The target with which the event associates.
     *  @note It onlys be available when the event listener is associated with node. 
     *        It returns 0 when the listener is associated with fixed priority.
     */
    inline Node* getCurrentTarget() { return _currentTarget; };
    
    std::string getResult() const { return _result; };
    void setResult(const std::string &result) { _result = result; };
protected:
    /** Sets current target */
    inline void setCurrentTarget(Node* target) { _currentTarget = target; };
    
	Type _type;     ///< Event type
    
    bool _isStopped;       ///< whether the event has been stopped.
    Node* _currentTarget;  ///< Current target
    std::string _result;   ///< Event result
    
    friend class EventDispatcher;
};

NS_CC_END


#endif // __CCEVENT_H__
