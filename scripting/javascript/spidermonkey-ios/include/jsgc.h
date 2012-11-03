/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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
#include "jslock.h"
#include "jsutil.h"
#include "jsversion.h"

#include "ds/BitArray.h"
#include "gc/Heap.h"
#include "gc/Statistics.h"
#include "js/HashTable.h"
#include "js/Vector.h"
#include "js/TemplateLib.h"

struct JSCompartment;

#if JS_STACK_GROWTH_DIRECTION > 0
# define JS_CHECK_STACK_SIZE(limit, lval)  ((uintptr_t)(lval) < limit)
#else
# define JS_CHECK_STACK_SIZE(limit, lval)  ((uintptr_t)(lval) > limit)
#endif

namespace js {

class GCHelperThread;
struct Shape;
struct SliceBudget;

namespace gc {

enum State {
    NO_INCREMENTAL,
    MARK_ROOTS,
    MARK,
    SWEEP,
    SWEEP_END,
    INVALID
};

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
};

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

static inline bool
IsNurseryAllocable(AllocKind kind)
{
    JS_ASSERT(kind >= 0 && unsigned(kind) < FINALIZE_LIMIT);
    static const bool map[FINALIZE_LIMIT] = {
        false,     /* FINALIZE_OBJECT0 */
        true,      /* FINALIZE_OBJECT0_BACKGROUND */
        false,     /* FINALIZE_OBJECT2 */
        true,      /* FINALIZE_OBJECT2_BACKGROUND */
        false,     /* FINALIZE_OBJECT4 */
        true,      /* FINALIZE_OBJECT4_BACKGROUND */
        false,     /* FINALIZE_OBJECT8 */
        true,      /* FINALIZE_OBJECT8_BACKGROUND */
        false,     /* FINALIZE_OBJECT12 */
        true,      /* FINALIZE_OBJECT12_BACKGROUND */
        false,     /* FINALIZE_OBJECT16 */
        true,      /* FINALIZE_OBJECT16_BACKGROUND */
        false,     /* FINALIZE_SCRIPT */
        false,     /* FINALIZE_SHAPE */
        false,     /* FINALIZE_BASE_SHAPE */
        false,     /* FINALIZE_TYPE_OBJECT */
#if JS_HAS_XML_SUPPORT
        false,     /* FINALIZE_XML */
#endif
        true,      /* FINALIZE_SHORT_STRING */
        true,      /* FINALIZE_STRING */
        false      /* FINALIZE_EXTERNAL_STRING */
    };
    return map[kind];
}

static inline bool
IsBackgroundFinalized(AllocKind kind)
{
    JS_ASSERT(kind >= 0 && unsigned(kind) < FINALIZE_LIMIT);
    static const bool map[FINALIZE_LIMIT] = {
        false,     /* FINALIZE_OBJECT0 */
        true,      /* FINALIZE_OBJECT0_BACKGROUND */
        false,     /* FINALIZE_OBJECT2 */
        true,      /* FINALIZE_OBJECT2_BACKGROUND */
        false,     /* FINALIZE_OBJECT4 */
        true,      /* FINALIZE_OBJECT4_BACKGROUND */
        false,     /* FINALIZE_OBJECT8 */
        true,      /* FINALIZE_OBJECT8_BACKGROUND */
        false,     /* FINALIZE_OBJECT12 */
        true,      /* FINALIZE_OBJECT12_BACKGROUND */
        false,     /* FINALIZE_OBJECT16 */
        true,      /* FINALIZE_OBJECT16_BACKGROUND */
        false,     /* FINALIZE_SCRIPT */
        false,     /* FINALIZE_SHAPE */
        false,     /* FINALIZE_BASE_SHAPE */
        false,     /* FINALIZE_TYPE_OBJECT */
#if JS_HAS_XML_SUPPORT
        false,     /* FINALIZE_XML */
#endif
        true,      /* FINALIZE_SHORT_STRING */
        true,      /* FINALIZE_STRING */
        false      /* FINALIZE_EXTERNAL_STRING */
    };
    return map[kind];
}

inline JSGCTraceKind
GetGCThingTraceKind(const void *thing);

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

    void insert(ArenaHeader *arena);
};

struct ArenaLists {

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

  public:
    /* For each arena kind, a list of arenas remaining to be swept. */
    ArenaHeader *arenaListsToSweep[FINALIZE_LIMIT];

