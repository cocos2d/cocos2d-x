/* ========================================================================== */
/*   Dynamic library loader for Killa                                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

/*
** This module contains an implementation of loadlib for Unix systems
** that have dlfcn, an implementation for Windows, and a stub for other
** systems.
*/


/*
** if needed, includes windows header before everything else
*/
#if defined(_WIN32)
#include <windows.h>
#endif


#include <stdlib.h>
#include <string.h>


#define loadlib_c
#define KILLA_LIB

#include "killa.h"

#include "kauxlib.h"
#include "killalib.h"


/*
** KILLA_PATH and KILLA_CPATH are the names of the environment
** variables that Killa check to set its paths.
*/
#if !defined(KILLA_PATH)
#define KILLA_PATH	"KILLA_PATH"
#endif

#if !defined(KILLA_CPATH)
#define KILLA_CPATH	"KILLA_CPATH"
#endif

#define KILLA_PATHSUFFIX    "_" KILLA_VERSION_MAJOR "_" KILLA_VERSION_MINOR

#define KILLA_PATHVERSION   KILLA_PATH KILLA_PATHSUFFIX
#define KILLA_CPATHVERSION	KILLA_CPATH KILLA_PATHSUFFIX

/*
** KILLA_PATH_SEP is the character that separates templates in a path.
** KILLA_PATH_MARK is the string that marks the substitution points in a
** template.
** KILLA_EXEC_DIR in a Windows path is replaced by the executable's
** directory.
** KILLA_IGMARK is a mark to ignore all before it when building the
** killaopen_ function name.
*/
#if !defined (KILLA_PATH_SEP)
#define KILLA_PATH_SEP		";"
#endif
#if !defined (KILLA_PATH_MARK)
#define KILLA_PATH_MARK		"?"
#endif
#if !defined (KILLA_EXEC_DIR)
#define KILLA_EXEC_DIR		"!"
#endif
#if !defined (KILLA_IGMARK)
#define KILLA_IGMARK		"-"
#endif


/*
** KILLA_CSUBSEP is the character that replaces dots in submodule names
** when searching for a C loader.
** KILLA_LSUBSEP is the character that replaces dots in submodule names
** when searching for a Killa loader.
*/
#if !defined(KILLA_CSUBSEP)
#define KILLA_CSUBSEP		KILLA_DIRSEP
#endif

#if !defined(KILLA_LSUBSEP)
#define KILLA_LSUBSEP		KILLA_DIRSEP
#endif


/* prefix for open functions in C libraries */
#define KILLA_POF		"killaopen_"

/* separator for open functions in C libraries */
#define KILLA_OFSEP	"_"


#define LIBPREFIX	"LOADLIB: "

#define POF		KILLA_POF
#define LIB_FAIL	"open"


/* error codes for ll_loadfunc */
#define ERRLIB		1
#define ERRFUNC		2

#define setprogdir(L)		((void)0)


/*
** system-dependent functions
*/
static void ll_unloadlib (void *lib);
static void *ll_load (killa_State *L, const char *path, int seeglb);
static killa_CFunction ll_sym (killa_State *L, void *lib, const char *sym);



#if defined(KILLA_USE_DLOPEN)
/*
** {========================================================================
** This is an implementation of loadlib based on the dlfcn interface.
** The dlfcn interface is available in Linux, SunOS, Solaris, IRIX, FreeBSD,
** NetBSD, AIX 4.2, HPUX 11, and  probably most other Unix flavors, at least
** as an emulation layer on top of native functions.
** =========================================================================
*/

#include <dlfcn.h>

static void ll_unloadlib (void *lib) {
  dlclose(lib);
}


static void *ll_load (killa_State *L, const char *path, int seeglb) {
  void *lib = dlopen(path, RTLD_NOW | (seeglb ? RTLD_GLOBAL : RTLD_LOCAL));
  if (lib == NULL) killa_pushstring(L, dlerror());
  return lib;
}


static killa_CFunction ll_sym (killa_State *L, void *lib, const char *sym) {
  killa_CFunction f = (killa_CFunction)dlsym(lib, sym);
  if (f == NULL) killa_pushstring(L, dlerror());
  return f;
}

