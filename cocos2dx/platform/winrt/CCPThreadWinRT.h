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
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

NS_CC_BEGIN
    
#define pthread_mutex_t std::mutex
#define pthread_cond_t std::condition_variable
#define pthread_t std::thread*

void pthread_cond_wait(pthread_cond_t *condition, pthread_mutex_t *mutex);

#define pthread_cond_destroy(x)
#define pthread_exit(x)
#define pthread_cond_signal(x) ((std::condition_variable*)x)->notify_one()
#define pthread_cond_init(x, y)

#define pthread_detach(x) ((std::thread*)x)->detach()

#define pthread_attr_t int
#define pthread_attr_init(x)


#define pthread_mutex_init(m, attributes) 
#define pthread_mutex_lock(m) ((std::mutex*)m)->lock()
#define pthread_mutex_unlock(m) ((std::mutex*)m)->unlock()
#define pthread_mutex_destroy(m) 

int pthread_create(pthread_t *threadInstance,pthread_attr_t* attr, void *(*start) (void *), void *arg);
#define pthread_join(ThreadInstance,ret) if(ThreadInstance->joinable()) ThreadInstance->join();

NS_CC_END

#endif // __CCPTHREADWINRT_H__
