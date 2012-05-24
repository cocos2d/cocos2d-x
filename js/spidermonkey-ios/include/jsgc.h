/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
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

#ifndef jsgc_h___
#define jsgc_h___

/*
 * JS Garbage Collector.
 */
#include <setjmp.h>

#include "mozilla/Util.h"

#include "jsalloc.h"
#include "jstypes.h"
#include "jsprvtd.h"
#include "jspubtd.h"
#include "jsdhash.h"
#include "jslock.h"
#include "jsutil.h"
#include "jsversion.h"
#include "jscell.h"

#include "ds/BitArray.h"
#include "gc/Statistics.h"
#include "js/HashTable.h"
#include "js/Vector.h"
#include "js/TemplateLib.h"

struct JSCompartment;

extern "C" void
js_TraceXML(JSTracer *trc, JSXML* thing);

#if JS_STACK_GROWTH_DIRECTION > 0
# define JS_CHECK_STACK_SIZE(limit, lval)  ((uintptr_t)(lval) < limit)
#else
# define JS_CHECK_STACK_SIZE(limit, lval)  ((uintptr_t)(lval) > limit)
#endif

namespace js {

class GCHelperThread;
struct Shape;

namespace gc {

enum State {
    NO_INCREMENTAL,
    MARK_ROOTS,
    MARK,
    SWEEP,
    INVALID
};

struct Arena;

/*
 * This must be an upper bound, but we do not need the least upper bound, so
 * we just exclude non-background objects.
 */
const size_t MAX_BACKGROUND_FINALIZE_KINDS = FINALIZE_LIMIT - FINALIZE_OBJECT_LIMIT / 2;

/*
 * Page size is 4096 by default, except for SPARC, where it is 8192.
 * Note: Do not use JS_CPU_SPARC here, this header is used outside JS.
 * Bug 692267: Move page size definition to gc/Memory.h and include it
 *             directly once jsgc.h is no longer an installed header.
 */
#if defined(SOLARIS) && (defined(__sparc) || defined(__sparcv9))
const size_t PageShift = 13;
#else
const size_t PageShift = 12;
#endif
const size_t PageSize = size_t(1) << PageShift;

const size_t ChunkShift = 20;
const size_t ChunkSize = size_t(1) << ChunkShift;
const size_t ChunkMask = ChunkSize - 1;

const size_t ArenaShift = PageShift;
const size_t ArenaSize = PageSize;
const size_t ArenaMask = ArenaSize - 1;

/*
 * This is the maximum number of arenas we allow in the FreeCommitted state
 * before we trigger a GC_SHRINK to release free arenas to the OS.
 */
const static uint32_t FreeCommittedArenasThreshold = (32 << 20) / ArenaSize;

/*
 * The mark bitmap has one bit per each GC cell. For multi-cell GC things this
 * wastes space but allows to avoid expensive devisions by thing's size when
 * accessing the bitmap. In addition this allows to use some bits for colored
 * marking during the cycle GC.
 */
const size_t ArenaCellCount = size_t(1) << (ArenaShift - Cell::CellShift);
const size_t ArenaBitmapBits = ArenaCellCount;
const size_t ArenaBitmapBytes = ArenaBitmapBits / 8;
const size_t ArenaBitmapWords = ArenaBitmapBits / JS_BITS_PER_WORD;

/*
 * A FreeSpan represents a contiguous sequence of free cells in an Arena.
 * |first| is the address of the first free cell in the span. |last| is the
 * address of the last free cell in the span. This last cell holds a FreeSpan
 * data structure for the next span unless this is the last span on the list
 * of spans in the arena. For this last span |last| points to the last byte of
 * the last thing in the arena and no linkage is stored there, so
 * |last| == arenaStart + ArenaSize - 1. If the space at the arena end is
 * fully used this last span is empty and |first| == |last + 1|.
 *
 * Thus |first| < |last| implies that we have either the last span with at least
 * one element or that the span is not the last and contains at least 2
 * elements. In both cases to allocate a thing from this span we need simply
 * to increment |first| by the allocation size.
 *
 * |first| == |last| implies that we have a one element span that records the
 * next span. So to allocate from it we need to update the span list head
 * with a copy of the span stored at |last| address so the following
 * allocations will use that span.
 *
 * |first| > |last| implies that we have an empty last span and the arena is
 * fully used.
 *
 * Also only for the last span (|last| & 1)! = 0 as all allocation sizes are
 * multiples of Cell::CellSize.
 */
struct FreeSpan {
    uintptr_t   first;
    uintptr_t   last;

  public:
    FreeSpan() {}

    FreeSpan(uintptr_t first, uintptr_t last)
      : first(first), last(last) {
        checkSpan();
    }

    /*
     * To minimize the size of the arena header the first span is encoded
     * there as offsets from the arena start.
     */
    static size_t encodeOffsets(size_t firstOffset, size_t lastOffset) {
        /* Check that we can pack the offsets into uint16. */
        JS_STATIC_ASSERT(ArenaShift < 16);
        JS_ASSERT(firstOffset <= ArenaSize);
        JS_ASSERT(lastOffset < ArenaSize);
        JS_ASSERT(firstOffset <= ((lastOffset + 1) & ~size_t(1)));
        return firstOffset | (lastOffset << 16);
    }

    /*
     * Encoded offsets for a full arena when its first span is the last one
     * and empty.
     */
    static const size_t FullArenaOffsets = ArenaSize | ((ArenaSize - 1) << 16);

    static FreeSpan decodeOffsets(uintptr_t arenaAddr, size_t offsets) {
        JS_ASSERT(!(arenaAddr & ArenaMask));

        size_t firstOffset = offsets & 0xFFFF;
        size_t lastOffset = offsets >> 16;
        JS_ASSERT(firstOffset <= ArenaSize);
        JS_ASSERT(lastOffset < ArenaSize);

        /*
         * We must not use | when calculating first as firstOffset is
         * ArenaMask + 1 for the empty span.
         */
        return FreeSpan(arenaAddr + firstOffset, arenaAddr | lastOffset);
    }

    void initAsEmpty(uintptr_t arenaAddr = 0) {
        JS_ASSERT(!(arenaAddr & ArenaMask));
        first = arenaAddr + ArenaSize;
        last = arenaAddr | (ArenaSize  - 1);
        JS_ASSERT(isEmpty());
    }

    bool isEmpty() const {
        checkSpan();
        return first > last;
    }

    bool hasNext() const {
        checkSpan();
        return !(last & uintptr_t(1));
    }

    const FreeSpan *nextSpan() const {
        JS_ASSERT(hasNext());
        return reinterpret_cast<FreeSpan *>(last);
    }

    FreeSpan *nextSpanUnchecked(size_t thingSize) const {
#ifdef DEBUG
        uintptr_t lastOffset = last & ArenaMask;
        JS_ASSERT(!(lastOffset & 1));
        JS_ASSERT((ArenaSize - lastOffset) % thingSize == 0);
#endif
        return reinterpret_cast<FreeSpan *>(last);
    }

    uintptr_t arenaAddressUnchecked() const {
        return last & ~ArenaMask;
    }

    uintptr_t arenaAddress() const {
        checkSpan();
        return arenaAddressUnchecked();
    }

    ArenaHeader *arenaHeader() const {
        return reinterpret_cast<ArenaHeader *>(arenaAddress());
    }

    bool isSameNonEmptySpan(const FreeSpan *another) const {
        JS_ASSERT(!isEmpty());
        JS_ASSERT(!another->isEmpty());
        return first == another->first && last == another->last;
    }

    bool isWithinArena(uintptr_t arenaAddr) const {
        JS_ASSERT(!(arenaAddr & ArenaMask));

        /* Return true for the last empty span as well. */
        return arenaAddress() == arenaAddr;
    }

