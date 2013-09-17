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

#include "UIWidget.h"
#include "../System/UILayer.h"
#include "../Layouts/Layout.h"
#include "../System/UIHelper.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCBLENDPROTOCOL dynamic_cast<cocos2d::BlendProtocol*>(_renderer)

#define DYNAMIC_CAST_CCRGBAPROTOCOL dynamic_cast<cocos2d::RGBAProtocol*>(_renderer)

#define DYNAMIC_CAST_CCNODERGBA dynamic_cast<GUIRenderer*>(_renderer)
    
UIWidget::UIWidget():
_enabled(true),
_visible(true),
_bright(true),
_touchEnabled(false),
_touchPassedEnabled(false),
_focus(false),
_widgetZOrder(0),
_anchorPoint(Point(0.5f, 0.5f)),
_widgetParent(NULL),
_brightStyle(BRIGHT_NONE),
_updateEnabled(false),
_renderer(NULL),
_touchStartPos(Point::ZERO),
_touchMovePos(Point::ZERO),
_touchEndPos(Point::ZERO),
_touchEventListener(NULL),
_touchEventSelector(NULL),
_widgetTag(-1),
_name("default"),
_widgetType(WidgetTypeWidget),
_actionTag(0),
_size(Size::ZERO),
_customSize(Size::ZERO),
_layoutParameter(NULL),
_ignoreSize(false),
_children(NULL),
_affectByClipping(false),
_scheduler(NULL),
_sizeType(SIZE_ABSOLUTE),
_sizePercent(Point::ZERO),
_positionType(POSITION_ABSOLUTE),
_positionPercent(Point::ZERO),
_isRunning(false)
{
    
}

UIWidget::~UIWidget()
{
    releaseResoures();
    setParent(NULL);
    CC_SAFE_RELEASE_NULL(_layoutParameter);
    CC_SAFE_RELEASE(_scheduler);
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
    return NULL;
}

bool UIWidget::init()
{
    _children = Array::create();
    _children->retain();
    initRenderer();
    _renderer->retain();
    _renderer->setZOrder(_widgetZOrder);
    RGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    setBright(true);
    ignoreContentAdaptWithSize(true);
    _scheduler = Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(_scheduler);
    return true;
}

void UIWidget::releaseResoures()
{
    setUpdateEnabled(false);
    removeAllChildren();
    _children->release();
    _renderer->removeAllChildrenWithCleanup(true);
    _renderer->removeFromParentAndCleanup(true);
    _renderer->release();
}

void UIWidget::onEnter()
{
    arrayMakeObjectsPerformSelector(_children, onEnter, UIWidget*);
    _isRunning = true;
    updateSizeAndPosition();
}

void UIWidget::onExit()
{
    _isRunning = false;
    arrayMakeObjectsPerformSelector(_children, onExit, UIWidget*);
}

bool UIWidget::addChild(UIWidget *child)
{
    if (!child)
    {
        return false;
    }
    if (_children->containsObject(child))
    {
        return false;
    }
    child->setParent(this);
    int childrenCount = _children->data->num;
    if (childrenCount <= 0)
    {
        _children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = _children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getZOrder() >= widget->getZOrder())
            {
                if (i == childrenCount-1)
                {
                    _children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    _children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            _children->insertObject(child,0);
        }
    }
    child->getRenderer()->setZOrder(child->getZOrder());
    _renderer->addChild(child->getRenderer());
    if (_isRunning)
    {
        child->onEnter();
    }
    return true;
}

bool UIWidget::removeChild(UIWidget *child)
{
    if (!child)
    {
        return false;
    }
    if (_children->containsObject(child))
    {
        if (_isRunning)
        {
            child->onExit();    
        }
        child->disableUpdate();
        child->setParent(NULL);
        _renderer->removeChild(child->getRenderer());
        _children->removeObject(child);
        return true;
    }
    return false;
}

void UIWidget::removeFromParent()
{
    if (_widgetParent)
    {
        _widgetParent->removeChild(this);
    }
}

void UIWidget::removeAllChildren()
{
    if (!_children || _children->count() <= 0)
    {
        return;
    }
    int times = _children->data->num;
    for (int i=0; i<times; ++i)
    {
        UIWidget* lastChild = (UIWidget*)(_children->getLastObject());
        removeChild(lastChild);
    }
}

void UIWidget::reorderChild(UIWidget* child)
{
    CC_SAFE_RETAIN(child);
    _children->removeObject(child);
    int childrenCount = _children->data->num;
    if (childrenCount <= 0)
    {
        _children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = _children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getZOrder() >= widget->getZOrder())
            {
                if (i == childrenCount-1)
                {
                    _children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    _children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            _children->insertObject(child,0);
        }
    }
    CC_SAFE_RELEASE(child);
}

void UIWidget::disableUpdate()
{
    if (_scheduler)
    {
        _scheduler->unscheduleUpdateForTarget(this);
    }
    int childrenCount = _children->data->num;
    ccArray* arrayChildren = _children->data;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->disableUpdate();
    }
}

