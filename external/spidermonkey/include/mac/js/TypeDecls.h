/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// This file contains public type declarations that are used *frequently*.  If
// it doesn't occur at least 10 times in Gecko, it probably shouldn't be in
// here.
//
// It includes only:
// - forward declarations of structs and classes;
// - typedefs;
// - enums (maybe).
// It does *not* contain any struct or class definitions.

#ifndef js_TypeDecls_h
#define js_TypeDecls_h

#include <stddef.h>
#include <stdint.h>

struct JSContext;
class JSFunction;
class JSObject;
class JSScript;
class JSString;

// In release builds, jsid is defined to be an integral type. This
// prevents many bugs from being caught at compile time. E.g.:
//
//  jsid id = ...
//  if (id)             // error
//    ...
//
//  size_t n = id;      // error
//
// To catch more errors, jsid is given a struct type in C++ debug builds.
// Struct assignment and (in C++) operator== allow correct code to be mostly
// oblivious to the change. This feature can be explicitly disabled in debug
// builds by defining JS_NO_JSVAL_JSID_STRUCT_TYPES.
//

// Needed for cocos2d-js
#define JS_NO_JSVAL_JSID_STRUCT_TYPES 

#if defined(DEBUG) && !defined(JS_NO_JSVAL_JSID_STRUCT_TYPES)
# define JS_USE_JSID_STRUCT_TYPES
#endif

#ifdef JS_USE_JSID_STRUCT_TYPES
struct jsid;
#else
typedef ptrdiff_t jsid;
#endif

typedef char16_t jschar;

namespace JS {

class Value;
template <typename T> class Handle;
template <typename T> class MutableHandle;

typedef Handle<JSFunction*> HandleFunction;
typedef Handle<jsid>        HandleId;
typedef Handle<JSObject*>   HandleObject;
typedef Handle<JSScript*>   HandleScript;
typedef Handle<JSString*>   HandleString;
typedef Handle<Value>       HandleValue;

typedef MutableHandle<JSFunction*> MutableHandleFunction;
typedef MutableHandle<jsid>        MutableHandleId;
typedef MutableHandle<JSObject*>   MutableHandleObject;
typedef MutableHandle<JSScript*>   MutableHandleScript;
typedef MutableHandle<JSString*>   MutableHandleString;
typedef MutableHandle<Value>       MutableHandleValue;

} // namespace JS

#endif /* js_TypeDecls_h */
