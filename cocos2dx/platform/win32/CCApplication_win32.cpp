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

ccDeviceOrientation CCXApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
{
	// swap width and height
	CCXEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
	if (pView)
	{
		return (ccDeviceOrientation)pView->setDeviceOrientation(eOritation);
	}
	return CCDirector::sharedDirector()->getDeviceOrientation();
}

CGRect CCXApplication::statusBarFrame()
{
	CGRect rc;
	return rc;
}

int CCXApplication::Run()
{
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
/// Implement static class member
//////////////////////////////////////////////////////////////////////////
CCXApplication * CCXApplication::sharedApplication()
{
	return s_pApplication;
}

void CCXApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

}
