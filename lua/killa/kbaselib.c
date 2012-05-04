/* ========================================================================== */
/*   Basic library                                                            */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


static int killaB_print (killa_State *L) {
  int n = killa_gettop(L);  /* number of arguments */
  int i;
  killa_getglobal(L, "tostring");
  for (i=1; i<=n; i++) {
    const char *s;
    size_t l;
    killa_pushvalue(L, -1);  /* function to be called */
    killa_pushvalue(L, i);   /* value to print */
    killa_call(L, 1, 1);
    s = killa_tolstring(L, -1, &l);  /* get result */
    if (s == NULL)
      return killaL_error(L,
         KILLA_QL("tostring") " must return a string to " KILLA_QL("print"));
    if (i>1) killai_writestring("\t", 1);
    killai_writestring(s, l);
    killa_pop(L, 1);  /* pop result */
  }
  killai_writeline();
  return 0;
}


#define SPACECHARS	" \f\n\r\t\v"

static int killaB_tonumber (killa_State *L) {
  if (killa_isnoneornull(L, 2)) {  /* standard conversion */
    int isnum;
    killa_Number n = killa_tonumberx(L, 1, &isnum);
    if (isnum) {
      killa_pushnumber(L, n);
      return 1;
    }  /* else not a number; must be something */
    killaL_checkany(L, 1);
  }
  else {
    size_t l;
    const char *s = killaL_checklstring(L, 1, &l);
    const char *e = s + l;  /* end point for 's' */
    int base = killaL_checkint(L, 2);
    int neg = 0;
    killaL_argcheck(L, 2 <= base && base <= 36, 2, "base out of range");
    s += strspn(s, SPACECHARS);  /* skip initial spaces */
    if (*s == '-') { s++; neg = 1; }  /* handle signal */
    else if (*s == '+') s++;
    if (isalnum((unsigned char)*s)) {
      killa_Number n = 0;
      do {
        int digit = (isdigit((unsigned char)*s)) ? *s - '0'
                       : toupper((unsigned char)*s) - 'A' + 10;
        if (digit >= base) break;  /* invalid numeral; force a fail */
        n = n * (killa_Number)base + (killa_Number)digit;
        s++;
      } while (isalnum((unsigned char)*s));
      s += strspn(s, SPACECHARS);  /* skip trailing spaces */
      if (s == e) {  /* no invalid trailing characters? */
        killa_pushnumber(L, (neg) ? -n : n);
        return 1;
      }  /* else not a number */
    }  /* else not a number */
  }
  killa_pushnull(L);  /* not a number */
  return 1;
}


static int killaB_error (killa_State *L) {
  int level = killaL_optint(L, 2, 1);
  killa_settop(L, 1);
  if (killa_isstring(L, 1) && level > 0) {  /* add extra information? */
    killaL_where(L, level);
    killa_pushvalue(L, 1);
    killa_concat(L, 2);
  }
  return killa_error(L);
}


static int killaB_getmetatable (killa_State *L) {
  killaL_checkany(L, 1);
  if (!killa_getmetatable(L, 1)) {
    killa_pushnull(L);
    return 1;  /* no metatable */
  }
  killaL_getmetafield(L, 1, "__metatable");
  return 1;  /* returns either __metatable field (if present) or metatable */
}


static int killaB_setmetatable (killa_State *L) {
  int t = killa_type(L, 2);
  killaL_checktype(L, 1, KILLA_TTABLE);
  killaL_argcheck(L, t == KILLA_TNULL || t == KILLA_TTABLE, 2,
                    "null or table expected");
  if (killaL_getmetafield(L, 1, "__metatable"))
    return killaL_error(L, "cannot change a protected metatable");
  killa_settop(L, 2);
  killa_setmetatable(L, 1);
  return 1;
}


static int killaB_rawequal (killa_State *L) {
  killaL_checkany(L, 1);
  killaL_checkany(L, 2);
  killa_pushboolean(L, killa_rawequal(L, 1, 2));
  return 1;
}


static int killaB_rawlen (killa_State *L) {
  int t = killa_type(L, 1);
  killaL_argcheck(L, t == KILLA_TTABLE || t == KILLA_TSTRING, 1,
                   "table or string expected");
  killa_pushinteger(L, killa_rawlen(L, 1));
  return 1;
}


static int killaB_rawget (killa_State *L) {
  killaL_checktype(L, 1, KILLA_TTABLE);
  killaL_checkany(L, 2);
  killa_settop(L, 2);
  killa_rawget(L, 1);
  return 1;
}

static int killaB_rawset (killa_State *L) {
  killaL_checktype(L, 1, KILLA_TTABLE);
  killaL_checkany(L, 2);
  killaL_checkany(L, 3);
  killa_settop(L, 3);
  killa_rawset(L, 1);
  return 1;
}


