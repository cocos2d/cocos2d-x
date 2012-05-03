/* ========================================================================== */
/*   Killa                                                                    */
/*   A programming language based in Lua with a Javascript-like syntax.       */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This project is licensed under the MIT license:                          */
/*                                                                            */
/*   Permission is hereby granted, free of charge, to any person              */
/*   obtaining a copy of this software and associated documentation           */
/*   files (the "Software"), to deal in the Software without                  */
/*   restriction, including without limitation the rights to use,             */
/*   copy, modify, merge, publish, distribute, sublicense, and/or sell        */
/*   copies of the Software, and to permit persons to whom the                */
/*   Software is furnished to do so, subject to the following                 */
/*   conditions:                                                              */
/*                                                                            */
/*   The above copyright notice and this permission notice shall be           */
/*   included in all copies or substantial portions of the Software.          */
/*                                                                            */
/*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          */
/*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES          */
/*   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                 */
/*   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT              */
/*   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,             */
/*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING             */
/*   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR            */
/*   OTHER DEALINGS IN THE SOFTWARE.                                          */
/* -------------------------------------------------------------------------- */

#ifndef KILLA_H_
#define KILLA_H_

#include <stdarg.h>
#include <stddef.h>


#include "killaconf.h"


#define KILLA_VERSION_MAJOR     "0"
#define KILLA_VERSION_MINOR     "1"
#define KILLA_VERSION_NUM		10
#define KILLA_VERSION_RELEASE	"0"

#define KILLA_VERSION	"Killa " KILLA_VERSION_MAJOR "." KILLA_VERSION_MINOR
#define KILLA_RELEASE	KILLA_VERSION "." KILLA_VERSION_RELEASE
#define KILLA_COPYRIGHT	KILLA_RELEASE "  Copyright (C) 2012 Laurens Rodriguez"
#define KILLA_AUTHORS	"L. Rodriguez, R. Ierusalimschy, L. H. de Figueiredo, W. Celes"

/* Mark for precompiled code (`<esc>Kia') */
#define	KILLA_SIGNATURE	"\033Kia"


/* option for multiple returns in 'killa_pcall' and 'killa_call' */
#define KILLA_MULTRET	(-1)


/*
** pseudo-indices
*/
#define KILLA_REGISTRYINDEX	KILLAI_FIRSTPSEUDOIDX
#define killa_upvalueindex(i)	(KILLA_REGISTRYINDEX - (i))


/* thread status */
#define KILLA_OK        0
#define KILLA_YIELD     1
#define KILLA_ERRRUN    2
#define KILLA_ERRSYNTAX 3
#define KILLA_ERRMEM    4
#define KILLA_ERRGCMM   5
#define KILLA_ERRERR    6


typedef struct killa_State killa_State;

typedef int (*killa_CFunction) (killa_State *L);


/*
** functions that read/write blocks when loading/dumping Killa chunks
*/
typedef const char * (*killa_Reader) (killa_State *L, void *ud, size_t *sz);

typedef int (*killa_Writer) (killa_State *L, const void* p, size_t sz, void* ud);


/*
** prototype for memory-allocation functions
*/
typedef void * (*killa_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);


/*
** basic types
*/
#define KILLA_TNONE		    (-1)

#define KILLA_TNULL          0
#define KILLA_TBOOLEAN       1
#define KILLA_TLIGHTUSERDATA 2
#define KILLA_TNUMBER        3
#define KILLA_TSTRING        4
#define KILLA_TTABLE         5
#define KILLA_TFUNCTION      6
#define KILLA_TUSERDATA      7
#define KILLA_TTHREAD        8

#define KILLA_NUMTAGS        9


/* minimum Killa stack available to a C function */
#define KILLA_MINSTACK	20


/* use this define to configure the index base for tables */
#define KILLA_BASE      0
#if (KILLA_BASE != 1)
#define KILLA_BASE_WARNING
#endif


/* predefined values in the registry */
#define KILLA_RIDX_MAINTHREAD   (KILLA_BASE? 1 : 0)
#define KILLA_RIDX_GLOBALS      (KILLA_BASE? 2 : 1)
#define KILLA_RIDX_SIZE         2


/* type of numbers in Killa */
typedef KILLA_NUMBER    killa_Number;


/* type for integer functions */
typedef KILLA_INTEGER   killa_Integer;


