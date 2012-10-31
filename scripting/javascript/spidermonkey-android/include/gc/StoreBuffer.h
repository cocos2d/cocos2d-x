/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifdef JSGC_GENERATIONAL
#ifndef jsgc_storebuffer_h___
#define jsgc_storebuffer_h___

#include "jsgc.h"
#include "jsalloc.h"

#include "gc/Marking.h"

namespace js {
namespace gc {

/*
 * Note: this is a stub Nursery that does not actually contain a heap, just a
 * set of pointers which are "inside" the nursery to implement verification.
 */
class Nursery
{
    HashSet<void*, PointerHasher<void*, 3>, SystemAllocPolicy> nursery;

  public:
    Nursery() : nursery() {}

    bool enable() {
        if (!nursery.initialized())
            return nursery.init();
        return true;
    }

    void disable() {
        if (!nursery.initialized())
            return;
        nursery.finish();
    }

    bool isInside(void *cell) const {
        JS_ASSERT((uintptr_t(cell) & 0x3) == 0);
        return nursery.initialized() && nursery.has(cell);
    }

    void insertPointer(void *cell) {
        nursery.putNew(cell);
    }
};

/*
 * BufferableRef represents an abstract reference for use in the generational
 * GC's remembered set. Entries in the store buffer that cannot be represented
 * with the simple pointer-to-a-pointer scheme must derive from this class and
 * use the generic store buffer interface.
 */
class BufferableRef
{
  public:
    virtual bool match(void *location) = 0;
    virtual void mark(JSTracer *trc) = 0;
};

/*
 * HashKeyRef represents a reference to a HashTable key. Manual HashTable
 * barriers should should instantiate this template with their own table/key
 * type to insert into the generic buffer with putGeneric.
 */
template <typename Map, typename Key>
class HashKeyRef : public BufferableRef
{
    Map *map;
    Key key;

    typedef typename Map::Ptr Ptr;

  public:
    HashKeyRef(Map *m, const Key &k) : map(m), key(k) {}

    bool match(void *location) {
        Ptr p = map->lookup(key);
        if (!p)
            return false;
        return &p->key == location;
    }

    void mark(JSTracer *trc) {}
};

/*
 * The StoreBuffer observes all writes that occur in the system and performs
 * efficient filtering of them to derive a remembered set for nursery GC.
 */
class StoreBuffer
{
    /* TODO: profile to find the ideal size for these. */
    static const size_t ValueBufferSize = 1 * 1024 * sizeof(Value *);
    static const size_t CellBufferSize = 2 * 1024 * sizeof(Cell **);
    static const size_t SlotBufferSize = 2 * 1024 * (sizeof(JSObject *) + sizeof(uint32_t));
    static const size_t RelocValueBufferSize = 1 * 1024 * sizeof(Value *);
    static const size_t RelocCellBufferSize = 1 * 1024 * sizeof(Cell **);
    static const size_t GenericBufferSize = 1 * 1024 * sizeof(int);
    static const size_t TotalSize = ValueBufferSize + CellBufferSize +
                                    SlotBufferSize + RelocValueBufferSize + RelocCellBufferSize +
                                    GenericBufferSize;

    typedef HashSet<void *, PointerHasher<void *, 3>, SystemAllocPolicy> EdgeSet;

    /*
     * This buffer holds only a single type of edge. Using this buffer is more
     * efficient than the generic buffer when many writes will be to the same
     * type of edge: e.g. Value or Cell*.
     */
    template<typename T>
    class MonoTypeBuffer
    {
        friend class StoreBuffer;

        StoreBuffer *owner;
        Nursery *nursery;

        T *base;      /* Pointer to the start of the buffer. */
        T *pos;       /* Pointer to the current insertion position. */
        T *top;       /* Pointer to one element after the end. */

        MonoTypeBuffer(StoreBuffer *owner, Nursery *nursery)
          : owner(owner), nursery(nursery), base(NULL), pos(NULL), top(NULL)
        {}

        MonoTypeBuffer &operator=(const MonoTypeBuffer& other) MOZ_DELETE;

