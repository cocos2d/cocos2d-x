#include "MciPlayer.h"

#define WIN_CLASS_NAME        "CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

static HINSTANCE s_hInstance;
static MCIERROR  s_mciError;

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

MciPlayer::MciPlayer()
: _wnd(NULL)
, _dev(NULL)
, _soundID(0)
, _times(0)
, _playing(false)
{
    if (! s_hInstance)
    {
        s_hInstance = GetModuleHandleA( NULL );            // Grab An Instance For Our Window

        WNDCLASSA  wc;        // Windows Class Structure

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
        wc.lpszClassName  = WIN_CLASS_NAME;                 // Set The Class Name

        if (! RegisterClassA(&wc)
            && 1410 != GetLastError())
        {
            return;
        }
    }

    _wnd = CreateWindowExA(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        WIN_CLASS_NAME,                                        // Class Name
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
        SetWindowLongA(_wnd, GWL_USERDATA, (LONG)this);
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

        Close();

        MCI_OPEN_PARMSA mciOpen = {0};
        MCIERROR mciError;
        mciOpen.lpstrDeviceType = (LPCSTR)MCI_ALL_DEVICE_ID;
        mciOpen.lpstrElementName = pFileName;

        mciError = mciSendCommandA(0,MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
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
    mciPlay.dwCallback = (DWORD_PTR)_wnd;
    s_mciError = mciSendCommandA(_dev,MCI_PLAY, MCI_FROM|MCI_NOTIFY,(DWORD)&mciPlay);
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
}

void MciPlayer::Resume()
{
    _SendGenericCommand(MCI_RESUME);
}

void MciPlayer::Stop()
{
    _SendGenericCommand(MCI_STOP);
    _playing = false;
}

void MciPlayer::Rewind()
{
    if (! _dev)
    {
        return;
    }
    mciSendCommandA(_dev, MCI_SEEK, MCI_SEEK_TO_START, 0);

    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD)_wnd;
    _playing = mciSendCommandA(_dev, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay) ? false : true;
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

void MciPlayer::_SendGenericCommand(int nCommand)
{
    if (! _dev)
    {
        return;
    }
    mciSendCommandA(_dev, nCommand, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    MciPlayer * pPlayer = NULL;
    if (MM_MCINOTIFY == Msg 
        && MCI_NOTIFY_SUCCESSFUL == wParam
        &&(pPlayer = (MciPlayer *)GetWindowLongA(hWnd, GWL_USERDATA)))
    {
        if (pPlayer->_times)
        {
            --pPlayer->_times;
        }

        if (pPlayer->_times)
        {
            mciSendCommandA(lParam, MCI_SEEK, MCI_SEEK_TO_START, 0);

            MCI_PLAY_PARMS mciPlay = {0};
            mciPlay.dwCallback = (DWORD)hWnd;
            mciSendCommandA(lParam, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay);
        }
        else
        {
            pPlayer->_playing = false;
        }
        return 0;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

} // end of namespace CocosDenshion
