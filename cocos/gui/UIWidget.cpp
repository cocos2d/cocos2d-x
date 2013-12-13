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
    
UIWidget::UIWidget():
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

UIWidget::~UIWidget()
{
    //recheck
    _touchEventListener = nullptr;
    _touchEventSelector = nullptr;
    _renderer->release();
    _layoutParameterDictionary->removeAllObjects();
    CC_SAFE_RELEASE(_layoutParameterDictionary);
}

UIWidget* UIWidget::create()
{
    UIWidget* widget = new UIWidget();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool UIWidget::init()
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

void UIWidget::onEnter()
{
    updateSizeAndPosition();
    NodeRGBA::onEnter();
}

void UIWidget::onExit()
{
    NodeRGBA::onExit();
}
    
void UIWidget::visit()
{
    if (_enabled)
    {
        NodeRGBA::visit();
    }    
}

void UIWidget::addChild(Node *child)
{
    NodeRGBA::addChild(child);
}

void UIWidget::addChild(Node * child, int zOrder)
{
    NodeRGBA::addChild(child, zOrder);
}
    
void UIWidget::addChild(Node* child, int zOrder, int tag)
{
    CCASSERT(dynamic_cast<UIWidget*>(child) != NULL, "UIWidget only supports Widgets as children");
    NodeRGBA::addChild(child, zOrder, tag);
    _widgetChildren.pushBack(child);
}
    
void UIWidget::sortAllChildren()
{
    _reorderWidgetChildDirty = _reorderChildDirty;
    NodeRGBA::sortAllChildren();
    if( _reorderWidgetChildDirty )
    {
        std::sort( std::begin(_widgetChildren), std::end(_widgetChildren), nodeComparisonLess );
        _reorderWidgetChildDirty = false;
    }
}
    
Node* UIWidget::getChildByTag(int aTag)
{
    CCASSERT( aTag != Node::INVALID_TAG, "Invalid tag");
    
    for (auto& child : _widgetChildren)
    {
        if(child && child->getTag() == aTag)
            return child;
    }
    return nullptr;
}

Vector<Node*>& UIWidget::getChildren()
{
    return _widgetChildren;
}
    
const Vector<Node*>& UIWidget::getChildren() const
{
    return _widgetChildren;
}
    
long UIWidget::getChildrenCount() const
{
    return _widgetChildren.size();
}

UIWidget* UIWidget::getWidgetParent()
{
    return dynamic_cast<UIWidget*>(getParent());
}
    
void UIWidget::removeFromParent()
{
    removeFromParentAndCleanup(true);
}

void UIWidget::removeFromParentAndCleanup(bool cleanup)
{
    NodeRGBA::removeFromParentAndCleanup(cleanup);
}

void UIWidget::removeChild(Node *child, bool cleanup)
{
    NodeRGBA::removeChild(child, cleanup);
    _widgetChildren.removeObject(child);
}

void UIWidget::removeChildByTag(int tag, bool cleanup)
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

void UIWidget::removeAllChildren()
{
    removeAllChildrenWithCleanup(true);
}
    
void UIWidget::removeAllChildrenWithCleanup(bool cleanup)
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

void UIWidget::setEnabled(bool enabled)
{
    _enabled = enabled;
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            ((UIWidget*)child)->setEnabled(enabled);
        }
    }
}

UIWidget* UIWidget::getChildByName(const char *name)
{
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            UIWidget* widgetChild = (UIWidget*)child;
            if (strcmp(widgetChild->getName(), name) == 0)
            {
                return widgetChild;
            }
        }
    }
    return nullptr;
}

void UIWidget::initRenderer()
{
    _renderer = NodeRGBA::create();
    _renderer->retain();
    NodeRGBA::addChild(_renderer, -1, -1);
}

void UIWidget::setSize(const Size &size)
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
        UIWidget* widgetParent = getWidgetParent();
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

