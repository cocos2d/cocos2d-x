/* ========================================================================== */
/*   Garbage Collector                                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <string.h>

#define KILLA_CORE

#include "killa.h"

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



/* how much to allocate before next GC step */
#define GCSTEPSIZE	1024

/* maximum number of elements to sweep in each single step */
#define GCSWEEPMAX	40

/* cost of sweeping one element */
#define GCSWEEPCOST	1

/* maximum number of finalizers to call in each GC step */
#define GCFINALIZENUM	4

/* cost of marking the root set */
#define GCROOTCOST	10

/* cost of atomic step */
#define GCATOMICCOST	1000

/* basic cost to traverse one object (to be added to the links the
   object may have) */
#define TRAVCOST	5


/*
** standard negative debt for GC; a reasonable "time" to wait before
** starting a new cycle
*/
#define stddebt(g)	(-killa_cast(killa_mem, killa_gettotalbytes(g)/100) * g->gcpause)


/*
** 'makewhite' erases all color bits plus the old bit and then
** sets only the current white bit
*/
#define maskcolors	(~(killa_bit2mask(KILLA_BLACKBIT, KILLA_OLDBIT) | KILLA_WHITEBITS))
#define makewhite(g,x)	\
 (gch(x)->marked = killa_cast_byte((gch(x)->marked & maskcolors) | killaC_white(g)))

#define white2gray(x)	killa_resetbits(gch(x)->marked, KILLA_WHITEBITS)
#define black2gray(x)	killa_resetbit(gch(x)->marked, KILLA_BLACKBIT)

#define stringmark(s)	((void)((s) && killa_resetbits((s)->tsv.marked, KILLA_WHITEBITS)))


#define isfinalized(x)		killa_testbit(gch(x)->marked, KILLA_FINALIZEDBIT)

#define checkdeadkey(n)	killa_assert(!killa_ttisdeadkey(killa_gkey(n)) || killa_ttisnil(killa_gval(n)))


#define checkconsistency(obj)  \
  killa_longassert(!killa_iscollectable(obj) || killa_righttt(obj))


#define markvalue(g,o) { checkconsistency(o); \
  if (killa_valiswhite(o)) reallymarkobject(g,killa_gcvalue(o)); }

#define markobject(g,t) { if ((t) && killa_iswhite(killa_obj2gco(t))) \
		reallymarkobject(g, killa_obj2gco(t)); }

static void reallymarkobject (killa_GlobalState *g, killa_GCObject *o);


/*
** {======================================================
** Generic functions
** =======================================================
*/


/*
** one after last element in a hash array
*/
#define gnodelast(h)	killa_gnode(h, killa_cast(size_t, killa_sizenode(h)))


/*
** link table 'h' into list pointed by 'p'
*/
#define linktable(h,p)	((h)->gclist = *(p), *(p) = killa_obj2gco(h))


/*
** if key is not marked, mark its entry as dead (therefore removing it
** from the table)
*/
static void removeentry (killa_Node *n) {
  killa_assert(killa_ttisnil(killa_gval(n)));
  if (killa_valiswhite(killa_gkey(n)))
    killa_setdeadvalue(killa_gkey(n));  /* unused and unmarked key; remove it */
}


/*
** tells whether a key or value can be cleared from a weak
** table. Non-collectable objects are never removed from weak
** tables. Strings behave as `values', so are never removed too. for
** other objects: if really collected, cannot keep them; for objects
** being finalized, keep them in keys, but not in values
*/
static int iscleared (const killa_TValue *o) {
  if (!killa_iscollectable(o)) return 0;
  else if (killa_ttisstring(o)) {
    stringmark(killa_rawtsvalue(o));  /* strings are `values', so are never weak */
    return 0;
  }
  else return killa_iswhite(killa_gcvalue(o));
}


/*
** barrier that moves collector forward, that is, mark the white object
** being pointed by a black object.
*/
void killaC_barrier_ (killa_State *L, killa_GCObject *o, killa_GCObject *v) {
  killa_GlobalState *g = KILLA_G(L);
  killa_assert(killa_isblack(o) && killa_iswhite(v) && !killa_isdead(g, v) && !killa_isdead(g, o));
  killa_assert(killa_isgenerational(g) || g->gcstate != killa_GCSpause);
  killa_assert(gch(o)->tt != KILLA_TTABLE);
  if (killa_keepinvariant(g))  /* must keep invariant? */
    reallymarkobject(g, v);  /* restore invariant */
  else {  /* sweep phase */
    killa_assert(killa_issweepphase(g));
    makewhite(g, o);  /* mark main obj. as white to avoid other barriers */
  }
}


/*
** barrier that moves collector backward, that is, mark the black object
** pointing to a white object as gray again. (Current implementation
** only works for tables; access to 'gclist' is not uniform across
** different types.)
*/
void killaC_barrierback_ (killa_State *L, killa_GCObject *o) {
  killa_GlobalState *g = KILLA_G(L);
  killa_assert(killa_isblack(o) && !killa_isdead(g, o) && gch(o)->tt == KILLA_TTABLE);
  black2gray(o);  /* make object gray (again) */
  killa_gco2t(o)->gclist = g->grayagain;
  g->grayagain = o;
}


