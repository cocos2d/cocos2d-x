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
 * @~english
 * ListView click item event type.
 * @~chinese 
 * ListView点击事件类型。
 */
typedef enum
{
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}ListViewEventType;

/**
 * @~english
 * A callback which would be called when a ListView item is clicked.
 * @~chinese 
 * ListView被点击的时候，调用的回调函数
 * @deprecated @~english Use `ccListViewCallback` instead.
 * @~chinese 请使用ccListViewCallback代替。
 */
typedef void (Ref::*SEL_ListViewEvent)(Ref*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

/**
 * @brief @~english ListView is a view group that displays a list of scrollable items.
 * The list items are inserted to the list by using `addChild` or  `insertDefaultItem`.
 * @~chinese ListView控件是一个显示滚动项目列表的视图组。
 * 列表项是通过使用`addChild`或`insertDefaultItem`插入到列表中的。
 * @warning @~english The list item in ListView doesn't support cell reuse at the moment, if you have a large amount of data need to be displayed, use  `TableView` instead.
 * ListView is a subclass of  `ScrollView`, so it shares many features of ScrollView.
 * @~chinese 在ListView控件列表项不支持复用节点，如果你有大量的数据需要显示，请使用`TableView`代替。
 * ListView控件是ScrollView的子类，所以它继承了ScrollView的特点。
 */
class CC_GUI_DLL ListView : public ScrollView
{
 
    DECLARE_CLASS_GUI_INFO
public:

    /**
     * @~english
     * Gravity for docking elements in ListView.
     * @~chinese 
     * ListView的停靠元素引力的方向
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
     * @~english
     * ListView element item click event.
     * @~chinese 
     * ListView控件元素的点击事件类型
     */
    enum class EventType
    {
        ON_SELECTED_ITEM_START,
        ON_SELECTED_ITEM_END
    };
    
    /**
     * @~english
     * ListView item click callback.
     * @~chinese 
     * ListView控件元素的点击回调。
     */
    typedef std::function<void(Ref*, EventType)> ccListViewCallback;
    
    /**
     * @~english
     * Default constructor
     * @~chinese 
     * 默认构造函数
     * @js ctor
     * @lua new
     */
    ListView();
    
    /**
     * @~english
     * Default destructor
     * @~chinese 
     * 默认的析构函数
     * @js NA
     * @lua NA
     */
    virtual ~ListView();
    
    /**
     * @~english
     * Create an empty ListView.
     * @~chinese 
     * 创建一个空ListView
     * @return @~english A ListView instance.
     * @~chinese 一个ListView实例。
     */
    static ListView* create();
    
    /**
     * @~english
     * Set a item model for listview.
     * When calling `pushBackDefaultItem`, the model will be used as a blueprint and new model copy will be inserted into ListView.
     *
     * @~chinese 
     * 设定一个ListView的模型。
     * 当调用`pushBackDefaultItem`，该模型将作为一个蓝图，新副本将被插入到ListView控件。
     *
     * @param model  @~english Model in `Widget*`.
     * @~chinese Widget的模型
     */
    void setItemModel(Widget* model);
    
    /**
     * @~english
     * Insert a default item(create by a cloned model) at the end of the listview.
     * @~chinese 
     * 插入一个默认项（通过克隆模式创建）到ListView的尾部。
     */
    void pushBackDefaultItem();
    
    /**
     * @~english
     * Insert a default item(create by cloning model) into listview at a give index.
     * @~chinese 
     * 插入一个默认项（通过克隆模式创建）到ListView的指定位置。
     * @param index  @~english A index in ssize_t.
     * @~chinese 指定的位置索引
     */
    void insertDefaultItem(ssize_t index);
    
    /**
     * @~english
     * Insert a custom item into the end of ListView.
     * @~chinese 
     * 插入一个自定义项到ListView的尾部。
     * @param item @~english A item in `Widget*`.
     * @~chinese 一个`Widget*`项目
     */
    void pushBackCustomItem(Widget* item);
    
    
    /**
     * @brief @~english Insert a custom widget into ListView at a given index.
     * @~chinese 插入自定义窗口小控件到ListView中指定索引处。
     * 
     * @param item @~english A widget pointer to be inserted.
     * @~chinese 要插入的一个小控件指针。
     *
     * @param index @~english A given index in ssize_t.
     * @~chinese 指定索引
     */
    void insertCustomItem(Widget* item, ssize_t index);
    
    /**
     * @~english
     *  Removes the last item of ListView.
     * @~chinese 
     * 删除ListView最后一个项目
     */
    void removeLastItem();
    
    /**
     * @~english
     * Remove a item at given index.
     *
     * @~chinese 
     * 在给定索引处删除一个项目
     * 
     * @param index @~english A given index in ssize_t.
     * @~chinese 给定索引
     */
    void removeItem(ssize_t index);
    
    
    /**
     * @brief @~english Remove all items in current ListView.
     * @~chinese 删除当前ListView中的所有项目。
     */
    void removeAllItems();
    
    /**
     * @~english
     * Return a item at a given index.
     *
     * @~chinese 
     * 返回一个给定的索引处的项目。
     * 
     * @param index @~english A given index in ssize_t.
     * @~chinese 给定的索引
     *
     * @return @~english A widget instance.
     * @~chinese 一个小控件实例。
     */
    Widget* getItem(ssize_t index)const;
    
    /**
     * @~english
     * Return all items in a ListView.
     * @~chinese 
     * 返回ListView中的所有项目。
     *
     * @returns @~english A vector of widget pointers.
     * @~chinese 一个控件指针数组。
     */
    Vector<Widget*>& getItems();
    
    /**
     * @~english
     * Return the index of specified widget.
     *
     * @~chinese 
     * 返回指定窗口小控件的索引。
     * 
     * @param item  @~english A widget pointer.
     * @~chinese 一个控件指针。
     * @return @~english The index of a given widget in ListView.
     * @~chinese 给定控件在ListView的索引。
     */
    ssize_t getIndex(Widget* item) const;
    
    /**
     * @~english
     * Set the gravity of ListView.
     * @~chinese 
     * 设置的ListView引力。
     * @see `ListViewGravity`
     */
    void setGravity(Gravity gravity);
    
    /**
     * @~english
     * Set the margin between each item in ListView.
     *
     * @~chinese 
     * 设置ListView中每一项之间的边距。
     * 
     * @param @~english margin
     * @~chinese 边距
     */
    void setItemsMargin(float margin);
    
    
    /**
     * @brief @~english Query margin between each item in ListView.
     *
     * @~chinese 查询ListView每个项之间的边距。
     *
     * @return @~english A margin in float.
     * @~chinese 一个边距浮点数
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
     * @brief @~english Query current selected widget's index.
     * @~chinese 查询当前选中控件的索引。
     *
     * @return @~english A index of a selected item.
     * @~chinese 选中的控件的索引。
     */
    ssize_t getCurSelectedIndex() const;
    
    /**
     * @~english
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     * @~chinese 
     * 添加ListView点击事件的回调，ListView中的一个项目被点击将会调用回调函数。
     * @deprecated @~english Use  `addEventListener` instead.
     * @~chinese 使用addEventListener代替。
     * @param target @~english A pointer of `Ref*` type.
     * @~chinese 一个`Ref*`指针
     * @param selector @~english A member function pointer with type of `SEL_ListViewEvent`.
     * @~chinese `SEL_ListViewEvent`类型的成员函数指针。
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerListView(Ref* target, SEL_ListViewEvent selector);

    /**
     * @~english
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     * @~chinese 
     * 添加ListView点击事件的回调，ListView中的一个项目被点击将会调用回调函数。
     * @param callback @~english A callback function with type of `ccListViewCallback`.
     * @~chinese 一个ccListViewCallback类型的回调函数。
     */
    void addEventListener(const ccListViewCallback& callback);
    using ScrollView::addEventListener;

    /**
     * @~english
     * Changes scroll direction of ListView.
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     *
     * @~chinese 
     * 改变ListView的滚动方向。
     * Direction Direction::VERTICAL意味着垂直滚动,Direction::HORIZONTAL意味着水平滚动。
     *
     * @param dir @~english Set the list view's scroll direction.
     * @~chinese 设置ListView的滚动方向。
     */
    virtual void setDirection(Direction dir) override;
    
    virtual std::string getDescription() const override;
    
    /**
     * @brief @~english Refresh view and layout of ListView manually.
     * This method will mark ListView content as dirty and the content view will be refreshed in the next frame.
     * @~chinese 手动刷新view和ListView的布局。
     * 该方法将列表视图内容标记为dirty，内容视图将在下一帧刷新。
     */
    void requestRefreshView();

    
    /**
     * @brief @~english Refresh content view of ListView.
     * @~chinese 更新ListView的视图。
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
