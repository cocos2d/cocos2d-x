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
#include "../System/UIHelper.h"
#include "../System/UILayer.h"
#include "../Action/UIActionNode.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCBLENDPROTOCOL dynamic_cast<cocos2d::CCBlendProtocol*>(m_pRender)

#define DYNAMIC_CAST_CCRGBAPROTOCOL dynamic_cast<cocos2d::CCRGBAProtocol*>(m_pRender)

#define DYNAMIC_CAST_CCNODERGBA dynamic_cast<CCNodeRGBA*>(m_pRender)
    
UIWidget::UIWidget():
m_bEnabled(true),
m_bActived(true),
m_bFocus(false),
m_nWidgetZOrder(0),
m_pWidgetParent(NULL),
m_nCurPressState(WidgetStateNone),
m_nPrevPressstate(WidgetStateNone),
m_bTouchEnabled(false),
m_nWidgetTag(-1),
m_bUpdateEnable(false),
m_pRender(NULL),
m_strName("default"),
m_children(NULL),
m_WidgetType(WidgetTypeWidget),
m_bVisible(true),
m_bNeedCheckVisibleDependParent(false),
m_pPushListener(NULL),
m_pfnPushSelector(NULL),
m_pMoveListener(NULL),
m_pfnMoveSelector(NULL),
m_pReleaseListener(NULL),
m_pfnReleaseSelector(NULL),
m_pCancelListener(NULL),
m_pfnCancelSelector(NULL),
m_fContentSizeHeight(0),
m_fContentSizeWidth(0),
//m_bUseMergedTexture(false),
m_fAbsoluteScaleX(1.0f),
m_fAbsoluteScaleY(1.0f),
m_bScaleXDirty(true),
m_bScaleYDirty(true),
m_bAbsoluteVisible(true),
m_bVisibleDirty(true),
m_fAdaptScaleX(1.0f),
m_fAdaptScaleY(1.0f),
m_anchorPoint(ccp(0.5f, 0.5f)),
m_pUILayer(NULL),
m_bIsCreatedFromFile(false),
m_nActionTag(0),
m_fileDesignSize(CCSizeZero),
m_pBindingAction(NULL)
{
    m_WidgetName = WIDGET_WIDGET;
}

UIWidget::~UIWidget()
{
    
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
    initNodes();
    m_pRender->retain();
    m_pRender->setZOrder(m_nWidgetZOrder);
    CCRGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    return true;
}

void UIWidget::releaseResoures()
{
    if (m_pBindingAction)
    {
        m_pBindingAction->releaseBindingWidget();
    }
    m_pPushListener = NULL;
    m_pfnPushSelector = NULL;
    m_pMoveListener = NULL;
    m_pfnMoveSelector = NULL;
    m_pReleaseListener = NULL;
    m_pfnReleaseSelector = NULL;
    m_pCancelListener = NULL;
    m_pfnCancelSelector = NULL;
    setUpdateEnable(false);
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->removeManageredWidget(this);
        setUILayer(NULL);
    }
    removeAllChildrenAndCleanUp(true);
    m_pRender->removeAllChildrenWithCleanup(true);
    m_pRender->removeFromParentAndCleanup(true);
    m_pRender->release();
    m_children->release();
}

void UIWidget::initNodes()
{
    m_pRender = CCNodeRGBA::create();
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
    child->m_pWidgetParent = this;
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
            if (child->getWidgetZOrder() >= widget->getWidgetZOrder())
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
    child->m_pRender->setZOrder(child->getWidgetZOrder());
    m_pRender->addChild(child->m_pRender);
    
    if (m_pUILayer)
    {
        int childrenCount = m_children->data->num;
        ccArray* arrayChildren = m_children->data;
        for (int i=0; i<childrenCount; i++) {
            UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
            child->updateChildrenUILayer(m_pUILayer);
        }
    }
    structureChangedEvent();
    return true;
}

void UIWidget::setUILayer(UILayer *uiLayer)
{
    m_pUILayer = uiLayer;
}

