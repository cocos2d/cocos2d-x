#ifndef _SIMPLE_AUDIO_ENGINE_OPENSL_H_
#define _SIMPLE_AUDIO_ENGINE_OPENSL_H_

#include "OpenSLEngine.h"

class SimpleAudioEngineOpenSL
{
public:
	SimpleAudioEngineOpenSL();
	~SimpleAudioEngineOpenSL();

	bool initEngine();

	static SimpleAudioEngineOpenSL* sharedEngine();

	static void end();

	float getEffectsVolume();

	void setEffectsVolume(float volume);

	unsigned int playEffect(const char* pszFilePath, bool bLoop = false);

	void pauseEffect(unsigned int nSoundId);

	void pauseAllEffects();

	void resumeEffect(unsigned int nSoundId);

	void resumeAllEffects();

	void stopEffect(unsigned int nSoundId);

	void stopAllEffects();

	void preloadEffect(const char* pszFilePath);

	void unloadEffect(const char* pszFilePath);
};


#endif
