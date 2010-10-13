#ifndef __DENSHION_PLATFORM_H__
#define __DENSHION_PLATFORM_H__

#if defined(_TRANZDA_VM_) || defined(UNDER_UPHONE)
    #define _PLATFORM_UPHONE
#endif

#ifdef _PLATFORM_UPHONE
    #include "uPhone/SoundPlayer.h"
    #include "uPhone/FileUtils.h"
#endif

#endif
