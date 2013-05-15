#include "SimpleAudioEngineOpenSL.h"
#include <dlfcn.h>
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"SIMPLEAUDIOENGINE_OPENSL", __VA_ARGS__)

#define  LIBOPENSLES "libOpenSLES.so"

#define  PLAYSTATE_UNKNOWN 0
#define  PLAYSTATE_STOPPED 1
#define  PLAYSTATE_PAUSED  2
#define  PLAYSTATE_PLAYING 3
#define  FILE_NOT_FOUND	   -1

static void * s_pHandle = 0;
static OpenSLEngine * s_pOpenSL = 0;
static SimpleAudioEngineOpenSL * s_pEngine = 0;

SimpleAudioEngineOpenSL::SimpleAudioEngineOpenSL()
{
}

SimpleAudioEngineOpenSL::~SimpleAudioEngineOpenSL()
{
	end();
}

bool SimpleAudioEngineOpenSL::initEngine()
{
	bool bRet = false;
	do 
	{
		if (s_pOpenSL == NULL)
		{
			// clear the error stack
			dlerror();
			s_pHandle = dlopen(LIBOPENSLES, RTLD_LAZY);
			const char* errorInfo = dlerror();
			if (errorInfo)
			{
				LOGD(errorInfo);
				bRet = false;
				break;
			}
			s_pOpenSL = new OpenSLEngine();
			s_pOpenSL->createEngine(s_pHandle);

			bRet = true;
		}
	} while (0);
	return bRet;
}

SimpleAudioEngineOpenSL* SimpleAudioEngineOpenSL::sharedEngine()
{
	if (s_pEngine == NULL)
	{
		s_pEngine = new SimpleAudioEngineOpenSL();
	}
	s_pEngine->initEngine();
	return s_pEngine;
}

void SimpleAudioEngineOpenSL::end()
{
	if (s_pOpenSL)
	{
		s_pOpenSL->closeEngine();
		delete s_pOpenSL;
		s_pOpenSL = NULL;

		dlclose(s_pHandle);
		s_pHandle = NULL;
	}
}

float SimpleAudioEngineOpenSL::getEffectsVolume()
{
	return s_pOpenSL->getEffectsVolume();
}

void SimpleAudioEngineOpenSL::setEffectsVolume(float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	if (volume > 1.0f) volume = 1.0f;
	s_pOpenSL->setEffectsVolume(volume);
}

unsigned int SimpleAudioEngineOpenSL::playEffect(const char* pszFilePath, bool bLoop)
{
    unsigned int soundID = s_pOpenSL->preloadEffect(pszFilePath);

    if (soundID != FILE_NOT_FOUND)
    {
        if (s_pOpenSL->getEffectState(soundID) == PLAYSTATE_PLAYING)
        {
            // recreate an effect player
            s_pOpenSL->recreatePlayer(pszFilePath);
        }
        else
        {
            s_pOpenSL->setEffectState(soundID, PLAYSTATE_STOPPED);
            s_pOpenSL->setEffectState(soundID, PLAYSTATE_PLAYING);
        }

        s_pOpenSL->setEffectLooping(soundID, bLoop);
    }

    return soundID;
}

void SimpleAudioEngineOpenSL::pauseEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_PAUSED);
}

void SimpleAudioEngineOpenSL::pauseAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_PAUSED);
}

void SimpleAudioEngineOpenSL::resumeEffect(unsigned int nSoundId)
{
	s_pOpenSL->resumeEffect(nSoundId);
}

void SimpleAudioEngineOpenSL::resumeAllEffects()
{
	s_pOpenSL->resumeAllEffects();
}

void SimpleAudioEngineOpenSL::stopEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_STOPPED, true);
}

void SimpleAudioEngineOpenSL::stopAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_STOPPED);
}

void SimpleAudioEngineOpenSL::preloadEffect(const char* pszFilePath)
{
	s_pOpenSL->preloadEffect(pszFilePath);
}

void SimpleAudioEngineOpenSL::unloadEffect(const char* pszFilePath)
{
	s_pOpenSL->unloadEffect(pszFilePath);
}

