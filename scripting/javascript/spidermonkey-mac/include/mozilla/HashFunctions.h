/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Utilities for hashing */

/*
 * This file exports functions for hashing data down to a 32-bit value,
 * including:
 *
 *  - HashString    Hash a char* or uint16_t/wchar_t* of known or unknown
 *                  length.
 *
 *  - HashBytes     Hash a byte array of known length.
 *
 *  - HashGeneric   Hash one or more values.  Currently, we support uint32_t,
 *                  types which can be implicitly cast to uint32_t, data
 *                  pointers, and function pointers.
 *
 *  - AddToHash     Add one or more values to the given hash.  This supports the
 *                  same list of types as HashGeneric.
 *
 *
 * You can chain these functions together to hash complex objects.  For example:
 *
 *  class ComplexObject {
 *    char* str;
 *    uint32_t uint1, uint2;
 *    void (*callbackFn)();
 *
 *    uint32_t Hash() {
 *      uint32_t hash = HashString(str);
 *      hash = AddToHash(hash, uint1, uint2);
 *      return AddToHash(hash, callbackFn);
 *    }
 *  };
 *
 * If you want to hash an nsAString or nsACString, use the HashString functions
 * in nsHashKey.h.
 */

#ifndef mozilla_HashFunctions_h_
#define mozilla_HashFunctions_h_

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/StandardInteger.h"

#ifdef __cplusplus
namespace mozilla {

/**
 * The golden ratio as a 32-bit fixed-point value.
 */
static const uint32_t GoldenRatioU32 = 0x9E3779B9U;

inline uint32_t
RotateLeft32(uint32_t value, uint8_t bits)
{
  MOZ_ASSERT(bits < 32);
  return (value << bits) | (value >> (32 - bits));
}

namespace detail {

inline uint32_t
AddU32ToHash(uint32_t hash, uint32_t value)
{
  /*
   * This is the meat of all our hash routines.  This hash function is not
   * particularly sophisticated, but it seems to work well for our mostly
   * plain-text inputs.  Implementation notes follow.
   *
   * Our use of the golden ratio here is arbitrary; we could pick almost any
   * number which:
   *
   *  * is odd (because otherwise, all our hash values will be even)
   *
   *  * has a reasonably-even mix of 1's and 0's (consider the extreme case
   *    where we multiply by 0x3 or 0xeffffff -- this will not produce good
   *    mixing across all bits of the hash).
   *
   * The rotation length of 5 is also arbitrary, although an odd number is again
   * preferable so our hash explores the whole universe of possible rotations.
   *
   * Finally, we multiply by the golden ratio *after* xor'ing, not before.
   * Otherwise, if |hash| is 0 (as it often is for the beginning of a message),
   * the expression
   *
   *   (GoldenRatioU32 * RotateLeft(hash, 5)) |xor| value
   *
   * evaluates to |value|.
   *
   * (Number-theoretic aside: Because any odd number |m| is relatively prime to
   * our modulus (2^32), the list
   *
   *    [x * m (mod 2^32) for 0 <= x < 2^32]
   *
   * has no duplicate elements.  This means that multiplying by |m| does not
   * cause us to skip any possible hash values.
   *
   * It's also nice if |m| has large-ish order mod 2^32 -- that is, if the
   * smallest k such that m^k == 1 (mod 2^32) is large -- so we can safely
   * multiply our hash value by |m| a few times without negating the
   * multiplicative effect.  Our golden ratio constant has order 2^29, which is
   * more than enough for our purposes.)
   */
  return GoldenRatioU32 * (RotateLeft32(hash, 5) ^ value);
}

/**
 * AddUintptrToHash takes sizeof(uintptr_t) as a template parameter.
 */
template<size_t PtrSize>
inline uint32_t
AddUintptrToHash(uint32_t hash, uintptr_t value);

template<>
inline uint32_t
AddUintptrToHash<4>(uint32_t hash, uintptr_t value)
{
  return AddU32ToHash(hash, static_cast<uint32_t>(value));
}

template<>
inline uint32_t
AddUintptrToHash<8>(uint32_t hash, uintptr_t value)
{
  /*
   * The static cast to uint64_t below is necessary because this function
   * sometimes gets compiled on 32-bit platforms (yes, even though it's a
   * template and we never call this particular override in a 32-bit build).  If
   * we do value >> 32 on a 32-bit machine, we're shifting a 32-bit uintptr_t
   * right 32 bits, and the compiler throws an error.
   */
  uint32_t v1 = static_cast<uint32_t>(value);
  uint32_t v2 = static_cast<uint32_t>(static_cast<uint64_t>(value) >> 32);
  return AddU32ToHash(AddU32ToHash(hash, v1), v2);
}

} /* namespace detail */

/**
 * AddToHash takes a hash and some values and returns a new hash based on the
 * inputs.
 *
 * Currently, we support hashing uint32_t's, values which we can implicitly
 * convert to uint32_t, data pointers, and function pointers.
 */
template<typename A>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, A a)
{
  /*
   * Try to convert |A| to uint32_t implicitly.  If this works, great.  If not,
   * we'll error out.
   */
  return detail::AddU32ToHash(hash, a);
}

