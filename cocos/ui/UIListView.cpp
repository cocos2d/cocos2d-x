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

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(ListView)

ListView::ListView():
_model(nullptr),
_gravity(Gravity::CENTER_VERTICAL),
_itemsMargin(0.0f),
_curSelectedIndex(0),
_refreshViewDirty(true),
_listViewEventListener(nullptr),
_listViewEventSelector(nullptr),
_eventCallback(nullptr)
{
    this->setTouchEnabled(true);
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
    ListView* widget = new (std::nothrow) ListView();
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
                totalHeight += item->getContentSize().height;
            }
            float finalWidth = _contentSize.width;
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
                totalWidth += item->getContentSize().width;
            }
            float finalWidth = totalWidth;
            float finalHeight = _contentSize.height;
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
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter());
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
                    defaultLp->setMargin(Margin::ZERO);
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
                    llp->setMargin(Margin::ZERO);
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
            LinearLayoutParameter* llp = (LinearLayoutParameter*)(item->getLayoutParameter());
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
                    defaultLp->setMargin(Margin::ZERO);
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
                    llp->setMargin(Margin::ZERO);
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
    ScrollView::addChild(newItem);

    remedyLayoutParameter(newItem);
    
    _refreshViewDirty = true;
}


void ListView::pushBackCustomItem(Widget* item)
{
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}
    
void ListView::addChild(cocos2d::Node *child, int zOrder, int tag)
{
    ScrollView::addChild(child, zOrder, tag);

    Widget* widget = dynamic_cast<Widget*>(child);
    if (widget)
    {
        _items.pushBack(widget);
    }
}
    
void ListView::addChild(cocos2d::Node *child)
{
    ListView::addChild(child, child->getLocalZOrder(), child->getName());
}

void ListView::addChild(cocos2d::Node *child, int zOrder)
{
    ListView::addChild(child, zOrder, child->getName());
}
 
void ListView::addChild(Node* child, int zOrder, const std::string &name)
{
    ScrollView::addChild(child, zOrder, name);
    
    Widget* widget = dynamic_cast<Widget*>(child);
    if (widget)
    {
        _items.pushBack(widget);
    }
}
    
void ListView::removeChild(cocos2d::Node *child, bool cleaup)
{
    Widget* widget = dynamic_cast<Widget*>(child);
    if (widget) {
        _items.eraseObject(widget);
    }
   
    ScrollView::removeChild(child, cleaup);
}
    
void ListView::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}
    
void ListView::removeAllChildrenWithCleanup(bool cleanup)
{
    ScrollView::removeAllChildrenWithCleanup(cleanup);
    _items.clear();
}

void ListView::insertCustomItem(Widget* item, ssize_t index)
{
    _items.insert(index, item);
    ScrollView::addChild(item);

    remedyLayoutParameter(item);
    _refreshViewDirty = true;
}

void ListView::removeItem(ssize_t index)
{
    Widget* item = getItem(index);
    if (!item)
    {
        return;
    }
    removeChild(item, true);
    
    _refreshViewDirty = true;
}

void ListView::removeLastItem()
{
    removeItem(_items.size() -1);
}
    
void ListView::removeAllItems()
{
    removeAllChildren();
}

Widget* ListView::getItem(ssize_t index)const
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
    
float ListView::getItemsMargin()const
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
    
void ListView::doLayout()
{
    Layout::doLayout();
    
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
    
void ListView::selectedItemEvent(TouchEventType event)
{
    this->retain();
    switch (event)
    {
        case TouchEventType::BEGAN:
        {
            if (_listViewEventListener && _listViewEventSelector)
            {
                (_listViewEventListener->*_listViewEventSelector)(this, LISTVIEW_ONSELECTEDITEM_START);
            }
            if (_eventCallback) {
                _eventCallback(this,EventType::ON_SELECTED_ITEM_START);
            }
            if (_ccEventCallback)
            {
                _ccEventCallback(this, static_cast<int>(EventType::ON_SELECTED_ITEM_START));
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
            if (_ccEventCallback)
            {
                _ccEventCallback(this, static_cast<int>(EventType::ON_SELECTED_ITEM_END));
            }
        }
        break;
    }
    this->release();
}
    
void ListView::interceptTouchEvent(TouchEventType event, Widget *sender, Touch* touch)
{
    ScrollView::interceptTouchEvent(event, sender, touch);
    if (event != TouchEventType::MOVED)
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
        if (sender->isHighlighted()) {
            selectedItemEvent(event);
        }
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