    size_t encodeAsOffsets() const {
        /*
         * We must use first - arenaAddress(), not first & ArenaMask as
         * first == ArenaMask + 1 for an empty span.
         */
        uintptr_t arenaAddr = arenaAddress();
        return encodeOffsets(first - arenaAddr, last & ArenaMask);
    }

    /* See comments before FreeSpan for details. */
    JS_ALWAYS_INLINE void *allocate(size_t thingSize) {
        JS_ASSERT(thingSize % Cell::CellSize == 0);
        checkSpan();
        uintptr_t thing = first;
        if (thing < last) {
            /* Bump-allocate from the current span. */
            first = thing + thingSize;
        } else if (JS_LIKELY(thing == last)) {
            /*
             * Move to the next span. We use JS_LIKELY as without PGO
             * compilers mis-predict == here as unlikely to succeed.
             */
            *this = *reinterpret_cast<FreeSpan *>(thing);
        } else {
            return NULL;
        }
        checkSpan();
        return reinterpret_cast<void *>(thing);
    }

    /* A version of allocate when we know that the span is not empty. */
    JS_ALWAYS_INLINE void *infallibleAllocate(size_t thingSize) {
        JS_ASSERT(thingSize % Cell::CellSize == 0);
        checkSpan();
        uintptr_t thing = first;
        if (thing < last) {
            first = thing + thingSize;
        } else {
            JS_ASSERT(thing == last);
            *this = *reinterpret_cast<FreeSpan *>(thing);
        }
        checkSpan();
        return reinterpret_cast<void *>(thing);
    }

    /*
     * Allocate from a newly allocated arena. We do not move the free list
     * from the arena. Rather we set the arena up as fully used during the
     * initialization so to allocate we simply return the first thing in the
     * arena and set the free list to point to the second.
     */
    JS_ALWAYS_INLINE void *allocateFromNewArena(uintptr_t arenaAddr, size_t firstThingOffset,
                                                size_t thingSize) {
        JS_ASSERT(!(arenaAddr & ArenaMask));
        uintptr_t thing = arenaAddr | firstThingOffset;
        first = thing + thingSize;
        last = arenaAddr | ArenaMask;
        checkSpan();
        return reinterpret_cast<void *>(thing);
    }

    void checkSpan() const {
#ifdef DEBUG
        /* We do not allow spans at the end of the address space. */
        JS_ASSERT(last != uintptr_t(-1));
        JS_ASSERT(first);
        JS_ASSERT(last);
        JS_ASSERT(first - 1 <= last);
        uintptr_t arenaAddr = arenaAddressUnchecked();
        if (last & 1) {
            /* The span is the last. */
            JS_ASSERT((last & ArenaMask) == ArenaMask);

            if (first - 1 == last) {
                /* The span is last and empty. The above start != 0 check
                 * implies that we are not at the end of the address space.
                 */
                return;
            }
            size_t spanLength = last - first + 1;
            JS_ASSERT(spanLength % Cell::CellSize == 0);

            /* Start and end must belong to the same arena. */
            JS_ASSERT((first & ~ArenaMask) == arenaAddr);
            return;
        }

        /* The span is not the last and we have more spans to follow. */
        JS_ASSERT(first <= last);
        size_t spanLengthWithoutOneThing = last - first;
        JS_ASSERT(spanLengthWithoutOneThing % Cell::CellSize == 0);

        JS_ASSERT((first & ~ArenaMask) == arenaAddr);

        /*
         * If there is not enough space before the arena end to allocate one
         * more thing, then the span must be marked as the last one to avoid
         * storing useless empty span reference.
         */
        size_t beforeTail = ArenaSize - (last & ArenaMask);
        JS_ASSERT(beforeTail >= sizeof(FreeSpan) + Cell::CellSize);

        FreeSpan *next = reinterpret_cast<FreeSpan *>(last);

        /*
         * The GC things on the list of free spans come from one arena
         * and the spans are linked in ascending address order with
         * at least one non-free thing between spans.
         */
        JS_ASSERT(last < next->first);
        JS_ASSERT(arenaAddr == next->arenaAddressUnchecked());

        if (next->first > next->last) {
            /*
             * The next span is the empty span that terminates the list for
             * arenas that do not have any free things at the end.
             */
            JS_ASSERT(next->first - 1 == next->last);
            JS_ASSERT(arenaAddr + ArenaSize == next->first);
        }
#endif
    }

};

/* Every arena has a header. */
struct ArenaHeader {
    friend struct FreeLists;

    JSCompartment   *compartment;

    /*
     * ArenaHeader::next has two purposes: when unallocated, it points to the
     * next available Arena's header. When allocated, it points to the next
     * arena of the same size class and compartment.
     */
    ArenaHeader     *next;

  private:
    /*
     * The first span of free things in the arena. We encode it as the start
     * and end offsets within the arena, not as FreeSpan structure, to
     * minimize the header size.
     */
    size_t          firstFreeSpanOffsets;

    /*
     * One of AllocKind constants or FINALIZE_LIMIT when the arena does not
     * contain any GC things and is on the list of empty arenas in the GC
     * chunk. The latter allows to quickly check if the arena is allocated
     * during the conservative GC scanning without searching the arena in the
     * list.
     */
    size_t       allocKind          : 8;

    /*
     * When recursive marking uses too much stack the marking is delayed and
     * the corresponding arenas are put into a stack using the following field
     * as a linkage. To distinguish the bottom of the stack from the arenas
     * not present in the stack we use an extra flag to tag arenas on the
     * stack.
     *
     * Delayed marking is also used for arenas that we allocate into during an
     * incremental GC. In this case, we intend to mark all the objects in the
     * arena, and it's faster to do this marking in bulk.
     *
     * To minimize the ArenaHeader size we record the next delayed marking
     * linkage as arenaAddress() >> ArenaShift and pack it with the allocKind
     * field and hasDelayedMarking flag. We use 8 bits for the allocKind, not
     * ArenaShift - 1, so the compiler can use byte-level memory instructions
     * to access it.
     */
  public:
    size_t       hasDelayedMarking  : 1;
    size_t       allocatedDuringIncremental : 1;
    size_t       markOverflow : 1;
    size_t       nextDelayedMarking : JS_BITS_PER_WORD - 8 - 1 - 1 - 1;

    static void staticAsserts() {
        /* We must be able to fit the allockind into uint8_t. */
        JS_STATIC_ASSERT(FINALIZE_LIMIT <= 255);

        /*
         * nextDelayedMarkingpacking assumes that ArenaShift has enough bits
         * to cover allocKind and hasDelayedMarking.
         */
        JS_STATIC_ASSERT(ArenaShift >= 8 + 1 + 1 + 1);
    }

    inline uintptr_t address() const;
    inline Chunk *chunk() const;

    bool allocated() const {
        JS_ASSERT(allocKind <= size_t(FINALIZE_LIMIT));
        return allocKind < size_t(FINALIZE_LIMIT);
    }

    void init(JSCompartment *comp, AllocKind kind) {
        JS_ASSERT(!allocated());
        JS_ASSERT(!markOverflow);
        JS_ASSERT(!allocatedDuringIncremental);
        JS_ASSERT(!hasDelayedMarking);
        compartment = comp;

        JS_STATIC_ASSERT(FINALIZE_LIMIT <= 255);
        allocKind = size_t(kind);

        /* See comments in FreeSpan::allocateFromNewArena. */
        firstFreeSpanOffsets = FreeSpan::FullArenaOffsets;
    }

    void setAsNotAllocated() {
        allocKind = size_t(FINALIZE_LIMIT);
        markOverflow = 0;
        allocatedDuringIncremental = 0;
        hasDelayedMarking = 0;
        nextDelayedMarking = 0;
    }

    uintptr_t arenaAddress() const {
        return address();
    }

