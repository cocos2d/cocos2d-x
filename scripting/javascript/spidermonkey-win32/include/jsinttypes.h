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
 * The Original Code is Mozilla SpiderMonkey JavaScript 1.9 code, released
 * May 28, 2008.
 *
 * The Initial Developer of the Original Code is
 *   Jim Blandy <jimb@mozilla.org>
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
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

#ifndef jsinttypes_h___
#define jsinttypes_h___

#include "js-config.h"

/*
 * Types:
 *   JSInt<N>, JSUint<N> (for <N> = 8, 16, 32, and 64)
 *   JSIntPtr, JSUIntPtr
 *
 * JSInt<N> and JSUint<N> are signed and unsigned types known to be
 * <N> bits long.  Note that neither JSInt8 nor JSUInt8 is necessarily
 * equivalent to a plain "char".
 *
 * JSIntPtr and JSUintPtr are signed and unsigned types capable of
 * holding an object pointer.
 *
 * Use these types in public SpiderMonkey header files, not the
 * corresponding types from the C standard <stdint.h> header.  Windows
 * doesn't support <stdint.h>, and Microsoft says it has no plans to
 * do so in the future; this means that projects that embed
 * SpiderMonkey often take matters into their own hands and define the
 * standard types themselves.  If we define them in our public
 * headers, our definitions may conflict with embedders' (see bug
 * 479258).  The JS* types are in our namespace, and can be used
 * without troubling anyone.
 *
 * Internal SpiderMonkey code wishing to use the type names ISO C
 * defines in the standard header <stdint.h> can #include
 * "jsstdint.h", which provides those types regardless of whether
 * <stdint.h> itself is available.
 */

#if defined(JS_HAVE_STDINT_H) || \
    defined(JS_SYS_TYPES_H_DEFINES_EXACT_SIZE_TYPES)

#if defined(JS_HAVE_STDINT_H)
#include <stdint.h>
#else
#include <sys/types.h>
#endif

typedef int8_t   JSInt8;
typedef int16_t  JSInt16;
typedef int32_t  JSInt32;
typedef int64_t  JSInt64;
typedef intptr_t JSIntPtr;

typedef uint8_t   JSUint8;
typedef uint16_t  JSUint16;
typedef uint32_t  JSUint32;
typedef uint64_t  JSUint64;
typedef uintptr_t JSUintPtr;

#else

#if defined(JS_HAVE___INTN)

typedef __int8  JSInt8;
typedef __int16 JSInt16;
typedef __int32 JSInt32;
typedef __int64 JSInt64;

typedef unsigned __int8 JSUint8;
typedef unsigned __int16 JSUint16;
typedef unsigned __int32 JSUint32;
typedef unsigned __int64 JSUint64;

#elif defined(JS_INT8_TYPE)

typedef signed JS_INT8_TYPE   JSInt8;
typedef signed JS_INT16_TYPE  JSInt16;
typedef signed JS_INT32_TYPE  JSInt32;
typedef signed JS_INT64_TYPE  JSInt64;

typedef unsigned JS_INT8_TYPE   JSUint8;
typedef unsigned JS_INT16_TYPE  JSUint16;
typedef unsigned JS_INT32_TYPE  JSUint32;
typedef unsigned JS_INT64_TYPE  JSUint64;

#else
#error "couldn't find exact-width integer types"
#endif

/* Microsoft Visual C/C++ defines intptr_t and uintptr_t in <stddef.h>.  */
#if defined(JS_STDDEF_H_HAS_INTPTR_T)
#include <stddef.h>
typedef intptr_t JSIntPtr;
typedef uintptr_t JSUintPtr;

/* Windows Mobile defines intptr_t and uintptr_t in <crtdefs.h>.  Why not?  */
#elif defined(JS_CRTDEFS_H_HAS_INTPTR_T)
#include <crtdefs.h>
typedef intptr_t JSIntPtr;
typedef uintptr_t JSUintPtr;

/* Failing that, the configure script will have found something.  */
#elif defined(JS_INTPTR_TYPE)
typedef signed   JS_INTPTR_TYPE JSIntPtr;
typedef unsigned JS_INTPTR_TYPE JSUintPtr;

#else
#error "couldn't find pointer-sized integer types"
#endif

#endif /* JS_HAVE_STDINT_H */

#endif /* jsinttypes_h___ */
