#include "CCXApplication_uphone.h"

#include "ssBackLightControl.h"
#include "ssKeyLockControl.h"

#include "CCDirector.h"
#include "CCScheduler.h"

// #include "CCXGLExtFunc.h"
#include <GLES/glext.h>

namespace   cocos2d {

static const Int32 CCX_ON_APPLICATION_IDLE = (EVENT_FirstUser + EVENT_LastUser) / 2;

CCXApplication::CCXApplication()
: m_bRunning(FALSE)
, m_bNeedStop(FALSE)
{
    memset(&m_tMsg, 0, sizeof(m_tMsg));
    SS_GetCurrentGTID(&m_tMsg.gtid);
    m_tMsg.type = CCX_ON_APPLICATION_IDLE;

    Sys_RegisterMessageCallBack(CCX_ON_APPLICATION_IDLE, CCXApplication::_OnAppIdle, (UInt32)this);

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

CCXApplication::~CCXApplication()
{
    Sys_RegisterMessageCallBack(CCX_ON_APPLICATION_IDLE, NULL, NULL);
}

Boolean CCXApplication::EventHandler(EventType * pEvent)
{
    Boolean bHandled = FALSE;
    switch (pEvent->eType)
    {
    case EVENT_AppLoad:
        if (! applicationDidFinishLaunching())
        {
            CCScheduler::purgeSharedScheduler();
            SendStopEvent();
        }
        bHandled = TRUE;
        break;

    case EVENT_AppStopNotify:

        break;
    case EVENT_AppActiveNotify:
        if (pEvent->sParam1 == 0)
        {
            applicationDidEnterBackground();
            if (CCDirector::sharedDirector()->isPaused())
            {
               StopMainLoop();
            }
            CfgTurnOnBackLight();
            EnableKeyLock();
        }
        else if (pEvent->sParam1 > 0)
        {
            applicationWillEnterForeground();
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

    if (! bHandled)
    {
        bHandled = TApplication::EventHandler(pEvent);
    }
    return bHandled;
}

ccDeviceOrientation CCXApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
{
	return eOritation;
}

CGRect CCXApplication::statusBarFrame()
{
    CGRect rc;
    return rc;
}

void CCXApplication::StartMainLoop()
{
    if (m_bRunning)
    {
        m_bNeedStop = FALSE;
        return;
    }
    Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &m_tMsg);
    m_bRunning = TRUE;
}

void CCXApplication::StopMainLoop()
{
    m_bNeedStop = TRUE;
}

//////////////////////////////////////////////////////////////////////////
/// Implement static class member
//////////////////////////////////////////////////////////////////////////

CCXApplication * CCXApplication::sharedApplication()
{
    return (CCXApplication *)TApplication::GetCurrentApplication();
}

Int32 CCXApplication::_OnAppIdle(MESSAGE_t * pMsg, UInt32 uData)
{
    CCXApplication *    pThis = CCXApplication::sharedApplication();
    CCXEGLView *        pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pThis && pView && pThis->m_bRunning)
    {
        if (pThis->m_bNeedStop)
        {
            pThis->m_bNeedStop = FALSE;
            pThis->m_bRunning  = FALSE;
        }
        else
        {
            pView->UpdateWindow(0);
            Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &pThis->m_tMsg);
        }
    }
    return 1;
}

const char* CCXApplication::getAppDataPath()
{
    return m_AppDataPath;
}

void CCXApplication::setAnimationInterval(double interval)
{
	// tbd
}

}

