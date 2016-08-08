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


#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "ui/UIScrollView.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui{
    
/**
 * ListView click item event type.
 */
typedef enum
{
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}ListViewEventType;

/**
 * A callback which would be called when a ListView item is clicked.
 *@deprecated Use `ccListViewCallback` instead.
 */
typedef void (Ref::*SEL_ListViewEvent)(Ref*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

/**
 *@brief ListView is a view group that displays a list of scrollable items.
 *The list items are inserted to the list by using `addChild` or  `insertDefaultItem`.
 * @warning The list item in ListView doesn't support cell reuse at the moment, if you have a large amount of data need to be displayed, use  `TableView` instead.
 * ListView is a subclass of  `ScrollView`, so it shares many features of ScrollView.
 */
class CC_GUI_DLL ListView : public ScrollView
{
 
    DECLARE_CLASS_GUI_INFO
public:
    /**
     * Gravity for docking elements in ListView.
     */
    enum class Gravity
    {
        LEFT,
        RIGHT,
        CENTER_HORIZONTAL,
        TOP,
        BOTTOM,
        CENTER_VERTICAL
    };
    
    /**
     * ListView element item click event.
     */
    enum class EventType
    {
        ON_SELECTED_ITEM_START,
        ON_SELECTED_ITEM_END
    };
    
    /**
     * ListView supports magnetic scroll.
     * With CENTER type, ListView tries to align its items in center of current view.
     * With BOTH_END type, ListView tries to align its items in left or right end if it is horizontal, top or bottom in vertical. The aligning side (left or right, top or bottom) is determined by user's scroll direction.
     */
    enum class MagneticType
    {
        NONE,
        CENTER,
        BOTH_END,
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
    };
    
    /**
     * ListView item click callback.
     */
    typedef std::function<void(Ref*, EventType)> ccListViewCallback;
    
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ListView();
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~ListView();
    
    /**
     * Create an empty ListView.
     *@return A ListView instance.
     */
    static ListView* create();
    
    /**
     * Set an item model for listview.
     *
     * When calling `pushBackDefaultItem`, the model will be used as a blueprint and new model copy will be inserted into ListView.
     * @param model  Model in `Widget*`.
     */
    void setItemModel(Widget* model);
    
    /**
     * Insert a default item(create by a cloned model) at the end of the listview.
     */
    void pushBackDefaultItem();
    
    /**
     * Insert a default item(create by cloning model) into listview at a give index.
     *@param index  An index in ssize_t.
     */
    void insertDefaultItem(ssize_t index);
    
    /**
     * Insert a  custom item into the end of ListView.
     *@param item An item in `Widget*`.
     */
    void pushBackCustomItem(Widget* item);
    
    
    /**
     * @brief Insert a custom widget into ListView at a given index.
     *
     * @param item A widget pointer to be inserted.
     * @param index A given index in ssize_t.
     */
    void insertCustomItem(Widget* item, ssize_t index);
    
    /**
     *  Removes the last item of ListView.
     */
    void removeLastItem();
    
    /**
     * Remove an item at given index.
     *
     * @param index A given index in ssize_t.
     */
    void removeItem(ssize_t index);

    /**
     * @brief Remove all items in current ListView.
     *
     
     */
    void removeAllItems();
    
    /**
     * Return an item at a given index.
     *
     * @param index A given index in ssize_t.
     * @return A widget instance.
     */
    Widget* getItem(ssize_t index)const;
    
    /**
     * Return all items in a ListView.
     *@returns A vector of widget pointers.
     */
    Vector<Widget*>& getItems();
    
    /**
     * Return the index of specified widget.
     *
     * @param item  A widget pointer.
     * @return The index of a given widget in ListView.
     */
    ssize_t getIndex(Widget* item) const;
    
    /**
     * Set the gravity of ListView.
     * @see `ListViewGravity`
     */
    void setGravity(Gravity gravity);
    
    /**
     * Set magnetic type of ListView.
     * @see `MagneticType`
     */
    void setMagneticType(MagneticType magneticType);
    
    /**
     * Get magnetic type of ListView.
     */
    MagneticType getMagneticType() const;
    
    /**
     * Set magnetic allowed out of boundary.
     */
    void setMagneticAllowedOutOfBoundary(bool magneticAllowedOutOfBoundary);
    
    /**
     * Query whether the magnetic out of boundary is allowed.
     */
    bool getMagneticAllowedOutOfBoundary() const;
    
    /**
     * Set the margin between each item in ListView.
     *
     * @param margin A margin in float.
     */
    void setItemsMargin(float margin);
    
    /**
     * @brief Query margin between each item in ListView.
     *
     
     * @return A margin in float.
     */
    float getItemsMargin()const;
    
    /**
     * Set the time in seconds to scroll between items.
     * Subsequent calls of function 'scrollToItem', will take 'time' seconds for scrolling.
     * @param time The seconds needed to scroll between two items. 'time' must be >= 0
     * @see scrollToItem(ssize_t, const Vec2&, const Vec2&)
     */
    void  setScrollDuration(float time);
    
     /**
     * Get the time in seconds to scroll between items.
     * @return The time in seconds to scroll between items
     * @see setScrollDuration(float)
     */
    float getScrollDuration() const;
    
    //override methods
    virtual void doLayout() override;
    virtual void requestDoLayout() override;
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleanup = true) override;

    /**
     * @brief Query the closest item to a specific position in inner container.
     *
     * @param targetPosition Specifies the target position in inner container's coordinates.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     * @return An item instance if list view is not empty. Otherwise, returns null.
     */
    Widget* getClosestItemToPosition(const Vec2& targetPosition, const Vec2& itemAnchorPoint) const;
    
    /**
     * @brief Query the closest item to a specific position in current view.
     * For instance, to find the item in the center of view, call 'getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE)'.
     *
     * @param positionRatioInView Specifies the target position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     * @return An item instance if list view is not empty. Otherwise, returns null.
     */
    Widget* getClosestItemToPositionInCurrentView(const Vec2& positionRatioInView, const Vec2& itemAnchorPoint) const;
    
    /**
     * @brief Query the center item
     * @return An item instance.
     */
    Widget* getCenterItemInCurrentView() const;
    
    /**
     * @brief Query the leftmost item in horizontal list
     * @return An item instance.
     */
    Widget* getLeftmostItemInCurrentView() const;
    
    /**
     * @brief Query the rightmost item in horizontal list
     * @return An item instance.
     */
    Widget* getRightmostItemInCurrentView() const;
    
    /**
     * @brief Query the topmost item in horizontal list
     * @return An item instance.
     */
    Widget* getTopmostItemInCurrentView() const;
    
    /**
     * @brief Query the bottommost item in horizontal list
     * @return An item instance.
     */
    Widget* getBottommostItemInCurrentView() const;

    /**
     * Override functions
     */
    virtual void jumpToBottom() override;
    virtual void jumpToTop() override;
    virtual void jumpToLeft() override;
    virtual void jumpToRight() override;
    virtual void jumpToTopLeft() override;
    virtual void jumpToTopRight() override;
    virtual void jumpToBottomLeft() override;
    virtual void jumpToBottomRight() override;
    virtual void jumpToPercentVertical(float percent) override;
    virtual void jumpToPercentHorizontal(float percent) override;
    virtual void jumpToPercentBothDirection(const Vec2& percent) override;

    /**
     * @brief Jump to specific item
     * @param itemIndex Specifies the item's index
     * @param positionRatioInView Specifies the position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     */
    void jumpToItem(ssize_t itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint);
    
    /**
     * @brief Scroll to specific item
     * @param positionRatioInView Specifies the position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     * @param timeInSec Scroll time
     */
    void scrollToItem(ssize_t itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint);
    void scrollToItem(ssize_t itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint, float timeInSec);
    
    /**
     * @brief Query current selected widget's index.
     *
     
     * @return An index of a selected item.
     */
    ssize_t getCurSelectedIndex() const;
    
    /**
     * @brief Set current selected widget's index and call TouchEventType::ENDED event.
     * @param itemIndex A index of a selected item.
     */
     void setCurSelectedIndex(int itemIndex);
    
    /**
     * Add an event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     *@deprecated Use  `addEventListener` instead.
     *@param target A pointer of `Ref*` type.
     *@param selector A member function pointer with type of `SEL_ListViewEvent`.
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerListView(Ref* target, SEL_ListViewEvent selector);

    /**
     * Add an event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     *@param callback A callback function with type of `ccListViewCallback`.
     */
    void addEventListener(const ccListViewCallback& callback);
    using ScrollView::addEventListener;

    /**
     * Changes scroll direction of scrollview.
     *
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     * @param dir Set the list view's scroll direction.
     */
    virtual void setDirection(Direction dir) override;
    
    virtual std::string getDescription() const override;
    
    /**
     * @brief Refresh view and layout of ListView manually.
     * This method will mark ListView content as dirty and the content view will be refreshed in the next frame.
     * @deprecated Use method requestDoLayout() instead
     */
    CC_DEPRECATED_ATTRIBUTE void requestRefreshView();

    /**
     * @brief Refresh content view of ListView.
     * @deprecated Use method forceDoLayout() instead
     */
    CC_DEPRECATED_ATTRIBUTE void refreshView();

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void handleReleaseLogic(Touch *touch) override;

    virtual void onItemListChanged();

    virtual void remedyLayoutParameter(Widget* item);
    void updateInnerContainerSize();
    void remedyVerticalLayoutParameter(LinearLayoutParameter* layoutParameter, ssize_t itemIndex);
    void remedyHorizontalLayoutParameter(LinearLayoutParameter* layoutParameter,ssize_t itemIndex);
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent(TouchEventType event);
    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch* touch) override;
    
    virtual Vec2 getHowMuchOutOfBoundary(const Vec2& addition = Vec2::ZERO) override;
    
    virtual void startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity) override;
    
    void startMagneticScroll();
    Vec2 calculateItemDestination(const Vec2& positionRatioInView, Widget* item, const Vec2& itemAnchorPoint);
    
protected:
    Widget* _model;
    
    Vector<Widget*> _items;
    
    Gravity _gravity;
    
    MagneticType _magneticType;
    bool _magneticAllowedOutOfBoundary;
    
    float _itemsMargin;
    
    float _scrollTime;
    
    ssize_t _curSelectedIndex;

    bool _innerContainerDoLayoutDirty;
    
    Ref*       _listViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ListViewEvent    _listViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccListViewCallback _eventCallback;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__ListView__) */
