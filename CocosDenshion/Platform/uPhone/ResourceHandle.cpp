#include "ResourceHandle.h"
#include "TG3.h"

ResourceHandle::ResourceHandle()
:m_pResLib(NULL)
{
}

ResourceHandle::~ResourceHandle()
{
    release();
}

void ResourceHandle::release()
{
    if (m_pResLib)
    {
        delete m_pResLib;
        m_pResLib = NULL;
    }
}

void ResourceHandle::setResourceEntry(const void* pResEntry)
{
    release();

    m_pResLib = new TResourceLib((const AppResourceEntry*)pResEntry);
}

const void* ResourceHandle::LoadConstRawData(int nResID, unsigned int* nLen)
{
    const void* pResult = NULL;

    if (m_pResLib)
    {
        pResult = m_pResLib->LoadConstRawData(nResID, nLen);
    }

    return pResult;
}
