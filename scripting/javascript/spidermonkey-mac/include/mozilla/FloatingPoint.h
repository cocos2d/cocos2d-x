/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Various predicates and operations on IEEE-754 floating point types. */

#ifndef mozilla_FloatingPoint_h_
#define mozilla_FloatingPoint_h_

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/StandardInteger.h"

/*
 * It's reasonable to ask why we have this header at all.  Don't isnan,
 * copysign, the built-in comparison operators, and the like solve these
 * problems?  Unfortunately, they don't.  We've found that various compilers
 * (MSVC, MSVC when compiling with PGO, and GCC on OS X, at least) miscompile
 * the standard methods in various situations, so we can't use them.  Some of
 * these compilers even have problems compiling seemingly reasonable bitwise
 * algorithms!  But with some care we've found algorithms that seem to not
 * trigger those compiler bugs.
 *
 * For the aforementioned reasons, be very wary of making changes to any of
 * these algorithms.  If you must make changes, keep a careful eye out for
 * compiler bustage, particularly PGO-specific bustage.
 *
 * Some users require that this file be C-compatible.  Unfortunately, this means
 * no mozilla namespace to contain everything, no detail namespace clarifying
 * MozDoublePun to be an internal data structure, and so on.
 */

/*
 * These implementations all assume |double| is a 64-bit double format number
 * type, compatible with the IEEE-754 standard.  C/C++ don't require this to be
 * the case.  But we required this in implementations of these algorithms that
 * preceded this header, so we shouldn't break anything if we continue doing so.
 */
MOZ_STATIC_ASSERT(sizeof(double) == sizeof(uint64_t), "double must be 64 bits");

/*
 * Constant expressions in C can't refer to consts, unfortunately, so #define
 * these rather than use |const uint64_t|.
 */
#define MOZ_DOUBLE_SIGN_BIT          0x8000000000000000ULL
#define MOZ_DOUBLE_EXPONENT_BITS     0x7ff0000000000000ULL
#define MOZ_DOUBLE_SIGNIFICAND_BITS  0x000fffffffffffffULL

#define MOZ_DOUBLE_EXPONENT_BIAS   1023
#define MOZ_DOUBLE_EXPONENT_SHIFT  52

MOZ_STATIC_ASSERT((MOZ_DOUBLE_SIGN_BIT & MOZ_DOUBLE_EXPONENT_BITS) == 0,
                  "sign bit doesn't overlap exponent bits");
MOZ_STATIC_ASSERT((MOZ_DOUBLE_SIGN_BIT & MOZ_DOUBLE_SIGNIFICAND_BITS) == 0,
                  "sign bit doesn't overlap significand bits");
MOZ_STATIC_ASSERT((MOZ_DOUBLE_EXPONENT_BITS & MOZ_DOUBLE_SIGNIFICAND_BITS) == 0,
                  "exponent bits don't overlap significand bits");

MOZ_STATIC_ASSERT((MOZ_DOUBLE_SIGN_BIT | MOZ_DOUBLE_EXPONENT_BITS | MOZ_DOUBLE_SIGNIFICAND_BITS)
                  == ~(uint64_t)0,
                  "all bits accounted for");

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This union is NOT a public data structure, and it is not to be used outside
 * this file!
 */
union MozDoublePun {
    /*
     * Every way to pun the bits of a double introduces an additional layer of
     * complexity, across a multitude of platforms, architectures, and ABIs.
     * Use *only* uint64_t to reduce complexity.  Don't add new punning here
     * without discussion!
     */
    uint64_t u;
    double d;
};

/** Determines whether a double is NaN. */
static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_NaN(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  /*
   * A double is NaN if all exponent bits are 1 and the significand contains at
   * least one non-zero bit.
   */
  return (pun.u & MOZ_DOUBLE_EXPONENT_BITS) == MOZ_DOUBLE_EXPONENT_BITS &&
         (pun.u & MOZ_DOUBLE_SIGNIFICAND_BITS) != 0;
}

/** Determines whether a double is +Infinity or -Infinity. */
static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_INFINITE(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  /* Infinities have all exponent bits set to 1 and an all-0 significand. */
  return (pun.u & ~MOZ_DOUBLE_SIGN_BIT) == MOZ_DOUBLE_EXPONENT_BITS;
}

