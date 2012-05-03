/* ========================================================================== */
/*   Code generator for Killa                                                 */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>

#define KILLA_CORE

#include "killa.h"

#include "kcode.h"
#include "kdebug.h"
#include "kdo.h"
#include "kgc.h"
#include "klex.h"
#include "kmem.h"
#include "kobject.h"
#include "kopcodes.h"
#include "kparser.h"
#include "kstring.h"
#include "ktable.h"
#include "kvm.h"


#define hasjumps(e)	((e)->t != (e)->f)


static int isnumeral(killa_expdesc *e) {
  return (e->k == VKNUM && e->t == KILLA_NO_JUMP && e->f == KILLA_NO_JUMP);
}


void killaK_nil (killa_FuncState *fs, int from, int n) {
  killa_Instruction *previous;
  int l = from + n - 1;  /* last register to set nil */
  if (fs->pc > fs->lasttarget) {  /* no jumps to current position? */
    previous = &fs->f->code[fs->pc-1];
    if (KILLA_GET_OPCODE(*previous) == OP_LOADNIL) {
      int pfrom = KILLA_GETARG_A(*previous);
      int pl = pfrom + KILLA_GETARG_B(*previous);
      if ((pfrom <= from && from <= pl + 1) ||
          (from <= pfrom && pfrom <= l + 1)) {  /* can connect both? */
        if (pfrom < from) from = pfrom;  /* from = min(from, pfrom) */
        if (pl > l) l = pl;  /* l = max(l, pl) */
        KILLA_SETARG_A(*previous, from);
        KILLA_SETARG_B(*previous, l - from);
        return;
      }
    }  /* else go through */
  }
  killaK_codeABC(fs, OP_LOADNIL, from, n - 1, 0);  /* else no optimization */
}


int killaK_jump (killa_FuncState *fs) {
  int jpc = fs->jpc;  /* save list of jumps to here */
  int j;
  fs->jpc = KILLA_NO_JUMP;
  j = killaK_codeAsBx(fs, OP_JMP, 0, KILLA_NO_JUMP);
  killaK_concat(fs, &j, jpc);  /* keep them on hold */
  return j;
}


void killaK_ret (killa_FuncState *fs, int first, int nret) {
  killaK_codeABC(fs, OP_RETURN, first, nret+1, 0);
}


static int condjump (killa_FuncState *fs, killa_OpCode op, int A, int B, int C) {
  killaK_codeABC(fs, op, A, B, C);
  return killaK_jump(fs);
}


static void fixjump (killa_FuncState *fs, int pc, int dest) {
  killa_Instruction *jmp = &fs->f->code[pc];
  int offset = dest-(pc+1);
  killa_assert(dest != KILLA_NO_JUMP);
  if (abs(offset) > KILLA_MAXARG_sBx)
    killaX_syntaxerror(fs->ls, "control structure too long");
  KILLA_SETARG_sBx(*jmp, offset);
}


/*
** returns current `pc' and marks it as a jump target (to avoid wrong
** optimizations with consecutive instructions not in the same basic block).
*/
int killaK_getlabel (killa_FuncState *fs) {
  fs->lasttarget = fs->pc;
  return fs->pc;
}


static int getjump (killa_FuncState *fs, int pc) {
  int offset = KILLA_GETARG_sBx(fs->f->code[pc]);
  if (offset == KILLA_NO_JUMP)  /* point to itself represents end of list */
    return KILLA_NO_JUMP;  /* end of list */
  else
    return (pc+1)+offset;  /* turn offset into absolute position */
}


static killa_Instruction *getjumpcontrol (killa_FuncState *fs, int pc) {
  killa_Instruction *pi = &fs->f->code[pc];
  if (pc >= 1 && killa_testTMode(KILLA_GET_OPCODE(*(pi-1))))
    return pi-1;
  else
    return pi;
}


