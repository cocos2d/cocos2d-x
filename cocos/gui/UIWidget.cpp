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
#include "gui/UILayer.h"
#include "gui/UILayout.h"
#include "gui/UIHelper.h"

namespace gui {

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
_anchorPoint(cocos2d::Point(0.5f, 0.5f)),
_widgetParent(nullptr),
_brightStyle(BRIGHT_NONE),
_updateEnabled(false),
_renderer(nullptr),
_touchStartPos(cocos2d::Point::ZERO),
_touchMovePos(cocos2d::Point::ZERO),
_touchEndPos(cocos2d::Point::ZERO),
_touchEventListener(nullptr),
_touchEventSelector(nullptr),
_widgetTag(-1),
_name("default"),
_widgetType(WidgetTypeWidget),
_actionTag(0),
_size(cocos2d::Size::ZERO),
_customSize(cocos2d::Size::ZERO),
_layoutParameterDictionary(nullptr),
_ignoreSize(false),
_children(nullptr),
_affectByClipping(false),
_scheduler(nullptr),
_sizeType(SIZE_ABSOLUTE),
_sizePercent(cocos2d::Point::ZERO),
_positionType(POSITION_ABSOLUTE),
_positionPercent(cocos2d::Point::ZERO),
_isRunning(false),
_userObject(nullptr)
{
    
}

UIWidget::~UIWidget()
{
    _touchEventListener = nullptr;
    _touchEventSelector = nullptr;
    removeAllChildren();
    _children->release();
    _renderer->removeAllChildrenWithCleanup(true);
    _renderer->removeFromParentAndCleanup(true);
    _renderer->release();
    setParent(nullptr);
    _layoutParameterDictionary->removeAllObjects();
    CC_SAFE_RELEASE(_layoutParameterDictionary);
    CC_SAFE_RELEASE(_scheduler);
    CC_SAFE_RELEASE(_userObject);
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
    _children = cocos2d::Array::create();
    _children->retain();
    _layoutParameterDictionary = cocos2d::Dictionary::create();
    CC_SAFE_RETAIN(_layoutParameterDictionary);
    initRenderer();
    _renderer->retain();
    _renderer->setZOrder(_widgetZOrder);
    cocos2d::RGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    setBright(true);
    ignoreContentAdaptWithSize(true);
    _scheduler = cocos2d::Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(_scheduler);
    return true;
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
    
void UIWidget::setUserObject(cocos2d::Object *pUserObject)
{
    CC_SAFE_RETAIN(pUserObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = pUserObject;
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
        cocos2d::ccArray* arrayChildren = _children->data;
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
        child->setUpdateEnabled(false);
        child->setParent(nullptr);
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
        cocos2d::ccArray* arrayChildren = _children->data;
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
        dynamic_cast<UIRectClippingNode*>(_renderer)->setEnabled(enabled);
    }
    cocos2d::ccArray* arrayChildren = _children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        child->setEnabled(enabled);
    }
}

UIWidget* UIWidget::getChildByName(const char *name)
{
    return UIHelper::seekWidgetByName(this, name);
}

UIWidget* UIWidget::getChildByTag(int tag)
{
    return UIHelper::seekWidgetByTag(this, tag);
}

cocos2d::Array* UIWidget::getChildren()
{
    return _children;
}

void UIWidget::initRenderer()
{
    _renderer = GUIRenderer::create();
}

void UIWidget::setSize(const cocos2d::Size &size)
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
    if (_isRunning && _widgetParent)
    {
        cocos2d::Size pSize = _widgetParent->getSize();
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
        _sizePercent = cocos2d::Point(spx, spy);
    }
    
    onSizeChanged();
}

