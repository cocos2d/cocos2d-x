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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "2d/CCProtectedNode.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"
#include "ui/GUIExport.h"
#include "base/CCMap.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class EventListenerTouchOneByOne;


namespace ui {
    class LayoutComponent;

/**@~english
 * Touch event type.
 * @~chinese 
 * 触摸事件类型。
 *@deprecated use `Widget::TouchEventType` instead
 */
typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;
    
/**@~english
 * Touch event callback.
 * @~chinese 
 * 触摸事件回调。
 *@deprecated use `Widget::ccWidgetTouchCallback` instead
 */
typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#endif

/**
 *@brief @~english Base class for all ui widgets.
 * This class inherent from `ProtectedNode` and `LayoutParameterProtocol`.
 * If you want to implements your own ui widget, you should subclass it.
 * @~chinese 所有UI控件的基类。
 * 这类继承自`ProtectedNode`和`LayoutParameterProtocol`。
 * 如果你想实现自己的UI控件，你应该继承这个类。
 */
class CC_GUI_DLL Widget : public ProtectedNode, public LayoutParameterProtocol
{
public:
    /**@~english
     * Widget focus direction.
     * @~chinese 
     * 控件焦点方向。
     */
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    /**@~english
     * Widget position type for layout.
     * @~chinese 
     * 布局系统中的控件位置类型。
     */
    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**@~english
     * Widget size type for layout.
     * @~chinese 
     * 布局系统中的控件尺寸类型。
     */
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**@~english
     * Touch event type.
     * @~chinese 
     * 触摸事件类型。
     */
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    /**@~english
     * Texture resource type.
     * - LOCAL: It means the texture is loaded from image.
     * - PLIST: It means the texture is loaded from texture atlas.
     * @~chinese 
     * 纹理资源类型。
     * - LOCAL：这意味着纹理从独立图像加载。
     * - PLIST：这意味着纹理从纹理图集中加载。
     */
    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };
    
    /**@~english
     * Widget bright style.
     * @~chinese 
     * 控件的高亮属性。
     */
    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    
    /**@~english
     * Widget touch event callback.
     * @~chinese 
     * 控件触摸事件回调。
     */
    typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;
    /**@~english
     * Widget click event callback.
     * @~chinese 
     * 控件点击事件回调。
     */
    typedef std::function<void(Ref*)> ccWidgetClickCallback;
    /**@~english
     * Widget custom event callback.
     * It is mainly used together with Cocos Studio.
     * @~chinese 
     * 控件用户定制事件回调。
     * 它主要和Cocos Studio一起使用。
     */
    typedef std::function<void(Ref*, int)> ccWidgetEventCallback;
    /**@~english
     * Default constructor
     * @~chinese 
     * 默认构造函数
     * @js ctor
     * @lua new
     */
    Widget(void);
    
    /**@~english
     * Default destructor
     * @~chinese 
     * 默认的析构函数
     * @js NA
     * @lua NA
     */
    virtual ~Widget();
    /**@~english
     * Create and return a empty Widget instance pointer.
     * @~chinese 
     * 创建并返回一个空的控件实例的指针。
     */
    static Widget* create();

    /**@~english
     * Sets whether the widget is enabled
     * 
     * true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.
     *
     * Note: If you want to change the widget's appearance to disabled state, you should also call `setBright(false)`.
     *
     * The default value is true, a widget is default to enable touch.
     *
     * @~chinese 
     * 设置是否启用了控件
     * 
     * 如果设置为true则启用了控件，部件可以响应触摸事件，如果设置为false则控件是禁用的，不会响应触摸事件。
     * 
     * 提醒：如果你想改变一个控件的外观为不可用状态，除了`setEnabled(false)`以外，还需要调用`setBright(false)`，否则外观不会改变。
     * 
     * 默认值是true,一个控件是默认启用触摸。
     * 
     * @param enabled @~english Set to true to enable touch, false otherwise.
     * @~chinese 设置为true来启用触摸，否则不启用触摸响应。
     */
    virtual void setEnabled(bool enabled);

    /**@~english
     * Determines if the widget is enabled or not.
     *
     * @~chinese 
     * 检查控件是否启用了。
     * 
     * @return @~english true if the widget is enabled, false if the widget is disabled.
     * @~chinese 如果启用了控件返回true，控件是禁用的返回false。
     */
    bool isEnabled() const;

    /**@~english
     * Sets whether the widget is bright
     * The default value is true, a widget is default to bright
     *
     * @~chinese 
     * 设置控件是否高亮，默认值是true，若设置为false，则控件外观是暗的。
     * 
     * @param bright @~english true if the widget is bright, false if the widget is dark.
     * @~chinese 设置true则控件是高亮的，否则设置false。
     */
    void setBright(bool bright);