    Arena *getArena() {
        return reinterpret_cast<Arena *>(arenaAddress());
    }

    AllocKind getAllocKind() const {
        JS_ASSERT(allocated());
        return AllocKind(allocKind);
    }

    inline size_t getThingSize() const;

    bool hasFreeThings() const {
        return firstFreeSpanOffsets != FreeSpan::FullArenaOffsets;
    }

    inline bool isEmpty() const;

    void setAsFullyUsed() {
        firstFreeSpanOffsets = FreeSpan::FullArenaOffsets;
    }

    FreeSpan getFirstFreeSpan() const {
#ifdef DEBUG
        checkSynchronizedWithFreeList();
#endif
        return FreeSpan::decodeOffsets(arenaAddress(), firstFreeSpanOffsets);
    }

    void setFirstFreeSpan(const FreeSpan *span) {
        JS_ASSERT(span->isWithinArena(arenaAddress()));
        firstFreeSpanOffsets = span->encodeAsOffsets();
    }

#ifdef DEBUG
    void checkSynchronizedWithFreeList() const;
#endif

    inline ArenaHeader *getNextDelayedMarking() const;
    inline void setNextDelayedMarking(ArenaHeader *aheader);
};

struct Arena {
    /*
     * Layout of an arena:
     * An arena is 4K in size and 4K-aligned. It starts with the ArenaHeader
     * descriptor followed by some pad bytes. The remainder of the arena is
     * filled with the array of T things. The pad bytes ensure that the thing
     * array ends exactly at the end of the arena.
     *
     * +-------------+-----+----+----+-----+----+
     * | ArenaHeader | pad | T0 | T1 | ... | Tn |
     * +-------------+-----+----+----+-----+----+
     *
     * <----------------------------------------> = ArenaSize bytes
     * <-------------------> = first thing offset
     */
    ArenaHeader aheader;
    uint8_t     data[ArenaSize - sizeof(ArenaHeader)];

  private:
    static JS_FRIEND_DATA(const uint32_t) ThingSizes[];
    static JS_FRIEND_DATA(const uint32_t) FirstThingOffsets[];

  public:
    static void staticAsserts();

    static size_t thingSize(AllocKind kind) {
        return ThingSizes[kind];
    }

    static size_t firstThingOffset(AllocKind kind) {
        return FirstThingOffsets[kind];
    }

    static size_t thingsPerArena(size_t thingSize) {
        JS_ASSERT(thingSize % Cell::CellSize == 0);

        /* We should be able to fit FreeSpan in any GC thing. */
        JS_ASSERT(thingSize >= sizeof(FreeSpan));

        return (ArenaSize - sizeof(ArenaHeader)) / thingSize;
    }

    static size_t thingsSpan(size_t thingSize) {
        return thingsPerArena(thingSize) * thingSize;
    }

    static bool isAligned(uintptr_t thing, size_t thingSize) {
        /* Things ends at the arena end. */
        uintptr_t tailOffset = (ArenaSize - thing) & ArenaMask;
        return tailOffset % thingSize == 0;
    }

    uintptr_t address() const {
        return aheader.address();
    }

    uintptr_t thingsStart(AllocKind thingKind) {
        return address() | firstThingOffset(thingKind);
    }

    uintptr_t thingsEnd() {
        return address() + ArenaSize;
    }

    template <typename T>
    bool finalize(JSContext *cx, AllocKind thingKind, size_t thingSize, bool background);
};

/* The chunk header (located at the end of the chunk to preserve arena alignment). */
struct ChunkInfo {
    Chunk           *next;
    Chunk           **prevp;

    /* Free arenas are linked together with aheader.next. */
    ArenaHeader     *freeArenasHead;

    /*
     * Decommitted arenas are tracked by a bitmap in the chunk header. We use
     * this offset to start our search iteration close to a decommitted arena
     * that we can allocate.
     */
    uint32_t        lastDecommittedArenaOffset;

    /* Number of free arenas, either committed or decommitted. */
    uint32_t        numArenasFree;

    /* Number of free, committed arenas. */
    uint32_t        numArenasFreeCommitted;

    /* Number of GC cycles this chunk has survived. */
    uint32_t        age;
};

/*
 * Calculating ArenasPerChunk:
 *
 * In order to figure out how many Arenas will fit in a chunk, we need to know
 * how much extra space is available after we allocate the header data. This
 * is a problem because the header size depends on the number of arenas in the
 * chunk. The two dependent fields are bitmap and decommittedArenas.
 *
 * For the mark bitmap, we know that each arena will use a fixed number of full
 * bytes: ArenaBitmapBytes. The full size of the header data is this number
 * multiplied by the eventual number of arenas we have in the header. We,
 * conceptually, distribute this header data among the individual arenas and do
 * not include it in the header. This way we do not have to worry about its
 * variable size: it gets attached to the variable number we are computing.
 *
 * For the decommitted arena bitmap, we only have 1 bit per arena, so this
 * technique will not work. Instead, we observe that we do not have enough
 * header info to fill 8 full arenas: it is currently 4 on 64bit, less on
 * 32bit. Thus, with current numbers, we need 64 bytes for decommittedArenas.
 * This will not become 63 bytes unless we double the data required in the
 * header. Therefore, we just compute the number of bytes required to track
 * every possible arena and do not worry about slop bits, since there are too
 * few to usefully allocate.
 *
 * To actually compute the number of arenas we can allocate in a chunk, we
 * divide the amount of available space less the header info (not including
 * the mark bitmap which is distributed into the arena size) by the size of
 * the arena (with the mark bitmap bytes it uses).
 */
const size_t BytesPerArenaWithHeader = ArenaSize + ArenaBitmapBytes;
const size_t ChunkDecommitBitmapBytes = ChunkSize / ArenaSize / JS_BITS_PER_BYTE;
const size_t ChunkBytesAvailable = ChunkSize - sizeof(ChunkInfo) - ChunkDecommitBitmapBytes;
const size_t ArenasPerChunk = ChunkBytesAvailable / BytesPerArenaWithHeader;

/* A chunk bitmap contains enough mark bits for all the cells in a chunk. */
struct ChunkBitmap {
    uintptr_t bitmap[ArenaBitmapWords * ArenasPerChunk];

    JS_ALWAYS_INLINE void getMarkWordAndMask(const Cell *cell, uint32_t color,
                                             uintptr_t **wordp, uintptr_t *maskp);

    JS_ALWAYS_INLINE bool isMarked(const Cell *cell, uint32_t color) {
        uintptr_t *word, mask;
        getMarkWordAndMask(cell, color, &word, &mask);
        return *word & mask;
    }

    JS_ALWAYS_INLINE bool markIfUnmarked(const Cell *cell, uint32_t color) {
        uintptr_t *word, mask;
        getMarkWordAndMask(cell, BLACK, &word, &mask);
        if (*word & mask)
            return false;
        *word |= mask;
        if (color != BLACK) {
            /*
             * We use getMarkWordAndMask to recalculate both mask and word as
             * doing just mask << color may overflow the mask.
             */
            getMarkWordAndMask(cell, color, &word, &mask);
            if (*word & mask)
                return false;
            *word |= mask;
        }
        return true;
    }

    JS_ALWAYS_INLINE void unmark(const Cell *cell, uint32_t color) {
        uintptr_t *word, mask;
        getMarkWordAndMask(cell, color, &word, &mask);
        *word &= ~mask;
    }

