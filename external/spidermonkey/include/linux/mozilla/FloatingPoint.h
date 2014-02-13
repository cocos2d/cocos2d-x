/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Various predicates and operations on IEEE-754 floating point types. */

#ifndef mozilla_FloatingPoint_h
#define mozilla_FloatingPoint_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Casting.h"
#include "mozilla/Types.h"

#include <stdint.h>

namespace mozilla {

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
 */

/*
 * These implementations all assume |double| is a 64-bit double format number
 * type, compatible with the IEEE-754 standard.  C/C++ don't require this to be
 * the case.  But we required this in implementations of these algorithms that
 * preceded this header, so we shouldn't break anything if we continue doing so.
 */
static_assert(sizeof(double) == sizeof(uint64_t), "double must be 64 bits");

const unsigned DoubleExponentBias = 1023;
const unsigned DoubleExponentShift = 52;

const uint64_t DoubleSignBit         = 0x8000000000000000ULL;
const uint64_t DoubleExponentBits    = 0x7ff0000000000000ULL;
const uint64_t DoubleSignificandBits = 0x000fffffffffffffULL;

static_assert((DoubleSignBit & DoubleExponentBits) == 0,
              "sign bit doesn't overlap exponent bits");
static_assert((DoubleSignBit & DoubleSignificandBits) == 0,
              "sign bit doesn't overlap significand bits");
static_assert((DoubleExponentBits & DoubleSignificandBits) == 0,
              "exponent bits don't overlap significand bits");

static_assert((DoubleSignBit | DoubleExponentBits | DoubleSignificandBits) ==
              ~uint64_t(0),
              "all bits accounted for");

/*
 * Ditto for |float| that must be a 32-bit double format number type, compatible
 * with the IEEE-754 standard.
 */
static_assert(sizeof(float) == sizeof(uint32_t), "float must be 32bits");

const unsigned FloatExponentBias = 127;
const unsigned FloatExponentShift = 23;

const uint32_t FloatSignBit         = 0x80000000UL;
const uint32_t FloatExponentBits    = 0x7F800000UL;
const uint32_t FloatSignificandBits = 0x007FFFFFUL;

static_assert((FloatSignBit & FloatExponentBits) == 0,
              "sign bit doesn't overlap exponent bits");
static_assert((FloatSignBit & FloatSignificandBits) == 0,
              "sign bit doesn't overlap significand bits");
static_assert((FloatExponentBits & FloatSignificandBits) == 0,
              "exponent bits don't overlap significand bits");

static_assert((FloatSignBit | FloatExponentBits | FloatSignificandBits) ==
              ~uint32_t(0),
              "all bits accounted for");

/** Determines whether a double is NaN. */
static MOZ_ALWAYS_INLINE bool
IsNaN(double d)
{
  /*
   * A double is NaN if all exponent bits are 1 and the significand contains at
   * least one non-zero bit.
   */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return (bits & DoubleExponentBits) == DoubleExponentBits &&
         (bits & DoubleSignificandBits) != 0;
}

/** Determines whether a double is +Infinity or -Infinity. */
static MOZ_ALWAYS_INLINE bool
IsInfinite(double d)
{
  /* Infinities have all exponent bits set to 1 and an all-0 significand. */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return (bits & ~DoubleSignBit) == DoubleExponentBits;
}

/** Determines whether a double is not NaN or infinite. */
static MOZ_ALWAYS_INLINE bool
IsFinite(double d)
{
  /*
   * NaN and Infinities are the only non-finite doubles, and both have all
   * exponent bits set to 1.
   */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return (bits & DoubleExponentBits) != DoubleExponentBits;
}

/**
 * Determines whether a double is negative.  It is an error to call this method
 * on a double which is NaN.
 */
static MOZ_ALWAYS_INLINE bool
IsNegative(double d)
{
  MOZ_ASSERT(!IsNaN(d), "NaN does not have a sign");

  /* The sign bit is set if the double is negative. */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return (bits & DoubleSignBit) != 0;
}

/** Determines whether a double represents -0. */
static MOZ_ALWAYS_INLINE bool
IsNegativeZero(double d)
{
  /* Only the sign bit is set if the double is -0. */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return bits == DoubleSignBit;
}

/**
 * Returns the exponent portion of the double.
 *
 * Zero is not special-cased, so ExponentComponent(0.0) is
 * -int_fast16_t(DoubleExponentBias).
 */
static MOZ_ALWAYS_INLINE int_fast16_t
ExponentComponent(double d)
{
  /*
   * The exponent component of a double is an unsigned number, biased from its
   * actual value.  Subtract the bias to retrieve the actual exponent.
   */
  uint64_t bits = BitwiseCast<uint64_t>(d);
  return int_fast16_t((bits & DoubleExponentBits) >> DoubleExponentShift) -
         int_fast16_t(DoubleExponentBias);
}

/** Returns +Infinity. */
static MOZ_ALWAYS_INLINE double
PositiveInfinity()
{
  /*
   * Positive infinity has all exponent bits set, sign bit set to 0, and no
   * significand.
   */
  return BitwiseCast<double>(DoubleExponentBits);
}

/** Returns -Infinity. */
static MOZ_ALWAYS_INLINE double
NegativeInfinity()
{
  /*
   * Negative infinity has all exponent bits set, sign bit set to 1, and no
   * significand.
   */
  return BitwiseCast<double>(DoubleSignBit | DoubleExponentBits);
}

/** Constructs a NaN value with the specified sign bit and significand bits. */
static MOZ_ALWAYS_INLINE double
SpecificNaN(int signbit, uint64_t significand)
{
  MOZ_ASSERT(signbit == 0 || signbit == 1);
  MOZ_ASSERT((significand & ~DoubleSignificandBits) == 0);
  MOZ_ASSERT(significand & DoubleSignificandBits);

  double d = BitwiseCast<double>((signbit ? DoubleSignBit : 0) |
                                 DoubleExponentBits |
                                 significand);
  MOZ_ASSERT(IsNaN(d));
  return d;
}

/** Computes the smallest non-zero positive double value. */
static MOZ_ALWAYS_INLINE double
MinDoubleValue()
{
  return BitwiseCast<double>(uint64_t(1));
}

static MOZ_ALWAYS_INLINE bool
DoubleIsInt32(double d, int32_t* i)
{
  /*
   * XXX Casting a double that doesn't truncate to int32_t, to int32_t, induces
   *     undefined behavior.  We should definitely fix this (bug 744965), but as
   *     apparently it "works" in practice, it's not a pressing concern now.
   */
  return !IsNegativeZero(d) && d == (*i = int32_t(d));
}

/**
 * Computes a NaN value.  Do not use this method if you depend upon a particular
 * NaN value being returned.
 */
static MOZ_ALWAYS_INLINE double
UnspecifiedNaN()
{
  /*
   * If we can use any quiet NaN, we might as well use the all-ones NaN,
   * since it's cheap to materialize on common platforms (such as x64, where
   * this value can be represented in a 32-bit signed immediate field, allowing
   * it to be stored to memory in a single instruction).
   */
  return SpecificNaN(1, 0xfffffffffffffULL);
}

/**
 * Compare two doubles for equality, *without* equating -0 to +0, and equating
 * any NaN value to any other NaN value.  (The normal equality operators equate
 * -0 with +0, and they equate NaN to no other value.)
 */
static inline bool
DoublesAreIdentical(double d1, double d2)
{
  if (IsNaN(d1))
    return IsNaN(d2);
  return BitwiseCast<uint64_t>(d1) == BitwiseCast<uint64_t>(d2);
}

/** Determines whether a float is NaN. */
static MOZ_ALWAYS_INLINE bool
IsFloatNaN(float f)
{
  /*
   * A float is NaN if all exponent bits are 1 and the significand contains at
   * least one non-zero bit.
   */
  uint32_t bits = BitwiseCast<uint32_t>(f);
  return (bits & FloatExponentBits) == FloatExponentBits &&
         (bits & FloatSignificandBits) != 0;
}

/** Constructs a NaN value with the specified sign bit and significand bits. */
static MOZ_ALWAYS_INLINE float
SpecificFloatNaN(int signbit, uint32_t significand)
{
  MOZ_ASSERT(signbit == 0 || signbit == 1);
  MOZ_ASSERT((significand & ~FloatSignificandBits) == 0);
  MOZ_ASSERT(significand & FloatSignificandBits);

  float f = BitwiseCast<float>((signbit ? FloatSignBit : 0) |
                                 FloatExponentBits |
                                 significand);
  MOZ_ASSERT(IsFloatNaN(f));
  return f;
}

/**
 * Returns true if the given value can be losslessly represented as an IEEE-754
 * single format number, false otherwise.  All NaN values are considered
 * representable (notwithstanding that the exact bit pattern of a double format
 * NaN value can't be exactly represented in single format).
 *
 * This function isn't inlined to avoid buggy optimizations by MSVC.
 */
MOZ_WARN_UNUSED_RESULT
extern MFBT_API bool
IsFloat32Representable(double x);

} /* namespace mozilla */

#endif /* mozilla_FloatingPoint_h */
