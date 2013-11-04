/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* mfbt maths algorithms. */

#ifndef mozilla_MathAlgorithms_h
#define mozilla_MathAlgorithms_h

#include "mozilla/Assertions.h"
#include "mozilla/TypeTraits.h"

#include <cmath>
#include <limits.h>
#include <stdint.h>

namespace mozilla {

// Greatest Common Divisor
template<typename IntegerType>
MOZ_ALWAYS_INLINE IntegerType
EuclidGCD(IntegerType a, IntegerType b)
{
  // Euclid's algorithm; O(N) in the worst case.  (There are better
  // ways, but we don't need them for the current use of this algo.)
  MOZ_ASSERT(a > 0);
  MOZ_ASSERT(b > 0);

  while (a != b) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }

  return a;
}

// Least Common Multiple
template<typename IntegerType>
MOZ_ALWAYS_INLINE IntegerType
EuclidLCM(IntegerType a, IntegerType b)
{
  // Divide first to reduce overflow risk.
  return (a / EuclidGCD(a, b)) * b;
}

namespace detail {

template<typename T>
struct AllowDeprecatedAbsFixed : FalseType {};

template<> struct AllowDeprecatedAbsFixed<int32_t> : TrueType {};
template<> struct AllowDeprecatedAbsFixed<int64_t> : TrueType {};

template<typename T>
struct AllowDeprecatedAbs : AllowDeprecatedAbsFixed<T> {};

template<> struct AllowDeprecatedAbs<int> : TrueType {};
template<> struct AllowDeprecatedAbs<long> : TrueType {};

} // namespace detail

// DO NOT USE DeprecatedAbs.  It exists only until its callers can be converted
// to Abs below, and it will be removed when all callers have been changed.
template<typename T>
inline typename mozilla::EnableIf<detail::AllowDeprecatedAbs<T>::value, T>::Type
DeprecatedAbs(const T t)
{
  // The absolute value of the smallest possible value of a signed-integer type
  // won't fit in that type (on twos-complement systems -- and we're blithely
  // assuming we're on such systems, for the non-<stdint.h> types listed above),
  // so assert that the input isn't that value.
  //
  // This is the case if: the value is non-negative; or if adding one (giving a
  // value in the range [-maxvalue, 0]), then negating (giving a value in the
  // range [0, maxvalue]), doesn't produce maxvalue (because in twos-complement,
  // (minvalue + 1) == -maxvalue).
  MOZ_ASSERT(t >= 0 ||
             -(t + 1) != T((1ULL << (CHAR_BIT * sizeof(T) - 1)) - 1),
             "You can't negate the smallest possible negative integer!");
  return t >= 0 ? t : -t;
}

namespace detail {

// For now mozilla::Abs only takes intN_T, the signed natural types, and
// float/double/long double.  Feel free to add overloads for other standard,
// signed types if you need them.

template<typename T>
struct AbsReturnTypeFixed;

template<> struct AbsReturnTypeFixed<int8_t> { typedef uint8_t Type; };
template<> struct AbsReturnTypeFixed<int16_t> { typedef uint16_t Type; };
template<> struct AbsReturnTypeFixed<int32_t> { typedef uint32_t Type; };
template<> struct AbsReturnTypeFixed<int64_t> { typedef uint64_t Type; };

template<typename T>
struct AbsReturnType : AbsReturnTypeFixed<T> {};

template<> struct AbsReturnType<char> : EnableIf<char(-1) < char(0), unsigned char> {};
template<> struct AbsReturnType<signed char> { typedef unsigned char Type; };
template<> struct AbsReturnType<short> { typedef unsigned short Type; };
template<> struct AbsReturnType<int> { typedef unsigned int Type; };
template<> struct AbsReturnType<long> { typedef unsigned long Type; };
template<> struct AbsReturnType<long long> { typedef unsigned long long Type; };
template<> struct AbsReturnType<float> { typedef float Type; };
template<> struct AbsReturnType<double> { typedef double Type; };
template<> struct AbsReturnType<long double> { typedef long double Type; };

} // namespace detail

template<typename T>
inline typename detail::AbsReturnType<T>::Type
Abs(const T t)
{
  typedef typename detail::AbsReturnType<T>::Type ReturnType;
  return t >= 0 ? ReturnType(t) : ~ReturnType(t) + 1;
}

template<>
inline float
Abs<float>(const float f)
{
  return std::fabs(f);
}

template<>
inline double
Abs<double>(const double d)
{
  return std::fabs(d);
}

