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

#define DYNAMIC_CAST_CCBLENDPROTOCOL dynamic_cast<cocos2d::BlendProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCRGBAPROTOCOL dynamic_cast<cocos2d::RGBAProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCNODERGBA dynamic_cast<GUIRenderer*>(m_pRenderer)
    
UIWidget::UIWidget():
m_bEnabled(true),
m_bVisible(true),
m_bBright(true),
m_bTouchEnabled(false),
m_bTouchPassedEnabled(false),
m_bFocus(false),
m_nWidgetZOrder(0),
m_anchorPoint(Point(0.5f, 0.5f)),
m_pWidgetParent(NULL),
m_eBrightStyle(BRIGHT_NONE),
m_bUpdateEnabled(false),
m_pRenderer(NULL),
m_touchStartPos(Point::ZERO),
m_touchMovePos(Point::ZERO),
m_touchEndPos(Point::ZERO),
m_pTouchEventListener(NULL),
m_pfnTouchEventSelector(NULL),
m_nWidgetTag(-1),
m_strName("default"),
m_WidgetType(WidgetTypeWidget),
m_nActionTag(0),
m_size(Size::ZERO),
m_customSize(Size::ZERO),
m_pLayoutParameter(NULL),
m_bIgnoreSize(false),
m_children(NULL),
m_bAffectByClipping(false),
m_pScheduler(NULL),
m_eSizeType(SIZE_ABSOLUTE),
m_sizePercent(Point::ZERO),
m_ePositionType(POSITION_ABSOLUTE),
m_positionPercent(Point::ZERO),
m_bIsRunning(false),

/*temp action*/
m_pBindingAction(NULL)
{
    
}

UIWidget::~UIWidget()
{
    releaseResoures();
    setParent(NULL);
    CC_SAFE_RELEASE_NULL(m_pLayoutParameter);
    CC_SAFE_RELEASE(m_pScheduler);
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
    m_children = Array::create();
    m_children->retain();
    initRenderer();
    m_pRenderer->retain();
    m_pRenderer->setZOrder(m_nWidgetZOrder);
    RGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    setBright(true);
    ignoreContentAdaptWithSize(true);
    m_pScheduler = Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(m_pScheduler);
    return true;
}

void UIWidget::releaseResoures()
{
    setUpdateEnabled(false);
    removeAllChildren();
    m_children->release();
    m_pRenderer->removeAllChildrenWithCleanup(true);
    m_pRenderer->removeFromParentAndCleanup(true);
    m_pRenderer->release();
}

void UIWidget::onEnter()
{
    arrayMakeObjectsPerformSelector(m_children, onEnter, UIWidget*);
    m_bIsRunning = true;
    updateSizeAndPosition();
}

void UIWidget::onExit()
{
    m_bIsRunning = false;
    arrayMakeObjectsPerformSelector(m_children, onExit, UIWidget*);
}

bool UIWidget::addChild(UIWidget *child)
{
    if (!child)
    {
        return false;
    }
    if (m_children->containsObject(child))
    {
        return false;
    }
    child->setParent(this);
    int childrenCount = m_children->data->num;
    if (childrenCount <= 0)
    {
        m_children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = m_children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getZOrder() >= widget->getZOrder())
            {
                if (i == childrenCount-1)
                {
                    m_children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    m_children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            m_children->insertObject(child,0);
        }
    }
    child->getRenderer()->setZOrder(child->getZOrder());
    m_pRenderer->addChild(child->getRenderer());
    if (m_bIsRunning)
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
    if (m_children->containsObject(child))
    {
        if (m_bIsRunning)
        {
            child->onExit();    
        }
        child->disableUpdate();
        child->setParent(NULL);
        m_pRenderer->removeChild(child->getRenderer());
        m_children->removeObject(child);
        return true;
    }
    return false;
}

void UIWidget::removeFromParent()
{
    if (m_pWidgetParent)
    {
        m_pWidgetParent->removeChild(this);
    }
}

