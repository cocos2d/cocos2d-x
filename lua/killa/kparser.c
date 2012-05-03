/* ========================================================================== */
/*   Killa Parser                                                             */
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

#include "kcode.h"
#include "kdebug.h"
#include "kdo.h"
#include "kfunc.h"
#include "klex.h"
#include "kmem.h"
#include "kobject.h"
#include "kopcodes.h"
#include "kparser.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"


/* Define 'this' symbol */
#define TK_THIS     "this"


/* maximum number of local variables per function (must be smaller
   than 250, due to the bytecode format) */
#define MAXVARS		200


#define hasmultret(k)		((k) == VCALL || (k) == VVARARG)



/*
** nodes for block list (list of active blocks)
*/
typedef struct killa_BlockCnt {
  struct killa_BlockCnt *previous;  /* chain */
  short firstlabel;  /* index of first label in this block */
  short firstgoto;  /* index of first pending goto in this block */
  killa_ubyte nactvar;  /* # active locals outside the block */
  killa_ubyte upval;  /* true if some variable in the block is an upvalue */
  killa_ubyte isloop;  /* true if `block' is a loop */
} killa_BlockCnt;



/*
** prototypes for recursive non-terminal functions
*/
static void statement (killa_LexState *ls);
static void expr (killa_LexState *ls, killa_expdesc *v);


static void anchor_token (killa_LexState *ls) {
  /* last token from outer function must be EOS */
  killa_assert(ls->fs != NULL || ls->t.token == TK_EOS);
  if (ls->t.token == TK_NAME || ls->t.token == TK_STRING) {
    killa_TString *ts = ls->t.seminfo.ts;
    killaX_newstring(ls, killa_getstr(ts), ts->tsv.len);
  }
}


/* semantic error */
static killa_noret semerror (killa_LexState *ls, const char *msg) {
  ls->t.token = 0;  /* remove 'near to' from final message */
  killaX_syntaxerror(ls, msg);
}


static killa_noret error_expected (killa_LexState *ls, int token) {
  killaX_syntaxerror(ls,
      killaO_pushfstring(ls->L, "%s expected", killaX_token2str(ls, token)));
}


static killa_noret errorlimit (killa_FuncState *fs, int limit, const char *what) {
  killa_State *L = fs->ls->L;
  const char *msg;
  int line = fs->f->linedefined;
  const char *where = (line == 0)
                      ? "main function"
                      : killaO_pushfstring(L, "function at line %d", line);
  msg = killaO_pushfstring(L, "too many %s (limit is %d) in %s",
                             what, limit, where);
  killaX_syntaxerror(fs->ls, msg);
}


static void checklimit (killa_FuncState *fs, int v, int l, const char *what) {
  if (v > l) errorlimit(fs, l, what);
}


static int testnext (killa_LexState *ls, int c) {
  if (ls->t.token == c) {
    killaX_next(ls);
    return 1;
  }
  else return 0;
}


static void check (killa_LexState *ls, int c) {
  if (ls->t.token != c)
    error_expected(ls, c);
}


static void checknext (killa_LexState *ls, int c) {
  check(ls, c);
  killaX_next(ls);
}


#define check_condition(ls,c,msg)	{ if (!(c)) killaX_syntaxerror(ls, msg); }



static void check_match (killa_LexState *ls, int what, int who, int where) {
  if (!testnext(ls, what)) {
    if (where == ls->linenumber)
      error_expected(ls, what);
    else {
      killaX_syntaxerror(ls, killaO_pushfstring(ls->L,
             "%s expected (to close %s at line %d)",
              killaX_token2str(ls, what), killaX_token2str(ls, who), where));
    }
  }
}


static killa_TString *str_checkname (killa_LexState *ls) {
  killa_TString *ts;
  check(ls, TK_NAME);
  ts = ls->t.seminfo.ts;
  killaX_next(ls);
  return ts;
}


static void init_exp (killa_expdesc *e, killa_expkind k, int i) {
  e->f = e->t = KILLA_NO_JUMP;
  e->k = k;
  e->u.info = i;
}


static void codestring (killa_LexState *ls, killa_expdesc *e, killa_TString *s) {
  init_exp(e, VK, killaK_stringK(ls->fs, s));
}


static void checkname (killa_LexState *ls, killa_expdesc *e) {
  codestring(ls, e, str_checkname(ls));
}


static int registerlocalvar (killa_LexState *ls, killa_TString *varname) {
  killa_FuncState *fs = ls->fs;
  killa_Proto *f = fs->f;
  int oldsize = f->sizelocvars;
  killaM_growvector(ls->L, f->locvars, fs->nlocvars, f->sizelocvars,
                  killa_LocVar, SHRT_MAX, "local variables");
  while (oldsize < f->sizelocvars) f->locvars[oldsize++].varname = NULL;
  f->locvars[fs->nlocvars].varname = varname;
  killaC_objbarrier(ls->L, f, varname);
  return fs->nlocvars++;
}


static void new_localvar (killa_LexState *ls, killa_TString *name) {
  killa_FuncState *fs = ls->fs;
  killa_Dyndata *dyd = ls->dyd;
  int reg = registerlocalvar(ls, name);
  checklimit(fs, dyd->actvar.n + 1 - fs->firstlocal,
                  MAXVARS, "local variables");
  killaM_growvector(ls->L, dyd->actvar.arr, dyd->actvar.n + 1,
                  dyd->actvar.size, killa_Vardesc, KILLA_MAX_INT, "local variables");
  dyd->actvar.arr[dyd->actvar.n++].idx = killa_cast(short, reg);
}


static void new_localvarliteral_ (killa_LexState *ls, const char *name, size_t sz) {
  new_localvar(ls, killaX_newstring(ls, name, sz));
}

#define new_localvarliteral(ls,v) \
	new_localvarliteral_(ls, "" v, (sizeof(v)/sizeof(char))-1)


static killa_LocVar *getlocvar (killa_FuncState *fs, int i) {
  int idx = fs->ls->dyd->actvar.arr[fs->firstlocal + i].idx;
  killa_assert(idx < fs->nlocvars);
  return &fs->f->locvars[idx];
}


static void adjustlocalvars (killa_LexState *ls, int nvars) {
  killa_FuncState *fs = ls->fs;
  fs->nactvar = killa_cast_byte(fs->nactvar + nvars);
  for (; nvars; nvars--) {
    getlocvar(fs, fs->nactvar - nvars)->startpc = fs->pc;
  }
}


static void removevars (killa_FuncState *fs, int tolevel) {
  fs->ls->dyd->actvar.n -= (fs->nactvar - tolevel);
  while (fs->nactvar > tolevel)
    getlocvar(fs, --fs->nactvar)->endpc = fs->pc;
}


static int searchupvalue (killa_FuncState *fs, killa_TString *name) {
  int i;
  killa_Upvaldesc *up = fs->f->upvalues;
  for (i = 0; i < fs->nups; i++) {
    if (killa_eqstr(up[i].name, name)) return i;
  }
  return -1;  /* not found */
}


static int newupvalue (killa_FuncState *fs, killa_TString *name, killa_expdesc *v) {
  killa_Proto *f = fs->f;
  int oldsize = f->sizeupvalues;
  checklimit(fs, fs->nups + 1, KILLA_MAXUPVAL, "upvalues");
  killaM_growvector(fs->ls->L, f->upvalues, fs->nups, f->sizeupvalues,
                  killa_Upvaldesc, KILLA_MAXUPVAL, "upvalues");
  while (oldsize < f->sizeupvalues) f->upvalues[oldsize++].name = NULL;
  f->upvalues[fs->nups].instack = (v->k == VLOCAL);
  f->upvalues[fs->nups].idx = killa_cast_byte(v->u.info);
  f->upvalues[fs->nups].name = name;
  killaC_objbarrier(fs->ls->L, f, name);
  return fs->nups++;
}


static int searchvar (killa_FuncState *fs, killa_TString *n) {
  int i;
  for (i=fs->nactvar-1; i >= 0; i--) {
    if (killa_eqstr(n, getlocvar(fs, i)->varname))
      return i;
  }
  return -1;  /* not found */
}


