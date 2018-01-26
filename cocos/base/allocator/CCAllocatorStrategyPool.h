/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.
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

#ifndef CC_ALLOCATOR_STRATEGY_POOL_H
#define CC_ALLOCATOR_STRATEGY_POOL_H
/// @cond DO_NOT_SHOW

#include <vector>
#include <typeinfo>
#include <sstream>

#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorGlobal.h"
#include "base/allocator/CCAllocatorStrategyFixedBlock.h"
#include "base/allocator/CCAllocatorDiagnostics.h"
#include "base/CCConfiguration.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

/**
 * ObjectTraits describes an allocatable object.
 *
 * Template class that represents a default allocatable object.
 * Provide custom implementations to change the constructor/destructor behavior,
 * or to change the default alignment of the object in memory.
 *
 * @param T Type of object.
 * @param _alignment Alignment of object T.
 */
template <typename T, size_t _alignment = sizeof(uint32_t)>
class ObjectTraits
{
public:
    
    typedef T value_type;
    
    static const size_t alignment = _alignment;
    
    virtual ~ObjectTraits()
    {}
    
    /** Constructor implementation for type T.*/
    void construct(T* address)
    {
        ::new(address) T();
    }
    
    /** Destructor implementation for type T.*/
    void destroy(T* address)
    {
        address->~T();
    }
    
    /** Returns the name of this object type T.*/
    const char* name() const
    {
        return typeid(T).name();
    }
};

/**
 * Fixed sized pool allocator strategy for objects of type T.
 *
 * Optionally takes a page size which determines how many objects are added when the allocator needs more storage.
 * ObjectTraits allows you to control the alignment, construction and destruction of an object in the pool.
 *
 * @param T Type of object.
 * @param _page_size Number of objects of T in each page.
 * @param O ObjectTraits for type T
 * @see CC_USE_ALLOCATOR_POOL
 */
template <typename T, typename O = ObjectTraits<T>, typename locking_traits = lockless_semantics>
class AllocatorStrategyPool
    : public AllocatorStrategyFixedBlock<sizeof(T), O::alignment, locking_traits>
    , public O
{
public:
    
    typedef T value_type;
    typedef value_type* pointer;
    
    /** Ugh wish I knew a way that I could declare this just once.*/
    typedef AllocatorStrategyFixedBlock<sizeof(T), O::alignment, locking_traits> tParentStrategy;
    
    AllocatorStrategyPool(const char* tag = nullptr, size_t poolSize = 100)
        : tParentStrategy(tag)
    {
        poolSize = Configuration::getInstance()->getValue(tag, Value((int)poolSize)).asInt();
        tParentStrategy::_pageSize = poolSize;
    }
    
    /**
     * Allocate block of size T.
     *
     * If size does not match sizeof(T) then the global allocator is called instead.
     * @see CC_USE_ALLOCATOR_POOL
     */
    CC_ALLOCATOR_INLINE void* allocate(size_t size)
    {
        T* object;
        if (sizeof(T) == size)
        {
            object = (pointer)tParentStrategy::allocate(sizeof(T));
        }
        else
        {
            object = (T*)ccAllocatorGlobal.allocate(size);
        }
        O::construct(object);
        return object;
    }
    
    /**
     * Deallocate block of size T.
     *
     * If size does not match sizeof(T) then the global allocator is called instead.
     * @see CC_USE_ALLOCATOR_POOL
     */
    CC_ALLOCATOR_INLINE void deallocate(void* address, size_t size = 0)
    {
        if (address)
        {
            O::destroy((T*)address);
            if (sizeof(T) == size)
            {
                tParentStrategy::deallocate(address, sizeof(T));
            }
            else
            {
                ccAllocatorGlobal.deallocate(address, size);
            }
        }
    }
    
#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
    std::string diagnostics() const
    {
        std::stringstream s;
        s << AllocatorBase::tag() << " initial:" << tParentStrategy::_pageSize << " count:" << tParentStrategy::_allocated << " highest:" << tParentStrategy::_highestCount << "\n";
        return s.str();
    }    
#endif
};

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_STRATEGY_POOL_H
