#ifndef __CCEXTENSIONEXPORT_H__
#define __CCEXTENSIONEXPORT_H__

#if defined(WIN32) && defined(_WINDOWS)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USREXDLL)
        #define CC_EX_DLL     __declspec(dllexport)
    #else         /* use a DLL library */
        #define CC_EX_DLL     __declspec(dllimport)
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
    #define CC_EX_DLL
#endif

#endif /* __CCEXTENSIONEXPORT_H__*/