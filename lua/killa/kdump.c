/* ========================================================================== */
/*   Save precompiled Killa scripts                                           */
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

#include "kobject.h"
#include "kstate.h"
#include "kundump.h"

typedef struct {
 killa_State* L;
 killa_Writer writer;
 void* data;
 int strip;
 int status;
} DumpState;

#define DumpMem(b,n,size,D)	DumpBlock(b,(n)*(size),D)
#define DumpVar(x,D)		DumpMem(&x,1,sizeof(x),D)

static void DumpBlock(const void* b, size_t size, DumpState* D)
{
 if (D->status==0)
 {
  killa_unlock(D->L);
  D->status=(*D->writer)(D->L,b,size,D->data);
  killa_lock(D->L);
 }
}

static void DumpChar(int y, DumpState* D)
{
 char x=(char)y;
 DumpVar(x,D);
}

static void DumpInt(int x, DumpState* D)
{
 DumpVar(x,D);
}

static void DumpNumber(killa_Number x, DumpState* D)
{
 DumpVar(x,D);
}

static void DumpVector(const void* b, int n, size_t size, DumpState* D)
{
 DumpInt(n,D);
 DumpMem(b,n,size,D);
}

static void DumpString(const killa_TString* s, DumpState* D)
{
 if (s==NULL)
 {
  size_t size=0;
  DumpVar(size,D);
 }
 else
 {
  size_t size=s->tsv.len+1;		/* include trailing '\0' */
  DumpVar(size,D);
  DumpBlock(killa_getstr(s),size*sizeof(char),D);
 }
}

#define DumpCode(f,D)	 DumpVector(f->code,f->sizecode,sizeof(killa_Instruction),D)

static void DumpFunction(const killa_Proto* f, DumpState* D);

static void DumpConstants(const killa_Proto* f, DumpState* D)
{
 int i,n=f->sizek;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  const killa_TValue* o=&f->k[i];
  DumpChar(killa_ttype(o),D);
  switch (killa_ttype(o))
  {
   case KILLA_TNULL:
	break;
   case KILLA_TBOOLEAN:
	DumpChar(killa_bvalue(o),D);
	break;
   case KILLA_TNUMBER:
	DumpNumber(killa_nvalue(o),D);
	break;
   case KILLA_TSTRING:
	DumpString(killa_rawtsvalue(o),D);
	break;
  }
 }
 n=f->sizep;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpFunction(f->p[i],D);
}

static void DumpUpvalues(const killa_Proto* f, DumpState* D)
{
 int i,n=f->sizeupvalues;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  DumpChar(f->upvalues[i].instack,D);
  DumpChar(f->upvalues[i].idx,D);
 }
}

static void DumpDebug(const killa_Proto* f, DumpState* D)
{
 int i,n;
 DumpString((D->strip) ? NULL : f->source,D);
 n= (D->strip) ? 0 : f->sizelineinfo;
 DumpVector(f->lineinfo,n,sizeof(int),D);
 n= (D->strip) ? 0 : f->sizelocvars;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  DumpString(f->locvars[i].varname,D);
  DumpInt(f->locvars[i].startpc,D);
  DumpInt(f->locvars[i].endpc,D);
 }
 n= (D->strip) ? 0 : f->sizeupvalues;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpString(f->upvalues[i].name,D);
}

static void DumpFunction(const killa_Proto* f, DumpState* D)
{
 DumpInt(f->linedefined,D);
 DumpInt(f->lastlinedefined,D);
 DumpChar(f->numparams,D);
 DumpChar(f->is_vararg,D);
 DumpChar(f->maxstacksize,D);
 DumpCode(f,D);
 DumpConstants(f,D);
 DumpUpvalues(f,D);
 DumpDebug(f,D);
}

static void DumpHeader(DumpState* D)
{
 killa_ubyte h[KILLAC_HEADERSIZE];
 killaU_header(h);
 DumpBlock(h,KILLAC_HEADERSIZE,D);
}

/*
** dump Killa function as precompiled chunk
*/
int killaU_dump (killa_State* L, const killa_Proto* f, killa_Writer w, void* data, int strip)
{
 DumpState D;
 D.L=L;
 D.writer=w;
 D.data=data;
 D.strip=strip;
 D.status=0;
 DumpHeader(&D);
 DumpFunction(f,&D);
 return D.status;
}
