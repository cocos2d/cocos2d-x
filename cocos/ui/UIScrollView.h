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

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class EventFocusListener;

namespace ui {

/**
 * @enum ScrollviewEventType
 * @brief @~english Scrollview scroll event type.
 * @~chinese 滚动视图的滚动事件类型
 * @deprecated use @see `ScrollView::EventType` instead.
 */
typedef enum
{
    SCROLLVIEW_EVENT_SCROLL_TO_TOP,
    SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM,
    SCROLLVIEW_EVENT_SCROLL_TO_LEFT,
    SCROLLVIEW_EVENT_SCROLL_TO_RIGHT,
    SCROLLVIEW_EVENT_SCROLLING,
    SCROLLVIEW_EVENT_BOUNCE_TOP,
    SCROLLVIEW_EVENT_BOUNCE_BOTTOM,
    SCROLLVIEW_EVENT_BOUNCE_LEFT,
    SCROLLVIEW_EVENT_BOUNCE_RIGHT
}ScrollviewEventType;

/**
 * @~english A callback which would be called when a ScrollView is scrolling.
 * @~chinese 当滚动视图滚动时会触发的回调函数
 *@deprecated Use @see `ccScrollViewCallback` instead.
 */
typedef void (Ref::*SEL_ScrollViewEvent)(Ref*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)

/**
 * @class ScrollView
 * @brief @~english Layout container for a view hierarchy that can be scrolled by the user, allowing it to be larger than the physical display.
 * It holds a inner `Layout` container for storing child items hironzontally or vertically.
 * @~chinese 一个能够被用户触摸滚动的一个层次型布局容器视图，允许其尺寸大于屏幕显示的物理尺寸，其内部维护有一个布局用于水平的或垂直的存放子节点
 */
class CC_GUI_DLL ScrollView : public Layout
{

    DECLARE_CLASS_GUI_INFO

public:
    /**
     * @enum Direction
     * @brief @~english ScrollView scroll direction type.
     * @~chinese 滚动视图的滚动方向
     */
    enum class Direction
    {
        /**
         * @~english User can not scroll the view.
         * @~chinese 禁止滚动
         **/
        NONE,
        /**
        * @~english User can scroll the view vertically.
        * @~chinese 竖直滚动
        **/
        VERTICAL,
        /**
        * @~english User can scroll the view horizontally.
        * @~chinese 水平滚动
        **/
        HORIZONTAL,
        /**
        * @~english User can scroll the view both horizontally and vertically.
        * @~chinese 水平与竖直滚动
        **/
        BOTH
    };

    /**
     * @enum EventType
     * @brief @~english Scrollview scroll event type.
     * @~chinese 滚动视图的滚动事件
     */
    enum class EventType
    {
        SCROLL_TO_TOP,
        SCROLL_TO_BOTTOM,
        SCROLL_TO_LEFT,
        SCROLL_TO_RIGHT,
        SCROLLING,
        BOUNCE_TOP,
        BOUNCE_BOTTOM,
        BOUNCE_LEFT,
        BOUNCE_RIGHT
    };

    /**
     * @~english A callback which would be called when a ScrollView is scrolling.
     * @~chinese 在滚动视图滚动时被触发的回调函数
     */
    typedef std::function<void(Ref*, EventType)> ccScrollViewCallback;

    /**
     * @~english Default constructor
     * @~chinese 默认构造函数
     * @js ctor
     * @lua new
     */
    ScrollView();

    /**
     * @~english Default destructor
     * @~chinese 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~ScrollView();

    /**
     * @~english Create an empty ScrollView.
     * @~chinese 创建一个空的滚动视图
     * @return @~english A ScrollView instance.
     * @~chinese 被创建的滚动视图的对象
     */
    static ScrollView* create();

    /**
     * @~english Changes scroll direction of scrollview.
     * @~chinese 改变滚动视图的方向
     * @see `Direction`
     * @param dir @~english Scroll direction enum.
     * @~chinese 滚动方向的枚举
     */
    virtual void setDirection(Direction dir);

    /**
     * @~english Query scroll direction of scrollview.
     * @~chinese 获取滚动视图的滚动方向
     * @see `Direction`      @~english Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll
     * @~chinese Direction::VERTICAL意味着竖直滚动，Direction::HORIZONTAL意味着水平滚动
     * @return @~english Scrollview scroll direction.
     * @~chinese 滚动视图可滚动方向
     */
    Direction getDirection()const;

