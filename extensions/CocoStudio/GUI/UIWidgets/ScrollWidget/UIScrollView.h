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

#include "../../Layouts/Layout.h"
#include "UIScrollInterface.h"

NS_CC_EXT_BEGIN

enum SCROLLVIEW_DIR
{
    SCROLLVIEW_DIR_NONE,
    SCROLLVIEW_DIR_VERTICAL,
    SCROLLVIEW_DIR_HORIZONTAL
};

enum SCROLLVIEW_MOVE_DIR
{
    SCROLLVIEW_MOVE_DIR_NONE,
    SCROLLVIEW_MOVE_DIR_UP,
    SCROLLVIEW_MOVE_DIR_DOWN,
    SCROLLVIEW_MOVE_DIR_LEFT,
    SCROLLVIEW_MOVE_DIR_RIGHT,
};

typedef enum
{
    SCROLLVIEW_EVENT_SCROLL_TO_TOP,
    SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM,
    SCROLLVIEW_EVENT_SCROLL_TO_LEFT,
    SCROLLVIEW_EVENT_SCROLL_TO_RIGHT,
}ScrollviewEventType;

typedef void (Object::*SEL_ScrollViewEvent)(Object*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)


class UIScrollView : public Layout , public UIScrollInterface
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
    void setDirection(SCROLLVIEW_DIR dir);
    
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
    Layout* getInnerContainer();
    
    /**
     * Scroll inner container to bottom boundary of scrollview.
     */
    void scrollToBottom();
    
    /**
     * Scroll inner container to top boundary of scrollview.
     */
    void scrollToTop();
    
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
    void addEventListener(Object* target, SEL_ScrollViewEvent selector);    
    
    //override "setLayoutExecutant" method of widget.
    virtual void setLayoutExecutant(LayoutExecutant* exe);
    
    //override "getLayoutExecutant" method of widget.
    virtual LayoutExecutant* getLayoutExecutant() const;
    
    //override "addChild" method of widget.
    virtual bool addChild(UIWidget* widget);
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildren();
    
    //override "removeChild" method of widget.
	virtual bool removeChild(UIWidget* child);
    
    //override "getChildren" method of widget.
    virtual Array* getChildren();
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const Point &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const Point &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const Point &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const Point &touchPoint);
    
    //override "onTouchLongClicked" method of widget.
    virtual void onTouchLongClicked(const Point &touchPoint);
    
    virtual void update(float dt);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
protected:
    virtual bool init();
    virtual void initRenderer();
    void moveChildren(float offset);
    void autoScrollChildren(float dt);
    void startAutoScrollChildren(float v);
    void stopAutoScrollChildren();
    float getCurAutoScrollDistance(float time);
    virtual bool scrollChildren(float touchOffset);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    virtual void handlePressLogic(const Point &touchPoint);
    virtual void handleMoveLogic(const Point &touchPoint);
    virtual void handleReleaseLogic(const Point &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const Point &touchPoint);
    virtual void checkChildInfo(int handleState,UIWidget* sender,const Point &touchPoint);
    void recordSlidTime(float dt);
    //override "releaseResoures" method of widget.
    virtual void releaseResoures();
    
    void scrollToTopEvent();
    void scrollToBottomEvent();
    void scrollToLeftEvent();
    void scrollToRightEvent();
    void setMoveDirection(SCROLLVIEW_MOVE_DIR dir);
    SCROLLVIEW_MOVE_DIR getMoveDirection();
    virtual void onSizeChanged();
    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
protected:
    Layout* _innerContainer;
    
    SCROLLVIEW_DIR _direction;
    SCROLLVIEW_MOVE_DIR _moveDirection;
    float _touchStartLocation;
    float _touchEndLocation;
    float _touchMoveStartLocation;
    float _topBoundary;//test
    float _bottomBoundary;//test
    float _leftBoundary;
    float _rightBoundary;
    
    bool _topEnd;
    bool _bottomEnd;
    bool _leftEnd;
    bool _rightEnd;
    
    bool _autoScroll;
    
    float _autoScrollOriginalSpeed;
    float _autoScrollAcceleration;
    
    bool _bePressed;
    float _slidTime;
    Point _moveChildPoint;
    float _childFocusCancelOffset;
    
    Object* _eventListener;
    SEL_ScrollViewEvent _eventSelector;
    
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIScrollView__) */
