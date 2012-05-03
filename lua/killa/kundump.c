/* ========================================================================== */
/*   Load precompiled Killa scripts                                           */
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

#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "kmem.h"
#include "kobject.h"
#include "kstring.h"
#include "kundump.h"
#include "kzio.h"

typedef struct {
 killa_State* L;
 killa_ZIO* Z;
 killa_Mbuffer* b;
 const char* name;
} LoadState;

static void error(LoadState* S, const char* why)
{
 killaO_pushfstring(S->L,"%s: %s precompiled chunk",S->name,why);
 killaD_throw(S->L,KILLA_ERRSYNTAX);
}

#define LoadMem(S,b,n,size)	LoadBlock(S,b,(n)*(size))
#define LoadByte(S)		(killa_ubyte)LoadChar(S)
#define LoadVar(S,x)		LoadMem(S,&x,1,sizeof(x))
#define LoadVector(S,b,n,size)	LoadMem(S,b,n,size)

#if !defined(killai_verifycode)
#define killai_verifycode(L,b,f)	(f)
#endif

static void LoadBlock(LoadState* S, void* b, size_t size)
{
 if (killaZ_read(S->Z,b,size)!=0) error(S,"truncated");
}

static int LoadChar(LoadState* S)
{
 char x;
 LoadVar(S,x);
 return x;
}

static int LoadInt(LoadState* S)
{
 int x;
 LoadVar(S,x);
 if (x<0) error(S,"corrupted");
 return x;
}

static killa_Number LoadNumber(LoadState* S)
{
 killa_Number x;
 LoadVar(S,x);
 return x;
}

static killa_TString* LoadString(LoadState* S)
{
 size_t size;
 LoadVar(S,size);
 if (size==0)
  return NULL;
 else
 {
  char* s=killaZ_openspace(S->L,S->b,size);
  LoadBlock(S,s,size*sizeof(char));
  return killaS_newlstr(S->L,s,size-1);		/* remove trailing '\0' */
 }
}

static void LoadCode(LoadState* S, killa_Proto* f)
{
 int n=LoadInt(S);
 f->code=killaM_newvector(S->L,n,killa_Instruction);
 f->sizecode=n;
 LoadVector(S,f->code,n,sizeof(killa_Instruction));
}

static killa_Proto* LoadFunction(LoadState* S);

static void LoadConstants(LoadState* S, killa_Proto* f)
{
 int i,n;
 n=LoadInt(S);
 f->k=killaM_newvector(S->L,n,killa_TValue);
 f->sizek=n;
 for (i=0; i<n; i++) killa_setnilvalue(&f->k[i]);
 for (i=0; i<n; i++)
 {
  killa_TValue* o=&f->k[i];
  int t=LoadChar(S);
  switch (t)
  {
   case KILLA_TNULL:
	killa_setnilvalue(o);
	break;
   case KILLA_TBOOLEAN:
	killa_setbvalue(o,LoadChar(S));
	break;
   case KILLA_TNUMBER:
	killa_setnvalue(o,LoadNumber(S));
	break;
   case KILLA_TSTRING:
	killa_setsvalue2n(S->L,o,LoadString(S));
	break;
  }
 }
 n=LoadInt(S);
 f->p=killaM_newvector(S->L,n,killa_Proto*);
 f->sizep=n;
 for (i=0; i<n; i++) f->p[i]=NULL;
 for (i=0; i<n; i++) f->p[i]=LoadFunction(S);
}

static void LoadUpvalues(LoadState* S, killa_Proto* f)
{
 int i,n;
 n=LoadInt(S);
 f->upvalues=killaM_newvector(S->L,n,killa_Upvaldesc);
 f->sizeupvalues=n;
 for (i=0; i<n; i++) f->upvalues[i].name=NULL;
 for (i=0; i<n; i++)
 {
  f->upvalues[i].instack=LoadByte(S);
  f->upvalues[i].idx=LoadByte(S);
 }
}