  public:
    ArenaLists() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            freeLists[i].initAsEmpty();
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            backgroundFinalizeState[i] = BFS_DONE;
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i)
            arenaListsToSweep[i] = NULL;
    }

    ~ArenaLists() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
            /*
             * We can only call this during the shutdown after the last GC when
             * the background finalization is disabled.
             */
            JS_ASSERT(backgroundFinalizeState[i] == BFS_DONE);
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

    ArenaHeader *getFirstArenaToSweep(AllocKind thingKind) const {
        return arenaListsToSweep[thingKind];
    }

    bool arenaListsAreEmpty() const {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
            /*
             * The arena cannot be empty if the background finalization is not yet
             * done.
             */
            if (backgroundFinalizeState[i] != BFS_DONE)
                return false;
            if (arenaLists[i].head)
                return false;
        }
        return true;
    }

    bool arenasAreFull(AllocKind thingKind) const {
        return !*arenaLists[thingKind].cursor;
    }

    void unmarkAll() {
        for (size_t i = 0; i != FINALIZE_LIMIT; ++i) {
            /* The background finalization must have stopped at this point. */
            JS_ASSERT(backgroundFinalizeState[i] == BFS_DONE ||
                      backgroundFinalizeState[i] == BFS_JUST_FINISHED);
            for (ArenaHeader *aheader = arenaLists[i].head; aheader; aheader = aheader->next) {
                uintptr_t *word = aheader->chunk()->bitmap.arenaBits(aheader);
                memset(word, 0, ArenaBitmapWords * sizeof(uintptr_t));
            }
        }
    }

    bool doneBackgroundFinalize(AllocKind kind) const {
        return backgroundFinalizeState[kind] == BFS_DONE ||
               backgroundFinalizeState[kind] == BFS_JUST_FINISHED;
    }

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

    void queueObjectsForSweep(FreeOp *fop);
    void queueStringsForSweep(FreeOp *fop);
    void queueShapesForSweep(FreeOp *fop);
    void queueScriptsForSweep(FreeOp *fop);

    bool foregroundFinalize(FreeOp *fop, AllocKind thingKind, SliceBudget &sliceBudget);
    static void backgroundFinalize(FreeOp *fop, ArenaHeader *listHead, bool onBackgroundThread);

  private:
    inline void finalizeNow(FreeOp *fop, AllocKind thingKind);
    inline void queueForForegroundSweep(FreeOp *fop, AllocKind thingKind);
    inline void queueForBackgroundSweep(FreeOp *fop, AllocKind thingKind);

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

extern void
ReleaseAllJITCode(FreeOp *op);

extern JS_FRIEND_API(void)
PrepareForFullGC(JSRuntime *rt);

/*
 * Kinds of js_GC invocation.
 */
typedef enum JSGCInvocationKind {
    /* Normal invocation. */
    GC_NORMAL           = 0,

    /* Minimize GC triggers and release empty GC chunks right away. */
    GC_SHRINK             = 1
} JSGCInvocationKind;

extern void
GC(JSRuntime *rt, JSGCInvocationKind gckind, js::gcreason::Reason reason);

extern void
GCSlice(JSRuntime *rt, JSGCInvocationKind gckind, js::gcreason::Reason reason, int64_t millis = 0);

extern void
GCFinalSlice(JSRuntime *rt, JSGCInvocationKind gckind, js::gcreason::Reason reason);

extern void
GCDebugSlice(JSRuntime *rt, bool limit, int64_t objCount);

extern void
PrepareForDebugGC(JSRuntime *rt);

} /* namespace js */

namespace js {

void
InitTracer(JSTracer *trc, JSRuntime *rt, JSTraceCallback callback);

/*
 * Helper that implements sweeping and allocation for kinds that can be swept
 * and allocated off the main thread.
 *
 * In non-threadsafe builds, all actual sweeping and allocation is performed
 * on the main thread, but GCHelperThread encapsulates this from clients as
 * much as possible.
 */
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

    bool              sweepFlag;
    bool              shrinkFlag;

    Vector<void **, 16, js::SystemAllocPolicy> freeVector;
    void            **freeCursor;
    void            **freeCursorEnd;

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
        sweepFlag(false),
        shrinkFlag(false),
        freeCursor(NULL),
        freeCursorEnd(NULL),
        backgroundAllocation(true)
    { }

    bool init();
    void finish();

    /* Must be called with the GC lock taken. */
    void startBackgroundSweep(bool shouldShrink);

    /* Must be called with the GC lock taken. */
    void startBackgroundShrink();

    /* Must be called without the GC lock taken. */
    void waitBackgroundSweepEnd();

    /* Must be called without the GC lock taken. */
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
};


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

    void step(intptr_t amt = 1) {
        counter -= amt;
    }

    bool checkOverBudget();

    bool isOverBudget() {
        if (counter >= 0)
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
        ArenaTag,
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

    void pushArenaList(gc::ArenaHeader *firstArena) {
        pushTaggedPtr(ArenaTag, firstArena);
    }

    void pushType(types::TypeObject *type) {
        pushTaggedPtr(TypeTag, type);
    }

#if JS_HAS_XML_SUPPORT
    void pushXML(JSXML *xml) {
        pushTaggedPtr(XmlTag, xml);
    }
#endif

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
    void processMarkStackOther(SliceBudget &budget, uintptr_t tag, uintptr_t addr);

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

/*
 * Invoke cellCallback on every gray JS_OBJECT in the given compartment.
 */
extern JS_FRIEND_API(void)
IterateGrayObjects(JSCompartment *compartment, GCThingCallback *cellCallback, void *data);

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

void
SetValidateGC(JSContext *cx, bool enabled);

const int ZealPokeValue = 1;
const int ZealAllocValue = 2;
const int ZealFrameGCValue = 3;
const int ZealVerifierPreValue = 4;
const int ZealFrameVerifierPreValue = 5;
const int ZealStackRootingSafeValue = 6;
const int ZealStackRootingValue = 7;
const int ZealIncrementalRootsThenFinish = 8;
const int ZealIncrementalMarkAllThenFinish = 9;
const int ZealIncrementalMultipleSlices = 10;
const int ZealVerifierPostValue = 11;
const int ZealFrameVerifierPostValue = 12;
const int ZealPurgeAnalysisValue = 13;

enum VerifierType {
    PreBarrierVerifier,
    PostBarrierVerifier
};

#ifdef JS_GC_ZEAL

/* Check that write barriers have been used correctly. See jsgc.cpp. */
void
VerifyBarriers(JSRuntime *rt, VerifierType type);

void
MaybeVerifyBarriers(JSContext *cx, bool always = false);

#else

static inline void
VerifyBarriers(JSRuntime *rt, VerifierType type)
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
