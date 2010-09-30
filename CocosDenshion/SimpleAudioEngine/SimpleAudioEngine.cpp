#include "SimpleAudioEngine.h"

#define BREAK_IF(cond)  if (cond) break;

unsigned int BKDRHash(const char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

static SimpleAudioEngine s_SharedAudioEngie;

SimpleAudioEngine::SimpleAudioEngine()
: m_nBackgroundMusicVolume(100)
, m_nEffectsVolume(100)
, m_bWillPlayBackgroundMusic(false)
, m_pEffects(NULL)
{
    m_EffectPlayers.resize(0);
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
    if (bLoop)
    {
        m_obBackPlayer.PlaySoundFile(pszFilePath, -1);
    }
    else
    {
        m_obBackPlayer.PlaySoundFile(pszFilePath);
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

    for (iter = m_EffectPlayers.begin(); iter != m_EffectPlayers.end(); ++iter)
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
    do 
    {
        // find the data in hash map
        tHashElement* pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nSoundId, pElement);
        BREAK_IF(!pElement);

        // get the pointer of the player
        SoundPlayer* pPlayer = pElement->pPlayer;
        BREAK_IF(!pPlayer);

        // stop play add set no player playing nSoundID
        pPlayer->Stop();
        pElement->pPlayer = NULL;
    } while (0);
}

int SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    SoundPlayer TempPlayer;
    int         nSoundID = 0;

    do
    {
        // calculate the hash value of the file name
        nSoundID = BKDRHash(pszFilePath);

        // if we have loaded the file before,break
        tHashElement *pElement = NULL;
        HASH_FIND_INT(m_pEffects, &nSoundID, pElement);
        BREAK_IF(pElement);

        // calculate the buffer size we needed
        int nBufferSize = TempPlayer.GetFileBufferSize(pszFilePath);
        if (nBufferSize < 0)
        {
            // can not calculate the size,load failed
            nSoundID = 0;
            break;
        }

        // load the file data
        unsigned char* buffer = NULL;
        buffer = new unsigned char[nBufferSize];
        if (!buffer)
        {
            nSoundID = 0;
            break;
        }
        int nSize = TempPlayer.DecodeFile(buffer, nBufferSize, pszFilePath);
        if (nSize < 0)
        {
            nSoundID = 0;
            break;
        }

        // add the data to hash map
        pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
        pElement->nSoundID    = nSoundID;
        pElement->pDataBuffer = buffer;
        pElement->pPlayer     = NULL;
        pElement->nDataSize   = nBufferSize;
        HASH_ADD_INT(m_pEffects, nSoundID, pElement);
    } while (0);

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

        SoundPlayer* pPlayer = pElement->pPlayer;
        if (!pPlayer)
        {
            // find the not playing player in m_EffectPlayers
            PlayerArrayIterator iter;
            for (iter = m_EffectPlayers.begin(); iter != m_EffectPlayers.end(); ++iter)
            {
                if ((*iter) && !(*iter)->IsPlaying())
                {
                    pPlayer = (*iter);
                    break;
                }
            }

            // not find player,new one player
            if (!pPlayer)
            {
                pPlayer = new SoundPlayer();
                m_EffectPlayers.push_back(pPlayer);

                // set the player volume
                pPlayer->SetVolumeValue(m_nEffectsVolume);
            }
        }

        // play the sound and record the player
        pPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize);
        pElement->pPlayer = pPlayer;
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

    for (iter = m_EffectPlayers.begin(); iter != m_EffectPlayers.end(); ++iter)
    {
        if (*iter)
        {
            delete *iter;
        }
    }

    m_EffectPlayers.clear();
}
