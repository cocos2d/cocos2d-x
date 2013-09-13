/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#ifndef __CC_APPLICATION_TIZEN_H__
#define __CC_APPLICATION_TIZEN_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include "CCOspApplication.h"

NS_CC_BEGIN

class Rect;

class CC_DLL Application
    : public ApplicationProtocol
{
public:
    /**
     * @js ctor
     */
    Application();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Application();

    /**
    @brief    Callback by Director to limit FPS.
    @param interval The time, expressed in seconds, between current frame and next.
    */
    void setAnimationInterval(double interval);
    long getAnimationInterval();

    /**
    @brief    Run the message loop.
    */
    int run();

    /**
    @brief    Get current application instance.
    @return Current application instance pointer.
    */
    static Application* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();
    
    /**
    @brief Get current language config
    @return Current language config
    */
    virtual LanguageType getCurrentLanguage();
    
    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();

protected:
    static Application * sm_pSharedApplication;
    static long _animationInterval; // milliseconds
};

NS_CC_END

#endif    // __CC_APPLICATION_TIZEN_H__
