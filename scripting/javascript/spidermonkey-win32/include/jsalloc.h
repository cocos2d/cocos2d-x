/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsalloc_h_
#define jsalloc_h_

#include "jspubtd.h"
#include "jsutil.h"

namespace js {

/*
 * Allocation policies.  These model the concept:
 *  - public copy constructor, assignment, destructor
 *  - void *malloc_(size_t)
 *      Responsible for OOM reporting on NULL return value.
 *  - void *realloc_(size_t)
 *      Responsible for OOM reporting on NULL return value.
 *      The *used* bytes of the previous buffer is passed in
 *      (rather than the old allocation size), in addition to
 *      the *new* allocation size requested.
 *  - void free_(void *)
 *  - reportAllocOverflow()
 *      Called on overflow before the container returns NULL.
 */

/* Policy for using system memory functions and doing no error reporting. */
class SystemAllocPolicy
{
  public:
    void *malloc_(size_t bytes) { return js_malloc(bytes); }
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
    JSContext *const cx;

    /*
     * Non-inline helper to call JSRuntime::onOutOfMemory with minimal
     * code bloat.
     */
    JS_FRIEND_API(void *) onOutOfMemory(void *p, size_t nbytes);

  public:
    TempAllocPolicy(JSContext *cx) : cx(cx) {}

    JSContext *context() const {
        return cx;
    }

    void *malloc_(size_t bytes) {
        void *p = js_malloc(bytes);
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

#endif /* jsalloc_h_ */