    /**@~english
     * Determines if the widget is bright
     *
     * @~chinese 
     * 返回控件是否高亮
     * 
     * @return @~english true if the widget is bright, false if the widget is dark.
     * @~chinese 如果控件是高亮的返回true，否则返回false。
     */
    bool isBright() const;

    /**@~english
     * Sets whether the widget is touch enabled.
     *
     * The default value is false, a widget is default to touch disabled.
     *
     * @~chinese 
     * 设置是否响应触摸事件。
     * 
     * 默认值是false，控件默认是禁用触摸的。
     * 
     * @param enabled   @~english True if the widget is touch enabled, false if the widget is touch disabled.
     * @~chinese 如果设置true则启用触摸，否则禁用。
     */
    virtual void setTouchEnabled(bool enabled);

    /**@~english
     * To set the bright style of widget.
     *
     * @~chinese 
     * 设置控件的高亮风格。
     * 
     * @see BrightStyle
     *
     * @param style   @~english BrightStyle::NORMAL means the widget is in normal state, BrightStyle::HIGHLIGHT means the widget is in highlight state.
     * @~chinese BrightStyle::NORMAL意味着部件在正常状态，BrightStyle::HIGHLIGHT意味着部件处于高亮状态。
     */
    void setBrightStyle(BrightStyle style);

    /**@~english
     * Determines if the widget is touch enabled
     *
     * @~chinese 
     * 获取触摸是否启用
     * 
     * @return @~english true if the widget is touch enabled, false if the widget is touch disabled.
     * @~chinese 如果触摸启用则返回true，否则返回false。
     */
    bool isTouchEnabled() const;

    /**@~english
     * Determines if the widget is highlighted
     *
     * @~chinese 
     * 获取是否高亮显示
     * 
     * @return @~english true if the widget is highlighted, false if the widget is not hignlighted .
     * @~chinese 如果高亮显示则返回true，否则返回false。
     */
    bool isHighlighted() const;

    /**@~english
     * Sets whether the widget is hilighted
     *
     * The default value is false, a widget is default to not hilighted
     *
     * @~chinese 
     * 设置是否高亮显示
     * 
     * 默认值是false，控件默认不高亮显示
     * 
     * @param hilight   @~english true if the widget is hilighted, false if the widget is not hilighted.
     * @~chinese 如果设置true则启用高亮。
     */
    void setHighlighted(bool hilight);

    /**@~english
     * Gets the left boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的左边界在父节点坐标系中的位置。
     * @deprecated use `getLeftBoundary` instead.
     * @return @~english The left boundary position of this widget.
     * @~chinese 这个控件的左边界在父节点坐标系中的位置。
     */
    CC_DEPRECATED_ATTRIBUTE float getLeftInParent(){return this->getLeftBoundary();}

    /**@~english
     * Gets the left boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的左边界在父节点坐标系中的位置。
     * @return @~english The left boundary position of this widget.
     * @~chinese 这个控件的左边界在父节点坐标系中的位置。
     */
    float getLeftBoundary() const;

    /**@~english
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的底边界在父节点坐标系中的位置。
     * @deprecated use `getBottomBoundary` instead.
     * @return @~english The bottom boundary position of this widget.
     * @~chinese 这个控件的底边界在父节点坐标系中的位置。
     */
    CC_DEPRECATED_ATTRIBUTE float getBottomInParent(){return this->getBottomBoundary();}
    /**@~english
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的底边界在父节点坐标系中的位置。
     * @return @~english The bottom boundary position of this widget.
     * @~chinese 这个控件的底边界在父节点坐标系中的位置。
     */
    float getBottomBoundary() const;

    /**@~english
     * Gets the right boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的右边界在父节点坐标系中的位置。
     * @deprecated use `getRightBoundary` instead.
     * @return @~english The right boundary position of this widget.
     * @~chinese 这个控件的右边界在父节点坐标系中的位置。
     */
    CC_DEPRECATED_ATTRIBUTE float getRightInParent(){return this->getRightBoundary();}
    /**@~english
     * Gets the right boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的右边界在父节点坐标系中的位置。
     * @return @~english The right boundary position of this widget.
     * @~chinese 这个控件的右边界在父节点坐标系中的位置。
     */
    float getRightBoundary() const;

    /**@~english
     * Gets the top boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的上边界在父节点坐标系中的位置。
     * @deprecated use `getTopBoundary` instead.
     * @return @~english The top boundary position of this widget.
     * @~chinese 这个控件的上边界在父节点坐标系中的位置。
     */
    CC_DEPRECATED_ATTRIBUTE float getTopInParent(){return this->getTopBoundary();}
    /**@~english
     * Gets the top boundary position of this widget in parent's coordination system.
     * @~chinese 
     * 获取这个控件的上边界在父节点坐标系中的位置。
     * @return @~english The top boundary position of this widget.
     * @~chinese 这个控件的上边界在父节点坐标系中的位置。
     */
    float getTopBoundary() const;

    virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    /**@~english
     * Sets the touch event target/selector to the widget
     * @~chinese 
     * 设置触摸事件的响应选择器和目标。
     */
    CC_DEPRECATED_ATTRIBUTE void addTouchEventListener(Ref* target,SEL_TouchEvent selector);
    /**@~english
     * Set a callback to touch vent listener.
     * @~chinese 
     * 设置触摸事件的回调函数。
     *@param callback  @~english The callback in `ccWidgetEventCallback.`
     * @~chinese 回调函数
     */
    void addTouchEventListener(const ccWidgetTouchCallback& callback);
    
    /**@~english
     * Set a click event handler to the widget.
     * @~chinese 
     * 设置一个点击事件的回调函数。
     * @param callback @~english The callback in `ccWidgetClickCallback`.
     * @~chinese 回调函数。
     */
    void addClickEventListener(const ccWidgetClickCallback& callback);
    /**@~english
     * Set a event handler to the widget in order to use cocostudio editor and framework
     * @~chinese 
     * 设置一个用于Cocos Studio事件处理的回调函数
     * @param callback @~english The callback in `ccWidgetEventCallback`.
     * @~chinese 回调函数。
     * @lua NA
     */
    virtual void addCCSEventListener(const ccWidgetEventCallback& callback);

    /**@~english
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose a Vec2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @~chinese 
     * 在OpenGL坐标系中设置控件位置(x,y)
     * 
     * 通常我们使用p(x,y)组成一个Vec2对象。
     * 原点(0,0)是屏幕的左下角。
     * 
     * @param pos  @~english The position (x,y) of the widget in OpenGL coordinates
     * @~chinese 控件在OpenGL坐标系中的位置(x,y)
     */
    virtual void setPosition(const Vec2 &pos) override;

    /**@~english
     * Set the percent(x,y) of the widget in OpenGL coordinates
     *
     * @~chinese 
     * 设置控件在OpenGL坐标系中的百分比位置(x,y)
     * 
     * @param percent  @~english The percent (x,y) of the widget in OpenGL coordinates
     * @~chinese 控件在OpenGL坐标系中的百分比位置
     */
    void setPositionPercent(const Vec2 &percent);

    /**@~english
     * Gets the percent (x,y) of the widget in OpenGL coordinates
     *
     * @~chinese 
     * 获取控件在OpenGL坐标系中的百分比位置(x,y)
     * 
     * @see setPosition(const Vec2&)
     *
     * @return @~english The percent (x,y) of the widget in OpenGL coordinates
     * @~chinese 控件在OpenGL坐标系中的百分比位置
     */
    const Vec2& getPositionPercent();

    /**@~english
     * Changes the position type of the widget
     *
     * @~chinese 
     * 设置控件的位置类型
     * 
     * @see `PositionType`
     *
     * @param type  @~english the position type of widget
     * @~chinese 位置类型
     */
    void setPositionType(PositionType type);

    /**@~english
     * Gets the position type of the widget
     *
     * @~chinese 
     * 获取控件的位置类型
     * 
     * @see `PositionType`
     *
     * @return @~english The position type of widget
     * @~chinese 位置类型
     */
    PositionType getPositionType() const;

    /**@~english
     * Sets whether the widget should be flipped horizontally or not.
     *
     * @~chinese 
     * 设置控件是否应该水平翻转。
     * 
     * @param flippedX @~english true if the widget should be flipped horizaontally, false otherwise.
     * @~chinese 设置true则控件水平翻转，否则不翻转。
     */
    virtual void setFlippedX(bool flippedX);

    /**@~english
     * Returns the flag which indicates whether the widget is flipped horizontally or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleX(-1) to flip the widget.
     *
     * @~chinese 
     * 返回控件是否水平翻转。
     * 
     * 它不仅翻转控件本身的纹理，而且还会翻转控件所有子节点的纹理。
     * 另外，翻转轴是控件的锚点控制的。
     * 内部实现上，它只是使用`setScaleX(-1)`来实现翻转。
     * 
     * @return @~english true if the widget is flipped horizaontally, false otherwise.
     * @~chinese true则控件水平翻转，否则不翻转。
     */
    virtual bool isFlippedX()const{return _flippedX;};

    /**@~english
     * Sets whether the widget should be flipped vertically or not.
     *
     * @~chinese 
     * 设置控件是否应垂直翻转。
     * 
     * @param flippedY @~english true if the widget should be flipped vertically, flase otherwise.
     * @~chinese 设置true则控件垂直翻转，否则不翻转。
     */
    virtual void setFlippedY(bool flippedY);

