/* ========================================================================== */
/*   Killa virtual machine                                                    */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KVM_H_
#define KVM_H_


#include "kdo.h"
#include "kobject.h"
#include "ktm.h"


#define killa_vmtostring(L,o)   (killa_ttisstring(o) || (killaV_tostring(L, o)))

#define killa_vmtonumber(o,n)   (killa_ttisnumber(o) || (((o) = killaV_tonumber(o,n)) != NULL))

#define killa_equalobj(L,o1,o2) (killa_ttisequal(o1, o2) && killaV_equalobj_(L, o1, o2))

#define killaV_rawequalobj(t1,t2)  \
        (killa_ttisequal(t1,t2) && killaV_equalobj_(NULL,t1,t2))


/* not to called directly */
KILLAI_FUNC int killaV_equalobj_ (killa_State *L, const killa_TValue *t1, const killa_TValue *t2);


KILLAI_FUNC int  killaV_lessthan (killa_State *L, const killa_TValue *l, const killa_TValue *r);
KILLAI_FUNC int  killaV_lessequal (killa_State *L, const killa_TValue *l, const killa_TValue *r);
KILLAI_FUNC const killa_TValue *killaV_tonumber (const killa_TValue *obj, killa_TValue *n);
KILLAI_FUNC int  killaV_tostring (killa_State *L, killa_StkId obj);
KILLAI_FUNC void killaV_gettable (killa_State *L, const killa_TValue *t, killa_TValue *key,
                                  killa_StkId val);
KILLAI_FUNC void killaV_settable (killa_State *L, const killa_TValue *t, killa_TValue *key,
                                  killa_StkId val);
KILLAI_FUNC void killaV_finishOp (killa_State *L);
KILLAI_FUNC void killaV_execute (killa_State *L);
KILLAI_FUNC void killaV_concat (killa_State *L, int total);
KILLAI_FUNC void killaV_arith (killa_State *L, killa_StkId ra, const killa_TValue *rb,
                               const killa_TValue *rc, KILLA_TMS op);
KILLAI_FUNC void killaV_objlen (killa_State *L, killa_StkId ra, const killa_TValue *rb);

#endif
