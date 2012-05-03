/* ========================================================================== */
/*   Stack and Call structure of Killa                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KDO_H_
#define KDO_H_


#include "kobject.h"
#include "kstate.h"
#include "kzio.h"


#define killaD_checkstack(L,n)  if (L->stack_last - L->top <= (n)) \
                    killaD_growstack(L, n); else killa_condmovestack(L);


#define killa_incr_top(L)   {L->top++; killaD_checkstack(L,0);}

#define killa_savestack(L,p)    ((char *)(p) - (char *)L->stack)
#define killa_restorestack(L,n) ((killa_TValue *)((char *)L->stack + (n)))


/* type of protected functions, to be ran by `runprotected' */
typedef void (*Pfunc) (killa_State *L, void *ud);

KILLAI_FUNC int  killaD_protectedparser (killa_State *L, killa_ZIO *z, const char *name,
                                         const char *mode);
KILLAI_FUNC void killaD_hook (killa_State *L, int event, int line);
KILLAI_FUNC int  killaD_precall (killa_State *L, killa_StkId func, int nresults);
KILLAI_FUNC void killaD_call (killa_State *L, killa_StkId func, int nResults,
                              int allowyield);
KILLAI_FUNC int  killaD_pcall (killa_State *L, Pfunc func, void *u,
                               ptrdiff_t oldtop, ptrdiff_t ef);
KILLAI_FUNC int  killaD_poscall (killa_State *L, killa_StkId firstResult);
KILLAI_FUNC void killaD_reallocstack (killa_State *L, int newsize);
KILLAI_FUNC void killaD_growstack (killa_State *L, int n);
KILLAI_FUNC void killaD_shrinkstack (killa_State *L);

KILLAI_FUNC killa_noret killaD_throw (killa_State *L, int errcode);
KILLAI_FUNC int  killaD_rawrunprotected (killa_State *L, Pfunc f, void *ud);

#endif

