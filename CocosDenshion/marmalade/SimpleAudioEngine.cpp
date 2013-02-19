/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) 2011 Giovanni Zito

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
#include <string>
#include <map>
#include "cocos2d.h"
USING_NS_CC;

using namespace std ;

#define	GEOM_ONE_FP8		0x100		// volume is in .8 fixed point format

namespace CocosDenshion
{
	class SoundFx {
	public:
		SoundFx() : data(0), size(0) {}
		SoundFx(void* pData, int32 nSize) : data((int16*)pData), size(nSize) {}

		int16*	data ;
		int32	size ;
	};

	static int16*		g_AudioBuffer = 0;
	static int32		g_AudioFileSize = 0;

	typedef map<string,SoundFx> SoundFxMap ;
	static SoundFxMap* g_pSoundFxMap = 0 ;
	
	static SimpleAudioEngine *s_pEngine = 0 ;

	SimpleAudioEngine::SimpleAudioEngine()
	{
		g_pSoundFxMap = new SoundFxMap() ;
	}

	SimpleAudioEngine::~SimpleAudioEngine()
	{
	}

	SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
	{
		if (! s_pEngine) {
			s_pEngine = new SimpleAudioEngine();
		}
        
		return s_pEngine;
	}

	void SimpleAudioEngine::end()
	{
		s3eAudioStop();

		if( g_AudioBuffer) {
			free(g_AudioBuffer);
			g_AudioBuffer = 0 ;
		}

		if(s_pEngine) {
			s_pEngine->stopAllEffects() ;
			delete s_pEngine;
			s_pEngine=0;
		} 

		if( g_pSoundFxMap ) {
		    for( SoundFxMap::iterator it = g_pSoundFxMap->begin(); it!=g_pSoundFxMap->end(); it++ )
			    if( it->second.data != 0 ) free( it->second.data ) ;

			delete g_pSoundFxMap ;
			g_pSoundFxMap = 0 ;
		}
	}

/*	void SimpleAudioEngine::setResource(const char* pszZipFileName)
	{
		// todo
	}
*/

    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
		// Changing file path to full path
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
		s3eFile *fileHandle = s3eFileOpen(fullPath.c_str(), "rb");
		
		IwAssertMsg(GAME, fileHandle, ("Open file %s Failed. s3eFileError Code : %i", fullPath.c_str(), s3eFileGetError()));
		
		g_AudioFileSize = s3eFileGetSize(fileHandle);
		g_AudioBuffer = (int16*)malloc(g_AudioFileSize);
		memset(g_AudioBuffer, 0, g_AudioFileSize);
		s3eFileRead(g_AudioBuffer, g_AudioFileSize, 1, fileHandle);
		s3eFileClose(fileHandle);
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
		// Changing file path to full path
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
		s3eResult result;
		
		result = s3eAudioPlayFromBuffer(g_AudioBuffer, g_AudioFileSize, bLoop ? 0 : 1);
		
		if ( result == S3E_RESULT_ERROR)
		{
			result = s3eAudioPlay(fullPath.c_str(), bLoop ? 0 : 1);
		}
		
		if ( result == S3E_RESULT_ERROR) 
		{
			IwAssert(GAME, ("Play music %s Failed. Error Code : %s", fullPath.c_str(), s3eAudioGetErrorString()));
		}
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
		s3eAudioStop();
		
		if (bReleaseData)
		{
			free(g_AudioBuffer);
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
		//todo
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		// todo
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
		return s3eAudioIsPlaying() == S3E_TRUE ;
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{

		return s3eAudioGetInt(S3E_AUDIO_VOLUME) / (float)GEOM_ONE_FP8;
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
		s3eAudioSetInt(S3E_AUDIO_VOLUME, (int32)(volume * (float)GEOM_ONE_FP8));
	}

	float SimpleAudioEngine::getEffectsVolume()
	{
		return s3eSoundGetInt(S3E_SOUND_VOLUME) / (float)GEOM_ONE_FP8;
	}

	void SimpleAudioEngine::setEffectsVolume(float volume)
	{		
		s3eSoundSetInt(S3E_SOUND_VOLUME, (int32)(volume * (float)GEOM_ONE_FP8));
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
		// Changing file path to full path
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);

		SoundFxMap::iterator it = g_pSoundFxMap->find(fullPath) ;
		
		int16* buff = 0 ;
		if( it==g_pSoundFxMap->end() ) {
			preloadEffect(fullPath.c_str()) ;
		}
		buff = (*g_pSoundFxMap)[fullPath].data ;

		int channel = s3eSoundGetFreeChannel();
		
		s3eSoundChannelPlay(channel, buff, (*g_pSoundFxMap)[fullPath].size/2, (bLoop ? 0 : 1), 0);
		
		if (s3eSoundGetError()!= S3E_SOUND_ERR_NONE) {
			IwAssertMsg(GAME, false, ("Play sound %s Failed. Error Code : %s", fullPath.c_str(), s3eSoundGetErrorString()));	
		}

		return channel;

	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
		s3eSoundChannelStop(nSoundId);
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
		// Changing file path to full path
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
		SoundFxMap::iterator it = g_pSoundFxMap->find(fullPath) ;
		if( it==g_pSoundFxMap->end() ) {
			s3eFile *fileHandle = s3eFileOpen(fullPath.c_str(), "rb");
		
			IwAssertMsg(GAME, fileHandle, ("Open file %s Failed. s3eFileError Code : %i", fullPath.c_str(), s3eFileGetError()));
		
			int32 fileSize = s3eFileGetSize(fileHandle);
			int16* buff = (int16*)malloc(fileSize);

			(*g_pSoundFxMap)[fullPath] = SoundFx(buff,fileSize) ;
			memset(buff, 0, fileSize);
			s3eFileRead(buff, fileSize, 1, fileHandle);
			s3eFileClose(fileHandle);
		}
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
		// Changing file path to full path
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
		// effect must not be playing!

		SoundFxMap::iterator it = g_pSoundFxMap->find(fullPath) ;
		if( it != g_pSoundFxMap->end() ) {
			free(it->second.data) ;
			g_pSoundFxMap->erase(it) ;
		}
	}

	void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
	{
		s3eSoundChannelPause(nSoundId);
	}

	void SimpleAudioEngine::pauseAllEffects()
	{
		s3eSoundPauseAllChannels();
	}

	void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
	{
		s3eSoundChannelResume(nSoundId);
	}

	void SimpleAudioEngine::resumeAllEffects()
	{
		s3eSoundResumeAllChannels();
	}

	void SimpleAudioEngine::stopAllEffects()
	{
		s3eSoundStopAllChannels();
	}
}