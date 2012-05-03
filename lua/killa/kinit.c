/* ========================================================================== */
/*   Initialization of libraries for killa.c                                  */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

/*
** If you embed Killa in your program and need to open the standard
** libraries, call killaL_openlibs in your program. If you need a
** different set of libraries, copy this file to your project and edit
** it to suit your needs.
*/


#define KILLA_LIB

#include "killa.h"

#include "killalib.h"
#include "kauxlib.h"


/*
** these libs are loaded by killa.c and are readily available to any Killa
** program
*/
static const killaL_Reg loadedlibs[] = {
  {"_G", killaopen_base},
  {KILLA_LOADLIBNAME, killaopen_package},
  {KILLA_COLIBNAME, killaopen_coroutine},
  {KILLA_TABLIBNAME, killaopen_table},
  {KILLA_IOLIBNAME, killaopen_io},
  {KILLA_OSLIBNAME, killaopen_os},
  {KILLA_STRLIBNAME, killaopen_string},
  {KILLA_BITLIBNAME, killaopen_bit32},
  {KILLA_MATHLIBNAME, killaopen_math},
  {KILLA_DBLIBNAME, killaopen_debug},
  {NULL, NULL}
};


/*
** these libs are preloaded and must be required before used
*/
static const killaL_Reg preloadedlibs[] = {
  {NULL, NULL}
};


KILLALIB_API void killaL_openlibs (killa_State *L) {
  const killaL_Reg *lib;
  /* call open functions from 'loadedlibs' and set results to global table */
  for (lib = loadedlibs; lib->func; lib++) {
    killaL_requiref(L, lib->name, lib->func, 1);
    killa_pop(L, 1);  /* remove lib */
  }
  /* add open functions from 'preloadedlibs' into 'package.preload' table */
  killaL_getsubtable(L, KILLA_REGISTRYINDEX, "_PRELOAD");
  for (lib = preloadedlibs; lib->func; lib++) {
    killa_pushcfunction(L, lib->func);
    killa_setfield(L, -2, lib->name);
  }
  killa_pop(L, 1);  /* remove _PRELOAD table */
}

