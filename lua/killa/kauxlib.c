/* ========================================================================== */
/*   Auxiliary functions for building Killa libraries                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* This file uses only the official API of Killa.
** Any function declared here could be written as an application function.
*/

#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"


/*
** {======================================================
** Traceback
** =======================================================
*/


#define LEVELS1	12	/* size of the first part of the stack */
#define LEVELS2	10	/* size of the second part of the stack */



/*
** search for 'objidx' in table at index -1.
** return 1 + string at top if find a good name.
*/
static int findfield (killa_State *L, int objidx, int level) {
  if (level == 0 || !killa_istable(L, -1))
    return 0;  /* not found */
  killa_pushnull(L);  /* start 'next' loop */
  while (killa_next(L, -2)) {  /* for each pair in table */
    if (killa_type(L, -2) == KILLA_TSTRING) {  /* ignore non-string keys */
      if (killa_rawequal(L, objidx, -1)) {  /* found object? */
        killa_pop(L, 1);  /* remove value (but keep name) */
        return 1;
      }
      else if (findfield(L, objidx, level - 1)) {  /* try recursively */
        killa_remove(L, -2);  /* remove table (but keep name) */
        killa_pushliteral(L, ".");
        killa_insert(L, -2);  /* place '.' between the two names */
        killa_concat(L, 3);
        return 1;
      }
    }
    killa_pop(L, 1);  /* remove value */
  }
  return 0;  /* not found */
}


static int pushglobalfuncname (killa_State *L, killa_Debug *ar) {
  int top = killa_gettop(L);
  killa_getinfo(L, "f", ar);  /* push function */
  killa_pushglobaltable(L);
  if (findfield(L, top + 1, 2)) {
    killa_copy(L, -1, top + 1);  /* move name to proper place */
    killa_pop(L, 2);  /* remove pushed values */
    return 1;
  }
  else {
    killa_settop(L, top);  /* remove function and global table */
    return 0;
  }
}


static void pushfuncname (killa_State *L, killa_Debug *ar) {
  if (*ar->namewhat != '\0')  /* is there a name? */
    killa_pushfstring(L, "function " KILLA_QS, ar->name);
  else if (*ar->what == 'm')  /* main? */
      killa_pushfstring(L, "main chunk");
  else if (*ar->what == 'C') {
    if (pushglobalfuncname(L, ar)) {
      killa_pushfstring(L, "function " KILLA_QS, killa_tostring(L, -1));
      killa_remove(L, -2);  /* remove name */
    }
    else
      killa_pushliteral(L, "?");
  }
  else
    killa_pushfstring(L, "function <%s:%d>", ar->short_src, ar->linedefined);
}


static int countlevels (killa_State *L) {
  killa_Debug ar;
  int li = 1, le = 1;
  /* find an upper bound */
  while (killa_getstack(L, le, &ar)) { li = le; le *= 2; }
  /* do a binary search */
  while (li < le) {
    int m = (li + le)/2;
    if (killa_getstack(L, m, &ar)) li = m + 1;
    else le = m;
  }
  return le - 1;
}


KILLALIB_API void killaL_traceback (killa_State *L, killa_State *L1,
                                const char *msg, int level) {
  killa_Debug ar;
  int top = killa_gettop(L);
  int numlevels = countlevels(L1);
  int mark = (numlevels > LEVELS1 + LEVELS2) ? LEVELS1 : 0;
  if (msg) killa_pushfstring(L, "%s\n", msg);
  killa_pushliteral(L, "stack traceback:");
  while (killa_getstack(L1, level++, &ar)) {
    if (level == mark) {  /* too many levels? */
      killa_pushliteral(L, "\n\t...");  /* add a '...' */
      level = numlevels - LEVELS2;  /* and skip to last ones */
    }
    else {
      killa_getinfo(L1, "Slnt", &ar);
      killa_pushfstring(L, "\n\t%s:", ar.short_src);
      if (ar.currentline > 0)
        killa_pushfstring(L, "%d:", ar.currentline);
      killa_pushliteral(L, " in ");
      pushfuncname(L, &ar);
      if (ar.istailcall)
        killa_pushliteral(L, "\n\t(...tail calls...)");
      killa_concat(L, killa_gettop(L) - top);
    }
  }
  killa_concat(L, killa_gettop(L) - top);
}