    /**
     * @~english Get inner container of scrollview.
     *
     * Inner container is a child of scrollview.
     * @~chinese 获取滚动视图的内部布局容器，该布局容器为滚动视图的子节点 
     * @return @~english Inner container pointer.
     */
    Layout* getInnerContainer()const;

    /**
     * @~english Scroll inner container to bottom boundary of scrollview.
     * @~chinese 将内部的布局容器滚动到滚动视图的底部边界
     * @param second @~english Time in seconds.
     * @~chinese 该动作所需时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 该动作进行时，滚动速度是否会衰减
     */
    void scrollToBottom(float second, bool attenuated);

    /**
     * @~english Scroll inner container to top boundary of scrollview.
     * @~chinese 将内部布局容器滚动到滚动视图的顶部边界
     * @param second @~english Time in seconds.
     * @~chinese 该动作所需的时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 该动作进行时，滚动速度是否会衰减
     */
    void scrollToTop(float second, bool attenuated);

    /**
     * @~english Scroll inner container to left boundary of scrollview.
     * @~chinese 将内部容器滚动到滚动视图的左端边界
     * @param second @~english Time in seconds.
     * @~chinese 动作执行所需时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToLeft(float second, bool attenuated);

    /**
     * @~english Scroll inner container to right boundary of scrollview.
     * @~chinese 将内部布局容器滚动到滚动视图的右端边界
     * @param second @~english Time in seconds.
     * @~chinese 动作执行所需时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToRight(float time, bool attenuated);

    /**
     * @~english Scroll inner container to top and left boundary of scrollview.
     * @~chinese 滚动内部布局容器到滚动视图的左上角
     * @param second @~english Time in seconds.
     * @~chinese 动作执行所需时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToTopLeft(float second, bool attenuated);

    /**
     * @~english Scroll inner container to top and right boundary of scrollview.
     * @~chinese 滚动内部布局容器到滚动使徒的右上角
     * @param second @~english Time in seconds.
     * @~chinese 动作所需时间，以秒计
     * @param attenuated Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToTopRight(float time, bool attenuated);

    /**
     * @~english Scroll inner container to bottom and left boundary of scrollview.
     * @~chinese 滚动内部布局容器到视图的左下角
     * @param second @~english Time in seconds.
     * @~chinese 动作执行所需时间，以秒计
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToBottomLeft(float second, bool attenuated);

    /**
     * @~english Scroll inner container to bottom and right boundary of scrollview.
     * @~chinese 滚动内部布局容器到视图的右下角
     * @param second @~english Time in seconds
     * @~chinese 动作执行所需时间
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToBottomRight(float time, bool attenuated);

    /**
     * @~english Scroll inner container to vertical percent position of scrollview.
     * @~chinese 按百分比竖直滚动内部布局容器
     * @param percent @~english A value between 0 and 100.
     * @~chinese 百分比，从0至100
     * @param second @~english Time in seconds.
     * @~chinese 动作执行时间
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToPercentVertical(float percent, float second, bool attenuated);

    /**
     * @~english Scroll inner container to horizontal percent position of scrollview.
     * @~chinese 按百分比水平滚动内部布局容器
     * @param percent @~english A value between 0 and 100.
     * @~chinese 百分比，从0至100
     * @param second @~english Time in seconds.
     * @~chinese 动作执行时间
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToPercentHorizontal(float percent, float second, bool attenuated);

    /**
     * @~english Scroll inner container to both direction percent position of scrollview.
     * @~chinese 在竖直方向和水平方向分别按一定的百分比滚动内部布局容器
     * @param percent @~english A value between 0 and 100.
     * @~chinese 百分比，x分量代表水平百分比，y分两代表竖直百分比
     * @param second @~english Time in seconds.
     * @~chinese 动作所需时间
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese 滚动速度是否发生衰减
     */
    void scrollToPercentBothDirection(const Vec2& percent, float second, bool attenuated);

    /**
     * @~english Move inner container to bottom boundary of scrollview.
     * @~chinese 将内部布局容器移至视图底端
     */
    void jumpToBottom();

    /**
     * @~english Move inner container to top boundary of scrollview.
     * @~chinese 将内部布局容器移至视图顶端
     */
    void jumpToTop();

    /**
     * @~english Move inner container to left boundary of scrollview.
     * @~chinese 将内部布局容器移至视图左端
     */
    void jumpToLeft();

    /**
     * @~english Move inner container to right boundary of scrollview.
     * @~chinese 将内部布局容器移至视图右端
     */
    void jumpToRight();

