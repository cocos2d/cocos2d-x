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

#ifndef CC_ALLOCATOR_BASE_H
#define CC_ALLOCATOR_BASE_H
/// @cond DO_NOT_SHOW

#include <string>

#include "platform/CCPlatformMacros.h"
#include "base/allocator/CCAllocatorMacros.h"



NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// @brief
// AllocatorBase
// Provides a base that contains a few methods and definitions that are helpful to all allocation strategies.
// Also provides a common base that can be used to point to all allocators generically.
class AllocatorBase
{
public:
    
    typedef void* pointer;
    
    enum { kDefaultAlignment = 16 };
    
    // this must be true for SSE instructions to be 16 byte aligned
    // we can now use kDefault alignment as our smallest alloc size
    static_assert(sizeof(uintptr_t) <= kDefaultAlignment, "pointer size must be smaller than default alignment");
    
#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
    AllocatorBase()
        : _next_allocator(nullptr)
    {}
#endif
    
    virtual ~AllocatorBase()
    {}
    
    // @brief
    // Given an address and alignment in bytes, returns an address aligned to the number of bytes
    // For example, if the alignment is 4 which is standard, then the address is divisible evenly by 4.
    CC_ALLOCATOR_INLINE pointer aligned(const pointer address, const size_t alignment = kDefaultAlignment) const
    {
        return (pointer) (((intptr_t)address + (alignment - 1)) & ~(alignment - 1));
    }
    
    // @brief Calculate the next power of two for a given size.
    // Most blocks requested are already a power of two. For small block alloc
    // this means we cannot add overhead, hence the slightly less performance
    // searching of fixed block pages to determine size if none is specified.
    CC_ALLOCATOR_INLINE size_t nextPow2BlockSize(size_t size) const
    {
        --size;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        return ++size;
    }
    
#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
    void setTag(const char* tag)
    {
        strncpy(_tag, tag, sizeof(_tag)-1);
    }
    
    const char* tag() const
    {
        return _tag;
    }
    
    // cannot use std::string as it allocates memory.
    // for some allocator this tag is set before the new/delete allocator has finished initializing.
    char _tag[1000];
    
    // @brief return any diagnostic info for this allocator
    virtual std::string diagnostics() const
    {
        return "";
    }
    AllocatorBase* _next_allocator;
#endif//CC_ENABLE_ALLOCATOR_DIAGNOSTICS
};

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_BASE_H