void UIWidget::updateChildrenUILayer(UILayer* uiLayer)
{
    setUILayer(uiLayer);
    setUpdateEnable(getUpdateEnable());
    int childrenCount = m_children->data->num;
    ccArray* arrayChildren = m_children->data;
    for (int i=0; i<childrenCount; i++) {
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

void UIWidget::structureChangedEvent()
{
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->uiSceneHasChanged();
    }
}

bool UIWidget::removeChild(UIWidget *child, bool cleanup)
{
    if (!child)
    {
        return false;
    }
    if (cleanup)
    {
        removeChildMoveToTrash(child);
    }
    else
    {
        removeChildReferenceOnly(child);
    }
    return true;
}

void UIWidget::removeChildMoveToTrash(UIWidget *child)
{
    if (!child)
    {
        return;
    }
    if (m_children->containsObject(child))
    {
        m_children->removeObject(child);
        child->structureChangedEvent();
        child->releaseResoures();
        child->m_pWidgetParent = NULL;
        delete child;
    }
}

void UIWidget::removeChildReferenceOnly(UIWidget *child)
{
    if (!child)
    {
        return;
    }
    if (m_children->containsObject(child))
    {
        child->structureChangedEvent();
        child->disableUpdate();
        child->updateChildrenUILayer(NULL);
        m_pRender->removeChild(child->m_pRender, false);
        child->setNeedCheckVisibleDepandParent(false);
        m_children->removeObject(child);
        child->m_pWidgetParent = NULL;
    }
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

void UIWidget::setWidgetZOrder(int z)
{
    m_nWidgetZOrder = z;
    m_pRender->setZOrder(z);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->reorderChild(this);
    }
}

int UIWidget::getWidgetZOrder()
{
    return m_nWidgetZOrder;
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
            if (child->getWidgetZOrder() >= widget->getWidgetZOrder())
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

void UIWidget::setNeedCheckVisibleDepandParent(bool need)
{
    m_bNeedCheckVisibleDependParent = need;
    if (m_children)
    {
        ccArray* arrayChildren = m_children->data;
        int childrenCount = arrayChildren->num;
        for (int i=0;i<childrenCount;i++)
        {
            UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
            child->setNeedCheckVisibleDepandParent(need);
        }
    }
}

void UIWidget::setTouchEnable(bool enable, bool containChildren)
{
    m_bTouchEnabled = enable;
    if (containChildren)
    {
        updateChildrenTouchEnable(enable, containChildren);
    }
    structureChangedEvent();
}

void UIWidget::updateChildrenTouchEnable(bool enable, bool containChildren)
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->setTouchEnable(enable, containChildren);
    }
}

bool UIWidget::isTouchEnable()
{
    return m_bTouchEnabled;
}

void UIWidget::setUpdateEnable(bool enable)
{
    m_bUpdateEnable = enable;
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

bool UIWidget::getUpdateEnable()
{
    return m_bUpdateEnable;
}

bool UIWidget::isFocus()
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
    if (m_bFocus)
    {
        setPressState(WidgetStateSelected);
    }
    else
    {
        setPressState(WidgetStateNormal);
    }
}

void UIWidget::initPressState(WidgetState state)
{
    if (m_nCurPressState == state)
    {
        return;
    }
    m_nPrevPressstate = m_nCurPressState;
    m_nCurPressState = state;
}

void UIWidget::setPressState(WidgetState state)
{
    if (m_nCurPressState == state)
    {
        return;
    }
    m_nPrevPressstate = m_nCurPressState;
    m_nCurPressState = state;
    switch (m_nCurPressState)
    {
        case WidgetStateNormal:
            onPressStateChangedToNormal();
            break;
        case WidgetStateSelected:
            onPressStateChangedToPressed();
            break;
        case WidgetStateDisabled:
            onPressStateChangedToDisabled();
            break;
        default:
            break;
            
    }
}

void UIWidget::disable(bool containChildren)
{
    m_bActived = false;
    setPressState(WidgetStateDisabled);
    if (containChildren)
    {
        updateChildrenDisable();
    }
}

void UIWidget::active(bool containChildren)
{
    m_bActived = true;
    setPressState(WidgetStateNormal);
    if (containChildren)
    {
        updateChildrenActive();
    }
}

void UIWidget::updateChildrenActive()
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        child->active();
    }
}

void UIWidget::updateChildrenDisable()
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        child->disable(true);
    }
}
bool UIWidget::isActive()
{
    return m_bActived;
}

void UIWidget::updateBeTouchEnable(bool enable)
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->setTouchEnable(enable);
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

void UIWidget::onTouchBegan(const CCPoint &touchPoint)
{
    setFocus(true);
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    }
    pushDownEvent();
}

void UIWidget::onTouchMoved(const CCPoint &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    setFocus(pointAtSelfBody(touchPoint));
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
    setPressState(WidgetStateNormal);
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

void UIWidget::getLocationInWindow()
{
    m_locationInWindow = m_pRender->convertToWorldSpace(CCPointZero);
}

CCRect UIWidget::getRect()
{
    CCNode* validNode = getValidNode();
    float width = 0.0f;
    float height = 0.0f;
    float anchorPointX = 0.0f;
    float anchorPointY = 0.0f;
    getLocationInWindow();
    CCSize nodeSize = validNode->getContentSize();
    width = nodeSize.width*getAbsoluteScaleX();
    height = nodeSize.height*getAbsoluteScaleY();
    CCPoint nodeAnchorPoint = validNode->getAnchorPoint();
    anchorPointX = nodeAnchorPoint.x;
    anchorPointY = nodeAnchorPoint.y;
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            m_rect.origin.x = m_locationInWindow.x - width * anchorPointX;
            m_rect.origin.y = m_locationInWindow.y - height * anchorPointY;
            break;
        case WidgetTypeContainer:
            m_rect.origin.x = m_locationInWindow.x;
            m_rect.origin.y = m_locationInWindow.y;
            break;
    }
    m_rect.size.width = width;
    m_rect.size.height = height;
    
    return m_rect;
}

