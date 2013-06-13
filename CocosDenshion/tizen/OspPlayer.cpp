/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "OspPlayer.h"

using namespace Tizen::Media;

OspPlayer::OspPlayer()
    : __pPlayer(null)
    , m_nSoundID(0)
{
    Initialize();
}

OspPlayer::~OspPlayer()
{
    Close();
}

result
OspPlayer::Initialize()
{
    result r = E_SUCCESS;

    __pPlayer = new (std::nothrow) Player();
    if (__pPlayer == null)
    {
        AppLogException("pPlyaer = new (std::nothrow) Player() has failed");
        return E_FAILURE;
    }

    r = __pPlayer->Construct(*this, null);
    if (IsFailed(r))
    {
        AppLog("pPlayer->Construct has failed\n");
        return E_FAILURE;
    }

    return r;
}

void
OspPlayer::Open(const char* pFileName, unsigned int uId)
{
    result r = E_SUCCESS;

    Close();

    r = __pPlayer->OpenFile(pFileName);
    if (IsFailed(r))
    {
        AppLog("pPlayer->OpenFile has failed\n");
    }

    m_nSoundID = uId;
}

void
OspPlayer::Play(bool bLoop)
{
    result r = E_SUCCESS;

    r = __pPlayer->SetLooping(bLoop);
    if (IsFailed(r))
    {
        AppLog("pPlayer->SetLooping has failed\n");
        return;
    }

    r = __pPlayer->Play();
    if (IsFailed(r))
    {
        AppLog("pPlayer->Play has failed\n");
    }
}

void
OspPlayer::Pause()
{
    result r = E_SUCCESS;

    r = __pPlayer->Pause();
    if (IsFailed(r))
    {
        AppLog("pPlayer->Pause has failed\n");
    }
}

void
OspPlayer::Stop()
{
    result r = E_SUCCESS;

    r = __pPlayer->Stop();
    if (IsFailed(r))
    {
        AppLog("pPlayer->Stop has failed\n");
    }
}

void
OspPlayer::Resume()
{
    result r = E_SUCCESS;

    if (__pPlayer->GetState() == PLAYER_STATE_PAUSED)
    {
        r = __pPlayer->Play();
        if (IsFailed(r))
        {
            AppLog("pPlayer->Play has failed\n");
        }
    }
}

void
OspPlayer::Rewind()
{
    result r = E_SUCCESS;

    r = __pPlayer->SeekTo(0);
    if (IsFailed(r))
    {
        AppLog("pPlayer->SeekTo has failed\n");
    }
}

bool
OspPlayer::IsPlaying()
{
    PlayerState state = __pPlayer->GetState();

    return (state == PLAYER_STATE_PLAYING) ? true : false;
}

void
OspPlayer::Close()
{
    result r = E_SUCCESS;

    if (__pPlayer->GetState() == PLAYER_STATE_PLAYING)
    {
        r = __pPlayer->Stop();
        if (IsFailed(r))
        {
            AppLog("pPlayer->Stop has failed\n");
        }
    }

    r = __pPlayer->Close();
    if (IsFailed(r))
    {
        AppLog("pPlayer->Close has failed\n");
    }
}

unsigned int
OspPlayer::GetSoundID()
{
    return m_nSoundID;
}

void
OspPlayer::SetVolume(int volume)
{
    result r = E_SUCCESS;

    if (volume > 100 || volume < 0)
    {
        return;
    }

    r = __pPlayer->SetVolume(volume);
    if (IsFailed(r))
    {
        AppLog("pPlayer->SetVolume has failed\n");
    }
}

int
OspPlayer::GetVolume()
{
    return __pPlayer->GetVolume();
}

void
OspPlayer::OnPlayerOpened(result r)
{
}

void
OspPlayer::OnPlayerEndOfClip(void)
{
}

void
OspPlayer::OnPlayerBuffering(int percent)
{
}

void
OspPlayer::OnPlayerErrorOccurred(Tizen::Media::PlayerErrorReason r)
{
}

void
OspPlayer::OnPlayerInterrupted(void)
{
}

void
OspPlayer::OnPlayerReleased(void)
{
}

void
OspPlayer::OnPlayerSeekCompleted(result r)
{
}

void
OspPlayer::OnPlayerAudioFocusChanged(void)
{
}