/*
** check whether list has any jump that do not produce a value
** (or produce an inverted value)
*/
static int need_value (killa_FuncState *fs, int list) {
  for (; list != KILLA_NO_JUMP; list = getjump(fs, list)) {
    killa_Instruction i = *getjumpcontrol(fs, list);
    if (KILLA_GET_OPCODE(i) != OP_TESTSET) return 1;
  }
  return 0;  /* not found */
}


static int patchtestreg (killa_FuncState *fs, int node, int reg) {
  killa_Instruction *i = getjumpcontrol(fs, node);
  if (KILLA_GET_OPCODE(*i) != OP_TESTSET)
    return 0;  /* cannot patch other instructions */
  if (reg != KILLA_NO_REG && reg != KILLA_GETARG_B(*i))
    KILLA_SETARG_A(*i, reg);
  else  /* no register to put value or register already has the value */
    *i = KILLA_CREATE_ABC(OP_TEST, KILLA_GETARG_B(*i), 0, KILLA_GETARG_C(*i));

  return 1;
}


static void removevalues (killa_FuncState *fs, int list) {
  for (; list != KILLA_NO_JUMP; list = getjump(fs, list))
      patchtestreg(fs, list, KILLA_NO_REG);
}


static void patchlistaux (killa_FuncState *fs, int list, int vtarget, int reg,
                          int dtarget) {
  while (list != KILLA_NO_JUMP) {
    int next = getjump(fs, list);
    if (patchtestreg(fs, list, reg))
      fixjump(fs, list, vtarget);
    else
      fixjump(fs, list, dtarget);  /* jump to default target */
    list = next;
  }
}


static void dischargejpc (killa_FuncState *fs) {
  patchlistaux(fs, fs->jpc, fs->pc, KILLA_NO_REG, fs->pc);
  fs->jpc = KILLA_NO_JUMP;
}


void killaK_patchlist (killa_FuncState *fs, int list, int target) {
  if (target == fs->pc)
    killaK_patchtohere(fs, list);
  else {
    killa_assert(target < fs->pc);
    patchlistaux(fs, list, target, KILLA_NO_REG, target);
  }
}


KILLAI_FUNC void killaK_patchclose (killa_FuncState *fs, int list, int level) {
  level++;  /* argument is +1 to reserve 0 as non-op */
  while (list != KILLA_NO_JUMP) {
    int next = getjump(fs, list);
    killa_assert(KILLA_GET_OPCODE(fs->f->code[list]) == OP_JMP &&
                (KILLA_GETARG_A(fs->f->code[list]) == 0 ||
                 KILLA_GETARG_A(fs->f->code[list]) >= level));
    KILLA_SETARG_A(fs->f->code[list], level);
    list = next;
  }
}


void killaK_patchtohere (killa_FuncState *fs, int list) {
  killaK_getlabel(fs);
  killaK_concat(fs, &fs->jpc, list);
}


void killaK_concat (killa_FuncState *fs, int *l1, int l2) {
  if (l2 == KILLA_NO_JUMP) return;
  else if (*l1 == KILLA_NO_JUMP)
    *l1 = l2;
  else {
    int list = *l1;
    int next;
    while ((next = getjump(fs, list)) != KILLA_NO_JUMP)  /* find last element */
      list = next;
    fixjump(fs, list, l2);
  }
}


static int killaK_code (killa_FuncState *fs, killa_Instruction i) {
  killa_Proto *f = fs->f;
  dischargejpc(fs);  /* `pc' will change */
  /* put new instruction in code array */
  killaM_growvector(fs->ls->L, f->code, fs->pc, f->sizecode, killa_Instruction,
                  KILLA_MAX_INT, "opcodes");
  f->code[fs->pc] = i;
  /* save corresponding line information */
  killaM_growvector(fs->ls->L, f->lineinfo, fs->pc, f->sizelineinfo, int,
                  KILLA_MAX_INT, "opcodes");
  f->lineinfo[fs->pc] = fs->ls->lastline;
  return fs->pc++;
}


