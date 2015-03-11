
/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#ifndef _CC_PAL_MACROS_H_
#define _CC_PAL_MACROS_H_

#include "assert.h"

// namespace _private {}
#ifdef __cplusplus
    #define NS_PRIVATE_BEGIN  namespace cocos2d { namespace _private {
    #define NS_PRIVATE_END    }}
    #define USING_NS_PRIVATE  using namespace cocos2d::_private
    #define NS_PRIVATE        ::cocos2d::_private
#else
    #define NS_PRIVATE_BEGIN
    #define NS_PRIVATE_END
    #define USING_NS_PRIVATE
    #define NS_PRIVATE
#endif

#define PAL_SAFE_RELEASE_NULL(x) { if (x) { x->release(); x = nullptr; } } 

#define PAL_ASSERT(cond, ...) assert(cond)

#endif//_CC_PAL_MACROS_H_


