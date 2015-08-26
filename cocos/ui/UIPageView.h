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

/** @class PageView
*@brief @~english Layout manager that allows the user to flip left & right and up & down through pages of data.
 
 @~chinese Layout的管理器，可以让用户在多个Layout之间左右或者上下切换显示。
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
     * @~english PageView page turn event callback.
     * @~chinese 页面翻页时的事件回调。
     */
    typedef std::function<void(Ref*,EventType)> ccPageViewCallback;

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
     * @~english Add a widget as a page of PageView in a given index.
     * @~chinese 把一个widget添加到指定的PageView页中。
     * @param widget    @~english Widget to be added to pageview. @~chinese 被添加到PageView中的Widget。
     * @param pageIdx   @~english A given index. @~chinese 页索引。
     * @param forceCreate   @~english If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it. @~chinese 如果forceCreate为True，并且指定页不存在，将会创建一个默认页并把widget加入。
     */
    void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
    /**
     * @~english Insert a page into the end of PageView.
     * @~chinese 往PageView的最后插入一页。
     * @param page @~english Page to be inserted. @~chinese 被插入的页。
     */
    void addPage(Layout* page);
    
    /**
     * @~english Insert a page into PageView at a given index.
     * @~chinese 在指定位置插入一页。
     * @param page  @~english Page to be inserted. @~chinese 被插入的页。
     * @param idx   @~english A given index. @~chinese 页索引号。
     */
    void insertPage(Layout* page, int idx);
    
    /**
     * @~english Remove a page of PageView.
     * @~chinese 从PageView中移除一页。
     * @param page  @~english Page to be removed. @~chinese 被移除的页。
     */
    void removePage(Layout* page);

    /**
     * @~english Remove a page at a given index of PageView.
     * @~chinese 移除指定位置的页。
     * @param index  @~english A given index. @~chinese 页索引号。
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
     * @~english Gets current displayed page index.
     * @~chinese 获取当前显示页的索引号。
     * @return @~english current page index. @~chinese 当前页索引号。
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
     * @~english Get all the pages in the PageView.
     * @~chinese 获取所有页的列表。
     * @return @~english A vector of Layout pionters. @~chinese 一个Layout指针数组。
     */
    Vector<Layout*>& getPages();
    
    
    /**
     * @~english Get a page at a given index
     * @~chinese 获取指定的页。
     * @param index @~english A given index. @~chinese 页索引号。
     * @return @~english A layout pointer in PageView container. @~chinese 一个已在PageView中的layout指针。
     */
    Layout* getPage(ssize_t index);
    
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
     * @~english If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.
     * @~chinese 如果没有指定该值，pageView会在滚到页面一半时切换到下一页。
     * @param threshold  @~english A threshold in float. @~chinese 切换页面门限值。
     */
    void setCustomScrollThreshold(float threshold);

    /**
     * @~english Query the custom scroll threshold of the PageView.
     * @~chinese 请求设定的切换页面门限值。
     * @return @~english Custom scroll threshold in float. @~chinese 切换页面门限值。
     */
    float getCustomScrollThreshold()const;

    /**
     * @~english Set using user defined scroll page threshold or not.
     * If you set it to false, then the default scroll threshold is pageView.width / 2
     * @~chinese 是否使用用户设置的切换页面门限值。
     * 如果设为false，那么pageView会在滚到页面一半时切换到下一页。
     * @param flag @~english True if using custom scroll threshold, false otherwise. @~chinese 切换页面门限值。
     */
    void setUsingCustomScrollThreshold(bool flag);

    /**
     * @~english Query whether use user defined scroll page threshold or not.
     * @~chinese 请求是否使用用户自定义页面切换门限值。
     * @return @~english True if using custom scroll threshold, false otherwise. @~chinese True表明使用用户设置的页面切换门限值。反之不使用。
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
