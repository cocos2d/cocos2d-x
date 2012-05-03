/* ========================================================================== */
/*   Standard Operating System library                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


/*
** list of valid conversion specifiers for the 'strftime' function
*/
#if !defined(KILLA_STRFTIMEOPTIONS)

#if !defined(KILLA_USE_POSIX)
#define KILLA_STRFTIMEOPTIONS     { "aAbBcdHIjmMpSUwWxXyYz%", "" }
#else
#define KILLA_STRFTIMEOPTIONS     { "aAbBcCdDeFgGhHIjmMnprRStTuUVwWxXyYzZ%", "", \
                                "E", "cCxXyY",  \
                                "O", "deHImMSuUVwWy" }
#endif

#endif



/*
** By default, Killa uses tmpnam except when POSIX is available, where it
** uses mkstemp.
*/
#if defined(KILLA_USE_MKSTEMP)
#include <unistd.h>
#define KILLA_TMPNAMBUFSIZE       32
#define killa_tmpnam(b,e) { \
        strcpy(b, "/tmp/killa_XXXXXX"); \
        e = mkstemp(b); \
        if (e != -1) close(e); \
        e = (e == -1); }

#elif !defined(killa_tmpnam)

#define KILLA_TMPNAMBUFSIZE       L_tmpnam
#define killa_tmpnam(b,e)         { e = (tmpnam(b) == NULL); }

#endif


/*
** By default, Killa uses gmtime/localtime, except when POSIX is available,
** where it uses gmtime_r/localtime_r
*/
#if defined(KILLA_USE_GMTIME_R)

#define l_gmtime(t,r)		gmtime_r(t,r)
#define l_localtime(t,r)	localtime_r(t,r)

#elif !defined(l_gmtime)

#define l_gmtime(t,r)		((void)r, gmtime(t))
#define l_localtime(t,r)  	((void)r, localtime(t))

#endif



static int os_execute (killa_State *L) {
  const char *cmd = killaL_optstring(L, 1, NULL);
  int stat = system(cmd);
  if (cmd != NULL)
    return killaL_execresult(L, stat);
  else {
    killa_pushboolean(L, stat);  /* true if there is a shell */
    return 1;
  }
}


static int os_remove (killa_State *L) {
  const char *filename = killaL_checkstring(L, 1);
  return killaL_fileresult(L, remove(filename) == 0, filename);
}


static int os_rename (killa_State *L) {
  const char *fromname = killaL_checkstring(L, 1);
  const char *toname = killaL_checkstring(L, 2);
  return killaL_fileresult(L, rename(fromname, toname) == 0, fromname);
}


static int os_tmpname (killa_State *L) {
  char buff[KILLA_TMPNAMBUFSIZE];
  int err;
  killa_tmpnam(buff, err);
  if (err)
    return killaL_error(L, "unable to generate a unique filename");
  killa_pushstring(L, buff);
  return 1;
}


static int os_getenv (killa_State *L) {
  killa_pushstring(L, getenv(killaL_checkstring(L, 1)));  /* if NULL push nil */
  return 1;
}


static int os_clock (killa_State *L) {
  killa_pushnumber(L, ((killa_Number)clock())/(killa_Number)CLOCKS_PER_SEC);
  return 1;
}


/*
** {======================================================
** Time/Date operations
** { year=%Y, month=%m, day=%d, hour=%H, min=%M, sec=%S,
**   wday=%w+1, yday=%j, isdst=? }
** =======================================================
*/

static void setfield (killa_State *L, const char *key, int value) {
  killa_pushinteger(L, value);
  killa_setfield(L, -2, key);
}

static void setboolfield (killa_State *L, const char *key, int value) {
  if (value < 0)  /* undefined? */
    return;  /* does not set field */
  killa_pushboolean(L, value);
  killa_setfield(L, -2, key);
}

static int getboolfield (killa_State *L, const char *key) {
  int res;
  killa_getfield(L, -1, key);
  res = killa_isnull(L, -1) ? -1 : killa_toboolean(L, -1);
  killa_pop(L, 1);
  return res;
}


static int getfield (killa_State *L, const char *key, int d) {
  int res, isnum;
  killa_getfield(L, -1, key);
  res = (int)killa_tointegerx(L, -1, &isnum);
  if (!isnum) {
    if (d < 0)
      return killaL_error(L, "field " KILLA_QS " missing in date table", key);
    res = d;
  }
  killa_pop(L, 1);
  return res;
}


