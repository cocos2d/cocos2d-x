#ifndef _OPENSL_ENGINE_H_
#define _OPENSL_ENGINE_H_

#include <assert.h>
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <dlfcn.h>
#include "SLES/OpenSLES.h"
#include "SLES/OpenSLES_Android.h"
#include <sys/types.h>
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#include <android/log.h>
#include <jni/JniHelper.h>
#include <dlfcn.h>


class OpenSLEngine
{
public:
	OpenSLEngine();
	~OpenSLEngine();

	void createEngine(void * pHandle);

	void closeEngine();


	bool preloadBackgroundMusic(const char * filename);

	void setBackgroundMusicState(int state);

	int getBackgroundMusicState();

	void rewindBackgroundMusic();

	void setBackgroundMusicLooping(bool isLooping);

	void setBackgroundVolume(int volume);

	int getBackgroundVolume();



	bool recreatePlayer(const char* filename);

	unsigned int preloadEffect(const char * filename);

	void unloadEffect(const char * filename);

	int getEffectState(unsigned int effectID);

	void setEffectState(unsigned int effectID, int state, bool isClear = false);

	void setAllEffectState(int state);

	void resumeEffect(unsigned int effectID);

	void resumeAllEffects();

	void setEffectLooping(unsigned int effectID, bool isLooping);

	void setEffectsVolume(float volume);

	float getEffectsVolume();

private:
	SLmillibel m_musicVolume;
	SLmillibel m_effectVolume;
};

#endif