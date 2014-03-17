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

#include "UIScrollView.h"

NS_CC_BEGIN

namespace ui{

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
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}ListViewEventType;

typedef void (CCObject::*SEL_ListViewEvent)(CCObject*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

class ListView : public ScrollView
{
    
    DECLARE_CLASS_GUI_INFO
    
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
    
    void removeAllItems();
    
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
    CCArray* getItems();
    
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
    
    float getItemsMargin();
    
    virtual void sortAllChildren();
    
    int getCurSelectedIndex() const;
    
    void addEventListenerListView(CCObject* target, SEL_ListViewEvent selector);
    
    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(SCROLLVIEW_DIR dir);
    
    virtual std::string getDescription() const;
    
    void requestRefreshView();
    
    void refreshView();
protected:
    virtual void addChild(CCNode* child) {ScrollView::addChild(child);};
    virtual void addChild(CCNode * child, int zOrder) {ScrollView::addChild(child, zOrder);};
    virtual void addChild(CCNode* child, int zOrder, int tag) {ScrollView::addChild(child, zOrder, tag);};
    virtual void removeChild(CCNode* widget) {ScrollView::removeChild(widget);};
    virtual void removeChild(CCNode* widget, bool cleanup) {ScrollView::removeChild(widget, cleanup);};
    
    virtual void removeAllChildren() {ScrollView::removeAllChildren();};
    virtual void removeAllChildrenWithCleanup(bool cleanup) {ScrollView::removeAllChildrenWithCleanup(cleanup);};
    virtual CCArray* getChildren() {return ScrollView::getChildren();};
    virtual unsigned int getChildrenCount() const {return ScrollView::getChildrenCount();};
    virtual CCNode * getChildByTag(int tag) {return ScrollView::getChildByTag(tag);};
    virtual Widget* getChildByName(const char* name) {return ScrollView::getChildByName(name);};
    virtual bool init();
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    virtual void onSizeChanged();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    void selectedItemEvent(int state);
    virtual void interceptTouchEvent(int handleState,Widget* sender,const CCPoint &touchPoint);
protected:
    
    Widget* _model;
    ListViewGravity _gravity;
    float _itemsMargin;
    CCObject*       _listViewEventListener;
    SEL_ListViewEvent    _listViewEventSelector;
    int _curSelectedIndex;
    bool _refreshViewDirty;
    CCArray* _items;
};

}
NS_CC_END

#endif /* defined(__ListView__) */
