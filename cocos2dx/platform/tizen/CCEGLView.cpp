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

#include "CCEGLView.h"
#include "CCApplication.h"
#include "CCGL.h"
#include "CCDirector.h"
#include "CCOspApplication.h"
#include "CCOspForm.h"

NS_CC_BEGIN
using namespace Tizen::App;
using namespace Tizen::Base::Runtime;

EGLView::EGLView()
    : __eglDisplay(EGL_DEFAULT_DISPLAY)
    , __eglSurface(EGL_NO_SURFACE)
    , __eglConfig(null)
    , __eglContext(EGL_NO_DISPLAY)
    , __pTimer(null)
{

}

EGLView::~EGLView()
{

}

bool EGLView::isOpenGLReady()
{
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

Tizen::Base::Runtime::Timer*
EGLView::getTimer()
{
    return __pTimer;
}

void
EGLView::cleanup()
{
    if (__pTimer != null)
    {
        __pTimer->Cancel();
        delete __pTimer;
        __pTimer = null;
    }

    destroyGL();
}

void EGLView::end()
{
    cleanup();

    UiApp* pApp = UiApp::GetInstance();
    AppAssert(pApp);
    pApp->Terminate();
}

void EGLView::swapBuffers()
{
    eglSwapBuffers(__eglDisplay, __eglSurface);
}

void EGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        ((OspForm *)OspApplication::GetInstance()->getOspForm())->ShowKeypad();
    }
    else
    {
        ((OspForm *)OspApplication::GetInstance()->getOspForm())->CloseKeypad();
    }
}

EGLView* EGLView::getInstance()
{
    static EGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new EGLView();
        if(!s_pEglView->create())
        {
            delete s_pEglView;
            s_pEglView = NULL;
        }
    }

    return s_pEglView;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

void
EGLView::OnTimerExpired(Tizen::Base::Runtime::Timer& timer)
{
    if (__pTimer == null)
    {
        return;
    }
    __pTimer->Start(Application::getInstance()->getAnimationInterval());

    Director::getInstance()->mainLoop();
}

bool
EGLView::create()
{
    result r = E_SUCCESS;

    TryCatch(initEGL(), , "[EGLView] EGLView::create() failed.");

    __pTimer = new (std::nothrow) Tizen::Base::Runtime::Timer;
    TryCatch(__pTimer != null, , "[EGLView] Failed to allocate memory.");

    r = __pTimer->Construct(*this);
    TryCatch(!IsFailed(r), , "[EGLView] __pTimer->Construct(*this) failed.");

    return true;

CATCH:
    return false;
}

bool
EGLView::initEGL()
{
    EGLint numConfigs = 1;

    EGLint eglConfigList[] =
    {
        EGL_RED_SIZE,        5,
        EGL_GREEN_SIZE,      6,
        EGL_BLUE_SIZE,       5,
        EGL_ALPHA_SIZE,      0,
        EGL_DEPTH_SIZE,      8,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint eglContextList[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    eglBindAPI(EGL_OPENGL_ES_API);

    if (__eglDisplay)
    {
        destroyGL();
    }

    __eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
    TryCatch(__eglDisplay != EGL_NO_DISPLAY, , "[EGLView] eglGetDisplay() failed.");

    TryCatch(!(eglInitialize(__eglDisplay, null, null) == EGL_FALSE || eglGetError() != EGL_SUCCESS), , "[EGLView] eglInitialize() failed.");

    TryCatch(!(eglChooseConfig(__eglDisplay, eglConfigList, &__eglConfig, 1, &numConfigs) == EGL_FALSE ||
        eglGetError() != EGL_SUCCESS), , "[EGLView] eglChooseConfig() failed.");

    TryCatch(numConfigs, , "[EGLView] eglChooseConfig() failed. because of matching config doesn't exist");

    __eglSurface = eglCreateWindowSurface(__eglDisplay, __eglConfig, (EGLNativeWindowType)OspApplication::GetInstance()->getOspForm(), null);
    TryCatch(!(__eglSurface == EGL_NO_SURFACE || eglGetError() != EGL_SUCCESS), , "[EGLView] eglCreateWindowSurface() failed.");

    __eglContext = eglCreateContext(__eglDisplay, __eglConfig, EGL_NO_CONTEXT, eglContextList);
    TryCatch(!(__eglContext == EGL_NO_CONTEXT || eglGetError() != EGL_SUCCESS), , "[EGLView] eglCreateContext() failed.");

    TryCatch(!(eglMakeCurrent(__eglDisplay, __eglSurface, __eglSurface, __eglContext) == EGL_FALSE ||
        eglGetError() != EGL_SUCCESS), , "[EGLView] eglMakeCurrent() failed.");

    return true;

CATCH:
    {
        AppLog("[EGLView] EGLView can run on systems which supports OpenGL ES(R) 2.0.");
        AppLog("[EGLView] When EGLView does not correctly execute, there are a few reasons.");
        AppLog("[EGLView]    1. The current device(real-target or emulator) does not support OpenGL ES(R) 2.0.\n"
               " Check the Release Notes.");
        AppLog("[EGLView]    2. The system running on emulator cannot support OpenGL(R) 2.1 or later.\n"
               " Try with other system.");
        AppLog("[EGLView]    3. The system running on emulator does not maintain the latest graphics driver.\n"
               " Update the graphics driver.");
    }

    destroyGL();

    return false;
}

void
EGLView::destroyGL(void)
{
    if (__eglDisplay)
    {
        eglMakeCurrent(__eglDisplay, null, null, null);

        if (__eglContext)
        {
            eglDestroyContext(__eglDisplay, __eglContext);
            __eglContext = EGL_NO_CONTEXT;
        }

        if (__eglSurface)
        {
            eglDestroySurface(__eglDisplay, __eglSurface);
            __eglSurface = EGL_NO_SURFACE;
        }

        eglTerminate(__eglDisplay);
        __eglDisplay = EGL_NO_DISPLAY;
    }

    return;
}

NS_CC_END

