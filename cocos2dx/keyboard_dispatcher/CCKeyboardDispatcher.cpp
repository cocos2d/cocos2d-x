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

#include "CCKeyboardDispatcher.h"
#include "support/data_support/ccCArray.h"

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCKeyboardDispatcher
//
//------------------------------------------------------------------
CCKeyboardDispatcher::CCKeyboardDispatcher()
: m_keyPressDelegate(NULL)
, m_keyReleaseDelegate(NULL)
{
}

CCKeyboardDispatcher::~CCKeyboardDispatcher()
{
}

void CCKeyboardDispatcher::setKeyPressDelegate(CCKeyboardDelegate delegate)
{
    m_keyPressDelegate = delegate;
}

void CCKeyboardDispatcher::setKeyReleaseDelegate(CCKeyboardDelegate delegate)
{
    m_keyReleaseDelegate = delegate;
}

bool CCKeyboardDispatcher::dispatchKeyboardEvent(int keyCode, bool pressed)
{
    if (m_keyPressDelegate != NULL && pressed)
    {
        m_keyPressDelegate(keyCode);
    }
    else if (m_keyReleaseDelegate != NULL)
    {
        m_keyReleaseDelegate(keyCode);
    }
    else
    {
        return false;
    }

    return true;
}

NS_CC_END
