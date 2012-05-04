/* ========================================================================== */
/*   Garbage Collector                                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KGC_H_
#define KGC_H_


#include "kobject.h"
#include "kstate.h"

/*
** Collectable objects may have one of three colors: white, which
** means the object is not marked; gray, which means the
** object is marked, but its references may be not marked; and
** black, which means that the object and all its references are marked.
** The main invariant of the garbage collector, while marking objects,
** is that a black object can never point to a white one. Moreover,
** any gray object must be in a "gray list" (gray, grayagain, weak,
** allweak, ephemeron) so that it can be visited again before finishing
** the collection cycle. These lists have no meaning when the invariant
** is not being enforced (e.g., sweep phase).
*/


/*
** Possible states of the Garbage Collector
*/
#define killa_GCSpropagate      0
#define killa_GCSatomic         1
#define killa_GCSsweepstring    2
#define killa_GCSsweepudata     3
#define killa_GCSsweep          4
#define killa_GCSpause          5


#define killa_issweepphase(g)  \
	(killa_GCSsweepstring <= (g)->gcstate && (g)->gcstate <= killa_GCSsweep)

#define killa_isgenerational(g)	((g)->gckind == KILLA_KGC_GEN)

/*
** macro to tell when main invariant (white objects cannot point to black
** ones) must be kept. During a non-generational collection, the sweep
** phase may break the invariant, as objects turned white may point to
** still-black objects. The invariant is restored when sweep ends and
** all objects are white again. During a generational collection, the
** invariant must be kept all times.
*/
#define killa_keepinvariant(g)  (killa_isgenerational(g) || g->gcstate <= killa_GCSatomic)


/*
** some useful bit tricks
*/
#define killa_resetbits(x,m)    ((x) &= killa_cast(killa_ubyte, ~(m)))
#define killa_setbits(x,m)      ((x) |= (m))
#define killa_testbits(x,m)     ((x) & (m))
#define killa_bitmask(b)        (1<<(b))
#define killa_bit2mask(b1,b2)   (killa_bitmask(b1) | killa_bitmask(b2))
#define killa_l_setbit(x,b)     killa_setbits(x, killa_bitmask(b))
#define killa_resetbit(x,b)     killa_resetbits(x, killa_bitmask(b))
#define killa_testbit(x,b)      killa_testbits(x, killa_bitmask(b))


/* Layout for bit use in `marked' field: */
#define KILLA_WHITE0BIT     0  /* object is white (type 0) */
#define KILLA_WHITE1BIT     1  /* object is white (type 1) */
#define KILLA_BLACKBIT      2  /* object is black */
#define KILLA_FINALIZEDBIT  3  /* object has been separated for finalization */
#define KILLA_SEPARATED     4  /* object is in 'finobj' list or in 'tobefnz' */
#define KILLA_FIXEDBIT      5  /* object is fixed (should not be collected) */
#define KILLA_OLDBIT        6  /* object is old (only in generational mode) */
/* bit 7 is currently used by tests (killa_checkmemory) */

#define KILLA_WHITEBITS	killa_bit2mask(KILLA_WHITE0BIT, KILLA_WHITE1BIT)


#define killa_iswhite(x)    killa_testbits((x)->gch.marked, KILLA_WHITEBITS)
#define killa_isblack(x)    killa_testbit((x)->gch.marked, KILLA_BLACKBIT)
#define killa_isgray(x)  /* neither white nor black */  \
    (!killa_testbits((x)->gch.marked, KILLA_WHITEBITS | killa_bitmask(KILLA_BLACKBIT)))

#define killa_isold(x)  killa_testbit((x)->gch.marked, KILLA_OLDBIT)

/* MOVE OLD rule: whenever an object is moved to the beginning of
   a GC list, its old bit must be cleared */
#define killa_resetoldbit(o)    killa_resetbit((o)->gch.marked, KILLA_OLDBIT)

#define killa_otherwhite(g) (g->currentwhite ^ KILLA_WHITEBITS)
#define killa_isdeadm(ow,m) (!(((m) ^ KILLA_WHITEBITS) & (ow)))
#define killa_isdead(g,v)   killa_isdeadm(killa_otherwhite(g), (v)->gch.marked)

#define killa_changewhite(x)    ((x)->gch.marked ^= KILLA_WHITEBITS)
#define killa_gray2black(x) killa_l_setbit((x)->gch.marked, KILLA_BLACKBIT)

#define killa_valiswhite(x) (killa_iscollectable(x) && killa_iswhite(killa_gcvalue(x)))

#define killaC_white(g) killa_cast(killa_ubyte, (g)->currentwhite & KILLA_WHITEBITS)


#define killaC_condGC(L,c) \
	{if (KILLA_G(L)->GCdebt > 0) {c;}; killa_condchangemem(L);}
#define killaC_checkGC(L)   killaC_condGC(L, killaC_step(L);)


#define killaC_barrier(L,p,v) { if (killa_valiswhite(v) && killa_isblack(killa_obj2gco(p)))  \
    killaC_barrier_(L,killa_obj2gco(p),killa_gcvalue(v)); }

#define killaC_barrierback(L,p,v) { if (killa_valiswhite(v) && killa_isblack(killa_obj2gco(p)))  \
    killaC_barrierback_(L,p); }

#define killaC_objbarrier(L,p,o)  \
    { if (killa_iswhite(killa_obj2gco(o)) && killa_isblack(killa_obj2gco(p))) \
        killaC_barrier_(L,killa_obj2gco(p),killa_obj2gco(o)); }

#define killaC_objbarrierback(L,p,o)  \
    { if (killa_iswhite(killa_obj2gco(o)) && killa_isblack(killa_obj2gco(p))) killaC_barrierback_(L,p); }

#define killaC_barrierproto(L,p,c) \
    { if (killa_isblack(killa_obj2gco(p))) killaC_barrierproto_(L,p,c); }

KILLAI_FUNC void killaC_freeallobjects (killa_State *L);
KILLAI_FUNC void killaC_step (killa_State *L);
KILLAI_FUNC void killaC_forcestep (killa_State *L);
KILLAI_FUNC void killaC_runtilstate (killa_State *L, int statesmask);
KILLAI_FUNC void killaC_fullgc (killa_State *L, int isemergency);
KILLAI_FUNC killa_GCObject *killaC_newobj (killa_State *L, int tt, size_t sz,
                                           killa_GCObject **list, int offset);
KILLAI_FUNC void killaC_barrier_ (killa_State *L, killa_GCObject *o, killa_GCObject *v);
KILLAI_FUNC void killaC_barrierback_ (killa_State *L, killa_GCObject *o);
KILLAI_FUNC void killaC_barrierproto_ (killa_State *L, killa_Proto *p, killa_Closure *c);
KILLAI_FUNC void killaC_checkfinalizer (killa_State *L, killa_GCObject *o, killa_Table *mt);
KILLAI_FUNC void killaC_checkupvalcolor (killa_GlobalState *g, killa_UpVal *uv);
KILLAI_FUNC void killaC_changemode (killa_State *L, int mode);

#endif
