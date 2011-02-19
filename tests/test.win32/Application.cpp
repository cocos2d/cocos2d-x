#include "Application.h"

#include "CCDirector.h"
USING_NS_CC;

Application::Application()
: m_hInstance(NULL)
, m_hAccelTable(NULL)
{
    m_hInstance	= GetModuleHandle(NULL);
    m_nAnimationInterval.QuadPart = 0;
}

Application::~Application()
{

}

int Application::run()
{
    // Main message loop:
    MSG msg;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLast);

    // Make sharedApplication work correctly.
    setSharedApplication(*this);

    // Initialize AppDelegate.
    if (! m_Delegate.applicationDidFinishLaunching())
    {
        return 0;
    }

    m_MainWnd.centerWindow();
    ShowWindow(m_MainWnd.getHWnd(), SW_SHOW);

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

bool Application::initInstance()
{
    bool bRet = false;
    do 
    {
        // the HelloWorld is designed as HVGA
        CCX_BREAK_IF(! m_MainWnd.Create(TEXT("cocos2d-win32"), 320, 480));
// #define SHOW_AS_WVGA
#ifdef  SHOW_AS_WVGA
        // the design size HVGA is 480x320
        // the WVGA is 800x480
        // screenScaleFactor = WVGA/HVGA = min(800/480, 480/320) = 1.5
        m_MainWnd.setScreenScale(1.5f);
        m_MainWnd.resize(480, 800);
#endif  // SHOW_AS_WVGA

        bRet = true;
    } while (0);
    return bRet;
}

void Application::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

Application::Orientation Application::setOrientation(Application::Orientation orientation)
{
    // swap width and height
    CCXEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pView)
    {
        return (Orientation)pView->setDeviceOrientation(orientation);
    }
    return (Orientation)CCDirector::sharedDirector()->getDeviceOrientation();
}

void Application::statusBarFrame(cocos2d::CGRect * rect)
{
    if (rect)
    {
        // Windows doesn't have status bar.
        *rect = CGRectMake(0, 0, 0, 0);
    }
}
