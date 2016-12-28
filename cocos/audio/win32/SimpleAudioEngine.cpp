/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
#include "audio/include/SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

#include "audio/win32/MciPlayer.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;

using namespace std;

namespace CocosDenshion {

typedef map<unsigned int, MciPlayer *> EffectList;
typedef pair<unsigned int, MciPlayer *> Effect;

static char     s_szRootPath[MAX_PATH];
static DWORD    s_dwRootLen;
static char     s_szFullPath[MAX_PATH];

static std::string _FullPath(const char * szPath);
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

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
    sharedMusic().Close();

    for (auto& iter : sharedList())
    {
        delete iter.second;
        iter.second = nullptr;
    }
    sharedList().clear();
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

    sharedMusic().Open(_FullPath(pszFilePath).c_str(), _Hash(pszFilePath));
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

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
                                           float pitch, float pan, float gain)
{
    unsigned int nRet = _Hash(pszFilePath);

    preloadEffect(pszFilePath);

    EffectList::iterator p = sharedList().find(nRet);
    if (p != sharedList().end())
    {
        p->second->Play((bLoop) ? -1 : 1);
    }

    return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Stop();
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

        sharedList().insert(Effect(nRet, new MciPlayer()));
        MciPlayer * pPlayer = sharedList()[nRet];
        pPlayer->Open(_FullPath(pszFilePath).c_str(), nRet);

        BREAK_IF(nRet == pPlayer->GetSoundID());

        delete pPlayer;
        sharedList().erase(nRet);
        nRet = 0;
    } while (0);
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Pause();
    }
}

void SimpleAudioEngine::pauseAllEffects()
{
    for (auto& iter : sharedList())
    {
        iter.second->Pause();
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Resume();
    }
}

void SimpleAudioEngine::resumeAllEffects()
{
    for (auto& iter : sharedList())
    {
        iter.second->Resume();
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    for (auto& iter : sharedList())
    {
        iter.second->Stop();
    }
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    unsigned int nID = _Hash(pszFilePath);

    EffectList::iterator p = sharedList().find(nID);
    if (p != sharedList().end())
    {
        delete p->second;
        p->second = nullptr;
        sharedList().erase(nID);
    }
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

static std::string _FullPath(const char * szPath)
{
    return FileUtils::getInstance()->fullPathForFilename(szPath);
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
