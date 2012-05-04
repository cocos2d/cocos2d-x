/* ========================================================================== */
/*   Auxiliary functions to manipulate prototypes and closures                */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KFUNC_H_
#define KFUNC_H_


#include "kobject.h"


#define killa_sizeCclosure(n)	(killa_cast(int, sizeof(killa_CClosure)) + \
                        killa_cast(int, sizeof(killa_TValue)*((n)-1)))

#define killa_sizeLclosure(n)	(killa_cast(int, sizeof(killa_LClosure)) + \
                        killa_cast(int, sizeof(killa_TValue *)*((n)-1)))


KILLAI_FUNC killa_Proto *killaF_newproto (killa_State *L);
KILLAI_FUNC killa_Closure *killaF_newCclosure (killa_State *L, int nelems);
KILLAI_FUNC killa_Closure *killaF_newLclosure (killa_State *L, killa_Proto *p);
KILLAI_FUNC killa_UpVal *killaF_newupval (killa_State *L);
KILLAI_FUNC killa_UpVal *killaF_findupval (killa_State *L, killa_StkId level);
KILLAI_FUNC void killaF_close (killa_State *L, killa_StkId level);
KILLAI_FUNC void killaF_freeproto (killa_State *L, killa_Proto *f);
KILLAI_FUNC void killaF_freeclosure (killa_State *L, killa_Closure *c);
KILLAI_FUNC void killaF_freeupval (killa_State *L, killa_UpVal *uv);
KILLAI_FUNC const char *killaF_getlocalname (const killa_Proto *func, 
                                             int local_number, int pc);

#endif