/* }====================================================== */


/*
** {======================================================
** Error-report functions
** =======================================================
*/

KILLALIB_API int killaL_argerror (killa_State *L, int narg, const char *extramsg) {
  killa_Debug ar;
  if (!killa_getstack(L, 0, &ar))  /* no stack frame? */
    return killaL_error(L, "bad argument #%d (%s)", narg, extramsg);
  killa_getinfo(L, "n", &ar);
  if (strcmp(ar.namewhat, "method") == 0) {
    narg--;  /* do not count `self' */
    if (narg == 0)  /* error is in the self argument itself? */
      return killaL_error(L, "calling " KILLA_QS " on bad self", ar.name);
  }
  if (ar.name == NULL)
    ar.name = (pushglobalfuncname(L, &ar)) ? killa_tostring(L, -1) : "?";
  return killaL_error(L, "bad argument #%d to " KILLA_QS " (%s)",
                        narg, ar.name, extramsg);
}


static int typeerror (killa_State *L, int narg, const char *tname) {
  const char *msg = killa_pushfstring(L, "%s expected, got %s",
                                    tname, killaL_typename(L, narg));
  return killaL_argerror(L, narg, msg);
}


static void tag_error (killa_State *L, int narg, int tag) {
  typeerror(L, narg, killa_typename(L, tag));
}


KILLALIB_API void killaL_where (killa_State *L, int level) {
  killa_Debug ar;
  if (killa_getstack(L, level, &ar)) {  /* check function at level */
    killa_getinfo(L, "Sl", &ar);  /* get info about it */
    if (ar.currentline > 0) {  /* is there info? */
      killa_pushfstring(L, "%s:%d: ", ar.short_src, ar.currentline);
      return;
    }
  }
  killa_pushliteral(L, "");  /* else, no information available... */
}


KILLALIB_API int killaL_error (killa_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  killaL_where(L, 1);
  killa_pushvfstring(L, fmt, argp);
  va_end(argp);
  killa_concat(L, 2);
  return killa_error(L);
}


#ifdef KILLA_BASE_WARNING
KILLALIB_API void killaL_warning (killa_State *L, const char *msg) {
  killa_Debug ar;
  if (killa_getstack(L, 1, &ar)) {  /* check function at level */
    char buff[512];
    killa_getinfo(L, "Sl", &ar);  /* get info about it */
    sprintf(buff, "%s at %s:%d", msg, ar.short_src, ar.currentline);
    killai_writestringerror("[WARN] %s\n", buff);
  }
  else 
    killai_writestringerror("[WARN] %s\n", msg);
}
#endif


KILLALIB_API int killaL_fileresult (killa_State *L, int stat, const char *fname) {
  int en = errno;  /* calls to Killa API may change this value */
  if (stat) {
    killa_pushboolean(L, 1);
    return 1;
  }
  else {
    killa_pushnull(L);
    if (fname)
      killa_pushfstring(L, "%s: %s", fname, strerror(en));
    else
      killa_pushfstring(L, "%s", strerror(en));
    killa_pushinteger(L, en);
    return 3;
  }
}


#if !defined(inspectstat)	/* { */

#if defined(KILLA_USE_POSIX)

#include <sys/wait.h>

/*
** use appropriate macros to interpret 'pclose' return status
*/
#define inspectstat(stat,what)  \
   if (WIFEXITED(stat)) { stat = WEXITSTATUS(stat); } \
   else if (WIFSIGNALED(stat)) { stat = WTERMSIG(stat); what = "signal"; }

#else

#define inspectstat(stat,what)  /* no op */

#endif

#endif				/* } */


