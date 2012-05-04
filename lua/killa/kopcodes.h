/* ========================================================================== */
/*   Opcodes for Killa virtual machine                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KOPCODES_H_
#define KOPCODES_H_

#include "klimits.h"


/*===========================================================================
  We assume that instructions are unsigned numbers.
  All instructions have an opcode in the first 6 bits.
  Instructions can have the following fields:
	`A' : 8 bits
	`B' : 9 bits
	`C' : 9 bits
	'Ax' : 26 bits ('A', 'B', and 'C' together)
	`Bx' : 18 bits (`B' and `C' together)
	`sBx' : signed Bx

  A signed argument is represented in excess K; that is, the number
  value is the unsigned value minus K. K is exactly the maximum value
  for that argument (so that -max is represented by 0, and +max is
  represented by 2*max), which is half the maximum for the corresponding
  unsigned argument.
===========================================================================*/


enum killa_OpMode {iABC, iABx, iAsBx, iAx};  /* basic instruction format */


/*
** size and position of opcode arguments.
*/
#define KILLA_SIZE_C    9
#define KILLA_SIZE_B    9
#define KILLA_SIZE_Bx   (KILLA_SIZE_C + KILLA_SIZE_B)
#define KILLA_SIZE_A    8
#define KILLA_SIZE_Ax   (KILLA_SIZE_C + KILLA_SIZE_B + KILLA_SIZE_A)

#define KILLA_SIZE_OP   6

#define KILLA_POS_OP    0
#define KILLA_POS_A     (KILLA_POS_OP + KILLA_SIZE_OP)
#define KILLA_POS_C     (KILLA_POS_A + KILLA_SIZE_A)
#define KILLA_POS_B     (KILLA_POS_C + KILLA_SIZE_C)
#define KILLA_POS_Bx    KILLA_POS_C
#define KILLA_POS_Ax    KILLA_POS_A


/*
** limits for opcode arguments.
** we use (signed) int to manipulate most arguments,
** so they must fit in KILLAI_BITSINT-1 bits (-1 for sign)
*/
#if KILLA_SIZE_Bx < KILLAI_BITSINT-1
#define KILLA_MAXARG_Bx     ((1<<KILLA_SIZE_Bx)-1)
#define KILLA_MAXARG_sBx    (KILLA_MAXARG_Bx>>1)         /* `sBx' is signed */
#else
#define KILLA_MAXARG_Bx     KILLA_MAX_INT
#define KILLA_MAXARG_sBx    KILLA_MAX_INT
#endif

#if KILLA_SIZE_Ax < KILLAI_BITSINT-1
#define KILLA_MAXARG_Ax     ((1<<KILLA_SIZE_Ax)-1)
#else
#define KILLA_MAXARG_Ax     KILLA_MAX_INT
#endif


#define KILLA_MAXARG_A  ((1<<KILLA_SIZE_A)-1)
#define KILLA_MAXARG_B  ((1<<KILLA_SIZE_B)-1)
#define KILLA_MAXARG_C  ((1<<KILLA_SIZE_C)-1)


/* creates a mask with `n' 1 bits at position `p' */
#define KILLA_MASK1(n,p)    ((~((~(killa_Instruction)0)<<(n)))<<(p))

/* creates a mask with `n' 0 bits at position `p' */
#define KILLA_MASK0(n,p)    (~KILLA_MASK1(n,p))

/*
** the following macros help to manipulate instructions
*/

#define KILLA_GET_OPCODE(i) (killa_cast(killa_OpCode, ((i)>>KILLA_POS_OP) & KILLA_MASK1(KILLA_SIZE_OP,0)))
#define KILLA_SET_OPCODE(i,o)	((i) = (((i)&KILLA_MASK0(KILLA_SIZE_OP,KILLA_POS_OP)) | \
        ((killa_cast(killa_Instruction, o)<<KILLA_POS_OP)&KILLA_MASK1(KILLA_SIZE_OP,KILLA_POS_OP))))

#define killa_getarg(i,pos,size)    (killa_cast(int, ((i)>>pos) & KILLA_MASK1(size,0)))
#define killa_setarg(i,v,pos,size)	((i) = (((i)&KILLA_MASK0(size,pos)) | \
                ((killa_cast(killa_Instruction, v)<<pos)&KILLA_MASK1(size,pos))))

#define KILLA_GETARG_A(i)   killa_getarg(i, KILLA_POS_A, KILLA_SIZE_A)
#define KILLA_SETARG_A(i,v) killa_setarg(i, v, KILLA_POS_A, KILLA_SIZE_A)

#define KILLA_GETARG_B(i)   killa_getarg(i, KILLA_POS_B, KILLA_SIZE_B)
#define KILLA_SETARG_B(i,v) killa_setarg(i, v, KILLA_POS_B, KILLA_SIZE_B)

