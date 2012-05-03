/* ========================================================================== */
/*   Coroutine Library                                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


static int auxresume (killa_State *L, killa_State *co, int narg) {
  int status;
  if (!killa_checkstack(co, narg)) {
    killa_pushliteral(L, "too many arguments to resume");
    return -1;  /* error flag */
  }
  if (killa_status(co) == KILLA_OK && killa_gettop(co) == 0) {
    killa_pushliteral(L, "cannot resume dead coroutine");
    return -1;  /* error flag */
  }
  killa_xmove(L, co, narg);
  status = killa_resume(co, L, narg);
  if (status == KILLA_OK || status == KILLA_YIELD) {
    int nres = killa_gettop(co);
    if (!killa_checkstack(L, nres + 1)) {
      killa_pop(co, nres);  /* remove results anyway */
      killa_pushliteral(L, "too many results to resume");
      return -1;  /* error flag */
    }
    killa_xmove(co, L, nres);  /* move yielded values */
    return nres;
  }
  else {
    killa_xmove(co, L, 1);  /* move error message */
    return -1;  /* error flag */
  }
}


static int killaB_coresume (killa_State *L) {
  killa_State *co = killa_tothread(L, 1);
  int r;
  killaL_argcheck(L, co, 1, "coroutine expected");
  r = auxresume(L, co, killa_gettop(L) - 1);
  if (r < 0) {
    killa_pushboolean(L, 0);
    killa_insert(L, -2);
    return 2;  /* return false + error message */
  }
  else {
    killa_pushboolean(L, 1);
    killa_insert(L, -(r + 1));
    return r + 1;  /* return true + `resume' returns */
  }
}


static int killaB_auxwrap (killa_State *L) {
  killa_State *co = killa_tothread(L, killa_upvalueindex(1));
  int r = auxresume(L, co, killa_gettop(L));
  if (r < 0) {
    if (killa_isstring(L, -1)) {  /* error object is a string? */
      killaL_where(L, 1);  /* add extra info */
      killa_insert(L, -2);
      killa_concat(L, 2);
    }
    killa_error(L);  /* propagate error */
  }
  return r;
}


static int killaB_cocreate (killa_State *L) {
  killa_State *NL = killa_newthread(L);
  killaL_checktype(L, 1, KILLA_TFUNCTION);
  killa_pushvalue(L, 1);  /* move function to top */
  killa_xmove(L, NL, 1);  /* move function from L to NL */
  return 1;
}


static int killaB_cowrap (killa_State *L) {
  killaB_cocreate(L);
  killa_pushcclosure(L, killaB_auxwrap, 1);
  return 1;
}


static int killaB_yield (killa_State *L) {
  return killa_yield(L, killa_gettop(L));
}


static int killaB_costatus (killa_State *L) {
  killa_State *co = killa_tothread(L, 1);
  killaL_argcheck(L, co, 1, "coroutine expected");
  if (L == co) killa_pushliteral(L, "running");
  else {
    switch (killa_status(co)) {
      case KILLA_YIELD:
        killa_pushliteral(L, "suspended");
        break;
      case KILLA_OK: {
        killa_Debug ar;
        if (killa_getstack(co, 0, &ar) > 0)  /* does it have frames? */
          killa_pushliteral(L, "normal");  /* it is running */
        else if (killa_gettop(co) == 0)
            killa_pushliteral(L, "dead");
        else
          killa_pushliteral(L, "suspended");  /* initial state */
        break;
      }
      default:  /* some error occurred */
        killa_pushliteral(L, "dead");
        break;
    }
  }
  return 1;
}


static int killaB_corunning (killa_State *L) {
  int ismain = killa_pushthread(L);
  killa_pushboolean(L, ismain);
  return 2;
}


static const killaL_Reg co_funcs[] = {
  {"create", killaB_cocreate},
  {"resume", killaB_coresume},
  {"running", killaB_corunning},
  {"status", killaB_costatus},
  {"wrap", killaB_cowrap},
  {"yield", killaB_yield},
  {NULL, NULL}
};



KILLAMOD_API int killaopen_coroutine (killa_State *L) {
  killaL_newlib(L, co_funcs);
  return 1;
}

