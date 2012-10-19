/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsgc_barrier_h___
#define jsgc_barrier_h___

#include "jsapi.h"

#include "gc/Heap.h"
#include "js/HashTable.h"

/*
 * A write barrier is a mechanism used by incremental or generation GCs to
 * ensure that every value that needs to be marked is marked. In general, the
 * write barrier should be invoked whenever a write can cause the set of things
 * traced through by the GC to change. This includes:
 *   - writes to object properties
 *   - writes to array slots
 *   - writes to fields like JSObject::shape_ that we trace through
 *   - writes to fields in private data, like JSGenerator::obj
 *   - writes to non-markable fields like JSObject::private that point to
 *     markable data
 * The last category is the trickiest. Even though the private pointers does not
 * point to a GC thing, changing the private pointer may change the set of
 * objects that are traced by the GC. Therefore it needs a write barrier.
 *
 * Every barriered write should have the following form:
 *   <pre-barrier>
 *   obj->field = value; // do the actual write
 *   <post-barrier>
 * The pre-barrier is used for incremental GC and the post-barrier is for
 * generational GC.
 *
 *                               PRE-BARRIER
 *
 * To understand the pre-barrier, let's consider how incremental GC works. The
 * GC itself is divided into "slices". Between each slice, JS code is allowed to
 * run. Each slice should be short so that the user doesn't notice the
 * interruptions. In our GC, the structure of the slices is as follows:
 *
 * 1. ... JS work, which leads to a request to do GC ...
 * 2. [first GC slice, which performs all root marking and possibly more marking]
 * 3. ... more JS work is allowed to run ...
 * 4. [GC mark slice, which runs entirely in drainMarkStack]
 * 5. ... more JS work ...
 * 6. [GC mark slice, which runs entirely in drainMarkStack]
 * 7. ... more JS work ...
 * 8. [GC marking finishes; sweeping done non-incrementally; GC is done]
 * 9. ... JS continues uninterrupted now that GC is finishes ...
 *
 * Of course, there may be a different number of slices depending on how much
 * marking is to be done.
 *
 * The danger inherent in this scheme is that the JS code in steps 3, 5, and 7
 * might change the heap in a way that causes the GC to collect an object that
 * is actually reachable. The write barrier prevents this from happening. We use
 * a variant of incremental GC called "snapshot at the beginning." This approach
 * guarantees the invariant that if an object is reachable in step 2, then we
 * will mark it eventually. The name comes from the idea that we take a
 * theoretical "snapshot" of all reachable objects in step 2; all objects in
 * that snapshot should eventually be marked. (Note that the write barrier
 * verifier code takes an actual snapshot.)
 *
 * The basic correctness invariant of a snapshot-at-the-beginning collector is
 * that any object reachable at the end of the GC (step 9) must either:
 *   (1) have been reachable at the beginning (step 2) and thus in the snapshot
 *   (2) or must have been newly allocated, in steps 3, 5, or 7.
 * To deal with case (2), any objects allocated during an incremental GC are
 * automatically marked black.
 *
 * This strategy is actually somewhat conservative: if an object becomes
 * unreachable between steps 2 and 8, it would be safe to collect it. We won't,
 * mainly for simplicity. (Also, note that the snapshot is entirely
 * theoretical. We don't actually do anything special in step 2 that we wouldn't
 * do in a non-incremental GC.
 *
 * It's the pre-barrier's job to maintain the snapshot invariant. Consider the
 * write "obj->field = value". Let the prior value of obj->field be
 * value0. Since it's possible that value0 may have been what obj->field
 * contained in step 2, when the snapshot was taken, the barrier marks
 * value0. Note that it only does this if we're in the middle of an incremental
 * GC. Since this is rare, the cost of the write barrier is usually just an
 * extra branch.
 *
 * In practice, we implement the pre-barrier differently based on the type of
 * value0. E.g., see JSObject::writeBarrierPre, which is used if obj->field is
 * a JSObject*. It takes value0 as a parameter.
 *
 *                                POST-BARRIER
 *
 * These are not yet implemented. Once we get generational GC, they will allow
 * us to keep track of pointers from non-nursery space into the nursery.
 *
 *                            IMPLEMENTATION DETAILS
 *
 * Since it would be awkward to change every write to memory into a function
 * call, this file contains a bunch of C++ classes and templates that use
 * operator overloading to take care of barriers automatically. In many cases,
 * all that's necessary to make some field be barriered is to replace
 *     Type *field;
 * with
 *     HeapPtr<Type> field;
 * There are also special classes HeapValue and HeapId, which barrier js::Value
 * and jsid, respectively.
 *
 * One additional note: not all object writes need to be barriered. Writes to
 * newly allocated objects do not need a pre-barrier.  In these cases, we use
 * the "obj->field.init(value)" method instead of "obj->field = value". We use
 * the init naming idiom in many places to signify that a field is being
 * assigned for the first time.
 */

