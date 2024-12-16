#ifndef _GL_CORE_
#define _GL_CORE_

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <string>

class EGLCore {
public:
    EGLCore() {};
    void GLContextInit(void* window, int w, int h);
    void Update();
    void destroySurface();
    void createSurface(void* window);
public:
    int width_;
    int height_;

private:
    bool checkGlError(const char* op);

    EGLNativeWindowType mEglWindow;
    EGLDisplay mEGLDisplay = EGL_NO_DISPLAY;
    EGLConfig mEGLConfig = nullptr;
    EGLContext mEGLContext = EGL_NO_CONTEXT;
    EGLContext mSharedEGLContext = EGL_NO_CONTEXT;
    EGLSurface mEGLSurface = nullptr;
};

#endif // _GL_CORE_
