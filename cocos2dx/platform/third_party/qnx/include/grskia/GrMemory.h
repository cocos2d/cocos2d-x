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


#ifndef GrMemory_DEFINED
#define GrMemory_DEFINED

#include "GrNoncopyable.h"

class GrAutoMalloc : GrNoncopyable {
public:
    GrAutoMalloc() : fPtr(NULL), fAllocatedBytes(0){
    }

    GrAutoMalloc(size_t bytes) : fPtr(GrMalloc(bytes)), fAllocatedBytes(bytes) {}
    ~GrAutoMalloc() { GrFree(fPtr); }

    /**
     *  Return the allocated memory, or NULL if it has already been freed or
     *  detached.
     */
    void* get() const { return fPtr; }

    size_t size() const { return fAllocatedBytes; }

    /**
     *  transfer ownership of the memory to the caller. It must be freed with
     *  a call to GrFree()
     */
    void* detach() {
        void* ptr = fPtr;
        fPtr = NULL;    // we no longer own the block
        fAllocatedBytes = 0;
        return ptr;
    }

    /**
     *  Reallocates to a new size. May or may not call malloc. The contents
     *  are not preserved. If growOnly is true it will never reduce the
     *  allocated size.
     */
    void* realloc(size_t newSize, bool growOnly = false) {
        bool alloc;
        if (growOnly) {
            alloc = newSize > fAllocatedBytes;
        } else {
            alloc = newSize != fAllocatedBytes;
        }
        if (alloc) {
            GrFree(fPtr);
            fPtr = newSize ? GrMalloc(newSize) : NULL;
            fAllocatedBytes = newSize;
        }
        GrAssert(fAllocatedBytes >= newSize);
        GR_DEBUGCODE(memset(fPtr, 0xEF, fAllocatedBytes));
        return fPtr;
    }

    /**
     *  free the block now. get() will now return NULL
     */
    void free() {
        GrFree(fPtr);
        fPtr = NULL;
        fAllocatedBytes = 0;
    }

private:
    void* fPtr;
    size_t fAllocatedBytes;
};

/**
 *  Variant of GrAutoMalloc with a compile-time specified byte size that is
 *  pre-allocated in the class object, avoiding a call to to GrMalloc if
 *  possible.
 */
template <size_t SIZE> class GrAutoSMalloc : GrNoncopyable {
public:
    GrAutoSMalloc() {
        fPtr = fStorage;
        fAllocatedBytes = SIZE;
    }

    explicit GrAutoSMalloc(size_t bytes) {
        if (bytes > SIZE) {
            fPtr = GrMalloc(bytes);
            fAllocatedBytes = bytes;
        } else {
            fPtr = fStorage;
            fAllocatedBytes = SIZE;
        }
    }

    ~GrAutoSMalloc() {
        if (fPtr != (void*)fStorage) {
            GrFree(fPtr);
        }
    }

    /**
     *  Return the allocated memory, or NULL if it has already been freed or
     *  detached.
     */
    void* get() const { return fPtr; }

    /**
     *  Reallocates to a new size. May or may not call malloc. The contents
     *  are not preserved. If growOnly is true it will never reduce the
     *  allocated size.
     */
    void* realloc(size_t newSize, bool growOnly = false) {
        if (newSize <= SIZE) {
            if (NULL == fPtr) {
                fPtr = fStorage;
                fAllocatedBytes = SIZE;
            } else if (!growOnly && fPtr != (void*)fStorage) {
                GrFree(fPtr);
                fPtr = fStorage;
                fAllocatedBytes = SIZE;
            }
        } else if ((newSize > fAllocatedBytes) ||
                   (!growOnly && newSize < (fAllocatedBytes >> 1))) {
            if (NULL != fPtr && fPtr != (void*)fStorage) {
                GrFree(fPtr);
            }
            fPtr = GrMalloc(newSize);
            fAllocatedBytes = newSize;
        }
        GrAssert(fAllocatedBytes >= newSize);
        GrAssert((fPtr == fStorage) == (fAllocatedBytes == SIZE));
        GR_DEBUGCODE(memset(fPtr, 0xEF, fAllocatedBytes));
        return fPtr;
    }

    /**
     *  free the block now. get() will now return NULL
     */
    void free() {
        if (fPtr != (void*)fStorage) {
            GrFree(fPtr);
        }
        fAllocatedBytes = 0;
        fPtr = NULL;
    }

private:
    void*    fPtr;
    uint32_t fAllocatedBytes;
    uint32_t fStorage[GrALIGN4(SIZE) >> 2];
};

/**
 *  Variant of GrAutoMalloc with a compile-time specified byte size that is
 *  pre-allocated in the class object, avoiding a call to to GrMalloc if
 *  possible.
 */
template <int COUNT, typename T>
class GrAutoSTMalloc : public GrAutoSMalloc<COUNT * sizeof(T)> {
public:
    GrAutoSTMalloc(int count) : GrAutoSMalloc<COUNT * sizeof(T)>(count * sizeof(T)) {}

    operator T*() { return (T*)this->get(); }
};


#endif

