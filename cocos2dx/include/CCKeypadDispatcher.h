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
#include "CCMutableArray.h"

namespace   cocos2d {

typedef enum {
    // the back key clicked msg
    kTypeBackClicked = 1,
    kTypeMenuClicked,
} ccKeypadMSGType;

struct _ccCArray;
/**
@class CCKeypadDispatcher
@brief Dispatch the keypad message from the phone
*/
class CC_DLL CCKeypadDispatcher : public CCObject
{
public:
    CCKeypadDispatcher();
    ~CCKeypadDispatcher();

    /**
    @brief Returns the shared CCKeypadDispatcher object for the system.
    */
    static CCKeypadDispatcher* sharedDispatcher();

    /**
    @brief Release the shared CCKeypadDispatcher object from the system.
    */
    static void purgeSharedDispatcher();

    /**
    @brief add delegate to concern keypad msg
    */
    void addDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern keypad msg
    */
    void removeDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief force add the delegate
    */
    void forceAddDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief force remove the delegate
    */
    void forceRemoveDelegate(CCKeypadDelegate* pDelegate);

    /**
    @brief dispatch the key pad msg
    */
    bool dispatchKeypadMSG(ccKeypadMSGType nMsgType);

protected:

    typedef CCMutableArray<CCKeypadHandler*> KeypadDelegateArray;

    KeypadDelegateArray* m_pDelegates;
    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;

    struct _ccCArray *m_pHandlersToAdd;
    struct _ccCArray *m_pHandlersToRemove;
};

} // namespace   cocos2d 

#endif //__CCKEYPAD_DISPATCHER_H__
