/* ========================================================================== */
/*   'ctype' functions for Killa                                              */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KCTYPE_H_
#define KCTYPE_H_

#include "killa.h"


/*
** WARNING: the functions defined here do not necessarily correspond
** to the similar functions in the standard C ctype.h. They are
** optimized for the specific needs of Killa
*/

#if !defined(KILLA_USE_CTYPE)

#if 'A' == 65 && '0' == 48
/* ASCII case: can use its own tables; faster and fixed */
#define KILLA_USE_CTYPE	0
#else
/* must use standard C ctype */
#define KILLA_USE_CTYPE	1
#endif

#endif


#if !KILLA_USE_CTYPE	/* { */

#include <limits.h>

#include "klimits.h"


#define KILLA_ALPHABIT	0
#define KILLA_DIGITBIT	1
#define KILLA_PRINTBIT	2
#define KILLA_SPACEBIT	3
#define KILLA_XDIGITBIT	4


#define KILLA_MASK(B)		(1 << (B))


/*
** add 1 to char to allow index -1 (KILLA_EOZ)
*/
#define killa_testprop(c,p)	(killai_ctype_[(c)+1] & (p))

/*
** 'lalpha' (Killa alphabetic) and 'lalnum' (Killa alphanumeric) both include '_'
*/
#define killa_islalpha(c)	killa_testprop(c, KILLA_MASK(KILLA_ALPHABIT))
#define killa_islalnum(c)	killa_testprop(c, (KILLA_MASK(KILLA_ALPHABIT) | KILLA_MASK(KILLA_DIGITBIT)))
#define killa_isdigit(c)	killa_testprop(c, KILLA_MASK(KILLA_DIGITBIT))
#define killa_isspace(c)	killa_testprop(c, KILLA_MASK(KILLA_SPACEBIT))
#define killa_isprint(c)	killa_testprop(c, KILLA_MASK(KILLA_PRINTBIT))
#define killa_isxdigit(c)	killa_testprop(c, KILLA_MASK(KILLA_XDIGITBIT))

/*
** this 'killa_tolower' only works for alphabetic characters
*/
#define killa_tolower(c)	((c) | ('A' ^ 'a'))


/* two more entries for 0 and -1 (KILLA_EOZ) */
KILLAI_DDEC const killa_ubyte killai_ctype_[UCHAR_MAX + 2];


#else			/* }{ */

/*
** use standard C ctypes
*/

#include <ctype.h>


#define killa_islalpha(c)	(isalpha(c) || (c) == '_')
#define killa_islalnum(c)	(isalnum(c) || (c) == '_')
#define killa_isdigit(c)	(isdigit(c))
#define killa_isspace(c)	(isspace(c))
#define killa_isprint(c)	(isprint(c))
#define killa_isxdigit(c)	(isxdigit(c))

#define killa_tolower(c)	(tolower(c))

#endif			/* } */

#endif