/* }====================================================== */



#elif defined(KILLA_DL_DLL)
/*
** {======================================================================
** This is an implementation of loadlib for Windows using native functions.
** =======================================================================
*/

#undef setprogdir

/*
** optional flags for LoadLibraryEx
*/
#if !defined(KILLA_LLE_FLAGS)
#define KILLA_LLE_FLAGS	0
#endif


static void setprogdir (killa_State *L) {
  char buff[MAX_PATH + 1];
  char *lb;
  DWORD nsize = sizeof(buff)/sizeof(char);
  DWORD n = GetModuleFileNameA(NULL, buff, nsize);
  if (n == 0 || n == nsize || (lb = strrchr(buff, '\\')) == NULL)
    killaL_error(L, "unable to get ModuleFileName");
  else {
    *lb = '\0';
    killaL_gsub(L, killa_tostring(L, -1), KILLA_EXEC_DIR, buff);
    killa_remove(L, -2);  /* remove original string */
  }
}


static void pusherror (killa_State *L) {
  int error = GetLastError();
  char buffer[128];
  if (FormatMessageA(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, error, 0, buffer, sizeof(buffer)/sizeof(char), NULL))
    killa_pushstring(L, buffer);
  else
    killa_pushfstring(L, "system error %d\n", error);
}

static void ll_unloadlib (void *lib) {
  FreeLibrary((HMODULE)lib);
}


static void *ll_load (killa_State *L, const char *path, int seeglb) {
  HMODULE lib = LoadLibraryExA(path, NULL, KILLA_LLE_FLAGS);
  (void)(seeglb);  /* not used: symbols are 'global' by default */
  if (lib == NULL) pusherror(L);
  return lib;
}


static killa_CFunction ll_sym (killa_State *L, void *lib, const char *sym) {
  killa_CFunction f = (killa_CFunction)GetProcAddress((HMODULE)lib, sym);
  if (f == NULL) pusherror(L);
  return f;
}

/* }====================================================== */


#else
/*
** {======================================================
** Fallback for other systems
** =======================================================
*/

#undef LIB_FAIL
#define LIB_FAIL	"absent"


#define DLMSG	"dynamic libraries not enabled; check your Killa installation"


static void ll_unloadlib (void *lib) {
  (void)(lib);  /* not used */
}


static void *ll_load (killa_State *L, const char *path, int seeglb) {
  (void)(path); (void)(seeglb);  /* not used */
  killa_pushliteral(L, DLMSG);
  return NULL;
}


static killa_CFunction ll_sym (killa_State *L, void *lib, const char *sym) {
  (void)(lib); (void)(sym);  /* not used */
  killa_pushliteral(L, DLMSG);
  return NULL;
}

/* }====================================================== */
#endif



static void **ll_register (killa_State *L, const char *path) {
  void **plib;
  killa_pushfstring(L, "%s%s", LIBPREFIX, path);
  killa_gettable(L, KILLA_REGISTRYINDEX);  /* check library in registry? */
  if (!killa_isnull(L, -1))  /* is there an entry? */
    plib = (void **)killa_touserdata(L, -1);
  else {  /* no entry yet; create one */
    killa_pop(L, 1);  /* remove result from gettable */
    plib = (void **)killa_newuserdata(L, sizeof(const void *));
    *plib = NULL;
    killaL_setmetatable(L, "_LOADLIB");
    killa_pushfstring(L, "%s%s", LIBPREFIX, path);
    killa_pushvalue(L, -2);
    killa_settable(L, KILLA_REGISTRYINDEX);
  }
  return plib;
}


/*
** __gc tag method: calls library's `ll_unloadlib' function with the lib
** handle
*/
static int gctm (killa_State *L) {
  void **lib = (void **)killaL_checkudata(L, 1, "_LOADLIB");
  if (*lib) ll_unloadlib(*lib);
  *lib = NULL;  /* mark library as closed */
  return 0;
}


