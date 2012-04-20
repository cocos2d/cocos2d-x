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

#ifndef SkChunkAlloc_DEFINED
#define SkChunkAlloc_DEFINED

#include "SkTypes.h"

class SkChunkAlloc : SkNoncopyable {
public:
    SkChunkAlloc(size_t minSize);
    ~SkChunkAlloc();

    /** Free up all allocated blocks. This invalidates all returned
        pointers.
    */
    void reset();

    /** Reuse all allocated blocks. This invalidates all returned
        pointers (like reset) but doesn't necessarily free up all
        of the privately allocated blocks. This is more efficient
        if you plan to reuse the allocator multiple times.
    */
    void reuse();

    enum AllocFailType {
        kReturnNil_AllocFailType,
        kThrow_AllocFailType
    };
    
    void* alloc(size_t bytes, AllocFailType);
    void* allocThrow(size_t bytes) {
        return this->alloc(bytes, kThrow_AllocFailType);
    }
    
    /** Call this to unalloc the most-recently allocated ptr by alloc(). On
        success, the number of bytes freed is returned, or 0 if the block could
        not be unallocated. This is a hint to the underlying allocator that
        the previous allocation may be reused, but the implementation is free
        to ignore this call (and return 0).
     */
    size_t unalloc(void* ptr);
    
    size_t totalCapacity() const { return fTotalCapacity; }

    /**
     *  Returns true if the specified address is within one of the chunks, and
     *  has at least 1-byte following the address (i.e. if addr points to the
     *  end of a chunk, then contains() will return false).
     */
    bool contains(const void* addr) const;

private:
    struct Block;
    Block*  fBlock;
    size_t  fMinSize;
    Block*  fPool;
    size_t  fTotalCapacity;

    Block* newBlock(size_t bytes, AllocFailType ftype);
};

#endif
