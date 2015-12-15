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

#include "ui/UIListView.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

class PageViewIndicator;

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
class CC_GUI_DLL PageView : public ListView
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

    /**
     * PageView page turn event callback.
     */
    typedef std::function<void(Ref*, EventType)> ccPageViewCallback;

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
     * Changes direction
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     * @param direction Set the page view's scroll direction.
     */
    virtual void setDirection(Direction direction) override;

    /**
     * Add a widget as a page of PageView in a given index.
     *
     * @param widget    Widget to be added to pageview.
     * @param pageIdx   A given index.
     * @param forceCreate   If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it.
     *
     * Since v3.9, this is deprecated. Use `insertPage(Widget* page, int idx)` instead.
     */
    CC_DEPRECATED_ATTRIBUTE void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
    /**
     * Insert a page into the end of PageView.
     *
     * @param page Page to be inserted.
     */
    void addPage(Widget* page);

    /**
     * Insert a page into PageView at a given index.
     *
     * @param page  Page to be inserted.
     * @param idx   A given index.
     */
    void insertPage(Widget* page, int idx);

    /**
     * Remove a page of PageView.
     *
     * @param page  Page to be removed.
     */
    void removePage(Widget* page);

    /**
     * Remove a page at a given index of PageView.
     *
     * @param index  A given index.
     */
    void removePageAtIndex(ssize_t index);

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
     * Scroll to a page with a given index.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     */
    void scrollToItem(ssize_t itemIndex);

    /**
     * Gets current displayed page index.
     * @return current page index.
     *
     * Since v3.9, this is deprecated. Use `getCurrentPageIndex()` instead.
     */
    CC_DEPRECATED_ATTRIBUTE ssize_t getCurPageIndex() const;

    /**
     * Gets current displayed page index.
     * @return current page index.
     */
    ssize_t getCurrentPageIndex() const { return _currentPageIndex; }

    /**
     * Jump to a page with a given index without scrolling.
     * This is the different between scrollToPage.
     *
     * @param index A given index in PageView. Index start from 0 to pageCount -1.
     *
     * Since v3.9, this is deprecated. Use `setCurrentPageIndex()` instead.
     */
    CC_DEPRECATED_ATTRIBUTE void setCurPageIndex(ssize_t index);

    /**
     * Jump to a page with a given index without scrolling.
     * This is the different between scrollToPage.
     *
     * @param index A given index in PageView. Index start from 0 to pageCount -1.
     */
    void setCurrentPageIndex(ssize_t index);

    /**
     * @brief Get all the pages in the PageView.
     * @return A vector of Layout pointers.
     *
     * Since v3.9, this is obsolete. Use `Vector<Widget*>& ListView::getItems()` instead.
     */
    CC_DEPRECATED_ATTRIBUTE Vector<Layout*>& getPages();

    /**
     * @brief Get a page at a given index
     *
     * @param index A given index.
     * @return A layout pointer in PageView container.
     *
     * Since v3.9, this is obsolete. Use `Widget* ListView::getItem(index)` instead.
     */
    CC_DEPRECATED_ATTRIBUTE Layout* getPage(ssize_t index);
    
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
    virtual std::string getDescription() const override;

    /**
     * @brief Toggle page indicator enabled.
     *
     * @param enabled True if enable page indicator, false otherwise.
     */
    void setIndicatorEnabled(bool enabled);

    /**
     * @brief Query page indicator state.
     *
     * @return True if page indicator is enabled, false otherwise.
     */
    bool getIndicatorEnabled() const { return _indicator != nullptr; }

    /**
     * @brief Set the page indicator's position using anchor point.
     *
     * @param positionAsAnchorPoint The position as anchor point.
     */
    void setIndicatorPositionAsAnchorPoint(const Vec2& positionAsAnchorPoint);

    /**
     * @brief Get the page indicator's position as anchor point.
     *
     * @return positionAsAnchorPoint
     */
    const Vec2& getIndicatorPositionAsAnchorPoint() const;

    /**
     * @brief Set the page indicator's position in page view.
     *
     * @param position The position in page view
     */
    void setIndicatorPosition(const Vec2& position);
    
    /**
     * @brief Get the page indicator's position.
     *
     * @return positionAsAnchorPoint
     */
    const Vec2& getIndicatorPosition() const;

    /**
     * @brief Set space between page indicator's index nodes.
     *
     * @param spaceBetweenIndexNodes Space between nodes in pixel.
     */
    void setIndicatorSpaceBetweenIndexNodes(float spaceBetweenIndexNodes);

    /**
     * @brief Get the space between page indicator's index nodes.
     *
     * @return spaceBetweenIndexNodes
     */
    float getIndicatorSpaceBetweenIndexNodes() const;

    /**
     * @brief Set color of page indicator's selected index.
     *
     * @param spaceBetweenIndexNodes Space between nodes in pixel.
     */
    void setIndicatorSelectedIndexColor(const Color3B& color);

    /**
     * @brief Get the color of page indicator's selected index.
     *
     * @return color
     */
    const Color3B& getIndicatorSelectedIndexColor() const;

    /**
     *@brief If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.
     *@param threshold  A threshold in float.
     *@deprecated Since v3.9, this method has no effect.
     */
    CC_DEPRECATED_ATTRIBUTE void setCustomScrollThreshold(float threshold);

    /**
     *@brief Query the custom scroll threshold of the PageView.
     *@return Custom scroll threshold in float.
     *@deprecated Since v3.9, this method always returns 0.
     */
    CC_DEPRECATED_ATTRIBUTE float getCustomScrollThreshold()const;

    /**
     *@brief Set using user defined scroll page threshold or not.
     * If you set it to false, then the default scroll threshold is pageView.width / 2
     *@param flag True if using custom scroll threshold, false otherwise.
     *@deprecated Since v3.9, this method has no effect.
     */
    CC_DEPRECATED_ATTRIBUTE void setUsingCustomScrollThreshold(bool flag);

    /**
     *@brief Query whether use user defined scroll page threshold or not.
     *@return True if using custom scroll threshold, false otherwise.
     *@deprecated Since v3.9, this method always returns false.
     */
    CC_DEPRECATED_ATTRIBUTE bool isUsingCustomScrollThreshold()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

    //override methods
    virtual void doLayout() override;

protected:
    void pageTurningEvent();

    virtual void remedyLayoutParameter(Widget* item)override;
    virtual void moveInnerContainer(const Vec2& deltaMove, bool canStartBounceBack) override;
    virtual void onItemListChanged() override;
    virtual void onSizeChanged() override;
    virtual void handleReleaseLogic(Touch *touch) override;

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

    void refreshIndicatorPosition();

protected:
    PageViewIndicator* _indicator;
    Vec2 _indicatorPositionAsAnchorPoint;

    ssize_t _currentPageIndex;

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
