#include "pch.h"

using namespace Platform;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

OpenGLES::OpenGLES() :
    mEglConfig(nullptr),
    mEglDisplay(EGL_NO_DISPLAY),
    mEglContext(EGL_NO_CONTEXT)
{
    Initialize();
}

OpenGLES::~OpenGLES()
{
    Cleanup();
}

void OpenGLES::Initialize()
{
    const EGLint configAttributes[] = 
    {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    const EGLint displayAttributes[] =
    {
        // This can be used to configure D3D11. For example, EGL_PLATFORM_ANGLE_TYPE_D3D11_FL9_3_ANGLE could be used.
        // This would ask the graphics card to use D3D11 Feature Level 9_3 instead of Feature Level 11_0+.
        // On Windows Phone, this would allow the Phone Emulator to act more like the GPUs that are available on real Phone devices.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_NONE,
    };

    const EGLint contextAttributes[] = 
    { 
        EGL_CONTEXT_CLIENT_VERSION, 2, 
        EGL_NONE
    };

    // eglGetPlatformDisplayEXT is an alternative to eglGetDisplay. It allows us to pass in 'displayAttributes' to configure D3D11.
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
    if (!eglGetPlatformDisplayEXT)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to get function eglGetPlatformDisplayEXT");
    }

    mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, displayAttributes);
    if (mEglDisplay == EGL_NO_DISPLAY)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to get default EGL display");
    }

    if (eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to initialize EGL");
    }

    EGLint numConfigs = 0;
    if (eglGetConfigs(mEglDisplay, NULL, 0, &numConfigs) == EGL_FALSE)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to get EGLConfig count");
    }

    if (eglChooseConfig(mEglDisplay, configAttributes, &mEglConfig, 1, &numConfigs) == EGL_FALSE)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to choose first EGLConfig");
    }

    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, contextAttributes);
    if (mEglContext == EGL_NO_CONTEXT)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to create EGL context");
    }
}

void OpenGLES::Cleanup()
{
    if (mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT)
    {
        eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }

    if (mEglDisplay != EGL_NO_DISPLAY)
    {
        eglTerminate(mEglDisplay);
        mEglDisplay = EGL_NO_DISPLAY;
    }
}

void OpenGLES::Reset()
{
    Cleanup();
    Initialize();
}

EGLSurface OpenGLES::CreateSurface(SwapChainPanel^ panel, const Size* renderSurfaceSize)
{
    if (!panel)
    {
        throw Exception::CreateException(E_INVALIDARG, L"SwapChainPanel parameter is invalid");
    }

    EGLSurface surface = EGL_NO_SURFACE;

    // Create a PropertySet and initialize with the EGLNativeWindowType.
    PropertySet^ surfaceCreationProperties = ref new PropertySet();
    surfaceCreationProperties->Insert(ref new String(EGLNativeWindowTypeProperty), panel);

    // If a render surface size is specified, add it to the surface creation properties
    if (renderSurfaceSize != nullptr)
    {
        surfaceCreationProperties->Insert(ref new String(EGLRenderSurfaceSizeProperty), PropertyValue::CreateSize(*renderSurfaceSize));
    }

    surface = eglCreateWindowSurface(mEglDisplay, mEglConfig, reinterpret_cast<IInspectable*>(surfaceCreationProperties), NULL);
    if (surface == EGL_NO_SURFACE)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to create EGL surface");
    }

    return surface;
}

void OpenGLES::DestroySurface(const EGLSurface surface)
{
    if (mEglDisplay != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE)
    {
        eglDestroySurface(mEglDisplay, surface);
    }
}

void OpenGLES::MakeCurrent(const EGLSurface surface)
{
    if (eglMakeCurrent(mEglDisplay, surface, surface, mEglContext) == EGL_FALSE)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to make EGLSurface current");
    }
}

EGLBoolean OpenGLES::SwapBuffers(const EGLSurface surface)
{
    return (eglSwapBuffers(mEglDisplay, surface));
}
