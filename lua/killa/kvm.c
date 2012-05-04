/* ========================================================================== */
/*   Killa virtual machine                                                    */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KVM_C_
#define KILLA_CORE

#include "killa.h"

#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "kgc.h"
#include "kobject.h"
#include "kopcodes.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"
#include "kvm.h"



/* limit for table tag-method chains (to avoid loops) */
#define MAXTAGLOOP	100


const killa_TValue *killaV_tonumber (const killa_TValue *obj, killa_TValue *n) {
  killa_Number num;
  if (killa_ttisnumber(obj)) return obj;
  if (killa_ttisstring(obj) && killaO_str2d(killa_svalue(obj), killa_tsvalue(obj)->len, &num)) {
    killa_setnvalue(n, num);
    return n;
  }
  else
    return NULL;
}


int killaV_tostring (killa_State *L, killa_StkId obj) {
  if (!killa_ttisnumber(obj))
    return 0;
  else {
    char s[KILLAI_MAXNUMBER2STR];
    killa_Number n = killa_nvalue(obj);
    int l = killa_number2str(s, n);
    killa_setsvalue2s(L, obj, killaS_newlstr(L, s, l));
    return 1;
  }
}


static void traceexec (killa_State *L) {
  killa_CallInfo *ci = L->ci;
  killa_ubyte mask = L->hookmask;
  if ((mask & KILLA_MASKCOUNT) && L->hookcount == 0) {
    killa_resethookcount(L);
    killaD_hook(L, KILLA_HOOKCOUNT, -1);
  }
  if (mask & KILLA_MASKLINE) {
    killa_Proto *p = killa_ci_func(ci)->p;
    int npc = killa_pcRel(ci->u.l.savedpc, p);
    int newline = killa_getfuncline(p, npc);
    if (npc == 0 ||  /* call linehook when enter a new function, */
        ci->u.l.savedpc <= L->oldpc ||  /* when jump back (loop), or when */
        newline != killa_getfuncline(p, killa_pcRel(L->oldpc, p)))  /* enter a new line */
      killaD_hook(L, KILLA_HOOKLINE, newline);
  }
  L->oldpc = ci->u.l.savedpc;
  if (L->status == KILLA_YIELD) {  /* did hook yield? */
    ci->u.l.savedpc--;  /* undo increment (resume will increment it again) */
    killaD_throw(L, KILLA_YIELD);
  }
}


static void callTM (killa_State *L, const killa_TValue *f, const killa_TValue *p1,
                    const killa_TValue *p2, killa_TValue *p3, int hasres) {
  ptrdiff_t result = killa_savestack(L, p3);
  killa_setobj2s(L, L->top++, f);  /* push function */
  killa_setobj2s(L, L->top++, p1);  /* 1st argument */
  killa_setobj2s(L, L->top++, p2);  /* 2nd argument */
  if (!hasres)  /* no result? 'p3' is third argument */
    killa_setobj2s(L, L->top++, p3);  /* 3rd argument */
  killaD_checkstack(L, 0);
  /* metamethod may yield only when called from Killa code */
  killaD_call(L, L->top - (4 - hasres), hasres, killa_isKilla(L->ci));
  if (hasres) {  /* if has result, move it to its place */
    p3 = killa_restorestack(L, result);
    killa_setobjs2s(L, p3, --L->top);
  }
}


void killaV_gettable (killa_State *L, const killa_TValue *t, killa_TValue *key, killa_StkId val) {
  int loop;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const killa_TValue *tm;
    if (killa_ttistable(t)) {  /* `t' is a table? */
      killa_Table *h = killa_hvalue(t);
      const killa_TValue *res = killaH_get(h, key); /* do a primitive get */
      if (!killa_ttisnil(res) ||  /* result is not nil? */
          (tm = killa_fasttm(L, h->metatable, TM_INDEX)) == NULL) { /* or no TM? */
        killa_setobj2s(L, val, res);
        return;
      }
      /* else will try the tag method */
    }
    else if (killa_ttisnil(tm = killaT_gettmbyobj(L, t, TM_INDEX)))
      killaG_typeerror(L, t, "index");
    if (killa_ttisfunction(tm)) {
      callTM(L, tm, t, key, val, 1);
      return;
    }
    t = tm;  /* else repeat with 'tm' */
  }
  killaG_runerror(L, "loop in gettable");
}


