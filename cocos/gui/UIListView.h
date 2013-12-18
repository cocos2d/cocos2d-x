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


#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "gui/UIScrollView.h"

NS_CC_BEGIN

namespace gui{

typedef enum
{
    LISTVIEW_GRAVITY_LEFT,
    LISTVIEW_GRAVITY_RIGHT,
    LISTVIEW_GRAVITY_CENTER_HORIZONTAL,
    
    LISTVIEW_GRAVITY_TOP,
    LISTVIEW_GRAVITY_BOTTOM,
    LISTVIEW_GRAVITY_CENTER_VERTICAL,
}ListViewGravity;
    
typedef enum
{
    LISTVIEW_ONSELECTEDITEM
}ListViewEventType;

typedef void (Object::*SEL_ListViewEvent)(Object*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

class ListView : public ScrollView
{
    
public:
    
    /**
     * Default constructor
     */
    ListView();
    
    /**
     * Default destructor
     */
    virtual ~ListView();
    
    /**
     * Allocates and initializes.
     */
    static ListView* create();
    
    /**
     * Sets a item model for listview
     *
     * A model will be cloned for adding default item.
     *
     * @param model  item model for listview
     */
    void setItemModel(Widget* model);
    
    /**
     * Push back a default item(create by a cloned model) into listview.
     */
    void pushBackDefaultItem();
    
    /**
     * Insert a default item(create by a cloned model) into listview.
     */
    void insertDefaultItem(int index);
    
    /**
     * Push back custom item into listview.
     */
    void pushBackCustomItem(Widget* item);
    
    /**
     * Insert custom item into listview.
     */
    void insertCustomItem(Widget* item, int index);
    
    /**
     *  Removes the last item of listview.
     */
    void removeLastItem();
    
    /**
     * Removes a item whose index is same as the parameter.
     *
     * @param index of item.
     */
    void removeItem(int index);
    
    /**
     * Returns a item whose index is same as the parameter.
     *
     * @param index of item.
     *
     * @return the item widget.
     */
    Widget* getItem(unsigned int index);
    
    /**
     * Returns the item container.
     */
    Vector<Widget*>& getItems();
    
    /**
     * Returns the index of item.
     *
     * @param item  the item which need to be checked.
     *
     * @return the index of item.
     */
    unsigned int getIndex(Widget* item) const;
    
    /**
     * Changes the gravity of listview.
     * @see ListViewGravity
     */
    void setGravity(ListViewGravity gravity);
    
    /**
     * Changes the margin between each item.
     *
     * @param margin
     */
    void setItemsMargin(float margin);
    
    virtual void sortAllChildren() override;
    
    int getCurSelectedIndex() const;
    
    void addEventListenerListView(Object* target, SEL_ListViewEvent selector);
    
    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(SCROLLVIEW_DIR dir) override;
    
    virtual std::string getDescription() const override;
    
protected:
    virtual void addChild(Node* child) override{ScrollView::addChild(child);};
    virtual void addChild(Node * child, int zOrder) override{ScrollView::addChild(child, zOrder);};
    virtual void addChild(Node* child, int zOrder, int tag) override{ScrollView::addChild(child, zOrder, tag);};
    virtual void removeChild(Node* widget, bool cleanup = true) override{ScrollView::removeChild(widget, cleanup);};
    
    virtual void removeAllChildren() override{ScrollView::removeAllChildren();};
    virtual Vector<Node*>& getChildren() override{return ScrollView::getChildren();};
    virtual const Vector<Node*>& getChildren() const override{return ScrollView::getChildren();};
    virtual bool init() override;
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent();
    virtual void interceptTouchEvent(int handleState,Widget* sender,const Point &touchPoint) override;
    void refreshView();
protected:
    
    Widget* _model;
    Vector<Widget*> _items;
    ListViewGravity _gravity;
    float _itemsMargin;
    Object*       _listViewEventListener;
    SEL_ListViewEvent    _listViewEventSelector;
    int _curSelectedIndex;
    bool _refreshViewDirty;
};

}
NS_CC_END

#endif /* defined(__ListView__) */
