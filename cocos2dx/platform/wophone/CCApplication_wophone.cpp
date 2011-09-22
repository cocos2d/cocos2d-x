// #define COCOS2D_DEBUG   1

#include "CCApplication_wophone.h"

#include "ssBackLightControl.h"
//#include "ssKeyLockControl.h"

#include "CCScheduler.h"

NS_CC_BEGIN;

static const Int32 CC_ON_APPLICATION_IDLE = (EVENT_FirstUser + EVENT_LastUser) / 2;

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

CCApplication::CCApplication()
: m_bRunning(false)
, m_bNeedStop(false)
, m_bInBackground(false)
, m_bEnterBackgroundCalled(false)
{
    memset(&m_tMsg, 0, sizeof(m_tMsg));
    SS_GetCurrentGTID(&m_tMsg.gtid);
    m_tMsg.type = CC_ON_APPLICATION_IDLE;

    Sys_RegisterMessageCallBack(CC_ON_APPLICATION_IDLE, CCApplication::_OnAppIdle, (UInt32)this);

    memset(m_AppDataPath, 0, sizeof(char) * EOS_FILE_MAX_PATH);

    do 
    {
        TUChar AppID[EOS_FILE_MAX_PATH] = {0};
        UInt32 nCmdType = 0;
        Int32  nRet = SS_AppRequest_GetAppName(AppID, &nCmdType);
        CC_BREAK_IF(nRet < 0);

#ifndef _TRANZDA_VM_
        char *pszDriver = "";
#else
        char *pszDriver = "D:/Work7";
#endif

        TUChar AppPath[EOS_FILE_MAX_PATH] = {0};
        char   DataPath[EOS_FILE_MAX_PATH] = {0};

        // get the const data path of the application and record it
        SS_GetApplicationPath(AppID, SS_APP_PATH_TYPE_CONST, AppPath);
        TUString::StrUnicodeToStrUtf8((Char*) DataPath, AppPath);
        strcpy(m_AppDataPath, pszDriver);
        strcat(m_AppDataPath, DataPath);

        // get the writable data path of the application and record it
        SS_GetApplicationPath(AppID, SS_APP_PATH_TYPE_DATA, AppPath);
        TUString::StrUnicodeToStrUtf8((Char*) DataPath, AppPath);
        strcpy(m_AppWritablePath, pszDriver);
        strcat(m_AppWritablePath, DataPath);
    } while (0);

    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    Sys_RegisterMessageCallBack(CC_ON_APPLICATION_IDLE, NULL, NULL);

    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

Boolean  CCApplication::EventHandler(EventType*  pEvent)
{
    Boolean     bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_AppLoad:
        if (! initInstance() || ! applicationDidFinishLaunching())
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
            CCLOG("EVENT_AppActiveNotify false");
            if (!m_bInBackground)
            {
                if (! m_bEnterBackgroundCalled)
                {
                    applicationDidEnterBackground();
                    m_bEnterBackgroundCalled = true;
                }
                m_bInBackground = true;
            }

            if (CCDirector::sharedDirector()->isPaused())
            {
                StopMainLoop();
            }

            // restore back light open mode
            if (CfgGetBackLightStatus())
            {
                CfgTurnOnBackLightEx(SYS_BACK_LIGHT_MODE_TIME_LONG);
                CCLOG("AppActiveNotify::TurnOnBackLight:MODE_TIME_LONG");
            }
        }
        else if (pEvent->sParam1 > 0)
        {
            CCLOG("EVENT_AppActiveNotify true");
            if (m_bInBackground)
            {
                if (m_bEnterBackgroundCalled)
                {
                    applicationWillEnterForeground();
                    m_bEnterBackgroundCalled = false;
                }
                m_bInBackground = false;
            }

            StartMainLoop();

            // modify back light open mode
            if (CfgGetBackLightStatus())
            {
                // Why doesn't use CfgTurnOnBackLightEx(SYS_BACK_LIGHT_MODE_TIME_ALWAYS)?
                // MODE_TIME_ALWAYS cause phone can't sleep when power button pressed.
                CfgTurnOnBackLightDelay(0x7fffffff);
                CCLOG("AppActiveNotify::TurnOnBackLight:0x7fffffff");
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

void CCApplication::setAnimationInterval(double interval)
{
#ifdef _TRANZDA_VM_
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    s_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
#else
    s_nAnimationInterval = (long long)(interval * 1000 * 1000);
#endif
}

CCApplication::Orientation CCApplication::setOrientation(CCApplication::Orientation orientation)
{
    return sm_OrientationTable[sm_uDesignOrientation][orientation];
}

void CCApplication::statusBarFrame(CCRect * rect)
{
}

const char* CCApplication::getAppDataPath()
{
    return m_AppDataPath;
}

const char* CCApplication::getAppWritablePath()
{
    return m_AppWritablePath;
}

void CCApplication::switchNotify(int nTurnOn)
{
    bool bInBack = isInBackground();

    // set the auto close screen and auto key lock status

    do 
    {
        // if the app have be in background,don't handle this message
        CC_BREAK_IF(bInBack);

        if (! nTurnOn)  // turn off screen
        {
            if (! m_bEnterBackgroundCalled)
            {
                applicationDidEnterBackground();
                m_bEnterBackgroundCalled = true;
            }
            StopMainLoop();
        }
        else
        {
            // modify back light open mode
            // Why doesn't use CfgTurnOnBackLightEx(SYS_BACK_LIGHT_MODE_TIME_ALWAYS)?
            // MODE_TIME_ALWAYS cause phone can't sleep when power button pressed.
            CfgTurnOnBackLightDelay(0x7fffffff);
            CCLOG("AppActiveNotify::TurnOnBackLight:0x7fffffff");

            if (m_bEnterBackgroundCalled)
            {
                applicationWillEnterForeground();
                m_bEnterBackgroundCalled = false;
            }
            StartMainLoop();
        }
    } while (0);
}

bool CCApplication::isInBackground()
{
    return m_bInBackground;
}

void CCApplication::StartMainLoop()
{
    m_bNeedStop = FALSE;
    if (m_bRunning)
    {
        return;
    }
    CCLOG("Post StartMainLoop");
    Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &m_tMsg);
}

void CCApplication::StopMainLoop()
{
    m_bNeedStop = TRUE;
}

Int32 CCApplication::_OnAppIdle(MESSAGE_t * pMsg, UInt32 uData)
{
    CCApplication& rThis = (CCApplication&) CCApplication::sharedApplication();
    CCEGLView *     pView = CCDirector::sharedDirector()->getOpenGLView();
    if (pView)
    {
        if (rThis.m_bNeedStop)
        {
            CCLOG("_OnAppIdle: Stop");
            rThis.m_bNeedStop = FALSE;
            rThis.m_bRunning  = FALSE;
        }
        else
        {
            rThis.m_bRunning  = TRUE;
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
                Sys_SchedYield();
            }
            Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &rThis.m_tMsg);
        }
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////

// shared application
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    return kLanguageChinese;
}

// rotate device support
static const CCApplication::Orientation s_OrientationModeNormal[] = 
{
    CCApplication::kOrientationPortrait,
    CCApplication::kOrientationPortraitUpsideDown,
    CCApplication::kOrientationLandscapeLeft,
    CCApplication::kOrientationLandscapeRight,
};

static const CCApplication::Orientation s_OrientationModeCW[] = 
{
    CCApplication::kOrientationLandscapeLeft,
    CCApplication::kOrientationLandscapeRight,
    CCApplication::kOrientationPortraitUpsideDown,
    CCApplication::kOrientationPortrait,
};

static const CCApplication::Orientation s_OrientationModeUD[] = 
{
    CCApplication::kOrientationPortraitUpsideDown,
    CCApplication::kOrientationPortrait,
    CCApplication::kOrientationLandscapeRight,
    CCApplication::kOrientationLandscapeLeft,
};

static const CCApplication::Orientation s_OrientationModeCCW[] = 
{
    CCApplication::kOrientationLandscapeRight,
    CCApplication::kOrientationLandscapeLeft,
    CCApplication::kOrientationPortrait,
    CCApplication::kOrientationPortraitUpsideDown,
};

const CCApplication::Orientation * const CCApplication::sm_OrientationTable[] = 
{
    s_OrientationModeNormal,
    s_OrientationModeCW,
    s_OrientationModeUD,
    s_OrientationModeCCW,
};

UInt32 CCApplication::sm_uDesignOrientation = WM_WINDOW_ROTATE_MODE_NORMAL;

void  CCApplication::setDesignOrientation(UInt32 uOrientation)
{
    sm_uDesignOrientation = uOrientation;
}

UInt32 CCApplication::getDesignOrientation()
{
    return sm_uDesignOrientation;
}

NS_CC_END;
