/* ANSI C namespace clean utility typedefs */

/* This file defines various typedefs needed by the system calls that support
   the C library.  Basically, they're just the POSIX versions with an '_'
   prepended.  This file lives in the `sys' directory so targets can provide
   their own if desired (or they can put target dependant conditionals here).
*/

#ifndef	_SYS__TYPES_H
#define _SYS__TYPES_H

#include <machine/_types.h>
#include <sys/lock.h>

#ifndef __off_t_defined
typedef long _off_t;
#endif

#if defined(__rtems__)
/* device numbers are 32-bit major and and 32-bit minor */
typedef unsigned long long __dev_t;
#else
#ifndef __dev_t_defined
typedef unsigned __dev_t; /* XXX Emscripten */
#endif
#endif

#ifndef __uid_t_defined
typedef unsigned __uid_t; /* XXX Emscripten */
#define __uid_t_defined 1
#endif
#ifndef __gid_t_defined
typedef unsigned __gid_t; /* XXX Emscripten */
#define __gid_t_defined 1
#endif
#ifndef __id_t_defined
typedef unsigned __id_t;  /* can hold a gid_t, pid_t, or uid_t XXX EMSCRIPTEN specific*/
#define __id_t_defined 1
#endif

#ifndef __off64_t_defined
__extension__ typedef unsigned _off64_t; /* XXX Emscripten */
#endif

/*
 * We need fpos_t for the following, but it doesn't have a leading "_",
 * so we use _fpos_t instead.
 */
#ifndef __fpos_t_defined
typedef long _fpos_t;		/* XXX must match off_t in <sys/types.h> */
				/* (and must be `long' for now) */
#endif

#ifdef __LARGE64_FILES
#ifndef __fpos64_t_defined
typedef _off64_t _fpos64_t;
#endif
#endif

#ifndef __ssize_t_defined
#if defined(__INT_MAX__) && __INT_MAX__ == 2147483647
typedef int _ssize_t;
#else
typedef long _ssize_t;
#endif
#endif

#define __need_wint_t
#include <stddef.h>

#ifndef __mbstate_t_defined
/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;		/* Value so far.  */
} _mbstate_t;
#endif

#ifndef __flock_t_defined
typedef _LOCK_RECURSIVE_T _flock_t;
#endif

#ifndef __iconv_t_defined
/* Iconv descriptor type */
typedef void *_iconv_t;
#endif

#endif	/* _SYS__TYPES_H */
