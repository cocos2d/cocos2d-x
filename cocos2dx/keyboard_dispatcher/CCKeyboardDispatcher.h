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

#ifndef __CCKEYBOARD_DISPATCHER_H__
#define __CCKEYBOARD_DISPATCHER_H__

#include <vector>
#include <functional>
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

typedef std::function<void(int)> KeyboardDelegate;

/**
@class KeyboardDispatcher
@brief Dispatch the keypad message from the phone
*/
class CC_DLL KeyboardDispatcher : public Object
{
public:
    KeyboardDispatcher();
    ~KeyboardDispatcher();

    /**
    @brief set delagate to key press event
    */
    void setKeyPressDelegate(KeyboardDelegate delegate);
    /**
    @brief set delagate to key release event
    */
    void setKeyReleaseDelegate(KeyboardDelegate delegate);

    /**
    @brief dispatch the key stroke event
    */
    bool dispatchKeyboardEvent(int keyCode, bool pressed);

protected:

    KeyboardDelegate _keyPressDelegate;
    KeyboardDelegate _keyReleaseDelegate;
};

// end of input group
/// @} 

NS_CC_END

#endif //__CCKEYBOARD_DISPATCHER_H__
