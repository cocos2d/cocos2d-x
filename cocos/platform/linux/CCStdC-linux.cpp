/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#include "CCStdC.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

int CC_DLL gettimeofday(struct timeval * val, struct timezone *)
{
    if (val)
    {
        SYSTEMTIME wtm;
        GetLocalTime(&wtm);

        struct tm tTm;
        tTm.tm_year     = wtm.wYear - 1900;
        tTm.tm_mon      = wtm.wMonth - 1;
        tTm.tm_mday     = wtm.wDay;
        tTm.tm_hour     = wtm.wHour;
        tTm.tm_min      = wtm.wMinute;
        tTm.tm_sec      = wtm.wSecond;
        tTm.tm_isdst    = -1;

        val->tv_sec     = (long)mktime(&tTm);       // time_t is 64-bit on win32
        val->tv_usec    = wtm.wMilliseconds * 1000;
    }
    return 0;
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)

using namespace Osp::System;

int CC_DLL gettimeofday(struct timeval * val, struct timezone *)
{
    if (val)
    {
    	long long curTick = 0;
    	SystemTime::GetTicks(curTick);
    	unsigned int ms = curTick;
    	val->tv_sec = ms / 1000;
    	val->tv_usec = (ms % 1000) * 1000;
    }
    return 0;
}

#endif  // CC_PLATFORM_WIN32

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