/*
  Mark block where variable at given level was defined
  (to emit close instructions later).
*/
static void markupval (killa_FuncState *fs, int level) {
  killa_BlockCnt *bl = fs->bl;
  while (bl->nactvar > level) bl = bl->previous;
  bl->upval = 1;
}


/*
  Find variable with given name 'n'. If it is an upvalue, add this
  upvalue into all intermediate functions.
*/
static int singlevaraux (killa_FuncState *fs, killa_TString *n, killa_expdesc *var, int base) {
  if (fs == NULL)  /* no more levels? */
    return VVOID;  /* default is global */
  else {
    int v = searchvar(fs, n);  /* look up locals at current level */
    if (v >= 0) {  /* found? */
      init_exp(var, VLOCAL, v);  /* variable is local */
      if (!base)
        markupval(fs, v);  /* local will be used as an upval */
      return VLOCAL;
    }
    else {  /* not found as local at current level; try upvalues */
      int idx = searchupvalue(fs, n);  /* try existing upvalues */
      if (idx < 0) {  /* not found? */
        if (singlevaraux(fs->prev, n, var, 0) == VVOID) /* try upper levels */
          return VVOID;  /* not found; is a global */
        /* else was LOCAL or UPVAL */
        idx  = newupvalue(fs, n, var);  /* will be a new upvalue */
      }
      init_exp(var, VUPVAL, idx);
      return VUPVAL;
    }
  }
}


static const char *singlevar (killa_LexState *ls, killa_expdesc *var, int isglobal) {
  killa_TString *varname = str_checkname(ls);
  killa_FuncState *fs = ls->fs;
  if (isglobal || (singlevaraux(fs, varname, var, 1) == VVOID)) {  /* global name? */
    killa_expdesc key;
    singlevaraux(fs, ls->envn, var, 1);  /* get environment variable */
    killa_assert(var->k == VLOCAL || var->k == VUPVAL);
    codestring(ls, &key, varname);  /* key is variable name */
    killaK_indexed(fs, var, &key);  /* env[varname] */

    /* if this symbol was not marked as global return the name for 
       possible error message */ 
    if (!isglobal) {
      return killa_getstr(varname);
    }
  }
  return NULL;
}


static void adjust_assign (killa_LexState *ls, int nvars, int nexps, killa_expdesc *e) {
  killa_FuncState *fs = ls->fs;
  int extra = nvars - nexps;
  if (hasmultret(e->k)) {
    extra++;  /* includes call itself */
    if (extra < 0) extra = 0;
    killaK_setreturns(fs, e, extra);  /* last exp. provides the difference */
    if (extra > 1) killaK_reserveregs(fs, extra-1);
  }
  else {
    if (e->k != VVOID) killaK_exp2nextreg(fs, e);  /* close last expression */
    if (extra > 0) {
      int reg = fs->freereg;
      killaK_reserveregs(fs, extra);
      killaK_nil(fs, reg, extra);
    }
  }
}


static void enterlevel (killa_LexState *ls) {
  killa_State *L = ls->L;
  ++L->nCcalls;
  checklimit(ls->fs, L->nCcalls, KILLAI_MAXCCALLS, "C levels");
}


#define leavelevel(ls)	((ls)->L->nCcalls--)


static void closegoto (killa_LexState *ls, int g, killa_Labeldesc *label) {
  int i;
  killa_FuncState *fs = ls->fs;
  killa_Labellist *gl = &ls->dyd->gt;
  killa_Labeldesc *gt = &gl->arr[g];
  killa_assert(killa_eqstr(gt->name, label->name));
  if (gt->nactvar < label->nactvar) {
    killa_TString *vname = getlocvar(fs, gt->nactvar)->varname;
    const char *msg = killaO_pushfstring(ls->L,
      "<goto %s> at line %d jumps into the scope of local " KILLA_QS,
      killa_getstr(gt->name), gt->line, killa_getstr(vname));
    semerror(ls, msg);
  }
  killaK_patchlist(fs, gt->pc, label->pc);
  /* remove goto from pending list */
  for (i = g; i < gl->n - 1; i++)
    gl->arr[i] = gl->arr[i + 1];
  gl->n--;
}


/*
** try to close a goto with existing labels; this solves backward jumps
*/
static int findlabel (killa_LexState *ls, int g) {
  int i;
  killa_BlockCnt *bl = ls->fs->bl;
  killa_Dyndata *dyd = ls->dyd;
  killa_Labeldesc *gt = &dyd->gt.arr[g];
  /* check labels in current block for a match */
  for (i = bl->firstlabel; i < dyd->label.n; i++) {
    killa_Labeldesc *lb = &dyd->label.arr[i];
    if (killa_eqstr(lb->name, gt->name)) {  /* correct label? */
      if (gt->nactvar > lb->nactvar &&
          (bl->upval || dyd->label.n > bl->firstlabel))
        killaK_patchclose(ls->fs, gt->pc, lb->nactvar);
      closegoto(ls, g, lb);  /* close it */
      return 1;
    }
  }
  return 0;  /* label not found; cannot close goto */
}


static int newlabelentry (killa_LexState *ls, killa_Labellist *l, killa_TString *name,
                          int line, int pc) {
  int n = l->n;
  killaM_growvector(ls->L, l->arr, n, l->size,
                  killa_Labeldesc, SHRT_MAX, "labels/gotos");
  l->arr[n].name = name;
  l->arr[n].line = line;
  l->arr[n].nactvar = ls->fs->nactvar;
  l->arr[n].pc = pc;
  l->n++;
  return n;
}


/*
** check whether new label 'lb' matches any pending gotos in current
** block; solves forward jumps
*/
static void findgotos (killa_LexState *ls, killa_Labeldesc *lb) {
  killa_Labellist *gl = &ls->dyd->gt;
  int i = ls->fs->bl->firstgoto;
  while (i < gl->n) {
    if (killa_eqstr(gl->arr[i].name, lb->name))
      closegoto(ls, i, lb);
    else
      i++;
  }
}


/*
** "export" pending gotos to outer level, to check them against
** outer labels; if the block being exited has upvalues, and
** the goto exits the scope of any variable (which can be the
** upvalue), close those variables being exited.
*/
static void movegotosout (killa_FuncState *fs, killa_BlockCnt *bl) {
  int i = bl->firstgoto;
  killa_Labellist *gl = &fs->ls->dyd->gt;
  /* correct pending gotos to current block and try to close it
     with visible labels */
  while (i < gl->n) {
    killa_Labeldesc *gt = &gl->arr[i];
    if (gt->nactvar > bl->nactvar) {
      if (bl->upval)
        killaK_patchclose(fs, gt->pc, bl->nactvar);
      gt->nactvar = bl->nactvar;
    }
    if (!findlabel(fs->ls, i))
      i++;  /* move to next one */
  }
}


static void enterblock (killa_FuncState *fs, killa_BlockCnt *bl, killa_ubyte isloop) {
  bl->isloop = isloop;
  bl->nactvar = fs->nactvar;
  bl->firstlabel = fs->ls->dyd->label.n;
  bl->firstgoto = fs->ls->dyd->gt.n;
  bl->upval = 0;
  bl->previous = fs->bl;
  fs->bl = bl;
  killa_assert(fs->freereg == fs->nactvar);
}


/*
** create a label named "break" to resolve break statements
*/
static void breaklabel (killa_LexState *ls) {
  killa_TString *n = killaS_new(ls->L, "break");
  int l = newlabelentry(ls, &ls->dyd->label, n, 0, ls->fs->pc);
  findgotos(ls, &ls->dyd->label.arr[l]);
}

/*
** generates an error for an undefined 'goto'; choose appropriate
** message when label name is a reserved word (which can only be 'break')
*/
static killa_noret undefgoto (killa_LexState *ls, killa_Labeldesc *gt) {
  const char *msg = (gt->name->tsv.reserved > 0)
                    ? "<%s> at line %d not inside a loop"
                    : "no visible label " KILLA_QS " for <goto> at line %d";
  msg = killaO_pushfstring(ls->L, msg, killa_getstr(gt->name), gt->line);
  semerror(ls, msg);
}


