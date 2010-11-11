#ifndef _SOUND_DATA_MANAGER_H_
#define _SOUND_DATA_MANAGER_H_

#include "ResourceHandle.h"
#include <map>
#include "uthash.h"
#include "SimpleAudioEngine.h"
#include <string>

typedef struct _hashElement
{
    int                 nSoundID;
    unsigned char*      pDataBuffer;
    const char*         FileName;
    int                 nDataSize;
    int                 nPlayerSoundID;
    UT_hash_handle		hh;
} tEffectElement;

class SoundDataManager
{
public:
    SoundDataManager();
    ~SoundDataManager();

    void setResEntry(const void* pResEntry);
    void setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount);

    int  loadSoundData(const char* pszFilePath);
    tEffectElement* getSoundData(int nSoundID);

    void unloadEffect(int nSoundID);
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