    void clear() {
        PodArrayZero(bitmap);
    }

#ifdef DEBUG
    bool noBitsSet(ArenaHeader *aheader) {
        /*
         * We assume that the part of the bitmap corresponding to the arena
         * has the exact number of words so we do not need to deal with a word
         * that covers bits from two arenas.
         */
        JS_STATIC_ASSERT(ArenaBitmapBits == ArenaBitmapWords * JS_BITS_PER_WORD);

        uintptr_t *word, unused;
        getMarkWordAndMask(reinterpret_cast<Cell *>(aheader->address()), BLACK, &word, &unused);
        for (size_t i = 0; i != ArenaBitmapWords; i++) {
            if (word[i])
                return false;
        }
        return true;
    }
#endif
};

JS_STATIC_ASSERT(ArenaBitmapBytes * ArenasPerChunk == sizeof(ChunkBitmap));

typedef BitArray<ArenasPerChunk> PerArenaBitmap;

const size_t ChunkPadSize = ChunkSize
                            - (sizeof(Arena) * ArenasPerChunk)
                            - sizeof(ChunkBitmap)
                            - sizeof(PerArenaBitmap)
                            - sizeof(ChunkInfo);
JS_STATIC_ASSERT(ChunkPadSize < BytesPerArenaWithHeader);

/*
 * Chunks contain arenas and associated data structures (mark bitmap, delayed
 * marking state).
 */
struct Chunk {
    Arena           arenas[ArenasPerChunk];

    /* Pad to full size to ensure cache alignment of ChunkInfo. */
    uint8_t         padding[ChunkPadSize];

    ChunkBitmap     bitmap;
    PerArenaBitmap  decommittedArenas;
    ChunkInfo       info;

    static Chunk *fromAddress(uintptr_t addr) {
        addr &= ~ChunkMask;
        return reinterpret_cast<Chunk *>(addr);
    }

    static bool withinArenasRange(uintptr_t addr) {
        uintptr_t offset = addr & ChunkMask;
        return offset < ArenasPerChunk * ArenaSize;
    }

    static size_t arenaIndex(uintptr_t addr) {
        JS_ASSERT(withinArenasRange(addr));
        return (addr & ChunkMask) >> ArenaShift;
    }

    uintptr_t address() const {
        uintptr_t addr = reinterpret_cast<uintptr_t>(this);
        JS_ASSERT(!(addr & ChunkMask));
        return addr;
    }

    bool unused() const {
        return info.numArenasFree == ArenasPerChunk;
    }

    bool hasAvailableArenas() const {
        return info.numArenasFree != 0;
    }

    inline void addToAvailableList(JSCompartment *compartment);
    inline void insertToAvailableList(Chunk **insertPoint);
    inline void removeFromAvailableList();

    ArenaHeader *allocateArena(JSCompartment *comp, AllocKind kind);

    void releaseArena(ArenaHeader *aheader);

    static Chunk *allocate(JSRuntime *rt);

    /* Must be called with the GC lock taken. */
    static inline void release(JSRuntime *rt, Chunk *chunk);
    static inline void releaseList(JSRuntime *rt, Chunk *chunkListHead);

    /* Must be called with the GC lock taken. */
    inline void prepareToBeFreed(JSRuntime *rt);

    /*
     * Assuming that the info.prevp points to the next field of the previous
     * chunk in a doubly-linked list, get that chunk.
     */
    Chunk *getPrevious() {
        JS_ASSERT(info.prevp);
        return fromPointerToNext(info.prevp);
    }

    /* Get the chunk from a pointer to its info.next field. */
    static Chunk *fromPointerToNext(Chunk **nextFieldPtr) {
        uintptr_t addr = reinterpret_cast<uintptr_t>(nextFieldPtr);
        JS_ASSERT((addr & ChunkMask) == offsetof(Chunk, info.next));
        return reinterpret_cast<Chunk *>(addr - offsetof(Chunk, info.next));
    }

  private:
    inline void init();

    /* Search for a decommitted arena to allocate. */
    unsigned findDecommittedArenaOffset();
    ArenaHeader* fetchNextDecommittedArena();

  public:
    /* Unlink and return the freeArenasHead. */
    inline ArenaHeader* fetchNextFreeArena(JSRuntime *rt);

    inline void addArenaToFreeList(JSRuntime *rt, ArenaHeader *aheader);
};

JS_STATIC_ASSERT(sizeof(Chunk) == ChunkSize);

class ChunkPool {
    Chunk   *emptyChunkListHead;
    size_t  emptyCount;

  public:
    ChunkPool()
      : emptyChunkListHead(NULL),
        emptyCount(0) { }

    size_t getEmptyCount() const {
        return emptyCount;
    }

    inline bool wantBackgroundAllocation(JSRuntime *rt) const;

    /* Must be called with the GC lock taken. */
    inline Chunk *get(JSRuntime *rt);

    /* Must be called either during the GC or with the GC lock taken. */
    inline void put(Chunk *chunk);

    /*
     * Return the list of chunks that can be released outside the GC lock.
     * Must be called either during the GC or with the GC lock taken.
     */
    Chunk *expire(JSRuntime *rt, bool releaseAll);

    /* Must be called with the GC lock taken. */
    void expireAndFree(JSRuntime *rt, bool releaseAll);

    /* Must be called either during the GC or with the GC lock taken. */
    JS_FRIEND_API(int64_t) countCleanDecommittedArenas(JSRuntime *rt);
};

inline uintptr_t
Cell::address() const
{
    uintptr_t addr = uintptr_t(this);
    JS_ASSERT(addr % Cell::CellSize == 0);
    JS_ASSERT(Chunk::withinArenasRange(addr));
    return addr;
}

inline ArenaHeader *
Cell::arenaHeader() const
{
    uintptr_t addr = address();
    addr &= ~ArenaMask;
    return reinterpret_cast<ArenaHeader *>(addr);
}

Chunk *
Cell::chunk() const
{
    uintptr_t addr = uintptr_t(this);
    JS_ASSERT(addr % Cell::CellSize == 0);
    addr &= ~(ChunkSize - 1);
    return reinterpret_cast<Chunk *>(addr);
}

AllocKind
Cell::getAllocKind() const
{
    return arenaHeader()->getAllocKind();
}

#ifdef DEBUG
inline bool
Cell::isAligned() const
{
    return Arena::isAligned(address(), arenaHeader()->getThingSize());
}
#endif

inline uintptr_t
ArenaHeader::address() const
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(this);
    JS_ASSERT(!(addr & ArenaMask));
    JS_ASSERT(Chunk::withinArenasRange(addr));
    return addr;
}

inline Chunk *
ArenaHeader::chunk() const
{
    return Chunk::fromAddress(address());
}

inline bool
ArenaHeader::isEmpty() const
{
    /* Arena is empty if its first span covers the whole arena. */
    JS_ASSERT(allocated());
    size_t firstThingOffset = Arena::firstThingOffset(getAllocKind());
    return firstFreeSpanOffsets == FreeSpan::encodeOffsets(firstThingOffset, ArenaMask);
}

inline size_t
ArenaHeader::getThingSize() const
{
    JS_ASSERT(allocated());
    return Arena::thingSize(getAllocKind());
}

inline ArenaHeader *
ArenaHeader::getNextDelayedMarking() const
{
    return &reinterpret_cast<Arena *>(nextDelayedMarking << ArenaShift)->aheader;
}

inline void
ArenaHeader::setNextDelayedMarking(ArenaHeader *aheader)
{
    JS_ASSERT(!(uintptr_t(aheader) & ArenaMask));
    hasDelayedMarking = 1;
    nextDelayedMarking = aheader->arenaAddress() >> ArenaShift;
}

JS_ALWAYS_INLINE void
ChunkBitmap::getMarkWordAndMask(const Cell *cell, uint32_t color,
                                uintptr_t **wordp, uintptr_t *maskp)
{
    size_t bit = (cell->address() & ChunkMask) / Cell::CellSize + color;
    JS_ASSERT(bit < ArenaBitmapBits * ArenasPerChunk);
    *maskp = uintptr_t(1) << (bit % JS_BITS_PER_WORD);
    *wordp = &bitmap[bit / JS_BITS_PER_WORD];
}

static void
AssertValidColor(const void *thing, uint32_t color)
{
#ifdef DEBUG
    ArenaHeader *aheader = reinterpret_cast<const js::gc::Cell *>(thing)->arenaHeader();
    JS_ASSERT_IF(color, color < aheader->getThingSize() / Cell::CellSize);
#endif
}

inline bool
Cell::isMarked(uint32_t color) const
{
    AssertValidColor(this, color);
    return chunk()->bitmap.isMarked(this, color);
}

bool
Cell::markIfUnmarked(uint32_t color) const
{
    AssertValidColor(this, color);
    return chunk()->bitmap.markIfUnmarked(this, color);
}

void
Cell::unmark(uint32_t color) const
{
    JS_ASSERT(color != BLACK);
    AssertValidColor(this, color);
    chunk()->bitmap.unmark(this, color);
}

JSCompartment *
Cell::compartment() const
{
    return arenaHeader()->compartment;
}

static inline JSGCTraceKind
MapAllocToTraceKind(AllocKind thingKind)
{
    static const JSGCTraceKind map[FINALIZE_LIMIT] = {
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT0 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT0_BACKGROUND */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT2 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT2_BACKGROUND */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT4 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT4_BACKGROUND */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT8 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT8_BACKGROUND */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT12 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT12_BACKGROUND */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT16 */
        JSTRACE_OBJECT,     /* FINALIZE_OBJECT16_BACKGROUND */
        JSTRACE_SCRIPT,     /* FINALIZE_SCRIPT */
        JSTRACE_SHAPE,      /* FINALIZE_SHAPE */
        JSTRACE_BASE_SHAPE, /* FINALIZE_BASE_SHAPE */
        JSTRACE_TYPE_OBJECT,/* FINALIZE_TYPE_OBJECT */
#if JS_HAS_XML_SUPPORT      /* FINALIZE_XML */
        JSTRACE_XML,
#endif
        JSTRACE_STRING,     /* FINALIZE_SHORT_STRING */
        JSTRACE_STRING,     /* FINALIZE_STRING */
        JSTRACE_STRING,     /* FINALIZE_EXTERNAL_STRING */
    };
    return map[thingKind];
}

inline JSGCTraceKind
GetGCThingTraceKind(const void *thing);

struct ArenaLists {

