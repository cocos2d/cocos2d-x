/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "base/CCAutoreleasePool.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL ApplicationProtocol
{
public:

    /** Since WINDOWS and ANDROID are defined as macros, we could not just use these keywords in enumeration(Platform).
     *  Therefore, 'OS_' prefix is added to avoid conflicts with the definitions of system macros.
     */
    enum class Platform
    {
        OS_WINDOWS,     /**< Windows */
        OS_LINUX,       /**< Linux */
        OS_MAC,         /**< Mac OS X*/
        OS_ANDROID,     /**< Android */
        OS_IPHONE,      /**< iPhone */
        OS_IPAD,        /**< iPad */
        OS_BLACKBERRY,  /**< BlackBerry */
        OS_NACL,        /**< Native Client in Chrome */
        OS_EMSCRIPTEN,  /**< Emscripten */
        OS_TIZEN,       /**< Tizen */
        OS_WINRT,       /**< Windows Runtime Applications */
        OS_WP8          /**< Windows Phone 8 Applications */
    };

    /**
     * @js NA
     * @lua NA
     */
    virtual ~ApplicationProtocol(){
        /** clean auto release pool. */
        PoolManager::destroyInstance();
    }

    /**
    * @brief    Implement Director and Scene init code here.
    * @return true    Initialize success, app continue.
    * @return false   Initialize failed, app terminate.
    * @js NA
    * @lua NA
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    * @brief  This function will be called when the application enters background.
    * @js NA
    * @lua NA
    */
    virtual void applicationDidEnterBackground() = 0;

    /**
    * @brief  This function will be called when the application enters foreground.
    * @js NA
    * @lua NA
    */
    virtual void applicationWillEnterForeground() = 0;

    /**
    * @brief    Callback by Director for limit FPS.
    * @param interval The time, expressed in seconds, between current frame and next.
    * @js NA
    * @lua NA
    */
    virtual void setAnimationInterval(float interval) = 0;

    /** Subclass override the function to set OpenGL context attribution instead of use default value.
    * And now can only set six attributions:redBits,greenBits,blueBits,alphaBits,depthBits,stencilBits.
    * Default value are(5,6,5,0,16,0), usually use as follows:
    * void AppDelegate::initGLContextAttrs(){
    *     GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    *     GLView::setGLContextAttrs(glContextAttrs);
    * }
    */
    virtual void initGLContextAttrs() {}

    /**
    @brief Get current language config.
    @return Current language config.
    * @js NA
    * @lua NA
    */
    virtual LanguageType getCurrentLanguage() = 0;
    
    /**
     @brief Get current language iso 639-1 code.
     @return Current language iso 639-1 code.
     * @js NA
     * @lua NA
     */
    virtual const char * getCurrentLanguageCode() = 0;
    
    /**
     @brief Get target platform.
     * @js NA
     * @lua NA
     */
    virtual Platform getTargetPlatform() = 0;
    
    /**
     @brief Get application version.
     * @js NA
     * @lua NA
     */
    virtual std::string getVersion() = 0;
    
    /**
     @brief Open url in default browser.
     @param String with url to open.
     @return True if the resource located by the URL was successfully opened; otherwise false.
     * @js NA
     * @lua NA
     */
    virtual bool openURL(const std::string &url) = 0;
};

// end of platform group
/** @} */

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
