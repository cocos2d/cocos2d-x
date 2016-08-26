/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2014 Won, KyungYoun

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

#include <FBaseSysLog.h>
#include "PlayerImpl.h"
#include "OpenAlWavPlayer.h"
#include "OpenAlBufferPlayer.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Io;
using namespace Tizen::Base::Collection;

using namespace std;

_PlayerImpl::_PlayerImpl(void)
	:__pOpenAlPlayer(null)
	, __currentVolume(99)
{

}

_PlayerImpl::~_PlayerImpl(void)
{

}

result
_PlayerImpl::Construct(void)
{
	result r = E_SUCCESS;
	return r;
}

result
_PlayerImpl::OpenFile(const Tizen::Base::String& mediaLocalPath)
{
	result r = E_SUCCESS;
	String ext =  Tizen::Io::File::GetFileExtension(mediaLocalPath);

	if (ext.Equals(L"wav", false))
	{
		unique_ptr<OpenAlWavPlayer> pPlayer (new (std::nothrow) OpenAlWavPlayer());
		r = pPlayer->Construct(mediaLocalPath);
		TryReturn( r == E_SUCCESS, r, "[%s] Propagating.", GetErrorMessage(r));

		IOpenAlPlayer* pPlayerI = dynamic_cast<IOpenAlPlayer*>(pPlayer.release());
		__pOpenAlPlayer.reset(pPlayerI);
		TryReturn( __pOpenAlPlayer.get() != null, E_SYSTEM, "[E_SYSTEM] Openal player creation failed.");
	}
	else
	{
		unique_ptr<OpenAlBufferPlayer> pPlayer (new (std::nothrow) OpenAlBufferPlayer());
		r = pPlayer->Construct(mediaLocalPath);
		TryReturn( r == E_SUCCESS, r, "[%s] Propagating.", GetErrorMessage(r));

		IOpenAlPlayer* pPlayerI = dynamic_cast<IOpenAlPlayer*>(pPlayer.release());			
		__pOpenAlPlayer.reset(pPlayerI);
		TryReturn( __pOpenAlPlayer.get() != null, E_SYSTEM, "[E_SYSTEM] Openal player creation failed.");
	}

	return r;
}

result
_PlayerImpl::Close(void)
{
	result r = E_SUCCESS;
	return r;
}


result
_PlayerImpl::Play(void)
{
	result r = E_SUCCESS;
	TryReturn( __pOpenAlPlayer.get() != null, E_OBJ_NOT_FOUND,
				"[E_OBJ_NOT_FOUND] Player is not found.");
	r = __pOpenAlPlayer->Play();
	return r;
}


result
_PlayerImpl::Stop(void)
{
	result r = E_SUCCESS;
	TryReturn( __pOpenAlPlayer.get() != null, E_OBJ_NOT_FOUND,
				"[E_OBJ_NOT_FOUND] Player is not found.");
	r = __pOpenAlPlayer->Stop();
	return r;
}


result
_PlayerImpl::Pause(void)
{
	result r = E_SUCCESS;
	TryReturn( __pOpenAlPlayer.get() != null, E_OBJ_NOT_FOUND,
				"[E_OBJ_NOT_FOUND] Player is not found.");
	r = __pOpenAlPlayer->Pause();
	return r;
}


PlayerState
_PlayerImpl::GetState(void)
{
	PlayerState state = PLAYER_STATE_INITIALIZED;
	if (__pOpenAlPlayer.get() == null )
	{
		return state;
	}

	OpenAlPlayerState openAlState = OPENAL_PLAYER_STATE_NONE;
	openAlState = __pOpenAlPlayer->GetState();

	switch (openAlState)
	{
		case OPENAL_PLAYER_STATE_NONE:
			state = PLAYER_STATE_INITIALIZED;
			break;
		case OPENAL_PLAYER_STATE_INITIALIZED:
			state = PLAYER_STATE_INITIALIZED;
			break;
		case OPENAL_PLAYER_STATE_PLAYING:
			state = PLAYER_STATE_PLAYING;
			break;
		case OPENAL_PLAYER_STATE_PAUSED:
			state = PLAYER_STATE_PAUSED;
			break;
		case OPENAL_PLAYER_STATE_STOPPED:
			state = PLAYER_STATE_STOPPED;
			break;
		default:
			break;
	}
	return state;
}

int
_PlayerImpl::GetVolume(void) const
{
	return __currentVolume;
}

result
_PlayerImpl::SeekTo(long msTime)
{
	result r = E_SUCCESS;
	r = __pOpenAlPlayer->SeekTo(msTime);
	return r;
}


result
_PlayerImpl::SetVolume(int volume)
{
	result r = E_SUCCESS;
	r = __pOpenAlPlayer->SetVolume(volume);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagating.", GetErrorMessage(r));

	__currentVolume = volume;
	return r;
}

result
_PlayerImpl::SetLoop(bool flag)
{
	result r = E_SUCCESS;
	r = __pOpenAlPlayer->SetLoop(flag);
	return r;
}