template<>
inline long double
Abs<long double>(const long double d)
{
  return std::fabs(d);
}

} // namespace mozilla

#if defined(_WIN32) && (_MSC_VER >= 1300) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))
#  define MOZ_BITSCAN_WINDOWS

  extern "C" {
    unsigned char _BitScanForward(unsigned long* Index, unsigned long mask);
    unsigned char _BitScanReverse(unsigned long* Index, unsigned long mask);
#  pragma intrinsic(_BitScanForward, _BitScanReverse)

#  if defined(_M_AMD64) || defined(_M_X64)
#    define MOZ_BITSCAN_WINDOWS64
    unsigned char _BitScanForward64(unsigned long* index, unsigned __int64 mask);
    unsigned char _BitScanReverse64(unsigned long* index, unsigned __int64 mask);
#   pragma intrinsic(_BitScanForward64, _BitScanReverse64)
#  endif
  } // extern "C"

#endif

namespace mozilla {

namespace detail {

#if defined(MOZ_BITSCAN_WINDOWS)

  inline uint_fast8_t
  CountLeadingZeroes32(uint32_t u)
  {
    unsigned long index;
    _BitScanReverse(&index, static_cast<unsigned long>(u));
    return uint_fast8_t(31 - index);
  }


  inline uint_fast8_t
  CountTrailingZeroes32(uint32_t u)
  {
    unsigned long index;
    _BitScanForward(&index, static_cast<unsigned long>(u));
    return uint_fast8_t(index);
  }

  inline uint_fast8_t
  CountLeadingZeroes64(uint64_t u)
  {
#  if defined(MOZ_BITSCAN_WINDOWS64)
    unsigned long index;
    _BitScanReverse64(&index, static_cast<unsigned __int64>(u));
    return uint_fast8_t(63 - index);
#  else
    uint32_t hi = uint32_t(u >> 32);
    if (hi != 0)
      return CountLeadingZeroes32(hi);
    return 32 + CountLeadingZeroes32(uint32_t(u));
#  endif
  }

  inline uint_fast8_t
  CountTrailingZeroes64(uint64_t u)
  {
#  if defined(MOZ_BITSCAN_WINDOWS64)
    unsigned long index;
    _BitScanForward64(&index, static_cast<unsigned __int64>(u));
    return uint_fast8_t(index);
#  else
    uint32_t lo = uint32_t(u);
    if (lo != 0)
      return CountTrailingZeroes32(lo);
    return 32 + CountTrailingZeroes32(uint32_t(u >> 32));
#  endif
  }

#  ifdef MOZ_HAVE_BITSCAN64
#    undef MOZ_HAVE_BITSCAN64
#  endif

#elif defined(__clang__) || defined(__GNUC__)

#  if defined(__clang__)
#    if !__has_builtin(__builtin_ctz) || !__has_builtin(__builtin_clz)
#      error "A clang providing __builtin_c[lt]z is required to build"
#    endif
#  else
     // gcc has had __builtin_clz and friends since 3.4: no need to check.
#  endif

  inline uint_fast8_t
  CountLeadingZeroes32(uint32_t u)
  {
    return __builtin_clz(u);
  }

  inline uint_fast8_t
  CountTrailingZeroes32(uint32_t u)
  {
    return __builtin_ctz(u);
  }

  inline uint_fast8_t
  CountLeadingZeroes64(uint64_t u)
  {
    return __builtin_clzll(u);
  }

