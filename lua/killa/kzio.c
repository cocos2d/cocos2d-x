/* ========================================================================== */
/*   A generic input stream interface                                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <string.h>

#define KILLA_CORE

#include "killa.h"

#include "klimits.h"
#include "kmem.h"
#include "kstate.h"
#include "kzio.h"


int killaZ_fill (killa_ZIO *z) {
  size_t size;
  killa_State *L = z->L;
  const char *buff;
  killa_unlock(L);
  buff = z->reader(L, z->data, &size);
  killa_lock(L);
  if (buff == NULL || size == 0)
    return KILLA_EOZ;
  z->n = size - 1;  /* discount char being returned */
  z->p = buff;
  return killa_cast_uchar(*(z->p++));
}


void killaZ_init (killa_State *L, killa_ZIO *z, killa_Reader reader, void *data) {
  z->L = L;
  z->reader = reader;
  z->data = data;
  z->n = 0;
  z->p = NULL;
}


/* --------------------------------------------------------------- read --- */
size_t killaZ_read (killa_ZIO *z, void *b, size_t n) {
  while (n) {
    size_t m;
    if (z->n == 0) {  /* no bytes in buffer? */
      if (killaZ_fill(z) == KILLA_EOZ)  /* try to read more */
        return n;  /* no more input; return number of missing bytes */
      else {
        z->n++;  /* killaZ_fill consumed first byte; put it back */
        z->p--;
      }
    }
    m = (n <= z->n) ? n : z->n;  /* min. between n and z->n */
    memcpy(b, z->p, m);
    z->n -= m;
    z->p += m;
    b = (char *)b + m;
    n -= m;
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
char *killaZ_openspace (killa_State *L, killa_Mbuffer *buff, size_t n) {
  if (n > buff->buffsize) {
    if (n < KILLA_MINBUFFER) n = KILLA_MINBUFFER;
    killaZ_resizebuffer(L, buff, n);
  }
  return buff->buffer;
}