KILLALIB_API int killaL_execresult (killa_State *L, int stat) {
  const char *what = "exit";  /* type of termination */
  if (stat == -1)  /* error? */
    return killaL_fileresult(L, 0, NULL);
  else {
    inspectstat(stat, what);  /* interpret result */
    if (*what == 'e' && stat == 0)  /* successful termination? */
      killa_pushboolean(L, 1);
    else
      killa_pushnull(L);
    killa_pushstring(L, what);
    killa_pushinteger(L, stat);
    return 3;  /* return true/nil,what,code */
  }
}

/* }====================================================== */


/*
** {======================================================
** Userdata's metatable manipulation
** =======================================================
*/

KILLALIB_API int killaL_newmetatable (killa_State *L, const char *tname) {
  killaL_getmetatable(L, tname);  /* try to get metatable */
  if (!killa_isnull(L, -1))  /* name already in use? */
    return 0;  /* leave previous value on top, but return 0 */
  killa_pop(L, 1);
  killa_newtable(L);  /* create metatable */
  killa_pushvalue(L, -1);
  killa_setfield(L, KILLA_REGISTRYINDEX, tname);  /* registry.name = metatable */
  return 1;
}


KILLALIB_API void killaL_setmetatable (killa_State *L, const char *tname) {
  killaL_getmetatable(L, tname);
  killa_setmetatable(L, -2);
}


KILLALIB_API void *killaL_testudata (killa_State *L, int ud, const char *tname) {
  void *p = killa_touserdata(L, ud);
  if (p != NULL) {  /* value is a userdata? */
    if (killa_getmetatable(L, ud)) {  /* does it have a metatable? */
      killaL_getmetatable(L, tname);  /* get correct metatable */
      if (!killa_rawequal(L, -1, -2))  /* not the same? */
        p = NULL;  /* value is a userdata with wrong metatable */
      killa_pop(L, 2);  /* remove both metatables */
      return p;
    }
  }
  return NULL;  /* value is not a userdata with a metatable */
}


KILLALIB_API void *killaL_checkudata (killa_State *L, int ud, const char *tname) {
  void *p = killaL_testudata(L, ud, tname);
  if (p == NULL) typeerror(L, ud, tname);
  return p;
}

/* }====================================================== */


/*
** {======================================================
** Argument check functions
** =======================================================
*/

KILLALIB_API int killaL_checkoption (killa_State *L, int narg, const char *def,
                                 const char *const lst[]) {
  const char *name = (def) ? killaL_optstring(L, narg, def) :
                             killaL_checkstring(L, narg);
  int i;
  for (i=0; lst[i]; i++)
    if (strcmp(lst[i], name) == 0)
      return i;
  return killaL_argerror(L, narg,
                       killa_pushfstring(L, "invalid option " KILLA_QS, name));
}


KILLALIB_API void killaL_checkstack (killa_State *L, int space, const char *msg) {
  /* keep some extra space to run error routines, if needed */
  const int extra = KILLA_MINSTACK;
  if (!killa_checkstack(L, space + extra)) {
    if (msg)
      killaL_error(L, "stack overflow (%s)", msg);
    else
      killaL_error(L, "stack overflow");
  }
}


KILLALIB_API void killaL_checktype (killa_State *L, int narg, int t) {
  if (killa_type(L, narg) != t)
    tag_error(L, narg, t);
}


KILLALIB_API void killaL_checkany (killa_State *L, int narg) {
  if (killa_type(L, narg) == KILLA_TNONE)
    killaL_argerror(L, narg, "value expected");
}


KILLALIB_API const char *killaL_checklstring (killa_State *L, int narg, size_t *len) {
  const char *s = killa_tolstring(L, narg, len);
  if (!s) tag_error(L, narg, KILLA_TSTRING);
  return s;
}


KILLALIB_API const char *killaL_optlstring (killa_State *L, int narg,
                                        const char *def, size_t *len) {
  if (killa_isnoneornull(L, narg)) {
    if (len)
      *len = (def ? strlen(def) : 0);
    return def;
  }
  else return killaL_checklstring(L, narg, len);
}


