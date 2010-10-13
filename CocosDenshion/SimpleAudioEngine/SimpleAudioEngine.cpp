#include "SimpleAudioEngine.h"
#include "TG3.h"
#include <map>
#include <string>

#define BREAK_IF(cond)  if (cond) break;

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

static SimpleAudioEngine s_SharedAudioEngie;
static SoundResHandle    s_HSoundRes;

typedef std::map<std::string, int> SoundInfoMap;
static SoundInfoMap s_SoundMap;

SimpleAudioEngine::SimpleAudioEngine()
: m_nBackgroundMusicVolume(100)
, m_nEffectsVolume(100)
, m_bWillPlayBackgroundMusic(false)
, m_pEffects(NULL)
{
    m_pEffectPlayers = new PlayerArray();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
    removeAllEffects();
    removeAllEffectPlayers();
}

SimpleAudioEngine* SimpleAudioEngine::getSharedSimpleAudioEngine()
{
    return &s_SharedAudioEngie;
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    int nTimes = 1;
    if (bLoop)
    {
        nTimes = -1;
    }

    if (FileUtils::isFileExisted(pszFilePath))
    {
        m_obBackPlayer.PlaySoundFile(pszFilePath, nTimes);
    }
    else
    {
        do 
        {
            SoundInfoMap::iterator iter;
            iter = s_SoundMap.find(pszFilePath);
            BREAK_IF(iter == s_SoundMap.end());

            unsigned int nSize = 0;
            const void* pData = s_HSoundRes.LoadConstRawData(iter->second, &nSize);
            BREAK_IF(!pData);

            m_obBackPlayer.PlaySoundFromMem((unsigned char*)pData, nSize, pszFilePath, nTimes);
        } while (0);
    }
}

void SimpleAudioEngine::stopBackgroundMusic()
{
    m_obBackPlayer.Stop();
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    m_obBackPlayer.Pause();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    m_obBackPlayer.Resume();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    m_obBackPlayer.Rewind();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return m_bWillPlayBackgroundMusic;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return m_obBackPlayer.IsPlaying();
}

// properties
int SimpleAudioEngine::GetBackgroundMusicVolume()
{
    return m_nBackgroundMusicVolume;
}

void SimpleAudioEngine::SetBackgroundMusicVolume(int volume)
{
    m_obBackPlayer.SetVolumeValue(volume);
    m_nBackgroundMusicVolume = volume;
}

int SimpleAudioEngine::GetEffectsVolume()
{
    return m_nEffectsVolume;
}

void SimpleAudioEngine::SetEffectsVolume(int volume)
{
    PlayerArrayIterator iter;

    for (iter = m_pEffectPlayers->begin(); iter != m_pEffectPlayers->end(); ++iter)
    {
        if (*iter)
        {
            (*iter)->SetVolumeValue(volume);
        }
    }

    m_nEffectsVolume = volume;
}


// for sound effects
int SimpleAudioEngine::playEffect(const char* pszFilePath)
{
    int nSoundID = preloadEffect(pszFilePath);

    if (nSoundID > 0)
    {
        playPreloadedEffect(nSoundID);
    }

    return nSoundID;
}

void SimpleAudioEngine::stopEffect(int nSoundId)
{
    SoundPlayer* pPlayer = NULL;

    // find the players are playing the effect
    PlayerArrayIterator iter;
    for (iter = m_pEffectPlayers->begin(); iter != m_pEffectPlayers->end(); ++iter)
    {
        if ((*iter) && pPlayer->GetCurrentSoundID() == nSoundId)
        {
            pPlayer->Stop();
        }
    }
}

int SimpleAudioEngine::preloadEffect(const char* pszFilePath)
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

void SimpleAudioEngine::unloadEffect(int nSoundId)
{
    do 
    {
        tHashElement* pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nSoundId, pElement);
        BREAK_IF(!pElement);

        delete [] (pElement->pDataBuffer);
        HASH_DEL(m_pEffects, pElement);
        free(pElement);
    } while (0);
}

