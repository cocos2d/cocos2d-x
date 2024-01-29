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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

#include "platform/ios/CCEAGLView-ios.h"
#include "platform/ios/CCDirectorCaller-ios.h"
#include "platform/ios/CCGLViewImpl-ios.h"
#include "base/CCTouch.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

void* GLViewImpl::_pixelFormat = kEAGLColorFormatRGB565;
int GLViewImpl::_depthFormat = GL_DEPTH_COMPONENT16;
int GLViewImpl::_multisamplingCount = 0;

GLViewImpl* GLViewImpl::createWithEAGLView(void *eaglview)
{
    auto ret = new (std::nothrow) GLViewImpl;
    if(ret && ret->initWithEAGLView(eaglview)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new (std::nothrow) GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, const Rect& rect, float frameZoomFactor)
{
    auto ret = new (std::nothrow) GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
    auto ret = new (std::nothrow) GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void GLViewImpl::convertAttrs()
{
    if(_glContextAttrs.redBits==8 && _glContextAttrs.greenBits==8 && _glContextAttrs.blueBits==8 && _glContextAttrs.alphaBits==8)
    {
        _pixelFormat = kEAGLColorFormatRGBA8;
    } else if (_glContextAttrs.redBits==5 && _glContextAttrs.greenBits==6 && _glContextAttrs.blueBits==5 && _glContextAttrs.alphaBits==0)
    {
        _pixelFormat = kEAGLColorFormatRGB565;
    } else
    {
        CCASSERT(0, "Unsupported render buffer pixel format. Using default");
    }

    if(_glContextAttrs.depthBits==24 && _glContextAttrs.stencilBits==8)
    {
        _depthFormat = GL_DEPTH24_STENCIL8_OES;
    } else if (_glContextAttrs.depthBits==0 && _glContextAttrs.stencilBits==0)
    {
        _depthFormat = 0;
    } else
    {
        CCASSERT(0, "Unsupported format for depth and stencil buffers. Using default");
    }
    
    _multisamplingCount = _glContextAttrs.multisamplingCount;
}

GLViewImpl::GLViewImpl()
{
}

GLViewImpl::~GLViewImpl()
{
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

bool GLViewImpl::initWithEAGLView(void *eaglview)
{
    _eaglview = eaglview;
    CCEAGLView *glview = (CCEAGLView*) _eaglview;

    _screenSize.width = _designResolutionSize.width = [glview getWidth];
    _screenSize.height = _designResolutionSize.height = [glview getHeight];
//    _scaleX = _scaleY = [glview contentScaleFactor];

    return true;
}

bool GLViewImpl::initWithRect(const std::string& viewName, const Rect& rect, float frameZoomFactor)
{
    CGRect r = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    convertAttrs();
    CCEAGLView *eaglview = [CCEAGLView viewWithFrame: r
                                       pixelFormat: (NSString*)_pixelFormat
                                       depthFormat: _depthFormat
                                preserveBackbuffer: NO
                                        sharegroup: nil
                                     multiSampling: NO
                                   numberOfSamples: 0];

    // Not available on tvOS
#if !defined(CC_TARGET_OS_TVOS)
    [eaglview setMultipleTouchEnabled:YES];
#endif

    _screenSize.width = _designResolutionSize.width = [eaglview getWidth];
    _screenSize.height = _designResolutionSize.height = [eaglview getHeight];
//    _scaleX = _scaleY = [eaglview contentScaleFactor];

    _eaglview = eaglview;

    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    CGRect rect = [[UIScreen mainScreen] bounds];
    Rect r;
    r.origin.x = rect.origin.x;
    r.origin.y = rect.origin.y;
    r.size.width = rect.size.width;
    r.size.height = rect.size.height;

    return initWithRect(viewName, r, 1);
}

bool GLViewImpl::isOpenGLReady()
{
    return _eaglview != nullptr;
}

bool GLViewImpl::setContentScaleFactor(float contentScaleFactor)
{
    CC_ASSERT(_resolutionPolicy == ResolutionPolicy::UNKNOWN); // cannot enable retina mode
    _scaleX = _scaleY = contentScaleFactor;

    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    [eaglview setNeedsLayout];

    return true;
}

float GLViewImpl::getContentScaleFactor() const
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    float scaleFactor = [eaglview contentScaleFactor];

//    CCASSERT(scaleFactor == _scaleX == _scaleY, "Logic error in GLView::getContentScaleFactor");

    return scaleFactor;
}

void GLViewImpl::end()
{
    [CCDirectorCaller destroy];

    // destroy EAGLView
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    [eaglview removeFromSuperview];
    //[eaglview release];
    release();
}


void GLViewImpl::swapBuffers()
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    [eaglview swapBuffers];
}

void GLViewImpl::setIMEKeyboardState(bool open)
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    if (open)
    {
        [eaglview showKeyboard];
    }
    else
    {
        [eaglview hideKeyboard];
    }
}

Rect GLViewImpl::getSafeAreaRect() const
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 110000
    float version = [[UIDevice currentDevice].systemVersion floatValue];
    if (version >= 11.0f)
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpartial-availability"
        UIEdgeInsets safeAreaInsets = eaglview.safeAreaInsets;
#pragma clang diagnostic pop

        // Multiply contentScaleFactor since safeAreaInsets return points.
        safeAreaInsets.left *= eaglview.contentScaleFactor;
        safeAreaInsets.right *= eaglview.contentScaleFactor;
        safeAreaInsets.top *= eaglview.contentScaleFactor;
        safeAreaInsets.bottom *= eaglview.contentScaleFactor;

        // Get leftBottom and rightTop point in UI coordinates
        Vec2 leftBottom = Vec2(safeAreaInsets.left, _screenSize.height - safeAreaInsets.bottom);
        Vec2 rightTop = Vec2(_screenSize.width - safeAreaInsets.right, safeAreaInsets.top);

        // Convert a point from UI coordinates to which in design resolution coordinate.
        leftBottom.x = (leftBottom.x - _viewPortRect.origin.x) / _scaleX,
        leftBottom.y = (leftBottom.y - _viewPortRect.origin.y) / _scaleY;
        rightTop.x = (rightTop.x - _viewPortRect.origin.x) / _scaleX,
        rightTop.y = (rightTop.y - _viewPortRect.origin.y) / _scaleY;

        // Adjust points to make them inside design resolution
        leftBottom.x = MAX(leftBottom.x, 0);
        leftBottom.y = MIN(leftBottom.y, _designResolutionSize.height);
        rightTop.x = MIN(rightTop.x, _designResolutionSize.width);
        rightTop.y = MAX(rightTop.y, 0);

        // Convert to GL coordinates
        leftBottom = Director::getInstance()->convertToGL(leftBottom);
        rightTop = Director::getInstance()->convertToGL(rightTop);

        return Rect(leftBottom.x, leftBottom.y, rightTop.x - leftBottom.x, rightTop.y - leftBottom.y);
    }
#endif

    // If running on iOS devices lower than 11.0, return visiable rect instead.
    return GLView::getSafeAreaRect();
}

NS_CC_END

#endif // CC_PLATFORM_IOS
