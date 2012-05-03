/* ========================================================================== */
/*   Killa API                                                                */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdarg.h>
#include <string.h>

#define KILLA_CORE

#include "killa.h"

#include "kapi.h"
#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "kgc.h"
#include "kmem.h"
#include "kobject.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"
#include "kundump.h"
#include "kvm.h"



const char killa_ident[] =
  "$KillaVersion: " KILLA_COPYRIGHT " $"
  "$KillaAuthors: " KILLA_AUTHORS " $";


/* value at a non-valid index */
#define NONVALIDVALUE		killa_cast(killa_TValue *, killaO_nilobject)

/* corresponding test */
#define isvalid(o)	((o) != killaO_nilobject)

#define api_checkvalidindex(L, i)  killa_api_check(L, isvalid(i), "invalid index")


static killa_TValue *index2addr (killa_State *L, int idx) {
  killa_CallInfo *ci = L->ci;
  if (idx > 0) {
    killa_TValue *o = ci->func + idx;
    killa_api_check(L, idx <= ci->top - (ci->func + 1), "unacceptable index");
    if (o >= L->top) return NONVALIDVALUE;
    else return o;
  }
  else if (idx > KILLA_REGISTRYINDEX) {
    killa_api_check(L, idx != 0 && -idx <= L->top - (ci->func + 1), "invalid index");
    return L->top + idx;
  }
  else if (idx == KILLA_REGISTRYINDEX)
    return &KILLA_G(L)->l_registry;
  else {  /* upvalues */
    idx = KILLA_REGISTRYINDEX - idx;
    killa_api_check(L, idx <= KILLA_MAXUPVAL + 1, "upvalue index too large");
    if (killa_ttislcf(ci->func))  /* light C function? */
      return NONVALIDVALUE;  /* it has no upvalues */
    else {
      killa_CClosure *func = killa_clCvalue(ci->func);
      return (idx <= func->nupvalues) ? &func->upvalue[idx-1] : NONVALIDVALUE;
    }
  }
}


/*
** to be called by 'killa_checkstack' in protected mode, to grow stack
** capturing memory errors
*/
static void growstack (killa_State *L, void *ud) {
  int size = *(int *)ud;
  killaD_growstack(L, size);
}


KILLA_API int killa_checkstack (killa_State *L, int size) {
  int res;
  killa_CallInfo *ci = L->ci;
  killa_lock(L);
  if (L->stack_last - L->top > size)  /* stack large enough? */
    res = 1;  /* yes; check is OK */
  else {  /* no; need to grow stack */
    int inuse = killa_cast_int(L->top - L->stack) + KILLA_EXTRA_STACK;
    if (inuse > KILLAI_MAXSTACK - size)  /* can grow without overflow? */
      res = 0;  /* no */
    else  /* try to grow stack */
      res = (killaD_rawrunprotected(L, &growstack, &size) == KILLA_OK);
  }
  if (res && ci->top < L->top + size)
    ci->top = L->top + size;  /* adjust frame top */
  killa_unlock(L);
  return res;
}


KILLA_API void killa_xmove (killa_State *from, killa_State *to, int n) {
  int i;
  if (from == to) return;
  killa_lock(to);
  killaA_checknelems(from, n);
  killa_api_check(from, KILLA_G(from) == KILLA_G(to), "moving among independent states");
  killa_api_check(from, to->ci->top - to->top >= n, "not enough elements to move");
  from->top -= n;
  for (i = 0; i < n; i++) {
    killa_setobj2s(to, to->top++, from->top + i);
  }
  killa_unlock(to);
}


KILLA_API killa_CFunction killa_atpanic (killa_State *L, killa_CFunction panicf) {
  killa_CFunction old;
  killa_lock(L);
  old = KILLA_G(L)->panic;
  KILLA_G(L)->panic = panicf;
  killa_unlock(L);
  return old;
}


KILLA_API const killa_Number *killa_version (killa_State *L) {
  static const killa_Number version = KILLA_VERSION_NUM;
  if (L == NULL) return &version;
  else return KILLA_G(L)->version;
}



/*
** basic stack manipulation
*/


/*
** convert an acceptable stack index into an absolute index
*/
KILLA_API int killa_absindex (killa_State *L, int idx) {
  return (idx > 0 || idx <= KILLA_REGISTRYINDEX)
         ? idx
         : killa_cast_int(L->top - L->ci->func + idx);
}


KILLA_API int killa_gettop (killa_State *L) {
  return killa_cast_int(L->top - (L->ci->func + 1));
}


KILLA_API void killa_settop (killa_State *L, int idx) {
  killa_StkId func = L->ci->func;
  killa_lock(L);
  if (idx >= 0) {
    killa_api_check(L, idx <= L->stack_last - (func + 1), "new top too large");
    while (L->top < (func + 1) + idx)
      killa_setnilvalue(L->top++);
    L->top = (func + 1) + idx;
  }
  else {
    killa_api_check(L, -(idx+1) <= (L->top - (func + 1)), "invalid new top");
    L->top += idx+1;  /* `subtract' index (index is negative) */
  }
  killa_unlock(L);
}


