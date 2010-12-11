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

#ifndef SkRefCnt_DEFINED
#define SkRefCnt_DEFINED

#include "SkThread.h"

/** \class SkRefCnt

    SkRefCnt is the base class for objects that may be shared by multiple
    objects. When a new owner wants a reference, it calls ref(). When an owner
    wants to release its reference, it calls unref(). When the shared object's
    reference count goes to zero as the result of an unref() call, its (virtual)
    destructor is called. It is an error for the destructor to be called
    explicitly (or via the object going out of scope on the stack or calling
    delete) if getRefCnt() > 1.
*/
class SkRefCnt : SkNoncopyable {
public:
    /** Default construct, initializing the reference count to 1.
    */
    SkRefCnt() : fRefCnt(1) {}

    /**  Destruct, asserting that the reference count is 1.
    */
    virtual ~SkRefCnt() { SkASSERT(fRefCnt == 1); }

    /** Return the reference count.
    */
    int32_t getRefCnt() const { return fRefCnt; }

    /** Increment the reference count. Must be balanced by a call to unref().
    */
    void ref() const {
        SkASSERT(fRefCnt > 0);
        sk_atomic_inc(&fRefCnt);
    }

    /** Decrement the reference count. If the reference count is 1 before the
        decrement, then call delete on the object. Note that if this is the
        case, then the object needs to have been allocated via new, and not on
        the stack.
    */
    void unref() const {
        SkASSERT(fRefCnt > 0);
        if (sk_atomic_dec(&fRefCnt) == 1) {
            fRefCnt = 1;    // so our destructor won't complain
            SkDELETE(this);
        }
    }
    
    /** Helper version of ref(), that first checks to see if this is not null.
        If this is null, then do nothing.
    */
    void safeRef() const {
        if (this) {
            this->ref();
        }
    }

    /** Helper version of unref(), that first checks to see if this is not null.
        If this is null, then do nothing.
    */
    void safeUnref() const {
        if (this) {
            this->unref();
        }
    }

private:
    mutable int32_t fRefCnt;
};

/** \class SkAutoUnref

    SkAutoUnref is a stack-helper class that will automatically call unref() on
    the object it points to when the SkAutoUnref object goes out of scope.
    If obj is null, do nothing.
*/
class SkAutoUnref : SkNoncopyable {
public:
    SkAutoUnref(SkRefCnt* obj) : fObj(obj) {}
    ~SkAutoUnref();

    SkRefCnt*   get() const { return fObj; }

    /** If the hosted object is null, do nothing and return false, else call
        ref() on it and return true
    */
    bool        ref();

    /** If the hosted object is null, do nothing and return false, else call
        unref() on it, set its reference to null, and return true
    */
    bool        unref();

    /** If the hosted object is null, do nothing and return NULL, else call
        unref() on it, set its reference to null, and return the object
    */
    SkRefCnt*   detach();

private:
    SkRefCnt*   fObj;
};

///////////////////////////////////////////////////////////////////////////////

/** Helper macro to safely assign one SkRefCnt[TS]* to another, checking for
    null in on each side of the assignment, and ensuring that ref() is called
    before unref(), in case the two pointers point to the same object.
*/
#define SkRefCnt_SafeAssign(dst, src)   \
    do {                                \
        if (src) src->ref();            \
        if (dst) dst->unref();          \
        dst = src;                      \
    } while (0)


/** Check if the argument is non-null, and if so, call obj->ref()
 */
template <typename T> static inline void SkSafeRef(T* obj) {
    if (obj) {
        obj->ref();
    }
}

/** Check if the argument is non-null, and if so, call obj->unref()
 */
template <typename T> static inline void SkSafeUnref(T* obj) {
    if (obj) {
        obj->unref();
    }
}

#endif

