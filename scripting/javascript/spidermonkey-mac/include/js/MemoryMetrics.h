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

class nsISupports;      // This is needed for ObjectPrivateVisitor.

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

// Data for tracking memory usage of things hanging off objects.
struct ObjectsExtraSizes {
    size_t slots;
    size_t elements;
    size_t argumentsData;
    size_t regExpStatics;
    size_t propertyIteratorData;
    size_t ctypesData;
    size_t private_;    // The '_' suffix is required because |private| is a keyword.
                        // Note that this field is measured separately from the others.

    ObjectsExtraSizes() { memset(this, 0, sizeof(ObjectsExtraSizes)); }

    void add(ObjectsExtraSizes &sizes) {
        this->slots                += sizes.slots;
        this->elements             += sizes.elements;
        this->argumentsData        += sizes.argumentsData;
        this->regExpStatics        += sizes.regExpStatics;
        this->propertyIteratorData += sizes.propertyIteratorData;
        this->ctypesData           += sizes.ctypesData;
        this->private_             += sizes.private_;
    }
};

// Data for tracking analysis/inference memory usage.
struct TypeInferenceSizes
{
    size_t typeScripts;
    size_t typeResults;
    size_t analysisPool;
    size_t typePool;
    size_t pendingArrays;
    size_t allocationSiteTables;
    size_t arrayTypeTables;
    size_t objectTypeTables;
    size_t typeObjects;

    TypeInferenceSizes() { memset(this, 0, sizeof(TypeInferenceSizes)); }

    void add(TypeInferenceSizes &sizes) {
        this->typeScripts          += sizes.typeScripts;
        this->typeResults          += sizes.typeResults;
        this->analysisPool         += sizes.analysisPool;
        this->typePool             += sizes.typePool;
        this->pendingArrays        += sizes.pendingArrays;
        this->allocationSiteTables += sizes.allocationSiteTables;
        this->arrayTypeTables      += sizes.arrayTypeTables;
        this->objectTypeTables     += sizes.objectTypeTables;
        this->typeObjects          += sizes.typeObjects;
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
    RuntimeSizes() { memset(this, 0, sizeof(RuntimeSizes)); }

    size_t object;
    size_t atomsTable;
    size_t contexts;
    size_t dtoa;
    size_t temporary;
    size_t jaegerCode;
    size_t ionCode;
    size_t regexpCode;
    size_t unusedCode;
    size_t regexpData;
    size_t stack;
    size_t gcMarker;
    size_t mathCache;
    size_t scriptFilenames;
    size_t scriptData;
    size_t scriptSources;
};

struct CompartmentStats
{
    CompartmentStats()
      : extra1(0)
      , extra2(0)
      , gcHeapArenaAdmin(0)
      , gcHeapUnusedGcThings(0)
      , gcHeapObjectsOrdinary(0)
      , gcHeapObjectsFunction(0)
      , gcHeapObjectsDenseArray(0)
      , gcHeapObjectsSlowArray(0)
      , gcHeapObjectsCrossCompartmentWrapper(0)
      , gcHeapStringsNormal(0)
      , gcHeapStringsShort(0)
      , gcHeapShapesTreeGlobalParented(0)
      , gcHeapShapesTreeNonGlobalParented(0)
      , gcHeapShapesDict(0)
      , gcHeapShapesBase(0)
      , gcHeapScripts(0)
      , gcHeapTypeObjects(0)
      , gcHeapIonCodes(0)
      , objectsExtra()
      , stringCharsNonHuge(0)
      , shapesExtraTreeTables(0)
      , shapesExtraDictTables(0)
      , shapesExtraTreeShapeKids(0)
      , shapesCompartmentTables(0)
      , scriptData(0)
      , jaegerData(0)
      , ionData(0)
      , compartmentObject(0)
      , crossCompartmentWrappersTable(0)
      , regexpCompartment(0)
      , debuggeesSet(0)
      , typeInference()
      , hugeStrings()
    {}