KILLA_API void killa_remove (killa_State *L, int idx) {
  killa_StkId p;
  killa_lock(L);
  p = index2addr(L, idx);
  api_checkvalidindex(L, p);
  while (++p < L->top) killa_setobjs2s(L, p-1, p);
  L->top--;
  killa_unlock(L);
}


KILLA_API void killa_insert (killa_State *L, int idx) {
  killa_StkId p;
  killa_StkId q;
  killa_lock(L);
  p = index2addr(L, idx);
  api_checkvalidindex(L, p);
  for (q = L->top; q>p; q--) killa_setobjs2s(L, q, q-1);
  killa_setobjs2s(L, p, L->top);
  killa_unlock(L);
}


static void moveto (killa_State *L, killa_TValue *fr, int idx) {
  killa_TValue *to = index2addr(L, idx);
  api_checkvalidindex(L, to);
  killa_setobj(L, to, fr);
  if (idx < KILLA_REGISTRYINDEX)  /* function upvalue? */
    killaC_barrier(L, killa_clCvalue(L->ci->func), fr);
  /* KILLA_REGISTRYINDEX does not need gc barrier
     (collector revisits it before finishing collection) */
}


KILLA_API void killa_replace (killa_State *L, int idx) {
  killa_lock(L);
  killaA_checknelems(L, 1);
  moveto(L, L->top - 1, idx);
  L->top--;
  killa_unlock(L);
}


KILLA_API void killa_copy (killa_State *L, int fromidx, int toidx) {
  killa_TValue *fr;
  killa_lock(L);
  fr = index2addr(L, fromidx);
  api_checkvalidindex(L, fr);
  moveto(L, fr, toidx);
  killa_unlock(L);
}


KILLA_API void killa_pushvalue (killa_State *L, int idx) {
  killa_lock(L);
  killa_setobj2s(L, L->top, index2addr(L, idx));
  killaA_incr_top(L);
  killa_unlock(L);
}



/*
** access functions (stack -> C)
*/


KILLA_API int killa_type (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  return (isvalid(o) ? killa_ttypenv(o) : KILLA_TNONE);
}


KILLA_API const char *killa_typename (killa_State *L, int t) {
  KILLA_UNUSED(L);
  return killa_ttypename(t);
}


KILLA_API int killa_iscfunction (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  return (killa_ttislcf(o) || (killa_ttisCclosure(o)));
}


KILLA_API int killa_isnumber (killa_State *L, int idx) {
  killa_TValue n;
  const killa_TValue *o = index2addr(L, idx);
  return killa_vmtonumber(o, &n);
}


KILLA_API int killa_isstring (killa_State *L, int idx) {
  int t = killa_type(L, idx);
  return (t == KILLA_TSTRING || t == KILLA_TNUMBER);
}


KILLA_API int killa_isuserdata (killa_State *L, int idx) {
  const killa_TValue *o = index2addr(L, idx);
  return (killa_ttisuserdata(o) || killa_ttislightuserdata(o));
}


KILLA_API int killa_rawequal (killa_State *L, int index1, int index2) {
  killa_StkId o1 = index2addr(L, index1);
  killa_StkId o2 = index2addr(L, index2);
  return (isvalid(o1) && isvalid(o2)) ? killaV_rawequalobj(o1, o2) : 0;
}


KILLA_API void  killa_arith (killa_State *L, int op) {
  killa_StkId o1;  /* 1st operand */
  killa_StkId o2;  /* 2nd operand */
  killa_lock(L);
  if (op != KILLA_OPUNM) /* all other operations expect two operands */
    killaA_checknelems(L, 2);
  else {  /* for unary minus, add fake 2nd operand */
    killaA_checknelems(L, 1);
    killa_setobjs2s(L, L->top, L->top - 1);
    L->top++;
  }
  o1 = L->top - 2;
  o2 = L->top - 1;
  if (killa_ttisnumber(o1) && killa_ttisnumber(o2)) {
    killa_changenvalue(o1, killaO_arith(op, killa_nvalue(o1), killa_nvalue(o2)));
  }
  else
    killaV_arith(L, o1, o1, o2, killa_cast(KILLA_TMS, op - KILLA_OPADD + TM_ADD));
  L->top--;
  killa_unlock(L);
}


KILLA_API int killa_compare (killa_State *L, int index1, int index2, int op) {
  killa_StkId o1, o2;
  int i = 0;
  killa_lock(L);  /* may call tag method */
  o1 = index2addr(L, index1);
  o2 = index2addr(L, index2);
  if (isvalid(o1) && isvalid(o2)) {
    switch (op) {
      case KILLA_OPEQ: i = killa_equalobj(L, o1, o2); break;
      case KILLA_OPLT: i = killaV_lessthan(L, o1, o2); break;
      case KILLA_OPLE: i = killaV_lessequal(L, o1, o2); break;
      default: killa_api_check(L, 0, "invalid option");
    }
  }
  killa_unlock(L);
  return i;
}


