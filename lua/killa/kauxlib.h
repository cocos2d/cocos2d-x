/* ========================================================================== */
/*   Auxiliary functions for building Killa libraries                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KAUXLIB_H_
#define KAUXLIB_H_


#include <stddef.h>
#include <stdio.h>

#include "killa.h"



/* extra error code for `killaL_load' */
#define KILLA_ERRFILE     (KILLA_ERRERR + 1)


typedef struct killaL_Reg {
  const char *name;
  killa_CFunction func;
} killaL_Reg;


KILLALIB_API void (killaL_checkversion_) (killa_State *L, killa_Number ver);
#define killaL_checkversion(L)	killaL_checkversion_(L, KILLA_VERSION_NUM)

KILLALIB_API int (killaL_getmetafield) (killa_State *L, int obj, const char *e);
KILLALIB_API int (killaL_callmeta) (killa_State *L, int obj, const char *e);
KILLALIB_API const char *(killaL_tolstring) (killa_State *L, int idx, size_t *len);
KILLALIB_API int (killaL_argerror) (killa_State *L, int numarg, const char *extramsg);
KILLALIB_API const char *(killaL_checklstring) (killa_State *L, int numArg, size_t *l);

KILLALIB_API const char *(killaL_optlstring) (killa_State *L, int numArg,
                                              const char *def, size_t *l);
KILLALIB_API killa_Number (killaL_checknumber) (killa_State *L, int numArg);
KILLALIB_API killa_Number (killaL_optnumber) (killa_State *L, int nArg, killa_Number def);

KILLALIB_API killa_Integer (killaL_checkinteger) (killa_State *L, int numArg);
KILLALIB_API killa_Integer (killaL_optinteger) (killa_State *L, int nArg,
                                                killa_Integer def);
KILLALIB_API killa_Unsigned (killaL_checkunsigned) (killa_State *L, int numArg);
KILLALIB_API killa_Unsigned (killaL_optunsigned) (killa_State *L, int numArg,
                                                  killa_Unsigned def);

KILLALIB_API void (killaL_checkstack) (killa_State *L, int sz, const char *msg);
KILLALIB_API void (killaL_checktype) (killa_State *L, int narg, int t);
KILLALIB_API void (killaL_checkany) (killa_State *L, int narg);

KILLALIB_API int   (killaL_newmetatable) (killa_State *L, const char *tname);
KILLALIB_API void  (killaL_setmetatable) (killa_State *L, const char *tname);
KILLALIB_API void *(killaL_testudata) (killa_State *L, int ud, const char *tname);
KILLALIB_API void *(killaL_checkudata) (killa_State *L, int ud, const char *tname);

KILLALIB_API void (killaL_where) (killa_State *L, int lvl);
KILLALIB_API int (killaL_error) (killa_State *L, const char *fmt, ...);
#ifdef KILLA_BASE_WARNING
KILLALIB_API void (killaL_warning) (killa_State *L, const char *fmt);
#endif

KILLALIB_API int (killaL_checkoption) (killa_State *L, int narg, const char *def,
                                   const char *const lst[]);

KILLALIB_API int (killaL_fileresult) (killa_State *L, int stat, const char *fname);
KILLALIB_API int (killaL_execresult) (killa_State *L, int stat);

/* pre-defined references */
#define KILLA_NOREF       (-2)
#define KILLA_REFNIL      (-1)

KILLALIB_API int (killaL_ref) (killa_State *L, int t);
KILLALIB_API void (killaL_unref) (killa_State *L, int t, int ref);

KILLALIB_API int (killaL_loadfilex) (killa_State *L, const char *filename,
                                     const char *mode);

#define killaL_loadfile(L,f)	killaL_loadfilex(L,f,NULL)

KILLALIB_API int (killaL_loadbufferx) (killa_State *L, const char *buff, size_t sz,
                                       const char *name, const char *mode);
KILLALIB_API int (killaL_loadstring) (killa_State *L, const char *s);

KILLALIB_API killa_State *(killaL_newstate) (void);

KILLALIB_API int (killaL_len) (killa_State *L, int idx);

KILLALIB_API const char *(killaL_gsub) (killa_State *L, const char *s, const char *p,
                                                  const char *r);

KILLALIB_API void (killaL_setfuncs) (killa_State *L, const killaL_Reg *l, int nup);

KILLALIB_API int (killaL_getsubtable) (killa_State *L, int idx, const char *fname);

