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


#ifndef GrBufferAllocPool_DEFINED
#define GrBufferAllocPool_DEFINED

#include "GrNoncopyable.h"
#include "GrTDArray.h"
#include "GrTArray.h"
#include "GrMemory.h"

class GrGeometryBuffer;
class GrGpu;

/**
 * A pool of geometry buffers tied to a GrGpu.
 *
 * The pool allows a client to make space for geometry and then put back excess
 * space if it over allocated. When a client is ready to draw from the pool
 * it calls unlock on the pool ensure buffers are ready for drawing. The pool
 * can be reset after drawing is completed to recycle space.
 *
 * At creation time a minimum per-buffer size can be specified. Additionally,
 * a number of buffers to preallocate can be specified. These will
 * be allocated at the min size and kept around until the pool is destroyed.
 */
class GrBufferAllocPool : GrNoncopyable {

public:
    /**
     * Ensures all buffers are unlocked and have all data written to them.
     * Call before drawing using buffers from the pool.
     */
    void unlock();

    /**
     *  Invalidates all the data in the pool, unrefs non-preallocated buffers.
     */
    void reset();

    /**
     * Gets the number of preallocated buffers that are yet to be used.
     */
    int preallocatedBuffersRemaining() const;

    /**
     * gets the number of preallocated buffers
     */
    int preallocatedBufferCount() const;

    /**
     * Frees data from makeSpaces in LIFO order.
     */
    void putBack(size_t bytes);

    /**
     * Gets the GrGpu that this pool is associated with.
     */
    GrGpu* getGpu() { return fGpu; }

protected:
    /**
     * Used to determine what type of buffers to create. We could make the
     * createBuffer a virtual except that we want to use it in the cons for
     * pre-allocated buffers.
     */
    enum BufferType {
        kVertex_BufferType,
        kIndex_BufferType,
    };

    /**
     * Constructor
     *
     * @param gpu                   The GrGpu used to create the buffers.
     * @param bufferType            The type of buffers to create.
     * @param frequentResetHint     A hint that indicates that the pool
     *                              should expect frequent unlock() calls
     *                              (as opposed to many makeSpace / acquires
     *                              between resets).
     * @param bufferSize            The minimum size of created buffers.
     *                              This value will be clamped to some
     *                              reasonable minimum.
     * @param preallocBufferCnt     The pool will allocate this number of
     *                              buffers at bufferSize and keep them until it
     *                              is destroyed.
     */
     GrBufferAllocPool(GrGpu* gpu,
                       BufferType bufferType,
                       bool frequentResetHint,
                       size_t   bufferSize = 0,
                       int preallocBufferCnt = 0);

    virtual ~GrBufferAllocPool();

    /**
     * Gets the size of the preallocated buffers.
     *
     * @return the size of preallocated buffers.
     */
    size_t preallocatedBufferSize() const {
        return fPreallocBuffers.count() ? fMinBlockSize : 0;
    }

    /**
     * Returns a block of memory to hold data. A buffer designated to hold the
     * data is given to the caller. The buffer may or may not be locked. The
     * returned ptr remains valid until any of the following:
     *      *makeSpace is called again.
     *      *unlock is called.
     *      *reset is called.
     *      *this object is destroyed.
     *
     * Once unlock on the pool is called the data is guaranteed to be in the
     * buffer at the offset indicated by offset. Until that time it may be
     * in temporary storage and/or the buffer may be locked.
     *
     * @param size         the amount of data to make space for
     * @param alignment    alignment constraint from start of buffer
     * @param buffer       returns the buffer that will hold the data.
     * @param offset       returns the offset into buffer of the data.
     * @return pointer to where the client should write the data.
     */
    void* makeSpace(size_t size,
                    size_t alignment,
                    const GrGeometryBuffer** buffer,
                    size_t* offset);

    /**
     * Gets the number of items of a size that can be added to the current
     * buffer without spilling to another buffer. If the pool has been reset, or
     * the previous makeSpace completely exhausted a buffer then the returned
     * size will be the size of the next available preallocated buffer, or zero
     * if no preallocated buffer remains available. It is assumed that items
     * should be itemSize-aligned from the start of a buffer.
     *
     * @return the number of items that would fit in the current buffer.
     */
    int currentBufferItems(size_t itemSize) const;

    GrGeometryBuffer* createBuffer(size_t size);

private:

    // The GrGpu must be able to clear the ref of pools it creates as members
    friend class GrGpu;
    void releaseGpuRef();

    struct BufferBlock {
        size_t              fBytesFree;
        GrGeometryBuffer*   fBuffer;
    };

    bool createBlock(size_t requestSize);
    void destroyBlock();
    void flushCpuData(GrGeometryBuffer* buffer, size_t flushSize);
#if GR_DEBUG
    void validate(bool unusedBlockAllowed = false) const;
#endif
    
    size_t                          fBytesInUse;

    GrGpu*                          fGpu;
    bool                            fGpuIsReffed;
    bool                            fFrequentResetHint;
    GrTDArray<GrGeometryBuffer*>    fPreallocBuffers;
    size_t                          fMinBlockSize;
    BufferType                      fBufferType;

    GrTArray<BufferBlock>           fBlocks;
    int                             fPreallocBuffersInUse;
    int                             fFirstPreallocBuffer;
    GrAutoMalloc                    fCpuData;
    void*                       	fBufferPtr;
};

class GrVertexBuffer;

/**
 * A GrBufferAllocPool of vertex buffers
 */
