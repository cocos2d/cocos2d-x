/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_MemoryMetrics_h
#define js_MemoryMetrics_h

// These declarations are not within jsapi.h because they are highly likely to
// change in the future. Depend on them at your own risk.

#include <string.h>

#include "jsalloc.h"
#include "jspubtd.h"

#include "js/Utility.h"
#include "js/Vector.h"

namespace js {

// In memory reporting, we have concept of "sundries", line items which are too
// small to be worth reporting individually.  Under some circumstances, a memory
// reporter gets tossed into the sundries bucket if it's smaller than
// MemoryReportingSundriesThreshold() bytes.
//
// We need to define this value here, rather than in the code which actually
// generates the memory reports, because HugeStringInfo uses this value.
JS_FRIEND_API(size_t) MemoryReportingSundriesThreshold();

} // namespace js

namespace JS {

// Data for tracking analysis/inference memory usage.
struct TypeInferenceSizes
{
    TypeInferenceSizes()
      : scripts(0)
      , objects(0)
      , tables(0)
      , temporary(0)
    {}

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

// Holds data about a huge string (one which uses more HugeStringInfo::MinSize
// bytes of memory), so we can report it individually.
struct HugeStringInfo
{
    HugeStringInfo()
      : length(0)
      , size(0)
    {
        memset(&buffer, 0, sizeof(buffer));
    }

    // A string needs to take up this many bytes of storage before we consider
    // it to be "huge".
    static size_t MinSize()
    {
      return js::MemoryReportingSundriesThreshold();
    }

    // A string's size in memory is not necessarily equal to twice its length
    // because the allocator and the JS engine both may round up.
    size_t length;
    size_t size;

    // We record the first 32 chars of the escaped string here.  (We escape the
    // string so we can use a char[] instead of a jschar[] here.
    char buffer[32];
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
      , jaegerCode(0)
      , ionCode(0)
      , regexpCode(0)
      , unusedCode(0)
      , stack(0)
      , gcMarker(0)
      , mathCache(0)
      , scriptFilenames(0)
      , scriptSources(0)
    {}

    size_t object;
    size_t atomsTable;
    size_t contexts;
    size_t dtoa;
    size_t temporary;
    size_t jaegerCode;
    size_t ionCode;
    size_t regexpCode;
    size_t unusedCode;
    size_t stack;
    size_t gcMarker;
    size_t mathCache;
    size_t scriptFilenames;
    size_t scriptSources;
};

struct CompartmentStats
{
    CompartmentStats()
      : extra1(0)
      , extra2(0)
      , gcHeapArenaAdmin(0)
      , gcHeapUnusedGcThings(0)
      , gcHeapObjectsNonFunction(0)
      , gcHeapObjectsFunction(0)
      , gcHeapStrings(0)
      , gcHeapShapesTree(0)
      , gcHeapShapesDict(0)
      , gcHeapShapesBase(0)
      , gcHeapScripts(0)
      , gcHeapTypeObjects(0)
      , gcHeapIonCodes(0)
#if JS_HAS_XML_SUPPORT
      , gcHeapXML(0)
#endif
      , objectsExtraSlots(0)
      , objectsExtraElements(0)
      , objectsExtraArgumentsData(0)
      , objectsExtraRegExpStatics(0)
      , objectsExtraPropertyIteratorData(0)
      , objectsExtraPrivate(0)
      , nonHugeStringChars(0)
      , shapesExtraTreeTables(0)
      , shapesExtraDictTables(0)
      , shapesExtraTreeShapeKids(0)
      , shapesCompartmentTables(0)
      , scriptData(0)
      , jaegerData(0)
      , ionData(0)
      , compartmentObject(0)
      , crossCompartmentWrappers(0)
      , regexpCompartment(0)
      , debuggeesSet(0)
    {}

