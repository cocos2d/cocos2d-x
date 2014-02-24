/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
** File:                jstypes.h
** Description: Definitions of NSPR's basic types
**
** Prototypes and macros used to make up for deficiencies in ANSI environments
** that we have found.
**
** Since we do not wrap <stdlib.h> and all the other standard headers, authors
** of portable code will not know in general that they need these definitions.
** Instead of requiring these authors to find the dependent uses in their code
** and take the following steps only in those C files, we take steps once here
** for all C files.
**/

#ifndef jstypes_h
#define jstypes_h

#include "mozilla/Attributes.h"
#include "mozilla/Types.h"

// jstypes.h is (or should be!) included by every file in SpiderMonkey.
// js-config.h and jsversion.h also should be included by every file.
// So include them here.
// XXX: including them in js/RequiredDefines.h should be a better option, since
// that is by definition the header file that should be included in all
// SpiderMonkey code.  However, Gecko doesn't do this!  See bug 909576.
#include "js-config.h"
#include "jsversion.h"

/***********************************************************************
** MACROS:      JS_EXTERN_API
**              JS_EXPORT_API
** DESCRIPTION:
**      These are only for externally visible routines and globals.  For
**      internal routines, just use "extern" for type checking and that
**      will not export internal cross-file or forward-declared symbols.
**      Define a macro for declaring procedures return types. We use this to
**      deal with windoze specific type hackery for DLL definitions. Use
**      JS_EXTERN_API when the prototype for the method is declared. Use
**      JS_EXPORT_API for the implementation of the method.
**
** Example:
**   in dowhim.h
**     JS_EXTERN_API( void ) DoWhatIMean( void );
**   in dowhim.c
**     JS_EXPORT_API( void ) DoWhatIMean( void ) { return; }
**
**
***********************************************************************/

#define JS_EXTERN_API(type)  extern MOZ_EXPORT type
#define JS_EXPORT_API(type)  MOZ_EXPORT type
#define JS_EXPORT_DATA(type) MOZ_EXPORT type
#define JS_IMPORT_API(type)  MOZ_IMPORT_API type
#define JS_IMPORT_DATA(type) MOZ_IMPORT_DATA type

/*
 * The linkage of JS API functions differs depending on whether the file is
 * used within the JS library or not. Any source file within the JS
 * interpreter should define EXPORT_JS_API whereas any client of the library
 * should not. STATIC_JS_API is used to build JS as a static library.
 */
#if defined(STATIC_JS_API)
#  define JS_PUBLIC_API(t)   t
#  define JS_PUBLIC_DATA(t)  t
#elif defined(EXPORT_JS_API) || defined(STATIC_EXPORTABLE_JS_API)
#  define JS_PUBLIC_API(t)   MOZ_EXPORT t
#  define JS_PUBLIC_DATA(t)  MOZ_EXPORT t
#else
#  define JS_PUBLIC_API(t)   MOZ_IMPORT_API t
#  define JS_PUBLIC_DATA(t)  MOZ_IMPORT_DATA t
#endif

#define JS_FRIEND_API(t)    JS_PUBLIC_API(t)
#define JS_FRIEND_DATA(t)   JS_PUBLIC_DATA(t)

#if defined(_MSC_VER) && defined(_M_IX86)
#define JS_FASTCALL __fastcall
#elif defined(__GNUC__) && defined(__i386__)
#define JS_FASTCALL __attribute__((fastcall))
#else
#define JS_FASTCALL
#define JS_NO_FASTCALL
#endif

#ifndef JS_ALWAYS_INLINE
#define JS_ALWAYS_INLINE MOZ_ALWAYS_INLINE
#endif

#ifndef JS_NEVER_INLINE
#define JS_NEVER_INLINE MOZ_NEVER_INLINE
#endif

#ifndef JS_WARN_UNUSED_RESULT
# if defined __GNUC__
#  define JS_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
# else
#  define JS_WARN_UNUSED_RESULT
# endif
#endif

/***********************************************************************
** MACROS:      JS_BEGIN_MACRO
**              JS_END_MACRO
** DESCRIPTION:
**      Macro body brackets so that macros with compound statement definitions
**      behave syntactically more like functions when called.
***********************************************************************/
#define JS_BEGIN_MACRO  do {

#if defined(_MSC_VER) && _MSC_VER >= 1400
# define JS_END_MACRO                                                         \
    } __pragma(warning(push)) __pragma(warning(disable:4127))                 \
    while (0) __pragma(warning(pop))
#else
# define JS_END_MACRO   } while (0)
#endif

/***********************************************************************
** MACROS:      JS_BEGIN_EXTERN_C
**              JS_END_EXTERN_C
** DESCRIPTION:
**      Macro shorthands for conditional C++ extern block delimiters.
***********************************************************************/
#define JS_BEGIN_EXTERN_C      MOZ_BEGIN_EXTERN_C
#define JS_END_EXTERN_C        MOZ_END_EXTERN_C