/* unsigned integer type */
typedef KILLA_UNSIGNED  killa_Unsigned;



/*
** generic extra include file
*/
#if defined(KILLA_USER_H_)
#include KILLA_USER_H_
#endif



/*
** state manipulation
*/
KILLA_API killa_State *(killa_newstate) (killa_Alloc f, void *ud);
KILLA_API void         (killa_close) (killa_State *L);
KILLA_API killa_State *(killa_newthread) (killa_State *L);

KILLA_API killa_CFunction (killa_atpanic) (killa_State *L, killa_CFunction panicf);


KILLA_API const killa_Number *(killa_version) (killa_State *L);


/*
** basic stack manipulation
*/
KILLA_API int   (killa_absindex) (killa_State *L, int idx);
KILLA_API int   (killa_gettop) (killa_State *L);
KILLA_API void  (killa_settop) (killa_State *L, int idx);
KILLA_API void  (killa_pushvalue) (killa_State *L, int idx);
KILLA_API void  (killa_remove) (killa_State *L, int idx);
KILLA_API void  (killa_insert) (killa_State *L, int idx);
KILLA_API void  (killa_replace) (killa_State *L, int idx);
KILLA_API void  (killa_copy) (killa_State *L, int fromidx, int toidx);
KILLA_API int   (killa_checkstack) (killa_State *L, int sz);

KILLA_API void  (killa_xmove) (killa_State *from, killa_State *to, int n);


/*
** access functions (stack -> C)
*/

KILLA_API int             (killa_isnumber) (killa_State *L, int idx);
KILLA_API int             (killa_isstring) (killa_State *L, int idx);
KILLA_API int             (killa_iscfunction) (killa_State *L, int idx);
KILLA_API int             (killa_isuserdata) (killa_State *L, int idx);
KILLA_API int             (killa_type) (killa_State *L, int idx);
KILLA_API const char     *(killa_typename) (killa_State *L, int tp);

KILLA_API killa_Number    (killa_tonumberx) (killa_State *L, int idx, int *isnum);
KILLA_API killa_Integer   (killa_tointegerx) (killa_State *L, int idx, int *isnum);
KILLA_API killa_Unsigned  (killa_tounsignedx) (killa_State *L, int idx, int *isnum);
KILLA_API int             (killa_toboolean) (killa_State *L, int idx);
KILLA_API const char     *(killa_tolstring) (killa_State *L, int idx, size_t *len);
KILLA_API size_t          (killa_rawlen) (killa_State *L, int idx);
KILLA_API killa_CFunction (killa_tocfunction) (killa_State *L, int idx);
KILLA_API void           *(killa_touserdata) (killa_State *L, int idx);
KILLA_API killa_State    *(killa_tothread) (killa_State *L, int idx);
KILLA_API const void     *(killa_topointer) (killa_State *L, int idx);


/*
** Comparison and arithmetic functions
*/

#define KILLA_OPADD     0	/* ORDER TM */
#define KILLA_OPSUB     1
#define KILLA_OPMUL     2
#define KILLA_OPDIV     3
#define KILLA_OPMOD     4
#define KILLA_OPPOW     5
#define KILLA_OPUNM     6

KILLA_API void  (killa_arith) (killa_State *L, int op);

#define KILLA_OPEQ      0
#define KILLA_OPLT      1
#define KILLA_OPLE      2

KILLA_API int   (killa_rawequal) (killa_State *L, int idx1, int idx2);
KILLA_API int   (killa_compare) (killa_State *L, int idx1, int idx2, int op);


/*
** push functions (C -> stack)
*/
KILLA_API void        (killa_pushnull) (killa_State *L);
KILLA_API void        (killa_pushnumber) (killa_State *L, killa_Number n);
KILLA_API void        (killa_pushinteger) (killa_State *L, killa_Integer n);
KILLA_API void        (killa_pushunsigned) (killa_State *L, killa_Unsigned n);
KILLA_API const char *(killa_pushlstring) (killa_State *L, const char *s, size_t l);
KILLA_API const char *(killa_pushstring) (killa_State *L, const char *s);
KILLA_API const char *(killa_pushvfstring) (killa_State *L, const char *fmt,
                                                      va_list argp);
KILLA_API const char *(killa_pushfstring) (killa_State *L, const char *fmt, ...);
KILLA_API void        (killa_pushcclosure) (killa_State *L, killa_CFunction fn, int n);
KILLA_API void        (killa_pushboolean) (killa_State *L, int b);
KILLA_API void        (killa_pushlightuserdata) (killa_State *L, void *p);
KILLA_API int         (killa_pushthread) (killa_State *L);