    CompartmentStats(const CompartmentStats &other)
      : extra1(other.extra1)
      , extra2(other.extra2)
      , gcHeapArenaAdmin(other.gcHeapArenaAdmin)
      , gcHeapUnusedGcThings(other.gcHeapUnusedGcThings)
      , gcHeapObjectsOrdinary(other.gcHeapObjectsOrdinary)
      , gcHeapObjectsFunction(other.gcHeapObjectsFunction)
      , gcHeapObjectsDenseArray(other.gcHeapObjectsDenseArray)
      , gcHeapObjectsSlowArray(other.gcHeapObjectsSlowArray)
      , gcHeapObjectsCrossCompartmentWrapper(other.gcHeapObjectsCrossCompartmentWrapper)
      , gcHeapStringsNormal(other.gcHeapStringsNormal)
      , gcHeapStringsShort(other.gcHeapStringsShort)
      , gcHeapShapesTreeGlobalParented(other.gcHeapShapesTreeGlobalParented)
      , gcHeapShapesTreeNonGlobalParented(other.gcHeapShapesTreeNonGlobalParented)
      , gcHeapShapesDict(other.gcHeapShapesDict)
      , gcHeapShapesBase(other.gcHeapShapesBase)
      , gcHeapScripts(other.gcHeapScripts)
      , gcHeapTypeObjects(other.gcHeapTypeObjects)
      , gcHeapIonCodes(other.gcHeapIonCodes)
      , objectsExtra(other.objectsExtra)
      , stringCharsNonHuge(other.stringCharsNonHuge)
      , shapesExtraTreeTables(other.shapesExtraTreeTables)
      , shapesExtraDictTables(other.shapesExtraDictTables)
      , shapesExtraTreeShapeKids(other.shapesExtraTreeShapeKids)
      , shapesCompartmentTables(other.shapesCompartmentTables)
      , scriptData(other.scriptData)
      , jaegerData(other.jaegerData)
      , ionData(other.ionData)
      , compartmentObject(other.compartmentObject)
      , crossCompartmentWrappersTable(other.crossCompartmentWrappersTable)
      , regexpCompartment(other.regexpCompartment)
      , debuggeesSet(other.debuggeesSet)
      , typeInference(other.typeInference)
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

    size_t gcHeapObjectsOrdinary;
    size_t gcHeapObjectsFunction;
    size_t gcHeapObjectsDenseArray;
    size_t gcHeapObjectsSlowArray;
    size_t gcHeapObjectsCrossCompartmentWrapper;
    size_t gcHeapStringsNormal;
    size_t gcHeapStringsShort;
    size_t gcHeapShapesTreeGlobalParented;
    size_t gcHeapShapesTreeNonGlobalParented;
    size_t gcHeapShapesDict;
    size_t gcHeapShapesBase;
    size_t gcHeapScripts;
    size_t gcHeapTypeObjects;
    size_t gcHeapIonCodes;
    ObjectsExtraSizes objectsExtra;

    size_t stringCharsNonHuge;
    size_t shapesExtraTreeTables;
    size_t shapesExtraDictTables;
    size_t shapesExtraTreeShapeKids;
    size_t shapesCompartmentTables;
    size_t scriptData;
    size_t jaegerData;
    size_t ionData;
    size_t compartmentObject;
    size_t crossCompartmentWrappersTable;
    size_t regexpCompartment;
    size_t debuggeesSet;

    TypeInferenceSizes typeInference;
    js::Vector<HugeStringInfo, 0, js::SystemAllocPolicy> hugeStrings;

    // Add cStats's numbers to this object's numbers.
    void add(CompartmentStats &cStats)
    {
        #define ADD(x)  this->x += cStats.x

        ADD(gcHeapArenaAdmin);
        ADD(gcHeapUnusedGcThings);

        ADD(gcHeapObjectsOrdinary);
        ADD(gcHeapObjectsFunction);
        ADD(gcHeapObjectsDenseArray);
        ADD(gcHeapObjectsSlowArray);
        ADD(gcHeapObjectsCrossCompartmentWrapper);
        ADD(gcHeapStringsNormal);
        ADD(gcHeapStringsShort);
        ADD(gcHeapShapesTreeGlobalParented);
        ADD(gcHeapShapesTreeNonGlobalParented);
        ADD(gcHeapShapesDict);
        ADD(gcHeapShapesBase);
        ADD(gcHeapScripts);
        ADD(gcHeapTypeObjects);
        ADD(gcHeapIonCodes);
        objectsExtra.add(cStats.objectsExtra);

        ADD(stringCharsNonHuge);
        ADD(shapesExtraTreeTables);
        ADD(shapesExtraDictTables);
        ADD(shapesExtraTreeShapeKids);
        ADD(shapesCompartmentTables);
        ADD(scriptData);
        ADD(jaegerData);
        ADD(ionData);
        ADD(compartmentObject);
        ADD(crossCompartmentWrappersTable);
        ADD(regexpCompartment);
        ADD(debuggeesSet);

        #undef ADD

        typeInference.add(cStats.typeInference);
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
      , mallocSizeOf_(mallocSizeOf)
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

    JSMallocSizeOfFun mallocSizeOf_;

    virtual void initExtraCompartmentStats(JSCompartment *c, CompartmentStats *cstats) = 0;
};

#ifdef JS_THREADSAFE

class ObjectPrivateVisitor
{
public:
    // Within CollectRuntimeStats, this method is called for each JS object
    // that has an nsISupports pointer.
    virtual size_t sizeOfIncludingThis(nsISupports *aSupports) = 0;

    // A callback that gets a JSObject's nsISupports pointer, if it has one.
    // Note: this function does *not* addref |iface|.
    typedef JSBool(*GetISupportsFun)(JSObject *obj, nsISupports **iface);
    GetISupportsFun getISupports_;

    ObjectPrivateVisitor(GetISupportsFun getISupports)
      : getISupports_(getISupports)
    {}
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
