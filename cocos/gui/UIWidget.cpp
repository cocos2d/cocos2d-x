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

#include "gui/UIWidget.h"
#include "gui/UILayout.h"
#include "gui/UIHelper.h"

NS_CC_BEGIN

namespace gui {
    
Widget::Widget():
_enabled(true),
_bright(true),
_touchEnabled(false),
_touchPassedEnabled(false),
_focus(false),
_brightStyle(BRIGHT_NONE),
_updateEnabled(false),
_renderer(nullptr),
_touchStartPos(Point::ZERO),
_touchMovePos(Point::ZERO),
_touchEndPos(Point::ZERO),
_touchEventListener(nullptr),
_touchEventSelector(nullptr),
_name("default"),
_widgetType(WidgetTypeWidget),
_actionTag(0),
_size(Size::ZERO),
_customSize(Size::ZERO),
_layoutParameterDictionary(nullptr),
_ignoreSize(false),
_affectByClipping(false),
_sizeType(SIZE_ABSOLUTE),
_sizePercent(Point::ZERO),
_positionType(POSITION_ABSOLUTE),
_positionPercent(Point::ZERO),
_reorderWidgetChildDirty(true),
_hitted(false)
{
    
}

Widget::~Widget()
{
    //recheck
    _touchEventListener = nullptr;
    _touchEventSelector = nullptr;
    _renderer->release();
    _layoutParameterDictionary->removeAllObjects();
    CC_SAFE_RELEASE(_layoutParameterDictionary);
}

Widget* Widget::create()
{
    Widget* widget = new Widget();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Widget::init()
{
    _layoutParameterDictionary = Dictionary::create();
    CC_SAFE_RETAIN(_layoutParameterDictionary);
    initRenderer();
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    setBright(true);
    ignoreContentAdaptWithSize(true);
    setAnchorPoint(Point(0.5f, 0.5f));
    return true;
}

void Widget::onEnter()
{
    updateSizeAndPosition();
    NodeRGBA::onEnter();
}

void Widget::onExit()
{
    NodeRGBA::onExit();
}
    
void Widget::visit()
{
    if (_enabled)
    {
        NodeRGBA::visit();
    }    
}

void Widget::addChild(Node *child)
{
    NodeRGBA::addChild(child);
}

void Widget::addChild(Node * child, int zOrder)
{
    NodeRGBA::addChild(child, zOrder);
}
    
void Widget::addChild(Node* child, int zOrder, int tag)
{
    CCASSERT(dynamic_cast<Widget*>(child) != NULL, "Widget only supports Widgets as children");
    NodeRGBA::addChild(child, zOrder, tag);
    _widgetChildren.pushBack(child);
}
    
void Widget::sortAllChildren()
{
    _reorderWidgetChildDirty = _reorderChildDirty;
    NodeRGBA::sortAllChildren();
    if( _reorderWidgetChildDirty )
    {
        std::sort( std::begin(_widgetChildren), std::end(_widgetChildren), nodeComparisonLess );
        _reorderWidgetChildDirty = false;
    }
}
    
Node* Widget::getChildByTag(int aTag)
{
    CCASSERT( aTag != Node::INVALID_TAG, "Invalid tag");
    
    for (auto& child : _widgetChildren)
    {
        if(child && child->getTag() == aTag)
            return child;
    }
    return nullptr;
}

Vector<Node*>& Widget::getChildren()
{
    return _widgetChildren;
}
    
const Vector<Node*>& Widget::getChildren() const
{
    return _widgetChildren;
}
    
long Widget::getChildrenCount() const
{
    return _widgetChildren.size();
}

Widget* Widget::getWidgetParent()
{
    return dynamic_cast<Widget*>(getParent());
}
    
void Widget::removeFromParent()
{
    removeFromParentAndCleanup(true);
}

void Widget::removeFromParentAndCleanup(bool cleanup)
{
    NodeRGBA::removeFromParentAndCleanup(cleanup);
}

void Widget::removeChild(Node *child, bool cleanup)
{
    NodeRGBA::removeChild(child, cleanup);
    _widgetChildren.removeObject(child);
}

void Widget::removeChildByTag(int tag, bool cleanup)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");
    
    Node *child = getChildByTag(tag);
    
    if (child == NULL)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        removeChild(child, cleanup);
    }
}

