/*
    Copyright 2010 Google Inc.

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


#ifndef GrConfig_DEFINED
#define GrConfig_DEFINED

///////////////////////////////////////////////////////////////////////////////
// preconfig section:
//
// All the work before including GrUserConfig.h should center around guessing
// what platform we're on, and defining low-level symbols based on that.
//
// A build environment may have already defined symbols, so we first check
// for that
//

// hack to ensure we know what sort of Apple platform we're on
#if defined(__APPLE_CPP__) || defined(__APPLE_CC__)
    #include <TargetConditionals.h>
#endif

/**
 *  Gr defines are set to 0 or 1, rather than being undefined or defined
 */

#if !defined(GR_ANDROID_BUILD)
    #define GR_ANDROID_BUILD    0
#endif
#if !defined(GR_IOS_BUILD)
    #define GR_IOS_BUILD        0
#endif
#if !defined(GR_LINUX_BUILD)
    #define GR_LINUX_BUILD      0
#endif
#if !defined(GR_MAC_BUILD)
    #define GR_MAC_BUILD        0
#endif
#if !defined(GR_WIN32_BUILD)
    #define GR_WIN32_BUILD      0
#endif
#if !defined(GR_QNX_BUILD)
    #define GR_QNX_BUILD        0
#endif

/**
 *  If no build target has been defined, attempt to infer.
 */
#if !GR_ANDROID_BUILD && !GR_IOS_BUILD && !GR_LINUX_BUILD && !GR_MAC_BUILD && !GR_WIN32_BUILD && !GR_QNX_BUILD
    #if defined(_WIN32)
        #undef GR_WIN32_BUILD
        #define GR_WIN32_BUILD      1
//      #error "WIN"
    #elif TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #undef GR_IOS_BUILD
        #define GR_IOS_BUILD        1
//      #error "IOS"
    #elif (defined(ANDROID_NDK) && ANDROID_NDK) || defined(ANDROID)
        #undef GR_ANDROID_BUILD
        #define GR_ANDROID_BUILD    1
//      #error "ANDROID"
    #elif TARGET_OS_MAC
        #undef GR_MAC_BUILD
        #define GR_MAC_BUILD        1
//      #error "MAC"
    #elif TARGET_OS_QNX || defined(__QNXNTO__)
        #undef GR_QNX_BUILD
        #define GR_QNX_BUILD        1
//      #error "QNX"
    #else
        #undef GR_LINUX_BUILD
        #define GR_LINUX_BUILD      1
//      #error "LINUX"
    #endif
#endif

// we need both GR_DEBUG and GR_RELEASE to be defined as 0 or 1
//
#ifndef GR_DEBUG
    #ifdef GR_RELEASE
        #define GR_DEBUG !GR_RELEASE
    #else
        #ifdef NDEBUG
            #define GR_DEBUG    0
        #else
            #define GR_DEBUG    1
        #endif
    #endif
#endif

#ifndef GR_RELEASE
    #define GR_RELEASE  !GR_DEBUG
#endif

#if GR_DEBUG == GR_RELEASE
    #error "GR_DEBUG and GR_RELEASE must not be the same"
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#if GR_WIN32_BUILD
// VC8 doesn't support stdint.h, so we define those types here.
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/*
 *  Include stdint.h with defines that trigger declaration of C99 limit/const
 *  macros here before anyone else has a chance to include stdint.h without 
 *  these.
 */
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <stdint.h>
#endif

/*
 *  The "user config" file can be empty, and everything should work. It is
 *  meant to store a given platform/client's overrides of our guess-work.
 *
 *  A alternate user config file can be specified by defining
 *  GR_USER_CONFIG_FILE. It should be defined relative to GrConfig.h
 *
 *  e.g. it can specify GR_DEBUG/GR_RELEASE as it please, change the BUILD
 *  target, or supply its own defines for anything else (e.g. GR_SCALAR)
 */
#if !defined(GR_USER_CONFIG_FILE)
    #include "GrUserConfig.h"
#else
    #include GR_USER_CONFIG_FILE
#endif


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// postconfig section:
//

// GR_IMPLEMENTATION should be define to 1 when building Gr and 0 when including
// it in another dependent build. The Gr makefile/ide-project should define this
// to 1.
#if !defined(GR_IMPLEMENTATION)
    #define GR_IMPLEMENTATION 0
#endif

// If Gr is built as a shared library then GR_DLL should be defined to 1 (both
// when building Gr and when including its headers in dependent builds). Only
// currently supported minimally for Chrome's Win32 Multi-DLL build (TODO:
// correctly exort all of the public API correctly and support shared lib on
// other platforms).
#if !defined(GR_DLL)
    #define GR_DLL 0
#endif

#if defined(WIN32) && defined(SKIA_DLL)
    #if GR_IMPLEMENTATION
        #if defined(__GNUC__)
            #define GR_API __attribute__((dllexport))
        #else
            #define GR_API __declspec(dllexport)
        #endif
    #else
        #if defined(__GNUC__)
            #define GR_API __attribute__((dllimport))
        #else
            #define GR_API __declspec(dllimport)
        #endif
    #endif