    /*
     * ArenaList::head points to the start of the list. Normally cursor points
     * to the first arena in the list with some free things and all arenas
     * before cursor are fully allocated. However, as the arena currently being
     * allocated from is considered full while its list of free spans is moved
     * into the freeList, during the GC or cell enumeration, when an
     * unallocated freeList is moved back to the arena, we can see an arena
     * with some free cells before the cursor. The cursor is an indirect
     * pointer to allow for efficient list insertion at the cursor point and
     * other list manipulations.
     */
    struct ArenaList {
        ArenaHeader     *head;
        ArenaHeader     **cursor;

        ArenaList() {
            clear();
        }

        void clear() {
            head = NULL;
            cursor = &head;
        }
    };

  private:
    /*
     * For each arena kind its free list is represented as the first span with
     * free things. Initially all the spans are initialized as empty. After we
     * find a new arena with available things we move its first free span into
     * the list and set the arena as fully allocated. way we do not need to
     * update the arena header after the initial allocation. When starting the
     * GC we only move the head of the of the list of spans back to the arena
     * only for the arena that was not fully allocated.
     */
    FreeSpan       freeLists[FINALIZE_LIMIT];

    ArenaList      arenaLists[FINALIZE_LIMIT];

#ifdef JS_THREADSAFE
    /*
     * The background finalization adds the finalized arenas to the list at
     * the *cursor position. backgroundFinalizeState controls the interaction
     * between the GC lock and the access to the list from the allocation
     * thread.
     *
     * BFS_DONE indicates that the finalizations is not running or cannot
     * affect this arena list. The allocation thread can access the list
     * outside the GC lock.
     *
     * In BFS_RUN and BFS_JUST_FINISHED the allocation thread must take the
     * lock. The former indicates that the finalization still runs. The latter
     * signals that finalization just added to the list finalized arenas. In
     * that case the lock effectively serves as a read barrier to ensure that
     * the allocation thread see all the writes done during finalization.
     */
    enum BackgroundFinalizeState {
        BFS_DONE,
        BFS_RUN,
        BFS_JUST_FINISHED
    };

    volatile uintptr_t backgroundFinalizeState[FINALIZE_LIMIT];
#endif

  public:
    ArenaLists() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            freeLists[i].initAsEmpty();
#ifdef JS_THREADSAFE
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            backgroundFinalizeState[i] = BFS_DONE;
#endif
    }

    ~ArenaLists() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
#ifdef JS_THREADSAFE
            /*
             * We can only call this during the shutdown after the last GC when
             * the background finalization is disabled.
             */
            JS_ASSERT(backgroundFinalizeState[i] == BFS_DONE);
#endif
            ArenaHeader **headp = &arenaLists[i].head;
            while (ArenaHeader *aheader = *headp) {
                *headp = aheader->next;
                aheader->chunk()->releaseArena(aheader);
            }
        }
    }

    const FreeSpan *getFreeList(AllocKind thingKind) const {
        return &freeLists[thingKind];
    }

    ArenaHeader *getFirstArena(AllocKind thingKind) const {
        return arenaLists[thingKind].head;
    }

    bool arenaListsAreEmpty() const {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
#ifdef JS_THREADSAFE
            /*
             * The arena cannot be empty if the background finalization is not yet
             * done.
             */
            if (backgroundFinalizeState[i] != BFS_DONE)
                return false;
#endif
            if (arenaLists[i].head)
                return false;
        }
        return true;
    }

#ifdef DEBUG
    bool checkArenaListAllUnmarked() const {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
# ifdef JS_THREADSAFE
            /* The background finalization must have stopped at this point. */
            JS_ASSERT(backgroundFinalizeState[i] == BFS_DONE ||
                      backgroundFinalizeState[i] == BFS_JUST_FINISHED);
# endif
            for (ArenaHeader *aheader = arenaLists[i].head; aheader; aheader = aheader->next) {
                if (!aheader->chunk()->bitmap.noBitsSet(aheader))
                    return false;
            }
        }
        return true;
    }
#endif

#ifdef JS_THREADSAFE
    bool doneBackgroundFinalize(AllocKind kind) const {
        return backgroundFinalizeState[kind] == BFS_DONE;
    }
