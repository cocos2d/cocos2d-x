#include "CCXApplication_win32.h"

#include "CCDirector.h"

namespace   cocos2d {

static CCXApplication * s_pApplication;

CCXApplication::CCXApplication()
: m_hAccelTable(NULL)
{
	m_hInstance	= GetModuleHandle(NULL);
	s_pApplication = this;
}

CCXApplication::~CCXApplication()
{
    s_pApplication = NULL;
}

void CCXApplication::setDeviceOrientation(int nOritation)
{
//         TWindow * pWnd = TApplication::GetCurrentWindow();
//         if (! pWnd)
//         {
//             return;
//         }
//         switch (nOritation)
//         {
//         /// Device oriented vertically, home button on the bottom
//         case kCCDeviceOrientationPortrait:
//             pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_NORMAL);
//             break;
//         /// Device oriented vertically, home button on the top
//         case kCCDeviceOrientationPortraitUpsideDown:
//             pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_UD);
//             break;
// 
//         /// Device oriented horizontally, home button on the right
//         case kCCDeviceOrientationLandscapeLeft:
//             pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_CW);
//             break;
//         /// Device oriented horizontally, home button on the left
//         case kCCDeviceOrientationLandscapeRight:
//             pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_CCW);
//             break;
//         }
}

CGRect CCXApplication::statusBarFrame()
{
    CGRect rc;
    return rc;
}

bool CCXApplication::InitInstance()
{
	return initCocos2d();
}

int CCXApplication::Run()
{
	// Main message loop:
	MSG msg;
	 while (1)
	{
		if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			CCDirector::getSharedDirector()->preMainLoop();
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
/// Implement static class member
//////////////////////////////////////////////////////////////////////////
CCXApplication * CCXApplication::getSharedApplication()
{
    return s_pApplication;
}

}