    /**@~english
     * Return the flag which indicates whether the widget is flipped vertically or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleY(-1) to flip the widget.
     *
     * @~chinese 
     * 返回控件是否垂直翻转。
     * 
     * 它不仅翻转控件本身的纹理，而且还会翻转控件所有子节点的纹理。
     * 另外，翻转轴是控件的锚点控制的。
     * 内部实现上，它只是使用`setScaleY(-1)`来实现翻转。
     * 
     * @return @~english true if the widget is flipped vertically, flase otherwise.
     * @~chinese true则控件垂直翻转，否则不翻转。
     */
    virtual bool isFlippedY()const{return _flippedY;};

    /** @deprecated Use isFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated Use isFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    //override the setScale function of Node
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scale) override;
    virtual void setScale(float scalex, float scaley) override;
    using Node::setScaleZ;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;
    virtual float getScale() const override;
    using Node::getScaleZ;
    
    /**@~english
     * Checks a point if in parent's area.
     * @~chinese 
     * 检查一个位置点是否在父节点区域内。
     * 
     * @deprecated  use `isClippingParentContainsPoint` instead.
     * @param pt @~english A point in `Vec2`.
     * @~chinese Vec2类型的位置点。
     * @return @~english true if the point is in parent's area, flase otherwise.
     * @~chinese 如果点是在父节点区域内，返回true，否则返回false。
     */
    CC_DEPRECATED_ATTRIBUTE bool clippingParentAreaContainPoint(const Vec2 &pt){return this->isClippingParentContainsPoint(pt);}

    /**@~english
     * Checks a point if in parent's area.
     * @~chinese 
     * 检查一个位置点是否在父节点区域内。
     * 
     * @param pt @~english A point in `Vec2`.
     * @~chinese Vec2类型的位置点。
     * @return @~english true if the point is in parent's area, flase otherwise.
     * @~chinese 如果点是在父节点区域内，返回true，否则返回false。
     */
    bool isClippingParentContainsPoint(const Vec2& pt);

    /**@~english
     * Gets the touch began point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的起始位置。
     * @deprecated use `getTouchBeganPosition` instead.
     * @return @~english the touch began point.
     * @~chinese 触点的起始位置。
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchStartPos()const{return this->getTouchBeganPosition();}
    /**@~english
     * Gets the touch began point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的起始位置。
     * @return @~english the touch began point.
     * @~chinese 触点的起始位置。
     */
    const Vec2& getTouchBeganPosition()const;

    /*@~english
     * Gets the touch move point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的当前移动位置。
     * @deprecated use `getTouchMovePosition` instead.
     * @return @~english the touch move point.
     * @~chinese 触点的当前移动位置。
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchMovePos()const{ return this->getTouchMovePosition();}
    /*@~english
     * Gets the touch move point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的当前移动位置。
     * @return @~english the touch move point.
     * @~chinese 触点的当前移动位置。
     */
    const Vec2& getTouchMovePosition()const;

    /*@~english
     * Gets the touch end point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的终点位置。
     * @deprecated use `getTouchEndPosition` instead.
     * @return @~english the touch end point.
     * @~chinese 触点的终点位置。
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchEndPos()const{return this->getTouchEndPosition();}
    /*@~english
     * Gets the touch end point of widget when widget is selected.
     * @~chinese 
     * 获取触点在控件被选中时的终点位置。
     * @return @~english the touch end point.
     * @~chinese 触点的终点位置。
     */
    const Vec2& getTouchEndPosition()const;

    /**@~english
     * Changes the widget's size
     * @~chinese 
     * 设置控件的尺寸
     * @deprecated use `setContentSize` instead.
     * @param size @~english Widget's size
     * @~chinese 控件的尺寸
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSize(const Size &size);
    /**@~english
     * Changes the widget's size
     * @~chinese 
     * 设置控件的尺寸
     * @param contentSize @~english Widget's size
     * @~chinese 控件的尺寸
     */
    virtual void setContentSize(const Size& contentSize) override;

    /**@~english
     * Changes the widget's size in percentage
     * @~chinese 
     * 设置控件的百分比尺寸
     * 
     * @param percent @~english Widget's size in percentage
     * @~chinese 控件的百分比尺寸
     */
    virtual void setSizePercent(const Vec2 &percent);

    /**@~english
     * Changes the size type of widget.
     * @~chinese 
     * 改变控件的尺寸类型。
     * 
     * @see `SizeType`
     *
     * @param type @~english Widget's size type
     * @~chinese 控件的尺寸类型。
     */
    void setSizeType(SizeType type);

    /**@~english
     * Gets the size type of widget.
     * @~chinese 
     * 获取控件的尺寸类型。
     * 
     * @see `SizeType`
     *
     * @return @~english Widget's size type
     * @~chinese 控件的尺寸类型。
     */
    SizeType getSizeType() const;

    /**@~english
     * Get the size of widget
     * @~chinese 
     * 获取控件的尺寸
     * 
     * @return @~english Widget content size.
     * @~chinese 控件内容尺寸。
     */
    CC_DEPRECATED_ATTRIBUTE const Size& getSize() const;
    
