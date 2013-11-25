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

namespace gui {

UIListView::UIListView():
_model(nullptr),
_items(nullptr),
_gravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL),
_itemsMargin(0.0f),
_listViewEventListener(nullptr),
_listViewEventSelector(nullptr),
_curSelectedIndex(0)
{
    
}

UIListView::~UIListView()
{
    _items->removeAllObjects();
    CC_SAFE_RELEASE(_items);
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
        _items = cocos2d::Array::create();
        CC_SAFE_RETAIN(_items);
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
    if (!_model)
    {
        return;
    }
    switch (_direction) {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            int childrenCount = _items->count();
            float totalHeight = _model->getSize().height * childrenCount + (childrenCount - 1) * _itemsMargin;
            float finalWidth = _size.width;
            float finalHeight = totalHeight;
            setInnerContainerSize(cocos2d::Size(finalWidth, finalHeight));
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            int childrenCount = _items->count();
            float totalWidth = _model->getSize().width * childrenCount + (childrenCount - 1) * _itemsMargin;
            float finalWidth = totalWidth;
            float finalHeight = _size.height;
            setInnerContainerSize(cocos2d::Size(finalWidth, finalHeight));
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
    _items->addObject(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListView::insertDefaultItem(int index)
{
    if (!_items)
    {
        return;
    }
    if (!_model)
    {
        return;
    }
    UIWidget* newItem = _model->clone();
    _items->insertObject(newItem, index);
    remedyLayoutParameter(newItem);
    addChild(newItem);
}

void UIListView::pushBackCustomItem(UIWidget* item)
{
    _items->addObject(item);
    remedyLayoutParameter(item);
    addChild(item);
}

void UIListView::insertCustomItem(UIWidget* item, int index)
{
    _items->insertObject(item, index);
    remedyLayoutParameter(item);
    addChild(item);
}

void UIListView::removeItem(int index)
{
    if (!_items)
    {
        return;
    }
    UIWidget* item = getItem(index);
    if (!item)
    {
        return;
        
    }
    _items->removeObject(item);
    removeChild(item);
}

void UIListView::removeLastItem()
{
    removeItem(_items->count() -1);
}

UIWidget* UIListView::getItem(unsigned int index)
{
    if ((int)index < 0 || index >= _items->count())
    {
        return nullptr;
    }
    return (UIWidget*)(_items->data->arr[index]);
}

cocos2d::Array* UIListView::getItems()
{
    return _items;
}

unsigned int UIListView::getIndex(UIWidget *item) const
{
    if (!_items)
    {
        return -1;
    }
    if (!item)
    {
        return -1;
    }
    return _items->getIndexOfObject(item);
}

void UIListView::setGravity(ListViewGravity gravity)
{
    if (_gravity == gravity)
    {
        return;
    }
    _gravity = gravity;
    refreshView();
}

void UIListView::setItemsMargin(float margin)
{
    if (_itemsMargin == margin)
    {
        return;
    }
    _itemsMargin = margin;
    refreshView();
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
    if (!_items)
    {
        return;
    }
    cocos2d::ccArray* arrayItems = _items->data;
    int length = arrayItems->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(arrayItems->arr[i]);
        item->setZOrder(i);
        remedyLayoutParameter(item);
    }
    updateInnerContainerSize();
}
    
void UIListView::addEventListenerListView(cocos2d::Object *target, SEL_ListViewEvent selector)
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
    
void UIListView::interceptTouchEvent(int handleState, gui::UIWidget *sender, const cocos2d::Point &touchPoint)
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
            parent = parent->getParent();
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
    refreshView();
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
    cocos2d::ccArray* arrayItems = dynamic_cast<UIListView*>(model)->getItems()->data;
    int length = arrayItems->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* item = (UIWidget*)(arrayItems->arr[i]);
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
