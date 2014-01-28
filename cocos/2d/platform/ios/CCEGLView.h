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

#ifndef __CC_EGLVIEW_IPHONE_H__
#define __CC_EGLVIEW_IPHONE_H__

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "CCObject.h"
#include "platform/CCCommon.h"
#include "platform/CCEGLViewProtocol.h"

NS_CC_BEGIN



class CC_DLL EGLView : public Object, public EGLViewProtocol
{
public:
    static EGLView* createWithEAGLView(void* eaglview);
    static EGLView* create(const std::string& viewName);
    static EGLView* createWithSize(const std::string& viewName, Size size, float frameZoomFactor = 1.0f);
    static EGLView* createWithFullScreen(const std::string& viewName);

    virtual bool setContentScaleFactor(float contentScaleFactor);

    // overrides
    virtual bool isOpenGLReady() override;
    virtual void end() override;
    virtual void swapBuffers() override;
    virtual void setIMEKeyboardState(bool bOpen) override;

protected:
    EGLView();
    virtual ~EGLView();

    bool initWithSize(const std::string& viewName, Size size, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);

    void *_glview;
};

NS_CC_END

#endif // CC_PLATFORM_IOS

#endif    // end of __CC_EGLVIEW_IPHONE_H__