static void leaveblock (killa_FuncState *fs) {
  killa_BlockCnt *bl = fs->bl;
  killa_LexState *ls = fs->ls;
  if (bl->previous && bl->upval) {
    /* create a 'jump to here' to close upvalues */
    int j = killaK_jump(fs);
    killaK_patchclose(fs, j, bl->nactvar);
    killaK_patchtohere(fs, j);
  }
  if (bl->isloop)
    breaklabel(ls);  /* close pending breaks */
  fs->bl = bl->previous;
  removevars(fs, bl->nactvar);
  killa_assert(bl->nactvar == fs->nactvar);
  fs->freereg = fs->nactvar;  /* free registers */
  ls->dyd->label.n = bl->firstlabel;  /* remove local labels */
  if (bl->previous)  /* inner block? */
    movegotosout(fs, bl);  /* update pending gotos to outer block */
  else if (bl->firstgoto < ls->dyd->gt.n)  /* pending gotos in outer block? */
    undefgoto(ls, &ls->dyd->gt.arr[bl->firstgoto]);  /* error */
}


/*
** adds prototype being created into its parent list of prototypes
** and codes instruction to create new closure
*/
static void codeclosure (killa_LexState *ls, killa_Proto *clp, killa_expdesc *v) {
  killa_FuncState *fs = ls->fs->prev;
  killa_Proto *f = fs->f;  /* prototype of function creating new closure */
  if (fs->np >= f->sizep) {
    int oldsize = f->sizep;
    killaM_growvector(ls->L, f->p, fs->np, f->sizep, killa_Proto *,
                    KILLA_MAXARG_Bx, "functions");
    while (oldsize < f->sizep) f->p[oldsize++] = NULL;
  }
  f->p[fs->np++] = clp;
  killaC_objbarrier(ls->L, f, clp);
  init_exp(v, VRELOCABLE, killaK_codeABx(fs, OP_CLOSURE, 0, fs->np-1));
  killaK_exp2nextreg(fs, v);  /* fix it at stack top (for GC) */
}


static void open_func (killa_LexState *ls, killa_FuncState *fs, killa_BlockCnt *bl) {
  killa_State *L = ls->L;
  killa_Proto *f;
  fs->prev = ls->fs;  /* linked list of funcstates */
  fs->ls = ls;
  ls->fs = fs;
  fs->pc = 0;
  fs->lasttarget = 0;
  fs->jpc = KILLA_NO_JUMP;
  fs->freereg = 0;
  fs->nk = 0;
  fs->np = 0;
  fs->nups = 0;
  fs->nlocvars = 0;
  fs->nactvar = 0;
  fs->firstlocal = ls->dyd->actvar.n;
  fs->bl = NULL;
  f = killaF_newproto(L);
  fs->f = f;
  f->source = ls->source;
  f->maxstacksize = 2;  /* registers 0/1 are always valid */
  /* anchor prototype (to avoid being collected) */
  killa_setptvalue2s(L, L->top, f);
  killa_incr_top(L);
  fs->h = killaH_new(L);
  /* anchor table of constants (to avoid being collected) */
  killa_sethvalue2s(L, L->top, fs->h);
  killa_incr_top(L);
  enterblock(fs, bl, 0);
}


static void close_func (killa_LexState *ls) {
  killa_State *L = ls->L;
  killa_FuncState *fs = ls->fs;
  killa_Proto *f = fs->f;
  killaK_ret(fs, 0, 0);  /* final return */
  leaveblock(fs);
  killaM_reallocvector(L, f->code, f->sizecode, fs->pc, killa_Instruction);
  f->sizecode = fs->pc;
  killaM_reallocvector(L, f->lineinfo, f->sizelineinfo, fs->pc, int);
  f->sizelineinfo = fs->pc;
  killaM_reallocvector(L, f->k, f->sizek, fs->nk, killa_TValue);
  f->sizek = fs->nk;
  killaM_reallocvector(L, f->p, f->sizep, fs->np, killa_Proto *);
  f->sizep = fs->np;
  killaM_reallocvector(L, f->locvars, f->sizelocvars, fs->nlocvars, killa_LocVar);
  f->sizelocvars = fs->nlocvars;
  killaM_reallocvector(L, f->upvalues, f->sizeupvalues, fs->nups, killa_Upvaldesc);
  f->sizeupvalues = fs->nups;
  killa_assert(fs->bl == NULL);
  ls->fs = fs->prev;
  /* last token read was anchored in defunct function; must re-anchor it */
  anchor_token(ls);
  L->top--;  /* pop table of constants */
  killaC_checkGC(L);
  L->top--;  /* pop prototype (after possible collection) */
}


/*
** opens the main function, which is a regular vararg function with an
** upvalue named KILLA_ENV
*/
static void open_mainfunc (killa_LexState *ls, killa_FuncState *fs, killa_BlockCnt *bl) {
  killa_expdesc v;
  open_func(ls, fs, bl);
  fs->f->is_vararg = 1;  /* main function is always vararg */
  init_exp(&v, VLOCAL, 0);
  newupvalue(fs, ls->envn, &v);  /* create environment upvalue */
}



/*============================================================*/
/* GRAMMAR RULES */
/*============================================================*/


/*
** check whether current token is in the follow set of a block.
*/
static int block_follow (killa_LexState *ls) {
  switch (ls->t.token) {
    case '}':
    case TK_EOS:
      return 1;
    default: return 0;
  }
}


static void statlist (killa_LexState *ls) {
  /* statlist -> { stat [`;'] } */
  while (!block_follow(ls)) {
    if (ls->t.token == TK_RETURN) {
      statement(ls);
      return;  /* 'return' must be last statement */
    }
    statement(ls);
  }
}


static void fieldsel (killa_LexState *ls, killa_expdesc *v) {
  /* fieldsel -> ['.' | '::'] NAME */
  killa_FuncState *fs = ls->fs;
  killa_expdesc key;
  killaK_exp2anyregup(fs, v);
  killaX_next(ls);  /* skip the dot or colon */
  checkname(ls, &key);
  killaK_indexed(fs, v, &key);
}


static void yindex (killa_LexState *ls, killa_expdesc *v) {
  /* index -> '[' expr ']' */
  killaX_next(ls);  /* skip the '[' */
  expr(ls, v);
  killaK_exp2val(ls->fs, v);
  checknext(ls, ']');
}


/*
** {======================================================================
** Rules for Constructors
** =======================================================================
*/


struct ConsControl {
  killa_expdesc v;  /* last list item read */
  killa_expdesc *t;  /* table descriptor */
  int nh;  /* total number of `record' elements */
  int na;  /* total number of array elements */
  int tostore;  /* number of array elements pending to be stored */
};


static void recfield (killa_LexState *ls, struct ConsControl *cc) {
  /* recfield -> (NAME | '['exp1 ']') ':' exp1 */
  killa_FuncState *fs = ls->fs;
  int reg = ls->fs->freereg;
  killa_expdesc key, val;
  int rkkey;
  if (ls->t.token == TK_NAME) {
    checklimit(fs, cc->nh, KILLA_MAX_INT, "items in a constructor");
    checkname(ls, &key);
  }
  else  /* ls->t.token == '[' */
    yindex(ls, &key);
  cc->nh++;
  checknext(ls, ':');
  rkkey = killaK_exp2RK(fs, &key);
  expr(ls, &val);
  killaK_codeABC(fs, OP_SETTABLE, cc->t->u.info, rkkey, killaK_exp2RK(fs, &val));
  fs->freereg = reg;  /* free registers */
}


static void closelistfield (killa_FuncState *fs, struct ConsControl *cc) {
  if (cc->v.k == VVOID) return;  /* there is no list item */
  killaK_exp2nextreg(fs, &cc->v);
  cc->v.k = VVOID;
  if (cc->tostore == KILLA_LFIELDS_PER_FLUSH) {
    killaK_setlist(fs, cc->t->u.info, cc->na, cc->tostore);  /* flush */
    cc->tostore = 0;  /* no more items pending */
  }
}


