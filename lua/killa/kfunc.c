/* ========================================================================== */
/*   Auxiliary functions to manipulate prototypes and closures                */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stddef.h>

#define KILLA_CORE

#include "killa.h"

#include "kfunc.h"
#include "kgc.h"
#include "kmem.h"
#include "kobject.h"
#include "kstate.h"



killa_Closure *killaF_newCclosure (killa_State *L, int n) {
  killa_Closure *c = &killaC_newobj(L, KILLA_TFUNCTION, killa_sizeCclosure(n), NULL, 0)->cl;
  c->c.isC = 1;
  c->c.nupvalues = killa_cast_byte(n);
  return c;
}


killa_Closure *killaF_newLclosure (killa_State *L, killa_Proto *p) {
  int n = p->sizeupvalues;
  killa_Closure *c = &killaC_newobj(L, KILLA_TFUNCTION, killa_sizeLclosure(n), NULL, 0)->cl;
  c->l.isC = 0;
  c->l.p = p;
  c->l.nupvalues = killa_cast_byte(n);
  while (n--) c->l.upvals[n] = NULL;
  return c;
}


killa_UpVal *killaF_newupval (killa_State *L) {
  killa_UpVal *uv = &killaC_newobj(L, KILLA_TUPVAL, sizeof(killa_UpVal), NULL, 0)->uv;
  uv->v = &uv->u.value;
  killa_setnilvalue(uv->v);
  return uv;
}


killa_UpVal *killaF_findupval (killa_State *L, killa_StkId level) {
  killa_GlobalState *g = KILLA_G(L);
  killa_GCObject **pp = &L->openupval;
  killa_UpVal *p;
  killa_UpVal *uv;
  while (*pp != NULL && (p = killa_gco2uv(*pp))->v >= level) {
    killa_GCObject *o = killa_obj2gco(p);
    killa_assert(p->v != &p->u.value);
    if (p->v == level) {  /* found a corresponding upvalue? */
      if (killa_isdead(g, o))  /* is it dead? */
        killa_changewhite(o);  /* resurrect it */
      return p;
    }
    killa_resetoldbit(o);  /* may create a newer upval after this one */
    pp = &p->next;
  }
  /* not found: create a new one */
  uv = &killaC_newobj(L, KILLA_TUPVAL, sizeof(killa_UpVal), pp, 0)->uv;
  uv->v = level;  /* current value lives in the stack */
  uv->u.l.prev = &g->uvhead;  /* double link it in `uvhead' list */
  uv->u.l.next = g->uvhead.u.l.next;
  uv->u.l.next->u.l.prev = uv;
  g->uvhead.u.l.next = uv;
  killa_assert(uv->u.l.next->u.l.prev == uv && uv->u.l.prev->u.l.next == uv);
  return uv;
}


static void unlinkupval (killa_UpVal *uv) {
  killa_assert(uv->u.l.next->u.l.prev == uv && uv->u.l.prev->u.l.next == uv);
  uv->u.l.next->u.l.prev = uv->u.l.prev;  /* remove from `uvhead' list */
  uv->u.l.prev->u.l.next = uv->u.l.next;
}


void killaF_freeupval (killa_State *L, killa_UpVal *uv) {
  if (uv->v != &uv->u.value)  /* is it open? */
    unlinkupval(uv);  /* remove from open list */
  killaM_free(L, uv);  /* free upvalue */
}


void killaF_close (killa_State *L, killa_StkId level) {
  killa_UpVal *uv;
  killa_GlobalState *g = KILLA_G(L);
  while (L->openupval != NULL && (uv = killa_gco2uv(L->openupval))->v >= level) {
    killa_GCObject *o = killa_obj2gco(uv);
    killa_assert(!killa_isblack(o) && uv->v != &uv->u.value);
    L->openupval = uv->next;  /* remove from `open' list */
    if (killa_isdead(g, o))
      killaF_freeupval(L, uv);  /* free upvalue */
    else {
      unlinkupval(uv);  /* remove upvalue from 'uvhead' list */
      killa_setobj(L, &uv->u.value, uv->v);  /* move value to upvalue slot */
      uv->v = &uv->u.value;  /* now current value lives here */
      gch(o)->next = g->allgc;  /* link upvalue into 'allgc' list */
      g->allgc = o;
      killaC_checkupvalcolor(g, uv);
    }
  }
}


killa_Proto *killaF_newproto (killa_State *L) {
  killa_Proto *f = &killaC_newobj(L, KILLA_TPROTO, sizeof(killa_Proto), NULL, 0)->p;
  f->k = NULL;
  f->sizek = 0;
  f->p = NULL;
  f->sizep = 0;
  f->code = NULL;
  f->cache = NULL;
  f->sizecode = 0;
  f->lineinfo = NULL;
  f->sizelineinfo = 0;
  f->upvalues = NULL;
  f->sizeupvalues = 0;
  f->numparams = 0;
  f->is_vararg = 0;
  f->maxstacksize = 0;
  f->locvars = NULL;
  f->sizelocvars = 0;
  f->linedefined = 0;
  f->lastlinedefined = 0;
  f->source = NULL;
  return f;
}


void killaF_freeproto (killa_State *L, killa_Proto *f) {
  killaM_freearray(L, f->code, f->sizecode);
  killaM_freearray(L, f->p, f->sizep);
  killaM_freearray(L, f->k, f->sizek);
  killaM_freearray(L, f->lineinfo, f->sizelineinfo);
  killaM_freearray(L, f->locvars, f->sizelocvars);
  killaM_freearray(L, f->upvalues, f->sizeupvalues);
  killaM_free(L, f);
}


void killaF_freeclosure (killa_State *L, killa_Closure *c) {
  int size = (c->c.isC) ? killa_sizeCclosure(c->c.nupvalues) :
                          killa_sizeLclosure(c->l.nupvalues);
  killaM_freemem(L, c, size);
}


/*
** Look for n-th local variable at line `line' in function `func'.
** Returns NULL if not found.
*/
const char *killaF_getlocalname (const killa_Proto *f, int local_number, int pc) {
  int i;
  for (i = 0; i<f->sizelocvars && f->locvars[i].startpc <= pc; i++) {
    if (pc < f->locvars[i].endpc) {  /* is variable active? */
      local_number--;
      if (local_number == 0)
        return killa_getstr(f->locvars[i].varname);
    }
  }
  return NULL;  /* not found */
}