/*
** get functions (Killa -> stack)
*/
KILLA_API void  (killa_getglobal) (killa_State *L, const char *var);
KILLA_API void  (killa_gettable) (killa_State *L, int idx);
KILLA_API void  (killa_getfield) (killa_State *L, int idx, const char *k);
KILLA_API void  (killa_rawget) (killa_State *L, int idx);
KILLA_API void  (killa_rawgeti) (killa_State *L, int idx, int n);
KILLA_API void  (killa_rawgetp) (killa_State *L, int idx, const void *p);
KILLA_API void  (killa_createtable) (killa_State *L, int narr, int nrec);
KILLA_API void *(killa_newuserdata) (killa_State *L, size_t sz);
KILLA_API int   (killa_getmetatable) (killa_State *L, int objindex);
KILLA_API void  (killa_getuservalue) (killa_State *L, int idx);


/*
** set functions (stack -> Killa)
*/
KILLA_API void  (killa_setglobal) (killa_State *L, const char *var);
KILLA_API void  (killa_settable) (killa_State *L, int idx);
KILLA_API void  (killa_setfield) (killa_State *L, int idx, const char *k);
KILLA_API void  (killa_rawset) (killa_State *L, int idx);
KILLA_API void  (killa_rawseti) (killa_State *L, int idx, int n);
KILLA_API void  (killa_rawsetp) (killa_State *L, int idx, const void *p);
KILLA_API int   (killa_setmetatable) (killa_State *L, int objindex);
KILLA_API void  (killa_setuservalue) (killa_State *L, int idx);


/*
** 'load' and 'call' functions (load and run Killa code)
*/
KILLA_API void  (killa_callk) (killa_State *L, int nargs, int nresults, int ctx,
                               killa_CFunction k);

#define killa_call(L,n,r)      killa_callk(L, (n), (r), 0, NULL)

KILLA_API int  (killa_getctx) (killa_State *L, int *ctx);

KILLA_API int  (killa_pcallk) (killa_State *L, int nargs, int nresults, int errfunc,
                               int ctx, killa_CFunction k);

#define killa_pcall(L,n,r,f)   killa_pcallk(L, (n), (r), (f), 0, NULL)

KILLA_API int (killa_load) (killa_State *L, killa_Reader reader, void *dt,
                            const char *chunkname,
                            const char *mode);

KILLA_API int (killa_dump) (killa_State *L, killa_Writer writer, void *data);


/*
** coroutine functions
*/
KILLA_API int (killa_yieldk) (killa_State *L, int nresults, int ctx,
                              killa_CFunction k);

#define killa_yield(L,n)      killa_yieldk(L, (n), 0, NULL)

KILLA_API int (killa_resume) (killa_State *L, killa_State *from, int narg);
KILLA_API int (killa_status) (killa_State *L);

/*
** garbage-collection function and options
*/

#define KILLA_GCSTOP        0
#define KILLA_GCRESTART     1
#define KILLA_GCCOLLECT     2
#define KILLA_GCCOUNT       3
#define KILLA_GCCOUNTB      4
#define KILLA_GCSTEP        5
#define KILLA_GCSETPAUSE    6
#define KILLA_GCSETSTEPMUL  7
#define KILLA_GCSETMAJORINC 8
#define KILLA_GCISRUNNING   9
#define KILLA_GCGEN         10
#define KILLA_GCINC         11

KILLA_API int (killa_gc) (killa_State *L, int what, int data);


/*
** miscellaneous functions
*/

KILLA_API int   (killa_error)  (killa_State *L);

KILLA_API int   (killa_next)   (killa_State *L, int idx);

KILLA_API void  (killa_concat) (killa_State *L, int n);
KILLA_API void  (killa_len)    (killa_State *L, int idx);

KILLA_API killa_Alloc (killa_getallocf) (killa_State *L, void **ud);
KILLA_API void  (killa_setallocf) (killa_State *L, killa_Alloc f, void *ud);



/*
** ===============================================================
** some useful macros
** ===============================================================
*/

#define killa_tonumber(L,i)         killa_tonumberx(L,i,NULL)
#define killa_tointeger(L,i)        killa_tointegerx(L,i,NULL)
#define killa_tounsigned(L,i)       killa_tounsignedx(L,i,NULL)