    /**@~english
     * Get the user defined widget size.
     * @~chinese 
     * 获取用户定义的控件尺寸。
     *@return @~english User defined size.
     * @~chinese 用户定义的尺寸。
     */
    const Size& getCustomSize() const;
    
    /**@~english
     * Get the content size of widget.
     * @~chinese 
     * 获取控件尺寸。
     * @warning @~english This API exists mainly for keeping back compatibility.
     * @~chinese 这个API的存在主要用于保持兼容性。
     * @return  @~english User defined size.
     * @~chinese 用户定义的尺寸。
     */
    virtual const Size& getLayoutSize() {return _contentSize;};

    /**@~english
     * Get size percent of widget.
     * @~chinese 
     * 获取控件的百分比尺寸。
     * 
     * @return @~english Percent size.
     * @~chinese 控件的百分比尺寸。
     */
    const Vec2& getSizePercent();

    /**@~english
     * Checks a point is in widget's content space.
     * This function is used for determining touch area of widget.
     * @~chinese 
     * 检查一个点是否在控件的内容空间里。
     * 这个函数是用于检测控件的触摸响应区域。
     * 
     * @param pt @~english The point in `Vec2`.
     * @~chinese Vec2类型的点。
     * @return @~english true if the point is in widget's content space, flase otherwise.
     * @~chinese 如果点在控件的内容空间内返回true，否则返回false。
     */
    virtual bool hitTest(const Vec2 &pt);

    /**@~english
     * A callback which will be called when touch began event is issued.
     * @~chinese 
     * 触摸事件开始时的回调函数。
     *@param touch @~english The touch info.
     * @~chinese 触点信息。
     *@param unusedEvent @~english The touch event info.
     * @~chinese 触摸事件信息。
     *@return @~english True if user want to handle touches, false otherwise.
     * @~chinese 如果需要响应这个触摸事件则返回true，否则返回false。
     */
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch moved event is issued.
     * @~chinese 
     * 触摸事件中触点移动时的回调函数。
     *@param touch @~english The touch info.
     * @~chinese 触点信息。
     *@param unusedEvent @~english The touch event info.
     * @~chinese 触摸事件信息。
     */
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch ended event is issued.
     * @~chinese 
     * 触摸事件结束时的回调函数。
     *@param touch @~english The touch info.
     * @~chinese 触点信息。
     *@param unusedEvent @~english The touch event info.
     * @~chinese 触摸事件信息。
     */
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch cancelled event is issued.
     * @~chinese 
     * 触摸事件取消时的回调函数。
     *@param touch @~english The touch info.
     * @~chinese 触点信息。
     *@param unusedEvent @~english The touch event info.
     * @~chinese 触摸事件信息。
     */
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    /**@~english
     * Sets a LayoutParameter to widget.
     * @~chinese 
     * 給控件设置一个布局参数（LayoutParameter）。
     * 
     * @see LayoutParameter
     * @param parameter @~english LayoutParameter pointer
     * @~chinese 布局参数对象指针
     */
    void setLayoutParameter(LayoutParameter* parameter);

    /**@~english
     * Gets LayoutParameter of widget.
     * @~chinese 
     * 获取控件的布局参数（LayoutParameter）。
     * 
     * @see LayoutParameter
     * @return @~english LayoutParameter
     * @~chinese 布局参数对象指针
     */
    LayoutParameter* getLayoutParameter()const override;
    /**@~english
     * Gets LayoutParameter of widget.
     * @~chinese 
     * 根据类型获取控件的布局参数（LayoutParameter）。
     * 
     * @see LayoutParameter
     * @deprecated use `getLayoutParameter()` instead.
     * @param type  @~english Relative or Linear
     * @~chinese 布局参数类型，相对或线性
     * @return @~english LayoutParameter
     * @~chinese 布局参数对象指针
     */
    CC_DEPRECATED_ATTRIBUTE LayoutParameter* getLayoutParameter(LayoutParameter::Type type);


    /**@~english
     * Toggle whether ignore user defined content size for widget.
     * Set true will ignore user defined content size which means 
     * the widget size is always equal to the return value of `getVirtualRendererSize`.
     * @~chinese 
     * 设置是否忽略用户定义通过`setContentSize`设定的控件尺寸。
     * 设置为true将忽略用户定义的尺寸，意味着控件尺寸永远等于`getVirtualRendererSize`的返回值。
     * 
     * @param ignore @~english Set member variabl _ignoreSize to ignore
     * @~chinese 是否忽略控件尺寸，将设置`_ignoreSize`属性。
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**@~english
     * Query whether the widget ignores user deinfed content size or not
     * @~chinese 
     * 查询是否忽略用户定义的控件尺寸。
     * 
     * @return @~english True means ignore user defined content size, false otherwise.
     * @~chinese 返回true意味着忽略用户定义的尺寸，否则返回false。
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**@~english
     * Gets position of widget in world space.
     * @~chinese 
     * 获取在世界空间中控件的位置。
     * 
     * @return @~english Position of widget in world space.
     * @~chinese 世界空间中控件的位置。
     */
    Vec2 getWorldPosition()const;

