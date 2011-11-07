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
		AppLog("OnPlayerOpened");
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
		AppLog("OnPlayerSeekCompleted");
	}


	/**
	*	Notifies that streaming data is being buffered.
	*
	*	@param[in]	percent		The percentage of buffering completed
	*	@see		Player::OpenUrl()
	*/
	virtual void OnPlayerBuffering(int percent)
	{
		AppLog("OnPlayerBuffering");
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
		AppLog("OnPlayerErrorOccurred");
	}


	/**
	 *	Notifies that the Player is being interrupted by a task of higher priority than Player.
	 *
	 */
	virtual void OnPlayerInterrupted(void)
	{
		//Insert your code here
		AppLog("OnPlayerInterrupted");
		if (s_pBackPlayer->GetState() == PLAYER_STATE_PLAYING)
			s_pBackPlayer->Pause();
	}

	/**
	 *	Notifies that the interrupting Player has been released.
	 *
	 */
	virtual void OnPlayerReleased(void)
	{
		//Insert your code here
		AppLog("OnPlayerReleased");
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
			AppLog("audio player closed");
		}
		else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
		{
			pPlayer->Close();
			AppLog("audio player closed");
		}
	}
}

static bool openMediaPlayer(Player*& pPlayer, const char* pszFilePath, bool bLoop)
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

		string strFilePath = s_strResourcePath+pszFilePath;
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
			pPlayer->SetLooping(bLoop);
			bRet = true;
		}
	}
	while (0);

	return bRet;
}

SimpleAudioEngine::SimpleAudioEngine()
{

}

SimpleAudioEngine::~SimpleAudioEngine()
{
	AppLog("destroy SimpleAudioEngine");

	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		it->second->Reset();
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

}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	result r = E_FAILURE;
	bool bRet = false;
	bRet = openMediaPlayer(s_pBackPlayer, pszFilePath, bLoop);

	setBackgroundMusicVolume(s_fBackgroundMusicVolume);

    if (bRet)
    {
    	r = s_pBackPlayer->Play();
    }
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (s_pBackPlayer && PLAYER_STATE_PLAYING == s_pBackPlayer->GetState())
    {
        s_pBackPlayer->Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    if (s_pBackPlayer && PLAYER_STATE_PLAYING == s_pBackPlayer->GetState())
    {
        s_pBackPlayer->Pause();
    }
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    if (s_pBackPlayer && PLAYER_STATE_PLAYING != s_pBackPlayer->GetState())
    {
        s_pBackPlayer->Play();
    }
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    if (s_pBackPlayer)
    {
        s_pBackPlayer->SeekTo(0);
        if (PLAYER_STATE_PLAYING != s_pBackPlayer->GetState())
        {
         	s_pBackPlayer->Play();
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

    if (s_pBackPlayer)
    {
        if (s_pBackPlayer->GetState() == PLAYER_STATE_PLAYING)
        {
        	bRet = true;
        }
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

    if (s_pBackPlayer)
    {
    	s_pBackPlayer->SetVolume((int) (volume * 99));
    	if (volume > 0.0f && s_pBackPlayer->GetVolume() == 0)
    	{
    		AppLog("volume is lowest");
    		s_pBackPlayer->SetVolume(1);
    	}
    }
    AppLog("volume = %f", volume);
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

    s_fEffectsVolume = volume;
}

// for sound effects
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop/* = false*/)
{
	long long curTick, oldTick;
	SystemTime::GetTicks(oldTick);
	result r = E_FAILURE;
	string strFilePath = s_strResourcePath+pszFilePath;
	unsigned int nRet = _Hash(strFilePath.c_str());
	AppLog("play effect (%s)", pszFilePath);
	preloadEffect(pszFilePath);

	EffectList::iterator p = s_List.find(nRet);
	if (p != s_List.end())
	{
		p->second->SetVolume((int) (s_fEffectsVolume * 99));
		int volume = p->second->GetVolume();
		AppLog("volume = %d, s_fEffectsVolume = %f", volume, s_fEffectsVolume);
    	if (s_fEffectsVolume > 0.0f && volume == 0)
    	{
    		AppLog("effect volume is lowest");
    		p->second->SetVolume(1);
    	}

	    if (AUDIOOUT_STATE_PLAYING == p->second->GetState())
		{
            return nRet; // reset waste a lot of time, so just return.
	    	AppLog("Reset effect...");
	    	r = p->second->Reset();
		}

	    AppLog("play...");

	    if (s_fEffectsVolume > 0.0f)
	    {
	    	r = p->second->Play();
	    }

    	if (IsFailed(r))
    	{
    		AppLog("play effect fails, error code = %d", r);
    	}
	}
	SystemTime::GetTicks(curTick);
	AppLog("play effect waste %ld ms...", (long)(curTick-oldTick));
	return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	CCAudioOut*& pPlayer = s_List[nSoundId];
	if (pPlayer != NULL)
	{
		pPlayer->Reset();
	}
}

void SimpleAudioEngine::stopAllEffects()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		it->second->Reset();
	}
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	int nRet = 0;
	CCAudioOut* pEffectPlayer = NULL;
	do
	{
		BREAK_IF(! pszFilePath);

		string strFilePath = s_strResourcePath+pszFilePath;

		nRet = _Hash(strFilePath.c_str());

		BREAK_IF(s_List.end() != s_List.find(nRet));

		AppLog("not find effect, create it...");
		// bada only support 10 player instance, we use one for background music, other for effect music.
		if (s_List.size() >= 64)
		{
			// get the first effect, and remove it form list
			AppLog("effect preload more than 9, delete the first effect");
			pEffectPlayer = s_List.begin()->second;
//			closeMediaPlayer(pEffectPlayer);
			pEffectPlayer->Finalize();
			s_List.erase(s_List.begin()->first);
		}
		if (pEffectPlayer == NULL)
			pEffectPlayer = new CCAudioOut;
		pEffectPlayer->Initialize(strFilePath.c_str());
	//	if (openMediaPlayer(pEffectPlayer, pszFilePath, false))
		{
			s_List.insert(Effect(nRet, pEffectPlayer));
		}

	} while (0);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	string strFilePath = s_strResourcePath+pszFilePath;
	unsigned int nSoundId = _Hash(strFilePath.c_str());
	CCAudioOut*& pPlayer = s_List[nSoundId];
	pPlayer->Reset();
	//closeMediaPlayer(pPlayer);
}

} // end of namespace CocosDenshion
