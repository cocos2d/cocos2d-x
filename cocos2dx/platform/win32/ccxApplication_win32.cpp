#include "ccxApplication.h"

#include "CCDirector.h"
#include "CCXEGLView.h"

NS_CC_BEGIN;

// sharedApplication pointer
ccxApplication * ccxApplication::sm_pSharedApplication = 0;

ccxApplication::ccxApplication()
: m_hInstance(NULL)
, m_hAccelTable(NULL)
{
    m_hInstance	= GetModuleHandle(NULL);
    m_nAnimationInterval.QuadPart = 0;
    CCX_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

ccxApplication::~ccxApplication()
{
    CCX_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int ccxApplication::run()
{
    // Main message loop:
    MSG msg;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLast);

    // Initialize instance and cocos2d.
    if (! initInstance() || ! applicationDidFinishLaunching())
    {
        return 0;
    }

    CCXEGLView& mainWnd = CCXEGLView::sharedOpenGLView();
    mainWnd.centerWindow();
    ShowWindow(mainWnd.getHWnd(), SW_SHOW);

    while (1)
    {
        if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Get current time tick.
            QueryPerformanceCounter(&nNow);

            // If it's the time to draw next frame, draw it, else sleep a while.
            if (nNow.QuadPart - nLast.QuadPart > m_nAnimationInterval.QuadPart)
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
            // Quit message loop.
            break;
        }

        // Deal with windows message.
        if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void ccxApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

ccxApplication::Orientation ccxApplication::setOrientation(Orientation orientation)
{
    // swap width and height
    CCXEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pView)
    {
        return (Orientation)pView->setDeviceOrientation(orientation);
    }
    return (Orientation)CCDirector::sharedDirector()->getDeviceOrientation();
}

void ccxApplication::statusBarFrame(CGRect * rect)
{
    if (rect)
    {
        // Windows doesn't have status bar.
        *rect = CGRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
ccxApplication& ccxApplication::sharedApplication()
{
    CCX_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

NS_CC_END;
