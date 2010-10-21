#include "SimpleAudioEngine.h"
#include "SoundPlayer.h"
#include "SoundDataManager.h"
#include <vector>

typedef std::vector<SoundPlayer*> PlayerArray;
typedef PlayerArray::iterator     PlayerArrayIterator;

#define BREAK_IF(cond)  if (cond) break;

static SimpleAudioEngine *s_pSharedAudioEngie = NULL;
static PlayerArray       *s_pEffectPlayers    = NULL;
static SoundDataManager  *s_pDataManager      = NULL;
static SoundPlayer       *s_pBackPlayer       = NULL;


static int     s_nBackgroundMusicVolume = 100;
static int     s_nEffectsVolume = 100;
static bool    s_bWillPlayBackgroundMusic = false;

void removeAllEffectPlayers()
{
    PlayerArrayIterator iter;

    for (iter = s_pEffectPlayers->begin(); iter != s_pEffectPlayers->end(); ++iter)
    {
        if (*iter)
        {
            delete *iter;
        }
    }

    s_pEffectPlayers->clear();
    delete s_pEffectPlayers;
}

SimpleAudioEngine::SimpleAudioEngine()
{
    if (s_pEffectPlayers)
    {
        removeAllEffectPlayers();
    }
    s_pEffectPlayers = new PlayerArray();
    SetEffectsVolume(s_nEffectsVolume);

    if (s_pBackPlayer)
    {
        delete s_pBackPlayer;
    }
    s_pBackPlayer    = new SoundPlayer();
    SetBackgroundMusicVolume(s_nBackgroundMusicVolume);

    if (s_pDataManager)
    {
        delete s_pDataManager;
    }
    s_pDataManager   = new SoundDataManager();
}

SimpleAudioEngine::~SimpleAudioEngine()
{
    removeAllEffectPlayers();

    if (s_pBackPlayer)
    {
        delete s_pBackPlayer;
        s_pBackPlayer = NULL;
    }

    if (s_pDataManager)
    {
        delete s_pDataManager;
        s_pDataManager = NULL;
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

    int nSoundID = s_pDataManager->loadSoundData(pszFilePath);
    tEffectElement* pElement = s_pDataManager->getSoundData(nSoundID);

    if (pElement)
    {
        s_pBackPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize, pElement->FileName, nTimes);
    }
}

void SimpleAudioEngine::stopBackgroundMusic()
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->Pause();
    }
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->Resume();
    }
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->Rewind();
    }
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return s_bWillPlayBackgroundMusic;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    bool bRet = false;

    if (s_pBackPlayer)
    {
        bRet = s_pBackPlayer->IsPlaying();
    }

    return bRet;
}

// properties
int SimpleAudioEngine::GetBackgroundMusicVolume()
{
    return s_nBackgroundMusicVolume;
}

void SimpleAudioEngine::SetBackgroundMusicVolume(int volume)
{
    if (volume > 100)
    {
        volume = 100;
    }
    else if (volume < 0)
    {
        volume = 0;
    }

    if (s_pBackPlayer)
    {
        s_pBackPlayer->SetVolumeValue(volume);
    }

    s_nBackgroundMusicVolume = volume;
}

int SimpleAudioEngine::GetEffectsVolume()
{
    return s_nEffectsVolume;
}

void SimpleAudioEngine::SetEffectsVolume(int volume)
{
    if (volume > 100)
    {
        volume = 100;
    }
    else if (volume < 0)
    {
        volume = 0;
    }

    PlayerArrayIterator iter;

    for (iter = s_pEffectPlayers->begin(); iter != s_pEffectPlayers->end(); ++iter)
    {
        if (*iter)
        {
            (*iter)->SetVolumeValue(volume);
        }
    }

    s_nEffectsVolume = volume;
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
    for (iter = s_pEffectPlayers->begin(); iter != s_pEffectPlayers->end(); ++iter)
    {
        if ((*iter) && pPlayer->GetCurrentSoundID() == nSoundId)
        {
            pPlayer->Stop();
        }
    }
}

int SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    return s_pDataManager->loadSoundData(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(int nSoundId)
{
    s_pDataManager->unloadEffect(nSoundId);
}

void SimpleAudioEngine::playPreloadedEffect(int nSoundId)
{
    do 
    {
        tEffectElement* pElement = s_pDataManager->getSoundData(nSoundId);
        BREAK_IF(! pElement);

        SoundPlayer* pPlayer = NULL;
        bool bLoaded = false;

        // find the not playing player in s_pEffectPlayers
        PlayerArrayIterator iter;
        for (iter = s_pEffectPlayers->begin(); iter != s_pEffectPlayers->end(); ++iter)
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
            s_pEffectPlayers->push_back(pPlayer);

            // set the player volume
            pPlayer->SetVolumeValue(s_nEffectsVolume);
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

void SimpleAudioEngine::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
{
    s_pDataManager->setSoundResInfo(ResInfo, nCount);
}

void SimpleAudioEngine::setResourceEntry(const void* pResEntry)
{
    s_pDataManager->setResEntry(pResEntry);
}