static void lastlistfield (killa_FuncState *fs, struct ConsControl *cc) {
  if (cc->tostore == 0) return;
  if (hasmultret(cc->v.k)) {
    killaK_setmultret(fs, &cc->v);
    killaK_setlist(fs, cc->t->u.info, cc->na, KILLA_MULTRET);
    cc->na--;  /* do not count last expression (unknown number of elements) */
  }
  else {
    if (cc->v.k != VVOID)
      killaK_exp2nextreg(fs, &cc->v);
    killaK_setlist(fs, cc->t->u.info, cc->na, cc->tostore);
  }
}


static void listfield (killa_LexState *ls, struct ConsControl *cc) {
  /* listfield -> exp */
  expr(ls, &cc->v);
  checklimit(ls->fs, cc->na, KILLA_MAX_INT, "items in a constructor");
  cc->na++;
  cc->tostore++;
}


static void field (killa_LexState *ls, struct ConsControl *cc) {
  /* field -> listfield | recfield */
  switch(ls->t.token) {
    case TK_NAME: {  /* may be 'listfield' or 'recfield' */
      if (killaX_lookahead(ls) != ':')  /* expression? */
        listfield(ls, cc);
      else
        recfield(ls, cc);
      break;
    }
    case '[': {
      recfield(ls, cc);
      break;
    }
    default: {
      listfield(ls, cc);
      break;
    }
  }
}


static void constructor (killa_LexState *ls, killa_expdesc *t) {
  /* constructor -> '{' [ field { sep field } [sep] ] '}'
     sep -> ',' | ';' */
  killa_FuncState *fs = ls->fs;
  int line = ls->linenumber;
  int pc = killaK_codeABC(fs, OP_NEWTABLE, 0, 0, 0);
  struct ConsControl cc;
  cc.na = cc.nh = cc.tostore = 0;
  cc.t = t;
  init_exp(t, VRELOCABLE, pc);
  init_exp(&cc.v, VVOID, 0);  /* no value (yet) */
  killaK_exp2nextreg(ls->fs, t);  /* fix it at stack top */
  checknext(ls, '{');
  do {
    killa_assert(cc.v.k == VVOID || cc.tostore > 0);
    if (ls->t.token == '}') break;
    closelistfield(fs, &cc);
    field(ls, &cc);
  } while (testnext(ls, ',') || testnext(ls, ';'));
  check_match(ls, '}', '{', line);
  lastlistfield(fs, &cc);
  KILLA_SETARG_B(fs->f->code[pc], killaO_int2fb(cc.na)); /* set initial array size */
  KILLA_SETARG_C(fs->f->code[pc], killaO_int2fb(cc.nh));  /* set initial table size */
}

/* }====================================================================== */



static void parlist (killa_LexState *ls) {
  /* parlist -> [ param { `,' param } ] */
  killa_FuncState *fs = ls->fs;
  killa_Proto *f = fs->f;
  int nparams = 0;
  f->is_vararg = 0;
  if (ls->t.token != ')') {  /* is `parlist' not empty? */
    do {
      switch (ls->t.token) {
        case TK_NAME: {  /* param -> NAME */
          new_localvar(ls, str_checkname(ls));
          nparams++;
          break;
        }
        case TK_DOTS: {  /* param -> `...' */
          killaX_next(ls);
          f->is_vararg = 1;
          break;
        }
        default: killaX_syntaxerror(ls, "<name> or " KILLA_QL("...") " expected");
      }
    } while (!f->is_vararg && testnext(ls, ','));
  }
  adjustlocalvars(ls, nparams);
  f->numparams = killa_cast_byte(fs->nactvar);
  killaK_reserveregs(fs, fs->nactvar);  /* reserve register for parameters */
}


static void body (killa_LexState *ls, killa_expdesc *e, int ismethod, int line) {
  /* body ->  '(' parlist ')' '{' block '}' */
  killa_FuncState new_fs;
  killa_BlockCnt bl;
  open_func(ls, &new_fs, &bl);
  new_fs.f->linedefined = line;
  checknext(ls, '(');
  if (ismethod) {
    new_localvarliteral(ls, TK_THIS);  /* create 'this' parameter */
    adjustlocalvars(ls, 1);
  }
  parlist(ls);
  checknext(ls, ')');
  checknext(ls, '{');
  statlist(ls);
  new_fs.f->lastlinedefined = ls->linenumber;
  check_match(ls, '}', TK_FUNCTION, line);
  codeclosure(ls, new_fs.f, e);
  close_func(ls);
}


static int explist (killa_LexState *ls, killa_expdesc *v) {
  /* explist -> expr { `,' expr } */
  int n = 1;  /* at least one expression */
  expr(ls, v);
  while (testnext(ls, ',')) {
    killaK_exp2nextreg(ls->fs, v);
    expr(ls, v);
    n++;
  }
  return n;
}


static void funcargs (killa_LexState *ls, killa_expdesc *f, int line) {
  killa_FuncState *fs = ls->fs;
  killa_expdesc args;
  int base, nparams;
  if (ls->t.token == '(') {
    /* funcargs -> `(' [ explist ] `)' */
    killaX_next(ls);
    if (ls->t.token == ')')  /* arg list is empty? */
      args.k = VVOID;
    else {
      explist(ls, &args);
      killaK_setmultret(fs, &args);
    }
    check_match(ls, ')', '(', line);
  }
  else {
    killaX_syntaxerror(ls, "function arguments expected");
  }
  killa_assert(f->k == VNONRELOC);
  base = f->u.info;  /* base register for call */
  if (hasmultret(args.k))
    nparams = KILLA_MULTRET;  /* open call */
  else {
    if (args.k != VVOID)
      killaK_exp2nextreg(fs, &args);  /* close last argument */
    nparams = fs->freereg - (base+1);
  }
  init_exp(f, VCALL, killaK_codeABC(fs, OP_CALL, base, nparams+1, 2));
  killaK_fixline(fs, line);
  fs->freereg = base+1;  /* call remove function and arguments and leaves
                            (unless changed) one result */
}




/*
** {======================================================================
** Expression parsing
** =======================================================================
*/


static const char *prefixexp (killa_LexState *ls, killa_expdesc *v) {
  /* prefixexp -> NAME | '(' expr ')' | '(' cond ')?' exptrue ':' expfalse */
  switch (ls->t.token) {
    case '(': {
      int line = ls->linenumber;
      killaX_next(ls);
      expr(ls, v);
      check_match(ls, ')', '(', line);
      if (testnext(ls, '?')) {
        int condexit;
        int escapelist = KILLA_NO_JUMP;
        int reg;
        killa_FuncState *fs = ls->fs;
        if (v->k == VNULL) v->k = VFALSE;  /* 'falses' are all equal here */
        killaK_goiftrue(ls->fs, v);  /* skip over block if condition is false */
        condexit = v->f;
        expr(ls, v);  /* eval part for true conditional */
        reg = killaK_exp2anyreg(fs, v);  /* set result to reg. */
        killaK_concat(fs, &escapelist, killaK_jump(fs));  /* must jump over it */
        killaK_patchtohere(fs, condexit);
        checknext(ls, ':');
        expr(ls, v);  /* eval part for false conditional */
        killaK_exp2reg(fs, v, reg);  /* set result to reg. */
        killaK_patchtohere(fs, escapelist);  /* patch escape list to conditional end */
        return NULL;
      }
      killaK_dischargevars(ls->fs, v);
      return NULL;
    }
    case TK_NAME: {
      return singlevar(ls, v, 0);
    }
    default: {
      killaX_syntaxerror(ls, "unexpected symbol");
    }
  }
  return NULL;
}


