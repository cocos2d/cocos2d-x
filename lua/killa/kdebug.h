/* ========================================================================== */
/*   Auxiliary functions from Debug Interface module                          */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KDEBUG_H_
#define KDEBUG_H_


#include "kstate.h"


#define killa_pcRel(pc, p)	(killa_cast(int, (pc) - (p)->code) - 1)

#define killa_getfuncline(f,pc)	(((f)->lineinfo) ? (f)->lineinfo[pc] : 0)

#define killa_resethookcount(L)	(L->hookcount = L->basehookcount)

/* Active Killa function (given call info) */
#define killa_ci_func(ci)		(killa_clLvalue((ci)->func))


KILLAI_FUNC killa_noret killaG_typeerror (killa_State *L, const killa_TValue *o,
                                      const char *opname);
KILLAI_FUNC killa_noret killaG_concaterror (killa_State *L, killa_StkId p1, killa_StkId p2);
KILLAI_FUNC killa_noret killaG_aritherror (killa_State *L, const killa_TValue *p1,
                                       const killa_TValue *p2);
KILLAI_FUNC killa_noret killaG_ordererror (killa_State *L, const killa_TValue *p1,
                                       const killa_TValue *p2);
KILLAI_FUNC killa_noret killaG_runerror (killa_State *L, const char *fmt, ...);
KILLAI_FUNC killa_noret killaG_errormsg (killa_State *L);

#endif
