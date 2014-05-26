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
#include "ui/UIScrollInterface.h"

NS_CC_BEGIN

namespace ui {
    
class ScrollInnerContainer : public Layout
{
public:
    ScrollInnerContainer();
    virtual ~ScrollInnerContainer();
    static ScrollInnerContainer* create();
    virtual const Size& getLayoutSize() override;
};

CC_DEPRECATED_ATTRIBUTE typedef enum
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

CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_ScrollViewEvent)(Ref*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)


class ScrollView : public Layout , public UIScrollInterface
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Direction
    {
        NONE,
        VERTICAL,
        HORIZONTAL,
        BOTH
    };
    
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
    typedef std::function<void(Ref*, EventType)> ccScrollViewCallback;
    /**
     * Default constructor
     */
    ScrollView();
    
    /**
     * Default destructor
     */
    virtual ~ScrollView();
    
    /**
     * Allocates and initializes.
     */
    static ScrollView* create();
    
    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(Direction dir);
    
    /**
     * Gets scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @return SCROLLVIEW_DIR
     */
    Direction getDirection();
    
    /**
     * Gets inner container of scrollview.
     *
     * Inner container is the container of scrollview's children.
     *
     * @return inner container.
     */
    Layout* getInnerContainer();
    
    /**
     * Scroll inner container to bottom boundary of scrollview.
     */
    void scrollToBottom(float time, bool attenuated);
    
    /**
     * Scroll inner container to top boundary of scrollview.
     */
    void scrollToTop(float time, bool attenuated);
    
    /**
     * Scroll inner container to left boundary of scrollview.
     */
    void scrollToLeft(float time, bool attenuated);
    
    /**
     * Scroll inner container to right boundary of scrollview.
     */
    void scrollToRight(float time, bool attenuated);
    
    /**
     * Scroll inner container to top and left boundary of scrollview.
     */
    void scrollToTopLeft(float time, bool attenuated);
    
    /**
     * Scroll inner container to top and right boundary of scrollview.
     */
    void scrollToTopRight(float time, bool attenuated);
    
    /**
     * Scroll inner container to bottom and left boundary of scrollview.
     */
    void scrollToBottomLeft(float time, bool attenuated);
    
    /**
     * Scroll inner container to bottom and right boundary of scrollview.
     */
    void scrollToBottomRight(float time, bool attenuated);
    
    /**
     * Scroll inner container to vertical percent position of scrollview.
     */
    void scrollToPercentVertical(float percent, float time, bool attenuated);
    
    /**
     * Scroll inner container to horizontal percent position of scrollview.
     */
    void scrollToPercentHorizontal(float percent, float time, bool attenuated);
    
    /**
     * Scroll inner container to both direction percent position of scrollview.
     */
    void scrollToPercentBothDirection(const Vec2& percent, float time, bool attenuated);
    
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
     */
    void jumpToPercentVertical(float percent);
    
    /**
     * Move inner container to horizontal percent position of scrollview.
     */
    void jumpToPercentHorizontal(float percent);
    
    /**
     * Move inner container to both direction percent position of scrollview.
     */
    void jumpToPercentBothDirection(const Vec2& percent);
    
    /**
     * Changes inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @param inner container size.
     */
    void setInnerContainerSize(const Size &size);
    
    /**
     * Gets inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @return inner container size.
     */
	const Size& getInnerContainerSize() const;
    
    /**
     * Add call back function called scrollview event triggered
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerScrollView(Ref* target, SEL_ScrollViewEvent selector);
    void addEventListener(const ccScrollViewCallback& callback);
        
    virtual void addChild(Node * child) override;
    /**
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     */
    virtual void addChild(Node * child, int zOrder) override;
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(Node* child, int zOrder, int tag) override;
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildren() override;
    
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    
    //override "removeChild" method of widget.
	virtual void removeChild(Node* child, bool cleaup = true) override;
    
    //override "getChildren" method of widget.
    virtual Vector<Node*>& getChildren() override;
    virtual const Vector<Node*>& getChildren() const override;
    
    virtual ssize_t getChildrenCount() const override;
    
    virtual Node * getChildByTag(int tag) const override;
    
    virtual Widget* getChildByName(const std::string& name) override;
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    virtual void update(float dt) override;
    
    void setBounceEnabled(bool enabled);
    
    bool isBounceEnabled() const;
    
    void setInertiaScrollEnabled(bool enabled);
    
    bool isInertiaScrollEnabled() const;
    
    /**
     * Sets LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(Type type) override;
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual Type getLayoutType() const override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;
    void moveChildren(float offsetX, float offsetY);
    void autoScrollChildren(float dt);
    void bounceChildren(float dt);
    void checkBounceBoundary();
    bool checkNeedBounce();
    void startAutoScrollChildrenWithOriginalSpeed(const Vec2& dir, float v, bool attenuated, float acceleration);
    void startAutoScrollChildrenWithDestination(const Vec2& des, float time, bool attenuated);
    void jumpToDestination(const Vec2& des);
    void stopAutoScrollChildren();
    void startBounceChildren(float v);
    void stopBounceChildren();
    bool checkCustomScrollDestination(float* touchOffsetX, float* touchOffsetY);
    
    virtual bool scrollChildren(float touchOffsetX, float touchOffsetY);
    virtual bool scrollChilderHorizontal(float touchOffsetX, float touchOffsetY);
    virtual bool scrollChilderVertical(float touchOffsetX, float touchOffsetY);
    virtual bool scrollChilderBoth(float touchOffsetX, float touchOffsetY);

    
    bool bounceScrollChildren(float touchOffsetX, float touchOffsetY);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    virtual void handlePressLogic(const Vec2 &touchPoint) override;
    virtual void handleMoveLogic(const Vec2 &touchPoint) override;
    virtual void handleReleaseLogic(const Vec2 &touchPoint) override;
    virtual void interceptTouchEvent(int handleState,Widget* sender,const Vec2 &touchPoint) override;
    virtual void checkChildInfo(int handleState,Widget* sender,const Vec2 &touchPoint) override;
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
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    virtual void setClippingEnabled(bool able) override{Layout::setClippingEnabled(able);};
    virtual void doLayout() override;
protected:
    Layout* _innerContainer;
    
    Direction _direction;

    Vec2 _touchBeganPoint;
    Vec2 _touchMovedPoint;
    Vec2 _touchEndedPoint;
    Vec2 _touchMovingPoint;
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
NS_CC_END
#endif /* defined(__CocoGUI__ScrollView__) */
