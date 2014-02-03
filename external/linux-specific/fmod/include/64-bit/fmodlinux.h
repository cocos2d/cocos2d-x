/* =========================================================================================== */
/* FMOD Linux Specific header file. Copyright (c), Firelight Technologies Pty, Ltd. 2005-2011. */
/* =========================================================================================== */

#ifndef _FMODLINUX_H
#define _FMODLINUX_H

#include "fmod.h"


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Use this structure with System::init to set the information required for linux
    initialisation.

    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]

    [PLATFORMS]
    Linux, Linux64

    [SEE_ALSO]
    System::init
]
*/
typedef struct FMOD_LINUX_EXTRADRIVERDATA
{
    const char  *output_driver_arguments;    /* ALSA Only - Arguments to apply to the selected output driver */
    const char  *record_driver_arguments;    /* ALSA Only - Arguments to apply to the selected input (record) driver */
} FMOD_LINUX_EXTRADRIVERDATA;

#endif

