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

#ifndef __CC_IME_DELEGATE_H__
#define __CC_IME_DELEGATE_H__

#include "CCGeometry.h"

NS_CC_BEGIN;

typedef struct
{
    CCRect  begin;              // the soft keyboard rectangle when animatin begin
    CCRect  end;                // the soft keyboard rectangle when animatin end
    float     duration;           // the soft keyboard animation duration
} CCIMEKeyboardNotificationInfo;

/**
@brief	Input method editor delegate.
*/
class CC_DLL CCIMEDelegate
{
public:
    virtual ~CCIMEDelegate();

    virtual bool attachWithIME();
    virtual bool detachWithIME();

protected:
    friend class CCIMEDispatcher;

    /**
    @brief	Decide the delegate instance is ready for receive ime message or not.

    Called by CCIMEDispatcher.
    */
    virtual bool canAttachWithIME() { return false; }
    /**
    @brief	When the delegate detach with IME, this method call by CCIMEDispatcher.
    */
    virtual void didAttachWithIME() {}

    /**
    @brief	Decide the delegate instance can stop receive ime message or not.
    */
    virtual bool canDetachWithIME() { return false; }

    /**
    @brief	When the delegate detach with IME, this method call by CCIMEDispatcher.
    */
    virtual void didDetachWithIME() {}

    /**
    @brief	Called by CCIMEDispatcher when some text input from IME.
    */
    virtual void insertText(const char * text, int len) {CC_UNUSED_PARAM(text);CC_UNUSED_PARAM(len);}

    /**
    @brief	Called by CCIMEDispatcher when user clicked the backward key.
    */
    virtual void deleteBackward() {}

    /**
    @brief	Called by CCIMEDispatcher for get text which delegate already has.
    */
    virtual const char * getContentText() { return 0; }

    //////////////////////////////////////////////////////////////////////////
    // keyboard show/hide notification
    //////////////////////////////////////////////////////////////////////////
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    virtual void keyboardDidShow(CCIMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}
    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    virtual void keyboardDidHide(CCIMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}

protected:
    CCIMEDelegate();
};

NS_CC_END;

#endif	// __CC_IME_DELEGATE_H__
