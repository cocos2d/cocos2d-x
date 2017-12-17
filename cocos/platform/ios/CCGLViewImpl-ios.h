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

#ifndef __CC_EGLVIEWIMPL_IPHONE_H__
#define __CC_EGLVIEWIMPL_IPHONE_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "base/CCRef.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN


/** Class that represent the OpenGL View
 */
class CC_DLL GLViewImpl : public GLView
{
public:
    /** creates a GLViewImpl with a objective-c CCEAGLViewImpl instance */
    static GLViewImpl* createWithEAGLView(void* eaGLView);

    /** creates a GLViewImpl with a title name in fullscreen mode */
    static GLViewImpl* create(const std::string& viewName);

    /** creates a GLViewImpl with a title name, a rect and the zoom factor */
    static GLViewImpl* createWithRect(const std::string& viewName, const Rect& rect, float frameZoomFactor = 1.0f);

    /** creates a GLViewImpl with a name in fullscreen mode */
    static GLViewImpl* createWithFullScreen(const std::string& viewName);
    
    static void convertAttrs();
    static void* _pixelFormat;
    static int _depthFormat;

    /** sets the content scale factor */
    virtual bool setContentScaleFactor(float contentScaleFactor) override;

    /** returns the content scale factor */
    virtual float getContentScaleFactor() const override;

    /** returns whether or not the view is in Retina Display mode */
    virtual bool isRetinaDisplay() const override { return getContentScaleFactor() == 2.0; }

    /** returns the objective-c CCEAGLView instance */
    virtual void* getEAGLView() const override { return _eaglview; }

    // overrides
    virtual bool isOpenGLReady() override;
    virtual void end() override;
    virtual void swapBuffers() override;
    virtual void setIMEKeyboardState(bool bOpen) override;

    virtual Rect getSafeAreaRect() const override;

protected:
    GLViewImpl();
    virtual ~GLViewImpl();

    bool initWithEAGLView(void* eaGLView);
    bool initWithRect(const std::string& viewName, const Rect& rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);

    // the objective-c CCEAGLView instance
    void *_eaglview;
};

NS_CC_END

#endif // CC_PLATFORM_IOS

#endif    // end of __CC_EGLViewImpl_IPHONE_H__