void Widget::removeAllChildren()
{
    removeAllChildrenWithCleanup(true);
}
    
void Widget::removeAllChildrenWithCleanup(bool cleanup)
{
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            NodeRGBA::removeChild(child);
        }
    }
    _widgetChildren.clear();
}

void Widget::setEnabled(bool enabled)
{
    _enabled = enabled;
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            ((Widget*)child)->setEnabled(enabled);
        }
    }
}

Widget* Widget::getChildByName(const char *name)
{
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            Widget* widgetChild = (Widget*)child;
            if (strcmp(widgetChild->getName(), name) == 0)
            {
                return widgetChild;
            }
        }
    }
    return nullptr;
}

void Widget::initRenderer()
{
    _renderer = NodeRGBA::create();
    _renderer->retain();
    NodeRGBA::addChild(_renderer, -1, -1);
}

void Widget::setSize(const Size &size)
{
    _customSize = size;
    if (_ignoreSize)
    {
        _size = getContentSize();
    }
    else
    {
        _size = size;
    }
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        Size pSize;
        if (widgetParent)
        {
            pSize = widgetParent->getSize();
        }
        else
        {
            pSize = _parent->getContentSize();
        }
        float spx = 0.0f;
        float spy = 0.0f;
        if (pSize.width > 0.0f)
        {
            spx = _customSize.width / pSize.width;
        }
        if (pSize.height > 0.0f)
        {
            spy = _customSize.height / pSize.height;
        }
        _sizePercent = Point(spx, spy);
    }
    onSizeChanged();
}

void Widget::setSizePercent(const Point &percent)
{
    _sizePercent = percent;
    Size cSize = _customSize;
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            cSize = Size(widgetParent->getSize().width * percent.x , widgetParent->getSize().height * percent.y);
        }
        else
        {
            cSize = Size(_parent->getContentSize().width * percent.x , _parent->getContentSize().height * percent.y);
        }
    }
    if (_ignoreSize)
    {
        _size = getContentSize();
    }
    else
    {
        _size = cSize;
    }
    _customSize = cSize;
    onSizeChanged();
}

void Widget::updateSizeAndPosition()
{
    switch (_sizeType)
    {
        case SIZE_ABSOLUTE:
        {
            if (_ignoreSize)
            {
                _size = getContentSize();
            }
            else
            {
                _size = _customSize;
            }
            Widget* widgetParent = getWidgetParent();
            if (widgetParent)
            {
                Size pSize = widgetParent->getSize();
                float spx = 0.0f;
                float spy = 0.0f;
                if (pSize.width > 0.0f)
                {
                    spx = _customSize.width / pSize.width;
                }
                if (pSize.height > 0.0f)
                {
                    spy = _customSize.height / pSize.height;
                }
                _sizePercent = Point(spx, spy);
            }
            else
            {
                Size pSize = _parent->getContentSize();
                float spx = 0.0f;
                float spy = 0.0f;
                if (pSize.width > 0.0f)
                {
                    spx = _customSize.width / pSize.width;
                }
                if (pSize.height > 0.0f)
                {
                    spy = _customSize.height / pSize.height;
                }
                _sizePercent = Point(spx, spy);
            }
            break;
        }
        case SIZE_PERCENT:
        {
            Widget* widgetParent = getWidgetParent();
            if (widgetParent)
            {
                Size cSize = Size(widgetParent->getSize().width * _sizePercent.x , widgetParent->getSize().height * _sizePercent.y);
                if (_ignoreSize)
                {
                    _size = getContentSize();
                }
                else
                {
                    _size = cSize;
                }
                _customSize = cSize;
            }
            else
            {
                Size cSize = Size(_parent->getContentSize().width * _sizePercent.x , _parent->getContentSize().height * _sizePercent.y);
                if (_ignoreSize)
                {
                    _size = getContentSize();
                }
                else
                {
                    _size = cSize;
                }
                _customSize = cSize;
            }
        }
            break;
        default:
            break;
    }
    onSizeChanged();
    Point absPos = getPosition();
    switch (_positionType)
    {
        case POSITION_ABSOLUTE:
        {
            Widget* widgetParent = getWidgetParent();
            if (widgetParent)
            {
                Size pSize = widgetParent->getSize();
                if (pSize.width <= 0.0f || pSize.height <= 0.0f)
                {
                    _positionPercent = Point::ZERO;
                }
                else
                {
                    _positionPercent = Point(absPos.x / pSize.width, absPos.y / pSize.height);
                }
            }
            else
            {
                Size pSize = _parent->getContentSize();
                if (pSize.width <= 0.0f || pSize.height <= 0.0f)
                {
                    _positionPercent = Point::ZERO;
                }
                else
                {
                    _positionPercent = Point(absPos.x / pSize.width, absPos.y / pSize.height);
                }
            }
            break;
        }
        case POSITION_PERCENT:
        {
            Widget* widgetParent = getWidgetParent();
            if (widgetParent)
            {
                Size parentSize = widgetParent->getSize();
                absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            }
            else
            {
                Size parentSize = _parent->getContentSize();
                absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            }
            break;
        }
        default:
            break;
    }
    setPosition(absPos);
}