static void primaryexp (killa_LexState *ls, killa_expdesc *v) {
  /* primaryexp ->
        prefixexp { '.' NAME | '[' exp ']' | '::' NAME funcargs | funcargs } */
  killa_FuncState *fs = ls->fs;
  int line = ls->linenumber;
  const char *globalname = prefixexp(ls, v);
  int isfunction = 0;
  for (;;) {
    switch (ls->t.token) {
      case '.': {  /* fieldsel */
        fieldsel(ls, v);
        break;
      }
      case '[': {  /* `[' exp1 `]' */
        killa_expdesc key;
        killaK_exp2anyregup(fs, v);
        yindex(ls, &key);
        killaK_indexed(fs, v, &key);
        break;
      }
      case TK_DBCOLON: {  /* '::' NAME funcargs */
        killa_expdesc key;
        killaX_next(ls);
        checkname(ls, &key);
        killaK_self(fs, v, &key);
        funcargs(ls, v, line);
        isfunction = 1;
        break;
      }
      case '(': {  /* funcargs */
        killaK_exp2nextreg(fs, v);
        funcargs(ls, v, line);
        isfunction = 1;
        break;
      }
      default: goto exitloop;
    }
  }
exitloop:
  /* only allow global calls to functions (they break at runtime), if it is 
     not a function and was not explicitely marked as global raise an error */
  if (globalname && !isfunction) {
    const char *msg = killaO_pushfstring(ls->L, "declaration for symbol " KILLA_QS " expected", 
                                       globalname);
    killaX_syntaxerror(ls, msg);
  }
}


static void simpleexp (killa_LexState *ls, killa_expdesc *v) {
  /* simpleexp -> NUMBER | STRING | NULL | TRUE | FALSE | ... |
                  constructor | FUNCTION body | primaryexp */
  switch (ls->t.token) {
    case TK_NUMBER: {
      init_exp(v, VKNUM, 0);
      v->u.nval = ls->t.seminfo.r;
      break;
    }
    case TK_STRING: {
      codestring(ls, v, ls->t.seminfo.ts);
      break;
    }
    case TK_NULL: {
      init_exp(v, VNULL, 0);
      break;
    }
    case TK_TRUE: {
      init_exp(v, VTRUE, 0);
      break;
    }
    case TK_FALSE: {
      init_exp(v, VFALSE, 0);
      break;
    }
    case TK_DOTS: {  /* vararg */
      killa_FuncState *fs = ls->fs;
      check_condition(ls, fs->f->is_vararg,
                      "cannot use " KILLA_QL("...") " outside a vararg function");
      init_exp(v, VVARARG, killaK_codeABC(fs, OP_VARARG, 0, 1, 0));
      break;
    }
    case '{': {  /* constructor */
      constructor(ls, v);
      return;
    }
    case TK_FUNCTION: {
      killaX_next(ls);
      body(ls, v, 0, ls->linenumber);
      return;
    }
    default: {
      primaryexp(ls, v);
      return;
    }
  }
  killaX_next(ls);
}


static killaK_UnOpr getunopr (int op) {
  switch (op) {
    case TK_NOT: return OPR_NOT;
    case '-': return OPR_MINUS;
    case '$': return OPR_LEN;
    default: return OPR_NOUNOPR;
  }
}


static killaK_BinOpr getbinopr (int op) {
  switch (op) {
    case '+': return OPR_ADD;
    case '-': return OPR_SUB;
    case '*': return OPR_MUL;
    case '/': return OPR_DIV;
    case '%': return OPR_MOD;
    case TK_POW: return OPR_POW;
    case TK_CONCAT: return OPR_CONCAT;
    case TK_NE: return OPR_NE;
    case TK_EQ: return OPR_EQ;
    case '<': return OPR_LT;
    case TK_LE: return OPR_LE;
    case '>': return OPR_GT;
    case TK_GE: return OPR_GE;
    case TK_AND: return OPR_AND;
    case TK_OR: return OPR_OR;
    case TK_CADD: return OPR_ADD;
    case TK_CSUB: return OPR_SUB;
    case TK_CMUL: return OPR_MUL;
    case TK_CDIV: return OPR_DIV;
    case TK_CMOD: return OPR_MOD;
    default: return OPR_NOBINOPR;
  }
}


static const struct {
  killa_ubyte left;  /* left priority for each binary operator */
  killa_ubyte right; /* right priority */
} priority[] = {  /* ORDER OPR */
   {6, 6}, {6, 6}, {7, 7}, {7, 7}, {7, 7},  /* `+' `-' `*' `/' `%' */
   {10, 9}, {5, 4},                 /* **, .. (right associative) */
   {3, 3}, {3, 3}, {3, 3},          /* ==, <, <= */
   {3, 3}, {3, 3}, {3, 3},          /* !=, >, >= */
   {2, 2}, {1, 1}                   /* &&, || */
};

#define UNARY_PRIORITY	8  /* priority for unary operators */


/*
** subexpr -> (simpleexp | unop subexpr) { binop subexpr }
** where `binop' is any binary operator with a priority higher than `limit'
*/
static killaK_BinOpr subexpr (killa_LexState *ls, killa_expdesc *v, int limit) {
  killaK_BinOpr op;
  killaK_UnOpr uop;
  enterlevel(ls);
  uop = getunopr(ls->t.token);
  if (uop != OPR_NOUNOPR) {
    int line = ls->linenumber;
    killaX_next(ls);
    subexpr(ls, v, UNARY_PRIORITY);
    killaK_prefix(ls->fs, uop, v, line);
  }
  else simpleexp(ls, v);
  /* expand while operators have priorities higher than `limit' */
  op = getbinopr(ls->t.token);
  while (op != OPR_NOBINOPR && priority[op].left > limit) {
    killa_expdesc v2;
    killaK_BinOpr nextop;
    int line = ls->linenumber;
    killaX_next(ls);
    killaK_infix(ls->fs, op, v);
    /* read sub-expression with higher priority */
    nextop = subexpr(ls, &v2, priority[op].right);
    killaK_posfix(ls->fs, op, v, &v2, line);
    op = nextop;
  }
  leavelevel(ls);
  return op;  /* return first untreated operator */
}


static void assignoperator (killa_LexState *ls, killa_expdesc *v) {
  killaK_BinOpr op;
  enterlevel(ls);
  op = getbinopr(ls->t.token);
  if (op != OPR_NOBINOPR) {
    killa_expdesc v2;
    int line = ls->linenumber;
    killaX_next(ls);
    killaK_infix(ls->fs, op, v);
    subexpr(ls, &v2, 0);
    killaK_posfix(ls->fs, op, v, &v2, line);
  }
  leavelevel(ls);
}


static void expr (killa_LexState *ls, killa_expdesc *v) {
  subexpr(ls, v, 0);
}

/* }==================================================================== */



/*
** {======================================================================
** Rules for Statements
** =======================================================================
*/


static void block (killa_LexState *ls) {
  /* block -> statlist */
  killa_FuncState *fs = ls->fs;
  killa_BlockCnt bl;
  enterblock(fs, &bl, 0);
  statlist(ls);
  leaveblock(fs);
}


/*
** structure to chain all variables in the left-hand side of an
** assignment
*/
struct LHS_assign {
  struct LHS_assign *prev;
  killa_expdesc v;  /* variable (global, local, upvalue, or indexed) */
};


/*
** check whether, in an assignment to an upvalue/local variable, the
** upvalue/local variable is begin used in a previous assignment to a
** table. If so, save original upvalue/local value in a safe place and
** use this safe copy in the previous assignment.
*/
static void check_conflict (killa_LexState *ls, struct LHS_assign *lh, killa_expdesc *v) {
  killa_FuncState *fs = ls->fs;
  int extra = fs->freereg;  /* eventual position to save local variable */
  int conflict = 0;
  for (; lh; lh = lh->prev) {  /* check all previous assignments */
    if (lh->v.k == VINDEXED) {  /* assigning to a table? */
      /* table is the upvalue/local being assigned now? */
      if (lh->v.u.ind.vt == v->k && lh->v.u.ind.t == v->u.info) {
        conflict = 1;
        lh->v.u.ind.vt = VLOCAL;
        lh->v.u.ind.t = extra;  /* previous assignment will use safe copy */
      }
      /* index is the local being assigned? (index cannot be upvalue) */
      if (v->k == VLOCAL && lh->v.u.ind.idx == v->u.info) {
        conflict = 1;
        lh->v.u.ind.idx = extra;  /* previous assignment will use safe copy */
      }
    }
  }
  if (conflict) {
    /* copy upvalue/local value to a temporary (in position 'extra') */
    killa_OpCode op = (v->k == VLOCAL) ? OP_MOVE : OP_GETUPVAL;
    killaK_codeABC(fs, op, extra, v->u.info, 0);
    killaK_reserveregs(fs, 1);
  }
}


