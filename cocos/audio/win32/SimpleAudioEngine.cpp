/****************************************************************************
http://www.openaudioengine.com/

http://post.justbilt.com/2013/11/29/cocos2dx_simpleaudio/
****************************************************************************/


#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>


#include "MciPlayer.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

namespace CocosDenshion {

typedef map<unsigned int, MciPlayer *> EffectList;
typedef EffectList::iterator EffectListIt;
typedef pair<unsigned int, MciPlayer *> Effect;

static std::string _FullPath(const char * szPath);
static unsigned int _StreameID();

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
	HINSTANCE lib = LoadLibrary("OpenAE.dll"); //Load Engine   


	// Get entry-function pointer for render device
	oae::Renderer* (*driver)(const char*,const unsigned&) = nullptr;
	driver = (oae::Renderer*(*)(const char*,const unsigned&)) 
		GetProcAddress(lib, "GetRenderDevice"); 

	unsigned choice=0; 

	// Get entry-function pointer for enum device
	const char* (*available)(unsigned int&) = nullptr;
	available = (const char*(*)(unsigned int&)) GetProcAddress(lib, "GetDeviceName"); 

	//enumerate and display device
	for(unsigned j=0; available(j)!=nullptr; j++)
	{
		log(available(j));
	} 

	MciPlayer::dev = driver(available(choice), 48000);
	oae::Listener* lis = MciPlayer::dev->GetListener();

	MciPlayer::lib=lib;
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

    EffectList::iterator p = sharedList().begin();
    while (p != sharedList().end())
    {
        delete p->second;
        p->second = NULL;
        p++;
    }   
    sharedList().clear();

	MciPlayer::dev->ReleaseRenderer(); // release device
	FreeLibrary(MciPlayer::lib); // release engine
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

	if (sharedMusic().m_strFileName!=_FullPath(pszFilePath))
	{
		sharedMusic().Close();
	}
	
	if (sharedMusic().m_scr==NULL)
	{
		sharedMusic().Open(_FullPath(pszFilePath).c_str(), _StreameID());
	}
	
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
	if (!pszFilePath)
	{
		return 0;
	}

	//看池中是否有缓冲好的
	for (EffectListIt it=sharedList().begin();it!=sharedList().end();++it)
	{
		MciPlayer* pTempPlayer=it->second;
		if (!pTempPlayer->IsPlaying() && pTempPlayer->m_strFileName==_FullPath(pszFilePath))
		{
			pTempPlayer->Play((bLoop) ? -1 : 1);
			return pTempPlayer->m_nSoundID;
		}
	}
	
	//添加新的
    unsigned int nRet = _StreameID();

	MciPlayer* pPlayer=new MciPlayer();
	if (!pPlayer)
	{
		return 0;
	}
	
	pPlayer->Open(_FullPath(pszFilePath).c_str(), nRet);
	sharedList().insert(Effect(nRet, pPlayer));
    pPlayer->Play((bLoop) ? -1 : 1);

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
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Pause();
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
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Resume();
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Stop();
    }
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	for (EffectListIt it=sharedList().begin();it!=sharedList().end();++it)
	{
		if (it->second->m_strFileName==pszFilePath)
		{
			delete it->second;
			it->second = NULL;
			it=sharedList().erase(it);
		}		
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

#define MAX_SOUND 256

unsigned int _StreameID()
{
	static unsigned int nSteameID=0;
	++nSteameID;
	log("%d",nSteameID);

	//Multi-Channel 256 simultaneous sources
	if (sharedList().size()>=MAX_SOUND)
	{
		for (EffectListIt it=sharedList().begin();it!=sharedList().end();)
		{
			if (!it->second->m_scr->GetSourceState())
			{
				it->second->Close();
				delete it->second;
				it->second = NULL;
				it=sharedList().erase(it);
			}	
			else
			{
				++it;
			}
		}
	}
    
    return nSteameID;
}

} // end of namespace CocosDenshion
