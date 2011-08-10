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

#include "SimpleAudioEngine.h"
#include "s3e.h"
#include "IwUtil.h"
#include <set>

namespace CocosDenshion
{
	static int16*   g_SoundBuffer = 0;
	static int16*   g_AudioBuffer = 0;
	static int32    g_SoundFileSize = 0;
	static int32    g_AudioFileSize = 0;
	static int      g_SoundChannel = 0;
	static bool     g_SoundIsPlaying = false;
	static s3eBool  g_MP3Support = S3E_FALSE;
	
	
	static SimpleAudioEngine *s_pEngine;

	SimpleAudioEngine::SimpleAudioEngine()
	{

	}

	SimpleAudioEngine::~SimpleAudioEngine()
	{

		
	}

	SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
	{
		if (! s_pEngine)
		{
			s_pEngine = new SimpleAudioEngine();
		}
        
		return s_pEngine;
	}

	void SimpleAudioEngine::end()
	{
		s3eAudioStop();
		s3eFreeBase(g_AudioBuffer);
	}

	void SimpleAudioEngine::setResource(const char* pszZipFileName)
	{

	}

    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
		
			s3eFile *fileHandle = s3eFileOpen(pszFilePath, "rb");
		
			IwAssertMsg(GAME, fileHandle, ("Open file %s Failed. s3eFileError Code : %i", pszFilePath, s3eFileGetError()));
		
			g_AudioFileSize = s3eFileGetSize(fileHandle);
			g_AudioBuffer = (int16*)s3eMallocBase(g_AudioFileSize);
			memset(g_AudioBuffer, 0, g_AudioFileSize);
			s3eFileRead(g_AudioBuffer, g_AudioFileSize, 1, fileHandle);
			s3eFileClose(fileHandle);
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
		s3eResult result;
		
		result = s3eAudioPlayFromBuffer(g_AudioBuffer, g_AudioFileSize, bLoop);
		
		if ( result == S3E_RESULT_ERROR)
		{
			if (bLoop)
			{
				result = s3eAudioPlay(pszFilePath, 1000000);
			}
			else
			{
				result = s3eAudioPlay(pszFilePath, 0);
			}
		}
		
		if ( result == S3E_RESULT_ERROR) 
		{
			IwAssert(GAME, ("Play music %s Failed. Error Code : %s", pszFilePath, s3eAudioGetErrorString()));
		}
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
		s3eAudioStop();
		
		if (bReleaseData)
		{
			s3eFreeBase(g_AudioBuffer);
		}

	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
		s3eAudioPause();
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
		s3eAudioResume();
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{

	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
		return s3eAudioIsPlaying();
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{

		return s3eAudioGetInt(S3E_AUDIO_VOLUME);
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
		s3eAudioSetInt(S3E_AUDIO_VOLUME, volume);
	}

	float SimpleAudioEngine::getEffectsVolume()
	{
		return s3eSoundGetInt(S3E_SOUND_VOLUME);
	}

	void SimpleAudioEngine::setEffectsVolume(float volume)
	{
		
		s3eSoundSetInt(S3E_SOUND_VOLUME, volume);
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
					
		
		int channel = s3eSoundGetFreeChannel();
		
		s3eSoundChannelPlay(channel, g_SoundBuffer, g_SoundFileSize/2, 1, 0);
		
		if (s3eSoundGetError()!= S3E_SOUND_ERR_NONE)
		{
			IwAssertMsg(GAME, this, ("Play sound %s Failed. Error Code : %s", pszFilePath, s3eSoundGetErrorString()));	
		}

		return channel;

	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
		s3eSoundChannelStop(nSoundId);
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
		s3eFile *fileHandle = s3eFileOpen(pszFilePath, "rb");
		
		IwAssertMsg(GAME, fileHandle, ("Open file %s Failed. s3eFileError Code : %i", pszFilePath, s3eFileGetError()));
		
		g_SoundFileSize = s3eFileGetSize(fileHandle);
		g_SoundBuffer = (int16*)s3eMallocBase(g_SoundFileSize);
		memset(g_SoundBuffer, 0, g_SoundFileSize);
		s3eFileRead(g_SoundBuffer, g_SoundFileSize, 1, fileHandle);
		s3eFileClose(fileHandle);
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
		s3eFreeBase(g_SoundBuffer);
	}
}