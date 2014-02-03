/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsversion_h
#define jsversion_h

/*
 * Deprecated JS_VERSION handler.
 */
#ifdef JS_VERSION
# if JS_VERSION == 185
#  warning "JS_VERSION defined but unsupported (legacy)"
# elif JS_VERSION < 185
#  error "Unsupported JS_VERSION"
# else
#  error "Unknown JS_VERSION"
# endif
#endif

/*
 * JS Capability Macros.
 */
#define JS_HAS_STR_HTML_HELPERS 1       /* has str.anchor, str.bold, etc. */
#define JS_HAS_OBJ_PROTO_PROP   1       /* has o.__proto__ etc. */
#define JS_HAS_OBJ_WATCHPOINT   1       /* has o.watch and o.unwatch */
#define JS_HAS_TOSOURCE         1       /* has Object/Array toSource method */
#define JS_HAS_CATCH_GUARD      1       /* has exception handling catch guard */
#define JS_HAS_UNEVAL           1       /* has uneval() top-level function */
#define JS_HAS_CONST            1       /* has JS2 const as alternative var */
#define JS_HAS_FUN_EXPR_STMT    1       /* has function expression statement */
#define JS_HAS_NO_SUCH_METHOD   1       /* has o.__noSuchMethod__ handler */
#define JS_HAS_FOR_EACH_IN      1       /* has for each (lhs in iterable) */
#define JS_HAS_GENERATORS       1       /* has yield in generator function */
#define JS_HAS_BLOCK_SCOPE      1       /* has block scope via let/arraycomp */
#define JS_HAS_DESTRUCTURING    2       /* has [a,b] = ... or {p:a,q:b} = ... */
#define JS_HAS_GENERATOR_EXPRS  1       /* has (expr for (lhs in iterable)) */
#define JS_HAS_EXPR_CLOSURES    1       /* has function (formals) listexpr */

/* Support for JS_NewGlobalObject. */
#define JS_HAS_NEW_GLOBAL_OBJECT        1

/* Support for JS_MakeSystemObject. */
#define JS_HAS_MAKE_SYSTEM_OBJECT       1

/* Feature-test macro for evolving destructuring support. */
#define JS_HAS_DESTRUCTURING_SHORTHAND  (JS_HAS_DESTRUCTURING == 2)

/*
 * Feature for Object.prototype.__{define,lookup}{G,S}etter__ legacy support;
 * support likely to be made opt-in at some future time.
 */
#define OLD_GETTER_SETTER_METHODS       1

/* A kill-switch for bug 586842.  Embedders shouldn't touch this! */
#define USE_NEW_OBJECT_REPRESENTATION 0

#if USE_NEW_OBJECT_REPRESENTATION
#  define NEW_OBJECT_REPRESENTATION_ONLY() ((void)0)
#else
#  define NEW_OBJECT_REPRESENTATION_ONLY() \
     MOZ_ASSUME_UNREACHABLE("don't call this!  to be used in the new object representation")
#endif

#endif /* jsversion_h */
