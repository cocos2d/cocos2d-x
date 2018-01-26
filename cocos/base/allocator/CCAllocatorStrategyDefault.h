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

#ifndef CC_ALLOCATOR_STRATEGY_DEFAULT_H
#define CC_ALLOCATOR_STRATEGY_DEFAULT_H
/// @cond DO_NOT_SHOW

#include <stdlib.h>
#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorBase.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

// @brief
// The default allocation strategy that just falls through to malloc and free
class AllocatorStrategyDefault
    : public AllocatorBase
{
public:
    
    CC_ALLOCATOR_INLINE void* allocate(size_t size)
    {
        return malloc(size);
    }
    
    CC_ALLOCATOR_INLINE void deallocate(void* address, size_t size = 0)
    {
        if (nullptr != address)
            free(address);
    }
};

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_STRATEGY_DEFAULT_H
