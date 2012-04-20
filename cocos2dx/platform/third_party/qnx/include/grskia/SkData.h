/*
    Copyright 2011 Google Inc.

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


#ifndef SkData_DEFINED
#define SkData_DEFINED

#include "SkRefCnt.h"

/**
 *  SkData holds an immutable data buffer. Not only is the data immutable,
 *  but the actual ptr that is returned (by data() or bytes()) is guaranteed
 *  to always be the same for the life of this instance.
 */
class SkData : public SkRefCnt {
public:
    /**
     *  Returns the number of bytes stored.
     */
    size_t size() const { return fSize; }

    /**
     *  Returns the ptr to the data.
     */
    const void* data() const { return fPtr; }

    /**
     *  Like data(), returns a read-only ptr into the data, but in this case
     *  it is cast to uint8_t*, to make it easy to add an offset to it.
     */
    const uint8_t* bytes() const {
        return reinterpret_cast<const uint8_t*>(fPtr);
    }

    /**
     *  Helper to copy a range of the data into a caller-provided buffer.
     *  Returns the actual number of bytes copied, after clamping offset and
     *  length to the size of the data. If buffer is NULL, it is ignored, and
     *  only the computed number of bytes is returned.
     */
    size_t copyRange(size_t offset, size_t length, void* buffer) const;

    /**
     *  Function that, if provided, will be called when the SkData goes out
     *  of scope, allowing for custom allocation/freeing of the data.
     */
    typedef void (*ReleaseProc)(const void* ptr, size_t length, void* context);
    
    /**
     *  Create a new dataref by copying the specified data
     */
    static SkData* NewWithCopy(const void* data, size_t length);

    /**
     *  Create a new dataref, taking the data ptr as is, and using the
     *  releaseproc to free it. The proc may be NULL.
     */
    static SkData* NewWithProc(const void* data, size_t length,
                               ReleaseProc proc, void* context);

    /**
     *  Create a new dataref, reference the data ptr as is, and calling
     *  sk_free to delete it.
     */
    static SkData* NewFromMalloc(const void* data, size_t length);

    /**
     *  Create a new dataref using a subset of the data in the specified
     *  src dataref.
     */
    static SkData* NewSubset(const SkData* src, size_t offset, size_t length);

    /**
     *  Returns a new empty dataref (or a reference to a shared empty dataref).
     *  New or shared, the caller must see that unref() is eventually called.
     */
    static SkData* NewEmpty();

private:
    ReleaseProc fReleaseProc;
    void*       fReleaseProcContext;

    const void* fPtr;
    size_t      fSize;

    SkData(const void* ptr, size_t size, ReleaseProc, void* context);
    ~SkData();
};

/**
 *  Specialized version of SkAutoTUnref<SkData> for automatically unref-ing a
 *  SkData. If the SkData is null, data(), bytes() and size() will return 0.
 */
class SkAutoDataUnref : SkNoncopyable {
public:
    SkAutoDataUnref(SkData* data) : fRef(data) {
        if (data) {
            fData = data->data();
            fSize = data->size();
        } else {
            fData = NULL;
            fSize = 0;
        }
    }
    ~SkAutoDataUnref() {
        SkSafeUnref(fRef);
    }

    const void* data() const { return fData; }
    const uint8_t* bytes() const {
        return reinterpret_cast<const uint8_t*> (fData);
    }
    size_t size() const { return fSize; }
    SkData* get() const { return fRef; }

    void release() {
        if (fRef) {
            fRef->unref();
            fRef = NULL;
            fData = NULL;
            fSize = 0;
        }
    }

private:
    SkData*     fRef;
    const void* fData;
    size_t      fSize;
};

#endif
