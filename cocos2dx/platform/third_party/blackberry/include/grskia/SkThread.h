/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkThread_DEFINED
#define SkThread_DEFINED

#include "SkTypes.h"
#include "SkThread_platform.h"

/****** SkThread_platform needs to define the following...

int32_t sk_atomic_inc(int32_t*);
int32_t sk_atomic_dec(int32_t*);

class SkMutex {
public:
    SkMutex();
    ~SkMutex();

    void    acquire();
    void    release();
};

****************/

class SkAutoMutexAcquire : SkNoncopyable {
public:
    explicit SkAutoMutexAcquire(SkMutex& mutex) : fMutex(&mutex)
    {
        SkASSERT(fMutex != NULL);
        mutex.acquire();
    }
    /** If the mutex has not been release, release it now.
    */
    ~SkAutoMutexAcquire()
    {
        if (fMutex)
            fMutex->release();
    }
    /** If the mutex has not been release, release it now.
    */
    void release()
    {
        if (fMutex)
        {
            fMutex->release();
            fMutex = NULL;
        }
    }
        
private:
    SkMutex* fMutex;
};

#endif
