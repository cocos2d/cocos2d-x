/* ========================================================================== */
/*   Debug Interface                                                          */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdarg.h>
#include <stddef.h>
#include <string.h>


#define KILLA_CORE

#include "killa.h"

#include "kapi.h"
#include "kcode.h"
#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "kobject.h"
#include "kopcodes.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"
#include "kvm.h"



static const char *getfuncname (killa_State *L, killa_CallInfo *ci, const char **name);


static int currentpc (killa_CallInfo *ci) {
  killa_assert(killa_isKilla(ci));
  return killa_pcRel(ci->u.l.savedpc, killa_ci_func(ci)->p);
}


static int currentline (killa_CallInfo *ci) {
  return killa_getfuncline(killa_ci_func(ci)->p, currentpc(ci));
}


/*
** this function can be called asynchronous (e.g. during a signal)
*/
KILLA_API int killa_sethook (killa_State *L, killa_Hook func, int mask, int count) {
  if (func == NULL || mask == 0) {  /* turn off hooks? */
    mask = 0;
    func = NULL;
  }
  if (killa_isKilla(L->ci))
    L->oldpc = L->ci->u.l.savedpc;
  L->hook = func;
  L->basehookcount = count;
  killa_resethookcount(L);
  L->hookmask = killa_cast_byte(mask);
  return 1;
}


KILLA_API killa_Hook killa_gethook (killa_State *L) {
  return L->hook;
}


KILLA_API int killa_gethookmask (killa_State *L) {
  return L->hookmask;
}


KILLA_API int killa_gethookcount (killa_State *L) {
  return L->basehookcount;
}


KILLA_API int killa_getstack (killa_State *L, int level, killa_Debug *ar) {
  int status;
  killa_CallInfo *ci;
  if (level < 0) return 0;  /* invalid (negative) level */
  killa_lock(L);
  for (ci = L->ci; level > 0 && ci != &L->base_ci; ci = ci->previous)
    level--;
  if (level == 0 && ci != &L->base_ci) {  /* level found? */
    status = 1;
    ar->i_ci = ci;
  }
  else status = 0;  /* no such level */
  killa_unlock(L);
  return status;
}


static const char *upvalname (killa_Proto *p, int uv) {
  killa_TString *s = killa_check_exp(uv < p->sizeupvalues, p->upvalues[uv].name);
  if (s == NULL) return "?";
  else return killa_getstr(s);
}


static const char *findvararg (killa_CallInfo *ci, int n, killa_StkId *pos) {
  int nparams = killa_clLvalue(ci->func)->p->numparams;
  if (n >= ci->u.l.base - ci->func - nparams)
    return NULL;  /* no such vararg */
  else {
    *pos = ci->func + nparams + n;
    return "(*vararg)";  /* generic name for any vararg */
  }
}


static const char *findlocal (killa_State *L, killa_CallInfo *ci, int n,
                              killa_StkId *pos) {
  const char *name = NULL;
  killa_StkId base;
  if (killa_isKilla(ci)) {
    if (n < 0)  /* access to vararg values? */
      return findvararg(ci, -n, pos);
    else {
      base = ci->u.l.base;
      name = killaF_getlocalname(killa_ci_func(ci)->p, n, currentpc(ci));
    }
  }
  else
    base = ci->func + 1;
  if (name == NULL) {  /* no 'standard' name? */
    killa_StkId limit = (ci == L->ci) ? L->top : ci->next->func;
    if (limit - base >= n && n > 0)  /* is 'n' inside 'ci' stack? */
      name = "(*temporary)";  /* generic name for any valid slot */
    else
      return NULL;  /* no name */
  }
  *pos = base + (n - 1);
  return name;
}


KILLA_API const char *killa_getlocal (killa_State *L, const killa_Debug *ar, int n) {
  const char *name;
  killa_lock(L);
  if (ar == NULL) {  /* information about non-active function? */
    if (!killa_isLfunction(L->top - 1))  /* not a Killa function? */
      name = NULL;
    else  /* consider live variables at function start (parameters) */
      name = killaF_getlocalname(killa_clLvalue(L->top - 1)->p, n, 0);
  }
  else {  /* active function; get information through 'ar' */
    killa_StkId pos = 0;  /* to avoid warnings */
    name = findlocal(L, ar->i_ci, n, &pos);
    if (name) {
      killa_setobj2s(L, L->top, pos);
      killaA_incr_top(L);
    }
  }
  killa_unlock(L);
  return name;
}


KILLA_API const char *killa_setlocal (killa_State *L, const killa_Debug *ar, int n) {
  killa_StkId pos = 0;  /* to avoid warnings */
  const char *name = findlocal(L, ar->i_ci, n, &pos);
  killa_lock(L);
  if (name)
    killa_setobjs2s(L, pos, L->top - 1);
  L->top--;  /* pop value */
  killa_unlock(L);
  return name;
}


