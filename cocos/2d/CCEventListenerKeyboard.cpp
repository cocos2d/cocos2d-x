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

#include "CCEventListenerKeyboard.h"
#include "CCEventKeyboard.h"
#include "ccMacros.h"

NS_CC_BEGIN

const std::string EventListenerKeyboard::LISTENER_ID = "__cc_keyboard";

bool EventListenerKeyboard::checkAvailable()
{
    if (onKeyPressed == nullptr && onKeyReleased == nullptr)
    {
        CCASSERT(false, "Invalid EventListenerKeyboard!");
        return false;
    }
    
    return true;
}

EventListenerKeyboard* EventListenerKeyboard::create()
{
    auto ret = new EventListenerKeyboard();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerKeyboard* EventListenerKeyboard::clone()
{
    auto ret = new EventListenerKeyboard();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->onKeyPressed = onKeyPressed;
        ret->onKeyReleased = onKeyReleased;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerKeyboard::EventListenerKeyboard()
: onKeyPressed(nullptr)
, onKeyReleased(nullptr)
{
}

bool EventListenerKeyboard::init()
{
    auto listener = [this](Event* event){
        auto keyboardEvent = static_cast<EventKeyboard*>(event);
        if (keyboardEvent->_isPressed)
        {
            if (onKeyPressed != nullptr)
                onKeyPressed(keyboardEvent->_keyCode, event);
        }
        else
        {
            if (onKeyReleased != nullptr)
                onKeyReleased(keyboardEvent->_keyCode, event);
        }
    };
    
    if (EventListener::init(Type::KEYBOARD, LISTENER_ID, listener))
    {
        return true;
    }
    
    return false;
}

NS_CC_END
