/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (C) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_IME_DELEGATE_H__
#define __CC_IME_DELEGATE_H__

#include <string>
#include "math/CCGeometry.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

/**
 * A static global empty std::string install.
 */
extern const std::string CC_DLL STD_STRING_EMPTY;


/**
 * Keyboard notification event type.
 */
typedef struct
{
    Rect  begin;              // the soft keyboard rectangle when animation begins
    Rect  end;                // the soft keyboard rectangle when animation ends
    float     duration;           // the soft keyboard animation duration
} IMEKeyboardNotificationInfo;

/**
 *@brief    Input method editor delegate.
 */
class CC_DLL IMEDelegate
{
public:
    /**
     * Default constructor.
     * @js NA
     * @lua NA
     */
    virtual ~IMEDelegate();
    
    /**
     * Default destructor.
     * @js NA
     * @lua NA
     */
    virtual bool attachWithIME();
    
    /**
     * Determine whether the IME is detached or not.
     * @js NA
     * @lua NA
     */
    virtual bool detachWithIME();

protected:
    friend class IMEDispatcher;

    /**
    @brief    Decide if the delegate instance is ready to receive an IME message.

    Called by IMEDispatcher.
    * @js NA
    * @lua NA
    */
    virtual bool canAttachWithIME() { return false; }
    /**
    @brief    When the delegate detaches from the IME, this method is called by IMEDispatcher.
    * @js NA
    * @lua NA
    */
    virtual void didAttachWithIME() {}

    /**
    @brief    Decide if the delegate instance can stop receiving IME messages.
    * @js NA
    * @lua NA
    */
    virtual bool canDetachWithIME() { return false; }

    /**
    @brief    When the delegate detaches from the IME, this method is called by IMEDispatcher.
    * @js NA
    * @lua NA
    */
    virtual void didDetachWithIME() {}

    /**
    @brief    Called by IMEDispatcher when text input received from the IME.
    * @js NA
    * @lua NA
    */
    virtual void insertText(const char * text, size_t len) {CC_UNUSED_PARAM(text);CC_UNUSED_PARAM(len);}

    /**
    @brief    Called by IMEDispatcher after the user clicks the backward key.
    * @js NA
    * @lua NA
    */
    virtual void deleteBackward() {}

    /**
    @brief    Called by IMEDispatcher for text stored in delegate.
    * @js NA
    * @lua NA
    */
    virtual const std::string& getContentText() { return STD_STRING_EMPTY; }

    //////////////////////////////////////////////////////////////////////////
    // keyboard show/hide notification
    //////////////////////////////////////////////////////////////////////////
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}

protected:
    /**
     * @js NA
     * @lua NA
     */
    IMEDelegate();
};


NS_CC_END
// end of base group
/// @}

#endif    // __CC_IME_DELEGATE_H__