        bool enable(uint8_t *region, size_t len);
        void disable();

        bool isEmpty() const { return pos == base; }
        bool isFull() const { JS_ASSERT(pos <= top); return pos == top; }

        /* Compaction algorithms. */
        void compactNotInSet();

        /*
         * Attempts to reduce the usage of the buffer by removing unnecessary
         * entries.
         */
        virtual void compact();

        /* Add one item to the buffer. */
        void put(const T &v);

        /* For verification. */
        bool accumulateEdges(EdgeSet &edges);
    };

    /*
     * Overrides the MonoTypeBuffer to support pointers that may be moved in
     * memory outside of the GC's control.
     */
    template <typename T>
    class RelocatableMonoTypeBuffer : public MonoTypeBuffer<T>
    {
        friend class StoreBuffer;

        RelocatableMonoTypeBuffer(StoreBuffer *owner, Nursery *nursery)
          : MonoTypeBuffer<T>(owner, nursery)
        {}

        /* Override compaction to filter out removed items. */
        void compactMoved();
        virtual void compact();

        /* Record a removal from the buffer. */
        void unput(const T &v);
    };

    class GenericBuffer
    {
        friend class StoreBuffer;

        StoreBuffer *owner;
        Nursery *nursery;

        uint8_t *base; /* Pointer to start of buffer. */
        uint8_t *pos;  /* Pointer to current buffer position. */
        uint8_t *top;  /* Pointer to one past the last entry. */

        GenericBuffer(StoreBuffer *owner, Nursery *nursery)
          : owner(owner), nursery(nursery)
        {}

        GenericBuffer &operator=(const GenericBuffer& other) MOZ_DELETE;

        bool enable(uint8_t *region, size_t len);
        void disable();

        /* Check if a pointer is present in the buffer. */
        bool containsEdge(void *location) const;

        template <typename T>
        void put(const T &t) {
            /* Check if we have been enabled. */
            if (!pos)
                return;

            /* Check for overflow. */
            if (top - pos < (unsigned)(sizeof(unsigned) + sizeof(T))) {
                owner->setOverflowed();
                return;
            }

            *((unsigned *)pos) = sizeof(T);
            pos += sizeof(unsigned);

            T *p = (T *)pos;
            new (p) T(t);
            pos += sizeof(T);
        }
    };

    class CellPtrEdge
    {
        friend class StoreBuffer;
        friend class StoreBuffer::MonoTypeBuffer<CellPtrEdge>;
        friend class StoreBuffer::RelocatableMonoTypeBuffer<CellPtrEdge>;

        Cell **edge;

        CellPtrEdge(Cell **v) : edge(v) {}
        bool operator==(const CellPtrEdge &other) const { return edge == other.edge; }
        bool operator!=(const CellPtrEdge &other) const { return edge != other.edge; }

        void *location() const { return (void *)edge; }

        bool inRememberedSet(Nursery *n) {
            return !n->isInside(edge) && n->isInside(*edge);
        }

        bool isNullEdge() const {
            return !*edge;
        }

        CellPtrEdge tagged() const { return CellPtrEdge((Cell **)(uintptr_t(edge) | 1)); }
        CellPtrEdge untagged() const { return CellPtrEdge((Cell **)(uintptr_t(edge) & ~1)); }
        bool isTagged() const { return bool(uintptr_t(edge) & 1); }
    };

    class ValueEdge
    {
        friend class StoreBuffer;
        friend class StoreBuffer::MonoTypeBuffer<ValueEdge>;
        friend class StoreBuffer::RelocatableMonoTypeBuffer<ValueEdge>;

        Value *edge;

        ValueEdge(Value *v) : edge(v) {}
        bool operator==(const ValueEdge &other) const { return edge == other.edge; }
        bool operator!=(const ValueEdge &other) const { return edge != other.edge; }

        void *deref() const { return edge->isGCThing() ? edge->toGCThing() : NULL; }
        void *location() const { return (void *)edge; }

