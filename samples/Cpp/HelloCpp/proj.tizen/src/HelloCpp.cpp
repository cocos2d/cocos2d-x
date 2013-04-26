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

#include <FIo.h>
#include <math.h>
#include "HelloCpp.h"
#include "Form1.h"

#include "../../Classes/AppDelegate.h"
#include "cocos2d.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Utility;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Graphics::Opengl;

Tizen::Graphics::Opengl::EGLDisplay g_eglDisplay;
Tizen::Graphics::Opengl::EGLSurface g_eglSurface;

const int TIME_OUT = 10;

HelloCpp::HelloCpp(void)
    : __pForm(null)
    , __eglDisplay(EGL_DEFAULT_DISPLAY)
    , __eglSurface(EGL_NO_SURFACE)
    , __eglConfig(null)
    , __eglContext(EGL_NO_DISPLAY)
    , __pTimer(null)
{
}

HelloCpp::~HelloCpp(void)
{
}

void
HelloCpp::Cleanup(void)
{
    if (__pTimer != null)
    {
        __pTimer->Cancel();
        delete __pTimer;
        __pTimer = null;
    }

    DestroyGL();
}

Application*
HelloCpp::CreateInstance(void)
{
    // Create the instance through the constructor.
    return new (std::nothrow) HelloCpp();
}

bool
HelloCpp::OnAppInitializing(AppRegistry& appRegistry)
{
    CCLOG("OnAppInitializing");

    result r = E_SUCCESS;

    Frame* pAppFrame = new (std::nothrow) Frame();
    TryReturn(pAppFrame != null, E_FAILURE, "[HelloCpp] Generating a frame failed.");

    r = pAppFrame->Construct();
    TryReturn(!IsFailed(r), E_FAILURE, "[HelloCpp] pAppFrame->Construct() failed.");

    this->AddFrame(*pAppFrame);

    __pForm = new (std::nothrow) Form1(this);
    TryCatch(__pForm != null, , "[HelloCpp] Allocation of Form1 failed.");

    r = __pForm->Construct(FORM_STYLE_NORMAL);
    TryCatch(!IsFailed(r), , "[HelloCpp] __pForm->Construct(FORM_STYLE_NORMAL) failed.");

    r = GetAppFrame()->GetFrame()->AddControl(*__pForm);
    TryCatch(!IsFailed(r), , "[HelloCpp] GetAppFrame()->GetFrame()->AddControl(*__pForm) failed.");

    TryCatch(InitEGL(), , "[HelloCpp] GlesCube::InitEGL() failed.");

    __pTimer = new (std::nothrow) Timer;
    TryCatch(__pTimer != null, , "[HelloCpp] Failed to allocate memory.");

    r = __pTimer->Construct(*this);
    TryCatch(!IsFailed(r), , "[HelloCpp] __pTimer->Construct(*this) failed.");

    return true;

CATCH:
    delete __pForm;
    __pForm = null;

    AppLog("[HelloCpp] HelloCpp::OnAppInitializing eglError : %#x\n"
           "[HelloCpp] HelloCpp::OnAppInitializing glError : %#x\n"
           "[HelloCpp] HelloCpp::OnAppInitializing VENDOR : %s\n"
           "[HelloCpp] HelloCpp::OnAppInitializing GL_RENDERER : %s\n"
           "[HelloCpp] HelloCpp::OnAppInitializing GL_VERSION : %s\n ",
           static_cast<unsigned int>(eglGetError()),
           static_cast<unsigned int>(glGetError()),
           glGetString(GL_VENDOR),
           glGetString(GL_RENDERER),
           glGetString(GL_VERSION));

    Cleanup();

    return false;
}

bool
HelloCpp::OnAppInitialized(void)
{
    AppDelegate app;

    cocos2d::CCEGLView* eglView = cocos2d::CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(720, 1280);

    cocos2d::CCApplication::sharedApplication()->run();

    return true;
}

