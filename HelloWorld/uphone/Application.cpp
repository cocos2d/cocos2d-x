#include "Application.h"
#include "ssBackLightControl.h"
#include "ssKeyLockControl.h"

using namespace cocos2d;

static const Int32 CCX_ON_APPLICATION_IDLE = (EVENT_FirstUser + EVENT_LastUser) / 2;

#ifdef _TRANZDA_VM_
static  LARGE_INTEGER s_nAnimationInterval;
static  LARGE_INTEGER s_nFreq;
static  LARGE_INTEGER s_nLast;
#else
#include <sys/time.h>
static long long s_nAnimationInterval;
static long long s_nLast;
static long long getTimeOfDayMicroSecond()
{
    timeval val;
    gettimeofday(&val, NULL);
    return (long long)val.tv_sec * 1000 * 1000 + val.tv_usec;
}
#endif

Application::Application()
: m_bRunning(FALSE)
, m_bNeedStop(FALSE)
, m_bInBackground(FALSE)
{
    memset(&m_tMsg, 0, sizeof(m_tMsg));
    SS_GetCurrentGTID(&m_tMsg.gtid);
    m_tMsg.type = CCX_ON_APPLICATION_IDLE;

    Sys_RegisterMessageCallBack(CCX_ON_APPLICATION_IDLE, Application::_OnAppIdle, (UInt32)this);

    memset(m_AppDataPath, 0, sizeof(char) * EOS_FILE_MAX_PATH);

    do 
    {
        TUChar AppID[EOS_FILE_MAX_PATH] = {0};
        UInt32 nCmdType = 0;
        Int32  nRet = SS_AppRequest_GetAppName(AppID, &nCmdType);
        CCX_BREAK_IF(nRet < 0);

        TUChar AppPath[EOS_FILE_MAX_PATH] = {0};
        SS_GetApplicationPath(AppID, SS_APP_PATH_TYPE_EXECUTABLE, AppPath);
        TUString::StrUnicodeToStrUtf8((Char*) m_AppDataPath, AppPath);
    } while (0);
}

Application::~Application()
{
    Sys_RegisterMessageCallBack(CCX_ON_APPLICATION_IDLE, NULL, NULL);
}

Boolean  Application::EventHandler(EventType*  pEvent)
{
    Boolean     bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_AppLoad:
        setSharedApplication(*this);
        if (! m_Delegate.applicationDidFinishLaunching())
        {
            CCScheduler::purgeSharedScheduler();
            SendStopEvent();
        }
#ifdef _TRANZDA_VM_
        QueryPerformanceFrequency(&s_nFreq);
        QueryPerformanceCounter(&s_nLast);
#else
        s_nLast = getTimeOfDayMicroSecond();
#endif
        bHandled = TRUE;
        break;

    case EVENT_AppStopNotify:
        break;

    case EVENT_AppActiveNotify:
        if (pEvent->sParam1 == 0)
        {
            if (!m_bInBackground)
            {
                m_Delegate.applicationDidEnterBackground();
                m_bInBackground = true;
            }

            if (CCDirector::sharedDirector()->isPaused())
            {
                StopMainLoop();
            }
            CfgTurnOnBackLight();
            EnableKeyLock();
        }
        else if (pEvent->sParam1 > 0)
        {
            if (m_bInBackground)
            {
                m_Delegate.applicationWillEnterForeground();
                m_bInBackground = false;
            }

            StartMainLoop();

            CfgTurnOnBackLightDelay(0x7fffffff);
            // if KeyLock disactived, disable it.
            if (! CfgKeyLock_GetActive())
            {
                DisableKeyLock();
            }
        }
        break;
    }
    if (FALSE == bHandled) 
    {
        return TApplication::EventHandler(pEvent);
    }

    return bHandled;
}

bool Application::initInstance()
{
    CCXEGLView* pMainWnd = new CCXEGLView(this);
    bool bRet = false;

    do 
    {
        CCX_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480));

#ifndef _TRANZDA_VM_  
        // on uphone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        cocos2d::CCFileUtils::setResource("HelloWorld.zip");
#endif

        bRet = true;
    } while (0);

    return bRet;
}

void Application::setAnimationInterval(double interval)
{
#ifdef _TRANZDA_VM_
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    s_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
#else
    s_nAnimationInterval = (long long)(interval * 1000 * 1000);
#endif
}

Application::Orientation Application::setOrientation(Application::Orientation orientation)
{
    return orientation;
}

void Application::statusBarFrame(CGRect * rect)
{
}

const char* Application::getAppDataPath()
{
    return m_AppDataPath;
}

void Application::switchNotify(int nTurnOn)
{
    bool bInBack = isInBackground();

    do 
    {
        // if the app have be in background,don't handle this message
        CCX_BREAK_IF(bInBack);

        if (! nTurnOn)  // turn off screen
        {
            // CCDirector::sharedDirector()->pause();
            m_Delegate.applicationDidEnterBackground();
            StopMainLoop();
        }
        else
        {
            // CCDirector::sharedDirector()->resume();
            m_Delegate.applicationWillEnterForeground();
            StartMainLoop();
        }
    } while (0);
}

bool Application::isInBackground()
{
    return m_bInBackground;
}

void Application::StartMainLoop()
{
    if (m_bRunning)
    {
        m_bNeedStop = FALSE;
        return;
    }
    Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &m_tMsg);
    m_bRunning = TRUE;
}

void Application::StopMainLoop()
{
    m_bNeedStop = TRUE;
}

Int32 Application::_OnAppIdle(MESSAGE_t * pMsg, UInt32 uData)
{
    Application& rThis = (Application&) Application::sharedApplication();
    CCXEGLView *     pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pView && rThis.m_bRunning)
    {
        if (rThis.m_bNeedStop)
        {
            rThis.m_bNeedStop = FALSE;
            rThis.m_bRunning  = FALSE;
        }
        else
        {
#ifdef _TRANZDA_VM_
            LARGE_INTEGER nNow;
            QueryPerformanceCounter(&nNow);
            if (nNow.QuadPart - s_nLast.QuadPart >= s_nAnimationInterval.QuadPart)
            {
                pView->UpdateWindow(0);
                s_nLast.QuadPart = nNow.QuadPart;
            }
#else
            long long nNow = getTimeOfDayMicroSecond();
            if (nNow - s_nLast >= s_nAnimationInterval)
            {
                pView->UpdateWindow(0);
                s_nLast = nNow;
            }
#endif
            else
            {
                Sys_Sleep(0);
            }
            Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &rThis.m_tMsg);
        }
    }
    return 1;
}
