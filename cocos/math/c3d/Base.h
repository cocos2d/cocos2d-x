#ifndef BASE_H_
#define BASE_H_

// C/C++
#include <new>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cwchar>
#include <cwctype>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <algorithm>
#include <limits>
#include <functional>

#include "ccConfig.h"
#include "CCGL.h"


#define C3D_Max(a,b)            (((a) > (b)) ? (a) : (b))
#define C3D_Min(a,b)            (((a) < (b)) ? (a) : (b))

// Common
#ifndef NULL
#define NULL     0
#endif

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F 
#endif

// Print logging (implemented per platform)
namespace cocos3d
{
extern void printError(const char* format, ...);
}

#ifdef __ANDROID__
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

// System Errors
#define LOG_ERROR(x) \
    { \
        LOGI(x); \
        assert(#x == 0); \
    }
#define LOG_ERROR_VARG(x, ...) \
    { \
        LOGI(x, __VA_ARGS__); \
        assert(#x == 0); \
    }

// Warning macro
#ifdef WARN
#undef WARN
#endif
#define WARN(x) LOGI(x)
#define WARN_VARG(x, ...) LOGI(x, __VA_ARGS__)

#else

// System Errors
#define LOG_ERROR(x) \
    { \
        printError(x); \
        assert(#x == 0); \
    }
#define LOG_ERROR_VARG(x, ...) \
    { \
        printError(x, __VA_ARGS__); \
        assert(#x == 0); \
    }

// Warning macro
#ifdef WARN
#undef WARN
#endif
#define WARN(x) printError(x)
#define WARN_VARG(x, ...) printError(x, __VA_ARGS__)
#endif


// Object deletion macro
#define SAFE_DELETE(x) \
    { \
        delete x; \
        x = NULL; \
    }

// Array deletion macro
#define SAFE_DELETE_ARRAY(x) \
    { \
        delete[] x; \
        x = NULL; \
    }

// Ref cleanup macro
#define SAFE_RELEASE(x) \
    if (x) \
    { \
        x->release(); \
        x = NULL; \
    }

// Math
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif

#ifdef WIN32
    inline float round(float r)
    {
        return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
    }
#endif

// NOMINMAX makes sure that windef.h doesn't add macros min and max
#ifdef WIN32
    #define NOMINMAX
#endif



#define WINDOW_VSYNC        1
#define WINDOW_FULLSCREEN   0

// Graphics (OpenGL)
#if defined(__ANDROID__)
    #include <EGL/egl.h>
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
    extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
    extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
    extern PFNGLISVERTEXARRAYOESPROC glIsVertexArray;
    #define glClearDepth glClearDepthf
    #define OPENGL_ES
    #define USE_PVRTC
#elif WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <GL/glew.h>
    #define USE_VAO
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
        #define glBindVertexArray glBindVertexArrayOES
        #define glDeleteVertexArrays glDeleteVertexArraysOES
        #define glGenVertexArrays glGenVertexArraysOES
        #define glIsVertexArray glIsVertexArrayOES
        #define glClearDepth glClearDepthf
        #define OPENGL_ES
        #define USE_PVRTC
        #define USE_VAO
    #elif TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
        #define glBindVertexArray glBindVertexArrayAPPLE
        #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
        #define glGenVertexArrays glGenVertexArraysAPPLE
        #define glIsVertexArray glIsVertexArrayAPPLE
        #define USE_VAO
    #else
        #error "Unsupported Apple Device"
    #endif
#endif



// Hardware buffer
namespace cocos3d
{
typedef GLint VertexAttribute;
typedef GLuint VertexBufferHandle;
typedef GLuint IndexBufferHandle;
typedef GLuint TextureHandle;
typedef GLuint FrameBufferHandle;
typedef GLuint RenderBufferHandle;
}

/**
 * GL assertion that can be used for any OpenGL function call.
 *
 * This macro will assert if an error is detected when executing
 * the specified GL code. This macro will do nothing in release
 * mode and is therefore safe to use for realtime/per-frame GL
 * function calls.
 */
#ifdef NDEBUG
#define GL_ASSERT( gl_code ) gl_code
#else
#define GL_ASSERT( gl_code ) \
    { \
        gl_code; \
        __gl_error_code = glGetError(); \
        if (__gl_error_code != GL_NO_ERROR) \
        { \
            LOG_ERROR_VARG(#gl_code ": 0x%x", (int)__gl_error_code); \
        } \
        assert(__gl_error_code == GL_NO_ERROR); \
    }
#endif

/**
 * Executes the specified GL code and checks the GL error afterwards
 * to ensure it succeeded.
 *
 * This macro should be used instead of GL_ASSERT for code that must
 * be checked in both debug and release builds. The GL_LAST_ERROR
 * macro can be used afterwards to check whether a GL error was
 * encountered executing the specified code.
 */
#define GL_CHECK( gl_code ) \
    { \
        while (glGetError() != GL_NO_ERROR) ; \
        gl_code; \
        __gl_error_code = glGetError(); \
        if (__gl_error_code != GL_NO_ERROR) \
        { \
            LOG_ERROR_VARG(#gl_code ": %d", (int)__gl_error_code); \
        } \
    }

// Global variable to hold GL errors
extern GLenum __gl_error_code;

/**
 * Accesses the most recently set global GL error.
 */
#define GL_LAST_ERROR() __gl_error_code


#if defined(WIN32)
    #pragma warning( disable : 4172 )
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4311 )
    #pragma warning( disable : 4390 )
    #pragma warning( disable : 4800 )
    #pragma warning( disable : 4996 )
#endif

#ifdef __ANDROID__
//#include <android_native_app_glue.h>
//extern void amain(struct android_app* state);
#endif


// Assert has special behavior on Windows (for Visual Studio).
#ifdef WIN32
#ifdef assert
#undef assert
#endif
#ifdef _DEBUG
#define assert(expression) do { \
    if (!(expression)) \
    { \
        printError("Assertion \'" #expression "\' failed."); \
        __debugbreak(); \
    } } while (0)

#else
#define assert(expression) do { (void)sizeof(expression); } while (0)
#endif
#endif

#endif
