#ifndef __COCOS_3D_3DEXPORT_H__
#define __COCOS_3D_3DEXPORT_H__

#if defined(WIN32) && defined(_WINDOWS)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USE3DDLL)
        #define CC_3D_DLL     __declspec(dllexport)
    #else         /* use a DLL library */
        #define CC_3D_DLL     __declspec(dllimport)
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
    #define CC_3D_DLL
#endif

#endif // __COCOS_3D_3DEXPORT_H__