template<typename A>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, A* a)
{
  /*
   * You might think this function should just take a void*.  But then we'd only
   * catch data pointers and couldn't handle function pointers.
   */

  MOZ_STATIC_ASSERT(sizeof(a) == sizeof(uintptr_t),
                    "Strange pointer!");

  return detail::AddUintptrToHash<sizeof(uintptr_t)>(hash, uintptr_t(a));
}

template<typename A, typename B>
MOZ_WARN_UNUSED_RESULT
uint32_t
AddToHash(uint32_t hash, A a, B b)
{
  return AddToHash(AddToHash(hash, a), b);
}

template<typename A, typename B, typename C>
MOZ_WARN_UNUSED_RESULT
uint32_t
AddToHash(uint32_t hash, A a, B b, C c)
{
  return AddToHash(AddToHash(hash, a, b), c);
}

template<typename A, typename B, typename C, typename D>
MOZ_WARN_UNUSED_RESULT
uint32_t
AddToHash(uint32_t hash, A a, B b, C c, D d)
{
  return AddToHash(AddToHash(hash, a, b, c), d);
}

template<typename A, typename B, typename C, typename D, typename E>
MOZ_WARN_UNUSED_RESULT
uint32_t
AddToHash(uint32_t hash, A a, B b, C c, D d, E e)
{
  return AddToHash(AddToHash(hash, a, b, c, d), e);
}

/**
 * The HashGeneric class of functions let you hash one or more values.
 *
 * If you want to hash together two values x and y, calling HashGeneric(x, y) is
 * much better than calling AddToHash(x, y), because AddToHash(x, y) assumes
 * that x has already been hashed.
 */
template<typename A>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashGeneric(A a)
{
  return AddToHash(0, a);
}

template<typename A, typename B>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashGeneric(A a, B b)
{
  return AddToHash(0, a, b);
}

template<typename A, typename B, typename C>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashGeneric(A a, B b, C c)
{
  return AddToHash(0, a, b, c);
}

template<typename A, typename B, typename C, typename D>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashGeneric(A a, B b, C c, D d)
{
  return AddToHash(0, a, b, c, d);
}

template<typename A, typename B, typename C, typename D, typename E>
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashGeneric(A a, B b, C c, D d, E e)
{
  return AddToHash(0, a, b, c, d, e);
}

namespace detail {

template<typename T>
uint32_t
HashUntilZero(const T* str)
{
  uint32_t hash = 0;
  for (T c; (c = *str); str++)
    hash = AddToHash(hash, c);
  return hash;
}

template<typename T>
uint32_t
HashKnownLength(const T* str, size_t length)
{
  uint32_t hash = 0;
  for (size_t i = 0; i < length; i++)
    hash = AddToHash(hash, str[i]);
  return hash;
}

} /* namespace detail */

/**
 * The HashString overloads below do just what you'd expect.
 *
 * If you have the string's length, you might as well call the overload which
 * includes the length.  It may be marginally faster.
 */
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const char* str)
{
  return detail::HashUntilZero(str);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const char* str, size_t length)
{
  return detail::HashKnownLength(str, length);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const uint16_t* str)
{
  return detail::HashUntilZero(str);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const uint16_t* str, size_t length)
{
  return detail::HashKnownLength(str, length);
}

/*
 * On Windows, wchar_t (PRUnichar) is not the same as uint16_t, even though it's
 * the same width!
 */
#ifdef WIN32
MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const wchar_t* str)
{
  return detail::HashUntilZero(str);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
HashString(const wchar_t* str, size_t length)
{
  return detail::HashKnownLength(str, length);
}
#endif

/**
 * Hash some number of bytes.
 *
 * This hash walks word-by-word, rather than byte-by-byte, so you won't get the
 * same result out of HashBytes as you would out of HashString.
 */
MOZ_WARN_UNUSED_RESULT
extern MFBT_API(uint32_t)
HashBytes(const void* bytes, size_t length);

} /* namespace mozilla */
#endif /* __cplusplus */
#endif /* mozilla_HashFunctions_h_ */
