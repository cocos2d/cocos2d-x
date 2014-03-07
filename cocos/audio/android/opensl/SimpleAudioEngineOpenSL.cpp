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
				LOGD("%s", errorInfo);
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

unsigned int SimpleAudioEngineOpenSL::playEffect(const char* pszFilePath, bool bLoop,
                                                 float pitch, float pan, float gain)
{
    unsigned int soundID = s_pOpenSL->preloadEffect(pszFilePath);

    if (soundID != FILE_NOT_FOUND)
    {
        if (s_pOpenSL->getEffectState(soundID) == PLAYSTATE_PLAYING)
        {
           // recreate an effect player.
           if (s_pOpenSL->recreatePlayer(pszFilePath))
           {
               s_pOpenSL->setEffectParameters(soundID, bLoop, pitch, pan, gain);
           }
        }
        else
        {
            s_pOpenSL->setEffectState(soundID, PLAYSTATE_STOPPED);
            s_pOpenSL->setEffectState(soundID, PLAYSTATE_PLAYING);
            s_pOpenSL->setEffectParameters(soundID, bLoop, pitch, pan, gain);
        }
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

