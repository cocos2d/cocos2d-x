/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
 Author: Justin Graham (https://github.com/mannewalis)
 
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

#ifndef CC_ALLOCATOR_MUTEX_H
#define CC_ALLOCATOR_MUTEX_H
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformMacros.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#include "pthread.h"
#define MUTEX pthread_mutex_t
#define MUTEX_INIT(m) \
    pthread_mutexattr_t mta; \
    pthread_mutexattr_init(&mta); \
    pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE); \
    pthread_mutex_init(&m, &mta)
#define MUTEX_LOCK(m) \
    pthread_mutex_lock(&m);
#define MUTEX_UNLOCK(m) \
    pthread_mutex_unlock(&m);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#include "windows.h"
#define MUTEX HANDLE
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#define MUTEX_INIT(m) \
    m = CreateMutex(0, FALSE, 0)
#define MUTEX_LOCK(m) \
    WaitForSingleObject(m, INFINITE)
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#define MUTEX_INIT(m) \
	m = CreateMutexEx(NULL,FALSE,0,NULL);
#define MUTEX_LOCK(m) \
    WaitForSingleObjectEx(m, INFINITE, false)
#endif
#define MUTEX_UNLOCK(m) \
    ReleaseMutex(m)
#else
#message "Unsupported platform for AllocatorMutex, Locking semantics will not be supported"
#define MUTEX
#define MUTEX_INIT(...)
#define MUTEX_LOCK(...)
#define MUTEX_UNLOCK(...)
#endif

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// so we cannot use std::mutex because it allocates memory
// which causes an infinite loop of death and exceptions.
class AllocatorMutex
{
public:
    
    AllocatorMutex()
    {
        MUTEX_INIT(_mutex);
    }
    
    void lock()
    {
        MUTEX_LOCK(_mutex);
    }
    
    void unlock()
    {
        MUTEX_UNLOCK(_mutex);
    }
    
protected:
    
    MUTEX _mutex;
};

#define LOCK(m)   m.lock()
#define UNLOCK(m) m.unlock()

// @param implementation that provides a mutex with locking semantics.
struct locking_semantics
{
    AllocatorMutex _mutex;
    CC_ALLOCATOR_INLINE void lock()
    {
        LOCK(_mutex);
    }
    CC_ALLOCATOR_INLINE void unlock()
    {
        UNLOCK(_mutex);
    }
};

// @param implementation that provides lockless semantics that should optimize away.
struct lockless_semantics
{
    CC_ALLOCATOR_INLINE void lock() {}
    CC_ALLOCATOR_INLINE void unlock() {}
};

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_MUTEX_H
