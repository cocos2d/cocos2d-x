/* ========================================================================== */
/*   Code generator for Killa                                                 */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KCODE_H_
#define KCODE_H_

#include "klex.h"
#include "kobject.h"
#include "kopcodes.h"
#include "kparser.h"


/*
** Marks the end of a patch list. It is an invalid value both as an absolute
** address, and as a list link (would link an element to itself).
*/
#define KILLA_NO_JUMP (-1)


/*
** grep "ORDER OPR" if you change these enums  (ORDER OP)
*/
typedef enum killaK_BinOpr {
  OPR_ADD, OPR_SUB, OPR_MUL, OPR_DIV, OPR_MOD, OPR_POW,
  OPR_CONCAT,
  OPR_EQ, OPR_LT, OPR_LE,
  OPR_NE, OPR_GT, OPR_GE,
  OPR_AND, OPR_OR,
  OPR_NOBINOPR
} killaK_BinOpr;


typedef enum killaK_UnOpr { OPR_MINUS, OPR_NOT, OPR_LEN, OPR_NOUNOPR } killaK_UnOpr;


#define killaK_getcode(fs,e)	((fs)->f->code[(e)->u.info])

#define killaK_codeAsBx(fs,o,A,sBx)	killaK_codeABx(fs,o,A,(sBx)+KILLA_MAXARG_sBx)

#define killaK_setmultret(fs,e)	killaK_setreturns(fs, e, KILLA_MULTRET)

#define killaK_jumpto(fs,t)	killaK_patchlist(fs, killaK_jump(fs), t)

KILLAI_FUNC int  killaK_codeABx (killa_FuncState *fs, killa_OpCode o, int A, unsigned int Bx);
KILLAI_FUNC int  killaK_codeABC (killa_FuncState *fs, killa_OpCode o, int A, int B, int C);
KILLAI_FUNC int  killaK_codek (killa_FuncState *fs, int reg, int k);
KILLAI_FUNC void killaK_fixline (killa_FuncState *fs, int line);
KILLAI_FUNC void killaK_nil (killa_FuncState *fs, int from, int n);
KILLAI_FUNC void killaK_reserveregs (killa_FuncState *fs, int n);
KILLAI_FUNC void killaK_checkstack (killa_FuncState *fs, int n);
KILLAI_FUNC int  killaK_stringK (killa_FuncState *fs, killa_TString *s);
KILLAI_FUNC int  killaK_numberK (killa_FuncState *fs, killa_Number r);
KILLAI_FUNC void killaK_dischargevars (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC int  killaK_exp2anyreg (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_exp2reg (killa_FuncState *fs, killa_expdesc *e, int reg);
KILLAI_FUNC void killaK_exp2anyregup (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_exp2nextreg (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_exp2val (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC int  killaK_exp2RK (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_self (killa_FuncState *fs, killa_expdesc *e, killa_expdesc *key);
KILLAI_FUNC void killaK_indexed (killa_FuncState *fs, killa_expdesc *t, killa_expdesc *k);
KILLAI_FUNC void killaK_goiftrue (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_goiffalse (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC void killaK_storevar (killa_FuncState *fs, killa_expdesc *var, killa_expdesc *e);
KILLAI_FUNC void killaK_setreturns (killa_FuncState *fs, killa_expdesc *e, int nresults);
KILLAI_FUNC void killaK_setoneret (killa_FuncState *fs, killa_expdesc *e);
KILLAI_FUNC int  killaK_jump (killa_FuncState *fs);
KILLAI_FUNC void killaK_ret (killa_FuncState *fs, int first, int nret);
KILLAI_FUNC void killaK_patchlist (killa_FuncState *fs, int list, int target);
KILLAI_FUNC void killaK_patchtohere (killa_FuncState *fs, int list);
KILLAI_FUNC void killaK_patchclose (killa_FuncState *fs, int list, int level);
KILLAI_FUNC void killaK_concat (killa_FuncState *fs, int *l1, int l2);
KILLAI_FUNC int  killaK_getlabel (killa_FuncState *fs);
KILLAI_FUNC void killaK_prefix (killa_FuncState *fs, killaK_UnOpr op, killa_expdesc *v, int line);
KILLAI_FUNC void killaK_infix (killa_FuncState *fs, killaK_BinOpr op, killa_expdesc *v);
KILLAI_FUNC void killaK_posfix (killa_FuncState *fs, killaK_BinOpr op, killa_expdesc *v1,
                                killa_expdesc *v2, int line);
KILLAI_FUNC void killaK_setlist (killa_FuncState *fs, int base, int nelems, int tostore);


#endif
