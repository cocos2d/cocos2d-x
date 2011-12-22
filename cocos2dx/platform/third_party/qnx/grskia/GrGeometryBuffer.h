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

#ifndef GrGeometryBuffer_DEFINED
#define GrGeometryBuffer_DEFINED

#include "GrResource.h"

class GrGpu;

/**
 * Parent class for vertex and index buffers
 */
class GrGeometryBuffer : public GrResource {
public:
    /**
     * Retrieves the size of the buffer
     *
     * @return the size of the buffer in bytes
     */
    size_t size() const { return fSizeInBytes; }

    /**
     *Retrieves whether the buffer was created with the dynamic flag
     *
     * @return true if the buffer was created with the dynamic flag
     */
    bool dynamic() const { return fDynamic; }

    /**
     * Locks the buffer to be written by the CPU.
     *
     * The previous content of the buffer is invalidated. It is an error
     * to draw from the buffer while it is locked. It is an error to call lock
     * on an already locked buffer.
     *
     * @return a pointer to the data or NULL if the lock fails.
     */
    virtual void* lock() = 0;

    /**
     * Returns the same ptr that lock() returned at time of lock or NULL if the
     * is not locked.
     *
     * @return ptr to locked buffer data or undefined if buffer is not locked.
     */
    virtual void* lockPtr() const = 0;

    /**
     * Unlocks the buffer.
     *
     * The pointer returned by the previous lock call will no longer be valid.
     */
    virtual void unlock() = 0;

    /**
     Queries whether the buffer has been locked.

     @return true if the buffer is locked, false otherwise.
     */
    virtual bool isLocked() const = 0;

    /**
     * Updates the buffer data.
     *
     * The size of the buffer will be preserved. The src data will be
     * placed at the begining of the buffer and any remaining contents will
     * be undefined.
     *
     * @return returns true if the update succeeds, false otherwise.
     */
    virtual bool updateData(const void* src, size_t srcSizeInBytes) = 0;

    /**
     * Updates a portion of the buffer data.
     *
     * The contents of the buffer outside the update region are preserved.
     *
     * @return returns true if the update succeeds, false otherwise.
     */
    virtual bool updateSubData(const void* src,
                               size_t srcSizeInBytes,
                               size_t offset) = 0;
protected:
    GrGeometryBuffer(GrGpu* gpu, size_t sizeInBytes, bool dynamic)
        : INHERITED(gpu)
        , fSizeInBytes(sizeInBytes)
        , fDynamic(dynamic) {}

private:
    size_t   fSizeInBytes;
    bool     fDynamic;

    typedef GrResource INHERITED;
};

#endif