void UIWidget::setSizePercent(const Point &percent)
{
    _sizePercent = percent;
    Size cSize = _customSize;
    if (_running)
    {
        UIWidget* widgetParent = getWidgetParent();
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

void UIWidget::updateSizeAndPosition()
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
            UIWidget* widgetParent = getWidgetParent();
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
            UIWidget* widgetParent = getWidgetParent();
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
            UIWidget* widgetParent = getWidgetParent();
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
            UIWidget* widgetParent = getWidgetParent();
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

void UIWidget::setSizeType(SizeType type)
{
    _sizeType = type;
}

SizeType UIWidget::getSizeType() const
{
    return _sizeType;
}

void UIWidget::ignoreContentAdaptWithSize(bool ignore)
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

bool UIWidget::isIgnoreContentAdaptWithSize() const
{
    return _ignoreSize;
}

const Size& UIWidget::getSize() const
{
    return _size;
}

const Point& UIWidget::getSizePercent() const
{
    return _sizePercent;
}

Point UIWidget::getWorldPosition()
{
    return _renderer->convertToWorldSpace(Point::ZERO);
}

Node* UIWidget::getVirtualRenderer()
{
    return _renderer;
}

void UIWidget::onSizeChanged()
{

}

const Size& UIWidget::getContentSize() const
{
    return _size;
}

void UIWidget::setTouchEnabled(bool enable)
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
        listener->onTouchBegan = CC_CALLBACK_2(UIWidget::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(UIWidget::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(UIWidget::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(UIWidget::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    else
    {
        _eventDispatcher->removeEventListeners(EventListener::Type::TOUCH_ONE_BY_ONE);
    }
}

bool UIWidget::isTouchEnabled() const
{
    return _touchEnabled;
}

void UIWidget::setUpdateEnabled(bool enable)
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

bool UIWidget::isUpdateEnabled()
{
    return _updateEnabled;
}

bool UIWidget::isFocused() const
{
    return _focus;
}

void UIWidget::setFocused(bool fucos)
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

void UIWidget::setBright(bool bright)
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

void UIWidget::setBrightStyle(BrightStyle style)
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

void UIWidget::onPressStateChangedToNormal()
{
    
}

void UIWidget::onPressStateChangedToPressed()
{
    
}

void UIWidget::onPressStateChangedToDisabled()
{
    
}

void UIWidget::didNotSelectSelf()
{
    
}

bool UIWidget::onTouchBegan(Touch *touch, Event *unused_event)
{
    
    _touchStartPos = touch->getLocation();
    _hitted = hitTest(_touchStartPos);
    if (!_hitted)
    {
        return false;
    }
    setFocused(true);
    UIWidget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(0,this,_touchStartPos);
    }
    pushDownEvent();
    return !_touchPassedEnabled;
}

void UIWidget::onTouchMoved(Touch *touch, Event *unused_event)
{
    _touchMovePos = touch->getLocation();
    setFocused(hitTest(_touchMovePos));
    UIWidget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void UIWidget::onTouchEnded(Touch *touch, Event *unused_event)
{
    _touchEndPos = touch->getLocation();
    bool focus = _focus;
    setFocused(false);
    UIWidget* widgetParent = getWidgetParent();
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

void UIWidget::onTouchCancelled(Touch *touch, Event *unused_event)
{
    setFocused(false);
    cancelUpEvent();
}

void UIWidget::onTouchLongClicked(const Point &touchPoint)
{
    longClickEvent();
}

void UIWidget::pushDownEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_BEGAN);
    }
}

void UIWidget::moveEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_MOVED);
    }
}

void UIWidget::releaseUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_ENDED);
    }
}

void UIWidget::cancelUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_CANCELED);
    }
}

void UIWidget::longClickEvent()
{
    
}

void UIWidget::addTouchEventListener(Object *target, SEL_TouchEvent selector)
{
    _touchEventListener = target;
    _touchEventSelector = selector;
}

Node* UIWidget::getRenderer()
{
    return _renderer;
}

void UIWidget::addRenderer(Node* renderer, int zOrder)
{
    _renderer->addChild(renderer, zOrder);
}

void UIWidget::removeRenderer(Node* renderer, bool cleanup)
{
    _renderer->removeChild(renderer,cleanup);
}

