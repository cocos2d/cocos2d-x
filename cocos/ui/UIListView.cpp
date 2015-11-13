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

static const float DEFAULT_TIME_IN_SEC_FOR_SCROLL_TO_ITEM = 1.0f;

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(ListView)

ListView::ListView():
_model(nullptr),
_gravity(Gravity::CENTER_VERTICAL),
_magneticType(MagneticType::NONE),
_magneticAllowedOutOfBoundary(true),
_itemsMargin(0.0f),
_curSelectedIndex(-1),
_innerContainerDoLayoutDirty(true),
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
    if (nullptr == model)
    {
        CCLOG("Can't set a nullptr to item model!");
        return;
    }
    CC_SAFE_RELEASE_NULL(_model);
    _model = model;
    CC_SAFE_RETAIN(_model);
}

void ListView::handleReleaseLogic(Touch *touch)
{
    ScrollView::handleReleaseLogic(touch);
    
    if(!_autoScrolling)
    {
        startMagneticScroll();
    }
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
    
void ListView::remedyVerticalLayoutParameter(LinearLayoutParameter* layoutParameter, ssize_t itemIndex)
{
    CCASSERT(nullptr != layoutParameter, "Layout parameter can't be nullptr!");
    
    switch (_gravity)
    {
        case Gravity::LEFT:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::LEFT);
            break;
        case Gravity::RIGHT:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::RIGHT);
            break;
        case Gravity::CENTER_HORIZONTAL:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
            break;
        default:
            break;
    }
    
    if (0 == itemIndex)
    {
        layoutParameter->setMargin(Margin::ZERO);
    }
    else
    {
        layoutParameter->setMargin(Margin(0.0f, _itemsMargin, 0.0f, 0.0f));
    }
}
    
void ListView::remedyHorizontalLayoutParameter(LinearLayoutParameter* layoutParameter, ssize_t itemIndex)
{
    CCASSERT(nullptr != layoutParameter, "Layout parameter can't be nullptr!");
    
    switch (_gravity)
    {
        case Gravity::TOP:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::TOP);
            break;
        case Gravity::BOTTOM:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::BOTTOM);
            break;
        case Gravity::CENTER_VERTICAL:
            layoutParameter->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
            break;
        default:
            break;
    }
    if (0 == itemIndex)
    {
        layoutParameter->setMargin(Margin::ZERO);
    }
    else
    {
        layoutParameter->setMargin(Margin(_itemsMargin, 0.0f, 0.0f, 0.0f));
    }
}

void ListView::remedyLayoutParameter(Widget *item)
{
    CCASSERT(nullptr != item, "ListView Item can't be nullptr!");
    
    LinearLayoutParameter* linearLayoutParameter = (LinearLayoutParameter*)(item->getLayoutParameter());
    bool isLayoutParameterExists = true;
    if (!linearLayoutParameter)
    {
        linearLayoutParameter = LinearLayoutParameter::create();
        isLayoutParameterExists = false;
    }
    ssize_t itemIndex = getIndex(item);
    
    switch (_direction)
    {
        case Direction::VERTICAL:
        {
            this->remedyVerticalLayoutParameter(linearLayoutParameter, itemIndex);
            break;
        }
        case Direction::HORIZONTAL:
        {
            this->remedyHorizontalLayoutParameter(linearLayoutParameter, itemIndex);
            break;
        }
        default:
            break;
    }
    if (!isLayoutParameterExists)
    {
        item->setLayoutParameter(linearLayoutParameter);
    }
}

void ListView::pushBackDefaultItem()
{
    if (nullptr == _model)
    {
        return;
    }
    Widget* newItem = _model->clone();
    remedyLayoutParameter(newItem);
    addChild(newItem);
    requestDoLayout();
}

void ListView::insertDefaultItem(ssize_t index)
{
    if (nullptr == _model)
    {
        return;
    }
    insertCustomItem(_model->clone(), index);
}


void ListView::pushBackCustomItem(Widget* item)
{
    remedyLayoutParameter(item);
    addChild(item);
    requestDoLayout();
}
    
