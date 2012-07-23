#ifndef _SOUND_DATA_MANAGER_H_
#define _SOUND_DATA_MANAGER_H_

#include <map>
#include "uthash.h"
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
    // use hash map to save the effects loaded
    struct _hashElement	*   m_pEffects;
};

} // end of namespace CocosDenshion

#endif
