/* ========================================================================== */
/*   Type definitions for Killa objects                                       */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KOBJECT_H_
#define KOBJECT_H_


#include <stdarg.h>


#include "klimits.h"
#include "killa.h"


/*
** Extra tags for non-values
*/
#define KILLA_TPROTO    KILLA_NUMTAGS
#define KILLA_TUPVAL    (KILLA_NUMTAGS+1)
#define KILLA_TDEADKEY  (KILLA_NUMTAGS+2)

/*
** number of all possible tags (including KILLA_TNONE but excluding DEADKEY)
*/
#define KILLA_TOTALTAGS	(KILLA_TUPVAL+2)


/*
** tags for Tagged Values have the following use of bits:
** bits 0-3: actual tag (a KILLA_T* value)
** bits 4-5: variant bits
** bit 6: whether value is collectable
*/

/*
** KILLA_TFUNCTION variants:
** 0 - Killa function
** 1 - light C function
** 2 - regular C function (closure)
*/

/* Variant tags for functions */
#define KILLA_TLCL  (KILLA_TFUNCTION | (0 << 4))  /* Killa closure */
#define KILLA_TLCF  (KILLA_TFUNCTION | (1 << 4))  /* light C function */
#define KILLA_TCCL  (KILLA_TFUNCTION | (2 << 4))  /* C closure */


/* Bit mark for collectable types */
#define KILLA_BIT_ISCOLLECTABLE	(1 << 6)

/* mark a tag as collectable */
#define killa_ctb(t)        ((t) | KILLA_BIT_ISCOLLECTABLE)


/*
** Union of all collectable objects
*/
typedef union killa_GCObject killa_GCObject;


/*
** Common Header for all collectable objects (in macro form, to be
** included in other objects)
*/
#define killa_CommonHeader	killa_GCObject *next; killa_ubyte tt; killa_ubyte marked


/*
** Common header in struct form
*/
typedef struct killa_GCheader {
  killa_CommonHeader;
} killa_GCheader;



/*
** Union of all Killa values
*/
typedef union killa_Value killa_Value;


#define killa_numfield  killa_Number n;    /* numbers */



/*
** Tagged Values. This is the basic representation of values in Killa,
** an actual value plus a tag with its type.
*/

#define killa_TValuefields  killa_Value value_; int tt_

typedef struct killa_TValue_ killa_TValue;


/* macro defining a nil value */
#define KILLA_NILCONSTANT	{NULL}, KILLA_TNULL


#define killa_val_(o)   ((o)->value_)
#define killa_num_(o)   (killa_val_(o).n)


/* raw type tag of a killa_TValue */
#define killa_rttype(o) ((o)->tt_)

/* type tag of a killa_TValue (bits 0-3 for tags + variant bits 4-5) */
#define killa_ttype(o)  (killa_rttype(o) & 0x3F)


/* type tag of a killa_TValue with no variants (bits 0-3) */
#define killa_ttypenv(o)    (killa_rttype(o) & 0x0F)


/* Macros to test type */
#define killa_checktag(o,t)         (killa_rttype(o) == (t))
#define killa_ttisnumber(o)         killa_checktag((o), KILLA_TNUMBER)
#define killa_ttisnil(o)            killa_checktag((o), KILLA_TNULL)
#define killa_ttisboolean(o)        killa_checktag((o), KILLA_TBOOLEAN)
#define killa_ttislightuserdata(o)	killa_checktag((o), KILLA_TLIGHTUSERDATA)
#define killa_ttisstring(o)         killa_checktag((o), killa_ctb(KILLA_TSTRING))
#define killa_ttistable(o)          killa_checktag((o), killa_ctb(KILLA_TTABLE))
#define killa_ttisfunction(o)       (killa_ttypenv(o) == KILLA_TFUNCTION)
#define killa_ttisclosure(o)        ((killa_rttype(o) & 0x1F) == KILLA_TFUNCTION)
#define killa_ttisCclosure(o)       killa_checktag((o), killa_ctb(KILLA_TCCL))
#define killa_ttisLclosure(o)       killa_checktag((o), killa_ctb(KILLA_TLCL))
#define killa_ttislcf(o)            killa_checktag((o), KILLA_TLCF)
#define killa_ttisuserdata(o)       killa_checktag((o), killa_ctb(KILLA_TUSERDATA))
#define killa_ttisthread(o)         killa_checktag((o), killa_ctb(KILLA_TTHREAD))
#define killa_ttisdeadkey(o)        killa_checktag((o), KILLA_TDEADKEY)

