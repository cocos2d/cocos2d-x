/****************************************************************************
Copyright (c) 2013 Zynga Inc.
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

// XXX: This is all just a bit of a hack. SDL uses channels as its underlying
// abstraction, whilst CocosDenshion deals in individual effects. Consequently
// we can't set start/stop, because to SDL, effects (chunks) are just opaque
// blocks of data that get scheduled on channels. To workaround this, we assign
// each sound to a channel, but since there are only 32 channels, we use the
// modulus of the sound's address (which on Emscripten is just an incrementing
// integer) to decide which channel.
//
// A more rigorous implementation would have logic to store the state of
// channels and restore it as necessary. This should probably just be
// considered a toy for now, but it will probably prove sufficient for many
// use-cases. Recall also that Emscripten undoes this abstraction on the other
// side because it is using HTML5 audio objects as its underlying primitive!

#include <map>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

USING_NS_CC;

using namespace std;

namespace CocosDenshion
{
	struct soundData {
        Mix_Chunk *chunk;
		bool   isLooped;
	};

	typedef map<string, soundData *> EffectsMap;
	EffectsMap s_effects;
    float s_effectsVolume = 1.0;

	typedef enum {
		PLAYING,
		STOPPED,
		PAUSED,
	} playStatus;

	struct backgroundMusicData {
		Mix_Music *music;
	};
	typedef map<string, backgroundMusicData *> BackgroundMusicsMap;
	BackgroundMusicsMap s_backgroundMusics;
    float s_backgroundVolume = 1.0;

	static SimpleAudioEngine  *s_engine = 0;

    // Unfortunately this is just hard-coded in Emscripten's SDL
    // implementation.
    static const int NR_CHANNELS = 32;
    static void stopBackground(bool bReleaseData)
    {
        SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
        engine->stopBackgroundMusic();
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
		// clear all the sounds
	    EffectsMap::const_iterator end = s_effects.end();
	    for (EffectsMap::iterator it = s_effects.begin(); it != end; it++)
	    {
            Mix_FreeChunk(it->second->chunk);
			delete it->second;
	    }
	    s_effects.clear();

		// and the background too
		stopBackground(true);

		for (BackgroundMusicsMap::iterator it = s_backgroundMusics.begin(); it != s_backgroundMusics.end(); ++it)
		{
            Mix_FreeMusic(it->second->music);
			delete it->second;
		}
		s_backgroundMusics.clear();
	}

	//
	// background audio
	//
    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
        std::string key = std::string(pszFilePath);
        struct backgroundMusicData *musicData;
        if(!s_backgroundMusics.count(key))
        {
            musicData = new struct backgroundMusicData();
            musicData->music = Mix_LoadMUS(pszFilePath);
            s_backgroundMusics[key] = musicData;
        }
        else
        {
            musicData = s_backgroundMusics[key];
        }

        Mix_PlayMusic(musicData->music, bLoop ? -1 : 0);
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
        Mix_HaltMusic();
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
        Mix_PauseMusic();
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
        Mix_ResumeMusic();
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
        CCLOGWARN("Cannot rewind background in Emscripten");
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
        return Mix_PlayingMusic();
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{
        return s_backgroundVolume;
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
        // Ensure volume is between 0.0 and 1.0.
        volume = volume > 1.0 ? 1.0 : volume;
        volume = volume < 0.0 ? 0.0 : volume;

        Mix_VolumeMusic(volume * MIX_MAX_VOLUME);
        s_backgroundVolume = volume;
	}

	float SimpleAudioEngine::getEffectsVolume()
	{
		return s_effectsVolume;
	}

	void SimpleAudioEngine::setEffectsVolume(float volume)
	{
        volume = volume > 1.0 ? 1.0 : volume;
        volume = volume < 0.0 ? 0.0 : volume;

        // Need to set volume on every channel. SDL will then read this volume
        // level and apply it back to the individual sample.
        for(int i = 0; i < NR_CHANNELS; i++)
        {
            Mix_Volume(i, volume * MIX_MAX_VOLUME);
        }

        s_effectsVolume = volume;
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
        std::string key = std::string(pszFilePath);
        struct soundData *sound;
        if(!s_effects.count(key))
        {
            sound = new struct soundData();
            sound->chunk = Mix_LoadWAV(pszFilePath);
            sound->isLooped = bLoop;
            s_effects[key] = sound;
        }
        else
        {
            sound = s_effects[key];
        }
        // This is safe here since Emscripten is just passing back an
        // incrementing integer each time you use the Mix_LoadWAV method.
        unsigned int result = (unsigned int) sound->chunk;

        // XXX: This is a bit of a hack, but... Choose a channel based on the
        // modulo of the # of channels. This allows us to set the volume
        // without passing around both chunk address and channel.
        Mix_PlayChannel(result % NR_CHANNELS, sound->chunk, bLoop ? -1 : 0);

        return result;
	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
        Mix_HaltChannel(nSoundId % NR_CHANNELS);
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
        std::string key = std::string(pszFilePath);
        if(!s_effects.count(key))
        {
            return;
        }

        struct soundData *sound = s_effects[key];

        Mix_FreeChunk(sound->chunk);
        delete sound;
        s_effects.erase(key);
	}

	void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
	{
        Mix_Pause(nSoundId % NR_CHANNELS);
	}

	void SimpleAudioEngine::pauseAllEffects()
	{
        for(int i = 0; i < NR_CHANNELS; i++)
        {
            Mix_Pause(i);
        }
	}

	void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
	{
        Mix_Resume(nSoundId % NR_CHANNELS);
	}

	void SimpleAudioEngine::resumeAllEffects()
	{
        for(int i = 0; i < NR_CHANNELS; i++)
        {
            Mix_Resume(i);
        }
	}

    void SimpleAudioEngine::stopAllEffects()
    {
        for(int i = 0; i < NR_CHANNELS; i++)
        {
            Mix_HaltChannel(i);
        }
    }

}
