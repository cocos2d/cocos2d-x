/* ========================================================================== */
/*   Standard mathematical library                                            */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <math.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


#undef PI
#define PI (3.14159265358979323846)
#define RADIANS_PER_DEGREE (PI/180.0)


/* macro 'l_tg' allows the addition of an 'l' or 'f' to all math operations */
#if !defined(l_tg)
#define l_tg(x)		(x)
#endif



static int math_abs (killa_State *L) {
  killa_pushnumber(L, l_tg(fabs)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_sin (killa_State *L) {
  killa_pushnumber(L, l_tg(sin)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_sinh (killa_State *L) {
  killa_pushnumber(L, l_tg(sinh)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_cos (killa_State *L) {
  killa_pushnumber(L, l_tg(cos)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_cosh (killa_State *L) {
  killa_pushnumber(L, l_tg(cosh)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_tan (killa_State *L) {
  killa_pushnumber(L, l_tg(tan)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_tanh (killa_State *L) {
  killa_pushnumber(L, l_tg(tanh)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_asin (killa_State *L) {
  killa_pushnumber(L, l_tg(asin)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_acos (killa_State *L) {
  killa_pushnumber(L, l_tg(acos)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_atan (killa_State *L) {
  killa_pushnumber(L, l_tg(atan)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_atan2 (killa_State *L) {
  killa_pushnumber(L, l_tg(atan2)(killaL_checknumber(L, 1),
                                killaL_checknumber(L, 2)));
  return 1;
}

static int math_ceil (killa_State *L) {
  killa_pushnumber(L, l_tg(ceil)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_floor (killa_State *L) {
  killa_pushnumber(L, l_tg(floor)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_fmod (killa_State *L) {
  killa_pushnumber(L, l_tg(fmod)(killaL_checknumber(L, 1),
                               killaL_checknumber(L, 2)));
  return 1;
}

static int math_modf (killa_State *L) {
  killa_Number ip;
  killa_Number fp = l_tg(modf)(killaL_checknumber(L, 1), &ip);
  killa_pushnumber(L, ip);
  killa_pushnumber(L, fp);
  return 2;
}

static int math_sqrt (killa_State *L) {
  killa_pushnumber(L, l_tg(sqrt)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_pow (killa_State *L) {
  killa_pushnumber(L, l_tg(pow)(killaL_checknumber(L, 1),
                              killaL_checknumber(L, 2)));
  return 1;
}

static int math_log (killa_State *L) {
  killa_Number x = killaL_checknumber(L, 1);
  killa_Number res;
  if (killa_isnoneornull(L, 2))
    res = l_tg(log)(x);
  else {
    killa_Number base = killaL_checknumber(L, 2);
    if (base == 10.0) res = l_tg(log10)(x);
    else res = l_tg(log)(x)/l_tg(log)(base);
  }
  killa_pushnumber(L, res);
  return 1;
}

#if defined(KILLA_COMPAT_LOG10)
static int math_log10 (killa_State *L) {
  killa_pushnumber(L, l_tg(log10)(killaL_checknumber(L, 1)));
  return 1;
}
#endif

static int math_exp (killa_State *L) {
  killa_pushnumber(L, l_tg(exp)(killaL_checknumber(L, 1)));
  return 1;
}

static int math_deg (killa_State *L) {
  killa_pushnumber(L, killaL_checknumber(L, 1)/RADIANS_PER_DEGREE);
  return 1;
}

static int math_rad (killa_State *L) {
  killa_pushnumber(L, killaL_checknumber(L, 1)*RADIANS_PER_DEGREE);
  return 1;
}

static int math_frexp (killa_State *L) {
  int e;
  killa_pushnumber(L, l_tg(frexp)(killaL_checknumber(L, 1), &e));
  killa_pushinteger(L, e);
  return 2;
}

static int math_ldexp (killa_State *L) {
  killa_pushnumber(L, l_tg(ldexp)(killaL_checknumber(L, 1),
                                killaL_checkint(L, 2)));
  return 1;
}



static int math_min (killa_State *L) {
  int n = killa_gettop(L);  /* number of arguments */
  killa_Number dmin = killaL_checknumber(L, 1);
  int i;
  for (i=2; i<=n; i++) {
    killa_Number d = killaL_checknumber(L, i);
    if (d < dmin)
      dmin = d;
  }
  killa_pushnumber(L, dmin);
  return 1;
}


static int math_max (killa_State *L) {
  int n = killa_gettop(L);  /* number of arguments */
  killa_Number dmax = killaL_checknumber(L, 1);
  int i;
  for (i=2; i<=n; i++) {
    killa_Number d = killaL_checknumber(L, i);
    if (d > dmax)
      dmax = d;
  }
  killa_pushnumber(L, dmax);
  return 1;
}


static int math_random (killa_State *L) {
  /* the `%' avoids the (rare) case of r==1, and is needed also because on
     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
  killa_Number r = (killa_Number)(rand()%RAND_MAX) / (killa_Number)RAND_MAX;
  switch (killa_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      killa_pushnumber(L, r);  /* Number between 0 and 1 */
      break;
    }
    case 1: {  /* only upper limit */
      killa_Number u = killaL_checknumber(L, 1);
      killaL_argcheck(L, 1.0 <= u, 1, "interval is empty");
      killa_pushnumber(L, l_tg(floor)(r*u) + 1.0);  /* int in [1, u] */
      break;
    }
    case 2: {  /* lower and upper limits */
      killa_Number l = killaL_checknumber(L, 1);
      killa_Number u = killaL_checknumber(L, 2);
      killaL_argcheck(L, l <= u, 2, "interval is empty");
      killa_pushnumber(L, l_tg(floor)(r*(u-l+1)) + l);  /* int in [l, u] */
      break;
    }
    default: return killaL_error(L, "wrong number of arguments");
  }
  return 1;
}


static int math_randomseed (killa_State *L) {
  srand(killaL_checkunsigned(L, 1));
  (void)rand(); /* discard first value to avoid undesirable correlations */
  return 0;
}


static const killaL_Reg mathlib[] = {
  {"abs",   math_abs},
  {"acos",  math_acos},
  {"asin",  math_asin},
  {"atan2", math_atan2},
  {"atan",  math_atan},
  {"ceil",  math_ceil},
  {"cosh",   math_cosh},
  {"cos",   math_cos},
  {"deg",   math_deg},
  {"exp",   math_exp},
  {"floor", math_floor},
  {"fmod",   math_fmod},
  {"frexp", math_frexp},
  {"ldexp", math_ldexp},
#if defined(KILLA_COMPAT_LOG10)
  {"log10", math_log10},
#endif
  {"log",   math_log},
  {"max",   math_max},
  {"min",   math_min},
  {"modf",   math_modf},
  {"pow",   math_pow},
  {"rad",   math_rad},
  {"random",     math_random},
  {"randomseed", math_randomseed},
  {"sinh",   math_sinh},
  {"sin",   math_sin},
  {"sqrt",  math_sqrt},
  {"tanh",   math_tanh},
  {"tan",   math_tan},
  {NULL, NULL}
};


/*
** Open math library
*/
KILLAMOD_API int killaopen_math (killa_State *L) {
  killaL_newlib(L, mathlib);
  killa_pushnumber(L, PI);
  killa_setfield(L, -2, "pi");
  killa_pushnumber(L, HUGE_VAL);
  killa_setfield(L, -2, "huge");
  return 1;
}

