#include <string.h>
#include "CCData.h"

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
