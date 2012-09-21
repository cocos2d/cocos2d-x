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
 * This section typedefs the old 'native' types to the new <stdint.h> types.
 * These redefinitions are provided solely to allow JSAPI users to more easily
 * transition to <stdint.h> types.  They are not to be used in the JSAPI, and
 * new JSAPI user code should not use them.  This mapping file may eventually
 * be removed from SpiderMonkey, so don't depend on it in the long run.
 */

/*
 * BEWARE: Comity with other implementers of these types is not guaranteed.
 *         Indeed, if you use this header and third-party code defining these
 *         types, *expect* to encounter either compile errors or link errors,
 *         depending how these types are used and on the order of inclusion.
 *         It is safest to use only the JSAPI <stdint.h>-style types,
 *         customizing those types using MOZ_CUSTOM_STDINT_H if necessary.
 */
#ifndef PROTYPES_H
#define PROTYPES_H

#include "mozilla/StandardInteger.h"

#include "js-config.h"

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

/*
 * On AIX 4.3, sys/inttypes.h (which is included by sys/types.h, a very
 * common header file) defines the types int8, int16, int32, and int64.
 * So we don't define these four types here to avoid conflicts in case
 * the code also includes sys/types.h.
 */
#if defined(AIX) && defined(HAVE_SYS_INTTYPES_H)
#include <sys/inttypes.h>
#else
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
#endif /* AIX && HAVE_SYS_INTTYPES_H */

typedef uint8_t JSUint8;
typedef uint16_t JSUint16;
typedef uint32_t JSUint32;
typedef uint64_t JSUint64;

typedef int8_t JSInt8;
typedef int16_t JSInt16;
typedef int32_t JSInt32;
typedef int64_t JSInt64;

#endif /* !defined(PROTYPES_H) */