#define killa_ttisequal(o1,o2)      (killa_rttype(o1) == killa_rttype(o2))

/* Macros to access values */
#define killa_nvalue(o)     killa_check_exp(killa_ttisnumber(o), killa_num_(o))
#define killa_gcvalue(o)    killa_check_exp(killa_iscollectable(o), killa_val_(o).gc)
#define killa_pvalue(o)     killa_check_exp(killa_ttislightuserdata(o), killa_val_(o).p)
#define killa_rawtsvalue(o) killa_check_exp(killa_ttisstring(o), &killa_val_(o).gc->ts)
#define killa_tsvalue(o)    (&killa_rawtsvalue(o)->tsv)
#define killa_rawuvalue(o)  killa_check_exp(killa_ttisuserdata(o), &killa_val_(o).gc->u)
#define killa_uvalue(o)     (&killa_rawuvalue(o)->uv)
#define killa_clvalue(o)    killa_check_exp(killa_ttisclosure(o), &killa_val_(o).gc->cl)
#define killa_clLvalue(o)   killa_check_exp(killa_ttisLclosure(o), &killa_val_(o).gc->cl.l)
#define killa_clCvalue(o)   killa_check_exp(killa_ttisCclosure(o), &killa_val_(o).gc->cl.c)
#define killa_fvalue(o)     killa_check_exp(killa_ttislcf(o), killa_val_(o).f)
#define killa_hvalue(o)     killa_check_exp(killa_ttistable(o), &killa_val_(o).gc->h)
#define killa_bvalue(o)     killa_check_exp(killa_ttisboolean(o), killa_val_(o).b)
#define killa_thvalue(o)    killa_check_exp(killa_ttisthread(o), &killa_val_(o).gc->th)
/* a dead value may get the 'gc' field, but cannot access its contents */
#define killa_deadvalue(o)  killa_check_exp(killa_ttisdeadkey(o), killa_cast(void *, killa_val_(o).gc))

#define killa_isfalse(o)    (killa_ttisnil(o) || (killa_ttisboolean(o) && killa_bvalue(o) == 0))


#define killa_iscollectable(o)  (killa_rttype(o) & KILLA_BIT_ISCOLLECTABLE)


/* Macros for internal tests */
#define killa_righttt(obj)      (killa_ttypenv(obj) == killa_gcvalue(obj)->gch.tt)

#define killa_checkliveness(g,obj) \
    killa_longassert(!killa_iscollectable(obj) || \
	        (killa_righttt(obj) && !killa_isdead(g,killa_gcvalue(obj))))


/* Macros to set values */
#define killa_settt_(o,t)	((o)->tt_=(t))

#define killa_setnvalue(obj,x) \
    { killa_TValue *io=(obj); killa_num_(io)=(x); killa_settt_(io, KILLA_TNUMBER); }

#define killa_changenvalue(o,x)	killa_check_exp(killa_ttisnumber(o), killa_num_(o)=(x))

#define killa_setnilvalue(obj) killa_settt_(obj, KILLA_TNULL)

#define killa_setfvalue(obj,x) \
    { killa_TValue *io=(obj); killa_val_(io).f=(x); killa_settt_(io, KILLA_TLCF); }

#define killa_setpvalue(obj,x) \
    { killa_TValue *io=(obj); killa_val_(io).p=(x); killa_settt_(io, KILLA_TLIGHTUSERDATA); }

