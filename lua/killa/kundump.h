/* ========================================================================== */
/*   Load precompiled Killa scripts                                           */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KUNDUMP_H_
#define KUNDUMP_H_

#include "kobject.h"
#include "kzio.h"

/* load one chunk; from lundump.c */
KILLAI_FUNC killa_Proto* killaU_undump (killa_State* L, killa_ZIO* Z, killa_Mbuffer* buff, const char* name);

/* make header; from lundump.c */
KILLAI_FUNC void killaU_header (killa_ubyte* h);

/* dump one chunk; from ldump.c */
KILLAI_FUNC int killaU_dump (killa_State* L, const killa_Proto* f, killa_Writer w, void* data, int strip);

/* data to catch conversion errors */
#define KILLAC_TAIL "\x19\x93\r\n\x1a\n"

/* size in bytes of header of binary files */
#define KILLAC_HEADERSIZE   (sizeof(KILLA_SIGNATURE)-sizeof(char)+2+6+sizeof(KILLAC_TAIL)-sizeof(char))

#endif
