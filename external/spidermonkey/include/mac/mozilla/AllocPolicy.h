/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * An allocation policy concept, usable for structures and algorithms to
 * control how memory is allocated and how failures are handled.
 */

#ifndef mozilla_AllocPolicy_h
#define mozilla_AllocPolicy_h

#include <stddef.h>
#include <stdlib.h>

namespace mozilla {

/*
 * Allocation policies are used to implement the standard allocation behaviors
 * in a customizable way.  Additionally, custom behaviors may be added to these
 * behaviors, such as additionally reporting an error through an out-of-band
 * mechanism when OOM occurs.  The concept modeled here is as follows:
 *
 *  - public copy constructor, assignment, destructor
 *  - void* malloc_(size_t)
 *      Responsible for OOM reporting when null is returned.
 *  - void* calloc_(size_t)
 *      Responsible for OOM reporting when null is returned.
 *  - void* realloc_(void*, size_t, size_t)
 *      Responsible for OOM reporting when null is returned.  The *used* bytes
 *      of the previous buffer is passed in (rather than the old allocation
 *      size), in addition to the *new* allocation size requested.
 *  - void free_(void*)
 *  - void reportAllocOverflow() const
 *      Called on allocation overflow (that is, an allocation implicitly tried
 *      to allocate more than the available memory space -- think allocating an
 *      array of large-size objects, where N * size overflows) before null is
 *      returned.
 *
 * mfbt provides (and typically uses by default) only MallocAllocPolicy, which
 * does nothing more than delegate to the malloc/alloc/free functions.
 */

/*
 * A policy that straightforwardly uses malloc/calloc/realloc/free and adds no
 * extra behaviors.
 */
class MallocAllocPolicy
{
  public:
    void* malloc_(size_t bytes) { return malloc(bytes); }
    void* calloc_(size_t bytes) { return calloc(bytes, 1); }
    void* realloc_(void* p, size_t oldBytes, size_t bytes) { return realloc(p, bytes); }
    void free_(void* p) { free(p); }
    void reportAllocOverflow() const {}
};


} // namespace mozilla

#endif /* mozilla_AllocPolicy_h */