void UIWidget::setEnabled(bool enabled)
{
    _enabled = enabled;
    GUIRenderer* renderer = DYNAMIC_CAST_CCNODERGBA;
    if (renderer)
    {
        renderer->setEnabled(enabled);
    }
    else
    {
        dynamic_cast<RectClippingNode*>(_renderer)->setEnabled(enabled);
    }
    ccArray* arrayChildren = _children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        child->setEnabled(enabled);
    }
}

UIWidget* UIWidget::getChildByName(const char *name)
{
    return CCUIHELPER->seekWidgetByName(this, name);
}

UIWidget* UIWidget::getChildByTag(int tag)
{
    return CCUIHELPER->seekWidgetByTag(this, tag);
}

Array* UIWidget::getChildren()
{
    return _children;
}

void UIWidget::initRenderer()
{
    _renderer = GUIRenderer::create();
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
    if (_isRunning)
    {
        _sizePercent = (_widgetParent == NULL) ? Point::ZERO : Point(_customSize.width / _widgetParent->getSize().width, _customSize.height / _widgetParent->getSize().height);
    }
    onSizeChanged();
}

void UIWidget::setSizePercent(const Point &percent)
{
    _sizePercent = percent;
    if (!_isRunning)
    {
        return;
    }
    Size cSize = (_widgetParent == NULL) ? Size::ZERO : Size(_widgetParent->getSize().width * percent.x , _widgetParent->getSize().height * percent.y);
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
            if (_ignoreSize)
            {
                _size = getContentSize();
            }
            else
            {
                _size = _customSize;
            }
            _sizePercent = (_widgetParent == NULL) ? Point::ZERO : Point(_customSize.width / _widgetParent->getSize().width, _customSize.height / _widgetParent->getSize().height);
            break;
        case SIZE_PERCENT:
        {
            Size cSize = (_widgetParent == NULL) ? Size::ZERO : Size(_widgetParent->getSize().width * _sizePercent.x , _widgetParent->getSize().height * _sizePercent.y);
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
            break;
        default:
            break;
    }
    onSizeChanged();
    Point absPos = getPosition();
    switch (_positionType)
    {
        case POSITION_ABSOLUTE:
            _positionPercent = (_widgetParent == NULL) ? Point::ZERO : Point(absPos.x / _widgetParent->getSize().width, absPos.y / _widgetParent->getSize().height);
            break;
        case POSITION_PERCENT:
        {
            Size parentSize = _widgetParent->getSize();
            absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
        }
            break;
        default:
            break;
    }
    _renderer->setPosition(absPos);
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

Point UIWidget::convertToWorldSpace(const Point& pt)
{
    return _renderer->convertToWorldSpace(pt);
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

void UIWidget::setZOrder(int z)
{
    _widgetZOrder = z;
    _renderer->setZOrder(z);
    if (_widgetParent)
    {
        _widgetParent->reorderChild(this);
    }
}

int UIWidget::getZOrder()
{
    return _widgetZOrder;
}

void UIWidget::setTouchEnabled(bool enable)
{
    _touchEnabled = enable;
}

bool UIWidget::isTouchEnabled() const
{
    return _touchEnabled;
}

void UIWidget::setUpdateEnabled(bool enable)
{
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

bool UIWidget::onTouchBegan(const Point &touchPoint)
{
    setFocused(true);
    _touchStartPos.x = touchPoint.x;
    _touchStartPos.y = touchPoint.y;
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(0,this,touchPoint);
    }
    pushDownEvent();
    return _touchPassedEnabled;
}

void UIWidget::onTouchMoved(const Point &touchPoint)
{
    _touchMovePos.x = touchPoint.x;
    _touchMovePos.y = touchPoint.y;
    setFocused(hitTest(touchPoint));
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
}

void UIWidget::onTouchEnded(const Point &touchPoint)
{
    _touchEndPos.x = touchPoint.x;
    _touchEndPos.y = touchPoint.y;
    bool focus = _focus;
    setFocused(false);
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(2,this,touchPoint);
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

void UIWidget::onTouchCancelled(const Point &touchPoint)
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
    UIWidget* parent = getParent();
    UIWidget* clippingParent = NULL;
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
        parent = parent->getParent();
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
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const Point &pos)
{
    if (_isRunning)
    {
        _positionPercent = (_widgetParent == NULL) ? Point::ZERO : Point(pos.x / _widgetParent->getSize().width, pos.y / _widgetParent->getSize().height);
    }
    _renderer->setPosition(pos);
}

void UIWidget::setPositionPercent(const Point &percent)
{
    _positionPercent = percent;
    if (_isRunning)
    {
        Size parentSize = _widgetParent->getSize();
        Point absPos = Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
        _renderer->setPosition(absPos);
    }
}

void UIWidget::setAnchorPoint(const Point &pt)
{
    _anchorPoint = pt;
    _renderer->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(_anchorPoint);
}

const Point& UIWidget::getPosition()
{
    return _renderer->getPosition();
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

const Point& UIWidget::getAnchorPoint()
{
    return _anchorPoint;
}

void UIWidget::setScale(float scale)
{
    _renderer->setScale(scale);
}

float UIWidget::getScale()
{
    return _renderer->getScale();
}

void UIWidget::setScaleX(float scaleX)
{
    _renderer->setScaleX(scaleX);
}

float UIWidget::getScaleX()
{
    return _renderer->getScaleX();
}

void UIWidget::setScaleY(float scaleY)
{
    _renderer->setScaleY(scaleY);
}

float UIWidget::getScaleY()
{
    return _renderer->getScaleY();
}

void UIWidget::setRotation(float rotation)
{
    _renderer->setRotation(rotation);
}

float UIWidget::getRotation()
{
    return _renderer->getRotation();
}

void UIWidget::setRotationX(float rotationX)
{
    _renderer->setRotationX(rotationX);
}

float UIWidget::getRotationX()
{
    return _renderer->getRotationX();
}

void UIWidget::setRotationY(float rotationY)
{
    _renderer->setRotationY(rotationY);
}

float UIWidget::getRotationY()
{
    return _renderer->getRotationY();
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
    float leftPos = 0.0f;
    switch (_widgetType)
    {
        case WidgetTypeWidget:
            leftPos = getPosition().x - getAnchorPoint().x * _size.width;
            break;
        case WidgetTypeContainer:
            leftPos = getPosition().x;
            break;
        default:
            break;
    }
    return leftPos;
}

float UIWidget::getBottomInParent()
{
    float bottomPos = 0.0f;
    switch (_widgetType)
    {
        case WidgetTypeWidget:
            bottomPos = getPosition().y - getAnchorPoint().y * _size.height;
            break;
        case WidgetTypeContainer:
            bottomPos = getPosition().y;
            break;
        default:
            break;
    }
    return bottomPos;
}

float UIWidget::getRightInParent()
{
    return getLeftInParent() + _size.width;
}

float UIWidget::getTopInParent()
{
    return getBottomInParent() + _size.height;
}

UIWidget* UIWidget::getParent()
{
    return _widgetParent;
}

void UIWidget::setParent(UIWidget* parent)
{
	_widgetParent = parent;
}

Action* UIWidget::runAction(Action *action)
{
    return _renderer->runAction(action);
}

void UIWidget::setActionManager(ActionManager *actionManager)
{
    _renderer->setActionManager(actionManager);
}

ActionManager* UIWidget::getActionManager()
{
    return _renderer->getActionManager();
}

void UIWidget::stopAllActions()
{
    _renderer->stopAllActions();
}

void UIWidget::stopAction(Action *action)
{
    _renderer->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    _renderer->stopActionByTag(tag);
}

Action* UIWidget::getActionByTag(int tag)
{
    return _renderer->getActionByTag(tag);
}  

void UIWidget::setColor(const Color3B &color)
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setColor(color);
    }
}

const Color3B& UIWidget::getColor()
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getColor();
    }
    return Color3B::WHITE;
}

