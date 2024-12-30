#include "egl_core.h"

#include "../../CCLogOhos.h"
#include "plugin_render.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>

EGLConfig getConfig(int version, EGLDisplay eglDisplay) {
    int attribList[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_STENCIL_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };
    EGLConfig configs = NULL;
    int configsNum;
    if (!eglChooseConfig(eglDisplay, attribList, &configs, 1, &configsNum)) {
        OHOS_LOGE("eglChooseConfig ERROR");
        return NULL;
    }
    return configs;
}

void EGLCore::GLContextInit(void* window, int w, int h)
{
    OHOS_LOGD("EGLCore::GLContextInit window = %{public}p, w = %{public}d, h = %{public}d.", window, w, h);
    width_ = w;
    height_ = h;
    mEglWindow = (EGLNativeWindowType)(window);

    // 1. create sharedcontext
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        OHOS_LOGE("EGLCore::unable to get EGL display.");
        return;
    }

    EGLint eglMajVers, eglMinVers;
    if (!eglInitialize(mEGLDisplay, &eglMajVers, &eglMinVers)) {
        mEGLDisplay = EGL_NO_DISPLAY;
        OHOS_LOGE("EGLCore::unable to initialize display");
        return;
    }

    mEGLConfig = getConfig(3, mEGLDisplay);
    if (mEGLConfig == nullptr) {
        OHOS_LOGE("EGLCore::GLContextInit config ERROR");
        return;
    }

    // 2. Create EGL Surface from Native Window
    if (mEglWindow) {
        mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEglWindow, nullptr);
        if (mEGLSurface == nullptr) {
            OHOS_LOGE("EGLCore::eglCreateContext eglSurface is null");
            return;
        }
    }

    // 3. Create EGLContext from
    int attrib3_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, mSharedEGLContext, attrib3_list);

    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        OHOS_LOGE("EGLCore::eglMakeCurrent error = %{public}d", eglGetError());
    }
}

void EGLCore::Update()
{
    eglSwapBuffers(mEGLDisplay, mEGLSurface);
}

bool EGLCore::checkGlError(const char* op)
{
    OHOS_LOGE("EGL ERROR CODE = %{public}x", eglGetError());
    GLint error;
    for (error = glGetError(); error; error = glGetError()) {
        OHOS_LOGE("ERROR: %{public}s, ERROR CODE = %{public}x", op, error);
        return true;
    }
    return false;
}

void EGLCore::destroySurface() {
    if(!eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT)) {
        OHOS_LOGE("eglMakeCurrent error = %{public}d", eglGetError());
    }
    eglDestroySurface(mEGLDisplay, mEGLSurface);
    mEGLSurface = nullptr;
}

void EGLCore::createSurface(void* window) {
    mEglWindow = (EGLNativeWindowType)(window);
    if(mEglWindow) {
        mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEglWindow, NULL);
        if(mEGLSurface == nullptr) {
            OHOS_LOGE("EGL eglCreateWindowSurface eglSurface is null");
            return;
        }
    }
    if(!(eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext))){
        OHOS_LOGE("eglMakeCurrent error = %{public}d", eglGetError());
    }
    return;
}