static void assignment (killa_LexState *ls, struct LHS_assign *lh, int nvars) {
  killa_expdesc e;
  check_condition(ls, killa_vkisvar(lh->v.k), "syntax error");
  if (testnext(ls, ',')) {  /* assignment -> `,' primaryexp assignment */
    struct LHS_assign nv;
    nv.prev = lh;
    primaryexp(ls, &nv.v);
    if (nv.v.k != VINDEXED)
      check_conflict(ls, lh, &nv.v);
    checklimit(ls->fs, nvars + ls->L->nCcalls, KILLAI_MAXCCALLS,
                    "C levels");
    assignment(ls, &nv, nvars+1);
  }
  else if (ls->t.token != '=') {  /* assignment operator? */
    int line = ls->linenumber;
    e = lh->v;
    assignoperator(ls, &e);
    if ((ls->t.token == ',') || (nvars != 1)) {
      const char *msg = killaO_pushfstring(ls->L,
          "assignment operator used with multiple expresions at line %d", line);
      semerror(ls, msg);
    }
    killaK_setoneret(ls->fs, &e);  /* close last expression */
    killaK_storevar(ls->fs, &lh->v, &e);
    return;  /* avoid default */
  }
  else {  /* assignment -> `=' explist */
    int nexps;
    checknext(ls, '=');
    nexps = explist(ls, &e);
    if (nexps != nvars) {
      adjust_assign(ls, nvars, nexps, &e);
      if (nexps > nvars)
        ls->fs->freereg -= nexps - nvars;  /* remove extra values */
    }
    else {
      killaK_setoneret(ls->fs, &e);  /* close last expression */
      killaK_storevar(ls->fs, &lh->v, &e);
      return;  /* avoid default */
    }
  }
  init_exp(&e, VNONRELOC, ls->fs->freereg-1);  /* default assignment */
  killaK_storevar(ls->fs, &lh->v, &e);
}


static void globalvar (killa_LexState *ls) {
  /* globalvar -> VAR name '=' expr */
  struct LHS_assign v;
  killa_TString *varname;
  killa_expdesc key, e;
  int nexps, line = ls->linenumber;
  killa_FuncState *fs = ls->fs;
  killaX_next(ls);  /* skip VAR */
  varname = str_checkname(ls);
  singlevaraux(fs, ls->envn, &v.v, 1);  /* get environment variable */
  killa_assert(v.v->k == VLOCAL || v.v->k == VUPVAL);
  codestring(ls, &key, varname);  /* key is variable name */
  killaK_indexed(fs, &v.v, &key);  /* env[varname] */
  v.prev = NULL;
  checknext(ls, '=');
  nexps = explist(ls, &e);
  if (nexps != 1) {
      const char *msg = killaO_pushfstring(ls->L,
          "global declaration with multiple expresions at line %d", line);
      semerror(ls, msg);
  }
  else {
    killaK_setoneret(ls->fs, &e);  /* close last expression */
    killaK_storevar(ls->fs, &v.v, &e);
  }
}


static int cond (killa_LexState *ls) {
  /* cond -> exp */
  killa_expdesc v;
  expr(ls, &v);  /* read condition */
  if (v.k == VNULL) v.k = VFALSE;  /* 'falses' are all equal here */
  killaK_goiftrue(ls->fs, &v);
  return v.f;
}


static int nocond (killa_LexState *ls) {
  /* cond -> exp */
  killa_expdesc v;
  expr(ls, &v);  /* read condition */
  if (v.k == VNULL) v.k = VFALSE;  /* 'falses' are all equal here */
  killaK_goiffalse(ls->fs, &v);
  return v.t;
}


static void gotostat (killa_LexState *ls, int pc) {
  int line = ls->linenumber;
  killa_TString *label;
  int g;
  if (testnext(ls, TK_GOTO))
    label = str_checkname(ls);
  else {
    killaX_next(ls);  /* skip break */
    label = killaS_new(ls->L, "break");
  }
  g = newlabelentry(ls, &ls->dyd->gt, label, line, pc);
  findlabel(ls, g);  /* close it if label already defined */
}


/* check for repeated labels on the same block */
static void checkrepeated (killa_FuncState *fs, killa_Labellist *ll, killa_TString *label) {
  int i;
  for (i = fs->bl->firstlabel; i < ll->n; i++) {
    if (killa_eqstr(label, ll->arr[i].name)) {
      const char *msg = killaO_pushfstring(fs->ls->L,
                          "label " KILLA_QS " already defined on line %d",
                          killa_getstr(label), ll->arr[i].line);
      semerror(fs->ls, msg);
    }
  }
}


static void labelstat (killa_LexState *ls, killa_TString *label, int line) {
  /* label -> name ':' */
  killa_FuncState *fs = ls->fs;
  killa_Labellist *ll = &ls->dyd->label;
  int l;  /* index of new label being created */
  checkrepeated(fs, ll, label);  /* check for repeated labels */
  checknext(ls, ':');
  /* create new entry for this label */
  l = newlabelentry(ls, ll, label, line, fs->pc);
  /* skip other no-op statements */
  while (ls->t.token == ';')
    statement(ls);
  if (block_follow(ls)) {  /* label is last no-op statement in the block? */
    /* assume that locals are already out of scope */
    ll->arr[l].nactvar = fs->bl->nactvar;
  }
  findgotos(ls, &ll->arr[l]);
}


static void whilestat (killa_LexState *ls, int line) {
  /* whilestat -> WHILE '(' cond ')' '{' block '}' */
  killa_FuncState *fs = ls->fs;
  int whileinit;
  int condexit;
  killa_BlockCnt bl;
  killaX_next(ls);  /* skip WHILE */
  checknext(ls, '(');
  whileinit = killaK_getlabel(fs);
  condexit = cond(ls);
  checknext(ls, ')');
  enterblock(fs, &bl, 1);
  checknext(ls, '{');
  block(ls);
  killaK_jumpto(fs, whileinit);
  check_match(ls, '}', TK_WHILE, line);
  leaveblock(fs);
  killaK_patchtohere(fs, condexit);  /* false conditions finish the loop */
}


static void repeatstat (killa_LexState *ls, int line) {
  /* repeatstat -> DO '{' block '}' WHILE '(' cond ')' */
  int condexit;
  killa_FuncState *fs = ls->fs;
  int repeat_init = killaK_getlabel(fs);
  killa_BlockCnt bl1;
  enterblock(fs, &bl1, 1);  /* loop block */
  killaX_next(ls);  /* skip DO */
  checknext(ls, '{');
  statlist(ls);
  checknext(ls, '}');
  check_match(ls, TK_WHILE, TK_DO, line);
  checknext(ls, '(');
  line = ls->linenumber;
  condexit = nocond(ls);  /* read condition (inside scope block) */
  check_match(ls, ')', '(', line);
  killaK_patchlist(fs, condexit, repeat_init);  /* close the loop */
  leaveblock(fs);  /* finish loop */
}


static int exp1 (killa_LexState *ls) {
  killa_expdesc e;
  int reg;
  expr(ls, &e);
  killaK_exp2nextreg(ls->fs, &e);
  killa_assert(e.k == VNONRELOC);
  reg = e.u.info;
  return reg;
}


