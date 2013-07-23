/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCKeypadDelegate.h"
#include "ccMacros.h"

NS_CC_BEGIN

//------------------------------------------------------------------
//
// KeypadHandler
//
//------------------------------------------------------------------
KeypadDelegate* KeypadHandler::getDelegate()
{
    return _delegate;
}

KeypadHandler::~KeypadHandler()
{
    if (_delegate)
    {
        dynamic_cast<Object*>(_delegate)->release();
    }  
}

void KeypadHandler::setDelegate(KeypadDelegate *pDelegate)
{
    if (pDelegate)
    {
        dynamic_cast<Object*>(pDelegate)->retain();
    }

    if (_delegate)
    {
        dynamic_cast<Object*>(_delegate)->release();
    }
    _delegate = pDelegate;
}

bool KeypadHandler::initWithDelegate(KeypadDelegate *pDelegate)
{
    CCASSERT(pDelegate != NULL, "It's a wrong delegate!");

    _delegate = pDelegate;
    dynamic_cast<Object*>(pDelegate)->retain();

    return true;
}

KeypadHandler* KeypadHandler::handlerWithDelegate(KeypadDelegate *pDelegate)
{
    KeypadHandler* pHandler = new KeypadHandler;

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}

NS_CC_END
