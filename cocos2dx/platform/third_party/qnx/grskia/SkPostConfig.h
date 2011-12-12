/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkPostConfig_DEFINED
#define SkPostConfig_DEFINED

#if defined(SK_BUILD_FOR_WIN32) || defined(SK_BUILD_FOR_WINCE)
    #define SK_BUILD_FOR_WIN
#endif

#if defined(SK_DEBUG) && defined(SK_RELEASE)
    #error "cannot define both SK_DEBUG and SK_RELEASE"
#elif !defined(SK_DEBUG) && !defined(SK_RELEASE)
    #error "must define either SK_DEBUG or SK_RELEASE"
#endif

#if defined SK_SUPPORT_UNITTEST && !defined(SK_DEBUG)
    #error "can't have unittests without debug"
#endif

#if defined(SK_SCALAR_IS_FIXED) && defined(SK_SCALAR_IS_FLOAT)
    #error "cannot define both SK_SCALAR_IS_FIXED and SK_SCALAR_IS_FLOAT"
#elif !defined(SK_SCALAR_IS_FIXED) && !defined(SK_SCALAR_IS_FLOAT)
    #ifdef SK_CAN_USE_FLOAT
        #define SK_SCALAR_IS_FLOAT
    #else
        #define SK_SCALAR_IS_FIXED
    #endif
#endif

#if defined(SK_SCALAR_IS_FLOAT) && !defined(SK_CAN_USE_FLOAT)
    #define SK_CAN_USE_FLOAT
    // we do nothing in the else case: fixed-scalars can have floats or not
#endif

#if defined(SK_CPU_LENDIAN) && defined(SK_CPU_BENDIAN)
    #error "cannot define both SK_CPU_LENDIAN and SK_CPU_BENDIAN"
#elif !defined(SK_CPU_LENDIAN) && !defined(SK_CPU_BENDIAN)
    #error "must define either SK_CPU_LENDIAN or SK_CPU_BENDIAN"
#endif

// ensure the port has defined all of these, or none of them
#ifdef SK_A32_SHIFT
    #if !defined(SK_R32_SHIFT) || !defined(SK_G32_SHIFT) || !defined(SK_B32_SHIFT)
        #error "all or none of the 32bit SHIFT amounts must be defined"
    #endif
#else
    #if defined(SK_R32_SHIFT) || defined(SK_G32_SHIFT) || defined(SK_B32_SHIFT)
        #error "all or none of the 32bit SHIFT amounts must be defined"
    #endif
#endif

///////////////////////////////////////////////////////////////////////////////

#ifndef SkNEW
    #define SkNEW(type_name)                new type_name
    #define SkNEW_ARGS(type_name, args)     new type_name args
    #define SkNEW_ARRAY(type_name, count)   new type_name[count]
    #define SkDELETE(obj)                   delete obj
    #define SkDELETE_ARRAY(array)           delete[] array
#endif

#ifndef SK_CRASH
#if 1   // set to 0 for infinite loop, which can help connecting gdb
    #define SK_CRASH() *(int *)(uintptr_t)0xbbadbeef = 0
#else
    #define SK_CRASH()  do {} while (true)
#endif
#endif

///////////////////////////////////////////////////////////////////////////////

#if defined(SK_SOFTWARE_FLOAT) && defined(SK_SCALAR_IS_FLOAT)
    // if this is defined, we convert floats to 2scompliment ints for compares
    #ifndef SK_SCALAR_SLOW_COMPARES
        #define SK_SCALAR_SLOW_COMPARES
    #endif
    #ifndef SK_USE_FLOATBITS
        #define SK_USE_FLOATBITS
    #endif
#endif

#ifdef SK_BUILD_FOR_WIN
    // we want lean_and_mean when we include windows.h
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
        #define WIN32_IS_MEAN_WAS_LOCALLY_DEFINED
    #endif

    #include <windows.h>

    #ifdef WIN32_IS_MEAN_WAS_LOCALLY_DEFINED
        #undef WIN32_LEAN_AND_MEAN
    #endif

    #ifndef SK_DEBUGBREAK
        #define SK_DEBUGBREAK(cond)     do { if (!(cond)) __debugbreak(); } while (false)
    #endif

    #ifndef SK_A32_SHIFT
        #define SK_A32_SHIFT 24
        #define SK_R32_SHIFT 16
        #define SK_G32_SHIFT 8
        #define SK_B32_SHIFT 0
    #endif

