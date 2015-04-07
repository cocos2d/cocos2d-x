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
     * Set a item model for listview.
     *
     * When calling `pushBackDefaultItem`, the model will be used as a blueprint and new model copy will be inserted into ListView.
     * @param model  Model in `Widget*`.
     */
    void setItemModel(Widget* model);
    
    /**
     * Insert a  a default item(create by a cloned model) at the end of the listview.
     */
    void pushBackDefaultItem();
    
    /**
     * Insert a default item(create by cloning model) into listview at a give index.
     *@param index  A index in ssize_t.
     */
    void insertDefaultItem(ssize_t index);
    
    /**
     * Insert a  custom item into the end of ListView.
     *@param item A item in `Widget*`.
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
     * Remove a item at given index.
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
     * Return a item at a given index.
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
     * Set the margin between each item in ListView.
     *
     * @param margin
     */
    void setItemsMargin(float margin);
    
    
    /**
     * @brief Query margin between each item in ListView.
     *
     
     * @return A margin in float.
     */
    float getItemsMargin()const;
    
    //override methods
    virtual void forceDoLayout()override;
    virtual void doLayout() override;
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleaup = true) override;
    
        
    /**
     * @brief Query current selected widget's idnex.
     *
     
     * @return A index of a selected item.
     */
    ssize_t getCurSelectedIndex() const;
    
    /**
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     *@deprecated Use  `addEventListener` instead.
     *@param target A pointer of `Ref*` type.
     *@param selector A member function pointer with type of `SEL_ListViewEvent`.
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerListView(Ref* target, SEL_ListViewEvent selector);

    /**
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
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
     * This method will mark ListView content as dirty and the content view will be refershed in the next frame.
     */
    void requestRefreshView();

    
    /**
     * @brief Refresh content view of ListView.
     */
    void refreshView();

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    void remedyVerticalLayoutParameter(LinearLayoutParameter* layoutParameter, ssize_t itemIndex);
    void remedyHorizontalLayoutParameter(LinearLayoutParameter* layoutParameter,ssize_t itemIndex);
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent(TouchEventType event);
    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch* touch) override;
protected:
    Widget* _model;
    
    Vector<Widget*> _items;
    
    Gravity _gravity;
    
    float _itemsMargin;
    
    ssize_t _curSelectedIndex;
    bool _refreshViewDirty;
    
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
