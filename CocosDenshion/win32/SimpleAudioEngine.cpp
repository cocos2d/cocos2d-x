#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

#include "MciPlayer.h"

using namespace std;

typedef map<unsigned int, MciPlayer> EffectList;
typedef pair<unsigned int ,MciPlayer> Effect;

static SimpleAudioEngine s_SharedEngine;
static EffectList	s_List;
static MciPlayer	s_Music;
static char			s_szRootPath[MAX_PATH];
static DWORD		s_dwRootLen;
static char			s_szFullPath[MAX_PATH];


static const char * _FullPath(const char * szPath);
static unsigned int _Hash(const char *key);

#define BREAK_IF(cond)  if (cond) break;

SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    return &s_SharedEngine;
}

void SimpleAudioEngine::release()
{
	return;
}
//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	if (! pszFilePath)
	{
		return;
	}

	s_Music.Open(_FullPath(pszFilePath), _Hash(pszFilePath));
	s_Music.Play((bLoop) ? -1 : 1);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
	s_Music.Stop();
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
	s_Music.Pause();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
	s_Music.Resume();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
	s_Music.Rewind();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
	return s_Music.IsPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

int SimpleAudioEngine::playEffect(const char* pszFilePath)
{
	int nRet = preloadEffect(pszFilePath);
	if (nRet)
	{
		playPreloadedEffect(nRet);
	}
	return nRet;
}

void SimpleAudioEngine::stopEffect(int nSoundId)
{
	EffectList::iterator p = s_List.find(nSoundId);
	if (p != s_List.end())
	{
		p->second.Stop();
	}
}

int SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	int nRet = 0;
	do 
	{
		BREAK_IF(! pszFilePath);

		nRet = _Hash(pszFilePath);

		BREAK_IF(s_List.end() != s_List.find(nRet));

		s_List.insert(Effect(nRet, MciPlayer()));
		MciPlayer& player = s_List[nRet];
		player.Open(_FullPath(pszFilePath), nRet);

		BREAK_IF(nRet == player.GetSoundID());

		s_List.erase(nRet);
		nRet = 0;
	} while (0);
	return nRet;
}

void SimpleAudioEngine::unloadEffect(int nSoundId)
{
	s_List.erase(nSoundId);
}

void SimpleAudioEngine::unloadEffectAll()
{
	s_List.clear();
}

void SimpleAudioEngine::playPreloadedEffect(int nSoundId)
{
	EffectList::iterator p = s_List.find(nSoundId);
	if (p != s_List.end())
	{
		p->second.Rewind();
	}
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

int SimpleAudioEngine::GetBackgroundMusicVolume()
{
	return 100;
}

void SimpleAudioEngine::SetBackgroundMusicVolume(int volume)
{
}

int SimpleAudioEngine::GetEffectsVolume()
{
	return 100;
}

void SimpleAudioEngine::SetEffectsVolume(int volume)
{
}

//////////////////////////////////////////////////////////////////////////
// resource function
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
{
}

void SimpleAudioEngine::setResourceEntry(const void* pResEntry)
{
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

const char * _FullPath(const char * szPath)
{
	if (! s_szRootPath[0])
	{
		s_dwRootLen = GetModuleFileName(NULL, s_szRootPath, sizeof(s_szRootPath));
		while (--s_dwRootLen)
		{
			if ('\\' == s_szRootPath[s_dwRootLen])
			{
				s_szRootPath[s_dwRootLen + 1] = 0;
				strcpy_s(s_szFullPath, sizeof(s_szFullPath), s_szRootPath);
				++s_dwRootLen;
				break;
			}
		}
	}

	if (0 != szPath[0] && ':' != szPath[1])
	{
		strcpy_s(s_szFullPath + s_dwRootLen, sizeof(s_szFullPath) - s_dwRootLen, szPath);
		return s_szFullPath;
	}
	else
	{
		return szPath;
	}
}

unsigned int _Hash(const char *key)
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
