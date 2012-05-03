/* ========================================================================== */
/*   Stack and Call structure of Killa                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <setjmp.h>
#include <stdlib.h>
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
#include "kopcodes.h"
#include "kparser.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"
#include "kundump.h"
#include "kvm.h"
#include "kzio.h"




/*
** {======================================================
** Error-recovery functions
** =======================================================
*/

/*
** KILLAI_THROW/KILLAI_TRY define how Killa does exception handling. By
** default, Killa handles errors with exceptions when compiling as
** C++ code, with _longjmp/_setjmp when asked to use them, and with
** longjmp/setjmp otherwise.
*/
#if !defined(KILLAI_THROW)

#if defined(__cplusplus) && !defined(KILLA_USE_LONGJMP)
/* C++ exceptions */
#define KILLAI_THROW(L,c)		throw(c)
#define KILLAI_TRY(L,c,a) \
	try { a } catch(...) { if ((c)->status == 0) (c)->status = -1; }
#define killai_jmpbuf		int  /* dummy variable */

#elif defined(KILLA_USE_ULONGJMP)
/* in Unix, try _longjmp/_setjmp (more efficient) */
#define KILLAI_THROW(L,c)		_longjmp((c)->b, 1)
#define KILLAI_TRY(L,c,a)		if (_setjmp((c)->b) == 0) { a }
#define killai_jmpbuf		jmp_buf

#else
/* default handling with long jumps */
#define KILLAI_THROW(L,c)		longjmp((c)->b, 1)
#define KILLAI_TRY(L,c,a)		if (setjmp((c)->b) == 0) { a }
#define killai_jmpbuf		jmp_buf

#endif

#endif



/* chain list of long jump buffers */
struct killa_LongJmp {
  struct killa_LongJmp *previous;
  killai_jmpbuf b;
  volatile int status;  /* error code */
};


static void seterrorobj (killa_State *L, int errcode, killa_StkId oldtop) {
  switch (errcode) {
    case KILLA_ERRMEM: {  /* memory error? */
      killa_setsvalue2s(L, oldtop, KILLA_G(L)->memerrmsg); /* reuse preregistered msg. */
      break;
    }
    case KILLA_ERRERR: {
      killa_setsvalue2s(L, oldtop, killaS_newliteral(L, "error in error handling"));
      break;
    }
    default: {
      killa_setobjs2s(L, oldtop, L->top - 1);  /* error message on current top */
      break;
    }
  }
  L->top = oldtop + 1;
}


killa_noret killaD_throw (killa_State *L, int errcode) {
  if (L->errorJmp) {  /* thread has an error handler? */
    L->errorJmp->status = errcode;  /* set status */
    KILLAI_THROW(L, L->errorJmp);  /* jump to it */
  }
  else {  /* thread has no error handler */
    L->status = killa_cast_byte(errcode);  /* mark it as dead */
    if (KILLA_G(L)->mainthread->errorJmp) {  /* main thread has a handler? */
      killa_setobjs2s(L, KILLA_G(L)->mainthread->top++, L->top - 1);  /* copy error obj. */
      killaD_throw(KILLA_G(L)->mainthread, errcode);  /* re-throw in main thread */
    }
    else {  /* no handler at all; abort */
      if (KILLA_G(L)->panic) {  /* panic function? */
        killa_unlock(L);
        KILLA_G(L)->panic(L);  /* call it (last chance to jump out) */
      }
      abort();
    }
  }
}


int killaD_rawrunprotected (killa_State *L, Pfunc f, void *ud) {
  unsigned short oldnCcalls = L->nCcalls;
  struct killa_LongJmp lj;
  lj.status = KILLA_OK;
  lj.previous = L->errorJmp;  /* chain new error handler */
  L->errorJmp = &lj;
  KILLAI_TRY(L, &lj,
    (*f)(L, ud);
  );
  L->errorJmp = lj.previous;  /* restore old error handler */
  L->nCcalls = oldnCcalls;
  return lj.status;
}

/* }====================================================== */


static void correctstack (killa_State *L, killa_TValue *oldstack) {
  killa_CallInfo *ci;
  killa_GCObject *up;
  L->top = (L->top - oldstack) + L->stack;
  for (up = L->openupval; up != NULL; up = up->gch.next)
    killa_gco2uv(up)->v = (killa_gco2uv(up)->v - oldstack) + L->stack;
  for (ci = L->ci; ci != NULL; ci = ci->previous) {
    ci->top = (ci->top - oldstack) + L->stack;
    ci->func = (ci->func - oldstack) + L->stack;
    if (killa_isKilla(ci))
      ci->u.l.base = (ci->u.l.base - oldstack) + L->stack;
  }
}


