/* ========================================================================== */
/*   Tag methods                                                              */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KTM_H_
#define KTM_H_


#include "kobject.h"


/*
* WARNING: if you change the order of this enumeration,
* grep "ORDER TM"
*/
typedef enum {
  TM_INDEX,
  TM_NEWINDEX,
  TM_GC,
  TM_MODE,
  TM_LEN,
  TM_EQ,  /* last tag method with `fast' access */
  TM_ADD,
  TM_SUB,
  TM_MUL,
  TM_DIV,
  TM_MOD,
  TM_POW,
  TM_UNM,
  TM_LT,
  TM_LE,
  TM_CONCAT,
  TM_CALL,
  TM_N		/* number of elements in the enum */
} KILLA_TMS;



#define killa_gfasttm(g,et,e) ((et) == NULL ? NULL : \
        ((et)->flags & (1u<<(e))) ? NULL : killaT_gettm(et, e, (g)->tmname[e]))

#define killa_fasttm(l,et,e)    killa_gfasttm(KILLA_G(l), et, e)

#define killa_ttypename(x)      killaT_typenames_[(x) + 1]
#define killa_objtypename(x)    killa_ttypename(killa_ttypenv(x))

KILLAI_DDEC const char *const killaT_typenames_[KILLA_TOTALTAGS];


KILLAI_FUNC const killa_TValue *killaT_gettm (killa_Table *events, KILLA_TMS event, killa_TString *ename);
KILLAI_FUNC const killa_TValue *killaT_gettmbyobj (killa_State *L, const killa_TValue *o,
                                                   KILLA_TMS event);
KILLAI_FUNC void killaT_init (killa_State *L);

#endif
