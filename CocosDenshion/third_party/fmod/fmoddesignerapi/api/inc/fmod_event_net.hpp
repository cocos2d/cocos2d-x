/* ============================================================================================ */
/* FMOD Ex - Main C/C++ Network event system header file.                                       */
/* Copyright (c), Firelight Technologies Pty, Ltd. 2004-2011.                                   */
/*                                                                                              */
/* Use this header to enable network tweaking and auditioning in realtime from FMOD Designer.   */
/* If you are programming in C use FMOD_EVENT_NET.H                                             */
/* ============================================================================================ */

#ifndef __FMOD_EVENT_NET_HPP__
#define __FMOD_EVENT_NET_HPP__

#ifndef __FMOD_EVENT_NET_H__
#include "fmod_event_net.h"
#endif

namespace FMOD
{
    class EventSystem;

    FMOD_RESULT F_API NetEventSystem_Init       (EventSystem *eventsystem, unsigned short port = FMOD_EVENT_NET_PORT);
    FMOD_RESULT F_API NetEventSystem_Update     ();
    FMOD_RESULT F_API NetEventSystem_Shutdown   ();
    FMOD_RESULT F_API NetEventSystem_GetVersion (unsigned int *version);
}

#endif
