/* ========================================================================== */
/*   Standard library for bitwise operations                                  */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


/* number of bits to consider in a number */
#if !defined(KILLA_NBITS)
#define KILLA_NBITS	32
#endif


#define ALLONES		(~(((~(killa_Unsigned)0) << (KILLA_NBITS - 1)) << 1))

/* macro to trim extra bits */
#define trim(x)		((x) & ALLONES)


/* builds a number with 'n' ones (1 <= n <= KILLA_NBITS) */
#define mask(n)		(~((ALLONES << 1) << ((n) - 1)))


typedef killa_Unsigned b_uint;



static b_uint andaux (killa_State *L) {
  int i, n = killa_gettop(L);
  b_uint r = ~(b_uint)0;
  for (i = 1; i <= n; i++)
    r &= killaL_checkunsigned(L, i);
  return trim(r);
}


static int b_and (killa_State *L) {
  b_uint r = andaux(L);
  killa_pushunsigned(L, r);
  return 1;
}


static int b_test (killa_State *L) {
  b_uint r = andaux(L);
  killa_pushboolean(L, r != 0);
  return 1;
}


static int b_or (killa_State *L) {
  int i, n = killa_gettop(L);
  b_uint r = 0;
  for (i = 1; i <= n; i++)
    r |= killaL_checkunsigned(L, i);
  killa_pushunsigned(L, trim(r));
  return 1;
}


static int b_xor (killa_State *L) {
  int i, n = killa_gettop(L);
  b_uint r = 0;
  for (i = 1; i <= n; i++)
    r ^= killaL_checkunsigned(L, i);
  killa_pushunsigned(L, trim(r));
  return 1;
}


static int b_not (killa_State *L) {
  b_uint r = ~killaL_checkunsigned(L, 1);
  killa_pushunsigned(L, trim(r));
  return 1;
}


static int b_shift (killa_State *L, b_uint r, int i) {
  if (i < 0) {  /* shift right? */
    i = -i;
    r = trim(r);
    if (i >= KILLA_NBITS) r = 0;
    else r >>= i;
  }
  else {  /* shift left */
    if (i >= KILLA_NBITS) r = 0;
    else r <<= i;
    r = trim(r);
  }
  killa_pushunsigned(L, r);
  return 1;
}


static int b_lshift (killa_State *L) {
  return b_shift(L, killaL_checkunsigned(L, 1), killaL_checkint(L, 2));
}


static int b_rshift (killa_State *L) {
  return b_shift(L, killaL_checkunsigned(L, 1), -killaL_checkint(L, 2));
}


static int b_arshift (killa_State *L) {
  b_uint r = killaL_checkunsigned(L, 1);
  int i = killaL_checkint(L, 2);
  if (i < 0 || !(r & ((b_uint)1 << (KILLA_NBITS - 1))))
    return b_shift(L, r, -i);
  else {  /* arithmetic shift for 'negative' number */
    if (i >= KILLA_NBITS) r = ALLONES;
    else
      r = trim((r >> i) | ~(~(b_uint)0 >> i));  /* add signal bit */
    killa_pushunsigned(L, r);
    return 1;
  }
}


static int b_rot (killa_State *L, int i) {
  b_uint r = killaL_checkunsigned(L, 1);
  i &= (KILLA_NBITS - 1);  /* i = i % NBITS */
  r = trim(r);
  r = (r << i) | (r >> (KILLA_NBITS - i));
  killa_pushunsigned(L, trim(r));
  return 1;
}


static int b_lrot (killa_State *L) {
  return b_rot(L, killaL_checkint(L, 2));
}


static int b_rrot (killa_State *L) {
  return b_rot(L, -killaL_checkint(L, 2));
}


/*
** get field and width arguments for field-manipulation functions,
** checking whether they are valid
*/
static int fieldargs (killa_State *L, int farg, int *width) {
  int f = killaL_checkint(L, farg);
  int w = killaL_optint(L, farg + 1, 1);
  killaL_argcheck(L, 0 <= f, farg, "field cannot be negative");
  killaL_argcheck(L, 0 < w, farg + 1, "width must be positive");
  if (f + w > KILLA_NBITS)
    killaL_error(L, "trying to access non-existent bits");
  *width = w;
  return f;
}


static int b_extract (killa_State *L) {
  int w;
  b_uint r = killaL_checkunsigned(L, 1);
  int f = fieldargs(L, 2, &w);
  r = (r >> f) & mask(w);
  killa_pushunsigned(L, r);
  return 1;
}


static int b_replace (killa_State *L) {
  int w;
  b_uint r = killaL_checkunsigned(L, 1);
  b_uint v = killaL_checkunsigned(L, 2);
  int f = fieldargs(L, 3, &w);
  int m = mask(w);
  v &= m;  /* erase bits outside given width */
  r = (r & ~(m << f)) | (v << f);
  killa_pushunsigned(L, r);
  return 1;
}


static const killaL_Reg bitlib[] = {
  {"arshift", b_arshift},
  {"band", b_and},
  {"bnot", b_not},
  {"bor", b_or},
  {"bxor", b_xor},
  {"btest", b_test},
  {"extract", b_extract},
  {"lrotate", b_lrot},
  {"lshift", b_lshift},
  {"replace", b_replace},
  {"rrotate", b_rrot},
  {"rshift", b_rshift},
  {NULL, NULL}
};



KILLAMOD_API int killaopen_bit32 (killa_State *L) {
  killaL_newlib(L, bitlib);
  return 1;
}

