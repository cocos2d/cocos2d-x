#include "MciPlayer.h"
#include "cocos2d.h"

namespace CocosDenshion {


HMODULE MciPlayer::lib=NULL;

oae::Renderer* MciPlayer::dev=NULL;

MciPlayer::MciPlayer()
: m_nSoundID(0)
, m_uTimes(0)
, m_scr(NULL)
{

}

MciPlayer::~MciPlayer()
{

}

void MciPlayer::Open(const char* pFileName, UINT uId)
{
	m_scr=dev->GetScreamer(pFileName);

	if (m_scr==NULL)
	{
		if (!cocos2d::CCFileUtils::getInstance()->isFileExist(m_strFileName))
		{
			assert(m_scr!=NULL && "File not exist!");
		}
		else
		{
			assert(m_scr!=NULL && "Only suppost .ogg file!");
		}
	}
	
	m_strFileName=pFileName;
	
	m_nSoundID=uId;
}

void MciPlayer::Play(UINT uTimes /* = 1 */)
{
	assert(m_scr);

	m_scr->SetSourceState(1);
	m_uTimes=uTimes;

	UINT nTime=-1;

	m_scr->Loop(nTime==uTimes);
}

void MciPlayer::Close()
{
	dev->ReleaseScreamer(m_scr);
	m_scr=NULL;
}

void MciPlayer::Pause()
{	
	if (m_scr)
	{
		m_scr->SetSourceState(0);
	}
}

void MciPlayer::Resume()
{
	if (m_scr)
	{
		m_scr->SetSourceState(1);
	}
}

void MciPlayer::Stop()
{
	if (m_scr)
	{
		m_scr->SetSourceState(0);
		m_scr->Seek(0);
	}
}

void MciPlayer::Rewind()
{

}

bool MciPlayer::IsPlaying()
{
	if (!m_scr)
	{
		return false;
	}
	
    return m_scr->GetSourceState();
}

UINT MciPlayer::GetSoundID()
{
    return m_nSoundID;
}

}