int killaK_codeABC (killa_FuncState *fs, killa_OpCode o, int a, int b, int c) {
  killa_assert(killa_getOpMode(o) == iABC);
  killa_assert(killa_getBMode(o) != OpArgN || b == 0);
  killa_assert(killa_getCMode(o) != OpArgN || c == 0);
  killa_assert(a <= KILLA_MAXARG_A && b <= KILLA_MAXARG_B && c <= KILLA_MAXARG_C);
  return killaK_code(fs, KILLA_CREATE_ABC(o, a, b, c));
}


int killaK_codeABx (killa_FuncState *fs, killa_OpCode o, int a, unsigned int bc) {
  killa_assert(killa_getOpMode(o) == iABx || killa_getOpMode(o) == iAsBx);
  killa_assert(killa_getCMode(o) == OpArgN);
  killa_assert(a <= KILLA_MAXARG_A && bc <= KILLA_MAXARG_Bx);
  return killaK_code(fs, KILLA_CREATE_ABx(o, a, bc));
}


static int codeextraarg (killa_FuncState *fs, int a) {
  killa_assert(a <= KILLA_MAXARG_Ax);
  return killaK_code(fs, KILLA_CREATE_Ax(OP_EXTRAARG, a));
}


int killaK_codek (killa_FuncState *fs, int reg, int k) {
  if (k <= KILLA_MAXARG_Bx)
    return killaK_codeABx(fs, OP_LOADK, reg, k);
  else {
    int p = killaK_codeABx(fs, OP_LOADKX, reg, 0);
    codeextraarg(fs, k);
    return p;
  }
}


void killaK_checkstack (killa_FuncState *fs, int n) {
  int newstack = fs->freereg + n;
  if (newstack > fs->f->maxstacksize) {
    if (newstack >= KILLA_MAXSTACK)
      killaX_syntaxerror(fs->ls, "function or expression too complex");
    fs->f->maxstacksize = killa_cast_byte(newstack);
  }
}


void killaK_reserveregs (killa_FuncState *fs, int n) {
  killaK_checkstack(fs, n);
  fs->freereg += n;
}


static void freereg (killa_FuncState *fs, int reg) {
  if (!KILLA_ISK(reg) && reg >= fs->nactvar) {
    fs->freereg--;
    killa_assert(reg == fs->freereg);
  }
}


static void freeexp (killa_FuncState *fs, killa_expdesc *e) {
  if (e->k == VNONRELOC)
    freereg(fs, e->u.info);
}


static int addk (killa_FuncState *fs, killa_TValue *key, killa_TValue *v) {
  killa_State *L = fs->ls->L;
  killa_TValue *idx = killaH_set(L, fs->h, key);
  killa_Proto *f = fs->f;
  int k, oldsize;
  if (killa_ttisnumber(idx)) {
    killa_Number n = killa_nvalue(idx);
    killa_number2int(k, n);
    if (killaV_rawequalobj(&f->k[k], v))
      return k;
    /* else may be a collision (e.g., between 0.0 and "\0\0\0\0\0\0\0\0");
       go through and create a new entry for this value */
  }
  /* constant not found; create a new entry */
  oldsize = f->sizek;
  k = fs->nk;
  /* numerical value does not need GC barrier;
     table has no metatable, so it does not need to invalidate cache */
  killa_setnvalue(idx, killa_cast_num(k));
  killaM_growvector(L, f->k, k, f->sizek, killa_TValue, KILLA_MAXARG_Ax, "constants");
  while (oldsize < f->sizek) killa_setnilvalue(&f->k[oldsize++]);
  killa_setobj(L, &f->k[k], v);
  fs->nk++;
  killaC_barrier(L, f, v);
  return k;
}


int killaK_stringK (killa_FuncState *fs, killa_TString *s) {
  killa_TValue o;
  killa_setsvalue(fs->ls->L, &o, s);
  return addk(fs, &o, &o);
}


