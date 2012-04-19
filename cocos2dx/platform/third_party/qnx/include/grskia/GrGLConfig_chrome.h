#ifndef GrGLConfig_chrome_DEFINED
#define GrGLConfig_chrome_DEFINED

// chrome always assumes BGRA
#define GR_GL_32BPP_COLOR_FORMAT        GR_GL_BGRA

// glGetError() forces a sync with gpu process on chrome
#define GR_GL_CHECK_ERROR_START         0

// ANGLE creates a temp VB for vertex attributes not specified per-vertex.
#define GR_GL_NO_CONSTANT_ATTRIBUTES    GR_WIN32_BUILD

#endif
