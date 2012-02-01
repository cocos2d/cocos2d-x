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
#include <AL/alut.h>
#include <sys/stat.h>
#include <vorbis/vorbisfile.h>

#include "SimpleAudioEngine.h"

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
	static bool  s_isBackgroundInitialized = false;
	static std::string s_currentBackgroundStr;

	ALuint s_backgroundBuffer;
	ALuint s_backgroundSource;

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
    	alSourceStop(s_backgroundSource);

		if (bReleaseData)
		{
			s_currentBackgroundStr = "";
			s_isBackgroundInitialized = false;

			alDeleteBuffers(1, &s_backgroundBuffer);
			checkALError("stopBackground");
			alDeleteSources(1, &s_backgroundSource);
			checkALError("stopBackground");
		}
    }

    static void setBackgroundVolume(float volume)
    {
    	alSourcef(s_backgroundSource, AL_GAIN, volume);
    }

	SimpleAudioEngine::SimpleAudioEngine()
	{
		alutInit(0, 0);
	}

	SimpleAudioEngine::~SimpleAudioEngine()
	{
		alutExit();
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
	}

	void SimpleAudioEngine::setResource(const char* pszZipFileName)
	{
	}

	//
	// OGG support
	//
	static bool isOGGFile(const char *pszFilePath)
	{
		FILE			*file;
		OggVorbis_File   ogg_file;
		int				 result;

		file = fopen(pszFilePath, "rb");
		result = ov_test(file, &ogg_file, 0, 0);
		ov_clear(&ogg_file);

		return (result == 0);
	}

	static ALuint createBufferFromOGG(const char *pszFilePath)
	{
		ALuint 			buffer;
		OggVorbis_File  ogg_file;
		vorbis_info*    info;
		ALenum 			format;
		int 			result;
		int 			section;
		int				err;
		unsigned int 	size = 0;

		if (ov_fopen(pszFilePath, &ogg_file) < 0)
		{
			ov_clear(&ogg_file);
			fprintf(stderr, "Could not open OGG file %s\n", pszFilePath);
			return -1;
		}

		info = ov_info(&ogg_file, -1);

		if (info->channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;

		// size = #samples * #channels * 2 (for 16 bit)
		unsigned int data_size = ov_pcm_total(&ogg_file, -1) * info->channels * 2;
		char* data = new char[data_size];

		while (size < data_size)
		{
			result = ov_read(&ogg_file, data + size, data_size - size, 0, 2, 1, &section);
			if (result > 0)
			{
				size += result;
			}
			else if (result < 0)
			{
				delete [] data;
				fprintf(stderr, "OGG file problem %s\n", pszFilePath);
				return -1;
			}
			else
			{
				break;
			}
		}

		if (size == 0)
		{
			delete [] data;
			fprintf(stderr, "Unable to read OGG data\n");
			return -1;
		}

		// clear al errors
		checkALError("createBufferFromOGG");

	    // Load audio data into a buffer.
	    alGenBuffers(1, &buffer);

	    if (checkALError("createBufferFromOGG") != AL_NO_ERROR)
	    {
	        fprintf(stderr, "Couldn't generate a buffer for OGG file\n");
	        delete [] data;
	        return buffer;
	    }

		alBufferData(buffer, format, data, data_size, info->rate);
		checkALError("createBufferFromOGG");

		delete [] data;
		ov_clear(&ogg_file);

		return buffer;
	}


	//
	// background audio
	//
    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
		if (!s_isBackgroundInitialized || s_currentBackgroundStr != pszFilePath)
		{
			string path = pszFilePath;

			if (isOGGFile(path.data()))
			{
				s_backgroundBuffer = createBufferFromOGG(path.data());
			}
			else
			{
				s_backgroundBuffer = alutCreateBufferFromFile(path.data());
			}

			checkALError("preloadBackgroundMusic");

			if (s_backgroundBuffer == AL_NONE)
			{
				fprintf(stderr, "Error loading file: '%s'\n", path.data());
				alDeleteBuffers(1, &s_backgroundBuffer);
				return;
			}

			alGenSources(1, &s_backgroundSource);
			checkALError("preloadBackgroundMusic");

			alSourcei(s_backgroundSource, AL_BUFFER, s_backgroundBuffer);
			checkALError("preloadBackgroundMusic");

			s_currentBackgroundStr = pszFilePath;
		}

		s_currentBackgroundStr 	  = pszFilePath;
		s_isBackgroundInitialized = true;
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
		if (!s_isBackgroundInitialized)
			preloadBackgroundMusic(pszFilePath);

		alSourcei(s_backgroundSource, AL_LOOPING, bLoop ? AL_TRUE : AL_FALSE);
		alSourcePlay(s_backgroundSource);
		checkALError("playBackgroundMusic");
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
		stopBackground(bReleaseData);
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
		alSourcePause(s_backgroundSource);
		checkALError("pauseBackgroundMusic");
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
		alSourcePlay(s_backgroundSource);
		checkALError("resumeBackgroundMusic");
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
		alSourceRewind(s_backgroundSource);
		checkALError("rewindBackgroundMusic");
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
	    ALint play_status;
	    alGetSourcei(s_backgroundSource, AL_SOURCE_STATE, &play_status);

		return (play_status == AL_PLAYING);
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{
		return s_volume;
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
		if (s_volume != volume && volume >= -0.0001 && volume <= 1.0001)
		{
    		s_volume = volume;

			setBackgroundVolume(volume);
		}
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
		if (volume != s_effectVolume)
		{
			EffectsMap::const_iterator end = s_effects.end();
			for (EffectsMap::const_iterator it = s_effects.begin(); it != end; it++)
			{
				alSourcef(it->second->source, AL_GAIN, volume);
			}

			s_effectVolume = volume;
		}
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
		EffectsMap::iterator iter = s_effects.find(pszFilePath);

		if (iter == s_effects.end())
		{
			preloadEffect(pszFilePath);

			// let's try again
			iter = s_effects.find(pszFilePath);
			if (iter == s_effects.end())
			{
				fprintf(stderr, "could not find play sound %s\n", pszFilePath);
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
		EffectsMap::iterator iter = s_effects.find(pszFilePath);

		// check if we have this already
		if (iter == s_effects.end())
		{
			ALuint 		buffer;
			ALuint 		source;
			soundData  *data = new soundData;
			string 	    path = pszFilePath;

			checkALError("preloadEffect");

			if (isOGGFile(path.data()))
			{
				buffer = createBufferFromOGG(path.data());
			}
			else
			{
				buffer = alutCreateBufferFromFile(path.data());
				checkALError("preloadEffect");
			}

			if (buffer == AL_NONE)
			{
				fprintf(stderr, "Error loading file: '%s'\n", path.data());
				alDeleteBuffers(1, &buffer);
				return;
			}

			alGenSources(1, &source);

			if (checkALError("preloadEffect") != AL_NO_ERROR)
			{
				alDeleteBuffers(1, &buffer);
				return;
			}

			alSourcei(source, AL_BUFFER, buffer);
			checkALError("preloadEffect");

			data->isLooped = false;
			data->buffer = buffer;
			data->source = source;

			s_effects.insert(EffectsMap::value_type(pszFilePath, data));
		}
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
		EffectsMap::iterator iter = s_effects.find(pszFilePath);

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
		alSourcePause(nSoundId);
		checkALError("pauseEffect");
	}

	void SimpleAudioEngine::pauseAllEffects()
	{
		EffectsMap::iterator iter = s_effects.begin();

		if (iter != s_effects.end())
	    {
			alSourcePause(iter->second->source);
			checkALError("pauseAllEffects");
	    }
	}

	void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
	{
		alSourcePlay(nSoundId);
		checkALError("resumeEffect");
	}

	void SimpleAudioEngine::resumeAllEffects()
	{
		EffectsMap::iterator iter = s_effects.begin();

		if (iter != s_effects.end())
	    {
			checkALError("resumeAllEffects");
			alSourcePlay(iter->second->source);
			checkALError("resumeAllEffects");
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