  inline uint_fast8_t
  CountTrailingZeroes64(uint64_t u)
  {
    return __builtin_ctzll(u);
  }

#else
#  error "Implement these!"
  inline uint_fast8_t CountLeadingZeroes32(uint32_t u) MOZ_DELETE;
  inline uint_fast8_t CountTrailingZeroes32(uint32_t u) MOZ_DELETE;
  inline uint_fast8_t CountLeadingZeroes64(uint64_t u) MOZ_DELETE;
  inline uint_fast8_t CountTrailingZeroes64(uint64_t u) MOZ_DELETE;
#endif

} // namespace detail

/**
 * Compute the number of high-order zero bits in the NON-ZERO number |u|.  That
 * is, looking at the bitwise representation of the number, with the highest-
 * valued bits at the start, return the number of zeroes before the first one
 * is observed.
 *
 * CountLeadingZeroes32(0xF0FF1000) is 0;
 * CountLeadingZeroes32(0x7F8F0001) is 1;
 * CountLeadingZeroes32(0x3FFF0100) is 2;
 * CountLeadingZeroes32(0x1FF50010) is 3; and so on.
 */
inline uint_fast8_t
CountLeadingZeroes32(uint32_t u)
{
  MOZ_ASSERT(u != 0);
  return detail::CountLeadingZeroes32(u);
}

/**
 * Compute the number of low-order zero bits in the NON-ZERO number |u|.  That
 * is, looking at the bitwise representation of the number, with the lowest-
 * valued bits at the start, return the number of zeroes before the first one
 * is observed.
 *
 * CountTrailingZeroes32(0x0100FFFF) is 0;
 * CountTrailingZeroes32(0x7000FFFE) is 1;
 * CountTrailingZeroes32(0x0080FFFC) is 2;
 * CountTrailingZeroes32(0x0080FFF8) is 3; and so on.
 */
inline uint_fast8_t
CountTrailingZeroes32(uint32_t u)
{
  MOZ_ASSERT(u != 0);
  return detail::CountTrailingZeroes32(u);
}

/** Analogous to CountLeadingZeroes32, but for 64-bit numbers. */
inline uint_fast8_t
CountLeadingZeroes64(uint64_t u)
{
  MOZ_ASSERT(u != 0);
  return detail::CountLeadingZeroes64(u);
}

/** Analogous to CountTrailingZeroes32, but for 64-bit numbers. */
inline uint_fast8_t
CountTrailingZeroes64(uint64_t u)
{
  MOZ_ASSERT(u != 0);
  return detail::CountTrailingZeroes64(u);
}

namespace detail {

template<typename T, size_t Size = sizeof(T)>
class CeilingLog2;

template<typename T>
class CeilingLog2<T, 4>
{
  public:
    static uint_fast8_t compute(const T t) {
      // Check for <= 1 to avoid the == 0 undefined case.
      return t <= 1 ? 0 : 32 - CountLeadingZeroes32(t - 1);
    }
};

template<typename T>
class CeilingLog2<T, 8>
{
  public:
    static uint_fast8_t compute(const T t) {
      // Check for <= 1 to avoid the == 0 undefined case.
      return t <= 1 ? 0 : 64 - CountLeadingZeroes64(t - 1);
    }
};

} // namespace detail

/**
 * Compute the log of the least power of 2 greater than or equal to |t|.
 *
 * CeilingLog2(0..1) is 0;
 * CeilingLog2(2) is 1;
 * CeilingLog2(3..4) is 2;
 * CeilingLog2(5..8) is 3;
 * CeilingLog2(9..16) is 4; and so on.
 */
template<typename T>
inline uint_fast8_t
CeilingLog2(const T t)
{
  return detail::CeilingLog2<T>::compute(t);
}

/** A CeilingLog2 variant that accepts only size_t. */
inline uint_fast8_t
CeilingLog2Size(size_t n)
{
  return CeilingLog2(n);
}

namespace detail {

template<typename T, size_t Size = sizeof(T)>
class FloorLog2;

template<typename T>
class FloorLog2<T, 4>
{
  public:
    static uint_fast8_t compute(const T t) {
      return 31 - CountLeadingZeroes32(t | 1);
    }
};

template<typename T>
class FloorLog2<T, 8>
{
  public:
    static uint_fast8_t compute(const T t) {
      return 63 - CountLeadingZeroes64(t | 1);
    }
};

} // namespace detail

/**
 * Compute the log of the greatest power of 2 less than or equal to |t|.
 *
 * FloorLog2(0..1) is 0;
 * FloorLog2(2..3) is 1;
 * FloorLog2(4..7) is 2;
 * FloorLog2(8..15) is 3; and so on.
 */
template<typename T>
inline uint_fast8_t
FloorLog2(const T t)
{
  return detail::FloorLog2<T>::compute(t);
}

/** A FloorLog2 variant that accepts only size_t. */
inline uint_fast8_t
FloorLog2Size(size_t n)
{
  return FloorLog2(n);
}

/*
 * Compute the smallest power of 2 greater than or equal to |x|.  |x| must not
 * be so great that the computed value would overflow |size_t|.
 */
inline size_t
RoundUpPow2(size_t x)
{
  MOZ_ASSERT(x <= (size_t(1) << (sizeof(size_t) * CHAR_BIT - 1)),
             "can't round up -- will overflow!");
  return size_t(1) << CeilingLog2(x);
}

} /* namespace mozilla */

#endif /* mozilla_MathAlgorithms_h */