int killaK_numberK (killa_FuncState *fs, killa_Number r) {
  int n;
  killa_State *L = fs->ls->L;
  killa_TValue o;
  killa_setnvalue(&o, r);
  if (r == 0 || killai_numisnan(NULL, r)) {  /* handle -0 and NaN */
    /* use raw representation as key to avoid numeric problems */
    killa_setsvalue(L, L->top, killaS_newlstr(L, (char *)&r, sizeof(r)));
     killa_incr_top(L);
     n = addk(fs, L->top - 1, &o);
     L->top--;
  }
  else
    n = addk(fs, &o, &o);  /* regular case */
  return n;
}


static int boolK (killa_FuncState *fs, int b) {
  killa_TValue o;
  killa_setbvalue(&o, b);
  return addk(fs, &o, &o);
}


static int nilK (killa_FuncState *fs) {
  killa_TValue k, v;
  killa_setnilvalue(&v);
  /* cannot use nil as key; instead use table itself to represent nil */
  killa_sethvalue(fs->ls->L, &k, fs->h);
  return addk(fs, &k, &v);
}


void killaK_setreturns (killa_FuncState *fs, killa_expdesc *e, int nresults) {
  if (e->k == VCALL) {  /* expression is an open function call? */
    KILLA_SETARG_C(killaK_getcode(fs, e), nresults+1);
  }
  else if (e->k == VVARARG) {
    KILLA_SETARG_B(killaK_getcode(fs, e), nresults+1);
    KILLA_SETARG_A(killaK_getcode(fs, e), fs->freereg);
    killaK_reserveregs(fs, 1);
  }
}


void killaK_setoneret (killa_FuncState *fs, killa_expdesc *e) {
  if (e->k == VCALL) {  /* expression is an open function call? */
    e->k = VNONRELOC;
    e->u.info = KILLA_GETARG_A(killaK_getcode(fs, e));
  }
  else if (e->k == VVARARG) {
    KILLA_SETARG_B(killaK_getcode(fs, e), 2);
    e->k = VRELOCABLE;  /* can relocate its simple result */
  }
}


void killaK_dischargevars (killa_FuncState *fs, killa_expdesc *e) {
  switch (e->k) {
    case VLOCAL: {
      e->k = VNONRELOC;
      break;
    }
    case VUPVAL: {
      e->u.info = killaK_codeABC(fs, OP_GETUPVAL, 0, e->u.info, 0);
      e->k = VRELOCABLE;
      break;
    }
    case VINDEXED: {
      killa_OpCode op = OP_GETTABUP;  /* assume 't' is in an upvalue */
      freereg(fs, e->u.ind.idx);
      if (e->u.ind.vt == VLOCAL) {  /* 't' is in a register? */
        freereg(fs, e->u.ind.t);
        op = OP_GETTABLE;
      }
      e->u.info = killaK_codeABC(fs, op, 0, e->u.ind.t, e->u.ind.idx);
      e->k = VRELOCABLE;
      break;
    }
    case VVARARG:
    case VCALL: {
      killaK_setoneret(fs, e);
      break;
    }
    default: break;  /* there is one value available (somewhere) */
  }
}


static int code_label (killa_FuncState *fs, int A, int b, int jump) {
  killaK_getlabel(fs);  /* those instructions may be jump targets */
  return killaK_codeABC(fs, OP_LOADBOOL, A, b, jump);
}


static void discharge2reg (killa_FuncState *fs, killa_expdesc *e, int reg) {
  killaK_dischargevars(fs, e);
  switch (e->k) {
    case VNULL: {
      killaK_nil(fs, reg, 1);
      break;
    }
    case VFALSE:  case VTRUE: {
      killaK_codeABC(fs, OP_LOADBOOL, reg, e->k == VTRUE, 0);
      break;
    }
    case VK: {
      killaK_codek(fs, reg, e->u.info);
      break;
    }
    case VKNUM: {
      killaK_codek(fs, reg, killaK_numberK(fs, e->u.nval));
      break;
    }
    case VRELOCABLE: {
      killa_Instruction *pc = &killaK_getcode(fs, e);
      KILLA_SETARG_A(*pc, reg);
      break;
    }
    case VNONRELOC: {
      if (reg != e->u.info)
        killaK_codeABC(fs, OP_MOVE, reg, e->u.info, 0);
      break;
    }
    default: {
      killa_assert(e->k == VVOID || e->k == VJMP);
      return;  /* nothing to do... */
    }
  }
  e->u.info = reg;
  e->k = VNONRELOC;
}


