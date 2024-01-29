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

#ifndef CC_ALLOCATOR_MACROS_H
#define CC_ALLOCATOR_MACROS_H
/// @cond DO_NOT_SHOW

#include "base/ccConfig.h"
#include "platform/CCPlatformMacros.h"

// namespace allocator {}
#ifdef __cplusplus
    #define NS_CC_ALLOCATOR_BEGIN   namespace allocator {
    #define NS_CC_ALLOCATOR_END     }
    #define USING_NS_CC_ALLOCATOR   using namespace cocos2d::allocator
    #define NS_CC_ALLOCATOR         ::cocos2d::allocator
#else
    #define NS_CC_ALLOCATOR_BEGIN
    #define NS_CC_ALLOCATOR_END
    #define USING_NS_CC_ALLOCATOR
    #define NS_CC_ALLOCATOR
#endif

#if COCOS2D_DEBUG

    // @brief CC_ALLOCATOR_INLINE
    // Turn off inlining of methods when debugging to make stack traces readable and stepping through code sane.
    #define CC_ALLOCATOR_INLINE

    // printf is safe to use
    #define LOG printf

#else

    #define CC_ALLOCATOR_INLINE inline
    #define LOG

#endif

// allocator macros
#if CC_ENABLE_ALLOCATOR

    // @brief macros for new/delete
    // we let global new/delete handle these as they are overridden.
    #define CC_NEW(klass, ...) new klass(__VAR_ARGS__)
    #define CC_DELETE(object) delete object;

    // @brief macros for malloc/free
    // these will use the global allocator
    #define CC_MALLOC(size) ccAllocatorGlobal.allocate(size)
    #define CC_FREE(address) ccAllocatorGlobal.deallocate(address)

    // alloc on the stack
    #define CC_ALLOCA(size) alloca(size)

    // @brief helper macro for overriding new/delete operators for a class.
    // This correctly passes the size in the deallocate method which is needed.
    #define CC_USE_ALLOCATOR_POOL(T, A) \
        CC_ALLOCATOR_INLINE void* operator new (size_t size) \
        { \
            return (void*)A.allocate(size); \
        } \
        CC_ALLOCATOR_INLINE void operator delete (void* object, size_t size) \
        { \
            A.deallocate((T*)object, size); \
        }

#else

    // macros for new/delete
    // these will use a general thread safe allocator
    #define CC_NEW(klass, ...) new klass(__VAR_ARGS__)
    #define CC_DELETE(object) delete object

    // macros for malloc/free
    // these will use a general thread safe allocator
    #define CC_MALLOC(size) malloc(size)
    #define CC_FREE(address) free(address)

    // alloc on the stack
    #define CC_ALLOCA(size) alloca(size)

    // throw these away if not enabled
    #define CC_USE_ALLOCATOR_POOL(...)
    #define CC_OVERRIDE_GLOBAL_NEWDELETE_WITH_ALLOCATOR(...)

#endif

// @ brief Quick and dirty macro to dump an area of memory
// useful for debugging blocks of memory from allocators.
#define DUMP(a, l, C) \
{ \
    LOG("> %p len %zu\n", a, l); \
    uint8_t* p = (uint8_t*)a; \
    uint8_t* e = p + l; \
    while (p < e) \
    { \
        LOG("%p ", p); \
        for (int i = 0; i < C && &p[i] < e; ++i) \
            LOG("%02x ", p[i]); \
        for (int i = 0; i < C && &p[i] < e; ++i) \
            LOG("%c ", isalnum(p[i]) ? p[i] : '.'); \
        LOG("\n"); \
        p = p + C > e ? e : p + C; \
    } \
}

/// @endcond
#endif//CC_ALLOCATOR_MACROS_H
