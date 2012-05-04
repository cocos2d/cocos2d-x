/* ========================================================================== */
/*   Global State                                                             */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KSTATE_H_
#define KSTATE_H_

#include "killa.h"

#include "kobject.h"
#include "ktm.h"
#include "kzio.h"


/*

** Some notes about garbage-collected objects:  All objects in Killa must
** be kept somehow accessible until being freed.
**
** Killa keeps most objects linked in list g->allgc. The link uses field
** 'next' of the killa_CommonHeader.
**
** Strings are kept in several lists headed by the array g->strt.hash.
**
** Open upvalues are not subject to independent garbage collection. They
** are collected together with their respective threads. Killa keeps a
** double-linked list with all open upvalues (g->uvhead) so that it can
** mark objects referred by them. (They are always gray, so they must
** be remarked in the atomic step. Usually their contents would be marked
** when traversing the respective threads, but the thread may already be
** dead, while the upvalue is still accessible through closures.)
**
** Objects with finalizers are kept in the list g->finobj.
**
** The list g->tobefnz links all objects being finalized.

*/


struct killa_LongJmp;  /* defined in ldo.c */



/* extra stack space to handle TM calls and some other extras */
#define KILLA_EXTRA_STACK   5


#define KILLA_BASIC_STACK_SIZE  (2*KILLA_MINSTACK)


/* kinds of Garbage Collection */
#define KILLA_KGC_NORMAL        0
#define KILLA_KGC_EMERGENCY     1   /* gc was forced by an allocation failure */
#define KILLA_KGC_GEN           2   /* generational collection */


typedef struct killa_StringTable {
  killa_GCObject **hash;
  killa_uint32 nuse;  /* number of elements */
  int size;
} killa_StringTable;


/*
** information about a call
*/
typedef struct killa_CallInfo {
  killa_StkId func;  /* function index in the stack */
  killa_StkId top;  /* top for this function */
  struct killa_CallInfo *previous, *next;  /* dynamic call link */
  short nresults;  /* expected number of results from this function */
  killa_ubyte callstatus;
  union {
    struct {  /* only for Killa functions */
      killa_StkId base;  /* base for this function */
      const killa_Instruction *savedpc;
    } l;
    struct {  /* only for C functions */
      int ctx;  /* context info. in case of yields */
      killa_CFunction k;  /* continuation in case of yields */
      ptrdiff_t old_errfunc;
      ptrdiff_t extra;
      killa_ubyte old_allowhook;
      killa_ubyte status;
    } c;
  } u;
} killa_CallInfo;


/*
** Bits in killa_CallInfo status
*/
#define KILLA_CIST_KILLA    (1<<0)	/* call is running a Killa function */
#define KILLA_CIST_HOOKED   (1<<1)	/* call is running a debug hook */
#define KILLA_CIST_REENTRY  (1<<2)	/* call is running on same invocation of
                                       killaV_execute of previous call */
#define KILLA_CIST_YIELDED  (1<<3)  /* call reentered after suspension */
#define KILLA_CIST_YPCALL   (1<<4)  /* call is a yieldable protected call */
#define KILLA_CIST_STAT     (1<<5)  /* call has an error status (pcall) */
#define KILLA_CIST_TAIL     (1<<6)  /* call was tail called */


#define killa_isKilla(ci)   ((ci)->callstatus & KILLA_CIST_KILLA)


