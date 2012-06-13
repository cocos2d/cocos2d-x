/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#ifndef SkTRelay_DEFINED
#define SkTRelay_DEFINED

#include "SkRefCnt.h"

/**
 *  Similar to a weakptr in java, a Relay allows for a back-ptr to an
 *  object to be "safe", without using a hard reference-count.
 *
 *  Typically, the target creates a Relay with a pointer to itself. Whenever it
 *  wants to have another object maintain a safe-ptr to it, it gives them a
 *  Relay, which they ref()/unref(). Through the Relay each external object can
 *  retrieve a pointer to the Target. However, when the Target goes away, it
 *  clears the Relay pointer to it (relay->set(NULL)) and then unref()s the
 *  Relay. The other objects still have a ref on the Relay, but now when they
 *  call get() the receive a NULL.
 */
template <template T> class SkTRelay : public SkRefCnt {
public:
    SkTRelay(T* ptr) : fPtr(ptr) {}

    // consumers call this
    T* get() const { return fPtr; }

    // producer calls this
    void set(T* ptr) { fPtr = ptr; }

    void clear() { this->set(NULL); }

private:
    T* fPtr;
};

#endif
