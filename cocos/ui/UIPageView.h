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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "ui/UILayout.h"
#include "ui/UIScrollInterface.h"

NS_CC_BEGIN

namespace ui {

typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

typedef void (Ref::*SEL_PageViewEvent)(Ref*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

typedef enum {
    PAGEVIEW_TOUCHLEFT,
    PAGEVIEW_TOUCHRIGHT
}PVTouchDir;

class PageView : public Layout , public UIScrollInterface
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    PageView();
    
    /**
     * Default destructor
     */
    virtual ~PageView();
    
    /**
     * Allocates and initializes.
     */
    static PageView* create();
    
    /**
     * Add a widget to a page of pageview.
     *
     * @param widget    widget to be added to pageview.
     *
     * @param pageIdx   index of page.
     *
     * @param forceCreate   if force create and there is no page exsit, pageview would create a default page for adding widget.
     */
    void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
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
    void removePageAtIndex(ssize_t index);
    
    void removeAllPages();
    
    /**
     * scroll pageview to index.
     *
     * @param idx    index of page.
     */
    void scrollToPage(ssize_t idx);
    
    /**
     * Gets current page index.
     *
     * @return current page index.
     */
    ssize_t getCurPageIndex() const;
    
    Vector<Layout*>& getPages();
    
    Layout* getPage(ssize_t index);
    
    // event
    void addEventListenerPageView(Ref *target, SEL_PageViewEvent selector);

    

    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    //override "update" method of widget.
    virtual void update(float dt) override;
    /**
     * Sets LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(LayoutType type) override{};
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual LayoutType getLayoutType() const override{return LAYOUT_ABSOLUTE;};
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void addChild(Node * child) override;
    virtual void addChild(Node * child, int zOrder) override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void removeChild(Node* widget, bool cleanup = true) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual Vector<Node*>& getChildren() override{return Widget::getChildren();};
    virtual const Vector<Node*>& getChildren() const override{return Widget::getChildren();};
    virtual ssize_t getChildrenCount() const override {return Widget::getChildrenCount();};
    virtual Node * getChildByTag(int tag) override {return Widget::getChildByTag(tag);};
    virtual Widget* getChildByName(const char* name) override {return Widget::getChildByName(name);};
    Layout* createPage();
    float getPositionXByIndex(ssize_t idx);
    void updateBoundaryPages();
    virtual void handlePressLogic(const Vector2 &touchPoint) override;
    virtual void handleMoveLogic(const Vector2 &touchPoint) override;
    virtual void handleReleaseLogic(const Vector2 &touchPoint) override;
    virtual void interceptTouchEvent(int handleState, Widget* sender, const Vector2 &touchPoint) override;
    virtual void checkChildInfo(int handleState, Widget* sender, const Vector2 &touchPoint) override;
    virtual bool scrollPages(float touchOffset);
    void movePages(float offset);
    void pageTurningEvent();
    void updateChildrenSize();
    void updateChildrenPosition();
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    virtual void setClippingEnabled(bool enabled) override {Layout::setClippingEnabled(enabled);};
    virtual void doLayout() override{if (!_doLayoutDirty){return;} _doLayoutDirty = false;};
protected:
    ssize_t _curPageIdx;
    Vector<Layout*> _pages;
    PVTouchDir _touchMoveDir;
    float _touchStartLocation;
    float _touchMoveStartLocation;
    Vector2 _movePagePoint;
    Widget* _leftChild;
    Widget* _rightChild;
    float _leftBoundary;
    float _rightBoundary;
    bool _isAutoScrolling;
    float _autoScrollDistance;
    float _autoScrollSpeed;
    int _autoScrollDir;
    float _childFocusCancelOffset;
    Ref* _pageViewEventListener;
    SEL_PageViewEvent _pageViewEventSelector;

};

}
NS_CC_END

#endif /* defined(__PageView__) */