KILLALIB_API killa_Number killaL_checknumber (killa_State *L, int narg) {
  int isnum;
  killa_Number d = killa_tonumberx(L, narg, &isnum);
  if (!isnum)
    tag_error(L, narg, KILLA_TNUMBER);
  return d;
}


KILLALIB_API killa_Number killaL_optnumber (killa_State *L, int narg, killa_Number def) {
  return killaL_opt(L, killaL_checknumber, narg, def);
}


KILLALIB_API killa_Integer killaL_checkinteger (killa_State *L, int narg) {
  int isnum;
  killa_Integer d = killa_tointegerx(L, narg, &isnum);
  if (!isnum)
    tag_error(L, narg, KILLA_TNUMBER);
  return d;
}


KILLALIB_API killa_Unsigned killaL_checkunsigned (killa_State *L, int narg) {
  int isnum;
  killa_Unsigned d = killa_tounsignedx(L, narg, &isnum);
  if (!isnum)
    tag_error(L, narg, KILLA_TNUMBER);
  return d;
}


KILLALIB_API killa_Integer killaL_optinteger (killa_State *L, int narg,
                                                      killa_Integer def) {
  return killaL_opt(L, killaL_checkinteger, narg, def);
}


KILLALIB_API killa_Unsigned killaL_optunsigned (killa_State *L, int narg,
                                                        killa_Unsigned def) {
  return killaL_opt(L, killaL_checkunsigned, narg, def);
}

/* }====================================================== */


/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

/*
** check whether buffer is using a userdata on the stack as a temporary
** buffer
*/
#define buffonstack(B)	((B)->b != (B)->initb)


/*
** returns a pointer to a free area with at least 'sz' bytes
*/
KILLALIB_API char *killaL_prepbuffsize (killaL_Buffer *B, size_t sz) {
  killa_State *L = B->L;
  if (B->size - B->n < sz) {  /* not enough space? */
    char *newbuff;
    size_t newsize = B->size * 2;  /* double buffer size */
    if (newsize - B->n < sz)  /* not bit enough? */
      newsize = B->n + sz;
    if (newsize < B->n || newsize - B->n < sz)
      killaL_error(L, "buffer too large");
    /* create larger buffer */
    newbuff = (char *)killa_newuserdata(L, newsize * sizeof(char));
    /* move content to new buffer */
    memcpy(newbuff, B->b, B->n * sizeof(char));
    if (buffonstack(B))
      killa_remove(L, -2);  /* remove old buffer */
    B->b = newbuff;
    B->size = newsize;
  }
  return &B->b[B->n];
}


KILLALIB_API void killaL_addlstring (killaL_Buffer *B, const char *s, size_t l) {
  char *b = killaL_prepbuffsize(B, l);
  memcpy(b, s, l * sizeof(char));
  killaL_addsize(B, l);
}


KILLALIB_API void killaL_addstring (killaL_Buffer *B, const char *s) {
  killaL_addlstring(B, s, strlen(s));
}


KILLALIB_API void killaL_pushresult (killaL_Buffer *B) {
  killa_State *L = B->L;
  killa_pushlstring(L, B->b, B->n);
  if (buffonstack(B))
    killa_remove(L, -2);  /* remove old buffer */
}


KILLALIB_API void killaL_pushresultsize (killaL_Buffer *B, size_t sz) {
  killaL_addsize(B, sz);
  killaL_pushresult(B);
}


KILLALIB_API void killaL_addvalue (killaL_Buffer *B) {
  killa_State *L = B->L;
  size_t l;
  const char *s = killa_tolstring(L, -1, &l);
  if (buffonstack(B))
    killa_insert(L, -2);  /* put value below buffer */
  killaL_addlstring(B, s, l);
  killa_remove(L, (buffonstack(B)) ? -2 : -1);  /* remove value */
}


KILLALIB_API void killaL_buffinit (killa_State *L, killaL_Buffer *B) {
  B->L = L;
  B->b = B->initb;
  B->n = 0;
  B->size = KILLAL_BUFFERSIZE;
}


