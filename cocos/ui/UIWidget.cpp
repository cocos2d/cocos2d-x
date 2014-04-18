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

#include "ui/UIWidget.h"
#include "ui/UILayout.h"
#include "ui/UIHelper.h"

NS_CC_BEGIN

namespace ui {

Widget::Widget():
_enabled(true),
_bright(true),
_touchEnabled(false),
_touchPassedEnabled(false),
_focus(false),
_brightStyle(BRIGHT_NONE),
_touchStartPos(Vector2::ZERO),
_touchMovePos(Vector2::ZERO),
_touchEndPos(Vector2::ZERO),
_touchEventListener(nullptr),
_touchEventSelector(nullptr),
_name("default"),
_widgetType(WidgetTypeWidget),
_actionTag(0),
_size(Size::ZERO),
_customSize(Size::ZERO),
_ignoreSize(false),
_affectByClipping(false),
_sizeType(SIZE_ABSOLUTE),
_sizePercent(Vector2::ZERO),
_positionType(POSITION_ABSOLUTE),
_positionPercent(Vector2::ZERO),
_reorderWidgetChildDirty(true),
_hitted(false),
_touchListener(nullptr),
_color(Color3B::WHITE),
_opacity(255),
_flippedX(false),
_flippedY(false)
{

}

Widget::~Widget()
{
    _touchEventListener = nullptr;
    _touchEventSelector = nullptr;
    setTouchEnabled(false);
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
    if (ProtectedNode::init())
    {
        initRenderer();
        setBright(true);
        ignoreContentAdaptWithSize(true);
        setAnchorPoint(Vector2(0.5f, 0.5f));
        return true;
    }
    return false;
}

void Widget::onEnter()
{
    updateSizeAndPosition();
    ProtectedNode::onEnter();
}

void Widget::onExit()
{
    unscheduleUpdate();
    ProtectedNode::onExit();
}

void Widget::visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated)
{
    if (_enabled)
    {
        adaptRenderers();
        ProtectedNode::visit(renderer, parentTransform, parentTransformUpdated);
    }
}

Widget* Widget::getWidgetParent()
{
    return dynamic_cast<Widget*>(getParent());
}

void Widget::setEnabled(bool enabled)
{
    _enabled = enabled;
    for (auto& child : _children)
    {
        if (child)
        {
            Widget* widgetChild = dynamic_cast<Widget*>(child);
            if (widgetChild)
            {
                widgetChild->setEnabled(enabled);
            }
        }
    }
    
    for (auto& child : _protectedChildren)
    {
        if (child)
        {
            Widget* widgetChild = dynamic_cast<Widget*>(child);
            if (widgetChild)
            {
                widgetChild->setEnabled(enabled);
            }
        }
    }
}

Widget* Widget::getChildByName(const char *name)
{
    for (auto& child : _children)
    {
        if (child)
        {
            Widget* widgetChild = dynamic_cast<Widget*>(child);
            if (widgetChild)
            {
                if (strcmp(widgetChild->getName(), name) == 0)
                {
                    return widgetChild;
                }
            }
        }
    }
    return nullptr;
}
    
void Widget::initRenderer()
{
}

void Widget::setSize(const Size &size)
{
    _customSize = size;
    if (_ignoreSize)
    {
        _size = getVirtualRendererSize();
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
        _sizePercent = Vector2(spx, spy);
    }
    onSizeChanged();
}

void Widget::setSizePercent(const Vector2 &percent)
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
        _size = getVirtualRendererSize();
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
    Widget* widgetParent = getWidgetParent();
    Size pSize;
    if (widgetParent)
    {
        pSize = widgetParent->getLayoutSize();
    }
    else
    {
        pSize = _parent->getContentSize();
    }
    updateSizeAndPosition(pSize);
}
    
