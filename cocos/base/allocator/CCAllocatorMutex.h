
#ifndef CC_ALLOCATOR_MUTEX_H
#define CC_ALLOCATOR_MUTEX_H

/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
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

#include "base/ccConfig.h"
#include "platform/CCPlatformMacros.h"
#include "base/allocator/CCAllocatorGlobal.h"
#include "pthread.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// so we cannot use std::mutex because it allocates memory
// which causes an infinite loop of death and exceptions.
class AllocatorMutex
{
public:
    
    AllocatorMutex()
    {
        pthread_mutexattr_t mta;
        pthread_mutexattr_init(&mta);
        pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&_mutex, &mta);
    }
    
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    
protected:
    
    pthread_mutex_t _mutex;
};

#define LOCK(m)   m.lock()
#define UNLOCK(m) m.unlock()

NS_CC_ALLOCATOR_END
NS_CC_END

#endif//CC_ALLOCATOR_MUTEX_H
