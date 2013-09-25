/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

NS_CC_BEGIN

enum TargetPlatform
{
    kTargetWindows,
    kTargetLinux,
    kTargetMacOS,
    kTargetAndroid,
    kTargetIphone,
    kTargetIpad,
    kTargetBlackBerry,
    kTargetNaCl,
    kTargetEmscripten,
    kTargetTizen,
    kTargetWinRT,
    kTargetWP8
};

/**
 * @addtogroup platform
 * @{
 * @js NA
 * @lua NA
 */

class CC_DLL CCApplicationProtocol
{
public:

    virtual ~CCApplicationProtocol() {}

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground() = 0;

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground() = 0;

    /**
    @brief    Callback by CCDirector for limit FPS.
    @interval       The time, expressed in seconds, between current frame and next. 
    */
    virtual void setAnimationInterval(double interval) = 0;

    /**
    @brief Get current language config
    @return Current language config
    */
    virtual ccLanguageType getCurrentLanguage() = 0;
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform() = 0;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
