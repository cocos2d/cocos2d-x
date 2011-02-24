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

#ifndef SkThread_platform_DEFINED
#define SkThread_platform_DEFINED

#ifdef ANDROID

#include <utils/threads.h>
#include <utils/Atomic.h>

#define sk_atomic_inc(addr)     android_atomic_inc(addr)
#define sk_atomic_dec(addr)     android_atomic_dec(addr)

class SkMutex : android::Mutex {
public:
    // if isGlobal is true, then ignore any errors in the platform-specific
    // destructor
    SkMutex(bool isGlobal = true) {}
    ~SkMutex() {}

    void    acquire() { this->lock(); }
    void    release() { this->unlock(); }
};

#else

/** Implemented by the porting layer, this function adds 1 to the int specified
    by the address (in a thread-safe manner), and returns the previous value.
*/
int32_t sk_atomic_inc(int32_t* addr);
/** Implemented by the porting layer, this function subtracts 1 to the int
    specified by the address (in a thread-safe manner), and returns the previous
    value.
*/
int32_t sk_atomic_dec(int32_t* addr);

class SkMutex {
public:
    // if isGlobal is true, then ignore any errors in the platform-specific
    // destructor
    SkMutex(bool isGlobal = true);
    ~SkMutex();

    void    acquire();
    void    release();

private:
    bool fIsGlobal;
    enum {
        kStorageIntCount = 12
    };
    uint32_t    fStorage[kStorageIntCount];
};

#endif

#endif
