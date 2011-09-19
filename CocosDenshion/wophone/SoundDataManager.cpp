#include "SoundDataManager.h"
#include "FileUtils.h"
#include "SoundPlayer.h"

#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

SoundDataManager::SoundDataManager()
: m_pEffects(NULL)
{
}

SoundDataManager::~SoundDataManager()
{
    removeAllEffects();
}

void SoundDataManager::loadSoundData(const char* pszFilePath)
{
    do
    {
        BREAK_IF(! FileUtils::isFileExisted(pszFilePath));

        // if we have loaded the file before,break
        tEffectElement *pElement = NULL;
        HASH_FIND_STR(m_pEffects, pszFilePath, pElement);
        if (pElement)
        {
            break;
        }

        // load the file data
        unsigned long nBufferSize = 0;
        unsigned char* buffer = FileUtils::getFileData(pszFilePath, "rb", &nBufferSize);
        BREAK_IF(!buffer || nBufferSize <= 0);

        // add the data to hash map
        pElement = (tEffectElement*)calloc(sizeof(*pElement), 1);
        pElement->pDataBuffer = buffer;
        pElement->nDataSize   = nBufferSize;
        strcpy(pElement->FileName, pszFilePath);
        HASH_ADD_STR(m_pEffects, FileName, pElement);
    } while (0);
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

} // end of namespace CocosDenshion
