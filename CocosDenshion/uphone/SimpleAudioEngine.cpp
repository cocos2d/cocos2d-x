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
static int          s_nBackgroundMusicVolume = 100;
static int          s_nEffectsVolume = 100;
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
    setBackgroundMusicVolume(s_nBackgroundMusicVolume);

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

void SimpleAudioEngine::setResource(const char* pszResPath, const char* pszZipFileName)
{
    FileUtils::setResource(pszResPath, pszZipFileName);
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
int SimpleAudioEngine::getBackgroundMusicVolume()
{
    return s_nBackgroundMusicVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(int volume)
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

int SimpleAudioEngine::getEffectsVolume()
{
    return s_nEffectsVolume;
}

void SimpleAudioEngine::setEffectsVolume(int volume)
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
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath)
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
        soundParam.volume     = (int) (0xFFFF * ((float) s_nEffectsVolume / 100));

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

void SimpleAudioEngine::unloadEffectAll()
{
    s_pDataManager->removeAllEffects();
}

} // end of namespace CocosDenshion