static void forbody (killa_LexState *ls, int base, int line, int nvars, int isnum) {
  /* forbody -> '{' block */
  killa_BlockCnt bl;
  killa_FuncState *fs = ls->fs;
  int prep, endfor;
  adjustlocalvars(ls, 3);  /* control variables */
  checknext(ls, '{');
  prep = isnum ? killaK_codeAsBx(fs, OP_FORPREP, base, KILLA_NO_JUMP) : killaK_jump(fs);
  enterblock(fs, &bl, 0);  /* scope for declared variables */
  adjustlocalvars(ls, nvars);
  killaK_reserveregs(fs, nvars);
  block(ls);
  leaveblock(fs);  /* end of scope for declared variables */
  killaK_patchtohere(fs, prep);
  if (isnum)  /* numeric for? */
    endfor = killaK_codeAsBx(fs, OP_FORLOOP, base, KILLA_NO_JUMP);
  else {  /* generic for */
    killaK_codeABC(fs, OP_TFORCALL, base, 0, nvars);
    killaK_fixline(fs, line);
    endfor = killaK_codeAsBx(fs, OP_TFORLOOP, base + 2, KILLA_NO_JUMP);
  }
  killaK_patchlist(fs, endfor, prep + 1);
  killaK_fixline(fs, line);
}


static void fornum (killa_LexState *ls, killa_TString *varname, int line) {
  /* fornum -> NAME = exp1 TO exp1 [',' exp1] ')' forbody */
  killa_FuncState *fs = ls->fs;
  int base = fs->freereg;
  new_localvarliteral(ls, "(for index)");
  new_localvarliteral(ls, "(for limit)");
  new_localvarliteral(ls, "(for step)");
  new_localvar(ls, varname);
  checknext(ls, '=');
  exp1(ls);  /* initial value */
  checknext(ls, TK_TO);
  exp1(ls);  /* limit */
  if (testnext(ls, ','))
    exp1(ls);  /* optional step */
  else {  /* default step = 1 */
    killaK_codek(fs, fs->freereg, killaK_numberK(fs, 1));
    killaK_reserveregs(fs, 1);
  }
  checknext(ls, ')');
  forbody(ls, base, line, 1, 1);
}


static void forlist (killa_LexState *ls, killa_TString *indexname) {
  /* forlist -> NAME {,NAME} IN explist ')' forbody */
  killa_FuncState *fs = ls->fs;
  killa_expdesc e;
  int nvars = 4;  /* gen, state, control, plus at least one declared var */
  int line;
  int base = fs->freereg;
  /* create control variables */
  new_localvarliteral(ls, "(for generator)");
  new_localvarliteral(ls, "(for state)");
  new_localvarliteral(ls, "(for control)");
  /* create declared variables */
  new_localvar(ls, indexname);
  while (testnext(ls, ',')) {
    new_localvar(ls, str_checkname(ls));
    nvars++;
  }
  checknext(ls, TK_IN);
  line = ls->linenumber;
  adjust_assign(ls, 3, explist(ls, &e), &e);
  killaK_checkstack(fs, 3);  /* extra space to call generator */
  checknext(ls, ')');
  forbody(ls, base, line, nvars - 3, 0);
}


static void forcstyle (killa_LexState *ls, killa_BlockCnt *bl, int line) {
  /* forcstyle -> [forinit] ';' forconditional ';' forstep ')' '{' block '}' */
  killa_FuncState *fs = ls->fs;
  int condinit, condexit;
  int stepinit, stepexit;
  int blockinit, blockexit;
  if (ls->t.token != ';') {
    statement(ls); /* forinit */
  }
  checknext(ls, ';');
  condinit = killaK_getlabel(fs);
  condexit = cond(ls); /* forconditional */
  checknext(ls, ';');
  blockinit = killaK_jump(fs);
  stepinit = killaK_getlabel(fs);
  statement(ls); /* forstep */
  stepexit = killaK_jump(fs);
  checknext(ls, ')');
  checknext(ls, '{');
  killaK_patchtohere(fs, blockinit);
  block(ls);
  blockexit = killaK_getlabel(fs);
  killaK_jumpto(fs, stepinit);
  killaK_patchtohere(fs, stepexit);
  killaK_jumpto(fs, condinit);
  check_match(ls, '}', TK_FOR, line);
  leaveblock(fs);  /* loop scope (`break' jumps to this point) */
  killaK_patchtohere(fs, condexit);  /* false conditions finish the loop */
}


static void forstat (killa_LexState *ls, int line) {
  /* forstat -> FOR EACH '(' VAR (fornum | forlist) '}' */
  /* forstat -> FOR '(' forcstyle '}' */
  killa_FuncState *fs = ls->fs;
  killa_TString *varname;
  killa_BlockCnt bl;
  enterblock(fs, &bl, 1);  /* scope for loop and control variables */
  killaX_next(ls);  /* skip FOR */
  if (ls->t.token == TK_EACH) {
    killaX_next(ls);  /* skip EACH */
    checknext(ls, '(');
    checknext(ls, TK_VAR);
    varname = str_checkname(ls);  /* first variable name */
    switch (ls->t.token) {
      case '=': fornum(ls, varname, line); break;
      case ',': case TK_IN: forlist(ls, varname); break;
      default: killaX_syntaxerror(ls, KILLA_QL("=") " or " KILLA_QL("in") " expected");
    }
    check_match(ls, '}', TK_FOR, line);
    leaveblock(fs);  /* loop scope (`break' jumps to this point) */
  }
  else {
    checknext(ls, '(');
    forcstyle(ls, &bl, line);
  }
}


static int test_then_block (killa_LexState *ls, int *escapelist, int line) { 
  /* test_then_block -> [IF | ELSE] '(' cond ')' '{' block */
  killa_BlockCnt bl;
  killa_FuncState *fs = ls->fs;
  killa_expdesc v;
  int jf;  /* instruction to skip 'then' code (if condition is false) */
  int tk = ls->t.token;
  killaX_next(ls);  /* skip IF or ELSE */
  checknext(ls, '(');
  expr(ls, &v);  /* read condition */
  checknext(ls, ')');
  checknext(ls, '{');
  if (ls->t.token == TK_GOTO || ls->t.token == TK_BREAK) {
    killaK_goiffalse(ls->fs, &v);  /* will jump to label if condition is true */
    enterblock(fs, &bl, 0);  /* must enter block before 'goto' */
    gotostat(ls, v.t);  /* handle goto/break */
    if (block_follow(ls)) {  /* 'goto' is the entire block? */
      leaveblock(fs);
      return 0;  /* and that is it */
    }
    else  /* must skip over 'then' part if condition is false */
      jf = killaK_jump(fs);
  }
  else {  /* regular case (not goto/break) */
    killaK_goiftrue(ls->fs, &v);  /* skip over block if condition is false */
    enterblock(fs, &bl, 0);
    jf = v.f;
  }
  statlist(ls);  /* `then' part */
  leaveblock(fs);
  if (ls->t.token == '}') {
      killaX_lookahead(ls);
      if (ls->lookahead.token == TK_ELSE) {  /* followed by 'else' */
        killaK_concat(fs, escapelist, killaK_jump(fs));  /* must jump over it */
        killaK_patchtohere(fs, jf);
        killaX_next(ls); /* skip '}' */
        return 1;
      }
  }
  killaK_patchtohere(fs, jf);
  check_match(ls, '}', tk, line);
  return 0;
}


static void ifstat (killa_LexState *ls, int line) {
  /* ifstat -> IF '(' cond ')' '{' block { '}' ELSE IF '(' cond ')' '{' block} [ '}' ELSE '{' block] '}' */
  killa_FuncState *fs = ls->fs;
  int escapelist = KILLA_NO_JUMP;  /* exit list for finished parts */
  int haselse = test_then_block(ls, &escapelist, line);  /* IF cond '{' block */
  while (haselse && (killaX_lookahead(ls) == TK_IF)) {
    killaX_next(ls); /* skip IF */
    haselse = test_then_block(ls, &escapelist, ls->linenumber);  /* ELSE IF cond BEGIN block */
  }
  if (testnext(ls, TK_ELSE)) {
    line = ls->linenumber;
    checknext(ls, '{');
    block(ls);  /* `else' part */
    check_match(ls, '}', TK_ELSE, line);
  }
  killaK_patchtohere(fs, escapelist);  /* patch escape list to 'if' end */
}