void ListView::addChild(cocos2d::Node *child, int zOrder, int tag)
{
    ScrollView::addChild(child, zOrder, tag);

    Widget* widget = dynamic_cast<Widget*>(child);
    if (nullptr != widget)
    {
        _items.pushBack(widget);
        _outOfBoundaryAmountDirty = true;
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
    if (nullptr != widget)
    {
        _items.pushBack(widget);
        _outOfBoundaryAmountDirty = true;
    }
}
    
void ListView::removeChild(cocos2d::Node *child, bool cleaup)
{
    Widget* widget = dynamic_cast<Widget*>(child);
    if (nullptr != widget)
    {
        if (-1 != _curSelectedIndex)
        {
            auto removedIndex = getIndex(widget);
            if (_curSelectedIndex > removedIndex)
            {
                _curSelectedIndex -= 1;
            }
            else if (_curSelectedIndex == removedIndex)
            {
                _curSelectedIndex = -1;
            }
        }
        _items.eraseObject(widget);
        _outOfBoundaryAmountDirty = true;
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
    _curSelectedIndex = -1;
    _outOfBoundaryAmountDirty = true;
}

void ListView::insertCustomItem(Widget* item, ssize_t index)
{
    if (-1 != _curSelectedIndex)
    {
        if (_curSelectedIndex >= index)
        {
            _curSelectedIndex += 1;
        }
    }
    _items.insert(index, item);
    _outOfBoundaryAmountDirty = true;
    
    ScrollView::addChild(item);

    remedyLayoutParameter(item);
    requestDoLayout();
}

void ListView::removeItem(ssize_t index)
{
    Widget* item = getItem(index);
    if (nullptr == item)
    {
        return;
    }
    removeChild(item, true);
    requestDoLayout();
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
    if (nullptr == item)
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
    requestDoLayout();
}

void ListView::setMagneticType(MagneticType magneticType)
{
    _magneticType = magneticType;
    _outOfBoundaryAmountDirty = true;
    startMagneticScroll();
}

ListView::MagneticType ListView::getMagneticType() const
{
    return _magneticType;
}

void ListView::setMagneticAllowedOutOfBoundary(bool magneticAllowedOutOfBoundary)
{
    _magneticAllowedOutOfBoundary = magneticAllowedOutOfBoundary;
}

bool ListView::getMagneticAllowedOutOfBoundary() const
{
    return _magneticAllowedOutOfBoundary;
}

void ListView::setItemsMargin(float margin)
{
    if (_itemsMargin == margin)
    {
        return;
    }
    _itemsMargin = margin;
    requestDoLayout();
}
    
float ListView::getItemsMargin()const
{
    return _itemsMargin;
}

void ListView::setDirection(Direction dir)
{
    switch (dir)
    {
        case Direction::NONE:
        case Direction::BOTH:
            break;
        case Direction::VERTICAL:
            setLayoutType(Type::VERTICAL);
            break;
        case Direction::HORIZONTAL:
            setLayoutType(Type::HORIZONTAL);
            break;
        default:
            return;
            break;
    }
    ScrollView::setDirection(dir);
}
    
void ListView::refreshView()
{
    forceDoLayout();
}

void ListView::requestDoLayout()
{
    _innerContainerDoLayoutDirty = true;
}

void ListView::doLayout()
{
    if(!_innerContainerDoLayoutDirty)
    {
        return;
    }

    ssize_t length = _items.size();
    for (int i = 0; i < length; ++i)
    {
        Widget* item = _items.at(i);
        item->setLocalZOrder(i);
        remedyLayoutParameter(item);
    }
    _innerContainer->forceDoLayout();
    updateInnerContainerSize();
    _innerContainerDoLayoutDirty = false;
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
    if (!_touchEnabled)
    {
        return;
    }
    if (event != TouchEventType::MOVED)
    {
        Widget* parent = sender;
        while (parent)
        {
            if (parent && (parent->getParent() == _innerContainer))
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
    
static Vec2 calculateItemPositionWithAnchor(Widget* item, const Vec2& itemAnchorPoint)
{
    Vec2 origin(item->getLeftBoundary(), item->getBottomBoundary());
    Size size = item->getContentSize();
    return origin + Vec2(size.width * itemAnchorPoint.x, size.height * itemAnchorPoint.y);
}
    
static Widget* findClosestItem(const Vec2& targetPosition, const Vector<Widget*>& items, const Vec2& itemAnchorPoint, ssize_t firstIndex, float distanceFromFirst, ssize_t lastIndex, float distanceFromLast)
{
    CCASSERT(firstIndex >= 0 && lastIndex < items.size() && firstIndex <= lastIndex, "");
    if (firstIndex == lastIndex)
    {
        return items.at(firstIndex);
    }
    if (lastIndex - firstIndex == 1)
    {
        if (distanceFromFirst <= distanceFromLast)
        {
            return items.at(firstIndex);
        }
        else
        {
            return items.at(lastIndex);
        }
    }
    
    // Binary search
    ssize_t midIndex = (firstIndex + lastIndex) / 2;
    Vec2 itemPosition = calculateItemPositionWithAnchor(items.at(midIndex), itemAnchorPoint);
    float distanceFromMid = (targetPosition - itemPosition).length();
    if (distanceFromFirst <= distanceFromLast)
    {
        // Left half
        return findClosestItem(targetPosition, items, itemAnchorPoint, firstIndex, distanceFromFirst, midIndex, distanceFromMid);
    }
    else
    {
        // Right half
        return findClosestItem(targetPosition, items, itemAnchorPoint, midIndex, distanceFromMid, lastIndex, distanceFromLast);
    }
}

Widget* ListView::getClosestItemToPosition(const Vec2& targetPosition, const Vec2& itemAnchorPoint) const
{
    if (_items.empty())
    {
        return nullptr;
    }
    
    // Find the closest item through binary search
    ssize_t firstIndex = 0;
    Vec2 firstPosition = calculateItemPositionWithAnchor(_items.at(firstIndex), itemAnchorPoint);
    float distanceFromFirst = (targetPosition - firstPosition).length();
    
    ssize_t lastIndex = _items.size() - 1;
    Vec2 lastPosition = calculateItemPositionWithAnchor(_items.at(lastIndex), itemAnchorPoint);
    float distanceFromLast = (targetPosition - lastPosition).length();
    
    return findClosestItem(targetPosition, _items, itemAnchorPoint, firstIndex, distanceFromFirst, lastIndex, distanceFromLast);
}

Widget* ListView::getClosestItemToPositionInCurrentView(const Vec2& positionRatioInView, const Vec2& itemAnchorPoint) const
{
    // Calculate the target position
    Size contentSize = getContentSize();
    Vec2 targetPosition = -_innerContainer->getPosition();
    targetPosition.x += contentSize.width * positionRatioInView.x;
    targetPosition.y += contentSize.height * positionRatioInView.y;
    return getClosestItemToPosition(targetPosition, itemAnchorPoint);
}

Widget* ListView::getCenterItemInCurrentView() const
{
    return getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE);
}

Widget* ListView::getLeftmostItemInCurrentView() const
{
    if (_direction == Direction::HORIZONTAL)
    {
        return getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE_LEFT, Vec2::ANCHOR_MIDDLE);
    }
    return nullptr;
}

Widget* ListView::getRightmostItemInCurrentView() const
{
    if (_direction == Direction::HORIZONTAL)
    {
        return getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE_RIGHT, Vec2::ANCHOR_MIDDLE);
    }
    return nullptr;
}

Widget* ListView::getTopmostItemInCurrentView() const
{
    if (_direction == Direction::VERTICAL)
    {
        return getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE_TOP, Vec2::ANCHOR_MIDDLE);
    }
    return nullptr;
}

Widget* ListView::getBottommostItemInCurrentView() const
{
    if (_direction == Direction::VERTICAL)
    {
        return getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE_BOTTOM, Vec2::ANCHOR_MIDDLE);
    }
    return nullptr;
}

