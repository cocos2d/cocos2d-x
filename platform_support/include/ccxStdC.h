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

#ifndef __CCX_STD_C_H__
#define __CCX_STD_C_H__

#include "ccxMacros.h"

#include <float.h>

// for math.h on win32 platform
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)

    #if ! defined(_USE_MATH_DEFINES)
        #define _USE_MATH_DEFINES       // make M_PI can be use
    #endif

    #if ! defined(isnan)
        #define isnan   _isnan
    #endif

#endif  // CCX_PLATFORM_WIN32
#include <math.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for sys/time.h on win32 platform
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)

#ifndef _WINSOCKAPI_    // struct timeval has define in winsock.h, no need redefine
struct timeval
{
    long tv_sec; /*second*/
    long tv_usec; /*microsecond*/
};
#endif  // _WINSOCKAPI_

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int CCX_DLL_PS gettimeofday(struct timeval *, struct timezone *);

#endif  // CCX_PLATFORM_WIN32

#endif  // __CCX_STD_C_H__