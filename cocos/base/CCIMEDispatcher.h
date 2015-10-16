/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
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

#ifndef __CC_IME_DISPATCHER_H__
#define __CC_IME_DISPATCHER_H__

#include "base/CCIMEDelegate.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN


/**
@brief    Input Method Edit Message Dispatcher.
*/
class CC_DLL IMEDispatcher
{
public:
    /**
     * @js NA
     * @lua NA
     */
    ~IMEDispatcher();

    /**
     * @brief Returns the shared IMEDispatcher object for the system.
     * @js NA
     * @lua NA
     */
    static IMEDispatcher* sharedDispatcher();

    /**
     * @brief Dispatches the input text from IME.
     * @lua NA
     */
    void dispatchInsertText(const char * text, size_t len);

    /**
     * @brief Dispatches the delete-backward operation.
     * @lua NA
     */
    void dispatchDeleteBackward();

    /**
    * @brief Dispatches the press control key operation.
    * @lua NA
    */
    void dispatchControlKey(EventKeyboard::KeyCode keyCode);

    /**
     * @brief Get the content text from IMEDelegate, retrieved previously from IME.
     * @lua NA
     */
    const std::string& getContentText();

    //////////////////////////////////////////////////////////////////////////
    // dispatch keyboard notification
    //////////////////////////////////////////////////////////////////////////
    /**
     * @lua NA
     */
    void dispatchKeyboardWillShow(IMEKeyboardNotificationInfo& info);
    /**
     * @lua NA
     */
    void dispatchKeyboardDidShow(IMEKeyboardNotificationInfo& info);
    /**
     * @lua NA
     */
    void dispatchKeyboardWillHide(IMEKeyboardNotificationInfo& info);
    /**
     * @lua NA
     */
    void dispatchKeyboardDidHide(IMEKeyboardNotificationInfo& info);

protected:
    friend class IMEDelegate;

    /**
     *@brief Add delegate to receive IME messages.
     *@param delegate A instance implements IMEDelegate delegate.
     */
    void addDelegate(IMEDelegate * delegate);

    /**
     *@brief Attach the Delegate to the IME.
     *@param delegate A instance implements IMEDelegate delegate.
     *@return If the old delegate can detach from the IME, and the new delegate 
     *       can attach to the IME, return true, otherwise false.
     */
    bool attachDelegateWithIME(IMEDelegate * delegate);

    /**
     * Detach the delegate to the IME
     *@see `attachDelegateWithIME(IMEDelegate*)`
     *@param delegate  A instance implements IMEDelegate delegate.
     *@return Whether the IME is detached or not.
     */
    bool detachDelegateWithIME(IMEDelegate * delegate);

    /**
     *@brief Remove the delegate from the delegates which receive IME messages.
     *@param delegate A instance implements the IMEDelegate delegate.
     */
    void removeDelegate(IMEDelegate * delegate);

private:
    IMEDispatcher();
    
    class Impl;
    Impl * _impl;
};


NS_CC_END
// end of base group
/// @}

#endif    // __CC_IME_DISPATCHER_H__
