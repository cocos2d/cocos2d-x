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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

/**
 *PageView page turn event type.
 *@deprecated Use `PageView::EventType` instead.
 */
typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

/**
 *A callback which would be called when a PageView turning event is happening.
 *@deprecated Use `PageView::ccPageViewCallback` instead.
 */
typedef void (Ref::*SEL_PageViewEvent)(Ref*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

/**
 *@brief Layout manager that allows the user to flip left & right and up & down through pages of data.
 *
 */
class CC_GUI_DLL PageView : public Layout
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Page turn event tpye.
     */
    enum class EventType
    {
        TURNING
    };
    
    /**
     * Touch direction type.
     */
    enum class TouchDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    enum class Direction
    {
        HORIZONTAL,
        VERTICAL
    };
    
    /**
     *PageView page turn event callback.
     */
    typedef std::function<void(Ref*,EventType)> ccPageViewCallback;

    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    PageView();
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~PageView();
    
    /**
     * Create an empty PageView.
     *@return A PageView instance.
     */
    static PageView* create();
    
    /**
     * Add a widget as a page of PageView in a given index.
     *
     * @param widget    Widget to be added to pageview.
     * @param pageIdx   A given index.
     * @param forceCreate   If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it.
     */
    void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
    /**
     * Insert a page into the end of PageView.
     *
     * @param page Page to be inserted.
     */
    void addPage(Layout* page);
    
    /**
     * Insert a page into PageView at a given index.
     *
     * @param page  Page to be inserted.
     * @param idx   A given index.
     */
    void insertPage(Layout* page, int idx);
    
    /**
     * Remove a page of PageView.
     *
     * @param page  Page to be removed.
     */
    void removePage(Layout* page);

    /**
     * Remove a page at a given index of PageView.
     *
     * @param index  A given index.
     */
    void removePageAtIndex(ssize_t index);

    /**
     * Changes scroll direction of PageView
     *
     * @see `Direction`
     * @param direction Scroll direction enum.
     * @since v3.8
     */
    void setDirection(Direction direction);

    /**
     * Query scroll direction of PageView.
     *
     * @see `Direction`
     * @since v3.8
     * @return PageView scroll direction.
     */
    Direction getDirection()const;
    
    /**
     * @brief Remove all pages of the PageView.
     */
    void removeAllPages();
    
    /**
     * Scroll to a page with a given index.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     */
    void scrollToPage(ssize_t idx);


    /**
     * Gets current displayed page index.
     * @return current page index.
     */
    ssize_t getCurPageIndex() const;

    /**
     * Jump to a page with a given index without scrolling.
     * This is the different between scrollToPage.
     *
     * @param index A given index in PageView. Index start from 0 to pageCount -1.
     */
    void setCurPageIndex(ssize_t index);
     
    /**
     * @brief Get all the pages in the PageView.
     * @return A vector of Layout pointers.
     */
    Vector<Layout*>& getPages();
    
    
    /**
     * @brief Get a page at a given index
     *
     * @param index A given index.
     * @return A layout pointer in PageView container.
     */
    Layout* getPage(ssize_t index);
    
    /**
     * Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     *@deprecated Use `PageView::addEventListener` instead.
     *@param target A pointer of `Ref*` type.
     *@param selector A member function pointer with signature of `SEL_PageViewEvent`.
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerPageView(Ref *target, SEL_PageViewEvent selector);

    
    /**
     * @brief Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     *
     * @param callback A page turning callback.
     */
    void addEventListener(const ccPageViewCallback& callback);
    
    //override methods
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    virtual void update(float dt) override;
    virtual void setLayoutType(Type type) override{};
    virtual Type getLayoutType() const override{return Type::ABSOLUTE;};
    virtual std::string getDescription() const override;
    /**
     * @lua NA
     */
    virtual void onEnter() override;

    /**   
     *@brief If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.
     *@param threshold  A threshold in float.
     */
    void setCustomScrollThreshold(float threshold);

    /**
     *@brief Query the custom scroll threshold of the PageView.
     *@return Custom scroll threshold in float.
     */
    float getCustomScrollThreshold()const;

    /**
     *@brief Set using user defined scroll page threshold or not.
     * If you set it to false, then the default scroll threshold is pageView.width / 2
     *@param flag True if using custom scroll threshold, false otherwise.
     */
    void setUsingCustomScrollThreshold(bool flag);

    /**
     *@brief Query whether use user defined scroll page threshold or not.
     *@return True if using custom scroll threshold, false otherwise.
     */
    bool isUsingCustomScrollThreshold()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:

    Layout* createPage();
    float getPositionXByIndex(ssize_t idx)const;
    float getPositionYByIndex(ssize_t idx)const;
    ssize_t getPageCount()const;

    void updateBoundaryPages();
    virtual bool scrollPages(Vec2 touchOffset);
    void movePages(Vec2 offset);
    void pageTurningEvent();
    void updateAllPagesSize();
    void updateAllPagesPosition();
    void autoScroll(float dt);

    virtual void handleMoveLogic(Touch *touch) ;
    virtual void handleReleaseLogic(Touch *touch) ;
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender,Touch *touch) override;
    
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;

    virtual void doLayout() override;

protected:
    enum class AutoScrollDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    bool _isAutoScrolling;
    float _autoScrollDistance;
    float _autoScrollSpeed;
    AutoScrollDirection _autoScrollDirection;
    Direction _direction;
    
    ssize_t _curPageIdx;
    Vector<Layout*> _pages;

    TouchDirection _touchMoveDirection;
   
    Widget* _leftBoundaryChild;
    Widget* _rightBoundaryChild;
    
    float _leftBoundary;
    float _rightBoundary;
    float _customScrollThreshold;
    bool _usingCustomScrollThreshold;

    float _childFocusCancelOffset;

    Ref* _pageViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_PageViewEvent _pageViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccPageViewCallback _eventCallback;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__PageView__) */
