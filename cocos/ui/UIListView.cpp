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

#include "ui/UIListView.h"
#include "ui/UIHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(ListView)

ListView::ListView():
_model(nullptr),
_gravity(Gravity::CENTER_VERTICAL),
_itemsMargin(0.0f),
_listViewEventListener(nullptr),
_listViewEventSelector(nullptr),
_curSelectedIndex(0),
_refreshViewDirty(true),
_eventCallback(nullptr)
{
    
}

ListView::~ListView()
{
    _listViewEventListener = nullptr;
    _listViewEventSelector = nullptr;
    _items.clear();
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
    return nullptr;
}

bool ListView::init()
{
    if (ScrollView::init())
    {
        setLayoutType(Type::VERTICAL);
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
        case Direction::VERTICAL:
        {
            size_t length = _items.size();
            float totalHeight = (length - 1) * _itemsMargin;
            for (auto& item : _items)
            {
                totalHeight += item->getSize().height;
            }
            float finalWidth = _size.width;
            float finalHeight = totalHeight;
            setInnerContainerSize(Size(finalWidth, finalHeight));
            break;
        }
        case Direction::HORIZONTAL:
        {
            size_t length = _items.size();
            float totalWidth = (length - 1) * _itemsMargin;
            for (auto& item : _items)
            {
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

void ListView::remedyLayoutParameter(Widget *item)
{
    if (!item)
    {
        return;
    }
    switch (_direction) {
        case Direction::VERTICAL:
        {
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LayoutParameter::Type::LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
                switch (_gravity) {
                    case Gravity::LEFT:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::LEFT);
                        break;
                    case Gravity::RIGHT:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::RIGHT);
                        break;
                    case Gravity::CENTER_HORIZONTAL:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
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
                    case Gravity::LEFT:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::LEFT);
                        break;
                    case Gravity::RIGHT:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::RIGHT);
                        break;
                    case Gravity::CENTER_HORIZONTAL:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        case Direction::HORIZONTAL:
        {
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter(LayoutParameter::Type::LINEAR));
            if (!llp)
            {
                LinearLayoutParameter* defaultLp = LinearLayoutParameter::create();
                switch (_gravity) {
                    case Gravity::TOP:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::TOP);
                        break;
                    case Gravity::BOTTOM:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::BOTTOM);
                        break;
                    case Gravity::CENTER_VERTICAL:
                        defaultLp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
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
                    case Gravity::TOP:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::TOP);
                        break;
                    case Gravity::BOTTOM:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::BOTTOM);
                        break;
                    case Gravity::CENTER_VERTICAL:
                        llp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
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
    _items.pushBack(newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void ListView::insertDefaultItem(ssize_t index)
{
    if (!_model)
    {
        return;
    }
    Widget* newItem = _model->clone();
    _items.insert(index, newItem);
    remedyLayoutParameter(newItem);
    addChild(newItem);
    _refreshViewDirty = true;
}

void ListView::pushBackCustomItem(Widget* item)
{
    _items.pushBack(item);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void ListView::insertCustomItem(Widget* item, ssize_t index)
{
    _items.insert(index, item);
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}

void ListView::removeItem(ssize_t index)
{
    Widget* item = getItem(index);
    if (!item)
    {
        return;
    }
    _items.eraseObject(item);
    removeChild(item);
    _refreshViewDirty = true;
}

void ListView::removeLastItem()
{
    removeItem(_items.size() -1);
}
    
void ListView::removeAllItems()
{
    _items.clear();
    removeAllChildren();
}

Widget* ListView::getItem(ssize_t index)
{
    if (index < 0 || index >= _items.size())
    {
        return nullptr;
    }
    return _items.at(index);
}

Vector<Widget*>& ListView::getItems()
{
    return _items;
}

ssize_t ListView::getIndex(Widget *item) const
{
    if (!item)
    {
        return -1;
    }
    return _items.getIndex(item);
}

void ListView::setGravity(Gravity gravity)
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

void ListView::setDirection(Direction dir)
{
    switch (dir)
    {
        case Direction::VERTICAL:
            setLayoutType(Type::VERTICAL);
            break;
        case Direction::HORIZONTAL:
            setLayoutType(Type::HORIZONTAL);
            break;
        case Direction::BOTH:
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
    ssize_t length = _items.size();
    for (int i=0; i<length; i++)
    {
        Widget* item = _items.at(i);
        item->setLocalZOrder(i);
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
    
void ListView::addEventListenerListView(Ref *target, SEL_ListViewEvent selector)
{
    _listViewEventListener = target;
    _listViewEventSelector = selector;
}
    
void ListView::addEventListener(const ccListViewCallback& callback)
{
    _eventCallback = callback;
}
    
void ListView::selectedItemEvent(int state)
{
    switch (state)
    {
        case 0:
        {
            if (_listViewEventListener && _listViewEventSelector)
            {
                (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM_START);
            }
            if (_eventCallback) {
                _eventCallback(this,EventType::ON_SELECTED_ITEM_START);
            }
        }
        break;
        default:
        {
            if (_listViewEventListener && _listViewEventSelector)
            {
                (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM_END);
            }
            if (_eventCallback) {
                _eventCallback(this, EventType::ON_SELECTED_ITEM_END);
            }
        }
        break;
    }

}
    
void ListView::interceptTouchEvent(int handleState, Widget *sender, const Vec2 &touchPoint)
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
    
ssize_t ListView::getCurSelectedIndex() const
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
    auto& arrayItems = static_cast<ListView*>(model)->getItems();
    for (auto& item : arrayItems)
    {
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
        _listViewEventListener = listViewEx->_listViewEventListener;
        _listViewEventSelector = listViewEx->_listViewEventSelector;
        _eventCallback = listViewEx->_eventCallback;
    }
}

}
NS_CC_END