static void discharge2anyreg (killa_FuncState *fs, killa_expdesc *e) {
  if (e->k != VNONRELOC) {
    killaK_reserveregs(fs, 1);
    discharge2reg(fs, e, fs->freereg-1);
  }
}


static void exp2reg (killa_FuncState *fs, killa_expdesc *e, int reg) {
  discharge2reg(fs, e, reg);
  if (e->k == VJMP)
    killaK_concat(fs, &e->t, e->u.info);  /* put this jump in `t' list */
  if (hasjumps(e)) {
    int final;  /* position after whole expression */
    int p_f = KILLA_NO_JUMP;  /* position of an eventual LOAD false */
    int p_t = KILLA_NO_JUMP;  /* position of an eventual LOAD true */
    if (need_value(fs, e->t) || need_value(fs, e->f)) {
      int fj = (e->k == VJMP) ? KILLA_NO_JUMP : killaK_jump(fs);
      p_f = code_label(fs, reg, 0, 1);
      p_t = code_label(fs, reg, 1, 0);
      killaK_patchtohere(fs, fj);
    }
    final = killaK_getlabel(fs);
    patchlistaux(fs, e->f, final, reg, p_f);
    patchlistaux(fs, e->t, final, reg, p_t);
  }
  e->f = e->t = KILLA_NO_JUMP;
  e->u.info = reg;
  e->k = VNONRELOC;
}


void killaK_exp2nextreg (killa_FuncState *fs, killa_expdesc *e) {
  killaK_dischargevars(fs, e);
  freeexp(fs, e);
  killaK_reserveregs(fs, 1);
  exp2reg(fs, e, fs->freereg - 1);
}


int killaK_exp2anyreg (killa_FuncState *fs, killa_expdesc *e) {
  killaK_dischargevars(fs, e);
  if (e->k == VNONRELOC) {
    if (!hasjumps(e)) return e->u.info;  /* exp is already in a register */
    if (e->u.info >= fs->nactvar) {  /* reg. is not a local? */
      exp2reg(fs, e, e->u.info);  /* put value on it */
      return e->u.info;
    }
  }
  killaK_exp2nextreg(fs, e);  /* default */
  return e->u.info;
}


void killaK_exp2reg (killa_FuncState *fs, killa_expdesc *e, int reg) {
  killaK_dischargevars(fs, e);
  freeexp(fs, e);
  exp2reg(fs, e, reg);
}


void killaK_exp2anyregup (killa_FuncState *fs, killa_expdesc *e) {
  if (e->k != VUPVAL || hasjumps(e))
    killaK_exp2anyreg(fs, e);
}


void killaK_exp2val (killa_FuncState *fs, killa_expdesc *e) {
  if (hasjumps(e))
    killaK_exp2anyreg(fs, e);
  else
    killaK_dischargevars(fs, e);
}


int killaK_exp2RK (killa_FuncState *fs, killa_expdesc *e) {
  killaK_exp2val(fs, e);
  switch (e->k) {
    case VTRUE:
    case VFALSE:
    case VNULL: {
      if (fs->nk <= KILLA_MAXINDEXRK) {  /* constant fits in RK operand? */
        e->u.info = (e->k == VNULL) ? nilK(fs) : boolK(fs, (e->k == VTRUE));
        e->k = VK;
        return KILLA_RKASK(e->u.info);
      }
      else break;
    }
    case VKNUM: {
      e->u.info = killaK_numberK(fs, e->u.nval);
      e->k = VK;
      /* go through */
    }
    case VK: {
      if (e->u.info <= KILLA_MAXINDEXRK)  /* constant fits in argC? */
        return KILLA_RKASK(e->u.info);
      else break;
    }
    default: break;
  }
  /* not a constant in the right range: put it in a register */
  return killaK_exp2anyreg(fs, e);
}


