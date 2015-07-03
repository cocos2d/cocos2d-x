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

#include "platform/CCPlatformMacros.h"
#include "base/CCScriptSupport.h"
#include "base/CCAutoreleasePool.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL ApplicationProtocol
{
public:

    /** @~english Since WINDOWS and ANDROID are defined as macros, we could not just use these keywords in enumeration(Platform).
     *  Therefore, 'OS_' prefix is added to avoid conflicts with the definitions of system macros.
     * @~chinese 以前 WINDOWS和 ANDROID直接被定义成宏，但是我们不能调用 enumeration(Platform)函数。因为可能会与系统宏定义冲突。
     * 因此,添加“OS_”前缀到这些宏里面，可以避免与系统定义的宏冲突。
     */
    enum class Platform
    {
        OS_WINDOWS,/** Windows */
        OS_LINUX,/** Linux */
        OS_MAC,/** Mac*/
        OS_ANDROID,/** Android */
        OS_IPHONE,/** Iphone */
        OS_IPAD,/** Ipad */
        OS_BLACKBERRY,/** BLACKBERRY */
        OS_NACL,/** Nacl */
        OS_EMSCRIPTEN,/** Emscripten */
        OS_TIZEN,/** Tizen */
        OS_WINRT,/** Windows Store Applications */
        OS_WP8/** Windows Phone Applications */
    };

    /**
     * @js NA
     * @lua NA
     */
    virtual ~ApplicationProtocol(){
#if CC_ENABLE_SCRIPT_BINDING
        ScriptEngineManager::destroyInstance();
#endif
        /** @~english clean auto release pool.  @~chinese 清理自动释放池。*/
        PoolManager::destroyInstance();
    }

    /**
     * @brief    @~english Implement Director and Scene init code here.
     * @~chinese 在这里实现导演（Director）和场景（Scene）的初始化代码
     * @return @~english true    Initialize success, app continue.
     * @~chinese 如果初始化成功,则程序继续。
     * @return @~english false   Initialize failed, app terminate.
     * @~chinese 如果初始化失败,则程序终止。
     * @js NA
     * @lua NA
     */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
     * @brief  @~english This function will be called when the application enters background.
     * @~chinese 这个函数将在应用程序进入后台时被调用。
     * @js NA
     * @lua NA
     */
    virtual void applicationDidEnterBackground() = 0;

    /**
     * @brief  @~english This function will be called when the application enters foreground.
     * @~chinese 这个函数将在应用程序进入前台时被调用。
     * @js NA
     * @lua NA
     */
    virtual void applicationWillEnterForeground() = 0;

    /**
     * @brief    @~english Callback by Director for limit FPS.
     * @~chinese 设置FPS的时间间隔，由 Director对象调用。
     * @param interval @~english The time, expressed in seconds, between current frame and next.
     * @~chinese 时间,以秒为单位,表示在当前帧和下一帧之间的时间间隔。
     * @js NA
     * @lua NA
     */
    virtual void setAnimationInterval(double interval) = 0;

    /** @~english Subclass override the function to set OpenGL context attribution instead of use default value.
     * And now can only set six attributions:redBits,greenBits,blueBits,alphaBits,depthBits,stencilBits.
     * Default value are(5,6,5,0,16,0), usually use as follows:
     * @code
     * void AppDelegate::initGLContextAttrs(){
     *     GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
     *     GLView::setGLContextAttrs(glContextAttrs);
     * }
     * @endcond
     * @~chinese 子类需要重载此函数来设置OpenGL上下文属性,而不能使用默认值。
     * 现在只能设置六个属性值,它们分别是:redBits greenBits,blueBits,alphaBits,depthBits stencilBits。
     * 默认值是(5,6,5,0,16,0 ), 一般使用方法如下:
     * @code
     * AppDelegate:initGLContextAttrs(){
     * GLContextAttrs GLContextAttrs = { 8、8、8、8、24日8 };
     * GLView:setGLContextAttrs(glContextAttrs);
     * }
     * @endcode
     */
    virtual void initGLContextAttrs() {}

    /**
     *  @brief @~english Get current language config.
     * @~chinese 获取当前的语言配置。
     *  @return @~english Current language config.
     * @~chinese 当前的语言配置。
     * @js NA
     * @lua NA
     */
    virtual LanguageType getCurrentLanguage() = 0;
    
    /**
     * @brief @~english Get current language iso 639-1 code.
     * @~chinese 获取当前语言的iso 639-1编码。
     * @return @~english Current language iso 639-1 code.
     * @~chinese 当前语言的iso 639-1编码
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode() = 0;
    
    /**
     * @brief @~english Get target platform.
     * @~chinese 获取目标平台类型
     * @js NA
     * @lua NA
     */
    virtual Platform getTargetPlatform() = 0;
    
    /**
     *@brief @~english Open url in default browser.
     * @~chinese 在默认浏览器打开网址。
     *@param String @~english with url to open.
     * @~chinese 要打开的网站URL
     @return @~english True if the resource located by the URL was successfully opened; otherwise false.
     * @~chinese 如果URL被成功打开,则返回True,,否则返回False
     * @js NA
     * @lua NA
     */
    virtual bool openURL(const std::string &url) = 0;
};

// end of platform group
/** @} */

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