/* some space for error handling */
#define ERRORSTACKSIZE	(KILLAI_MAXSTACK + 200)


void killaD_reallocstack (killa_State *L, int newsize) {
  killa_TValue *oldstack = L->stack;
  int lim = L->stacksize;
  killa_assert(newsize <= KILLAI_MAXSTACK || newsize == ERRORSTACKSIZE);
  killa_assert(L->stack_last - L->stack == L->stacksize - KILLA_EXTRA_STACK);
  killaM_reallocvector(L, L->stack, L->stacksize, newsize, killa_TValue);
  for (; lim < newsize; lim++)
    killa_setnilvalue(L->stack + lim); /* erase new segment */
  L->stacksize = newsize;
  L->stack_last = L->stack + newsize - KILLA_EXTRA_STACK;
  correctstack(L, oldstack);
}


void killaD_growstack (killa_State *L, int n) {
  int size = L->stacksize;
  if (size > KILLAI_MAXSTACK)  /* error after extra size? */
    killaD_throw(L, KILLA_ERRERR);
  else {
    int needed = killa_cast_int(L->top - L->stack) + n + KILLA_EXTRA_STACK;
    int newsize = 2 * size;
    if (newsize > KILLAI_MAXSTACK) newsize = KILLAI_MAXSTACK;
    if (newsize < needed) newsize = needed;
    if (newsize > KILLAI_MAXSTACK) {  /* stack overflow? */
      killaD_reallocstack(L, ERRORSTACKSIZE);
      killaG_runerror(L, "stack overflow");
    }
    else
      killaD_reallocstack(L, newsize);
  }
}


static int stackinuse (killa_State *L) {
  killa_CallInfo *ci;
  killa_StkId lim = L->top;
  for (ci = L->ci; ci != NULL; ci = ci->previous) {
    killa_assert(ci->top <= L->stack_last);
    if (lim < ci->top) lim = ci->top;
  }
  return killa_cast_int(lim - L->stack) + 1;  /* part of stack in use */
}


void killaD_shrinkstack (killa_State *L) {
  int inuse = stackinuse(L);
  int goodsize = inuse + (inuse / 8) + 2*KILLA_EXTRA_STACK;
  if (goodsize > KILLAI_MAXSTACK) goodsize = KILLAI_MAXSTACK;
  if (inuse > KILLAI_MAXSTACK ||  /* handling stack overflow? */
      goodsize >= L->stacksize)  /* would grow instead of shrink? */
    killa_condmovestack(L);  /* don't change stack (change only for debugging) */
  else
    killaD_reallocstack(L, goodsize);  /* shrink it */
}


void killaD_hook (killa_State *L, int event, int line) {
  killa_Hook hook = L->hook;
  if (hook && L->allowhook) {
    killa_CallInfo *ci = L->ci;
    ptrdiff_t top = killa_savestack(L, L->top);
    ptrdiff_t ci_top = killa_savestack(L, ci->top);
    killa_Debug ar;
    ar.event = event;
    ar.currentline = line;
    ar.i_ci = ci;
    killaD_checkstack(L, KILLA_MINSTACK);  /* ensure minimum stack size */
    ci->top = L->top + KILLA_MINSTACK;
    killa_assert(ci->top <= L->stack_last);
    L->allowhook = 0;  /* cannot call hooks inside a hook */
    ci->callstatus |= KILLA_CIST_HOOKED;
    killa_unlock(L);
    (*hook)(L, &ar);
    killa_lock(L);
    killa_assert(!L->allowhook);
    L->allowhook = 1;
    ci->top = killa_restorestack(L, ci_top);
    L->top = killa_restorestack(L, top);
    ci->callstatus &= ~KILLA_CIST_HOOKED;
  }
}