#define killa_setbvalue(obj,x) \
    { killa_TValue *io=(obj); killa_val_(io).b=(x); killa_settt_(io, KILLA_TBOOLEAN); }

#define killa_setgcovalue(L,obj,x) \
    { killa_TValue *io=(obj); killa_GCObject *i_g=(x); \
      killa_val_(io).gc=i_g; killa_settt_(io, killa_ctb(gch(i_g)->tt)); }

#define killa_setsvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TSTRING)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setuvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TUSERDATA)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setthvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TTHREAD)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setclLvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TLCL)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setclCvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TCCL)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_sethvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TTABLE)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setptvalue(L,obj,x) \
    { killa_TValue *io=(obj); \
      killa_val_(io).gc=killa_cast(killa_GCObject *, (x)); killa_settt_(io, killa_ctb(KILLA_TPROTO)); \
      killa_checkliveness(KILLA_G(L),io); }

#define killa_setdeadvalue(obj)	killa_settt_(obj, KILLA_TDEADKEY)



#define killa_setobj(L,obj1,obj2) \
    { const killa_TValue *io2=(obj2); killa_TValue *io1=(obj1); \
      io1->value_ = io2->value_; io1->tt_ = io2->tt_; \
      killa_checkliveness(KILLA_G(L),io1); }


/*
** different types of assignments, according to destination
*/

/* from stack to (same) stack */
#define killa_setobjs2s     killa_setobj
/* to stack (not from same stack) */
#define killa_setobj2s      killa_setobj
#define killa_setsvalue2s   killa_setsvalue
#define killa_sethvalue2s   killa_sethvalue
#define killa_setptvalue2s  killa_setptvalue
/* from table to same table */
#define killa_setobjt2t     killa_setobj
/* to table */
#define killa_setobj2t      killa_setobj
/* to new object */
#define killa_setobj2n      killa_setobj
#define killa_setsvalue2n   killa_setsvalue




/*
** {======================================================
** NaN Trick
** =======================================================
*/

#if defined(KILLA_NANTRICK) \
 || defined(KILLA_NANTRICK_LE) \
 || defined(KILLA_NANTRICK_BE)

/*
** numbers are represented in the 'd_' field. All other values have the
** value (KILLA_NNMARK | tag) in 'tt__'. A number with such pattern would be
** a "signaled NaN", which is never generated by regular operations by
** the CPU (nor by 'strtod')
*/
#if !defined(KILLA_NNMARK)
#define KILLA_NNMARK    0x7FF7A500
#define KILLA_NNMASK    0x7FFFFF00
#endif

#undef killa_TValuefields
#undef KILLA_NILCONSTANT

#if defined(KILLA_NANTRICK_LE)

/* little endian */
#define killa_TValuefields  \
	union { struct { killa_Value v__; int tt__; } i; double d__; } u
#define KILLA_NILCONSTANT	{{{NULL}, killa_tag2tt(KILLA_TNULL)}}
/* field-access macros */
#define v_(o)		((o)->u.i.v__)
#define d_(o)		((o)->u.d__)
#define tt_(o)		((o)->u.i.tt__)

#elif defined(KILLA_NANTRICK_BE)

/* big endian */
#define killa_TValuefields  \
	union { struct { int tt__; killa_Value v__; } i; double d__; } u
#define KILLA_NILCONSTANT	{{killa_tag2tt(KILLA_TNULL), {NULL}}}
/* field-access macros */
#define v_(o)		((o)->u.i.v__)
#define d_(o)		((o)->u.d__)
#define tt_(o)		((o)->u.i.tt__)

#elif !defined(killa_TValuefields)
#error option 'KILLA_NANTRICK' needs declaration for 'killa_TValuefields'

#endif


/* correspondence with standard representation */
#undef killa_val_
#define killa_val_(o)		v_(o)
#undef killa_num_
#define killa_num_(o)		d_(o)


#undef killa_numfield
#define killa_numfield	/* no such field; numbers are the entire struct */

