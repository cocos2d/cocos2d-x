/*
    Copyright 2011 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrGLConfig_DEFINED
#define GrGLConfig_DEFINED

#include "GrTypes.h"
#include "GrGLDefines.h"

/**
 * Optional GL config file.
 */
#ifdef GR_GL_CUSTOM_SETUP_HEADER
    #include GR_GL_CUSTOM_SETUP_HEADER
#endif

#if !defined(GR_GL_FUNCTION_TYPE)
    #define GR_GL_FUNCTION_TYPE
#endif

/**
 * The following are optional defines that can be enabled at the compiler
 * command line, in a IDE project, in a GrUserConfig.h file, or in a GL custom
 * file (if one is in use). If a GR_GL_CUSTOM_SETUP_HEADER is used they can
 * also be placed there.
 *
 * GR_GL_LOG_CALLS: if 1 Gr can print every GL call using GrPrintf. Defaults to
 * 0. Logging can be enabled and disabled at runtime using a debugger via to
 * global gLogCallsGL. The initial value of gLogCallsGL is controlled by
 * GR_GL_LOG_CALLS_START.
 *
 * GR_GL_LOG_CALLS_START: controls the initial value of gLogCallsGL when
 * GR_GL_LOG_CALLS is 1. Defaults to 0.
 *
 * GR_GL_CHECK_ERROR: if enabled Gr can do a glGetError() after every GL call.
 * Defaults to 1 if GR_DEBUG is set, otherwise 0. When GR_GL_CHECK_ERROR is 1
 * this can be toggled in a debugger using the gCheckErrorGL global. The initial
 * value of gCheckErrorGL is controlled by by GR_GL_CHECK_ERROR_START.
 *
 * GR_GL_CHECK_ERROR_START: controls the initial value of gCheckErrorGL
 * when GR_GL_CHECK_ERROR is 1.  Defaults to 1.
 *
 * GR_GL_NO_CONSTANT_ATTRIBUTES: if this evaluates to true then the GL backend
 * will use uniforms instead of attributes in all cases when there is not
 * per-vertex data. This is important when the underlying GL implementation
 * doesn't actually support immediate style attribute values (e.g. when 
 * the GL stream is converted to DX as in ANGLE on Chrome). Defaults to 0.
 *
 * GR_GL_ATTRIBUTE_MATRICES: If changing uniforms is very expensive it may be
 * faster to use vertex attributes for matrices (set via glVertexAttrib3fv). 
 * Setting this build flag enables this behavior. GR_GL_NO_CONSTANT_ATTRIBUTES
 * must not be set since this uses constant attributes for the matrices. 
 * Defaults to 0.
 */

#if !defined(GR_GL_LOG_CALLS)
    #define GR_GL_LOG_CALLS                 0
#endif

#if !defined(GR_GL_LOG_CALLS_START)
    #define GR_GL_LOG_CALLS_START           0
#endif

#if !defined(GR_GL_CHECK_ERROR)
    #define GR_GL_CHECK_ERROR               GR_DEBUG
#endif

#if !defined(GR_GL_CHECK_ERROR_START)
    #define GR_GL_CHECK_ERROR_START         1
#endif

#if !defined(GR_GL_NO_CONSTANT_ATTRIBUTES)
    #define GR_GL_NO_CONSTANT_ATTRIBUTES    0
#endif

#if !defined(GR_GL_ATTRIBUTE_MATRICES)
    #define GR_GL_ATTRIBUTE_MATRICES        0
#endif

#if(GR_GL_NO_CONSTANT_ATTRIBUTES) && (GR_GL_ATTRIBUTE_MATRICES)
    #error "Cannot combine GR_GL_NO_CONSTANT_ATTRIBUTES and GR_GL_ATTRIBUTE_MATRICES"
#endif

////////////////////////////////////////////////////////////////////////////////

/**
 * The following macros are used to staticlly configure the default
 * GrGLInterface, but should not be used outside of the GrGLInterface
 * scaffolding.  Undefine here to prevent accidental use.
 */
