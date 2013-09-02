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

#define DYNAMIC_CAST_CCBLENDPROTOCOL dynamic_cast<cocos2d::CCBlendProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCRGBAPROTOCOL dynamic_cast<cocos2d::CCRGBAProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCNODERGBA dynamic_cast<GUIRenderer*>(m_pRenderer)
    
UIWidget::UIWidget():
m_bEnabled(true),
m_bBright(true),
m_bFocus(false),
m_nWidgetZOrder(0),
m_pWidgetParent(NULL),
m_eBrightStyle(BRIGHT_NONE),
m_bTouchEnabled(false),
m_bTouchPassedEnabled(false),
m_nWidgetTag(-1),
m_bUpdateEnabled(false),
m_pRenderer(NULL),
m_strName("default"),
m_WidgetType(WidgetTypeWidget),
m_bVisible(true),
m_pPushListener(NULL),
m_pfnPushSelector(NULL),
m_pMoveListener(NULL),
m_pfnMoveSelector(NULL),
m_pReleaseListener(NULL),
m_pfnReleaseSelector(NULL),
m_pCancelListener(NULL),
m_pfnCancelSelector(NULL),
m_anchorPoint(ccp(0.5f, 0.5f)),
m_pUILayer(NULL),
m_nActionTag(0),
m_pLayoutParameter(NULL),
m_size(CCSizeZero),
m_customSize(CCSizeZero),
m_bIgnoreSize(false),
m_children(NULL),
m_bAffectByClipping(false),
/*temp action*/
m_pBindingAction(NULL)
{
}

UIWidget::~UIWidget()
{
    CC_SAFE_RELEASE_NULL(m_pLayoutParameter);
}

UIWidget* UIWidget::create()
{
    UIWidget* widget = new UIWidget();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIWidget::init()
{
    m_children = CCArray::create();
    m_children->retain();
    initRenderer();
    m_pRenderer->retain();
    m_pRenderer->setZOrder(m_nWidgetZOrder);
    CCRGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    setBright(true);
    ignoreContentAdaptWithSize(true);
    return true;
}

void UIWidget::releaseResoures()
{
    m_pPushListener = NULL;
    m_pfnPushSelector = NULL;
    m_pMoveListener = NULL;
    m_pfnMoveSelector = NULL;
    m_pReleaseListener = NULL;
    m_pfnReleaseSelector = NULL;
    m_pCancelListener = NULL;
    m_pfnCancelSelector = NULL;
    setUpdateEnabled(false);
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->removeManageredWidget(this);
        setUILayer(NULL);
    }
    removeAllChildrenAndCleanUp(true);
    m_pRenderer->removeAllChildrenWithCleanup(true);
    m_pRenderer->removeFromParentAndCleanup(true);
    m_pRenderer->release();
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
    
    if (m_pUILayer)
    {
        int childrenCount = m_children->data->num;
        ccArray* arrayChildren = m_children->data;
        for (int i=0; i<childrenCount; i++)
        {
            UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
            child->updateChildrenUILayer(m_pUILayer);
        }
    }
    structureChangedEvent();
    return true;
}

bool UIWidget::removeChild(UIWidget *child, bool cleanup)
{
    if (!child)
    {
        return false;
    }
    if (cleanup)
    {
        if (m_children->containsObject(child))
        {
            m_children->removeObject(child);
            child->structureChangedEvent();
            child->releaseResoures();
            child->setParent(NULL);
            delete child;
        }
    }
    else
    {
        if (m_children->containsObject(child))
        {
            child->structureChangedEvent();
            child->disableUpdate();
            child->updateChildrenUILayer(NULL);
            m_pRenderer->removeChild(child->getRenderer(), false);
            m_children->removeObject(child);
            child->setParent(NULL);
        }
    }
    return true;
}

void UIWidget::removeFromParentAndCleanup(bool cleanup)
{
    if (m_pWidgetParent)
    {
        m_pWidgetParent->removeChild(this, cleanup);
    }
    else
    {
        structureChangedEvent();
        releaseResoures();
        m_pWidgetParent = NULL;
        delete this;
    }
}

void UIWidget::removeAllChildrenAndCleanUp(bool cleanup)
{
    int times = m_children->data->num;
    for (int i=0;i<times;i++)
    {
        UIWidget* child = (UIWidget*)(m_children->lastObject());
        m_children->removeObject(child);
        child->structureChangedEvent();
        child->releaseResoures();
        delete child;
        child = NULL;
    }
}

void UIWidget::reorderChild(UIWidget* child)
{
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
    structureChangedEvent();
}

void UIWidget::updateChildrenUILayer(UILayer* uiLayer)
{
    setUILayer(uiLayer);
    setUpdateEnabled(isUpdateEnabled());
    int childrenCount = m_children->data->num;
    ccArray* arrayChildren = m_children->data;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->updateChildrenUILayer(m_pUILayer);
    }
}

