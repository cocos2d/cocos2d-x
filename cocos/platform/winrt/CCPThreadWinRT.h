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

#ifndef __CCPTHREADWINRT_H__
#define __CCPTHREADWINRT_H__


#include "base/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "base/CCPlatformMacros.h"

#include <Windows.h>

NS_CC_BEGIN

typedef HANDLE pthread_t;
typedef HANDLE pthread_mutex_t;
typedef int pthread_cond_t;
#define pthread_cond_wait(x, y)

void pthread_mutex_init(pthread_mutex_t* m, void* attributes);

int pthread_mutex_lock(pthread_mutex_t* m);

int pthread_mutex_unlock(pthread_mutex_t* m);

void pthread_mutex_destroy(pthread_mutex_t* m);

#define pthread_cond_destroy(x)
#define pthread_cond_signal(x)
#define pthread_cond_init(x, y)

NS_CC_END


#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif // __CCPTHREADWINRT_H__
