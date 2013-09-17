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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "../../Layouts/Layout.h"
#include "UIScrollInterface.h"

NS_CC_EXT_BEGIN

typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

typedef void (Object::*SEL_PageViewEvent)(Object*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

typedef enum {
    PAGEVIEW_TOUCHLEFT,
    PAGEVIEW_TOUCHRIGHT
}PVTouchDir;

class UIPageView : public Layout , public UIScrollInterface
{
    
public:
    /**
     * Default constructor
     */
    UIPageView();
    
    /**
     * Default destructor
     */
    virtual ~UIPageView();
    
    /**
     * Allocates and initializes.
     */
    static UIPageView* create();
    
    /**
     * Add a widget to a page of pageview.
     *
     * @param widget    widget to be added to pageview.
     *
     * @param pageIdx   index of page.
     *
     * @param forceCreate   if force create and there is no page exsit, pageview would create a default page for adding widget.
     */
    void addWidgetToPage(UIWidget* widget, int pageIdx, bool forceCreate);
    
    /**
     * Push back a page to pageview.
     *
     * @param page    page to be added to pageview.
     */
    void addPage(Layout* page);
    
    /**
     * Inert a page to pageview.
     *
     * @param page    page to be added to pageview.
     */
    void insertPage(Layout* page, int idx);
    
    /**
     * Remove a page of pageview.
     *
     * @param page    page which will be removed.
     */
    void removePage(Layout* page);

    /**
     * Remove a page at index of pageview.
     *
     * @param index    index of page.
     */
    void removePageAtIndex(int index);
    
    /**
     * scroll pageview to index.
     *
     * @param idx    index of page.
     */
    void scrollToPage(int idx);
    
    /**
     * Gets current page index.
     *
     * @return current page index.
     */
    int getCurPageIndex() const;
    
    // event
    void addEventListener(Object *target, SEL_PageViewEvent selector);
    
    //override "removeChild" method of widget.
    virtual bool removeChild(UIWidget* widget);
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildren();
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const Point &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const Point &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const Point &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const Point &touchPoint);
    
    //override "update" method of widget.
    virtual void update(float dt);

    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
protected:
    virtual bool addChild(UIWidget* widget);
    virtual bool init();
    Layout* createPage();
    float getPositionXByIndex(int idx);
    void updateBoundaryPages();
    virtual void handlePressLogic(const Point &touchPoint);
    virtual void handleMoveLogic(const Point &touchPoint);
    virtual void handleReleaseLogic(const Point &touchPoint);
    virtual void interceptTouchEvent(int handleState, UIWidget* sender, const Point &touchPoint);
    virtual void checkChildInfo(int handleState, UIWidget* sender, const Point &touchPoint);
    virtual bool scrollPages(float touchOffset);
    void movePages(float offset);
    void pageTurningEvent();
    void updateChildrenSize();
    void updateChildrenPosition();
    virtual void onSizeChanged();

    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
protected:
    int _curPageIdx;
    Array* _pages;
    PVTouchDir _touchMoveDir;
    float _touchStartLocation;
    float _touchEndLocation;
    float _touchMoveStartLocation;
    Point _movePagePoint;
    UIWidget* _leftChild;
    UIWidget* _rightChild;
    float _leftBoundary;
    float _rightBoundary;
    bool _isAutoScrolling;
    float _autoScrollDistance;
    float _autoScrollSpeed;
    int _autoScrollDir;
    float _childFocusCancelOffset;
    Object* _eventListener;
    SEL_PageViewEvent _eventSelector;
};

NS_CC_EXT_END

#endif /* defined(__UIPageView__) */
