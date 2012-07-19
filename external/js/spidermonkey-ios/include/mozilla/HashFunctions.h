/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Utilities for hashing */

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

/**
 * Add the given value(s) to the given hashcode and return the new hashcode.
 *
 * AddToHash(h, x, y) is equivalent to AddToHash(AddToHash(h, x), y).
 */
MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, uint32_t value)
{
  /*
   * This is not a sophisticated hash routine, but it seems to work well for our
   * mostly plain-text inputs.  Implementation notes follow.
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
   *   (GoldenRatioU32 * RotateLeft(hash, 5)) ^ value
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
   * It's also nice if |m| has larger order mod 2^32 -- that is, if the smallest
   * k such that m^k == 1 (mod 2^32) is large -- so we can safely multiply our
   * hash value by |m| a few times without negating the multiplicative effect.
   * Our golden ratio constant has order 2^29, which is more than enough for our
   * purposes.)
   */
  return GoldenRatioU32 * (RotateLeft32(hash, 5) ^ value);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, uint32_t v1, uint32_t v2)
{
  return AddToHash(AddToHash(hash, v1), v2);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, uint32_t v1, uint32_t v2, uint32_t v3)
{
  return AddToHash(AddToHash(hash, v1, v2), v3);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4)
{
  return AddToHash(AddToHash(hash, v1, v2, v3), v4);
}

MOZ_WARN_UNUSED_RESULT
inline uint32_t
AddToHash(uint32_t hash, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5)
{
  return AddToHash(AddToHash(hash, v1, v2, v3, v4), v5);
}

} /* namespace mozilla */
#endif /* __cplusplus */
#endif /* mozilla_HashFunctions_h_ */
