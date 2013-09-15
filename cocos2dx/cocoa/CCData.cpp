/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

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

#include <string.h>
#include "CCData.h"
#include "platform/CCCommon.h"

NS_CC_BEGIN

Data::Data(unsigned char *pBytes, const unsigned long nSize)
{
    _size = nSize;
    _bytes = new unsigned char[_size];
    memcpy(_bytes, pBytes, _size);
}

Data::Data(Data *pData)
{
    _size = pData->_size;
    _bytes = new unsigned char[_size];
    memcpy(_bytes, pData->_bytes, _size);
}

Data::~Data()
{
    CCLOGINFO("deallocing Data: %p", this);
    CC_SAFE_DELETE_ARRAY(_bytes);
}

unsigned char* Data::getBytes() const
{
    return _bytes;
}

unsigned long Data::getSize() const
{
    return _size;
}

NS_CC_END