void killaV_settable (killa_State *L, const killa_TValue *t, killa_TValue *key, killa_StkId val) {
  int loop;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const killa_TValue *tm;
    if (killa_ttistable(t)) {  /* `t' is a table? */
      killa_Table *h = killa_hvalue(t);
      killa_TValue *oldval = killa_cast(killa_TValue *, killaH_get(h, key));
      /* if previous value is not nil, there must be a previous entry
         in the table; moreover, a metamethod has no relevance */
      if (!killa_ttisnil(oldval) ||
         /* previous value is nil; must check the metamethod */
         ((tm = killa_fasttm(L, h->metatable, TM_NEWINDEX)) == NULL &&
         /* no metamethod; is there a previous entry in the table? */
         (oldval != killaO_nilobject ||
         /* no previous entry; must create one. (The next test is
            always true; we only need the assignment.) */
         (oldval = killaH_newkey(L, h, key), 1)))) {
        /* no metamethod and (now) there is an entry with given key */
        killa_setobj2t(L, oldval, val);  /* assign new value to that entry */
        killa_invalidateTMcache(h);
        killaC_barrierback(L, killa_obj2gco(h), val);
        return;
      }
      /* else will try the metamethod */
    }
    else  /* not a table; check metamethod */
      if (killa_ttisnil(tm = killaT_gettmbyobj(L, t, TM_NEWINDEX)))
        killaG_typeerror(L, t, "index");
    /* there is a metamethod */
    if (killa_ttisfunction(tm)) {
      callTM(L, tm, t, key, val, 0);
      return;
    }
    t = tm;  /* else repeat with 'tm' */
  }
  killaG_runerror(L, "loop in settable");
}


static int call_binTM (killa_State *L, const killa_TValue *p1, const killa_TValue *p2,
                       killa_StkId res, KILLA_TMS event) {
  const killa_TValue *tm = killaT_gettmbyobj(L, p1, event);  /* try first operand */
  if (killa_ttisnil(tm))
    tm = killaT_gettmbyobj(L, p2, event);  /* try second operand */
  if (killa_ttisnil(tm)) return 0;
  callTM(L, tm, p1, p2, res, 1);
  return 1;
}


static const killa_TValue *get_equalTM (killa_State *L, killa_Table *mt1, killa_Table *mt2,
                                  KILLA_TMS event) {
  const killa_TValue *tm1 = killa_fasttm(L, mt1, event);
  const killa_TValue *tm2;
  if (tm1 == NULL) return NULL;  /* no metamethod */
  if (mt1 == mt2) return tm1;  /* same metatables => same metamethods */
  tm2 = killa_fasttm(L, mt2, event);
  if (tm2 == NULL) return NULL;  /* no metamethod */
  if (killaV_rawequalobj(tm1, tm2))  /* same metamethods? */
    return tm1;
  return NULL;
}


static int call_orderTM (killa_State *L, const killa_TValue *p1, const killa_TValue *p2,
                         KILLA_TMS event) {
  if (!call_binTM(L, p1, p2, L->top, event))
    return -1;  /* no metamethod */
  else
    return !killa_isfalse(L->top);
}


static int l_strcmp (const killa_TString *ls, const killa_TString *rs) {
  const char *l = killa_getstr(ls);
  size_t ll = ls->tsv.len;
  const char *r = killa_getstr(rs);
  size_t lr = rs->tsv.len;
  for (;;) {
    int temp = strcoll(l, r);
    if (temp != 0) return temp;
    else {  /* strings are equal up to a `\0' */
      size_t len = strlen(l);  /* index of first `\0' in both strings */
      if (len == lr)  /* r is finished? */
        return (len == ll) ? 0 : 1;
      else if (len == ll)  /* l is finished? */
        return -1;  /* l is smaller than r (because r is not finished) */
      /* both strings longer than `len'; go on comparing (after the `\0') */
      len++;
      l += len; ll -= len; r += len; lr -= len;
    }
  }
}


int killaV_lessthan (killa_State *L, const killa_TValue *l, const killa_TValue *r) {
  int res;
  if (killa_ttisnumber(l) && killa_ttisnumber(r))
    return killai_numlt(L, killa_nvalue(l), killa_nvalue(r));
  else if (killa_ttisstring(l) && killa_ttisstring(r))
    return l_strcmp(killa_rawtsvalue(l), killa_rawtsvalue(r)) < 0;
  else if ((res = call_orderTM(L, l, r, TM_LT)) < 0)
    killaG_ordererror(L, l, r);
  return res;
}


int killaV_lessequal (killa_State *L, const killa_TValue *l, const killa_TValue *r) {
  int res;
  if (killa_ttisnumber(l) && killa_ttisnumber(r))
    return killai_numle(L, killa_nvalue(l), killa_nvalue(r));
  else if (killa_ttisstring(l) && killa_ttisstring(r))
    return l_strcmp(killa_rawtsvalue(l), killa_rawtsvalue(r)) <= 0;
  else if ((res = call_orderTM(L, l, r, TM_LE)) >= 0)  /* first try `le' */
    return res;
  else if ((res = call_orderTM(L, r, l, TM_LT)) < 0)  /* else try `lt' */
    killaG_ordererror(L, l, r);
  return !res;
}