#define KILLA_GETARG_C(i)   killa_getarg(i, KILLA_POS_C, KILLA_SIZE_C)
#define KILLA_SETARG_C(i,v) killa_setarg(i, v, KILLA_POS_C, KILLA_SIZE_C)

#define KILLA_GETARG_Bx(i)      killa_getarg(i, KILLA_POS_Bx, KILLA_SIZE_Bx)
#define KILLA_SETARG_Bx(i,v)    killa_setarg(i, v, KILLA_POS_Bx, KILLA_SIZE_Bx)

#define KILLA_GETARG_Ax(i)      killa_getarg(i, KILLA_POS_Ax, KILLA_SIZE_Ax)
#define KILLA_SETARG_Ax(i,v)    killa_setarg(i, v, KILLA_POS_Ax, KILLA_SIZE_Ax)

#define KILLA_GETARG_sBx(i)     (KILLA_GETARG_Bx(i)-KILLA_MAXARG_sBx)
#define KILLA_SETARG_sBx(i,b)   KILLA_SETARG_Bx((i),killa_cast(unsigned int, (b)+KILLA_MAXARG_sBx))


#define KILLA_CREATE_ABC(o,a,b,c)   ((killa_cast(killa_Instruction, o)<<KILLA_POS_OP) \
			| (killa_cast(killa_Instruction, a)<<KILLA_POS_A) \
			| (killa_cast(killa_Instruction, b)<<KILLA_POS_B) \
			| (killa_cast(killa_Instruction, c)<<KILLA_POS_C))

#define KILLA_CREATE_ABx(o,a,bc)    ((killa_cast(killa_Instruction, o)<<KILLA_POS_OP) \
			| (killa_cast(killa_Instruction, a)<<KILLA_POS_A) \
			| (killa_cast(killa_Instruction, bc)<<KILLA_POS_Bx))

#define KILLA_CREATE_Ax(o,a)        ((killa_cast(killa_Instruction, o)<<KILLA_POS_OP) \
			| (killa_cast(killa_Instruction, a)<<KILLA_POS_Ax))


/*
** Macros to operate RK indices
*/

/* this bit 1 means constant (0 means register) */
#define KILLA_BITRK     (1 << (KILLA_SIZE_B - 1))

/* test whether value is a constant */
#define KILLA_ISK(x)    ((x) & KILLA_BITRK)

/* gets the index of the constant */
#define KILLA_INDEXK(r) ((int)(r) & ~KILLA_BITRK)

#define KILLA_MAXINDEXRK    (KILLA_BITRK - 1)

/* code a constant index as a RK value */
#define KILLA_RKASK(x)  ((x) | KILLA_BITRK)


/*
** invalid register that fits in 8 bits
*/
#define KILLA_NO_REG    KILLA_MAXARG_A


/*
** R(x) - register
** Kst(x) - constant (in constant table)
** RK(x) == if KILLA_ISK(x) then Kst(KILLA_INDEXK(x)) else R(x)
*/


/*
** grep "ORDER OP" if you change these enums
*/