    CompartmentStats(const CompartmentStats &other)
      : extra1(other.extra1)
      , extra2(other.extra2)
      , gcHeapArenaAdmin(other.gcHeapArenaAdmin)
      , gcHeapUnusedGcThings(other.gcHeapUnusedGcThings)
      , gcHeapObjectsNonFunction(other.gcHeapObjectsNonFunction)
      , gcHeapObjectsFunction(other.gcHeapObjectsFunction)
      , gcHeapStrings(other.gcHeapStrings)
      , gcHeapShapesTree(other.gcHeapShapesTree)
      , gcHeapShapesDict(other.gcHeapShapesDict)
      , gcHeapShapesBase(other.gcHeapShapesBase)
      , gcHeapScripts(other.gcHeapScripts)
      , gcHeapTypeObjects(other.gcHeapTypeObjects)
      , gcHeapIonCodes(other.gcHeapIonCodes)
#if JS_HAS_XML_SUPPORT
      , gcHeapXML(other.gcHeapXML)
#endif
      , objectsExtraSlots(other.objectsExtraSlots)
      , objectsExtraElements(other.objectsExtraElements)
      , objectsExtraArgumentsData(other.objectsExtraArgumentsData)
      , objectsExtraRegExpStatics(other.objectsExtraRegExpStatics)
      , objectsExtraPropertyIteratorData(other.objectsExtraPropertyIteratorData)
      , objectsExtraPrivate(other.objectsExtraPrivate)
      , nonHugeStringChars(other.nonHugeStringChars)
      , shapesExtraTreeTables(other.shapesExtraTreeTables)
      , shapesExtraDictTables(other.shapesExtraDictTables)
      , shapesExtraTreeShapeKids(other.shapesExtraTreeShapeKids)
      , shapesCompartmentTables(other.shapesCompartmentTables)
      , scriptData(other.scriptData)
      , jaegerData(other.jaegerData)
      , ionData(other.ionData)
      , compartmentObject(other.compartmentObject)
      , crossCompartmentWrappers(other.crossCompartmentWrappers)
      , regexpCompartment(other.regexpCompartment)
      , debuggeesSet(other.debuggeesSet)
      , typeInferenceSizes(other.typeInferenceSizes)
    {
      hugeStrings.append(other.hugeStrings);
    }

    // These fields can be used by embedders.
    void   *extra1;
    void   *extra2;

    // If you add a new number, remember to update the constructors, add(), and
    // maybe gcHeapThingsSize()!
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
    size_t gcHeapIonCodes;
#if JS_HAS_XML_SUPPORT
    size_t gcHeapXML;
#endif

    size_t objectsExtraSlots;
    size_t objectsExtraElements;
    size_t objectsExtraArgumentsData;
    size_t objectsExtraRegExpStatics;
    size_t objectsExtraPropertyIteratorData;
    size_t objectsExtraPrivate;
    size_t nonHugeStringChars;
    size_t shapesExtraTreeTables;
    size_t shapesExtraDictTables;
    size_t shapesExtraTreeShapeKids;
    size_t shapesCompartmentTables;
    size_t scriptData;
    size_t jaegerData;
    size_t ionData;
    size_t compartmentObject;
    size_t crossCompartmentWrappers;
    size_t regexpCompartment;
    size_t debuggeesSet;

    TypeInferenceSizes typeInferenceSizes;
    js::Vector<HugeStringInfo, 0, js::SystemAllocPolicy> hugeStrings;

    // Add cStats's numbers to this object's numbers.
    void add(CompartmentStats &cStats)
    {
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
        ADD(gcHeapIonCodes);
    #if JS_HAS_XML_SUPPORT
        ADD(gcHeapXML);
    #endif

        ADD(objectsExtraSlots);
        ADD(objectsExtraElements);
        ADD(objectsExtraArgumentsData);
        ADD(objectsExtraRegExpStatics);
        ADD(objectsExtraPropertyIteratorData);
        ADD(objectsExtraPrivate);
        ADD(nonHugeStringChars);
        ADD(shapesExtraTreeTables);
        ADD(shapesExtraDictTables);
        ADD(shapesExtraTreeShapeKids);
        ADD(shapesCompartmentTables);
        ADD(scriptData);
        ADD(jaegerData);
        ADD(ionData);
        ADD(compartmentObject);
        ADD(crossCompartmentWrappers);
        ADD(regexpCompartment);
        ADD(debuggeesSet);

        #undef ADD

        typeInferenceSizes.add(cStats.typeInferenceSizes);
        hugeStrings.append(cStats.hugeStrings);
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

#endif // JS_THREADSAFE

extern JS_PUBLIC_API(size_t)
SystemCompartmentCount(const JSRuntime *rt);

extern JS_PUBLIC_API(size_t)
UserCompartmentCount(const JSRuntime *rt);

} // namespace JS

#endif // js_MemoryMetrics_h
