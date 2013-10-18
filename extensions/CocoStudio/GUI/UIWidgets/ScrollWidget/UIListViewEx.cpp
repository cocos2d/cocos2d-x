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

#include "UIListViewEx.h"
#include "../../System/UIHelper.h"
#include "../../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

UIListViewEx::UIListViewEx():
m_pModel(NULL),
m_pItems(NULL),
m_eGravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL),
m_fItemsMargin(0.0f)
{
    
}

UIListViewEx::~UIListViewEx()
{
    m_pItems->removeAllObjects();
    CC_SAFE_RELEASE(m_pItems);
}

UIListViewEx* UIListViewEx::create()
{
    UIListViewEx* widget = new UIListViewEx();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIListViewEx::init()
{
    if (UIScrollView::init())
    {
        m_pItems = CCArray::create();
        CC_SAFE_RETAIN(m_pItems);
        setLayoutType(LAYOUT_LINEAR_VERTICAL);
        return true;
    }
    return false;
}

void UIListViewEx::setItemModel(UIWidget *model)
{
    if (!model)
    {
        return;
    }
    CC_SAFE_RELEASE_NULL(m_pModel);
    m_pModel = model;
    CC_SAFE_RETAIN(m_pModel);
}

void UIListViewEx::updateInnerContainerSize()
{
    if (!m_pModel)
    {
        return;
    }
    switch (m_eDirection) {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            int childrenCount = m_pItems->count();
            float totalHeight = m_pModel->getSize().height * childrenCount + (childrenCount - 1) * m_fItemsMargin;
            float finalWidth = m_size.width;
            float finalHeight = totalHeight;
            setInnerContainerSize(CCSizeMake(finalWidth, finalHeight));
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            int childrenCount = m_pItems->count();
            float totalWidth = m_pModel->getSize().width * childrenCount + (childrenCount - 1) * m_fItemsMargin;
            float finalWidth = totalWidth;
            float finalHeight = m_size.height;
            setInnerContainerSize(CCSizeMake(finalWidth, finalHeight));
            break;
        }
        default:
            break;
    }
}

