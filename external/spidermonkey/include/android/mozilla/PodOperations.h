/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Operations for zeroing POD types, arrays, and so on.
 *
 * These operations are preferable to memset, memcmp, and the like because they
 * don't require remembering to multiply by sizeof(T), array lengths, and so on
 * everywhere.
 */

#ifndef mozilla_PodOperations_h
#define mozilla_PodOperations_h

#include "mozilla/Attributes.h"
#include "mozilla/Util.h"

#include <string.h>

namespace mozilla {

/** Set the contents of |t| to 0. */
template<typename T>
static void
PodZero(T* t)
{
  memset(t, 0, sizeof(T));
}

/** Set the contents of |nelem| elements starting at |t| to 0. */
template<typename T>
static void
PodZero(T* t, size_t nelem)
{
  /*
   * This function is often called with 'nelem' small; we use an inline loop
   * instead of calling 'memset' with a non-constant length.  The compiler
   * should inline the memset call with constant size, though.
   */
  for (T* end = t + nelem; t < end; t++)
    memset(t, 0, sizeof(T));
}

/*
 * Arrays implicitly convert to pointers to their first element, which is
 * dangerous when combined with the above PodZero definitions.  Adding an
 * overload for arrays is ambiguous, so we need another identifier.  The
 * ambiguous overload is left to catch mistaken uses of PodZero; if you get a
 * compile error involving PodZero and array types, use PodArrayZero instead.
 */
template<typename T, size_t N>
static void PodZero(T (&t)[N]) MOZ_DELETE;
template<typename T, size_t N>
static void PodZero(T (&t)[N], size_t nelem) MOZ_DELETE;

/** Set the contents of the array |t| to zero. */
template <class T, size_t N>
static void
PodArrayZero(T (&t)[N])
{
  memset(t, 0, N * sizeof(T));
}

/**
 * Assign |*src| to |*dst|.  The locations must not be the same and must not
 * overlap.
 */
template<typename T>
static void
PodAssign(T* dst, const T* src)
{
  MOZ_ASSERT(dst != src);
  MOZ_ASSERT_IF(src < dst, PointerRangeSize(src, static_cast<const T*>(dst)) >= 1);
  MOZ_ASSERT_IF(dst < src, PointerRangeSize(static_cast<const T*>(dst), src) >= 1);
  memcpy(reinterpret_cast<char*>(dst), reinterpret_cast<const char*>(src), sizeof(T));
}

/**
 * Copy |nelem| T elements from |src| to |dst|.  The two memory ranges must not
 * overlap!
 */
template<typename T>
MOZ_ALWAYS_INLINE static void
PodCopy(T* dst, const T* src, size_t nelem)
{
  MOZ_ASSERT(dst != src);
  MOZ_ASSERT_IF(src < dst, PointerRangeSize(src, static_cast<const T*>(dst)) >= nelem);
  MOZ_ASSERT_IF(dst < src, PointerRangeSize(static_cast<const T*>(dst), src) >= nelem);

  if (nelem < 128) {
    /*
     * Avoid using operator= in this loop, as it may have been
     * intentionally deleted by the POD type.
     */
    for (const T* srcend = src + nelem; src < srcend; src++, dst++)
      PodAssign(dst, src);
  } else {
    memcpy(dst, src, nelem * sizeof(T));
  }
}

template<typename T>
MOZ_ALWAYS_INLINE static void
PodCopy(volatile T* dst, const volatile T* src, size_t nelem)
{
  MOZ_ASSERT(dst != src);
  MOZ_ASSERT_IF(src < dst,
                PointerRangeSize(src, static_cast<const volatile T*>(dst)) >= nelem);
  MOZ_ASSERT_IF(dst < src,
                PointerRangeSize(static_cast<const volatile T*>(dst), src) >= nelem);

  /*
   * Volatile |dst| requires extra work, because it's undefined behavior to
   * modify volatile objects using the mem* functions.  Just write out the
   * loops manually, using operator= rather than memcpy for the same reason,
   * and let the compiler optimize to the extent it can.
   */
  for (const volatile T* srcend = src + nelem; src < srcend; src++, dst++)
    *dst = *src;
}

/*
 * Copy the contents of the array |src| into the array |dst|, both of size N.
 * The arrays must not overlap!
 */
template <class T, size_t N>
static void
PodArrayCopy(T (&dst)[N], const T (&src)[N])
{
  PodCopy(dst, src, N);
}

/**
 * Determine whether the |len| elements at |one| are memory-identical to the
 * |len| elements at |two|.
 */
template<typename T>
MOZ_ALWAYS_INLINE static bool
PodEqual(const T* one, const T* two, size_t len)
{
  if (len < 128) {
    const T* p1end = one + len;
    const T* p1 = one;
    const T* p2 = two;
    for (; p1 < p1end; p1++, p2++) {
      if (*p1 != *p2)
        return false;
    }
    return true;
  }

  return !memcmp(one, two, len * sizeof(T));
}

} // namespace mozilla

#endif /* mozilla_PodOperations_h */
