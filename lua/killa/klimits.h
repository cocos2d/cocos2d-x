/* ========================================================================== */
/*   Limits, basic types, and some other installation-dependent definitions   */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KLIMITS_H_
#define KLIMITS_H_


#include <limits.h>
#include <stddef.h>


#include "killa.h"


typedef unsigned KILLA_INT32 killa_uint32;

typedef KILLAI_UMEM killa_umem;

typedef KILLAI_MEM killa_mem;



/* chars used as small naturals (so that `char' is reserved for characters) */
typedef unsigned char killa_ubyte;


#define KILLA_MAX_SIZET	((size_t)(~(size_t)0)-2)

#define KILLA_MAX_LUMEM	((killa_umem)(~(killa_umem)0)-2)


#define KILLA_MAX_INT (INT_MAX-2)  /* maximum value of an int (-2 for safety) */

/*
** conversion of pointer to integer
** this is for hashing only; there is no problem if the integer
** cannot hold the whole pointer value
*/
#define killa_IntPoint(p)  ((unsigned int)(killa_umem)(p))



/* type to ensure maximum alignment */
#if !defined(KILLAI_USER_ALIGNMENT_T)
#define KILLAI_USER_ALIGNMENT_T	union { double u; void *s; long l; }
#endif

typedef KILLAI_USER_ALIGNMENT_T killa_Umaxalign;


/* result of a `usual argument conversion' over killa_Number */
typedef KILLAI_UACNUMBER killa_uacNumber;


/* internal assertions for in-house debugging */
#if defined(killa_assert)
#define killa_check_exp(c,e)    (killa_assert(c), (e))
/* to avoid problems with conditions too long */
#define killa_longassert(c)	{ if (!(c)) killa_assert(0); }
#else
#define killa_assert(c)         ((void)0)
#define killa_check_exp(c,e)    (e)
#define killa_longassert(c)     ((void)0)
#endif

/*
** assertion for checking API calls
*/
#if !defined(killai_apicheck)

#if defined(KILLA_USE_APICHECK)
#include <assert.h>
#define killai_apicheck(L,e)    assert(e)
#else
#define killai_apicheck(L,e)    killa_assert(e)
#endif

#endif

#define killa_api_check(l,e,msg)    killai_apicheck(l,(e) && msg)


#if !defined(KILLA_UNUSED)
#define KILLA_UNUSED(x) ((void)(x))	/* to avoid warnings */
#endif


#define killa_cast(t, exp)  ((t)(exp))

#define killa_cast_byte(i)	killa_cast(killa_ubyte, (i))
#define killa_cast_num(i)	killa_cast(killa_Number, (i))
#define killa_cast_int(i)	killa_cast(int, (i))
#define killa_cast_uchar(i)	killa_cast(unsigned char, (i))


/*
** non-return type
*/
#if defined(__GNUC__)
#define killa_noret		void __attribute__((noreturn))
#elif defined(_MSC_VER)
#define killa_noret		void __declspec(noreturn)
#else
#define killa_noret		void
#endif



/*
** maximum depth for nested C calls and syntactical nested non-terminals
** in a program. (killa_Value must fit in an unsigned short int.)
*/
#if !defined(KILLAI_MAXCCALLS)
#define KILLAI_MAXCCALLS    200
#endif

/*
** maximum number of upvalues in a closure (both C and Killa). (killa_Value
** must fit in an unsigned char.)
*/
#define KILLA_MAXUPVAL  UCHAR_MAX


/*
** type for virtual-machine instructions
** must be an unsigned with (at least) 4 bytes (see details in lopcodes.h)
*/
typedef killa_uint32 killa_Instruction;



/* maximum stack for a Killa function */
#define KILLA_MAXSTACK  250



/* minimum size for the string table (must be power of 2) */
#if !defined(KILLA_MINSTRTABSIZE)
#define KILLA_MINSTRTABSIZE	32
#endif


/* minimum size for string buffer */
#if !defined(KILLA_MINBUFFER)
#define KILLA_MINBUFFER	32
#endif


#if !defined(killa_lock)
#define killa_lock(L)   ((void) 0)
#define killa_unlock(L) ((void) 0)
#endif

#if !defined(killai_threadyield)
#define killai_threadyield(L)   {killa_unlock(L); killa_lock(L);}
#endif


/*
** these macros allow user-specific actions on threads when you defined
** KILLAI_EXTRASPACE and need to do something extra when a thread is
** created/deleted/resumed/yielded.
*/
#if !defined(killai_userstateopen)
#define killai_userstateopen(L)         ((void)L)
#endif

#if !defined(killai_userstateclose)
#define killai_userstateclose(L)        ((void)L)
#endif

#if !defined(killai_userstatethread)
#define killai_userstatethread(L,L1)    ((void)L)
#endif

