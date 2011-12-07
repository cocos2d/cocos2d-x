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


#ifndef GrVertexBufferAllocPool_DEFINED
#define GrVertexBufferAllocPool_DEFINED

#include "GrNoncopyable.h"
#include "GrTDArray.h"
#include "GrTArray.h"

class GrVertexBuffer;
class GrGpu;

/**
 * A pool of vertices in vertex buffers tied to a GrGpu.
 *
 * The pool has an alloc() function that returns a pointer into a locked
 * vertex buffer. A client can release() if it has over-allocated.
 *
 * At creation time a minimum VB size can be specified. Additionally,
 * a number of vertex buffers to preallocate can be specified. These will
 * be allocated at the min size and kept until the pool is destroyed.
 */
class GrVertexBufferAllocPool : GrNoncopyable {
public:
    /**
     * Constructor
     *
     * @param gpu               The GrGpu used to create the vertex buffers.
     * @param bufferSize        The size of created VBs (unless an alloc request
     *                          exceeds this size in which case a larger VB is
     *                          created). This value is clamped to some
     *                          reasonable minimum.
     * @param preallocBufferCnt The pool will allocate this number of VBs at
     *                          bufferSize and keep them until it is destroyed.
     */
     GrVertexBufferAllocPool(GrGpu* gpu,
                             size_t   bufferSize = 0,
                             int preallocBufferCnt = 0);
    ~GrVertexBufferAllocPool();

    /**
     * Ensures all VBs are unlocked. Call before using to draw.
     */
    void unlock();

    /**
     *  Frees all vertex data that has been allocated with alloc().
     */
    void reset();

    /**
     * Returns a block of memory bytes size big. The vertex buffer
     * containing the memory is returned in buffer.
     *
     * @param layout       specifies type of vertices to allocate space for
     * @param vertexCount  number of vertices to allocate space for
     * @param buffer       returns the vertex buffer that will hold the
     *                     vertices.
     * @param startVertex  returns the offset into buffer of the first vertex.
     *                     In units of the size of a vertex using layout param.
     * @return pointer to first vertex.
     */
    void* alloc(GrVertexLayout layout,
                uint32_t vertexCount,
                GrVertexBuffer** buffer,
                uint32_t* startVertex);

    /**
     * Gets the number of vertices that can be allocated without changing VBs.
     * This means either the last VB returned by alloc() if the last alloc did
     * not exhaust it. If that VB was exhausted by the last alloc or alloc hasn't
     * been called since reset() then it will be the number of vertices that
     * would fit in an available preallocated VB. If no preallocated VB
     * is available then it returns 0 since the next alloc would force a new
     * VB to be created.
     */
    int currentBufferVertices(GrVertexLayout layout) const;

    /**
     * Gets the number of preallocated buffers that are yet to be used.
     */
    int preallocatedBuffersRemaining() const;

    /**
     * Gets the number of vertices that can fit in a  preallocated vertex buffer.
     * Zero if no preallocated buffers.
     */
    int preallocatedBufferVertices(GrVertexLayout layout) const;

    /**
     * gets the number of preallocated vertex buffers
     */
    int preallocatedBufferCount() const;


    /**
     * Releases the most recently allocated bytes back to the pool.
     */
    void release(size_t bytes);

    /**
     * Gets the GrGpu that this pool is associated with.
     */
    GrGpu* getGpu() { return fGpu; }


private:
    struct BufferBlock {
        size_t              fBytesFree;
        GrVertexBuffer*     fVertexBuffer;
    };

    bool createBlock(size_t size);
    void destroyBlock();

    GrTArray<BufferBlock>       fBlocks;
    GrTDArray<GrVertexBuffer*>  fPreallocBuffers;
    int                         fPreallocBuffersInUse;
    int                         fFirstPreallocBuffer;

    size_t              fMinBlockSize;
    GrGpu*              fGpu;
    void*               fBufferPtr;
};

#endif
