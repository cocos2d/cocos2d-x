#ifndef _SOUND_DATA_MANAGER_H_
#define _SOUND_DATA_MANAGER_H_

#include "ResourceHandle.h"
#include <map>
#include "uthash.h"
#include "SimpleAudioEngine.h"
#include <string>

/**
@struct tEffectElement
@brief  The struct of hash table elements
*/
typedef struct _hashElement
{
    int                 nSoundID;
    unsigned char*      pDataBuffer;
    const char*         FileName;
    int                 nDataSize;
    int                 nPlayerSoundID;
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
    @return Load success, return the SoundId;Or return 0
    */
    int  loadSoundData(const char* pszFilePath);

    /**
    @brief Get the sound data by SoundID
    @param nSoundID The soundID
    @return If find succeed,return the pointer of hash table element;or return NULL
    */
    tEffectElement* getSoundData(int nSoundID);

    /**
    @brief Unload the sound effect element by SoundID
    @param nSoundID The effect soundID
    */
    void unloadEffect(int nSoundID);

    /**
    @brief Unload all effect elements
    */
    void removeAllEffects();

private:
    int  loadFromResourceInfo(const char* pFileKey);
    int  loadFromFile(const char* pFilePath);

private:
    ResourceHandle* m_pHRes;

    // use hash map to save the effects loaded
    struct _hashElement	*   m_pEffects;

    typedef std::map<std::string, int> SoundInfoMap;
    SoundInfoMap* m_pSoundMap;
};

#endif
