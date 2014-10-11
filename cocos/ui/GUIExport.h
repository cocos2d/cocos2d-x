#ifndef __CCLIBGUI_H__
#define __CCLIBGUI_H__

#if defined(WIN32) && defined(_WINDOWS)
    #ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(CC_STATIC)
        #define CC_GUI_DLL
    #else
        #if defined(_USEGUIDLL)
            #define CC_GUI_DLL     __declspec(dllexport)
        #else
            #define CC_GUI_DLL     __declspec(dllimport)
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
#else
    #define CC_GUI_DLL
#endif

#endif /* __CCEXTENSIONEXPORT_H__*/