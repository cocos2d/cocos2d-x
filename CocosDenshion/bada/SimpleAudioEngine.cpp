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
#include "CCAudioOut.h"
#include <FBase.h>
#include <FMedia.h>
#include <FSystem.h>
#include <string>
#include <map>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;
using namespace Osp::Media;
using namespace Osp::System;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;

#define BREAK_IF(cond)  if (cond) break;

namespace CocosDenshion {

#define MAX_BUFFER_SIZE	2520 // 840 byte

typedef map<unsigned int, CCAudioOut*> EffectList;
typedef pair<unsigned int ,CCAudioOut*> Effect;


static SimpleAudioEngine *s_pSharedAudioEngine = NULL;
static Player       *s_pBackPlayer       = NULL;
static EffectList	s_List;
static float   s_fBackgroundMusicVolume = 1.0f;
static float   s_fEffectsVolume = 1.0f;
static bool    s_bWillPlayBackgroundMusic = false;
static bool    s_bBackgroundMusicPaused = false;
static string s_strResourcePath = "/Res/";

static unsigned int _Hash(const char *key)
{
	unsigned int len = strlen(key);
	const char *end=key+len;
	unsigned int hash;

	for (hash = 0; key < end; key++)
	{
		hash *= 16777619;
		hash ^= (unsigned int) (unsigned char) toupper(*key);
	}
	return (hash);
}

static string fullPathFromRelativePath(const char *pszRelativePath)
{
	string strRet="";
	int len = strlen(pszRelativePath);
	if (pszRelativePath == NULL || len <= 0)
	{
		return strRet;
	}

    if (len > 1 && pszRelativePath[0] == '/')
    {
    	strRet = pszRelativePath;
    }
    else
    {
    	strRet = s_strResourcePath;
    	strRet += pszRelativePath;
    }
	return strRet;
}

class MyPlayerEventListener :
	public IPlayerEventListener
{

public:

	/**
	*	Notifies that audio/video content was opened asynchronously.
	*
	* 	@param[in]	r	The cause of the error
	*	@exception	 E_SUCCESS							The method was successful.
	*	@exception	 E_SYSTEM							A system error occurred.
	*	@exception	 E_CONNECTION_FAILED				Network connection failed.
	* 	@exception	 E_UNSUPPORTED_FORMAT				The specified format is not supported.
	* 	@exception	 E_UNSUPPORTED_CODEC				The specified codec is not supported.
	*	@exception	 E_OUT_OF_MEMORY					Insufficient memory.
	*	@see		Player::OpenFile(), Player::OpenUrl(), Player::OpenBuffer()
	*/
	virtual void OnPlayerOpened( result r )
	{
		AppLog("OnPlayerOpened result = %d", r);
	}

	/**
	*	Notifies that the Player has reached the end of the clip.
	*
	*/
	virtual void OnPlayerEndOfClip(void)
	{
		AppLog("OnPlayerEndOfClip");
	}

	/**
	*	Notifies that the position of the audio/video content was moved asynchronously.
	*
	*	@exception	 E_SUCCESS		The method was successful.
	*	@exception	 E_SYSTEM		A system error occurred.
	*	@see		Player::SeekTo()
	*/

	virtual void OnPlayerSeekCompleted( result r )
	{
		AppLog("OnPlayerSeekCompleted result = %d", r);
	}


	/**
	*	Notifies that streaming data is being buffered.
	*
	*	@param[in]	percent		The percentage of buffering completed
	*	@see		Player::OpenUrl()
	*/
	virtual void OnPlayerBuffering(int percent)
	{
		AppLog("OnPlayerBuffering percent = %d%", percent);
	}

	/**
	*	Notifies that an error has occurred while the Player is working.
	*
	*	@param[in]	r		A player error reason of type ::PlayerErrorReason
	*	@remark		While playing streaming media, the player might throw an error like ::PLAYER_ERROR_CONNECTION_LOST @n
	*				::PLAYER_ERROR_STREAMING_TIMEOUT, ::PLAYER_ERROR_TRANSPORT or ::PLAYER_ERROR_SERVER. @n
	*				If the content includes invalid data, ::PLAYER_ERROR_INVALID_DATA may occur.
	*	@see	PlayerErrorReason
	*/
	virtual void OnPlayerErrorOccurred( PlayerErrorReason r )
	{
		AppLog("OnPlayerErrorOccurred PlayerErrorReason = %d", r);
	}


	/**
	 *	Notifies that the Player is being interrupted by a task of higher priority than Player.
	 *
	 */
	virtual void OnPlayerInterrupted(void)
	{
		AppLog("OnPlayerInterrupted");
		//Insert your code here
		if (s_pBackPlayer->GetState() == PLAYER_STATE_PLAYING)
			s_pBackPlayer->Pause();
	}

	/**
	 *	Notifies that the interrupting Player has been released.
	 *
	 */
	virtual void OnPlayerReleased(void)
	{
		AppLog("OnPlayerReleased");
		//Insert your code here
		if (s_pBackPlayer->GetState() != PLAYER_STATE_PLAYING)
			s_pBackPlayer->Play();
	}

};

static 	MyPlayerEventListener s_playerListener;

static void closeMediaPlayer(Player*& pPlayer)
{
	if (pPlayer != NULL)
	{
		PlayerState nowState = pPlayer->GetState();
		if( nowState == PLAYER_STATE_PLAYING || nowState == PLAYER_STATE_PAUSED )
		{
			pPlayer->Stop();
			pPlayer->Close();
		}
		else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
		{
			pPlayer->Close();
		}
	}
}

static bool openMediaPlayer(Player*& pPlayer, const char* pszFilePath)
{
	bool bRet = false;
	result r = E_FAILURE;

	do
	{
		closeMediaPlayer(pPlayer);

		if (pPlayer == NULL)
		{
			pPlayer = new Player();
			r = pPlayer->Construct(s_playerListener, null);
			if (IsFailed(r))
			{
				AppLog("player construct fails, pszFilePath = %s", pszFilePath);
				delete pPlayer;
				pPlayer = NULL;
				break;
			}
		}

		string strFilePath = fullPathFromRelativePath(pszFilePath);
		// OpenFile must use synchronous param, for after that it will playing.
		r = pPlayer->OpenFile(strFilePath.c_str(), false);
		if (IsFailed(r))
		{
			AppLog("Open (%s) fails\n", strFilePath.c_str());
			delete pPlayer;
			pPlayer = NULL;
			break;
		}
		else
		{
			bRet = true;
		}
	}
	while (0);

	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(s_fBackgroundMusicVolume);

	return bRet;
}

SimpleAudioEngine::SimpleAudioEngine()
{

}

SimpleAudioEngine::~SimpleAudioEngine()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		it->second->Stop();
		delete it->second;
	}

	s_List.clear();

	closeMediaPlayer(s_pBackPlayer);
	delete s_pBackPlayer;
	s_pBackPlayer = NULL;
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    if (s_pSharedAudioEngine == NULL)
    {
        s_pSharedAudioEngine = new SimpleAudioEngine;
    }
    
    return s_pSharedAudioEngine;
}

