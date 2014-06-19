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
#include "base/CCPlatformMacros.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

/**
 * Stream is an interface for reading and writing a sequence of bytes.
 */
class BundleReader: public cocos2d::Ref
{
public:
    ~BundleReader();

    static BundleReader* create(char* lpbuffer, unsigned int length);

    void close();

	/**
     * Reads an array of elements.
	 *
	 * @param ptr   The pointer to the memory to copy into.
	 *              The available size should be at least bytes.
	 * @param size  The size of each element to be read, in bytes.
	 * @param count The number of elements to read.
	 *
	 * @return The number of elements read.
     */
    size_t read(void* ptr, size_t size, size_t count);

	/**
     * Reads a line from the stream.
     */
	char* readLine(int num,char* line);

	 /**
     * Writes an array of elements.
     *
     * @param ptr   The pointer to the array of elements to be written.
     * @param size  The size of each element to be written, in bytes.
     * @param count The number of elements to write.
     *
     * @return The number of elements written.
     */
	size_t write(const void* ptr, size_t size, size_t count);

	/**
     * Returns true if the end of the stream has been reached.
     */
    bool eof();

	/**
     * Returns the length of the stream in bytes.
     */
    size_t length();

	/**
     * Returns the position of the file pointer.
     */
    long int tell();

	/**
     * Sets the position of the file pointer.
     */
    bool seek(long int offset, int origin);

	/**
	 * Sets the file pointer at the start of the file.
	 */
    bool rewind();

	/**
    * read binary typed value.
    */
	template<typename T> bool read(T* ptr);
	template<typename T> bool readArray(unsigned int* length, std::vector<T>* values);

	/**
	* first read length, then read string text
	*/
    std::string readString();
    bool readMatrix(float* m);

private:
    BundleReader();
    void init(char* lpbuffer, unsigned int length);

private:
    long int m_position;
    size_t  m_length;
    char* m_buffer;
};

// template read routines
template<typename T>
inline bool BundleReader::read(T *ptr)
{
    return (read(ptr, sizeof(T), 1) == 1);
}

/**
* template function to read array of value.
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
* specalization for char
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
* specalization for std::string
*/
template<>
inline bool BundleReader::read<std::string>(std::string *ptr)
{
    CCLOG("can not read std::string, use readString() instead");
    return false;
}

/**
* template function to read array of value.
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


NS_CC_END

#endif
