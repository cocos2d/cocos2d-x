#ifndef __eglplatform_h_
#define __eglplatform_h_

/*
** Copyright (c) 2007-2009 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

// Define MESA_EGL_NO_X11_HEADERS for Emscripten
#define MESA_EGL_NO_X11_HEADERS

/* Platform-specific types and definitions for egl.h
 * $Revision: 9724 $ on $Date: 2009-12-02 02:05:33 -0800 (Wed, 02 Dec 2009) $
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by sending them to the public Khronos Bugzilla (http://khronos.org/bugzilla)
 * by filing a bug against product "EGL" component "Registry".
 */

#include <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 */

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

typedef HDC     EGLNativeDisplayType;
typedef HBITMAP EGLNativePixmapType;
typedef HWND    EGLNativeWindowType;

#elif defined(EMSCRIPTEN)

typedef int EGLNativeDisplayType;
typedef int EGLNativeWindowType;
typedef int EGLNativePixmapType;

#elif defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

typedef int   EGLNativeDisplayType;
typedef void *EGLNativeWindowType;
typedef void *EGLNativePixmapType;

#elif defined(WL_EGL_PLATFORM)

typedef struct wl_display     *EGLNativeDisplayType;
typedef struct wl_egl_pixmap  *EGLNativePixmapType;
typedef struct wl_egl_window  *EGLNativeWindowType;

#elif defined(__GBM__)

typedef struct gbm_device  *EGLNativeDisplayType;
typedef struct gbm_bo      *EGLNativePixmapType;
typedef void               *EGLNativeWindowType;

#elif defined(__unix__) || defined(__unix)

#ifdef MESA_EGL_NO_X11_HEADERS

typedef void            *EGLNativeDisplayType;
typedef khronos_uint32_t EGLNativePixmapType;
typedef khronos_uint32_t EGLNativeWindowType;

#else

/* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

#endif /* MESA_EGL_NO_X11_HEADERS */

#else
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
typedef khronos_int32_t EGLint;

#endif /* __eglplatform_h */