#endif

    /*
     * Return the free list back to the arena so the GC finalization will not
     * run the finalizers over unitialized bytes from free things.
     */
    void purge() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
            FreeSpan *headSpan = &freeLists[i];
            if (!headSpan->isEmpty()) {
                ArenaHeader *aheader = headSpan->arenaHeader();
                aheader->setFirstFreeSpan(headSpan);
                headSpan->initAsEmpty();
            }
        }
    }

    inline void prepareForIncrementalGC(JSRuntime *rt);

    /*
     * Temporarily copy the free list heads to the arenas so the code can see
     * the proper value in ArenaHeader::freeList when accessing the latter
     * outside the GC.
     */
    void copyFreeListsToArenas() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            copyFreeListToArena(AllocKind(i));
    }

    void copyFreeListToArena(AllocKind thingKind) {
        FreeSpan *headSpan = &freeLists[thingKind];
        if (!headSpan->isEmpty()) {
            ArenaHeader *aheader = headSpan->arenaHeader();
            JS_ASSERT(!aheader->hasFreeThings());
            aheader->setFirstFreeSpan(headSpan);
        }
    }

    /*
     * Clear the free lists in arenas that were temporarily set there using
     * copyToArenas.
     */
    void clearFreeListsInArenas() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            clearFreeListInArena(AllocKind(i));
    }


    void clearFreeListInArena(AllocKind kind) {
        FreeSpan *headSpan = &freeLists[kind];
        if (!headSpan->isEmpty()) {
            ArenaHeader *aheader = headSpan->arenaHeader();
            JS_ASSERT(aheader->getFirstFreeSpan().isSameNonEmptySpan(headSpan));
            aheader->setAsFullyUsed();
        }
    }

    /*
     * Check that the free list is either empty or were synchronized with the
     * arena using copyToArena().
     */
    bool isSynchronizedFreeList(AllocKind kind) {
        FreeSpan *headSpan = &freeLists[kind];
        if (headSpan->isEmpty())
            return true;
        ArenaHeader *aheader = headSpan->arenaHeader();
        if (aheader->hasFreeThings()) {
            /*
             * If the arena has a free list, it must be the same as one in
             * lists.
             */
            JS_ASSERT(aheader->getFirstFreeSpan().isSameNonEmptySpan(headSpan));
            return true;
        }
        return false;
    }

    JS_ALWAYS_INLINE void *allocateFromFreeList(AllocKind thingKind, size_t thingSize) {
        return freeLists[thingKind].allocate(thingSize);
    }

    static void *refillFreeList(JSContext *cx, AllocKind thingKind);

    void checkEmptyFreeLists() {
#ifdef DEBUG
        for (size_t i = 0; i < mozilla::ArrayLength(freeLists); ++i)
            JS_ASSERT(freeLists[i].isEmpty());
#endif
    }

    void checkEmptyFreeList(AllocKind kind) {
        JS_ASSERT(freeLists[kind].isEmpty());
    }

    void finalizeObjects(JSContext *cx);
    void finalizeStrings(JSContext *cx);
    void finalizeShapes(JSContext *cx);
    void finalizeScripts(JSContext *cx);

#ifdef JS_THREADSAFE
    static void backgroundFinalize(JSContext *cx, ArenaHeader *listHead);
#endif

  private:
    inline void finalizeNow(JSContext *cx, AllocKind thingKind);
    inline void finalizeLater(JSContext *cx, AllocKind thingKind);

    inline void *allocateFromArena(JSCompartment *comp, AllocKind thingKind);
};

/*
 * Initial allocation size for data structures holding chunks is set to hold
 * chunks with total capacity of 16MB to avoid buffer resizes during browser
 * startup.
 */
const size_t INITIAL_CHUNK_CAPACITY = 16 * 1024 * 1024 / ChunkSize;

/* The number of GC cycles an empty chunk can survive before been released. */
const size_t MAX_EMPTY_CHUNK_AGE = 4;

inline Cell *
AsCell(JSObject *obj)
{
    return reinterpret_cast<Cell *>(obj);
}

} /* namespace gc */

struct GCPtrHasher
{
    typedef void *Lookup;

    static HashNumber hash(void *key) {
        return HashNumber(uintptr_t(key) >> JS_GCTHING_ZEROBITS);
    }

    static bool match(void *l, void *k) { return l == k; }
};

typedef HashMap<void *, uint32_t, GCPtrHasher, SystemAllocPolicy> GCLocks;

struct RootInfo {
    RootInfo() {}
    RootInfo(const char *name, JSGCRootType type) : name(name), type(type) {}
    const char *name;
    JSGCRootType type;
};

typedef js::HashMap<void *,
                    RootInfo,
                    js::DefaultHasher<void *>,
                    js::SystemAllocPolicy> RootedValueMap;

} /* namespace js */

extern JS_FRIEND_API(JSGCTraceKind)
js_GetGCThingTraceKind(void *thing);

extern JSBool
js_InitGC(JSRuntime *rt, uint32_t maxbytes);

extern void
js_FinishGC(JSRuntime *rt);

extern JSBool
js_AddRoot(JSContext *cx, js::Value *vp, const char *name);

extern JSBool
js_AddGCThingRoot(JSContext *cx, void **rp, const char *name);

#ifdef DEBUG
extern void
js_DumpNamedRoots(JSRuntime *rt,
                  void (*dump)(const char *name, void *rp, JSGCRootType type, void *data),
                  void *data);
#endif

extern uint32_t
js_MapGCRoots(JSRuntime *rt, JSGCRootMapFun map, void *data);

/* Table of pointers with count valid members. */
typedef struct JSPtrTable {
    size_t      count;
    void        **array;
} JSPtrTable;

extern JSBool
js_LockGCThingRT(JSRuntime *rt, void *thing);

extern void
js_UnlockGCThingRT(JSRuntime *rt, void *thing);

extern JS_FRIEND_API(bool)
IsAboutToBeFinalized(const js::gc::Cell *thing);

extern bool
IsAboutToBeFinalized(const js::Value &value);

extern bool
js_IsAddressableGCThing(JSRuntime *rt, uintptr_t w, js::gc::AllocKind *thingKind, void **thing);

namespace js {

extern void
MarkCompartmentActive(js::StackFrame *fp);

extern void
TraceRuntime(JSTracer *trc);

extern JS_FRIEND_API(void)
MarkContext(JSTracer *trc, JSContext *acx);

/* Must be called with GC lock taken. */
extern void
TriggerGC(JSRuntime *rt, js::gcreason::Reason reason);

/* Must be called with GC lock taken. */
extern void
TriggerCompartmentGC(JSCompartment *comp, js::gcreason::Reason reason);

extern void
MaybeGC(JSContext *cx);

extern void
ShrinkGCBuffers(JSRuntime *rt);

/*
 * Kinds of js_GC invocation.
 */
typedef enum JSGCInvocationKind {
    /* Normal invocation. */
    GC_NORMAL           = 0,

    /* Minimize GC triggers and release empty GC chunks right away. */
    GC_SHRINK             = 1
} JSGCInvocationKind;

/* Pass NULL for |comp| to get a full GC. */
extern void
GC(JSContext *cx, JSCompartment *comp, JSGCInvocationKind gckind, js::gcreason::Reason reason);

extern void
GCSlice(JSContext *cx, JSCompartment *comp, JSGCInvocationKind gckind, js::gcreason::Reason reason);

extern void
GCDebugSlice(JSContext *cx, int64_t objCount);

} /* namespace js */

namespace js {

void
InitTracer(JSTracer *trc, JSRuntime *rt, JSTraceCallback callback);

#ifdef JS_THREADSAFE

class GCHelperThread {
    enum State {
        IDLE,
        SWEEPING,
        ALLOCATING,
        CANCEL_ALLOCATION,
        SHUTDOWN
    };

    /*
     * During the finalization we do not free immediately. Rather we add the
     * corresponding pointers to a buffer which we later release on a
     * separated thread.
     *
     * The buffer is implemented as a vector of 64K arrays of pointers, not as
     * a simple vector, to avoid realloc calls during the vector growth and to
     * not bloat the binary size of the inlined freeLater method. Any OOM
     * during buffer growth results in the pointer being freed immediately.
     */
    static const size_t FREE_ARRAY_SIZE = size_t(1) << 16;
    static const size_t FREE_ARRAY_LENGTH = FREE_ARRAY_SIZE / sizeof(void *);

    JSRuntime         *const rt;
    PRThread          *thread;
    PRCondVar         *wakeup;
    PRCondVar         *done;
    volatile State    state;

    JSContext         *finalizationContext;
    bool              shrinkFlag;

    Vector<void **, 16, js::SystemAllocPolicy> freeVector;
    void            **freeCursor;
    void            **freeCursorEnd;

    Vector<js::gc::ArenaHeader *, 64, js::SystemAllocPolicy> finalizeVector;

    bool    backgroundAllocation;

    friend struct js::gc::ArenaLists;

    JS_FRIEND_API(void)
    replenishAndFreeLater(void *ptr);