#elif __GNUC__ >= 4
    #if GR_IMPLEMENTATION
        #define GR_API __attribute__((visibility("default")))
    #else
        #define GR_API
    #endif
#else
    #define GR_API
#endif


// By now we must have a GR_..._BUILD symbol set to 1, and a decision about
// debug -vs- release
//

extern GR_API void GrPrintf(const char format[], ...);

/**
 *  GR_STRING makes a string of X where X is expanded before conversion to a string
 *  if X itself contains macros.
 */
#define GR_STRING(X) GR_STRING_IMPL(X)
#define GR_STRING_IMPL(X) #X

/**
 *  GR_CONCAT concatenates X and Y  where each is expanded before
 *  contanenation if either contains macros.
 */
#define GR_CONCAT(X,Y) GR_CONCAT_IMPL(X,Y)
#define GR_CONCAT_IMPL(X,Y) X##Y

/**
 *  Creates a string of the form "<filename>(<linenumber>) : "
 */
#define GR_FILE_AND_LINE_STR __FILE__ "(" GR_STRING(__LINE__) ") : "

/**
 *  Compilers have different ways of issuing warnings. This macro
 *  attempts to abstract them, but may need to be specialized for your
 *  particular compiler.
 *  To insert compiler warnings use "#pragma message GR_WARN(<string>)"
 */
#if defined(_MSC_VER) && _MSC_VER
    #define GR_WARN(MSG) (GR_FILE_AND_LINE_STR "WARNING: " MSG)
#else//__GNUC__ - may need other defines for different compilers
    #define GR_WARN(MSG) ("WARNING: " MSG)
#endif

/**
 *  GR_ALWAYSBREAK is an unconditional break in all builds.
 */
#if !defined(GR_ALWAYSBREAK)
    #if     GR_WIN32_BUILD
        #define GR_ALWAYSBREAK __debugbreak()
    #else
        // TODO: do other platforms really not have continuable breakpoints?
        // sign extend for 64bit architectures to be sure this is
        // in the high address range
        #define GR_ALWAYSBREAK *((int*)(int64_t)(int32_t)0xbeefcafe) = 0;
    #endif
#endif

/**
 *  GR_DEBUGBREAK is an unconditional break in debug builds.
 */
#if !defined(GR_DEBUGBREAK)
    #if GR_DEBUG
        #define GR_DEBUGBREAK GR_ALWAYSBREAK
    #else
        #define GR_DEBUGBREAK
    #endif
#endif

/**
 *  GR_ALWAYSASSERT is an assertion in all builds.
 */
