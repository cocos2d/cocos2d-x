#include "CCXApplication_uphone.h"

#include "CCDirector.h"

// #include "CCXGLExtFunc.h"
#include <GLES/glext.h>

namespace   cocos2d {

    static const Int32 CCX_ON_APPLICATION_IDLE = (EVENT_FirstUser + EVENT_LastUser) / 2;

    static Int32 _OnAppIdle(MESSAGE_t * pMsg, UInt32 uData)
    {
        //CCDirector::getSharedDirector()->preMainLoop();
        CCXEGLView * pView = CCDirector::getSharedDirector()->getOpenGLView();
        if (pView)
        {
            pView->UpdateWindow(0);
        }
        int nRtn = Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, (MESSAGE_t *)uData);
        return 1;
    }

    CCXApplication::CCXApplication()
    {
        memset(&m_tMsg, 0, sizeof(m_tMsg));
        SS_GetCurrentGTID(&m_tMsg.gtid);
        m_tMsg.type = CCX_ON_APPLICATION_IDLE;

        Sys_RegisterMessageCallBack(CCX_ON_APPLICATION_IDLE, _OnAppIdle, (UInt32)&m_tMsg);
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
            if (! initCocos2d())
            {
                SendStopEvent();
            }
            bHandled = Sys_PostMessage2(MESSAGE_PRIOR_LOWEST, &m_tMsg);
            bHandled = TRUE;
            break;

        case EVENT_AppStopNotify:

            break;
        case EVENT_AppActiveNotify:
            if (pEvent->sParam1 == 0)
            {
                applicationDidEnterBackground();
            }
            else if (pEvent->sParam1 > 0)
            {
                applicationWillEnterForeground();
            }
            break;
        }

        if (! bHandled)
        {
            bHandled = TApplication::EventHandler(pEvent);
        }
        return bHandled;
    }

    void CCXApplication::setDeviceOrientation(int nOritation)
    {
        TWindow * pWnd = TApplication::GetCurrentWindow();
        if (! pWnd)
        {
            return;
        }
        switch (nOritation)
        {
        /// Device oriented vertically, home button on the bottom
        case kCCDeviceOrientationPortrait:
            pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_NORMAL);
            break;
        /// Device oriented vertically, home button on the top
        case kCCDeviceOrientationPortraitUpsideDown:
            pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_UD);
            break;

        /// Device oriented horizontally, home button on the right
        case kCCDeviceOrientationLandscapeLeft:
            pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_CW);
            break;
        /// Device oriented horizontally, home button on the left
        case kCCDeviceOrientationLandscapeRight:
            pWnd->RotateWindow(WM_WINDOW_ROTATE_MODE_CCW);
            break;
        }
    }

    CGRect CCXApplication::statusBarFrame()
    {
        CGRect rc;
        return rc;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Implement static class member
    //////////////////////////////////////////////////////////////////////////
    CCXApplication * CCXApplication::getSharedApplication()
    {
        return (CCXApplication *)TApplication::GetCurrentApplication();
    }

}
