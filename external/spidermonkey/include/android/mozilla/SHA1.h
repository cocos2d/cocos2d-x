/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Simple class for computing SHA1. */

#ifndef mozilla_SHA1_h_
#define mozilla_SHA1_h_

#include "mozilla/StandardInteger.h"
#include "mozilla/Types.h"

#include <stddef.h>

namespace mozilla {

/**
 * This class computes the SHA1 hash of a byte sequence, or of the concatenation
 * of multiple sequences.  For example, computing the SHA1 of two sequences of
 * bytes could be done as follows:
 *
 *   void SHA1(const uint8_t* buf1, uint32_t size1,
 *             const uint8_t* buf2, uint32_t size2,
 *             SHA1Sum::Hash& hash)
 *   {
 *     SHA1Sum s;
 *     s.update(buf1, size1);
 *     s.update(buf2, size2);
 *     s.finish(hash);
 *   }
 *
 * The finish method may only be called once and cannot be followed by calls
 * to update.
 */
class SHA1Sum
{
    union {
        uint32_t w[16]; /* input buffer */
        uint8_t b[64];
    } u;
    uint64_t size; /* count of hashed bytes. */
    unsigned H[22]; /* 5 state variables, 16 tmp values, 1 extra */
    bool mDone;

  public:
    MFBT_API SHA1Sum();

    static const size_t HashSize = 20;
    typedef uint8_t Hash[HashSize];

    /* Add len bytes of dataIn to the data sequence being hashed. */
    MFBT_API void update(const void* dataIn, uint32_t len);

    /* Compute the final hash of all data into hashOut. */
    MFBT_API void finish(SHA1Sum::Hash& hashOut);
};

} /* namespace mozilla */

#endif /* mozilla_SHA1_h_ */
