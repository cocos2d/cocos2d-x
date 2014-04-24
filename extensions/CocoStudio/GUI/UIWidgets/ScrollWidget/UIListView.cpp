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

#include "UIListView.h"
#include "../../System/UIHelper.h"
#include "../../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(ListView)

ListView::ListView():
_model(NULL),
_gravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL),
_itemsMargin(0.0f),
_listViewEventListener(NULL),
_listViewEventSelector(NULL),
_curSelectedIndex(0),
_refreshViewDirty(true),
_items(NULL)
{
    
}

ListView::~ListView()
{
    _listViewEventListener = NULL;
    _listViewEventSelector = NULL;
    _items->removeAllObjects();
    CC_SAFE_RELEASE(_items);
    CC_SAFE_RELEASE(_model);
}

ListView* ListView::create()
{
    ListView* widget = new ListView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool ListView::init()
{
    if (ScrollView::init())
    {
        _items = CCArray::create();
        CC_SAFE_RETAIN(_items);
        setLayoutType(LAYOUT_LINEAR_VERTICAL);
        return true;
    }
    return false;
}

void ListView::setItemModel(Widget *model)
{
    if (!model)
    {
        return;
    }
    CC_SAFE_RELEASE_NULL(_model);
    _model = model;
    CC_SAFE_RETAIN(_model);
}

void ListView::updateInnerContainerSize()
{
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            ccArray* arrayItems = _items->data;
            int length = arrayItems->num;
            float totalHeight = (length - 1) * _itemsMargin;
            for (int i=0; i<length; i++)
            {
                Widget* item = static_cast<Widget*>(arrayItems->arr[i]);
                totalHeight += item->getSize().height;
            }
            float finalWidth = _size.width;
            float finalHeight = totalHeight;
            setInnerContainerSize(CCSize(finalWidth, finalHeight));
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL:
        {
            ccArray* arrayItems = _items->data;
            int length = arrayItems->num;
            float totalWidth = (length - 1) * _itemsMargin;
            for (int i=0; i<length; i++)
            {
                Widget* item = static_cast<Widget*>(arrayItems->arr[i]);
                totalWidth += item->getSize().width;
            }
            float finalWidth = totalWidth;
            float finalHeight = _size.height;
            setInnerContainerSize(CCSize(finalWidth, finalHeight));
            break;
        }
        default:
            break;
    }
}

