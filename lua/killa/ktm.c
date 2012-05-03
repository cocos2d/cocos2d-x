/* ========================================================================== */
/*   Tag methods`                                                             */
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

#include "kobject.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "ktm.h"


static const char udatatypename[] = "userdata";

KILLAI_DDEF const char *const killaT_typenames_[KILLA_TOTALTAGS] = {
  "no value",
  "null", "boolean", udatatypename, "number",
  "string", "table", "function", udatatypename, "thread",
  "proto", "upval"  /* these last two cases are used for tests only */
};


void killaT_init (killa_State *L) {
  static const char *const killaT_eventname[] = {  /* ORDER TM */
    "__index", "__newindex",
    "__gc", "__mode", "__len", "__eq",
    "__add", "__sub", "__mul", "__div", "__mod",
    "__pow", "__unm", "__lt", "__le",
    "__concat", "__call"
  };
  int i;
  for (i=0; i<TM_N; i++) {
    KILLA_G(L)->tmname[i] = killaS_new(L, killaT_eventname[i]);
    killaS_fix(KILLA_G(L)->tmname[i]);  /* never collect these names */
  }
}


/*
** function to be used with macro "killa_fasttm": optimized for absence of
** tag methods
*/
const killa_TValue *killaT_gettm (killa_Table *events, KILLA_TMS event, killa_TString *ename) {
  const killa_TValue *tm = killaH_getstr(events, ename);
  killa_assert(event <= TM_EQ);
  if (killa_ttisnil(tm)) {  /* no tag method? */
    events->flags |= killa_cast_byte(1u<<event);  /* cache this fact */
    return NULL;
  }
  else return tm;
}


const killa_TValue *killaT_gettmbyobj (killa_State *L, const killa_TValue *o, KILLA_TMS event) {
  killa_Table *mt;
  switch (killa_ttypenv(o)) {
    case KILLA_TTABLE:
      mt = killa_hvalue(o)->metatable;
      break;
    case KILLA_TUSERDATA:
      mt = killa_uvalue(o)->metatable;
      break;
    default:
      mt = KILLA_G(L)->mt[killa_ttypenv(o)];
  }
  return (mt ? killaH_getstr(mt, KILLA_G(L)->tmname[event]) : killaO_nilobject);
}