KILLA_API killa_Number killa_tonumberx (killa_State *L, int idx, int *isnum) {
  killa_TValue n;
  const killa_TValue *o = index2addr(L, idx);
  if (killa_vmtonumber(o, &n)) {
    if (isnum) *isnum = 1;
    return killa_nvalue(o);
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}


KILLA_API killa_Integer killa_tointegerx (killa_State *L, int idx, int *isnum) {
  killa_TValue n;
  const killa_TValue *o = index2addr(L, idx);
  if (killa_vmtonumber(o, &n)) {
    killa_Integer res;
    killa_Number num = killa_nvalue(o);
    killa_number2integer(res, num);
    if (isnum) *isnum = 1;
    return res;
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}


KILLA_API killa_Unsigned killa_tounsignedx (killa_State *L, int idx, int *isnum) {
  killa_TValue n;
  const killa_TValue *o = index2addr(L, idx);
  if (killa_vmtonumber(o, &n)) {
    killa_Unsigned res;
    killa_Number num = killa_nvalue(o);
    killa_number2unsigned(res, num);
    if (isnum) *isnum = 1;
    return res;
  }
  else {
    if (isnum) *isnum = 0;
    return 0;
  }
}


KILLA_API int killa_toboolean (killa_State *L, int idx) {
  const killa_TValue *o = index2addr(L, idx);
  return !killa_isfalse(o);
}


KILLA_API const char *killa_tolstring (killa_State *L, int idx, size_t *len) {
  killa_StkId o = index2addr(L, idx);
  if (!killa_ttisstring(o)) {
    killa_lock(L);  /* `killaV_tostring' may create a new string */
    if (!killaV_tostring(L, o)) {  /* conversion failed? */
      if (len != NULL) *len = 0;
      killa_unlock(L);
      return NULL;
    }
    killaC_checkGC(L);
    o = index2addr(L, idx);  /* previous call may reallocate the stack */
    killa_unlock(L);
  }
  if (len != NULL) *len = killa_tsvalue(o)->len;
  return killa_svalue(o);
}


KILLA_API size_t killa_rawlen (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  switch (killa_ttypenv(o)) {
    case KILLA_TSTRING: return killa_tsvalue(o)->len;
    case KILLA_TUSERDATA: return killa_uvalue(o)->len;
    case KILLA_TTABLE: return killaH_getn(killa_hvalue(o));
    default: return 0;
  }
}


KILLA_API killa_CFunction killa_tocfunction (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  if (killa_ttislcf(o)) return killa_fvalue(o);
  else if (killa_ttisCclosure(o))
    return killa_clCvalue(o)->f;
  else return NULL;  /* not a C function */
}


KILLA_API void *killa_touserdata (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  switch (killa_ttypenv(o)) {
    case KILLA_TUSERDATA: return (killa_rawuvalue(o) + 1);
    case KILLA_TLIGHTUSERDATA: return killa_pvalue(o);
    default: return NULL;
  }
}


KILLA_API killa_State *killa_tothread (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  return (!killa_ttisthread(o)) ? NULL : killa_thvalue(o);
}


KILLA_API const void *killa_topointer (killa_State *L, int idx) {
  killa_StkId o = index2addr(L, idx);
  switch (killa_ttype(o)) {
    case KILLA_TTABLE: return killa_hvalue(o);
    case KILLA_TLCL: return killa_clLvalue(o);
    case KILLA_TCCL: return killa_clCvalue(o);
    case KILLA_TLCF: return killa_cast(void *, killa_cast(size_t, killa_fvalue(o)));
    case KILLA_TTHREAD: return killa_thvalue(o);
    case KILLA_TUSERDATA:
    case KILLA_TLIGHTUSERDATA:
      return killa_touserdata(L, idx);
    default: return NULL;
  }
}



/*
** push functions (C -> stack)
*/


KILLA_API void killa_pushnull (killa_State *L) {
  killa_lock(L);
  killa_setnilvalue(L->top);
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_pushnumber (killa_State *L, killa_Number n) {
  killa_lock(L);
  killa_setnvalue(L->top, n);
  killai_checknum(L, L->top,
    killaG_runerror(L, "C API - attempt to push a signaling NaN"));
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_pushinteger (killa_State *L, killa_Integer n) {
  killa_lock(L);
  killa_setnvalue(L->top, killa_cast_num(n));
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_pushunsigned (killa_State *L, killa_Unsigned u) {
  killa_Number n;
  killa_lock(L);
  n = killa_unsigned2number(u);
  killa_setnvalue(L->top, n);
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API const char *killa_pushlstring (killa_State *L, const char *s, size_t len) {
  killa_TString *ts;
  killa_lock(L);
  killaC_checkGC(L);
  ts = killaS_newlstr(L, s, len);
  killa_setsvalue2s(L, L->top, ts);
  killaA_incr_top(L);
  killa_unlock(L);
  return killa_getstr(ts);
}


KILLA_API const char *killa_pushstring (killa_State *L, const char *s) {
  if (s == NULL) {
    killa_pushnull(L);
    return NULL;
  }
  else {
    killa_TString *ts;
    killa_lock(L);
    killaC_checkGC(L);
    ts = killaS_new(L, s);
    killa_setsvalue2s(L, L->top, ts);
    killaA_incr_top(L);
    killa_unlock(L);
    return killa_getstr(ts);
  }
}


KILLA_API const char *killa_pushvfstring (killa_State *L, const char *fmt,
                                      va_list argp) {
  const char *ret;
  killa_lock(L);
  killaC_checkGC(L);
  ret = killaO_pushvfstring(L, fmt, argp);
  killa_unlock(L);
  return ret;
}


KILLA_API const char *killa_pushfstring (killa_State *L, const char *fmt, ...) {
  const char *ret;
  va_list argp;
  killa_lock(L);
  killaC_checkGC(L);
  va_start(argp, fmt);
  ret = killaO_pushvfstring(L, fmt, argp);
  va_end(argp);
  killa_unlock(L);
  return ret;
}


KILLA_API void killa_pushcclosure (killa_State *L, killa_CFunction fn, int n) {
  killa_lock(L);
  if (n == 0) {
    killa_setfvalue(L->top, fn);
  }
  else {
    killa_Closure *cl;
    killaA_checknelems(L, n);
    killa_api_check(L, n <= KILLA_MAXUPVAL, "upvalue index too large");
    killaC_checkGC(L);
    cl = killaF_newCclosure(L, n);
    cl->c.f = fn;
    L->top -= n;
    while (n--)
      killa_setobj2n(L, &cl->c.upvalue[n], L->top + n);
    killa_setclCvalue(L, L->top, cl);
  }
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_pushboolean (killa_State *L, int b) {
  killa_lock(L);
  killa_setbvalue(L->top, (b != 0));  /* ensure that true is 1 */
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_pushlightuserdata (killa_State *L, void *p) {
  killa_lock(L);
  killa_setpvalue(L->top, p);
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API int killa_pushthread (killa_State *L) {
  killa_lock(L);
  killa_setthvalue(L, L->top, L);
  killaA_incr_top(L);
  killa_unlock(L);
  return (KILLA_G(L)->mainthread == L);
}



/*
** get functions (Killa -> stack)
*/


KILLA_API void killa_getglobal (killa_State *L, const char *var) {
  killa_Table *reg = killa_hvalue(&KILLA_G(L)->l_registry);
  const killa_TValue *gt;  /* global table */
  killa_lock(L);
  gt = killaH_getint(reg, KILLA_RIDX_GLOBALS);
  killa_setsvalue2s(L, L->top++, killaS_new(L, var));
  killaV_gettable(L, gt, L->top - 1, L->top - 1);
  killa_unlock(L);
}


KILLA_API void killa_gettable (killa_State *L, int idx) {
  killa_StkId t;
  killa_lock(L);
  t = index2addr(L, idx);
  api_checkvalidindex(L, t);
  killaV_gettable(L, t, L->top - 1, L->top - 1);
  killa_unlock(L);
}


KILLA_API void killa_getfield (killa_State *L, int idx, const char *k) {
  killa_StkId t;
  killa_lock(L);
  t = index2addr(L, idx);
  api_checkvalidindex(L, t);
  killa_setsvalue2s(L, L->top, killaS_new(L, k));
  killaA_incr_top(L);
  killaV_gettable(L, t, L->top - 1, L->top - 1);
  killa_unlock(L);
}


KILLA_API void killa_rawget (killa_State *L, int idx) {
  killa_StkId t;
  killa_lock(L);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killa_setobj2s(L, L->top - 1, killaH_get(killa_hvalue(t), L->top - 1));
  killa_unlock(L);
}


KILLA_API void killa_rawgeti (killa_State *L, int idx, int n) {
  killa_StkId t;
  killa_lock(L);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killa_setobj2s(L, L->top, killaH_getint(killa_hvalue(t), n));
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_rawgetp (killa_State *L, int idx, const void *p) {
  killa_StkId t;
  killa_TValue k;
  killa_lock(L);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killa_setpvalue(&k, killa_cast(void *, p));
  killa_setobj2s(L, L->top, killaH_get(killa_hvalue(t), &k));
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API void killa_createtable (killa_State *L, int narray, int nrec) {
  killa_Table *t;
  killa_lock(L);
  killaC_checkGC(L);
  t = killaH_new(L);
  killa_sethvalue(L, L->top, t);
  killaA_incr_top(L);
  if (narray > 0 || nrec > 0)
    killaH_resize(L, t, narray, nrec);
  killa_unlock(L);
}


KILLA_API int killa_getmetatable (killa_State *L, int objindex) {
  const killa_TValue *obj;
  killa_Table *mt = NULL;
  int res;
  killa_lock(L);
  obj = index2addr(L, objindex);
  switch (killa_ttypenv(obj)) {
    case KILLA_TTABLE:
      mt = killa_hvalue(obj)->metatable;
      break;
    case KILLA_TUSERDATA:
      mt = killa_uvalue(obj)->metatable;
      break;
    default:
      mt = KILLA_G(L)->mt[killa_ttypenv(obj)];
      break;
  }
  if (mt == NULL)
    res = 0;
  else {
    killa_sethvalue(L, L->top, mt);
    killaA_incr_top(L);
    res = 1;
  }
  killa_unlock(L);
  return res;
}


KILLA_API void killa_getuservalue (killa_State *L, int idx) {
  killa_StkId o;
  killa_lock(L);
  o = index2addr(L, idx);
  api_checkvalidindex(L, o);
  killa_api_check(L, killa_ttisuserdata(o), "userdata expected");
  if (killa_uvalue(o)->env) {
    killa_sethvalue(L, L->top, killa_uvalue(o)->env);
  } else
    killa_setnilvalue(L->top);
  killaA_incr_top(L);
  killa_unlock(L);
}


/*
** set functions (stack -> Killa)
*/


KILLA_API void killa_setglobal (killa_State *L, const char *var) {
  killa_Table *reg = killa_hvalue(&KILLA_G(L)->l_registry);
  const killa_TValue *gt;  /* global table */
  killa_lock(L);
  killaA_checknelems(L, 1);
  gt = killaH_getint(reg, KILLA_RIDX_GLOBALS);
  killa_setsvalue2s(L, L->top++, killaS_new(L, var));
  killaV_settable(L, gt, L->top - 1, L->top - 2);
  L->top -= 2;  /* pop value and key */
  killa_unlock(L);
}


KILLA_API void killa_settable (killa_State *L, int idx) {
  killa_StkId t;
  killa_lock(L);
  killaA_checknelems(L, 2);
  t = index2addr(L, idx);
  api_checkvalidindex(L, t);
  killaV_settable(L, t, L->top - 2, L->top - 1);
  L->top -= 2;  /* pop index and value */
  killa_unlock(L);
}


KILLA_API void killa_setfield (killa_State *L, int idx, const char *k) {
  killa_StkId t;
  killa_lock(L);
  killaA_checknelems(L, 1);
  t = index2addr(L, idx);
  api_checkvalidindex(L, t);
  killa_setsvalue2s(L, L->top++, killaS_new(L, k));
  killaV_settable(L, t, L->top - 1, L->top - 2);
  L->top -= 2;  /* pop value and key */
  killa_unlock(L);
}


KILLA_API void killa_rawset (killa_State *L, int idx) {
  killa_StkId t;
  killa_lock(L);
  killaA_checknelems(L, 2);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killa_setobj2t(L, killaH_set(L, killa_hvalue(t), L->top-2), L->top-1);
  killa_invalidateTMcache(killa_hvalue(t));
  killaC_barrierback(L, killa_gcvalue(t), L->top-1);
  L->top -= 2;
  killa_unlock(L);
}


KILLA_API void killa_rawseti (killa_State *L, int idx, int n) {
  killa_StkId t;
  killa_lock(L);
  killaA_checknelems(L, 1);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killaH_setint(L, killa_hvalue(t), n, L->top - 1);
  killaC_barrierback(L, killa_gcvalue(t), L->top-1);
  L->top--;
  killa_unlock(L);
}


KILLA_API void killa_rawsetp (killa_State *L, int idx, const void *p) {
  killa_StkId t;
  killa_TValue k;
  killa_lock(L);
  killaA_checknelems(L, 1);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  killa_setpvalue(&k, killa_cast(void *, p));
  killa_setobj2t(L, killaH_set(L, killa_hvalue(t), &k), L->top - 1);
  killaC_barrierback(L, killa_gcvalue(t), L->top - 1);
  L->top--;
  killa_unlock(L);
}


KILLA_API int killa_setmetatable (killa_State *L, int objindex) {
  killa_TValue *obj;
  killa_Table *mt;
  killa_lock(L);
  killaA_checknelems(L, 1);
  obj = index2addr(L, objindex);
  api_checkvalidindex(L, obj);
  if (killa_ttisnil(L->top - 1))
    mt = NULL;
  else {
    killa_api_check(L, killa_ttistable(L->top - 1), "table expected");
    mt = killa_hvalue(L->top - 1);
  }
  switch (killa_ttypenv(obj)) {
    case KILLA_TTABLE: {
      killa_hvalue(obj)->metatable = mt;
      if (mt)
        killaC_objbarrierback(L, killa_gcvalue(obj), mt);
        killaC_checkfinalizer(L, killa_gcvalue(obj), mt);
      break;
    }
    case KILLA_TUSERDATA: {
      killa_uvalue(obj)->metatable = mt;
      if (mt) {
        killaC_objbarrier(L, killa_rawuvalue(obj), mt);
        killaC_checkfinalizer(L, killa_gcvalue(obj), mt);
      }
      break;
    }
    default: {
      KILLA_G(L)->mt[killa_ttypenv(obj)] = mt;
      break;
    }
  }
  L->top--;
  killa_unlock(L);
  return 1;
}


KILLA_API void killa_setuservalue (killa_State *L, int idx) {
  killa_StkId o;
  killa_lock(L);
  killaA_checknelems(L, 1);
  o = index2addr(L, idx);
  api_checkvalidindex(L, o);
  killa_api_check(L, killa_ttisuserdata(o), "userdata expected");
  if (killa_ttisnil(L->top - 1))
    killa_uvalue(o)->env = NULL;
  else {
    killa_api_check(L, killa_ttistable(L->top - 1), "table expected");
    killa_uvalue(o)->env = killa_hvalue(L->top - 1);
    killaC_objbarrier(L, killa_gcvalue(o), killa_hvalue(L->top - 1));
  }
  L->top--;
  killa_unlock(L);
}


/*
** `load' and `call' functions (run Killa code)
*/


#define checkresults(L,na,nr) \
     killa_api_check(L, (nr) == KILLA_MULTRET || (L->ci->top - L->top >= (nr) - (na)), \
	"results from function overflow current stack size")


KILLA_API int killa_getctx (killa_State *L, int *ctx) {
  if (L->ci->callstatus & KILLA_CIST_YIELDED) {
    if (ctx) *ctx = L->ci->u.c.ctx;
    return L->ci->u.c.status;
  }
  else return KILLA_OK;
}


KILLA_API void killa_callk (killa_State *L, int nargs, int nresults, int ctx,
                        killa_CFunction k) {
  killa_StkId func;
  killa_lock(L);
  killa_api_check(L, k == NULL || !killa_isKilla(L->ci),
    "cannot use continuations inside hooks");
  killaA_checknelems(L, nargs+1);
  killa_api_check(L, L->status == KILLA_OK, "cannot do calls on non-normal thread");
  checkresults(L, nargs, nresults);
  func = L->top - (nargs+1);
  if (k != NULL && L->nny == 0) {  /* need to prepare continuation? */
    L->ci->u.c.k = k;  /* save continuation */
    L->ci->u.c.ctx = ctx;  /* save context */
    killaD_call(L, func, nresults, 1);  /* do the call */
  }
  else  /* no continuation or no yieldable */
    killaD_call(L, func, nresults, 0);  /* just do the call */
  killaA_adjustresults(L, nresults);
  killa_unlock(L);
}



/*
** Execute a protected call.
*/
struct CallS {  /* data to `f_call' */
  killa_StkId func;
  int nresults;
};


static void f_call (killa_State *L, void *ud) {
  struct CallS *c = killa_cast(struct CallS *, ud);
  killaD_call(L, c->func, c->nresults, 0);
}



KILLA_API int killa_pcallk (killa_State *L, int nargs, int nresults, int errfunc,
                        int ctx, killa_CFunction k) {
  struct CallS c;
  int status;
  ptrdiff_t func;
  killa_lock(L);
  killa_api_check(L, k == NULL || !killa_isKilla(L->ci),
    "cannot use continuations inside hooks");
  killaA_checknelems(L, nargs+1);
  killa_api_check(L, L->status == KILLA_OK, "cannot do calls on non-normal thread");
  checkresults(L, nargs, nresults);
  if (errfunc == 0)
    func = 0;
  else {
    killa_StkId o = index2addr(L, errfunc);
    api_checkvalidindex(L, o);
    func = killa_savestack(L, o);
  }
  c.func = L->top - (nargs+1);  /* function to be called */
  if (k == NULL || L->nny > 0) {  /* no continuation or no yieldable? */
    c.nresults = nresults;  /* do a 'conventional' protected call */
    status = killaD_pcall(L, f_call, &c, killa_savestack(L, c.func), func);
  }
  else {  /* prepare continuation (call is already protected by 'resume') */
    killa_CallInfo *ci = L->ci;
    ci->u.c.k = k;  /* save continuation */
    ci->u.c.ctx = ctx;  /* save context */
    /* save information for error recovery */
    ci->u.c.extra = killa_savestack(L, c.func);
    ci->u.c.old_allowhook = L->allowhook;
    ci->u.c.old_errfunc = L->errfunc;
    L->errfunc = func;
    /* mark that function may do error recovery */
    ci->callstatus |= KILLA_CIST_YPCALL;
    killaD_call(L, c.func, nresults, 1);  /* do the call */
    ci->callstatus &= ~KILLA_CIST_YPCALL;
    L->errfunc = ci->u.c.old_errfunc;
    status = KILLA_OK;  /* if it is here, there were no errors */
  }
  killaA_adjustresults(L, nresults);
  killa_unlock(L);
  return status;
}


KILLA_API int killa_load (killa_State *L, killa_Reader reader, void *data,
                      const char *chunkname, const char *mode) {
  killa_ZIO z;
  int status;
  killa_lock(L);
  if (!chunkname) chunkname = "?";
  killaZ_init(L, &z, reader, data);
  status = killaD_protectedparser(L, &z, chunkname, mode);
  if (status == KILLA_OK) {  /* no errors? */
    killa_LClosure *f = killa_clLvalue(L->top - 1);  /* get newly created function */
    if (f->nupvalues == 1) {  /* does it have one upvalue? */
      /* get global table from registry */
      killa_Table *reg = killa_hvalue(&KILLA_G(L)->l_registry);
      const killa_TValue *gt = killaH_getint(reg, KILLA_RIDX_GLOBALS);
      /* set global table as 1st upvalue of 'f' (may be KILLA_ENV) */
      killa_setobj(L, f->upvals[0]->v, gt);
      killaC_barrier(L, f->upvals[0], gt);
    }
  }
  killa_unlock(L);
  return status;
}


KILLA_API int killa_dump (killa_State *L, killa_Writer writer, void *data) {
  int status;
  killa_TValue *o;
  killa_lock(L);
  killaA_checknelems(L, 1);
  o = L->top - 1;
  if (killa_isLfunction(o))
    status = killaU_dump(L, killa_getproto(o), writer, data, 0);
  else
    status = 1;
  killa_unlock(L);
  return status;
}


KILLA_API int  killa_status (killa_State *L) {
  return L->status;
}


/*
** Garbage-collection function
*/

KILLA_API int killa_gc (killa_State *L, int what, int data) {
  int res = 0;
  killa_GlobalState *g;
  killa_lock(L);
  g = KILLA_G(L);
  switch (what) {
    case KILLA_GCSTOP: {
      g->gcrunning = 0;
      break;
    }
    case KILLA_GCRESTART: {
      killaE_setdebt(g, 0);
      g->gcrunning = 1;
      break;
    }
    case KILLA_GCCOLLECT: {
      killaC_fullgc(L, 0);
      break;
    }
    case KILLA_GCCOUNT: {
      /* GC values are expressed in Kbytes: #bytes/2^10 */
      res = killa_cast_int(killa_gettotalbytes(g) >> 10);
      break;
    }
    case KILLA_GCCOUNTB: {
      res = killa_cast_int(killa_gettotalbytes(g) & 0x3ff);
      break;
    }
    case KILLA_GCSTEP: {
      if (g->gckind == KILLA_KGC_GEN) {  /* generational mode? */
        res = (g->lastmajormem == 0);  /* 1 if will do major collection */
        killaC_forcestep(L);  /* do a single step */
      }
      else {
        while (data-- >= 0) {
          killaC_forcestep(L);
          if (g->gcstate == killa_GCSpause) {  /* end of cycle? */
            res = 1;  /* signal it */
            break;
          }
        }
      }
      break;
    }
    case KILLA_GCSETPAUSE: {
      res = g->gcpause;
      g->gcpause = data;
      break;
    }
    case KILLA_GCSETMAJORINC: {
      res = g->gcmajorinc;
      g->gcmajorinc = data;
      break;
    }
    case KILLA_GCSETSTEPMUL: {
      res = g->gcstepmul;
      g->gcstepmul = data;
      break;
    }
    case KILLA_GCISRUNNING: {
      res = g->gcrunning;
      break;
    }
    case KILLA_GCGEN: {  /* change collector to generational mode */
      killaC_changemode(L, KILLA_KGC_GEN);
      break;
    }
    case KILLA_GCINC: {  /* change collector to incremental mode */
      killaC_changemode(L, KILLA_KGC_NORMAL);
      break;
    }
    default: res = -1;  /* invalid option */
  }
  killa_unlock(L);
  return res;
}



/*
** miscellaneous functions
*/


KILLA_API int killa_error (killa_State *L) {
  killa_lock(L);
  killaA_checknelems(L, 1);
  killaG_errormsg(L);
  killa_unlock(L);
  return 0;  /* to avoid warnings */
}


KILLA_API int killa_next (killa_State *L, int idx) {
  killa_StkId t;
  int more;
  killa_lock(L);
  t = index2addr(L, idx);
  killa_api_check(L, killa_ttistable(t), "table expected");
  more = killaH_next(L, killa_hvalue(t), L->top - 1);
  if (more) {
    killaA_incr_top(L);
  }
  else  /* no more elements */
    L->top -= 1;  /* remove key */
  killa_unlock(L);
  return more;
}


KILLA_API void killa_concat (killa_State *L, int n) {
  killa_lock(L);
  killaA_checknelems(L, n);
  if (n >= 2) {
    killaC_checkGC(L);
    killaV_concat(L, n);
  }
  else if (n == 0) {  /* push empty string */
    killa_setsvalue2s(L, L->top, killaS_newlstr(L, "", 0));
    killaA_incr_top(L);
  }
  /* else n == 1; nothing to do */
  killa_unlock(L);
}


KILLA_API void killa_len (killa_State *L, int idx) {
  killa_StkId t;
  killa_lock(L);
  t = index2addr(L, idx);
  killaV_objlen(L, L->top, t);
  killaA_incr_top(L);
  killa_unlock(L);
}


KILLA_API killa_Alloc killa_getallocf (killa_State *L, void **ud) {
  killa_Alloc f;
  killa_lock(L);
  if (ud) *ud = KILLA_G(L)->ud;
  f = KILLA_G(L)->frealloc;
  killa_unlock(L);
  return f;
}


KILLA_API void killa_setallocf (killa_State *L, killa_Alloc f, void *ud) {
  killa_lock(L);
  KILLA_G(L)->ud = ud;
  KILLA_G(L)->frealloc = f;
  killa_unlock(L);
}


KILLA_API void *killa_newuserdata (killa_State *L, size_t size) {
  killa_Udata *u;
  killa_lock(L);
  killaC_checkGC(L);
  u = killaS_newudata(L, size, NULL);
  killa_setuvalue(L, L->top, u);
  killaA_incr_top(L);
  killa_unlock(L);
  return u + 1;
}



static const char *aux_upvalue (killa_StkId fi, int n, killa_TValue **val,
                                killa_GCObject **owner) {
  switch (killa_ttype(fi)) {
    case KILLA_TCCL: {  /* C closure */
      killa_CClosure *f = killa_clCvalue(fi);
      if (!(1 <= n && n <= f->nupvalues)) return NULL;
      *val = &f->upvalue[n-1];
      if (owner) *owner = killa_obj2gco(f);
      return "";
    }
    case KILLA_TLCL: {  /* Killa closure */
      killa_LClosure *f = killa_clLvalue(fi);
      killa_TString *name;
      killa_Proto *p = f->p;
      if (!(1 <= n && n <= p->sizeupvalues)) return NULL;
      *val = f->upvals[n-1]->v;
      if (owner) *owner = killa_obj2gco(f->upvals[n - 1]);
      name = p->upvalues[n-1].name;
      return (name == NULL) ? "" : killa_getstr(name);
    }
    default: return NULL;  /* not a closure */
  }
}


KILLA_API const char *killa_getupvalue (killa_State *L, int funcindex, int n) {
  const char *name;
  killa_TValue *val = NULL;  /* to avoid warnings */
  killa_lock(L);
  name = aux_upvalue(index2addr(L, funcindex), n, &val, NULL);
  if (name) {
    killa_setobj2s(L, L->top, val);
    killaA_incr_top(L);
  }
  killa_unlock(L);
  return name;
}


KILLA_API const char *killa_setupvalue (killa_State *L, int funcindex, int n) {
  const char *name;
  killa_TValue *val = NULL;  /* to avoid warnings */
  killa_GCObject *owner = NULL;  /* to avoid warnings */
  killa_StkId fi;
  killa_lock(L);
  fi = index2addr(L, funcindex);
  killaA_checknelems(L, 1);
  name = aux_upvalue(fi, n, &val, &owner);
  if (name) {
    L->top--;
    killa_setobj(L, val, L->top);
    killaC_barrier(L, owner, L->top);
  }
  killa_unlock(L);
  return name;
}


static killa_UpVal **getupvalref (killa_State *L, int fidx, int n, killa_LClosure **pf) {
  killa_LClosure *f;
  killa_StkId fi = index2addr(L, fidx);
  killa_api_check(L, killa_ttisLclosure(fi), "Killa function expected");
  f = killa_clLvalue(fi);
  killa_api_check(L, (1 <= n && n <= f->p->sizeupvalues), "invalid upvalue index");
  if (pf) *pf = f;
  return &f->upvals[n - 1];  /* get its upvalue pointer */
}


KILLA_API void *killa_upvalueid (killa_State *L, int fidx, int n) {
  killa_StkId fi = index2addr(L, fidx);
  switch (killa_ttype(fi)) {
    case KILLA_TLCL: {  /* killa closure */
      return *getupvalref(L, fidx, n, NULL);
    }
    case KILLA_TCCL: {  /* C closure */
      killa_CClosure *f = killa_clCvalue(fi);
      killa_api_check(L, 1 <= n && n <= f->nupvalues, "invalid upvalue index");
      return &f->upvalue[n - 1];
    }
    default: {
      killa_api_check(L, 0, "closure expected");
      return NULL;
    }
  }
}


KILLA_API void killa_upvaluejoin (killa_State *L, int fidx1, int n1,
                                            int fidx2, int n2) {
  killa_LClosure *f1;
  killa_UpVal **up1 = getupvalref(L, fidx1, n1, &f1);
  killa_UpVal **up2 = getupvalref(L, fidx2, n2, NULL);
  *up1 = *up2;
  killaC_objbarrier(L, f1, *up2);
}