/* basic check to distinguish numbers from non-numbers */
#undef killa_ttisnumber
#define killa_ttisnumber(o)	((tt_(o) & KILLA_NNMASK) != KILLA_NNMARK)

#define killa_tag2tt(t)	(KILLA_NNMARK | (t))

#undef killa_rttype
#define killa_rttype(o)	(killa_ttisnumber(o) ? KILLA_TNUMBER : tt_(o) & 0xff)

#undef killa_settt_
#define killa_settt_(o,t)	(tt_(o) = killa_tag2tt(t))

#undef killa_setnvalue
#define killa_setnvalue(obj,x) \
    { killa_TValue *io_=(obj); killa_num_(io_)=(x); killa_assert(killa_ttisnumber(io_)); }

#undef killa_setobj
#define killa_setobj(L,obj1,obj2) \
    { const killa_TValue *o2_=(obj2); killa_TValue *o1_=(obj1); \
	  o1_->u = o2_->u; \
	  killa_checkliveness(KILLA_G(L),o1_); }


/*
** these redefinitions are not mandatory, but these forms are more efficient
*/

#undef killa_checktag
#define killa_checktag(o,t)	(tt_(o) == killa_tag2tt(t))

#undef killa_ttisequal
#define killa_ttisequal(o1,o2)  \
    (killa_ttisnumber(o1) ? killa_ttisnumber(o2) : (tt_(o1) == tt_(o2)))



#define killai_checknum(L,o,c)	{ if (!killa_ttisnumber(o)) c; }


#else

#define killai_checknum(L,o,c)	{ /* empty */ }

#endif
/* }====================================================== */



/*
** {======================================================
** types and prototypes
** =======================================================
*/


union killa_Value {
  killa_GCObject *gc;    /* collectable objects */
  void *p;         /* light userdata */
  int b;           /* booleans */
  killa_CFunction f; /* light C functions */
  killa_numfield         /* numbers */
};


struct killa_TValue_ {
  killa_TValuefields;
};


typedef killa_TValue *killa_StkId;  /* index to stack elements */




/*
** Header for string value; string bytes follow the end of this structure
*/
typedef union killa_TString {
  killa_Umaxalign dummy;  /* ensures maximum alignment for strings */
  struct {
    killa_CommonHeader;
    killa_ubyte reserved;
    unsigned int hash;
    size_t len;  /* number of characters in string */
  } tsv;
} killa_TString;


/* get the actual string (array of bytes) from a killa_TString */
#define killa_getstr(ts)    killa_cast(const char *, (ts) + 1)

/* get the actual string (array of bytes) from a Killa value */
#define killa_svalue(o)     killa_getstr(killa_rawtsvalue(o))


/*
** Header for userdata; memory area follows the end of this structure
*/
typedef union killa_Udata {
  killa_Umaxalign dummy;  /* ensures maximum alignment for `local' udata */
  struct {
    killa_CommonHeader;
    struct killa_Table *metatable;
    struct killa_Table *env;
    size_t len;  /* number of bytes */
  } uv;
} killa_Udata;



/*
** Description of an upvalue for function prototypes
*/
typedef struct killa_Upvaldesc {
  killa_TString *name;  /* upvalue name (for debug information) */
  killa_ubyte instack;  /* whether it is in stack */
  killa_ubyte idx;  /* index of upvalue (in stack or in outer function's list) */
} killa_Upvaldesc;


/*
** Description of a local variable for function prototypes
** (used for debug information)
*/
typedef struct killa_LocVar {
  killa_TString *varname;
  int startpc;  /* first point where variable is active */
  int endpc;    /* first point where variable is dead */
} killa_LocVar;


