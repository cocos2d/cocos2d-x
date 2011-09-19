/* ============================================================================================ */
/* FMOD Ex - Main C/C++ Network event system header file.                                       */
/* Copyright (c), Firelight Technologies Pty, Ltd. 2004-2011.                                   */
/*                                                                                              */
/* This header is the base header for all other FMOD NetEventSystem headers. If you are         */
/* programming in C use this exclusively, or if you are programming C++ use this in             */
/* conjunction with FMOD_EVENT_NET.HPP                                                          */
/* ============================================================================================ */

#ifndef __FMOD_EVENT_NET_H__
#define __FMOD_EVENT_NET_H__

#ifndef __FMOD_EVENT_H__
#include "fmod_event.h"
#endif

/*
    FMOD NetEventSystem version number.  Check this against NetEventSystem_GetVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/
#define FMOD_EVENT_NET_VERSION 0x00043601

/*
    Default port that the target (game) will listen on
*/
#define FMOD_EVENT_NET_PORT    17997

#ifdef __cplusplus
extern "C" 
{
#endif

FMOD_RESULT F_API FMOD_NetEventSystem_Init       (FMOD_EVENTSYSTEM *eventsystem, unsigned short port);
FMOD_RESULT F_API FMOD_NetEventSystem_Update     ();
FMOD_RESULT F_API FMOD_NetEventSystem_Shutdown   ();
FMOD_RESULT F_API FMOD_NetEventSystem_GetVersion (unsigned int *version);

#ifdef __cplusplus
}
#endif

#endif
