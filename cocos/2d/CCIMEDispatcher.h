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

#include "2d/CCIMEDelegate.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

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
     @brief 返回系统共享的IMEDispatcher对象
     * @js NA
     * @lua NA
     */
    static IMEDispatcher* sharedDispatcher();

//     /**
//     @brief 从共享dispatcher释放所有IMEDelegate
//     */
//     static void purgeSharedDispatcher();

    /**
     @brief 分派从IME得到的输入文本
     * @js NA
     * @lua NA
     */
    void dispatchInsertText(const char * text, size_t len);

    /**
     @brief 分派对文本的删除回退操作
     * @js NA
     * @lua NA
     */
    void dispatchDeleteBackward();

    /**
     @brief 从IMEDelegate得到之前保存在IME的文本
     * @js NA
     * @lua NA
     */
    const std::string& getContentText();

    //////////////////////////////////////////////////////////////////////////
    // 分发键盘相关事件的notification
    //////////////////////////////////////////////////////////////////////////
    /**
     * @js NA
     * @lua NA
     */
    void dispatchKeyboardWillShow(IMEKeyboardNotificationInfo& info);
    /**
     * @js NA
     * @lua NA
     */
    void dispatchKeyboardDidShow(IMEKeyboardNotificationInfo& info);
    /**
     * @js NA
     * @lua NA
     */
    void dispatchKeyboardWillHide(IMEKeyboardNotificationInfo& info);
    /**
     * @js NA
     * @lua NA
     */
    void dispatchKeyboardDidHide(IMEKeyboardNotificationInfo& info);

protected:
    friend class IMEDelegate;

    /**
    @brief 添加delegate接收IME消息
    */
    void addDelegate(IMEDelegate * delegate);

    /**
    @brief 将pDelegate分配到IME
    @return 如果成功解除旧的delegate,返回true，否则返回false
             如果成功附加新的delegate，返回true,否则返回false
    */
    bool attachDelegateWithIME(IMEDelegate * delegate);
    bool detachDelegateWithIME(IMEDelegate * delegate);

    /**
    @brief 从delegate队列里移除某一从IME消息获取的delegate
    */
    void removeDelegate(IMEDelegate * delegate);

private:
    IMEDispatcher();
    
    class Impl;
    Impl * _impl;
};

// end of input group
/// @}

NS_CC_END

#endif    // __CC_IME_DISPATCHER_H__
