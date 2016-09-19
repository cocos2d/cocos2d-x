/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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
     * This parameter is defined for convenient reference if a null Data object is needed.
     */
    static const Data Null;

    /**
     * Constructor of Data.
     */
    Data();

    /**
     * Copy constructor of Data.
     */
    Data(const Data& other);

    /**
     * Copy constructor of Data.
     */
    Data(Data&& other);

    /**
     * Destructor of Data.
     */
    ~Data();

    /**
     * Overloads of operator=.
     */
    Data& operator= (const Data& other);

    /**
     * Overloads of operator=.
     */
    Data& operator= (Data&& other);

    /**
     * Gets internal bytes of Data. It will return the pointer directly used in Data, so don't delete it.
     *
     * @return Pointer of bytes used internal in Data.
     */
    unsigned char* getBytes() const;

    /**
     * Gets the size of the bytes.
     *
     * @return The size of bytes of Data.
     */
    ssize_t getSize() const;

    /** Copies the buffer pointer and its size.
     *  @note This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     *  @see Data::fastSet
     */
    void copy(const unsigned char* bytes, const ssize_t size);

    /** Fast set the buffer pointer and its size. Please use it carefully.
     *  @param bytes The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     *  @note 1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);

    /**
     * Clears data, free buffer and reset data size.
     */
    void clear();

    /**
     * Check whether the data is null.
     *
     * @return True if the Data is null, false if not.
     */
    bool isNull() const;

    /**
     * Get the internal buffer of data and set data to empty state.
     *
     * The ownership of the buffer removed from the data object.
     * That is the user have to free the returned buffer.
     * The data object is set to empty state, that is internal buffer is set to nullptr
     * and size is set to zero.
     * Usage:
     * @code
     *  Data d;
     *  // ...
     *  ssize_t size;
     *  unsigned char* buffer = d.takeBuffer(&size);
     *  // use buffer and size
     *  free(buffer);
     * @endcode
     *
     * @param size Will fill with the data buffer size in bytes, if you do not care buffer size, pass nullptr.
     * @return the internal data buffer, free it after use.
     */
    unsigned char* takeBuffer(ssize_t* size);
private:
    void move(Data& other);

private:
    unsigned char* _bytes;
    ssize_t _size;
};


NS_CC_END

/** @} */
#endif // __CCDATA_H__
