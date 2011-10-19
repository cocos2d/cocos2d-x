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

#ifndef __CC_IME_DISPATCHER_H__
#define __CC_IME_DISPATCHER_H__

#include "CCIMEDelegate.h"

NS_CC_BEGIN;

/**
@brief	Input Method Edit Message Dispatcher.
*/
class CC_DLL CCIMEDispatcher
{
public:
    ~CCIMEDispatcher();

    /**
    @brief Returns the shared CCIMEDispatcher object for the system.
    */
    static CCIMEDispatcher* sharedDispatcher();

//     /**
//     @brief Release all CCIMEDelegates from shared dispatcher.
//     */
//     static void purgeSharedDispatcher();

    /**
    @brief dispatch the input text from ime
    */
    void dispatchInsertText(const char * pText, int nLen);

    /**
    @brief	dispatch the delete backward operation
    */
    void dispatchDeleteBackward();

    /**
    @brief	get the content text, which current CCIMEDelegate which attached with IME has.
    */
    const char * getContentText();

    //////////////////////////////////////////////////////////////////////////
    // dispatch keyboard notification
    //////////////////////////////////////////////////////////////////////////
    void dispatchKeyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    void dispatchKeyboardDidShow(CCIMEKeyboardNotificationInfo& info);
    void dispatchKeyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    void dispatchKeyboardDidHide(CCIMEKeyboardNotificationInfo& info);

protected:
    friend class CCIMEDelegate;

    /**
    @brief add delegate to concern ime msg
    */
    void addDelegate(CCIMEDelegate * pDelegate);

    /**
    @brief	attach the pDeleate with ime.
    @return If the old delegate can detattach with ime and the new delegate 
            can attach with ime, return true, otherwise return false.
    */
    bool attachDelegateWithIME(CCIMEDelegate * pDelegate);
    bool detachDelegateWithIME(CCIMEDelegate * pDelegate);

    /**
    @brief remove the delegate from the delegates who concern ime msg
    */
    void removeDelegate(CCIMEDelegate * pDelegate);

private:
    CCIMEDispatcher();
    
    class Impl;
    Impl * m_pImpl;
};

NS_CC_END;

#endif	// __CC_IME_DISPATCHER_H__
