/* ========================================================================== */
/*   String table (keeps all strings handled by Killa)                        */
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

#include "kmem.h"
#include "kobject.h"
#include "kstate.h"
#include "kstring.h"



void killaS_resize (killa_State *L, int newsize) {
  int i;
  killa_StringTable *tb = &KILLA_G(L)->strt;
  /* cannot resize while GC is traversing strings */
  killaC_runtilstate(L, ~killa_bitmask(killa_GCSsweepstring));
  if (newsize > tb->size) {
    killaM_reallocvector(L, tb->hash, tb->size, newsize, killa_GCObject *);
    for (i = tb->size; i < newsize; i++) tb->hash[i] = NULL;
  }
  /* rehash */
  for (i=0; i<tb->size; i++) {
    killa_GCObject *p = tb->hash[i];
    tb->hash[i] = NULL;
    while (p) {  /* for each node in the list */
      killa_GCObject *next = gch(p)->next;  /* save next */
      unsigned int h = killa_lmod(killa_gco2ts(p)->hash, newsize);  /* new position */
      gch(p)->next = tb->hash[h];  /* chain it */
      tb->hash[h] = p;
      killa_resetoldbit(p);  /* see MOVE OLD rule */
      p = next;
    }
  }
  if (newsize < tb->size) {
    /* shrinking slice must be empty */
    killa_assert(tb->hash[newsize] == NULL && tb->hash[tb->size - 1] == NULL);
    killaM_reallocvector(L, tb->hash, tb->size, newsize, killa_GCObject *);
  }
  tb->size = newsize;
}


static killa_TString *newlstr (killa_State *L, const char *str, size_t l,
                                       unsigned int h) {
  size_t totalsize;  /* total size of killa_TString object */
  killa_GCObject **list;  /* (pointer to) list where it will be inserted */
  killa_TString *ts;
  killa_StringTable *tb = &KILLA_G(L)->strt;
  if (l+1 > (KILLA_MAX_SIZET - sizeof(killa_TString))/sizeof(char))
    killaM_toobig(L);
  if (tb->nuse >= killa_cast(killa_uint32, tb->size) && tb->size <= KILLA_MAX_INT/2)
    killaS_resize(L, tb->size*2);  /* too crowded */
  totalsize = sizeof(killa_TString) + ((l + 1) * sizeof(char));
  list = &tb->hash[killa_lmod(h, tb->size)];
  ts = &killaC_newobj(L, KILLA_TSTRING, totalsize, list, 0)->ts;
  ts->tsv.len = l;
  ts->tsv.hash = h;
  ts->tsv.reserved = 0;
  memcpy(ts+1, str, l*sizeof(char));
  ((char *)(ts+1))[l] = '\0';  /* ending 0 */
  tb->nuse++;
  return ts;
}


killa_TString *killaS_newlstr (killa_State *L, const char *str, size_t l) {
  killa_GCObject *o;
  unsigned int h = killa_cast(unsigned int, l);  /* seed */
  size_t step = (l>>5)+1;  /* if string is too long, don't hash all its chars */
  size_t l1;
  for (l1=l; l1>=step; l1-=step)  /* compute hash */
    h = h ^ ((h<<5)+(h>>2)+killa_cast(unsigned char, str[l1-1]));
  for (o = KILLA_G(L)->strt.hash[killa_lmod(h, KILLA_G(L)->strt.size)];
       o != NULL;
       o = gch(o)->next) {
    killa_TString *ts = killa_rawgco2ts(o);
    if (h == ts->tsv.hash &&
        ts->tsv.len == l &&
        (memcmp(str, killa_getstr(ts), l * sizeof(char)) == 0)) {
      if (killa_isdead(KILLA_G(L), o))  /* string is dead (but was not collected yet)? */
        killa_changewhite(o);  /* resurrect it */
      return ts;
    }
  }
  return newlstr(L, str, l, h);  /* not found; create a new string */
}


killa_TString *killaS_new (killa_State *L, const char *str) {
  return killaS_newlstr(L, str, strlen(str));
}


killa_Udata *killaS_newudata (killa_State *L, size_t s, killa_Table *e) {
  killa_Udata *u;
  if (s > KILLA_MAX_SIZET - sizeof(killa_Udata))
    killaM_toobig(L);
  u = &killaC_newobj(L, KILLA_TUSERDATA, sizeof(killa_Udata) + s, NULL, 0)->u;
  u->uv.len = s;
  u->uv.metatable = NULL;
  u->uv.env = e;
  return u;
}

