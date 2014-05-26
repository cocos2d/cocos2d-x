/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "UIFocusManager.h"
#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
    static const int keyboardEventPriority = 1;
    
    FocusManager* FocusManager::_instance = nullptr;
    
    FocusManager* FocusManager::getInstance()
    {
        if (nullptr == _instance)
        {
            _instance = new FocusManager;
        }
        return _instance;
    }
    
    void FocusManager::destroyInstance()
    {
        CC_SAFE_DELETE(_instance);

    }
    
    FocusManager::~FocusManager()
    {
        this->removeKeyboardEventListener();
    }
    
    void FocusManager::onKeypadKeyPressed(EventKeyboard::KeyCode  keyCode, Event *event)
    {
        if (_enableFocusNavigation && _firstFocusedWidget)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_DOWN)
            {
                _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::DOWN, _firstFocusedWidget);
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_UP)
            {
                _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::UP, _firstFocusedWidget);
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT)
            {
                _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::LEFT, _firstFocusedWidget);
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
            {
                _firstFocusedWidget = _firstFocusedWidget->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _firstFocusedWidget);
            }
        }
    }
    
    void FocusManager::enableFocusNavigation(bool flag)
    {
        if (_enableFocusNavigation == flag)
            return;
        
        _enableFocusNavigation = flag;
        
        if (flag)
            this->addKeyboardEventListener();
        else
            this->removeKeyboardEventListener();
    }
    
    void FocusManager::setFirstFocsuedWidget(Widget* widget)
    {
        _firstFocusedWidget = widget;
    }
    
    void FocusManager::addKeyboardEventListener()
    {
        if (nullptr == _keyboardListener)
        {
            CCASSERT(_firstFocusedWidget != nullptr, "Please set the first focused widget first!");
            
            _keyboardListener = EventListenerKeyboard::create();
            _keyboardListener->onKeyReleased = CC_CALLBACK_2(FocusManager::onKeypadKeyPressed, this);
            EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->addEventListenerWithFixedPriority(_keyboardListener, keyboardEventPriority);
        }
    }
    
    void FocusManager::removeKeyboardEventListener()
    {
        if (nullptr != _keyboardListener)
        {
            EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeEventListener(_keyboardListener);
            _keyboardListener = nullptr;
        }
    }
}

NS_CC_END