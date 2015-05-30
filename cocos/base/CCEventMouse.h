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

#ifndef __cocos2d_libs__CCMouseEvent__
#define __cocos2d_libs__CCMouseEvent__

#include "base/CCEvent.h"
#include "math/CCGeometry.h"

#define MOUSE_BUTTON_LEFT       0
#define MOUSE_BUTTON_RIGHT      1
#define MOUSE_BUTTON_MIDDLE     2
#define MOUSE_BUTTON_4          3
#define MOUSE_BUTTON_5          4
#define MOUSE_BUTTON_6          5
#define MOUSE_BUTTON_7          6
#define MOUSE_BUTTON_8          7

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/** @class @~english EventMouse
 * @~chinese 鼠标事件对象
 *
 * @brief @~english The mouse event.
 * @~chinese 鼠标事件
 */
class CC_DLL EventMouse : public Event
{
public:
    /**
    * @~english MouseEventType Different types of MouseEvent.
    * @~chinese 鼠标事件所支持的事件类型列表
    *
    * @js NA
    */
    enum class MouseEventType
    {
        MOUSE_NONE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_MOVE,
        MOUSE_SCROLL,
    };

    /** @~english Constructor.
     * @~chinese 构造函数
     *
     * @param mouseEventCode @~english A given mouse event type.
     * @~chinese mouseEventCode鼠标事件类型
     * @js ctor
     */
    EventMouse(MouseEventType mouseEventCode);

    /** @~english Set mouse scroll data.
     * @~chinese 设置鼠标的滚动数据
     *
     * @param scrollX @~english The scroll data of x axis.
     * @~chinese x轴滚动的数据
     * @param scrollY @~english The scroll data of y axis.
     * @~chinese y轴滚动的数据
     */
    inline void setScrollData(float scrollX, float scrollY) { _scrollX = scrollX; _scrollY = scrollY; };

    /** @~english Get mouse scroll data of x axis.
     * 
     * @~chinese 

     * @return @~english The scroll data of x axis.
     * @~chinese 
     */
    inline float getScrollX() const { return _scrollX; };
    /** @~english Get mouse scroll data of y axis.
     *
     * @~chinese 

     * @return @~english The scroll data of y axis.
     * @~chinese 
     */
    inline float getScrollY() const { return _scrollY; };

    /** @~english Set the cursor position.
     * @~chinese 设置光标位置
     *
     * @param x @~english The x coordinate of cursor position.
     * @~chinese 光标的x轴坐标
     * @param y @~english The y coordinate of cursor position.
     * @~chinese 光标的y轴坐标
     *
     * @js setLocation
     */
    inline void setCursorPosition(float x, float y) { 
        _x = x;
        _y = y;
        _prevPoint = _point;
        _point.x = x;
        _point.y = y;
        if (!_startPointCaptured)
        {
            _startPoint = _point;
            _startPointCaptured = true;
        }
    }

    /** @~english Set mouse button.
     * @~chinese 设置鼠标按钮
     *
     * @param button @~english a given mouse button.
     * @~chinese 鼠标按钮
     *
     * @js setButton
     */
    inline void setMouseButton(int button) { _mouseButton = button; };

    /** @~english Get mouse button.
     * @~chinese 获取一个鼠标按钮
     *
     * @return @~english The mouse button.
     * @~chinese 鼠标按钮
     *
     * @js getButton
     */
    inline int getMouseButton() const { return _mouseButton; };

    /** @~english Get the cursor position of x axis.
     * @~chinese 获取光标的x轴坐标
     *
     * @return @~english The x coordinate of cursor position.
     * @~chinese 光标的x轴坐标
     * @js getLocationX
     */
    inline float getCursorX() const { return _x; };

    /** @~english Get the cursor position of y axis.
     * @~chinese 获取光标的x轴坐标
     *
     * @return @~english The y coordinate of cursor position.
     * @~chinese x轴坐标
     *
     * @js getLocationY
     */
    inline float getCursorY() const { return _y; };

    /** @~english Returns the current touch location in OpenGL coordinates.
     * @~chinese 返回当前位置在OpenGL世界中的坐标
     *
     * @return @~english The current touch location in OpenGL coordinates.
     * @~chinese 当前光标在OpenGL中的坐标数据
     */
    Vec2 getLocation() const;

    /** @~english Returns the previous touch location in OpenGL coordinates.
     * @~chinese 返回事件之前的光标在OpenGL世界中的坐标
     *
     * @return @~english The previous touch location in OpenGL coordinates.
     * @~chinese 事件之前，光标在OpenGL中的坐标数据
     *
     * @js NA
     */
    Vec2 getPreviousLocation() const;

    /** @~english Returns the start touch location in OpenGL coordinates.
     * @~chinese 返回点击开始时光标在OpenGL世界中的坐标
     *
     * @return @~english The start touch location in OpenGL coordinates.
     * @~chinese 点击开始时，光标在OpenGL世界中的坐标数据
     *
     * @js NA
     */
    Vec2 getStartLocation() const;

    /** @~english Returns the delta of 2 current touches locations in screen coordinates.
     * @~chinese 返回鼠标事件开始到结束时，两个点之间在屏幕坐标空间内的向量
     *
     * @return @~english The delta of 2 current touches locations in screen coordinates.
     * @~chinese 鼠标事件开始到结束时，两个点之间在屏幕做表空间内的向量
     */
    Vec2 getDelta() const;

    /** @~english Returns the current touch location in screen coordinates.
     * @~chinese 返回当前事件在屏幕空间内的坐标位置
     *
     * @return @~english The current touch location in screen coordinates.
     * @~chinese 当前鼠标事件在屏幕内的坐标位置
     */
    Vec2 getLocationInView() const;

    /** @~english Returns the previous touch location in screen coordinates.
     * @~chinese 返回前一个点击事件在屏幕内的坐标
     *
     * @return @~english The previous touch location in screen coordinates.
     * @~chinese 前一个点击事件在屏幕内的坐标
     *
     * @js NA
     */
    Vec2 getPreviousLocationInView() const;

    /** @~english Returns the start touch location in screen coordinates.
     * @~chinese 返回开始点击时的光标在屏幕的内的坐标
     *
     * @return @~english The start touch location in screen coordinates.
     * @~chinese 开始点击时的光标在屏幕的内的坐标
     *
     * @js NA
     */
    Vec2 getStartLocationInView() const;


private:
    MouseEventType _mouseEventType;
    int _mouseButton;
    float _x;
    float _y;
    float _scrollX;
    float _scrollY;

    bool _startPointCaptured;
    Vec2 _startPoint;
    Vec2 _point;
    Vec2 _prevPoint;

    friend class EventListenerMouse;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCMouseEvent__) */
