/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implements the C99 <stdint.h> interface for C and C++ code. */

#ifndef mozilla_StandardInteger_h_
#define mozilla_StandardInteger_h_

/*
 * The C99 standard header <stdint.h> exposes typedefs for common fixed-width
 * integer types.  It would be feasible to simply #include <stdint.h>, but
 * MSVC++ versions prior to 2010 don't provide <stdint.h>.  We could solve this
 * by reimplementing <stdint.h> for MSVC++ 2008 and earlier.  But then we reach
 * a second problem: our custom <stdint.h> might conflict with a <stdint.h>
 * defined by an embedder already looking to work around the MSVC++ <stdint.h>
 * absence.
 *
 * We address these issues in this manner:
 *
 *   1. If the preprocessor macro MOZ_CUSTOM_STDINT_H is defined to a path to a
 *      custom <stdint.h> implementation, we will #include it.  Embedders using
 *      a custom <stdint.h> must define this macro to an implementation that
 *      will work with their embedding.
 *   2. Otherwise, if we are compiling with a an MSVC++ version without
 *      <stdint.h>, #include our custom <stdint.h> reimplementation.
 *   3. Otherwise, #include the standard <stdint.h> provided by the compiler.
 *
 * Note that we can't call this file "stdint.h" or something case-insensitively
 * equal to "stdint.h" because then MSVC (and other compilers on
 * case-insensitive file systems) will include this file, rather than the system
 * stdint.h, when we ask for <stdint.h> below.
 */
#if defined(MOZ_CUSTOM_STDINT_H)
#  include MOZ_CUSTOM_STDINT_H
#elif defined(_MSC_VER) && _MSC_VER < 1600
#  include "mozilla/MSStdInt.h"
#else
#  include <stdint.h>
#endif

#endif  /* mozilla_StandardInteger_h_ */
