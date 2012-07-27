/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   IBM Corp.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

#ifndef jstypes_h___
#define jstypes_h___

#include <stddef.h>
#include "js-config.h"

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

#define DEFINE_LOCAL_CLASS_OF_STATIC_FUNCTION(Name) class Name

#if defined(WIN32) || defined(XP_OS2)

/* These also work for __MWERKS__ */
# define JS_EXTERN_API(__type)  extern __declspec(dllexport) __type
# define JS_EXPORT_API(__type)  __declspec(dllexport) __type
# define JS_EXTERN_DATA(__type) extern __declspec(dllexport) __type
# define JS_EXPORT_DATA(__type) __declspec(dllexport) __type

#elif defined(__SYMBIAN32__)

# define JS_EXTERN_API(__type) extern EXPORT_C __type
# define JS_EXPORT_API(__type) EXPORT_C __type
# define JS_EXTERN_DATA(__type) extern EXPORT_C __type
# define JS_EXPORT_DATA(__type) EXPORT_C __type

#else /* Unix */

# ifdef HAVE_VISIBILITY_ATTRIBUTE
#  define JS_EXTERNAL_VIS __attribute__((visibility ("default")))
#  if defined(__GNUC__) && __GNUC__ <= 4 && __GNUC_MINOR__ < 5
    /*
     * GCC wrongly produces a warning when a type with hidden visibility
     * (e.g. js::Value) is a member of a local class of a static function.
     * This is apparently fixed with GCC 4.5 and above.  See:
     *
     *   http://gcc.gnu.org/bugzilla/show_bug.cgi?id=40145.
     */
#   undef  DEFINE_LOCAL_CLASS_OF_STATIC_FUNCTION
#   define DEFINE_LOCAL_CLASS_OF_STATIC_FUNCTION(Name) class __attribute__((visibility ("hidden"))) Name
#  endif
# elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define JS_EXTERNAL_VIS __global
# else
#  define JS_EXTERNAL_VIS
# endif

# define JS_EXTERN_API(__type)  extern JS_EXTERNAL_VIS __type
# define JS_EXPORT_API(__type)  JS_EXTERNAL_VIS __type
# define JS_EXTERN_DATA(__type) extern JS_EXTERNAL_VIS __type
# define JS_EXPORT_DATA(__type) JS_EXTERNAL_VIS __type

#endif

#ifdef _WIN32
# if defined(__MWERKS__) || defined(__GNUC__)
#  define JS_IMPORT_API(__x)    __x
# else
#  define JS_IMPORT_API(__x)    __declspec(dllimport) __x
# endif
#elif defined(XP_OS2)
# define JS_IMPORT_API(__x)     __declspec(dllimport) __x
#elif defined(__SYMBIAN32__)
# define JS_IMPORT_API(__x)     IMPORT_C __x
#else
# define JS_IMPORT_API(__x)     JS_EXPORT_API (__x)
#endif

#if defined(_WIN32) && !defined(__MWERKS__)
# define JS_IMPORT_DATA(__x)      __declspec(dllimport) __x
#elif defined(XP_OS2)
# define JS_IMPORT_DATA(__x)      __declspec(dllimport) __x
#elif defined(__SYMBIAN32__)
# if defined(__CW32__)
#   define JS_IMPORT_DATA(__x)    __declspec(dllimport) __x
# else
#   define JS_IMPORT_DATA(__x)    IMPORT_C __x
# endif
#else
# define JS_IMPORT_DATA(__x)     JS_EXPORT_DATA (__x)
#endif

/*
 * The linkage of JS API functions differs depending on whether the file is
 * used within the JS library or not. Any source file within the JS
 * interpreter should define EXPORT_JS_API whereas any client of the library
 * should not. STATIC_JS_API is used to build JS as a static library.
 */
#if defined(STATIC_JS_API)

# define JS_PUBLIC_API(t)   t
# define JS_PUBLIC_DATA(t)  t

#elif defined(EXPORT_JS_API) || defined(STATIC_EXPORTABLE_JS_API)

# define JS_PUBLIC_API(t)   JS_EXPORT_API(t)
# define JS_PUBLIC_DATA(t)  JS_EXPORT_DATA(t)

#else

# define JS_PUBLIC_API(t)   JS_IMPORT_API(t)
# define JS_PUBLIC_DATA(t)  JS_IMPORT_DATA(t)

#endif

#define JS_FRIEND_API(t)    JS_PUBLIC_API(t)
#define JS_FRIEND_DATA(t)   JS_PUBLIC_DATA(t)

#if defined(_MSC_VER) && defined(_M_IX86)
#define JS_FASTCALL __fastcall
#elif defined(__GNUC__) && defined(__i386__) &&                         \
  ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define JS_FASTCALL __attribute__((fastcall))
#else
#define JS_FASTCALL
#define JS_NO_FASTCALL
#endif

#ifndef JS_INLINE
# if defined __cplusplus
#  define JS_INLINE          inline
# elif defined _MSC_VER
#  define JS_INLINE          __inline
# elif defined __GNUC__
#  define JS_INLINE          __inline__
# else
#  define JS_INLINE          inline
# endif
#endif

#ifndef JS_ALWAYS_INLINE
# if defined DEBUG
#  define JS_ALWAYS_INLINE   JS_INLINE
# elif defined _MSC_VER
#  define JS_ALWAYS_INLINE   __forceinline
# elif defined __GNUC__
#  define JS_ALWAYS_INLINE   __attribute__((always_inline)) JS_INLINE
# else
#  define JS_ALWAYS_INLINE   JS_INLINE
# endif
#endif

