/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Miscellaneous uncategorized functionality.  Please add new functionality to
 * new headers, or to other appropriate existing headers, not here.
 */

#ifndef mozilla_Util_h
#define mozilla_Util_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Types.h"

#ifdef __cplusplus

#include "mozilla/Alignment.h"

namespace mozilla {

/*
 * Safely subtract two pointers when it is known that end >= begin.  This avoids
 * the common compiler bug that if (size_t(end) - size_t(begin)) has the MSB
 * set, the unsigned subtraction followed by right shift will produce -1, or
 * size_t(-1), instead of the real difference.
 */
template<class T>
MOZ_ALWAYS_INLINE size_t
PointerRangeSize(T* begin, T* end)
{
  MOZ_ASSERT(end >= begin);
  return (size_t(end) - size_t(begin)) / sizeof(T);
}

/*
 * Compute the length of an array with constant length.  (Use of this method
 * with a non-array pointer will not compile.)
 *
 * Beware of the implicit trailing '\0' when using this with string constants.
 */
template<typename T, size_t N>
MOZ_CONSTEXPR size_t
ArrayLength(T (&arr)[N])
{
  return N;
}

/*
 * Compute the address one past the last element of a constant-length array.
 *
 * Beware of the implicit trailing '\0' when using this with string constants.
 */
template<typename T, size_t N>
MOZ_CONSTEXPR T*
ArrayEnd(T (&arr)[N])
{
  return arr + ArrayLength(arr);
}

} /* namespace mozilla */

#endif /* __cplusplus */

/*
 * MOZ_ARRAY_LENGTH() is an alternative to mozilla::ArrayLength() for C files
 * that can't use C++ template functions and for static_assert() calls that
 * can't call ArrayLength() when it is not a C++11 constexpr function.
 */
#ifdef MOZ_HAVE_CXX11_CONSTEXPR
#  define MOZ_ARRAY_LENGTH(array)   mozilla::ArrayLength(array)
#else
#  define MOZ_ARRAY_LENGTH(array)   (sizeof(array)/sizeof((array)[0]))
#endif

#endif /* mozilla_Util_h */