void Widget::updateSizeAndPosition(const cocos2d::Size &parentSize)
{
    switch (_sizeType)
    {
        case SIZE_ABSOLUTE:
        {
            if (_ignoreSize)
            {
                _size = getVirtualRendererSize();
            }
            else
            {
                _size = _customSize;
            }
            float spx = 0.0f;
            float spy = 0.0f;
            if (parentSize.width > 0.0f)
            {
                spx = _customSize.width / parentSize.width;
            }
            if (parentSize.height > 0.0f)
            {
                spy = _customSize.height / parentSize.height;
            }
            _sizePercent = Vector2(spx, spy);
            break;
        }
        case SIZE_PERCENT:
        {
            Size cSize = Size(parentSize.width * _sizePercent.x , parentSize.height * _sizePercent.y);
            if (_ignoreSize)
            {
                _size = getVirtualRendererSize();
            }
            else
            {
                _size = cSize;
            }
            _customSize = cSize;
            break;
        }
        default:
            break;
    }
    onSizeChanged();
    Vector2 absPos = getPosition();
    switch (_positionType)
    {
        case POSITION_ABSOLUTE:
        {
            if (parentSize.width <= 0.0f || parentSize.height <= 0.0f)
            {
                _positionPercent = Vector2::ZERO;
            }
            else
            {
                _positionPercent = Vector2(absPos.x / parentSize.width, absPos.y / parentSize.height);
            }
            break;
        }
        case POSITION_PERCENT:
        {
            absPos = Vector2(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
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
    if (_ignoreSize == ignore)
    {
        return;
    }
    _ignoreSize = ignore;
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
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
    
const Size& Widget::getCustomSize() const
{
    return _customSize;
}

const Vector2& Widget::getSizePercent() const
{
    return _sizePercent;
}

Vector2 Widget::getWorldPosition()
{
    return convertToWorldSpace(Vector2(_anchorPoint.x * _contentSize.width, _anchorPoint.y * _contentSize.height));
}

Node* Widget::getVirtualRenderer()
{
    return this;
}

void Widget::onSizeChanged()
{
    setContentSize(_size);
    for (auto& child : getChildren())
    {
        Widget* widgetChild = dynamic_cast<Widget*>(child);
        if (widgetChild)
        {
            widgetChild->updateSizeAndPosition();
        }
    }
}

const Size& Widget::getVirtualRendererSize() const
{
    return _contentSize;
}
    
void Widget::updateContentSizeWithTextureSize(const cocos2d::Size &size)
{
    if (_ignoreSize)
    {
        _size = size;
    }
    else
    {
        _size = _customSize;
    }
    onSizeChanged();
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
        _touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(_touchListener);
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = CC_CALLBACK_2(Widget::onTouchBegan, this);
        _touchListener->onTouchMoved = CC_CALLBACK_2(Widget::onTouchMoved, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(Widget::onTouchEnded, this);
        _touchListener->onTouchCancelled = CC_CALLBACK_2(Widget::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    else
    {
        _eventDispatcher->removeEventListener(_touchListener);
        CC_SAFE_RELEASE_NULL(_touchListener);
    }
}

bool Widget::isTouchEnabled() const
{
    return _touchEnabled;
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

bool Widget::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    _hitted = false;
    if (isEnabled() && isTouchEnabled())
    {
        _touchStartPos = touch->getLocation();
        if(hitTest(_touchStartPos) && clippingParentAreaContainPoint(_touchStartPos))
        {
            _hitted = true;
        }
    }
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

void Widget::onTouchMoved(Touch *touch, Event *unusedEvent)
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

void Widget::onTouchEnded(Touch *touch, Event *unusedEvent)
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

void Widget::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    setFocused(false);
    cancelUpEvent();
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

void Widget::addTouchEventListener(Ref *target, SEL_TouchEvent selector)
{
    _touchEventListener = target;
    _touchEventSelector = selector;
}

bool Widget::hitTest(const Vector2 &pt)
{
    Vector2 nsp = convertToNodeSpace(pt);
    Rect bb;
    bb.size = _contentSize;
    if (bb.containsPoint(nsp))
    {
        return true;
    }
    return false;
}

bool Widget::clippingParentAreaContainPoint(const Vector2 &pt)
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

void Widget::checkChildInfo(int handleState, Widget *sender, const Vector2 &touchPoint)
{
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void Widget::setPosition(const Vector2 &pos)
{
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            Size pSize = widgetParent->getSize();
            if (pSize.width <= 0.0f || pSize.height <= 0.0f)
            {
                _positionPercent = Vector2::ZERO;
            }
            else
            {
                _positionPercent = Vector2(pos.x / pSize.width, pos.y / pSize.height);
            }
        }
    }
    ProtectedNode::setPosition(pos);
}

void Widget::setPositionPercent(const Vector2 &percent)
{
    _positionPercent = percent;
    if (_running)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            Size parentSize = widgetParent->getSize();
            Vector2 absPos = Vector2(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            setPosition(absPos);
        }
    }
}

const Vector2& Widget::getPositionPercent()
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

const Vector2& Widget::getTouchStartPos()
{
    return _touchStartPos;
}

const Vector2& Widget::getTouchMovePos()
{
    return _touchMovePos;
}

const Vector2& Widget::getTouchEndPos()
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
    _layoutParameterDictionary.insert(parameter->getLayoutType(), parameter);
}

LayoutParameter* Widget::getLayoutParameter(LayoutParameterType type)
{
    return dynamic_cast<LayoutParameter*>(_layoutParameterDictionary.at(type));
}

std::string Widget::getDescription() const
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
    auto& modelChildren = model->getChildren();

    for (auto& subWidget : modelChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            addChild(child->clone());
        }
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
    setLocalZOrder(widget->getLocalZOrder());
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
    setRotationSkewX(widget->getRotationSkewX());
    setRotationSkewY(widget->getRotationSkewY());
    setFlippedX(widget->isFlippedX());
    setFlippedY(widget->isFlippedY());
    setColor(widget->getColor());
    setOpacity(widget->getOpacity());
    Map<int, LayoutParameter*>& layoutParameterDic = widget->_layoutParameterDictionary;
    for (auto iter = layoutParameterDic.begin(); iter != layoutParameterDic.end(); ++iter)
    {
        setLayoutParameter(iter->second->clone());
    }
    onSizeChanged();
}
    
void Widget::setColor(const Color3B& color)
{
    _color = color;
    updateTextureColor();
}

void Widget::setOpacity(GLubyte opacity)
{
    _opacity = opacity;
    updateTextureOpacity();
}
    
void Widget::setFlippedX(bool flippedX)
{
    _flippedX = flippedX;
    updateFlippedX();
}

void Widget::setFlippedY(bool flippedY)
{
    _flippedY = flippedY;
    updateFlippedY();
}

void Widget::updateColorToRenderer(Node* renderer)
{
    renderer->setColor(_color);
}

void Widget::updateOpacityToRenderer(Node* renderer)
{
    renderer->setOpacity(_opacity);
}

void Widget::updateRGBAToRenderer(Node* renderer)
{
    renderer->setColor(_color);
    renderer->setOpacity(_opacity);
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
