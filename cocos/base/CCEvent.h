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

#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"


/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Node;


/** @class Event
 * @brief @~english Base class of all kinds of events.
 * @~chinese 各种各样的事件的基类。
 */
class CC_DLL Event : public Ref
{
public:

    /** @~english Type Event type. @~chinese 事件类型。*/
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

    /** @~english Constructor  @~chinese 构造函数*/
    Event(Type type);
public:

    /** @~english Destructor.
     * @~chinese 析构函数。
     */
    virtual ~Event();


    /** @~english Gets the event type.
     *
     * @~chinese 获取事件类型。
     * 
     * @return @~english The event type.
     * @~chinese 事件类型。
     */
	inline Type getType() const { return _type; };
    

    /** @~english Stops propagation for current event.
     * @~chinese 停止传播当前事件。
     */
    inline void stopPropagation() { _isStopped = true; };
    

    /** @~english Checks whether the event has been stopped.
     *
     * @~chinese 检查事件是否已经停止。
     * 
     * @return @~english True if the event has been stopped.
     * @~chinese 如果事件已经停止则返回真。
     */
    inline bool isStopped() const { return _isStopped; };
    

    /** @~english Gets current target of the event.
     * @~chinese 得到的当前目标的事件。
     * @return @~english The target with which the event associates.
     * @~chinese 与事件关联的目标。
     * @note @~english It onlys be available when the event listener is associated with node.
     *        It returns 0 when the listener is associated with fixed priority.
     * @~chinese 只有当事件侦听器与节点相关联时才有效。
     * 如果侦听器与固定优先级相关联则返回0。
     */
    inline Node* getCurrentTarget() { return _currentTarget; };
    
protected:

    /** @~english Sets current target  @~chinese Sets the current target*/
    inline void setCurrentTarget(Node* target) { _currentTarget = target; };
    
	Type _type;     ///< Event type
    
    bool _isStopped;       ///< whether the event has been stopped.
    Node* _currentTarget;  ///< Current target
    
    friend class EventDispatcher;
};

NS_CC_END

// end of base group
/// @}

#endif // __CCEVENT_H__
