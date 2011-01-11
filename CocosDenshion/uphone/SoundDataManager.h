#ifndef _SOUND_DATA_MANAGER_H_
#define _SOUND_DATA_MANAGER_H_

#include "ResourceHandle.h"
#include <map>
#include "uthash.h"
#include "SimpleAudioEngine.h"
#include <string>
#include "TG3.h"

namespace CocosDenshion {

/**
@struct tEffectElement
@brief  The struct of hash table elements
*/
typedef struct _hashElement
{
    char                FileName[MAX_PATH];
    unsigned char*      pDataBuffer;
    int                 nDataSize;
    UT_hash_handle		hh;
} tEffectElement;

/**
@class SoundDataManager
@brief The manager of sound data
*/
class SoundDataManager
{
public:
    SoundDataManager();
    ~SoundDataManager();

    /**
    @brief Set the resource entry,it's only used on platform-uphone now
    */
    void setResEntry(const void* pResEntry);

    /**
    @brief set the sound ResInfo,it's only used on platform-uphone now
    */
    void setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount);

    /**
    @brief Load the sound data
    @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
    */
    void  loadSoundData(const char* pszFilePath);

    /**
    @brief Get the sound data by SoundID
    @param pFileName The sound file name(have the path)
    @return If find succeed,return the pointer of hash table element;or return NULL
    */
    tEffectElement* getSoundData(const char* pFileName);

    /**
    @brief Unload the sound effect element by SoundID
    @param pFileName The sound file name(have the path)
    */
    void unloadEffect(const char* pFileName);

    /**
    @brief Unload all effect elements
    */
    void removeAllEffects();

private:
    void loadFromResourceInfo(const char* pFileKey);
    void loadFromFile(const char* pFilePath);

private:
    ResourceHandle* m_pHRes;

    // use hash map to save the effects loaded
    struct _hashElement	*   m_pEffects;

    typedef std::map<std::string, int> SoundInfoMap;
    SoundInfoMap* m_pSoundMap;
};

} // end of namespace CocosDenshion

#endif
