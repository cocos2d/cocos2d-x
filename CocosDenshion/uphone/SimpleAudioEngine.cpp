#include "SimpleAudioEngine.h"
#include "SoundPlayer.h"
#include "SoundDataManager.h"
#include "TSoundPlayer.h"

#define BREAK_IF(cond)  if (cond) break;

static SimpleAudioEngine *s_pSharedAudioEngine = NULL;
static SoundDataManager  *s_pDataManager      = NULL;
static SoundPlayer       *s_pBackPlayer       = NULL;
static TSoundPlayer      *s_pEffectPlayer     = NULL;


static int     s_nBackgroundMusicVolume = 100;
static int     s_nEffectsVolume = 100;
static bool    s_bWillPlayBackgroundMusic = false;

SimpleAudioEngine::SimpleAudioEngine()
{
    if (s_pEffectPlayer)
    {
        delete s_pEffectPlayer;
    }
    s_pEffectPlayer = new TSoundPlayer();

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
    if (s_pEffectPlayer)
    {
        delete s_pEffectPlayer;
        s_pEffectPlayer = NULL;
    }

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
    if (s_pSharedAudioEngine == NULL)
    {
        s_pSharedAudioEngine = new SimpleAudioEngine;
    }
    
    return s_pSharedAudioEngine;
}

void SimpleAudioEngine::release()
{
	if (s_pSharedAudioEngine)
	{
		delete s_pSharedAudioEngine;
		s_pSharedAudioEngine = NULL;
	}
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
    do 
    {
        tEffectElement* pElement = s_pDataManager->getSoundData(nSoundId);
        BREAK_IF(! pElement);

        Int32 nID = pElement->nPlayerSoundID;

        if (nID >= 0)
        {
            s_pEffectPlayer->Stop(nID);
            pElement->nPlayerSoundID = -1;
        }
    } while (0);    
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

        TSoundPlayParameter soundParam;
        soundParam.pSoundData = pElement->pDataBuffer;
        soundParam.dataLen    = pElement->nDataSize;
        soundParam.dataType   = SOUND_TYPE_WAVE;
        soundParam.volume     = (int) (0xFFFF * ((float) s_nEffectsVolume / 100));

        Int32 nID = s_pEffectPlayer->Play(soundParam);

        if (nID >= 0)
        {
            pElement->nPlayerSoundID = nID;
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

void SimpleAudioEngine::unloadEffectAll()
{
    s_pDataManager->removeAllEffects();
}