        bool inRememberedSet(Nursery *n) {
            return !n->isInside(edge) && n->isInside(deref());
        }

        bool isNullEdge() const {
            return !deref();
        }

        ValueEdge tagged() const { return ValueEdge((Value *)(uintptr_t(edge) | 1)); }
        ValueEdge untagged() const { return ValueEdge((Value *)(uintptr_t(edge) & ~1)); }
        bool isTagged() const { return bool(uintptr_t(edge) & 1); }
    };

    struct SlotEdge
    {
        friend class StoreBuffer;
        friend class StoreBuffer::MonoTypeBuffer<SlotEdge>;

        JSObject *object;
        uint32_t offset;

        SlotEdge(JSObject *object, uint32_t offset) : object(object), offset(offset) {}

        bool operator==(const SlotEdge &other) const {
            return object == other.object && offset == other.offset;
        }

        bool operator!=(const SlotEdge &other) const {
            return object != other.object || offset != other.offset;
        }

        HeapSlot *slotLocation() const {
            if (object->isDenseArray()) {
                if (offset >= object->getDenseArrayInitializedLength())
                    return NULL;
                return (HeapSlot *)&object->getDenseArrayElement(offset);
            }
            if (offset >= object->slotSpan())
                return NULL;
            return &object->getSlotRef(offset);
        }

        void *deref() const {
            HeapSlot *loc = slotLocation();
            return (loc && loc->isGCThing()) ? loc->toGCThing() : NULL;
        }

        void *location() const {
            return (void *)slotLocation();
        }

        bool inRememberedSet(Nursery *n) {
            return !n->isInside(object) && n->isInside(deref());
        }

        bool isNullEdge() const {
            return !deref();
        }
    };

    MonoTypeBuffer<ValueEdge> bufferVal;
    MonoTypeBuffer<CellPtrEdge> bufferCell;
    MonoTypeBuffer<SlotEdge> bufferSlot;
    RelocatableMonoTypeBuffer<ValueEdge> bufferRelocVal;
    RelocatableMonoTypeBuffer<CellPtrEdge> bufferRelocCell;
    GenericBuffer bufferGeneric;

    Nursery *nursery;

    void *buffer;

    bool overflowed;
    bool enabled;

    /* For the verifier. */
    EdgeSet edgeSet;

    /* For use by our owned buffers. */
    void setOverflowed() { overflowed = true; }

  public:
    StoreBuffer(Nursery *n)
      : bufferVal(this, n), bufferCell(this, n), bufferSlot(this, n),
        bufferRelocVal(this, n), bufferRelocCell(this, n), bufferGeneric(this, n),
        nursery(n), buffer(NULL), overflowed(false), enabled(false)
    {}

    bool enable();
    void disable();
    bool isEnabled() { return enabled; }

    /* Get the overflowed status. */
    bool hasOverflowed() const { return overflowed; }

    /* Insert a single edge into the buffer/remembered set. */
    void putValue(Value *v) {
        bufferVal.put(v);
    }
    void putCell(Cell **o) {
        bufferCell.put(o);
    }
    void putSlot(JSObject *obj, uint32_t slot) {
        bufferSlot.put(SlotEdge(obj, slot));
    }

    /* Insert or update a single edge in the Relocatable buffer. */
    void putRelocatableValue(Value *v) {
        bufferRelocVal.put(v);
    }
    void putRelocatableCell(Cell **c) {
        bufferRelocCell.put(c);
    }
    void removeRelocatableValue(Value *v) {
        bufferRelocVal.unput(v);
    }
    void removeRelocatableCell(Cell **c) {
        bufferRelocCell.unput(c);
    }

    /* Insert an entry into the generic buffer. */
    template <typename T>
    void putGeneric(const T &t) {
        bufferGeneric.put(t);
    }

    /* For the verifier. */
    bool coalesceForVerification();
    void releaseVerificationData();
    bool containsEdgeAt(void *loc) const;
};

} /* namespace gc */
} /* namespace js */

#endif /* jsgc_storebuffer_h___ */
#endif /* JSGC_GENERATIONAL */
