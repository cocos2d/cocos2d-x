#include "OpenGLES.h"

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

    const EGLint contextAttributes[] = 
    { 
        EGL_CONTEXT_CLIENT_VERSION, 2, 
        EGL_NONE
    };

    const EGLint defaultDisplayAttributes[] =
    {
        // These are the default display attributes, used to request ANGLE's D3D11 renderer.
        // eglInitialize will only succeed with these attributes if the hardware supports D3D11 Feature Level 10_0+.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_NONE,
    };
    
    const EGLint fl9_3DisplayAttributes[] =
    {
        // These can be used to request ANGLE's D3D11 renderer, with D3D11 Feature Level 9_3.
        // These attributes are used if the call to eglInitialize fails with the default display attributes.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE, 9,
        EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE, 3,
        EGL_NONE,
    };

    const EGLint warpDisplayAttributes[] =
    {
        // These attributes can be used to request D3D11 WARP.
        // They are used if eglInitialize fails with both the default display attributes and the 9_3 display attributes.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_PLATFORM_ANGLE_USE_WARP_ANGLE, EGL_TRUE,
        EGL_NONE,
    };
    
    EGLConfig config = NULL;

    // eglGetPlatformDisplayEXT is an alternative to eglGetDisplay. It allows us to pass in display attributes, used to configure D3D11.
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
    if (!eglGetPlatformDisplayEXT)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to get function eglGetPlatformDisplayEXT");
    }

#if (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
    // Firstly get the display, and apply the default display attributes. They correspond to D3D11 Feature Level 10_0+.
    mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, defaultDisplayAttributes);
    if (mEglDisplay == EGL_NO_DISPLAY)
    {
        throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
    }

    if (eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
    {
#endif
        // This call to eglInitialize (after applying the default display attributes) will return EGL_FALSE if Feature Level 10_0+ 
        // is not supported by the hardware graphics card. This could happen on Windows Phone devices or on certain Windows tablets.
        // Instead, we try applying the D3D11 Feature Level 9_3 display attributes and try to initialize the display again.
        mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, fl9_3DisplayAttributes);
        if (mEglDisplay == EGL_NO_DISPLAY)
        {
            throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
        }

        if (eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
        {
            // This call to eglInitialize will return EGL_FALSE if Feature Level 9_3 isn't supported either (for example, on a Surface RT).
            // We must now use WARP, a fully-featured D3D11 software rasterizer. WARP supports all valid D3D11 feature levels.
            mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, warpDisplayAttributes);
            if (mEglDisplay == EGL_NO_DISPLAY)
            {
                throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
            }

            if (eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
            {
                // If all of the calls to eglInitialize returned EGL_FALSE then an error has occurred.
                throw Exception::CreateException(E_FAIL, L"Failed to initialize EGL");
            }
        }
#if (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
    }
#endif
    EGLint numConfigs = 0;
    if ((eglChooseConfig(mEglDisplay, configAttributes, &mEglConfig, 1, &numConfigs) == EGL_FALSE) || (numConfigs == 0))
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
