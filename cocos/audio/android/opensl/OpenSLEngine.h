/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
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
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
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

	void setEffectParameters(unsigned int effectID, bool isLooping, float pitch, float pan, float gain);

	void setEffectsVolume(float volume);

	float getEffectsVolume();

private:
	SLmillibel _musicVolume;
    float _effectVolume;
};

#endif