struct JSXML;

namespace js {

template<class T, typename Unioned = uintptr_t>
class EncapsulatedPtr
{
  protected:
    union {
        T *value;
        Unioned other;
    };

  public:
    EncapsulatedPtr() : value(NULL) {}
    explicit EncapsulatedPtr(T *v) : value(v) {}
    explicit EncapsulatedPtr(const EncapsulatedPtr<T> &v) : value(v.value) {}

    ~EncapsulatedPtr() { pre(); }

    /* Use to set the pointer to NULL. */
    void clear() {
        pre();
        value = NULL;
    }

    EncapsulatedPtr<T, Unioned> &operator=(T *v) {
        pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v));
        value = v;
        return *this;
    }

    EncapsulatedPtr<T, Unioned> &operator=(const EncapsulatedPtr<T> &v) {
        pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v.value));
        value = v.value;
        return *this;
    }

    /* Use this if the automatic coercion to T* isn't working. */
    T *get() const { return value; }

    /*
     * Use these if you want to change the value without invoking the barrier.
     * Obviously this is dangerous unless you know the barrier is not needed.
     */
    T **unsafeGet() { return &value; }
    void unsafeSet(T *v) { value = v; }

    Unioned *unsafeGetUnioned() { return &other; }

    T &operator*() const { return *value; }
    T *operator->() const { return value; }

    operator T*() const { return value; }

  protected:
    void pre() { T::writeBarrierPre(value); }
};

template <class T, class Unioned = uintptr_t>
class HeapPtr : public EncapsulatedPtr<T, Unioned>
{
  public:
    HeapPtr() : EncapsulatedPtr<T>(NULL) {}
    explicit HeapPtr(T *v) : EncapsulatedPtr<T>(v) { post(); }
    explicit HeapPtr(const HeapPtr<T> &v)
      : EncapsulatedPtr<T>(v) { post(); }

    void init(T *v) {
        JS_ASSERT(!IsPoisonedPtr<T>(v));
        this->value = v;
        post();
    }

    HeapPtr<T, Unioned> &operator=(T *v) {
        this->pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v));
        this->value = v;
        post();
        return *this;
    }

    HeapPtr<T, Unioned> &operator=(const HeapPtr<T> &v) {
        this->pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v.value));
        this->value = v.value;
        post();
        return *this;
    }

  protected:
    void post() { T::writeBarrierPost(this->value, (void *)&this->value); }

    /* Make this friend so it can access pre() and post(). */
    template<class T1, class T2>
    friend inline void
    BarrieredSetPair(JSCompartment *comp,
                     HeapPtr<T1> &v1, T1 *val1,
                     HeapPtr<T2> &v2, T2 *val2);
};

template <class T>
class RelocatablePtr : public EncapsulatedPtr<T>
{
  public:
    RelocatablePtr() : EncapsulatedPtr<T>(NULL) {}
    explicit RelocatablePtr(T *v) : EncapsulatedPtr<T>(v) { post(); }
    explicit RelocatablePtr(const RelocatablePtr<T> &v)
      : EncapsulatedPtr<T>(v) { post(); }

    ~RelocatablePtr() {
        this->pre();
        relocate();
    }

    RelocatablePtr<T> &operator=(T *v) {
        this->pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v));
        this->value = v;
        post();
        return *this;
    }

    RelocatablePtr<T> &operator=(const RelocatablePtr<T> &v) {
        this->pre();
        JS_ASSERT(!IsPoisonedPtr<T>(v.value));
        this->value = v.value;
        post();
        return *this;
    }

  protected:
    void post() { T::writeBarrierRelocPost(this->value, (void *)&this->value); }
    void relocate() { T::writeBarrierRelocated(this->value, (void *)&this->value); }
};

/*
 * This is a hack for RegExpStatics::updateFromMatch. It allows us to do two
 * barriers with only one branch to check if we're in an incremental GC.
 */
template<class T1, class T2>
static inline void
BarrieredSetPair(JSCompartment *comp,
                 HeapPtr<T1> &v1, T1 *val1,
                 HeapPtr<T2> &v2, T2 *val2)
{
    if (T1::needWriteBarrierPre(comp)) {
        v1.pre();
        v2.pre();
    }
    v1.unsafeSet(val1);
    v2.unsafeSet(val2);
    v1.post();
    v2.post();
}

struct Shape;
class BaseShape;
namespace types { struct TypeObject; }

typedef RelocatablePtr<JSObject> RelocatablePtrObject;
typedef RelocatablePtr<JSScript> RelocatablePtrScript;

