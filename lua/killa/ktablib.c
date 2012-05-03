/* ========================================================================== */
/*   Library for Table Manipulation                                           */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stddef.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


#define aux_getn(L,n)  \
	(killaL_checktype(L, n, KILLA_TTABLE), killaL_len(L, n))


#if defined(KILLA_COMPAT_MAXN)
static int maxn (killa_State *L) {
  killa_Number max = 0;
  killaL_checktype(L, 1, KILLA_TTABLE);
  killa_pushnull(L);  /* first key */
  while (killa_next(L, 1)) {
    killa_pop(L, 1);  /* remove value */
    if (killa_type(L, -1) == KILLA_TNUMBER) {
      killa_Number v = killa_tonumber(L, -1);
      if (v > max) max = v;
    }
  }
  killa_pushnumber(L, max);
  return 1;
}
#endif


static int tinsert (killa_State *L) {
  int e = aux_getn(L, 1) + KILLA_BASE;  /* first empty element */
  int pos;  /* where to insert new element */
  switch (killa_gettop(L)) {
    case 2: {  /* called with only 2 arguments */
      pos = e;  /* insert new element at the end */
      break;
    }
    case 3: {
      int i;
      pos = killaL_checkint(L, 2);  /* 2nd argument is the position */
      if (pos > e) e = pos;  /* `grow' array if necessary */
      for (i = e; i > pos; i--) {  /* move up elements */
        killa_rawgeti(L, 1, i-1);
        killa_rawseti(L, 1, i);  /* t[i] = t[i-1] */
      }
#ifdef KILLA_BASE_WARNING
      killaL_warning(L, "using table.insert with base-1 index");
#endif
      break;
    }
    default: {
      return killaL_error(L, "wrong number of arguments to " KILLA_QL("insert"));
    }
  }
  killa_rawseti(L, 1, pos);  /* t[pos] = v */
  return 0;
}


static int tremove (killa_State *L) {
  int e = aux_getn(L, 1);
  int pos = killaL_optint(L, 2, (e + KILLA_BASE - 1));
#ifdef KILLA_BASE_WARNING
  if (killa_gettop(L) > 1) {
    killaL_warning(L, "using table.remove with base-1 index");
  }
#endif
  if (!(KILLA_BASE <= pos && (pos + 1 - KILLA_BASE <= e)))  /* position is outside bounds? */
    return 0;  /* nothing to remove */
  killa_rawgeti(L, 1, pos);  /* result = t[pos] */
  for ( ;pos<e; pos++) {
    killa_rawgeti(L, 1, pos+1);
    killa_rawseti(L, 1, pos);  /* t[pos] = t[pos+1] */
  }
  killa_pushnull(L);
  killa_rawseti(L, 1, e);  /* t[e] = nil */
  return 1;
}


static void addfield (killa_State *L, killaL_Buffer *b, int i) {
  killa_rawgeti(L, 1, i);
  if (!killa_isstring(L, -1))
    killaL_error(L, "invalid value (%s) at index %d in table for "
                  KILLA_QL("concat"), killaL_typename(L, -1), i);
  killaL_addvalue(b);
}


static int tconcat (killa_State *L) {
  killaL_Buffer b;
  size_t lsep;
  int i, last;
  const char *sep = killaL_optlstring(L, 2, "", &lsep);
  killaL_checktype(L, 1, KILLA_TTABLE);
#ifdef KILLA_BASE_WARNING
  if (killa_gettop(L) > 2) {
    killaL_warning(L, "using table.concat with base-1 index");
  }
#endif
  i = killaL_optint(L, 3, KILLA_BASE);
  last = killaL_opt(L, killaL_checkint, 4, killaL_len(L, 1) + KILLA_BASE - 1);
  killaL_buffinit(L, &b);
  for (; i < last; i++) {
    addfield(L, &b, i);
    killaL_addlstring(&b, sep, lsep);
  }
  if (i == last)  /* add last value (if interval was not empty) */
    addfield(L, &b, i);
  killaL_pushresult(&b);
  return 1;
}


/*
** {======================================================
** Pack/unpack
** =======================================================
*/

static int pack (killa_State *L) {
  int n = killa_gettop(L);  /* number of elements to pack */
  killa_createtable(L, n, 1);  /* create result table */
  killa_pushinteger(L, n);
  killa_setfield(L, -2, "n");  /* t.n = number of elements */
  if (n > 0) {  /* at least one element? */
    int i;
    killa_pushvalue(L, 1);
    killa_rawseti(L, -2, 1);  /* insert first element */
    killa_replace(L, 1);  /* move table into index 1 */
    for (i = n; i >= 2; i--)  /* assign other elements */
      killa_rawseti(L, 1, i);
  }
  return 1;  /* return table */
}


static int unpack (killa_State *L) {
  int i, e, n;
  killaL_checktype(L, 1, KILLA_TTABLE);
  i = killaL_optint(L, 2, 1);
  e = killaL_opt(L, killaL_checkint, 3, killaL_len(L, 1));
  if (i > e) return 0;  /* empty range */
  n = e - i + 1;  /* number of elements */
  if (n <= 0 || !killa_checkstack(L, n))  /* n <= 0 means arith. overflow */
    return killaL_error(L, "too many results to unpack");
  killa_rawgeti(L, 1, i);  /* push arg[i] (avoiding overflow problems) */
  while (i++ < e)  /* push arg[i + 1...e] */
    killa_rawgeti(L, 1, i);
  return n;
}