#ifndef JS_NEVER_INLINE
# if defined _MSC_VER
#  define JS_NEVER_INLINE __declspec(noinline)
# elif defined __GNUC__
#  define JS_NEVER_INLINE __attribute__((noinline))
# else
#  define JS_NEVER_INLINE
# endif
#endif

#ifndef JS_WARN_UNUSED_RESULT
# if defined __GNUC__
#  define JS_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
# else
#  define JS_WARN_UNUSED_RESULT
# endif
#endif

#ifdef NS_STATIC_CHECKING
/*
 * Attributes for static analysis. Functions declared with JS_REQUIRES_STACK
 * always have a valid cx->fp and can access it freely.  Other functions can
 * access cx->fp only after calling a function that "forces" the stack
 * (i.e. lazily instantiates it as needed).
 */
# define JS_REQUIRES_STACK   __attribute__((user("JS_REQUIRES_STACK")))
# define JS_FORCES_STACK     __attribute__((user("JS_FORCES_STACK")))
/*
 * Skip the JS_REQUIRES_STACK analysis within functions with this annotation.
 */
# define JS_IGNORE_STACK     __attribute__((user("JS_IGNORE_STACK")))
#else
# define JS_REQUIRES_STACK
# define JS_FORCES_STACK
# define JS_IGNORE_STACK
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
#ifdef __cplusplus

# define JS_BEGIN_EXTERN_C      extern "C" {
# define JS_END_EXTERN_C        }

#else

# define JS_BEGIN_EXTERN_C
# define JS_END_EXTERN_C

#endif

/***********************************************************************
** MACROS:      JS_BIT
**              JS_BITMASK
** DESCRIPTION:
** Bit masking macros.  XXX n must be <= 31 to be portable
***********************************************************************/
#define JS_BIT(n)       ((JSUint32)1 << (n))
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
#define JS_MIN(x,y)     ((x)<(y)?(x):(y))
#define JS_MAX(x,y)     ((x)>(y)?(x):(y))

#ifdef _MSC_VER
# include "jscpucfg.h"  /* We can't auto-detect MSVC configuration */
# if _MSC_VER < 1400
#  define NJ_NO_VARIADIC_MACROS
# endif
#else
# include "jsautocfg.h" /* Use auto-detected configuration */
#endif

/*
 * Define JS_64BIT iff we are building in an environment with 64-bit
 * addresses.
 */
#ifdef _MSC_VER
# if defined(_M_X64) || defined(_M_AMD64)
#  define JS_64BIT
# endif
#elif defined(__GNUC__)
# ifdef __x86_64__
#  define JS_64BIT
# endif
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# ifdef __x86_64
#  define JS_64BIT
# endif
#else
# error "Implement me"
#endif


#include "jsinttypes.h"

JS_BEGIN_EXTERN_C

/************************************************************************
** TYPES:       JSUintn
**              JSIntn
** DESCRIPTION:
**  The JSIntn types are most appropriate for automatic variables. They are
**      guaranteed to be at least 16 bits, though various architectures may
**      define them to be wider (e.g., 32 or even 64 bits). These types are
**      never valid for fields of a structure.
************************************************************************/

typedef int JSIntn;
typedef unsigned int JSUintn;

/************************************************************************
** TYPES:       JSFloat64
** DESCRIPTION:
**  NSPR's floating point type is always 64 bits.
************************************************************************/
typedef double          JSFloat64;

/************************************************************************
** TYPES:       JSSize
** DESCRIPTION:
**  A type for representing the size of objects.
************************************************************************/
typedef size_t JSSize;

/************************************************************************
** TYPES:       JSPtrDiff
** DESCRIPTION:
**  A type for pointer difference. Variables of this type are suitable
**      for storing a pointer or pointer sutraction.
************************************************************************/
typedef ptrdiff_t JSPtrdiff;

/************************************************************************
** TYPES:       JSUptrdiff
** DESCRIPTION:
**  A type for pointer difference. Variables of this type are suitable
**      for storing a pointer or pointer sutraction.
************************************************************************/
typedef JSUintPtr JSUptrdiff;

/************************************************************************
** TYPES:       JSBool
** DESCRIPTION:
**  Use JSBool for variables and parameter types. Use JS_FALSE and JS_TRUE
**      for clarity of target type in assignments and actual arguments. Use
**      'if (bool)', 'while (!bool)', '(bool) ? x : y' etc., to test booleans
**      just as you would C int-valued conditions.
************************************************************************/
typedef JSIntn JSBool;
#define JS_TRUE (JSIntn)1
#define JS_FALSE (JSIntn)0
/*
** Special: JS_NEITHER is used by the tracer to have tri-state booleans.
** This should not be used in new code.
*/
#define JS_NEITHER (JSIntn)2

/************************************************************************
** TYPES:       JSPackedBool
** DESCRIPTION:
**  Use JSPackedBool within structs where bitfields are not desireable
**      but minimum and consistent overhead matters.
************************************************************************/
typedef JSUint8 JSPackedBool;

/*
** A JSWord is an integer that is the same size as a void*
*/
typedef JSIntPtr JSWord;
typedef JSUintPtr JSUword;

#include "jsotypes.h"

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
#if defined(__GNUC__) && (__GNUC__ > 2)

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

#define JS_BITS_PER_WORD (JS_BITS_PER_BYTE * JS_BYTES_PER_WORD)
#define JS_BITS_PER_DOUBLE (JS_BITS_PER_BYTE * JS_BYTES_PER_DOUBLE)

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

JS_END_EXTERN_C

#endif /* jstypes_h___ */