static void callhook (killa_State *L, killa_CallInfo *ci) {
  int hook = KILLA_HOOKCALL;
  ci->u.l.savedpc++;  /* hooks assume 'pc' is already incremented */
  if (killa_isKilla(ci->previous) &&
      KILLA_GET_OPCODE(*(ci->previous->u.l.savedpc - 1)) == OP_TAILCALL) {
    ci->callstatus |= KILLA_CIST_TAIL;
    hook = KILLA_HOOKTAILCALL;
  }
  killaD_hook(L, hook, -1);
  ci->u.l.savedpc--;  /* correct 'pc' */
}


static killa_StkId adjust_varargs (killa_State *L, killa_Proto *p, int actual) {
  int i;
  int nfixargs = p->numparams;
  killa_StkId base, fixed;
  killa_assert(actual >= nfixargs);
  /* move fixed parameters to final position */
  fixed = L->top - actual;  /* first fixed argument */
  base = L->top;  /* final position of first argument */
  for (i=0; i<nfixargs; i++) {
    killa_setobjs2s(L, L->top++, fixed + i);
    killa_setnilvalue(fixed + i);
  }
  return base;
}


static killa_StkId tryfuncTM (killa_State *L, killa_StkId func) {
  const killa_TValue *tm = killaT_gettmbyobj(L, func, TM_CALL);
  killa_StkId p;
  ptrdiff_t funcr = killa_savestack(L, func);
  if (!killa_ttisfunction(tm))
    killaG_typeerror(L, func, "call");
  /* Open a hole inside the stack at `func' */
  for (p = L->top; p > func; p--) killa_setobjs2s(L, p, p-1);
  killa_incr_top(L);
  func = killa_restorestack(L, funcr);  /* previous call may change stack */
  killa_setobj2s(L, func, tm);  /* tag method is the new function to be called */
  return func;
}



#define next_ci(L) (L->ci = (L->ci->next ? L->ci->next : killaE_extendCI(L)))


/*
** returns true if function has been executed (C function)
*/
int killaD_precall (killa_State *L, killa_StkId func, int nresults) {
  killa_CFunction f;
  killa_CallInfo *ci;
  int n;  /* number of arguments (Killa) or returns (C) */
  ptrdiff_t funcr = killa_savestack(L, func);
  switch (killa_ttype(func)) {
    case KILLA_TLCF:  /* light C function */
      f = killa_fvalue(func);
      goto Cfunc;
    case KILLA_TCCL: {  /* C closure */
      f = killa_clCvalue(func)->f;
     Cfunc:
      killaD_checkstack(L, KILLA_MINSTACK);  /* ensure minimum stack size */
      ci = next_ci(L);  /* now 'enter' new function */
      ci->nresults = nresults;
      ci->func = killa_restorestack(L, funcr);
      ci->top = L->top + KILLA_MINSTACK;
      killa_assert(ci->top <= L->stack_last);
      ci->callstatus = 0;
      if (L->hookmask & KILLA_MASKCALL)
        killaD_hook(L, KILLA_HOOKCALL, -1);
      killa_unlock(L);
      n = (*f)(L);  /* do the actual call */
      killa_lock(L);
      killaA_checknelems(L, n);
      killaD_poscall(L, L->top - n);
      return 1;
    }
    case KILLA_TLCL: {  /* Killa function: prepare its call */
      killa_StkId base;
      killa_Proto *p = killa_clLvalue(func)->p;
      killaD_checkstack(L, p->maxstacksize);
      func = killa_restorestack(L, funcr);
      n = killa_cast_int(L->top - func) - 1;  /* number of real arguments */
      for (; n < p->numparams; n++)
        killa_setnilvalue(L->top++);  /* complete missing arguments */
      base = (!p->is_vararg) ? func + 1 : adjust_varargs(L, p, n);
      ci = next_ci(L);  /* now 'enter' new function */
      ci->nresults = nresults;
      ci->func = func;
      ci->u.l.base = base;
      ci->top = base + p->maxstacksize;
      killa_assert(ci->top <= L->stack_last);
      ci->u.l.savedpc = p->code;  /* starting point */
      ci->callstatus = KILLA_CIST_KILLA;
      L->top = ci->top;
      if (L->hookmask & KILLA_MASKCALL)
        callhook(L, ci);
      return 0;
    }
    default: {  /* not a function */
      func = tryfuncTM(L, func);  /* retry with 'function' tag method */
      return killaD_precall(L, func, nresults);  /* now it must be a function */
    }
  }
}