/*
** equality of Killa values. L == NULL means raw equality (no metamethods)
*/
int killaV_equalobj_ (killa_State *L, const killa_TValue *t1, const killa_TValue *t2) {
  const killa_TValue *tm;
  killa_assert(killa_ttisequal(t1, t2));
  switch (killa_ttype(t1)) {
    case KILLA_TNULL: return 1;
    case KILLA_TNUMBER: return killai_numeq(killa_nvalue(t1), killa_nvalue(t2));
    case KILLA_TBOOLEAN: return killa_bvalue(t1) == killa_bvalue(t2);  /* true must be 1 !! */
    case KILLA_TLIGHTUSERDATA: return killa_pvalue(t1) == killa_pvalue(t2);
    case KILLA_TLCF: return killa_fvalue(t1) == killa_fvalue(t2);
    case KILLA_TSTRING: return killa_eqstr(killa_rawtsvalue(t1), killa_rawtsvalue(t2));
    case KILLA_TUSERDATA: {
      if (killa_uvalue(t1) == killa_uvalue(t2)) return 1;
      else if (L == NULL) return 0;
      tm = get_equalTM(L, killa_uvalue(t1)->metatable, killa_uvalue(t2)->metatable, TM_EQ);
      break;  /* will try TM */
    }
    case KILLA_TTABLE: {
      if (killa_hvalue(t1) == killa_hvalue(t2)) return 1;
      else if (L == NULL) return 0;
      tm = get_equalTM(L, killa_hvalue(t1)->metatable, killa_hvalue(t2)->metatable, TM_EQ);
      break;  /* will try TM */
    }
    default:
      killa_assert(killa_iscollectable(t1));
      return killa_gcvalue(t1) == killa_gcvalue(t2);
  }
  if (tm == NULL) return 0;  /* no TM? */
  callTM(L, tm, t1, t2, L->top, 1);  /* call TM */
  return !killa_isfalse(L->top);
}


void killaV_concat (killa_State *L, int total) {
  killa_assert(total >= 2);
  do {
    killa_StkId top = L->top;
    int n = 2;  /* number of elements handled in this pass (at least 2) */
    if (!(killa_ttisstring(top-2) || killa_ttisnumber(top-2)) || !killa_vmtostring(L, top-1)) {
      if (!call_binTM(L, top-2, top-1, top-2, TM_CONCAT))
        killaG_concaterror(L, top-2, top-1);
    }
    else if (killa_tsvalue(top-1)->len == 0)  /* second operand is empty? */
      (void)killa_vmtostring(L, top - 2);  /* result is first operand */
    else if (killa_ttisstring(top-2) && killa_tsvalue(top-2)->len == 0) {
      killa_setsvalue2s(L, top-2, killa_rawtsvalue(top-1));  /* result is second op. */
    }
    else {
      /* at least two non-empty string values; get as many as possible */
      size_t tl = killa_tsvalue(top-1)->len;
      char *buffer;
      int i;
      /* collect total length */
      for (i = 1; i < total && killa_vmtostring(L, top-i-1); i++) {
        size_t l = killa_tsvalue(top-i-1)->len;
        if (l >= (KILLA_MAX_SIZET/sizeof(char)) - tl)
          killaG_runerror(L, "string length overflow");
        tl += l;
      }
      buffer = killaZ_openspace(L, &KILLA_G(L)->buff, tl);
      tl = 0;
      n = i;
      do {  /* concat all strings */
        size_t l = killa_tsvalue(top-i)->len;
        memcpy(buffer+tl, killa_svalue(top-i), l * sizeof(char));
        tl += l;
      } while (--i > 0);
      killa_setsvalue2s(L, top-n, killaS_newlstr(L, buffer, tl));
    }
    total -= n-1;  /* got 'n' strings to create 1 new */
    L->top -= n-1;  /* popped 'n' strings and pushed one */
  } while (total > 1);  /* repeat until only 1 result left */
}


void killaV_objlen (killa_State *L, killa_StkId ra, const killa_TValue *rb) {
  const killa_TValue *tm;
  switch (killa_ttypenv(rb)) {
    case KILLA_TTABLE: {
      killa_Table *h = killa_hvalue(rb);
      tm = killa_fasttm(L, h->metatable, TM_LEN);
      if (tm) break;  /* metamethod? break switch to call it */
      killa_setnvalue(ra, killa_cast_num(killaH_getn(h)));  /* else primitive len */
      return;
    }
    case KILLA_TSTRING: {
      killa_setnvalue(ra, killa_cast_num(killa_tsvalue(rb)->len));
      return;
    }
    default: {  /* try metamethod */
      tm = killaT_gettmbyobj(L, rb, TM_LEN);
      if (killa_ttisnil(tm))  /* no metamethod? */
        killaG_typeerror(L, rb, "get length of");
      break;
    }
  }
  callTM(L, tm, rb, rb, ra, 1);
}