    /**@~english
     * Gets the inner Renderer node of widget.
     * For example, a button's Virtual Renderer is its texture renderer.
     * @~chinese 
     * 控件的内部渲染节点。
     * 例如，一个按钮的虚拟渲染节点是它的纹理节点。
     * 
     * @return @~english Node pointer.
     * @~chinese 纹理节点的指针。
     */
    virtual Node* getVirtualRenderer();


    /**@~english
     * Get the virtual renderer's size
     * @~chinese 
     * 获取虚拟渲染节点的尺寸
     * @return @~english Widget virtual renderer size.
     * @~chinese 虚拟渲染节点的尺寸。
     */
    virtual Size getVirtualRendererSize() const;
    

    /**@~english
     * Returns the string representation of widget class name
     * @~chinese 
     * 返回控件类的描述
     * @return @~english get the class description.
     * @~chinese 控件类的描述。
     */
    virtual std::string getDescription() const override;

    /**@~english
     * Create a new widget copy of the original one.
     * @~chinese 
     * 创建一个新的控件拷贝。
     * @return @~english A cloned widget copy of original.
     * @~chinese 一个克隆的控件。
     */
    Widget* clone();

    virtual void onEnter() override;

    virtual void onExit() override;

    /**@~english
     * Update all children's contents size and position recursively.
     * @~chinese 
     * 递归地更新所有子节点的尺寸和位置。
     * @see `updateSizeAndPosition(const Size&)`
     */
    void updateSizeAndPosition();

    /**@~english
     * Update all children's contents size and position recursively.
     * @~chinese 
     * 递归地更新所有子节点的尺寸和位置。
     */
    void updateSizeAndPosition(const Size& parentSize);
    
    /**@~english
     * Set the tag of action.
     * @~chinese 
     * 设置动作的标签。
     * @param tag  @~english A integer tag value.
     * @~chinese 一个整数标签值。
     */
    void setActionTag(int tag);

    /**@~english
     * Get the action tag.
     * @~chinese 
     * 获取动作标签。
     *@return @~english Action tag.
     * @~chinese 动作标签。
     */
    int getActionTag()const;
    
    /**
     * @brief @~english Allow widget touch events to propagate to its parents. Set false will disable propagation
     * @~chinese 允许控件的触摸事件向上传播到父节点，设置为false会阻止向上传播。
     * @param isPropagate  @~english True to allow propagation, false otherwise.
     * @~chinese true允许向上传播，false不允许。
     * @since v3.3
     */
    void setPropagateTouchEvents(bool isPropagate);
    
    /**@~english
     * Return whether the widget is propagate touch events to its parents or not
     * @~chinese 
     * 返回控件是否允许触摸事件传播到其父节点
     * @return @~english whether touch event propagation is allowed or not.
     * @~chinese Been touch event propagation charges or not.
     * @since v3.3
     */
    bool isPropagateTouchEvents()const;
    
    /**@~english
     * Toggle widget to swallow touches or not.
     * @~chinese 
     * 设置控件是否吞噬触摸事件。
     * @param swallow @~english True to swallow touch, false otherwise.
     * @~chinese true则吞噬触摸事件，false不吞噬。
     * @since v3.3
     */
    void setSwallowTouches(bool swallow);
    
    /**@~english
     * Return whether the widget is swallowing touch or not
     * @~chinese 
     * 查询控件是否吞噬触摸事件
     * @return @~english Whether touch is swallowed.
     * @~chinese 是否吞噬触摸事件。
     * @since v3.3
     */
    bool isSwallowTouches()const;
    
    /**@~english
     * Query whether widget is focused or not.
     * @~chinese 
     * 查询控件是否拥有焦点。
     * @return @~english  whether the widget is focused or not
     * @~chinese 是否拥有焦点
     */
    bool isFocused()const;
    
    /**@~english
     * Toggle widget focus status.
     * @~chinese 
     * 切换控件是否拥有焦点。
     * @param focus  @~english pass true to let the widget get focus or pass false to let the widget lose focus
     * @~chinese 传true使控件获得焦点，否则让控件失去焦点
     */
    void setFocused(bool focus);
    
    /**@~english
     * Query widget's focus enable state.
     * @~chinese 
     * 查询控件是否拥有焦点。
     * @return @~english true represent the widget could accept focus, false represent the widget couldn't accept focus
     * @~chinese 返回true代表控件拥有焦点，反之返回false。
     */
    bool isFocusEnabled()const;
    
    /**@~english
     * Allow widget to accept focus.
     * @~chinese 
     * 允许控件接受焦点。
     * @param enable @~english pass true/false to enable/disable the focus ability of a widget
     * @~chinese 通过传递true/false来启用或禁用一个控件获取焦点
     */
    void setFocusEnabled(bool enable);
    