bool UIWidget::hitTest(const Point &pt)
{
    Point nsp = _renderer->convertToNodeSpace(pt);
    Rect bb = Rect(-_size.width * _anchorPoint.x, -_size.height * _anchorPoint.y, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::clippingParentAreaContainPoint(const Point &pt)
{
    _affectByClipping = false;
    UIWidget* parent = getWidgetParent();
    UIWidget* clippingParent = nullptr;
    while (parent)
    {
        UILayout* layoutParent = dynamic_cast<UILayout*>(parent);
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

void UIWidget::checkChildInfo(int handleState, UIWidget *sender, const Point &touchPoint)
{
    UIWidget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const Point &pos)
{
    if (_running)
    {
        UIWidget* widgetParent = getWidgetParent();
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

void UIWidget::setPositionPercent(const Point &percent)
{
    _positionPercent = percent;
    if (_running)
    {
        UIWidget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            Size parentSize = widgetParent->getSize();
            Point absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            _renderer->setPosition(absPos);
        }
    }
}

void UIWidget::setAnchorPoint(const Point &pt)
{
    NodeRGBA::setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(getAnchorPoint());
}

const Point& UIWidget::getPositionPercent()
{
    return _positionPercent;
}

void UIWidget::setPositionType(PositionType type)
{
    _positionType = type;
}

PositionType UIWidget::getPositionType() const
{
    return _positionType;
}

const Point& UIWidget::getAnchorPoint() const
{
    return NodeRGBA::getAnchorPoint();
}

void UIWidget::setVisible(bool visible)
{
    _visible = visible;
    _renderer->setVisible(visible);
}

bool UIWidget::isVisible() const
{
    return _visible;
}

bool UIWidget::isBright() const
{
    return _bright;
}

bool UIWidget::isEnabled() const
{
    return _enabled;
}

float UIWidget::getLeftInParent()
{
    return getPosition().x - getAnchorPoint().x * _size.width;;
}

float UIWidget::getBottomInParent()
{
    return getPosition().y - getAnchorPoint().y * _size.height;;
}

float UIWidget::getRightInParent()
{
    return getLeftInParent() + _size.width;
}

float UIWidget::getTopInParent()
{
    return getBottomInParent() + _size.height;
}

const Point& UIWidget::getTouchStartPos()
{
    return _touchStartPos;
}

const Point& UIWidget::getTouchMovePos()
{
    return _touchMovePos;
}

const Point& UIWidget::getTouchEndPos()
{
    return _touchEndPos;
}

void UIWidget::setName(const char* name)
{
    _name = name;
}

const char* UIWidget::getName() const
{
    return _name.c_str();
}

WidgetType UIWidget::getWidgetType() const
{
    return _widgetType;
}

void UIWidget::setLayoutParameter(UILayoutParameter *parameter)
{
    if (!parameter)
    {
        return;
    }
    _layoutParameterDictionary->setObject(parameter, parameter->getLayoutType());
}

UILayoutParameter* UIWidget::getLayoutParameter(LayoutParameterType type)
{
    return dynamic_cast<UILayoutParameter*>(_layoutParameterDictionary->objectForKey(type));
}

const char* UIWidget::getDescription() const
{
    return "Widget";
}

UIWidget* UIWidget::clone()
{
    UIWidget* clonedWidget = createCloneInstance();
    clonedWidget->copyProperties(this);
    clonedWidget->copyClonedWidgetChildren(this);
    return clonedWidget;
}

UIWidget* UIWidget::createCloneInstance()
{
    return UIWidget::create();
}

void UIWidget::copyClonedWidgetChildren(UIWidget* model)
{
    int length = model->getChildren().size();
    for (int i=0; i<length; i++)
    {
        UIWidget* child = (UIWidget*)(model->getChildren().at(i));
        addChild(child->clone());
    }
}

void UIWidget::copySpecialProperties(UIWidget* model)
{
    
}

void UIWidget::copyProperties(UIWidget *widget)
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
void UIWidget::setActionTag(int tag)
{
	_actionTag = tag;
}

int UIWidget::getActionTag()
{
	return _actionTag;
}
    
}

NS_CC_END