int killaD_poscall (killa_State *L, killa_StkId firstResult) {
  killa_StkId res;
  int wanted, i;
  killa_CallInfo *ci = L->ci;
  if (L->hookmask & (KILLA_MASKRET | KILLA_MASKLINE)) {
    if (L->hookmask & KILLA_MASKRET) {
      ptrdiff_t fr = killa_savestack(L, firstResult);  /* hook may change stack */
      killaD_hook(L, KILLA_HOOKRET, -1);
      firstResult = killa_restorestack(L, fr);
    }
    L->oldpc = ci->previous->u.l.savedpc;  /* 'oldpc' for caller function */
  }
  res = ci->func;  /* res == final position of 1st result */
  wanted = ci->nresults;
  L->ci = ci = ci->previous;  /* back to caller */
  /* move results to correct place */
  for (i = wanted; i != 0 && firstResult < L->top; i--)
    killa_setobjs2s(L, res++, firstResult++);
  while (i-- > 0)
    killa_setnilvalue(res++);
  L->top = res;
  return (wanted - KILLA_MULTRET);  /* 0 iff wanted == KILLA_MULTRET */
}


/*
** Call a function (C or Killa). The function to be called is at *func.
** The arguments are on the stack, right after the function.
** When returns, all the results are on the stack, starting at the original
** function position.
*/
void killaD_call (killa_State *L, killa_StkId func, int nResults, int allowyield) {
  if (++L->nCcalls >= KILLAI_MAXCCALLS) {
    if (L->nCcalls == KILLAI_MAXCCALLS)
      killaG_runerror(L, "C stack overflow");
    else if (L->nCcalls >= (KILLAI_MAXCCALLS + (KILLAI_MAXCCALLS>>3)))
      killaD_throw(L, KILLA_ERRERR);  /* error while handing stack error */
  }
  if (!allowyield) L->nny++;
  if (!killaD_precall(L, func, nResults))  /* is a Killa function? */
    killaV_execute(L);  /* call it */
  if (!allowyield) L->nny--;
  L->nCcalls--;
  killaC_checkGC(L);
}


static void finishCcall (killa_State *L) {
  killa_CallInfo *ci = L->ci;
  int n;
  killa_assert(ci->u.c.k != NULL);  /* must have a continuation */
  killa_assert(L->nny == 0);
  /* finish 'killaD_call' */
  L->nCcalls--;
  /* finish 'killa_callk' */
  killaA_adjustresults(L, ci->nresults);
  /* call continuation function */
  if (!(ci->callstatus & KILLA_CIST_STAT))  /* no call status? */
    ci->u.c.status = KILLA_YIELD;  /* 'default' status */
  killa_assert(ci->u.c.status != KILLA_OK);
  ci->callstatus = (ci->callstatus & ~(KILLA_CIST_YPCALL | KILLA_CIST_STAT)) | KILLA_CIST_YIELDED;
  killa_unlock(L);
  n = (*ci->u.c.k)(L);
  killa_lock(L);
  killaA_checknelems(L, n);
  /* finish 'killaD_precall' */
  killaD_poscall(L, L->top - n);
}


static void unroll (killa_State *L, void *ud) {
  KILLA_UNUSED(ud);
  for (;;) {
    if (L->ci == &L->base_ci)  /* stack is empty? */
      return;  /* coroutine finished normally */
    if (!killa_isKilla(L->ci))  /* C function? */
      finishCcall(L);
    else {  /* Killa function */
      killaV_finishOp(L);  /* finish interrupted instruction */
      killaV_execute(L);  /* execute down to higher C 'boundary' */
    }
  }
}


/*
** check whether thread has a suspended protected call
*/
static killa_CallInfo *findpcall (killa_State *L) {
  killa_CallInfo *ci;
  for (ci = L->ci; ci != NULL; ci = ci->previous) {  /* search for a pcall */
    if (ci->callstatus & KILLA_CIST_YPCALL)
      return ci;
  }
  return NULL;  /* no pending pcall */
}


static int recover (killa_State *L, int status) {
  killa_StkId oldtop;
  killa_CallInfo *ci = findpcall(L);
  if (ci == NULL) return 0;  /* no recovery point */
  /* "finish" killaD_pcall */
  oldtop = killa_restorestack(L, ci->u.c.extra);
  killaF_close(L, oldtop);
  seterrorobj(L, status, oldtop);
  L->ci = ci;
  L->allowhook = ci->u.c.old_allowhook;
  L->nny = 0;  /* should be zero to be yieldable */
  killaD_shrinkstack(L);
  L->errfunc = ci->u.c.old_errfunc;
  ci->callstatus |= KILLA_CIST_STAT;  /* call has error status */
  ci->u.c.status = status;  /* (here it is) */
  return 1;  /* continue running the coroutine */
}


