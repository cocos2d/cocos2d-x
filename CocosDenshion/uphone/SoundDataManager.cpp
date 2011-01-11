#include "SoundDataManager.h"
#include "FileUtils.h"
#include "SoundPlayer.h"

#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

SoundDataManager::SoundDataManager()
: m_pEffects(NULL)
{
    m_pHRes     = new ResourceHandle;
    m_pSoundMap = new SoundInfoMap;
}

SoundDataManager::~SoundDataManager()
{
    removeAllEffects();

    if (m_pHRes)
    {
        delete m_pHRes;
        m_pHRes = NULL;
    }

    if (m_pSoundMap)
    {
        delete m_pSoundMap;
        m_pSoundMap = NULL;
    }
}

void SoundDataManager::setResEntry(const void* pResEntry)
{
    if (pResEntry)
    {
        m_pHRes->setResourceEntry(pResEntry);
    }
}

void SoundDataManager::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
{
    // first, clear the map before
    if (!m_pSoundMap->empty())
    {
        m_pSoundMap->clear();
    }

    // second, insert the pairs
    for (int i = 0; i < nCount; ++i)
    {
        std::string name = (ResInfo[i]).FileName;
        int nResID       = (ResInfo[i]).nResID;

        m_pSoundMap->insert(SoundInfoMap::value_type(name, nResID));
    }
}

void SoundDataManager::loadSoundData(const char* pszFilePath)
{
    SoundInfoMap::iterator iter;
    iter = m_pSoundMap->find(pszFilePath);

    if (iter != m_pSoundMap->end())
    {
        // if the file is not existed, find in the ResourceInfo
        loadFromResourceInfo(pszFilePath);
    }
    else
    {
        // load effect info from file
        loadFromFile(pszFilePath);
    }
}

tEffectElement* SoundDataManager::getSoundData(const char* pFileName)
{
    tEffectElement* pElement = NULL;
    HASH_FIND_STR(m_pEffects, pFileName, pElement);

    return pElement;
}

void SoundDataManager::unloadEffect(const char* pFileName)
{
    do 
    {
        tEffectElement* pElement = NULL;
        HASH_FIND_STR(m_pEffects, pFileName, pElement);
        BREAK_IF(!pElement);

        delete [] (pElement->pDataBuffer);
        HASH_DEL(m_pEffects, pElement);
        free(pElement);
    } while (0);
}

void SoundDataManager::removeAllEffects()
{
    for (tEffectElement *pElement = m_pEffects; pElement != NULL; )
    {
        std::string fName = pElement->FileName;
        pElement = (tEffectElement*)pElement->hh.next;
        unloadEffect(fName.c_str());
    }
}

void SoundDataManager::loadFromResourceInfo(const char* pFileKey)
{
    SoundInfoMap::iterator iter;
    iter = m_pSoundMap->find(pFileKey);

    do 
    {
        BREAK_IF(iter == m_pSoundMap->end());

        // if we have loaded the file before,break
        tEffectElement *pElement = NULL;
        HASH_FIND_STR(m_pEffects, pFileKey, pElement);
        if (pElement)
        {
            break;
        }

        unsigned int nSize = 0;
        const void* pData = m_pHRes->LoadConstRawData(iter->second, &nSize);
        BREAK_IF(!pData);

        // copy the data
        unsigned char* pSoundData = new unsigned char[nSize];
        MemCopy(pSoundData, pData, nSize);

        // add the data to hash map
        pElement = (tEffectElement*)calloc(sizeof(*pElement), 1);
        pElement->pDataBuffer = pSoundData;
        pElement->nDataSize   = nSize;
        strcpy(pElement->FileName, pFileKey);
        HASH_ADD_STR(m_pEffects, FileName, pElement);
    } while (0);
}

void SoundDataManager::loadFromFile(const char* pFilePath)
{
    do
    {
        BREAK_IF(! FileUtils::isFileExisted(pFilePath));

        // if we have loaded the file before,break
        tEffectElement *pElement = NULL;
        HASH_FIND_STR(m_pEffects, pFilePath, pElement);
        if (pElement)
        {
            break;
        }

        // load the file data
        unsigned long nBufferSize = 0;
        unsigned char* buffer = FileUtils::getFileData(pFilePath, "rb", &nBufferSize);
        BREAK_IF(!buffer || nBufferSize <= 0);

        // add the data to hash map
        pElement = (tEffectElement*)calloc(sizeof(*pElement), 1);
        pElement->pDataBuffer = buffer;
        pElement->nDataSize   = nBufferSize;
        strcpy(pElement->FileName, pFilePath);
        HASH_ADD_STR(m_pEffects, FileName, pElement);
    } while (0);
}

} // end of namespace CocosDenshion
