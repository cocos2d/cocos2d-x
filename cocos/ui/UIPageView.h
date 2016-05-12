/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

/** @class PageView
*@brief @~english Layout manager that allows the user to flip left & right and up & down through pages of data.
 
 @~chinese Layout的管理器，可以让用户在多个Layout之间左右或者上下切换显示。
*/
class CC_GUI_DLL PageView : public ListView
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Page turn event type.
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
     * @~english PageView page turn event callback.
     * @~chinese 页面翻页时的事件回调。
     */
    typedef std::function<void(Ref*, EventType)> ccPageViewCallback;

    /**
     * @~english Default constructor
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    PageView();
    
    /**
     * @~english Default destructor
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~PageView();
    
    /**
     * @~english Create an empty PageView.
     * @~chinese 创建一个空的PageView。
     * @return @~english A PageView instance.
     */
    static PageView* create();

    /**
     * Changes direction
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     * @param direction Set the page view's scroll direction.
     */
    virtual void setDirection(Direction direction) override;

    /**
     * @~english Add a widget as a page of PageView in a given index.
     * @~chinese 把一个widget添加到指定的PageView页中。
     * @param widget    @~english Widget to be added to pageview. @~chinese 被添加到PageView中的Widget。
     * @param pageIdx   @~english A given index. @~chinese 页索引。
     * @param forceCreate   @~english If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it. @~chinese 如果forceCreate为True，并且指定页不存在，将会创建一个默认页并把widget加入。
     */
    CC_DEPRECATED_ATTRIBUTE void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
    /**
     * @~english Insert a page into the end of PageView.
     * @~chinese 往PageView的最后插入一页。
     * @param page @~english Page to be inserted. @~chinese 被插入的页。
     */
    void addPage(Widget* page);

    /**
     * @~english Insert a page into PageView at a given index.
     * @~chinese 在指定位置插入一页。
     * @param page  @~english Page to be inserted. @~chinese 被插入的页。
     * @param idx   @~english A given index. @~chinese 页索引号。
     */
    void insertPage(Widget* page, int idx);

    /**
     * @~english Remove a page of PageView.
     * @~chinese 从PageView中移除一页。
     * @param page  @~english Page to be removed. @~chinese 被移除的页。
     */
    void removePage(Widget* page);

    /**
     * @~english Remove a page at a given index of PageView.
     * @~chinese 移除指定位置的页。
     * @param index  @~english A given index. @~chinese 页索引号。
     */
    void removePageAtIndex(ssize_t index);

    /**
     * @~english Remove all pages of the PageView.
     * @~chinese 移除PageView中所有页。
     */
    void removeAllPages();
    
    /**
     * @~english Scroll to a page with a given index.
     * @~chinese 滚动到一个指定的页。
     * @param idx   @~english A given index in the PageView. Index start from 0 to pageCount-1. 
     * @~chinese 页索引号。索引从0到pageCount-1
     */
    void scrollToPage(ssize_t idx);

    /**
     * Scroll to a page with a given index.
     *
     * @param idx   A given index in the PageView. Index start from 0 to pageCount -1.
     */
    void scrollToItem(ssize_t itemIndex);

    /**
     * @~english Gets current displayed page index.
     * @~chinese 获取当前显示页的索引号。
     * @return @~english current page index. @~chinese 当前页索引号。
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
     * @~english Get all the pages in the PageView.
     * @~english Since v3.9, this is obsolete. Use `Vector<Widget*>& ListView::getItems()` instead.
     * @~chinese 获取所有页的列表。
     * @~chinese 从v3.9版开始此函数已废弃。使用`Vector<Widget*>& ListView::getItems()`取代.
     * @return @~english A vector of Layout pionters. @~chinese 一个Layout指针数组。
     */
    CC_DEPRECATED_ATTRIBUTE Vector<Layout*>& getPages();

    /**
     * @~english Get a page at a given index
     * @~english Since v3.9, this is obsolete. Use `Widget* ListView::getItem(index)` instead.
     * @~chinese 获取指定的页。
     * @~chinese 从v3.9版开始此函数已废弃。使用`Widget* ListView::getItem(index)`取代.
     * @param index @~english A given index. @~chinese 页索引号。
     * @return @~english A layout pointer in PageView container. @~chinese 一个已在PageView中的layout指针。
     */
    CC_DEPRECATED_ATTRIBUTE Layout* getPage(ssize_t index);
    
    /**
     * @~english Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     * @~chinese 添加一个页面切换时的回调函数，当页面切换时被调用。
     * @deprecated Use `PageView::addEventListener` instead.
     * @param target @~english A pointer of `Ref*` type.　@~chinese 一个Ref类型指针。
     * @param selector @~english A member function pointer with signature of `SEL_PageViewEvent`.　@~chinese 回调函数。
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerPageView(Ref *target, SEL_PageViewEvent selector);

    /**
     * @~english Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     * @~chinese 添加一个页面切换时的回调函数，当页面切换时被调用。
     * @param callback @~english A page turning callback. @~chinese 回调函数。
     */
    void addEventListener(const ccPageViewCallback& callback);
    using ScrollView::addEventListener;
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
     * @~english If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.
     * @~chinese 如果没有指定该值，pageView会在滚到页面一半时切换到下一页。
     * @param threshold  @~english A threshold in float. @~chinese 切换页面门限值。
     */
    CC_DEPRECATED_ATTRIBUTE void setCustomScrollThreshold(float threshold);

    /**
     * @~english Query the custom scroll threshold of the PageView.
     * @~chinese 请求设定的切换页面门限值。
     * @return @~english Custom scroll threshold in float. @~chinese 切换页面门限值。
     */
    CC_DEPRECATED_ATTRIBUTE float getCustomScrollThreshold()const;

    /**
     * @~english Set using user defined scroll page threshold or not.
     * If you set it to false, then the default scroll threshold is pageView.width / 2
     * @~chinese 是否使用用户设置的切换页面门限值。
     * 如果设为false，那么pageView会在滚到页面一半时切换到下一页。
     * @param flag @~english True if using custom scroll threshold, false otherwise. @~chinese 切换页面门限值。
     */
    CC_DEPRECATED_ATTRIBUTE void setUsingCustomScrollThreshold(bool flag);

    /**
     * @~english Query whether use user defined scroll page threshold or not.
     * @~chinese 请求是否使用用户自定义页面切换门限值。
     * @return @~english True if using custom scroll threshold, false otherwise. @~chinese True表明使用用户设置的页面切换门限值。反之不使用。
     */
    CC_DEPRECATED_ATTRIBUTE bool isUsingCustomScrollThreshold()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

    //override methods
    virtual void doLayout() override;

protected:
    void pageTurningEvent();
    virtual float getAutoScrollStopEpsilon() const override;

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
