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

#ifndef __cocos2d_libs__TouchEvent__
#define __cocos2d_libs__TouchEvent__

#include "base/CCEvent.h"
#include <vector>

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Touch;

#define TOUCH_PERF_DEBUG 1

/** @class @~english EventTouch
 * @~chinese 触摸事件对象
 * @brief @~english Touch event.
 * @~chinese 触摸事件
 */
class CC_DLL EventTouch : public Event
{
public:
    static const int MAX_TOUCHES = 15;
    
    /** @~english EventCode Touch event code. @~chinese 触摸事件对应的类型列表 */

    enum class EventCode
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };

    /** @~english Constructor.
     * @~chinese 构造函数
     *
     * @js NA
     */
    EventTouch();

    /** @~english Get event code.
     * @~chinese 获取事件类型
     *
     * @return @~english The code of the event.
     * @~chinese 当前触摸事件所对应的事件代码
     */
    inline EventCode getEventCode() const { return _eventCode; };
    
    /** @~english Get the touches.
     * @~chinese 获取触摸点的列表

     * @return @~english The touches of the event.
     * @~chinese 获取当前触摸屏幕所有点的列表
     */
    inline const std::vector<Touch*>& getTouches() const { return _touches; };

#if TOUCH_PERF_DEBUG
    /** @~english Set the event code.
     * @~chinese 设置事件类型代码

     * @param eventCode @~english A given EventCode.
     * @~chinese 触摸事件所对应的事件类型
     */
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };

    /** @~english Set the touches
     * @~chinese 设置触摸列表
     *
     * @param touches @~english A given touches vector.
     * @~chinese 一个触摸列表
     */
    void setTouches(const std::vector<Touch*>& touches) { _touches = touches; };
#endif
    
private:
    EventCode _eventCode;
    std::vector<Touch*> _touches;

    friend class GLView;
};


NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__TouchEvent__) */