void killaV_arith (killa_State *L, killa_StkId ra, const killa_TValue *rb,
                 const killa_TValue *rc, KILLA_TMS op) {
  killa_TValue tempb, tempc;
  const killa_TValue *b, *c;
  if ((b = killaV_tonumber(rb, &tempb)) != NULL &&
      (c = killaV_tonumber(rc, &tempc)) != NULL) {
    killa_Number res = killaO_arith(op - TM_ADD + KILLA_OPADD, killa_nvalue(b), killa_nvalue(c));
    killa_setnvalue(ra, res);
  }
  else if (!call_binTM(L, rb, rc, ra, op))
    killaG_aritherror(L, rb, rc);
}


/*
** check whether cached closure in prototype 'p' may be reused, that is,
** whether there is a cached closure with the same upvalues needed by
** new closure to be created.
*/
static killa_Closure *getcached (killa_Proto *p, killa_UpVal **encup, killa_StkId base) {
  killa_Closure *c = p->cache;
  if (c != NULL) {  /* is there a cached closure? */
    int nup = p->sizeupvalues;
    killa_Upvaldesc *uv = p->upvalues;
    int i;
    for (i = 0; i < nup; i++) {  /* check whether it has right upvalues */
      killa_TValue *v = uv[i].instack ? base + uv[i].idx : encup[uv[i].idx]->v;
      if (c->l.upvals[i]->v != v)
        return NULL;  /* wrong upvalue; cannot reuse closure */
    }
  }
  return c;  /* return cached closure (or NULL if no cached closure) */
}


/*
** create a new Killa closure, push it in the stack, and initialize
** its upvalues. Note that the call to 'killaC_barrierproto' must come
** before the assignment to 'p->cache', as the function needs the
** original value of that field.
*/
static void pushclosure (killa_State *L, killa_Proto *p, killa_UpVal **encup, killa_StkId base,
                         killa_StkId ra) {
  int nup = p->sizeupvalues;
  killa_Upvaldesc *uv = p->upvalues;
  int i;
  killa_Closure *ncl = killaF_newLclosure(L, p);
  killa_setclLvalue(L, ra, ncl);  /* anchor new closure in stack */
  for (i = 0; i < nup; i++) {  /* fill in its upvalues */
    if (uv[i].instack)  /* upvalue refers to local variable? */
      ncl->l.upvals[i] = killaF_findupval(L, base + uv[i].idx);
    else  /* get upvalue from enclosing function */
      ncl->l.upvals[i] = encup[uv[i].idx];
  }
  killaC_barrierproto(L, p, ncl);
  p->cache = ncl;  /* save it on cache for reuse */
}


/*
** finish execution of an opcode interrupted by an yield
*/
void killaV_finishOp (killa_State *L) {
  killa_CallInfo *ci = L->ci;
  killa_StkId base = ci->u.l.base;
  killa_Instruction inst = *(ci->u.l.savedpc - 1);  /* interrupted instruction */
  killa_OpCode op = KILLA_GET_OPCODE(inst);
  switch (op) {  /* finish its execution */
    case OP_ADD: case OP_SUB: case OP_MUL: case OP_DIV:
    case OP_MOD: case OP_POW: case OP_UNM: case OP_LEN:
    case OP_GETTABUP: case OP_GETTABLE: case OP_SELF: {
      killa_setobjs2s(L, base + KILLA_GETARG_A(inst), --L->top);
      break;
    }
    case OP_LE: case OP_LT: case OP_EQ: {
      int res = !killa_isfalse(L->top - 1);
      L->top--;
      /* metamethod should not be called when operand is K */
      killa_assert(!KILLA_ISK(KILLA_GETARG_B(inst)));
      if (op == OP_LE &&  /* "<=" using "<" instead? */
          killa_ttisnil(killaT_gettmbyobj(L, base + KILLA_GETARG_B(inst), TM_LE)))
        res = !res;  /* invert result */
      killa_assert(KILLA_GET_OPCODE(*ci->u.l.savedpc) == OP_JMP);
      if (res != KILLA_GETARG_A(inst))  /* condition failed? */
        ci->u.l.savedpc++;  /* skip jump instruction */
      break;
    }
    case OP_CONCAT: {
      killa_StkId top = L->top - 1;  /* top when 'call_binTM' was called */
      int b = KILLA_GETARG_B(inst);      /* first element to concatenate */
      int total = killa_cast_int(top - 1 - (base + b));  /* yet to concatenate */
      killa_setobj2s(L, top - 2, top);  /* put TM result in proper position */
      if (total > 1) {  /* are there elements to concat? */
        L->top = top - 1;  /* top is one after last element (at top-2) */
        killaV_concat(L, total);  /* concat them (may yield again) */
      }
      /* move final result to final position */
      killa_setobj2s(L, ci->u.l.base + KILLA_GETARG_A(inst), L->top - 1);
      L->top = ci->top;  /* restore top */
      break;
    }
    case OP_TFORCALL: {
      killa_assert(KILLA_GET_OPCODE(*ci->u.l.savedpc) == OP_TFORLOOP);
      L->top = ci->top;  /* correct top */
      break;
    }
    case OP_CALL: {
      if (KILLA_GETARG_C(inst) - 1 >= 0)  /* nresults >= 0? */
        L->top = ci->top;  /* adjust results */
      break;
    }
    case OP_TAILCALL: case OP_SETTABUP:  case OP_SETTABLE:
      break;
    default: killa_assert(0);
  }
}



