/* ========================================================================== */
/*   Global State                                                             */
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

#include "kapi.h"
#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "kgc.h"
#include "klex.h"
#include "kmem.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"


#if !defined(KILLAI_GCPAUSE)
#define KILLAI_GCPAUSE	200  /* 200% */
#endif

#if !defined(KILLAI_GCMAJOR)
#define KILLAI_GCMAJOR	200  /* 200% */
#endif

#if !defined(KILLAI_GCMUL)
#define KILLAI_GCMUL	200 /* GC runs 'twice the speed' of memory allocation */
#endif


#define MEMERRMSG       "not enough memory"


/*
** thread state + extra space
*/
typedef struct LX {
#if defined(KILLAI_EXTRASPACE)
  char buff[KILLAI_EXTRASPACE];
#endif
  killa_State l;
} LX;


/*
** Main thread combines a thread state and the global state
*/
typedef struct LG {
  LX l;
  killa_GlobalState g;
} LG;



#define fromstate(L)	(killa_cast(LX *, killa_cast(killa_ubyte *, (L)) - offsetof(LX, l)))


/*
** set GCdebt to a new value keeping the value (totalbytes + GCdebt)
** invariant
*/
void killaE_setdebt (killa_GlobalState *g, killa_mem debt) {
  g->totalbytes -= (debt - g->GCdebt);
  g->GCdebt = debt;
}


killa_CallInfo *killaE_extendCI (killa_State *L) {
  killa_CallInfo *ci = killaM_new(L, killa_CallInfo);
  killa_assert(L->ci->next == NULL);
  L->ci->next = ci;
  ci->previous = L->ci;
  ci->next = NULL;
  return ci;
}


void killaE_freeCI (killa_State *L) {
  killa_CallInfo *ci = L->ci;
  killa_CallInfo *next = ci->next;
  ci->next = NULL;
  while ((ci = next) != NULL) {
    next = ci->next;
    killaM_free(L, ci);
  }
}


static void stack_init (killa_State *L1, killa_State *L) {
  int i; killa_CallInfo *ci;
  /* initialize stack array */
  L1->stack = killaM_newvector(L, KILLA_BASIC_STACK_SIZE, killa_TValue);
  L1->stacksize = KILLA_BASIC_STACK_SIZE;
  for (i = 0; i < KILLA_BASIC_STACK_SIZE; i++)
    killa_setnilvalue(L1->stack + i);  /* erase new stack */
  L1->top = L1->stack;
  L1->stack_last = L1->stack + L1->stacksize - KILLA_EXTRA_STACK;
  /* initialize first ci */
  ci = &L1->base_ci;
  ci->next = ci->previous = NULL;
  ci->callstatus = 0;
  ci->func = L1->top;
  killa_setnilvalue(L1->top++);  /* 'function' entry for this 'ci' */
  ci->top = L1->top + KILLA_MINSTACK;
  L1->ci = ci;
}


static void freestack (killa_State *L) {
  if (L->stack == NULL)
    return;  /* stack not completely built yet */
  L->ci = &L->base_ci;  /* free the entire 'ci' list */
  killaE_freeCI(L);
  killaM_freearray(L, L->stack, L->stacksize);  /* free stack array */
}


/*
** Create registry table and its predefined values
*/
static void init_registry (killa_State *L, killa_GlobalState *g) {
  killa_TValue mt;
  /* create registry */
  killa_Table *registry = killaH_new(L);
  killa_sethvalue(L, &g->l_registry, registry);
  killaH_resize(L, registry, KILLA_RIDX_SIZE, 0);
  /* registry[KILLA_RIDX_MAINTHREAD] = L */
  killa_setthvalue(L, &mt, L);
  killaH_setint(L, registry, KILLA_RIDX_MAINTHREAD, &mt);
  /* registry[KILLA_RIDX_GLOBALS] = table of globals */
  killa_sethvalue(L, &mt, killaH_new(L));
  killaH_setint(L, registry, KILLA_RIDX_GLOBALS, &mt);
}


/*
** open parts of the state that may cause memory-allocation errors
*/
static void f_killaopen (killa_State *L, void *ud) {
  killa_GlobalState *g = KILLA_G(L);
  KILLA_UNUSED(ud);
  stack_init(L, L);  /* init stack */
  init_registry(L, g);
  killaS_resize(L, KILLA_MINSTRTABSIZE);  /* initial size of string table */
  killaT_init(L);
  killaX_init(L);
  /* pre-create memory-error message */
  g->memerrmsg = killaS_newliteral(L, MEMERRMSG);
  killaS_fix(g->memerrmsg);  /* it should never be collected */
  g->gcrunning = 1;  /* allow gc */
}


