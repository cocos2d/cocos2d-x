#include "OpenSLEngine.h"

#define  PLAYSTATE_STOPPED 1
#define  PLAYSTATE_PAUSED  2
#define  PLAYSTATE_PLAYING 3
#define  FILE_NOT_FOUND	   -1

OpenSL * s_pOpenSL = 0;
static OpenSLEngine * s_pEngine = 0;

OpenSLEngine::OpenSLEngine()
{
}

OpenSLEngine::~OpenSLEngine()
{
	if (s_pOpenSL)
	{
		s_pOpenSL->closeEngine();

		delete s_pOpenSL;
		s_pOpenSL = 0;
	}
}

bool OpenSLEngine::initEngine()
{
	bool bRet = false;
	do 
	{
		s_pOpenSL = new OpenSL();
		s_pOpenSL->createEngine();

		bRet = true;
	} while (0);
	return bRet;
}

OpenSLEngine* OpenSLEngine::sharedEngine()
{
	if (! s_pEngine)
	{
		s_pEngine = new OpenSLEngine();
		s_pEngine->initEngine();
	}
	return s_pEngine;
}

void OpenSLEngine::end()
{
	if (s_pOpenSL)
	{
		s_pOpenSL->closeEngine();
	}
}

float OpenSLEngine::getEffectsVolume()
{
	// TODO
	return 1.0f;
}

void OpenSLEngine::setEffectsVolume(float volume)
{
	int attenuation = (1 - volume) * 100;
	int millibel = attenuation * -15;
	s_pOpenSL->setEffectsVolume(millibel);
}

unsigned int OpenSLEngine::playEffect(const char* pszFilePath, bool bLoop)
{
	unsigned int soundID = s_pOpenSL->preloadEffect(pszFilePath);
	if (soundID != FILE_NOT_FOUND)
	{
		s_pOpenSL->setEffectState(soundID, PLAYSTATE_STOPPED);
		s_pOpenSL->setEffectLooping(soundID, bLoop);
		s_pOpenSL->setEffectState(soundID, PLAYSTATE_PLAYING);
	}

	return soundID;
}

void OpenSLEngine::pauseEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_PAUSED);
}

void OpenSLEngine::pauseAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_PAUSED);
}

void OpenSLEngine::resumeEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_PLAYING);
}

void OpenSLEngine::resumeAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_PLAYING);
}

void OpenSLEngine::stopEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_STOPPED);
}

void OpenSLEngine::stopAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_STOPPED);
}

void OpenSLEngine::preloadEffect(const char* pszFilePath)
{
	s_pOpenSL->preloadEffect(pszFilePath);
}

void OpenSLEngine::unloadEffect(const char* pszFilePath)
{
	s_pOpenSL->unloadEffect(pszFilePath);
}

