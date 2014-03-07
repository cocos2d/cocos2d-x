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

#include "CCPlatformMacros.h"
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
    
    // Assignment operator
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
    
    /** Copies the buffer pointer and its size.
     *  @note This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     *  @see Data::fastSet
     */
    void copy(unsigned char* bytes, const ssize_t size);
    
    /** Fast set the buffer pointer and its size. Please use it carefully.
     *  @param bytes The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     *  @note 1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);
    
    /** Clears data, free buffer and reset data size */
    void clear();
    
    /** Check whether the data is null. */
    bool isNull() const;
    
private:
    void move(Data& other);
    
private:
    unsigned char* _bytes;
    ssize_t _size;
};

NS_CC_END

#endif // __CCDATA_H__