KILLALIB_API char *killaL_buffinitsize (killa_State *L, killaL_Buffer *B, size_t sz) {
  killaL_buffinit(L, B);
  return killaL_prepbuffsize(B, sz);
}

/* }====================================================== */


/*
** {======================================================
** Reference system
** =======================================================
*/

/* index of free-list header */
#define freelist	0


KILLALIB_API int killaL_ref (killa_State *L, int t) {
  int ref;
  t = killa_absindex(L, t);
  if (killa_isnull(L, -1)) {
    killa_pop(L, 1);  /* remove from stack */
    return KILLA_REFNIL;  /* `nil' has a unique fixed reference */
  }
  killa_rawgeti(L, t, freelist);  /* get first free element */
  ref = (int)killa_tointeger(L, -1);  /* ref = t[freelist] */
  killa_pop(L, 1);  /* remove it from stack */
  if (ref != 0) {  /* any free element? */
    killa_rawgeti(L, t, ref);  /* remove it from list */
    killa_rawseti(L, t, freelist);  /* (t[freelist] = t[ref]) */
  }
  else  /* no free elements */
    ref = (int)killa_rawlen(L, t) + 1;  /* get a new reference */
  killa_rawseti(L, t, ref);
  return ref;
}


KILLALIB_API void killaL_unref (killa_State *L, int t, int ref) {
  if (ref >= 0) {
    t = killa_absindex(L, t);
    killa_rawgeti(L, t, freelist);
    killa_rawseti(L, t, ref);  /* t[ref] = t[freelist] */
    killa_pushinteger(L, ref);
    killa_rawseti(L, t, freelist);  /* t[freelist] = ref */
  }
}

/* }====================================================== */


/*
** {======================================================
** Load functions
** =======================================================
*/

typedef struct LoadF {
  int n;  /* number of pre-read characters */
  FILE *f;  /* file being read */
  char buff[KILLAL_BUFFERSIZE];  /* area for reading file */
} LoadF;


static const char *getF (killa_State *L, void *ud, size_t *size) {
  LoadF *lf = (LoadF *)ud;
  (void)L;  /* not used */
  if (lf->n > 0) {  /* are there pre-read characters to be read? */
    *size = lf->n;  /* return them (chars already in buffer) */
    lf->n = 0;  /* no more pre-read characters */
  }
  else {  /* read a block from file */
    /* 'fread' can return > 0 *and* set the EOF flag. If next call to
       'getF' called 'fread', it might still wait for user input.
       The next check avoids this problem. */
    if (feof(lf->f)) return NULL;
    *size = fread(lf->buff, 1, sizeof(lf->buff), lf->f);  /* read block */
  }
  return lf->buff;
}


static int errfile (killa_State *L, const char *what, int fnameindex) {
  const char *serr = strerror(errno);
  const char *filename = killa_tostring(L, fnameindex) + 1;
  killa_pushfstring(L, "cannot %s %s: %s", what, filename, serr);
  killa_remove(L, fnameindex);
  return KILLA_ERRFILE;
}


static int skipBOM (LoadF *lf) {
  const char *p = "\xEF\xBB\xBF";  /* Utf8 BOM mark */
  int c;
  lf->n = 0;
  do {
    c = getc(lf->f);
    if (c == EOF || c != *(unsigned char *)p++) return c;
    lf->buff[lf->n++] = c;  /* to be read by the parser */
  } while (*p != '\0');
  lf->n = 0;  /* prefix matched; discard it */
  return getc(lf->f);  /* return next character */
}


/*
** reads the first character of file 'f' and skips an optional BOM mark
** in its beginning plus its first line if it starts with '#'. Returns
** true if it skipped the first line.  In any case, '*cp' has the
** first "valid" character of the file (after the optional BOM and
** a first-line comment).
*/
static int skipcomment (LoadF *lf, int *cp) {
  int c = *cp = skipBOM(lf);
  if (c == '#') {  /* first line is a comment (Unix exec. file)? */
    while ((c = getc(lf->f)) != EOF && c != '\n') ;  /* skip first line */
    *cp = getc(lf->f);  /* skip end-of-line */
    return 1;  /* there was a comment */
  }
  else return 0;  /* no comment */
}


