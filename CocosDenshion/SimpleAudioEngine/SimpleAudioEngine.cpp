#include "SimpleAudioEngine.h"

#define BREAK_IF(cond)  if (cond) break;

static SimpleAudioEngine *s_pSharedAudioEngie = NULL;

SimpleAudioEngine::SimpleAudioEngine()
: m_nBackgroundMusicVolume(100)
, m_nEffectsVolume(100)
, m_bWillPlayBackgroundMusic(false)
{
    m_pEffectPlayers = new PlayerArray();
    m_pBackPlayer    = new SoundPlayer();
    m_pDataManager   = new SoundDataManager();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
    removeAllEffectPlayers();

    if (m_pBackPlayer)
    {
        delete m_pBackPlayer;
        m_pBackPlayer = NULL;
    }

    if (m_pDataManager)
    {
        delete m_pDataManager;
        m_pDataManager = NULL;
    }
}

SimpleAudioEngine* SimpleAudioEngine::getSharedEngine()
{
    if (s_pSharedAudioEngie == NULL)
    {
        s_pSharedAudioEngie = new SimpleAudioEngine;
    }
    
    return s_pSharedAudioEngie;
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    int nTimes = 1;
    if (bLoop)
    {
        nTimes = -1;
    }

    int nSoundID = m_pDataManager->loadSoundData(pszFilePath);
    tEffectElement* pElement = m_pDataManager->getSoundData(nSoundID);

    if (pElement)
    {
        m_pBackPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize, pElement->FileName, nTimes);
    }
}

void SimpleAudioEngine::stopBackgroundMusic()
{
    if (m_pBackPlayer)
    {
        m_pBackPlayer->Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    if (m_pBackPlayer)
    {
        m_pBackPlayer->Pause();
    }
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    if (m_pBackPlayer)
    {
        m_pBackPlayer->Resume();
    }
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    if (m_pBackPlayer)
    {
        m_pBackPlayer->Rewind();
    }
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return m_bWillPlayBackgroundMusic;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    bool bRet = false;

    if (m_pBackPlayer)
    {
        bRet = m_pBackPlayer->IsPlaying();
    }

    return bRet;
}

// properties
int SimpleAudioEngine::GetBackgroundMusicVolume()
{
    return m_nBackgroundMusicVolume;
}

void SimpleAudioEngine::SetBackgroundMusicVolume(int volume)
{
    if (m_pBackPlayer)
    {
        m_pBackPlayer->SetVolumeValue(volume);
    }

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
    return m_pDataManager->loadSoundData(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(int nSoundId)
{
    m_pDataManager->unloadEffect(nSoundId);
}

void SimpleAudioEngine::playPreloadedEffect(int nSoundId)
{
    do 
    {
        tEffectElement* pElement = m_pDataManager->getSoundData(nSoundId);
        BREAK_IF(! pElement);

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
            pPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize, pElement->FileName.c_str());
            pPlayer->SetCurrentSoundID(nSoundId);
        }
    } while (0);
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

void SimpleAudioEngine::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
{
    m_pDataManager->setSoundResInfo(ResInfo, nCount);
}

void SimpleAudioEngine::setResourceEntry(const void* pResEntry)
{
    m_pDataManager->setResEntry(pResEntry);
}
