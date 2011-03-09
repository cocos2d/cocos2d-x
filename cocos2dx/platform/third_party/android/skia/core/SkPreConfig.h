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

#ifndef SkPreConfig_DEFINED
#define SkPreConfig_DEFINED

//////////////////////////////////////////////////////////////////////

#if !defined(SK_BUILD_FOR_PALM) && !defined(SK_BUILD_FOR_WINCE) && !defined(SK_BUILD_FOR_WIN32) && !defined(SK_BUILD_FOR_SYMBIAN) && !defined(SK_BUILD_FOR_UNIX) && !defined(SK_BUILD_FOR_MAC) && !defined(SK_BUILD_FOR_SDL)

    #if defined(PALMOS_SDK_VERSION)
        #define SK_BUILD_FOR_PALM
    #elif defined(UNDER_CE)
        #define SK_BUILD_FOR_WINCE
    #elif defined(WIN32)
        #define SK_BUILD_FOR_WIN32
    #elif defined(__SYMBIAN32__)
        #define SK_BUILD_FOR_WIN32
    #elif defined(linux)
        #define SK_BUILD_FOR_UNIX
    #else
        #define SK_BUILD_FOR_MAC
    #endif

#endif

//////////////////////////////////////////////////////////////////////

#if !defined(SK_DEBUG) && !defined(SK_RELEASE)
    #ifdef NDEBUG
        #define SK_RELEASE
    #else
        #define SK_DEBUG
    #endif
#endif

//////////////////////////////////////////////////////////////////////

#if !defined(SK_RESTRICT)
//    #define SK_RESTRICT __restrict__
#endif

//////////////////////////////////////////////////////////////////////

#if !defined(SK_SCALAR_IS_FLOAT) && !defined(SK_SCALAR_IS_FIXED)
    #define SK_SCALAR_IS_FLOAT
    #define SK_CAN_USE_FLOAT
#endif

//////////////////////////////////////////////////////////////////////

#if !defined(SK_CPU_BENDIAN) && !defined(SK_CPU_LENDIAN)
    #if defined (__ppc__) || defined(__ppc64__)
        #define SK_CPU_BENDIAN
    #else
        #define SK_CPU_LENDIAN
    #endif
#endif

//////////////////////////////////////////////////////////////////////

#if (defined(__arm__) && !defined(__thumb__)) || defined(SK_BUILD_FOR_BREW) || defined(SK_BUILD_FOR_WINCE) || (defined(SK_BUILD_FOR_SYMBIAN) && !defined(__MARM_THUMB__))
    /* e.g. the ARM instructions have conditional execution, making tiny branches cheap */
    #define SK_CPU_HAS_CONDITIONAL_INSTR
#endif

#endif

