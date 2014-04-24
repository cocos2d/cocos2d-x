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

#include "UITouchGroup.h"
#include "UIHelper.h"

NS_CC_BEGIN

namespace ui {

TouchGroup::TouchGroup():
m_pRootWidget(NULL)
{
}

TouchGroup::~TouchGroup()
{
    m_pSelectedWidgets->removeAllObjects();
    m_pSelectedWidgets->release();
    m_pRootWidget->release();
}

bool TouchGroup::init()
{
    if (CCLayer::init())
    {
        m_pSelectedWidgets = CCArray::create();
        m_pSelectedWidgets->retain();
        m_pRootWidget = Widget::create();
        m_pRootWidget->retain();
        addChild(m_pRootWidget);
        return true;
    }
    return false;
}

TouchGroup* TouchGroup::create(void)
{
    TouchGroup *pRet = new TouchGroup();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void TouchGroup::onEnter()
{
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    CCLayer::onEnter();
}

void TouchGroup::onExit()
{
    setTouchEnabled(false);
    CCLayer::onExit();
}

void TouchGroup::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}
    
bool TouchGroup::checkEventWidget(CCTouch* touch, CCEvent *pEvent)
{
    checkTouchEvent(m_pRootWidget,touch, pEvent);
    return (m_pSelectedWidgets->count() > 0);
}
    
bool TouchGroup::checkTouchEvent(Widget *root, CCTouch* touch, CCEvent* pEvent)
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

void TouchGroup::addWidget(Widget* widget)
{
    m_pRootWidget->addChild(widget);
}

void TouchGroup::removeWidget(Widget* widget)
{
    m_pRootWidget->removeChild(widget);
}

Widget* TouchGroup::getWidgetByTag(int tag)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return UIHelper::seekWidgetByTag(m_pRootWidget, tag);
}

Widget* TouchGroup::getWidgetByName(const char* name)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return UIHelper::seekWidgetByName(m_pRootWidget, name);
}

Widget* TouchGroup::getRootWidget()
{
    return m_pRootWidget;
}

void TouchGroup::clear()
{
    m_pRootWidget->removeAllChildren();
}

bool TouchGroup::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return checkEventWidget(pTouch, pEvent);
}

void TouchGroup::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchMoved(pTouch, pEvent);
    }
}

void TouchGroup::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[0]);
        m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchEnded(pTouch, pEvent);
    }
}

void TouchGroup::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        Widget* hitWidget = (Widget*)(selectedWidgetArray->arr[0]);
        m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchCancelled(pTouch, pEvent);
    }
}
    
}

NS_CC_END