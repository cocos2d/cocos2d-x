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


#ifndef GrRefCnt_DEFINED
#define GrRefCnt_DEFINED

#include "GrTypes.h"
#include "GrNoncopyable.h"

/**
 *  Base class for reference counting. When an object is first instantiated,
 *  its reference count is 1. If the object may be null, use GrSafeRef() and
 *  GrSafeUnref().
 *
 *  It is an error (though only checked for in the debug build) to call unref()
 *  such that the reference count becomes 0.
 */
class GR_API GrRefCnt : GrNoncopyable {
public:
            GrRefCnt() : fRefCnt(1) {}
    virtual ~GrRefCnt() {
        GrAssert(1 == fRefCnt);
#if GR_DEBUG
        fRefCnt = 0;    // force validate() to trigger if called afterwards
#endif
    }

    int32_t refcnt() const { return fRefCnt; }

    void ref() const {
        GrAssert(fRefCnt > 0);
        ++fRefCnt;
    }

    void unref() const {
        GrAssert(fRefCnt > 0);
        if (1 == fRefCnt) {
            delete this;
        } else {
            --fRefCnt;
        }
    }

#if GR_DEBUG
    void validate() const {
        GrAssert(fRefCnt > 0);
    }
#else
    void validate() const {}
#endif

private:
    mutable int32_t fRefCnt;
};

///////////////////////////////////////////////////////////////////////////////

/**
 *  Call with instance/subclass of GrRefCnt. This does nothing if obj is null,
 *  but otherwise it calls ref().
 */
static inline void GrSafeRef(const GrRefCnt* obj) {
    if (obj) {
        obj->ref();
    }
}

/**
 *  Call with instance/subclass of GrRefCnt. This does nothing if obj is null,
 *  but otherwise it calls unref().
 */
static inline void GrSafeUnref(const GrRefCnt* obj) {
    if (obj) {
        obj->unref();
    }
}

/**
 *  Assigns src to dst, checking for NULLs in each, and correctly incrementing
 *  the reference count of src, and decrementing the reference count of dst
 */
template<typename T>
static inline void GrSafeAssign(T*& dst, T* src) {
    if (src) {
        src->ref();
    }
    if (dst) {
        dst->unref();
    }
    dst = src;
}

template<typename T>
static inline void GrSafeSetNull(T*& obj) {
    if (NULL != obj) {
        obj->unref();
        obj = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////

class GrAutoRef : GrNoncopyable {
public:
    GrAutoRef(GrRefCnt* obj) : fObj(obj) { GrSafeRef(obj); }
    ~GrAutoRef() { GrSafeUnref(fObj); }
private:
    GrRefCnt* fObj;
};

class GrAutoUnref : GrNoncopyable {
public:
    GrAutoUnref(GrRefCnt* obj) : fObj(obj) {}
    ~GrAutoUnref() { GrSafeUnref(fObj); }
private:
    GrRefCnt* fObj;
};

#endif