typedef HeapPtr<JSObject> HeapPtrObject;
typedef HeapPtr<JSFunction> HeapPtrFunction;
typedef HeapPtr<JSString> HeapPtrString;
typedef HeapPtr<JSScript> HeapPtrScript;
typedef HeapPtr<Shape> HeapPtrShape;
typedef HeapPtr<BaseShape> HeapPtrBaseShape;
typedef HeapPtr<types::TypeObject> HeapPtrTypeObject;
typedef HeapPtr<JSXML> HeapPtrXML;

/* Useful for hashtables with a HeapPtr as key. */
template<class T>
struct HeapPtrHasher
{
    typedef HeapPtr<T> Key;
    typedef T *Lookup;

    static HashNumber hash(Lookup obj) { return DefaultHasher<T *>::hash(obj); }
    static bool match(const Key &k, Lookup l) { return k.get() == l; }
};

/* Specialized hashing policy for HeapPtrs. */
template <class T>
struct DefaultHasher< HeapPtr<T> > : HeapPtrHasher<T> { };

class EncapsulatedValue : public ValueOperations<EncapsulatedValue>
{
  protected:
    Value value;

    /*
     * Ensure that EncapsulatedValue is not constructable, except by our
     * implementations.
     */
    EncapsulatedValue() MOZ_DELETE;
    EncapsulatedValue(const EncapsulatedValue &v) MOZ_DELETE;
    EncapsulatedValue &operator=(const Value &v) MOZ_DELETE;
    EncapsulatedValue &operator=(const EncapsulatedValue &v) MOZ_DELETE;

    EncapsulatedValue(const Value &v) : value(v) {}
    ~EncapsulatedValue() {}

  public:
    bool operator==(const EncapsulatedValue &v) const { return value == v.value; }
    bool operator!=(const EncapsulatedValue &v) const { return value != v.value; }

    const Value &get() const { return value; }
    Value *unsafeGet() { return &value; }
    operator const Value &() const { return value; }

    JSGCTraceKind gcKind() const { return value.gcKind(); }

    uint64_t asRawBits() const { return value.asRawBits(); }

    static inline void writeBarrierPre(const Value &v);
    static inline void writeBarrierPre(JSCompartment *comp, const Value &v);

  protected:
    inline void pre();
    inline void pre(JSCompartment *comp);

  private:
    friend class ValueOperations<EncapsulatedValue>;
    const Value * extract() const { return &value; }
};

class HeapValue : public EncapsulatedValue
{
  public:
    explicit inline HeapValue();
    explicit inline HeapValue(const Value &v);
    explicit inline HeapValue(const HeapValue &v);
    inline ~HeapValue();

    inline void init(const Value &v);
    inline void init(JSCompartment *comp, const Value &v);

    inline HeapValue &operator=(const Value &v);
    inline HeapValue &operator=(const HeapValue &v);

    /*
     * This is a faster version of operator=. Normally, operator= has to
     * determine the compartment of the value before it can decide whether to do
     * the barrier. If you already know the compartment, it's faster to pass it
     * in.
     */
    inline void set(JSCompartment *comp, const Value &v);

    static inline void writeBarrierPost(const Value &v, Value *addr);
    static inline void writeBarrierPost(JSCompartment *comp, const Value &v, Value *addr);

  private:
    inline void post();
    inline void post(JSCompartment *comp);
};

class RelocatableValue : public EncapsulatedValue
{
  public:
    explicit inline RelocatableValue();
    explicit inline RelocatableValue(const Value &v);
    explicit inline RelocatableValue(const RelocatableValue &v);
    inline ~RelocatableValue();

    inline RelocatableValue &operator=(const Value &v);
    inline RelocatableValue &operator=(const RelocatableValue &v);

  private:
    inline void post();
    inline void post(JSCompartment *comp);
    inline void relocate();
};

class HeapSlot : public EncapsulatedValue
{
    /*
     * Operator= is not valid for HeapSlot because is must take the object and
     * slot offset to provide to the post/generational barrier.
     */
    inline HeapSlot &operator=(const Value &v) MOZ_DELETE;
    inline HeapSlot &operator=(const HeapValue &v) MOZ_DELETE;
    inline HeapSlot &operator=(const HeapSlot &v) MOZ_DELETE;

  public:
    explicit inline HeapSlot() MOZ_DELETE;
    explicit inline HeapSlot(JSObject *obj, uint32_t slot, const Value &v);
    explicit inline HeapSlot(JSObject *obj, uint32_t slot, const HeapSlot &v);
    inline ~HeapSlot();

    inline void init(JSObject *owner, uint32_t slot, const Value &v);
    inline void init(JSCompartment *comp, JSObject *owner, uint32_t slot, const Value &v);

    inline void set(JSObject *owner, uint32_t slot, const Value &v);
    inline void set(JSCompartment *comp, JSObject *owner, uint32_t slot, const Value &v);

    static inline void writeBarrierPost(JSObject *obj, uint32_t slot);
    static inline void writeBarrierPost(JSCompartment *comp, JSObject *obj, uint32_t slotno);