    /**@~english
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. 
     *  If the widget is not in a layout, it will return itself
     * @~chinese 
     * 当一个控件在一个布局中，您可以调用这个方法得到在指定的方向上的下一个控件，方向分为上下左右。
     * 如果控件没有在布局中，它将返回自身
     *@param direction @~english the direction to look for the next focused widget in a layout
     * @~chinese 指定的方向
     *@param current  @~english the current focused widget
     * @~chinese 当前拥有焦点的控件
     *@return @~english the next focused widget in a layout
     * @~chinese 布局中下一个获取焦点的控件
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    
    /**@~english
     * when a widget calls this method, it will get focus immediately.
     * @~chinese 
     * 当调用这个方法时，控件会立即拥有焦点。
     */
    void requestFocus();

    /**@~english
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on, it will return you the exact one focused widget.
     * @~chinese 
     * 获取当前拥有焦点的控件。
     * 不管对什么控件对象调用这个方法，它将返回当前拥有焦点的控件。
     * @param isWidget  @~english Unused parameter
     * @~chinese 无用的参数
     * @deprecated use `getCurrentFocusedWidget` instead.
     */
    CC_DEPRECATED_ATTRIBUTE Widget* getCurrentFocusedWidget(bool isWidget){
        CC_UNUSED_PARAM(isWidget);
        return getCurrentFocusedWidget();
    }

    /**@~english
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on, it will return you the exact one focused widget.
     * @~chinese 
     * 获取当前拥有焦点的控件。
     * 不管对什么控件对象调用这个方法，它将返回当前拥有焦点的控件。
     */
    Widget* getCurrentFocusedWidget()const;

    /*@~english
     * Enable or disable the Android Dpad focus navigation feature
     * @~chinese 
     * 开启或关闭Android系统的Dpad焦点导航功能
     * @param enable  @~english set true to enable dpad focus navigation, otherwise disenable dpad focus navigation
     * @~chinese 设置为true开启Android系统的Dpad焦点导航功能，否则关闭
     */
    static void enableDpadNavigation(bool enable);

    /**@~english
     * When a widget lose/get focus, this method will be called. Be Caution when you provide your own version of focus system, 
     * you must call widget->setFocused(true/false) to change the focus state of the current focused widget;
     * @~chinese 
     * 当一个控件失去或者获得焦点，这个回调函数将被调用。当你提供自己的版本的焦点系统时，
     * 请注意一定要调用widget->setFocused(true/false)来改变控件的焦点状态;
     */
    std::function<void(Widget*,Widget*)> onFocusChanged;

    /**@~english
     * Use this function to manually specify the next focused widget regards to each direction
     * @~chinese 
     * 实现这个函数来手动指定各个方向上的下一个焦点控件
     */
    std::function<Widget*(FocusDirection)> onNextFocusedWidget;
    
    /**@~english
     * Toggle use unify size.
     * @~chinese 
     * 设置是否使用归一化的尺寸。
     * @param enable @~english True to use unify size, false otherwise.
     * @~chinese 传递true则使用归一化尺寸，否则不使用。
     */
    void setUnifySizeEnabled(bool enable);

    /**@~english
     * Query whether unify size enable state. 
     * @~chinese 
     * 查询是否使用归一化的尺寸。
     * @return @~english true represent the widget use Unify Size, false represent the widget couldn't use Unify Size
     * @~chinese true则使用归一化尺寸，否则不使用。
     */
    bool isUnifySizeEnabled()const;

    /**@~english
     * Set callback name.
     * @~chinese 
     * 设置回调函数的名称。
     * @param callbackName @~english A string representation of callback name.
     * @~chinese 回调函数的名称。
     */
    void setCallbackName(const std::string& callbackName) { _callbackName = callbackName; }


    /**@~english
     * Query callback name.
     * @~chinese 
     * 查询回调函数的名称。
     * @return @~english The callback name.
     * @~chinese 回调函数的名称。
     */
    const std::string& getCallbackName() const{ return _callbackName; }
    
    /**@~english
     * Set callback type.
     * @~chinese 
     * 设置回调函数类型。
     * @param callbackType @~english A string representation of callback type.
     * @~chinese 回调函数的类型。
     */
    void setCallbackType(const std::string& callbackType) { _callbackType = callbackType; }

    /**@~english
     * Query callback type.
     * @~chinese 
     * 查询回调函数类型。
     * @return @~english Callback type string.
     * @~chinese 回调函数的类型。
     */
    const std::string& getCallbackType() const{ return _callbackType; }

    /**@~english
     * Toggle layout component enable.
     * @~chinese 
     * 设置是否启用布局组件。
     * @param enable @~english Enable layout Component or not
     * @~chinese 是否启用布局组件。
     */
    void setLayoutComponentEnabled(bool enable);