void killaK_storevar (killa_FuncState *fs, killa_expdesc *var, killa_expdesc *ex) {
  switch (var->k) {
    case VLOCAL: {
      freeexp(fs, ex);
      exp2reg(fs, ex, var->u.info);
      return;
    }
    case VUPVAL: {
      int e = killaK_exp2anyreg(fs, ex);
      killaK_codeABC(fs, OP_SETUPVAL, e, var->u.info, 0);
      break;
    }
    case VINDEXED: {
      killa_OpCode op = (var->u.ind.vt == VLOCAL) ? OP_SETTABLE : OP_SETTABUP;
      int e = killaK_exp2RK(fs, ex);
      killaK_codeABC(fs, op, var->u.ind.t, var->u.ind.idx, e);
      break;
    }
    default: {
      killa_assert(0);  /* invalid var kind to store */
      break;
    }
  }
  freeexp(fs, ex);
}


void killaK_self (killa_FuncState *fs, killa_expdesc *e, killa_expdesc *key) {
  int ereg;
  killaK_exp2anyreg(fs, e);
  ereg = e->u.info;  /* register where 'e' was placed */
  freeexp(fs, e);
  e->u.info = fs->freereg;  /* base register for op_self */
  e->k = VNONRELOC;
  killaK_reserveregs(fs, 2);  /* function and 'self' produced by op_self */
  killaK_codeABC(fs, OP_SELF, e->u.info, ereg, killaK_exp2RK(fs, key));
  freeexp(fs, key);
}


static void invertjump (killa_FuncState *fs, killa_expdesc *e) {
  killa_Instruction *pc = getjumpcontrol(fs, e->u.info);
  killa_assert(killa_testTMode(KILLA_GET_OPCODE(*pc)) && KILLA_GET_OPCODE(*pc) != OP_TESTSET &&
                                           KILLA_GET_OPCODE(*pc) != OP_TEST);
  KILLA_SETARG_A(*pc, !(KILLA_GETARG_A(*pc)));
}


static int jumponcond (killa_FuncState *fs, killa_expdesc *e, int cond) {
  if (e->k == VRELOCABLE) {
    killa_Instruction ie = killaK_getcode(fs, e);
    if (KILLA_GET_OPCODE(ie) == OP_NOT) {
      fs->pc--;  /* remove previous OP_NOT */
      return condjump(fs, OP_TEST, KILLA_GETARG_B(ie), 0, !cond);
    }
    /* else go through */
  }
  discharge2anyreg(fs, e);
  freeexp(fs, e);
  return condjump(fs, OP_TESTSET, KILLA_NO_REG, e->u.info, cond);
}


void killaK_goiftrue (killa_FuncState *fs, killa_expdesc *e) {
  int pc;  /* pc of last jump */
  killaK_dischargevars(fs, e);
  switch (e->k) {
    case VJMP: {
      invertjump(fs, e);
      pc = e->u.info;
      break;
    }
    case VK: case VKNUM: case VTRUE: {
      pc = KILLA_NO_JUMP;  /* always true; do nothing */
      break;
    }
    default: {
      pc = jumponcond(fs, e, 0);
      break;
    }
  }
  killaK_concat(fs, &e->f, pc);  /* insert last jump in `f' list */
  killaK_patchtohere(fs, e->t);
  e->t = KILLA_NO_JUMP;
}


void killaK_goiffalse (killa_FuncState *fs, killa_expdesc *e) {
  int pc;  /* pc of last jump */
  killaK_dischargevars(fs, e);
  switch (e->k) {
    case VJMP: {
      pc = e->u.info;
      break;
    }
    case VNULL: case VFALSE: {
      pc = KILLA_NO_JUMP;  /* always false; do nothing */
      break;
    }
    default: {
      pc = jumponcond(fs, e, 1);
      break;
    }
  }
  killaK_concat(fs, &e->t, pc);  /* insert last jump in `t' list */
  killaK_patchtohere(fs, e->f);
  e->f = KILLA_NO_JUMP;
}


