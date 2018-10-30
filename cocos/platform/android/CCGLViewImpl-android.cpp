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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/CCGLViewImpl-android.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "platform/android/jni/JniHelper.h"
#include "CCGL.h"

#include <stdlib.h>
#include <android/log.h>

// <EGL/egl.h> exists since android 2.3
#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

#define DEFAULT_MARGIN_ANDROID				30.0f
#define WIDE_SCREEN_ASPECT_RATIO_ANDROID	2.0f

void initExtensions() {
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
}

NS_CC_BEGIN

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
    auto ret = new GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl::GLViewImpl()
{
    initExtensions();
}

GLViewImpl::~GLViewImpl()
{

}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    return true;
}


bool GLViewImpl::isOpenGLReady()
{
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLViewImpl::end()
{
    JniHelper::callStaticVoidMethod("org.cocos2dx.lib.Cocos2dxHelper", "terminateProcess");
}

void GLViewImpl::swapBuffers()
{
}

void GLViewImpl::setIMEKeyboardState(bool bOpen)
{
    if (bOpen) {
        JniHelper::callStaticVoidMethod("org.cocos2dx.lib.Cocos2dxGLSurfaceView", "openIMEKeyboard");
    } else {
        JniHelper::callStaticVoidMethod("org.cocos2dx.lib.Cocos2dxGLSurfaceView", "closeIMEKeyboard");
    }
}

Rect GLViewImpl::getSafeAreaRect() const {
    Rect safeAreaRect = GLView::getSafeAreaRect();
    float deviceAspectRatio = 0;
    if(safeAreaRect.size.height > safeAreaRect.size.width) {
        deviceAspectRatio = safeAreaRect.size.height / safeAreaRect.size.width;
    } else {
        deviceAspectRatio = safeAreaRect.size.width / safeAreaRect.size.height;
    }

    float marginX = DEFAULT_MARGIN_ANDROID / _scaleX;
    float marginY = DEFAULT_MARGIN_ANDROID / _scaleY;

    bool isScreenRound = JniHelper::callStaticBooleanMethod("org/cocos2dx/lib/Cocos2dxHelper", "isScreenRound");
    bool hasSoftKeys = JniHelper::callStaticBooleanMethod("org/cocos2dx/lib/Cocos2dxHelper", "hasSoftKeys");
    if(isScreenRound) {
        // edge screen (ex. Samsung Galaxy s7, s9, s9+, Note 9, Nokia 8 Sirocco, Sony Xperia XZ3, Oppo Find X...)
        if(safeAreaRect.size.width < safeAreaRect.size.height) {
            safeAreaRect.origin.y += marginY * 2.f;
            safeAreaRect.size.height -= (marginY * 2.f);

            safeAreaRect.origin.x += marginX;
            safeAreaRect.size.width -= (marginX * 2.f);
        } else {
            safeAreaRect.origin.y += marginY;
            safeAreaRect.size.height -= (marginY * 2.f);

            // landscape: no changes with X-coords
        }
    } else if (deviceAspectRatio >= WIDE_SCREEN_ASPECT_RATIO_ANDROID) {
        // almost all devices on the market have round corners if
        // deviceAspectRatio more than 2 (@see "android.max_aspect" parameter in AndroidManifest.xml)
        float bottomMarginIfPortrait = 0;
        if(hasSoftKeys) {
            bottomMarginIfPortrait = marginY * 2.f;
        }

        if(safeAreaRect.size.width < safeAreaRect.size.height) {
            // portrait: double margin space if device has soft menu
            safeAreaRect.origin.y += bottomMarginIfPortrait;
            safeAreaRect.size.height -= (bottomMarginIfPortrait + marginY);
        } else {
            // landscape: ignore double margin at the bottom in any cases
            // prepare signle margin for round corners
            safeAreaRect.origin.y += marginY;
            safeAreaRect.size.height -= (marginY * 2.f);
        }
    } else {
        if(hasSoftKeys && (safeAreaRect.size.width < safeAreaRect.size.height)) {
            // portrait: preserve only for soft system menu
            safeAreaRect.origin.y += marginY * 2.f;
            safeAreaRect.size.height -= (marginY * 2.f);
        }
    }

    return safeAreaRect;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
