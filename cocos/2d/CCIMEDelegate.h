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

NS_CC_BEGIN
extern const std::string STD_STRING_EMPTY;

/**
 * @addtogroup input
 * @{
 */

typedef struct
{
    Rect  begin;              // 键盘动画开始时，软键盘所在矩形区域
    Rect  end;                // 键盘动画结束时，软键盘所在矩形区域
    float     duration;           // 软键盘动画时长
} IMEKeyboardNotificationInfo;

/**
@brief    输入编辑器的delegate
*/
class CC_DLL IMEDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~IMEDelegate();
    /**
     * @js NA
     * @lua NA
     */
    virtual bool attachWithIME();
    /**
     * @js NA
     * @lua NA
     */
    virtual bool detachWithIME();

protected:
    friend class IMEDispatcher;

    /**
    @brief     分辨delegate实例是否准备接收一条IME消息

    Called by IMEDispatcher.
    * @js NA
    * @lua NA
    */
    virtual bool canAttachWithIME() { return false; }
    /**
    @brief    当IME分派delegate，这个方法将被IMEDispatcher调用
    * @js NA
    * @lua NA
    */
    virtual void didAttachWithIME() {}

    /**
    @brief    决定delegate实例是否停止接收IME发送的消息
    * @js NA
    * @lua NA
    */
    virtual bool canDetachWithIME() { return false; }

    /**
    @brief    当IME分派delegate，这个方法将被IMEDispatcher调用
    * @js NA
    * @lua NA
    */
    virtual void didDetachWithIME() {}

    /**
    @brief    当文本输入从IME传递过来，这个方法被IMEDispatcher调用
    * @js NA
    * @lua NA
    */
    virtual void insertText(const char * text, size_t len) {CC_UNUSED_PARAM(text);CC_UNUSED_PARAM(len);}

    /**
    @brief    当user点击回退键，这个方法被IMEDispatcher调用
    * @js NA
    * @lua NA
    */
    virtual void deleteBackward() {}

    /**
    @brief    IMEDispatcher调用该方法获得保存在delegate中的文本
    * @js NA
    * @lua NA
    */
    virtual const std::string& getContentText() { return STD_STRING_EMPTY; }

    //////////////////////////////////////////////////////////////////////////
    // 键盘弹出或者隐藏的notification
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

// end of input group
/// @}

NS_CC_END

#endif    // __CC_IME_DELEGATE_H__
