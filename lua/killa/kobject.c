/* ========================================================================== */
/*   Some generic functions over Killa objects                                */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KOBJECT_C_
#define KILLA_CORE

#include "killa.h"

#include "kctype.h"
#include "kdebug.h"
#include "kdo.h"
#include "kmem.h"
#include "kobject.h"
#include "kstate.h"
#include "kstring.h"
#include "kvm.h"



KILLAI_DDEF const killa_TValue killaO_nilobject_ = {KILLA_NILCONSTANT};


/*
** converts an integer to a "floating point byte", represented as
** (eeeeexxx), where the real value is (1xxx) * 2^(eeeee - 1) if
** eeeee != 0 and (xxx) otherwise.
*/
int killaO_int2fb (unsigned int x) {
  int e = 0;  /* exponent */
  if (x < 8) return x;
  while (x >= 0x10) {
    x = (x+1) >> 1;
    e++;
  }
  return ((e+1) << 3) | (killa_cast_int(x) - 8);
}


/* converts back */
int killaO_fb2int (int x) {
  int e = (x >> 3) & 0x1f;
  if (e == 0) return x;
  else return ((x & 7) + 8) << (e - 1);
}


int killaO_ceillog2 (unsigned int x) {
  static const killa_ubyte log_2[256] = {
    0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
  };
  int l = 0;
  x--;
  while (x >= 256) { l += 8; x >>= 8; }
  return l + log_2[x];
}


killa_Number killaO_arith (int op, killa_Number v1, killa_Number v2) {
  switch (op) {
    case KILLA_OPADD: return killai_numadd(NULL, v1, v2);
    case KILLA_OPSUB: return killai_numsub(NULL, v1, v2);
    case KILLA_OPMUL: return killai_nummul(NULL, v1, v2);
    case KILLA_OPDIV: return killai_numdiv(NULL, v1, v2);
    case KILLA_OPMOD: return killai_nummod(NULL, v1, v2);
    case KILLA_OPPOW: return killai_numpow(NULL, v1, v2);
    case KILLA_OPUNM: return killai_numunm(NULL, v1);
    default: killa_assert(0); return 0;
  }
}


int killaO_hexavalue (int c) {
  if (killa_isdigit(c)) return c - '0';
  else return killa_tolower(c) - 'a' + 10;
}


#if !defined(killa_strx2number)

#include <math.h>


static int isneg (const char **s) {
  if (**s == '-') { (*s)++; return 1; }
  else if (**s == '+') (*s)++;
  return 0;
}


static killa_Number readhexa (const char **s, killa_Number r, int *count) {
  for (; killa_isxdigit(killa_cast_uchar(**s)); (*s)++) {  /* read integer part */
    r = (r * 16.0) + killa_cast_num(killaO_hexavalue(killa_cast_uchar(**s)));
    (*count)++;
  }
  return r;
}