#define killa_pop(L,n)              killa_settop(L, -(n)-1)

#define killa_newtable(L)           killa_createtable(L, 0, 0)

#define killa_register(L,n,f)      (killa_pushcfunction(L, (f)), killa_setglobal(L, (n)))

#define killa_pushcfunction(L,f)    killa_pushcclosure(L, (f), 0)

#define killa_isfunction(L,n)      (killa_type(L, (n)) == KILLA_TFUNCTION)
#define killa_istable(L,n)         (killa_type(L, (n)) == KILLA_TTABLE)
#define killa_islightuserdata(L,n) (killa_type(L, (n)) == KILLA_TLIGHTUSERDATA)
#define killa_isnull(L,n)          (killa_type(L, (n)) == KILLA_TNULL)
#define killa_isboolean(L,n)       (killa_type(L, (n)) == KILLA_TBOOLEAN)
#define killa_isthread(L,n)        (killa_type(L, (n)) == KILLA_TTHREAD)
#define killa_isnone(L,n)          (killa_type(L, (n)) == KILLA_TNONE)
#define killa_isnoneornull(L, n)   (killa_type(L, (n)) <= 0)

#define killa_pushliteral(L, s)	\
	killa_pushlstring(L, "" s, (sizeof(s)/sizeof(char))-1)

#define killa_pushglobaltable(L)  \
	killa_rawgeti(L, KILLA_REGISTRYINDEX, KILLA_RIDX_GLOBALS)

#define killa_tostring(L,i)         killa_tolstring(L, (i), NULL)



/*
** {======================================================================
** Debug API
** =======================================================================
*/


/*
** Event codes
*/
#define KILLA_HOOKCALL      0
#define KILLA_HOOKRET       1
#define KILLA_HOOKLINE      2
#define KILLA_HOOKCOUNT     3
#define KILLA_HOOKTAILCALL  4


/*
** Event masks
*/
#define KILLA_MASKCALL  (1 << KILLA_HOOKCALL)
#define KILLA_MASKRET   (1 << KILLA_HOOKRET)
#define KILLA_MASKLINE  (1 << KILLA_HOOKLINE)
#define KILLA_MASKCOUNT (1 << KILLA_HOOKCOUNT)

typedef struct killa_Debug killa_Debug;  /* activation record */


/* Functions to be called by the debugger in specific events */
typedef void (*killa_Hook) (killa_State *L, killa_Debug *ar);


KILLA_API int (killa_getstack) (killa_State *L, int level, killa_Debug *ar);
KILLA_API int (killa_getinfo)  (killa_State *L, const char *what, killa_Debug *ar);
KILLA_API const char *(killa_getlocal)   (killa_State *L, const killa_Debug *ar, int n);
KILLA_API const char *(killa_setlocal)   (killa_State *L, const killa_Debug *ar, int n);
KILLA_API const char *(killa_getupvalue) (killa_State *L, int funcindex, int n);
KILLA_API const char *(killa_setupvalue) (killa_State *L, int funcindex, int n);

KILLA_API void *(killa_upvalueid)   (killa_State *L, int fidx, int n);
KILLA_API void  (killa_upvaluejoin) (killa_State *L, int fidx1, int n1,
                                     int fidx2, int n2);

KILLA_API int (killa_sethook) (killa_State *L, killa_Hook func, int mask, int count);
KILLA_API killa_Hook (killa_gethook) (killa_State *L);
KILLA_API int (killa_gethookmask) (killa_State *L);
KILLA_API int (killa_gethookcount) (killa_State *L);


struct killa_Debug {
  int event;
  const char *name;	/* (n) */
  const char *namewhat;	/* (n) 'global', 'local', 'field', 'method' */
  const char *what;	/* (S) 'Killa', 'C', 'main', 'tail' */
  const char *source;	/* (S) */
  int currentline;	/* (l) */
  int linedefined;	/* (S) */
  int lastlinedefined;	/* (S) */
  unsigned char nups;	/* (u) number of upvalues */
  unsigned char nparams;/* (u) number of parameters */
  char isvararg;        /* (u) */
  char istailcall;	/* (t) */
  char short_src[KILLA_IDSIZE]; /* (S) */
  /* private part */
  struct killa_CallInfo *i_ci;  /* active function */
};

#endif
