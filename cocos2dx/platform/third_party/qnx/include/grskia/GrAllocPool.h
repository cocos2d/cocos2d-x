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


#ifndef GrAllocPool_DEFINED
#define GrAllocPool_DEFINED

#include "GrNoncopyable.h"

class GrAllocPool : GrNoncopyable {
public:
    GrAllocPool(size_t blockSize = 0);
    ~GrAllocPool();

    /**
     *  Frees all blocks that have been allocated with alloc().
     */
    void reset();

    /**
     *  Returns a block of memory bytes size big. This address must not be
     *  passed to realloc/free/delete or any other function that assumes the
     *  address was allocated by malloc or new (because it hasn't).
     */
    void* alloc(size_t bytes);
    
    /**
     * Releases the most recently allocated bytes back to allocpool.
     */
    void release(size_t bytes);

private:
    struct Block;

    Block*  fBlock;
    size_t  fMinBlockSize;

#if GR_DEBUG
    int fBlocksAllocated;
    void validate() const;
#else
    void validate() const {}
#endif
};

template <typename T> class GrTAllocPool {
public:
    GrTAllocPool(int count) : fPool(count * sizeof(T)) {}

    void reset() { fPool.reset(); }
    T* alloc() { return (T*)fPool.alloc(sizeof(T)); }

private:
    GrAllocPool fPool;
};

#endif