static void localfunc (killa_LexState *ls) {
  killa_expdesc b;
  killa_FuncState *fs = ls->fs;
  new_localvar(ls, str_checkname(ls));  /* new local variable */
  adjustlocalvars(ls, 1);  /* enter its scope */
  body(ls, &b, 0, ls->linenumber);  /* function created in next register */
  /* debug information will only see the variable after this point! */
  getlocvar(fs, b.u.info)->startpc = fs->pc;
}


static void localstat (killa_LexState *ls) {
  /* stat -> VAR NAME {`,' NAME} [`=' explist] */
  int nvars = 0;
  int nexps;
  killa_expdesc e;
  killaX_next(ls);  /* skip VAR */
  do {
    new_localvar(ls, str_checkname(ls));
    nvars++;
  } while (testnext(ls, ','));
  if (testnext(ls, '='))
    nexps = explist(ls, &e);
  else {
    e.k = VVOID;
    nexps = 0;
  }
  adjust_assign(ls, nvars, nexps, &e);
  adjustlocalvars(ls, nvars);
}


static int funcname (killa_LexState *ls, killa_expdesc *v, int isglobal) {
  /* funcname -> NAME {fieldsel} ['::' NAME] */
  int ismethod = 0;
  singlevar(ls, v, isglobal);
  while (ls->t.token == '.')
    fieldsel(ls, v);
  if (ls->t.token == TK_DBCOLON) {
    ismethod = 1;
    fieldsel(ls, v);
  }
  return ismethod;
}


static void funcstat (killa_LexState *ls, int line, int isglobal) {
  /* funcstat -> funcname body */
  int ismethod;
  killa_expdesc v, b;
  ismethod = funcname(ls, &v, isglobal);
  body(ls, &b, ismethod, line);
  killaK_storevar(ls->fs, &v, &b);
  killaK_fixline(ls->fs, line);  /* definition `happens' in the first line */
}


static void exprstat (killa_LexState *ls) {
  /* stat -> label | func | assignment */
  killa_FuncState *fs = ls->fs;
  struct LHS_assign v;
  if (ls->t.token == TK_NAME) {
    killaX_lookahead(ls);
    if (ls->lookahead.token == ':') {  /* stat -> label */
        labelstat(ls, str_checkname(ls), ls->linenumber);
        return;
    }
  }
  primaryexp(ls, &v.v);
  if (v.v.k == VCALL)  /* stat -> func */
    KILLA_SETARG_C(killaK_getcode(fs, &v.v), 1);  /* call statement uses no results */
  else {  /* stat -> assignment */
    v.prev = NULL;
    assignment(ls, &v, 1);
  }
}


static void retstat (killa_LexState *ls) {
  /* stat -> RETURN [explist] [';'] */
  killa_FuncState *fs = ls->fs;
  killa_expdesc e;
  int first, nret;  /* registers with returned values */
  if (block_follow(ls) || ls->t.token == ';')
    first = nret = 0;  /* return no values */
  else {
    nret = explist(ls, &e);  /* optional return values */
    if (hasmultret(e.k)) {
      killaK_setmultret(fs, &e);
      if (e.k == VCALL && nret == 1) {  /* tail call? */
        KILLA_SET_OPCODE(killaK_getcode(fs,&e), OP_TAILCALL);
        killa_assert(KILLA_GETARG_A(killaK_getcode(fs,&e)) == fs->nactvar);
      }
      first = fs->nactvar;
      nret = KILLA_MULTRET;  /* return all values */
    }
    else {
      if (nret == 1)  /* only one single value? */
        first = killaK_exp2anyreg(fs, &e);
      else {
        killaK_exp2nextreg(fs, &e);  /* values must go to the `stack' */
        first = fs->nactvar;  /* return all `active' values */
        killa_assert(nret == fs->freereg - first);
      }
    }
  }
  killaK_ret(fs, first, nret);
  testnext(ls, ';');  /* skip optional semicolon */
}


static void statement (killa_LexState *ls) {
  int line = ls->linenumber;  /* may be needed for error messages */
  enterlevel(ls);
  switch (ls->t.token) {
    case ';': {  /* stat -> ';' (empty statement) */
      killaX_next(ls);  /* skip ';' */
      break;
    }
    case TK_IF: {  /* stat -> ifstat */
      ifstat(ls, line);
      break;
    }
    case TK_WHILE: {  /* stat -> whilestat */
      whilestat(ls, line);
      break;
    }
    case '{': {  /* stat -> '{' block '}' */
      killaX_next(ls);  /* skip '{' */
      block(ls);
      check_match(ls, '}', '{', line);
      break;
    }
    case TK_FOR: {  /* stat -> forstat */
      forstat(ls, line);
      break;
    }
    case TK_DO: {  /* stat -> repeatstat */
      repeatstat(ls, line);
      break;
    }
    case TK_PRIVATE: {
      killaX_next(ls);  /* skip PRIVATE */
      if (ls->t.token == TK_FUNCTION) {  /* local function? */
        killaX_next(ls);  /* skip FUNCTION */
        if (killaX_lookahead(ls) == '(') {
          localfunc(ls);
        }
        else {
          funcstat(ls, line, 0);
        }
      }
      else if (ls->t.token == TK_VAR) {  /* local variable? */
        localstat(ls);
      }
      else
        killaX_syntaxerror(ls, "unexpected symbol");
      break;
    }
    case TK_PUBLIC: {
      killaX_next(ls);  /* skip PUBLIC */
      if (ls->t.token == TK_FUNCTION) {  /* global function? */
        killaX_next(ls);  /* skip FUNCTION */
        funcstat(ls, line, 1);
      }
      else if (ls->t.token == TK_VAR) {  /* global variable? */
        globalvar(ls);
      }
      else 
        killaX_syntaxerror(ls, "unexpected symbol");
      break;
    }
    case TK_FUNCTION: {  /* stat -> localfunc */
      killaX_next(ls);  /* skip FUNCTION */
      if (killaX_lookahead(ls) == '(') {
        localfunc(ls);
      }
      else {
        funcstat(ls, line, 0);
      }
      break;
    }
    case TK_VAR: {  /* stat -> localstat */
      localstat(ls);
      break;
    }
    case TK_RETURN: {  /* stat -> retstat */
      killaX_next(ls);  /* skip RETURN */
      retstat(ls);
      break;
    }
    case TK_BREAK:   /* stat -> breakstat */
    case TK_GOTO: {  /* stat -> 'goto' NAME */
      gotostat(ls, killaK_jump(ls->fs));
      break;
    }
    default: {  /* stat -> func | assignment */
      exprstat(ls);
      break;
    }
  }
  killa_assert(ls->fs->f->maxstacksize >= ls->fs->freereg &&
             ls->fs->freereg >= ls->fs->nactvar);
  ls->fs->freereg = ls->fs->nactvar;  /* free registers */
  leavelevel(ls);
}

/* }====================================================================== */


killa_Proto *killaY_parser (killa_State *L, killa_ZIO *z, killa_Mbuffer *buff,
                    killa_Dyndata *dyd, const char *name, int firstchar) {
  killa_LexState lexstate;
  killa_FuncState funcstate;
  killa_BlockCnt bl;
  killa_TString *tname = killaS_new(L, name);
  killa_setsvalue2s(L, L->top, tname);  /* push name to protect it */
  killa_incr_top(L);
  lexstate.buff = buff;
  lexstate.dyd = dyd;
  dyd->actvar.n = dyd->gt.n = dyd->label.n = 0;
  killaX_setinput(L, &lexstate, z, tname, firstchar);
  open_mainfunc(&lexstate, &funcstate, &bl);
  killaX_next(&lexstate);  /* read first token */
  statlist(&lexstate);  /* main body */
  check(&lexstate, TK_EOS);
  close_func(&lexstate);
  L->top--;  /* pop name */
  killa_assert(!funcstate.prev && funcstate.nups == 1 && !lexstate.fs);
  /* all scopes should be correctly finished */
  killa_assert(dyd->actvar.n == 0 && dyd->gt.n == 0 && dyd->label.n == 0);
  return funcstate.f;
}

