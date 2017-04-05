#pragma once

#if (defined(WIN32) && defined(_WINDOWS)) || defined(WINRT) || defined(WP8)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USRLIBSIMSTATIC)
        #define CC_LIBSIM_DLL
    #else
        #if defined(_USRLIBSIMDLL)
            #define CC_LIBSIM_DLL     __declspec(dllexport)
        #else         /* use a DLL library */
            #define CC_LIBSIM_DLL     __declspec(dllimport)
        #endif
    #endif

    /* Define NULL pointer value */
    #ifndef NULL
        #ifdef __cplusplus
            #define NULL    0
        #else
            #define NULL    ((void *)0)
        #endif
    #endif
#elif defined(_SHARED_)
    #define CC_LIBSIM_DLL     __attribute__((visibility("default")))
#else
    #define CC_LIBSIM_DLL
#endif