KILLALIB_API void (killaL_traceback) (killa_State *L, killa_State *L1,
                                    const char *msg, int level);

KILLALIB_API void (killaL_requiref) (killa_State *L, const char *modname,
                                     killa_CFunction openf, int glb);

/*
** ===============================================================
** some useful macros
** ===============================================================
*/


#define killaL_newlibtable(L,l)	\
        killa_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)

#define killaL_newlib(L,l)	(killaL_newlibtable(L,l), killaL_setfuncs(L,l,0))

#define killaL_argcheck(L, cond,numarg,extramsg)	\
        ((void)((cond) || killaL_argerror(L, (numarg), (extramsg))))
#define killaL_checkstring(L,n)	(killaL_checklstring(L, (n), NULL))
#define killaL_optstring(L,n,d)	(killaL_optlstring(L, (n), (d), NULL))
#define killaL_checkint(L,n)	((int)killaL_checkinteger(L, (n)))
#define killaL_optint(L,n,d)	((int)killaL_optinteger(L, (n), (d)))
#define killaL_checklong(L,n)	((long)killaL_checkinteger(L, (n)))
#define killaL_optlong(L,n,d)	((long)killaL_optinteger(L, (n), (d)))

#define killaL_typename(L,i)	killa_typename(L, killa_type(L,(i)))

#define killaL_dofile(L, fn) \
        (killaL_loadfile(L, fn) || killa_pcall(L, 0, KILLA_MULTRET, 0))

#define killaL_dostring(L, s) \
        (killaL_loadstring(L, s) || killa_pcall(L, 0, KILLA_MULTRET, 0))

#define killaL_getmetatable(L,n)	(killa_getfield(L, KILLA_REGISTRYINDEX, (n)))

#define killaL_opt(L,f,n,d)	(killa_isnoneornull(L,(n)) ? (d) : f(L,(n)))

#define killaL_loadbuffer(L,s,sz,n)	killaL_loadbufferx(L,s,sz,n,NULL)


/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

typedef struct killaL_Buffer {
  char *b;  /* buffer address */
  size_t size;  /* buffer size */
  size_t n;  /* number of characters in buffer */
  killa_State *L;
  char initb[KILLAL_BUFFERSIZE];  /* initial buffer */
} killaL_Buffer;


#define killaL_addchar(B,c) \
  ((void)((B)->n < (B)->size || killaL_prepbuffsize((B), 1)), \
   ((B)->b[(B)->n++] = (c)))

#define killaL_addsize(B,s)	((B)->n += (s))

KILLALIB_API void (killaL_buffinit) (killa_State *L, killaL_Buffer *B);
KILLALIB_API char *(killaL_prepbuffsize) (killaL_Buffer *B, size_t sz);
KILLALIB_API void (killaL_addlstring) (killaL_Buffer *B, const char *s, size_t l);
KILLALIB_API void (killaL_addstring) (killaL_Buffer *B, const char *s);
KILLALIB_API void (killaL_addvalue) (killaL_Buffer *B);
KILLALIB_API void (killaL_pushresult) (killaL_Buffer *B);
KILLALIB_API void (killaL_pushresultsize) (killaL_Buffer *B, size_t sz);
KILLALIB_API char *(killaL_buffinitsize) (killa_State *L, killaL_Buffer *B, size_t sz);

#define killaL_prepbuffer(B)	killaL_prepbuffsize(B, KILLAL_BUFFERSIZE)

/* }====================================================== */



/*
** {======================================================
** File handles for IO library
** =======================================================
*/

/*
** A file handle is a userdata with metatable 'KILLA_FILEHANDLE' and
** initial structure 'killaL_Stream' (it may contain other fields
** after that initial structure).
*/

#define KILLA_FILEHANDLE          "FILE*"


typedef struct killaL_Stream {
  FILE *f;  /* stream (NULL for incompletely created streams) */
  killa_CFunction closef;  /* to close stream (NULL for closed streams) */
} killaL_Stream;

/* }====================================================== */



/* compatibility with old module system */
#if defined(KILLA_COMPAT_MODULE)

KILLALIB_API void (killaL_pushmodule) (killa_State *L, const char *modname,
                                       int sizehint);
KILLALIB_API void (killaL_openlib) (killa_State *L, const char *libname,
                                    const killaL_Reg *l, int nup);

#define killaL_register(L,n,l)	(killaL_openlib(L,(n),(l),0))

#endif


KILLALIB_API int (killaL_typerror) (killa_State *L, int narg, const char *tname);

#endif


