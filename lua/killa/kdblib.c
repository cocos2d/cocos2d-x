/* ========================================================================== */
/*   Interface from Killa to its debug API                                    */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


#define HOOKKEY		"_HKEY"



static int db_getregistry (killa_State *L) {
  killa_pushvalue(L, KILLA_REGISTRYINDEX);
  return 1;
}


static int db_getmetatable (killa_State *L) {
  killaL_checkany(L, 1);
  if (!killa_getmetatable(L, 1)) {
    killa_pushnull(L);  /* no metatable */
  }
  return 1;
}


static int db_setmetatable (killa_State *L) {
  int t = killa_type(L, 2);
  killaL_argcheck(L, t == KILLA_TNULL || t == KILLA_TTABLE, 2,
                    "null or table expected");
  killa_settop(L, 2);
  killa_setmetatable(L, 1);
  return 1;  /* return 1st argument */
}


static int db_getuservalue (killa_State *L) {
  if (killa_type(L, 1) != KILLA_TUSERDATA)
    killa_pushnull(L);
  else
    killa_getuservalue(L, 1);
  return 1;
}


static int db_setuservalue (killa_State *L) {
  if (killa_type(L, 1) == KILLA_TLIGHTUSERDATA)
    killaL_argerror(L, 1, "full userdata expected, got light userdata");
  killaL_checktype(L, 1, KILLA_TUSERDATA);
  if (!killa_isnoneornull(L, 2))
    killaL_checktype(L, 2, KILLA_TTABLE);
  killa_settop(L, 2);
  killa_setuservalue(L, 1);
  return 1;
}


static void settabss (killa_State *L, const char *i, const char *v) {
  killa_pushstring(L, v);
  killa_setfield(L, -2, i);
}


static void settabsi (killa_State *L, const char *i, int v) {
  killa_pushinteger(L, v);
  killa_setfield(L, -2, i);
}


static void settabsb (killa_State *L, const char *i, int v) {
  killa_pushboolean(L, v);
  killa_setfield(L, -2, i);
}


static killa_State *getthread (killa_State *L, int *arg) {
  if (killa_isthread(L, 1)) {
    *arg = 1;
    return killa_tothread(L, 1);
  }
  else {
    *arg = 0;
    return L;
  }
}


static void treatstackoption (killa_State *L, killa_State *L1, const char *fname) {
  if (L == L1) {
    killa_pushvalue(L, -2);
    killa_remove(L, -3);
  }
  else
    killa_xmove(L1, L, 1);
  killa_setfield(L, -2, fname);
}


static int db_getinfo (killa_State *L) {
  killa_Debug ar;
  int arg;
  killa_State *L1 = getthread(L, &arg);
  const char *options = killaL_optstring(L, arg+2, "flnStu");
  if (killa_isnumber(L, arg+1)) {
    if (!killa_getstack(L1, (int)killa_tointeger(L, arg+1), &ar)) {
      killa_pushnull(L);  /* level out of range */
      return 1;
    }
  }
  else if (killa_isfunction(L, arg+1)) {
    killa_pushfstring(L, ">%s", options);
    options = killa_tostring(L, -1);
    killa_pushvalue(L, arg+1);
    killa_xmove(L, L1, 1);
  }
  else
    return killaL_argerror(L, arg+1, "function or level expected");
  if (!killa_getinfo(L1, options, &ar))
    return killaL_argerror(L, arg+2, "invalid option");
  killa_createtable(L, 0, 2);
  if (strchr(options, 'S')) {
    settabss(L, "source", ar.source);
    settabss(L, "short_src", ar.short_src);
    settabsi(L, "linedefined", ar.linedefined);
    settabsi(L, "lastlinedefined", ar.lastlinedefined);
    settabss(L, "what", ar.what);
  }
  if (strchr(options, 'l'))
    settabsi(L, "currentline", ar.currentline);
  if (strchr(options, 'u')) {
    settabsi(L, "nups", ar.nups);
    settabsi(L, "nparams", ar.nparams);
    settabsb(L, "isvararg", ar.isvararg);
  }
  if (strchr(options, 'n')) {
    settabss(L, "name", ar.name);
    settabss(L, "namewhat", ar.namewhat);
  }
  if (strchr(options, 't'))
    settabsb(L, "istailcall", ar.istailcall);
  if (strchr(options, 'L'))
    treatstackoption(L, L1, "activelines");
  if (strchr(options, 'f'))
    treatstackoption(L, L1, "func");
  return 1;  /* return table */
}