class GrVertexBufferAllocPool : public GrBufferAllocPool {
public:
    /**
     * Constructor
     *
     * @param gpu                   The GrGpu used to create the vertex buffers.
     * @param frequentResetHint     A hint that indicates that the pool
     *                              should expect frequent unlock() calls
     *                              (as opposed to many makeSpace / acquires
     *                              between resets).
     * @param bufferSize            The minimum size of created VBs This value
     *                              will be clamped to some reasonable minimum.
     * @param preallocBufferCnt     The pool will allocate this number of VBs at
     *                              bufferSize and keep them until it is
     *                              destroyed.
     */
    GrVertexBufferAllocPool(GrGpu* gpu,
                            bool frequentResetHint,
                            size_t bufferSize = 0,
                            int preallocBufferCnt = 0);

    /**
     * Returns a block of memory to hold vertices. A buffer designated to hold
     * the vertices given to the caller. The buffer may or may not be locked.
     * The returned ptr remains valid until any of the following:
     *      *makeSpace is called again.
     *      *unlock is called.
     *      *reset is called.
     *      *this object is destroyed.
     *
     * Once unlock on the pool is called the vertices are guaranteed to be in
     * the buffer at the offset indicated by startVertex. Until that time they
     * may be in temporary storage and/or the buffer may be locked.
     *
     * @param layout       specifies type of vertices to allocate space for
     * @param vertexCount  number of vertices to allocate space for
     * @param buffer       returns the vertex buffer that will hold the
     *                     vertices.
     * @param startVertex  returns the offset into buffer of the first vertex.
     *                     In units of the size of a vertex from layout param.
     * @return pointer to first vertex.
     */
    void* makeSpace(GrVertexLayout layout,
                    int vertexCount,
                    const GrVertexBuffer** buffer,
                    int* startVertex);

    /**
     * Shortcut to make space and then write verts into the made space.
     */
    bool appendVertices(GrVertexLayout layout,
                        int vertexCount,
                        const void* vertices,
                        const GrVertexBuffer** buffer,
                        int* startVertex);

    /**
     * Gets the number of vertices that can be added to the current VB without
     * spilling to another VB. If the pool has been reset, or the previous
     * makeSpace completely exhausted a VB then the returned number of vertices
     * would fit in the next available preallocated buffer. If any makeSpace
     * would force a new VB to be created the return value will be zero.
     *
     * @param   the format of vertices to compute space for.
     * @return the number of vertices that would fit in the current buffer.
     */
    int currentBufferVertices(GrVertexLayout layout) const;

    /**
     * Gets the number of vertices that can fit in a  preallocated vertex buffer.
     * Zero if no preallocated buffers.
     *
     * @param   the format of vertices to compute space for.
     *
     * @return number of vertices that fit in one of the preallocated vertex
     *         buffers.
     */
    int preallocatedBufferVertices(GrVertexLayout layout) const;

private:
    typedef GrBufferAllocPool INHERITED;
};

class GrIndexBuffer;

/**
 * A GrBufferAllocPool of index buffers
 */
class GrIndexBufferAllocPool : public GrBufferAllocPool {
public:
    /**
     * Constructor
     *
     * @param gpu                   The GrGpu used to create the index buffers.
     * @param frequentResetHint     A hint that indicates that the pool
     *                              should expect frequent unlock() calls
     *                              (as opposed to many makeSpace / acquires
     *                              between resets).
     * @param bufferSize            The minimum size of created IBs This value
     *                              will be clamped to some reasonable minimum.
     * @param preallocBufferCnt     The pool will allocate this number of VBs at
     *                              bufferSize and keep them until it is
     *                              destroyed.
     */
    GrIndexBufferAllocPool(GrGpu* gpu,
                           bool frequentResetHint,
                           size_t bufferSize = 0,
                           int preallocBufferCnt = 0);

    /**
     * Returns a block of memory to hold indices. A buffer designated to hold
     * the indices is given to the caller. The buffer may or may not be locked.
     * The returned ptr remains valid until any of the following:
     *      *makeSpace is called again.
     *      *unlock is called.
     *      *reset is called.
     *      *this object is destroyed.
     *
     * Once unlock on the pool is called the indices are guaranteed to be in the
     * buffer at the offset indicated by startIndex. Until that time they may be
     * in temporary storage and/or the buffer may be locked.
     *
     * @param indexCount   number of indices to allocate space for
     * @param buffer       returns the index buffer that will hold the indices.
     * @param startIndex   returns the offset into buffer of the first index.
     * @return pointer to first index.
     */
    void* makeSpace(int indexCount,
                    const GrIndexBuffer** buffer,
                    int* startIndex);

    /**
     * Shortcut to make space and then write indices into the made space.
     */
    bool appendIndices(int indexCount,
                       const void* indices,
                       const GrIndexBuffer** buffer,
                       int* startIndex);

    /**
     * Gets the number of indices that can be added to the current IB without
     * spilling to another IB. If the pool has been reset, or the previous
     * makeSpace completely exhausted a IB then the returned number of indices
     * would fit in the next available preallocated buffer. If any makeSpace
     * would force a new IB to be created the return value will be zero.
     */
    int currentBufferIndices() const;

    /**
     * Gets the number of indices that can fit in a preallocated index buffer.
     * Zero if no preallocated buffers.
     *
     * @return number of indices that fit in one of the preallocated index
     *         buffers.
     */
    int preallocatedBufferIndices() const;

private:
    typedef GrBufferAllocPool INHERITED;
};

#endif