/*
** preinitialize a state with consistent values without allocating
** any memory (to avoid errors)
*/
static void preinit_state (killa_State *L, killa_GlobalState *g) {
  KILLA_G(L) = g;
  L->stack = NULL;
  L->ci = NULL;
  L->stacksize = 0;
  L->errorJmp = NULL;
  L->nCcalls = 0;
  L->hook = NULL;
  L->hookmask = 0;
  L->basehookcount = 0;
  L->allowhook = 1;
  killa_resethookcount(L);
  L->openupval = NULL;
  L->nny = 1;
  L->status = KILLA_OK;
  L->errfunc = 0;
}


static void close_state (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  killaF_close(L, L->stack);  /* close all upvalues for this thread */
  killaC_freeallobjects(L);  /* collect all objects */
  killaM_freearray(L, KILLA_G(L)->strt.hash, KILLA_G(L)->strt.size);
  killaZ_freebuffer(L, &g->buff);
  freestack(L);
  killa_assert(killa_gettotalbytes(g) == sizeof(LG));
  (*g->frealloc)(g->ud, fromstate(L), sizeof(LG), 0);  /* free main block */
}


KILLA_API killa_State *killa_newthread (killa_State *L) {
  killa_State *L1;
  killa_lock(L);
  killaC_checkGC(L);
  L1 = &killaC_newobj(L, KILLA_TTHREAD, sizeof(LX), NULL, offsetof(LX, l))->th;
  killa_setthvalue(L, L->top, L1);
  killaA_incr_top(L);
  preinit_state(L1, KILLA_G(L));
  L1->hookmask = L->hookmask;
  L1->basehookcount = L->basehookcount;
  L1->hook = L->hook;
  killa_resethookcount(L1);
  killai_userstatethread(L, L1);
  stack_init(L1, L);  /* init stack */
  killa_unlock(L);
  return L1;
}


void killaE_freethread (killa_State *L, killa_State *L1) {
  LX *l = fromstate(L1);
  killaF_close(L1, L1->stack);  /* close all upvalues for this thread */
  killa_assert(L1->openupval == NULL);
  killai_userstatefree(L, L1);
  freestack(L1);
  killaM_free(L, l);
}


KILLA_API killa_State *killa_newstate (killa_Alloc f, void *ud) {
  int i;
  killa_State *L;
  killa_GlobalState *g;
  LG *l = killa_cast(LG *, (*f)(ud, NULL, KILLA_TTHREAD, sizeof(LG)));
  if (l == NULL) return NULL;
  L = &l->l.l;
  g = &l->g;
  L->next = NULL;
  L->tt = KILLA_TTHREAD;
  g->currentwhite = killa_bit2mask(KILLA_WHITE0BIT, KILLA_FIXEDBIT);
  L->marked = killaC_white(g);
  g->gckind = KILLA_KGC_NORMAL;
  preinit_state(L, g);
  g->frealloc = f;
  g->ud = ud;
  g->mainthread = L;
  g->uvhead.u.l.prev = &g->uvhead;
  g->uvhead.u.l.next = &g->uvhead;
  g->gcrunning = 0;  /* no GC while building state */
  g->lastmajormem = 0;
  g->strt.size = 0;
  g->strt.nuse = 0;
  g->strt.hash = NULL;
  killa_setnilvalue(&g->l_registry);
  killaZ_initbuffer(L, &g->buff);
  g->panic = NULL;
  g->version = killa_version(NULL);
  g->gcstate = killa_GCSpause;
  g->allgc = NULL;
  g->finobj = NULL;
  g->tobefnz = NULL;
  g->gray = g->grayagain = NULL;
  g->weak = g->ephemeron = g->allweak = NULL;
  g->totalbytes = sizeof(LG);
  g->GCdebt = 0;
  g->gcpause = KILLAI_GCPAUSE;
  g->gcmajorinc = KILLAI_GCMAJOR;
  g->gcstepmul = KILLAI_GCMUL;
  for (i=0; i < KILLA_NUMTAGS; i++) g->mt[i] = NULL;
  if (killaD_rawrunprotected(L, f_killaopen, NULL) != KILLA_OK) {
    /* memory allocation error: free partial state */
    close_state(L);
    L = NULL;
  }
  else
    killai_userstateopen(L);
  return L;
}


KILLA_API void killa_close (killa_State *L) {
  L = KILLA_G(L)->mainthread;  /* only the main thread can be closed */
  killa_lock(L);
  killai_userstateclose(L);
  close_state(L);
}