static int killaB_collectgarbage (killa_State *L) {
  static const char *const opts[] = {"stop", "restart", "collect",
    "count", "step", "setpause", "setstepmul",
    "setmajorinc", "isrunning", "generational", "incremental", NULL};
  static const int optsnum[] = {KILLA_GCSTOP, KILLA_GCRESTART, KILLA_GCCOLLECT,
    KILLA_GCCOUNT, KILLA_GCSTEP, KILLA_GCSETPAUSE, KILLA_GCSETSTEPMUL,
    KILLA_GCSETMAJORINC, KILLA_GCISRUNNING, KILLA_GCGEN, KILLA_GCINC};
  int o = optsnum[killaL_checkoption(L, 1, "collect", opts)];
  int ex = killaL_optint(L, 2, 0);
  int res = killa_gc(L, o, ex);
  switch (o) {
    case KILLA_GCCOUNT: {
      int b = killa_gc(L, KILLA_GCCOUNTB, 0);
      killa_pushnumber(L, res + ((killa_Number)b/1024));
      killa_pushinteger(L, b);
      return 2;
    }
    case KILLA_GCSTEP: case KILLA_GCISRUNNING: {
      killa_pushboolean(L, res);
      return 1;
    }
    default: {
      killa_pushinteger(L, res);
      return 1;
    }
  }
}


static int killaB_type (killa_State *L) {
  killaL_checkany(L, 1);
  killa_pushstring(L, killaL_typename(L, 1));
  return 1;
}


static int pairsmeta (killa_State *L, const char *method, int iszero,
                      killa_CFunction iter) {
  if (!killaL_getmetafield(L, 1, method)) {  /* no metamethod? */
    killaL_checktype(L, 1, KILLA_TTABLE);  /* argument must be a table */
    killa_pushcfunction(L, iter);  /* will return generator, */
    killa_pushvalue(L, 1);  /* state, */
    if (iszero)
        killa_pushinteger(L, KILLA_BASE - 1);  /* and initial value */
    else
        killa_pushnull(L);
  }
  else {
    killa_pushvalue(L, 1);  /* argument 'self' to metamethod */
    killa_call(L, 1, 3);  /* get 3 values from metamethod */
  }
  return 3;
}


static int killaB_next (killa_State *L) {
  killaL_checktype(L, 1, KILLA_TTABLE);
  killa_settop(L, 2);  /* create a 2nd argument if there isn't one */
  if (killa_next(L, 1))
    return 2;
  else {
    killa_pushnull(L);
    return 1;
  }
}


static int killaB_pairs (killa_State *L) {
  return pairsmeta(L, "__pairs", 0, killaB_next);
}


static int ipairsaux (killa_State *L) {
  int i = killaL_checkint(L, 2);
  killaL_checktype(L, 1, KILLA_TTABLE);
  i++;  /* next value */
  killa_pushinteger(L, i);
  killa_rawgeti(L, 1, i);
  return (killa_isnull(L, -1)) ? 1 : 2;
}


static int killaB_ipairs (killa_State *L) {
  return pairsmeta(L, "__ipairs", 1, ipairsaux);
}


static int load_aux (killa_State *L, int status) {
  if (status == KILLA_OK)
    return 1;
  else {
    killa_pushnull(L);
    killa_insert(L, -2);  /* put before error message */
    return 2;  /* return nil plus error message */
  }
}


static int killaB_loadfile (killa_State *L) {
  const char *fname = killaL_optstring(L, 1, NULL);
  const char *mode = killaL_optstring(L, 2, NULL);
  int env = !killa_isnone(L, 3);  /* 'env' parameter? */
  int status = killaL_loadfilex(L, fname, mode);
  if (status == KILLA_OK && env) {  /* 'env' parameter? */
    killa_pushvalue(L, 3);
    killa_setupvalue(L, -2, 1);  /* set it as 1st upvalue of loaded chunk */
  }
  return load_aux(L, status);
}


/*
** {======================================================
** Generic Read function
** =======================================================
*/


/*
** reserved slot, above all arguments, to hold a copy of the returned
** string to avoid it being collected while parsed. 'load' has four
** optional arguments (chunk, source name, mode, and environment).
*/
#define RESERVEDSLOT	5


/*
** Reader for generic `load' function: `killa_load' uses the
** stack for internal stuff, so the reader cannot change the
** stack top. Instead, it keeps its resulting string in a
** reserved slot inside the stack.
*/
static const char *generic_reader (killa_State *L, void *ud, size_t *size) {
  (void)(ud);  /* not used */
  killaL_checkstack(L, 2, "too many nested functions");
  killa_pushvalue(L, 1);  /* get function */
  killa_call(L, 0, 1);  /* call it */
  if (killa_isnull(L, -1)) {
    *size = 0;
    return NULL;
  }
  else if (!killa_isstring(L, -1))
    killaL_error(L, "reader function must return a string");
  killa_replace(L, RESERVEDSLOT);  /* save string in reserved slot */
  return killa_tolstring(L, RESERVEDSLOT, size);
}