void UIWidget::setSizePercent(const cocos2d::Point &percent)
{
    _sizePercent = percent;
    cocos2d::Size cSize = _customSize;
    if (_isRunning)
    {
        cSize = (_widgetParent == nullptr) ? cocos2d::Size::ZERO : cocos2d::Size(_widgetParent->getSize().width * percent.x , _widgetParent->getSize().height * percent.y);
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
            if (_widgetParent)
            {
                cocos2d::Size pSize = _widgetParent->getSize();
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
                _sizePercent = cocos2d::Point(spx, spy);
            }
            break;
        }
        case SIZE_PERCENT:
        {
            cocos2d::Size cSize = (_widgetParent == NULL) ? cocos2d::Size::ZERO : cocos2d::Size(_widgetParent->getSize().width * _sizePercent.x , _widgetParent->getSize().height * _sizePercent.y);
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
    cocos2d::Point absPos = getPosition();
    switch (_positionType)
    {
        case POSITION_ABSOLUTE:
        {
            if (_widgetParent)
            {
                cocos2d::Size pSize = _widgetParent->getSize();
                if (pSize.width <= 0.0f || pSize.height <= 0.0f)
                {
                    _positionPercent = cocos2d::Point::ZERO;
                }
                else
                {
                    _positionPercent = cocos2d::Point(absPos.x / pSize.width, absPos.y / pSize.height);
                }
            }
            else
            {
                _positionPercent = cocos2d::Point::ZERO;
            }
            break;
        }
        case POSITION_PERCENT:
        {
            if (_widgetParent)
            {
                cocos2d::Size parentSize = _widgetParent->getSize();
                absPos = cocos2d::Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            }
            else
            {
                absPos = cocos2d::Point::ZERO;
            }
            break;
        }
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
        cocos2d::Size s = getContentSize();
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

const cocos2d::Size& UIWidget::getSize() const
{
    return _size;
}

const cocos2d::Point& UIWidget::getSizePercent() const
{
    return _sizePercent;
}

cocos2d::Point UIWidget::getWorldPosition()
{
    return _renderer->convertToWorldSpace(cocos2d::Point::ZERO);
}

cocos2d::Point UIWidget::convertToWorldSpace(const cocos2d::Point& pt)
{
    return _renderer->convertToWorldSpace(pt);
}

cocos2d::Node* UIWidget::getVirtualRenderer()
{
    return _renderer;
}

void UIWidget::onSizeChanged()
{

}

const cocos2d::Size& UIWidget::getContentSize() const
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

bool UIWidget::onTouchBegan(const cocos2d::Point &touchPoint)
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

void UIWidget::onTouchMoved(const cocos2d::Point &touchPoint)
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

void UIWidget::onTouchEnded(const cocos2d::Point &touchPoint)
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

void UIWidget::onTouchCancelled(const cocos2d::Point &touchPoint)
{
    setFocused(false);
    cancelUpEvent();
}

void UIWidget::onTouchLongClicked(const cocos2d::Point &touchPoint)
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

void UIWidget::addTouchEventListener(cocos2d::Object *target, SEL_TouchEvent selector)
{
    _touchEventListener = target;
    _touchEventSelector = selector;
}

cocos2d::Node* UIWidget::getRenderer()
{
    return _renderer;
}

void UIWidget::addRenderer(cocos2d::Node* renderer, int zOrder)
{
    _renderer->addChild(renderer, zOrder);
}

void UIWidget::removeRenderer(cocos2d::Node* renderer, bool cleanup)
{
    _renderer->removeChild(renderer,cleanup);
}

bool UIWidget::hitTest(const cocos2d::Point &pt)
{
    cocos2d::Point nsp = _renderer->convertToNodeSpace(pt);
    cocos2d::Rect bb = cocos2d::Rect(-_size.width * _anchorPoint.x, -_size.height * _anchorPoint.y, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::clippingParentAreaContainPoint(const cocos2d::Point &pt)
{
    _affectByClipping = false;
    UIWidget* parent = getParent();
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

void UIWidget::checkChildInfo(int handleState, UIWidget *sender, const cocos2d::Point &touchPoint)
{
    if (_widgetParent)
    {
        _widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const cocos2d::Point &pos)
{
    if (_isRunning && _widgetParent)
    {
        cocos2d::Size pSize = _widgetParent->getSize();
        if (pSize.width <= 0.0f || pSize.height <= 0.0f)
        {
            _positionPercent = cocos2d::Point::ZERO;
        }
        else
        {
            _positionPercent = (_widgetParent == NULL) ? cocos2d::Point::ZERO : cocos2d::Point(pos.x / pSize.width, pos.y / pSize.height);
        }
    }
    _renderer->setPosition(pos);
}

void UIWidget::setPositionPercent(const cocos2d::Point &percent)
{
    _positionPercent = percent;
    if (_isRunning && _widgetParent)
    {
        cocos2d::Size parentSize = _widgetParent->getSize();
        cocos2d::Point absPos = cocos2d::Point(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
        _renderer->setPosition(absPos);
    }
}

void UIWidget::setAnchorPoint(const cocos2d::Point &pt)
{
    _anchorPoint = pt;
    _renderer->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(_anchorPoint);
}

const cocos2d::Point& UIWidget::getPosition()
{
    return _renderer->getPosition();
}

const cocos2d::Point& UIWidget::getPositionPercent()
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

const cocos2d::Point& UIWidget::getAnchorPoint()
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

UIWidget* UIWidget::getParent()
{
    return _widgetParent;
}

void UIWidget::setParent(UIWidget* parent)
{
	_widgetParent = parent;
}

cocos2d::Action* UIWidget::runAction(cocos2d::Action *action)
{
    return _renderer->runAction(action);
}

void UIWidget::setActionManager(cocos2d::ActionManager *actionManager)
{
    _renderer->setActionManager(actionManager);
}

cocos2d::ActionManager* UIWidget::getActionManager()
{
    return _renderer->getActionManager();
}

void UIWidget::stopAllActions()
{
    _renderer->stopAllActions();
}

void UIWidget::stopAction(cocos2d::Action *action)
{
    _renderer->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    _renderer->stopActionByTag(tag);
}

cocos2d::Action* UIWidget::getActionByTag(int tag)
{
    return _renderer->getActionByTag(tag);
}  

void UIWidget::setColor(const cocos2d::Color3B &color)
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setColor(color);
    }
}

const cocos2d::Color3B& UIWidget::getColor()
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getColor();
    }
    return cocos2d::Color3B::WHITE;
}

void UIWidget::setOpacity(int opacity)
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setOpacity(opacity);
    }
}

int UIWidget::getOpacity()
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getOpacity();
    }
    return 255;
}

bool UIWidget::isCascadeOpacityEnabled()
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeOpacityEnabled();
    }
    return false;
}

void UIWidget::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    }
}

bool UIWidget::isCascadeColorEnabled()
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeColorEnabled();
    }
    return false;
}

void UIWidget::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    cocos2d::RGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeColorEnabled(cascadeColorEnabled);
    }
}

void UIWidget::setBlendFunc(cocos2d::BlendFunc blendFunc)
{
    cocos2d::BlendProtocol * blendNode = DYNAMIC_CAST_CCBLENDPROTOCOL;
    if (blendNode)
    {
        blendNode->setBlendFunc(blendFunc);
    }
}

const cocos2d::Point& UIWidget::getTouchStartPos()
{
    return _touchStartPos;
}

const cocos2d::Point& UIWidget::getTouchMovePos()
{
    return _touchMovePos;
}

const cocos2d::Point& UIWidget::getTouchEndPos()
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
    cocos2d::ccArray* arrayWidgetChildren = model->getChildren()->data;
    int length = arrayWidgetChildren->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* child = (UIWidget*)(arrayWidgetChildren->arr[i]);
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
    cocos2d::NodeRGBA::visit();
}
    
}