KILLALIB_API int killaL_loadfilex (killa_State *L, const char *filename,
                                             const char *mode) {
  LoadF lf;
  int status, readstatus;
  int c;
  int fnameindex = killa_gettop(L) + 1;  /* index of filename on the stack */
  if (filename == NULL) {
    killa_pushliteral(L, "=stdin");
    lf.f = stdin;
  }
  else {
    killa_pushfstring(L, "@%s", filename);
    lf.f = fopen(filename, "r");
    if (lf.f == NULL) return errfile(L, "open", fnameindex);
  }
  if (skipcomment(&lf, &c))  /* read initial portion */
    lf.buff[lf.n++] = '\n';  /* add line to correct line numbers */
  if (c == KILLA_SIGNATURE[0] && filename) {  /* binary file? */
    lf.f = freopen(filename, "rb", lf.f);  /* reopen in binary mode */
    if (lf.f == NULL) return errfile(L, "reopen", fnameindex);
    skipcomment(&lf, &c);  /* re-read initial portion */
  }
  if (c != EOF)
    lf.buff[lf.n++] = c;  /* 'c' is the first character of the stream */
  status = killa_load(L, getF, &lf, killa_tostring(L, -1), mode);
  readstatus = ferror(lf.f);
  if (filename) fclose(lf.f);  /* close file (even in case of errors) */
  if (readstatus) {
    killa_settop(L, fnameindex);  /* ignore results from `killa_load' */
    return errfile(L, "read", fnameindex);
  }
  killa_remove(L, fnameindex);
  return status;
}


typedef struct LoadS {
  const char *s;
  size_t size;
} LoadS;


static const char *getS (killa_State *L, void *ud, size_t *size) {
  LoadS *ls = (LoadS *)ud;
  (void)L;  /* not used */
  if (ls->size == 0) return NULL;
  *size = ls->size;
  ls->size = 0;
  return ls->s;
}


KILLALIB_API int killaL_loadbufferx (killa_State *L, const char *buff, size_t size,
                                 const char *name, const char *mode) {
  LoadS ls;
  ls.s = buff;
  ls.size = size;
  return killa_load(L, getS, &ls, name, mode);
}


KILLALIB_API int killaL_loadstring (killa_State *L, const char *s) {
  return killaL_loadbuffer(L, s, strlen(s), s);
}

/* }====================================================== */



KILLALIB_API int killaL_getmetafield (killa_State *L, int obj, const char *event) {
  if (!killa_getmetatable(L, obj))  /* no metatable? */
    return 0;
  killa_pushstring(L, event);
  killa_rawget(L, -2);
  if (killa_isnull(L, -1)) {
    killa_pop(L, 2);  /* remove metatable and metafield */
    return 0;
  }
  else {
    killa_remove(L, -2);  /* remove only metatable */
    return 1;
  }
}


KILLALIB_API int killaL_callmeta (killa_State *L, int obj, const char *event) {
  obj = killa_absindex(L, obj);
  if (!killaL_getmetafield(L, obj, event))  /* no metafield? */
    return 0;
  killa_pushvalue(L, obj);
  killa_call(L, 1, 1);
  return 1;
}


KILLALIB_API int killaL_len (killa_State *L, int idx) {
  int l;
  int isnum;
  killa_len(L, idx);
  l = (int)killa_tointegerx(L, -1, &isnum);
  if (!isnum)
    killaL_error(L, "object length is not a number");
  killa_pop(L, 1);  /* remove object */
  return l;
}


