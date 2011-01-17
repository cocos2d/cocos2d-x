#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

#include "MciPlayer.h"

using namespace std;

namespace CocosDenshion {

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

void SimpleAudioEngine::end()
{
	return;
}

void SimpleAudioEngine::setResourcePath(const char *pszResourcePath)
{
}

void SimpleAudioEngine::setResourceZipFile(const char* pszZipPath)
{
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
    if (bReleaseData)
    {
        s_Music.Close();
    }
    else
    {
        s_Music.Stop();
    }
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

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath)
{
    unsigned int nRet = _Hash(pszFilePath);

	preloadEffect(pszFilePath);

    EffectList::iterator p = s_List.find(nRet);
    if (p != s_List.end())
    {
        p->second.Rewind();
    }

	return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	EffectList::iterator p = s_List.find(nSoundId);
	if (p != s_List.end())
	{
		p->second.Stop();
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

		s_List.insert(Effect(nRet, MciPlayer()));
		MciPlayer& player = s_List[nRet];
		player.Open(_FullPath(pszFilePath), nRet);

		BREAK_IF(nRet == player.GetSoundID());

		s_List.erase(nRet);
		nRet = 0;
	} while (0);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    unsigned int nID = _Hash(pszFilePath);
	s_List.erase(nID);
}

void SimpleAudioEngine::unloadEffectAll()
{
	s_List.clear();
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

int SimpleAudioEngine::getBackgroundMusicVolume()
{
	return 100;
}

void SimpleAudioEngine::setBackgroundMusicVolume(int volume)
{
}

int SimpleAudioEngine::getEffectsVolume()
{
	return 100;
}

void SimpleAudioEngine::setEffectsVolume(int volume)
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

} // end of namespace CocosDenshion