void ListView::jumpToBottom()
{
    doLayout();
    ScrollView::jumpToBottom();
}

void ListView::jumpToTop()
{
    doLayout();
    ScrollView::jumpToTop();
}

void ListView::jumpToLeft()
{
    doLayout();
    ScrollView::jumpToLeft();
}

void ListView::jumpToRight()
{
    doLayout();
    ScrollView::jumpToRight();
}

void ListView::jumpToTopLeft()
{
    doLayout();
    ScrollView::jumpToTopLeft();
}

void ListView::jumpToTopRight()
{
    doLayout();
    ScrollView::jumpToTopRight();
}

void ListView::jumpToBottomLeft()
{
    doLayout();
    ScrollView::jumpToBottomLeft();
}

void ListView::jumpToBottomRight()
{
    doLayout();
    ScrollView::jumpToBottomRight();
}

void ListView::jumpToPercentVertical(float percent)
{
    doLayout();
    ScrollView::jumpToPercentVertical(percent);
}

void ListView::jumpToPercentHorizontal(float percent)
{
    doLayout();
    ScrollView::jumpToPercentHorizontal(percent);
}

void ListView::jumpToPercentBothDirection(const Vec2& percent)
{
    doLayout();
    ScrollView::jumpToPercentBothDirection(percent);
}