static void funcinfo (killa_Debug *ar, killa_Closure *cl) {
  if (cl == NULL || cl->c.isC) {
    ar->source = "=[C]";
    ar->linedefined = -1;
    ar->lastlinedefined = -1;
    ar->what = "C";
  }
  else {
    killa_Proto *p = cl->l.p;
    ar->source = p->source ? killa_getstr(p->source) : "=?";
    ar->linedefined = p->linedefined;
    ar->lastlinedefined = p->lastlinedefined;
    ar->what = (ar->linedefined == 0) ? "main" : "Killa";
  }
  killaO_chunkid(ar->short_src, ar->source, KILLA_IDSIZE);
}


static void collectvalidlines (killa_State *L, killa_Closure *f) {
  if (f == NULL || f->c.isC) {
    killa_setnilvalue(L->top);
    killa_incr_top(L);
  }
  else {
    int i;
    killa_TValue v;
    int *lineinfo = f->l.p->lineinfo;
    killa_Table *t = killaH_new(L);  /* new table to store active lines */
    killa_sethvalue(L, L->top, t);  /* push it on stack */
    killa_incr_top(L);
    killa_setbvalue(&v, 1);  /* boolean 'true' to be the value of all indices */
    for (i = 0; i < f->l.p->sizelineinfo; i++)  /* for all lines with code */
      killaH_setint(L, t, lineinfo[i], &v);  /* table[line] = true */
  }
}


static int auxgetinfo (killa_State *L, const char *what, killa_Debug *ar,
                    killa_Closure *f, killa_CallInfo *ci) {
  int status = 1;
  for (; *what; what++) {
    switch (*what) {
      case 'S': {
        funcinfo(ar, f);
        break;
      }
      case 'l': {
        ar->currentline = (ci && killa_isKilla(ci)) ? currentline(ci) : -1;
        break;
      }
      case 'u': {
        ar->nups = (f == NULL) ? 0 : f->c.nupvalues;
        if (f == NULL || f->c.isC) {
          ar->isvararg = 1;
          ar->nparams = 0;
        }
        else {
          ar->isvararg = f->l.p->is_vararg;
          ar->nparams = f->l.p->numparams;
        }
        break;
      }
      case 't': {
        ar->istailcall = (ci) ? ci->callstatus & KILLA_CIST_TAIL : 0;
        break;
      }
      case 'n': {
        /* calling function is a known Killa function? */
        if (ci && !(ci->callstatus & KILLA_CIST_TAIL) && killa_isKilla(ci->previous))
          ar->namewhat = getfuncname(L, ci->previous, &ar->name);
        else
          ar->namewhat = NULL;
        if (ar->namewhat == NULL) {
          ar->namewhat = "";  /* not found */
          ar->name = NULL;
        }
        break;
      }
      case 'L':
      case 'f':  /* handled by killa_getinfo */
        break;
      default: status = 0;  /* invalid option */
    }
  }
  return status;
}


KILLA_API int killa_getinfo (killa_State *L, const char *what, killa_Debug *ar) {
  int status;
  killa_Closure *cl;
  killa_CallInfo *ci;
  killa_StkId func;
  killa_lock(L);
  if (*what == '>') {
    ci = NULL;
    func = L->top - 1;
    killa_api_check(L, killa_ttisfunction(func), "function expected");
    what++;  /* skip the '>' */
    L->top--;  /* pop function */
  }
  else {
    ci = ar->i_ci;
    func = ci->func;
    killa_assert(killa_ttisfunction(ci->func));
  }
  cl = killa_ttisclosure(func) ? killa_clvalue(func) : NULL;
  status = auxgetinfo(L, what, ar, cl, ci);
  if (strchr(what, 'f')) {
    killa_setobjs2s(L, L->top, func);
    killa_incr_top(L);
  }
  if (strchr(what, 'L'))
    collectvalidlines(L, cl);
  killa_unlock(L);
  return status;
}


/*
** {======================================================
** Symbolic Execution
** =======================================================
*/

static const char *getobjname (killa_Proto *p, int lastpc, int reg,
                               const char **name);


/*
** find a "name" for the RK value 'c'
*/
static void kname (killa_Proto *p, int pc, int c, const char **name) {
  if (KILLA_ISK(c)) {  /* is 'c' a constant? */
    killa_TValue *kvalue = &p->k[KILLA_INDEXK(c)];
    if (killa_ttisstring(kvalue)) {  /* literal constant? */
      *name = killa_svalue(kvalue);  /* it is its own name */
      return;
    }
    /* else no reasonable name found */
  }
  else {  /* 'c' is a register */
    const char *what = getobjname(p, pc, c, name); /* search for 'c' */
    if (what && *what == 'c') {  /* found a constant name? */
      return;  /* 'name' already filled */
    }
    /* else no reasonable name found */
  }
  *name = "?";  /* no reasonable name found */
}