/*
** `global state', shared by all threads of this state
*/
typedef struct killa_GlobalState {
  killa_Alloc frealloc;  /* function to reallocate memory */
  void *ud;         /* auxiliary data to `frealloc' */
  killa_umem totalbytes;  /* number of bytes currently allocated - GCdebt */
  killa_mem GCdebt;  /* bytes allocated not yet compensated by the collector */
  killa_umem lastmajormem;  /* memory in use after last major collection */
  killa_StringTable strt;  /* hash table for strings */
  killa_TValue l_registry;
  killa_ubyte currentwhite;
  killa_ubyte gcstate;  /* state of garbage collector */
  killa_ubyte gckind;  /* kind of GC running */
  killa_ubyte gcrunning;  /* true if GC is running */
  int sweepstrgc;  /* position of sweep in `strt' */
  killa_GCObject *allgc;  /* list of all collectable objects */
  killa_GCObject *finobj;  /* list of collectable objects with finalizers */
  killa_GCObject **sweepgc;  /* current position of sweep */
  killa_GCObject *gray;  /* list of gray objects */
  killa_GCObject *grayagain;  /* list of objects to be traversed atomically */
  killa_GCObject *weak;  /* list of tables with weak values */
  killa_GCObject *ephemeron;  /* list of ephemeron tables (weak keys) */
  killa_GCObject *allweak;  /* list of all-weak tables */
  killa_GCObject *tobefnz;  /* list of userdata to be GC */
  killa_UpVal uvhead;  /* head of double-linked list of all open upvalues */
  killa_Mbuffer buff;  /* temporary buffer for string concatenation */
  int gcpause;  /* size of pause between successive GCs */
  int gcmajorinc;  /* how much to wait for a major GC (only in gen. mode) */
  int gcstepmul;  /* GC `granularity' */
  killa_CFunction panic;  /* to be called in unprotected errors */
  struct killa_State *mainthread;
  const killa_Number *version;  /* pointer to version number */
  killa_TString *memerrmsg;  /* memory-error message */
  killa_TString *tmname[TM_N];  /* array with tag-method names */
  struct killa_Table *mt[KILLA_NUMTAGS];  /* metatables for basic types */
} killa_GlobalState;


/*
** `per thread' state
*/
struct killa_State {
  killa_CommonHeader;
  killa_ubyte status;
  killa_StkId top;  /* first free slot in the stack */
  killa_GlobalState *l_G;
  killa_CallInfo *ci;  /* call info for current function */
  const killa_Instruction *oldpc;  /* last pc traced */
  killa_StkId stack_last;  /* last free slot in the stack */
  killa_StkId stack;  /* stack base */
  int stacksize;
  unsigned short nny;  /* number of non-yieldable calls in stack */
  unsigned short nCcalls;  /* number of nested C calls */
  killa_ubyte hookmask;
  killa_ubyte allowhook;
  int basehookcount;
  int hookcount;
  killa_Hook hook;
  killa_GCObject *openupval;  /* list of open upvalues in this stack */
  killa_GCObject *gclist;
  struct killa_LongJmp *errorJmp;  /* current error recover point */
  ptrdiff_t errfunc;  /* current error handling function (stack index) */
  killa_CallInfo base_ci;  /* killa_CallInfo for first level (C calling Killa) */
};


#define KILLA_G(L)	(L->l_G)


/*
** Union of all collectable objects
*/
union killa_GCObject {
  killa_GCheader gch;  /* common header */
  union killa_TString ts;
  union killa_Udata u;
  union killa_Closure cl;
  struct killa_Table h;
  struct killa_Proto p;
  struct killa_UpVal uv;
  struct killa_State th;  /* thread */
};


#define gch(o)        (&(o)->gch)

/* macros to convert a killa_GCObject into a specific value */
#define killa_rawgco2ts(o)	killa_check_exp((o)->gch.tt == KILLA_TSTRING, &((o)->ts))
#define killa_gco2ts(o)     (&killa_rawgco2ts(o)->tsv)
#define killa_rawgco2u(o)   killa_check_exp((o)->gch.tt == KILLA_TUSERDATA, &((o)->u))
#define killa_gco2u(o)      (&killa_rawgco2u(o)->uv)
#define killa_gco2cl(o)     killa_check_exp((o)->gch.tt == KILLA_TFUNCTION, &((o)->cl))
#define killa_gco2t(o)      killa_check_exp((o)->gch.tt == KILLA_TTABLE, &((o)->h))
#define killa_gco2p(o)      killa_check_exp((o)->gch.tt == KILLA_TPROTO, &((o)->p))
#define killa_gco2uv(o)     killa_check_exp((o)->gch.tt == KILLA_TUPVAL, &((o)->uv))
#define killa_gco2th(o)     killa_check_exp((o)->gch.tt == KILLA_TTHREAD, &((o)->th))

/* macro to convert any Killa object into a killa_GCObject */
#define killa_obj2gco(v)	(killa_cast(killa_GCObject *, (v)))


/* actual number of total bytes allocated */
#define killa_gettotalbytes(g)	((g)->totalbytes + (g)->GCdebt)

KILLAI_FUNC void killaE_setdebt (killa_GlobalState *g, killa_mem debt);
KILLAI_FUNC void killaE_freethread (killa_State *L, killa_State *L1);
KILLAI_FUNC killa_CallInfo *killaE_extendCI (killa_State *L);
KILLAI_FUNC void killaE_freeCI (killa_State *L);


#endif

