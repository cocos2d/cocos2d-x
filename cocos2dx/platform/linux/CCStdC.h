/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_STD_C_H__
#define __CC_STD_C_H__

#include "CCPlatformMacros.h"

#include <float.h>

// for math.h on win32 platform
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

    #if ! defined(_USE_MATH_DEFINES)
        #define _USE_MATH_DEFINES       // make M_PI can be use
    #endif

    #if ! defined(isnan)
        #define isnan   _isnan
    #endif

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE && defined(_TRANZDA_VM_))

    #if ! defined(_USE_MATH_DEFINES)
        #define _USE_MATH_DEFINES       // make M_PI can be use
    #endif

    #if ! defined(isnan)
        #define isnan   _isnan
    #endif

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE && defined(_TRANZDA_VM_)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

#include "TG3.h"

#endif  // CC_PLATFORM_WOPHONE

#include <math.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for MIN MAX and sys/time.h on win32 platform
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define MIN     min
#define MAX     max

// Structure timeval has define in winsock.h, include windows.h for it.
#include <Windows.h>

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int CC_DLL gettimeofday(struct timeval *, struct timezone *);

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_QNX)

#include <sys/time.h>


#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

// some function linux do not have
#define tanf tan
#define sqrtf sqrt
#define cosf cos
#define sinf sin

#endif

#endif  // CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)

#include <s3e.h>
#include <sys/time.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif  // CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)

#include <FSysSystemTime.h>

struct timeval
{
 	long tv_sec;		// seconds
 	long tv_usec;    // microSeconds
};

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};


int CC_DLL gettimeofday(struct timeval *, struct timezone *);

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#ifndef UINT_MAX
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#endif  // UINT_MAX

#endif  // CC_TARGET_PLATFORM == CC_PLATFORM_BADA

#endif  // __CC_STD_C_H__