void UIWidget::removeAllChildren()
{
    if (!m_children || m_children->count() <= 0)
    {
        return;
    }
    int times = m_children->data->num;
    for (int i=0; i<times; ++i)
    {
        UIWidget* lastChild = (UIWidget*)(m_children->getLastObject());
        removeChild(lastChild);
    }
}

void UIWidget::reorderChild(UIWidget* child)
{
    CC_SAFE_RETAIN(child);
    m_children->removeObject(child);
    int childrenCount = m_children->data->num;
    if (childrenCount <= 0)
    {
        m_children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = m_children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getZOrder() >= widget->getZOrder())
            {
                if (i == childrenCount-1)
                {
                    m_children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    m_children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            m_children->insertObject(child,0);
        }
    }
    CC_SAFE_RELEASE(child);
}

void UIWidget::disableUpdate()
{
    if (m_pScheduler)
    {
        m_pScheduler->unscheduleUpdateForTarget(this);
    }
    int childrenCount = m_children->data->num;
    ccArray* arrayChildren = m_children->data;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->disableUpdate();
    }
}

void UIWidget::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    GUIRenderer* renderer = DYNAMIC_CAST_CCNODERGBA;
    if (renderer)
    {
        renderer->setEnabled(enabled);
    }
    else
    {
        dynamic_cast<RectClippingNode*>(m_pRenderer)->setEnabled(enabled);
    }
    ccArray* arrayChildren = m_children->data;
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
    return m_children;
}

void UIWidget::initRenderer()
{
    m_pRenderer = GUIRenderer::create();
}

void UIWidget::setSize(const Size &size)
{
    m_customSize = size;
    if (m_bIgnoreSize)
    {
        m_size = getContentSize();
    }
    else
    {
        m_size = size;
    }
    if (m_bIsRunning)
    {
        m_sizePercent = (m_pWidgetParent == NULL) ? Point::ZERO : Point(m_customSize.width / m_pWidgetParent->getSize().width, m_customSize.height / m_pWidgetParent->getSize().height);
    }
    onSizeChanged();
}

void UIWidget::setSizePercent(const Point &percent)
{
    m_sizePercent = percent;
    if (!m_bIsRunning)
    {
        return;
    }
    Size cSize = (m_pWidgetParent == NULL) ? Size::ZERO : Size(m_pWidgetParent->getSize().width * percent.x , m_pWidgetParent->getSize().height * percent.y);
    if (m_bIgnoreSize)
    {
        m_size = getContentSize();
    }
    else
    {
        m_size = cSize;
    }
    m_customSize = cSize;
    onSizeChanged();
}

void UIWidget::updateSizeAndPosition()
{
    switch (m_eSizeType)
    {
        case SIZE_ABSOLUTE:
            if (m_bIgnoreSize)
            {
                m_size = getContentSize();
            }
            else
            {
                m_size = m_customSize;
            }
            m_sizePercent = (m_pWidgetParent == NULL) ? Point::ZERO : Point(m_customSize.width / m_pWidgetParent->getSize().width, m_customSize.height / m_pWidgetParent->getSize().height);
            break;
        case SIZE_PERCENT:
        {
            Size cSize = (m_pWidgetParent == NULL) ? Size::ZERO : Size(m_pWidgetParent->getSize().width * m_sizePercent.x , m_pWidgetParent->getSize().height * m_sizePercent.y);
            if (m_bIgnoreSize)
            {
                m_size = getContentSize();
            }
            else
            {
                m_size = cSize;
            }
            m_customSize = cSize;
        }
            break;
        default:
            break;
    }
    onSizeChanged();
    Point absPos = getPosition();
    switch (m_ePositionType)
    {
        case POSITION_ABSOLUTE:
            m_positionPercent = (m_pWidgetParent == NULL) ? Point::ZERO : Point(absPos.x / m_pWidgetParent->getSize().width, absPos.y / m_pWidgetParent->getSize().height);
            break;
        case POSITION_PERCENT:
        {
            Size parentSize = m_pWidgetParent->getSize();
            absPos = Point(parentSize.width * m_positionPercent.x, parentSize.height * m_positionPercent.y);
        }
            break;
        default:
            break;
    }
    m_pRenderer->setPosition(absPos);
}

