#pragma once

// OpenGL ES includes
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <angle_windowsstore.h>

class OpenGLES
{
public:
    OpenGLES();
    ~OpenGLES();

    EGLSurface CreateSurface(Windows::UI::Xaml::Controls::SwapChainPanel^ panel, const Windows::Foundation::Size* renderSurfaceSize);
    void DestroySurface(const EGLSurface surface);
    void MakeCurrent(const EGLSurface surface);
    EGLBoolean SwapBuffers(const EGLSurface surface);
    void Reset();

private:
    void Initialize();
    void Cleanup();

private:
    EGLDisplay mEglDisplay;
    EGLContext mEglContext;
    EGLConfig  mEglConfig;
};