/*
** try to find last instruction before 'lastpc' that modified register 'reg'
*/
static int findsetreg (killa_Proto *p, int lastpc, int reg) {
  int pc;
  int setreg = -1;  /* keep last instruction that changed 'reg' */
  for (pc = 0; pc < lastpc; pc++) {
    killa_Instruction i = p->code[pc];
    killa_OpCode op = KILLA_GET_OPCODE(i);
    int a = KILLA_GETARG_A(i);
    switch (op) {
      case OP_LOADNIL: {
        int b = KILLA_GETARG_B(i);
        if (a <= reg && reg <= a + b)  /* set registers from 'a' to 'a+b' */
          setreg = pc;
        break;
      }
      case OP_TFORCALL: {
        if (reg >= a + 2) setreg = pc;  /* affect all regs above its base */
        break;
      }
      case OP_CALL:
      case OP_TAILCALL: {
        if (reg >= a) setreg = pc;  /* affect all registers above base */
        break;
      }
      case OP_JMP: {
        int b = KILLA_GETARG_sBx(i);
        int dest = pc + 1 + b;
        /* jump is forward and do not skip `lastpc'? */
        if (pc < dest && dest <= lastpc)
          pc += b;  /* do the jump */
        break;
      }
      case OP_TEST: {
        if (reg == a) setreg = pc;  /* jumped code can change 'a' */
        break;
      }
      default:
        if (killa_testAMode(op) && reg == a)  /* any instruction that set A */
          setreg = pc;
        break;
    }
  }
  return setreg;
}


static const char *getobjname (killa_Proto *p, int lastpc, int reg,
                               const char **name) {
  int pc;
  *name = killaF_getlocalname(p, reg + 1, lastpc);
  if (*name)  /* is a local? */
    return "local";
  /* else try symbolic execution */
  pc = findsetreg(p, lastpc, reg);
  if (pc != -1) {  /* could find instruction? */
    killa_Instruction i = p->code[pc];
    killa_OpCode op = KILLA_GET_OPCODE(i);
    switch (op) {
      case OP_MOVE: {
        int b = KILLA_GETARG_B(i);  /* move from 'b' to 'a' */
        if (b < KILLA_GETARG_A(i))
          return getobjname(p, pc, b, name);  /* get name for 'b' */
        break;
      }
      case OP_GETTABUP:
      case OP_GETTABLE: {
        int k = KILLA_GETARG_C(i);  /* key index */
        int t = KILLA_GETARG_B(i);  /* table index */
        const char *vn = (op == OP_GETTABLE)  /* name of indexed variable */
                         ? killaF_getlocalname(p, t + 1, pc)
                         : upvalname(p, t);
        kname(p, pc, k, name);
        return (vn && strcmp(vn, KILLA_ENV) == 0) ? "global" : "field";
      }
      case OP_GETUPVAL: {
        *name = upvalname(p, KILLA_GETARG_B(i));
        return "upvalue";
      }
      case OP_LOADK:
      case OP_LOADKX: {
        int b = (op == OP_LOADK) ? KILLA_GETARG_Bx(i)
                                 : KILLA_GETARG_Ax(p->code[pc + 1]);
        if (killa_ttisstring(&p->k[b])) {
          *name = killa_svalue(&p->k[b]);
          return "constant";
        }
        break;
      }
      case OP_SELF: {
        int k = KILLA_GETARG_C(i);  /* key index */
        kname(p, pc, k, name);
        return "method";
      }
      default: break;  /* go through to return NULL */
    }
  }
  return NULL;  /* could not find reasonable name */
}


static const char *getfuncname (killa_State *L, killa_CallInfo *ci, const char **name) {
  KILLA_TMS tm;
  killa_Proto *p = killa_ci_func(ci)->p;  /* calling function */
  int pc = currentpc(ci);  /* calling instruction index */
  killa_Instruction i = p->code[pc];  /* calling instruction */
  switch (KILLA_GET_OPCODE(i)) {
    case OP_CALL:
    case OP_TAILCALL:  /* get function name */
      return getobjname(p, pc, KILLA_GETARG_A(i), name);
    case OP_TFORCALL: {  /* for iterator */
      *name = "for iterator";
       return "for iterator";
    }
    /* all other instructions can call only through metamethods */
    case OP_SELF:
    case OP_GETTABUP:
    case OP_GETTABLE: tm = TM_INDEX; break;
    case OP_SETTABUP:
    case OP_SETTABLE: tm = TM_NEWINDEX; break;
    case OP_EQ: tm = TM_EQ; break;
    case OP_ADD: tm = TM_ADD; break;
    case OP_SUB: tm = TM_SUB; break;
    case OP_MUL: tm = TM_MUL; break;
    case OP_DIV: tm = TM_DIV; break;
    case OP_MOD: tm = TM_MOD; break;
    case OP_POW: tm = TM_POW; break;
    case OP_UNM: tm = TM_UNM; break;
    case OP_LEN: tm = TM_LEN; break;
    case OP_LT: tm = TM_LT; break;
    case OP_LE: tm = TM_LE; break;
    case OP_CONCAT: tm = TM_CONCAT; break;
    default:
      return NULL;  /* else no useful name can be found */
  }
  *name = killa_getstr(KILLA_G(L)->tmname[tm]);
  return "metamethod";
}

