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

#ifndef __CC_EGLVIEW_TIZEN_H__
#define __CC_EGLVIEW_TIZEN_H__

#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include <FBase.h>

NS_CC_BEGIN

class CC_DLL CCEGLView
    : public CCEGLViewProtocol
    , public Tizen::Base::Runtime::ITimerEventListener
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    bool    isOpenGLReady();
    Tizen::Base::Runtime::Timer*    getTimer();
    void    cleanup();

    // keep compatible
    void    end();
    void    swapBuffers();
    void    setIMEKeyboardState(bool bOpen);

    // static function
    /**
    @brief    get the shared main open gl window
    */
    static CCEGLView* sharedOpenGLView();

    // Tizen timer callback
    virtual void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

private:
    bool create();
    bool initEGL();
    void destroyGL();

    Tizen::Graphics::Opengl::EGLDisplay __eglDisplay;
    Tizen::Graphics::Opengl::EGLSurface __eglSurface;
    Tizen::Graphics::Opengl::EGLConfig  __eglConfig;
    Tizen::Graphics::Opengl::EGLContext __eglContext;

    Tizen::Base::Runtime::Timer*        __pTimer;
};

NS_CC_END

#endif    // end of __CC_EGLVIEW_TIZEN_H__