/* }====================================================== */



/*
** {======================================================
** Quicksort
** (based on `Algorithms in MODULA-3', Robert Sedgewick;
**  Addison-Wesley, 1993.)
** =======================================================
*/


static void set2 (killa_State *L, int i, int j) {
  killa_rawseti(L, 1, i);
  killa_rawseti(L, 1, j);
}

static int sort_comp (killa_State *L, int a, int b) {
  if (!killa_isnull(L, 2)) {  /* function? */
    int res;
    killa_pushvalue(L, 2);
    killa_pushvalue(L, a-1);  /* -1 to compensate function */
    killa_pushvalue(L, b-2);  /* -2 to compensate function and `a' */
    killa_call(L, 2, 1);
    res = killa_toboolean(L, -1);
    killa_pop(L, 1);
    return res;
  }
  else  /* a < b? */
    return killa_compare(L, a, b, KILLA_OPLT);
}

static void auxsort (killa_State *L, int l, int u) {
  while (l < u) {  /* for tail recursion */
    int i, j;
    /* sort elements a[l], a[(l+u)/2] and a[u] */
    killa_rawgeti(L, 1, l);
    killa_rawgeti(L, 1, u);
    if (sort_comp(L, -1, -2))  /* a[u] < a[l]? */
      set2(L, l, u);  /* swap a[l] - a[u] */
    else
      killa_pop(L, 2);
    if (u-l == 1) break;  /* only 2 elements */
    i = (l+u)/2;
    killa_rawgeti(L, 1, i);
    killa_rawgeti(L, 1, l);
    if (sort_comp(L, -2, -1))  /* a[i]<a[l]? */
      set2(L, i, l);
    else {
      killa_pop(L, 1);  /* remove a[l] */
      killa_rawgeti(L, 1, u);
      if (sort_comp(L, -1, -2))  /* a[u]<a[i]? */
        set2(L, i, u);
      else
        killa_pop(L, 2);
    }
    if (u-l == 2) break;  /* only 3 elements */
    killa_rawgeti(L, 1, i);  /* Pivot */
    killa_pushvalue(L, -1);
    killa_rawgeti(L, 1, u-1);
    set2(L, i, u-1);
    /* a[l] <= P == a[u-1] <= a[u], only need to sort from l+1 to u-2 */
    i = l; j = u-1;
    for (;;) {  /* invariant: a[l..i] <= P <= a[j..u] */
      /* repeat ++i until a[i] >= P */
      while (killa_rawgeti(L, 1, ++i), sort_comp(L, -1, -2)) {
        if (i>=u) killaL_error(L, "invalid order function for sorting");
        killa_pop(L, 1);  /* remove a[i] */
      }
      /* repeat --j until a[j] <= P */
      while (killa_rawgeti(L, 1, --j), sort_comp(L, -3, -1)) {
        if (j<=l) killaL_error(L, "invalid order function for sorting");
        killa_pop(L, 1);  /* remove a[j] */
      }
      if (j<i) {
        killa_pop(L, 3);  /* pop pivot, a[i], a[j] */
        break;
      }
      set2(L, i, j);
    }
    killa_rawgeti(L, 1, u-1);
    killa_rawgeti(L, 1, i);
    set2(L, u-1, i);  /* swap pivot (a[u-1]) with a[i] */
    /* a[l..i-1] <= a[i] == P <= a[i+1..u] */
    /* adjust so that smaller half is in [j..i] and larger one in [l..u] */
    if (i-l < u-i) {
      j=l; i=i-1; l=i+2;
    }
    else {
      j=i+1; i=u; u=j-2;
    }
    auxsort(L, j, i);  /* call recursively the smaller one */
  }  /* repeat the routine for the larger one */
}

static int sort (killa_State *L) {
  int n = aux_getn(L, 1) + KILLA_BASE - 1;
  killaL_checkstack(L, 40, "");  /* assume array is smaller than 2^40 */
  if (!killa_isnoneornull(L, 2))  /* is there a 2nd argument? */
    killaL_checktype(L, 2, KILLA_TFUNCTION);
  killa_settop(L, 2);  /* make sure there is two arguments */
  auxsort(L, KILLA_BASE, n);
  return 0;
}

/* }====================================================== */


static const killaL_Reg tab_funcs[] = {
  {"concat", tconcat},
#if defined(KILLA_COMPAT_MAXN)
  {"maxn", maxn},
#endif
  {"insert", tinsert},
  {"pack", pack},
  {"unpack", unpack},
  {"remove", tremove},
  {"sort", sort},
  {NULL, NULL}
};


KILLAMOD_API int killaopen_table (killa_State *L) {
  killaL_newlib(L, tab_funcs);
#if defined(KILLA_COMPAT_UNPACK)
  /* _G.unpack = table.unpack */
  killa_getfield(L, -1, "unpack");
  killa_setglobal(L, "unpack");
#endif
  return 1;
}

