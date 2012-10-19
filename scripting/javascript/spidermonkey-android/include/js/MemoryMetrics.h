/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_MemoryMetrics_h
#define js_MemoryMetrics_h

/*
 * These declarations are not within jsapi.h because they are highly likely
 * to change in the future. Depend on them at your own risk.
 */

#include <string.h>

#include "jsalloc.h"
#include "jspubtd.h"

#include "js/Utility.h"
#include "js/Vector.h"

namespace JS {

/* Data for tracking analysis/inference memory usage. */
struct TypeInferenceSizes
{
    size_t scripts;
    size_t objects;
    size_t tables;
    size_t temporary;

    void add(TypeInferenceSizes &sizes) {
        this->scripts   += sizes.scripts;
        this->objects   += sizes.objects;
        this->tables    += sizes.tables;
        this->temporary += sizes.temporary;
    }
};

// These measurements relate directly to the JSRuntime, and not to
// compartments within it.
struct RuntimeSizes
{
    RuntimeSizes()
      : object(0)
      , atomsTable(0)
      , contexts(0)
      , dtoa(0)
      , temporary(0)
      , mjitCode(0)
      , regexpCode(0)
      , unusedCodeMemory(0)
      , stackCommitted(0)
      , gcMarker(0)
      , mathCache(0)
      , scriptFilenames(0)
      , compartmentObjects(0)
    {}

    size_t object;
    size_t atomsTable;
    size_t contexts;
    size_t dtoa;
    size_t temporary;
    size_t mjitCode;
    size_t regexpCode;
    size_t unusedCodeMemory;
    size_t stackCommitted;
    size_t gcMarker;
    size_t mathCache;
    size_t scriptFilenames;

    // This is the exception to the "RuntimeSizes doesn't measure things within
    // compartments" rule.  We combine the sizes of all the JSCompartment
    // objects into a single measurement because each one is fairly small, and
    // they're all the same size.
    size_t compartmentObjects;
};

struct CompartmentStats
{
    CompartmentStats() {
        memset(this, 0, sizeof(*this));
    }

    // These fields can be used by embedders.
    void   *extra1;
    void   *extra2;

    // If you add a new number, remember to update add() and maybe
    // gcHeapThingsSize()!
    size_t gcHeapArenaAdmin;
    size_t gcHeapUnusedGcThings;

    size_t gcHeapObjectsNonFunction;
    size_t gcHeapObjectsFunction;
    size_t gcHeapStrings;
    size_t gcHeapShapesTree;
    size_t gcHeapShapesDict;
    size_t gcHeapShapesBase;
    size_t gcHeapScripts;
    size_t gcHeapTypeObjects;
#if JS_HAS_XML_SUPPORT
    size_t gcHeapXML;
#endif

    size_t objectSlots;
    size_t objectElements;
    size_t objectMisc;
    size_t objectPrivate;
    size_t stringChars;
    size_t shapesExtraTreeTables;
    size_t shapesExtraDictTables;
    size_t shapesExtraTreeShapeKids;
    size_t shapesCompartmentTables;
    size_t scriptData;
    size_t mjitData;
    size_t crossCompartmentWrappers;

    TypeInferenceSizes typeInferenceSizes;

    // Add cStats's numbers to this object's numbers.
    void add(CompartmentStats &cStats) {
        #define ADD(x)  this->x += cStats.x

        ADD(gcHeapArenaAdmin);
        ADD(gcHeapUnusedGcThings);

        ADD(gcHeapObjectsNonFunction);
        ADD(gcHeapObjectsFunction);
        ADD(gcHeapStrings);
        ADD(gcHeapShapesTree);
        ADD(gcHeapShapesDict);
        ADD(gcHeapShapesBase);
        ADD(gcHeapScripts);
        ADD(gcHeapTypeObjects);
    #if JS_HAS_XML_SUPPORT
        ADD(gcHeapXML);
    #endif

        ADD(objectSlots);
        ADD(objectElements);
        ADD(objectMisc);
        ADD(objectPrivate);
        ADD(stringChars);
        ADD(shapesExtraTreeTables);
        ADD(shapesExtraDictTables);
        ADD(shapesExtraTreeShapeKids);
        ADD(shapesCompartmentTables);
        ADD(scriptData);
        ADD(mjitData);
        ADD(crossCompartmentWrappers);

        #undef ADD

        typeInferenceSizes.add(cStats.typeInferenceSizes);
    }

