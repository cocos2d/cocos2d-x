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


#ifndef __TestCpp__UIListViewEx__
#define __TestCpp__UIListViewEx__

#include "UIScrollView.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LISTVIEWEX_ONSELECTEDITEM
}ListViewExEventType;

typedef void (cocos2d::CCObject::*SEL_ListViewExEvent)(cocos2d::CCObject*,ListViewExEventType);
#define listviewexeventselector(_SELECTOR) (SEL_ListViewExEvent)(&_SELECTOR)

typedef enum
{
    LISTVIEW_GRAVITY_LEFT,
    LISTVIEW_GRAVITY_RIGHT,
    LISTVIEW_GRAVITY_CENTER_HORIZONTAL,
    
    LISTVIEW_GRAVITY_TOP,
    LISTVIEW_GRAVITY_BOTTOM,
    LISTVIEW_GRAVITY_CENTER_VERTICAL,
}ListViewGravity;

class UIListViewEx : public UIScrollView
{
    
public:

    /**
     * Default constructor
     */
    UIListViewEx();
    
    /**
     * Default destructor
     */
    virtual ~UIListViewEx();
    
    /**
     * Allocates and initializes.
     */
    static UIListViewEx* create();

    /**
     * Sets a item model for listview
     *
     * A model will be cloned for adding default item.
     *
     * @param model  item model for listview
     */
    void setItemModel(UIWidget* model);

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
    void pushBackCustomItem(UIWidget* item);
    
    /**
     * Insert custom item into listview.
     */
    void insertCustomItem(UIWidget* item, int index);
    
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
    UIWidget* getItem(unsigned int index);
    
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
    unsigned int getIndex(UIWidget* item) const;
    
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
    
    /**
     * Refresh the view of list.
     *
     * If you change the data, you need to call this mathod.
     */
    void refreshView();
    
    int getCurSelectedIndex() const;
    
    void addEventListenerListViewEx(cocos2d::CCObject* target, SEL_ListViewExEvent selector);

    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(SCROLLVIEW_DIR dir);
    
    virtual const char* getDescription() const;

protected:
    virtual bool addChild(UIWidget* widget){return UIScrollView::addChild(widget);};
    virtual bool removeChild(UIWidget* widget){return UIScrollView::removeChild(widget);};
    virtual void removeAllChildren(){UIScrollView::removeAllChildren();};
    virtual CCArray* getChildren(){return UIScrollView::getChildren();};
    virtual bool init();
    void updateInnerContainerSize();
    void remedyLayoutParameter(UIWidget* item);
    virtual void onSizeChanged();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
    virtual void copyClonedWidgetChildren(UIWidget* model);
    void selectedItemEvent();
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const cocos2d::CCPoint &touchPoint);
protected:

    UIWidget* m_pModel;
    CCArray* m_pItems;
    ListViewGravity m_eGravity;
    float m_fItemsMargin;
    cocos2d::CCObject*       _listViewEventListener;
    SEL_ListViewExEvent    _listViewEventSelector;
    int _curSelectedIndex;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIListViewEx__) */
