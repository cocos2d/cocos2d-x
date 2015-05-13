/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL_platform.h
 *  
 *  Try to get a standard set of platform defines.
 */

#ifndef _SDL_platform_h
#define _SDL_platform_h

#if defined(_AIX)
#undef __AIX__
#define __AIX__		1
#endif
#if defined(__BEOS__)
#undef __BEOS__
#define __BEOS__	1
#endif
#if defined(__HAIKU__)
#undef __HAIKU__
#define __HAIKU__	1
#endif
#if defined(bsdi) || defined(__bsdi) || defined(__bsdi__)
#undef __BSDI__
#define __BSDI__	1
#endif
#if defined(_arch_dreamcast)
#undef __DREAMCAST__
#define __DREAMCAST__	1
#endif
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
#undef __FREEBSD__
#define __FREEBSD__	1
#endif
#if defined(hpux) || defined(__hpux) || defined(__hpux__)
#undef __HPUX__
#define __HPUX__	1
#endif
#if defined(sgi) || defined(__sgi) || defined(__sgi__) || defined(_SGI_SOURCE)
#undef __IRIX__
#define __IRIX__	1
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
#undef __LINUX__
#define __LINUX__	1
#endif
#if defined(ANDROID)
#undef __ANDROID__
#undef __LINUX__ /*do we need to do this?*/
#define __ANDROID__ 1
#endif

#if defined(__APPLE__)
/* lets us know what version of Mac OS X we're compiling on */
#include "AvailabilityMacros.h"
#include "TargetConditionals.h"
#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif
#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif
#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif
#if TARGET_OS_IPHONE
/* if compiling for iPhone */
#undef __IPHONEOS__
#define __IPHONEOS__ 1
#undef __MACOSX__
#else
/* if not compiling for iPhone */
#undef __MACOSX__
#define __MACOSX__	1
#endif /* TARGET_OS_IPHONE */
#endif /* defined(__APPLE__) */

#if defined(__NetBSD__)
#undef __NETBSD__
#define __NETBSD__	1
#endif
#if defined(__OpenBSD__)
#undef __OPENBSD__
#define __OPENBSD__	1
#endif
#if defined(__OS2__)
#undef __OS2__
#define __OS2__		1
#endif
#if defined(osf) || defined(__osf) || defined(__osf__) || defined(_OSF_SOURCE)
#undef __OSF__
#define __OSF__		1
#endif
#if defined(__QNXNTO__)
#undef __QNXNTO__
#define __QNXNTO__	1
#endif
#if defined(riscos) || defined(__riscos) || defined(__riscos__)
#undef __RISCOS__
#define __RISCOS__	1
#endif
#if defined(__SVR4)
#undef __SOLARIS__
#define __SOLARIS__	1
#endif
#if defined(WIN32) || defined(_WIN32)
#undef __WIN32__
#define __WIN32__	1
#endif

#if defined(__NDS__)
#undef __NINTENDODS__
#define __NINTENDODS__	1
#endif


#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

/**
 *  \brief Gets the name of the platform.
 */
extern DECLSPEC const char * SDLCALL SDL_GetPlatform (void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif /* _SDL_platform_h */

/* vi: set ts=4 sw=4 expandtab: */
