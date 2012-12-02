#include "CCData.h"

NS_CC_EXT_BEGIN

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

unsigned char* CCData::getBytes()
{
    return m_pBytes;
}

NS_CC_EXT_END
