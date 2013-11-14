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

#include "../../Layouts/UILayout.h"
#include "UIScrollInterface.h"

NS_CC_EXT_BEGIN

typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

typedef void (CCObject::*SEL_PageViewEvent)(CCObject*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

/*******Compatible*******/
typedef void (CCObject::*SEL_PageViewPageTurningEvent)(CCObject*);
#define coco_PageView_PageTurning_selector(_SELECTOR) (SEL_PageViewPageTurningEvent)(&_SELECTOR)
/************************/

typedef enum {
    PAGEVIEW_TOUCHLEFT,
    PAGEVIEW_TOUCHRIGHT
}PVTouchDir;

class UIPageView : public UILayout , public UIScrollInterface
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
    void addPage(UILayout* page);
    
    /**
     * Inert a page to pageview.
     *
     * @param page    page to be added to pageview.
     */
    void insertPage(UILayout* page, int idx);
    
    /**
     * Remove a page of pageview.
     *
     * @param page    page which will be removed.
     */
    void removePage(UILayout* page);

    /**
     * Remove a page at index of pageview.
     *
     * @param index    index of page.
     */
    void removePageAtIndex(int index);
    
    void removeAllPages();
    
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
    
    CCArray* getPages();
    
    UILayout* getPage(int index);
    
    // event
    void addEventListenerPageView(CCObject *target, SEL_PageViewEvent selector);
    /*******Compatible*******/
    //Add call back function called when page turning.
    void addPageTurningEvent(CCObject *target, SEL_PageViewPageTurningEvent selector);
    /**************/
    

    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const CCPoint &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    //override "update" method of widget.
    virtual void update(float dt);
    
    virtual void doLayout(){};
    
    /**
     * Sets LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(LayoutType type){};
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual LayoutType getLayoutType() const{return LAYOUT_ABSOLUTE;};
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
    /*compatible*/
    /**
     * These methods will be removed
     */
    int getPage() const{return getCurPageIndex();};
    void removePage(UILayout* page, bool cleanup){removePage(page);};
    void removePageAtIndex(int index, bool cleanup){removePageAtIndex(index);};
    /************/
protected:
    virtual bool addChild(UIWidget* widget);
    virtual bool removeChild(UIWidget* widget);
    virtual void removeAllChildren();
    virtual bool init();
    UILayout* createPage();
    float getPositionXByIndex(int idx);
    void updateBoundaryPages();
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual bool scrollPages(float touchOffset);
    void movePages(float offset);
    void pageTurningEvent();
    void updateChildrenSize();
    void updateChildrenPosition();
    virtual void onSizeChanged();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
    virtual void copyClonedWidgetChildren(UIWidget* model);
    /*compatible*/
    /**
     * These methods will be removed
     */
    virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/
    virtual void setClippingEnabled(bool able){UILayout::setClippingEnabled(able);};
protected:
    int m_nCurPageIdx;
    CCArray* m_pages;
    PVTouchDir m_touchMoveDir;
    float m_fTouchStartLocation;
    float m_fTouchMoveStartLocation;
    CCPoint movePagePoint;
    UIWidget* m_pLeftChild;
    UIWidget* m_pRightChild;
    float m_fLeftBoundary;
    float m_fRightBoundary;
    bool m_bIsAutoScrolling;
    float m_fAutoScrollDistance;
    float m_fAutoScrollSpeed;
    int m_nAutoScrollDir;
    float m_fChildFocusCancelOffset;
    CCObject* m_pPageViewEventListener;
    SEL_PageViewEvent m_pfnPageViewEventSelector;
    /*compatible*/
    CCObject* m_pPageTurningListener;
    SEL_PageViewPageTurningEvent m_pfnPageTurningSelector;
    /************/
};

NS_CC_EXT_END

#endif /* defined(__UIPageView__) */