KILLALIB_API const char *killaL_tolstring (killa_State *L, int idx, size_t *len) {
  if (!killaL_callmeta(L, idx, "__tostring")) {  /* no metafield? */
    switch (killa_type(L, idx)) {
      case KILLA_TNUMBER:
      case KILLA_TSTRING:
        killa_pushvalue(L, idx);
        break;
      case KILLA_TBOOLEAN:
        killa_pushstring(L, (killa_toboolean(L, idx) ? "true" : "false"));
        break;
      case KILLA_TNULL:
        killa_pushliteral(L, "null");
        break;
      default:
        killa_pushfstring(L, "%s: %p", killaL_typename(L, idx),
                                            killa_topointer(L, idx));
        break;
    }
  }
  return killa_tolstring(L, -1, len);
}


/*
** {======================================================
** Compatibility with 5.1 module functions
** =======================================================
*/
#if defined(KILLA_COMPAT_MODULE)

static const char *killaL_findtable (killa_State *L, int idx,
                                   const char *fname, int szhint) {
  const char *e;
  if (idx) killa_pushvalue(L, idx);
  do {
    e = strchr(fname, '.');
    if (e == NULL) e = fname + strlen(fname);
    killa_pushlstring(L, fname, e - fname);
    killa_rawget(L, -2);
    if (killa_isnull(L, -1)) {  /* no such field? */
      killa_pop(L, 1);  /* remove this nil */
      killa_createtable(L, 0, (*e == '.' ? 1 : szhint)); /* new table for field */
      killa_pushlstring(L, fname, e - fname);
      killa_pushvalue(L, -2);
      killa_settable(L, -4);  /* set new table into field */
    }
    else if (!killa_istable(L, -1)) {  /* field has a non-table value? */
      killa_pop(L, 2);  /* remove table and value */
      return fname;  /* return problematic part of the name */
    }
    killa_remove(L, -2);  /* remove previous table */
    fname = e + 1;
  } while (*e == '.');
  return NULL;
}


/*
** Count number of elements in a killaL_Reg list.
*/
static int libsize (const killaL_Reg *l) {
  int size = 0;
  for (; l && l->name; l++) size++;
  return size;
}


/*
** Find or create a module table with a given name. The function
** first looks at the _LOADED table and, if that fails, try a
** global variable with that name. In any case, leaves on the stack
** the module table.
*/
KILLALIB_API void killaL_pushmodule (killa_State *L, const char *modname,
                                 int sizehint) {
  killaL_findtable(L, KILLA_REGISTRYINDEX, "_LOADED", 1);  /* get _LOADED table */
  killa_getfield(L, -1, modname);  /* get _LOADED[modname] */
  if (!killa_istable(L, -1)) {  /* not found? */
    killa_pop(L, 1);  /* remove previous result */
    /* try global variable (and create one if it does not exist) */
    killa_pushglobaltable(L);
    if (killaL_findtable(L, 0, modname, sizehint) != NULL)
      killaL_error(L, "name conflict for module " KILLA_QS, modname);
    killa_pushvalue(L, -1);
    killa_setfield(L, -3, modname);  /* _LOADED[modname] = new table */
  }
  killa_remove(L, -2);  /* remove _LOADED table */
}


KILLALIB_API void killaL_openlib (killa_State *L, const char *libname,
                               const killaL_Reg *l, int nup) {
  killaL_checkversion(L);
  if (libname) {
    killaL_pushmodule(L, libname, libsize(l));  /* get/create library table */
    killa_insert(L, -(nup + 1));  /* move library table to below upvalues */
  }
  if (l)
    killaL_setfuncs(L, l, nup);
  else
    killa_pop(L, nup);  /* remove upvalues */
}

#endif
/* }====================================================== */

/*
** set functions from list 'l' into table at top - 'nup'; each
** function gets the 'nup' elements at the top as upvalues.
** Returns with only the table at the stack.
*/
KILLALIB_API void killaL_setfuncs (killa_State *L, const killaL_Reg *l, int nup) {
  killaL_checkstack(L, nup, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      killa_pushvalue(L, -nup);
    killa_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    killa_setfield(L, -(nup + 2), l->name);
  }
  killa_pop(L, nup);  /* remove upvalues */
}


