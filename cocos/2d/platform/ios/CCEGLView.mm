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

#include "CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "CCEAGLView.h"
#include "CCDirectorCaller.h"
#include "CCEGLView.h"
#include "CCSet.h"
#include "CCTouch.h"

NS_CC_BEGIN

EGLView* EGLView::create(const std::string& viewName)
{
    auto ret = new EGLView;
    if(ret && ret->initWithSize(viewName, Size(0,0), 1)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

EGLView* EGLView::createWithSize(const std::string& viewName, Size size, float frameZoomFactor)
{
    auto ret = new EGLView;
    if(ret && ret->initWithSize(viewName, size, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

EGLView* EGLView::createWithFullScreen(const std::string& viewName)
{
    auto ret = new EGLView();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

EGLView::EGLView()
{
//    CGRect r = CGRectMake(0,0,300,300);
//    CCEAGLView *glView = [CCEAGLView viewWithFrame:r
//                                         pixelFormat: kEAGLColorFormatRGB565
//                                         depthFormat: GL_DEPTH24_STENCIL8_OES
//                                  preserveBackbuffer: NO
//                                          sharegroup: nil
//                                       multiSampling: NO
//                                     numberOfSamples: 0];
//    [__glView setMultipleTouchEnabled:YES];
//
//    _screenSize.width = _designResolutionSize.width = [glview getWidth];
//    _screenSize.height = _designResolutionSize.height = [glview getHeight];
//
//    _glview = glview;
}

EGLView::~EGLView()
{
    CCEAGLView *glview = (CCEAGLView*) _glview;
    [glview release];
}

bool EGLView::initWithSize(const std::string& viewName, Size size, float frameZoomFactor)
{
    return true;
}

bool EGLView::initWithFullScreen(const std::string& viewName)
{
    return true;
}

bool EGLView::isOpenGLReady()
{
    return _glview != nullptr;
}

bool EGLView::setContentScaleFactor(float contentScaleFactor)
{
    CC_ASSERT(_resolutionPolicy == ResolutionPolicy::UNKNOWN); // cannot enable retina mode
    _scaleX = _scaleY = contentScaleFactor;

    CCEAGLView *glview = (CCEAGLView*) _glview;
    [glview setNeedsLayout];

    return true;
}

void EGLView::end()
{
    [CCDirectorCaller destroy];
    
    // destroy EAGLView
    CCEAGLView *glview = (CCEAGLView*) _glview;

    [glview removeFromSuperview];
    [glview release];
}


void EGLView::swapBuffers()
{
    CCEAGLView *glview = (CCEAGLView*) _glview;
    [glview swapBuffers];
}

void EGLView::setIMEKeyboardState(bool open)
{
    CCEAGLView *glview = (CCEAGLView*) _glview;

    if (open)
    {
        [glview becomeFirstResponder];
    }
    else
    {
        [glview resignFirstResponder];
    }
}

NS_CC_END

#endif // CC_PLATFOR_IOS

