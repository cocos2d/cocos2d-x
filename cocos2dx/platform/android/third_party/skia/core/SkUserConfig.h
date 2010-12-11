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

#ifndef SkUserConfig_DEFINED
#define SkUserConfig_DEFINED

/*  SkTypes.h, the root of the public header files, does the following trick:
 
    #include "SkPreConfig.h"
    #include "SkUserConfig.h"
    #include "SkPostConfig.h"
 
    SkPreConfig.h runs first, and it is responsible for initializing certain
    skia defines.
 
    SkPostConfig.h runs last, and its job is to just check that the final
    defines are consistent (i.e. that we don't have mutually conflicting
    defines).
 
    SkUserConfig.h (this file) runs in the middle. It gets to change or augment
    the list of flags initially set in preconfig, and then postconfig checks
    that everything still makes sense.

    Below are optional defines that add, subtract, or change default behavior
    in Skia. Your port can locally edit this file to enable/disable flags as
    you choose, or these can be delared on your command line (i.e. -Dfoo).

    By default, this include file will always default to having all of the flags
    commented out, so including it will have no effect.
*/

///////////////////////////////////////////////////////////////////////////////

//
// ANDROID Specific changes - NO NOT CHECK BACK INTO code.google.com/p/skia
//

// do this build check for other tools that still read this header
#ifdef ANDROID
    #include <utils/misc.h>
#endif

#ifdef SK_BUILD_FOR_MAC
    #undef SK_BUILD_FOR_MAC
#endif
#define SK_BUILD_FOR_UNIX

/*  Scalars (the fractional value type in skia) can be implemented either as
    floats or 16.16 integers (fixed). Exactly one of these two symbols must be
    defined.
*/
#define SK_SCALAR_IS_FLOAT
#undef SK_SCALAR_IS_FIXED


/*  Somewhat independent of how SkScalar is implemented, Skia also wants to know
    if it can use floats at all. Naturally, if SK_SCALAR_IS_FLOAT is defined,
    then so muse SK_CAN_USE_FLOAT, but if scalars are fixed, SK_CAN_USE_FLOAT
    can go either way.
 */
#define SK_CAN_USE_FLOAT

/*  For some performance-critical scalar operations, skia will optionally work
    around the standard float operators if it knows that the CPU does not have
    native support for floats. If your environment uses software floating point,
    define this flag.
 */
//#define SK_SOFTWARE_FLOAT


/*  Skia has lots of debug-only code. Often this is just null checks or other
    parameter checking, but sometimes it can be quite intrusive (e.g. check that
    each 32bit pixel is in premultiplied form). This code can be very useful
    during development, but will slow things down in a shipping product.
 
    By default, these mutually exclusive flags are defined in SkPreConfig.h,
    based on the presence or absence of NDEBUG, but that decision can be changed
    here.
 */
//#define SK_DEBUG
//#define SK_RELEASE


/*  If, in debugging mode, Skia needs to stop (presumably to invoke a debugger)
    it will call SK_CRASH(). If this is not defined it, it is defined in
    SkPostConfig.h to write to an illegal address
 */
//#define SK_CRASH() *(int *)(uintptr_t)0 = 0


/*  preconfig will have attempted to determine the endianness of the system,
    but you can change these mutually exclusive flags here.
 */
#if __BYTE_ORDER == __BIG_ENDIAN
    #define SK_CPU_BENDIAN
    #undef  SK_CPU_LENDIAN
#else
    #define SK_CPU_LENDIAN
    #undef  SK_CPU_BENDIAN
#endif


/*  Some compilers don't support long long for 64bit integers. If yours does
    not, define this to the appropriate type.
 */
#define SkLONGLONG int64_t


/*  Some envorinments do not suport writable globals (eek!). If yours does not,
    define this flag.
 */
//#define SK_USE_RUNTIME_GLOBALS


/*  To write debug messages to a console, skia will call SkDebugf(...) following
    printf conventions (e.g. const char* format, ...). If you want to redirect
    this to something other than printf, define yours here
 */
#define SkDebugf(...) Android_SkDebugf(__FILE__, __LINE__, \
                                        __FUNCTION__, __VA_ARGS__)
void Android_SkDebugf(const char* file, int line, 
                      const char* function, const char* format, ...);


/*  If SK_DEBUG is defined, then you can optionally define SK_SUPPORT_UNITTEST
    which will run additional self-tests at startup. These can take a long time,
    so this flag is optional.
 */
#ifdef SK_DEBUG
    #define SK_SUPPORT_UNITTEST
#endif

#endif

