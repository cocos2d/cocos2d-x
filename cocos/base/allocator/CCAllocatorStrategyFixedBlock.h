
#ifndef CC_ALLOCATOR_STRATEGY_FIXED_BLOCK_H
#define CC_ALLOCATOR_STRATEGY_FIXED_BLOCK_H

/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 Author: Justin Graham (https://github.com/mannewalis)
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/****************************************************************************
                                    WARNING!
     Do not use Console::log or any other methods that use NEW inside of this
     allocator. Failure to do so will result in recursive memory allocation.
 ****************************************************************************/

#include "base/allocator/CCAllocator.h"
#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorGlobal.h"
#include "base/allocator/CCAllocatorMutex.h"
#include <vector>

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// @brief define this to cause this allocator to fallback to the global allocator
// this is just for testing purposes to see if this allocator is broken.
//#define FALLBACK_TO_GLOBAL

// @brief
// Fixed sized block allocator strategy for allocating blocks
// of memory that are the same size.
// Optionally takes a page size which determines how many blocks
// are added when the allocator needs more storage.
// @param _block_size the size of the fixed block allocated by this allocator.
// @param _page_size the number of blocks to allocate when growing the free list.
// @param _alignment the alignment size in bytes of each block.
template <size_t _block_size, size_t _page_size = 100, size_t _alignment = 16>
class AllocatorStrategyFixedBlock
    : public Allocator<AllocatorStrategyFixedBlock<_block_size, _page_size, _alignment>>
{
public:
    
    static constexpr size_t block_size = _block_size;
    static constexpr size_t page_size  = _page_size;
    static constexpr size_t alignment  = _alignment;
    
    AllocatorStrategyFixedBlock()
        : _list(nullptr)
        , _pages(nullptr)
        , _available(0)
    {}
    
    virtual ~AllocatorStrategyFixedBlock()
    {
        CC_ASSERT(0 == _available); // assert if we didn't free all the blocks before destroying the allocator.
        do
        {
            intptr_t* page = (intptr_t*)_pages;
            intptr_t* next = (intptr_t*)*page;
            ccAllocatorGlobal.deallocate(page);
            _pages = (void*)next;
        }
        while (_pages);
    }
    
    // @brief
    // allocate a block of memory by returning the first item in the list or if empty
    // then allocate a new page of blocks, and return the first element and store the rest.
    // if _block_size does not match the requested size, then we assert.
    CC_ALLOCATOR_INLINE void* allocate(size_t size)
    {
        CC_ASSERT(block_size == size);
#ifdef FALLBACK_TO_GLOBAL
        return ccAllocatorGlobal.allocate(size);
#else
        return pop_front();
#endif
    }
    
    // @brief Deallocate a block by pushing it on the head of a linked list of free blocks.
    CC_ALLOCATOR_INLINE void deallocate(void* address, size_t size = 0)
    {
        CC_ASSERT(0 == size || block_size == size);
#ifdef FALLBACK_TO_GLOBAL
        ccAllocatorGlobal.deallocate(address);
#else
        push_front(address);
#endif
    }
    
    // @brief Checks allocated pages to determine whether or not a block
    // is owned by this allocator. This should be reasonably fast
    // for properly configured allocators with few large pages.
    CC_ALLOCATOR_INLINE bool owns(const void* const address)
    {
#ifdef FALLBACK_TO_GLOBAL
        return true; // since everything uses the global allocator, we can just lie and say we own this address.
#else
        LOCK(_mutex);
        
        const uint8_t* const a = (const uint8_t* const)address;
        const uint8_t* p = (uint8_t*)_pages;
        const size_t pSize = pageSize();
        while (p)
        {
            if (a >= p && a < (p + pSize))
            {
                UNLOCK(_mutex);
                return true;
            }
            p = (uint8_t*)(*(uintptr_t*)p);
        }
        UNLOCK(_mutex);
        return false;
#endif
    }
    
protected:
    
    #define VALIDATE \
        if (nullptr != _list) \
        { \
            CC_ASSERT(nullptr != _pages); \
        }
    
    // @brief Method to push an allocated block onto the free list.
    // No check is made that the block belongs to this allocator.
    // No check is made that the block hasn't been already added to this allocator.
    // There checks should be added for DEBUG builds.
    CC_ALLOCATOR_INLINE void push_front(void* block)
    {
        CC_ASSERT(block);
        CC_ASSERT(block_size < AllocatorBase::kDefaultAlignment || 0 == ((intptr_t)block & (AllocatorBase::kDefaultAlignment - 1)));

        LOCK(_mutex);
        
        VALIDATE
        
        if (nullptr == _list)
        {
            _list = block;
            *(uintptr_t*)block = 0;
        }
        else
        {
            uintptr_t* p = (uintptr_t*)(block);
            *p = (uintptr_t)_list;
            _list = block;
        }
        ++_available;
        
        UNLOCK(_mutex);
    }
    
    // @brief Method to pop a block off the free list.
    // If no blocks are available, then the list is grown by _page_size
    // Tuning of the page size is critical to getting good performance.
    // Ideally you would use a page size that is around the high water mark
    // for the number of blocks of this size being allocated.
    CC_ALLOCATOR_INLINE void* pop_front()
    {
        LOCK(_mutex);
        
        VALIDATE

        if (nullptr == _list)
        {
            allocatePage();
        }
        auto next = (void*)*(uintptr_t*)_list;
        auto block = _list;
        _list = next;
        --_available;
        
        UNLOCK(_mutex);
        
        CC_ASSERT(block_size < AllocatorBase::kDefaultAlignment || 0 == ((intptr_t)block & (AllocatorBase::kDefaultAlignment - 1)));
        return block;
    }
    
protected:
        
    // @brief Returns the size of a page in bytes + overhead.
    constexpr size_t pageSize() const
    {
        return AllocatorBase::kDefaultAlignment + AllocatorBase::nextPow2BlockSize(block_size) * page_size;
    }
    
    // @brief Allocates a new page from the global allocator,
    // and adds all the blocks to the free list.
    CC_ALLOCATOR_INLINE void allocatePage()
    {
        uint8_t* p = (uint8_t*)AllocatorBase::aligned(ccAllocatorGlobal.allocate(pageSize()));
        intptr_t* page = (intptr_t*)p;
        if (nullptr == _pages)
        {
            _pages = page;
            *page = 0;
        }
        else
        {
            *page = (intptr_t)_pages;
            _pages = page;
        }
        
        p += AllocatorBase::kDefaultAlignment; // step past the linked list node
        
        size_t aligned_size = AllocatorBase::nextPow2BlockSize(block_size);
        uint8_t* block = (uint8_t*)p;
        for (int i = 0; i < page_size; ++i, block += aligned_size)
        {
            push_front(block);
        }
    }
    
protected:
    
    // @brief Linked list of free blocks.
    void* _list;
    
    // @brief Linked list of allocated pages.
    void* _pages;
    
    // @brief Number of blocks that are free in the list.
    size_t _available;
    
    // @brief mutex for thread safety.
    AllocatorMutex _mutex;
};

NS_CC_ALLOCATOR_END
NS_CC_END

#endif//CC_ALLOCATOR_STRATEGY_FIXED_BLOCK_H
