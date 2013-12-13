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

#include "gui/UIListView.h"
#include "gui/UIHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace gui {

UIListView::UIListView():
_model(nullptr),
_gravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL),
_itemsMargin(0.0f),
_listViewEventListener(nullptr),
_listViewEventSelector(nullptr),
_curSelectedIndex(0),
_refreshViewDirty(true)
{
    
}

UIListView::~UIListView()
{
    _listViewEventListener = nullptr;
    _listViewEventSelector = nullptr;
}

UIListView* UIListView::create()
{
    UIListView* widget = new UIListView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool UIListView::init()
{
    if (UIScrollView::init())
    {
        setLayoutType(LAYOUT_LINEAR_VERTICAL);
        return true;
    }
    return false;
}

void UIListView::setItemModel(UIWidget *model)
{
    if (!model)
    {
        return;
    }
    CC_SAFE_RELEASE_NULL(_model);
    _model = model;
    CC_SAFE_RETAIN(_model);
}

void UIListView::updateInnerContainerSize()
{
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            int length = _items.size();
            float totalHeight = (length - 1) * _itemsMargin;
            for (int i=0; i<length; i++)
            {
                UIWidget* item = _items.at(i);
                totalHeight += item->getSize().height;
            }
            float finalWidth = _size.width;
            float finalHeight = totalHeight;
            setInnerContainerSize(Size(finalWidth, finalHeight));
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            int length = _items.size();
            float totalWidth = (length - 1) * _itemsMargin;
            for (int i=0; i<length; i++)
            {
                UIWidget* item = _items.at(i);
                totalWidth += item->getSize().width;
            }
            float finalWidth = totalWidth;
            float finalHeight = _size.height;
            setInnerContainerSize(Size(finalWidth, finalHeight));
            break;
        }
        default:
            break;
    }
}

void UIListView::remedyLayoutParameter(UIWidget *item)
{
    if (!item)
    {
        return;
    }
    switch (_direction) {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            UILinearLayoutParameter* llp = (UILinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                UILinearLayoutParameter* defaultLp = UILinearLayoutParameter::create();
                switch (_gravity) {
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
                    defaultLp->setMargin(UIMargin(0.0f, _itemsMargin, 0.0f, 0.0f));
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
                    llp->setMargin(UIMargin(0.0f, _itemsMargin, 0.0f, 0.0f));
                }
                switch (_gravity) {
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
                switch (_gravity) {
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
                    defaultLp->setMargin(UIMargin(_itemsMargin, 0.0f, 0.0f, 0.0f));
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
                    llp->setMargin(UIMargin(_itemsMargin, 0.0f, 0.0f, 0.0f));
                }
                switch (_gravity) {
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

void UIListView::pushBackDefaultItem()
{
    if (!_model)
    {
        return;
    }
    UIWidget* newItem = _model->clone();
    _items.pushBack(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void UIListView::insertDefaultItem(int index)
{
    if (!_model)
    {
        return;
    }
    UIWidget* newItem = _model->clone();
    _items.insert(index, newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void UIListView::pushBackCustomItem(UIWidget* item)
{
    _items.pushBack(item);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void UIListView::insertCustomItem(UIWidget* item, int index)
{
    _items.insert(index, item);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void UIListView::removeItem(int index)
{
    UIWidget* item = getItem(index);
    if (!item)
    {
        return;
        
    }
    _items.removeObject(item);
    removeChild(item);
    _refreshViewDirty = true;
}

void UIListView::removeLastItem()
{
    removeItem(_items.size() -1);
}

UIWidget* UIListView::getItem(unsigned int index)
{
    if ((int)index < 0 || index >= _items.size())
    {
        return nullptr;
    }
    return _items.at(index);
}

Vector<UIWidget*>& UIListView::getItems()
{
    return _items;
}

unsigned int UIListView::getIndex(UIWidget *item) const
{
    if (!item)
    {
        return -1;
    }
    return _items.getIndex(item);
}

void UIListView::setGravity(ListViewGravity gravity)
{
    if (_gravity == gravity)
    {
        return;
    }
    _gravity = gravity;
    _refreshViewDirty = true;
}

void UIListView::setItemsMargin(float margin)
{
    if (_itemsMargin == margin)
    {
        return;
    }
    _itemsMargin = margin;
    _refreshViewDirty = true;
}

void UIListView::setDirection(SCROLLVIEW_DIR dir)
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

void UIListView::refreshView()
{
    int length = _items.size();
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(_items.at(i));
        item->setZOrder(i);
        remedyLayoutParameter(item);
    }
    updateInnerContainerSize();
}
    
void UIListView::sortAllChildren()
{
    UIScrollView::sortAllChildren();
    if (_refreshViewDirty)
    {
        refreshView();
        _refreshViewDirty = false;
    }
}
    
void UIListView::addEventListenerListView(Object *target, SEL_ListViewEvent selector)
{
    _listViewEventListener = target;
    _listViewEventSelector = selector;
}
    
void UIListView::selectedItemEvent()
{
    if (_listViewEventListener && _listViewEventSelector)
    {
        (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM);
    }
}
    
void UIListView::interceptTouchEvent(int handleState, gui::UIWidget *sender, const Point &touchPoint)
{
    UIScrollView::interceptTouchEvent(handleState, sender, touchPoint);
    if (handleState != 1)
    {
        UIWidget* parent = sender;
        while (parent)
        {
            if (parent && parent->getParent() == _innerContainer)
            {
                _curSelectedIndex = getIndex(parent);
                break;
            }
            parent = dynamic_cast<UIWidget*>(parent->getParent());
        }
        selectedItemEvent();
    }
}
    
int UIListView::getCurSelectedIndex() const
{
    return _curSelectedIndex;
}

void UIListView::onSizeChanged()
{
    UIScrollView::onSizeChanged();
    _refreshViewDirty = true;
}

const char* UIListView::getDescription() const
{
    return "ListViewEx";
}

UIWidget* UIListView::createCloneInstance()
{
    return UIListView::create();
}

void UIListView::copyClonedWidgetChildren(UIWidget* model)
{
    Vector<UIWidget*> arrayItems = getItems();
    
    int length = arrayItems.size();
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(arrayItems.at(i));
        pushBackCustomItem(item->clone());
    }
}

void UIListView::copySpecialProperties(UIWidget *widget)
{
    UIListView* listViewEx = dynamic_cast<UIListView*>(widget);
    if (listViewEx)
    {
        UIScrollView::copySpecialProperties(widget);
        setItemModel(listViewEx->_model);
        setItemsMargin(listViewEx->_itemsMargin);
        setGravity(listViewEx->_gravity);
    }
}

}
NS_CC_END