/* }====================================================== */



/*
** only ANSI way to check whether a pointer points to an array
** (used only for error messages, so efficiency is not a big concern)
*/
static int isinstack (killa_CallInfo *ci, const killa_TValue *o) {
  killa_StkId p;
  for (p = ci->u.l.base; p < ci->top; p++)
    if (o == p) return 1;
  return 0;
}


static const char *getupvalname (killa_CallInfo *ci, const killa_TValue *o,
                                 const char **name) {
  killa_LClosure *c = killa_ci_func(ci);
  int i;
  for (i = 0; i < c->nupvalues; i++) {
    if (c->upvals[i]->v == o) {
      *name = upvalname(c->p, i);
      return "upvalue";
    }
  }
  return NULL;
}


killa_noret killaG_typeerror (killa_State *L, const killa_TValue *o, const char *op) {
  killa_CallInfo *ci = L->ci;
  const char *name = NULL;
  const char *t = killa_objtypename(o);
  const char *kind = NULL;
  if (killa_isKilla(ci)) {
    kind = getupvalname(ci, o, &name);  /* check whether 'o' is an upvalue */
    if (!kind && isinstack(ci, o))  /* no? try a register */
      kind = getobjname(killa_ci_func(ci)->p, currentpc(ci),
                        killa_cast_int(o - ci->u.l.base), &name);
  }
  if (kind)
    killaG_runerror(L, "attempt to %s %s " KILLA_QS " (a %s value)",
                op, kind, name, t);
  else
    killaG_runerror(L, "attempt to %s a %s value", op, t);
}


killa_noret killaG_concaterror (killa_State *L, killa_StkId p1, killa_StkId p2) {
  if (killa_ttisstring(p1) || killa_ttisnumber(p1)) p1 = p2;
  killa_assert(!killa_ttisstring(p1) && !killa_ttisnumber(p2));
  killaG_typeerror(L, p1, "concatenate");
}


killa_noret killaG_aritherror (killa_State *L, const killa_TValue *p1, const killa_TValue *p2) {
  killa_TValue temp;
  if (killaV_tonumber(p1, &temp) == NULL)
    p2 = p1;  /* first operand is wrong */
  killaG_typeerror(L, p2, "perform arithmetic on");
}


killa_noret killaG_ordererror (killa_State *L, const killa_TValue *p1, const killa_TValue *p2) {
  const char *t1 = killa_objtypename(p1);
  const char *t2 = killa_objtypename(p2);
  if (t1 == t2)
    killaG_runerror(L, "attempt to compare two %s values", t1);
  else
    killaG_runerror(L, "attempt to compare %s with %s", t1, t2);
}


static void addinfo (killa_State *L, const char *msg) {
  killa_CallInfo *ci = L->ci;
  if (killa_isKilla(ci)) {  /* is Killa code? */
    char buff[KILLA_IDSIZE];  /* add file:line information */
    int line = currentline(ci);
    killa_TString *src = killa_ci_func(ci)->p->source;
    if (src)
      killaO_chunkid(buff, killa_getstr(src), KILLA_IDSIZE);
    else {  /* no source available; use "?" instead */
      buff[0] = '?'; buff[1] = '\0';
    }
    killaO_pushfstring(L, "%s:%d: %s", buff, line, msg);
  }
}


killa_noret killaG_errormsg (killa_State *L) {
  if (L->errfunc != 0) {  /* is there an error handling function? */
    killa_StkId errfunc = killa_restorestack(L, L->errfunc);
    if (!killa_ttisfunction(errfunc)) killaD_throw(L, KILLA_ERRERR);
    killa_setobjs2s(L, L->top, L->top - 1);  /* move argument */
    killa_setobjs2s(L, L->top - 1, errfunc);  /* push function */
    killa_incr_top(L);
    killaD_call(L, L->top - 2, 1, 0);  /* call it */
  }
  killaD_throw(L, KILLA_ERRRUN);
}


killa_noret killaG_runerror (killa_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  addinfo(L, killaO_pushvfstring(L, fmt, argp));
  va_end(argp);
  killaG_errormsg(L);
}