static void codenot (killa_FuncState *fs, killa_expdesc *e) {
  killaK_dischargevars(fs, e);
  switch (e->k) {
    case VNULL: case VFALSE: {
      e->k = VTRUE;
      break;
    }
    case VK: case VKNUM: case VTRUE: {
      e->k = VFALSE;
      break;
    }
    case VJMP: {
      invertjump(fs, e);
      break;
    }
    case VRELOCABLE:
    case VNONRELOC: {
      discharge2anyreg(fs, e);
      freeexp(fs, e);
      e->u.info = killaK_codeABC(fs, OP_NOT, 0, e->u.info, 0);
      e->k = VRELOCABLE;
      break;
    }
    default: {
      killa_assert(0);  /* cannot happen */
      break;
    }
  }
  /* interchange true and false lists */
  { int temp = e->f; e->f = e->t; e->t = temp; }
  removevalues(fs, e->f);
  removevalues(fs, e->t);
}


void killaK_indexed (killa_FuncState *fs, killa_expdesc *t, killa_expdesc *k) {
  killa_assert(!hasjumps(t));
  t->u.ind.t = t->u.info;
  t->u.ind.idx = killaK_exp2RK(fs, k);
  t->u.ind.vt = (t->k == VUPVAL) ? VUPVAL
                                 : killa_check_exp(killa_vkisinreg(t->k), VLOCAL);
  t->k = VINDEXED;
}


static int constfolding (killa_OpCode op, killa_expdesc *e1, killa_expdesc *e2) {
  killa_Number r;
  if (!isnumeral(e1) || !isnumeral(e2)) return 0;
  if ((op == OP_DIV || op == OP_MOD) && e2->u.nval == 0)
    return 0;  /* do not attempt to divide by 0 */
  r = killaO_arith(op - OP_ADD + KILLA_OPADD, e1->u.nval, e2->u.nval);
  e1->u.nval = r;
  return 1;
}


static void codearith (killa_FuncState *fs, killa_OpCode op,
                       killa_expdesc *e1, killa_expdesc *e2, int line) {
  if (constfolding(op, e1, e2))
    return;
  else {
    int o2 = (op != OP_UNM && op != OP_LEN) ? killaK_exp2RK(fs, e2) : 0;
    int o1 = killaK_exp2RK(fs, e1);
    if (o1 > o2) {
      freeexp(fs, e1);
      freeexp(fs, e2);
    }
    else {
      freeexp(fs, e2);
      freeexp(fs, e1);
    }
    e1->u.info = killaK_codeABC(fs, op, 0, o1, o2);
    e1->k = VRELOCABLE;
    killaK_fixline(fs, line);
  }
}


static void codecomp (killa_FuncState *fs, killa_OpCode op, int cond, killa_expdesc *e1,
                                                          killa_expdesc *e2) {
  int o1 = killaK_exp2RK(fs, e1);
  int o2 = killaK_exp2RK(fs, e2);
  freeexp(fs, e2);
  freeexp(fs, e1);
  if (cond == 0 && op != OP_EQ) {
    int temp;  /* exchange args to replace by `<' or `<=' */
    temp = o1; o1 = o2; o2 = temp;  /* o1 <==> o2 */
    cond = 1;
  }
  e1->u.info = condjump(fs, op, cond, o1, o2);
  e1->k = VJMP;
}


void killaK_prefix (killa_FuncState *fs, killaK_UnOpr op, killa_expdesc *e, int line) {
  killa_expdesc e2;
  e2.t = e2.f = KILLA_NO_JUMP; e2.k = VKNUM; e2.u.nval = 0;
  switch (op) {
    case OPR_MINUS: {
      if (isnumeral(e))  /* minus constant? */
        e->u.nval = killai_numunm(NULL, e->u.nval);  /* fold it */
      else {
        killaK_exp2anyreg(fs, e);
        codearith(fs, OP_UNM, e, &e2, line);
      }
      break;
    }
    case OPR_NOT: codenot(fs, e); break;
    case OPR_LEN: {
      killaK_exp2anyreg(fs, e);  /* cannot operate on constants */
      codearith(fs, OP_LEN, e, &e2, line);
      break;
    }
    default: killa_assert(0);
  }
}


