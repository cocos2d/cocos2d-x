/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "gui/UILayout.h"
#include "gui/UIScrollInterface.h"

namespace gui {

enum SCROLLVIEW_DIR
{
    SCROLLVIEW_DIR_NONE,
    SCROLLVIEW_DIR_VERTICAL,
    SCROLLVIEW_DIR_HORIZONTAL,
    SCROLLVIEW_DIR_BOTH
};

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

typedef void (cocos2d::CCObject::*SEL_ScrollViewEvent)(cocos2d::Object*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)


class UIScrollView : public UILayout , public UIScrollInterface
{
public:
    /**
     * Default constructor
     */
    UIScrollView();
    
    /**
     * Default destructor
     */
    virtual ~UIScrollView();
    
    /**
     * Allocates and initializes.
     */
    static UIScrollView* create();
    
    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(SCROLLVIEW_DIR dir);
    
    /**
     * Gets scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @return SCROLLVIEW_DIR
     */
    SCROLLVIEW_DIR getDirection();
    
    /**
     * Gets inner container of scrollview.
     *
     * Inner container is the container of scrollview's children.
     *
     * @return inner container.
     */
    UILayout* getInnerContainer();
    
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
    void scrollToPercentBothDirection(const cocos2d::Point& percent, float time, bool attenuated);
    
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
    void jumpToPercentBothDirection(const cocos2d::Point& percent);
    
    /**
     * Changes inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @param inner container size.
     */
    void setInnerContainerSize(const cocos2d::Size &size);
    
    /**
     * Gets inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @return inner container size.
     */
	const cocos2d::Size& getInnerContainerSize() const;
    
    /**
     * Add call back function called scrollview event triggered
     */
    void addEventListenerScrollView(cocos2d::Object* target, SEL_ScrollViewEvent selector);
        
    //override "addChild" method of widget.
    virtual bool addChild(UIWidget* widget) override;
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildren() override;
    
    //override "removeChild" method of widget.
	virtual bool removeChild(UIWidget* child) override;
    
    //override "getChildren" method of widget.
    virtual cocos2d::Array* getChildren() override;
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchLongClicked" method of widget.
    virtual void onTouchLongClicked(const cocos2d::Point &touchPoint) override;
    
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
    virtual void setLayoutType(LayoutType type) override;
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual LayoutType getLayoutType() const override;
    
    virtual void doLayout() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;
protected:
    virtual bool init() override;
    virtual void initRenderer() override;
    void moveChildren(float offsetX, float offsetY);
    void autoScrollChildren(float dt);
    void bounceChildren(float dt);
    void checkBounceBoundary();
    bool checkNeedBounce();
    void startAutoScrollChildrenWithOriginalSpeed(const cocos2d::Point& dir, float v, bool attenuated, float acceleration);
    void startAutoScrollChildrenWithDestination(const cocos2d::Point& des, float time, bool attenuated);
    void jumpToDestination(const cocos2d::Point& des);
    void stopAutoScrollChildren();
    void startBounceChildren(float v);
    void stopBounceChildren();
    bool checkCustomScrollDestination(float* touchOffsetX, float* touchOffsetY);
    virtual bool scrollChildren(float touchOffsetX, float touchOffsetY);
    bool bounceScrollChildren(float touchOffsetX, float touchOffsetY);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    virtual void handlePressLogic(const cocos2d::Point &touchPoint) override;
    virtual void handleMoveLogic(const cocos2d::Point &touchPoint) override;
    virtual void handleReleaseLogic(const cocos2d::Point &touchPoint) override;
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const cocos2d::Point &touchPoint) override;
    virtual void checkChildInfo(int handleState,UIWidget* sender,const cocos2d::Point &touchPoint) override;
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
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
    virtual void copyClonedWidgetChildren(UIWidget* model) override;
    virtual void setClippingEnabled(bool able) override{UILayout::setClippingEnabled(able);};
protected:
    UILayout* _innerContainer;
    
    SCROLLVIEW_DIR _direction;

    cocos2d::Point _touchBeganPoint;
    cocos2d::Point _touchMovedPoint;
    cocos2d::Point _touchEndedPoint;
    cocos2d::Point _touchMovingPoint;
    cocos2d::Point _autoScrollDir;
    
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
    cocos2d::Point _autoScrollDestination;
    
    bool _bePressed;
    float _slidTime;
    cocos2d::Point _moveChildPoint;
    float _childFocusCancelOffset;
    
    bool _leftBounceNeeded;
    bool _topBounceNeeded;
    bool _rightBounceNeeded;
    bool _bottomBounceNeeded;
    
    bool _bounceEnabled;
    bool _bouncing;
    cocos2d::Point _bounceDir;
    float _bounceOriginalSpeed;
    bool _inertiaScrollEnabled;


    
    cocos2d::Object* _scrollViewEventListener;
    SEL_ScrollViewEvent _scrollViewEventSelector;
};

}

#endif /* defined(__CocoGUI__UIScrollView__) */
