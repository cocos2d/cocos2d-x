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

/* mfbt foundational types and macros. */

#ifndef mozilla_Types_h_
#define mozilla_Types_h_

/*
 * This header must be valid C and C++, includable by code embedding either
 * SpiderMonkey or Gecko.
 */

/*
 * Expose all the integer types defined in C99's <stdint.h> (and the integer
 * limit and constant macros, if compiling C code or if compiling C++ code and
 * the right __STDC_*_MACRO has been defined for each).  These are all usable
 * throughout mfbt code, and throughout Mozilla code more generally.
 */
#include "mozilla/StandardInteger.h"

/* Also expose size_t. */
#include <stddef.h>

/* Implement compiler and linker macros needed for APIs. */

/*
 * MOZ_EXPORT_API is used to declare and define a method which is externally
 * visible to users of the current library.  It encapsulates various decorations
 * needed to properly export the method's symbol.  MOZ_EXPORT_DATA serves the
 * same purpose for data.
 *
 *   api.h:
 *     extern MOZ_EXPORT_API(int) MeaningOfLife(void);
 *     extern MOZ_EXPORT_DATA(int) LuggageCombination;
 *
 *   api.c:
 *     MOZ_EXPORT_API(int) MeaningOfLife(void) { return 42; }
 *     MOZ_EXPORT_DATA(int) LuggageCombination = 12345;
 *
 * If you are merely sharing a method across files, just use plain |extern|.
 * These macros are designed for use by library interfaces -- not for normal
 * methods or data used cross-file.
 */
#if defined(WIN32) || defined(XP_OS2)
#  define MOZ_EXPORT_API(type)    __declspec(dllexport) type
#  define MOZ_EXPORT_DATA(type)   __declspec(dllexport) type
#else /* Unix */
#  ifdef HAVE_VISIBILITY_ATTRIBUTE
#    define MOZ_EXTERNAL_VIS       __attribute__((visibility("default")))
#  elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#    define MOZ_EXTERNAL_VIS      __global
#  else
#    define MOZ_EXTERNAL_VIS
#  endif
#  define MOZ_EXPORT_API(type)    MOZ_EXTERNAL_VIS type
#  define MOZ_EXPORT_DATA(type)   MOZ_EXTERNAL_VIS type
#endif

/*
 * Whereas implementers use MOZ_EXPORT_API and MOZ_EXPORT_DATA to declare and
 * define library symbols, users use MOZ_IMPORT_API and MOZ_IMPORT_DATA to
 * access them.  Most often the implementer of the library will expose an API
 * macro which expands to either the export or import version of the macro,
 * depending upon the compilation mode.
 */
#ifdef _WIN32
#  if defined(__MWERKS__)
#    define MOZ_IMPORT_API(x)    x
#  else
#    define MOZ_IMPORT_API(x)    __declspec(dllimport) x
#  endif
#elif defined(XP_OS2)
#  define MOZ_IMPORT_API(x)     __declspec(dllimport) x
#else
#  define MOZ_IMPORT_API(x)     MOZ_EXPORT_API(x)
#endif

#if defined(_WIN32) && !defined(__MWERKS__)
#  define MOZ_IMPORT_DATA(x)     __declspec(dllimport) x
#elif defined(XP_OS2)
#  define MOZ_IMPORT_DATA(x)     __declspec(dllimport) x
#else
#  define MOZ_IMPORT_DATA(x)     MOZ_EXPORT_DATA(x)
#endif

/*
 * Consistent with the above comment, the MFBT_API and MFBT_DATA macros expose
 * export mfbt declarations when building mfbt, and they expose import mfbt
 * declarations when using mfbt.
 */
#if defined(IMPL_MFBT)
#  define MFBT_API(type)        MOZ_EXPORT_API(type)
#  define MFBT_DATA(type)       MOZ_EXPORT_DATA(type)
#else
  /*
   * When mozglue is linked in the program, we need the MFBT API symbols
   * to be weak.
   */
#  if defined(MOZ_GLUE_IN_PROGRAM)
#    define MFBT_API(type)        __attribute__((weak)) MOZ_IMPORT_API(type)
#    define MFBT_DATA(type)       __attribute__((weak)) MOZ_IMPORT_DATA(type)
#  else
#    define MFBT_API(type)        MOZ_IMPORT_API(type)
#    define MFBT_DATA(type)       MOZ_IMPORT_DATA(type)
#  endif
#endif

/*
 * C symbols in C++ code must be declared immediately within |extern "C"|
 * blocks.  However, in C code, they need not be declared specially.  This
 * difference is abstracted behind the MOZ_BEGIN_EXTERN_C and MOZ_END_EXTERN_C
 * macros, so that the user need not know whether he is being used in C or C++
 * code.
 *
 *   MOZ_BEGIN_EXTERN_C
 *
 *   extern MOZ_EXPORT_API(int) MostRandomNumber(void);
 *   ...other declarations...
 *
 *   MOZ_END_EXTERN_C
 *
 * This said, it is preferable to just use |extern "C"| in C++ header files for
 * its greater clarity.
 */
#ifdef __cplusplus
#  define MOZ_BEGIN_EXTERN_C    extern "C" {
#  define MOZ_END_EXTERN_C      }
#else
#  define MOZ_BEGIN_EXTERN_C
#  define MOZ_END_EXTERN_C
#endif

#endif  /* mozilla_Types_h_ */
