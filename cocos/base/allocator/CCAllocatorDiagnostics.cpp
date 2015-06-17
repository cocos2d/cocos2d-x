
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

#include "CCAllocatorDiagnostics.h"
#include "CCAllocatorGlobal.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
AllocatorDiagnostics::AllocatorDiagnostics()
    : _allocators(nullptr)
{}

AllocatorDiagnostics* AllocatorDiagnostics::instance()
{
    static AllocatorDiagnostics* _this = nullptr;
    if (nullptr == _this)
    {
        // have to use global allocator because none of the constructors will have been called.
        _this = (AllocatorDiagnostics*)ccAllocatorGlobal.allocate(sizeof(AllocatorDiagnostics));
        new (_this) AllocatorDiagnostics();
    }
    return _this;
}

void AllocatorDiagnostics::trackAllocator(AllocatorBase* allocator)
{
    LOCK(_mutex);
    auto p = _allocators;
    for (; nullptr != p; p = p->_next_allocator)
    {
        CC_ASSERT(p != allocator);
    }
    allocator->_next_allocator = _allocators;
    _allocators = allocator;
    UNLOCK(_mutex);
}

void AllocatorDiagnostics::untrackAllocator(AllocatorBase* allocator)
{
    LOCK(_mutex);
    auto pp = &_allocators;
    for (; *pp != allocator; pp = &(*pp)->_next_allocator);
    if (*pp == allocator)
        *pp = (*pp)->_next_allocator;
    UNLOCK(_mutex);
}

std::string AllocatorDiagnostics::diagnostics()
{
    std::string data;
    LOCK(_mutex);
    auto a = _allocators;
    while (a)
    {
        data += a->diagnostics();
        a = a->_next_allocator;
    }
    UNLOCK(_mutex);
    return data;
}
#endif//CC_ENABLE_ALLOCATOR_DIAGNOSTICS

NS_CC_ALLOCATOR_END
NS_CC_END
