/* ========================================================================== */
/*   Buffered streams                                                         */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KZIO_H_
#define KZIO_H_

#include "killa.h"

#include "kmem.h"


#define KILLA_EOZ   (-1)    /* end of stream */

typedef struct killa_Zio    killa_ZIO;

#define killa_zgetc(z)  (((z)->n--)>0 ?  killa_cast_uchar(*(z)->p++) : killaZ_fill(z))


typedef struct killa_Mbuffer {
  char *buffer;
  size_t n;
  size_t buffsize;
} killa_Mbuffer;

#define killaZ_initbuffer(L, buff)  ((buff)->buffer = NULL, (buff)->buffsize = 0)

#define killaZ_buffer(buff)     ((buff)->buffer)
#define killaZ_sizebuffer(buff) ((buff)->buffsize)
#define killaZ_bufflen(buff)    ((buff)->n)

#define killaZ_resetbuffer(buff)    ((buff)->n = 0)


#define killaZ_resizebuffer(L, buff, size) \
    (killaM_reallocvector(L, (buff)->buffer, (buff)->buffsize, size, char), \
    (buff)->buffsize = size)

#define killaZ_freebuffer(L, buff)  killaZ_resizebuffer(L, buff, 0)


KILLAI_FUNC char *killaZ_openspace (killa_State *L, killa_Mbuffer *buff, size_t n);
KILLAI_FUNC void killaZ_init (killa_State *L, killa_ZIO *z, killa_Reader reader,
                              void *data);
KILLAI_FUNC size_t killaZ_read (killa_ZIO* z, void* b, size_t n);	/* read next n bytes */



/* --------- Private Part ------------------ */

struct killa_Zio {
  size_t n;			/* bytes still unread */
  const char *p;		/* current position in buffer */
  killa_Reader reader;		/* reader function */
  void* data;			/* additional data */
  killa_State *L;			/* Killa state (for reader) */
};


KILLAI_FUNC int killaZ_fill (killa_ZIO *z);

#endif