void ListView::remedyLayoutParameter(Widget *item)
{
    if (!item)
    {
        return;
    }
    switch (_direction) {
        case SCROLLVIEW_DIR_VERTICAL:
        {
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
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
                    defaultLp->setMargin(MarginZero);
                }
                else
                {
                    defaultLp->setMargin(Margin(0.0f, _itemsMargin, 0.0f, 0.0f));
                }
                item->setLayoutParameter(defaultLp);
            }
            else
            {
                if (getIndex(item) == 0)
                {
                    llp->setMargin(MarginZero);
                }
                else
                {
                    llp->setMargin(Margin(0.0f, _itemsMargin, 0.0f, 0.0f));
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
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
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
                    defaultLp->setMargin(MarginZero);
                }
                else
                {
                    defaultLp->setMargin(Margin(_itemsMargin, 0.0f, 0.0f, 0.0f));
                }
                item->setLayoutParameter(defaultLp);
            }
            else
            {
                if (getIndex(item) == 0)
                {
                    llp->setMargin(MarginZero);
                }
                else
                {
                    llp->setMargin(Margin(_itemsMargin, 0.0f, 0.0f, 0.0f));
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

void ListView::pushBackDefaultItem()
{
    if (!_model)
    {
        return;
    }
    Widget* newItem = _model->clone();
    _items->addObject(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void ListView::insertDefaultItem(int index)
{
    if (!_model)
    {
        return;
    }
    Widget* newItem = _model->clone();
    _items->insertObject(newItem, index);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void ListView::pushBackCustomItem(Widget* item)
{
    _items->addObject(item);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void ListView::insertCustomItem(Widget* item, int index)
{
    _items->insertObject(item, index);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void ListView::removeItem(int index)
{
    Widget* item = getItem(index);
    if (!item)
    {
        return;
    }
    _items->removeObject(item);
    removeChild(item);
    _refreshViewDirty = true;
}

void ListView::removeLastItem()
{
    removeItem(_items->count() -1);
}
    
void ListView::removeAllItems()
{
    _items->removeAllObjects();
    removeAllChildren();
}

Widget* ListView::getItem(unsigned int index)
{
    if ((int)index < 0 || index >= _items->count())
    {
        return NULL;
    }
    return static_cast<Widget*>(_items->objectAtIndex(index));
}

CCArray* ListView::getItems()
{
    return _items;
}

unsigned int ListView::getIndex(Widget *item) const
{
    if (!item)
    {
        return -1;
    }
    return _items->indexOfObject(item);
}

void ListView::setGravity(ListViewGravity gravity)
{
    if (_gravity == gravity)
    {
        return;
    }
    _gravity = gravity;
    _refreshViewDirty = true;
}

void ListView::setItemsMargin(float margin)
{
    if (_itemsMargin == margin)
    {
        return;
    }
    _itemsMargin = margin;
    _refreshViewDirty = true;
}
    
float ListView::getItemsMargin()
{
    return _itemsMargin;
}

void ListView::setDirection(SCROLLVIEW_DIR dir)
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
    ScrollView::setDirection(dir);
}
    
void ListView::requestRefreshView()
{
    _refreshViewDirty = true;
}

void ListView::refreshView()
{
    ccArray* arrayItems = getItems()->data;
    int length = arrayItems->num;
    for (int i=0; i<length; i++)
    {
        Widget* item = static_cast<Widget*>(arrayItems->arr[i]);
        item->setZOrder(i);
        remedyLayoutParameter(item);
    }
    updateInnerContainerSize();
}
    
void ListView::sortAllChildren()
{
    ScrollView::sortAllChildren();
    if (_refreshViewDirty)
    {
        refreshView();
        _refreshViewDirty = false;
    }
}
    
void ListView::addEventListenerListView(CCObject *target, SEL_ListViewEvent selector)
{
    _listViewEventListener = target;
    _listViewEventSelector = selector;
}
    
void ListView::selectedItemEvent(int state)
{
    if (_listViewEventListener && _listViewEventSelector)
    {
        switch (state)
        {
            case 0:
                (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM_START);
                break;
            default:
                (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM_END);
                break;
        }
    }
}
    
void ListView::interceptTouchEvent(int handleState, Widget *sender, const CCPoint &touchPoint)
{
    ScrollView::interceptTouchEvent(handleState, sender, touchPoint);
    if (handleState != 1)
    {
        Widget* parent = sender;
        while (parent)
        {
            if (parent && parent->getParent() == _innerContainer)
            {
                _curSelectedIndex = getIndex(parent);
                break;
            }
            parent = dynamic_cast<Widget*>(parent->getParent());
        }
        selectedItemEvent(handleState);
    }
}
    
int ListView::getCurSelectedIndex() const
{
    return _curSelectedIndex;
}

void ListView::onSizeChanged()
{
    ScrollView::onSizeChanged();
    _refreshViewDirty = true;
}

std::string ListView::getDescription() const
{
    return "ListView";
}

Widget* ListView::createCloneInstance()
{
    return ListView::create();
}

void ListView::copyClonedWidgetChildren(Widget* model)
{
    ccArray* arrayModelItems = static_cast<ListView*>(model)->getItems()->data;
    int length = arrayModelItems->num;
    for (int i=0; i<length; i++)
    {
        Widget* item = static_cast<Widget*>(arrayModelItems->arr[i]);
        pushBackCustomItem(item->clone());
    }
}

void ListView::copySpecialProperties(Widget *widget)
{
    ListView* listViewEx = dynamic_cast<ListView*>(widget);
    if (listViewEx)
    {
        ScrollView::copySpecialProperties(widget);
        setItemModel(listViewEx->_model);
        setItemsMargin(listViewEx->_itemsMargin);
        setGravity(listViewEx->_gravity);
    }
}

}
NS_CC_END