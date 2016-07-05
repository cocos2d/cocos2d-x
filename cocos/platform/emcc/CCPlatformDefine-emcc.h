/****************************************************************************
Copyright (c) 2011      Laschweinski
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

#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include <string.h>

#define CC_DLL 

#include <assert.h>
#define CC_ASSERT(cond)    assert(cond)
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/*
#include <time.h>
#define TIME_START(var) clock_t var = clock(); clock_t var##_mark = var
#define TIME_END_MARK(var) ((double)(clock() - var##_mark)/CLOCKS_PER_SEC)
#define TIME_END(var) ((double)(clock() - var)/CLOCKS_PER_SEC)

#define TIME_LOG(var, desc) do { printf(#var " " desc " time %f s\n", TIME_END_MARK(var)); var##_mark = clock(); } while(0)
#define TIME_TOTAL_LOG(var, desc) printf(#var " " desc " total time %f s\n", TIME_END(var))
*/

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#endif /* __CCPLATFORMDEFINE_H__*/