void Widget::setSizeType(SizeType type)
{
    _sizeType = type;
}

SizeType Widget::getSizeType() const
{
    return _sizeType;
}

void Widget::ignoreContentAdaptWithSize(bool ignore)
{
    _ignoreSize = ignore;
    if (_ignoreSize)
    {
        Size s = getContentSize();
        _size = s;
    }
    else
    {
        _size = _customSize;
    }
    onSizeChanged();
}

bool Widget::isIgnoreContentAdaptWithSize() const
{
    return _ignoreSize;
}

const Size& Widget::getSize() const
{
    return _size;
}

const Point& Widget::getSizePercent() const
{
    return _sizePercent;
}

Point Widget::getWorldPosition()
{
    return _renderer->convertToWorldSpace(Point::ZERO);
}

Node* Widget::getVirtualRenderer()
{
    return _renderer;
}

void Widget::onSizeChanged()
{

}

const Size& Widget::getContentSize() const
{
    return _size;
}

void Widget::setTouchEnabled(bool enable)
{
    if (enable == _touchEnabled)
    {
        return;
    }
    _touchEnabled = enable;
    if (_touchEnabled)
    {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(Widget::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Widget::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Widget::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Widget::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    else
    {
        _eventDispatcher->removeEventListeners(EventListener::Type::TOUCH_ONE_BY_ONE);
    }
}

bool Widget::isTouchEnabled() const
{
    return _touchEnabled;
}

void Widget::setUpdateEnabled(bool enable)
{
    if (enable == _updateEnabled)
    {
        return;
    }
    _updateEnabled = enable;
    if (enable)
    {
        if (_scheduler)
        {
            _scheduler->scheduleUpdateForTarget(this, 0, false);
        }
    }
    else
    {
        if (_scheduler)
        {
            _scheduler->unscheduleUpdateForTarget(this);
        }
    }
}

bool Widget::isUpdateEnabled()
{
    return _updateEnabled;
}

bool Widget::isFocused() const
{
    return _focus;
}

void Widget::setFocused(bool fucos)
{
    if (fucos == _focus)
    {
        return;
    }
    _focus = fucos;
    if (_bright)
    {
        if (_focus)
        {
            setBrightStyle(BRIGHT_HIGHLIGHT);
        }
        else
        {
            setBrightStyle(BRIGHT_NORMAL);
        }
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBright(bool bright)
{
    _bright = bright;
    if (_bright)
    {
        _brightStyle = BRIGHT_NONE;
        setBrightStyle(BRIGHT_NORMAL);
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBrightStyle(BrightStyle style)
{
    if (_brightStyle == style)
    {
        return;
    }
    _brightStyle = style;
    switch (_brightStyle)
    {
        case BRIGHT_NORMAL:
            onPressStateChangedToNormal();
            break;
        case BRIGHT_HIGHLIGHT:
            onPressStateChangedToPressed();
            break;
        default:
            break;
    }
}

void Widget::onPressStateChangedToNormal()
{
    
}

void Widget::onPressStateChangedToPressed()
{
    
}

void Widget::onPressStateChangedToDisabled()
{
    
}

void Widget::didNotSelectSelf()
{
    
}

bool Widget::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    _touchStartPos = touch->getLocation();
    _hitted = hitTest(_touchStartPos);
    if (!_hitted)
    {
        return false;
    }
    setFocused(true);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(0,this,_touchStartPos);
    }
    pushDownEvent();
    return !_touchPassedEnabled;
}

void Widget::onTouchMoved(Touch *touch, Event *unused_event)
{
    _touchMovePos = touch->getLocation();
    setFocused(hitTest(_touchMovePos));
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void Widget::onTouchEnded(Touch *touch, Event *unused_event)
{
    _touchEndPos = touch->getLocation();
    bool focus = _focus;
    setFocused(false);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(2,this,_touchEndPos);
    }
    if (focus)
    {
        releaseUpEvent();
    }
    else
    {
        cancelUpEvent();
    }
}

void Widget::onTouchCancelled(Touch *touch, Event *unused_event)
{
    setFocused(false);
    cancelUpEvent();
}

void Widget::onTouchLongClicked(const Point &touchPoint)
{
    longClickEvent();
}

void Widget::pushDownEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_BEGAN);
    }
}

void Widget::moveEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_MOVED);
    }
}