static Vec2 calculateItemDestination(const Size& contentSize, Widget* item, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint)
{
    Vec2 positionInView;
    positionInView.x += contentSize.width * positionRatioInView.x;
    positionInView.y += contentSize.height * positionRatioInView.y;

    Vec2 itemPosition = calculateItemPositionWithAnchor(item, itemAnchorPoint);
    return -(itemPosition - positionInView);
}

void ListView::jumpToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint)
{
    Widget* item = getItem(itemIndex);
    if (item == nullptr)
    {
        return;
    }
    doLayout();

    Vec2 destination = calculateItemDestination(getContentSize(), item, positionRatioInView, itemAnchorPoint);
    destination = flattenVectorByDirection(destination);
    Vec2 delta = destination - getInnerContainerPosition();
    Vec2 outOfBoundary = getHowMuchOutOfBoundary(delta);
    destination += outOfBoundary;
    moveChildrenToPosition(destination);
}

void ListView::scrollToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint)
{
    scrollToItem(itemIndex, positionRatioInView, itemAnchorPoint, DEFAULT_TIME_IN_SEC_FOR_SCROLL_TO_ITEM);
}

void ListView::scrollToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint, float timeInSec)
{
    Widget* item = getItem(itemIndex);
    if (item == nullptr)
    {
        return;
    }
    Vec2 destination = calculateItemDestination(getContentSize(), item, positionRatioInView, itemAnchorPoint);
    startAutoScrollToDestination(destination, timeInSec, true);
}

ssize_t ListView::getCurSelectedIndex() const
{
    return _curSelectedIndex;
}

