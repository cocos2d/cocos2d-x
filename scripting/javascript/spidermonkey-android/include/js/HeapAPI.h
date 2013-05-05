/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_heap_api_h___
#define js_heap_api_h___

#include "jsfriendapi.h"

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

const size_t CellShift = 3;
const size_t CellSize = size_t(1) << CellShift;
const size_t CellMask = CellSize - 1;

/* These are magic constants derived from actual offsets in gc/Heap.h. */
const size_t ChunkMarkBitmapOffset = 1032376;
const size_t ChunkMarkBitmapBits = 129024;

/*
 * Live objects are marked black. How many other additional colors are available
 * depends on the size of the GCThing. Objects marked gray are eligible for
 * cycle collection.
 */
static const uint32_t BLACK = 0;
static const uint32_t GRAY = 1;

} /* namespace gc */
} /* namespace js */

namespace JS {
namespace shadow {

struct ArenaHeader
{
    JSCompartment *compartment;
};

struct Compartment
{
    bool needsBarrier_;

    Compartment() : needsBarrier_(false) {}
};

} /* namespace shadow */
} /* namespace JS */

namespace js {
namespace gc {

static JS_ALWAYS_INLINE uintptr_t *
GetGCThingMarkBitmap(const void *thing)
{
    uintptr_t addr = uintptr_t(thing);
    addr &= ~js::gc::ChunkMask;
    addr |= js::gc::ChunkMarkBitmapOffset;
    return reinterpret_cast<uintptr_t *>(addr);
}

static JS_ALWAYS_INLINE void
GetGCThingMarkWordAndMask(const void *thing, uint32_t color,
                          uintptr_t **wordp, uintptr_t *maskp)
{
    uintptr_t addr = uintptr_t(thing);
    size_t bit = (addr & js::gc::ChunkMask) / js::gc::CellSize + color;
    JS_ASSERT(bit < js::gc::ChunkMarkBitmapBits);
    uintptr_t *bitmap = GetGCThingMarkBitmap(thing);
    *maskp = uintptr_t(1) << (bit % JS_BITS_PER_WORD);
    *wordp = &bitmap[bit / JS_BITS_PER_WORD];
}

static JS_ALWAYS_INLINE JS::shadow::ArenaHeader *
GetGCThingArena(void *thing)
{
    uintptr_t addr = uintptr_t(thing);
    addr &= ~js::gc::ArenaMask;
    return reinterpret_cast<JS::shadow::ArenaHeader *>(addr);
}

} /* namespace gc */
} /* namespace js */

namespace JS {

static JS_ALWAYS_INLINE JSCompartment *
GetGCThingCompartment(void *thing)
{
    JS_ASSERT(thing);
    return js::gc::GetGCThingArena(thing)->compartment;
}

static JS_ALWAYS_INLINE JSCompartment *
GetObjectCompartment(JSObject *obj)
{
    return GetGCThingCompartment(obj);
}

static JS_ALWAYS_INLINE bool
GCThingIsMarkedGray(void *thing)
{
    uintptr_t *word, mask;
    js::gc::GetGCThingMarkWordAndMask(thing, js::gc::GRAY, &word, &mask);
    return *word & mask;
}

static JS_ALWAYS_INLINE bool
IsIncrementalBarrierNeededOnGCThing(void *thing, JSGCTraceKind kind)
{
    JSCompartment *comp = GetGCThingCompartment(thing);
    return reinterpret_cast<shadow::Compartment *>(comp)->needsBarrier_;
}

/*
 * This should be called when an object that is marked gray is exposed to the JS
 * engine (by handing it to running JS code or writing it into live JS
 * data). During incremental GC, since the gray bits haven't been computed yet,
 * we conservatively mark the object black.
 */
static JS_ALWAYS_INLINE void
ExposeGCThingToActiveJS(void *thing, JSGCTraceKind kind)
{
    JS_ASSERT(kind != JSTRACE_SHAPE);

    if (GCThingIsMarkedGray(thing))
        js::UnmarkGrayGCThingRecursively(thing, kind);
    else if (IsIncrementalBarrierNeededOnGCThing(thing, kind))
        js::IncrementalReferenceBarrier(thing);
}

static JS_ALWAYS_INLINE void
ExposeValueToActiveJS(const Value &v)
{
    if (v.isMarkable())
        ExposeGCThingToActiveJS(v.toGCThing(), v.gcKind());
}

} /* namespace JS */

#endif /* js_heap_api_h___ */