    static void freeElementsAndArray(void **array, void **end) {
        JS_ASSERT(array <= end);
        for (void **p = array; p != end; ++p)
            js::Foreground::free_(*p);
        js::Foreground::free_(array);
    }

    static void threadMain(void* arg);
    void threadLoop();

    /* Must be called with the GC lock taken. */
    void doSweep();

  public:
    GCHelperThread(JSRuntime *rt)
      : rt(rt),
        thread(NULL),
        wakeup(NULL),
        done(NULL),
        state(IDLE),
        finalizationContext(NULL),
        shrinkFlag(false),
        freeCursor(NULL),
        freeCursorEnd(NULL),
        backgroundAllocation(true)
    { }

    bool init();
    void finish();

    /* Must be called with the GC lock taken. */
    void startBackgroundSweep(JSContext *cx, bool shouldShrink);

    /* Must be called with the GC lock taken. */
    void startBackgroundShrink();

    /* Must be called with the GC lock taken. */
    void waitBackgroundSweepEnd();

    /* Must be called with the GC lock taken. */
    void waitBackgroundSweepOrAllocEnd();

    /* Must be called with the GC lock taken. */
    inline void startBackgroundAllocationIfIdle();

    bool canBackgroundAllocate() const {
        return backgroundAllocation;
    }

    void disableBackgroundAllocation() {
        backgroundAllocation = false;
    }

    PRThread *getThread() const {
        return thread;
    }

    /*
     * Outside the GC lock may give true answer when in fact the sweeping has
     * been done.
     */
    bool sweeping() const {
        return state == SWEEPING;
    }

    bool shouldShrink() const {
        JS_ASSERT(sweeping());
        return shrinkFlag;
    }

    void freeLater(void *ptr) {
        JS_ASSERT(!sweeping());
        if (freeCursor != freeCursorEnd)
            *freeCursor++ = ptr;
        else
            replenishAndFreeLater(ptr);
    }

    /* Must be called with the GC lock taken. */
    bool prepareForBackgroundSweep();
};

#endif /* JS_THREADSAFE */

struct GCChunkHasher {
    typedef gc::Chunk *Lookup;

    /*
     * Strip zeros for better distribution after multiplying by the golden
     * ratio.
     */
    static HashNumber hash(gc::Chunk *chunk) {
        JS_ASSERT(!(uintptr_t(chunk) & gc::ChunkMask));
        return HashNumber(uintptr_t(chunk) >> gc::ChunkShift);
    }

    static bool match(gc::Chunk *k, gc::Chunk *l) {
        JS_ASSERT(!(uintptr_t(k) & gc::ChunkMask));
        JS_ASSERT(!(uintptr_t(l) & gc::ChunkMask));
        return k == l;
    }
};

typedef HashSet<js::gc::Chunk *, GCChunkHasher, SystemAllocPolicy> GCChunkSet;

template<class T>
struct MarkStack {
    T *stack;
    T *tos;
    T *limit;

    T *ballast;
    T *ballastLimit;

    size_t sizeLimit;

    MarkStack(size_t sizeLimit)
      : stack(NULL),
        tos(NULL),
        limit(NULL),
        ballast(NULL),
        ballastLimit(NULL),
        sizeLimit(sizeLimit) { }

    ~MarkStack() {
        if (stack != ballast)
            js_free(stack);
        js_free(ballast);
    }

    bool init(size_t ballastcap) {
        JS_ASSERT(!stack);

        if (ballastcap == 0)
            return true;

        ballast = (T *)js_malloc(sizeof(T) * ballastcap);
        if (!ballast)
            return false;
        ballastLimit = ballast + ballastcap;
        initFromBallast();
        return true;
    }

    void initFromBallast() {
        stack = ballast;
        limit = ballastLimit;
        if (size_t(limit - stack) > sizeLimit)
            limit = stack + sizeLimit;
        tos = stack;
    }

    void setSizeLimit(size_t size) {
        JS_ASSERT(isEmpty());

        sizeLimit = size;
        reset();
    }

    bool push(T item) {
        if (tos == limit) {
            if (!enlarge())
                return false;
        }
        JS_ASSERT(tos < limit);
        *tos++ = item;
        return true;
    }

    bool push(T item1, T item2, T item3) {
        T *nextTos = tos + 3;
        if (nextTos > limit) {
            if (!enlarge())
                return false;
            nextTos = tos + 3;
        }
        JS_ASSERT(nextTos <= limit);
        tos[0] = item1;
        tos[1] = item2;
        tos[2] = item3;
        tos = nextTos;
        return true;
    }

    bool isEmpty() const {
        return tos == stack;
    }

    T pop() {
        JS_ASSERT(!isEmpty());
        return *--tos;
    }

    ptrdiff_t position() const {
        return tos - stack;
    }

    void reset() {
        if (stack != ballast)
            js_free(stack);
        initFromBallast();
        JS_ASSERT(stack == ballast);
    }

    bool enlarge() {
        size_t tosIndex = tos - stack;
        size_t cap = limit - stack;
        if (cap == sizeLimit)
            return false;
        size_t newcap = cap * 2;
        if (newcap == 0)
            newcap = 32;
        if (newcap > sizeLimit)
            newcap = sizeLimit;

        T *newStack;
        if (stack == ballast) {
            newStack = (T *)js_malloc(sizeof(T) * newcap);
            if (!newStack)
                return false;
            for (T *src = stack, *dst = newStack; src < tos; )
                *dst++ = *src++;
        } else {
            newStack = (T *)js_realloc(stack, sizeof(T) * newcap);
            if (!newStack)
                return false;
        }
        stack = newStack;
        tos = stack + tosIndex;
        limit = newStack + newcap;
        return true;
    }

    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const {
        size_t n = 0;
        if (stack != ballast)
            n += mallocSizeOf(stack);
        n += mallocSizeOf(ballast);
        return n;
    }
};

/*
 * This class records how much work has been done in a given GC slice, so that
 * we can return before pausing for too long. Some slices are allowed to run for
 * unlimited time, and others are bounded. To reduce the number of gettimeofday
 * calls, we only check the time every 1000 operations.
 */
struct SliceBudget {
    int64_t deadline; /* in microseconds */
    intptr_t counter;

    static const intptr_t CounterReset = 1000;

    static const int64_t Unlimited = 0;
    static int64_t TimeBudget(int64_t millis);
    static int64_t WorkBudget(int64_t work);

    /* Equivalent to SliceBudget(UnlimitedBudget). */
    SliceBudget();

    /* Instantiate as SliceBudget(Time/WorkBudget(n)). */
    SliceBudget(int64_t budget);

    void reset() {
        deadline = INT64_MAX;
        counter = INTPTR_MAX;
    }

    void step() {
        counter--;
    }

    bool checkOverBudget();

    bool isOverBudget() {
        if (counter > 0)
            return false;
        return checkOverBudget();
    }
};

static const size_t MARK_STACK_LENGTH = 32768;

struct GCMarker : public JSTracer {
  private:
    /*
     * We use a common mark stack to mark GC things of different types and use
     * the explicit tags to distinguish them when it cannot be deduced from
     * the context of push or pop operation.
     */
    enum StackTag {
        ValueArrayTag,
        ObjectTag,
        TypeTag,
        XmlTag,
        SavedValueArrayTag,
        LastTag = SavedValueArrayTag
    };

    static const uintptr_t StackTagMask = 7;

    static void staticAsserts() {
        JS_STATIC_ASSERT(StackTagMask >= uintptr_t(LastTag));
        JS_STATIC_ASSERT(StackTagMask <= gc::Cell::CellMask);
    }

  public:
    explicit GCMarker();
    bool init();

    void setSizeLimit(size_t size) { stack.setSizeLimit(size); }
    size_t sizeLimit() const { return stack.sizeLimit; }