static const char *checkoption (killa_State *L, const char *conv, char *buff) {
  static const char *const options[] = KILLA_STRFTIMEOPTIONS;
  unsigned int i;
  for (i = 0; i < sizeof(options)/sizeof(options[0]); i += 2) {
    if (*conv != '\0' && strchr(options[i], *conv) != NULL) {
      buff[1] = *conv;
      if (*options[i + 1] == '\0') {  /* one-char conversion specifier? */
        buff[2] = '\0';  /* end buffer */
        return conv + 1;
      }
      else if (*(conv + 1) != '\0' &&
               strchr(options[i + 1], *(conv + 1)) != NULL) {
        buff[2] = *(conv + 1);  /* valid two-char conversion specifier */
        buff[3] = '\0';  /* end buffer */
        return conv + 2;
      }
    }
  }
  killaL_argerror(L, 1,
    killa_pushfstring(L, "invalid conversion specifier '%%%s'", conv));
  return conv;  /* to avoid warnings */
}


static int os_date (killa_State *L) {
  const char *s = killaL_optstring(L, 1, "%c");
  time_t t = killaL_opt(L, (time_t)killaL_checknumber, 2, time(NULL));
  struct tm tmr, *stm;
  if (*s == '!') {  /* UTC? */
    stm = l_gmtime(&t, &tmr);
    s++;  /* skip `!' */
  }
  else
    stm = l_localtime(&t, &tmr);
  if (stm == NULL)  /* invalid date? */
    killa_pushnull(L);
  else if (strcmp(s, "*t") == 0) {
    killa_createtable(L, 0, 9);  /* 9 = number of fields */
    setfield(L, "sec", stm->tm_sec);
    setfield(L, "min", stm->tm_min);
    setfield(L, "hour", stm->tm_hour);
    setfield(L, "day", stm->tm_mday);
    setfield(L, "month", stm->tm_mon+1);
    setfield(L, "year", stm->tm_year+1900);
    setfield(L, "wday", stm->tm_wday+1);
    setfield(L, "yday", stm->tm_yday+1);
    setboolfield(L, "isdst", stm->tm_isdst);
  }
  else {
    char cc[4];
    killaL_Buffer b;
    cc[0] = '%';
    killaL_buffinit(L, &b);
    while (*s) {
      if (*s != '%')  /* no conversion specifier? */
        killaL_addchar(&b, *s++);
      else {
        size_t reslen;
        char buff[200];  /* should be big enough for any conversion result */
        s = checkoption(L, s + 1, cc);
        reslen = strftime(buff, sizeof(buff), cc, stm);
        killaL_addlstring(&b, buff, reslen);
      }
    }
    killaL_pushresult(&b);
  }
  return 1;
}


static int os_time (killa_State *L) {
  time_t t;
  if (killa_isnoneornull(L, 1))  /* called without args? */
    t = time(NULL);  /* get current time */
  else {
    struct tm ts;
    killaL_checktype(L, 1, KILLA_TTABLE);
    killa_settop(L, 1);  /* make sure table is at the top */
    ts.tm_sec = getfield(L, "sec", 0);
    ts.tm_min = getfield(L, "min", 0);
    ts.tm_hour = getfield(L, "hour", 12);
    ts.tm_mday = getfield(L, "day", -1);
    ts.tm_mon = getfield(L, "month", -1) - 1;
    ts.tm_year = getfield(L, "year", -1) - 1900;
    ts.tm_isdst = getboolfield(L, "isdst");
    t = mktime(&ts);
  }
  if (t == (time_t)(-1))
    killa_pushnull(L);
  else
    killa_pushnumber(L, (killa_Number)t);
  return 1;
}


static int os_difftime (killa_State *L) {
  killa_pushnumber(L, difftime((time_t)(killaL_checknumber(L, 1)),
                             (time_t)(killaL_optnumber(L, 2, 0))));
  return 1;
}

/* }====================================================== */


static int os_setlocale (killa_State *L) {
  static const int cat[] = {LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY,
                      LC_NUMERIC, LC_TIME};
  static const char *const catnames[] = {"all", "collate", "ctype", "monetary",
     "numeric", "time", NULL};
  const char *l = killaL_optstring(L, 1, NULL);
  int op = killaL_checkoption(L, 2, "all", catnames);
  killa_pushstring(L, setlocale(cat[op], l));
  return 1;
}


static int os_exit (killa_State *L) {
  int status;
  if (killa_isboolean(L, 1))
    status = (killa_toboolean(L, 1) ? EXIT_SUCCESS : EXIT_FAILURE);
  else
    status = killaL_optint(L, 1, EXIT_SUCCESS);
  if (killa_toboolean(L, 2))
    killa_close(L);
  if (L) exit(status);  /* 'if' to avoid warnings for unreachable 'return' */
  return 0;
}


static const killaL_Reg syslib[] = {
  {"clock",     os_clock},
  {"date",      os_date},
  {"difftime",  os_difftime},
  {"execute",   os_execute},
  {"exit",      os_exit},
  {"getenv",    os_getenv},
  {"remove",    os_remove},
  {"rename",    os_rename},
  {"setlocale", os_setlocale},
  {"time",      os_time},
  {"tmpname",   os_tmpname},
  {NULL, NULL}
};

/* }====================================================== */



KILLAMOD_API int killaopen_os (killa_State *L) {
  killaL_newlib(L, syslib);
  return 1;
}

