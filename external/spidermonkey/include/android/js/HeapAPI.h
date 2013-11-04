/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_HeapAPI_h
#define js_HeapAPI_h

#include "jspubtd.h"

#include "js/Utility.h"

/* These values are private to the JS engine. */
namespace js {
namespace gc {

const size_t ArenaShift = 12;
const size_t ArenaSize = size_t(1) << ArenaShift;
const size_t ArenaMask = ArenaSize - 1;

const size_t ChunkShift = 20;
const size_t ChunkSize = size_t(1) << ChunkShift;
const size_t ChunkMask = ChunkSize - 1;

const size_t CellShift = 3;
const size_t CellSize = size_t(1) << CellShift;
const size_t CellMask = CellSize - 1;

/* These are magic constants derived from actual offsets in gc/Heap.h. */
const size_t ChunkMarkBitmapOffset = 1032368;
const size_t ChunkMarkBitmapBits = 129024;
const size_t ChunkRuntimeOffset = ChunkSize - sizeof(void*);

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
struct Zone;
} /* namespace JS */

namespace JS {
namespace shadow {

struct ArenaHeader
{
    JS::Zone *zone;
};

struct Zone
{
    bool needsBarrier_;

    Zone() : needsBarrier_(false) {}
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

static JS_ALWAYS_INLINE JS::shadow::Runtime *
GetGCThingRuntime(const void *thing)
{
    uintptr_t addr = uintptr_t(thing);
    addr &= ~js::gc::ChunkMask;
    addr |= js::gc::ChunkRuntimeOffset;
    return *reinterpret_cast<JS::shadow::Runtime **>(addr);
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

static JS_ALWAYS_INLINE Zone *
GetGCThingZone(void *thing)
{
    JS_ASSERT(thing);
    return js::gc::GetGCThingArena(thing)->zone;
}

static JS_ALWAYS_INLINE Zone *
GetObjectZone(JSObject *obj)
{
    return GetGCThingZone(obj);
}

static JS_ALWAYS_INLINE bool
GCThingIsMarkedGray(void *thing)
{
    uintptr_t *word, mask;
    js::gc::GetGCThingMarkWordAndMask(thing, js::gc::GRAY, &word, &mask);
    return *word & mask;
}

static JS_ALWAYS_INLINE bool
IsIncrementalBarrierNeededOnGCThing(shadow::Runtime *rt, void *thing, JSGCTraceKind kind)
{
    if (!rt->needsBarrier_)
        return false;
    JS::Zone *zone = GetGCThingZone(thing);
    return reinterpret_cast<shadow::Zone *>(zone)->needsBarrier_;
}

} /* namespace JS */

#endif /* js_HeapAPI_h */