void UIWidget::disableUpdate()
{
    if (m_pUILayer)
    {
        m_pUILayer->removeUpdateEnableWidget(this);
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
    DYNAMIC_CAST_CCNODERGBA->setEnabled(enabled);
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

CCArray* UIWidget::getChildren()
{
    return m_children;
}


void UIWidget::initRenderer()
{
    m_pRenderer = GUIRenderer::create();
}

void UIWidget::setSize(const CCSize &size)
{
    if (m_bIgnoreSize)
    {
        m_size = getContentSize();
    }
    else
    {
        m_size = size;
    }
    m_customSize = size;
    onSizeChanged();
}

void UIWidget::ignoreContentAdaptWithSize(bool ignore)
{
    m_bIgnoreSize = ignore;
    if (m_bIgnoreSize)
    {
        CCSize s = getContentSize();
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

const CCSize& UIWidget::getSize() const
{
    return m_size;
}

CCPoint UIWidget::getWorldPosition()
{
    return m_pRenderer->convertToWorldSpace(CCPointZero);
}

CCPoint UIWidget::convertToWorldSpace(const CCPoint& pt)
{
    return m_pRenderer->convertToWorldSpace(pt);
}

CCNode* UIWidget::getVirtualRenderer()
{
    return m_pRenderer;
}

void UIWidget::onSizeChanged()
{

}

const CCSize& UIWidget::getContentSize() const
{
    return m_size;
}

void UIWidget::setUILayer(UILayer *uiLayer)
{
    m_pUILayer = uiLayer;
}

void UIWidget::structureChangedEvent()
{
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->uiSceneHasChanged();
    }
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
    structureChangedEvent();
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
        if (m_pUILayer)
        {
            m_pUILayer->addUpdateEnableWidget(this);
        }
    }
    else
    {
        if (m_pUILayer)
        {
            m_pUILayer->removeUpdateEnableWidget(this);
        }
    }
}

bool UIWidget::isUpdateEnabled()
{
    return m_bUpdateEnabled;
}

bool UIWidget::isFocus() const
{
    return m_bFocus;
}

void UIWidget::setFocus(bool fucos)
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

bool UIWidget::onTouchBegan(const CCPoint &touchPoint)
{
    setFocus(true);
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    }
    pushDownEvent();
    return m_bTouchPassedEnabled;
}

void UIWidget::onTouchMoved(const CCPoint &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    setFocus(hitTest(touchPoint));
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
}

void UIWidget::onTouchEnded(const CCPoint &touchPoint)
{
    m_touchEndPos.x = touchPoint.x;
    m_touchEndPos.y = touchPoint.y;
    bool focus = m_bFocus;
    setFocus(false);
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

void UIWidget::onTouchCancelled(const CCPoint &touchPoint)
{
    setFocus(false);
}

void UIWidget::onTouchLongClicked(const CCPoint &touchPoint)
{
    longClickEvent();
}

void UIWidget::pushDownEvent()
{
    if (m_pPushListener && m_pfnPushSelector)
    {
        (m_pPushListener->*m_pfnPushSelector)(this);
    }
}

void UIWidget::moveEvent()
{
    if (m_pMoveListener && m_pfnMoveSelector)
    {
        (m_pMoveListener->*m_pfnMoveSelector)(this);
    }
}

void UIWidget::releaseUpEvent()
{
    if (m_pReleaseListener && m_pfnReleaseSelector)
    {
        (m_pReleaseListener->*m_pfnReleaseSelector)(this);
    }
}

void UIWidget::cancelUpEvent()
{
    if (m_pCancelListener && m_pfnCancelSelector)
    {
        (m_pCancelListener->*m_pfnCancelSelector)(this);
    }
}

void UIWidget::longClickEvent()
{
    
}

void UIWidget::addPushDownEvent(CCObject*target, SEL_PushEvent selector)
{
    m_pPushListener = target;
    m_pfnPushSelector = selector;
}

void UIWidget::addMoveEvent(CCObject* target,SEL_MoveEvent selector)
{
    m_pMoveListener = target;
    m_pfnMoveSelector = selector;
}

void UIWidget::addReleaseEvent(CCObject* target,SEL_ReleaseEvent selector)
{
    m_pReleaseListener = target;
    m_pfnReleaseSelector = selector;
}

void UIWidget::addCancelEvent(CCObject *target, SEL_CancelEvent selector)
{
    m_pCancelListener = target;
    m_pfnCancelSelector = selector;
}

CCNode* UIWidget::getRenderer()
{
    return m_pRenderer;
}

bool UIWidget::hitTest(const CCPoint &pt)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(pt);
    CCRect bb = CCRectMake(-m_size.width * m_anchorPoint.x, -m_size.height * m_anchorPoint.y, m_size.width, m_size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::parentAreaContainPoint(const CCPoint &pt)
{

    m_bAffectByClipping = false;
    UIWidget* parent = getParent();
    while (parent)
    {
        Layout* layoutParent = dynamic_cast<Layout*>(parent);
        if (layoutParent)
        {
            if (layoutParent->isClippingEnabled())
            {
                m_bAffectByClipping = true;
                break;
            }
        }
        parent = parent->getParent();
    }
    
    if (!m_bAffectByClipping)
    {
        return true;
    }
    
    
    if (m_pWidgetParent)
    {
        bool bRet = false;
        if (m_pWidgetParent->hitTest(pt))
        {
            bRet = true;
        }
        if (bRet)
        {
            return m_pWidgetParent->parentAreaContainPoint(pt);
        }
        return false;
    }
    return true;
}

void UIWidget::checkChildInfo(int handleState, UIWidget *sender,const CCPoint &touchPoint)
{
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const CCPoint &pos)
{
    m_pRenderer->setPosition(pos);
}

void UIWidget::setAnchorPoint(const CCPoint &pt)
{
    m_anchorPoint = pt;
    m_pRenderer->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(m_anchorPoint);
}

const CCPoint& UIWidget::getPosition()
{
    return m_pRenderer->getPosition();
}

const CCPoint& UIWidget::getAnchorPoint()
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

CCAction* UIWidget::runAction(CCAction *action)
{
    return m_pRenderer->runAction(action);
}

void UIWidget::setActionManager(CCActionManager *actionManager)
{
    m_pRenderer->setActionManager(actionManager);
}

CCActionManager* UIWidget::getActionManager()
{
    return m_pRenderer->getActionManager();
}

void UIWidget::stopAllActions()
{
    m_pRenderer->stopAllActions();
}

void UIWidget::stopAction(CCAction *action)
{
    m_pRenderer->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    m_pRenderer->stopActionByTag(tag);
}

CCAction* UIWidget::getActionByTag(int tag)
{
    return m_pRenderer->getActionByTag(tag);
}  

void UIWidget::setColor(const ccColor3B &color)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setColor(color);
    }
}

const ccColor3B& UIWidget::getColor()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getColor();
    }
    return ccWHITE;
}