CCRect UIWidget::getRelativeRect()
{
    CCNode* validNode = getValidNode();
    float width = 0.0f;
    float height = 0.0f;
    float anchorPointX = 0.0f;
    float anchorPointY = 0.0f;
    CCSize nodeSize = validNode->getContentSize();
    width = nodeSize.width*getScaleX();
    height = nodeSize.height*getScaleY();
    CCPoint nodeAnchorPoint = validNode->getAnchorPoint();
    anchorPointX = nodeAnchorPoint.x;
    anchorPointY = nodeAnchorPoint.y;
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            m_relativeRect.origin.x = getPosition().x - width * anchorPointX;
            m_relativeRect.origin.y = getPosition().y - height * anchorPointY;
            break;
        case WidgetTypeContainer:
            m_relativeRect.origin.x = getPosition().x;
            m_relativeRect.origin.y = getPosition().y;
            break;
    }
    m_relativeRect.size.width = width;
    m_relativeRect.size.height = height;
    return m_relativeRect;
}

const CCSize& UIWidget::getContentSize()
{
    return getValidNode()->getContentSize();
}

CCNode* UIWidget::getValidNode()
{
    return m_pRender;
}

CCNode* UIWidget::getContainerNode()
{
    return m_pRender;
}

bool UIWidget::pointAtSelfBody(const CCPoint &pt)
{
    if (!getAbsoluteVisible())
    {
        return false;
    }
    return hitTest(getValidNode(),pt);
}