void UIListViewEx::remedyLayoutParameter(UIWidget *item)
{
    if (!item)
    {
        return;
    }
    switch (m_eDirection) {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
                switch (m_eGravity) {
                    case LISTVIEW_GRAVITY_LEFT:
                        defaultLp->setGravity(LINEAR_GRAVITY_LEFT);
                        break;
                    case LISTVIEW_GRAVITY_RIGHT:
                        defaultLp->setGravity(LINEAR_GRAVITY_RIGHT);
                        break;
                    case LISTVIEW_GRAVITY_CENTER_HORIZONTAL:
                        defaultLp->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
                        break;
                    default:
                        break;
                }
                if (indexOfItem(item) == 0)
                {
                    defaultLp->setMargin(UIMarginZero);
                }
                else
                {
                    defaultLp->setMargin(UIMargin(0.0f, m_fItemsMargin, 0.0f, 0.0f));
                }
                item->setLayoutParameter(defaultLp);
            }
            else
            {
                if (indexOfItem(item) == 0)
                {
                    llp->setMargin(UIMarginZero);
                }
                else
                {
                    llp->setMargin(UIMargin(0.0f, m_fItemsMargin, 0.0f, 0.0f));
                }
                switch (m_eGravity) {
                    case LISTVIEW_GRAVITY_LEFT:
                        llp->setGravity(LINEAR_GRAVITY_LEFT);
                        break;
                    case LISTVIEW_GRAVITY_RIGHT:
                        llp->setGravity(LINEAR_GRAVITY_RIGHT);
                        break;
                    case LISTVIEW_GRAVITY_CENTER_HORIZONTAL:
                        llp->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
                switch (m_eGravity) {
                    case LISTVIEW_GRAVITY_TOP:
                        defaultLp->setGravity(LINEAR_GRAVITY_TOP);
                        break;
                    case LISTVIEW_GRAVITY_BOTTOM:
                        defaultLp->setGravity(LINEAR_GRAVITY_BOTTOM);
                        break;
                    case LISTVIEW_GRAVITY_CENTER_VERTICAL:
                        defaultLp->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
                        break;
                    default:
                        break;
                }
                if (indexOfItem(item) == 0)
                {
                    defaultLp->setMargin(UIMarginZero);
                }
                else
                {
                    defaultLp->setMargin(UIMargin(m_fItemsMargin, 0.0f, 0.0f, 0.0f));
                }
                item->setLayoutParameter(defaultLp);
            }
            else
            {
                if (indexOfItem(item) == 0)
                {
                    llp->setMargin(UIMarginZero);
                }
                else
                {
                    llp->setMargin(UIMargin(m_fItemsMargin, 0.0f, 0.0f, 0.0f));
                }
                switch (m_eGravity) {
                    case LISTVIEW_GRAVITY_TOP:
                        llp->setGravity(LINEAR_GRAVITY_TOP);
                        break;
                    case LISTVIEW_GRAVITY_BOTTOM:
                        llp->setGravity(LINEAR_GRAVITY_BOTTOM);
                        break;
                    case LISTVIEW_GRAVITY_CENTER_VERTICAL:
                        llp->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        default:
            break;
    }
    
}

void UIListViewEx::pushBackItem()
{
    if (!m_pModel)
    {
        return;
    }
    UIWidget* newItem = CCUIHELPER->cloneWidget(m_pModel);
    m_pItems->addObject(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListViewEx::insetItem(int index)
{
    UIWidget* newItem = CCUIHELPER->cloneWidget(m_pModel);
    m_pItems->insertObject(newItem, index);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListViewEx::removeItemAtIndex(int index)
{
    if (!m_pItems)
    {
        return;
    }
    UIWidget* item = getItemByIndex(index);
    if (!item)
    {
        return;
    
    }
    m_pItems->removeObject(item);
    removeChild(item);
}

void UIListViewEx::removeLastItem()
{
    removeItemAtIndex(m_pItems->count() -1);
}

UIWidget* UIListViewEx::getItemByIndex(int index)
{
    if (index < 0 || index >= m_pItems->count())
    {
        return NULL;
    }
    return (UIWidget*)(m_pItems->data->arr[index]);
}

int UIListViewEx::indexOfItem(UIWidget *item)
{
    if (!m_pItems)
    {
        return -1;
    }
    if (!item)
    {
        return -1;
    }
    return m_pItems->indexOfObject(item);
}

void UIListViewEx::setGravity(ListViewGravity gravity)
{
    if (m_eGravity == gravity)
    {
        return;
    }
    m_eGravity = gravity;
    refreshView();
}

void UIListViewEx::setItemsMargin(float margin)
{
    if (m_fItemsMargin == margin)
    {
        return;
    }
    m_fItemsMargin = margin;
    refreshView();
}

void UIListViewEx::setDirection(SCROLLVIEW_DIR dir)
{
    UIScrollView::setDirection(dir);
    setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
}

void UIListViewEx::refreshView()
{
    if (!m_pItems)
    {
        return;
    }
    ccArray* arrayItems = m_pItems->data;
    int length = arrayItems->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(arrayItems->arr[i]);
        item->setZOrder(i);
        remedyLayoutParameter(item);
    }
    updateInnerContainerSize();
    doLayout();
}

void UIListViewEx::onSizeChanged()
{
    dynamic_cast<RectClippingNode*>(m_pRenderer)->setClippingSize(m_size);
    if (m_pBackGroundImage)
    {
        m_pBackGroundImage->setPosition(ccp(m_size.width/2.0f, m_size.height/2.0f));
        if (m_bBackGroundScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setPreferredSize(m_size);
        }
    }
    if (m_pColorRender)
    {
        m_pColorRender->setContentSize(m_size);
    }
    if (m_pGradientRender)
    {
        m_pGradientRender->setContentSize(m_size);
    }
    m_fTopBoundary = m_size.height;
    m_fRightBoundary = m_size.width;
    CCSize innerSize = m_pInnerContainer->getSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, m_size.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, m_size.height);
    m_pInnerContainer->setSize(CCSizeMake(innerSizeWidth, innerSizeHeight));
    m_pInnerContainer->setPosition(ccp(0, m_size.height - m_pInnerContainer->getSize().height));
    refreshView();
}

NS_CC_EXT_END