void SimpleAudioEngine::playPreloadedEffect(int nSoundId)
{
    do 
    {
        tHashElement* pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nSoundId, pElement);
        BREAK_IF(!pElement);

        SoundPlayer* pPlayer = NULL;
        bool bLoaded = false;

        // find the not playing player in m_pEffectPlayers
        PlayerArrayIterator iter;
        for (iter = m_pEffectPlayers->begin(); iter != m_pEffectPlayers->end(); ++iter)
        {
            if ((*iter) && !(*iter)->IsPlaying())
            {
                pPlayer = (*iter);
                if (pPlayer->GetCurrentSoundID() == nSoundId)
                {
                    bLoaded = true;
                    break;
                }
            }
        }

        // not find player,new one player
        if (!pPlayer)
        {
            pPlayer = new SoundPlayer();
            m_pEffectPlayers->push_back(pPlayer);

            // set the player volume
            pPlayer->SetVolumeValue(m_nEffectsVolume);
        }

        // play the sound and record the player
        if (bLoaded)
        {
            pPlayer->Rewind();
        }
        else
        {
            pPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize, pElement->FileName);
            pPlayer->SetCurrentSoundID(nSoundId);
        }
    } while (0);
}

void SimpleAudioEngine::removeAllEffects()
{
    for (tHashElement *pElement = m_pEffects; pElement != NULL; )
    {
        int nSoundID = pElement->nSoundID;
        pElement = (tHashElement*)pElement->hh.next;
        unloadEffect(nSoundID);
    }
}

void SimpleAudioEngine::removeAllEffectPlayers()
{
    PlayerArrayIterator iter;

    for (iter = m_pEffectPlayers->begin(); iter != m_pEffectPlayers->end(); ++iter)
    {
        if (*iter)
        {
            delete *iter;
        }
    }

    m_pEffectPlayers->clear();
    delete m_pEffectPlayers;
}

int  SimpleAudioEngine::loadFromResourceInfo(const char* pFileKey)
{
    SoundInfoMap::iterator iter;
    iter = s_SoundMap.find(pFileKey);
    int nSoundID = 0;

    do 
    {
        BREAK_IF(iter == s_SoundMap.end());

        // if we have loaded the file before,break
        tHashElement *pElement = NULL;
        HASH_FIND_INT(m_pEffects, &iter->second, pElement);
        if (pElement)
        {
            nSoundID = iter->second;
            break;
        }

        unsigned int nSize = 0;
        const void* pData = s_HSoundRes.LoadConstRawData(iter->second, &nSize);
        BREAK_IF(!pData);

         // copy the data
        unsigned char* pSoundData = new unsigned char[nSize];
        MemCopy(pSoundData, pData, nSize);

        // record the id
        nSoundID = iter->second;

        // add the data to hash map
        pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
        pElement->nSoundID    = nSoundID;
        pElement->pDataBuffer = pSoundData;
        pElement->nDataSize   = nSize;
        pElement->FileName    = pFileKey;
        HASH_ADD_INT(m_pEffects, nSoundID, pElement);
    } while (0);

    return nSoundID;
}

int  SimpleAudioEngine::loadFromFile(const char* pFilePath)
{
    int nSoundID = 0;

    do
    {
        int nID = BKDRHash(pFilePath);

        // if we have loaded the file before,break
        tHashElement *pElement = NULL;
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
        pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
        pElement->nSoundID    = nSoundID;
        pElement->pDataBuffer = buffer;
        pElement->nDataSize   = nBufferSize;
        pElement->FileName    = "";
        HASH_ADD_INT(m_pEffects, nSoundID, pElement);
    } while (0);

    return nSoundID;
}

void SimpleAudioEngine::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
{
    // first, clear the map before
    if (!s_SoundMap.empty())
    {
        s_SoundMap.clear();
    }

    // second, insert the pairs
    for (int i = 0; i < nCount; ++i)
    {
        std::string name = (ResInfo[i]).FileName;
        int nResID       = (ResInfo[i]).nResID;

        s_SoundMap.insert(SoundInfoMap::value_type(name, nResID));
    }
}

void SimpleAudioEngine::setResourceEntry(const AppResourceEntry* pResEntry)
{
    if (pResEntry)
    {
        s_HSoundRes.setResourceEntry(pResEntry);
    }
}

//////////////////////////////////////////////////
//
// SoundResHandle
//
//////////////////////////////////////////////////
SoundResHandle::SoundResHandle()
:m_pResLib(NULL)
{
}

SoundResHandle::~SoundResHandle()
{
    release();
}

void SoundResHandle::release()
{
    if (m_pResLib)
    {
        delete m_pResLib;
        m_pResLib = NULL;
    }
}

void SoundResHandle::setResourceEntry(const AppResourceEntry* pResEntry)
{
    release();

    m_pResLib = new TResourceLib(pResEntry);
}

const void* SoundResHandle::LoadConstRawData(int nResID, unsigned int* nLen)
{
    const void* pResult = NULL;

    if (m_pResLib)
    {
        pResult = m_pResLib->LoadConstRawData(nResID, nLen);
    }

    return pResult;
}