    void start(JSRuntime *rt);
    void stop();
    void reset();

    void pushObject(JSObject *obj) {
        pushTaggedPtr(ObjectTag, obj);
    }

    void pushType(types::TypeObject *type) {
        pushTaggedPtr(TypeTag, type);
    }

    void pushXML(JSXML *xml) {
        pushTaggedPtr(XmlTag, xml);
    }

    uint32_t getMarkColor() const {
        return color;
    }

    /*
     * The only valid color transition during a GC is from black to gray. It is
     * wrong to switch the mark color from gray to black. The reason is that the
     * cycle collector depends on the invariant that there are no black to gray
     * edges in the GC heap. This invariant lets the CC not trace through black
     * objects. If this invariant is violated, the cycle collector may free
     * objects that are still reachable.
     */
    void setMarkColorGray() {
        JS_ASSERT(isDrained());
        JS_ASSERT(color == gc::BLACK);
        color = gc::GRAY;
    }

    inline void delayMarkingArena(gc::ArenaHeader *aheader);
    void delayMarkingChildren(const void *thing);
    void markDelayedChildren(gc::ArenaHeader *aheader);
    bool markDelayedChildren(SliceBudget &budget);
    bool hasDelayedChildren() const {
        return !!unmarkedArenaStackTop;
    }

    bool isDrained() {
        return isMarkStackEmpty() && !unmarkedArenaStackTop;
    }

    bool drainMarkStack(SliceBudget &budget);

    /*
     * Gray marking must be done after all black marking is complete. However,
     * we do not have write barriers on XPConnect roots. Therefore, XPConnect
     * roots must be accumulated in the first slice of incremental GC. We
     * accumulate these roots in the GrayRootMarker and then mark them later,
     * after black marking is complete. This accumulation can fail, but in that
     * case we switch to non-incremental GC.
     */
    bool hasBufferedGrayRoots() const;
    void startBufferingGrayRoots();
    void endBufferingGrayRoots();
    void markBufferedGrayRoots();

    static void GrayCallback(JSTracer *trc, void **thing, JSGCTraceKind kind);

    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const;

    MarkStack<uintptr_t> stack;

  private:
#ifdef DEBUG
    void checkCompartment(void *p);
#else
    void checkCompartment(void *p) {}
#endif

    void pushTaggedPtr(StackTag tag, void *ptr) {
        checkCompartment(ptr);
        uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
        JS_ASSERT(!(addr & StackTagMask));
        if (!stack.push(addr | uintptr_t(tag)))
            delayMarkingChildren(ptr);
    }

    void pushValueArray(JSObject *obj, void *start, void *end) {
        checkCompartment(obj);

        if (start == end)
            return;

        JS_ASSERT(start <= end);
        uintptr_t tagged = reinterpret_cast<uintptr_t>(obj) | GCMarker::ValueArrayTag;
        uintptr_t startAddr = reinterpret_cast<uintptr_t>(start);
        uintptr_t endAddr = reinterpret_cast<uintptr_t>(end);

        /*
         * Push in the reverse order so obj will be on top. If we cannot push
         * the array, we trigger delay marking for the whole object.
         */
        if (!stack.push(endAddr, startAddr, tagged))
            delayMarkingChildren(obj);
    }

    bool isMarkStackEmpty() {
        return stack.isEmpty();
    }

    bool restoreValueArray(JSObject *obj, void **vpp, void **endp);
    void saveValueRanges();
    inline void processMarkStackTop(SliceBudget &budget);

    void appendGrayRoot(void *thing, JSGCTraceKind kind);

    /* The color is only applied to objects, functions and xml. */
    uint32_t color;

    DebugOnly<bool> started;

    /* Pointer to the top of the stack of arenas we are delaying marking on. */
    js::gc::ArenaHeader *unmarkedArenaStackTop;
    /* Count of arenas that are currently in the stack. */
    DebugOnly<size_t> markLaterArenas;

    struct GrayRoot {
        void *thing;
        JSGCTraceKind kind;
#ifdef DEBUG
        JSTraceNamePrinter debugPrinter;
        const void *debugPrintArg;
        size_t debugPrintIndex;
#endif

        GrayRoot(void *thing, JSGCTraceKind kind)
          : thing(thing), kind(kind) {}
    };

    bool grayFailed;
    Vector<GrayRoot, 0, SystemAllocPolicy> grayRoots;
};

void
SetMarkStackLimit(JSRuntime *rt, size_t limit);

void
MarkStackRangeConservatively(JSTracer *trc, Value *begin, Value *end);

typedef void (*IterateChunkCallback)(JSRuntime *rt, void *data, gc::Chunk *chunk);
typedef void (*IterateArenaCallback)(JSRuntime *rt, void *data, gc::Arena *arena,
                                     JSGCTraceKind traceKind, size_t thingSize);
typedef void (*IterateCellCallback)(JSRuntime *rt, void *data, void *thing,
                                    JSGCTraceKind traceKind, size_t thingSize);

/*
 * This function calls |compartmentCallback| on every compartment,
 * |arenaCallback| on every in-use arena, and |cellCallback| on every in-use
 * cell in the GC heap.
 */
extern JS_FRIEND_API(void)
IterateCompartmentsArenasCells(JSRuntime *rt, void *data,
                               JSIterateCompartmentCallback compartmentCallback,
                               IterateArenaCallback arenaCallback,
                               IterateCellCallback cellCallback);

/*
 * Invoke chunkCallback on every in-use chunk.
 */
extern JS_FRIEND_API(void)
IterateChunks(JSRuntime *rt, void *data, IterateChunkCallback chunkCallback);

/*
 * Invoke cellCallback on every in-use object of the specified thing kind for
 * the given compartment or for all compartments if it is null.
 */
extern JS_FRIEND_API(void)
IterateCells(JSRuntime *rt, JSCompartment *compartment, gc::AllocKind thingKind,
             void *data, IterateCellCallback cellCallback);

} /* namespace js */

extern void
js_FinalizeStringRT(JSRuntime *rt, JSString *str);

/*
 * Macro to test if a traversal is the marking phase of the GC.
 */
#define IS_GC_MARKING_TRACER(trc) \
    ((trc)->callback == NULL || (trc)->callback == GCMarker::GrayCallback)

namespace js {
namespace gc {

JSCompartment *
NewCompartment(JSContext *cx, JSPrincipals *principals);

/* Tries to run a GC no matter what (used for GC zeal). */
void
RunDebugGC(JSContext *cx);

void
SetDeterministicGC(JSContext *cx, bool enabled);

#if defined(JSGC_ROOT_ANALYSIS) && defined(DEBUG) && !defined(JS_THREADSAFE)
/* Overwrites stack references to GC things which have not been rooted. */
void CheckStackRoots(JSContext *cx);

inline void MaybeCheckStackRoots(JSContext *cx) { CheckStackRoots(cx); }
#else
inline void MaybeCheckStackRoots(JSContext *cx) {}
#endif

const int ZealPokeValue = 1;
const int ZealAllocValue = 2;
const int ZealFrameGCValue = 3;
const int ZealVerifierValue = 4;
const int ZealFrameVerifierValue = 5;

#ifdef JS_GC_ZEAL

/* Check that write barriers have been used correctly. See jsgc.cpp. */
void
VerifyBarriers(JSContext *cx);

void
MaybeVerifyBarriers(JSContext *cx, bool always = false);

#else

static inline void
VerifyBarriers(JSContext *cx)
{
}

static inline void
MaybeVerifyBarriers(JSContext *cx, bool always = false)
{
}

#endif

} /* namespace gc */

static inline JSCompartment *
GetObjectCompartment(JSObject *obj) { return reinterpret_cast<js::gc::Cell *>(obj)->compartment(); }

} /* namespace js */

#endif /* jsgc_h___ */