/*
** barrier for prototypes. When creating first closure (cache is
** NULL), use a forward barrier; this may be the only closure of the
** prototype (if it is a "regular" function, with a single instance)
** and the prototype may be big, so it is better to avoid traversing
** it again. Otherwise, use a backward barrier, to avoid marking all
** possible instances.
*/
KILLAI_FUNC void killaC_barrierproto_ (killa_State *L, killa_Proto *p, killa_Closure *c) {
  killa_GlobalState *g = KILLA_G(L);
  killa_assert(killa_isblack(killa_obj2gco(p)));
  if (p->cache == NULL) {  /* first time? */
    killaC_objbarrier(L, p, c);
  }
  else {  /* use a backward barrier */
    black2gray(killa_obj2gco(p));  /* make prototype gray (again) */
    p->gclist = g->grayagain;
    g->grayagain = killa_obj2gco(p);
  }
}


/*
** check color (and invariants) for an upvalue that was closed,
** i.e., moved into the 'allgc' list
*/
void killaC_checkupvalcolor (killa_GlobalState *g, killa_UpVal *uv) {
  killa_GCObject *o = killa_obj2gco(uv);
  killa_assert(!killa_isblack(o));  /* open upvalues are never black */
  if (killa_isgray(o)) {
    if (killa_keepinvariant(g)) {
      killa_resetoldbit(o);  /* see MOVE OLD rule */
      killa_gray2black(o);  /* it is being visited now */
      markvalue(g, uv->v);
    }
    else {
      killa_assert(killa_issweepphase(g));
      makewhite(g, o);
    }
  }
}


/*
** create a new collectable object (with given type and size) and link
** it to '*list'. 'offset' tells how many bytes to allocate before the
** object itself (used only by states).
*/
killa_GCObject *killaC_newobj (killa_State *L, int tt, size_t sz, killa_GCObject **list,
                       int offset) {
  killa_GlobalState *g = KILLA_G(L);
  killa_GCObject *o = killa_obj2gco(killa_cast(char *, killaM_newobject(L, tt, sz)) + offset);
  if (list == NULL)
    list = &g->allgc;  /* standard list for collectable objects */
  gch(o)->marked = killaC_white(g);
  gch(o)->tt = tt;
  gch(o)->next = *list;
  *list = o;
  return o;
}

/* }====================================================== */



/*
** {======================================================
** Mark functions
** =======================================================
*/