    /**
     * @~english Move inner container to top and left boundary of scrollview.
     * @~chinese 将内部布局容器移至视图的左上角
     */
    void jumpToTopLeft();

    /**
     * @~english Move inner container to top and right boundary of scrollview.
     * @~chinese 将内部布局容器移至视图的右上角
     */
    void jumpToTopRight();

    /**
     * @~english Move inner container to bottom and left boundary of scrollview.
     * @~chinese 将内部布局容器移至视图的左下角
     */
    void jumpToBottomLeft();

    /**
     * @~english Move inner container to bottom and right boundary of scrollview.
     * @~chinese 将内部布局容器移至视图的右下角
     */
    void jumpToBottomRight();

    /**
     * @~english Move inner container to vertical percent position of scrollview.
     * @~chinese 按一定的百分比竖直滚动视图内的布局容器
     * @param percent @~english A value between 0 and 100.
     * @~chinese 百分比，从0至100
     */
    void jumpToPercentVertical(float percent);

    /**
     * @~english Move inner container to horizontal percent position of scrollview.
     * @~chinese 按一定的百分比竖直滚动视图内的布局容器
     * @param percent   @~english A value between 0 and 100.
     * @~chinese 百分比，从0至100
     */
    void jumpToPercentHorizontal(float percent);

    /**
     * @~english Move inner container to both direction percent position of scrollview.
     * @~chinese 竖直方向和水平方向分别按一定的百分比滚动容器
     * @param percent  @~english  A value between 0 and 100.
     * @~chinese x分量为水平方向的百分比，y分量为竖直方向的百分比
     */
    void jumpToPercentBothDirection(const Vec2& percent);

    /**
     * @~english Change inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     * @~chinese 更改内部布局容器的尺寸大小，内部容器的尺寸必须大于或等于滚动视图的尺寸
     * @param size @~english Inner container size.
     * @~chinese 内部容器的尺寸
     */
    void setInnerContainerSize(const Size &size);

    /**
     * @~english Get inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     * @~chinese 获取内部容器的尺寸，内部容器的尺寸必须大于或等于滚动视图的尺寸
     * @return @~english The inner container size.
     * @~chinese 内部容器的尺寸
     */
	const Size& getInnerContainerSize() const;

    /**
     * @~english Add callback function which will be called  when scrollview event triggered.
     * @~chinese 添加一个回调函数，该回调函数将会在视图发生滚动时触发
     * @deprecated Use @see `addEventListener` instead.
     * @param target @~english A pointer of `Ref*` type.
     * @~english Ref* 指针
     * @param selector @~english A member function pointer with type of `SEL_ScrollViewEvent`.
     * @~chinese `SEL_ScrollViewEvent`类型的成员函数指针
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerScrollView(Ref* target, SEL_ScrollViewEvent selector);

    /**
     * @~english Add callback function which will be called  when scrollview event triggered.
     * @~chinese 添加一个回调函数，该回调函数将在滚动事件触发时被调用
     * @param callback @~english A callback function with type of `ccScrollViewCallback`.
     * @~chinese `ccScrollViewCallback` 类型的回调函数
     */
    virtual void addEventListener(const ccScrollViewCallback& callback);

    //override functions
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int localZOrder, int tag) override;
    virtual void addChild(Node* child, int localZOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleaup = true) override;
    virtual Vector<Node*>& getChildren() override;
    virtual const Vector<Node*>& getChildren() const override;
    virtual ssize_t getChildrenCount() const override;
    virtual Node * getChildByTag(int tag) const override;
    virtual Node* getChildByName(const std::string& name)const override;
    //touch event callback
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    virtual void update(float dt) override;


    /**
     * @brief @~english Toggle bounce enabled when scroll to the edge.
     * @~chinese 设置当滚动到边界时，是否内部容器发生弹回(bounce)效果
     * @param enabled @~english True if enable bounce, false otherwise.
     * @~chinese 是否发生弹回(bounce)效果
     */
    void setBounceEnabled(bool enabled);

    /**
     * @brief @~english Query bounce state.
     * @~chinese 获取弹回(bounce)状态
     * @return @~english True if bounce is enabled, false otherwise.
     * @~chinese 开启弹回时返回true，反之返回false
     */
    bool isBounceEnabled() const;

    /**
     * @brief @~english Toggle whether enable scroll inertia while scrolling.
     * @~chinese 设置是否开启滚动惯性
     * @param enabled @~english True if enable inertia, false otherwise.
     * @~chinese 设为true将开启滚动惯性，反之不开启
     */
    void setInertiaScrollEnabled(bool enabled);

