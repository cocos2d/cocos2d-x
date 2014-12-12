
#ifndef CC_ALLOCATOR_STRATEGY_GLOBAL_SMALL_BLOCK_H
#define CC_ALLOCATOR_STRATEGY_GLOBAL_SMALL_BLOCK_H

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

#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocator.h"
#include "base/allocator/CCAllocatorGlobal.h"
#include "base/allocator/CCAllocatorStrategyFixedBlock.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// @brief
class AllocatorStrategyGlobalSmallBlock
    : public Allocator<AllocatorStrategyGlobalSmallBlock>
{
public:
    
    // default number of block to allocate per page.
    static constexpr size_t kDefaultSmallBlockCount = 100;
    
    // default max small block size pool.
    static constexpr size_t kMaxSmallBlockPower = 13; // 2^13 8192
  
    // @brief define for allocator strategy, cannot be typedef because we want to eval at use
    #define SType(size) AllocatorStrategyFixedBlock<size>
    
    void _lazy_init()
    {
        static bool first = true;
        if (first)
        {
            first = false;
            
            // call our own constructor. Global new can be called before the constructors are called.
            // Make sure it gets called by having it done lazily in the call to allocate.
            new (this) AllocatorStrategyGlobalSmallBlock();
        }
    }
    
    AllocatorStrategyGlobalSmallBlock()
    {
        static bool once = true;
        if (once)
        {
            once = false;
            
            memset(_smallBlockAllocators, 0, sizeof(_smallBlockAllocators));
            
            // cannot call new on the allocator here because it will recurse
            // so instead we allocate from the global allocator and construct in place.
            #define SBA(n, size) \
            { \
                auto v = ccAllocatorGlobal.allocate(sizeof(SType(size))); \
                _smallBlockAllocators[n] = (void*)(new (v) SType(size)("Global::"#size)); \
            }
            
            SBA(2,  4);
            SBA(3,  8);
            SBA(4,  16);
            SBA(5,  32);
            SBA(6,  64);
            SBA(7,  128);
            SBA(8,  256);
            SBA(9,  512);
            SBA(10, 1024);
            SBA(11, 2048);
            SBA(12, 4096);
            SBA(13, 8192);
            
            #undef SBA
        }
    }
    
    virtual ~AllocatorStrategyGlobalSmallBlock()
    {
        for (int i = 0; i <= kMaxSmallBlockPower; ++i)
            if (_smallBlockAllocators[i])
                ccAllocatorGlobal.deallocate(_smallBlockAllocators[i]);
    }
    
    // @brief Allocate a block of some size. If the block is <= 8192 it is allocated out of an array
    // of fixed size block allocators. If larger, then we default back to the global allocator.
    // @param size Size of block to allocate. This will be rounded to the next power of two.
    CC_ALLOCATOR_INLINE void* allocate(size_t size)
    {
        _lazy_init();
        
        if (size < sizeof(intptr_t)) // always allocate at least enough space to store a pointer. this is
            size = sizeof(intptr_t); // so we can link the empty blocks together in the block allocator.
        
        // if the size is greater than what we determine to be a small block
        // size then fall through to calling the global allocator instead.
        if (size > _maxBlockSize)
            return ccAllocatorGlobal.allocate(size);
        
        // make sure the size fits into one of the
        // fixed sized block allocators we have above.
        size_t adjusted_size = AllocatorBase::nextPow2BlockSize(size);
       
        #define ALLOCATE(slot, size) \
            case size: \
            { \
                void* v = _smallBlockAllocators[slot]; \
                CC_ASSERT(nullptr != v); \
                auto a = (SType(size)*)v; \
                address = a->allocate(adjusted_size); \
            } \
            break;
        
        void* address;
        
        switch (adjusted_size)
        {
        ALLOCATE(2,  4);
        ALLOCATE(3,  8);
        ALLOCATE(4,  16);
        ALLOCATE(5,  32);
        ALLOCATE(6,  64);
        ALLOCATE(7,  128);
        ALLOCATE(8,  256);
        ALLOCATE(9,  512);
        ALLOCATE(10, 1024);
        ALLOCATE(11, 2048);
        ALLOCATE(12, 4096);
        ALLOCATE(13, 8192);
        default:
            CC_ASSERT(false);
            throw std::bad_alloc();
            break;
        }

        #undef ALLOCATE
        
        CC_ASSERT(adjusted_size < AllocatorBase::kDefaultAlignment || 0 == ((intptr_t)address & (AllocatorBase::kDefaultAlignment - 1)));
        CC_ASSERT(nullptr != address);
        
        return address;
    }
    
    // @brief Deallocate a block by choosing one of the fixed size block allocators
    // or defaulting to the global allocator if we do not own this block.
    CC_ALLOCATOR_INLINE void deallocate(void* address, size_t size = 0)
    {
        // if we didn't get a size, then we need to find the allocator
        // by asking each if they own the block. For allocators that
        // have few large pages, this is extremely fast.
        if (0 == size)
        {
            #define OWNS(slot, S, address) \
            case S: \
            { \
                void* v = _smallBlockAllocators[slot]; \
                CC_ASSERT(nullptr != v); \
                auto a = (SType(S)*)v; \
                if (a->owns(address)) \
                { \
                    size = SType(S)::block_size; \
                    break; \
                } \
            }
            
            switch (sizeof(uint32_t))
            {
            OWNS(2,  4,    address);
            OWNS(3,  8,    address);
            OWNS(4,  16,   address);
            OWNS(5,  32,   address);
            OWNS(6,  64,   address);
            OWNS(7,  128,  address);
            OWNS(8,  256,  address);
            OWNS(9,  512,  address);
            OWNS(10, 1024, address);
            OWNS(11, 2048, address);
            OWNS(12, 4096, address);
            OWNS(13, 8192, address);
            }
        }
        
        // if the size is greater than what we determine to be a small block
        // size then default to calling the global allocator instead.
        if (0 == size || size > _maxBlockSize)
            return ccAllocatorGlobal.deallocate(address, size);
        
        if (size < sizeof(intptr_t)) // always allocate at least enough space to store a pointer. this is
            size = sizeof(intptr_t); // so we can link the empty blocks together in the block allocator.

        // make sure the size fits into one of the
        // fixed sized block allocators we have above.
        size_t adjusted_size = AllocatorBase::nextPow2BlockSize(size);
        
        #define DEALLOCATE(slot, size, address) \
            case size: \
            { \
                void* v = _smallBlockAllocators[slot]; \
                CC_ASSERT(nullptr != v); \
                auto a = (SType(size)*)v; \
                a->deallocate(address, size); \
            } \
            break;
        
        switch (adjusted_size)
        {
        DEALLOCATE(2,  4,    address);
        DEALLOCATE(3,  8,    address);
        DEALLOCATE(4,  16,   address);
        DEALLOCATE(5,  32,   address);
        DEALLOCATE(6,  64,   address);
        DEALLOCATE(7,  128,  address);
        DEALLOCATE(8,  256,  address);
        DEALLOCATE(9,  512,  address);
        DEALLOCATE(10, 1024, address);
        DEALLOCATE(11, 2048, address);
        DEALLOCATE(12, 4096, address);
        DEALLOCATE(13, 8192, address);
        default:
            CC_ASSERT(false);
            throw std::bad_alloc();
        }
        
        #undef DEALLOCATE
    }
    
protected:
    
    // @brief array of small block allocators from 2^2 -> 2^13
    void* _smallBlockAllocators[kMaxSmallBlockPower + 1];
    
    // @brief the max size of a block this allocator will pool before using global allocator
    size_t _maxBlockSize;
};

NS_CC_ALLOCATOR_END
NS_CC_END

#endif//CC_ALLOCATOR_STRATEGY_GLOBAL_SMALL_BLOCK_H