bool
HelloCpp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
    Cleanup();

    return true;
}

void
HelloCpp::OnForeground(void)
{
    if (__pTimer != null)
    {
        __pTimer->Start(TIME_OUT);
    }
}

void
HelloCpp::OnBackground(void)
{
    if (__pTimer != null)
    {
        __pTimer->Cancel();
    }
}

void
HelloCpp::OnLowMemory(void)
{
}

void
HelloCpp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}

void
HelloCpp::OnScreenOn(void)
{
}

void
HelloCpp::OnScreenOff(void)
{
}

void
HelloCpp::OnTimerExpired(Timer& timer)
{
    if (__pTimer == null)
    {
        return;
    }
    __pTimer->Start(TIME_OUT);

    IncTimeStamp();

    if (!Draw())
    {
        AppLog("[HelloCpp] HelloCpp:Draw() failed.");
    }
}

void
HelloCpp::DestroyGL(void)
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

bool
HelloCpp::InitEGL(void)
{
    EGLint numConfigs = 1;

    EGLint eglConfigList[] =
    {
        EGL_RED_SIZE,    5,
        EGL_GREEN_SIZE,    6,
        EGL_BLUE_SIZE,    5,
        EGL_ALPHA_SIZE,    0,
        EGL_DEPTH_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
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
        DestroyGL();
    }

    __eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
    g_eglDisplay = __eglDisplay;
    TryCatch(__eglDisplay != EGL_NO_DISPLAY, , "[HelloCpp] eglGetDisplay() failed.");

    TryCatch(!(eglInitialize(__eglDisplay, null, null) == EGL_FALSE || eglGetError() != EGL_SUCCESS), , "[HelloCpp] eglInitialize() failed.");

    TryCatch(!(eglChooseConfig(__eglDisplay, eglConfigList, &__eglConfig, 1, &numConfigs) == EGL_FALSE ||
        eglGetError() != EGL_SUCCESS), , "[HelloCpp] eglChooseConfig() failed.");

    TryCatch(numConfigs, , "[HelloCpp] eglChooseConfig() failed. because of matching config doesn't exist");

    __eglSurface = eglCreateWindowSurface(__eglDisplay, __eglConfig, (EGLNativeWindowType)__pForm, null);
    g_eglSurface = __eglSurface;
    TryCatch(!(__eglSurface == EGL_NO_SURFACE || eglGetError() != EGL_SUCCESS), , "[HelloCpp] eglCreateWindowSurface() failed.");

    __eglContext = eglCreateContext(__eglDisplay, __eglConfig, EGL_NO_CONTEXT, eglContextList);
    TryCatch(!(__eglContext == EGL_NO_CONTEXT || eglGetError() != EGL_SUCCESS), , "[HelloCpp] eglCreateContext() failed.");

    TryCatch(!(eglMakeCurrent(__eglDisplay, __eglSurface, __eglSurface, __eglContext) == EGL_FALSE ||
        eglGetError() != EGL_SUCCESS), , "[HelloCpp] eglMakeCurrent() failed.");

    return true;

CATCH:
    {
        AppLog("[HelloCpp] HelloCpp can run on systems which supports OpenGL ES(R) 2.0.");
        AppLog("[HelloCpp] When HelloCpp does not correctly execute, there are a few reasons.");
        AppLog("[HelloCpp]    1. The current device(real-target or emulator) does not support OpenGL ES(R) 2.0.\n"
               " Check the Release Notes.");
        AppLog("[HelloCpp]    2. The system running on emulator cannot support OpenGL(R) 2.1 or later.\n"
               " Try with other system.");
        AppLog("[HelloCpp]    3. The system running on emulator does not maintain the latest graphics driver.\n"
               " Update the graphics driver.");
    }

    DestroyGL();

    return false;
}

void
HelloCpp::IncTimeStamp(void)
{
}

bool
HelloCpp::Draw(void)
{
    cocos2d::CCDirector::sharedDirector()->mainLoop();

    return true;
}
