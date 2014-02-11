/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implements a UTF-16 character type. */

#ifndef mozilla_Char16_h
#define mozilla_Char16_h

/*
 * C11 and C++11 introduce a char16_t type and support for UTF-16 string and
 * character literals. C++11's char16_t is a distinct builtin type. C11's
 * char16_t is a typedef for uint_least16_t. Technically, char16_t is a 16-bit
 * code unit of a Unicode code point, not a "character".
 */

#ifdef _MSC_VER
   /*
    * C++11 says char16_t is a distinct builtin type, but Windows's yvals.h
    * typedefs char16_t as an unsigned short. We would like to alias char16_t
    * to Windows's 16-bit wchar_t so we can declare UTF-16 literals as constant
    * expressions (and pass char16_t pointers to Windows APIs). We #define
    * _CHAR16T here in order to prevent yvals.h from overriding our char16_t
    * typedefs, which we set to wchar_t for C++ code and to unsigned short for
    * C code.
    *
    * In addition, #defining _CHAR16T will prevent yvals.h from defining a
    * char32_t type, so we have to undo that damage here and provide our own,
    * which is identical to the yvals.h type.
    */
#  define MOZ_UTF16_HELPER(s) L##s
#  define _CHAR16T
#  ifdef __cplusplus
     typedef wchar_t char16_t;
#  else
     typedef unsigned short char16_t;
#  endif
   typedef unsigned int char32_t;
#elif defined(__cplusplus) && \
      (__cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__))
   /* C++11 has a builtin char16_t type. */
#  define MOZ_UTF16_HELPER(s) u##s
   /**
    * This macro is used to distinguish when char16_t would be a distinct
    * typedef from wchar_t.
    */
#  define MOZ_CHAR16_IS_NOT_WCHAR
#elif !defined(__cplusplus)
#  if defined(WIN32)
#    include <yvals.h>
     typedef wchar_t char16_t;
#  else
     /**
      * We can't use the stdint.h uint16_t type here because including
      * stdint.h will break building some of our C libraries, such as
      * sqlite.
      */
     typedef unsigned short char16_t;
#  endif
#else
#  error "Char16.h requires C++11 (or something like it) for UTF-16 support."
#endif

/* This is a temporary hack until bug 927728 is fixed. */
#define __PRUNICHAR__
typedef char16_t PRUnichar;

/*
 * Macro arguments used in concatenation or stringification won't be expanded.
 * Therefore, in order for |MOZ_UTF16(FOO)| to work as expected (which is to
 * expand |FOO| before doing whatever |MOZ_UTF16| needs to do to it) a helper
 * macro, |MOZ_UTF16_HELPER| needs to be inserted in between to allow the macro
 * argument to expand. See "3.10.6 Separate Expansion of Macro Arguments" of the
 * CPP manual for a more accurate and precise explanation.
 */
#define MOZ_UTF16(s) MOZ_UTF16_HELPER(s)

#if defined(__cplusplus) && \
    (__cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__))
static_assert(sizeof(char16_t) == 2, "Is char16_t type 16 bits?");
static_assert(char16_t(-1) > char16_t(0), "Is char16_t type unsigned?");
static_assert(sizeof(MOZ_UTF16('A')) == 2, "Is char literal 16 bits?");
static_assert(sizeof(MOZ_UTF16("")[0]) == 2, "Is string char 16 bits?");
#endif

#endif /* mozilla_Char16_h */
