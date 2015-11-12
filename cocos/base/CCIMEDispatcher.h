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
 * @brief @~english Input Method Edit Message Dispatcher.
 * @~chinese 输入法编辑消息调度器。
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
     * @brief @~english Returns the shared IMEDispatcher object for the system.
     * @~chinese 返回系统共享的IMEDispatcher对象。
     * @js NA
     * @lua NA
     */
    static IMEDispatcher* sharedDispatcher();

    /**
     * @brief @~english Dispatches the input text from IME.
     * @~chinese 分派输入文本。
     * @lua NA
     */
    void dispatchInsertText(const char * text, size_t len);

    /**
     * @brief @~english Dispatches the delete-backward operation.
     * @~chinese 分派删除回退操作。
     * @lua NA
     */
    void dispatchDeleteBackward();

    /**
     * @brief @~english Get the content text from IMEDelegate, retrieved previously from IME.
     * @~chinese 从IMEDelegate获得文本的内容。
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
     * @brief @~english Add delegate to receive IME messages.
     * @~chinese 添加代理去接收IME消息。
     * @param delegate @~english A instance implements IMEDelegate delegate.
     * @~chinese 一个IME代理实例。
     */
    void addDelegate(IMEDelegate * delegate);

    /**
     * @brief @~english Attach the Delegate to the IME.
     * @~chinese 挂载IME的代理。
     * @param delegate @~english A instance implements IMEDelegate delegate.
     * @~chinese 一个IMEDelegate代理实例。
     * @return @~english If the old delegate can detach from the IME, and the new delegate can attach to the IME, return true, otherwise false.
     * @~chinese 如果旧的代理可以从IME分离并且新代理可以连接到输入法,则返回true,否则为false。
     */
    bool attachDelegateWithIME(IMEDelegate * delegate);

    /**
     * @~english Detach the delegate to the IME
     * @~chinese 分离IME的代理
     * @see `attachDelegateWithIME(IMEDelegate*)`
     * @param delegate  @~english A instance implements IMEDelegate delegate.
     * @~chinese 一个IMEDelegate代理实例。
     * @return @~english Whether the IME is detached or not.
     * @~chinese 输入法是否分离。
     */
    bool detachDelegateWithIME(IMEDelegate * delegate);

    /**
     * @brief @~english Remove the delegate from the delegates which receive IME messages.
     * @~chinese 从正在接受消息的代理列表删除代理。
     * @param delegate @~english A instance implements the IMEDelegate delegate.
     * @~chinese 一个IMEDelegate代理实例。
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
