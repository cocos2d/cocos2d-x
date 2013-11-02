/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* JS allocation policies. */

#ifndef jsalloc_h
#define jsalloc_h

#include "mozilla/AllocPolicy.h"

#include "js/Utility.h"

struct JSContext;

namespace js {

class ContextFriendFields;

/* Policy for using system memory functions and doing no error reporting. */
class SystemAllocPolicy
{
  public:
    void *malloc_(size_t bytes) { return js_malloc(bytes); }
    void *calloc_(size_t bytes) { return js_calloc(bytes); }
    void *realloc_(void *p, size_t oldBytes, size_t bytes) { return js_realloc(p, bytes); }
    void free_(void *p) { js_free(p); }
    void reportAllocOverflow() const {}
};

/*
 * Allocation policy that calls the system memory functions and reports errors
 * to the context. Since the JSContext given on construction is stored for
 * the lifetime of the container, this policy may only be used for containers
 * whose lifetime is a shorter than the given JSContext.
 *
 * FIXME bug 647103 - rewrite this in terms of temporary allocation functions,
 * not the system ones.
 */
class TempAllocPolicy
{
    ContextFriendFields *const cx_;

    /*
     * Non-inline helper to call JSRuntime::onOutOfMemory with minimal
     * code bloat.
     */
    JS_FRIEND_API(void *) onOutOfMemory(void *p, size_t nbytes);

  public:
    TempAllocPolicy(JSContext *cx) : cx_((ContextFriendFields *) cx) {} // :(
    TempAllocPolicy(ContextFriendFields *cx) : cx_(cx) {}

    void *malloc_(size_t bytes) {
        void *p = js_malloc(bytes);
        if (JS_UNLIKELY(!p))
            p = onOutOfMemory(NULL, bytes);
        return p;
    }

    void *calloc_(size_t bytes) {
        void *p = js_calloc(bytes);
        if (JS_UNLIKELY(!p))
            p = onOutOfMemory(NULL, bytes);
        return p;
    }

    void *realloc_(void *p, size_t oldBytes, size_t bytes) {
        void *p2 = js_realloc(p, bytes);
        if (JS_UNLIKELY(!p2))
            p2 = onOutOfMemory(p2, bytes);
        return p2;
    }

    void free_(void *p) {
        js_free(p);
    }

    JS_FRIEND_API(void) reportAllocOverflow() const;
};

} /* namespace js */

#endif /* jsalloc_h */
