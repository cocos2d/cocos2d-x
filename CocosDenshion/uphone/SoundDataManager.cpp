#include "SoundDataManager.h"
#include "FileUtils.h"
#include "SoundPlayer.h"

#define BREAK_IF(cond)      if (cond) break;

unsigned int BKDRHash(const char *str)
{
    unsigned int seed = 31; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

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

int SoundDataManager::loadSoundData(const char* pszFilePath)
{
    int nSoundID = 0;

    if (! FileUtils::isFileExisted(pszFilePath))
    {
        // if the file is not existed, find in the ResourceInfo
        nSoundID = loadFromResourceInfo(pszFilePath);
    }
    else
    {
        // load effect info from file
        nSoundID = loadFromFile(pszFilePath);
    }

    return nSoundID;
}

tEffectElement* SoundDataManager::getSoundData(int nSoundID)
{
    tEffectElement* pElement = NULL;
    HASH_FIND_INT(m_pEffects, &nSoundID, pElement);

    return pElement;
}

void SoundDataManager::unloadEffect(int nSoundID)
{
    do 
    {
        tEffectElement* pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nSoundID, pElement);
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
        int nSoundID = pElement->nSoundID;
        pElement = (tEffectElement*)pElement->hh.next;
        unloadEffect(nSoundID);
    }
}

int SoundDataManager::loadFromResourceInfo(const char* pFileKey)
{
    SoundInfoMap::iterator iter;
    iter = m_pSoundMap->find(pFileKey);
    int nSoundID = 0;

    do 
    {
        BREAK_IF(iter == m_pSoundMap->end());

        // if we have loaded the file before,break
        tEffectElement *pElement = NULL;
        HASH_FIND_INT(m_pEffects, &iter->second, pElement);
        if (pElement)
        {
            nSoundID = iter->second;
            break;
        }

        unsigned int nSize = 0;
        const void* pData = m_pHRes->LoadConstRawData(iter->second, &nSize);
        BREAK_IF(!pData);

        // copy the data
        unsigned char* pSoundData = new unsigned char[nSize];
        MemCopy(pSoundData, pData, nSize);

        // record the id
        nSoundID = iter->second;

        // add the data to hash map
        pElement = (tEffectElement*)calloc(sizeof(*pElement), 1);
        pElement->nSoundID    = nSoundID;
        pElement->pDataBuffer = pSoundData;
        pElement->nDataSize   = nSize;
        pElement->FileName    = pFileKey;
        pElement->nPlayerSoundID = -1;
        HASH_ADD_INT(m_pEffects, nSoundID, pElement);
    } while (0);

    return nSoundID;
}

int SoundDataManager::loadFromFile(const char* pFilePath)
{
    int nSoundID = 0;

    do
    {
        int nID = BKDRHash(pFilePath);

        // if we have loaded the file before,break
        tEffectElement *pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nID, pElement);
        if (pElement)
        {
            nSoundID = nID;
            break;
        }

        // calculate the buffer size we needed
        SoundPlayer TempPlayer;
        int nBufferSize = TempPlayer.GetFileBufferSize(pFilePath);
        // can not calculate the size,load failed
        BREAK_IF(nBufferSize < 0);

        // load the file data
        unsigned char* buffer = NULL;
        buffer = new unsigned char[nBufferSize];
        BREAK_IF(!buffer);
        int nSize = TempPlayer.DecodeFile(buffer, nBufferSize, pFilePath);
        BREAK_IF(nSize < 0);

        // record the id
        nSoundID = nID;

        // add the data to hash map
        pElement = (tEffectElement*)calloc(sizeof(*pElement), 1);
        pElement->nSoundID    = nSoundID;
        pElement->pDataBuffer = buffer;
        pElement->nDataSize   = nBufferSize;
        pElement->FileName    = "";
        pElement->nPlayerSoundID = -1;
        HASH_ADD_INT(m_pEffects, nSoundID, pElement);
    } while (0);

    return nSoundID;
}
