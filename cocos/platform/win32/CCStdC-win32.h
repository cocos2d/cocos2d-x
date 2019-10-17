/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include <BaseTsd.h>
#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

#include "platform/CCPlatformMacros.h"
#include <float.h>

// for math.h on win32 platform
#ifndef __MINGW32__

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if _MSC_VER < 1800
#if !defined(isnan)
    #define isnan   _isnan
#endif
#endif

#if _MSC_VER < 1900
#ifndef snprintf
#define snprintf _snprintf
#endif
#endif

#endif // __MINGW32__

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
#ifdef __MINGW32__
#include <sys/time.h>
#endif // __MINGW32__

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX


#if _MSC_VER >= 1600 || defined(__MINGW32__)
    #include <stdint.h>
#else
    #include "platform/win32/compat/stdint.h"
#endif

#define _WINSOCKAPI_
#ifndef NOMINMAX
  #define NOMINMAX
#endif

#ifndef __MINGW32__

#include <WinSock2.h>
// Structure timeval has define in winsock.h, include windows.h for it.
#include <Windows.h>

NS_CC_BEGIN

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int CC_DLL gettimeofday(struct timeval *, struct timezone *);

NS_CC_END

#else

#undef _WINSOCKAPI_
#include <winsock2.h>
#include <Windows.h>

// Conflicted with math.h isnan
#include <cmath>
using std::isnan;

inline int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count,
                 const char *format, va_list argptr) {
  return vsnprintf(buffer, sizeOfBuffer, format, argptr);
}

#ifndef __clang__
inline errno_t strcpy_s(char *strDestination, size_t numberOfElements,
        const char *strSource) {
    strcpy(strDestination, strSource);
    return 0;
}
#endif
#endif // __MINGW32__

// Conflicted with ParticleSystem::PositionType::RELATIVE, so we need to undef it.
#ifdef RELATIVE
#undef RELATIVE
#endif

// Conflicted with CCBReader::SizeType::RELATIVE and CCBReader::ScaleType::RELATIVE, so we need to undef it.
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif

// Conflicted with HttpRequest::Type::DELETE, so we need to undef it.
#ifdef DELETE
#undef DELETE
#endif

#undef min
#undef max

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#endif  // __CC_STD_C_H__