  private:
    inline void post(JSObject *owner, uint32_t slot);
    inline void post(JSCompartment *comp, JSObject *owner, uint32_t slot);
};

/*
 * NOTE: This is a placeholder for bug 619558.
 *
 * Run a post write barrier that encompasses multiple contiguous slots in a
 * single step.
 */
inline void
SlotRangeWriteBarrierPost(JSCompartment *comp, JSObject *obj, uint32_t start, uint32_t count)
{
}

static inline const Value *
Valueify(const EncapsulatedValue *array)
{
    JS_STATIC_ASSERT(sizeof(HeapValue) == sizeof(Value));
    JS_STATIC_ASSERT(sizeof(HeapSlot) == sizeof(Value));
    return (const Value *)array;
}

static inline HeapValue *
HeapValueify(Value *v)
{
    JS_STATIC_ASSERT(sizeof(HeapValue) == sizeof(Value));
    JS_STATIC_ASSERT(sizeof(HeapSlot) == sizeof(Value));
    return (HeapValue *)v;
}

class HeapSlotArray
{
    HeapSlot *array;

  public:
    HeapSlotArray(HeapSlot *array) : array(array) {}

    operator const Value *() const { return Valueify(array); }
    operator HeapSlot *() const { return array; }

    HeapSlotArray operator +(int offset) const { return HeapSlotArray(array + offset); }
    HeapSlotArray operator +(uint32_t offset) const { return HeapSlotArray(array + offset); }
};

class EncapsulatedId
{
  protected:
    jsid value;

    explicit EncapsulatedId() : value(JSID_VOID) {}
    explicit inline EncapsulatedId(jsid id) : value(id) {}
    ~EncapsulatedId() {}

  private:
    EncapsulatedId(const EncapsulatedId &v) MOZ_DELETE;
    EncapsulatedId &operator=(const EncapsulatedId &v) MOZ_DELETE;

  public:
    bool operator==(jsid id) const { return value == id; }
    bool operator!=(jsid id) const { return value != id; }

    jsid get() const { return value; }
    jsid *unsafeGet() { return &value; }
    operator jsid() const { return value; }

  protected:
    inline void pre();
};

class RelocatableId : public EncapsulatedId
{
  public:
    explicit RelocatableId() : EncapsulatedId() {}
    explicit inline RelocatableId(jsid id) : EncapsulatedId(id) {}
    inline ~RelocatableId();

    inline RelocatableId &operator=(jsid id);
    inline RelocatableId &operator=(const RelocatableId &v);
};

class HeapId : public EncapsulatedId
{
  public:
    explicit HeapId() : EncapsulatedId() {}
    explicit inline HeapId(jsid id);
    inline ~HeapId();

    inline void init(jsid id);

    inline HeapId &operator=(jsid id);
    inline HeapId &operator=(const HeapId &v);

  private:
    inline void post();

    HeapId(const HeapId &v) MOZ_DELETE;
};

/*
 * Incremental GC requires that weak pointers have read barriers. This is mostly
 * an issue for empty shapes stored in JSCompartment. The problem happens when,
 * during an incremental GC, some JS code stores one of the compartment's empty
 * shapes into an object already marked black. Normally, this would not be a
 * problem, because the empty shape would have been part of the initial snapshot
 * when the GC started. However, since this is a weak pointer, it isn't. So we
 * may collect the empty shape even though a live object points to it. To fix
 * this, we mark these empty shapes black whenever they get read out.
 */
template<class T>
class ReadBarriered
{
    T *value;

  public:
    ReadBarriered() : value(NULL) {}
    ReadBarriered(T *value) : value(value) {}

    T *get() const {
        if (!value)
            return NULL;
        T::readBarrier(value);
        return value;
    }

    operator T*() const { return get(); }

    T &operator*() const { return *get(); }
    T *operator->() const { return get(); }

    T **unsafeGet() { return &value; }

    void set(T *v) { value = v; }

    operator bool() { return !!value; }
};

class ReadBarrieredValue
{
    Value value;

  public:
    ReadBarrieredValue() : value(UndefinedValue()) {}
    ReadBarrieredValue(const Value &value) : value(value) {}

    inline const Value &get() const;
    Value *unsafeGet() { return &value; }
    inline operator const Value &() const;

    inline JSObject &toObject() const;
};

namespace tl {

template <class T> struct IsRelocatableHeapType<HeapPtr<T> >
                                                    { static const bool result = false; };
template <> struct IsRelocatableHeapType<HeapSlot>  { static const bool result = false; };
template <> struct IsRelocatableHeapType<HeapValue> { static const bool result = false; };
template <> struct IsRelocatableHeapType<HeapId>    { static const bool result = false; };

} /* namespace tl */
} /* namespace js */

#endif /* jsgc_barrier_h___ */
