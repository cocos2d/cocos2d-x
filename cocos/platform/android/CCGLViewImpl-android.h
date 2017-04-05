/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __CC_EGLVIEWIMPL_ANDROID_H__
#define __CC_EGLVIEWIMPL_ANDROID_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

class CC_DLL GLViewImpl : public GLView
{
public:

    // static function
    static GLViewImpl* create(const std::string &viewname);
    static GLViewImpl* createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor = 1.0f);
    static GLViewImpl* createWithFullScreen(const std::string& viewName);

    bool isOpenGLReady() override;
    void end() override;
    void swapBuffers() override;
    void setIMEKeyboardState(bool bOpen) override;

protected:
    GLViewImpl();
    virtual ~GLViewImpl();

    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);
};

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif    // end of __CC_EGLVIEWIMPL_ANDROID_H__