#if !defined(GR_ALWAYSASSERT)
    #define GR_ALWAYSASSERT(COND)                                        \
        do {                                                             \
            if (!(COND)) {                                               \
                GrPrintf("%s %s failed\n", GR_FILE_AND_LINE_STR, #COND); \
                GR_ALWAYSBREAK;                                          \
            }                                                            \
        } while (false)
#endif

/**
 *  GR_DEBUGASSERT is an assertion in debug builds only.
 */
#if !defined(GR_DEBUGASSERT)
    #if GR_DEBUG
        #define GR_DEBUGASSERT(COND) GR_ALWAYSASSERT(COND)
    #else
        #define GR_DEBUGASSERT(COND)
    #endif
#endif

/**
 *  Prettier forms of the above macros.
 */
#define GrAssert(COND) GR_DEBUGASSERT(COND)
#define GrAlwaysAssert(COND) GR_ALWAYSASSERT(COND)

/**
 * Crash from unrecoverable condition, optionally with a message.
 */
inline void GrCrash() { GrAlwaysAssert(false); }
inline void GrCrash(const char* msg) { GrPrintf(msg); GrAlwaysAssert(false); }

/**
 *  GR_DEBUGCODE compiles the code X in debug builds only
 */
#if !defined(GR_DEBUGCODE)
    #if GR_DEBUG
        #define GR_DEBUGCODE(X) X
    #else
        #define GR_DEBUGCODE(X)
    #endif
#endif

/**
 *  GR_STATIC_ASSERT is a compile time assertion. Depending on the platform
 *  it may print the message in the compiler log. Obviously, the condition must
 *  be evaluatable at compile time.
 */
// VS 2010 and GCC compiled with c++0x or gnu++0x support the new
// static_assert.
#if !defined(GR_STATIC_ASSERT)
    #if (defined(_MSC_VER) && _MSC_VER >= 1600) || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__)
        #define GR_STATIC_ASSERT(CONDITION) static_assert(CONDITION, "bug")
    #else
        template <bool> class GR_STATIC_ASSERT_FAILURE;
        template <> class GR_STATIC_ASSERT_FAILURE<true> {};
        #define GR_STATIC_ASSERT(CONDITION) \
            enum {GR_CONCAT(X,__LINE__) = \
            sizeof(GR_STATIC_ASSERT_FAILURE<CONDITION>)}
    #endif
#endif

#if !defined(GR_SCALAR_IS_FLOAT)
    #define GR_SCALAR_IS_FLOAT   0
#endif
#if !defined(GR_SCALAR_IS_FIXED)
    #define GR_SCALAR_IS_FIXED   0
#endif

#if !defined(GR_TEXT_SCALAR_TYPE_IS_USHORT)
    #define GR_TEXT_SCALAR_TYPE_IS_USHORT  0
#endif
#if !defined(GR_TEXT_SCALAR_TYPE_IS_FLOAT)
    #define GR_TEXT_SCALAR_TYPE_IS_FLOAT   0
#endif
#if !defined(GR_TEXT_SCALAR_TYPE_IS_FIXED)
    #define GR_TEXT_SCALAR_TYPE_IS_FIXED   0
#endif

#ifndef GR_DUMP_TEXTURE_UPLOAD
    #define GR_DUMP_TEXTURE_UPLOAD  0
#endif

/**
 *  GR_COLLECT_STATS controls whether the GrGpu class collects stats.
 *  If not already defined then collect in debug build but not release.
 */
#if !defined(GR_COLLECT_STATS)
    #define GR_COLLECT_STATS GR_DEBUG
#endif

/**
 *  GR_STATIC_RECT_VB controls whether rects are drawn by issuing a vertex
 *  for each corner or using a static vb that is positioned by modifying the
 *  view / texture matrix.
 */
#if !defined(GR_STATIC_RECT_VB)
    #define GR_STATIC_RECT_VB 1
#endif

/**
 *  GR_AGGRESSIVE_SHADER_OPTS controls how aggressively shaders are optimized
 *  for special cases. On systems where program changes are expensive this
 *  may not be advantageous. Consecutive draws may no longer use the same
 *  program.
 */
#if !defined(GR_AGGRESSIVE_SHADER_OPTS)
    #define GR_AGGRESSIVE_SHADER_OPTS 1
#endif

/**
 * GR_GEOM_BUFFER_LOCK_THRESHOLD gives a threshold (in bytes) for when Gr should
 * lock a GrGeometryBuffer to update its contents. It will use Lock() if the
 * size of the udpated region is greater than the threshold. Otherwise it will
 * use updateData() or updateSubData().
 */
#if !defined(GR_GEOM_BUFFER_LOCK_THRESHOLD)
    #define GR_GEOM_BUFFER_LOCK_THRESHOLD (1 << 15)
#endif

/**
 * Enables/disables use of offscreen AA
 */
#if !defined(GR_USE_OFFSCREEN_AA)
    #define GR_USE_OFFSCREEN_AA 0
#endif

/**
 * GR_MAX_OFFSCREEN_AA_SIZE controls the size at which offscreen AA will tile.
 * Tiling saves GPU memory by limiting the size of the offscreen buffer. The
 * max offscreen may be as large as (4*GR_MAX_OFFSCREEN_AA_SIZE)^2 pixels.
 */
#if !defined(GR_MAX_OFFSCREEN_AA_SIZE)
    #define GR_MAX_OFFSCREEN_AA_SIZE    256
#endif

///////////////////////////////////////////////////////////////////////////////
// tail section:
//
// Now we just assert if we are missing some required define, or if we detect
// and inconsistent combination of defines
//


/**
 *  Only one build target macro should be 1 and the rest should be 0.
 */
#define GR_BUILD_SUM    (GR_WIN32_BUILD + GR_MAC_BUILD + GR_IOS_BUILD + GR_ANDROID_BUILD + GR_LINUX_BUILD + GR_QNX_BUILD)
#if 0 == GR_BUILD_SUM
    #error "Missing a GR_BUILD define"
#elif 1 != GR_BUILD_SUM
    #error "More than one GR_BUILD defined"
#endif


#if !GR_SCALAR_IS_FLOAT && !GR_SCALAR_IS_FIXED
    #undef  GR_SCALAR_IS_FLOAT
    #define GR_SCALAR_IS_FLOAT              1
    #pragma message GR_WARN("Scalar type not defined, defaulting to float")
#endif

#if !GR_TEXT_SCALAR_IS_FLOAT && \
    !GR_TEXT_SCALAR_IS_FIXED && \
    !GR_TEXT_SCALAR_IS_USHORT
    #undef  GR_TEXT_SCALAR_IS_FLOAT
    #define GR_TEXT_SCALAR_IS_FLOAT         1
    #pragma message GR_WARN("Text scalar type not defined, defaulting to float")
#endif

#if 0
#if GR_WIN32_BUILD
//    #pragma message GR_WARN("GR_WIN32_BUILD")
#endif
#if GR_MAC_BUILD
//    #pragma message GR_WARN("GR_MAC_BUILD")
#endif
#if GR_IOS_BUILD
//    #pragma message GR_WARN("GR_IOS_BUILD")
#endif
#if GR_ANDROID_BUILD
//    #pragma message GR_WARN("GR_ANDROID_BUILD")
#endif
#if GR_LINUX_BUILD
//    #pragma message GR_WARN("GR_LINUX_BUILD")
#endif
#if GR_QNX_BUILD
//    #pragma message GR_WARN("GR_QNX_BUILD")
#endif
#endif

#endif

