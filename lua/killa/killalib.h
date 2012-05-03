/* ========================================================================== */
/*   Killa standard libraries                                                 */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KILLALIB_H_
#define KILLALIB_H_

#include "killa.h"



KILLAMOD_API int (killaopen_base) (killa_State *L);

#define KILLA_COLIBNAME     "coroutine"
KILLAMOD_API int (killaopen_coroutine) (killa_State *L);

#define KILLA_TABLIBNAME    "table"
KILLAMOD_API int (killaopen_table) (killa_State *L);

#define KILLA_IOLIBNAME     "io"
KILLAMOD_API int (killaopen_io) (killa_State *L);

#define KILLA_OSLIBNAME     "os"
KILLAMOD_API int (killaopen_os) (killa_State *L);

#define KILLA_STRLIBNAME    "string"
KILLAMOD_API int (killaopen_string) (killa_State *L);

#define KILLA_BITLIBNAME    "bit32"
KILLAMOD_API int (killaopen_bit32) (killa_State *L);

#define KILLA_MATHLIBNAME   "math"
KILLAMOD_API int (killaopen_math) (killa_State *L);

#define KILLA_DBLIBNAME     "debug"
KILLAMOD_API int (killaopen_debug) (killa_State *L);

#define KILLA_LOADLIBNAME   "package"
KILLAMOD_API int (killaopen_package) (killa_State *L);


/* open all previous libraries */
KILLALIB_API void (killaL_openlibs) (killa_State *L); 



#if !defined(killa_assert)
#define killa_assert(x)	((void)0)
#endif


#endif