void SimpleAudioEngine::end()
{
	if (s_pSharedAudioEngine)
	{
		delete s_pSharedAudioEngine;
		s_pSharedAudioEngine = NULL;
	}
}

void SimpleAudioEngine::setResource(const char* pszZipFileName)
{

}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
	openMediaPlayer(s_pBackPlayer, pszFilePath);
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	result r = E_FAILURE;
	bool bRet = false;
	bRet = openMediaPlayer(s_pBackPlayer, pszFilePath);

    if (bRet)
    {
    	s_pBackPlayer->SetLooping(bLoop);
    	r = s_pBackPlayer->Play();
    }
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
	s_bBackgroundMusicPaused = false;
    if (s_pBackPlayer != NULL && PLAYER_STATE_PLAYING == s_pBackPlayer->GetState())
    {
        s_pBackPlayer->Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    if (s_pBackPlayer != NULL && PLAYER_STATE_PLAYING == s_pBackPlayer->GetState())
    {
    	s_bBackgroundMusicPaused = true;
        s_pBackPlayer->Pause();
    }
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    if (s_pBackPlayer != NULL && s_bBackgroundMusicPaused && PLAYER_STATE_PLAYING != s_pBackPlayer->GetState())
    {
    	s_bBackgroundMusicPaused = false;
        s_pBackPlayer->Play();
    }
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
	stopBackgroundMusic();
    if (s_pBackPlayer != NULL)
    {
        if (PLAYER_STATE_PLAYING != s_pBackPlayer->GetState())
        {
         	result r = s_pBackPlayer->Play();
         	if (IsFailed(r))
         	{
         		AppLog("ERROR: %s", GetErrorMessage(r));
         	}
        }
    }
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return s_bWillPlayBackgroundMusic;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    bool bRet = false;

    if (s_pBackPlayer != NULL && s_pBackPlayer->GetState() == PLAYER_STATE_PLAYING)
    {
        bRet = true;
    }

    return bRet;
}

