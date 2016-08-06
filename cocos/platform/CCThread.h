/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#ifndef __CC_PLATFORM_THREAD_H__
#define __CC_PLATFORM_THREAD_H__
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/* On iOS, should create autorelease pool when create a new thread
 * and release it when the thread end.
 */

class CC_DLL ThreadHelper
{
public:

    /** Create an autorelease pool for objective-c codes.
     * @js NA
     * @lua NA
     */
    static void* createAutoreleasePool();
    
    /**
     * @js NA
     * @lua NA
    */
    static void releaseAutoreleasePool(void *autoreleasePool);
};

// end of platform group
/// @}

NS_CC_END

/// @endcond
#endif    // __CC_PLATFORM_THREAD_H__
