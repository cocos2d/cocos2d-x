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

#ifndef __CCKEYPAD_DISPATCHER_H__
#define __CCKEYPAD_DISPATCHER_H__

#include "CCKeypadDelegate.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

typedef enum {
    // the back key clicked msg
    kTypeBackClicked = 1,
    kTypeMenuClicked,
} ccKeypadMSGType;

struct _ccCArray;
/**
@class KeypadDispatcher
@brief Dispatch the keypad message from the phone
*/
class CC_DLL KeypadDispatcher : public Object
{
public:
    KeypadDispatcher();
    ~KeypadDispatcher();

    /**
    @brief add delegate to concern keypad msg
    */
    void addDelegate(KeypadDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern keypad msg
    */
    void removeDelegate(KeypadDelegate* pDelegate);

    /**
    @brief force add the delegate
    */
    void forceAddDelegate(KeypadDelegate* pDelegate);

    /**
    @brief force remove the delegate
    */
    void forceRemoveDelegate(KeypadDelegate* pDelegate);

    /**
    @brief dispatch the key pad msg
    */
    bool dispatchKeypadMSG(ccKeypadMSGType nMsgType);

protected:

    Array* _delegates;
    bool _locked;
    bool _toAdd;
    bool _toRemove;

    struct _ccCArray *_handlersToAdd;
    struct _ccCArray *_handlersToRemove;
};

// end of input group
/// @} 

NS_CC_END

#endif //__CCKEYPAD_DISPATCHER_H__
