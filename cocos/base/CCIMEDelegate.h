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
 * @~english A static global empty std::string install.
 * @~chinese 一个全局的空字符
 */
extern const std::string CC_DLL STD_STRING_EMPTY;

/**
 * @~english Keyboard notification event type.
 * @~chinese 键盘事件的类型
 */
typedef struct
{
    Rect  begin;              // the soft keyboard rectangle when animation begins
    Rect  end;                // the soft keyboard rectangle when animation ends
    float     duration;           // the soft keyboard animation duration
} IMEKeyboardNotificationInfo;

/**
 * @brief @~english Input method editor delegate.
 * @~chinese 输入代理
 */
class CC_DLL IMEDelegate
{
public:

    /**
     * @~english Default destructor.
     * @~chinese 析构函数
     *
     * @js NA
     * @lua NA
     */
    virtual ~IMEDelegate();
    
    /**
     * @~english attach with IME.
     * @~chinese 挂载IME
     *
     * @js NA
     * @lua NA
     */
    virtual bool attachWithIME();
    
    /**
     * @~english detach with IME
     * @~chinese 分离IME
     *
     * @js NA
     * @lua NA
     */
    virtual bool detachWithIME();

protected:
    friend class IMEDispatcher;

    /**
     * @brief @~english Could mount an IME
     * @~chinese 能否挂载IME
     *
     * @js NA
     * @lua NA
     */
    virtual bool canAttachWithIME() { return false; }

    /**
     * @brief @~english Whether have mounted the IME
     * @~chinese 是否已经挂载了IME
     * @js NA
     * @lua NA
     */
    virtual void didAttachWithIME() {}

    /**
     * @brief @~english Could detach an IME
     * @~chinese 能否分离一个IME
     *
     * @js NA
     * @lua NA
     */
    virtual bool canDetachWithIME() { return false; }

    /**
     * @brief @~english Whether have detached the IME.
     * @~chinese 是否已经分离了IME
     *
     * @js NA
     * @lua NA
     */
    virtual void didDetachWithIME() {}

    /**
     * @brief @~english insert text
     * @~chinese 插入文本
     * @js NA
     * @lua NA
     */
    virtual void insertText(const char * text, size_t len) {CC_UNUSED_PARAM(text);CC_UNUSED_PARAM(len);}

    /**
     * @brief @~english delete back ward
     * @~chinese 回退删除
     *
     * @js NA
     * @lua NA
     */
    virtual void deleteBackward() {}

    /**
     * @brief @~english get content text
     * @~chinese 获取内容文本
     *
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