typedef enum {
/*----------------------------------------------------------------------
name		args	description
------------------------------------------------------------------------*/
OP_MOVE,/*	A B	R(A) := R(B)					*/
OP_LOADK,/*	A Bx	R(A) := Kst(Bx)					*/
OP_LOADKX,/*	A 	R(A) := Kst(extra arg)				*/
OP_LOADBOOL,/*	A B C	R(A) := (Bool)B; if (C) pc++			*/
OP_LOADNIL,/*	A B	R(A), R(A+1), ..., R(A+B) := nil		*/
OP_GETUPVAL,/*	A B	R(A) := UpValue[B]				*/

OP_GETTABUP,/*	A B C	R(A) := UpValue[B][RK(C)]			*/
OP_GETTABLE,/*	A B C	R(A) := R(B)[RK(C)]				*/

OP_SETTABUP,/*	A B C	UpValue[A][RK(B)] := RK(C)			*/
OP_SETUPVAL,/*	A B	UpValue[B] := R(A)				*/
OP_SETTABLE,/*	A B C	R(A)[RK(B)] := RK(C)				*/

OP_NEWTABLE,/*	A B C	R(A) := {} (size = B,C)				*/

OP_SELF,/*	A B C	R(A+1) := R(B); R(A) := R(B)[RK(C)]		*/

OP_ADD,/*	A B C	R(A) := RK(B) + RK(C)				*/
OP_SUB,/*	A B C	R(A) := RK(B) - RK(C)				*/
OP_MUL,/*	A B C	R(A) := RK(B) * RK(C)				*/
OP_DIV,/*	A B C	R(A) := RK(B) / RK(C)				*/
OP_MOD,/*	A B C	R(A) := RK(B) % RK(C)				*/
OP_POW,/*	A B C	R(A) := RK(B) ^ RK(C)				*/
OP_UNM,/*	A B	R(A) := -R(B)					*/
OP_NOT,/*	A B	R(A) := not R(B)				*/
OP_LEN,/*	A B	R(A) := length of R(B)				*/

OP_CONCAT,/*	A B C	R(A) := R(B).. ... ..R(C)			*/

OP_JMP,/*	A sBx	pc+=sBx; if (A) close all upvalues >= R(A) + 1	*/
OP_EQ,/*	A B C	if ((RK(B) == RK(C)) ~= A) then pc++		*/
OP_LT,/*	A B C	if ((RK(B) <  RK(C)) ~= A) then pc++		*/
OP_LE,/*	A B C	if ((RK(B) <= RK(C)) ~= A) then pc++		*/

OP_TEST,/*	A C	if not (R(A) <=> C) then pc++			*/
OP_TESTSET,/*	A B C	if (R(B) <=> C) then R(A) := R(B) else pc++	*/

OP_CALL,/*	A B C	R(A), ... ,R(A+C-2) := R(A)(R(A+1), ... ,R(A+B-1)) */
OP_TAILCALL,/*	A B C	return R(A)(R(A+1), ... ,R(A+B-1))		*/
OP_RETURN,/*	A B	return R(A), ... ,R(A+B-2)	(see note)	*/

OP_FORLOOP,/*	A sBx	R(A)+=R(A+2);
			if R(A) <?= R(A+1) then { pc+=sBx; R(A+3)=R(A) }*/
OP_FORPREP,/*	A sBx	R(A)-=R(A+2); pc+=sBx				*/

OP_TFORCALL,/*	A C	R(A+3), ... ,R(A+2+C) := R(A)(R(A+1), R(A+2));	*/
OP_TFORLOOP,/*	A sBx	if R(A+1) ~= nil then { R(A)=R(A+1); pc += sBx }*/

OP_SETLIST,/*	A B C	R(A)[(C-1)*FPF+i] := R(A+i), 1 <= i <= B	*/

OP_CLOSURE,/*	A Bx	R(A) := closure(KPROTO[Bx])			*/

OP_VARARG,/*	A B	R(A), R(A+1), ..., R(A+B-2) = vararg		*/

OP_EXTRAARG/*	Ax	extra (larger) argument for previous opcode	*/
} killa_OpCode;


#define KILLA_NUM_OPCODES   (killa_cast(int, OP_EXTRAARG) + 1)



/*===========================================================================
  Notes:
  (*) In OP_CALL, if (B == 0) then B = top. If (C == 0), then `top' is
  set to last_result+1, so next open instruction (OP_CALL, OP_RETURN,
  OP_SETLIST) may use `top'.

  (*) In OP_VARARG, if (B == 0) then use actual number of varargs and
  set top (like in OP_CALL with C == 0).

  (*) In OP_RETURN, if (B == 0) then return up to `top'.

  (*) In OP_SETLIST, if (B == 0) then B = `top'; if (C == 0) then next
  'instruction' is EXTRAARG(real C).

  (*) In OP_LOADKX, the next 'instruction' is always EXTRAARG.

  (*) For comparisons, A specifies what condition the test should accept
  (true or false).

  (*) All `skips' (pc++) assume that next instruction is a jump.

===========================================================================*/


/*
** masks for instruction properties. The format is:
** bits 0-1: op mode
** bits 2-3: C arg mode
** bits 4-5: B arg mode
** bit 6: instruction set register A
** bit 7: operator is a test (next instruction must be a jump)
*/

enum killa_OpArgMask {
  OpArgN,  /* argument is not used */
  OpArgU,  /* argument is used */
  OpArgR,  /* argument is a register or a jump offset */
  OpArgK   /* argument is a constant or register/constant */
};

KILLAI_DDEC const killa_ubyte killaP_opmodes[KILLA_NUM_OPCODES];

#define killa_getOpMode(m)  (killa_cast(enum killa_OpMode, killaP_opmodes[m] & 3))
#define killa_getBMode(m)   (killa_cast(enum killa_OpArgMask, (killaP_opmodes[m] >> 4) & 3))
#define killa_getCMode(m)   (killa_cast(enum killa_OpArgMask, (killaP_opmodes[m] >> 2) & 3))
#define killa_testAMode(m)  (killaP_opmodes[m] & (1 << 6))
#define killa_testTMode(m)  (killaP_opmodes[m] & (1 << 7))


KILLAI_DDEC const char *const killaP_opnames[KILLA_NUM_OPCODES+1];  /* opcode names */


/* number of list items to accumulate before a SETLIST instruction */
#define KILLA_LFIELDS_PER_FLUSH	50


#endif
