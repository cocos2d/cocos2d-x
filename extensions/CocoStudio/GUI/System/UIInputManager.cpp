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

NS_CC_BEGIN

namespace gui {

UIInputManager::UIInputManager():
m_manageredWidget(NULL),
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

void UIInputManager::registWidget(Widget* widget)
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

bool UIInputManager::checkTouchEvent(Widget *root, CCTouch* touch, CCEvent* pEvent)
{
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=length-1; i >= 0; i--)
    {
        Widget* widget = (Widget*)(arrayRootChildren->arr[i]);
        if (checkTouchEvent(widget, touch, pEvent))
        {
            return true;
        }
    }
    bool pass = root->onTouchBegan(touch, pEvent);
    if (root->_hitted)
    {
        m_pSelectedWidgets->addObject(root);
        return true;
    }
    return pass;
}

void UIInputManager::removeManageredWidget(Widget* widget)
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

bool UIInputManager::checkEventWidget(CCTouch* touch, CCEvent *pEvent)
{
    checkTouchEvent(m_pRootWidget,touch, pEvent);
    return (m_pSelectedWidgets->count() > 0);
}

void UIInputManager::addCheckedDoubleClickWidget(Widget* widget)
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
        Widget* widget = (Widget*)(arrayWidget->arr[i]);
        if (!widget->isVisible())
        {
            continue;
        }
    }
}

bool UIInputManager::onTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    touchBeganedPoint.x = touch->getLocation().x;
    touchBeganedPoint.y = touch->getLocation().y;
    m_bTouchDown = true;
    return checkEventWidget(touch, pEvent);
}

void UIInputManager::onTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    touchMovedPoint.x = touch->getLocation().x;
    touchMovedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchMoved(touch, pEvent);
    }
    if (m_bTouchDown)
    {
        m_fLongClickRecordTime = 0;
        m_bTouchDown = false;
    }
}

void UIInputManager::onTouchEnd(CCTouch* touch, CCEvent *pEvent)
{
    m_bTouchDown = false;
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[0]);
        m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchEnded(touch, pEvent);
    }
}

void UIInputManager::onTouchCancelled(CCTouch* touch, CCEvent *pEvent)
{
    m_bTouchDown = false;
    touchEndedPoint.x = touch->getLocation().x;
    touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[0]);
        m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchCancelled(touch, pEvent);
    }
}

void UIInputManager::setRootWidget(Widget *root)
{
    m_pRootWidget = root;
}

Widget* UIInputManager::getRootWidget()
{
    return m_pRootWidget;
}
    
}

NS_CC_END