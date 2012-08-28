/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Code.
 *
 * The Initial Developer of the Original Code is
 *   The Mozilla Foundation
 * Portions created by the Initial Developer are Copyright (C) 2011
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Jeff Walden <jwalden+code@mit.edu> (original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

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