void UIWidget::setOpacity(int opacity)
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setOpacity(opacity);
    }
}

int UIWidget::getOpacity()
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getOpacity();
    }
    return 255;
}

bool UIWidget::isCascadeOpacityEnabled()
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeOpacityEnabled();
    }
    return false;
}

void UIWidget::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    }
}

bool UIWidget::isCascadeColorEnabled()
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeColorEnabled();
    }
    return false;
}

void UIWidget::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeColorEnabled(cascadeColorEnabled);
    }
}

void UIWidget::setBlendFunc(BlendFunc blendFunc)
{
    BlendProtocol * blendNode = DYNAMIC_CAST_CCBLENDPROTOCOL;
    if (blendNode)
    {
        blendNode->setBlendFunc(blendFunc);
    }
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

void UIWidget::setTag(int tag)
{
    _widgetTag = tag;
}

int UIWidget::getTag() const
{
    return _widgetTag;
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

void UIWidget::setLayoutParameter(LayoutParameter *parameter)
{
    if (_layoutParameter)
    {
        CC_SAFE_RELEASE_NULL(_layoutParameter);
    }
    _layoutParameter = parameter;
    CC_SAFE_RETAIN(_layoutParameter);
}

LayoutParameter* UIWidget::getLayoutParameter()
{
    return _layoutParameter;
}

const char* UIWidget::getDescription() const
{
    return "Widget";
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

GUIRenderer::GUIRenderer():
_enabled(true)
{
    
}

GUIRenderer::~GUIRenderer()
{
    
}

GUIRenderer* GUIRenderer::create()
{
    GUIRenderer* renderer = new GUIRenderer();
    if (renderer && renderer->init())
    {
        renderer->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(renderer);
    }
    return renderer;
}

void GUIRenderer::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool GUIRenderer::isEnabled() const
{
    return _enabled;
}

void GUIRenderer::visit()
{
    if (!_enabled)
    {
        return;
    }
    NodeRGBA::visit();
}

NS_CC_EXT_END