void UIWidget::setOpacity(int opacity)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setOpacity(opacity);
    }
}

int UIWidget::getOpacity()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getOpacity();
    }
    return 255;
}

bool UIWidget::isCascadeOpacityEnabled()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeOpacityEnabled();
    }
    return false;
}

void UIWidget::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    }
}

bool UIWidget::isCascadeColorEnabled()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeColorEnabled();
    }
    return false;
}

void UIWidget::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeColorEnabled(cascadeColorEnabled);
    }
}

void UIWidget::setBlendFunc(ccBlendFunc blendFunc)
{
    CCBlendProtocol * blendNode = DYNAMIC_CAST_CCBLENDPROTOCOL;
    if (blendNode)
    {
        blendNode->setBlendFunc(blendFunc);
    }
}

const CCPoint& UIWidget::getTouchStartPos()
{
    return m_touchStartPos;
}

const CCPoint& UIWidget::getTouchMovePos()
{
    return m_touchMovePos;
}

const CCPoint& UIWidget::getTouchEndPos()
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

/*******to be removed*******/

void UIWidget::setTouchEnable(bool enabled, bool containChildren)
{
    setTouchEnabled(enabled);
    if (containChildren)
    {
        ccArray* childrenArray = getChildren()->data;
        int length = childrenArray->num;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = (UIWidget*)childrenArray->arr[i];
            child->setTouchEnable(enabled,true);
        }
    }
}

void UIWidget::disable(bool containChildren)
{
    setBright(false,containChildren);
    setTouchEnable(false,containChildren);
}

void UIWidget::active(bool containChildren)
{
    setBright(true,containChildren);
    setTouchEnable(true,containChildren);
}

bool UIWidget::isActive()
{
    return isBright();
}

void UIWidget::setBright(bool bright, bool containChild)
{
    setBright(bright);
    if (containChild)
    {
        ccArray* childrenArray = getChildren()->data;
        int length = childrenArray->num;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = (UIWidget*)childrenArray->arr[i];
            child->setBright(bright,containChild);
        }
    }
}

CCRect UIWidget::getRect()
{
    CCPoint wPos = getWorldPosition();
    float width = m_size.width;
    float height = m_size.height;
    float offset_width = m_anchorPoint.x * width;
    float offset_height = m_anchorPoint.y * height;
    return CCRectMake(wPos.x - offset_width, wPos.y - offset_height, width, height);
}

/***************************/

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

bool GUIRenderer::getEnabled() const
{
    return m_bEnabled;
}

void GUIRenderer::visit()
{
    if (!m_bEnabled)
    {
        return;
    }
    CCNodeRGBA::visit();
}

NS_CC_EXT_END