/*
** signal an error in the call to 'resume', not in the execution of the
** coroutine itself. (Such errors should not be handled by any coroutine
** error handler and should not kill the coroutine.)
*/
static killa_noret resume_error (killa_State *L, const char *msg, killa_StkId firstArg) {
  L->top = firstArg;  /* remove args from the stack */
  killa_setsvalue2s(L, L->top, killaS_new(L, msg));  /* push error message */
  killa_incr_top(L);
  killaD_throw(L, -1);  /* jump back to 'killa_resume' */
}


/*
** do the work for 'killa_resume' in protected mode
*/
static void resume (killa_State *L, void *ud) {
  killa_StkId firstArg = killa_cast(killa_StkId, ud);
  killa_CallInfo *ci = L->ci;
  if (L->nCcalls >= KILLAI_MAXCCALLS)
    resume_error(L, "C stack overflow", firstArg);
  if (L->status == KILLA_OK) {  /* may be starting a coroutine */
    if (ci != &L->base_ci)  /* not in base level? */
      resume_error(L, "cannot resume non-suspended coroutine", firstArg);
    /* coroutine is in base level; start running it */
    if (!killaD_precall(L, firstArg - 1, KILLA_MULTRET))  /* Killa function? */
      killaV_execute(L);  /* call it */
  }
  else if (L->status != KILLA_YIELD)
    resume_error(L, "cannot resume dead coroutine", firstArg);
  else {  /* resuming from previous yield */
    L->status = KILLA_OK;
    if (killa_isKilla(ci))  /* yielded inside a hook? */
      killaV_execute(L);  /* just continue running Killa code */
    else {  /* 'common' yield */
      ci->func = killa_restorestack(L, ci->u.c.extra);
      if (ci->u.c.k != NULL) {  /* does it have a continuation? */
        int n;
        ci->u.c.status = KILLA_YIELD;  /* 'default' status */
        ci->callstatus |= KILLA_CIST_YIELDED;
        killa_unlock(L);
        n = (*ci->u.c.k)(L);  /* call continuation */
        killa_lock(L);
        killaA_checknelems(L, n);
        firstArg = L->top - n;  /* yield results come from continuation */
      }
      L->nCcalls--;  /* finish 'killaD_call' */
      killaD_poscall(L, firstArg);  /* finish 'killaD_precall' */
    }
    unroll(L, NULL);
  }
}


KILLA_API int killa_resume (killa_State *L, killa_State *from, int nargs) {
  int status;
  killa_lock(L);
  killai_userstateresume(L, nargs);
  L->nCcalls = (from) ? from->nCcalls + 1 : 1;
  L->nny = 0;  /* allow yields */
  killaA_checknelems(L, (L->status == KILLA_OK) ? nargs + 1 : nargs);
  status = killaD_rawrunprotected(L, resume, L->top - nargs);
  if (status == -1)  /* error calling 'killa_resume'? */
    status = KILLA_ERRRUN;
  else {  /* yield or regular error */
    while (status != KILLA_OK && status != KILLA_YIELD) {  /* error? */
      if (recover(L, status))  /* recover point? */
        status = killaD_rawrunprotected(L, unroll, NULL);  /* run continuation */
      else {  /* unrecoverable error */
        L->status = killa_cast_byte(status);  /* mark thread as `dead' */
        seterrorobj(L, status, L->top);
        L->ci->top = L->top;
        break;
      }
    }
    killa_assert(status == L->status);
  }
  L->nny = 1;  /* do not allow yields */
  L->nCcalls--;
  killa_assert(L->nCcalls == ((from) ? from->nCcalls : 0));
  killa_unlock(L);
  return status;
}


