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
_rootWidget(NULL),
_inputManager(NULL)
{
    
}

UILayer::~UILayer()
{
    _rootWidget->release();
    CC_SAFE_DELETE(_inputManager);
}

bool UILayer::init()
{
    if (CCLayer::init())
    {
        _rootWidget = UIRootWidget::create();
        _rootWidget->retain();
        _rootWidget->onEnter();
        addChild(_rootWidget->getRenderer());
        _inputManager = new UIInputManager();
        _inputManager->setRootWidget(_rootWidget);
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
    _rootWidget->addChild(widget);
}

void UILayer::removeWidget(UIWidget* widget)
{
    _rootWidget->removeChild(widget);
}

void UILayer::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    _rootWidget->setVisible(visible);
}

UIWidget* UILayer::getWidgetByTag(int tag)
{
    if (!_rootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByTag(_rootWidget, tag);
}

UIWidget* UILayer::getWidgetByName(const char* name)
{
    if (!_rootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByName(_rootWidget, name);
}

UIRootWidget* UILayer::getRootWidget()
{
    return _rootWidget;
}

UIInputManager* UILayer::getInputManager()
{
    return _inputManager;
}

void UILayer::clear()
{
    _rootWidget->removeAllChildren();
}

bool UILayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (_inputManager && _inputManager->onTouchBegan(pTouch))
    {
        return true;
    }
    return false;
}

void UILayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    _inputManager->onTouchMoved(pTouch);
}

void UILayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    _inputManager->onTouchEnd(pTouch);
}

void UILayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    _inputManager->onTouchCancelled(pTouch);
}

NS_CC_EXT_END