/*
** ensure that stack[idx][fname] has a table and push that table
** into the stack
*/
KILLALIB_API int killaL_getsubtable (killa_State *L, int idx, const char *fname) {
  killa_getfield(L, idx, fname);
  if (killa_istable(L, -1)) return 1;  /* table already there */
  else {
    idx = killa_absindex(L, idx);
    killa_pop(L, 1);  /* remove previous result */
    killa_newtable(L);
    killa_pushvalue(L, -1);  /* copy to be left at top */
    killa_setfield(L, idx, fname);  /* assign new table to field */
    return 0;  /* false, because did not find table there */
  }
}


/*
** stripped-down 'require'. Calls 'openf' to open a module,
** registers the result in 'package.loaded' table and, if 'glb'
** is true, also registers the result in the global table.
** Leaves resulting module on the top.
*/
KILLALIB_API void killaL_requiref (killa_State *L, const char *modname,
                               killa_CFunction openf, int glb) {
  killa_pushcfunction(L, openf);
  killa_pushstring(L, modname);  /* argument to open function */
  killa_call(L, 1, 1);  /* open module */
  killaL_getsubtable(L, KILLA_REGISTRYINDEX, "_LOADED");
  killa_pushvalue(L, -2);  /* make copy of module (call result) */
  killa_setfield(L, -2, modname);  /* _LOADED[modname] = module */
  killa_pop(L, 1);  /* remove _LOADED table */
  if (glb) {
    killa_pushglobaltable(L);
    killa_pushvalue(L, -2);  /* copy of 'mod' */
    killa_setfield(L, -2, modname);  /* _G[modname] = module */
    killa_pop(L, 1);  /* remove _G table */
  }
}


KILLALIB_API const char *killaL_gsub (killa_State *L, const char *s, const char *p,
                                                               const char *r) {
  const char *wild;
  size_t l = strlen(p);
  killaL_Buffer b;
  killaL_buffinit(L, &b);
  while ((wild = strstr(s, p)) != NULL) {
    killaL_addlstring(&b, s, wild - s);  /* push prefix */
    killaL_addstring(&b, r);  /* push replacement in place of pattern */
    s = wild + l;  /* continue after `p' */
  }
  killaL_addstring(&b, s);  /* push last suffix */
  killaL_pushresult(&b);
  return killa_tostring(L, -1);
}


static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
  (void)ud; (void)osize;  /* not used */
  if (nsize == 0) {
    free(ptr);
    return NULL;
  }
  else
    return realloc(ptr, nsize);
}


static int panic (killa_State *L) {
  killai_writestringerror("PANIC: unprotected error in call to Killa API (%s)\n",
                   killa_tostring(L, -1));
  return 0;  /* return to Killa to abort */
}


KILLALIB_API killa_State *killaL_newstate (void) {
  killa_State *L = killa_newstate(l_alloc, NULL);
  if (L) killa_atpanic(L, &panic);
  return L;
}


KILLALIB_API void killaL_checkversion_ (killa_State *L, killa_Number ver) {
  const killa_Number *v = killa_version(L);
  if (v != killa_version(NULL))
    killaL_error(L, "multiple Killa VMs detected");
  else if (*v != ver)
    killaL_error(L, "version mismatch: app. needs %f, Killa core provides %f",
                  ver, *v);
  /* check conversions number -> integer types */
  killa_pushnumber(L, -(killa_Number)0x1234);
  if (killa_tointeger(L, -1) != -0x1234 ||
      killa_tounsigned(L, -1) != (killa_Unsigned)-0x1234)
    killaL_error(L, "bad conversion number->int;"
                  " must recompile Killa with proper settings");
  killa_pop(L, 1);
}


KILLALIB_API int killaL_typerror (killa_State *L, int narg, const char *tname) {
  const char *msg = killa_pushfstring(L, "%s expected, got %s",
                                    tname, killaL_typename(L, narg));
  return killaL_argerror(L, narg, msg);
}


