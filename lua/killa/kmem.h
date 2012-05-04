/* ========================================================================== */
/*   Interface to Memory Manager                                              */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KMEM_H_
#define KMEM_H_


#include <stddef.h>

#include "klimits.h"
#include "killa.h"


#define killaM_reallocv(L,b,on,n,e) \
    ((killa_cast(size_t, (n)+1) > KILLA_MAX_SIZET/(e)) ?  /* +1 to avoid warnings */ \
        (killaM_toobig(L), (void *)0) : \
        killaM_realloc_(L, (b), (on)*(e), (n)*(e)))

#define killaM_freemem(L, b, s)     killaM_realloc_(L, (b), (s), 0)
#define killaM_free(L, b)           killaM_realloc_(L, (b), sizeof(*(b)), 0)
#define killaM_freearray(L, b, n)   killaM_reallocv(L, (b), n, 0, sizeof((b)[0]))

#define killaM_malloc(L,s)  killaM_realloc_(L, NULL, 0, (s))
#define killaM_new(L,t)     killa_cast(t *, killaM_malloc(L, sizeof(t)))
#define killaM_newvector(L,n,t) \
		killa_cast(t *, killaM_reallocv(L, NULL, 0, n, sizeof(t)))

#define killaM_newobject(L,tag,s)   killaM_realloc_(L, NULL, tag, (s))

#define killaM_growvector(L,v,nelems,size,t,limit,e) \
    if ((nelems)+1 > (size)) \
        ((v)=killa_cast(t *, killaM_growaux_(L,v,&(size),sizeof(t),limit,e)))

#define killaM_reallocvector(L, v,oldn,n,t) \
    ((v)=killa_cast(t *, killaM_reallocv(L, v, oldn, n, sizeof(t))))

KILLAI_FUNC killa_noret killaM_toobig (killa_State *L);

/* not to be called directly */
KILLAI_FUNC void *killaM_realloc_ (killa_State *L, void *block, size_t oldsize,
                                                          size_t size);
KILLAI_FUNC void *killaM_growaux_ (killa_State *L, void *block, int *size,
                                   size_t size_elem, int limit,
                                   const char *what);

#endif