/*
** Function Prototypes
*/
typedef struct killa_Proto {
  killa_CommonHeader;
  killa_TValue *k;  /* constants used by the function */
  killa_Instruction *code;
  struct killa_Proto **p;  /* functions defined inside the function */
  int *lineinfo;  /* map from opcodes to source lines (debug information) */
  killa_LocVar *locvars;  /* information about local variables (debug information) */
  killa_Upvaldesc *upvalues;  /* upvalue information */
  union killa_Closure *cache;  /* last created closure with this prototype */
  killa_TString  *source;  /* used for debug information */
  int sizeupvalues;  /* size of 'upvalues' */
  int sizek;  /* size of `k' */
  int sizecode;
  int sizelineinfo;
  int sizep;  /* size of `p' */
  int sizelocvars;
  int linedefined;
  int lastlinedefined;
  killa_GCObject *gclist;
  killa_ubyte numparams;  /* number of fixed parameters */
  killa_ubyte is_vararg;
  killa_ubyte maxstacksize;  /* maximum stack used by this function */
} killa_Proto;



/*
** Killa Upvalues
*/
typedef struct killa_UpVal {
  killa_CommonHeader;
  killa_TValue *v;  /* points to stack or to its own value */
  union {
    killa_TValue value;  /* the value (when closed) */
    struct {  /* double linked list (when open) */
      struct killa_UpVal *prev;
      struct killa_UpVal *next;
    } l;
  } u;
} killa_UpVal;


/*
** Closures
*/

#define killa_ClosureHeader \
	killa_CommonHeader; killa_ubyte isC; killa_ubyte nupvalues; killa_GCObject *gclist

typedef struct killa_CClosure {
  killa_ClosureHeader;
  killa_CFunction f;
  killa_TValue upvalue[1];  /* list of upvalues */
} killa_CClosure;


typedef struct killa_LClosure {
  killa_ClosureHeader;
  struct killa_Proto *p;
  killa_UpVal *upvals[1];  /* list of upvalues */
} killa_LClosure;


typedef union killa_Closure {
  killa_CClosure c;
  killa_LClosure l;
} killa_Closure;


#define killa_isLfunction(o)    killa_ttisLclosure(o)

#define killa_getproto(o)       (killa_clLvalue(o)->p)


/*
** Tables
*/

typedef union killa_TKey {
  struct {
    killa_TValuefields;
    struct killa_Node *next;  /* for chaining */
  } nk;
  killa_TValue tvk;
} killa_TKey;


typedef struct killa_Node {
  killa_TValue i_val;
  killa_TKey i_key;
} killa_Node;


typedef struct killa_Table {
  killa_CommonHeader;
  killa_ubyte flags;  /* 1<<p means tagmethod(p) is not present */
  killa_ubyte lsizenode;  /* log2 of size of `node' array */
  struct killa_Table *metatable;
  killa_TValue *array;  /* array part */
  killa_Node *node;
  killa_Node *lastfree;  /* any free position is before this position */
  killa_GCObject *gclist;
  int sizearray;  /* size of `array' array */
} killa_Table;



/*
** `module' operation for hashing (size is always a power of 2)
*/
#define killa_lmod(s,size) \
    (killa_check_exp((size&(size-1))==0, (killa_cast(int, (s) & ((size)-1)))))


#define killa_twoto(x)      (1<<(x))
#define killa_sizenode(t)   (killa_twoto((t)->lsizenode))


/*
** (address of) a fixed nil value
*/
#define killaO_nilobject    (&killaO_nilobject_)


KILLAI_DDEC const killa_TValue killaO_nilobject_;


KILLAI_FUNC int killaO_int2fb (unsigned int x);
KILLAI_FUNC int killaO_fb2int (int x);
KILLAI_FUNC int killaO_ceillog2 (unsigned int x);
KILLAI_FUNC killa_Number killaO_arith (int op, killa_Number v1, killa_Number v2);
KILLAI_FUNC int killaO_str2d (const char *s, size_t len, killa_Number *result);
KILLAI_FUNC int killaO_hexavalue (int c);
KILLAI_FUNC const char *killaO_pushvfstring (killa_State *L, const char *fmt,
                                             va_list argp);
KILLAI_FUNC const char *killaO_pushfstring (killa_State *L, const char *fmt, ...);
KILLAI_FUNC void killaO_chunkid (char *out, const char *source, size_t len);


#endif

