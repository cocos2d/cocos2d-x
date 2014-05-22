/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CC_APPLICATION_PROTOCOL_H__
#define __CC_APPLICATION_PROTOCOL_H__

#include "base/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL ApplicationProtocol
{
public:

    //因为在windows和Android平台上被定义为宏，我们不能只是使用枚举里面的这些关键字，
    //因此，添加‘OS_’前缀来避免和系统定义的宏发生冲突
    enum class Platform
    {
        OS_WINDOWS,
        OS_LINUX,
        OS_MAC,
        OS_ANDROID,
        OS_IPHONE,
        OS_IPAD,
        OS_BLACKBERRY,
        OS_NACL,
        OS_EMSCRIPTEN,
        OS_TIZEN,
        OS_WINRT,
        OS_WP8
    };

    /**
     * @js NA
     * @lua NA
     */
    virtual ~ApplicationProtocol() {}

    /**
    @brief    在这里实现Director和Scene的初始化。
    @return true    初始化成功，应用程序继续。
    @return false   初始化失败，应用程序终止。
    * @js NA
    * @lua NA
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  这个函数在应用程序进入后台的时候被调用
    * @js NA
    * @lua NA
    */
    virtual void applicationDidEnterBackground() = 0;

    /**
    @brief  这个函数在应用程序进入前台的时候被调用
    * @js NA
    * @lua NA
    */
    virtual void applicationWillEnterForeground() = 0;

    /**
    @brief    被Director调用来限制FPS.
    @param interval 当前帧和下一帧的时间间隔，以秒为单位。
    * @js NA
    * @lua NA
    */
    virtual void setAnimationInterval(double interval) = 0;

    /**
    @brief 获取当前语言配置
    @return 返回当前语言配置
    * @js NA
    * @lua NA
    */
    virtual LanguageType getCurrentLanguage() = 0;
    
    /**
     @brief 获取当前语言的iso 639-1代码
     @return 返回当前语言的iso 639-1代码
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode() = 0;
    
    /**
     @brief 获取目标平台
     * @js NA
     * @lua NA
     */
    virtual Platform getTargetPlatform() = 0;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
