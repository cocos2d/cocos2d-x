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

    /**@~english
     * This parameter is defined for convenient reference if a null Data object is needed.
     * @~chinese 
     * 这个参数被定义为null Data对象，以方便需要时进行引用。
     */
    static const Data Null;
    

    /**@~english
     * Constructor of Data.
     * @~chinese 
     * Data的构造函数。
     */
    Data();
    

    /**@~english
     * Copy constructor of Data.
     * @~chinese 
     * Data的拷贝构造函数。
     */
    Data(const Data& other);
    

    /**@~english
     * Copy constructor of Data.
     * @~chinese 
     * Data的拷贝构造函数。
     */
    Data(Data&& other);
    

    /**@~english
     * Destructor of Data.
     * @~chinese 
     * Data的析构函数。
     */
    ~Data();
    

    /**@~english
     * Overloads of operator=.
     * @~chinese 
     * 重载赋值操作符。
     */
    Data& operator= (const Data& other);
    

    /**@~english
     * Overloads of operator=.
     * @~chinese 
     * 重载赋值操作符。
     */
    Data& operator= (Data&& other);
    

    /**@~english
     * Gets internal bytes of Data. It will return the pointer directly used in Data, so don't delete it.
     *
     * @~chinese 
     * 获取Data的内部字节。它将会返回一个Data中直接使用的指针,所以不要删除它。
     * 
     * @return @~english Pointer of bytes used internal in Data.
     * @~chinese Data中内部使用的指针。
     */
    unsigned char* getBytes() const;
    

    /**@~english
     * Gets the size of the bytes.
     *
     * @~chinese 
     * 获取字节的大小。
     * 
     * @return @~english The size of bytes of Data.
     * @~chinese 字节的数据的大小。
     */
    ssize_t getSize() const;
    

    /** @~english Copies the buffer pointer and its size.
     * @~chinese 拷贝缓冲指针和它的大小。
     *  @note @~english This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     * @~chinese 该方法将复制整个缓冲区。
     * 开发人员应该在调用这个方法后释放指针。
     *  @see Data::fastSet
     */
    void copy(const unsigned char* bytes, const ssize_t size);
    

    /** @~english Fast set the buffer pointer and its size. Please use it carefully.
     * @~chinese 快速设置缓冲区指针和它的大小。请小心使用它。
     *  @param bytes @~english The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     * @~chinese 缓冲区的指针,注意,一定要由“malloc”或“calloc”分配
     * 因为在Data的析构函数中,缓冲区将被“free”删除。
     *  @note @~english 1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     * @~chinese 1。该方法移动buffer指针的所有权,
     * 2。这个指针不应在传递给这个方法后再进行使用。
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);
    

    /** @~english
     * Clears data, free buffer and reset data size.
     * @~chinese 
     * 清除数据,释放缓冲区和重置数据大小。
     */
    void clear();
    

    /** @~english
     * Check whether the data is null.
     *
     * @~chinese 
     * 检查数据是否为空。
     * 
     * @return @~english True if the the Data is null, false if not.
     * @~chinese 如果数据为空返回真,如果不是返回假。
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
