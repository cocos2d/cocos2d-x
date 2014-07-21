#ifndef __CCCOCOSSTUDIO_H__
#define __CCCOCOSSTUDIO_H__

#if defined(WIN32) && defined(_WINDOWS)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USRSTUDIODLL)
        #define CC_STUDIO_DLL     __declspec(dllexport)
    #else         /* use a DLL library */
        #define CC_STUDIO_DLL     __declspec(dllimport)
    #endif


    /* Define NULL pointer value */
    #ifndef NULL
        #ifdef __cplusplus
            #define NULL    0
        #else
            #define NULL    ((void *)0)
        #endif
    #endif
#else
    #define CC_STUDIO_DLL
#endif

#endif /* __CCEXTENSIONEXPORT_H__*/