static int ll_loadfunc (killa_State *L, const char *path, const char *sym) {
  void **reg = ll_register(L, path);
  if (*reg == NULL) *reg = ll_load(L, path, *sym == '*');
  if (*reg == NULL) return ERRLIB;  /* unable to load library */
  if (*sym == '*') {  /* loading only library (no function)? */
    killa_pushboolean(L, 1);  /* return 'true' */
    return 0;  /* no errors */
  }
  else {
    killa_CFunction f = ll_sym(L, *reg, sym);
    if (f == NULL)
      return ERRFUNC;  /* unable to find function */
    killa_pushcfunction(L, f);  /* else create new function */
    return 0;  /* no errors */
  }
}


static int ll_loadlib (killa_State *L) {
  const char *path = killaL_checkstring(L, 1);
  const char *init = killaL_checkstring(L, 2);
  int stat = ll_loadfunc(L, path, init);
  if (stat == 0)  /* no errors? */
    return 1;  /* return the loaded function */
  else {  /* error; error message is on stack top */
    killa_pushnull(L);
    killa_insert(L, -2);
    killa_pushstring(L, (stat == ERRLIB) ?  LIB_FAIL : "init");
    return 3;  /* return nil, error message, and where */
  }
}



/*
** {======================================================
** 'require' function
** =======================================================
*/


static int readable (const char *filename) {
  FILE *f = fopen(filename, "r");  /* try to open file */
  if (f == NULL) return 0;  /* open failed */
  fclose(f);
  return 1;
}


static const char *pushnexttemplate (killa_State *L, const char *path) {
  const char *l;
  while (*path == *KILLA_PATH_SEP) path++;  /* skip separators */
  if (*path == '\0') return NULL;  /* no more templates */
  l = strchr(path, *KILLA_PATH_SEP);  /* find next separator */
  if (l == NULL) l = path + strlen(path);
  killa_pushlstring(L, path, l - path);  /* template */
  return l;
}


static const char *searchpath (killa_State *L, const char *name,
                                             const char *path,
                                             const char *sep,
                                             const char *dirsep) {
  killaL_Buffer msg;  /* to build error message */
  killaL_buffinit(L, &msg);
  if (*sep != '\0')  /* non-empty separator? */
    name = killaL_gsub(L, name, sep, dirsep);  /* replace it by 'dirsep' */
  while ((path = pushnexttemplate(L, path)) != NULL) {
    const char *filename = killaL_gsub(L, killa_tostring(L, -1),
                                     KILLA_PATH_MARK, name);
    killa_remove(L, -2);  /* remove path template */
    if (readable(filename))  /* does file exist and is readable? */
      return filename;  /* return that file name */
    killa_pushfstring(L, "\n\tno file " KILLA_QS, filename);
    killa_remove(L, -2);  /* remove file name */
    killaL_addvalue(&msg);  /* concatenate error msg. entry */
  }
  killaL_pushresult(&msg);  /* create error message */
  return NULL;  /* not found */
}


static int ll_searchpath (killa_State *L) {
  const char *f = searchpath(L, killaL_checkstring(L, 1),
                                killaL_checkstring(L, 2),
                                killaL_optstring(L, 3, "."),
                                killaL_optstring(L, 4, KILLA_DIRSEP));
  if (f != NULL) return 1;
  else {  /* error message is on top of the stack */
    killa_pushnull(L);
    killa_insert(L, -2);
    return 2;  /* return nil + error message */
  }
}


static const char *findfile (killa_State *L, const char *name,
                                           const char *pname,
                                           const char *dirsep) {
  const char *path;
  killa_getfield(L, killa_upvalueindex(1), pname);
  path = killa_tostring(L, -1);
  if (path == NULL)
    killaL_error(L, KILLA_QL("package.%s") " must be a string", pname);
  return searchpath(L, name, path, ".", dirsep);
}


static int checkload (killa_State *L, int stat, const char *filename) {
  if (stat) {  /* module loaded successfully? */
    killa_pushstring(L, filename);  /* will be 2nd argument to module */
    return 2;  /* return open function and file name */
  }
  else
    return killaL_error(L, "error loading module " KILLA_QS
                         " from file " KILLA_QS ":\n\t%s",
                          killa_tostring(L, 1), filename, killa_tostring(L, -1));
}