bool UIWidget::hitTest(CCNode* node, const CCPoint &pt)
{
    CCPoint nsp = node->convertToNodeSpace(pt);
    CCRect bb = node->boundingBox();
    if (nsp.x >= 0.0f && nsp.x <= bb.size.width && nsp.y >= 0.0f && nsp.y <= bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::checkVisibleDependParent(const CCPoint &pt)
{
    if (!m_bNeedCheckVisibleDependParent)
    {
        return true;
    }
    if (m_pWidgetParent)
    {
        bool bRet = false;
        if (m_pWidgetParent->pointAtSelfBody(pt))
        {
            bRet = true;
        }
        if (bRet)
        {
            return m_pWidgetParent->checkVisibleDependParent(pt);
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
    m_pRender->setPosition(pos);
}

void UIWidget::setAnchorPoint(const CCPoint &pt)
{
    m_anchorPoint = pt;
    m_pRender->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(m_anchorPoint);
}

const CCPoint& UIWidget::getPosition()
{
    return m_pRender->getPosition();
}

const CCPoint& UIWidget::getAnchorPoint()
{
    return m_anchorPoint;
}

void UIWidget::setScale(float scale)
{
    m_pRender->setScale(scale);
    onScaleDirtyChanged();
}

void UIWidget::onScaleDirtyChanged()
{
    m_bScaleXDirty = m_bScaleYDirty = true;
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->onScaleDirtyChanged();
    }
}

void UIWidget::onScaleXDirtyChanged()
{
    m_bScaleXDirty = true;
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->onScaleXDirtyChanged();
    }
}

void UIWidget::onScaleYDirtyChanged()
{
    m_bScaleYDirty = true;
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->onScaleYDirtyChanged();
    }
}

float UIWidget::getScale()
{
    return m_pRender->getScale();
}

void UIWidget::setScaleX(float scaleX)
{
    m_pRender->setScaleX(scaleX);
    onScaleXDirtyChanged();
}

float UIWidget::getScaleX()
{
    return m_pRender->getScaleX();
}

void UIWidget::setScaleY(float scaleY)
{
    m_pRender->setScaleY(scaleY);
    onScaleYDirtyChanged();
}

float UIWidget::getScaleY()
{
    return m_pRender->getScaleY();
}

void UIWidget::setRotation(float rotation)
{
    m_pRender->setRotation(rotation);
}

float UIWidget::getRotation()
{
    return m_pRender->getRotation();
}

void UIWidget::setRotationX(float rotationX)
{
    m_pRender->setRotationX(rotationX);
}

float UIWidget::getRotationX()
{
    return m_pRender->getRotationX();
}

void UIWidget::setRotationY(float rotationY)
{
    m_pRender->setRotationY(rotationY);
}

float UIWidget::getRotationY()
{
    return m_pRender->getRotationY();
}

void UIWidget::setSkewX(float skewX)
{
    m_pRender->setSkewX(skewX);
}

float UIWidget::getSkewX()
{
    return m_pRender->getSkewX();
}

void UIWidget::setSkewY(float skewY)
{
    m_pRender->setSkewY(skewY);
}

float UIWidget::getSkewY()
{
    return m_pRender->getSkewY();
}

void UIWidget::setVisible(bool visible)
{
    m_bVisibleDirty = true;
    updateChildrenVisibleDirty(m_bVisibleDirty);
    m_bVisible = visible;
    m_pRender->setVisible(visible);
}

bool UIWidget::isVisible()
{
    return m_bVisible;
}

float UIWidget::getRelativeLeftPos()
{
    return getRelativeRect().origin.x;
}

float UIWidget::getRelativeBottomPos()
{
    return getRelativeRect().origin.y;
}

float UIWidget::getRelativeRightPos()
{
    CCRect rect = getRelativeRect();
    return rect.origin.x + rect.size.width;
}

float UIWidget::getRelativeTopPos()
{
    CCRect rect = getRelativeRect();
    return rect.origin.y + rect.size.height;
}

UIWidget* UIWidget::getWidgetParent()
{
    return m_pWidgetParent;
}

void UIWidget::setWidgetParent(UIWidget* parent)
{
	m_pWidgetParent = parent;
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

CCAction* UIWidget::runAction(CCAction *action)
{
    return m_pRender->runAction(action);
}

void UIWidget::setActionManager(CCActionManager *actionManager)
{
    m_pRender->setActionManager(actionManager);
}

CCActionManager* UIWidget::getActionManager()
{
    return m_pRender->getActionManager();
}

void UIWidget::stopAllActions()
{
    m_pRender->stopAllActions();
}

void UIWidget::stopAction(CCAction *action)
{
    m_pRender->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    m_pRender->stopActionByTag(tag);
}

CCAction* UIWidget::getActionByTag(int tag)
{
    return m_pRender->getActionByTag(tag);
}

float UIWidget::getAbsoluteScaleX()
{
    if (m_bScaleXDirty)
    {
        float scaleX = getScaleX();
        UIWidget* parent = getWidgetParent();
        while (parent)
        {
            scaleX *= parent->getScaleX();
            parent = parent->getWidgetParent();
        }
        m_fAbsoluteScaleX = scaleX;
        m_bScaleXDirty = false;
    }
    return m_fAbsoluteScaleX;
}

float UIWidget::getAbsoluteScaleY()
{
    if (m_bScaleYDirty)
    {
        float scaleY = getScaleY();
        UIWidget* parent = getWidgetParent();
        while (parent)
        {
            scaleY *= parent->getScaleY();
            parent = parent->getWidgetParent();
        }
        m_fAbsoluteScaleY = scaleY;
        m_bScaleYDirty = false;
    }
    return m_fAbsoluteScaleY;
}

bool UIWidget::getAbsoluteVisible()
{
    if (m_bVisibleDirty)
    {
        UIWidget* parent = this;
        bool visible = isVisible();
        while (parent){
            visible &= parent->isVisible();
            if (!visible)
            {
                break;
            }
            parent = parent->getWidgetParent();
        }
        m_bAbsoluteVisible = visible;
        m_bVisibleDirty = false;
    }
    return m_bAbsoluteVisible;
}

void UIWidget::updateChildrenVisibleDirty(bool dirty)
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->m_bVisibleDirty = dirty;
        child->updateChildrenVisibleDirty(dirty);
    }
}

void UIWidget::updateChildrenOpacityDirty(bool dirty)
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->m_bOpacityDirty = dirty;
        child->updateChildrenOpacityDirty(dirty);
    }
}    

void UIWidget::adaptSize(float xProportion,float yProportion)
{
    m_fAdaptScaleX = xProportion;
    m_fAdaptScaleY = yProportion;
    setScaleX(m_fAdaptScaleX*getScaleX());
    setScaleY(m_fAdaptScaleY*getScaleY());
}

void UIWidget::setCreateFromFile(bool is)
{
    m_bIsCreatedFromFile = is;
}

void UIWidget::setFileDesignSize(const CCSize &size)
{
    m_fileDesignSize = size;
}

const CCSize& UIWidget::getFileDesignSize()
{
    return m_fileDesignSize;
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
    return 0;
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

void UIWidget::setWidgetTag(int tag)
{
    m_nWidgetTag = tag;
}

int UIWidget::getWidgetTag()
{
    return m_nWidgetTag;
}

void UIWidget::setName(const char* name)
{
    m_strName = name;
}

const char* UIWidget::getName()
{
    return m_strName.c_str();
}

WidgetType UIWidget::getWidgetType()
{
    return m_WidgetType;
}

WidgetName UIWidget::getWidgetName()
{
    return m_WidgetName;
}

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

NS_CC_EXT_END