/***********************************************************************
** MACROS:      JS_BIT
**              JS_BITMASK
** DESCRIPTION:
** Bit masking macros.  XXX n must be <= 31 to be portable
***********************************************************************/
#define JS_BIT(n)       ((uint32_t)1 << (n))
#define JS_BITMASK(n)   (JS_BIT(n) - 1)

/***********************************************************************
** MACROS:      JS_HOWMANY
**              JS_ROUNDUP
**              JS_MIN
**              JS_MAX
** DESCRIPTION:
**      Commonly used macros for operations on compatible types.
***********************************************************************/
#define JS_HOWMANY(x,y) (((x)+(y)-1)/(y))
#define JS_ROUNDUP(x,y) (JS_HOWMANY(x,y)*(y))

#include "jscpucfg.h"

/*
 * Define JS_64BIT iff we are building in an environment with 64-bit
 * addresses.
 */
#ifdef _MSC_VER
# if defined(_M_X64) || defined(_M_AMD64)
#  define JS_64BIT
# endif
#elif defined(__GNUC__)
/* Additional GCC defines are when running on Solaris, AIX, and HPUX */
# if defined(__x86_64__) || defined(__sparcv9) || \
        defined(__64BIT__) || defined(__LP64__)
#  define JS_64BIT
# endif
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC) /* Sun Studio C/C++ */
# if defined(__x86_64) || defined(__sparcv9)
#  define JS_64BIT
# endif
#elif defined(__xlc__) || defined(__xlC__)        /* IBM XL C/C++ */
# if defined(__64BIT__)
#  define JS_64BIT
# endif
#elif defined(__HP_cc) || defined(__HP_aCC)       /* HP-UX cc/aCC */
# if defined(__LP64__)
#  define JS_64BIT
# endif
#else
# error "Implement me"
#endif

/***********************************************************************
** MACROS:      JS_LIKELY
**              JS_UNLIKELY
** DESCRIPTION:
**      These macros allow you to give a hint to the compiler about branch
**      probability so that it can better optimize.  Use them like this:
**
**      if (JS_LIKELY(v == 1)) {
**          ... expected code path ...
**      }
**
**      if (JS_UNLIKELY(v == 0)) {
**          ... non-expected code path ...
**      }
**
***********************************************************************/
#ifdef __GNUC__

# define JS_LIKELY(x)   (__builtin_expect((x), 1))
# define JS_UNLIKELY(x) (__builtin_expect((x), 0))

#else

# define JS_LIKELY(x)   (x)
# define JS_UNLIKELY(x) (x)

#endif

/***********************************************************************
** MACROS:      JS_ARRAY_LENGTH
**              JS_ARRAY_END
** DESCRIPTION:
**      Macros to get the number of elements and the pointer to one past the
**      last element of a C array. Use them like this:
**
**      jschar buf[10], *s;
**      JSString *str;
**      ...
**      for (s = buf; s != JS_ARRAY_END(buf); ++s) *s = ...;
**      ...
**      str = JS_NewStringCopyN(cx, buf, JS_ARRAY_LENGTH(buf));
**      ...
**
***********************************************************************/

#define JS_ARRAY_LENGTH(array) (sizeof (array) / sizeof (array)[0])
#define JS_ARRAY_END(array)    ((array) + JS_ARRAY_LENGTH(array))

#define JS_BITS_PER_BYTE 8
#define JS_BITS_PER_BYTE_LOG2 3

#if defined(JS_64BIT)
# define JS_BITS_PER_WORD 64
#else
# define JS_BITS_PER_WORD 32
#endif

/***********************************************************************
** MACROS:      JS_FUNC_TO_DATA_PTR
**              JS_DATA_TO_FUNC_PTR
** DESCRIPTION:
**      Macros to convert between function and data pointers assuming that
**      they have the same size. Use them like this:
**
**      JSPropertyOp nativeGetter;
**      JSObject *scriptedGetter;
**      ...
**      scriptedGetter = JS_FUNC_TO_DATA_PTR(JSObject *, nativeGetter);
**      ...
**      nativeGetter = JS_DATA_TO_FUNC_PTR(JSPropertyOp, scriptedGetter);
**
***********************************************************************/

#ifdef __GNUC__
# define JS_FUNC_TO_DATA_PTR(type, fun) (__extension__ (type) (size_t) (fun))
# define JS_DATA_TO_FUNC_PTR(type, ptr) (__extension__ (type) (size_t) (ptr))
#else
/* Use an extra (void *) cast for MSVC. */
# define JS_FUNC_TO_DATA_PTR(type, fun) ((type) (void *) (fun))
# define JS_DATA_TO_FUNC_PTR(type, ptr) ((type) (void *) (ptr))
#endif

#ifdef __GNUC__
# define JS_EXTENSION __extension__
# define JS_EXTENSION_(s) __extension__ ({ s; })
#else
# define JS_EXTENSION
# define JS_EXTENSION_(s) s
#endif

#endif /* jstypes_h */
