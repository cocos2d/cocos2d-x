#include "CCXApplication_uphone.h"

#include "CCDirector.h"

namespace   cocos2d {

    static const Int32 CCX_ON_APPLICATION_IDLE = (EVENT_FirstUser + EVENT_LastUser) / 2;

    static Int32 _OnAppIdle(MESSAGE_t * pMsg, UInt32 uData)
    {
        CCDirector::getSharedDirector()->preMainLoop();
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
        }

        if (! bHandled)
        {
            bHandled = TApplication::EventHandler(pEvent);
        }
        return bHandled;
    }
}