/** Determines whether a double is not NaN or infinite. */
static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_FINITE(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  /*
   * NaN and Infinities are the only non-finite doubles, and both have all
   * exponent bits set to 1.
   */
  return (pun.u & MOZ_DOUBLE_EXPONENT_BITS) != MOZ_DOUBLE_EXPONENT_BITS;
}

/**
 * Determines whether a double is negative.  It is an error to call this method
 * on a double which is NaN.
 */
static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_NEGATIVE(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  MOZ_ASSERT(!MOZ_DOUBLE_IS_NaN(d), "NaN does not have a sign");

  /* The sign bit is set if the double is negative. */
  return (pun.u & MOZ_DOUBLE_SIGN_BIT) != 0;
}

/** Determines whether a double represents -0. */
static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_NEGATIVE_ZERO(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  /* Only the sign bit is set if the double is -0. */
  return pun.u == MOZ_DOUBLE_SIGN_BIT;
}

/** Returns the exponent portion of the double. */
static MOZ_ALWAYS_INLINE int_fast16_t
MOZ_DOUBLE_EXPONENT(double d)
{
  union MozDoublePun pun;
  pun.d = d;

  /*
   * The exponent component of a double is an unsigned number, biased from its
   * actual value.  Subtract the bias to retrieve the actual exponent.
   */
  return (int_fast16_t)((pun.u & MOZ_DOUBLE_EXPONENT_BITS) >> MOZ_DOUBLE_EXPONENT_SHIFT) -
                        MOZ_DOUBLE_EXPONENT_BIAS;
}

/** Returns +Infinity. */
static MOZ_ALWAYS_INLINE double
MOZ_DOUBLE_POSITIVE_INFINITY()
{
  union MozDoublePun pun;

  /*
   * Positive infinity has all exponent bits set, sign bit set to 0, and no
   * significand.
   */
  pun.u = MOZ_DOUBLE_EXPONENT_BITS;
  return pun.d;
}

/** Returns -Infinity. */
static MOZ_ALWAYS_INLINE double
MOZ_DOUBLE_NEGATIVE_INFINITY()
{
  union MozDoublePun pun;

  /*
   * Negative infinity has all exponent bits set, sign bit set to 1, and no
   * significand.
   */
  pun.u = MOZ_DOUBLE_SIGN_BIT | MOZ_DOUBLE_EXPONENT_BITS;
  return pun.d;
}

/** Constructs a NaN value with the specified sign bit and significand bits. */
static MOZ_ALWAYS_INLINE double
MOZ_DOUBLE_SPECIFIC_NaN(int signbit, uint64_t significand)
{
  union MozDoublePun pun;

  MOZ_ASSERT(signbit == 0 || signbit == 1);
  MOZ_ASSERT((significand & ~MOZ_DOUBLE_SIGNIFICAND_BITS) == 0);
  MOZ_ASSERT(significand & MOZ_DOUBLE_SIGNIFICAND_BITS);

  pun.u = (signbit ? MOZ_DOUBLE_SIGN_BIT : 0) |
          MOZ_DOUBLE_EXPONENT_BITS |
          significand;
  MOZ_ASSERT(MOZ_DOUBLE_IS_NaN(pun.d));
  return pun.d;
}

/**
 * Computes a NaN value.  Do not use this method if you depend upon a particular
 * NaN value being returned.
 */
static MOZ_ALWAYS_INLINE double
MOZ_DOUBLE_NaN()
{
  return MOZ_DOUBLE_SPECIFIC_NaN(0, 0xfffffffffffffULL);
}

/** Computes the smallest non-zero positive double value. */
static MOZ_ALWAYS_INLINE double
MOZ_DOUBLE_MIN_VALUE()
{
  union MozDoublePun pun;
  pun.u = 1;
  return pun.d;
}

static MOZ_ALWAYS_INLINE int
MOZ_DOUBLE_IS_INT32(double d, int32_t* i)
{
  /*
   * XXX Casting a double that doesn't truncate to int32_t, to int32_t, induces
   *     undefined behavior.  We should definitely fix this (bug 744965), but as
   *     apparently it "works" in practice, it's not a pressing concern now.
   */
  return !MOZ_DOUBLE_IS_NEGATIVE_ZERO(d) && d == (*i = (int32_t)d);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* mozilla_FloatingPoint_h_ */
