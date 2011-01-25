#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

#include "MciPlayer.h"

using namespace std;

namespace CocosDenshion {

typedef map<unsigned int, MciPlayer> EffectList;
typedef pair<unsigned int, MciPlayer> Effect;

static char     s_szRootPath[MAX_PATH];
static DWORD    s_dwRootLen;
static char     s_szFullPath[MAX_PATH];

static const char * _FullPath(const char * szPath);
static unsigned int _Hash(const char *key);

#define BREAK_IF(cond)  if (cond) break;

static EffectList& sharedList()
{
    static EffectList s_List;
    return s_List;
}

static MciPlayer& sharedMusic()
{
    static MciPlayer s_Music;
    return s_Music;
}

SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
    sharedMusic().Close();
    sharedList().clear();
    return;
}

void SimpleAudioEngine::setResource(const char* pszZipFileName, const char* pszResPath)
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

    sharedMusic().Open(_FullPath(pszFilePath), _Hash(pszFilePath));
    sharedMusic().Play((bLoop) ? -1 : 1);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (bReleaseData)
    {
        sharedMusic().Close();
    }
    else
    {
        sharedMusic().Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    sharedMusic().Pause();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    sharedMusic().Resume();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    sharedMusic().Rewind();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return sharedMusic().IsPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath)
{
    unsigned int nRet = _Hash(pszFilePath);

    preloadEffect(pszFilePath);

    EffectList::iterator p = sharedList().find(nRet);
    if (p != sharedList().end())
    {
        p->second.Rewind();
    }

    return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
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

        BREAK_IF(sharedList().end() != sharedList().find(nRet));

        sharedList().insert(Effect(nRet, MciPlayer()));
        MciPlayer& player = sharedList()[nRet];
        player.Open(_FullPath(pszFilePath), nRet);

        BREAK_IF(nRet == player.GetSoundID());

        sharedList().erase(nRet);
        nRet = 0;
    } while (0);
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    unsigned int nID = _Hash(pszFilePath);
    sharedList().erase(nID);
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return 1.0;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
}

float SimpleAudioEngine::getEffectsVolume()
{
    return 1.0;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
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
