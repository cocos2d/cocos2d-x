/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8


#include "CCPlatformMacros.h"
#include <float.h>
#include <BaseTsd.h>

#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

// for math.h on win32 platform

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if !defined(isnan)
    #define isnan   _isnan
#endif

#ifndef snprintf
#define snprintf _snprintf
#endif

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef M_PI
  #define M_PI      3.14159265358
#endif
#ifndef M_PI_2
  #define M_PI_2    1.57079632679
#endif


// for MIN MAX and sys/time.h on win32 platform
#ifndef NOMINMAX
  #define NOMINMAX
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#include <stdint.h>

// Structure timeval has define in winsock.h, include windows.h for it.
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
#define _WINSOCKAPI_
#include <WinSock2.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#include <Windows.h>

#undef timeval
struct timeval
{
	long tv_sec;		// seconds
	long tv_usec;    // microSeconds
};
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WP8

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int CC_DLL gettimeofday(struct timeval *, struct timezone *);

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8

#endif  // __CC_STD_C_H__

