/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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


#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "platform/CCStdC.h"

#ifndef __MINGW32__

NS_CC_BEGIN

int gettimeofday(struct timeval * val, struct timezone *)
{
    if (val)
    {
        LARGE_INTEGER liTime, liFreq;
        QueryPerformanceFrequency( &liFreq );
        QueryPerformanceCounter( &liTime );
        val->tv_sec     = (long)( liTime.QuadPart / liFreq.QuadPart );
        val->tv_usec    = (long)( liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0 );
    }
    return 0;
}

NS_CC_END

#endif // __MINGW32__

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
