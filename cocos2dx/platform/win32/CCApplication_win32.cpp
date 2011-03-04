#include "CCApplication_win32.h"

#include "CCDirector.h"

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
