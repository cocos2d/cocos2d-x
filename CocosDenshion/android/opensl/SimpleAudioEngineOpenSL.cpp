#include "SimpleAudioEngineOpenSL.h"

#define  PLAYSTATE_STOPPED 1
#define  PLAYSTATE_PAUSED  2
#define  PLAYSTATE_PLAYING 3
#define  FILE_NOT_FOUND	   -1

OpenSLEngine * s_pOpenSL = 0;
static SimpleAudioEngineOpenSL * s_pEngine = 0;

SimpleAudioEngineOpenSL::SimpleAudioEngineOpenSL()
{
}

SimpleAudioEngineOpenSL::~SimpleAudioEngineOpenSL()
{
	if (s_pOpenSL)
	{
		s_pOpenSL->closeEngine();

		delete s_pOpenSL;
		s_pOpenSL = 0;
	}
}

bool SimpleAudioEngineOpenSL::initEngine()
{
	bool bRet = false;
	do 
	{
		s_pOpenSL = new OpenSLEngine();
		s_pOpenSL->createEngine();

		bRet = true;
	} while (0);
	return bRet;
}

SimpleAudioEngineOpenSL* SimpleAudioEngineOpenSL::sharedEngine()
{
	if (! s_pEngine)
	{
		s_pEngine = new SimpleAudioEngineOpenSL();
		s_pEngine->initEngine();
	}
	return s_pEngine;
}

void SimpleAudioEngineOpenSL::end()
{
	if (s_pOpenSL)
	{
		s_pOpenSL->closeEngine();
	}
}

float SimpleAudioEngineOpenSL::getEffectsVolume()
{
	// TODO
	return 1.0f;
}

void SimpleAudioEngineOpenSL::setEffectsVolume(float volume)
{
	int attenuation = (1 - volume) * 100;
	int millibel = attenuation * -15;
	s_pOpenSL->setEffectsVolume(millibel);
}

unsigned int SimpleAudioEngineOpenSL::playEffect(const char* pszFilePath, bool bLoop)
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
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_PLAYING);
}

void SimpleAudioEngineOpenSL::resumeAllEffects()
{
	s_pOpenSL->setAllEffectState(PLAYSTATE_PLAYING);
}

void SimpleAudioEngineOpenSL::stopEffect(unsigned int nSoundId)
{
	s_pOpenSL->setEffectState(nSoundId, PLAYSTATE_STOPPED);
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