#if !defined(killai_userstatefree)
#define killai_userstatefree(L,L1)      ((void)L)
#endif

#if !defined(killai_userstateresume)
#define killai_userstateresume(L,n)     ((void)L)
#endif

#if !defined(killai_userstateyield)
#define killai_userstateyield(L,n)      ((void)L)
#endif

/*
** killa_number2int is a macro to convert killa_Number to int.
** killa_number2integer is a macro to convert killa_Number to killa_Integer.
** killa_number2unsigned is a macro to convert a killa_Number to a killa_Unsigned.
** killa_unsigned2number is a macro to convert a killa_Unsigned to a killa_Number.
** killai_hashnum is a macro to hash a killa_Number value into an integer.
** The hash must be deterministic and give reasonable values for
** both small and large values (outside the range of integers).
*/

#if defined(KILLA_MS_ASMTRICK)	/* { */
/* trick with Microsoft assembler for X86 */

#define killa_number2int(i,n)  __asm {__asm fld n   __asm fistp i}
#define killa_number2integer(i,n)		killa_number2int(i, n)
#define killa_number2unsigned(i,n)  \
  {__int64 l; __asm {__asm fld n   __asm fistp l} i = (unsigned int)l;}


#elif defined(KILLA_IEEE754TRICK)		/* }{ */
/* the next trick should work on any machine using IEEE754 with
   a 32-bit integer type */

union killai_Cast { double l_d; KILLA_INT32 l_p[2]; };

#if !defined(KILLA_IEEEENDIAN)	/* { */
#define KILLAI_EXTRAIEEE	\
  static const union killai_Cast ieeeendian = {-(33.0 + 6755399441055744.0)};
#define KILLA_IEEEENDIAN		(ieeeendian.l_p[1] == 33)
#else
#define KILLAI_EXTRAIEEE		/* empty */
#endif				/* } */

#define killa_number2int32(i,n,t) \
  { KILLAI_EXTRAIEEE \
    volatile union killai_Cast u; u.l_d = (n) + 6755399441055744.0; \
    (i) = (t)u.l_p[KILLA_IEEEENDIAN]; }

#define killai_hashnum(i,n)  \
  { volatile union killai_Cast u; u.l_d = (n) + 1.0;  /* avoid -0 */ \
    (i) = u.l_p[0]; (i) += u.l_p[1]; }  /* add double bits for his hash */

#define killa_number2int(i,n)       killa_number2int32(i, n, int)
#define killa_number2integer(i,n)   killa_number2int32(i, n, killa_Integer)
#define killa_number2unsigned(i,n)  killa_number2int32(i, n, killa_Unsigned)

#endif				/* } */


/* the following definitions always work, but may be slow */

#if !defined(killa_number2int)
#define killa_number2int(i,n)	((i)=(int)(n))
#endif

#if !defined(killa_number2integer)
#define killa_number2integer(i,n)	((i)=(killa_Integer)(n))
#endif

#if !defined(killa_number2unsigned)	/* { */
/* the following definition assures proper modulo behavior */
#if defined(KILLA_NUMBER_DOUBLE)
#include <math.h>
#define KILLA_SUPUNSIGNED	((killa_Number)(~(killa_Unsigned)0) + 1)
#define killa_number2unsigned(i,n)  \
	((i)=(killa_Unsigned)((n) - floor((n)/KILLA_SUPUNSIGNED)*KILLA_SUPUNSIGNED))
#else
#define killa_number2unsigned(i,n)	((i)=(killa_Unsigned)(n))
#endif
#endif				/* } */


#if !defined(killa_unsigned2number)
/* on several machines, coercion from unsigned to double is slow,
   so it may be worth to avoid */
#define killa_unsigned2number(u)  \
    (((u) <= (killa_Unsigned)INT_MAX) ? (killa_Number)(int)(u) : (killa_Number)(u))
#endif



#if defined(KTABLE_C_) && !defined(killai_hashnum)

#include <float.h>
#include <math.h>

#define killai_hashnum(i,n) { int e;  \
  n = frexp(n, &e) * (killa_Number)(INT_MAX - DBL_MAX_EXP);  \
  killa_number2int(i, n); i += e; }

#endif



/*
** macro to control inclusion of some hard tests on stack reallocation
*/
#if !defined(KILLA_HARDSTACKTESTS)
#define killa_condmovestack(L)	((void)0)
#else
/* realloc stack keeping its size */
#define killa_condmovestack(L)	killaD_reallocstack((L), (L)->stacksize)
#endif

#if !defined(KILLA_HARDMEMTESTS)
#define killa_condchangemem(L)	killa_condmovestack(L)
#else
#define killa_condchangemem(L)  \
	((void)(!(KILLA_G(L)->gcrunning) || (killaC_fullgc(L, 0), 1)))
#endif

#endif