    // The size of all the live things in the GC heap.
    size_t gcHeapThingsSize();
};

struct RuntimeStats
{
    RuntimeStats(JSMallocSizeOfFun mallocSizeOf)
      : runtime()
      , gcHeapChunkTotal(0)
      , gcHeapDecommittedArenas(0)
      , gcHeapUnusedChunks(0)
      , gcHeapUnusedArenas(0)
      , gcHeapUnusedGcThings(0)
      , gcHeapChunkAdmin(0)
      , gcHeapGcThings(0)
      , totals()
      , compartmentStatsVector()
      , currCompartmentStats(NULL)
      , mallocSizeOf(mallocSizeOf)
    {}

    RuntimeSizes runtime;

    // If you add a new number, remember to update the constructor!

    // Here's a useful breakdown of the GC heap.
    //
    // - rtStats.gcHeapChunkTotal
    //   - decommitted bytes
    //     - rtStats.gcHeapDecommittedArenas (decommitted arenas in non-empty chunks)
    //   - unused bytes
    //     - rtStats.gcHeapUnusedChunks (empty chunks)
    //     - rtStats.gcHeapUnusedArenas (empty arenas within non-empty chunks)
    //     - rtStats.total.gcHeapUnusedGcThings (empty GC thing slots within non-empty arenas)
    //   - used bytes
    //     - rtStats.gcHeapChunkAdmin
    //     - rtStats.total.gcHeapArenaAdmin
    //     - rtStats.gcHeapGcThings (in-use GC things)
    //
    // It's possible that some arenas in empty chunks may be decommitted, but
    // we don't count those under rtStats.gcHeapDecommittedArenas because (a)
    // it's rare, and (b) this means that rtStats.gcHeapUnusedChunks is a
    // multiple of the chunk size, which is good.

    size_t gcHeapChunkTotal;
    size_t gcHeapDecommittedArenas;
    size_t gcHeapUnusedChunks;
    size_t gcHeapUnusedArenas;
    size_t gcHeapUnusedGcThings;
    size_t gcHeapChunkAdmin;
    size_t gcHeapGcThings;

    // The sum of all compartment's measurements.
    CompartmentStats totals;
 
    js::Vector<CompartmentStats, 0, js::SystemAllocPolicy> compartmentStatsVector;
    CompartmentStats *currCompartmentStats;

    JSMallocSizeOfFun mallocSizeOf;

    virtual void initExtraCompartmentStats(JSCompartment *c, CompartmentStats *cstats) = 0;
};

#ifdef JS_THREADSAFE

class ObjectPrivateVisitor
{
public:
    // Within CollectRuntimeStats, this method is called for each JS object
    // that has a private slot containing an nsISupports pointer.
    virtual size_t sizeOfIncludingThis(void *aSupports) = 0;
};

extern JS_PUBLIC_API(bool)
CollectRuntimeStats(JSRuntime *rt, RuntimeStats *rtStats, ObjectPrivateVisitor *opv);

extern JS_PUBLIC_API(int64_t)
GetExplicitNonHeapForRuntime(JSRuntime *rt, JSMallocSizeOfFun mallocSizeOf);

#endif /* JS_THREADSAFE */

extern JS_PUBLIC_API(size_t)
SystemCompartmentCount(const JSRuntime *rt);

extern JS_PUBLIC_API(size_t)
UserCompartmentCount(const JSRuntime *rt);

} // namespace JS

#endif // js_MemoryMetrics_h
