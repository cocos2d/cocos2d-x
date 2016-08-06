/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#ifndef CC_ALLOCATOR_DIAGNOSTICS_H
#define CC_ALLOCATOR_DIAGNOSTICS_H
/// @cond DO_NOT_SHOW

#include <unordered_set>

#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorMutex.h"
#include "base/allocator/CCAllocatorBase.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
class AllocatorBase;
class AllocatorDiagnostics
{
public:
    
    AllocatorDiagnostics();
    static AllocatorDiagnostics* instance();
    void trackAllocator(AllocatorBase* allocator);
    void untrackAllocator(AllocatorBase* allocator);
    std::string diagnostics();
    
protected:
    
    AllocatorMutex _mutex;
    AllocatorBase* _allocators;
};
#endif//CC_ENABLE_ALLOCATOR_DIAGNOSTICS

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_DIAGNOSTICS_H