/*
** some macros for common tasks in `killaV_execute'
*/

#if !defined killai_runtimecheck
#define killai_runtimecheck(L, c)		/* void */
#endif


#define RA(i)	(base+KILLA_GETARG_A(i))
/* to be used after possible stack reallocation */
#define RB(i)	killa_check_exp(killa_getBMode(KILLA_GET_OPCODE(i)) == OpArgR, base+KILLA_GETARG_B(i))
#define RC(i)	killa_check_exp(killa_getCMode(KILLA_GET_OPCODE(i)) == OpArgR, base+KILLA_GETARG_C(i))
#define RKB(i)	killa_check_exp(killa_getBMode(KILLA_GET_OPCODE(i)) == OpArgK, \
	KILLA_ISK(KILLA_GETARG_B(i)) ? k+KILLA_INDEXK(KILLA_GETARG_B(i)) : base+KILLA_GETARG_B(i))
#define RKC(i)	killa_check_exp(killa_getCMode(KILLA_GET_OPCODE(i)) == OpArgK, \
	KILLA_ISK(KILLA_GETARG_C(i)) ? k+KILLA_INDEXK(KILLA_GETARG_C(i)) : base+KILLA_GETARG_C(i))
#define KBx(i)  \
  (k + (KILLA_GETARG_Bx(i) != 0 ? KILLA_GETARG_Bx(i) - 1 : KILLA_GETARG_Ax(*ci->u.l.savedpc++)))


/* execute a jump instruction */
#define dojump(ci,i,e) \
  { int a = KILLA_GETARG_A(i); \
    if (a > 0) killaF_close(L, ci->u.l.base + a - 1); \
    ci->u.l.savedpc += KILLA_GETARG_sBx(i) + e; }

/* for test instructions, execute the jump instruction that follows it */
#define donextjump(ci)	{ i = *ci->u.l.savedpc; dojump(ci, i, 1); }


#define Protect(x)	{ {x;}; base = ci->u.l.base; }

#define checkGC(L,c)	Protect(killaC_condGC(L, c); killai_threadyield(L);)


#define arith_op(op,tm) { \
        killa_TValue *rb = RKB(i); \
        killa_TValue *rc = RKC(i); \
        if (killa_ttisnumber(rb) && killa_ttisnumber(rc)) { \
          killa_Number nb = killa_nvalue(rb), nc = killa_nvalue(rc); \
          killa_setnvalue(ra, op(L, nb, nc)); \
        } \
        else { Protect(killaV_arith(L, ra, rb, rc, tm)); } }


#define vmdispatch(o)	switch(o)
#define vmcase(l,b)	case l: {b}  break;
#define vmcasenb(l,b)	case l: {b}		/* nb = no break */