    /**@~english
     * Query whether layout component is enabled or not. 
     * @~chinese 
     * 查询是否启用布局组件。
     * @return @~english true represent the widget use Layout Component, false represent the widget couldn't use Layout Component.
     * @~chinese 返回true代表使用布局组件，否则不使用。
     */
    bool isLayoutComponentEnabled()const;

CC_CONSTRUCTOR_ACCESS:

    //initializes state of widget.
    virtual bool init() override;

    /*
     * @brief @~english Sends the touch event to widget's parent, if a widget wants to handle touch event under another widget, 
     *        it must overide this function.
     * @~chinese 将触摸事件发送给控件的节点，如果一个控件想处理触摸事件则必须重载这个函数，
     * @param  event  @~english the touch event type, it could be BEGAN/MOVED/CANCELED/ENDED
     * @~chinese 触摸事件类型，可能的值是：BEGAN/MOVED/CANCELED/ENDED
     * @param @~english parent
     * @~chinese 父节点
     * @param @~english point
     * @~chinese 触点
     */
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    /**
     *@brief @~english Propagate touch events to its parents
     * @~chinese 向上传播触摸事件到其父节点
     */
    void propagateTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    friend class PageView;
    /**@~english
     * This method is called when a focus change event happens
     * @~chinese 
     * 焦点更改事件发生时会调用此方法
     * @param widgetLostFocus  @~english The widget which lose its focus
     * @~chinese 失去焦点的控件
     * @param widgetGetFocus  @~english The widget which get its focus
     * @~chinese 获得焦点的控件
     */
    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    /**@~english
     * Dispatch a EventFocus through a EventDispatcher
     * @~chinese 
     * 通过EventDispatcher分发焦点更改事件
     * @param widgetLoseFocus  @~english The widget which lose its focus
     * @~chinese 失去焦点的控件
     * @param widgetGetFocus  @~english The widget which get its focus
     * @~chinese 获得焦点的控件
     */
    void dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);
    
protected:
    /**@~english
     * Get GLProgramState under normal state 
     * @~chinese 
     * 获取正常状态下的GLProgramState
     * @since v3.4
     */
    GLProgramState* getNormalGLProgramState()const;
    
    /**@~english
     * Get GLProgramState under disabled state 
     * @~chinese 
     * 获取禁用状态下的GLProgramState
     * @since v3.4
     */
    GLProgramState* getGrayGLProgramState()const;
     
    
    //call back function called when size changed.
    virtual void onSizeChanged();

    //initializes renderer of widget.
    virtual void initRenderer();

    //call back function called widget's state changed to normal.
    virtual void onPressStateChangedToNormal();
    //call back function called widget's state changed to selected.
    virtual void onPressStateChangedToPressed();
    //call back function called widget's state changed to dark.
    virtual void onPressStateChangedToDisabled();

    void pushDownEvent();
    void moveEvent();

    virtual void releaseUpEvent();
    virtual void cancelUpEvent();

    
    virtual void adaptRenderers(){};
    void updateChildrenDisplayedRGBA();
    
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const Size& size);
    
    bool isAncestorsEnabled();
    Widget* getAncensterWidget(Node* node);
    bool isAncestorsVisible(Node* node);

    void cleanupWidget();
    LayoutComponent* getOrCreateLayoutComponent();

protected:
    bool _usingLayoutComponent;
    bool _unifySize;
    bool _enabled;
    bool _bright;
    bool _touchEnabled;
    bool _highlight;
    bool _affectByClipping;
    bool _ignoreSize;
    bool _propagateTouchEvents;

    BrightStyle _brightStyle;
    SizeType _sizeType;
    PositionType _positionType;

    //used for search widget by action tag in UIHelper class
    int _actionTag;

    Size _customSize;

    Vec2 _sizePercent;
    Vec2 _positionPercent;

    bool _hitted;
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    Vec2 _touchMovePosition;
    Vec2 _touchEndPosition;

    bool _flippedX;
    bool _flippedY;

    //use map to enble switch back and forth for user layout parameters
    Map<int,LayoutParameter*> _layoutParameterDictionary;
    LayoutParameter::Type _layoutParameterType;

    bool _focused;
    bool _focusEnabled;

    static Widget *_focusedWidget;  //both layout & widget will be stored in this variable

    Ref*       _touchEventListener;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (push)
    #pragma warning (disable: 4996)
    #endif
    SEL_TouchEvent    _touchEventSelector;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic warning "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (pop)
    #endif
    ccWidgetTouchCallback _touchEventCallback;
    ccWidgetClickCallback _clickEventListener;
    ccWidgetEventCallback _ccEventCallback;
    
    std::string _callbackType;
    std::string _callbackName;
private:
    class FocusNavigationController;
    static FocusNavigationController* _focusNavigationController;
};
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__Widget__) */
