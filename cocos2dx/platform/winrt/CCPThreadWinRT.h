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

#include "platform/CCPlatformMacros.h"

#include <Windows.h>
#include <thread>
#include <functional>
#include <mutex>
#include <memory>

NS_CC_BEGIN

typedef std::shared_ptr<std::thread>  pthread_t;
typedef std::mutex pthread_mutex_t;
typedef int pthread_cond_t;

typedef struct  
{
    int foo;
} pthread_attr_t;


#define pthread_cond_wait(x, y)

void pthread_mutex_init(pthread_mutex_t* m, void* attributes);

int pthread_mutex_lock(pthread_mutex_t* m);

int pthread_mutex_unlock(pthread_mutex_t* m);

void pthread_mutex_destroy(pthread_mutex_t* m);

int pthread_attr_init(pthread_attr_t *attr);

template<class T>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, T start, void *arg)
{
    std::shared_ptr<std::thread> t(new std::thread(start));
    (*thread).swap(t);
    return 0;
}

int pthread_detach(pthread_t thread);
int pthread_join(pthread_t thread, void** ret);

void pthread_exit(void *value_ptr);

void Sleep(DWORD dwMilliseconds);


#define pthread_cond_destroy(x)
#define pthread_cond_signal(x)
#define pthread_cond_init(x, y)




NS_CC_END

#endif // __CCPTHREADWINRT_H__