    /**
     * @brief @~english Query inertia scroll state.
     * @~chinese 获取滚动视图是否开启滚动惯性
     * @return @~english True if inertia is enabled, false otherwise.
     * @~chinese 滚动惯性开启时返回true，反之返回false
     */
    bool isInertiaScrollEnabled() const;

    /**
     * @~english Set layout type for scrollview.
     * 设置滚动视图的布局类型
     * @see `Layout::Type`
     * @param type  @~english Layout type enum.
     * @~chinese 布局类型的枚举
     */
    virtual void setLayoutType(Type type) override;

    /**
     * @~english Get the layout type for scrollview.
     * @~chinese 获取滚动视图的当前布局类型
     * @see `Layout::Type`
     * @return @~english LayoutType
     * @~chinese 布局类型
     */
    virtual Type getLayoutType() const override;

    /**
     * @~english Return the "class name" of widget.
     * @~chinese 返回类型名
     */
    virtual std::string getDescription() const override;

    /**
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     *  @~english When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     * @~chinese 当一个控件是布局时，你可以调用此方法获取指定方向上下一个有焦点的控件，如果当前控件不是布局，将返回自身
     * @param direction @~english The direction to look for the next focused widget in a layout
     * @~chinese 指定方向
     * @param current  @~english The current focused widget
     * @~chinese 当前焦点的控件
     * @return @~english The next focused widget in a layout
     * @~chinese 下一个有焦点的控件
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;

    virtual void onSizeChanged() override;
    virtual void doLayout() override;

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;


    void moveChildren(float offsetX, float offsetY);
    void autoScrollChildren(float dt);
    void bounceChildren(float dt);
    void checkBounceBoundary();
    bool checkNeedBounce();
    void startAutoScrollChildrenWithOriginalSpeed(const Vec2& dir, float v, bool attenuated, float acceleration);
    void startAutoScrollChildrenWithDestination(const Vec2& des, float second, bool attenuated);
    void jumpToDestination(const Vec2& des);
    void stopAutoScrollChildren();
    void startBounceChildren(float v);
    void stopBounceChildren();
    bool checkCustomScrollDestination(float* touchOffsetX, float* touchOffsetY);

    virtual bool scrollChildren(float touchOffsetX, float touchOffsetY);

    bool scrollChildrenVertical(float touchOffsetX, float touchOffsetY);
    bool scrollChildrenHorizontal(float touchOffsetX, float touchOffestY);
    bool scrollChildrenBoth(float touchOffsetX, float touchOffsetY);


    bool bounceScrollChildren(float touchOffsetX, float touchOffsetY);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();

    //ScrollViewProtocol
    virtual void handlePressLogic(Touch *touch) ;
    virtual void handleMoveLogic(Touch *touch) ;
    virtual void handleReleaseLogic(Touch *touch) ;

    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch *touch) override;

    void recordSlidTime(float dt);

    void scrollToTopEvent();
    void scrollToBottomEvent();
    void scrollToLeftEvent();
    void scrollToRightEvent();
    void scrollingEvent();

    void bounceTopEvent();
    void bounceBottomEvent();
    void bounceLeftEvent();
    void bounceRightEvent();

protected:
    Layout* _innerContainer;

    Direction _direction;
    Vec2 _autoScrollDir;

    float _topBoundary;
    float _bottomBoundary;
    float _leftBoundary;
    float _rightBoundary;

    float _bounceTopBoundary;
    float _bounceBottomBoundary;
    float _bounceLeftBoundary;
    float _bounceRightBoundary;


    bool _autoScroll;
    float _autoScrollAddUpTime;

    float _autoScrollOriginalSpeed;
    float _autoScrollAcceleration;
    bool _isAutoScrollSpeedAttenuated;
    bool _needCheckAutoScrollDestination;
    Vec2 _autoScrollDestination;

    bool _bePressed;
    float _slidTime;
    Vec2 _moveChildPoint;
    float _childFocusCancelOffset;

    bool _leftBounceNeeded;
    bool _topBounceNeeded;
    bool _rightBounceNeeded;
    bool _bottomBounceNeeded;

    bool _bounceEnabled;
    bool _bouncing;
    Vec2 _bounceDir;
    float _bounceOriginalSpeed;
    bool _inertiaScrollEnabled;

    Ref* _scrollViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ScrollViewEvent _scrollViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccScrollViewCallback _eventCallback;
};

}
// end of ui group
/// @}
NS_CC_END
#endif /* defined(__CocoGUI__ScrollView__) */