/*
** convert an hexadecimal numeric string to a number, following
** C99 specification for 'strtod'
*/
static killa_Number killa_strx2number (const char *s, char **endptr) {
  killa_Number r = 0.0;
  int e = 0, i = 0;
  int neg = 0;  /* 1 if number is negative */
  *endptr = killa_cast(char *, s);  /* nothing is valid yet */
  while (killa_isspace(killa_cast_uchar(*s))) s++;  /* skip initial spaces */
  neg = isneg(&s);  /* check signal */
  if (!(*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X')))  /* check '0x' */
    return 0.0;  /* invalid format (no '0x') */
  s += 2;  /* skip '0x' */
  r = readhexa(&s, r, &i);  /* read integer part */
  if (*s == '.') {
    s++;  /* skip dot */
    r = readhexa(&s, r, &e);  /* read fractional part */
  }
  if (i == 0 && e == 0)
    return 0.0;  /* invalid format (no digit) */
  e *= -4;  /* each fractional digit divides value by 2^-4 */
  *endptr = killa_cast(char *, s);  /* valid up to here */
  if (*s == 'p' || *s == 'P') {  /* exponent part? */
    int exp1 = 0;
    int neg1;
    s++;  /* skip 'p' */
    neg1 = isneg(&s);  /* signal */
    if (!killa_isdigit(killa_cast_uchar(*s)))
      goto ret;  /* must have at least one digit */
    while (killa_isdigit(killa_cast_uchar(*s)))  /* read exponent */
      exp1 = exp1 * 10 + *(s++) - '0';
    if (neg1) exp1 = -exp1;
    e += exp1;
  }
  *endptr = killa_cast(char *, s);  /* valid up to here */
 ret:
  if (neg) r = -r;
  return ldexp(r, e);
}

#endif


int killaO_str2d (const char *s, size_t len, killa_Number *result) {
  char *endptr;
  if (strpbrk(s, "nN"))  /* reject 'inf' and 'nan' */
    return 0;
  else if (strpbrk(s, "xX"))  /* hexa? */
    *result = killa_strx2number(s, &endptr);
  else
    *result = killa_str2number(s, &endptr);
  if (endptr == s) return 0;  /* nothing recognized */
  while (killa_isspace(killa_cast_uchar(*endptr))) endptr++;
  return (endptr == s + len);  /* OK if no trailing characters */
}



static void pushstr (killa_State *L, const char *str, size_t l) {
  killa_setsvalue2s(L, L->top, killaS_newlstr(L, str, l));
  killa_incr_top(L);
}


/* this function handles only `%d', `%c', %f, %p, and `%s' formats */
const char *killaO_pushvfstring (killa_State *L, const char *fmt, va_list argp) {
  int n = 0;
  for (;;) {
    const char *e = strchr(fmt, '%');
    if (e == NULL) break;
    killa_setsvalue2s(L, L->top, killaS_newlstr(L, fmt, e-fmt));
    killa_incr_top(L);
    switch (*(e+1)) {
      case 's': {
        const char *s = va_arg(argp, char *);
        if (s == NULL) s = "(null)";
        pushstr(L, s, strlen(s));
        break;
      }
      case 'c': {
        char buff;
        buff = killa_cast(char, va_arg(argp, int));
        pushstr(L, &buff, 1);
        break;
      }
      case 'd': {
        killa_setnvalue(L->top, killa_cast_num(va_arg(argp, int)));
        killa_incr_top(L);
        break;
      }
      case 'f': {
        killa_setnvalue(L->top, killa_cast_num(va_arg(argp, killa_uacNumber)));
        killa_incr_top(L);
        break;
      }
      case 'p': {
        char buff[4*sizeof(void *) + 8]; /* should be enough space for a `%p' */
        int l = sprintf(buff, "%p", va_arg(argp, void *));
        pushstr(L, buff, l);
        break;
      }
      case '%': {
        pushstr(L, "%", 1);
        break;
      }
      default: {
        killaG_runerror(L,
            "invalid option " KILLA_QL("%%%c") " to " KILLA_QL("killa_pushfstring"),
            *(e + 1));
      }
    }
    n += 2;
    fmt = e+2;
  }
  pushstr(L, fmt, strlen(fmt));
  if (n > 0) killaV_concat(L, n + 1);
  return killa_svalue(L->top - 1);
}


const char *killaO_pushfstring (killa_State *L, const char *fmt, ...) {
  const char *msg;
  va_list argp;
  va_start(argp, fmt);
  msg = killaO_pushvfstring(L, fmt, argp);
  va_end(argp);
  return msg;
}


/* number of chars of a literal string without the ending \0 */
#define LL(x)	(sizeof(x)/sizeof(char) - 1)

#define RETS	"..."
#define PRE	"[string \""
#define POS	"\"]"

#define addstr(a,b,l)	( memcpy(a,b,(l) * sizeof(char)), a += (l) )

void killaO_chunkid (char *out, const char *source, size_t bufflen) {
  size_t l = strlen(source);
  if (*source == '=') {  /* 'literal' source */
    if (l <= bufflen)  /* small enough? */
      memcpy(out, source + 1, l * sizeof(char));
    else {  /* truncate it */
      addstr(out, source + 1, bufflen - 1);
      *out = '\0';
    }
  }
  else if (*source == '@') {  /* file name */
    if (l <= bufflen)  /* small enough? */
      memcpy(out, source + 1, l * sizeof(char));
    else {  /* add '...' before rest of name */
      addstr(out, RETS, LL(RETS));
      bufflen -= LL(RETS);
      memcpy(out, source + 1 + l - bufflen, bufflen * sizeof(char));
    }
  }
  else {  /* string; format as [string "source"] */
    const char *nl = strchr(source, '\n');  /* find first new line (if any) */
    addstr(out, PRE, LL(PRE));  /* add prefix */
    bufflen -= LL(PRE RETS POS) + 1;  /* save space for prefix+suffix+'\0' */
    if (l < bufflen && nl == NULL) {  /* small one-line source? */
      addstr(out, source, l);  /* keep it */
    }
    else {
      if (nl != NULL) l = nl - source;  /* stop at first newline */
      if (l > bufflen) l = bufflen;
      addstr(out, source, l);
      addstr(out, RETS, LL(RETS));
    }
    memcpy(out, POS, (LL(POS) + 1) * sizeof(char));
  }
}

