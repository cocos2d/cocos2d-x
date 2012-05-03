/* ========================================================================== */
/*   Killa Parser                                                             */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KPARSER_H_
#define KPARSER_H_

#include "klimits.h"
#include "kobject.h"
#include "kzio.h"


/*
 * Expression descriptor
 */

typedef enum {
    VVOID,      /* no value */
    VUNDEFINED,
    VNULL,
    VTRUE,
    VFALSE,
    VK,		    /* info = index of constant in `k' */
    VKNUM,	    /* nval = numerical value */
    VNONRELOC,	/* info = result register */
    VLOCAL,	    /* info = local register */
    VUPVAL,     /* info = index of upvalue in 'upvalues' */
    VINDEXED,	/* t = table register/upvalue; idx = index R/K */
    VJMP,		/* info = instruction pc */
    VRELOCABLE,	/* info = instruction pc */
    VCALL,	    /* info = instruction pc */
    VVARARG	    /* info = instruction pc */
} killa_expkind;


#define killa_vkisvar(k)    (VLOCAL <= (k) && (k) <= VINDEXED)
#define killa_vkisinreg(k)  ((k) == VNONRELOC || (k) == VLOCAL)

typedef struct killa_expdesc {
  killa_expkind k;
  union {
    struct {  /* for indexed variables (VINDEXED) */
      short idx;  /* index (R/K) */
      killa_ubyte t;  /* table (register or upvalue) */
      killa_ubyte vt;  /* whether 't' is register (VLOCAL) or upvalue (VUPVAL) */
    } ind;
    int info;  /* for generic use */
    killa_Number nval;  /* for VKNUM */
  } u;
  int t;  /* patch list of `exit when true' */
  int f;  /* patch list of `exit when false' */
} killa_expdesc;


/* description of active local variable */
typedef struct killa_Vardesc {
  short idx;  /* variable index in stack */
} killa_Vardesc;


/* description of pending goto statements and label statements */
typedef struct killa_Labeldesc {
  killa_TString *name;  /* label identifier */
  int pc;  /* position in code */
  int line;  /* line where it appeared */
  killa_ubyte nactvar;  /* local level where it appears in current block */
} killa_Labeldesc;


/* list of labels or gotos */
typedef struct killa_Labellist {
  killa_Labeldesc *arr;  /* array */
  int n;  /* number of entries in use */
  int size;  /* array size */
} killa_Labellist;


/* dynamic structures used by the parser */
typedef struct killa_Dyndata {
  struct {  /* list of active local variables */
    killa_Vardesc *arr;
    int n;
    int size;
  } actvar;
  killa_Labellist gt;  /* list of pending gotos */
  killa_Labellist label;   /* list of active labels */
} killa_Dyndata;


/* control of blocks */
struct killa_BlockCnt;  /* defined in lparser.c */


/* state needed to generate code for a given function */
typedef struct killa_FuncState {
  killa_Proto *f;  /* current function header */
  killa_Table *h;  /* table to find (and reuse) elements in `k' */
  struct killa_FuncState *prev;  /* enclosing function */
  struct killa_LexState *ls;  /* lexical state */
  struct killa_BlockCnt *bl;  /* chain of current blocks */
  int pc;  /* next position to code (equivalent to `ncode') */
  int lasttarget;   /* 'label' of last 'jump label' */
  int jpc;  /* list of pending jumps to `pc' */
  int nk;  /* number of elements in `k' */
  int np;  /* number of elements in `p' */
  int firstlocal;  /* index of first local var (in killa_Dyndata array) */
  short nlocvars;  /* number of elements in 'f->locvars' */
  killa_ubyte nactvar;  /* number of active local variables */
  killa_ubyte nups;  /* number of upvalues */
  killa_ubyte freereg;  /* first free register */
} killa_FuncState;


KILLAI_FUNC killa_Proto *killaY_parser (killa_State *L, killa_ZIO *z, killa_Mbuffer *buff,
                                        killa_Dyndata *dyd, const char *name, int firstchar);


#endif
