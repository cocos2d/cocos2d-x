/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_heap_api_h___
#define js_heap_api_h___

/* These values are private to the JS engine. */
namespace js {
namespace gc {

/*
 * Page size must be static to support our arena pointer optimizations, so we
 * are forced to support each platform with non-4096 pages as a special case.
 * Note: The freelist supports a maximum arena shift of 15.
 * Note: Do not use JS_CPU_SPARC here, this header is used outside JS.
 */
#if (defined(SOLARIS) || defined(__FreeBSD__)) && \
    (defined(__sparc) || defined(__sparcv9) || defined(__ia64))
const size_t PageShift = 13;
const size_t ArenaShift = PageShift;
#elif defined(__powerpc64__)
const size_t PageShift = 16;
const size_t ArenaShift = 12;
#else
const size_t PageShift = 12;
const size_t ArenaShift = PageShift;
#endif
const size_t PageSize = size_t(1) << PageShift;
const size_t ArenaSize = size_t(1) << ArenaShift;
const size_t ArenaMask = ArenaSize - 1;

const size_t ChunkShift = 20;
const size_t ChunkSize = size_t(1) << ChunkShift;
const size_t ChunkMask = ChunkSize - 1;

} /* namespace gc */
} /* namespace js */

namespace JS {

namespace shadow {

struct ArenaHeader
{
    JSCompartment *compartment;
};

} /* namespace shadow */

static inline shadow::ArenaHeader *
GetGCThingArena(void *thing)
{
    uintptr_t addr = uintptr_t(thing);
    addr &= ~js::gc::ArenaMask;
    return reinterpret_cast<shadow::ArenaHeader *>(addr);
}

static inline JSCompartment *
GetGCThingCompartment(void *thing)
{
    JS_ASSERT(thing);
    return GetGCThingArena(thing)->compartment;
}

static inline JSCompartment *
GetObjectCompartment(JSObject *obj)
{
    return GetGCThingCompartment(obj);
}

} /* namespace JS */

#endif /* js_heap_api_h___ */