void Widget::releaseUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_ENDED);
    }
}

void Widget::cancelUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_CANCELED);
    }
}

void Widget::longClickEvent()
{
    
}

void Widget::addTouchEventListener(Object *target, SEL_TouchEvent selector)
{
    _touchEventListener = target;
    _touchEventSelector = selector;
}

Node* Widget::getRenderer()
{
    return _renderer;
}

void Widget::addRenderer(Node* renderer, int zOrder)
{
    _renderer->addChild(renderer, zOrder);
}

void Widget::removeRenderer(Node* renderer, bool cleanup)
{
    _renderer->removeChild(renderer,cleanup);
}

bool Widget::hitTest(const Point &pt)
{
    Point nsp = _renderer->convertToNodeSpace(pt);
    Rect bb = Rect(-_size.width * _anchorPoint.x, -_size.height * _anchorPoint.y, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool Widget::clippingParentAreaContainPoint(const Point &pt)
{
    _affectByClipping = false;
    Widget* parent = getWidgetParent();
    Widget* clippingParent = nullptr;
    while (parent)
    {
        Layout* layoutParent = dynamic_cast<Layout*>(parent);
        if (layoutParent)
        {
            if (layoutParent->isClippingEnabled())
            {
                _affectByClipping = true;
                clippingParent = layoutParent;
                break;
            }
        }
        parent = parent->getWidgetParent();
    }
    
    if (!_affectByClipping)
    {
        return true;
    }
    
    
    if (clippingParent)
    {
        bool bRet = false;
        if (clippingParent->hitTest(pt))
        {
            bRet = true;
        }
        if (bRet)
        {
            return clippingParent->clippingParentAreaContainPoint(pt);
        }
        return false;
    }
    return true;
}

void Widget::checkChildInfo(int handleState, Widget *sender, const Point &touchPoint)
{
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void Widget::setPosition(const Point &pos)
{
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            Size pSize = widgetParent->getSize();
            if (pSize.width <= 0.0f || pSize.height <= 0.0f)
            {
                _positionPercent = Point::ZERO;
            }
            else
            {
                _positionPercent = Point(pos.x / pSize.width, pos.y / pSize.height);
            }
        }
    }
    NodeRGBA::setPosition(pos);
}

void Widget::setPositionPercent(const Point &percent)
{
    _positionPercent = percent;
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            Size parentSize = widgetParent->getSize();
            Point absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            _renderer->setPosition(absPos);
        }
    }
}

void Widget::setAnchorPoint(const Point &pt)
{
    NodeRGBA::setAnchorPoint(pt);
}

void Widget::updateAnchorPoint()
{
    setAnchorPoint(getAnchorPoint());
}

const Point& Widget::getPositionPercent()
{
    return _positionPercent;
}

