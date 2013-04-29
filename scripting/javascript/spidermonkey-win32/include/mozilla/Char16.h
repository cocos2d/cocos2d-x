/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implements a UTF-16 character type. */

#ifndef mozilla_Char16_h_
#define mozilla_Char16_h_

#include "mozilla/Assertions.h"

/*
 * C11 and C++11 introduce a char16_t type and support for UTF-16 string and
 * character literals. C++11's char16_t is a distinct builtin type. C11's
 * char16_t is a typedef for uint_least16_t. Technically, char16_t is a 16-bit
 * code unit of a Unicode code point, not a "character".
 *
 * For now, Char16.h only supports C++ because we don't want mix different C
 * and C++ definitions of char16_t in the same code base.
 */

#ifdef _MSC_VER
   /*
    * C++11 says char16_t is a distinct builtin type, but Windows's yvals.h
    * typedefs char16_t as an unsigned short. We would like to alias char16_t
    * to Windows's 16-bit wchar_t so we can declare UTF-16 literals as constant
    * expressions (and pass char16_t pointers to Windows APIs). We #define our
    * char16_t as a macro to override yval.h's typedef of the same name.
    */
#  define MOZ_UTF16_HELPER(s) L##s
#  include <yvals.h>
#  define char16_t wchar_t
#elif defined(__cplusplus) && \
      (__cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__))
   /* C++11 has a builtin char16_t type. */
#  define MOZ_UTF16_HELPER(s) u##s
#else
#  error "Char16.h requires C++11 (or something like it) for UTF-16 support."
#endif

/*
 * Macro arguments used in concatenation or stringification won't be expanded.
 * Therefore, in order for |MOZ_UTF16(FOO)| to work as expected (which is to
 * expand |FOO| before doing whatever |MOZ_UTF16| needs to do to it) a helper
 * macro, |MOZ_UTF16_HELPER| needs to be inserted in between to allow the macro
 * argument to expand. See "3.10.6 Separate Expansion of Macro Arguments" of the
 * CPP manual for a more accurate and precise explanation.
 */
#define MOZ_UTF16(s) MOZ_UTF16_HELPER(s)

MOZ_STATIC_ASSERT(sizeof(char16_t) == 2, "Is char16_t type 16 bits?");
MOZ_STATIC_ASSERT(sizeof(MOZ_UTF16('A')) == 2, "Is char literal 16 bits?");
MOZ_STATIC_ASSERT(sizeof(MOZ_UTF16("")[0]) == 2, "Is string char 16 bits?");

#endif /* mozilla_Char16_h_ */
