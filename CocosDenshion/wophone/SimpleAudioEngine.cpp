#include "SimpleAudioEngine.h"
#include "SoundPlayer.h"
#include "SoundDataManager.h"
#include "TSoundPlayer.h"
#include "FileUtils.h"

#define BREAK_IF(cond)  if (cond) break;

namespace CocosDenshion {

static SimpleAudioEngine *s_pSharedAudioEngine = NULL;
static SoundDataManager  *s_pDataManager      = NULL;
static SoundPlayer       *s_pBackPlayer       = NULL;
static TSoundPlayer      *s_pEffectPlayer     = NULL;

static std::string  s_strBackMusicName = "";
static float        s_fBackgroundMusicVolume = 1.0f;
static float        s_fEffectsVolume = 1.0f;
static bool         s_bWillPlayBackgroundMusic = false;

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
    setBackgroundMusicVolume(s_fBackgroundMusicVolume);

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

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    if (s_pSharedAudioEngine == NULL)
    {
        s_pSharedAudioEngine = new SimpleAudioEngine;
    }
    
    return s_pSharedAudioEngine;
}

void SimpleAudioEngine::end()
{
	if (s_pSharedAudioEngine)
	{
		delete s_pSharedAudioEngine;
		s_pSharedAudioEngine = NULL;
	}
}

void SimpleAudioEngine::setResource(const char* pszZipFileName)
{
    FileUtils::setResource(pszZipFileName);
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    int nTimes = 1;
    if (bLoop)
    {
        nTimes = -1;
    }

    s_strBackMusicName = pszFilePath;
    s_pDataManager->loadSoundData(pszFilePath);
    tEffectElement* pElement = s_pDataManager->getSoundData(pszFilePath);

    if (pElement)
    {
        s_pBackPlayer->PlaySoundFromMem(pElement->pDataBuffer, pElement->nDataSize, pElement->FileName, nTimes);
    }
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->Stop();
    }

    if (bReleaseData && s_strBackMusicName.length())
    {
        s_pDataManager->unloadEffect(s_strBackMusicName.c_str());
        s_strBackMusicName = "";
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
float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return s_fBackgroundMusicVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if (volume < 0.0f)
    {
        volume = 0.0f;
    }

    if (s_pBackPlayer)
    {
        s_pBackPlayer->SetVolumeValue((Int32) (volume * 100));
    }

    s_fBackgroundMusicVolume = volume;
}

float SimpleAudioEngine::getEffectsVolume()
{
    return s_fEffectsVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if (volume < 0.0f)
    {
        volume = 0.0f;
    }

    s_fEffectsVolume = volume;
}


// for sound effects
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    preloadEffect(pszFilePath);
    int nRet = -1;

    do 
    {
        tEffectElement* pElement = s_pDataManager->getSoundData(pszFilePath);
        BREAK_IF(! pElement);

        TSoundPlayParameter soundParam;
        soundParam.pSoundData = pElement->pDataBuffer;
        soundParam.dataLen    = pElement->nDataSize;
        soundParam.dataType   = SOUND_TYPE_WAVE;
        soundParam.volume     = (int) (0xFFFF * s_fEffectsVolume);
		int nTimes = 0;
		if (bLoop)
		{
			nTimes = -1;
		}
		soundParam.loopTime = nTimes;

        nRet = s_pEffectPlayer->Play(soundParam);
    } while (0);

    return (unsigned int) nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    do 
    {
        int nID = (int) nSoundId;

        BREAK_IF(nID < 0);
        s_pEffectPlayer->Stop(nID);
    } while (0);    
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    s_pDataManager->loadSoundData(pszFilePath);
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    s_pDataManager->loadSoundData(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    s_pDataManager->unloadEffect(pszFilePath);
}

// void SimpleAudioEngine::unloadEffectAll()
// {
//     s_pDataManager->removeAllEffects();
// }

} // end of namespace CocosDenshion