void killaK_infix (killa_FuncState *fs, killaK_BinOpr op, killa_expdesc *v) {
  switch (op) {
    case OPR_AND: {
      killaK_goiftrue(fs, v);
      break;
    }
    case OPR_OR: {
      killaK_goiffalse(fs, v);
      break;
    }
    case OPR_CONCAT: {
      killaK_exp2nextreg(fs, v);  /* operand must be on the `stack' */
      break;
    }
    case OPR_ADD: case OPR_SUB: case OPR_MUL: case OPR_DIV:
    case OPR_MOD: case OPR_POW: {
      if (!isnumeral(v)) killaK_exp2RK(fs, v);
      break;
    }
    default: {
      killaK_exp2RK(fs, v);
      break;
    }
  }
}


void killaK_posfix (killa_FuncState *fs, killaK_BinOpr op,
                  killa_expdesc *e1, killa_expdesc *e2, int line) {
  switch (op) {
    case OPR_AND: {
      killa_assert(e1->t == KILLA_NO_JUMP);  /* list must be closed */
      killaK_dischargevars(fs, e2);
      killaK_concat(fs, &e2->f, e1->f);
      *e1 = *e2;
      break;
    }
    case OPR_OR: {
      killa_assert(e1->f == KILLA_NO_JUMP);  /* list must be closed */
      killaK_dischargevars(fs, e2);
      killaK_concat(fs, &e2->t, e1->t);
      *e1 = *e2;
      break;
    }
    case OPR_CONCAT: {
      killaK_exp2val(fs, e2);
      if (e2->k == VRELOCABLE && KILLA_GET_OPCODE(killaK_getcode(fs, e2)) == OP_CONCAT) {
        killa_assert(e1->u.info == KILLA_GETARG_B(killaK_getcode(fs, e2))-1);
        freeexp(fs, e1);
        KILLA_SETARG_B(killaK_getcode(fs, e2), e1->u.info);
        e1->k = VRELOCABLE; e1->u.info = e2->u.info;
      }
      else {
        killaK_exp2nextreg(fs, e2);  /* operand must be on the 'stack' */
        codearith(fs, OP_CONCAT, e1, e2, line);
      }
      break;
    }
    case OPR_ADD: case OPR_SUB: case OPR_MUL: case OPR_DIV:
    case OPR_MOD: case OPR_POW: {
      codearith(fs, killa_cast(killa_OpCode, op - OPR_ADD + OP_ADD), e1, e2, line);
      break;
    }
    case OPR_EQ: case OPR_LT: case OPR_LE: {
      codecomp(fs, killa_cast(killa_OpCode, op - OPR_EQ + OP_EQ), 1, e1, e2);
      break;
    }
    case OPR_NE: case OPR_GT: case OPR_GE: {
      codecomp(fs, killa_cast(killa_OpCode, op - OPR_NE + OP_EQ), 0, e1, e2);
      break;
    }
    default: killa_assert(0);
  }
}


void killaK_fixline (killa_FuncState *fs, int line) {
  fs->f->lineinfo[fs->pc - 1] = line;
}


void killaK_setlist (killa_FuncState *fs, int base, int nelems, int tostore) {
  int c =  (nelems - 1)/KILLA_LFIELDS_PER_FLUSH + 1;
  int b = (tostore == KILLA_MULTRET) ? 0 : tostore;
  killa_assert(tostore != 0);
  if (c <= KILLA_MAXARG_C)
    killaK_codeABC(fs, OP_SETLIST, base, b, c);
  else if (c <= KILLA_MAXARG_Ax) {
    killaK_codeABC(fs, OP_SETLIST, base, b, 0);
    codeextraarg(fs, c);
  }
  else
    killaX_syntaxerror(fs->ls, "constructor too long");
  fs->freereg = base + 1;  /* free registers with list values */
}