/*
** mark an object. Userdata and closed upvalues are visited and turned
** black here. Strings remain gray (it is the same as making them
** black). Other objects are marked gray and added to appropriate list
** to be visited (and turned black) later. (Open upvalues are already
** linked in 'headuv' list.)
*/
static void reallymarkobject (killa_GlobalState *g, killa_GCObject *o) {
  killa_assert(killa_iswhite(o) && !killa_isdead(g, o));
  white2gray(o);
  switch (gch(o)->tt) {
    case KILLA_TSTRING: {
      return;  /* for strings, gray is as good as black */
    }
    case KILLA_TUSERDATA: {
      killa_Table *mt = killa_gco2u(o)->metatable;
      markobject(g, mt);
      markobject(g, killa_gco2u(o)->env);
      killa_gray2black(o);  /* all pointers marked */
      return;
    }
    case KILLA_TUPVAL: {
      killa_UpVal *uv = killa_gco2uv(o);
      markvalue(g, uv->v);
      if (uv->v == &uv->u.value)  /* closed? (open upvalues remain gray) */
        killa_gray2black(o);  /* make it black */
      return;
    }
    case KILLA_TFUNCTION: {
      killa_gco2cl(o)->c.gclist = g->gray;
      g->gray = o;
      break;
    }
    case KILLA_TTABLE: {
      linktable(killa_gco2t(o), &g->gray);
      break;
    }
    case KILLA_TTHREAD: {
      killa_gco2th(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    case KILLA_TPROTO: {
      killa_gco2p(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    default: killa_assert(0);
  }
}


/*
** mark metamethods for basic types
*/
static void markmt (killa_GlobalState *g) {
  int i;
  for (i=0; i < KILLA_NUMTAGS; i++)
    markobject(g, g->mt[i]);
}


/*
** mark all objects in list of being-finalized
*/
static void markbeingfnz (killa_GlobalState *g) {
  killa_GCObject *o;
  for (o = g->tobefnz; o != NULL; o = gch(o)->next) {
    makewhite(g, o);
    reallymarkobject(g, o);
  }
}


/*
** mark all values stored in marked open upvalues. (See comment in
** 'lstate.h'.)
*/
static void remarkupvals (killa_GlobalState *g) {
  killa_UpVal *uv;
  for (uv = g->uvhead.u.l.next; uv != &g->uvhead; uv = uv->u.l.next) {
    if (killa_isgray(killa_obj2gco(uv)))
      markvalue(g, uv->v);
  }
}


/*
** mark root set and reset all gray lists, to start a new
** incremental (or full) collection
*/
static void markroot (killa_GlobalState *g) {
  g->gray = g->grayagain = NULL;
  g->weak = g->allweak = g->ephemeron = NULL;
  markobject(g, g->mainthread);
  markvalue(g, &g->l_registry);
  markmt(g);
  markbeingfnz(g);  /* mark any finalizing object left from previous cycle */
}

/* }====================================================== */


/*
** {======================================================
** Traverse functions
** =======================================================
*/

static void traverseweakvalue (killa_GlobalState *g, killa_Table *h) {
  killa_Node *n, *limit = gnodelast(h);
  /* if there is array part, assume it may have white values (do not
     traverse it just to check) */
  int hasclears = (h->sizearray > 0);
  for (n = killa_gnode(h, 0); n < limit; n++) {
    checkdeadkey(n);
    if (killa_ttisnil(killa_gval(n)))  /* entry is empty? */
      removeentry(n);  /* remove it */
    else {
      killa_assert(!killa_ttisnil(killa_gkey(n)));
      markvalue(g, killa_gkey(n));  /* mark key */
      if (!hasclears && iscleared(killa_gval(n)))  /* is there a white value? */
        hasclears = 1;  /* table will have to be cleared */
    }
  }
  if (hasclears)
    linktable(h, &g->weak);  /* has to be cleared later */
  else  /* no white values */
    linktable(h, &g->grayagain);  /* no need to clean */
}


static int traverseephemeron (killa_GlobalState *g, killa_Table *h) {
  int marked = 0;  /* true if an object is marked in this traversal */
  int hasclears = 0;  /* true if table has white keys */
  int prop = 0;  /* true if table has entry "white-key -> white-value" */
  killa_Node *n, *limit = gnodelast(h);
  int i;
  /* traverse array part (numeric keys are 'strong') */
  for (i = 0; i < h->sizearray; i++) {
    if (killa_valiswhite(&h->array[i])) {
      marked = 1;
      reallymarkobject(g, killa_gcvalue(&h->array[i]));
    }
  }
  /* traverse hash part */
  for (n = killa_gnode(h, 0); n < limit; n++) {
    checkdeadkey(n);
    if (killa_ttisnil(killa_gval(n)))  /* entry is empty? */
      removeentry(n);  /* remove it */
    else if (iscleared(killa_gkey(n))) {  /* key is not marked (yet)? */
      hasclears = 1;  /* table must be cleared */
      if (killa_valiswhite(killa_gval(n)))  /* value not marked yet? */
        prop = 1;  /* must propagate again */
    }
    else if (killa_valiswhite(killa_gval(n))) {  /* value not marked yet? */
      marked = 1;
      reallymarkobject(g, killa_gcvalue(killa_gval(n)));  /* mark it now */
    }
  }
  if (prop)
    linktable(h, &g->ephemeron);  /* have to propagate again */
  else if (hasclears)  /* does table have white keys? */
    linktable(h, &g->allweak);  /* may have to clean white keys */
  else  /* no white keys */
    linktable(h, &g->grayagain);  /* no need to clean */
  return marked;
}


static void traversestrongtable (killa_GlobalState *g, killa_Table *h) {
  killa_Node *n, *limit = gnodelast(h);
  int i;
  for (i = 0; i < h->sizearray; i++)  /* traverse array part */
    markvalue(g, &h->array[i]);
  for (n = killa_gnode(h, 0); n < limit; n++) {  /* traverse hash part */
    checkdeadkey(n);
    if (killa_ttisnil(killa_gval(n)))  /* entry is empty? */
      removeentry(n);  /* remove it */
    else {
      killa_assert(!killa_ttisnil(killa_gkey(n)));
      markvalue(g, killa_gkey(n));  /* mark key */
      markvalue(g, killa_gval(n));  /* mark value */
    }
  }
}


static int traversetable (killa_GlobalState *g, killa_Table *h) {
  const killa_TValue *mode = killa_gfasttm(g, h->metatable, TM_MODE);
  markobject(g, h->metatable);
  if (mode && killa_ttisstring(mode)) {  /* is there a weak mode? */
    int weakkey = (strchr(killa_svalue(mode), 'k') != NULL);
    int weakvalue = (strchr(killa_svalue(mode), 'v') != NULL);
    if (weakkey || weakvalue) {  /* is really weak? */
      black2gray(killa_obj2gco(h));  /* keep table gray */
      if (!weakkey) {  /* strong keys? */
        traverseweakvalue(g, h);
        return TRAVCOST + killa_sizenode(h);
      }
      else if (!weakvalue) {  /* strong values? */
        traverseephemeron(g, h);
        return TRAVCOST + h->sizearray + killa_sizenode(h);
      }
      else {
        linktable(h, &g->allweak);  /* nothing to traverse now */
        return TRAVCOST;
      }
    }  /* else go through */
  }
  traversestrongtable(g, h);
  return TRAVCOST + h->sizearray + (2 * killa_sizenode(h));
}


static int traverseproto (killa_GlobalState *g, killa_Proto *f) {
  int i;
  if (f->cache && killa_iswhite(killa_obj2gco(f->cache)))
    f->cache = NULL;  /* allow cache to be collected */
  stringmark(f->source);
  for (i = 0; i < f->sizek; i++)  /* mark literals */
    markvalue(g, &f->k[i]);
  for (i = 0; i < f->sizeupvalues; i++)  /* mark upvalue names */
    stringmark(f->upvalues[i].name);
  for (i = 0; i < f->sizep; i++)  /* mark nested protos */
    markobject(g, f->p[i]);
  for (i = 0; i < f->sizelocvars; i++)  /* mark local-variable names */
    stringmark(f->locvars[i].varname);
  return TRAVCOST + f->sizek + f->sizeupvalues + f->sizep + f->sizelocvars;
}


static int traverseclosure (killa_GlobalState *g, killa_Closure *cl) {
  if (cl->c.isC) {
    int i;
    for (i=0; i<cl->c.nupvalues; i++)  /* mark its upvalues */
      markvalue(g, &cl->c.upvalue[i]);
  }
  else {
    int i;
    killa_assert(cl->l.nupvalues == cl->l.p->sizeupvalues);
    markobject(g, cl->l.p);  /* mark its prototype */
    for (i=0; i<cl->l.nupvalues; i++)  /* mark its upvalues */
      markobject(g, cl->l.upvals[i]);
  }
  return TRAVCOST + cl->c.nupvalues;
}


static int traversestack (killa_GlobalState *g, killa_State *L) {
  killa_StkId o = L->stack;
  if (o == NULL)
    return 1;  /* stack not completely built yet */
  for (; o < L->top; o++)
    markvalue(g, o);
  if (g->gcstate == killa_GCSatomic) {  /* final traversal? */
    killa_StkId lim = L->stack + L->stacksize;  /* real end of stack */
    for (; o < lim; o++)  /* clear not-marked stack slice */
      killa_setnilvalue(o);
  }
  return TRAVCOST + killa_cast_int(o - L->stack);
}


/*
** traverse one gray object, turning it to black (except for threads,
** which are always gray).
** Returns number of values traversed.
*/
static int propagatemark (killa_GlobalState *g) {
  killa_GCObject *o = g->gray;
  killa_assert(killa_isgray(o));
  killa_gray2black(o);
  switch (gch(o)->tt) {
    case KILLA_TTABLE: {
      killa_Table *h = killa_gco2t(o);
      g->gray = h->gclist;
      return traversetable(g, h);
    }
    case KILLA_TFUNCTION: {
      killa_Closure *cl = killa_gco2cl(o);
      g->gray = cl->c.gclist;
      return traverseclosure(g, cl);
    }
    case KILLA_TTHREAD: {
      killa_State *th = killa_gco2th(o);
      g->gray = th->gclist;
      th->gclist = g->grayagain;
      g->grayagain = o;
      black2gray(o);
      return traversestack(g, th);
    }
    case KILLA_TPROTO: {
      killa_Proto *p = killa_gco2p(o);
      g->gray = p->gclist;
      return traverseproto(g, p);
    }
    default: killa_assert(0); return 0;
  }
}


static void propagateall (killa_GlobalState *g) {
  while (g->gray) propagatemark(g);
}


static void propagatelist (killa_GlobalState *g, killa_GCObject *l) {
  killa_assert(g->gray == NULL);  /* no grays left */
  g->gray = l;
  propagateall(g);  /* traverse all elements from 'l' */
}

/*
** retraverse all gray lists. Because tables may be reinserted in other
** lists when traversed, traverse the original lists to avoid traversing
** twice the same table (which is not wrong, but inefficient)
*/
static void retraversegrays (killa_GlobalState *g) {
  killa_GCObject *weak = g->weak;  /* save original lists */
  killa_GCObject *grayagain = g->grayagain;
  killa_GCObject *ephemeron = g->ephemeron;
  g->weak = g->grayagain = g->ephemeron = NULL;
  propagateall(g);  /* traverse main gray list */
  propagatelist(g, grayagain);
  propagatelist(g, weak);
  propagatelist(g, ephemeron);
}


static void convergeephemerons (killa_GlobalState *g) {
  int changed;
  do {
    killa_GCObject *w;
    killa_GCObject *next = g->ephemeron;  /* get ephemeron list */
    g->ephemeron = NULL;  /* tables will return to this list when traversed */
    changed = 0;
    while ((w = next) != NULL) {
      next = killa_gco2t(w)->gclist;
      if (traverseephemeron(g, killa_gco2t(w))) {  /* traverse marked some value? */
        propagateall(g);  /* propagate changes */
        changed = 1;  /* will have to revisit all ephemeron tables */
      }
    }
  } while (changed);
}

/* }====================================================== */


/*
** {======================================================
** Sweep Functions
** =======================================================
*/


/*
** clear entries with unmarked keys from all weaktables in list 'l' up
** to element 'f'
*/
static void clearkeys (killa_GCObject *l, killa_GCObject *f) {
  for (; l != f; l = killa_gco2t(l)->gclist) {
    killa_Table *h = killa_gco2t(l);
    killa_Node *n, *limit = gnodelast(h);
    for (n = killa_gnode(h, 0); n < limit; n++) {
      if (!killa_ttisnil(killa_gval(n)) && (iscleared(killa_gkey(n)))) {
        killa_setnilvalue(killa_gval(n));  /* remove value ... */
        removeentry(n);  /* and remove entry from table */
      }
    }
  }
}


/*
** clear entries with unmarked values from all weaktables in list 'l' up
** to element 'f'
*/
static void clearvalues (killa_GCObject *l, killa_GCObject *f) {
  for (; l != f; l = killa_gco2t(l)->gclist) {
    killa_Table *h = killa_gco2t(l);
    killa_Node *n, *limit = gnodelast(h);
    int i;
    for (i = 0; i < h->sizearray; i++) {
      killa_TValue *o = &h->array[i];
      if (iscleared(o))  /* value was collected? */
        killa_setnilvalue(o);  /* remove value */
    }
    for (n = killa_gnode(h, 0); n < limit; n++) {
      if (!killa_ttisnil(killa_gval(n)) && iscleared(killa_gval(n))) {
        killa_setnilvalue(killa_gval(n));  /* remove value ... */
        removeentry(n);  /* and remove entry from table */
      }
    }
  }
}


static void freeobj (killa_State *L, killa_GCObject *o) {
  switch (gch(o)->tt) {
    case KILLA_TPROTO: killaF_freeproto(L, killa_gco2p(o)); break;
    case KILLA_TFUNCTION: killaF_freeclosure(L, killa_gco2cl(o)); break;
    case KILLA_TUPVAL: killaF_freeupval(L, killa_gco2uv(o)); break;
    case KILLA_TTABLE: killaH_free(L, killa_gco2t(o)); break;
    case KILLA_TTHREAD: killaE_freethread(L, killa_gco2th(o)); break;
    case KILLA_TUSERDATA: killaM_freemem(L, o, killa_sizeudata(killa_gco2u(o))); break;
    case KILLA_TSTRING: {
      KILLA_G(L)->strt.nuse--;
      killaM_freemem(L, o, killa_sizestring(killa_gco2ts(o)));
      break;
    }
    default: killa_assert(0);
  }
}


#define sweepwholelist(L,p)	sweeplist(L,p,KILLA_MAX_LUMEM)
static killa_GCObject **sweeplist (killa_State *L, killa_GCObject **p, killa_umem count);


/*
** sweep the (open) upvalues of a thread and resize its stack and
** list of call-info structures.
*/
static void sweepthread (killa_State *L, killa_State *L1) {
  if (L1->stack == NULL) return;  /* stack not completely built yet */
  sweepwholelist(L, &L1->openupval);  /* sweep open upvalues */
  killaE_freeCI(L1);  /* free extra killa_CallInfo slots */
  /* should not change the stack during an emergency gc cycle */
  if (KILLA_G(L)->gckind != KILLA_KGC_EMERGENCY)
    killaD_shrinkstack(L1);
}


/*
** sweep at most 'count' elements from a list of GCObjects erasing dead
** objects, where a dead (not alive) object is one marked with the "old"
** (non current) white and not fixed.
** In non-generational mode, change all non-dead objects back to white,
** preparing for next collection cycle.
** In generational mode, keep black objects black, and also mark them as
** old; stop when hitting an old object, as all objects after that
** one will be old too.
** When object is a thread, sweep its list of open upvalues too.
*/
static killa_GCObject **sweeplist (killa_State *L, killa_GCObject **p, killa_umem count) {
  killa_GlobalState *g = KILLA_G(L);
  int ow = killa_otherwhite(g);
  int toclear, toset;  /* bits to clear and to set in all live objects */
  int tostop;  /* stop sweep when this is true */
  killa_mem debt = g->GCdebt;  /* current debt */
  if (killa_isgenerational(g)) {  /* generational mode? */
    toclear = ~0;  /* clear nothing */
    toset = killa_bitmask(KILLA_OLDBIT);  /* set the old bit of all surviving objects */
    tostop = killa_bitmask(KILLA_OLDBIT);  /* do not sweep old generation */
  }
  else {  /* normal mode */
    toclear = maskcolors;  /* clear all color bits + old bit */
    toset = killaC_white(g);  /* make object white */
    tostop = 0;  /* do not stop */
  }
  while (*p != NULL && count-- > 0) {
    killa_GCObject *curr = *p;
    int marked = gch(curr)->marked;
    if (killa_isdeadm(ow, marked)) {  /* is 'curr' dead? */
      *p = gch(curr)->next;  /* remove 'curr' from list */
      freeobj(L, curr);  /* erase 'curr' */
    }
    else {
      if (gch(curr)->tt == KILLA_TTHREAD)
        sweepthread(L, killa_gco2th(curr));  /* sweep thread's upvalues */
      if (killa_testbits(marked, tostop)) {
        static killa_GCObject *nullp = NULL;
        p = &nullp;  /* stop sweeping this list */
        break;
      }
      /* update marks */
      gch(curr)->marked = killa_cast_byte((marked & toclear) | toset);
      p = &gch(curr)->next;  /* go to next element */
    }
  }
  killaE_setdebt(g, debt);  /* sweeping should not change debt */
  return p;
}

/* }====================================================== */


/*
** {======================================================
** Finalization
** =======================================================
*/

static void checkSizes (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  if (g->gckind != KILLA_KGC_EMERGENCY) {  /* do not change sizes in emergency */
    int hs = g->strt.size / 2;  /* half the size of the string table */
    if (g->strt.nuse < killa_cast(killa_uint32, hs))  /* using less than that half? */
      killaS_resize(L, hs);  /* halve its size */
    killaZ_freebuffer(L, &g->buff);  /* free concatenation buffer */
  }
}


static killa_GCObject *udata2finalize (killa_GlobalState *g) {
  killa_GCObject *o = g->tobefnz;  /* get first element */
  killa_assert(isfinalized(o));
  g->tobefnz = gch(o)->next;  /* remove it from 'tobefnz' list */
  gch(o)->next = g->allgc;  /* return it to 'allgc' list */
  g->allgc = o;
  killa_resetbit(gch(o)->marked, KILLA_SEPARATED);  /* mark that it is not in 'tobefnz' */
  killa_assert(!killa_isold(o));  /* see MOVE OLD rule */
  if (!killa_keepinvariant(g))  /* not keeping invariant? */
    makewhite(g, o);  /* "sweep" object */
  return o;
}


static void dothecall (killa_State *L, void *ud) {
  KILLA_UNUSED(ud);
  killaD_call(L, L->top - 2, 0, 0);
}


static void GCTM (killa_State *L, int propagateerrors) {
  killa_GlobalState *g = KILLA_G(L);
  const killa_TValue *tm;
  killa_TValue v;
  killa_setgcovalue(L, &v, udata2finalize(g));
  tm = killaT_gettmbyobj(L, &v, TM_GC);
  if (tm != NULL && killa_ttisfunction(tm)) {  /* is there a finalizer? */
    int status;
    killa_ubyte oldah = L->allowhook;
    int running  = g->gcrunning;
    L->allowhook = 0;  /* stop debug hooks during GC metamethod */
    g->gcrunning = 0;  /* avoid GC steps */
    killa_setobj2s(L, L->top, tm);  /* push finalizer... */
    killa_setobj2s(L, L->top + 1, &v);  /* ... and its argument */
    L->top += 2;  /* and (next line) call the finalizer */
    status = killaD_pcall(L, dothecall, NULL, killa_savestack(L, L->top - 2), 0);
    L->allowhook = oldah;  /* restore hooks */
    g->gcrunning = running;  /* restore state */
    if (status != KILLA_OK && propagateerrors) {  /* error while running __gc? */
      if (status == KILLA_ERRRUN) {  /* is there an error msg.? */
        killaO_pushfstring(L, "error in __gc metamethod (%s)",
                                        killa_tostring(L, -1));
        status = KILLA_ERRGCMM;  /* error in __gc metamethod */
      }
      killaD_throw(L, status);  /* re-send error */
    }
  }
}


/*
** move all unreachable objects (or 'all' objects) that need
** finalization from list 'finobj' to list 'tobefnz' (to be finalized)
*/
static void separatetobefnz (killa_State *L, int all) {
  killa_GlobalState *g = KILLA_G(L);
  killa_GCObject **p = &g->finobj;
  killa_GCObject *curr;
  killa_GCObject **lastnext = &g->tobefnz;
  /* find last 'next' field in 'tobefnz' list (to add elements in its end) */
  while (*lastnext != NULL)
    lastnext = &gch(*lastnext)->next;
  while ((curr = *p) != NULL) {  /* traverse all finalizable objects */
    killa_assert(!isfinalized(curr));
    killa_assert(killa_testbit(gch(curr)->marked, KILLA_SEPARATED));
    if (!(all || killa_iswhite(curr)))  /* not being collected? */
      p = &gch(curr)->next;  /* don't bother with it */
    else {
      killa_l_setbit(gch(curr)->marked, KILLA_FINALIZEDBIT); /* won't be finalized again */
      *p = gch(curr)->next;  /* remove 'curr' from 'finobj' list */
      gch(curr)->next = *lastnext;  /* link at the end of 'tobefnz' list */
      *lastnext = curr;
      lastnext = &gch(curr)->next;
    }
  }
}


/*
** if object 'o' has a finalizer, remove it from 'allgc' list (must
** search the list to find it) and link it in 'finobj' list.
*/
void killaC_checkfinalizer (killa_State *L, killa_GCObject *o, killa_Table *mt) {
  killa_GlobalState *g = KILLA_G(L);
  if (killa_testbit(gch(o)->marked, KILLA_SEPARATED) || /* obj. is already separated... */
      isfinalized(o) ||                           /* ... or is finalized... */
      killa_gfasttm(g, mt, TM_GC) == NULL)                /* or has no finalizer? */
    return;  /* nothing to be done */
  else {  /* move 'o' to 'finobj' list */
    killa_GCObject **p;
    for (p = &g->allgc; *p != o; p = &gch(*p)->next) ;
    *p = gch(o)->next;  /* remove 'o' from root list */
    gch(o)->next = g->finobj;  /* link it in list 'finobj' */
    g->finobj = o;
    killa_l_setbit(gch(o)->marked, KILLA_SEPARATED);  /* mark it as such */
    killa_resetoldbit(o);  /* see MOVE OLD rule */
  }
}

/* }====================================================== */


/*
** {======================================================
** GC control
** =======================================================
*/


#define sweepphases  \
	(killa_bitmask(killa_GCSsweepstring) | killa_bitmask(killa_GCSsweepudata) | killa_bitmask(killa_GCSsweep))

/*
** change GC mode
*/
void killaC_changemode (killa_State *L, int mode) {
  killa_GlobalState *g = KILLA_G(L);
  if (mode == g->gckind) return;  /* nothing to change */
  if (mode == KILLA_KGC_GEN) {  /* change to generational mode */
    /* make sure gray lists are consistent */
    killaC_runtilstate(L, killa_bitmask(killa_GCSpropagate));
    g->lastmajormem = killa_gettotalbytes(g);
    g->gckind = KILLA_KGC_GEN;
  }
  else {  /* change to incremental mode */
    /* sweep all objects to turn them back to white
       (as white has not changed, nothing extra will be collected) */
    g->sweepstrgc = 0;
    g->gcstate = killa_GCSsweepstring;
    g->gckind = KILLA_KGC_NORMAL;
    killaC_runtilstate(L, ~sweepphases);
  }
}


/*
** call all pending finalizers
*/
static void callallpendingfinalizers (killa_State *L, int propagateerrors) {
  killa_GlobalState *g = KILLA_G(L);
  while (g->tobefnz) {
    killa_resetoldbit(g->tobefnz);
    GCTM(L, propagateerrors);
  }
}


void killaC_freeallobjects (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  int i;
  separatetobefnz(L, 1);  /* separate all objects with finalizers */
  killa_assert(g->finobj == NULL);
  callallpendingfinalizers(L, 0);
  g->currentwhite = KILLA_WHITEBITS; /* this "white" makes all objects look dead */
  g->gckind = KILLA_KGC_NORMAL;
  sweepwholelist(L, &g->finobj);  /* finalizers can create objs. in 'finobj' */
  sweepwholelist(L, &g->allgc);
  for (i = 0; i < g->strt.size; i++)  /* free all string lists */
    sweepwholelist(L, &g->strt.hash[i]);
  killa_assert(g->strt.nuse == 0);
}


static void atomic (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  killa_GCObject *origweak, *origall;
  killa_assert(!killa_iswhite(killa_obj2gco(g->mainthread)));
  markobject(g, L);  /* mark running thread */
  /* registry and global metatables may be changed by API */
  markvalue(g, &g->l_registry);
  markmt(g);  /* mark basic metatables */
  /* remark occasional upvalues of (maybe) dead threads */
  remarkupvals(g);
  /* traverse objects caught by write barrier and by 'remarkupvals' */
  retraversegrays(g);
  convergeephemerons(g);
  /* at this point, all strongly accessible objects are marked. */
  /* clear values from weak tables, before checking finalizers */
  clearvalues(g->weak, NULL);
  clearvalues(g->allweak, NULL);
  origweak = g->weak; origall = g->allweak;
  separatetobefnz(L, 0);  /* separate objects to be finalized */
  markbeingfnz(g);  /* mark userdata that will be finalized */
  propagateall(g);  /* remark, to propagate `preserveness' */
  convergeephemerons(g);
  /* at this point, all resurrected objects are marked. */
  /* remove dead objects from weak tables */
  clearkeys(g->ephemeron, NULL);  /* clear keys from all ephemeron tables */
  clearkeys(g->allweak, NULL);  /* clear keys from all allweak tables */
  /* clear values from resurrected weak tables */
  clearvalues(g->weak, origweak);
  clearvalues(g->allweak, origall);
  g->sweepstrgc = 0;  /* prepare to sweep strings */
  g->gcstate = killa_GCSsweepstring;
  g->currentwhite = killa_cast_byte(killa_otherwhite(g));  /* flip current white */
  /*killa_checkmemory(L);*/
}


static killa_mem singlestep (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  switch (g->gcstate) {
    case killa_GCSpause: {
      if (!killa_isgenerational(g))
        markroot(g);  /* start a new collection */
      /* in any case, root must be marked */
      killa_assert(!killa_iswhite(killa_obj2gco(g->mainthread))
              && !killa_iswhite(killa_gcvalue(&g->l_registry)));
      g->gcstate = killa_GCSpropagate;
      return GCROOTCOST;
    }
    case killa_GCSpropagate: {
      if (g->gray)
        return propagatemark(g);
      else {  /* no more `gray' objects */
        g->gcstate = killa_GCSatomic;  /* finish mark phase */
        atomic(L);
        return GCATOMICCOST;
      }
    }
    case killa_GCSsweepstring: {
      if (g->sweepstrgc < g->strt.size) {
        sweepwholelist(L, &g->strt.hash[g->sweepstrgc++]);
        return GCSWEEPCOST;
      }
      else {  /* no more strings to sweep */
        g->sweepgc = &g->finobj;  /* prepare to sweep finalizable objects */
        g->gcstate = killa_GCSsweepudata;
        return 0;
      }
    }
    case killa_GCSsweepudata: {
      if (*g->sweepgc) {
        g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {
        g->sweepgc = &g->allgc;  /* go to next phase */
        g->gcstate = killa_GCSsweep;
        return GCSWEEPCOST;
      }
    }
    case killa_GCSsweep: {
      if (*g->sweepgc) {
        g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
        return GCSWEEPMAX*GCSWEEPCOST;
      }
      else {
        /* sweep main thread */
        killa_GCObject *mt = killa_obj2gco(g->mainthread);
        sweeplist(L, &mt, 1);
        checkSizes(L);
        g->gcstate = killa_GCSpause;  /* finish collection */
        return GCSWEEPCOST;
      }
    }
    default: killa_assert(0); return 0;
  }
}


/*
** advances the garbage collector until it reaches a state allowed
** by 'statemask'
*/
void killaC_runtilstate (killa_State *L, int statesmask) {
  killa_GlobalState *g = KILLA_G(L);
  while (!killa_testbit(statesmask, g->gcstate))
    singlestep(L);
}


static void generationalcollection (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  if (g->lastmajormem == 0) {  /* signal for another major collection? */
    killaC_fullgc(L, 0);  /* perform a full regular collection */
    g->lastmajormem = killa_gettotalbytes(g);  /* update control */
  }
  else {
    killaC_runtilstate(L, ~killa_bitmask(killa_GCSpause));  /* run complete cycle */
    killaC_runtilstate(L, killa_bitmask(killa_GCSpause));
    if (killa_gettotalbytes(g) > g->lastmajormem/100 * g->gcmajorinc)
      g->lastmajormem = 0;  /* signal for a major collection */
  }
  killaE_setdebt(g, stddebt(g));
}


static void step (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  killa_mem lim = g->gcstepmul;  /* how much to work */
  do {  /* always perform at least one single step */
    lim -= singlestep(L);
  } while (lim > 0 && g->gcstate != killa_GCSpause);
  if (g->gcstate != killa_GCSpause)
    killaE_setdebt(g, g->GCdebt - GCSTEPSIZE);
  else
    killaE_setdebt(g, stddebt(g));
}


/*
** performs a basic GC step even if the collector is stopped
*/
void killaC_forcestep (killa_State *L) {
  killa_GlobalState *g = KILLA_G(L);
  int i;
  if (killa_isgenerational(g)) generationalcollection(L);
  else step(L);
  for (i = 0; i < GCFINALIZENUM && g->tobefnz; i++)
    GCTM(L, 1);  /* Call a few pending finalizers */
}


/*
** performs a basic GC step only if collector is running
*/
void killaC_step (killa_State *L) {
  if (KILLA_G(L)->gcrunning) killaC_forcestep(L);
}


/*
** performs a full GC cycle; if "isemergency", does not call
** finalizers (which could change stack positions)
*/
void killaC_fullgc (killa_State *L, int isemergency) {
  killa_GlobalState *g = KILLA_G(L);
  int origkind = g->gckind;
  killa_assert(origkind != KILLA_KGC_EMERGENCY);
  if (!isemergency)   /* do not run finalizers during emergency GC */
    callallpendingfinalizers(L, 1);
  if (killa_keepinvariant(g)) {  /* marking phase? */
    /* must sweep all objects to turn them back to white
       (as white has not changed, nothing will be collected) */
    g->sweepstrgc = 0;
    g->gcstate = killa_GCSsweepstring;
  }
  g->gckind = isemergency ? KILLA_KGC_EMERGENCY : KILLA_KGC_NORMAL;
  /* finish any pending sweep phase to start a new cycle */
  killaC_runtilstate(L, killa_bitmask(killa_GCSpause));
  /* run entire collector */
  killaC_runtilstate(L, ~killa_bitmask(killa_GCSpause));
  killaC_runtilstate(L, killa_bitmask(killa_GCSpause));
  if (origkind == KILLA_KGC_GEN) {  /* generational mode? */
    /* generational mode must always start in propagate phase */
    killaC_runtilstate(L, killa_bitmask(killa_GCSpropagate));
  }
  g->gckind = origkind;
  killaE_setdebt(g, stddebt(g));
  if (!isemergency)   /* do not run finalizers during emergency GC */
    callallpendingfinalizers(L, 1);
}

/* }====================================================== */


