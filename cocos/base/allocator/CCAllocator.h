
#pragma once

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

#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorBase.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// @brief Template class that injects the type T as a subclass of Allocator
// This allows us to call methods on T that are declared in Allocator without
// the need for making those methods virtual, avoiding a vtable lookup per call.
// With inlining, the calls below should collapse and a single call made.
template <class T>
class Allocator
    : public AllocatorBase
{
public:

    virtual ~Allocator()
	{}
    
    CC_ALLOCATOR_INLINE void* allocate(size_t size)
    {
        return static_cast<T*>(this)->allocate(size);
    }
    
    CC_ALLOCATOR_INLINE void deallocate(void* address, size_t size = 0)
    {
        static_cast<T*>(this)->deallocate(address, size);
    }
    
    CC_ALLOCATOR_INLINE bool owns(const void* const address) const
    {
        return static_cast<const T* const>(this)->owns(address);
    }
};

NS_CC_ALLOCATOR_END
NS_CC_END