static int searcher_Killa (killa_State *L) {
  const char *filename;
  const char *name = killaL_checkstring(L, 1);
  filename = findfile(L, name, "path", KILLA_LSUBSEP);
  if (filename == NULL) return 1;  /* module not found in this path */
  return checkload(L, (killaL_loadfile(L, filename) == KILLA_OK), filename);
}


static int loadfunc (killa_State *L, const char *filename, const char *modname) {
  const char *funcname;
  const char *mark;
  modname = killaL_gsub(L, modname, ".", KILLA_OFSEP);
  mark = strchr(modname, *KILLA_IGMARK);
  if (mark) {
    int stat;
    funcname = killa_pushlstring(L, modname, mark - modname);
    funcname = killa_pushfstring(L, POF"%s", funcname);
    stat = ll_loadfunc(L, filename, funcname);
    if (stat != ERRFUNC) return stat;
    modname = mark + 1;  /* else go ahead and try old-style name */
  }
  funcname = killa_pushfstring(L, POF"%s", modname);
  return ll_loadfunc(L, filename, funcname);
}


static int searcher_C (killa_State *L) {
  const char *name = killaL_checkstring(L, 1);
  const char *filename = findfile(L, name, "cpath", KILLA_CSUBSEP);
  if (filename == NULL) return 1;  /* module not found in this path */
  return checkload(L, (loadfunc(L, filename, name) == 0), filename);
}


static int searcher_Croot (killa_State *L) {
  const char *filename;
  const char *name = killaL_checkstring(L, 1);
  const char *p = strchr(name, '.');
  int stat;
  if (p == NULL) return 0;  /* is root */
  killa_pushlstring(L, name, p - name);
  filename = findfile(L, killa_tostring(L, -1), "cpath", KILLA_CSUBSEP);
  if (filename == NULL) return 1;  /* root not found */
  if ((stat = loadfunc(L, filename, name)) != 0) {
    if (stat != ERRFUNC)
      return checkload(L, 0, filename);  /* real error */
    else {  /* open function not found */
      killa_pushfstring(L, "\n\tno module " KILLA_QS " in file " KILLA_QS,
                         name, filename);
      return 1;
    }
  }
  killa_pushstring(L, filename);  /* will be 2nd argument to module */
  return 2;
}


static int searcher_preload (killa_State *L) {
  const char *name = killaL_checkstring(L, 1);
  killa_getfield(L, KILLA_REGISTRYINDEX, "_PRELOAD");
  killa_getfield(L, -1, name);
  if (killa_isnull(L, -1))  /* not found? */
    killa_pushfstring(L, "\n\tno field package.preload['%s']", name);
  return 1;
}


static void findloader (killa_State *L, const char *name) {
  int i;
  killaL_Buffer msg;  /* to build error message */
  killaL_buffinit(L, &msg);
  killa_getfield(L, killa_upvalueindex(1), "searchers");  /* will be at index 3 */
  if (!killa_istable(L, 3))
    killaL_error(L, KILLA_QL("package.searchers") " must be a table");
  /*  iterate over available seachers to find a loader */
  for (i = KILLA_BASE; ; i++) {
    killa_rawgeti(L, 3, i);  /* get a seacher */
    if (killa_isnull(L, -1)) {  /* no more searchers? */
      killa_pop(L, 1);  /* remove nil */
      killaL_pushresult(&msg);  /* create error message */
      killaL_error(L, "module " KILLA_QS " not found:%s",
                    name, killa_tostring(L, -1));
    }
    killa_pushstring(L, name);
    killa_call(L, 1, 2);  /* call it */
    if (killa_isfunction(L, -2))  /* did it find a loader? */
      return;  /* module loader found */
    else if (killa_isstring(L, -2)) {  /* searcher returned error message? */
      killa_pop(L, 1);  /* remove extra return */
      killaL_addvalue(&msg);  /* concatenate error message */
    }
    else
      killa_pop(L, 2);  /* remove both returns */
  }
}


