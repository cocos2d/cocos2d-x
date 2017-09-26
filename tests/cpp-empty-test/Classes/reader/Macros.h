/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#pragma once

#ifdef __cplusplus
#define NS_CCR_BEGIN                     namespace creator {
#define NS_CCR_END                       }
#define USING_NS_CCR                     using namespace creator
#else
#define NS_CC_BEGIN
#define NS_CC_END
#define USING_NS_CC
#define NS_CC
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
|| (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
    #define CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
        TypeName(const TypeName &) = delete; \
        TypeName& operator =(const TypeName &) = delete; \
        TypeName(TypeName &&) = delete; \
        TypeName& operator =(TypeName &&) = delete;
#else
    #define CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
        TypeName(const TypeName &); \
        TypeName& operator =(const TypeName &); \
        TypeName(TypeName &&); \
        TypeName& operator =(TypeName &&);
#endif