KILLA_API int killa_yieldk (killa_State *L, int nresults, int ctx, killa_CFunction k) {
  killa_CallInfo *ci = L->ci;
  killai_userstateyield(L, nresults);
  killa_lock(L);
  killaA_checknelems(L, nresults);
  if (L->nny > 0) {
    if (L != KILLA_G(L)->mainthread)
      killaG_runerror(L, "attempt to yield across metamethod/C-call boundary");
    else
      killaG_runerror(L, "attempt to yield from outside a coroutine");
  }
  L->status = KILLA_YIELD;
  if (killa_isKilla(ci)) {  /* inside a hook? */
    killa_api_check(L, k == NULL, "hooks cannot continue after yielding");
  }
  else {
    if ((ci->u.c.k = k) != NULL)  /* is there a continuation? */
      ci->u.c.ctx = ctx;  /* save context */
    ci->u.c.extra = killa_savestack(L, ci->func);  /* save current 'func' */
    ci->func = L->top - nresults - 1;  /* protect stack below results */
    killaD_throw(L, KILLA_YIELD);
  }
  killa_assert(ci->callstatus & KILLA_CIST_HOOKED);  /* must be inside a hook */
  killa_unlock(L);
  return 0;  /* return to 'killaD_hook' */
}


int killaD_pcall (killa_State *L, Pfunc func, void *u,
                ptrdiff_t old_top, ptrdiff_t ef) {
  int status;
  killa_CallInfo *old_ci = L->ci;
  killa_ubyte old_allowhooks = L->allowhook;
  unsigned short old_nny = L->nny;
  ptrdiff_t old_errfunc = L->errfunc;
  L->errfunc = ef;
  status = killaD_rawrunprotected(L, func, u);
  if (status != KILLA_OK) {  /* an error occurred? */
    killa_StkId oldtop = killa_restorestack(L, old_top);
    killaF_close(L, oldtop);  /* close possible pending closures */
    seterrorobj(L, status, oldtop);
    L->ci = old_ci;
    L->allowhook = old_allowhooks;
    L->nny = old_nny;
    killaD_shrinkstack(L);
  }
  L->errfunc = old_errfunc;
  return status;
}



/*
** Execute a protected parser.
*/
struct SParser {  /* data to `f_parser' */
  killa_ZIO *z;
  killa_Mbuffer buff;  /* dynamic structure used by the scanner */
  killa_Dyndata dyd;  /* dynamic structures used by the parser */
  const char *mode;
  const char *name;
};


static void checkmode (killa_State *L, const char *mode, const char *x) {
  if (mode && strchr(mode, x[0]) == NULL) {
    killaO_pushfstring(L,
       "attempt to load a %s chunk (mode is " KILLA_QS ")", x, mode);
    killaD_throw(L, KILLA_ERRSYNTAX);
  }
}


static void f_parser (killa_State *L, void *ud) {
  int i;
  killa_Proto *tf;
  killa_Closure *cl;
  struct SParser *p = killa_cast(struct SParser *, ud);
  int c = killa_zgetc(p->z);  /* read first character */
  if (c == KILLA_SIGNATURE[0]) {
    checkmode(L, p->mode, "binary");
    tf = killaU_undump(L, p->z, &p->buff, p->name);
  }
  else {
    checkmode(L, p->mode, "text");
    tf = killaY_parser(L, p->z, &p->buff, &p->dyd, p->name, c);
  }
  killa_setptvalue2s(L, L->top, tf);
  killa_incr_top(L);
  cl = killaF_newLclosure(L, tf);
  killa_setclLvalue(L, L->top - 1, cl);
  for (i = 0; i < tf->sizeupvalues; i++)  /* initialize upvalues */
    cl->l.upvals[i] = killaF_newupval(L);
}


int killaD_protectedparser (killa_State *L, killa_ZIO *z, const char *name,
                                        const char *mode) {
  struct SParser p;
  int status;
  L->nny++;  /* cannot yield during parsing */
  p.z = z; p.name = name; p.mode = mode;
  p.dyd.actvar.arr = NULL; p.dyd.actvar.size = 0;
  p.dyd.gt.arr = NULL; p.dyd.gt.size = 0;
  p.dyd.label.arr = NULL; p.dyd.label.size = 0;
  killaZ_initbuffer(L, &p.buff);
  status = killaD_pcall(L, f_parser, &p, killa_savestack(L, L->top), L->errfunc);
  killaZ_freebuffer(L, &p.buff);
  killaM_freearray(L, p.dyd.actvar.arr, p.dyd.actvar.size);
  killaM_freearray(L, p.dyd.gt.arr, p.dyd.gt.size);
  killaM_freearray(L, p.dyd.label.arr, p.dyd.label.size);
  L->nny--;
  return status;
}


