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
_manageredWidget(NULL),
_touchDown(false),
_longClickTime(0.0),
_longClickRecordTime(0.0),
_checkedDoubleClickWidget(NULL),
_rootWidget(NULL)
{
    _manageredWidget = CCArray::create();
    _manageredWidget->retain();
    _checkedDoubleClickWidget = CCArray::create();
    _checkedDoubleClickWidget->retain();
    _selectedWidgets = CCArray::create();
    _selectedWidgets->retain();
}

UIInputManager::~UIInputManager()
{
    _manageredWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(_manageredWidget);
    _checkedDoubleClickWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(_checkedDoubleClickWidget);
    _selectedWidgets->removeAllObjects();
    CC_SAFE_RELEASE_NULL(_selectedWidgets);
}

void UIInputManager::registWidget(UIWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (_manageredWidget->containsObject(widget))
    {
        return;
    }
    _manageredWidget->addObject(widget);
}

bool UIInputManager::checkTouchEvent(UIWidget *root, const Point &touchPoint)
{
    ccArray* arrayRootChildren = root->getChildren()->data;
    int length = arrayRootChildren->num;
    for (int i=length-1; i >= 0; i--)
    {
        UIWidget* widget = (UIWidget*)(arrayRootChildren->arr[i]);
        if (checkTouchEvent(widget, touchPoint))
        {
            return true;
        }
    }
    if (root->isEnabled() && root->isTouchEnabled() && root->hitTest(touchPoint) && root->clippingParentAreaContainPoint(touchPoint))
    {
        _selectedWidgets->addObject(root);
        root->onTouchBegan(touchPoint);
        return true;
    }
    return false;
}

void UIInputManager::removeManageredWidget(UIWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (!_manageredWidget->containsObject(widget))
    {
        return;
    }
    _manageredWidget->removeObject(widget);
}

bool UIInputManager::checkEventWidget(const Point &touchPoint)
{
    checkTouchEvent(_rootWidget,touchPoint);
    return (_selectedWidgets->count() > 0);
}

void UIInputManager::addCheckedDoubleClickWidget(UIWidget* widget)
{
    if (_checkedDoubleClickWidget->containsObject(widget))
    {
        return;
    }
    _checkedDoubleClickWidget->addObject(widget);
}

void UIInputManager::update(float dt)
{
    if (_touchDown)
    {
        _longClickRecordTime += dt;
        if (_longClickRecordTime >= _longClickTime)
        {
            _longClickRecordTime = 0;
            _touchDown = false;
//            m_pCurSelectedWidget->onTouchLongClicked(touchBeganedPoint);
        }
    }
    ccArray* arrayWidget = _checkedDoubleClickWidget->data;
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

bool UIInputManager::onTouchBegan(Touch* touch)
{
    _touchBeganedPoint.x = touch->getLocation().x;
    _touchBeganedPoint.y = touch->getLocation().y;
    _touchDown = true;
    return checkEventWidget(_touchBeganedPoint);
}

void UIInputManager::onTouchMoved(Touch* touch)
{
    _touchMovedPoint.x = touch->getLocation().x;
    _touchMovedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = _selectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchMoved(_touchMovedPoint);
    }
    if (_touchDown)
    {
        _longClickRecordTime = 0;
        _touchDown = false;
    }
}

void UIInputManager::onTouchEnd(Touch* touch)
{
    _touchDown = false;
    _touchEndedPoint.x = touch->getLocation().x;
    _touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = _selectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchEnded(_touchEndedPoint);
    }
    _selectedWidgets->removeAllObjects();
}

void UIInputManager::onTouchCancelled(Touch* touch)
{
    _touchDown = false;
    _touchEndedPoint.x = touch->getLocation().x;
    _touchEndedPoint.y = touch->getLocation().y;
    ccArray* selectedWidgetArray = _selectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        UIWidget* hitWidget = (UIWidget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchCancelled(_touchEndedPoint);
    }
    _selectedWidgets->removeAllObjects();
}

void UIInputManager::setRootWidget(UIWidget *root)
{
    _rootWidget = root;
}

UIWidget* UIInputManager::getRootWidget()
{
    return _rootWidget;
}

NS_CC_EXT_END