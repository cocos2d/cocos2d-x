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
m_pCurSelectedWidget(NULL),
m_bWidgetBeSorted(false),
m_bTouchDown(false),
m_fLongClickTime(0.0),
m_fLongClickRecordTime(0.0),
checkedDoubleClickWidget(NULL),
m_pRootWidget(NULL)
{
    m_manageredWidget = cocos2d::CCArray::create();
    m_manageredWidget->retain();
    checkedDoubleClickWidget = cocos2d::CCArray::create();
    checkedDoubleClickWidget->retain();
}

UIInputManager::~UIInputManager()
{
    m_manageredWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_manageredWidget);
    checkedDoubleClickWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(checkedDoubleClickWidget);
}

void UIInputManager::registWidget(UIWidget* widget)
{
    if (!widget){
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

void UIInputManager::sortWidgets(cocos2d::extension::UIWidget *widget)
{

    m_manageredWidget->removeAllObjects();
    sortRootWidgets(widget);
    m_bWidgetBeSorted = true;
}

void UIInputManager::sortRootWidgets(UIWidget *root)
{
    for (int i=root->getChildren()->count()-1; i >= 0; i--)
    {
        UIWidget* widget = (UIWidget*)(root->getChildren()->objectAtIndex(i));
        sortRootWidgets(widget);
    }
    if (root->getBeTouchEnable())
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

UIWidget* UIInputManager::checkEventWidget(cocos2d::CCPoint &touchPoint)
{
    if (!m_bWidgetBeSorted && m_pRootWidget)
    {
        sortWidgets(m_pRootWidget);
    }
    int widgetCount = m_manageredWidget->count();
    for (int i=0;i<widgetCount;i++)
    {
        UIWidget* widget = (UIWidget*)(m_manageredWidget->objectAtIndex(i));
        
        if(widget->pointAtSelfBody(touchPoint))
        {
            if (!widget->checkVisibleDependParent(touchPoint))
            {
                continue;
            }
            if (i != m_manageredWidget->count()-1){
                int j = i+1;
                for (;j < m_manageredWidget->count();j++)
                {
                    UIWidget* wid = (UIWidget*)(m_manageredWidget->objectAtIndex(j));
                    wid->didNotSelectSelf();
                }
            }
            return widget;
        }
        else
        {
            widget->didNotSelectSelf();
        }
    }
    return NULL;
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
            m_pCurSelectedWidget->onTouchLongClicked(touchBeganedPoint);
        }
    }
    for (int i=0;i<checkedDoubleClickWidget->count();i++)
    {
        UIWidget* widget = (UIWidget*)(checkedDoubleClickWidget->objectAtIndex(i));
        if (!widget->isVisible())
        {
            continue;
        }
    }
}

bool UIInputManager::onTouchBegan(cocos2d::CCTouch* touch)
{
    touchBeganedPoint.x = touch->getLocation().x;
    touchBeganedPoint.y = touch->getLocation().y;
    UIWidget* hitWidget = checkEventWidget(touchBeganedPoint);
    if (!hitWidget || !hitWidget->isActive())
    {
        m_pCurSelectedWidget = NULL;
        return false;
    }
    m_pCurSelectedWidget = hitWidget;
    hitWidget->onTouchBegan(touchBeganedPoint);
    m_bTouchDown = true;
    return true;
}

bool UIInputManager::onTouchMoved(cocos2d::CCTouch* touch)
{
    UIWidget* hitWidget = m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->isActive())
    {
        return false;
    }
    touchMovedPoint.x = touch->getLocation().x;
    touchMovedPoint.y = touch->getLocation().y;
    hitWidget->onTouchMoved(touchMovedPoint);
    if (m_bTouchDown)
    {
        m_fLongClickRecordTime = 0;
        m_bTouchDown = false;
    }
    return true;
}

bool UIInputManager::onTouchEnd(cocos2d::CCTouch* touch)
{
    m_bTouchDown = false;
    UIWidget* hitWidget = m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->isActive())
    {
        return false;
    }
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    hitWidget->onTouchEnded(touchEndedPoint);
    m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

bool UIInputManager::onTouchCancelled(cocos2d::CCTouch* touch)
{
    m_bTouchDown = false;
    UIWidget* hitWidget = m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->isActive())
    {
        return false;
    }
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    hitWidget->onTouchCancelled(touchEndedPoint);
    m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

void UIInputManager::setRootWidget(cocos2d::extension::UIWidget *root)
{
    m_pRootWidget = root;
}

UIWidget* UIInputManager::getRootWidget()
{
    return m_pRootWidget;
}

NS_CC_EXT_END