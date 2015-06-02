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

#include "platform/CCPlatformMacros.h"
#include <stdint.h> // for ssize_t on android
#include <string>   // for ssize_t on linux
#include "platform/CCStdC.h" // for ssize_t on window

/**
 * @addtogroup base
 * @js NA
 * @lua NA
 */
NS_CC_BEGIN

class CC_DLL Data
{
    friend class Properties;
    
public:
    /**
     * @~english This parameter is defined for convenient reference if a null Data object is needed.
     * @~chinese 定义该参数的作用是，当需要使用空的数据对象时，提供一个方便的引用。
     */
    static const Data Null;
    
    /**
     * @~english Constructor of Data.
     * @~chinese 数据构造函数。
     */
    Data();
    
    /**
    * @~english Copy constructor of Data.
    * @~chinese 数据拷贝构造函数。
    */
    Data(const Data& other);
    
    /**
    * @~english Copy constructor of Data.
    * @~chinese 数据拷贝构造函数。
    */
    Data(Data&& other);
    
    /**
    * @~english Destructor of Data.
    * @~chinese 数据析构函数。
    */
    ~Data();
    
    /**
    * @~english Overroads of operator=.
    * @~chinese 重载=运算符。
    */
    Data& operator= (const Data& other);
    
    /**
    * @~english Overroads of operator=.
    * @~chinese 重载=运算符。
    */
    Data& operator= (Data&& other);
    
    /**
     * @~english Gets internal bytes of Data. It will return the pointer directly used in Data, so don't delete it.
     * @~chinese 获取数据的内部字节指针。将返回数据内部用来直接使用的指针，因此不要删除。
     * @return @~english Pointer of bytes used internal in Data.
     * @~chinese 数据内部使用的字节指针。
     */
    unsigned char* getBytes() const;
    
    /**
     * @~english Gets the size of the bytes.
     * @~chinese  获得字节大小
     * @return @~english The size of bytes of Data.
     * @~chinese  数据的字节大小。
     */
    ssize_t getSize() const;
    
    /** 
     *  @~english Copies the buffer pointer and its size.
     * @~chinese 复制缓冲区指针及其大小
     *  @note @~english  This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     * @~chinese 该方法将复制整个缓冲区。在调用该方法后应当释放指针。
     *  @see Data::fastSet
     */
    void copy(const unsigned char* bytes, const ssize_t size);
    
    /** 
     *   @~english  Fast set the buffer pointer and its size. Please use it carefully.
     * @~chinese 快速设置缓冲区指针和尺寸，请谨慎使用。
     *  @param bytes @~english  The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     * @~chinese 缓冲区指针，注意一定要用'malloc'或'calloc'进行分配空间，因为在数据的析构函数中缓冲区被'free'释放。
     *  @note @~english  1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     * @~chinese 1. 该方法将转移数据的字节指针所有权。
     * 2. 在指针传入该方法后，不应在外部调用该指针。
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);
    
    /** 
     * @~english  Clears data, free buffer and reset data size.
     * @~chinese 清除数据，释放缓冲区并重置数据大小。
     */
    void clear();
    
    /** 
     * @~english Check whether the data is null.
     * @~chinese 检查数据是否为空。
     * @return @~english True if the the Data is null, false if not.
     * @~chinese 数据为空返回真，否则为假。
     */
    bool isNull() const;
    
private:
    void move(Data& other);
    
private:
    unsigned char* _bytes;
    ssize_t _size;
};


NS_CC_END

/** @} */
#endif // __CCDATA_H__
