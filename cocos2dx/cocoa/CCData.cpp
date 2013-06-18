#include <string.h>
#include "CCData.h"

NS_CC_BEGIN

CCData::CCData(unsigned char *pBytes, const unsigned long nSize)
{
    _size = nSize;
    _bytes = new unsigned char[_size];
    memcpy(_bytes, pBytes, _size);
}

CCData::CCData(CCData *pData)
{
    _size = pData->_size;
    _bytes = new unsigned char[_size];
    memcpy(_bytes, pData->_bytes, _size);
}

CCData::~CCData()
{
    CC_SAFE_DELETE_ARRAY(_bytes);
}

unsigned char* CCData::getBytes() const
{
    return _bytes;
}

unsigned long CCData::getSize() const
{
    return _size;
}

NS_CC_END
