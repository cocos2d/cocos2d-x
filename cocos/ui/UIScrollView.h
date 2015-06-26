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
 *Scrollview scroll event type.
 *@deprecated use @see `ScrollView::EventType` instead.
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
 * A callback which would be called when a ScrollView is scrolling.
 *@deprecated Use @see `ccScrollViewCallback` instead.
 */
typedef void (Ref::*SEL_ScrollViewEvent)(Ref*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)

/**
 * Layout container for a view hierarchy that can be scrolled by the user, allowing it to be larger than the physical display.
 * It holds a inner `Layout` container for storing child items hironzontally or vertically.
 */
class CC_GUI_DLL ScrollView : public Layout
{

    DECLARE_CLASS_GUI_INFO

public:
    /**
     * ScrollView scroll direction type.
     */
    enum class Direction
    {
        NONE,
        VERTICAL,
        HORIZONTAL,
        BOTH
    };

    /**
     * Scrollview scroll event type.
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
     * A callback which would be called when a ScrollView is scrolling.
     */
    typedef std::function<void(Ref*, EventType)> ccScrollViewCallback;

    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ScrollView();

    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~ScrollView();

    /**
     * Create an empty ScrollView.
     * @return A ScrollView instance.
     */
    static ScrollView* create();

    /**
     * Changes scroll direction of scrollview.
     *
     * @see `Direction`
     * @param dir Scroll direction enum.
     */
    virtual void setDirection(Direction dir);

    /**
     * Query scroll direction of scrollview.
     *
     * @see `Direction`      Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll
     *
     * @return Scrollview scroll direction.
     */
    Direction getDirection()const;

    /**
     * Get inner container of scrollview.
     *
     * Inner container is a child of scrollview.
     *
     * @return Inner container pointer.
     */
    Layout* getInnerContainer()const;

    /**
     * Scroll inner container to bottom boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToBottom(float second, bool attenuated);

    /**
     * Scroll inner container to top boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToTop(float second, bool attenuated);

    /**
     * Scroll inner container to left boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToLeft(float second, bool attenuated);

    /**
     * Scroll inner container to right boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToRight(float time, bool attenuated);

    /**
     * Scroll inner container to top and left boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToTopLeft(float second, bool attenuated);

    /**
     * Scroll inner container to top and right boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToTopRight(float time, bool attenuated);

    /**
     * Scroll inner container to bottom and left boundary of scrollview.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToBottomLeft(float second, bool attenuated);

    /**
     * Scroll inner container to bottom and right boundary of scrollview.
     * @param second Time in seconds
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToBottomRight(float time, bool attenuated);

    /**
     * Scroll inner container to vertical percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToPercentVertical(float percent, float second, bool attenuated);

    /**
     * Scroll inner container to horizontal percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToPercentHorizontal(float percent, float second, bool attenuated);

    /**
     * Scroll inner container to both direction percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param second Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    void scrollToPercentBothDirection(const Vec2& percent, float second, bool attenuated);

    /**
     * Move inner container to bottom boundary of scrollview.
     */
    void jumpToBottom();

    /**
     * Move inner container to top boundary of scrollview.
     */
    void jumpToTop();

    /**
     * Move inner container to left boundary of scrollview.
     */
    void jumpToLeft();

    /**
     * Move inner container to right boundary of scrollview.
     */
    void jumpToRight();

    /**
     * Move inner container to top and left boundary of scrollview.
     */
    void jumpToTopLeft();

    /**
     * Move inner container to top and right boundary of scrollview.
     */
    void jumpToTopRight();

    /**
     * Move inner container to bottom and left boundary of scrollview.
     */
    void jumpToBottomLeft();

    /**
     * Move inner container to bottom and right boundary of scrollview.
     */
    void jumpToBottomRight();

    /**
     * Move inner container to vertical percent position of scrollview.
     * @param percent A value between 0 and 100.
     */
    void jumpToPercentVertical(float percent);

    /**
     * Move inner container to horizontal percent position of scrollview.
     * @param percent   A value between 0 and 100.
     */
    void jumpToPercentHorizontal(float percent);

    /**
     * Move inner container to both direction percent position of scrollview.
     * @param percent   A value between 0 and 100.
     */
    void jumpToPercentBothDirection(const Vec2& percent);

    /**
     * Change inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @param size Inner container size.
     */
    void setInnerContainerSize(const Size &size);

    /**
     * Get inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @return The inner container size.
     */
	const Size& getInnerContainerSize() const;

    /**
     * Add callback function which will be called  when scrollview event triggered.
     * @deprecated Use @see `addEventListener` instead.
     * @param target A pointer of `Ref*` type.
     * @param selector A member function pointer with type of `SEL_ScrollViewEvent`.
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerScrollView(Ref* target, SEL_ScrollViewEvent selector);

    /**
     * Add callback function which will be called  when scrollview event triggered.
     * @param callback A callback function with type of `ccScrollViewCallback`.
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
     * @brief Toggle bounce enabled when scroll to the edge.
     *
     * @param enabled True if enable bounce, false otherwise.
     */
    void setBounceEnabled(bool enabled);

    /**
     * @brief Query bounce state.
     *
     * @return True if bounce is enabled, false otherwise.
     */
    bool isBounceEnabled() const;

    /**
     * @brief Toggle whether enable scroll inertia while scrolling.
     *
     * @param enabled True if enable inertia, false otherwise.
     */
    void setInertiaScrollEnabled(bool enabled);

    /**
     * @brief Query inertia scroll state.
     *
     * @return True if inertia is enabled, false otherwise.
     */
    bool isInertiaScrollEnabled() const;

    /**
     * Set layout type for scrollview.
     *
     * @see `Layout::Type`
     * @param type  Layout type enum.
     */
    virtual void setLayoutType(Type type) override;

    /**
     * Get the layout type for scrollview.
     *
     * @see `Layout::Type`
     * @return LayoutType
     */
    virtual Type getLayoutType() const override;

    /**
     * Return the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    /**
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     *@param direction the direction to look for the next focused widget in a layout
     *@param current  the current focused widget
     *@return the next focused widget in a layout
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
    float _childFocusCancelOffsetInInch;

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