static int db_getlocal (killa_State *L) {
  int arg;
  killa_State *L1 = getthread(L, &arg);
  killa_Debug ar;
  const char *name;
  int nvar = killaL_checkint(L, arg+2);  /* local-variable index */
  if (killa_isfunction(L, arg + 1)) {  /* function argument? */
    killa_pushvalue(L, arg + 1);  /* push function */
    killa_pushstring(L, killa_getlocal(L, NULL, nvar));  /* push local name */
    return 1;
  }
  else {  /* stack-level argument */
    if (!killa_getstack(L1, killaL_checkint(L, arg+1), &ar))  /* out of range? */
      return killaL_argerror(L, arg+1, "level out of range");
    name = killa_getlocal(L1, &ar, nvar);
    if (name) {
      killa_xmove(L1, L, 1);  /* push local value */
      killa_pushstring(L, name);  /* push name */
      killa_pushvalue(L, -2);  /* re-order */
      return 2;
    }
    else {
      killa_pushnull(L);  /* no name (nor value) */
      return 1;
    }
  }
}


static int db_setlocal (killa_State *L) {
  int arg;
  killa_State *L1 = getthread(L, &arg);
  killa_Debug ar;
  if (!killa_getstack(L1, killaL_checkint(L, arg+1), &ar))  /* out of range? */
    return killaL_argerror(L, arg+1, "level out of range");
  killaL_checkany(L, arg+3);
  killa_settop(L, arg+3);
  killa_xmove(L, L1, 1);
  killa_pushstring(L, killa_setlocal(L1, &ar, killaL_checkint(L, arg+2)));
  return 1;
}


static int auxupvalue (killa_State *L, int get) {
  const char *name;
  int n = killaL_checkint(L, 2);
  killaL_checktype(L, 1, KILLA_TFUNCTION);
  name = get ? killa_getupvalue(L, 1, n) : killa_setupvalue(L, 1, n);
  if (name == NULL) return 0;
  killa_pushstring(L, name);
  killa_insert(L, -(get+1));
  return get + 1;
}


static int db_getupvalue (killa_State *L) {
  return auxupvalue(L, 1);
}


static int db_setupvalue (killa_State *L) {
  killaL_checkany(L, 3);
  return auxupvalue(L, 0);
}


static int checkupval (killa_State *L, int argf, int argnup) {
  killa_Debug ar;
  int nup = killaL_checkint(L, argnup);
  killaL_checktype(L, argf, KILLA_TFUNCTION);
  killa_pushvalue(L, argf);
  killa_getinfo(L, ">u", &ar);
  killaL_argcheck(L, 1 <= nup && nup <= ar.nups, argnup, "invalid upvalue index");
  return nup;
}


static int db_upvalueid (killa_State *L) {
  int n = checkupval(L, 1, 2);
  killa_pushlightuserdata(L, killa_upvalueid(L, 1, n));
  return 1;
}


static int db_upvaluejoin (killa_State *L) {
  int n1 = checkupval(L, 1, 2);
  int n2 = checkupval(L, 3, 4);
  killaL_argcheck(L, !killa_iscfunction(L, 1), 1, "Killa function expected");
  killaL_argcheck(L, !killa_iscfunction(L, 3), 3, "Killa function expected");
  killa_upvaluejoin(L, 1, n1, 3, n2);
  return 0;
}


#define gethooktable(L)	killaL_getsubtable(L, KILLA_REGISTRYINDEX, HOOKKEY);


static void hookf (killa_State *L, killa_Debug *ar) {
  static const char *const hooknames[] =
    {"call", "return", "line", "count", "tail call"};
  gethooktable(L);
  killa_rawgetp(L, -1, L);
  if (killa_isfunction(L, -1)) {
    killa_pushstring(L, hooknames[(int)ar->event]);
    if (ar->currentline >= 0)
      killa_pushinteger(L, ar->currentline);
    else killa_pushnull(L);
    killa_assert(killa_getinfo(L, "lS", ar));
    killa_call(L, 2, 0);
  }
}


