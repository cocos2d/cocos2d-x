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

#include "CCCommon.h"

NS_CC_BEGIN;

/**
@brief	Input method editor protocol.
*/
class CC_DLL CCIMEDelegate
{
public:
    virtual ~CCIMEDelegate();

    bool attachWithIME();

protected:
    friend class CCIMEDispatcher;

    /**
    @brief	Decide the delegate instance is ready for receive ime message or not.

    Called by CCIMEDispatcher.
    */
    virtual bool canAttachWithIME() = 0;

    /**
    @brief	Decide the delegate instance can stop receive ime message or not.
    */
    virtual bool canDetatchWithIME() = 0;

    /**
    @brief	Input end and release keyboard.
    */
    virtual void detatchWithIME() = 0;

    /**
    @brief	Called by CCIMEDispatcher when some text input from IME.
    */
    virtual void insertText(const char * text, int len) = 0;

    /**
    @brief	Called by CCIMEDispatcher when user clicked the backward key.
    */
    virtual void deleteBackward() = 0;

protected:
    CCIMEDelegate();
};

NS_CC_END;

#endif	// __CC_IME_DELEGATE_H__
