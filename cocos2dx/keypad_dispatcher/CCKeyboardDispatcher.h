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

#ifndef __CCKeyboard_DISPATCHER_H__
#define __CCKeyboard_DISPATCHER_H__

#include "CCKeyboardDelegate.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

typedef enum {
    kLeft,
    kRight,
    kUp,
    kDown,
} ccKeyboardMSGType;

struct _ccCArray;

/**
@class CCKeyboardDispatcher
@brief Dispatch the Keyboard message from the phone
*/
class CC_DLL CCKeyboardDispatcher : public CCObject
{
public:
    CCKeyboardDispatcher();
    ~CCKeyboardDispatcher();

    /**
    @brief add delegate to concern Keyboard msg
    */
    void addDelegate(CCKeyboardDelegate* pDelegate);

    /**
    @brief remove the delegate from the delegates who concern Keyboard msg
    */
    void removeDelegate(CCKeyboardDelegate* pDelegate);

    /**
    @brief force add the delegate
    */
    void forceAddDelegate(CCKeyboardDelegate* pDelegate);

    /**
    @brief force remove the delegate
    */
    void forceRemoveDelegate(CCKeyboardDelegate* pDelegate);

    /**
    @brief dispatch the key down
    */
    bool dispatchKeyboardDown(CCKeyboardEvent event);
    
    /**
    @brief dispatch the key up
    */
    bool dispatchKeyboardUp(CCKeyboardEvent event);

    /**
     @brief dispatch the change in system keys
     */
    bool dispatchKeyboardFlagsChanged(CCKeyboardEvent event);
    
protected:

    CCArray* m_pDelegates;
    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;

    struct _ccCArray *m_pHandlersToAdd;
    struct _ccCArray *m_pHandlersToRemove;
};

// end of input group
/// @} 

NS_CC_END

#endif //__CCKeyboard_DISPATCHER_H__