void killaV_execute (killa_State *L) {
  killa_CallInfo *ci = L->ci;
  killa_LClosure *cl;
  killa_TValue *k;
  killa_StkId base;
 newframe:  /* reentry point when frame changes (call/return) */
  killa_assert(ci == L->ci);
  cl = killa_clLvalue(ci->func);
  k = cl->p->k;
  base = ci->u.l.base;
  /* main loop of interpreter */
  for (;;) {
    killa_Instruction i = *(ci->u.l.savedpc++);
    killa_StkId ra;
    if ((L->hookmask & (KILLA_MASKLINE | KILLA_MASKCOUNT)) &&
        (--L->hookcount == 0 || L->hookmask & KILLA_MASKLINE)) {
      Protect(traceexec(L));
    }
    /* WARNING: several calls may realloc the stack and invalidate `ra' */
    ra = RA(i);
    killa_assert(base == ci->u.l.base);
    killa_assert(base <= L->top && L->top < L->stack + L->stacksize);
    vmdispatch (KILLA_GET_OPCODE(i)) {
      vmcase(OP_MOVE,
        killa_setobjs2s(L, ra, RB(i));
      )
      vmcase(OP_LOADK,
        killa_TValue *rb = k + KILLA_GETARG_Bx(i);
        killa_setobj2s(L, ra, rb);
      )
      vmcase(OP_LOADKX,
        killa_TValue *rb;
        killa_assert(KILLA_GET_OPCODE(*ci->u.l.savedpc) == OP_EXTRAARG);
        rb = k + KILLA_GETARG_Ax(*ci->u.l.savedpc++);
        killa_setobj2s(L, ra, rb);
      )
      vmcase(OP_LOADBOOL,
        killa_setbvalue(ra, KILLA_GETARG_B(i));
        if (KILLA_GETARG_C(i)) ci->u.l.savedpc++;  /* skip next instruction (if C) */
      )
      vmcase(OP_LOADNIL,
        int b = KILLA_GETARG_B(i);
        do {
          killa_setnilvalue(ra++);
        } while (b--);
      )
      vmcase(OP_GETUPVAL,
        int b = KILLA_GETARG_B(i);
        killa_setobj2s(L, ra, cl->upvals[b]->v);
      )
      vmcase(OP_GETTABUP,
        int b = KILLA_GETARG_B(i);
        Protect(killaV_gettable(L, cl->upvals[b]->v, RKC(i), ra));
      )
      vmcase(OP_GETTABLE,
        Protect(killaV_gettable(L, RB(i), RKC(i), ra));
      )
      vmcase(OP_SETTABUP,
        int a = KILLA_GETARG_A(i);
        Protect(killaV_settable(L, cl->upvals[a]->v, RKB(i), RKC(i)));
      )
      vmcase(OP_SETUPVAL,
        killa_UpVal *uv = cl->upvals[KILLA_GETARG_B(i)];
        killa_setobj(L, uv->v, ra);
        killaC_barrier(L, uv, ra);
      )
      vmcase(OP_SETTABLE,
        Protect(killaV_settable(L, ra, RKB(i), RKC(i)));
      )
      vmcase(OP_NEWTABLE,
        int b = KILLA_GETARG_B(i);
        int c = KILLA_GETARG_C(i);
        killa_Table *t = killaH_new(L);
        killa_sethvalue(L, ra, t);
        if (b != 0 || c != 0)
          killaH_resize(L, t, killaO_fb2int(b), killaO_fb2int(c));
        checkGC(L,
          L->top = ra + 1;  /* limit of live values */
          killaC_step(L);
          L->top = ci->top;  /* restore top */
        )
      )
      vmcase(OP_SELF,
        killa_StkId rb = RB(i);
        killa_setobjs2s(L, ra+1, rb);
        Protect(killaV_gettable(L, rb, RKC(i), ra));
      )
      vmcase(OP_ADD,
        arith_op(killai_numadd, TM_ADD);
      )
      vmcase(OP_SUB,
        arith_op(killai_numsub, TM_SUB);
      )
      vmcase(OP_MUL,
        arith_op(killai_nummul, TM_MUL);
      )
      vmcase(OP_DIV,
        arith_op(killai_numdiv, TM_DIV);
      )
      vmcase(OP_MOD,
        arith_op(killai_nummod, TM_MOD);
      )
      vmcase(OP_POW,
        arith_op(killai_numpow, TM_POW);
      )
      vmcase(OP_UNM,
        killa_TValue *rb = RB(i);
        if (killa_ttisnumber(rb)) {
          killa_Number nb = killa_nvalue(rb);
          killa_setnvalue(ra, killai_numunm(L, nb));
        }
        else {
          Protect(killaV_arith(L, ra, rb, rb, TM_UNM));
        }
      )
      vmcase(OP_NOT,
        killa_TValue *rb = RB(i);
        int res = killa_isfalse(rb);  /* next assignment may change this value */
        killa_setbvalue(ra, res);
      )
      vmcase(OP_LEN,
        Protect(killaV_objlen(L, ra, RB(i)));
      )
      vmcase(OP_CONCAT,
        int b = KILLA_GETARG_B(i);
        int c = KILLA_GETARG_C(i);
        killa_StkId rb;
        L->top = base + c + 1;  /* mark the end of concat operands */
        Protect(killaV_concat(L, c - b + 1));
        ra = RA(i);  /* 'killaV_concat' may invoke TMs and move the stack */
        rb = b + base;
        killa_setobjs2s(L, ra, rb);
        checkGC(L,
          L->top = (ra >= rb ? ra + 1 : rb);  /* limit of live values */
          killaC_step(L);
        )
        L->top = ci->top;  /* restore top */
      )
      vmcase(OP_JMP,
        dojump(ci, i, 0);
      )
      vmcase(OP_EQ,
        killa_TValue *rb = RKB(i);
        killa_TValue *rc = RKC(i);
        Protect(
          if (killa_cast_int(killa_equalobj(L, rb, rc)) != KILLA_GETARG_A(i))
            ci->u.l.savedpc++;
          else
            donextjump(ci);
        )
      )
      vmcase(OP_LT,
        Protect(
          if (killaV_lessthan(L, RKB(i), RKC(i)) != KILLA_GETARG_A(i))
            ci->u.l.savedpc++;
          else
            donextjump(ci);
        )
      )
      vmcase(OP_LE,
        Protect(
          if (killaV_lessequal(L, RKB(i), RKC(i)) != KILLA_GETARG_A(i))
            ci->u.l.savedpc++;
          else
            donextjump(ci);
        )
      )
      vmcase(OP_TEST,
        if (KILLA_GETARG_C(i) ? killa_isfalse(ra) : !killa_isfalse(ra))
            ci->u.l.savedpc++;
          else
          donextjump(ci);
      )
      vmcase(OP_TESTSET,
        killa_TValue *rb = RB(i);
        if (KILLA_GETARG_C(i) ? killa_isfalse(rb) : !killa_isfalse(rb))
          ci->u.l.savedpc++;
        else {
          killa_setobjs2s(L, ra, rb);
          donextjump(ci);
        }
      )
      vmcase(OP_CALL,
        int b = KILLA_GETARG_B(i);
        int nresults = KILLA_GETARG_C(i) - 1;
        if (b != 0) L->top = ra+b;  /* else previous instruction set top */
        if (killaD_precall(L, ra, nresults)) {  /* C function? */
          if (nresults >= 0) L->top = ci->top;  /* adjust results */
          base = ci->u.l.base;
        }
        else {  /* Killa function */
          ci = L->ci;
          ci->callstatus |= KILLA_CIST_REENTRY;
          goto newframe;  /* restart killaV_execute over new Killa function */
        }
      )
      vmcase(OP_TAILCALL,
        int b = KILLA_GETARG_B(i);
        if (b != 0) L->top = ra+b;  /* else previous instruction set top */
        killa_assert(KILLA_GETARG_C(i) - 1 == KILLA_MULTRET);
        if (killaD_precall(L, ra, KILLA_MULTRET))  /* C function? */
          base = ci->u.l.base;
        else {
          /* tail call: put called frame (n) in place of caller one (o) */
          killa_CallInfo *nci = L->ci;  /* called frame */
          killa_CallInfo *oci = nci->previous;  /* caller frame */
          killa_StkId nfunc = nci->func;  /* called function */
          killa_StkId ofunc = oci->func;  /* caller function */
          /* last stack slot filled by 'precall' */
          killa_StkId lim = nci->u.l.base + killa_getproto(nfunc)->numparams;
          int aux;
          /* close all upvalues from previous call */
          if (cl->p->sizep > 0) killaF_close(L, oci->u.l.base);
          /* move new frame into old one */
          for (aux = 0; nfunc + aux < lim; aux++)
            killa_setobjs2s(L, ofunc + aux, nfunc + aux);
          oci->u.l.base = ofunc + (nci->u.l.base - nfunc);  /* correct base */
          oci->top = L->top = ofunc + (L->top - nfunc);  /* correct top */
          oci->u.l.savedpc = nci->u.l.savedpc;
          oci->callstatus |= KILLA_CIST_TAIL;  /* function was tail called */
          ci = L->ci = oci;  /* remove new frame */
          killa_assert(L->top == oci->u.l.base + killa_getproto(ofunc)->maxstacksize);
          goto newframe;  /* restart killaV_execute over new Killa function */
        }
      )
      vmcasenb(OP_RETURN,
        int b = KILLA_GETARG_B(i);
        if (b != 0) L->top = ra+b-1;
        if (cl->p->sizep > 0) killaF_close(L, base);
        b = killaD_poscall(L, ra);
        if (!(ci->callstatus & KILLA_CIST_REENTRY))  /* 'ci' still the called one */
          return;  /* external invocation: return */
        else {  /* invocation via reentry: continue execution */
          ci = L->ci;
          if (b) L->top = ci->top;
          killa_assert(killa_isKilla(ci));
          killa_assert(KILLA_GET_OPCODE(*((ci)->u.l.savedpc - 1)) == OP_CALL);
          goto newframe;  /* restart killaV_execute over new Killa function */
        }
      )
      vmcase(OP_FORLOOP,
        killa_Number step = killa_nvalue(ra+2);
        killa_Number idx = killai_numadd(L, killa_nvalue(ra), step); /* increment index */
        killa_Number limit = killa_nvalue(ra+1);
        if (killai_numlt(L, 0, step) ? killai_numle(L, idx, limit)
                                   : killai_numle(L, limit, idx)) {
          ci->u.l.savedpc += KILLA_GETARG_sBx(i);  /* jump back */
          killa_setnvalue(ra, idx);  /* update internal index... */
          killa_setnvalue(ra+3, idx);  /* ...and external index */
        }
      )
      vmcase(OP_FORPREP,
        const killa_TValue *init = ra;
        const killa_TValue *plimit = ra+1;
        const killa_TValue *pstep = ra+2;
        if (!killa_vmtonumber(init, ra))
          killaG_runerror(L, KILLA_QL("for") " initial value must be a number");
        else if (!killa_vmtonumber(plimit, ra+1))
          killaG_runerror(L, KILLA_QL("for") " limit must be a number");
        else if (!killa_vmtonumber(pstep, ra+2))
          killaG_runerror(L, KILLA_QL("for") " step must be a number");
        killa_setnvalue(ra, killai_numsub(L, killa_nvalue(ra), killa_nvalue(pstep)));
        ci->u.l.savedpc += KILLA_GETARG_sBx(i);
      )
      vmcasenb(OP_TFORCALL,
        killa_StkId cb = ra + 3;  /* call base */
        killa_setobjs2s(L, cb+2, ra+2);
        killa_setobjs2s(L, cb+1, ra+1);
        killa_setobjs2s(L, cb, ra);
        L->top = cb + 3;  /* func. + 2 args (state and index) */
        Protect(killaD_call(L, cb, KILLA_GETARG_C(i), 1));
        L->top = ci->top;
        i = *(ci->u.l.savedpc++);  /* go to next instruction */
        ra = RA(i);
        killa_assert(KILLA_GET_OPCODE(i) == OP_TFORLOOP);
        goto l_tforloop;
      )
      vmcase(OP_TFORLOOP,
        l_tforloop:
        if (!killa_ttisnil(ra + 1)) {  /* continue loop? */
          killa_setobjs2s(L, ra, ra + 1);  /* save control variable */
           ci->u.l.savedpc += KILLA_GETARG_sBx(i);  /* jump back */
        }
      )
      vmcase(OP_SETLIST,
        int n = KILLA_GETARG_B(i);
        int c = KILLA_GETARG_C(i);
        int last;
        killa_Table *h;
        if (n == 0) n = killa_cast_int(L->top - ra) - 1;
        if (c == 0) {
          killa_assert(KILLA_GET_OPCODE(*ci->u.l.savedpc) == OP_EXTRAARG);
          c = KILLA_GETARG_Ax(*ci->u.l.savedpc++);
        }
        killai_runtimecheck(L, killa_ttistable(ra));
        h = killa_hvalue(ra);
        last = ((c-1)*KILLA_LFIELDS_PER_FLUSH) + n;
        if (last > h->sizearray)  /* needs more space? */
          killaH_resizearray(L, h, last);  /* pre-allocate it at once */
        for (last += KILLA_BASE - 1; n > 0; n--) {
          killa_TValue *val = ra+n;
          killaH_setint(L, h, last--, val);
          killaC_barrierback(L, killa_obj2gco(h), val);
        }
        L->top = ci->top;  /* correct top (in case of previous open call) */
      )
      vmcase(OP_CLOSURE,
        killa_Proto *p = cl->p->p[KILLA_GETARG_Bx(i)];
        killa_Closure *ncl = getcached(p, cl->upvals, base);  /* cached closure */
        if (ncl == NULL)  /* no match? */
          pushclosure(L, p, cl->upvals, base, ra);  /* create a new one */
        else
          killa_setclLvalue(L, ra, ncl);  /* push cashed closure */
        checkGC(L,
          L->top = ra + 1;  /* limit of live values */
          killaC_step(L);
          L->top = ci->top;  /* restore top */
        )
      )
      vmcase(OP_VARARG,
        int b = KILLA_GETARG_B(i) - 1;
        int j;
        int n = killa_cast_int(base - ci->func) - cl->p->numparams - 1;
        if (b < 0) {  /* B == 0? */
          b = n;  /* get all var. arguments */
          Protect(killaD_checkstack(L, n));
          ra = RA(i);  /* previous call may change the stack */
          L->top = ra + n;
        }
        for (j = 0; j < b; j++) {
          if (j < n) {
            killa_setobjs2s(L, ra + j, base - n + j);
          }
          else {
            killa_setnilvalue(ra + j);
          }
        }
      )
      vmcase(OP_EXTRAARG,
        killa_assert(0);
      )
    }
  }
}

