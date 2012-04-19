#ifndef SkEGLContext_DEFINED
#define SkEGLContext_DEFINED

#if defined(SK_MESA)
    #include "GL/osmesa.h"
#elif defined(SK_BUILD_FOR_MAC)
    #include <AGL/agl.h>
#elif defined(SK_BUILD_FOR_UNIX)
    #include <X11/Xlib.h>
    #include <GL/glx.h>
#elif defined(SK_BUILD_FOR_WIN32)
    #include <Windows.h>
    #include <GL/GL.h>
#else

#endif

/**
 *  Create an offscreen opengl context
 */
class SkEGLContext {
public:
    SkEGLContext();
    ~SkEGLContext();

    bool init(const int width, const int height);

private:
#if defined(SK_MESA)
    OSMesaContext context;
    GLfloat *image;
#elif defined(SK_BUILD_FOR_MAC)
    AGLContext context;
#elif defined(SK_BUILD_FOR_UNIX)
    GLXContext context;
    Display *display;
    Pixmap pixmap;
    GLXPixmap glxPixmap;
#elif defined(SK_BUILD_FOR_WIN32)
    HWND fWindow;
    HDC fDeviceContext;
    HGLRC fGlRenderContext;
#else

#endif
};

#endif
