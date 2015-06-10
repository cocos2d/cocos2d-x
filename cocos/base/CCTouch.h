/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CC_TOUCH_H__
#define __CC_TOUCH_H__

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/** @class Touch
 * @brief @~english Encapsulates the Touch information, such as touch point, id and so on,
 and provides the methods that commonly used.
 * @~chinese 封装了触摸相关的信息，如触摸点，id等等。
 * 并且提供了常用的方法。
 */
class CC_DLL Touch : public Ref
{
public:
    /** @~english
     * Dispatch mode, how the touches are dispathced.
     * @~chinese 
     * 消息分发模式，定义如何分发触摸事件。
     * @js NA
     */
    enum class DispatchMode {
        ALL_AT_ONCE, /** @~english All at once. @~chinese 多点触摸。 */
        ONE_BY_ONE,  /** @~english One by one. @~chinese 单点触摸。 */
    };

    /** @~english Constructor.
     * @~chinese 构造函数。
     * @js ctor
     */
    Touch() 
        : _id(0),
        _startPointCaptured(false)
    {}

    /** @~english Returns the current touch location in OpenGL coordinates.
     *
     * @~chinese 获取当前的触摸点在 OpenGL 坐标系下的坐标。
     * 
     * @return @~english The current touch location in OpenGL coordinates.
     * @~chinese 当前的触摸点在 OpenGL 坐标系下的坐标。
     */
    Vec2 getLocation() const;
    /** @~english Returns the previous touch location in OpenGL coordinates.
     *
     * @~chinese 获取之前的触摸点在 OpenGL 坐标系下的坐标。
     * 
     * @return @~english The previous touch location in OpenGL coordinates.
     * @~chinese 之前的触摸点在 OpenGL 坐标系下的坐标。
     */
    Vec2 getPreviousLocation() const;
    /** @~english Returns the start touch location in OpenGL coordinates.
     *
     * @~chinese 获取触摸起始点在 OpenGL 坐标系下的坐标。
     * 
     * @return @~english The start touch location in OpenGL coordinates.
     * @~chinese 触摸起始点在 OpenGL 坐标系下的坐标。
     */
    Vec2 getStartLocation() const;
    /** @~english Returns the delta of 2 current touches locations in screen coordinates.
     *
     * @~chinese 获取当前两个触摸点在屏幕坐标系下的差值。
     * 
     * @return @~english The delta of 2 current touches locations in screen coordinates.
     * @~chinese 当前两个触摸点在屏幕坐标系下的差值。
     */
    Vec2 getDelta() const;
    /** @~english Returns the current touch location in screen coordinates.
     *
     * @~chinese 获取当前触摸点在屏幕坐标系下的坐标。
     * 
     * @return @~english The current touch location in screen coordinates.
     * @~chinese 当前触摸点在屏幕坐标系下的坐标。
     */
    Vec2 getLocationInView() const;
    /** @~english Returns the previous touch location in screen coordinates. 
     *
     * @~chinese 获取之前的触摸点在屏幕坐标系下的坐标。
     * 
     * @return @~english The previous touch location in screen coordinates.
     * @~chinese 之前的触摸点在屏幕坐标系下的坐标。
     */
    Vec2 getPreviousLocationInView() const;
    /** @~english Returns the start touch location in screen coordinates.
     *
     * @~chinese 获取触摸起始点在屏幕坐标系下的坐标。
     * 
     * @return @~english The start touch location in screen coordinates.
     * @~chinese 触摸起始点在屏幕坐标系下的坐标。
     */
    Vec2 getStartLocationInView() const;
    
    /** @~english Set the touch infomation. It always used to monitor touch event.
     *
     * @~chinese 设置触摸相关的信息。用于监控触摸事件。
     * 
     * @param id @~english A given id
     * @~chinese 一个给定的id
     * @param x @~english A given x coordinate.
     * @~chinese 一个给定的x坐标。
     * @param y @~english A given y coordinate.
     * @~chinese 一个给定的y坐标。
     */
    void setTouchInfo(int id, float x, float y)
    {
        _id = id;
        _prevPoint = _point;
        _point.x   = x;
        _point.y   = y;
        if (!_startPointCaptured)
        {
            _startPoint = _point;
            _startPointCaptured = true;
            _prevPoint = _point;
        }
    }
    /** @~english Get touch id.
     * @~chinese 获取触摸id。
     *
     * @return @~english The id of touch.
     * @~chinese 触摸id
     * @js getId
     * @lua getId
     */
    int getID() const
    {
        return _id;
    }

private:
    int _id;
    bool _startPointCaptured;
    Vec2 _startPoint;
    Vec2 _point;
    Vec2 _prevPoint;
};

// end of base group
/// @}

NS_CC_END

#endif  // __PLATFORM_TOUCH_H__