// properties
float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return s_fBackgroundMusicVolume;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if (volume < 0.0f)
    {
        volume = 0.0f;
    }

    if (s_pBackPlayer != NULL)
    {
    	s_pBackPlayer->SetVolume(ceil(volume*99));
    }
    s_fBackgroundMusicVolume = volume;
}

float SimpleAudioEngine::getEffectsVolume()
{
    return s_fEffectsVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    if (volume > 1.0f)
    {
        volume = 1.0f;
    }
    else if (volume < 0.0f)
    {
        volume = 0.0f;
    }

	EffectList::iterator it;
	for (it = s_List.begin(); it != s_List.end(); ++it)
	{
		if (it->second != NULL)
		{
			it->second->SetVolume(ceil(volume*99));
		}
	}
	s_fEffectsVolume = volume;
}

// for sound effects
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop/* = false*/)
{
	result r = E_FAILURE;
	string strFilePath = fullPathFromRelativePath(pszFilePath);
	unsigned int nRet = _Hash(strFilePath.c_str());

	preloadEffect(pszFilePath);

	EffectList::iterator p = s_List.find(nRet);
	if (p != s_List.end())
	{
		if (NULL == p->second)
		{
			AppLog("CCAudioOut instance must not be NULL, id = %d", p->first);
			return 0;
		}
		p->second->SetVolume(ceil(s_fEffectsVolume * 99));

	    if (AUDIOOUT_STATE_PLAYING == p->second->GetState())
		{
            return nRet; // Stop waste a lot of time, so just return.
	    	//r = p->second->Stop();
		}

	    if (s_fEffectsVolume > 0.0f)
	    {
	    	r = p->second->Play(bLoop);
	    }

    	if (IsFailed(r))
    	{
    		AppLog("play effect fails, error code = %d", r);
    	}
	}
	return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	EffectList::iterator it = s_List.find(nSoundId);
	if (it != s_List.end())
	{
		if (it->second != NULL)
		{
			it->second->Stop();
		}
	}
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
	EffectList::iterator it = s_List.find(nSoundId);
	if (it != s_List.end())
	{
		if (it->second != NULL)
		{
			it->second->Pause();
		}
	}
}

void SimpleAudioEngine::pauseAllEffects()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		if (it->second != NULL)
		{
			it->second->Pause();
		}
	}
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
	EffectList::iterator it = s_List.find(nSoundId);
	if (it != s_List.end())
	{
		if (it->second != NULL)
		{
			it->second->Resume();
		}
	}
}

void SimpleAudioEngine::resumeAllEffects()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		if (it->second != NULL)
		{
			it->second->Resume();
		}
	}
}

void SimpleAudioEngine::stopAllEffects()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		if (it->second != NULL)
		{
			it->second->Stop();
		}
	}
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	int nRet = 0;
	CCAudioOut* pEffectPlayer = NULL;
	do
	{
		BREAK_IF(! pszFilePath);

		string strFilePath = fullPathFromRelativePath(pszFilePath);

		nRet = _Hash(strFilePath.c_str());

		BREAK_IF(s_List.end() != s_List.find(nRet));

		//AppLog("not find effect, create it...");
		if (s_List.size() >= 64)
		{
			// get the first effect, and remove it form list
			AppLog("effect preload more than 64, delete the first effect");
			pEffectPlayer = s_List.begin()->second;
			pEffectPlayer->Finalize();
			s_List.erase(s_List.begin());
		}

		if (NULL == pEffectPlayer)
		{
			pEffectPlayer = new CCAudioOut();
		}

		pEffectPlayer->Initialize(strFilePath.c_str());

		s_List.insert(Effect(nRet, pEffectPlayer));

	} while (0);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	string strFilePath = fullPathFromRelativePath(pszFilePath);
	unsigned int nID = _Hash(strFilePath.c_str());
	EffectList::iterator p = s_List.find(nID);
	if (p != s_List.end())
	{
		if (p->second != NULL)
		{
			delete p->second;
			p->second = NULL;
			AppLog("delete CCAudioOut, id = %d", nID);
		}
		else
		{
			AppLog("CCAudioOut instance is NULL, id = %d", nID);
		}
		s_List.erase(p);
	}
}

} // end of namespace CocosDenshion
