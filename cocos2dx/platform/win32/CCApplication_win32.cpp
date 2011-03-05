#include "CCApplication_win32.h"

#include "CCDirector.h"

/**
@brief	This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/
static void PVRFrameEnableControlWindow(bool bEnable);

namespace   cocos2d {

static CCApplication * s_pApplication;

CCApplication::CCApplication()
	: m_hAccelTable(NULL)
{
	m_hInstance	= GetModuleHandle(NULL);
	s_pApplication = this;
}

CCApplication::~CCApplication()
{
	s_pApplication = NULL;
}

ccDeviceOrientation CCApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
{
	// swap width and height
	CCEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
	if (pView)
	{
		return (ccDeviceOrientation)pView->setDeviceOrientation(eOritation);
	}
	return CCDirector::sharedDirector()->getDeviceOrientation();
}

CCRect CCApplication::statusBarFrame()
{
	CCRect rc;
	return rc;
}

int CCApplication::Run()
{
    PVRFrameEnableControlWindow(false);

	// Main message loop:
	MSG msg;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLast);

    if ( !applicationDidFinishLaunching() )
    {
        return 0;
    }
    
	while (1)
	{
		if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
            QueryPerformanceCounter(&nNow);
			if (nNow.QuadPart - nLast.QuadPart >= m_nAnimationInterval.QuadPart)
			{
                nLast.QuadPart = nNow.QuadPart;
				CCDirector::sharedDirector()->mainLoop();
			}
			else
			{
				Sleep(0);
			}
			continue;
		}

		if (WM_QUIT == msg.message)
		{
			break;
		}

		if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

//////////////////////////////////////////////////////////////////////////
// Implement static class member
//////////////////////////////////////////////////////////////////////////
CCApplication * CCApplication::sharedApplication()
{
	return s_pApplication;
}

void CCApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

}

//////////////////////////////////////////////////////////////////////////
// Local function
//////////////////////////////////////////////////////////////////////////
static void PVRFrameEnableControlWindow(bool bEnable)
{
    HKEY hKey = 0;

    // Open PVRFrame control key, if not exist create it.
    if(ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
        L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
        0,
        0,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        0,
        &hKey,
        NULL))
    {
        return;
    }

    const wchar_t * wszValue = L"hide_gui";
    const wchar_t * wszNewData = (bEnable) ? L"NO" : L"YES";
    wchar_t wszOldData[256] = {0};
    DWORD   dwSize = sizeof(wszOldData);
    LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, NULL, (LPBYTE)wszOldData, &dwSize);
    if (ERROR_FILE_NOT_FOUND == status              // the key not exist
        || (ERROR_SUCCESS == status                 // or the hide_gui value is exist
        && 0 != wcscmp(wszNewData, wszOldData)))    // but new data and old data not equal
    {
        dwSize = sizeof(wchar_t) * (wcslen(wszNewData) + 1);
        RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE *)wszNewData, dwSize);
    }

    RegCloseKey(hKey);
}
