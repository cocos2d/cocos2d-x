/****************************************************************************

Copyright (c) 2010-2014 cocos2d-x.org
Copyright (c) 2013-2014 Martell Malone < martell malone at gmail dot com >
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

#include "platform/CCPlatformMacros.h"
#include <float.h>

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

// for MIN MAX and sys/time.h on win32 platform

#define MIN     min
#define MAX     max

#if _MSC_VER >= 1600
    #include <stdint.h>
#else
    #include "./compat/stdint.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//#include "winrtsock.h" //this will replace windows include and timeval struct below
#include <Windows.h>
#undef timeval
struct timeval
{
         long tv_sec;                // seconds
         long tv_usec;    // microSeconds
};
#else
#include <WinSock2.h>
#endif

#ifndef _TIME_ZONE_DEFINED
#define _TIME_ZONE_DEFINED
struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};
#endif

int CC_DLL gettimeofday(struct timeval *, struct timezone *);

#endif  // __CC_STD_C_H__

