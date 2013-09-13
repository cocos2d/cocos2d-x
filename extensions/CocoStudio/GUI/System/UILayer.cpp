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

#include "UILayer.h"
#include "UIHelper.h"

NS_CC_EXT_BEGIN

UILayer::UILayer():
m_pRootWidget(NULL),
m_pInputManager(NULL),
m_updateEnableWidget(NULL)
{
    
}

UILayer::~UILayer()
{
    m_pRootWidget->release();
    CC_SAFE_DELETE(m_pInputManager);
    m_updateEnableWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_updateEnableWidget);
}

bool UILayer::init()
{
    if (CCLayer::init())
    {
        m_pRootWidget = UIRootWidget::create();
        m_pRootWidget->retain();
        m_pRootWidget->onEnter();
        addChild(m_pRootWidget->getRenderer());
        m_pInputManager = new UIInputManager();
        m_pInputManager->setRootWidget(m_pRootWidget);
        m_updateEnableWidget = CCArray::create();
        m_updateEnableWidget->retain();
        return true;
    }
    return false;
}

UILayer* UILayer::create(void)
{
    UILayer *pRet = new UILayer();
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

void UILayer::onEnter()
{
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    CCLayer::onEnter();
    
}

void UILayer::onExit()
{
    setTouchEnabled(false);
    CCLayer::onExit();
}

void UILayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void UILayer::addWidget(UIWidget* widget)
{
    m_pRootWidget->addChild(widget);
}

void UILayer::removeWidget(UIWidget* widget)
{
    m_pRootWidget->removeChild(widget);
}

void UILayer::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    m_pRootWidget->setVisible(visible);
}

void UILayer::update(float dt)
{
    if (!m_updateEnableWidget)
    {
        return;
    }
    ccArray* arrayWidget = m_updateEnableWidget->data;
    int length = arrayWidget->num;
    for (int i=0; i<length; i++)
    {
        dynamic_cast<UIWidget*>(arrayWidget->arr[i])->update(dt);
    }
}

void UILayer::addUpdateEnableWidget(UIWidget* widget)
{
    if (!widget || !m_updateEnableWidget)
    {
        return;
    }
    if (m_updateEnableWidget->containsObject(widget))
    {
        return;
    }
    m_updateEnableWidget->addObject(widget);
}

void UILayer::removeUpdateEnableWidget(UIWidget* widget)
{
    if (!widget || !m_updateEnableWidget)
    {
        return;
    }
    if (!m_updateEnableWidget->containsObject(widget))
    {
        return;
    }
    m_updateEnableWidget->removeObject(widget);
}

UIWidget* UILayer::getWidgetByTag(int tag)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByTag(m_pRootWidget, tag);
}

UIWidget* UILayer::getWidgetByName(const char* name)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByName(m_pRootWidget, name);
}

UIRootWidget* UILayer::getRootWidget()
{
    return m_pRootWidget;
}

UIInputManager* UILayer::getInputManager()
{
    return m_pInputManager;
}

void UILayer::clear()
{
    m_pRootWidget->removeAllChildren();
}

bool UILayer::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (m_pInputManager && m_pInputManager->onTouchBegan(pTouch))
    {
        return true;
    }
    return false;
}

void UILayer::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    m_pInputManager->onTouchMoved(pTouch);
}

void UILayer::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    m_pInputManager->onTouchEnd(pTouch);
}

void UILayer::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    m_pInputManager->onTouchCancelled(pTouch);
}

NS_CC_EXT_END