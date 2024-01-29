
/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "base/allocator/CCAllocatorStrategyGlobalSmallBlock.h"
#include <new>
#include <exception>

#include <assert.h>

USING_NS_CC_ALLOCATOR;

#if CC_ENABLE_ALLOCATOR
#if CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE

namespace
{
    // @brief Declare the allocator for global new/delete
    static CC_ALLOCATOR_GLOBAL_NEW_DELETE global;
}

// @brief overrides global operator new array
void* operator new[] (std::size_t size)
{
    void* ptr = global.allocate(size);
    assert(ptr && "No memory");

    // disabling exceptions since cocos2d-x doesn't use them
//#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
//    if (nullptr == ptr)
//        throw std::bad_alloc();
//#endif
    return ptr;
}

// @brief overrides global operator new
void* operator new(std::size_t size)
{
    void* ptr = global.allocate(size);
    assert(ptr && "No memory");

    // disabling exceptions since cocos2d-x doesn't use them
//#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
//    if (nullptr == ptr)
//        throw std::bad_alloc();
//#endif
    return ptr;
}

// @brief overrides global operator delete
void operator delete(void* p) throw()
{
    if (p)
        global.deallocate(p);
}

#endif // CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
#endif // CC_ENABLE_ALLOCATOR