void Widget::setPositionType(PositionType type)
{
    _positionType = type;
}

PositionType Widget::getPositionType() const
{
    return _positionType;
}

const Point& Widget::getAnchorPoint() const
{
    return NodeRGBA::getAnchorPoint();
}

void Widget::setVisible(bool visible)
{
    _visible = visible;
    _renderer->setVisible(visible);
}

bool Widget::isVisible() const
{
    return _visible;
}

bool Widget::isBright() const
{
    return _bright;
}

bool Widget::isEnabled() const
{
    return _enabled;
}

float Widget::getLeftInParent()
{
    return getPosition().x - getAnchorPoint().x * _size.width;;
}

float Widget::getBottomInParent()
{
    return getPosition().y - getAnchorPoint().y * _size.height;;
}

float Widget::getRightInParent()
{
    return getLeftInParent() + _size.width;
}

float Widget::getTopInParent()
{
    return getBottomInParent() + _size.height;
}

const Point& Widget::getTouchStartPos()
{
    return _touchStartPos;
}

const Point& Widget::getTouchMovePos()
{
    return _touchMovePos;
}

const Point& Widget::getTouchEndPos()
{
    return _touchEndPos;
}

void Widget::setName(const char* name)
{
    _name = name;
}

const char* Widget::getName() const
{
    return _name.c_str();
}

WidgetType Widget::getWidgetType() const
{
    return _widgetType;
}

void Widget::setLayoutParameter(LayoutParameter *parameter)
{
    if (!parameter)
    {
        return;
    }
    _layoutParameterDictionary->setObject(parameter, parameter->getLayoutType());
}

LayoutParameter* Widget::getLayoutParameter(LayoutParameterType type)
{
    return dynamic_cast<LayoutParameter*>(_layoutParameterDictionary->objectForKey(type));
}

const char* Widget::getDescription() const
{
    return "Widget";
}

Widget* Widget::clone()
{
    Widget* clonedWidget = createCloneInstance();
    clonedWidget->copyProperties(this);
    clonedWidget->copyClonedWidgetChildren(this);
    return clonedWidget;
}

Widget* Widget::createCloneInstance()
{
    return Widget::create();
}

void Widget::copyClonedWidgetChildren(Widget* model)
{
    int length = model->getChildren().size();
    for (int i=0; i<length; i++)
    {
        Widget* child = (Widget*)(model->getChildren().at(i));
        addChild(child->clone());
    }
}

void Widget::copySpecialProperties(Widget* model)
{
    
}

void Widget::copyProperties(Widget *widget)
{
    setEnabled(widget->isEnabled());
    setVisible(widget->isVisible());
    setBright(widget->isBright());
    setTouchEnabled(widget->isTouchEnabled());
    _touchPassedEnabled = false;
    setZOrder(widget->getZOrder());
    setUpdateEnabled(widget->isUpdateEnabled());
    setTag(widget->getTag());
    setName(widget->getName());
    setActionTag(widget->getActionTag());
    _ignoreSize = widget->_ignoreSize;
    _size = widget->_size;
    _customSize = widget->_customSize;
    copySpecialProperties(widget);
    _sizeType = widget->getSizeType();
    _sizePercent = widget->_sizePercent;
    _positionType = widget->_positionType;
    _positionPercent = widget->_positionPercent;
    setPosition(widget->getPosition());
    setAnchorPoint(widget->getAnchorPoint());
    setScaleX(widget->getScaleX());
    setScaleY(widget->getScaleY());
    setRotation(widget->getRotation());
    setRotationX(widget->getRotationX());
    setRotationY(widget->getRotationY());
    setFlipX(widget->isFlipX());
    setFlipY(widget->isFlipY());
    setColor(widget->getColor());
    setOpacity(widget->getOpacity());
    setCascadeOpacityEnabled(widget->isCascadeOpacityEnabled());
    setCascadeColorEnabled(widget->isCascadeColorEnabled());
    onSizeChanged();
}

/*temp action*/
void Widget::setActionTag(int tag)
{
	_actionTag = tag;
}

int Widget::getActionTag()
{
	return _actionTag;
}
    
}

NS_CC_END
