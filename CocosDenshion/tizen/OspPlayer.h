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

#ifndef _OSP_PLAYER_H_
#define _OSP_PLAYER_H_

#include <FMedia.h>

class OspPlayer : public Tizen::Media::IPlayerEventListener
{
public:
    OspPlayer();
    ~OspPlayer();

    result Initialize();
    void Open(const char* pFileName, unsigned int uId);
    void Play(bool bLoop);
    void Pause();
    void Stop();
    void Resume();
    void Rewind();
    bool IsPlaying();
    void SetVolume(int volume);
    int GetVolume();
    void Close();
    unsigned int GetSoundID();

protected:
    void OnPlayerOpened(result r);
    void OnPlayerEndOfClip(void);
    void OnPlayerBuffering(int percent);
    void OnPlayerErrorOccurred(Tizen::Media::PlayerErrorReason r);
    void OnPlayerInterrupted(void);
    void OnPlayerReleased(void);
    void OnPlayerSeekCompleted(result r);
    void OnPlayerAudioFocusChanged(void);

private:
    Tizen::Media::Player* __pPlayer;
    unsigned int m_nSoundID;
};

#endif // _OSP_PLAYER_H_
