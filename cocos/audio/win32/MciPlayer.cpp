#include "MciPlayer.h"
#include "cocos2d.h"

namespace CocosDenshion {


HMODULE MciPlayer::_lib=NULL;

oae::Renderer* MciPlayer::_device=NULL;

MciPlayer::MciPlayer()
: _nSoundID(0)
, _uTimes(0)
, _scr(NULL)
{

}

MciPlayer::~MciPlayer()
{

}

void MciPlayer::Open(const char* pFileName, UINT uId)
{
	_scr=_device->GetScreamer(pFileName);

	if (_scr==NULL)
	{
		if (!cocos2d::CCFileUtils::getInstance()->isFileExist(_fileName))
		{
			assert(_scr!=NULL && "File not exist!");
		}
		else
		{
			assert(_scr!=NULL && "Only suppost .ogg file!");
		}
	}
	
	_fileName=pFileName;
	
	_nSoundID=uId;
}

void MciPlayer::Play(UINT uTimes /* = 1 */)
{
	assert(_scr);

	_scr->SetSourceState(1);
	_uTimes=uTimes;

	UINT nTime=-1;

	_scr->Loop(nTime==uTimes);
}

void MciPlayer::Close()
{
	_device->ReleaseScreamer(_scr);
	_scr=NULL;
}

void MciPlayer::Pause()
{	
	if (_scr)
	{
		_scr->SetSourceState(0);
	}
}

void MciPlayer::Resume()
{
	if (_scr)
	{
		_scr->SetSourceState(1);
	}
}

void MciPlayer::Stop()
{
	if (_scr)
	{
		_scr->SetSourceState(0);
		_scr->Seek(0);
	}
}

void MciPlayer::Rewind()
{

}

bool MciPlayer::IsPlaying()
{
	if (!_scr)
	{
		return false;
	}
	
    return _scr->GetSourceState();
}

UINT MciPlayer::GetSoundID()
{
    return _nSoundID;
}

}