static int killaB_load (killa_State *L) {
  int status;
  size_t l;
  int top = killa_gettop(L);
  const char *s = killa_tolstring(L, 1, &l);
  const char *mode = killaL_optstring(L, 3, "bt");
  if (s != NULL) {  /* loading a string? */
    const char *chunkname = killaL_optstring(L, 2, s);
    status = killaL_loadbufferx(L, s, l, chunkname, mode);
  }
  else {  /* loading from a reader function */
    const char *chunkname = killaL_optstring(L, 2, "=(load)");
    killaL_checktype(L, 1, KILLA_TFUNCTION);
    killa_settop(L, RESERVEDSLOT);  /* create reserved slot */
    status = killa_load(L, generic_reader, NULL, chunkname, mode);
  }
  if (status == KILLA_OK && top >= 4) {  /* is there an 'env' argument */
    killa_pushvalue(L, 4);  /* environment for loaded function */
    killa_setupvalue(L, -2, 1);  /* set it as 1st upvalue */
  }
  return load_aux(L, status);
}

/* }====================================================== */


static int dofilecont (killa_State *L) {
  return killa_gettop(L) - 1;
}


static int killaB_dofile (killa_State *L) {
  const char *fname = killaL_optstring(L, 1, NULL);
  killa_settop(L, 1);
  if (killaL_loadfile(L, fname) != KILLA_OK) killa_error(L);
  killa_callk(L, 0, KILLA_MULTRET, 0, dofilecont);
  return dofilecont(L);
}


static int killaB_assert (killa_State *L) {
  if (!killa_toboolean(L, 1))
    return killaL_error(L, "%s", killaL_optstring(L, 2, "assertion failed!"));
  return killa_gettop(L);
}


static int killaB_select (killa_State *L) {
  int n = killa_gettop(L);
  if (killa_type(L, 1) == KILLA_TSTRING && *killa_tostring(L, 1) == '#') {
    killa_pushinteger(L, n-1);
    return 1;
  }
  else {
    int i = killaL_checkint(L, 1);
    if (i < 0) i = n + i;
    else if (i > n) i = n;
    killaL_argcheck(L, 1 <= i, 1, "index out of range");
    return n - i;
  }
}


static int finishpcall (killa_State *L, int status) {
  if (!killa_checkstack(L, 1)) {  /* no space for extra boolean? */
    killa_settop(L, 0);  /* create space for return values */
    killa_pushboolean(L, 0);
    killa_pushstring(L, "stack overflow");
    return 2;  /* return false, msg */
  }
  killa_pushboolean(L, status);  /* first result (status) */
  killa_replace(L, 1);  /* put first result in first slot */
  return killa_gettop(L);
}


static int pcallcont (killa_State *L) {
  int status = killa_getctx(L, NULL);
  return finishpcall(L, (status == KILLA_YIELD));
}


static int killaB_pcall (killa_State *L) {
  int status;
  killaL_checkany(L, 1);
  killa_pushnull(L);
  killa_insert(L, 1);  /* create space for status result */
  status = killa_pcallk(L, killa_gettop(L) - 2, KILLA_MULTRET, 0, 0, pcallcont);
  return finishpcall(L, (status == KILLA_OK));
}


static int killaB_xpcall (killa_State *L) {
  int status;
  int n = killa_gettop(L);
  killaL_argcheck(L, n >= 2, 2, "value expected");
  killa_pushvalue(L, 1);  /* exchange function... */
  killa_copy(L, 2, 1);  /* ...and error handler */
  killa_replace(L, 2);
  status = killa_pcallk(L, n - 2, KILLA_MULTRET, 1, 0, pcallcont);
  return finishpcall(L, (status == KILLA_OK));
}


static int killaB_tostring (killa_State *L) {
  killaL_checkany(L, 1);
  killaL_tolstring(L, 1, NULL);
  return 1;
}


static const killaL_Reg base_funcs[] = {
  {"assert", killaB_assert},
  {"collectgarbage", killaB_collectgarbage},
  {"dofile", killaB_dofile},
  {"error", killaB_error},
  {"getmetatable", killaB_getmetatable},
  {"ipairs", killaB_ipairs},
  {"loadfile", killaB_loadfile},
  {"load", killaB_load},
#if defined(KILLA_COMPAT_LOADSTRING)
  {"loadstring", killaB_load},
#endif
  {"next", killaB_next},
  {"pairs", killaB_pairs},
  {"pcall", killaB_pcall},
  {"print", killaB_print},
  {"rawequal", killaB_rawequal},
  {"rawlen", killaB_rawlen},
  {"rawget", killaB_rawget},
  {"rawset", killaB_rawset},
  {"select", killaB_select},
  {"setmetatable", killaB_setmetatable},
  {"tonumber", killaB_tonumber},
  {"tostring", killaB_tostring},
  {"type", killaB_type},
  {"xpcall", killaB_xpcall},
  {NULL, NULL}
};


KILLAMOD_API int killaopen_base (killa_State *L) {
  /* set global _G */
  killa_pushglobaltable(L);
  killa_pushglobaltable(L);
  killa_setfield(L, -2, "_G");
  /* open lib into global table */
  killaL_setfuncs(L, base_funcs, 0);
  killa_pushliteral(L, KILLA_VERSION);
  killa_setfield(L, -2, "_VERSION");  /* set global _VERSION */
  return 1;
}

