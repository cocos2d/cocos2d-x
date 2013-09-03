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

#include "CCKeyboardEventListener.h"
#include "CCKeyboardEvent.h"
#include "ccMacros.h"

NS_CC_BEGIN

bool KeyboardEventListener::checkAvaiable()
{
    CCASSERT(onKeyPressed && onKeyReleased, "");
    
    return true;
}

std::shared_ptr<KeyboardEventListener> KeyboardEventListener::create()
{
    std::shared_ptr<KeyboardEventListener> ret(new KeyboardEventListener());
    return ret;
}

KeyboardEventListener::KeyboardEventListener()
: EventListener(KeyboardEvent::EVENT_TYPE, nullptr)
, onKeyPressed(nullptr)
, onKeyReleased(nullptr)
{
    onEvent = [this](Event* event){
        auto keyboardEvent = static_cast<KeyboardEvent*>(event);
        if (keyboardEvent->_isPressed)
        {
            onKeyPressed(keyboardEvent->_keyCode, event);
        }
        else
        {
            onKeyReleased(keyboardEvent->_keyCode, event);
        }
    };
}

NS_CC_END
