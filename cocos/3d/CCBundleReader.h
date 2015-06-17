/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_BUNDLE_READER_H__
#define __CC_BUNDLE_READER_H__

#include <string>
#include <vector>

#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class BundleReader
 * @brief @~english BundleReader is an interface for reading sequence of bytes.
 * @~chinese BundleReader提供了接口用于读取字节序列
 * @js NA
 * @lua NA
 */
class BundleReader: public cocos2d::Ref
{
public:
    /**
     * Constructor.
     */
    BundleReader();
    
    /**
     * Destructor.
     */
    ~BundleReader();
    
    /**
     * @~english Initialise
     * @~chinese 初始化
     * @param buffer @~english The data buffer pointer
     * @~chinese 数据缓冲指针
     * @param length @~english The data buffer size
     * @~chinese 数据缓冲大小
     */
    void init(char* buffer, ssize_t length);

    /**
     * @~english Reads an array of elements.
     * @~chinese 读取一系列元素
     * @param ptr   @~english The pointer to the memory to copy into.
     *              The available size should be at least bytes.
     * @~chinese 指向被拷贝结果的指针，该指针所在处的内存大小必须能够存放所有读取元素
     * @param size  @~english The size of each element to be read, in bytes.
     * @~chinese 每个元素的数据大小，以字节计
     * @param count @~english The number of elements to read.
     * @~chinese 需要读取的元素个数
     * @return @~english The number of elements read.
     * @~chinese 读取的元素个数
     */
    ssize_t read(void* ptr, ssize_t size, ssize_t count);

    /**
     * @~english Reads a line from the buffer.
     * @~chinese 按行读取数据，并将其放入指定的缓冲中
     * @param num @~english The amount of lines to reads
     * @~chinese 需要读取的行数
     * @param line @~english The result
     * @~chinese 缓冲区域
     * @return @~english The result, same as line.
     * @~chinese 被读取缓冲区的指针，与line参数等同
     */
    char* readLine(int num, char* line);

    /**
     * @~english Check if the file pointer is at the end of the buffer or not.
     * @~chinese 检查当前的文件指针(流指针)是否在缓冲区的结尾
     * @return @~english Returns true if the end of the buffer has been reached, otherwise returns false.
     * @~chinese 如果在缓存区末尾返回true，反之返回false
     */
    bool eof();

    /**
     * @~english Returns the length of the buffer in bytes.
     * @~chinese 返回缓冲大小，以字节计
     */
    ssize_t length();

    /**
     * @~english Returns the position of the file pointer.
     * @~chinese 返回当前文件指针（流指针）所在缓冲区的位置
     * @return @~english @~english The position of the file pointer
     * @~chinese 文件指针在缓冲区的位置
     */
    ssize_t tell();

    /**
     * @~english Sets the position of the file pointer.
     * @~chinese 设置文件指针（流指针）的位置，最终位置等于 基位置 + 偏移量
     * @param offset @~english The offset
     * @~chinese 位置的偏移量
     * @param origin @~english The base position.
     * @~chinese 位置的基位置
     * @return @~english The result of the seek
     * @~chinese 设置结果
     */
    bool seek(long int offset, int origin);

    /**
     * @~english Sets the file pointer at the start of the file.
     * @~chinese 将文件指针（流指针）设为文件的开始位置
     * @return @~english The result of the rewind.
     * @~chinese 设置结果
     */
    bool rewind();

    /**
     * @~english Read binary typed value.
     * @~chinese 以二进制方式读取指定类型的值
     * @param ptr @~english The specified type pointer. 
     * @~chinese 指定类型的数据接受指针
     * @return @~english The result of the read.
     * @~chinese 读取结果
     */
    template<typename T> bool read(T* ptr);

    /**
     * Read binary typed value array.
     * @~chinese 以二进制方式读取指定类型的值数组
     * @param length @~english Length of the array @~chinese 数组的长度
     * @param values @~english Output array to store the result @~chinese 用于保存结果的数组
     * @return the result of the read.
     */
    template<typename T> bool readArray(unsigned int* length, std::vector<T>* values);

    /**
     * @~english Read the string from the bundle, first read length, then read string text.
     * @~chinese 从bundle中读取字符串，首先将会读取长度，然后读取字符串的文本
     * @return @~english The result string.
     * @~chinese 返回被读取的字符串
     */
    std::string readString();

    /**
     * @~english Read the matrix.
     * @~chinese 读取矩阵
     * @note @~english the matrix type must be the 4*4 float matrix
     * @~chinese 该矩阵必须是4*4的float型矩阵
     * @param m @~english The result matrix.
     * @~chinese 目标矩阵
     * @return @~english The result of the reading.
     * @~chinese 读取的结果
     */
    bool readMatrix(float* m);

private:
    ssize_t _position;
    ssize_t  _length;
    char* _buffer;
};

/// @cond 

/**
* @~english Template read routines
* @~chinese 用于读取Bundle单个数据的模板函数
* @param ptr  @~english The generic type pointer to get the value.
* @~chinese 用以接收数据的泛型指针
* @return @~english The result of the load.
* @~chinese 读取结果
*/
template<typename T>
inline bool BundleReader::read(T *ptr)
{
    return (read(ptr, sizeof(T), 1) == 1);
}

/**
* @~english Template function to read array of value.
* @~chinese 用于从bundle中读取数组的模板函数
* @param length @~english The length of the array.
* @~chinese 数组的长度
* @param values @~english The result array of value.
* @~chinese 获取数据的接受数组
* @return @~english The result of the reading.
* @~chinese 读取结果
*/
template<typename T>
inline bool BundleReader::readArray(unsigned int *length, std::vector<T> *values)
{
    if (!read(length))
    {
        return false;
    }
    
    if (*length > 0 && values)
    {
        values->resize(*length);
        if (read(&(*values)[0], sizeof(T), *length) != *length)
        {
            return false;
        }
    }
    return true;
}

/**
* @~english Specalization for char
* @~chinese 模板函数的特化版本，专用于读取字符
*/
template<>
inline bool BundleReader::read<char>(char *ptr)
{
    if (read(ptr, sizeof(char), 1) == 1)
    {
        return true;
    }
    else
    {
        *ptr = -1;
        return false;
    }
}

/**
* @~english Specalization for std::string
* @~chinese 模板函数的特化版本，专门用于读取std::string型字符串
*/
template<>
inline bool BundleReader::read<std::string>(std::string *ptr)
{
    CCLOG("can not read std::string, use readString() instead");
    return false;
}

/**
* @~english Template function to read array of value.
* @~chinese 用于从bundle中读取字符串数组的模板函数特化版本
* @param length @~english The length of the array.
* @~chinese 数组的长度
* @param values @~english The result array of value.
* @~chinese 获取数据接受字符串数组
* @return @~english The result of the reading.
* @~chinese 读取结果
*/
template<>
inline bool BundleReader::readArray<std::string>(unsigned int *length, std::vector<std::string> *values)
{
    if (!read(length))
    {
        return false;
    }
    values->clear();
    if (*length > 0 && values)
    {
        for (int i = 0; i < (int)*length; ++i)
        {
            values->push_back(readString());
        }
    }
    return true;
}

/// @endcond

// end of 3d group
/// @}

NS_CC_END

#endif