static int makemask (const char *smask, int count) {
  int mask = 0;
  if (strchr(smask, 'c')) mask |= KILLA_MASKCALL;
  if (strchr(smask, 'r')) mask |= KILLA_MASKRET;
  if (strchr(smask, 'l')) mask |= KILLA_MASKLINE;
  if (count > 0) mask |= KILLA_MASKCOUNT;
  return mask;
}


static char *unmakemask (int mask, char *smask) {
  int i = 0;
  if (mask & KILLA_MASKCALL) smask[i++] = 'c';
  if (mask & KILLA_MASKRET) smask[i++] = 'r';
  if (mask & KILLA_MASKLINE) smask[i++] = 'l';
  smask[i] = '\0';
  return smask;
}


static int db_sethook (killa_State *L) {
  int arg, mask, count;
  killa_Hook func;
  killa_State *L1 = getthread(L, &arg);
  if (killa_isnoneornull(L, arg+1)) {
    killa_settop(L, arg+1);
    func = NULL; mask = 0; count = 0;  /* turn off hooks */
  }
  else {
    const char *smask = killaL_checkstring(L, arg+2);
    killaL_checktype(L, arg+1, KILLA_TFUNCTION);
    count = killaL_optint(L, arg+3, 0);
    func = hookf; mask = makemask(smask, count);
  }
  gethooktable(L);
  killa_pushvalue(L, arg+1);
  killa_rawsetp(L, -2, L1);  /* set new hook */
  killa_pop(L, 1);  /* remove hook table */
  killa_sethook(L1, func, mask, count);  /* set hooks */
  return 0;
}


static int db_gethook (killa_State *L) {
  int arg;
  killa_State *L1 = getthread(L, &arg);
  char buff[5];
  int mask = killa_gethookmask(L1);
  killa_Hook hook = killa_gethook(L1);
  if (hook != NULL && hook != hookf)  /* external hook? */
    killa_pushliteral(L, "external hook");
  else {
    gethooktable(L);
    killa_rawgetp(L, -1, L1);   /* get hook */
    killa_remove(L, -2);  /* remove hook table */
  }
  killa_pushstring(L, unmakemask(mask, buff));
  killa_pushinteger(L, killa_gethookcount(L1));
  return 3;
}


static int db_debug (killa_State *L) {
  for (;;) {
    char buffer[250];
    killai_writestringerror("%s", "killa_debug> ");
    if (fgets(buffer, sizeof(buffer), stdin) == 0 ||
        strcmp(buffer, "cont\n") == 0)
      return 0;
    if (killaL_loadbuffer(L, buffer, strlen(buffer), "=(debug command)") ||
        killa_pcall(L, 0, 0, 0))
      killai_writestringerror("%s\n", killa_tostring(L, -1));
    killa_settop(L, 0);  /* remove eventual returns */
  }
}


static int db_traceback (killa_State *L) {
  int arg;
  killa_State *L1 = getthread(L, &arg);
  const char *msg = killa_tostring(L, arg + 1);
  if (msg == NULL && !killa_isnoneornull(L, arg + 1))  /* non-string 'msg'? */
    killa_pushvalue(L, arg + 1);  /* return it untouched */
  else {
    int level = killaL_optint(L, arg + 2, (L == L1) ? 1 : 0);
    killaL_traceback(L, L1, msg, level);
  }
  return 1;
}


static const killaL_Reg dblib[] = {
  {"debug", db_debug},
  {"getuservalue", db_getuservalue},
  {"gethook", db_gethook},
  {"getinfo", db_getinfo},
  {"getlocal", db_getlocal},
  {"getregistry", db_getregistry},
  {"getmetatable", db_getmetatable},
  {"getupvalue", db_getupvalue},
  {"upvaluejoin", db_upvaluejoin},
  {"upvalueid", db_upvalueid},
  {"setuservalue", db_setuservalue},
  {"sethook", db_sethook},
  {"setlocal", db_setlocal},
  {"setmetatable", db_setmetatable},
  {"setupvalue", db_setupvalue},
  {"traceback", db_traceback},
  {NULL, NULL}
};


KILLAMOD_API int killaopen_debug (killa_State *L) {
  killaL_newlib(L, dblib);
  return 1;
}

