#include "SimpleAudioEngine.h"
#include "MyAudioOutListener.h"

#include <FBase.h>
#include <FMedia.h>
#include <FSystem.h>

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

typedef map<unsigned int, MyAudioOutEventListener*> EffectList;
typedef pair<unsigned int ,MyAudioOutEventListener*> Effect;

static SimpleAudioEngine *s_pSharedAudioEngine = NULL;
static Player       *s_pBackPlayer       = NULL;
static EffectList	s_List;
static float   s_fBackgroundMusicVolume = 1.0f;
static float   s_fEffectsVolume = 1.0f;
static bool    s_bWillPlayBackgroundMusic = false;

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

static void unloadEffectAll()
{
	for (EffectList::iterator it = s_List.begin(); it != s_List.end(); ++it)
	{
		delete it->second;
	}

	s_List.clear();
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
	virtual void OnPlayerOpened( result r ){}

	/**
	*	Notifies that the Player has reached the end of the clip.
	*
	*/
	virtual void OnPlayerEndOfClip(void){}

	/**
	*	Notifies that the position of the audio/video content was moved asynchronously.
	*
	*	@exception	 E_SUCCESS		The method was successful.
	*	@exception	 E_SYSTEM		A system error occurred.
	*	@see		Player::SeekTo()
	*/

	virtual void OnPlayerSeekCompleted( result r ){};


	/**
	*	Notifies that streaming data is being buffered.
	*
	*	@param[in]	percent		The percentage of buffering completed
	*	@see		Player::OpenUrl()
	*/
	virtual void OnPlayerBuffering(int percent){}

	/**
	*	Notifies that an error has occurred while the Player is working.
	*
	*	@param[in]	r		A player error reason of type ::PlayerErrorReason
	*	@remark		While playing streaming media, the player might throw an error like ::PLAYER_ERROR_CONNECTION_LOST @n
	*				::PLAYER_ERROR_STREAMING_TIMEOUT, ::PLAYER_ERROR_TRANSPORT or ::PLAYER_ERROR_SERVER. @n
	*				If the content includes invalid data, ::PLAYER_ERROR_INVALID_DATA may occur.
	*	@see	PlayerErrorReason
	*/
	virtual void OnPlayerErrorOccurred( PlayerErrorReason r ){}


	/**
	 *	Notifies that the Player is being interrupted by a task of higher priority than Player.
	 *
	 */
	virtual void OnPlayerInterrupted(void){}

	/**
	 *	Notifies that the interrupting Player has been released.
	 *
	 */
	virtual void OnPlayerReleased(void){}

};

static 	MyPlayerEventListener s_playerListener;

SimpleAudioEngine::SimpleAudioEngine()
{

}

SimpleAudioEngine::~SimpleAudioEngine()
{
	AppLog("destroy SimpleAudioEngine");

	unloadEffectAll();

	if( s_pBackPlayer )
	{
		PlayerState nowState = s_pBackPlayer->GetState();
		if( nowState == PLAYER_STATE_PLAYING || nowState == PLAYER_STATE_PAUSED )
		{
			s_pBackPlayer->Stop();
			s_pBackPlayer->Close();
		}else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
		{
			s_pBackPlayer->Close();
		}
		delete s_pBackPlayer;
		s_pBackPlayer = null;
	}
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

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    if (s_pBackPlayer)
    {
		PlayerState nowState = s_pBackPlayer->GetState();
		if( nowState == PLAYER_STATE_PLAYING || nowState == PLAYER_STATE_PAUSED )
		{
			s_pBackPlayer->Stop();
			s_pBackPlayer->Close();
		}else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
		{
			s_pBackPlayer->Close();
		}
    }
    else
    {
    	s_pBackPlayer = new Player();
    	result r = s_pBackPlayer->Construct(s_playerListener, null);
    	AppLog("player construct return %d", r);
    }

	setBackgroundMusicVolume(s_fBackgroundMusicVolume);

	// OpenFile must use synchronous param, for after that it will playing.
	result r = s_pBackPlayer->OpenFile(pszFilePath, false);
    if (IsFailed(r))
    {
    	AppLog("Openfile fails\n");
    }
    else
    {
    	s_pBackPlayer->SetLooping(bLoop);
    }

    r = s_pBackPlayer->Play();
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
    if (s_pBackPlayer && PLAYER_STATE_PAUSED == s_pBackPlayer->GetState())
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

    s_fEffectsVolume = volume;
}

// for sound effects
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath)
{
	unsigned int nRet = _Hash(pszFilePath);

	preloadEffect(pszFilePath);

	EffectList::iterator p = s_List.find(nRet);
	if (p != s_List.end())
	{
		p->second->setVolume((int) (s_fEffectsVolume * 99));
		p->second->play();
	}

	return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	MyAudioOutEventListener*& pListener = s_List[nSoundId];
	if (pListener != null)
	{
		pListener->stop();
	}
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	int nRet = 0;
	do
	{
		BREAK_IF(! pszFilePath);

		nRet = _Hash(pszFilePath);

		BREAK_IF(s_List.end() != s_List.find(nRet));

		if (s_List.size() >= 64)
		{
			unloadEffectAll();
		}

		MyAudioOutEventListener* pListener = new MyAudioOutEventListener();
		pListener->Construct(pszFilePath);
		s_List.insert(Effect(nRet, pListener));

	} while (0);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	unsigned int nSoundId = _Hash(pszFilePath);
	MyAudioOutEventListener*& pListener = s_List[nSoundId];
	delete pListener;
	s_List.erase(nSoundId);
}

} // end of namespace CocosDenshion
