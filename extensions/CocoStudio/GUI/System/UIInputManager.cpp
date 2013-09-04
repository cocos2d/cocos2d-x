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

#include "UIInputManager.h"
#include "UIHelper.h"

NS_CC_EXT_BEGIN

UIInputManager::UIInputManager():
m_manageredWidget(NULL),
//m_pCurSelectedWidget(NULL),
m_bWidgetBeSorted(false),
m_bTouchDown(false),
m_fLongClickTime(0.0),
m_fLongClickRecordTime(0.0),
checkedDoubleClickWidget(NULL),
m_pRootWidget(NULL)
{
    m_manageredWidget = CCArray::create();
    m_manageredWidget->retain();
    checkedDoubleClickWidget = CCArray::create();
    checkedDoubleClickWidget->retain();
    m_pSelectedWidgets = CCArray::create();
    m_pSelectedWidgets->retain();
}

UIInputManager::~UIInputManager()
{
    m_manageredWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_manageredWidget);
    checkedDoubleClickWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(checkedDoubleClickWidget);
    m_pSelectedWidgets->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_pSelectedWidgets);
}

void UIInputManager::registWidget(UIWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (m_manageredWidget->containsObject(widget))
    {
        return;
    }
    m_manageredWidget->addObject(widget);
}

void UIInputManager::uiSceneHasChanged()
{
    m_bWidgetBeSorted = false;
}

void UIInputManager::sortWidgets(UIWidget *widget)
{
    m_manageredWidget->removeAllObjects();
    sortRootWidgets(widget);
    m_bWidgetBeSorted = true;
}

void UIInputManager::sortRootWidgets(UIWidget *root)
{
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=length-1; i >= 0; i--)
    {
        UIWidget* widget = (UIWidget*)(arrayRootChildren->arr[i]);
        sortRootWidgets(widget);
    }
    if (root->isTouchEnabled())
    {
        registWidget(root);
    }
}

void UIInputManager::removeManageredWidget(UIWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (!m_manageredWidget->containsObject(widget))
    {
        return;
    }
    m_manageredWidget->removeObject(widget);
}

bool UIInputManager::checkEventWidget(const CCPoint &touchPoint)
{
    if (!m_bWidgetBeSorted && m_pRootWidget)
    {
        sortWidgets(m_pRootWidget);
    }
    ccArray* arrayWidget = m_manageredWidget->data;
    int widgetCount = arrayWidget->num;
    for (int i=0;i<widgetCount;i++)
    {
        UIWidget* widget = (UIWidget*)(arrayWidget->arr[i]);
        if(widget->hitTest(touchPoint) && widget->isEnabled())
        {
            if (!widget->parentAreaContainPoint(touchPoint))
            {
                continue;
            }
            m_pSelectedWidgets->addObject(widget);
            if (!widget->onTouchBegan(touchPoint))
            {
                break;
            }
        }
    }
    return (m_pSelectedWidgets->count() > 0);
}

void UIInputManager::addCheckedDoubleClickWidget(UIWidget* widget)
{
    if (checkedDoubleClickWidget->containsObject(widget))
    {
        return;
    }
    checkedDoubleClickWidget->addObject(widget);
}

void UIInputManager::update(float dt)
{
    if (m_bTouchDown)
    {
        m_fLongClickRecordTime += dt;
        if (m_fLongClickRecordTime >= m_fLongClickTime)
        {
            m_fLongClickRecordTime = 0;
            m_bTouchDown = false;
//            m_pCurSelectedWidget->onTouchLongClicked(touchBeganedPoint);
        }
    }
    ccArray* arrayWidget = checkedDoubleClickWidget->data;
    int widgetCount = arrayWidget->num;
    for (int i=0;i<widgetCount;i++)
    {
        UIWidget* widget = (UIWidget*)(arrayWidget->arr[i]);
        if (!widget->isVisible())
        {
            continue;
        }
    }
}

bool UIInputManager::onTouchBegan(CCTouch* touch)
{
    touchBeganedPoint.x = touch->getLocation().x;
    touchBeganedPoint.y = touch->getLocation().y;
    m_bTouchDown = true;
    return checkEventWidget(touchBeganedPoint);
}

void UIInputManager::onTouchMoved(CCTouch* touch)
{
    touchMovedPoint.x = touch->getLocation().x;
    touchMovedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchMoved(touchMovedPoint);
    }
    if (m_bTouchDown)
    {
        m_fLongClickRecordTime = 0;
        m_bTouchDown = false;
    }
}

void UIInputManager::onTouchEnd(CCTouch* touch)
{
    m_bTouchDown = false;
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchEnded(touchEndedPoint);
    }
    m_pSelectedWidgets->removeAllObjects();
}

void UIInputManager::onTouchCancelled(CCTouch* touch)
{
    m_bTouchDown = false;
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchCancelled(touchEndedPoint);
    }
    m_pSelectedWidgets->removeAllObjects();
}

void UIInputManager::setRootWidget(UIWidget *root)
{
    m_pRootWidget = root;
}

UIWidget* UIInputManager::getRootWidget()
{
    return m_pRootWidget;
}

NS_CC_EXT_END