// XXX: Have just stubbed stuff out to get this building for now.

/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include <map>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include <AL/al.h>
#include <AL/alc.h>
//#include <AL/alut.h>
#include <sys/stat.h>
//#include <vorbis/vorbisfile.h>

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

namespace CocosDenshion
{
	struct soundData {
		ALuint buffer;
		ALuint source;
		bool   isLooped;
	};

	typedef map<string, soundData *> EffectsMap;
	EffectsMap s_effects;

	typedef enum {
		PLAYING,
		STOPPED,
		PAUSED,
	} playStatus;

	static float s_volume 				   = 1.0f;
	static float s_effectVolume			   = 1.0f;

	struct backgroundMusicData {
		ALuint buffer;
		ALuint source;
	};
	typedef map<string, backgroundMusicData *> BackgroundMusicsMap;
	BackgroundMusicsMap s_backgroundMusics;

	static ALuint s_backgroundSource = AL_NONE;

	static SimpleAudioEngine  *s_engine = 0;

	static int checkALError(const char *funcName)
	{
		int err = alGetError();

		if (err != AL_NO_ERROR)
		{
			switch (err)
			{
				case AL_INVALID_NAME:
					fprintf(stderr, "AL_INVALID_NAME in %s\n", funcName);
					break;

				case AL_INVALID_ENUM:
					fprintf(stderr, "AL_INVALID_ENUM in %s\n", funcName);
					break;

				case AL_INVALID_VALUE:
					fprintf(stderr, "AL_INVALID_VALUE in %s\n", funcName);
					break;

				case AL_INVALID_OPERATION:
					fprintf(stderr, "AL_INVALID_OPERATION in %s\n", funcName);
					break;

				case AL_OUT_OF_MEMORY:
					fprintf(stderr, "AL_OUT_OF_MEMORY in %s\n", funcName);
					break;
			}
		}

		return err;
	}

    static void stopBackground(bool bReleaseData)
    {
		s_backgroundSource = AL_NONE;
    }

    static void setBackgroundVolume(float volume)
    {
    }

	SimpleAudioEngine::SimpleAudioEngine()
	{
	}

	SimpleAudioEngine::~SimpleAudioEngine()
	{
	}

	SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
	{
		if (!s_engine)
			s_engine = new SimpleAudioEngine();
        
		return s_engine;
	}

	void SimpleAudioEngine::end()
	{
		checkALError("end");

		// clear all the sounds
	    EffectsMap::const_iterator end = s_effects.end();
	    for (EffectsMap::iterator it = s_effects.begin(); it != end; it++)
	    {
	        alSourceStop(it->second->source);
	        checkALError("end");
			alDeleteBuffers(1, &it->second->buffer);
			checkALError("end");
			alDeleteSources(1, &it->second->source);
			checkALError("end");
			delete it->second;
	    }
	    s_effects.clear();

		// and the background too
		stopBackground(true);

		for (BackgroundMusicsMap::iterator it = s_backgroundMusics.begin(); it != s_backgroundMusics.end(); ++it)
		{
			alSourceStop(it->second->source);
			checkALError("end");
			alDeleteBuffers(1, &it->second->buffer);
			checkALError("end");
			alDeleteSources(1, &it->second->source);
			checkALError("end");
			delete it->second;
		}
		s_backgroundMusics.clear();
	}

	//
	// OGG support
	//
	static bool isOGGFile(const char *pszFilePath)
	{
        return true;
	}

	static ALuint createBufferFromOGG(const char *pszFilePath)
	{
	}


	//
	// background audio
	//
    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return false;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
        return false;
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{
		return s_volume;
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
	}

	//
	// Effect audio (using OpenAL)
	//
	float SimpleAudioEngine::getEffectsVolume()
	{
		return s_effectVolume;
	}

	void SimpleAudioEngine::setEffectsVolume(float volume)
	{
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
		// Changing file path to full path
    	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);

		EffectsMap::iterator iter = s_effects.find(fullPath);

		if (iter == s_effects.end())
		{
			preloadEffect(fullPath.c_str());

			// let's try again
			iter = s_effects.find(fullPath);
			if (iter == s_effects.end())
			{
				fprintf(stderr, "could not find play sound %s\n", fullPath.c_str());
				return -1;
			}
		}

		checkALError("playEffect");
		iter->second->isLooped = bLoop;
		alSourcei(iter->second->source, AL_LOOPING, iter->second->isLooped ? AL_TRUE : AL_FALSE);
		alSourcePlay(iter->second->source);
		checkALError("playEffect");

		return iter->second->source;
	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
		alSourceStop(nSoundId);
		checkALError("stopEffect");
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
		// Changing file path to full path
    	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
    	
		EffectsMap::iterator iter = s_effects.find(fullPath);

		if (iter != s_effects.end())
	    {
			checkALError("unloadEffect");

	        alSourceStop(iter->second->source);
	        checkALError("unloadEffect");

			alDeleteSources(1, &iter->second->source);
			checkALError("unloadEffect");

			alDeleteBuffers(1, &iter->second->buffer);
			checkALError("unloadEffect");
			delete iter->second;

			s_effects.erase(iter);
	    }
	}

	void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
	{
		ALint state;
		alGetSourcei(nSoundId, AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING)
			alSourcePause(nSoundId);
		checkALError("pauseEffect");
	}

	void SimpleAudioEngine::pauseAllEffects()
	{
		EffectsMap::iterator iter = s_effects.begin();
		ALint state;
		while (iter != s_effects.end())
	    {
			alGetSourcei(iter->second->source, AL_SOURCE_STATE, &state);
			if (state == AL_PLAYING)
				alSourcePause(iter->second->source);
			checkALError("pauseAllEffects");
			++iter;
	    }
	}

	void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
	{
		ALint state;
		alGetSourcei(nSoundId, AL_SOURCE_STATE, &state);
		if (state == AL_PAUSED)
			alSourcePlay(nSoundId);
		checkALError("resumeEffect");
	}

	void SimpleAudioEngine::resumeAllEffects()
	{
		EffectsMap::iterator iter = s_effects.begin();
		ALint state;
		while (iter != s_effects.end())
	    {
			alGetSourcei(iter->second->source, AL_SOURCE_STATE, &state);
			if (state == AL_PAUSED)
				alSourcePlay(iter->second->source);
			checkALError("resumeAllEffects");
			++iter;
	    }
	}

    void SimpleAudioEngine::stopAllEffects()
    {
		EffectsMap::iterator iter = s_effects.begin();

		if (iter != s_effects.end())
	    {
			checkALError("stopAllEffects");
	        alSourceStop(iter->second->source);
			checkALError("stopAllEffects");
	    }
    }

}
