/* ========================================================================== */
/*   Interface to Memory Manager                                              */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stddef.h>

#define KILLA_CORE

#include "killa.h"

#include "kdebug.h"
#include "kdo.h"
#include "kgc.h"
#include "kmem.h"
#include "kobject.h"
#include "kstate.h"



/*
** About the realloc function:
** void * frealloc (void *ud, void *ptr, size_t osize, size_t nsize);
** (`osize' is the old size, `nsize' is the new size)
**
** * frealloc(ud, NULL, x, s) creates a new block of size `s' (no
** matter 'x').
**
** * frealloc(ud, p, x, 0) frees the block `p'
** (in this specific case, frealloc must return NULL);
** particularly, frealloc(ud, NULL, 0, 0) does nothing
** (which is equivalent to free(NULL) in ANSI C)
**
** frealloc returns NULL if it cannot create or reallocate the area
** (any reallocation to an equal or smaller size cannot fail!)
*/



#define MINSIZEARRAY	4


void *killaM_growaux_ (killa_State *L, void *block, int *size, size_t size_elems,
                     int limit, const char *what) {
  void *newblock;
  int newsize;
  if (*size >= limit/2) {  /* cannot double it? */
    if (*size >= limit)  /* cannot grow even a little? */
      killaG_runerror(L, "too many %s (limit is %d)", what, limit);
    newsize = limit;  /* still have at least one free place */
  }
  else {
    newsize = (*size)*2;
    if (newsize < MINSIZEARRAY)
      newsize = MINSIZEARRAY;  /* minimum size */
  }
  newblock = killaM_reallocv(L, block, *size, newsize, size_elems);
  *size = newsize;  /* update only when everything else is OK */
  return newblock;
}


killa_noret killaM_toobig (killa_State *L) {
  killaG_runerror(L, "memory allocation error: block too big");
}



/*
** generic allocation routine.
*/
void *killaM_realloc_ (killa_State *L, void *block, size_t osize, size_t nsize) {
  void *newblock;
  killa_GlobalState *g = KILLA_G(L);
  size_t realosize = (block) ? osize : 0;
  killa_assert((realosize == 0) == (block == NULL));
#if defined(KILLA_HARDMEMTESTS)
  if (nsize > realosize && g->gcrunning)
    killaC_fullgc(L, 1);  /* force a GC whenever possible */
#endif
  newblock = (*g->frealloc)(g->ud, block, osize, nsize);
  if (newblock == NULL && nsize > 0) {
    killa_api_check(L, nsize > realosize,
                 "realloc cannot fail when shrinking a block");
    if (g->gcrunning) {
      killaC_fullgc(L, 1);  /* try to free some memory... */
      newblock = (*g->frealloc)(g->ud, block, osize, nsize);  /* try again */
    }
    if (newblock == NULL)
      killaD_throw(L, KILLA_ERRMEM);
  }
  killa_assert((nsize == 0) == (newblock == NULL));
  g->GCdebt = (g->GCdebt + nsize) - realosize;
#if defined(TRACEMEM)
  { /* auxiliary patch to monitor garbage collection.
    ** To plot, gnuplot with following command:
    ** plot TRACEMEM using 1:2 with lines, TRACEMEM using 1:3 with lines
    */
    static unsigned long total = 0;  /* our "time" */
    static FILE *f = NULL;  /* output file */
    total++;  /* "time" always grows */
    if ((total % 200) == 0) {
      if (f == NULL) f = fopen(TRACEMEM, "w");
      fprintf(f, "%lu %u %d %d\n", total,
              killa_gettotalbytes(g), g->GCdebt, g->gcstate * 10000);
    }
  }
#endif

  return newblock;
}