#elif defined(SK_BUILD_FOR_MAC)
    #ifndef SK_DEBUGBREAK
        #define SK_DEBUGBREAK(cond)     do { if (!(cond)) SK_CRASH(); } while (false)
    #endif
#else
    #ifdef SK_DEBUG
        #include <stdio.h>
        #ifndef SK_DEBUGBREAK
            #define SK_DEBUGBREAK(cond) do { if (cond) break; \
                SkDebugf("%s:%d: failed assertion \"%s\"\n", \
                __FILE__, __LINE__, #cond); SK_CRASH(); } while (false)
        #endif
    #endif
#endif

/*
 *  We check to see if the SHIFT value has already been defined.
 *  if not, we define it ourself to some default values. We default to OpenGL
 *  order (in memory: r,g,b,a)
 */

#ifndef SK_A32_SHIFT
    #if !defined(__QNXNTO__)
        #ifdef SK_CPU_BENDIAN
            #define SK_R32_SHIFT    24
            #define SK_G32_SHIFT    16
            #define SK_B32_SHIFT    8
            #define SK_A32_SHIFT    0
        #else
            #define SK_R32_SHIFT    0
            #define SK_G32_SHIFT    8
            #define SK_B32_SHIFT    16
            #define SK_A32_SHIFT    24
        #endif
    #else
        #define SK_B32_SHIFT    0
        #define SK_G32_SHIFT    8
        #define SK_R32_SHIFT    16
        #define SK_A32_SHIFT    24
    #endif
#endif

//  stdlib macros

#if 0
#if !defined(strlen) && defined(SK_DEBUG)
    extern size_t sk_strlen(const char*);
    #define strlen(s)   sk_strlen(s)
#endif
#ifndef sk_strcpy
    #define sk_strcpy(dst, src)     strcpy(dst, src)
#endif
#ifndef sk_strchr
    #define sk_strchr(s, c)         strchr(s, c)
#endif
#ifndef sk_strrchr
    #define sk_strrchr(s, c)        strrchr(s, c)
#endif
#ifndef sk_strcmp
    #define sk_strcmp(s, t)         strcmp(s, t)
#endif
#ifndef sk_strncmp
    #define sk_strncmp(s, t, n)     strncmp(s, t, n)
#endif
#ifndef sk_memcpy
    #define sk_memcpy(dst, src, n)  memcpy(dst, src, n)
#endif
#ifndef memmove
    #define memmove(dst, src, n)    memmove(dst, src, n)
#endif
#ifndef sk_memset
    #define sk_memset(dst, val, n)  memset(dst, val, n)
#endif
#ifndef sk_memcmp
    #define sk_memcmp(s, t, n)      memcmp(s, t, n)
#endif

#define sk_strequal(s, t)           (!sk_strcmp(s, t))
#define sk_strnequal(s, t, n)       (!sk_strncmp(s, t, n))
#endif

//////////////////////////////////////////////////////////////////////

#if defined(SK_BUILD_FOR_WIN32) || defined(SK_BUILD_FOR_MAC)
    #ifndef SkLONGLONG
        #ifdef SK_BUILD_FOR_WIN32
            #define SkLONGLONG  __int64
        #else
            #define SkLONGLONG  long long
        #endif
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SK_BUILD_FOR_WINCE
#include <string.h>
#include <stdlib.h>
#else
#define _CMNINTRIN_DECLARE_ONLY
#include "cmnintrin.h"
#endif

#if defined SK_DEBUG && defined SK_BUILD_FOR_WIN32
//#define _CRTDBG_MAP_ALLOC
#ifdef free
#undef free
#endif
#include <crtdbg.h>
#undef free

#ifdef SK_DEBUGx
#if defined(SK_SIMULATE_FAILED_MALLOC) && defined(__cplusplus)
    void * operator new(
        size_t cb,
        int nBlockUse,
        const char * szFileName,
        int nLine,
        int foo
        );
    void * operator new[](
        size_t cb,
        int nBlockUse,
        const char * szFileName,
        int nLine,
        int foo
        );
    void operator delete(
        void *pUserData,
        int, const char*, int, int
        );
    void operator delete(
        void *pUserData
        );
    void operator delete[]( void * p );
    #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__, 0)
#else
    #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif
    #define new DEBUG_CLIENTBLOCK
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#endif

#endif

