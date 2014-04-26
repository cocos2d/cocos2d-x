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

#include "base/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

#include "CCEAGLView.h"
#include "CCDirectorCaller.h"
#include "CCGLView.h"
#include "CCSet.h"
#include "2d/CCTouch.h"

NS_CC_BEGIN

GLView* GLView::createWithEAGLView(void *eaglview)
{
    auto ret = new GLView;
    if(ret && ret->initWithEAGLView(eaglview)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLView* GLView::create(const std::string& viewName)
{
    auto ret = new GLView;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLView* GLView::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new GLView;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLView* GLView::createWithFullScreen(const std::string& viewName)
{
    auto ret = new GLView();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLView::GLView()
{
}

GLView::~GLView()
{
    CCEAGLView *glview = (CCEAGLView*) _eaglview;
    [glview release];
}

bool GLView::initWithEAGLView(void *eaglview)
{
    _eaglview = eaglview;
    CCEAGLView *glview = (CCEAGLView*) _eaglview;

    _screenSize.width = _designResolutionSize.width = [glview getWidth];
    _screenSize.height = _designResolutionSize.height = [glview getHeight];
//    _scaleX = _scaleY = [glview contentScaleFactor];

    return true;
}

bool GLView::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    CGRect r = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    CCEAGLView *eaglview = [CCEAGLView viewWithFrame: r
                                       pixelFormat: kEAGLColorFormatRGB565
                                       depthFormat: GL_DEPTH24_STENCIL8_OES
                                preserveBackbuffer: NO
                                        sharegroup: nil
                                     multiSampling: NO
                                   numberOfSamples: 0];
    [eaglview setMultipleTouchEnabled:YES];

    _screenSize.width = _designResolutionSize.width = [eaglview getWidth];
    _screenSize.height = _designResolutionSize.height = [eaglview getHeight];
//    _scaleX = _scaleY = [eaglview contentScaleFactor];

    _eaglview = eaglview;

    return true;
}

bool GLView::initWithFullScreen(const std::string& viewName)
{
    CGRect rect = [[UIScreen mainScreen] bounds];
    Rect r;
    r.origin.x = rect.origin.x;
    r.origin.y = rect.origin.y;
    r.size.width = rect.size.width;
    r.size.height = rect.size.height;

    return initWithRect(viewName, r, 1);
}

bool GLView::isOpenGLReady()
{
    return _eaglview != nullptr;
}

bool GLView::setContentScaleFactor(float contentScaleFactor)
{
    CC_ASSERT(_resolutionPolicy == ResolutionPolicy::UNKNOWN); // cannot enable retina mode
    _scaleX = _scaleY = contentScaleFactor;

    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    [eaglview setNeedsLayout];

    return true;
}

float GLView::getContentScaleFactor() const
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    float scaleFactor = [eaglview contentScaleFactor];

//    CCASSERT(scaleFactor == _scaleX == _scaleY, "Logic error in GLView::getContentScaleFactor");

    return scaleFactor;
}

void GLView::end()
{
    [CCDirectorCaller destroy];
    
    // destroy EAGLView
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    [eaglview removeFromSuperview];
    [eaglview release];
}


void GLView::swapBuffers()
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    [eaglview swapBuffers];
}

void GLView::setIMEKeyboardState(bool open)
{
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;

    if (open)
    {
        [eaglview becomeFirstResponder];
    }
    else
    {
        [eaglview resignFirstResponder];
    }
}

NS_CC_END

#endif // CC_PLATFOR_IOS

