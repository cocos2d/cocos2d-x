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
#include <mm/renderer.h>
#include <sys/stat.h>

//#include "CCFileUtils.h"

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

	static int	 s_audioOid;

	static float s_volume 				  = 1.0f;
	static float s_effectVolume			  = 1.0f;
	static bool s_isBackgroundInitialized = false;
	static bool s_hasMMRError			  = false;
	static playStatus s_playStatus	  	  = STOPPED;

	static string 		   s_currentBackgroundStr;
	static mmr_connection_t   *s_mmrConnection 	  = 0;
	static mmr_context_t 	  *s_mmrContext 	  = 0;
	static strm_dict_t 		  *s_repeatDictionary = 0;
	static strm_dict_t 		  *s_volumeDictionary = 0;

	static SimpleAudioEngine  *s_engine = 0;

	static void printALError(int err)
	{
		switch (err)
		{
			case AL_NO_ERROR:
				fprintf(stderr, "AL_NO_ERROR");
				break;

			case AL_INVALID_NAME:
				fprintf(stderr, "AL_INVALID_NAME");
				break;

			case AL_INVALID_ENUM:
				fprintf(stderr, "AL_INVALID_ENUM");
				break;

			case AL_INVALID_VALUE:
				fprintf(stderr, "AL_INVALID_VALUE");
				break;

			case AL_INVALID_OPERATION:
				fprintf(stderr, "AL_INVALID_OPERATION");
				break;

			case AL_OUT_OF_MEMORY:
				fprintf(stderr, "AL_OUT_OF_MEMORY");
				break;
		};
	}

    static void mmrerror(mmr_context_t *ctxt, const char *msg)
    {
    	const mmr_error_info_t  *err = mmr_error_info( ctxt );
    	unsigned 				 errcode = (err) ? err->error_code : -1;
    	const char 				*name;

    	fprintf(stderr, "%s: error %d \n", msg, errcode);
    	s_hasMMRError = true;
    }

    static void stopBackground(bool bReleaseData)
    {
    	s_playStatus = STOPPED;

		if (s_mmrContext)
			mmr_stop(s_mmrContext);

		if (bReleaseData)
		{
			if (s_mmrContext)
			{
				mmr_input_detach(s_mmrContext);
				mmr_context_destroy(s_mmrContext);
			}

			if (s_mmrConnection)
				mmr_disconnect(s_mmrConnection);

			if (s_repeatDictionary)
				strm_dict_destroy(s_repeatDictionary);

			if (s_volumeDictionary)
				strm_dict_destroy(s_volumeDictionary);

			s_mmrContext = 0;
			s_mmrConnection = 0;
			s_repeatDictionary = 0;
			s_volumeDictionary = 0;
			s_hasMMRError = false;
			s_currentBackgroundStr = "";
			s_isBackgroundInitialized = false;
		}
    }

    static void setBackgroundVolume(float volume)
    {
		char volume_str[128];

		// set it up the background volume
		strm_dict_t *dictionary = strm_dict_new();

		sprintf(volume_str, "%d", (int)(volume * 100) );
		s_volumeDictionary = strm_dict_set(dictionary, "volume", volume_str);

		if (mmr_output_parameters(s_mmrContext, s_audioOid, s_volumeDictionary) != 0)
		{
			mmrerror(s_mmrContext, "output parameters");
			return;
		}
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
		// clear all the sounds
	    EffectsMap::const_iterator end = s_effects.end();
	    for (EffectsMap::iterator it = s_effects.begin(); it != end; it++)
	    {
	        alSourceStop(it->second->source);

			alDeleteBuffers(1, &it->second->buffer);
			alDeleteSources(1, &it->second->source);
			delete it->second;
	    }
	    s_effects.clear();

		if (s_isBackgroundInitialized)
		{
			s_isBackgroundInitialized = false;
		}

		// and the background too
		stopBackground(true);
	}

	void SimpleAudioEngine::setResource(const char* pszZipFileName)
	{
	}

	//
	// background audio (using mmrenderer)
	//
    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
    	if (!s_isBackgroundInitialized)
    	{
    		const char 		*mmrname = NULL;
    		const char 		*ctxtname = "mmrplayer";
    		char 			 cwd[PATH_MAX];
    		mode_t 			 mode = S_IRUSR | S_IXUSR;

//cjh    		getcwd(cwd, PATH_MAX);
    		string path = "file://";
//    		path += cwd;
//    		path += "/";
//    		path += cocos2d::CCFileUtils::getResourcePath();
//    		path += pszFilePath;

    		s_mmrConnection = mmr_connect(mmrname);
    		if (!s_mmrConnection)
    		{
    			perror("mmr_connect");
    			s_hasMMRError = true;
    			return;
    		}

    		s_mmrContext = mmr_context_create(s_mmrConnection, ctxtname, 0, mode);
    		if (!s_mmrContext)
    		{
    			perror(ctxtname);
    			s_hasMMRError = true;
    			return;
    		}

    		if ((s_audioOid = mmr_output_attach(s_mmrContext, "audio:default", "audio")) < 0)
    		{
    			mmrerror(s_mmrContext, "audio:default");
    			return;
    		}

    		setBackgroundVolume(s_volume);

    		if (mmr_input_attach(s_mmrContext, path.data(), "autolist") < 0)
    		{
    			fprintf(stderr, "unable to load %s\n", path.data());
    			mmrerror(s_mmrContext, path.data());
    			return;
    		}

    		s_currentBackgroundStr 	  = pszFilePath;
			s_isBackgroundInitialized = true;
    	}
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
		if (0 == strcmp(s_currentBackgroundStr.c_str(), pszFilePath))
		{
			stopBackgroundMusic(true);
		}
		else
		{
			if (s_playStatus == PAUSED)
				resumeBackgroundMusic();
			else
				rewindBackgroundMusic();
		}

		if (!s_isBackgroundInitialized)
			preloadBackgroundMusic(pszFilePath);

		if (bLoop)
		{
			// set it up to loop
			strm_dict_t *dictionary = strm_dict_new();
			s_repeatDictionary = strm_dict_set(dictionary, "repeat", "all");

    		if (mmr_input_parameters(s_mmrContext, s_repeatDictionary) != 0)
    		{
    			mmrerror(s_mmrContext, "input parameters (loop)");
    			return;
    		}
		}

		if (s_hasMMRError || !s_mmrContext)
			return;

		if (mmr_play(s_mmrContext) < 0)
		{
			mmrerror(s_mmrContext, "mmr_play");
			s_hasMMRError = true;
		}

		if (!s_hasMMRError)
			s_playStatus = PLAYING;
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
    	// if we were paused then we need to resume first so that we can play
		if (s_playStatus == PAUSED)
			resumeBackgroundMusic();

		stopBackground(bReleaseData);
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
		if (s_mmrContext && mmr_speed_set(s_mmrContext, 0) < 0)
		{
			mmrerror(s_mmrContext, "pause");
		}
		s_playStatus = PAUSED;
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
		if (s_mmrContext && mmr_speed_set(s_mmrContext, 1000) < 0)
		{
			mmrerror(s_mmrContext, "resume");
		}
		s_playStatus = PLAYING;
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
		if (s_mmrContext && mmr_seek(s_mmrContext, "1:0") < 0)
		{
			mmrerror(s_mmrContext, "rewind");
		}
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
		return (s_playStatus == PLAYING) && s_isBackgroundInitialized;
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

		iter->second->isLooped = bLoop;
		alSourcei(iter->second->source, AL_LOOPING, iter->second->isLooped ? AL_TRUE : AL_FALSE);
		alSourcePlay(iter->second->source);

		return iter->second->source;
	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
		alSourceStop(nSoundId);
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

			string path = "";//cjh cocos2d::CCFileUtils::getResourcePath();
			path += pszFilePath;

			buffer = alutCreateBufferFromFile(path.data());

			if (buffer == AL_NONE)
			{
				fprintf(stderr, "Error loading file: '%s'\n", path.data());
				alDeleteBuffers(1, &buffer);
				return;
			}

			alGenSources(1, &source);
			alSourcei(source, AL_BUFFER, buffer);

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
	        alSourceStop(iter->second->source);
			alDeleteSources(1, &iter->second->source);
			alDeleteBuffers(1, &iter->second->buffer);
			delete iter->second;

			int err = alGetError();
			if (err != AL_NO_ERROR)
				printALError(err);

			s_effects.erase(iter);
	    }
	}
}
