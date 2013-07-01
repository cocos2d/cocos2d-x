/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* mfbt maths algorithms. */

#ifndef mozilla_MathAlgorithms_h_
#define mozilla_MathAlgorithms_h_

#include "mozilla/Assertions.h"
#include "mozilla/StandardInteger.h"
#include "mozilla/TypeTraits.h"

#include <cmath>
#include <limits.h>

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

} /* namespace mozilla */

#endif  /* mozilla_MathAlgorithms_h_ */