void UIWidget::setSizeType(SizeType type)
{
    m_eSizeType = type;
}

SizeType UIWidget::getSizeType() const
{
    return m_eSizeType;
}

void UIWidget::ignoreContentAdaptWithSize(bool ignore)
{
    m_bIgnoreSize = ignore;
    if (m_bIgnoreSize)
    {
        Size s = getContentSize();
        m_size = s;
    }
    else
    {
        m_size = m_customSize;
    }
    onSizeChanged();
}

bool UIWidget::isIgnoreContentAdaptWithSize() const
{
    return m_bIgnoreSize;
}

const Size& UIWidget::getSize() const
{
    return m_size;
}

const Point& UIWidget::getSizePercent() const
{
    return m_sizePercent;
}

Point UIWidget::getWorldPosition()
{
    return m_pRenderer->convertToWorldSpace(Point::ZERO);
}

Point UIWidget::convertToWorldSpace(const Point& pt)
{
    return m_pRenderer->convertToWorldSpace(pt);
}

Node* UIWidget::getVirtualRenderer()
{
    return m_pRenderer;
}

void UIWidget::onSizeChanged()
{

}

const Size& UIWidget::getContentSize() const
{
    return m_size;
}

void UIWidget::setZOrder(int z)
{
    m_nWidgetZOrder = z;
    m_pRenderer->setZOrder(z);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->reorderChild(this);
    }
}

int UIWidget::getZOrder()
{
    return m_nWidgetZOrder;
}

void UIWidget::setTouchEnabled(bool enable)
{
    m_bTouchEnabled = enable;
}

bool UIWidget::isTouchEnabled() const
{
    return m_bTouchEnabled;
}

void UIWidget::setUpdateEnabled(bool enable)
{
    m_bUpdateEnabled = enable;
    if (enable)
    {
        if (m_pScheduler)
        {
            m_pScheduler->scheduleUpdateForTarget(this, 0, false);
        }
    }
    else
    {
        if (m_pScheduler)
        {
            m_pScheduler->unscheduleUpdateForTarget(this);
        }
    }
}

bool UIWidget::isUpdateEnabled()
{
    return m_bUpdateEnabled;
}

bool UIWidget::isFocused() const
{
    return m_bFocus;
}

