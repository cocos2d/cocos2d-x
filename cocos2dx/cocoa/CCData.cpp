#include <string.h>
#include "CCData.h"

NS_CC_BEGIN

CCData::CCData(unsigned char *pBytes, const unsigned long nSize)
{
    m_nSize = nSize;
    m_pBytes = new unsigned char[m_nSize];
    memcpy(m_pBytes, pBytes, m_nSize);
}

CCData::CCData(CCData *pData)
{
    m_nSize = pData->m_nSize;
    m_pBytes = new unsigned char[m_nSize];
    memcpy(m_pBytes, pData->m_pBytes, m_nSize);
}

CCData::~CCData()
{
    CC_SAFE_DELETE_ARRAY(m_pBytes);
}

unsigned char* CCData::getBytes() const
{
    return m_pBytes;
}

unsigned long CCData::getSize() const
{
    return m_nSize;
}

NS_CC_END