static int ll_require (killa_State *L) {
  const char *name = killaL_checkstring(L, 1);
  killa_settop(L, 1);  /* _LOADED table will be at index 2 */
  killa_getfield(L, KILLA_REGISTRYINDEX, "_LOADED");
  killa_getfield(L, 2, name);  /* _LOADED[name] */
  if (killa_toboolean(L, -1))  /* is it there? */
    return 1;  /* package is already loaded */
  /* else must load package */
  killa_pop(L, 1);  /* remove 'getfield' result */
  findloader(L, name);
  killa_pushstring(L, name);  /* pass name as argument to module loader */
  killa_insert(L, -2);  /* name is 1st argument (before search data) */
  killa_call(L, 2, 1);  /* run loader to load module */
  if (!killa_isnull(L, -1))  /* non-nil return? */
    killa_setfield(L, 2, name);  /* _LOADED[name] = returned value */
  killa_getfield(L, 2, name);
  if (killa_isnull(L, -1)) {   /* module did not set a value? */
    killa_pushboolean(L, 1);  /* use true as result */
    killa_pushvalue(L, -1);  /* extra copy to be returned */
    killa_setfield(L, 2, name);  /* _LOADED[name] = true */
  }
  return 1;
}

/* }====================================================== */



/*
** {======================================================
** 'module' function
** =======================================================
*/
#if defined(KILLA_COMPAT_MODULE)

/*
** changes the environment variable of calling function
*/
static void set_env (killa_State *L) {
  killa_Debug ar;
  if (killa_getstack(L, 1, &ar) == 0 ||
      killa_getinfo(L, "f", &ar) == 0 ||  /* get calling function */
      killa_iscfunction(L, -1))
    killaL_error(L, KILLA_QL("module") " not called from a Killa function");
  killa_pushvalue(L, -2);  /* copy new environment table to top */
  killa_setupvalue(L, -2, 1);
  killa_pop(L, 1);  /* remove function */
}


static void dooptions (killa_State *L, int n) {
  int i;
  for (i = 2; i <= n; i++) {
    if (killa_isfunction(L, i)) {  /* avoid 'calling' extra info. */
      killa_pushvalue(L, i);  /* get option (a function) */
      killa_pushvalue(L, -2);  /* module */
      killa_call(L, 1, 0);
    }
  }
}


static void modinit (killa_State *L, const char *modname) {
  const char *dot;
  killa_pushvalue(L, -1);
  killa_setfield(L, -2, "_M");  /* module._M = module */
  killa_pushstring(L, modname);
  killa_setfield(L, -2, "_NAME");
  dot = strrchr(modname, '.');  /* look for last dot in module name */
  if (dot == NULL) dot = modname;
  else dot++;
  /* set _PACKAGE as package name (full module name minus last part) */
  killa_pushlstring(L, modname, dot - modname);
  killa_setfield(L, -2, "_PACKAGE");
}


static int ll_module (killa_State *L) {
  const char *modname = killaL_checkstring(L, 1);
  int lastarg = killa_gettop(L);  /* last parameter */
  killaL_pushmodule(L, modname, 1);  /* get/create module table */
  /* check whether table already has a _NAME field */
  killa_getfield(L, -1, "_NAME");
  if (!killa_isnull(L, -1))  /* is table an initialized module? */
    killa_pop(L, 1);
  else {  /* no; initialize it */
    killa_pop(L, 1);
    modinit(L, modname);
  }
  killa_pushvalue(L, -1);
  set_env(L);
  dooptions(L, lastarg);
  return 1;
}


static int ll_seeall (killa_State *L) {
  killaL_checktype(L, 1, KILLA_TTABLE);
  if (!killa_getmetatable(L, 1)) {
    killa_createtable(L, 0, 1); /* create new metatable */
    killa_pushvalue(L, -1);
    killa_setmetatable(L, 1);
  }
  killa_pushglobaltable(L);
  killa_setfield(L, -2, "__index");  /* mt.__index = _G */
  return 0;
}

#endif
/* }====================================================== */



/* auxiliary mark (for internal use) */
#define AUXMARK		"\1"


