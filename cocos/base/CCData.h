/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CCDATA_H__
#define __CCDATA_H__

#include "base/CCPlatformMacros.h"
#include <stdint.h> // for ssize_t on android
#include <string>   // for ssize_t on linux
#include "CCStdC.h" // for ssize_t on window

NS_CC_BEGIN

class CC_DLL Data
{
public:
    static const Data Null;
    
    Data();
    Data(const Data& other);
    Data(Data&& other);
    ~Data();
    
    // copy assignment operator
    Data& operator= (const Data& other);
    Data& operator= (Data&& other);
    
    /**
     * @js NA
     * @lua NA
     */
    unsigned char* getBytes() const;
    /**
     * @js NA
     * @lua NA
     */
    ssize_t getSize() const;
    
    /** 拷贝缓冲区内容(指 `bytes`), 缓冲区长度信息到Data.
     *  @note 这个方法会拷贝整个缓冲区的内容到Data.
     *        开发者应该在调用这个方法之后释放内存(指 `bytes`).
     *  @see Data::fastSet
     */
    void copy(unsigned char* bytes, const ssize_t size);
    
    /** 快速设置 Data 缓冲区内容(仅复制指针, 不复制内容)和缓冲区长度. 请谨慎使用.
     *  @param bytes 缓冲区指针, 必须使用 'malloc' 或 'calloc' 来分配内存,
     *         因为 Data 析构函数会使用 'free' 释放内存.
     *  @note 1. 这个方法将移动 `bytes`指针的拥有权至Data,
     *        2. 这个指针(指 `bytes`)在作为参数传递给这个方法之后不应该再在其他地方使用.
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);
    
    /** 清空 Data, 释放缓冲区内存, 重置 Data 缓冲区长度. */
    void clear();
    
    /** 检查 Data 是否为空. */
    bool isNull() const;
    
private:
    void move(Data& other);
    
private:
    unsigned char* _bytes;
    ssize_t _size;
};

NS_CC_END

#endif // __CCDATA_H__
