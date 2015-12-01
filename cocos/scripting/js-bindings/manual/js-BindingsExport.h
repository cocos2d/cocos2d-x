#pragma once

#if (defined(WIN32) && defined(_WINDOWS)) || defined(WINRT) || defined(WP8)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USRJSSTATIC)
        #define CC_JS_DLL
    #else
        #if defined(_USRJSDLL)
            #define CC_JS_DLL     __declspec(dllexport)
        #else         /* use a DLL library */
            #define CC_JS_DLL     __declspec(dllimport)
        #endif
    #endif

    /* Define NULL pointer value */
    #ifndef NULL
        #ifdef __cplusplus
            #define nullptr    0
        #else
            #define NULL    ((void *)0)
        #endif
    #endif
#elif defined(_SHARED_)
    #define CC_JS_DLL     __attribute__((visibility("default")))
#else
    #define CC_JS_DLL
#endif