/*
** return registry.KILLA_NOENV as a boolean
*/
static int noenv (killa_State *L) {
  int b;
  killa_getfield(L, KILLA_REGISTRYINDEX, "KILLA_NOENV");
  b = killa_toboolean(L, -1);
  killa_pop(L, 1);  /* remove value */
  return b;
}


static void setpath (killa_State *L, const char *fieldname, const char *envname1,
                                   const char *envname2, const char *def) {
  const char *path = getenv(envname1);
  if (path == NULL)  /* no environment variable? */
    path = getenv(envname2);  /* try alternative name */
  if (path == NULL || noenv(L))  /* no environment variable? */
    killa_pushstring(L, def);  /* use default */
  else {
    /* replace ";;" by ";AUXMARK;" and then AUXMARK by default path */
    path = killaL_gsub(L, path, KILLA_PATH_SEP KILLA_PATH_SEP,
                              KILLA_PATH_SEP AUXMARK KILLA_PATH_SEP);
    killaL_gsub(L, path, AUXMARK, def);
    killa_remove(L, -2);
  }
  setprogdir(L);
  killa_setfield(L, -2, fieldname);
}


static const killaL_Reg pk_funcs[] = {
  {"loadlib", ll_loadlib},
  {"searchpath", ll_searchpath},
#if defined(KILLA_COMPAT_MODULE)
  {"seeall", ll_seeall},
#endif
  {NULL, NULL}
};


static const killaL_Reg ll_funcs[] = {
#if defined(KILLA_COMPAT_MODULE)
  {"module", ll_module},
#endif
  {"require", ll_require},
  {NULL, NULL}
};


static const killa_CFunction searchers[] =
  {searcher_preload, searcher_Killa, searcher_C, searcher_Croot, NULL};


KILLAMOD_API int killaopen_package (killa_State *L) {
  int i;
  /* create new type _LOADLIB */
  killaL_newmetatable(L, "_LOADLIB");
  killa_pushcfunction(L, gctm);
  killa_setfield(L, -2, "__gc");
  /* create `package' table */
  killaL_newlib(L, pk_funcs);
  /* create 'searchers' table */
  killa_createtable(L, sizeof(searchers)/sizeof(searchers[0]) - 1, 0);
  /* fill it with pre-defined searchers */
  for (i=0; searchers[i] != NULL; i++) {
    killa_pushvalue(L, -2);  /* set 'package' as upvalue for all searchers */
    killa_pushcclosure(L, searchers[i], 1);
    killa_rawseti(L, -2, i + KILLA_BASE);
  }
#if defined(KILLA_COMPAT_LOADERS)
  killa_pushvalue(L, -1);  /* make a copy of 'searchers' table */
  killa_setfield(L, -3, "loaders");  /* put it in field `loaders' */
#endif
  killa_setfield(L, -2, "searchers");  /* put it in field 'searchers' */
  /* set field 'path' */
  setpath(L, "path", KILLA_PATHVERSION, KILLA_PATH, KILLA_PATH_DEFAULT);
  /* set field 'cpath' */
  setpath(L, "cpath", KILLA_CPATHVERSION, KILLA_CPATH, KILLA_CPATH_DEFAULT);
  /* store config information */
  killa_pushliteral(L, KILLA_DIRSEP "\n" KILLA_PATH_SEP "\n" KILLA_PATH_MARK "\n"
                     KILLA_EXEC_DIR "\n" KILLA_IGMARK "\n");
  killa_setfield(L, -2, "config");
  /* set field `loaded' */
  killaL_getsubtable(L, KILLA_REGISTRYINDEX, "_LOADED");
  killa_setfield(L, -2, "loaded");
  /* set field `preload' */
  killaL_getsubtable(L, KILLA_REGISTRYINDEX, "_PRELOAD");
  killa_setfield(L, -2, "preload");
  killa_pushglobaltable(L);
  killa_pushvalue(L, -2);  /* set 'package' as upvalue for next lib */
  killaL_setfuncs(L, ll_funcs, 1);  /* open lib into global table */
  killa_pop(L, 1);  /* pop global table */
  return 1;  /* return 'package' table */
}

