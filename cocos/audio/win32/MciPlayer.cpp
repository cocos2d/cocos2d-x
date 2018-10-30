/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "audio/win32/MciPlayer.h"
#include <tchar.h>
#include "platform/CCFileUtils.h"

#define WIN_CLASS_NAME        "CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

static HINSTANCE s_hInstance;
static MCIERROR  s_mciError;

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

MciPlayer::MciPlayer()
: _wnd(NULL)
, _dev(0L)
, _soundID(0)
, _times(0)
, _playing(false)
, strExt("")
{
    if (! s_hInstance)
    {
        s_hInstance = GetModuleHandle( NULL );            // Grab An Instance For Our Window

        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = 0;
        wc.lpfnWndProc    = _SoundPlayProc;                    // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                                // No Extra Window Data
        wc.hInstance      = s_hInstance;                    // Set The Instance
        wc.hIcon          = 0;                                // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = _T(WIN_CLASS_NAME);                 // Set The Class Name

        if (! RegisterClass(&wc)
            && ERROR_CLASS_ALREADY_EXISTS != GetLastError())
        {
            return;
        }
    }

    _wnd = CreateWindowEx(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        _T(WIN_CLASS_NAME),                                        // Class Name
        NULL,                                        // Window Title
        WS_POPUPWINDOW,/*WS_OVERLAPPEDWINDOW*/               // Defined Window Style
        0, 0,                                                // Window Position
        0,                                                    // Window Width
        0,                                                    // Window Height
        NULL,                                                // No Parent Window
        NULL,                                                // No Menu
        s_hInstance,                                        // Instance
        NULL );
    if (_wnd)
    {
        SetWindowLongPtr(_wnd, GWLP_USERDATA, (LONG_PTR)this);
    }
}

MciPlayer::~MciPlayer()
{
    Close();
    DestroyWindow(_wnd);
}

void MciPlayer::Open(const char* pFileName, UINT uId)
{
//     WCHAR * pBuf = NULL;
    do
    {
        BREAK_IF(! pFileName || ! _wnd);
        int nLen = (int)strlen(pFileName);
        BREAK_IF(! nLen);
//         pBuf = new WCHAR[nLen + 1];
//         BREAK_IF(! pBuf);
//         MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, pBuf, nLen + 1);

        strExt = cocos2d::FileUtils::getInstance()->getFileExtension(pFileName);

        Close();

        MCI_OPEN_PARMS mciOpen = {0};
        MCIERROR mciError;
        mciOpen.lpstrDeviceType = (LPCTSTR)MCI_ALL_DEVICE_ID;
        WCHAR* fileNameWideChar = new WCHAR[nLen + 1];
        BREAK_IF(! fileNameWideChar);
        MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, fileNameWideChar, nLen + 1);
        mciOpen.lpstrElementName = fileNameWideChar;

        mciError = mciSendCommand(0,MCI_OPEN, MCI_OPEN_ELEMENT, reinterpret_cast<DWORD_PTR>(&mciOpen));
        CC_SAFE_DELETE_ARRAY(mciOpen.lpstrElementName);
        BREAK_IF(mciError);

        _dev = mciOpen.wDeviceID;
        _soundID = uId;
        _playing = false;
    } while (0);
}

void MciPlayer::Play(UINT uTimes /* = 1 */)
{
    if (! _dev)
    {
        return;
    }
    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = reinterpret_cast<DWORD_PTR>(_wnd);
    s_mciError = mciSendCommand(_dev,MCI_PLAY, MCI_FROM|MCI_NOTIFY,reinterpret_cast<DWORD_PTR>(&mciPlay));
    if (! s_mciError)
    {
        _playing = true;
        _times = uTimes;
    }
}

void MciPlayer::Close()
{
    if (_playing)
    {
        Stop();
    }
    if (_dev)
    {
         _SendGenericCommand(MCI_CLOSE);
    }
    _dev = 0;
    _playing = false;
}

void MciPlayer::Pause()
{
    _SendGenericCommand(MCI_PAUSE);
    _playing = false;
}

void MciPlayer::Resume()
{
    if (strExt == ".mid")
    {
        // midi not support MCI_RESUME, should get the position and use MCI_FROM
        MCI_STATUS_PARMS mciStatusParms;
        MCI_PLAY_PARMS   mciPlayParms;
        mciStatusParms.dwItem = MCI_STATUS_POSITION;
        _SendGenericCommand(MCI_STATUS, MCI_STATUS_ITEM, reinterpret_cast<DWORD_PTR>(&mciStatusParms)); // MCI_STATUS
        mciPlayParms.dwFrom = mciStatusParms.dwReturn;  // get position
        _SendGenericCommand(MCI_PLAY, MCI_FROM, reinterpret_cast<DWORD_PTR>(&mciPlayParms)); // MCI_FROM
    }
    else
    {
        _SendGenericCommand(MCI_RESUME);
        _playing = true;
    }
}

void MciPlayer::Stop()
{
    _SendGenericCommand(MCI_STOP);
    _playing = false;
    _times = 0;
}

void MciPlayer::Rewind()
{
    if (! _dev)
    {
        return;
    }
    mciSendCommand(_dev, MCI_SEEK, MCI_SEEK_TO_START, 0);

    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = reinterpret_cast<DWORD_PTR>(_wnd);
    _playing = mciSendCommand(_dev, MCI_PLAY, MCI_NOTIFY,reinterpret_cast<DWORD_PTR>(&mciPlay)) ? false : true;
}

bool MciPlayer::IsPlaying()
{
    return _playing;
}

UINT MciPlayer::GetSoundID()
{
    return _soundID;
}

//////////////////////////////////////////////////////////////////////////
// private member
//////////////////////////////////////////////////////////////////////////
void MciPlayer::_SendGenericCommand( int nCommand, DWORD_PTR param1 /*= 0*/, DWORD_PTR parma2 /*= 0*/ )
{
    if (! _dev)
    {
        return;
    }
    mciSendCommand(_dev, nCommand, param1, parma2);
}


//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    MciPlayer * pPlayer = NULL;
    if (MM_MCINOTIFY == Msg
        && MCI_NOTIFY_SUCCESSFUL == wParam
        &&(pPlayer = (MciPlayer *)GetWindowLongPtr(hWnd, GWLP_USERDATA)))
    {
        if (pPlayer->_times)
        {
            --pPlayer->_times;
        }

        if (pPlayer->_times)
        {
            mciSendCommand(lParam, MCI_SEEK, MCI_SEEK_TO_START, 0);

            MCI_PLAY_PARMS mciPlay = {0};
            mciPlay.dwCallback = reinterpret_cast<DWORD_PTR>(hWnd);
            mciSendCommand(lParam, MCI_PLAY, MCI_NOTIFY,reinterpret_cast<DWORD_PTR>(&mciPlay));
        }
        else
        {
            pPlayer->_playing = false;
        }
        return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

} // end of namespace CocosDenshion