void ListView::onSizeChanged()
{
    ScrollView::onSizeChanged();
    requestDoLayout();
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

Vec2 ListView::getHowMuchOutOfBoundary(const Vec2& addition)
{
    if(!_magneticAllowedOutOfBoundary || _items.empty())
    {
        return ScrollView::getHowMuchOutOfBoundary(addition);
    }
    else if(_magneticType == MagneticType::NONE || _magneticType == MagneticType::BOTH_END)
    {
        return ScrollView::getHowMuchOutOfBoundary(addition);
    }
    else if(addition == Vec2::ZERO && !_outOfBoundaryAmountDirty)
    {
        return _outOfBoundaryAmount;
    }
    
    // If it is allowed to be out of boundary by magnetic, adjust the boundaries according to the magnetic type.
    float leftBoundary = _leftBoundary;
    float rightBoundary = _rightBoundary;
    float topBoundary = _topBoundary;
    float bottomBoundary = _bottomBoundary;
    {
        int lastItemIndex = _items.size() - 1;
        Size contentSize = getContentSize();
        Vec2 firstItemAdjustment, lastItemAdjustment;
        if(_magneticType == MagneticType::CENTER)
        {
            firstItemAdjustment = (contentSize - _items.at(0)->getContentSize()) / 2;
            lastItemAdjustment = (contentSize - _items.at(lastItemIndex)->getContentSize()) / 2;
        }
        else if(_magneticType == MagneticType::LEFT)
        {
            lastItemAdjustment = contentSize - _items.at(lastItemIndex)->getContentSize();
        }
        else if(_magneticType == MagneticType::RIGHT)
        {
            firstItemAdjustment = contentSize - _items.at(0)->getContentSize();
        }
        else if(_magneticType == MagneticType::TOP)
        {
            lastItemAdjustment = contentSize - _items.at(lastItemIndex)->getContentSize();
        }
        else if(_magneticType == MagneticType::BOTTOM)
        {
            firstItemAdjustment = contentSize - _items.at(0)->getContentSize();
        }
        leftBoundary += firstItemAdjustment.x;
        rightBoundary -= lastItemAdjustment.x;
        topBoundary -= firstItemAdjustment.y;
        bottomBoundary += lastItemAdjustment.y;
    }
    
    // Calculate the actual amount
    Vec2 outOfBoundaryAmount;
    if(_innerContainer->getLeftBoundary() + addition.x > leftBoundary)
    {
        outOfBoundaryAmount.x = leftBoundary - (_innerContainer->getLeftBoundary() + addition.x);
    }
    else if(_innerContainer->getRightBoundary() + addition.x < rightBoundary)
    {
        outOfBoundaryAmount.x = rightBoundary - (_innerContainer->getRightBoundary() + addition.x);
    }
    
    if(_innerContainer->getTopBoundary() + addition.y < topBoundary)
    {
        outOfBoundaryAmount.y = topBoundary - (_innerContainer->getTopBoundary() + addition.y);
    }
    else if(_innerContainer->getBottomBoundary() + addition.y > bottomBoundary)
    {
        outOfBoundaryAmount.y = bottomBoundary - (_innerContainer->getBottomBoundary() + addition.y);
    }
    
    if(addition == Vec2::ZERO)
    {
        _outOfBoundaryAmount = outOfBoundaryAmount;
        _outOfBoundaryAmountDirty = false;
    }
    return outOfBoundaryAmount;
}

static Vec2 getAnchorPointByMagneticType(ListView::MagneticType magneticType)
{
    switch(magneticType)
    {
        case ListView::MagneticType::NONE: return Vec2::ZERO;
        case ListView::MagneticType::BOTH_END: return Vec2::ANCHOR_TOP_LEFT;
        case ListView::MagneticType::CENTER: return Vec2::ANCHOR_MIDDLE;
        case ListView::MagneticType::LEFT: return Vec2::ANCHOR_MIDDLE_LEFT;
        case ListView::MagneticType::RIGHT: return Vec2::ANCHOR_MIDDLE_RIGHT;
        case ListView::MagneticType::TOP: return Vec2::ANCHOR_MIDDLE_TOP;
        case ListView::MagneticType::BOTTOM: return Vec2::ANCHOR_MIDDLE_BOTTOM;
    }
    return Vec2::ZERO;
}

void ListView::startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity)
{
    Vec2 adjustedDeltaMove = deltaMove;
    
    if(!_items.empty() && _magneticType != MagneticType::NONE)
    {
        adjustedDeltaMove = flattenVectorByDirection(adjustedDeltaMove);

        // If the destination is out of boundary, do nothing here. Because it will be handled by bouncing back.
        if(getHowMuchOutOfBoundary(adjustedDeltaMove) == Vec2::ZERO)
        {
            MagneticType magType = _magneticType;
            if(magType == MagneticType::BOTH_END)
            {
                if(_direction == Direction::HORIZONTAL)
                {
                    magType = (adjustedDeltaMove.x > 0 ? MagneticType::LEFT : MagneticType::RIGHT);
                }
                else if(_direction == Direction::VERTICAL)
                {
                    magType = (adjustedDeltaMove.y > 0 ? MagneticType::BOTTOM : MagneticType::TOP);
                }
            }
            
            // Adjust the delta move amount according to the magnetic type
            Vec2 magneticAnchorPoint = getAnchorPointByMagneticType(magType);
            Vec2 magneticPosition = -_innerContainer->getPosition();
            magneticPosition.x += getContentSize().width * magneticAnchorPoint.x;
            magneticPosition.y += getContentSize().height * magneticAnchorPoint.y;
            
            Widget* pTargetItem = getClosestItemToPosition(magneticPosition - adjustedDeltaMove, magneticAnchorPoint);
            Vec2 itemPosition = calculateItemPositionWithAnchor(pTargetItem, magneticAnchorPoint);
            adjustedDeltaMove = magneticPosition - itemPosition;
        }
    }
    ScrollView::startAttenuatingAutoScroll(adjustedDeltaMove, initialVelocity);
}

void ListView::startMagneticScroll()
{
    if(_items.empty() || _magneticType == MagneticType::NONE)
    {
        return;
    }
    
    // Find the closest item
    Vec2 magneticAnchorPoint = getAnchorPointByMagneticType(_magneticType);
    Vec2 magneticPosition = -_innerContainer->getPosition();
    magneticPosition.x += getContentSize().width * magneticAnchorPoint.x;
    magneticPosition.y += getContentSize().height * magneticAnchorPoint.y;
    
    Widget* pTargetItem = getClosestItemToPosition(magneticPosition, magneticAnchorPoint);
    scrollToItem(getIndex(pTargetItem), magneticAnchorPoint, magneticAnchorPoint);
}

}
NS_CC_END
