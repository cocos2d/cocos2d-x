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
m_fItemsMargin(0.0f),
_listViewEventListener(NULL),
_listViewEventSelector(NULL),
_curSelectedIndex(0)
{
    
}

UIListViewEx::~UIListViewEx()
{
    m_pItems->removeAllObjects();
    CC_SAFE_RELEASE(m_pItems);
    _listViewEventListener = NULL;
    _listViewEventSelector = NULL;
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
            UILinearLayoutParameter* llp = (UILinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                UILinearLayoutParameter* defaultLp = UILinearLayoutParameter::create();
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
                if (getIndex(item) == 0)
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
                if (getIndex(item) == 0)
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
            UILinearLayoutParameter* llp = (UILinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                UILinearLayoutParameter* defaultLp = UILinearLayoutParameter::create();
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
                if (getIndex(item) == 0)
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
                if (getIndex(item) == 0)
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

void UIListViewEx::pushBackDefaultItem()
{
    if (!m_pModel)
    {
        return;
    }
    UIWidget* newItem = m_pModel->clone();
    m_pItems->addObject(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListViewEx::insertDefaultItem(int index)
{
    if (!m_pItems)
    {
        return;
    }
    if (!m_pModel)
    {
        return;
    }
    UIWidget* newItem = m_pModel->clone();
    m_pItems->insertObject(newItem, index);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListViewEx::pushBackCustomItem(UIWidget* item)
{
    m_pItems->addObject(item);
    remedyLayoutParameter(item);
    addChild(item);
}

void UIListViewEx::insertCustomItem(UIWidget* item, int index)
{
    m_pItems->insertObject(item, index);
    remedyLayoutParameter(item);
    addChild(item);
}

void UIListViewEx::removeItem(int index)
{
    if (!m_pItems)
    {
        return;
    }
    UIWidget* item = getItem(index);
    if (!item)
    {
        return;
    
    }
    m_pItems->removeObject(item);
    removeChild(item);
}

void UIListViewEx::removeLastItem()
{
    removeItem(m_pItems->count() -1);
}

UIWidget* UIListViewEx::getItem(unsigned int index)
{
    if ((int)index < 0 || index >= m_pItems->count())
    {
        return NULL;
    }
    return (UIWidget*)(m_pItems->data->arr[index]);
}

CCArray* UIListViewEx::getItems()
{
    return m_pItems;
}

unsigned int UIListViewEx::getIndex(UIWidget *item) const
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
    switch (dir)
    {
        case SCROLLVIEW_DIR_VERTICAL:
            setLayoutType(LAYOUT_LINEAR_VERTICAL);
            break;
        case SCROLLVIEW_DIR_HORIZONTAL:
            setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
            break;
        case SCROLLVIEW_DIR_BOTH:
            return;
        default:
            return;
            break;
    }
    UIScrollView::setDirection(dir);
    
}

void UIListViewEx::addEventListenerListViewEx(cocos2d::CCObject *target, SEL_ListViewExEvent selector)
{
    _listViewEventListener = target;
    _listViewEventSelector = selector;
}

void UIListViewEx::selectedItemEvent()
{
    if (_listViewEventListener && _listViewEventSelector)
    {
        (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEWEX_ONSELECTEDITEM);
    }
}

void UIListViewEx::interceptTouchEvent(int handleState, UIWidget *sender, const cocos2d::CCPoint &touchPoint)
{
    UIScrollView::interceptTouchEvent(handleState, sender, touchPoint);
    if (handleState != 1)
    {
        UIWidget* parent = sender;
        while (parent)
        {
            if (parent && parent->getParent() == m_pInnerContainer)
            {
                _curSelectedIndex = getIndex(parent);
                break;
            }
            parent = parent->getParent();
        }
        selectedItemEvent();
    }
}

int UIListViewEx::getCurSelectedIndex() const
{
    return _curSelectedIndex;
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
}

void UIListViewEx::onSizeChanged()
{
    UIScrollView::onSizeChanged();
    refreshView();
}

const char* UIListViewEx::getDescription() const
{
    return "ListViewEx";
}

UIWidget* UIListViewEx::createCloneInstance()
{
    return UIListViewEx::create();
}

void UIListViewEx::copyClonedWidgetChildren(UIWidget* model)
{
    ccArray* arrayItems = dynamic_cast<UIListViewEx*>(model)->getItems()->data;
    int length = arrayItems->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(arrayItems->arr[i]);
        pushBackCustomItem(item->clone());
    }
}

void UIListViewEx::copySpecialProperties(UIWidget *widget)
{
    UIListViewEx* listViewEx = dynamic_cast<UIListViewEx*>(widget);
    if (listViewEx)
    {
        UIScrollView::copySpecialProperties(widget);
        setItemModel(listViewEx->m_pModel);
        setItemsMargin(listViewEx->m_fItemsMargin);
        setGravity(listViewEx->m_eGravity);
    }
}

NS_CC_EXT_END
