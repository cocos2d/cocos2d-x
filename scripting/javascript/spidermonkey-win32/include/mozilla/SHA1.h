/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Simple class for computing SHA1. */

/*
 * To compute the SHA1 of a buffer using this class you should write something
 * like:
 * void SHA1(const uint8_t* buf, unsigned size, uint8_t hash[20])
 * {
 *   SHA1Sum S;
 *   S.update(buf, size);
 *   S.finish(hash);
 * }
 * If there are multiple buffers or chunks, the update method can be called
 * multiple times and the SHA1 is computed on the concatenation of all the
 * buffers passed to it.
 * The finish method may only be called once and cannot be followed by calls
 * to update.
 */

#ifndef mozilla_SHA1_h_
#define mozilla_SHA1_h_

#include "mozilla/StandardInteger.h"
namespace mozilla {
class SHA1Sum {
  union {
    uint32_t w[16];         /* input buffer */
    uint8_t  b[64];
  } u;
  uint64_t size;            /* count of hashed bytes. */
  unsigned H[22];           /* 5 state variables, 16 tmp values, 1 extra */
  bool mDone;

public:
  static const unsigned int HashSize = 20;
  SHA1Sum();
  void update(const uint8_t *dataIn, uint32_t len);
  void finish(uint8_t hashout[20]);
};
}

#endif /* mozilla_SHA1_h_ */