void UIWidget::setFocused(bool fucos)
{
    if (fucos == m_bFocus)
    {
        return;
    }
    m_bFocus = fucos;
    if (m_bBright)
    {
        if (m_bFocus)
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
    m_bBright = bright;
    if (m_bBright)
    {
        m_eBrightStyle = BRIGHT_NONE;
        setBrightStyle(BRIGHT_NORMAL);
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void UIWidget::setBrightStyle(BrightStyle style)
{
    if (m_eBrightStyle == style)
    {
        return;
    }
    m_eBrightStyle = style;
    switch (m_eBrightStyle)
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
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    }
    pushDownEvent();
    return m_bTouchPassedEnabled;
}

void UIWidget::onTouchMoved(const Point &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    setFocused(hitTest(touchPoint));
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
}

void UIWidget::onTouchEnded(const Point &touchPoint)
{
    m_touchEndPos.x = touchPoint.x;
    m_touchEndPos.y = touchPoint.y;
    bool focus = m_bFocus;
    setFocused(false);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(2,this,touchPoint);
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
    if (m_pTouchEventListener && m_pfnTouchEventSelector)
    {
        (m_pTouchEventListener->*m_pfnTouchEventSelector)(this,TOUCH_EVENT_BEGAN);
    }
}

void UIWidget::moveEvent()
{
    if (m_pTouchEventListener && m_pfnTouchEventSelector)
    {
        (m_pTouchEventListener->*m_pfnTouchEventSelector)(this,TOUCH_EVENT_MOVED);
    }
}

void UIWidget::releaseUpEvent()
{
    if (m_pTouchEventListener && m_pfnTouchEventSelector)
    {
        (m_pTouchEventListener->*m_pfnTouchEventSelector)(this,TOUCH_EVENT_ENDED);
    }
}

void UIWidget::cancelUpEvent()
{
    if (m_pTouchEventListener && m_pfnTouchEventSelector)
    {
        (m_pTouchEventListener->*m_pfnTouchEventSelector)(this,TOUCH_EVENT_CANCELED);
    }
}

void UIWidget::longClickEvent()
{
    
}

void UIWidget::addTouchEventListener(Object *target, SEL_TouchEvent selector)
{
    m_pTouchEventListener = target;
    m_pfnTouchEventSelector = selector;
}

Node* UIWidget::getRenderer()
{
    return m_pRenderer;
}

void UIWidget::addRenderer(Node* renderer, int zOrder)
{
    m_pRenderer->addChild(renderer, zOrder);
}

void UIWidget::removeRenderer(Node* renderer, bool cleanup)
{
    m_pRenderer->removeChild(renderer,cleanup);
}

bool UIWidget::hitTest(const Point &pt)
{
    Point nsp = m_pRenderer->convertToNodeSpace(pt);
    Rect bb = Rect(-m_size.width * m_anchorPoint.x, -m_size.height * m_anchorPoint.y, m_size.width, m_size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::clippingParentAreaContainPoint(const Point &pt)
{
    m_bAffectByClipping = false;
    UIWidget* parent = getParent();
    UIWidget* clippingParent = NULL;
    while (parent)
    {
        Layout* layoutParent = dynamic_cast<Layout*>(parent);
        if (layoutParent)
        {
            if (layoutParent->isClippingEnabled())
            {
                m_bAffectByClipping = true;
                clippingParent = layoutParent;
                break;
            }
        }
        parent = parent->getParent();
    }
    
    if (!m_bAffectByClipping)
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
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const Point &pos)
{
    if (m_bIsRunning)
    {
        m_positionPercent = (m_pWidgetParent == NULL) ? Point::ZERO : Point(pos.x / m_pWidgetParent->getSize().width, pos.y / m_pWidgetParent->getSize().height);
    }
    m_pRenderer->setPosition(pos);
}

void UIWidget::setPositionPercent(const Point &percent)
{
    m_positionPercent = percent;
    if (m_bIsRunning)
    {
        Size parentSize = m_pWidgetParent->getSize();
        Point absPos = Point(parentSize.width * m_positionPercent.x, parentSize.height * m_positionPercent.y);
        m_pRenderer->setPosition(absPos);
    }
}

void UIWidget::setAnchorPoint(const Point &pt)
{
    m_anchorPoint = pt;
    m_pRenderer->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(m_anchorPoint);
}

const Point& UIWidget::getPosition()
{
    return m_pRenderer->getPosition();
}

const Point& UIWidget::getPositionPercent()
{
    return m_positionPercent;
}

void UIWidget::setPositionType(PositionType type)
{
    m_ePositionType = type;
}

PositionType UIWidget::getPositionType() const
{
    return m_ePositionType;
}

const Point& UIWidget::getAnchorPoint()
{
    return m_anchorPoint;
}

void UIWidget::setScale(float scale)
{
    m_pRenderer->setScale(scale);
}

float UIWidget::getScale()
{
    return m_pRenderer->getScale();
}

void UIWidget::setScaleX(float scaleX)
{
    m_pRenderer->setScaleX(scaleX);
}

float UIWidget::getScaleX()
{
    return m_pRenderer->getScaleX();
}

void UIWidget::setScaleY(float scaleY)
{
    m_pRenderer->setScaleY(scaleY);
}

float UIWidget::getScaleY()
{
    return m_pRenderer->getScaleY();
}

void UIWidget::setRotation(float rotation)
{
    m_pRenderer->setRotation(rotation);
}

float UIWidget::getRotation()
{
    return m_pRenderer->getRotation();
}

void UIWidget::setRotationX(float rotationX)
{
    m_pRenderer->setRotationX(rotationX);
}

float UIWidget::getRotationX()
{
    return m_pRenderer->getRotationX();
}

void UIWidget::setRotationY(float rotationY)
{
    m_pRenderer->setRotationY(rotationY);
}

float UIWidget::getRotationY()
{
    return m_pRenderer->getRotationY();
}

void UIWidget::setVisible(bool visible)
{
    m_bVisible = visible;
    m_pRenderer->setVisible(visible);
}

bool UIWidget::isVisible() const
{
    return m_bVisible;
}

bool UIWidget::isBright() const
{
    return m_bBright;
}

bool UIWidget::isEnabled() const
{
    return m_bEnabled;
}

float UIWidget::getLeftInParent()
{
    float leftPos = 0.0f;
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            leftPos = getPosition().x - getAnchorPoint().x * m_size.width;
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
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            bottomPos = getPosition().y - getAnchorPoint().y * m_size.height;
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
    return getLeftInParent() + m_size.width;
}

float UIWidget::getTopInParent()
{
    return getBottomInParent() + m_size.height;
}

UIWidget* UIWidget::getParent()
{
    return m_pWidgetParent;
}

void UIWidget::setParent(UIWidget* parent)
{
	m_pWidgetParent = parent;
}

Action* UIWidget::runAction(Action *action)
{
    return m_pRenderer->runAction(action);
}

void UIWidget::setActionManager(ActionManager *actionManager)
{
    m_pRenderer->setActionManager(actionManager);
}

ActionManager* UIWidget::getActionManager()
{
    return m_pRenderer->getActionManager();
}

void UIWidget::stopAllActions()
{
    m_pRenderer->stopAllActions();
}

void UIWidget::stopAction(Action *action)
{
    m_pRenderer->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    m_pRenderer->stopActionByTag(tag);
}

Action* UIWidget::getActionByTag(int tag)
{
    return m_pRenderer->getActionByTag(tag);
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
    return m_touchStartPos;
}

const Point& UIWidget::getTouchMovePos()
{
    return m_touchMovePos;
}

const Point& UIWidget::getTouchEndPos()
{
    return m_touchEndPos;
}

void UIWidget::setTag(int tag)
{
    m_nWidgetTag = tag;
}

int UIWidget::getTag() const
{
    return m_nWidgetTag;
}

void UIWidget::setName(const char* name)
{
    m_strName = name;
}

const char* UIWidget::getName() const
{
    return m_strName.c_str();
}

WidgetType UIWidget::getWidgetType() const
{
    return m_WidgetType;
}

void UIWidget::setLayoutParameter(LayoutParameter *parameter)
{
    if (m_pLayoutParameter)
    {
        CC_SAFE_RELEASE_NULL(m_pLayoutParameter);
    }
    m_pLayoutParameter = parameter;
    CC_SAFE_RETAIN(m_pLayoutParameter);
}

LayoutParameter* UIWidget::getLayoutParameter()
{
    return m_pLayoutParameter;
}

/*temp action*/
void UIWidget::setActionTag(int tag)
{
	m_nActionTag = tag;
}

int UIWidget::getActionTag()
{
	return m_nActionTag;
}

void UIWidget::setBindingAction(UIActionNode *actionNode)
{
    m_pBindingAction = actionNode;
}

GUIRenderer::GUIRenderer():
m_bEnabled(true)
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
    m_bEnabled = enabled;
}

bool GUIRenderer::isEnabled() const
{
    return m_bEnabled;
}

void GUIRenderer::visit()
{
    if (!m_bEnabled)
    {
        return;
    }
    NodeRGBA::visit();
}

NS_CC_EXT_END
