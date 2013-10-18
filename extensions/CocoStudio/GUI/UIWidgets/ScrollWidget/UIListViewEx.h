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

    void setItemModel(UIWidget* model);

    void pushBackItem();
    void insetItem(int index);
    void removeLastItem();
    void removeItemAtIndex(int index);
    UIWidget* getItemByIndex(int index);
    int indexOfItem(UIWidget* item);
    void setGravity(ListViewGravity gravity);
    void setItemsMargin(float margin);
    void refreshView();
    virtual void onSizeChanged();

    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(SCROLLVIEW_DIR dir);
protected:
    virtual bool init();
    void updateInnerContainerSize();
    void remedyLayoutParameter(UIWidget* item);
protected:

    UIWidget* m_pModel;
    CCArray* m_pItems;
    ListViewGravity m_eGravity;
    float m_fItemsMargin;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIListViewEx__) */