static void LoadDebug(LoadState* S, killa_Proto* f)
{
 int i,n;
 f->source=LoadString(S);
 n=LoadInt(S);
 f->lineinfo=killaM_newvector(S->L,n,int);
 f->sizelineinfo=n;
 LoadVector(S,f->lineinfo,n,sizeof(int));
 n=LoadInt(S);
 f->locvars=killaM_newvector(S->L,n,killa_LocVar);
 f->sizelocvars=n;
 for (i=0; i<n; i++) f->locvars[i].varname=NULL;
 for (i=0; i<n; i++)
 {
  f->locvars[i].varname=LoadString(S);
  f->locvars[i].startpc=LoadInt(S);
  f->locvars[i].endpc=LoadInt(S);
 }
 n=LoadInt(S);
 for (i=0; i<n; i++) f->upvalues[i].name=LoadString(S);
}

static killa_Proto* LoadFunction(LoadState* S)
{
 killa_Proto* f=killaF_newproto(S->L);
 killa_setptvalue2s(S->L,S->L->top,f); killa_incr_top(S->L);
 f->linedefined=LoadInt(S);
 f->lastlinedefined=LoadInt(S);
 f->numparams=LoadByte(S);
 f->is_vararg=LoadByte(S);
 f->maxstacksize=LoadByte(S);
 LoadCode(S,f);
 LoadConstants(S,f);
 LoadUpvalues(S,f);
 LoadDebug(S,f);
 S->L->top--;
 return f;
}

/* the code below must be consistent with the code in killaU_header */
#define N0	KILLAC_HEADERSIZE
#define N1	(sizeof(KILLA_SIGNATURE) - sizeof(char))
#define N2	N1+2
#define N3	N2+6

static void LoadHeader(LoadState* S)
{
 killa_ubyte h[KILLAC_HEADERSIZE];
 killa_ubyte s[KILLAC_HEADERSIZE];
 killaU_header(h);
 memcpy(s,h,sizeof(char));			/* first char already read */
 LoadBlock(S,s+sizeof(char),KILLAC_HEADERSIZE-sizeof(char));
 if (memcmp(h,s,N0)==0) return;
 if (memcmp(h,s,N1)!=0) error(S,"not a");
 if (memcmp(h,s,N2)!=0) error(S,"version mismatch in");
 if (memcmp(h,s,N3)!=0) error(S,"incompatible"); else error(S,"corrupted");
}

/*
** load precompiled chunk
*/
killa_Proto* killaU_undump (killa_State* L, killa_ZIO* Z, killa_Mbuffer* buff, const char* name)
{
 LoadState S;
 if (*name=='@' || *name=='=')
  S.name=name+1;
 else if (*name == KILLA_SIGNATURE[0])
  S.name="binary string";
 else
  S.name=name;
 S.L=L;
 S.Z=Z;
 S.b=buff;
 LoadHeader(&S);
 return killai_verifycode(L,buff,LoadFunction(&S));
}

#define MYINT(s)	(s[0]-'0')
#define VERSION		MYINT(KILLA_VERSION_MAJOR)*16+MYINT(KILLA_VERSION_MINOR)
#define FORMAT		0		/* this is the official format */

/*
* make header for precompiled chunks
* if you change the code below be sure to update LoadHeader and FORMAT above
* and KILLAC_HEADERSIZE in lundump.h
*/
void killaU_header (killa_ubyte* h)
{
 int x=1;
 memcpy(h, KILLA_SIGNATURE, sizeof(KILLA_SIGNATURE)-sizeof(char));
 h += sizeof(KILLA_SIGNATURE)-sizeof(char);
 *h++=killa_cast_byte(VERSION);
 *h++=killa_cast_byte(FORMAT);
 *h++=killa_cast_byte(*(char*)&x);			/* endianness */
 *h++=killa_cast_byte(sizeof(int));
 *h++=killa_cast_byte(sizeof(size_t));
 *h++=killa_cast_byte(sizeof(killa_Instruction));
 *h++=killa_cast_byte(sizeof(killa_Number));
 *h++=killa_cast_byte(((killa_Number)0.5)==0);		/* is killa_Number integral? */
 memcpy(h,KILLAC_TAIL,sizeof(KILLAC_TAIL)-sizeof(char));
}
