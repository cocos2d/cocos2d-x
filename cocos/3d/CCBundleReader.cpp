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

#include "CCBundleReader.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

BundleReader::BundleReader()
{
    _buffer = nullptr;
    _position = 0;
    _length = 0;
};

BundleReader::~BundleReader()
{
    
};

void BundleReader::init(char* buffer, ssize_t length)
{
    _position = 0;
    _buffer  = buffer;
    _length = length;
}

ssize_t BundleReader::read(void* ptr, ssize_t size, ssize_t count)
{
    if (!_buffer || eof())
    {
        CCLOG("warning: bundle reader out of range");
        return 0;
    }

    ssize_t validCount;
    ssize_t validLength = _length - _position;
    ssize_t needLength = size*count;
    char* ptr1 = (char*)ptr;
    if(validLength < needLength)
    {
        validCount = validLength/size;
        ssize_t readLength = size*validCount;
        memcpy(ptr1,(char*)_buffer+_position,readLength);
        ptr1 += readLength;
        _position += readLength;
        readLength = validLength - readLength;
        if(readLength>0)
        {
            memcpy(ptr1,(char*)_buffer+_position,readLength);
            _position += readLength;
            validCount+=1;
        }
        CCLOG("warning: bundle reader out of range");
    }
    else
    {
        memcpy(ptr1,(char*)_buffer+_position,needLength);
        _position += needLength;
        validCount = count;
    }

    return validCount;
}

char* BundleReader::readLine(int num,char* line)
{
    if (!_buffer)
        return 0;

    char* buffer = (char*)_buffer+_position;
    char* p = line;
    char c;
    ssize_t readNum = 0;
    while((c=*buffer) != 10 && readNum < (ssize_t)num && _position < _length)
    {
        *p = c;
        p++;
        buffer++;
        _position++;
        readNum++;
    }
    *p = '\0';

    return line;
}

bool BundleReader::eof()
{
    if (!_buffer)
        return true;
    
    return ((ssize_t)tell()) >= length();
}

ssize_t BundleReader::length()
{
    return _length;
}

ssize_t BundleReader::tell()
{
    if (!_buffer)
        return -1;
    return _position;
}

bool BundleReader::seek(long int offset, int origin)
{
    if (!_buffer)
        return false;

    if(origin == SEEK_CUR)
    {
        _position += offset;
    }
    else if(origin == SEEK_SET)
    {
        _position = offset;
    }
    else if(origin == SEEK_END)
    {
        _position = _length+offset;
    }
    else
        return false;

    return true;
}

bool BundleReader::rewind()
{
    if (_buffer != nullptr)
    {
        _position = 0;
        return true;
    }
    return false;
}

std::string BundleReader::readString()
{
    unsigned int length;
    if(read(&length, 4, 1) != 1)
    {
        return std::string();
    }

    std::string str;
    
    ssize_t validLength = _length - _position;
    if (length > 0 && static_cast<ssize_t>(length) <= validLength)
    {
        str.resize(length);
        if (read(&str[0], 1, length) != length)
        {
            return std::string();
        }
    }
    
    return str;
}

bool BundleReader::readMatrix(float* m)
{
    return (read(m, sizeof(float), 16) == 16);
}

NS_CC_END