#undef GR_SUPPORT_GLDESKTOP
#undef GR_SUPPORT_GLES1
#undef GR_SUPPORT_GLES2
#undef GR_SUPPORT_GLES

////////////////////////////////////////////////////////////////////////////////

#if GR_SCALAR_IS_FIXED
    #define GrGLType   GL_FIXED
#elif GR_SCALAR_IS_FLOAT
    #define GrGLType   GR_GL_FLOAT
#else
    #error "unknown GR_SCALAR type"
#endif

#if GR_TEXT_SCALAR_IS_USHORT
    #define GrGLTextType                    GR_GL_UNSIGNED_SHORT
    #define GR_GL_TEXT_TEXTURE_NORMALIZED   1
#elif GR_TEXT_SCALAR_IS_FLOAT
    #define GrGLTextType                    GR_GL_FLOAT
    #define GR_GL_TEXT_TEXTURE_NORMALIZED   0
#elif GR_TEXT_SCALAR_IS_FIXED
    #define GrGLTextType                    GR_GL_FIXED
    #define GR_GL_TEXT_TEXTURE_NORMALIZED   0
#else
    #error "unknown GR_TEXT_SCALAR type"
#endif

// Pick a pixel config for 32bit bitmaps. Our default is GL_RGBA (except on
// Windows where we match GDI's order).
#ifndef GR_GL_32BPP_COLOR_FORMAT
    #if GR_WIN32_BUILD || GR_LINUX_BUILD || GR_QNX_BUILD
        #define GR_GL_32BPP_COLOR_FORMAT    GR_GL_BGRA
    #else
        #define GR_GL_32BPP_COLOR_FORMAT    GR_GL_RGBA
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////

extern void GrGLCheckErr(const char* location, const char* call);

extern void GrGLClearErr();

#if GR_GL_CHECK_ERROR
    extern bool gCheckErrorGL;
    #define GR_GL_CHECK_ERROR_IMPL(X) if (gCheckErrorGL) GrGLCheckErr(GR_FILE_AND_LINE_STR, #X)
#else
    #define GR_GL_CHECK_ERROR_IMPL(X)
#endif

#if GR_GL_LOG_CALLS
    extern bool gLogCallsGL;
    #define GR_GL_LOG_CALLS_IMPL(X) if (gLogCallsGL) GrPrintf(GR_FILE_AND_LINE_STR "GL: " #X "\n")
#else
    #define GR_GL_LOG_CALLS_IMPL(X)
#endif

#define GR_GL(X)                 GrGLGetGLInterface()->f##X;; GR_GL_LOG_CALLS_IMPL(X); GR_GL_CHECK_ERROR_IMPL(X);
#define GR_GL_NO_ERR(X)          GrGLGetGLInterface()->f##X;; GR_GL_LOG_CALLS_IMPL(X);

#define GR_GL_SUPPORT_DESKTOP   (kDesktop_GrGLBinding == GrGLGetGLInterface()->fBindingsExported)
#define GR_GL_SUPPORT_ES1       (kES1_GrGLBinding == GrGLGetGLInterface()->fBindingsExported)
#define GR_GL_SUPPORT_ES2       (kES2_GrGLBinding == GrGLGetGLInterface()->fBindingsExported)
#define GR_GL_SUPPORT_ES        (GR_GL_SUPPORT_ES1 || GR_GL_SUPPORT_ES2)

////////////////////////////////////////////////////////////////////////////////

/**
 *  GrGLRestoreResetRowLength() will reset GL_UNPACK_ROW_LENGTH to 0. We write
 *  this wrapper, since GL_UNPACK_ROW_LENGTH is not available on all GL versions
 */
extern void GrGLRestoreResetRowLength();

////////////////////////////////////////////////////////////////////////////////

/**
 *  Some drivers want the var-int arg to be zero-initialized on input.
 */
#define GR_GL_INIT_ZERO     0
#define GR_GL_GetIntegerv(e, p)     \
    do {                            \
        *(p) = GR_GL_INIT_ZERO;     \
        GR_GL(GetIntegerv(e, p));   \
    } while (0)

////////////////////////////////////////////////////////////////////////////////

#endif
