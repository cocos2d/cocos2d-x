/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
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

#ifndef CC_ALLOCATOR_GLOBAL_H
#define CC_ALLOCATOR_GLOBAL_H
/// @cond DO_NOT_SHOW

#include "base/allocator/CCAllocatorMacros.h"
#include "base/allocator/CCAllocatorStrategyDefault.h"

NS_CC_BEGIN
NS_CC_ALLOCATOR_BEGIN

/** Make visible at the global scope.*/
extern CC_ALLOCATOR_GLOBAL ccAllocatorGlobal;

NS_CC_ALLOCATOR_END
NS_CC_END

/// @endcond
#endif//CC_ALLOCATOR_GLOBAL_H
